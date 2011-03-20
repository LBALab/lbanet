#include "NaviMeshHandler.h"
#include "DataLoader.h"
#include "CommonTypes.h"

#include <fstream>
#include <LbaTypes.h>
#include <math.h>

#include "Recast.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourNavMeshQuery.h"

#include "LogHandler.h"

#include <osg/Node>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/LineWidth>
#include <osgUtil/SmoothingVisitor>
#include "OSGHandler.h"



NaviMeshHandler* NaviMeshHandler::_Instance = NULL;

static const int NAVMESHSET_MAGIC = 'M'<<24 | 'S'<<16 | 'E'<<8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct NavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

// These are just sample areas to use consistent values across the samples.
// The use should specify these base on his needs.
enum SamplePolyAreas
{
	SAMPLE_POLYAREA_GROUND,
	SAMPLE_POLYAREA_WATER,
	SAMPLE_POLYAREA_ROAD,
	SAMPLE_POLYAREA_DOOR,
	SAMPLE_POLYAREA_GRASS,
	SAMPLE_POLYAREA_JUMP,
};
enum SamplePolyFlags
{
	SAMPLE_POLYFLAGS_WALK = 0x01,		// Ability to walk (ground, grass, road)
	SAMPLE_POLYFLAGS_SWIM = 0x02,		// Ability to swim (water).
	SAMPLE_POLYFLAGS_DOOR = 0x04,		// Ability to move through doors.
	SAMPLE_POLYFLAGS_JUMP = 0x08,		// Ability to jump.
	SAMPLE_POLYFLAGS_ALL = 0xffff		// All abilities.
};

// Recast build context.
class BuildContext : public rcContext
{
public:
	BuildContext(){}
	virtual ~BuildContext(){}

	
protected:	
	virtual void doLog(const rcLogCategory category, const char* msg, const int len)
	{
		std::string text(msg, len);
		LogHandler::getInstance()->LogToFile("Recast: "+text, category);
	}
};



	//! constructor
/***********************************************************
constructor
***********************************************************/
NavMeshConfig::NavMeshConfig()
{
	// set default values
	m_cellSize = 0.1f;
	m_cellHeight = 0.2f;
	m_agentHeight = 4;
	m_agentRadius = 0.5f;
	m_agentMaxClimb = 0.9f;
	m_agentMaxSlope = 70;
	m_regionMinSize = 8;
	m_regionMergeSize = 20;
	m_monotonePartitioning = false;
	m_edgeMaxLen = 12;
	m_edgeMaxError = 1.3f;
	m_vertsPerPoly = 6;
	m_detailSampleDist = 6;
	m_detailSampleMaxError = 1;
}



/***********************************************************
constructor
***********************************************************/
NaviMeshHandler::NaviMeshHandler(void)
: 	m_triareas(0),
	m_solid(0),
	m_chf(0),
	m_cset(0),
	m_pmesh(0),
	m_dmesh(0),
	m_navMesh(0), 
	m_navQuery(0),
	_root(0)
{
}

/***********************************************************
destructor
***********************************************************/
NaviMeshHandler::~NaviMeshHandler(void)
{
	cleanup();

	if(_root)
		_root = 0;
}


/***********************************************************
cleanup
***********************************************************/
void NaviMeshHandler::cleanup()
{
	delete [] m_triareas;
	m_triareas = 0;
	rcFreeHeightField(m_solid);
	m_solid = 0;
	rcFreeCompactHeightfield(m_chf);
	m_chf = 0;
	rcFreeContourSet(m_cset);
	m_cset = 0;
	rcFreePolyMesh(m_pmesh);
	m_pmesh = 0;
	rcFreePolyMeshDetail(m_dmesh);
	m_dmesh = 0;
	dtFreeNavMesh(m_navMesh);
	m_navMesh = 0;
}


/***********************************************************
singleton pattern
***********************************************************/
NaviMeshHandler * NaviMeshHandler::getInstance()
{
    if(!_Instance)
    {
        _Instance = new NaviMeshHandler();
		return _Instance;
    }
    else
    {
		return _Instance;
    }
}



/***********************************************************
reset mesh
***********************************************************/
void NaviMeshHandler::Reset()
{
	_vertexes.clear();
	_indices.clear();

	_bmin[0] = _bmin[1] = _bmin[2] = 0;
	_bmax[0] = _bmax[1] = _bmax[2] = 0;

	cleanup();
	m_navQuery = dtAllocNavMeshQuery();
}

/***********************************************************
add actor to mesh
***********************************************************/
void NaviMeshHandler::AddActor(const LbaNet::ObjectPhysicDesc & PhysicDesc)
{
	switch(PhysicDesc.TypeShape)
	{
		case LbaNet::TriangleMeshShape:
			AddTriangleMesh(PhysicDesc);
		break;

		case LbaNet::BoxShape:
			AddBox(PhysicDesc);
		break;

		case LbaNet::CapsuleShape:
			AddCapsule(PhysicDesc);
		break;

		case LbaNet::SphereShape:
			AddSphere(PhysicDesc);
		break;
	}
}


/***********************************************************
generate
***********************************************************/
bool NaviMeshHandler::GenerateMesh()
{
	const float* bmin = _bmin;
	const float* bmax = _bmax;
	const float* verts = &_vertexes[0];
	const int nverts = (int)_vertexes.size();
	const int* tris = &_indices[0];
	const int ntris = (int)_indices.size()/3;

	BuildContext m_ctx;
	
	//
	// Step 1. Initialize build config.
	//
	
	// Init build configuration from GUI
	rcConfig m_cfg;	
	memset(&m_cfg, 0, sizeof(m_cfg));
	m_cfg.cs = _config.m_cellSize;
	m_cfg.ch = _config.m_cellHeight;
	m_cfg.walkableSlopeAngle = _config.m_agentMaxSlope;
	m_cfg.walkableHeight = (int)ceilf(_config.m_agentHeight / m_cfg.ch);
	m_cfg.walkableClimb = (int)floorf(_config.m_agentMaxClimb / m_cfg.ch);
	m_cfg.walkableRadius = (int)ceilf(_config.m_agentRadius / m_cfg.cs);
	m_cfg.maxEdgeLen = (int)(_config.m_edgeMaxLen / _config.m_cellSize);
	m_cfg.maxSimplificationError = _config.m_edgeMaxError;
	m_cfg.minRegionArea = (int)rcSqr(_config.m_regionMinSize);		// Note: area = size*size
	m_cfg.mergeRegionArea = (int)rcSqr(_config.m_regionMergeSize);	// Note: area = size*size
	m_cfg.maxVertsPerPoly = (int)_config.m_vertsPerPoly;
	m_cfg.detailSampleDist = _config.m_detailSampleDist < 0.9f ? 0 : _config.m_cellSize * _config.m_detailSampleDist;
	m_cfg.detailSampleMaxError = _config.m_cellHeight * _config.m_detailSampleMaxError;
	
	// Set the area where the navigation will be build.
	// Here the bounds of the input mesh are used, but the
	// area could be specified by an user defined box, etc.
	rcVcopy(m_cfg.bmin, bmin);
	rcVcopy(m_cfg.bmax, bmax);
	rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);


	
	m_ctx.log(RC_LOG_PROGRESS, "Building navigation:");
	m_ctx.log(RC_LOG_PROGRESS, " - %d x %d cells", m_cfg.width, m_cfg.height);
	m_ctx.log(RC_LOG_PROGRESS, " - %.1fK verts, %.1fK tris", nverts/1000.0f, ntris/1000.0f);
	
	//
	// Step 2. Rasterize input polygon soup.
	//
	
	// Allocate voxel heightfield where we rasterize our input data to.
	m_solid = rcAllocHeightfield();
	if (!m_solid)
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'solid'.");
		return false;
	}
	if (!rcCreateHeightfield(&m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not create solid heightfield.");
		return false;
	}
	
	// Allocate array that can hold triangle area types.
	// If you have multiple meshes you need to process, allocate
	// and array which can hold the max number of triangles you need to process.
	m_triareas = new unsigned char[ntris];
	if (!m_triareas)
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'm_triareas' (%d).", ntris);
		return false;
	}
	
	// Find triangles which are walkable based on their slope and rasterize them.
	// If your input data is multiple meshes, you can transform them here, calculate
	// the are type for each of the meshes and rasterize them.
	memset(m_triareas, 0, ntris*sizeof(unsigned char));
	rcMarkWalkableTriangles(&m_ctx, m_cfg.walkableSlopeAngle, verts, nverts, tris, ntris, m_triareas);
	rcRasterizeTriangles(&m_ctx, verts, nverts, tris, m_triareas, ntris, *m_solid, m_cfg.walkableClimb);

	// delete temporary results
	delete [] m_triareas;
	m_triareas = 0;
	

	//
	// Step 3. Filter walkables surfaces.
	//
	
	// Once all geoemtry is rasterized, we do initial pass of filtering to
	// remove unwanted overhangs caused by the conservative rasterization
	// as well as filter spans where the character cannot possibly stand.
	rcFilterLowHangingWalkableObstacles(&m_ctx, m_cfg.walkableClimb, *m_solid);
	rcFilterLedgeSpans(&m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
	rcFilterWalkableLowHeightSpans(&m_ctx, m_cfg.walkableHeight, *m_solid);


	//
	// Step 4. Partition walkable surface to simple regions.
	//

	// Compact the heightfield so that it is faster to handle from now on.
	// This will result more cache coherent data as well as the neighbours
	// between walkable cells will be calculated.
	m_chf = rcAllocCompactHeightfield();
	if (!m_chf)
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'chf'.");
		return false;
	}
	if (!rcBuildCompactHeightfield(&m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf))
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build compact data.");
		return false;
	}
	
	// delete temporary results
	rcFreeHeightField(m_solid);
	m_solid = 0;

		
	// Erode the walkable area by agent radius.
	if (!rcErodeWalkableArea(&m_ctx, m_cfg.walkableRadius, *m_chf))
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not erode.");
		return false;
	}

	// (Optional) Mark areas.
	//const ConvexVolume* vols = m_geom->getConvexVolumes();
	//for (int i  = 0; i < m_geom->getConvexVolumeCount(); ++i)
	//	rcMarkConvexPolyArea(&m_ctx, vols[i].verts, vols[i].nverts, vols[i].hmin, vols[i].hmax, (unsigned char)vols[i].area, *m_chf);
	
	
	if (_config.m_monotonePartitioning)
	{
		// Partition the walkable surface into simple regions without holes.
		// Monotone partitioning does not need distancefield.
		if (!rcBuildRegionsMonotone(&m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
		{
			m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
			return false;
		}
	}
	else
	{
		// Prepare for region partitioning, by calculating distance field along the walkable surface.
		if (!rcBuildDistanceField(&m_ctx, *m_chf))
		{
			m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build distance field.");
			return false;
		}

		// Partition the walkable surface into simple regions without holes.
		if (!rcBuildRegions(&m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
		{
			m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
			return false;
		}
	}

	//
	// Step 5. Trace and simplify region contours.
	//
	
	// Create contours.
	m_cset = rcAllocContourSet();
	if (!m_cset)
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'cset'.");
		return false;
	}
	if (!rcBuildContours(&m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset))
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not create contours.");
		return false;
	}
	
	//
	// Step 6. Build polygons mesh from contours.
	//
	
	// Build polygon navmesh from the contours.
	m_pmesh = rcAllocPolyMesh();
	if (!m_pmesh)
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmesh'.");
		return false;
	}
	if (!rcBuildPolyMesh(&m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh))
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not triangulate contours.");
		return false;
	}
	
	//
	// Step 7. Create detail mesh which allows to access approximate height on each polygon.
	//
	
	m_dmesh = rcAllocPolyMeshDetail();
	if (!m_dmesh)
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmdtl'.");
		return false;
	}

	if (!rcBuildPolyMeshDetail(&m_ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh))
	{
		m_ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build detail mesh.");
		return false;
	}

	// delete temporary results
	rcFreeCompactHeightfield(m_chf);
	m_chf = 0;
	rcFreeContourSet(m_cset);
	m_cset = 0;


	// At this point the navigation mesh data is ready, you can access it from m_pmesh.
	// See duDebugDrawPolyMesh or dtCreateNavMeshData as examples how to access the data.
	
	//
	// (Optional) Step 8. Create Detour data from Recast poly mesh.
	//
	
	// The GUI may allow more max points per polygon than Detour can handle.
	// Only build the detour navmesh if we do not exceed the limit.
	if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
	{
		unsigned char* navData = 0;
		int navDataSize = 0;

		// Update poly flags from areas.
		for (int i = 0; i < m_pmesh->npolys; ++i)
		{
			if (m_pmesh->areas[i] == RC_WALKABLE_AREA)
				m_pmesh->areas[i] = SAMPLE_POLYAREA_GROUND;
				
			if (m_pmesh->areas[i] == SAMPLE_POLYAREA_GROUND ||
				m_pmesh->areas[i] == SAMPLE_POLYAREA_GRASS ||
				m_pmesh->areas[i] == SAMPLE_POLYAREA_ROAD)
			{
				m_pmesh->flags[i] = SAMPLE_POLYFLAGS_WALK;
			}
			else if (m_pmesh->areas[i] == SAMPLE_POLYAREA_WATER)
			{
				m_pmesh->flags[i] = SAMPLE_POLYFLAGS_SWIM;
			}
			else if (m_pmesh->areas[i] == SAMPLE_POLYAREA_DOOR)
			{
				m_pmesh->flags[i] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
			}
		}


		dtNavMeshCreateParams params;
		memset(&params, 0, sizeof(params));
		params.verts = m_pmesh->verts;
		params.vertCount = m_pmesh->nverts;
		params.polys = m_pmesh->polys;
		params.polyAreas = m_pmesh->areas;
		params.polyFlags = m_pmesh->flags;
		params.polyCount = m_pmesh->npolys;
		params.nvp = m_pmesh->nvp;
		params.detailMeshes = m_dmesh->meshes;
		params.detailVerts = m_dmesh->verts;
		params.detailVertsCount = m_dmesh->nverts;
		params.detailTris = m_dmesh->tris;
		params.detailTriCount = m_dmesh->ntris;

		//TODO
		params.offMeshConVerts = 0;
		params.offMeshConRad = 0;
		params.offMeshConDir = 0;
		params.offMeshConAreas = 0;
		params.offMeshConFlags = 0;
		params.offMeshConUserID = 0;
		params.offMeshConCount = 0;


		params.walkableHeight = _config.m_agentHeight;
		params.walkableRadius = _config.m_agentRadius;
		params.walkableClimb = _config.m_agentMaxClimb;
		rcVcopy(params.bmin, m_pmesh->bmin);
		rcVcopy(params.bmax, m_pmesh->bmax);
		params.cs = m_cfg.cs;
		params.ch = m_cfg.ch;
		
		if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
		{
			m_ctx.log(RC_LOG_ERROR, "Could not build Detour navmesh.");
			return false;
		}
		
		m_navMesh = dtAllocNavMesh();
		if (!m_navMesh)
		{
			dtFree(navData);
			m_ctx.log(RC_LOG_ERROR, "Could not create Detour navmesh");
			return false;
		}
		
		dtStatus status;
		
		status = m_navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA);
		if (dtStatusFailed(status))
		{
			dtFree(navData);
			m_ctx.log(RC_LOG_ERROR, "Could not init Detour navmesh");
			return false;
		}
		
		status = m_navQuery->init(m_navMesh, 2048);
		if (dtStatusFailed(status))
		{
			m_ctx.log(RC_LOG_ERROR, "Could not init Detour navmesh query");
			return false;
		}
	}


	//todo for test - remove
	drawNavMesh();

	return true;
}


/***********************************************************
save mesh to file
***********************************************************/
void NaviMeshHandler::SaveToFile(const std::string & filename) const
{
	//save mesh to file
	if (!m_navMesh) 
		return;
	
	FILE* fp = fopen(filename.c_str(), "wb");
	if (!fp)
		return;
	
	// Store header.
	NavMeshSetHeader header;
	header.magic = NAVMESHSET_MAGIC;
	header.version = NAVMESHSET_VERSION;
	header.numTiles = 0;
	for (int i = 0; i < m_navMesh->getMaxTiles(); ++i)
	{
		const dtNavMesh* mesh = m_navMesh;
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		header.numTiles++;
	}
	memcpy(&header.params, m_navMesh->getParams(), sizeof(dtNavMeshParams));
	fwrite(&header, sizeof(NavMeshSetHeader), 1, fp);

	// Store tiles.
	for (int i = 0; i < m_navMesh->getMaxTiles(); ++i)
	{
		const dtNavMesh* mesh = m_navMesh;
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;

		NavMeshTileHeader tileHeader;
		tileHeader.tileRef = m_navMesh->getTileRef(tile);
		tileHeader.dataSize = tile->dataSize;
		fwrite(&tileHeader, sizeof(tileHeader), 1, fp);

		fwrite(tile->data, tile->dataSize, 1, fp);
	}

	fclose(fp);


	// save to obj file for test
	//std::ofstream fileobj((filename+".obj").c_str());
	//for(size_t cv = 0; cv < _vertexes.size(); cv += 3)
	//{
	//	fileobj<<"v "<<	_vertexes[cv]<<" "<<	_vertexes[cv+1]<<" "<<	_vertexes[cv+2]<<std::endl;
	//}
	//fileobj<<std::endl;
	//for(size_t ci = 0; ci < _indices.size(); ci += 3)
	//{
	//	fileobj<<"f "<<	_indices[ci]+1<<"// "<<	_indices[ci+1]+1<<"// "<<	_indices[ci+2]+1<<"//"<<std::endl;
	//}
}


/***********************************************************
load mesh from file
***********************************************************/
void NaviMeshHandler::LoadFromFile(const std::string & filename)
{
	Reset();

	//load mesh from file
	FILE* fp = fopen(filename.c_str(), "rb");
	if (!fp) 
		return;
	
	// Read header.
	NavMeshSetHeader header;
	fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		return;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		return;
	}
	
	m_navMesh = dtAllocNavMesh();
	if (!m_navMesh)
	{
		fclose(fp);
		return;
	}
	dtStatus status = m_navMesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		return;
	}
		
	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i)
	{
		NavMeshTileHeader tileHeader;
		fread(&tileHeader, sizeof(tileHeader), 1, fp);
		if (!tileHeader.tileRef || !tileHeader.dataSize)
			break;

		unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) break;
		memset(data, 0, tileHeader.dataSize);
		fread(data, tileHeader.dataSize, 1, fp);
		
		m_navMesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}
	
	fclose(fp);

	// init query
	status = m_navQuery->init(m_navMesh, 2048);
	if (dtStatusFailed(status))
	{
		BuildContext m_ctx;
		m_ctx.log(RC_LOG_ERROR, "Could not init Detour navmesh query");
		return;
	}

}


/***********************************************************
add vertex
***********************************************************/
void NaviMeshHandler::AddVertex(const LbaNet::PlayerPosition &pos, LbaVec3 ptr,
								bool rotate)
{
	if(rotate)
	{
		LbaQuaternion quat(pos.Rotation, LbaVec3(0, 1, 0));
		quat.rotate(ptr);
	}

	ptr.x += pos.X;
	ptr.y += pos.Y;
	ptr.z += pos.Z;

	// save bounding box
	if(ptr.x < _bmin[0])
		_bmin[0] = ptr.x;
	if(ptr.x > _bmax[0])
		_bmax[0] = ptr.x;
	if(ptr.y < _bmin[1])
		_bmin[1] = ptr.y;
	if(ptr.y > _bmax[1])
		_bmax[1] = ptr.y;
	if(ptr.z < _bmin[2])
		_bmin[2] = ptr.z;
	if(ptr.z > _bmax[2])
		_bmax[2] = ptr.z;

	_vertexes.push_back(ptr.x);
	_vertexes.push_back(ptr.y);
	_vertexes.push_back(ptr.z);
}

/***********************************************************
add trianglemesh
***********************************************************/
void NaviMeshHandler::AddTriangleMesh(const LbaNet::ObjectPhysicDesc & PhysicDesc)
{
	TriangleMeshInfo triinfo("Data/"+PhysicDesc.Filename, true);
	if(triinfo._buffervertex == NULL)
		return;

	unsigned int offset = (unsigned int)_vertexes.size()/3;
	for(unsigned int i=0; i < triinfo._sizevertex; i+=3)
	{
		LbaVec3 pt3(triinfo._buffervertex[i], triinfo._buffervertex[i+1], triinfo._buffervertex[i+2]);
		AddVertex(PhysicDesc.Pos, pt3, true);
	}


	for(unsigned int i=0; i < triinfo._sizeindices; i+=3)
	{
		bool add = true;
		unsigned int nbface = i /3;
		if(nbface < triinfo._sizematerials)
		{
			short mat = triinfo._buffermaterials[nbface];
			if(mat == 17 || mat == 18 || mat == 19) // dont add water
				add = false;
		}

		if(add)
		{
			_indices.push_back(offset+(int)triinfo._bufferindices[i]);
			_indices.push_back(offset+(int)triinfo._bufferindices[i+1]);
			_indices.push_back(offset+(int)triinfo._bufferindices[i+2]);
		}
	}
}



/***********************************************************
AddBox
***********************************************************/
void NaviMeshHandler::AddBox(const LbaNet::PlayerPosition &pos, float sizeX, float sizeY, float sizeZ,
								bool rotate)
{
	unsigned int offset = (unsigned int)_vertexes.size()/3;
	sizeX/=2;
	sizeZ/=2;

	// prepare the 8 vertex
	LbaVec3 pt0(-sizeX, 0, -sizeZ);
	AddVertex(pos, pt0, rotate);
	LbaVec3 pt1(sizeX, 0, -sizeZ);
	AddVertex(pos, pt1, rotate);
	LbaVec3 pt2(sizeX, 0, sizeZ);
	AddVertex(pos, pt2, rotate);
	LbaVec3 pt3(-sizeX, 0, sizeZ);
	AddVertex(pos, pt3, rotate);	
	LbaVec3 pt4(-sizeX, sizeY, -sizeZ);
	AddVertex(pos, pt4, rotate);
	LbaVec3 pt5(sizeX, sizeY, -sizeZ);
	AddVertex(pos, pt5, rotate);
	LbaVec3 pt6(sizeX, sizeY, sizeZ);
	AddVertex(pos, pt6, rotate);
	LbaVec3 pt7(-sizeX, sizeY, sizeZ);
	AddVertex(pos, pt7, rotate);		

	// add indices
	_indices.push_back(offset+0);
	_indices.push_back(offset+1);
	_indices.push_back(offset+2);
	_indices.push_back(offset+2);
	_indices.push_back(offset+3);
	_indices.push_back(offset+0);

	_indices.push_back(offset+4);
	_indices.push_back(offset+7);
	_indices.push_back(offset+6);
	_indices.push_back(offset+6);
	_indices.push_back(offset+5);
	_indices.push_back(offset+4);

	_indices.push_back(offset+3);
	_indices.push_back(offset+2);
	_indices.push_back(offset+6);
	_indices.push_back(offset+6);
	_indices.push_back(offset+7);
	_indices.push_back(offset+3);

	_indices.push_back(offset+0);
	_indices.push_back(offset+4);
	_indices.push_back(offset+5);
	_indices.push_back(offset+5);
	_indices.push_back(offset+1);
	_indices.push_back(offset+0);

	_indices.push_back(offset+1);
	_indices.push_back(offset+5);
	_indices.push_back(offset+6);
	_indices.push_back(offset+6);
	_indices.push_back(offset+2);
	_indices.push_back(offset+1);

	_indices.push_back(offset+0);
	_indices.push_back(offset+3);
	_indices.push_back(offset+7);
	_indices.push_back(offset+7);
	_indices.push_back(offset+4);
	_indices.push_back(offset+0);
}

/***********************************************************
AddBox
***********************************************************/
void NaviMeshHandler::AddBox(const LbaNet::ObjectPhysicDesc & PhysicDesc)
{
	AddBox(PhysicDesc.Pos, PhysicDesc.SizeX, PhysicDesc.SizeY, PhysicDesc.SizeZ, true);
}

/***********************************************************
AddBox
***********************************************************/
void NaviMeshHandler::AddCapsule(const LbaNet::ObjectPhysicDesc & PhysicDesc)
{
	AddBox(PhysicDesc.Pos, PhysicDesc.SizeX-0.1f, PhysicDesc.SizeY, PhysicDesc.SizeX-0.1f, false);
}

/***********************************************************
AddBox
***********************************************************/
void NaviMeshHandler::AddSphere(const LbaNet::ObjectPhysicDesc & PhysicDesc)
{
	AddBox(PhysicDesc.Pos, PhysicDesc.SizeY-0.1f, PhysicDesc.SizeY-0.1f, PhysicDesc.SizeY-0.1f, false);
}


/***********************************************************
draw debug
***********************************************************/
void NaviMeshHandler::drawPolyBoundaries(const dtMeshTile* tile,
										   const unsigned int col, const float linew,
										   bool inner, osg::Group * root)
{
	//static const float thr = 0.01f*0.01f;

	//osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
	//root->addChild(myGeode);

	//osg::ref_ptr<osg::Geometry> m_myGeometry = new osg::Geometry();
	//myGeode->addDrawable(m_myGeometry.get());

	//osg::Vec3Array* myVerticesPoly = new osg::Vec3Array();
	//osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);


	//for (int i = 0; i < tile->header->polyCount; ++i)
	//{
	//	const dtPoly* p = &tile->polys[i];
	//	
	//	if (p->getType() == DT_POLYTYPE_OFFMESH_CONNECTION) continue;
	//	
	//	const dtPolyDetail* pd = &tile->detailMeshes[i];
	//	
	//	for (int j = 0, nj = (int)p->vertCount; j < nj; ++j)
	//	{
	//		unsigned int c = col;
	//		if (inner)
	//		{
	//			if (p->neis[j] == 0) continue;
	//			if (p->neis[j] & DT_EXT_LINK)
	//			{
	//				bool con = false;
	//				for (unsigned int k = p->firstLink; k != DT_NULL_LINK; k = tile->links[k].next)
	//				{
	//					if (tile->links[k].edge == j)
	//					{
	//						con = true;
	//						break;
	//					}
	//				}
	//				if (con)
	//					c = duRGBA(255,255,255,24);
	//				else
	//					c = duRGBA(0,0,0,48);
	//			}
	//			else
	//				c = duRGBA(0,48,64,32);
	//		}
	//		else
	//		{
	//			if (p->neis[j] != 0) continue;
	//		}
	//		
	//		const float* v0 = &tile->verts[p->verts[j]*3];
	//		const float* v1 = &tile->verts[p->verts[(j+1) % nj]*3];
	//		
	//		// Draw detail mesh edges which align with the actual poly edge.
	//		// This is really slow.
	//		for (int k = 0; k < pd->triCount; ++k)
	//		{
	//			const unsigned char* t = &tile->detailTris[(pd->triBase+k)*4];
	//			const float* tv[3];
	//			for (int m = 0; m < 3; ++m)
	//			{
	//				if (t[m] < p->vertCount)
	//					tv[m] = &tile->verts[p->verts[t[m]]*3];
	//				else
	//					tv[m] = &tile->detailVerts[(pd->vertBase+(t[m]-p->vertCount))*3];
	//			}
	//			for (int m = 0, n = 2; m < 3; n=m++)
	//			{
	//				if (((t[3] >> (n*2)) & 0x3) == 0) continue;	// Skip inner detail edges.
	//				if (distancePtLine2d(tv[n],v0,v1) < thr &&
	//					distancePtLine2d(tv[m],v0,v1) < thr)
	//				{
	//					dd->vertex(tv[n], c);
	//					dd->vertex(tv[m], c);
	//				}
	//			}
	//		}
	//	}
	//}

}

/***********************************************************
draw debug
***********************************************************/
void NaviMeshHandler::drawMeshTile(const dtNavMesh* mesh, const dtNavMeshQuery* query,
											const dtMeshTile* tile, osg::Group * root)
{
	dtPolyRef base = mesh->getPolyRefBase(tile);

	osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
	root->addChild(myGeode);

	osg::ref_ptr<osg::Geometry> m_myGeometry = new osg::Geometry();
	myGeode->addDrawable(m_myGeometry.get());

	osg::Vec3Array* myVerticesPoly = new osg::Vec3Array();
	osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);



	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(0,192/255.0f,1,64/255.0f));

	int counter = 0;
	for (int i = 0; i < tile->header->polyCount; ++i)
	{
		const dtPoly* p = &tile->polys[i];
		if (p->getType() == DT_POLYTYPE_OFFMESH_CONNECTION)	// Skip off-mesh links.
			continue;
			
		const dtPolyDetail* pd = &tile->detailMeshes[i];

		//unsigned int col;
		//if (query && query->isInClosedList(base | (dtPolyRef)i))
		//	col = duRGBA(255,196,0,64);
		//else
		//{
		//	if (p->getArea() == 0) // Treat zero area type as default.
		//		col = duRGBA(0,192,255,64);
		//	else
		//		col = duIntToCol(p->getArea(), 64);
		//}
		
		for (int j = 0; j < pd->triCount; ++j)
		{
			const unsigned char* t = &tile->detailTris[(pd->triBase+j)*4];
			for (int k = 0; k < 3; ++k, ++counter)
			{
				if (t[k] < p->vertCount)
				{
					float * ptrtmp = &tile->verts[p->verts[t[k]]*3];
					float vx = *ptrtmp;
					++ptrtmp;
					float vy = *ptrtmp;
					++ptrtmp;
					float vz = *ptrtmp;
					myVerticesPoly->push_back(osg::Vec3(vx,vy,vz));
				}
				else
				{
					float * ptrtmp = &tile->detailVerts[(pd->vertBase+t[k]-p->vertCount)*3];
					float vx = *ptrtmp;
					++ptrtmp;
					float vy = *ptrtmp;
					++ptrtmp;
					float vz = *ptrtmp;
					myVerticesPoly->push_back(osg::Vec3(vx,vy,vz));
				}

				myprimitive->push_back(counter);
			}
		}
	}
						

	m_myGeometry->addPrimitiveSet(myprimitive);
	m_myGeometry->setVertexArray( myVerticesPoly ); 
	osgUtil::SmoothingVisitor::smooth(*(m_myGeometry.get()));


	m_myGeometry->setColorArray(colors);
	m_myGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);


	osg::StateSet* stateset2 = m_myGeometry->getOrCreateStateSet();
	//stateset2->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateset2->setMode( GL_BLEND, osg::StateAttribute::ON );
	stateset2->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
	stateset2->setRenderBinDetails( 40, "DepthSortedBin");

	// Draw inter poly boundaries
	//drawPolyBoundaries(tile, duRGBA(0,48,64,32), 1.5f, true);
	
	// Draw outer poly boundaries
	//drawPolyBoundaries(tile, duRGBA(0,48,64,220), 2.5f, false);
}

/***********************************************************
draw debug
***********************************************************/
void NaviMeshHandler::drawNavMesh()
{
	if(!m_navMesh)
		return;

	if(_root)
	{
		OsgHandler::getInstance()->RemoveActorNode(_root, false);
		_root = 0;
	}

	_root = OsgHandler::getInstance()->AddEmptyActorNode(false);
	osg::Matrixd Trans;
	osg::Matrixd Rotation;
	Trans.makeTranslate(0, 0, 0);
	LbaQuaternion Q(0, LbaVec3(0,1,0));
	Rotation.makeRotate(osg::Quat(Q.X, Q.Y, Q.Z, Q.W));
	_root->setMatrix(Rotation * Trans);



	for (int i = 0; i < m_navMesh->getMaxTiles(); ++i)
	{
		const dtNavMesh* mesh = m_navMesh;
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile->header) 
			continue;

		drawMeshTile(m_navMesh, 0, tile, _root.get());
	}
}