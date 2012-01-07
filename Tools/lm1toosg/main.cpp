#include "LBA1ModelClass.h"
#include <osgDB/FileUtils>
#include <osgUtil/Optimizer>
#include <osgDB/WriteFile>
#include "Entities.h"
#include "Lba1ModelPath.h"

void Test()
{
	entitiesTableStruct* entities = parseEntities(Lba1ModelDataPath+"FILE3D.HQR");
	LBA1ModelClass lba1mode(entities, Lba1ModelDataPath+"BODY.HQR", 
										Lba1ModelDataPath+"ANIM.HQR", 0, 0);
	osg::ref_ptr<osg::Node> modelnode = lba1mode.ExportOSGModel(false);

	//osgUtil::Optimizer optOSGFile;
	//optOSGFile.optimize (modelnode.get());
	osgDB::writeNodeFile(*modelnode.get(), "test.osgb", new osgDB::Options("Compressor=zlib"));	
}

void Convert(const std::string & filename, const std::string & outfilename)
{
	LBA1ModelClass lba1mode(filename, 5, true);
	osg::ref_ptr<osg::Node> modelnode = lba1mode.ExportOSGModel(true);

	osgUtil::Optimizer optOSGFile;
	optOSGFile.optimize (modelnode.get());

	osgDB::writeNodeFile(*modelnode.get(), outfilename, new osgDB::Options("Compressor=zlib"));	
}

int main(int argc, char** argv)
{
	Convert("RESS10.lm1", "TwinsenHolo.osgb");
	Convert("RESS11.lm1", "ArrowHolo.osgb");
	Convert("RESS12.lm1", "TwinsenArrowHolo.osgb");
	Convert("RESS30.lm1", "DotHolo.osgb");
	return 0;
}
