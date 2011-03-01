#include <map>
#include <set>
#include <fstream>


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>


#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/WriteFile>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgUtil/Optimizer>
#include <osgUtil/SmoothingVisitor>


const static int BUF_SIZE = 4096;
using std::ios_base;

void copyfile(const std::string & source, const std::string & dest)
{
   std::ifstream in(source.c_str(), ios_base::in | ios_base::binary);
   std::ofstream out(dest.c_str(), ios_base::out | ios_base::binary);

   char buf[BUF_SIZE];
   do 
   {
      in.read(&buf[0], BUF_SIZE);
      out.write(&buf[0], in.gcount( ));
   } 
   while (in.gcount( ) > 0);



   in.close( );
   out.close( );
}




int main(int argc, char** argv)
{
	osgDB::setDataFilePathList("./Out");


	// Create an empty property tree object
	using boost::property_tree::ptree;
	ptree pt;

	// Load the XML file into the property tree
	try
	{
		read_xml("sprites.xml", pt);
	}
	catch(...)
	{
		return 0;
	}

	// get text info
	try
	{
		BOOST_FOREACH(ptree::value_type &v, pt.get_child("sprites"))
		{
			long Id = v.second.get<long>("<xmlattr>.id");
			std::string filename = v.second.get<std::string>("<xmlattr>.filename");
			filename = filename.substr(filename.find("/")+1);
			filename = filename.substr(filename.find("/")+1);

			std::stringstream modelname;
			modelname<<"sprite";
			if(Id < 10)
				modelname<<"0";
			if(Id < 100)
				modelname<<"0";
			modelname<<Id;

			std::string dest = "Out/"+modelname.str()+".png";
			copyfile(filename, dest);

			// load an image by reading a file: 
			std::string imagef = modelname.str()+".png";
			osg::Image* klnFace = osgDB::readImageFile(imagef);
			float TextureWidthInPixels  = klnFace->s();
			float TextureHeightInPixels  = klnFace->t();


			osg::ref_ptr<osg::Group> root = new osg::Group();
			osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
			root->addChild(myGeode.get());

			ptree::iterator itspX= v.second.begin();
			ptree::iterator endspX= v.second.end();
			for(; itspX != endspX; ++itspX)
			{
				ptree::value_type v2 = *itspX;
				if(v2.first == "textpart")
				{
					float BottomLeftCornerX = v2.second.get<float>("<xmlattr>.BottomLeftCornerX"); 
					float BottomLeftCornerY = v2.second.get<float>("<xmlattr>.BottomLeftCornerY"); 
					float BottomLeftCornerZ = v2.second.get<float>("<xmlattr>.BottomLeftCornerZ"); 
					float TopRightCornerX = v2.second.get<float>("<xmlattr>.TopRightCornerX"); 
					float TopRightCornerY = v2.second.get<float>("<xmlattr>.TopRightCornerY"); 
					float TopRightCornerZ = v2.second.get<float>("<xmlattr>.TopRightCornerZ"); 
					float BottomRightCornerX = v2.second.get<float>("<xmlattr>.BottomRightCornerX"); 
					float BottomRightCornerY = v2.second.get<float>("<xmlattr>.BottomRightCornerY"); 
					float BottomRightCornerZ = v2.second.get<float>("<xmlattr>.BottomRightCornerZ"); 
					float TopLeftCornerX = v2.second.get<float>("<xmlattr>.TopLeftCornerX"); 
					float TopLeftCornerY = v2.second.get<float>("<xmlattr>.TopLeftCornerY"); 
					float TopLeftCornerZ = v2.second.get<float>("<xmlattr>.TopLeftCornerZ"); 

					float BottomLeftTextcoordX = v2.second.get<long>("<xmlattr>.BottomLeftTextcoordX"); 
					float BottomLeftTextcoordY = v2.second.get<long>("<xmlattr>.BottomLeftTextcoordY"); 
					float BottomRightTextcoordX = v2.second.get<long>("<xmlattr>.BottomRightTextcoordX"); 
					float BottomRightTextcoordY = v2.second.get<long>("<xmlattr>.BottomRightTextcoordY"); 
					float TopLeftTextcoordX = v2.second.get<long>("<xmlattr>.TopLeftTextcoordX"); 
					float TopLeftTextcoordY = v2.second.get<long>("<xmlattr>.TopLeftTextcoordY"); 
					float TopRightTextcoordX = v2.second.get<long>("<xmlattr>.TopRightTextcoordX"); 
					float TopRightTextcoordY = v2.second.get<long>("<xmlattr>.TopRightTextcoordY"); 



					osg::ref_ptr<osg::Geometry> myGeometry = new osg::Geometry();
					myGeode->addDrawable(myGeometry.get());

					osg::Vec3Array* myVertices = new osg::Vec3Array;
					osg::Vec2Array* myTexts = new osg::Vec2Array;
					osg::Vec4Array* myColors = new osg::Vec4Array;
					myColors->push_back(osg::Vec4(1, 1, 1, 1));

					osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
					myprimitive->push_back(0);
					myprimitive->push_back(1);
					myprimitive->push_back(2);
					myprimitive->push_back(3);

					myTexts->push_back(osg::Vec2(TopRightTextcoordX/TextureWidthInPixels, TopRightTextcoordY/TextureHeightInPixels));
					myTexts->push_back(osg::Vec2(TopLeftTextcoordX/TextureWidthInPixels, TopLeftTextcoordY/TextureHeightInPixels));
					myTexts->push_back(osg::Vec2(BottomLeftTextcoordX/TextureWidthInPixels, BottomLeftTextcoordY/TextureHeightInPixels));
					myTexts->push_back(osg::Vec2(BottomRightTextcoordX/TextureWidthInPixels, BottomRightTextcoordY/TextureHeightInPixels));

					myVertices->push_back(osg::Vec3(TopRightCornerX, TopRightCornerY, TopRightCornerZ));
					myVertices->push_back(osg::Vec3(TopLeftCornerX,  TopLeftCornerY, TopLeftCornerZ));
					myVertices->push_back(osg::Vec3(BottomLeftCornerX, BottomLeftCornerY, BottomLeftCornerZ));
					myVertices->push_back(osg::Vec3(BottomRightCornerX, BottomRightCornerY, BottomRightCornerZ));


					myGeometry->addPrimitiveSet(myprimitive);
					myGeometry->setVertexArray( myVertices ); 
					myGeometry->setTexCoordArray(0, myTexts);

					myGeometry->setColorArray(myColors);
					myGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

					osgUtil::SmoothingVisitor::smooth(*(myGeometry.get()));
				}
			}



			osg::StateSet* stateSet = root->getOrCreateStateSet();

			// Enable blending, select transparent bin.
			stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
			stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );


			osg::ref_ptr<osg::Texture2D> KLN89FaceTexture = new osg::Texture2D;

			// protect from being optimized away as static state:
			KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 



			// Assign the texture to the image we read from file: 
			KLN89FaceTexture->setImage(klnFace);

			KLN89FaceTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
			KLN89FaceTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

			KLN89FaceTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
			KLN89FaceTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
			KLN89FaceTexture->setUseHardwareMipMapGeneration(false);
			KLN89FaceTexture->setResizeNonPowerOfTwoHint(false);

			// Assign texture unit 0 of our new StateSet to the texture 
			// we just created and enable the texture.
			stateSet->setTextureAttributeAndModes
			  (0,KLN89FaceTexture,osg::StateAttribute::ON);

			osgUtil::Optimizer optOSGFile;
			optOSGFile.optimize (root.get());

			osgDB::writeNodeFile(*root.get(), modelname.str()+".osgb", new osgDB::Options("Compressor=zlib"));

		}
	}
	catch(...){} // no text


	return 0;
}














