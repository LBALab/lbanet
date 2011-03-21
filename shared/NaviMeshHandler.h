/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/


#if !defined(__LbaNetModel_NaviMeshHandler_h)
#define __LbaNetModel_NaviMeshHandler_h

#include <string>
#include <vector>
#include <osg/ref_ptr>

namespace LbaNet
{
	struct ObjectPhysicDesc;
	struct PlayerPosition;
};

namespace osg
{
	class Group;
	class MatrixTransform;
};

class LbaVec3;

class dtNavMesh;
class dtNavMeshQuery;
class dtMeshTile;
class rcHeightfield;
class rcCompactHeightfield;
class rcContourSet;
class rcPolyMesh;
class rcPolyMeshDetail;


class NavMeshConfig
{
public:
	//! constructor
	NavMeshConfig();

	float						m_cellSize;
	float						m_cellHeight;
	float						m_agentHeight;
	float						m_agentRadius;
	float						m_agentMaxClimb;
	float						m_agentMaxSlope;
	float						m_regionMinSize;
	float						m_regionMergeSize;
	bool						m_monotonePartitioning;
	float						m_edgeMaxLen;
	float						m_edgeMaxError;
	float						m_vertsPerPoly;
	float						m_detailSampleDist;
	float						m_detailSampleMaxError;
};

/***********************************************************************
 * Module:  NaviMeshHandler.h
 * Author:  Vivien
 * Purpose: Used to handle navigation mesh
 ***********************************************************************/
class NaviMeshHandler
{
public:
	//! constructor
	NaviMeshHandler(void);

	//! destructor
	~NaviMeshHandler(void);

	//! reset mesh
	void Reset();

	//! add actor to mesh
	void AddActor(const LbaNet::ObjectPhysicDesc & PhysicDesc);

	//! generate
	bool GenerateMesh();

	//! save mesh to file
	void SaveToFile(const std::string & filename) const;

	//! load mesh from file
	void LoadFromFile(const std::string & filename);


	//! get config
	NavMeshConfig GetConfig() const
	{ return _config;}

	//! set config
	void SetConfig(const NavMeshConfig & cfg)
	{ _config = cfg;}


	//! toogle debug display
	void ToogleDebugDisplay(bool Display);

	//! calculate path
	//! return path size
	int CalculatePath(const LbaVec3 & Start, const LbaVec3 & End);

	//! draw last calculated path
	void DrawLastPath();

protected:


	NaviMeshHandler(const NaviMeshHandler &);
	const NaviMeshHandler & operator=(const NaviMeshHandler &);

	//! add trianglemesh
	void AddTriangleMesh(const LbaNet::ObjectPhysicDesc & PhysicDesc);

	//! AddBox
	void AddBox(const LbaNet::ObjectPhysicDesc & PhysicDesc);

	//! AddBox
	void AddCapsule(const LbaNet::ObjectPhysicDesc & PhysicDesc);

	//! AddBox
	void AddSphere(const LbaNet::ObjectPhysicDesc & PhysicDesc);

	//! clean up
	void cleanup();

	//! add vertex
	void AddVertex(const LbaNet::PlayerPosition &pos, LbaVec3 ptr,
					bool rotate);

	//! add box
	void AddBox(const LbaNet::PlayerPosition &pos, float sizeX, float sizeY, float sizeZ,
					bool rotate);



	// debug draw
	void drawPolyBoundaries(const dtMeshTile* tile,
							    const float linew,
							   bool inner, osg::Group * root);
	// debug draw
	void drawMeshTile(const dtNavMesh* mesh, const dtNavMeshQuery* query,
							const dtMeshTile* tile, osg::Group * root);
	// debug draw
	void drawNavMesh();



private:
	std::vector<float>			_vertexes;
	std::vector<int>			_indices;

	float						_bmin[3];
	float						_bmax[3];


	unsigned char*				m_triareas;
	rcHeightfield*				m_solid;
	rcCompactHeightfield*		m_chf;
	rcContourSet*				m_cset;
	rcPolyMesh*					m_pmesh;
	rcPolyMeshDetail*			m_dmesh;
	dtNavMesh*					m_navMesh;
	dtNavMeshQuery*				m_navQuery;


	NavMeshConfig				_config;

	osg::ref_ptr<osg::MatrixTransform>	_root;
	osg::ref_ptr<osg::MatrixTransform>	_rootpath;

	static const int			MAX_POLYS = 256;
	static const int			MAX_SMOOTH = 2048;
	unsigned int				m_polys[MAX_POLYS];
	float						m_smoothPath[MAX_SMOOTH*3];
	int							m_nsmoothPath;

};

#endif
