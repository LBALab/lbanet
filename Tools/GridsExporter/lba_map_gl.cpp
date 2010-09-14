#include "lba_map_gl.h"


#include <sstream>

#include <IL/il.h>
#include <IL/ilu.h>


#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/WriteFile>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgUtil/Optimizer>


void LBA_MAP_GL::face(double X,double Y,double Z,double texture_x,double texture_y,double h,int a,int b,int c,bool hidden)
{
    double vertex[20][3];
    double uv[24][2];
    for(int i=0;i<20;i++)
    vertex[i][0]=vertex[i][1]=vertex[i][2]=0.;

    vertex[ 0][0]=X+0.;vertex[ 0][1]=Y*h+h ,vertex[ 0][2]=Z+0.;
    vertex[ 1][0]=X+0.;vertex[ 1][1]=Y*h+h ,vertex[ 1][2]=Z+0.;
    vertex[ 2][0]=X+0.;vertex[ 2][1]=Y*h+h ,vertex[ 2][2]=Z+1.;
    vertex[ 3][0]=X+0.;vertex[ 3][1]=Y*h+h ,vertex[ 3][2]=Z+1.;
    vertex[ 4][0]=X+0.;vertex[ 4][1]=Y*h+0.,vertex[ 4][2]=Z+0.;
    vertex[ 5][0]=X+0.;vertex[ 5][1]=Y*h+0.,vertex[ 5][2]=Z+0.;
    vertex[ 6][0]=X+0.;vertex[ 6][1]=Y*h+0.,vertex[ 6][2]=Z+0.;
    vertex[ 7][0]=X+0.;vertex[ 7][1]=Y*h+0.,vertex[ 7][2]=Z+0.;
    vertex[ 8][0]=X+1.;vertex[ 8][1]=Y*h+h ,vertex[ 8][2]=Z+0.;
    vertex[ 9][0]=X+1.;vertex[ 9][1]=Y*h+h ,vertex[ 9][2]=Z+0.;
    vertex[10][0]=X+0.;vertex[10][1]=Y*h+0.,vertex[10][2]=Z+1.;
    vertex[11][0]=X+0.;vertex[11][1]=Y*h+0.,vertex[11][2]=Z+1.;
    vertex[12][0]=X+1.;vertex[12][1]=Y*h+h ,vertex[12][2]=Z+1.;
    vertex[13][0]=X+1.;vertex[13][1]=Y*h+h ,vertex[13][2]=Z+1.;
    vertex[14][0]=X+1.;vertex[14][1]=Y*h+h ,vertex[14][2]=Z+1.;
    vertex[15][0]=X+1.;vertex[15][1]=Y*h+h ,vertex[15][2]=Z+1.;
    vertex[16][0]=X+1.;vertex[16][1]=Y*h+0.,vertex[16][2]=Z+0.;
    vertex[17][0]=X+1.;vertex[17][1]=Y*h+0.,vertex[17][2]=Z+0.;
    vertex[18][0]=X+1.;vertex[18][1]=Y*h+0.,vertex[18][2]=Z+1.;
    vertex[19][0]=X+1.;vertex[19][1]=Y*h+0.,vertex[19][2]=Z+1.;

//UV shared + OFFSET 0.5 NOT MIRRORED
    uv[0][0]=23.5;   uv[0][1]=0.5;
    uv[1][0]=23.5;   uv[1][1]=0.5;
    uv[2][0]=0.5;    uv[2][1]=11;
    uv[3][0]=0.5;   uv[3][1]=13.;
    uv[4][0]=23.5;  uv[4][1]=13.5;
    uv[5][0]=23.5;  uv[5][1]=13.5;
    uv[6][0]=23.5;  uv[6][1]=15.5;
    uv[7][0]=23.5;  uv[7][1]=15.5;
    uv[8][0]=46.5;  uv[8][1]=11;
    uv[9][0]=46.5;  uv[9][1]=13.;
    uv[10][0]=0.5;   uv[10][1]=24.5;
    uv[11][0]=0.5;   uv[11][1]=26;
    uv[12][0]=23.5; uv[12][1]=21.5;
    uv[13][0]=23.5;  uv[13][1]=21.5;
    uv[14][0]=22.5; uv[14][1]=24.;
    uv[15][0]=24.5; uv[15][1]=24.;
    uv[16][0]=46.5; uv[16][1]=24.5;
    uv[17][0]=46.5; uv[17][1]=26;
    uv[18][0]=22.5; uv[18][1]=36.5;
    uv[19][0]=24.5; uv[19][1]=36.5;


    double ab[3];
    ab[0]=vertex[b][0]-vertex[a][0];
    ab[1]=vertex[b][1]-vertex[a][1];
    ab[2]=vertex[b][2]-vertex[a][2];
    double ac[3];
    ac[0]=vertex[c][0]-vertex[a][0];
    ac[1]=vertex[c][1]-vertex[a][1];
    ac[2]=vertex[c][2]-vertex[a][2];
    double n[3];
    n[0]=ab[1]*ac[2]-ac[1]*ab[2];
    n[1]=ab[2]*ac[0]-ac[2]*ab[0];
    n[2]=ab[0]*ac[1]-ac[0]*ab[1];
    double l=sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    double g[3];
    g[0]=(vertex[a][0]+vertex[b][0]+vertex[c][0])/3.;
    g[1]=(vertex[a][1]+vertex[b][1]+vertex[c][1])/3.;
    g[2]=(vertex[a][2]+vertex[b][2]+vertex[c][2])/3.;
	
	double f=0.5;

	LBA_FACE face;
	face.v[0]=vertex[a][0];
	face.v[1]=vertex[a][1];
	face.v[2]=vertex[a][2];
	face.v[3]=vertex[b][0];
	face.v[4]=vertex[b][1];
	face.v[5]=vertex[b][2];
	face.v[6]=vertex[c][0];
	face.v[7]=vertex[c][1];
	face.v[8]=vertex[c][2];
	
	if(hidden)
	{
		face.vt[0]=0.;
		face.vt[1]=0.;
		face.vt[2]=0.;
		face.vt[3]=0.;
		face.vt[4]=0.;
		face.vt[5]=0.;
	}
	else
	{
		face.vt[0]=(texture_x+uv[a][0])/2048.;
		face.vt[1]=(texture_y+uv[a][1])/2048.;
		face.vt[2]=(texture_x+uv[b][0])/2048.;
		face.vt[3]=(texture_y+uv[b][1])/2048.;
		face.vt[4]=(texture_x+uv[c][0])/2048.;
		face.vt[5]=(texture_y+uv[c][1])/2048.;
	}

	face.vn[0]=n[0]/l;
	face.vn[1]=n[1]/l;
	face.vn[2]=n[2]/l;
	lba_face.push_back(face);
}


// initialize LBA_MAP_GL
void LBA_MAP_GL::Initialize(int LBA2)
{
	nb_faces.clear();
	islba2 = LBA2;

    int i,j,k;
    int offset_x,offset_y;
    texture_map=new unsigned char[2048*2048*4];
	memset(texture_map, 0, 2048*2048*4*sizeof(unsigned char));

    LBA_SHARED_BRICK *shared_brick1= new LBA_SHARED_BRICK[lba_map->number_brick];
    LBA_SHARED_BRICK *shared_brick2= new LBA_SHARED_BRICK[lba_map->number_brick];


    for(int i=0;i<lba_map->number_brick;i++)
      shared_brick1[i].id=-1,shared_brick1[i].dx=0,shared_brick1[i].dz=0;
    for(int i=0;i<lba_map->number_brick;i++)
      shared_brick2[i].id=-1,shared_brick2[i].dx=0,shared_brick2[i].dz=0;



	for(int Z=0;Z<64;Z++)
	for(int X=0;X<64;X++)
	for(int Y=0;Y<25;Y++)
	if(lba_map->brick_list[lba_map->grid->info_brick[X][Z][Y].index_brick]!=126)//LBA2 temple of bu 2nd scene : some inivsible walls have same brick index (127) than a shaped brick (layout 183 object 52 brick 1)
	{
	//    if(lba_map->grid->info_brick[X][Z][Y].shape==3)printf("%d %d %d %d\n",X,Y,Z,lba_map->brick_list[lba_map->grid->info_brick[X][Z][Y].index_brick]);
		if(lba_map->grid->info_brick[X][Z][Y].index_brick!=-1)
		{
			if(
			X<63&&
			lba_map->grid->info_brick[X+1][Z][Y].shape!=1&&
			lba_map->grid->info_brick[X+1][Z][Y].index_brick!=-1&&
			(lba_map->grid->info_brick[X][Z][Y].shape==4||
			 lba_map->grid->info_brick[X][Z][Y].shape==9||
			 lba_map->grid->info_brick[X][Z][Y].shape==12||
			 lba_map->grid->info_brick[X][Z][Y].shape==3)&&
			lba_map->grid->info_brick[X][Z][Y].object==lba_map->grid->info_brick[X+1][Z][Y].object)
			{
				shared_brick1[lba_map->grid->info_brick[X][Z][Y].index_brick].id=lba_map->grid->info_brick[X+1][Z][Y].index_brick;
				shared_brick1[lba_map->grid->info_brick[X][Z][Y].index_brick].dx=1;
				shared_brick1[lba_map->grid->info_brick[X][Z][Y].index_brick].dz=0;
			}
		   if(
			  Z<63&&
			   lba_map->grid->info_brick[X][Z+1][Y].shape!=1&&
			   lba_map->grid->info_brick[X][Z+1][Y].index_brick!=-1&&
			  (lba_map->grid->info_brick[X][Z][Y].shape==5||
			   lba_map->grid->info_brick[X][Z][Y].shape==7||
			   lba_map->grid->info_brick[X][Z][Y].shape==2||
			   lba_map->grid->info_brick[X][Z][Y].shape==13||
			   lba_map->grid->info_brick[X][Z][Y].shape==10)&&//&&lba_map->grid->info_brick[X][Z][Y].object==lba_map->grid->info_brick[X][Z+1][Y].object)
			  lba_map->grid->info_brick[X][Z][Y].object==lba_map->grid->info_brick[X][Z+1][Y].object)
			{
				shared_brick1[lba_map->grid->info_brick[X][Z][Y].index_brick].id=lba_map->grid->info_brick[X][Z+1][Y].index_brick;
				shared_brick1[lba_map->grid->info_brick[X][Z][Y].index_brick].dx=0;
				shared_brick1[lba_map->grid->info_brick[X][Z][Y].index_brick].dz=1;
			}
			if(
			X<63&&
			lba_map->grid->info_brick[X+1][Z][Y].shape!=1&&
			lba_map->grid->info_brick[X+1][Z][Y].index_brick!=-1&&
		   (lba_map->grid->info_brick[X][Z][Y].shape==7||
			lba_map->grid->info_brick[X][Z][Y].shape==10)&&
		   lba_map->grid->info_brick[X][Z][Y].object==lba_map->grid->info_brick[X+1][Z][Y].object)
			{
				shared_brick2[lba_map->grid->info_brick[X][Z][Y].index_brick].id=lba_map->grid->info_brick[X+1][Z][Y].index_brick;
				shared_brick2[lba_map->grid->info_brick[X][Z][Y].index_brick].dx=1;
				shared_brick2[lba_map->grid->info_brick[X][Z][Y].index_brick].dz=0;
			}



		}
	}



    for(i=0;i<lba_map->number_brick;i++)
    {
        offset_x=(i%42);offset_x*=48;
        offset_y=(i/42);offset_y*=38;
        for(j=0;j<38;j++)
        for(k=0;k<48;k++)
        {
          texture_map[((offset_y+j)*2048+offset_x+k)*4+0]=lba_map->palet->couleur[lba_map->brick[i].pixel[j][k]][0];
          texture_map[((offset_y+j)*2048+offset_x+k)*4+1]=lba_map->palet->couleur[lba_map->brick[i].pixel[j][k]][1];
          texture_map[((offset_y+j)*2048+offset_x+k)*4+2]=lba_map->palet->couleur[lba_map->brick[i].pixel[j][k]][2];
          if(lba_map->brick[i].pixel[j][k]==0)
          texture_map[((offset_y+j)*2048+offset_x+k)*4+3]=0;
          else
          texture_map[((offset_y+j)*2048+offset_x+k)*4+3]=255;
        }

        if(shared_brick1[i].id!=-1)
        {
            for(j=0;j<38;j++)
            for(k=0;k<48;k++)
            {
                int k2=k-(shared_brick1[i].dx-shared_brick1[i].dz)*24;
                int j2=j-(shared_brick1[i].dx+shared_brick1[i].dz)*12;
                if(j2>=0&&j2<38&&k2>=0&&k2<48&&lba_map->brick[shared_brick1[i].id].pixel[j2][k2]!=0)
                {

                    texture_map[((offset_y+j)*2048+offset_x+k)*4+0]=lba_map->palet->couleur[lba_map->brick[shared_brick1[i].id].pixel[j2][k2]][0];
                    texture_map[((offset_y+j)*2048+offset_x+k)*4+1]=lba_map->palet->couleur[lba_map->brick[shared_brick1[i].id].pixel[j2][k2]][1];
                    texture_map[((offset_y+j)*2048+offset_x+k)*4+2]=lba_map->palet->couleur[lba_map->brick[shared_brick1[i].id].pixel[j2][k2]][2];
                    texture_map[((offset_y+j)*2048+offset_x+k)*4+3]=255;
                }
            }
        }
        if(shared_brick2[i].id!=-1)
        {
            for(j=0;j<38;j++)
            for(k=0;k<48;k++)
            {
                int k2=k-(shared_brick2[i].dx-shared_brick2[i].dz)*24;
                int j2=j-(shared_brick2[i].dx+shared_brick2[i].dz)*12;
                if(j2>=0&&j2<38&&k2>=0&&k2<48&&lba_map->brick[shared_brick2[i].id].pixel[j2][k2]!=0)
                {

                    texture_map[((offset_y+j)*2048+offset_x+k)*4+0]=lba_map->palet->couleur[lba_map->brick[shared_brick2[i].id].pixel[j2][k2]][0];
                    texture_map[((offset_y+j)*2048+offset_x+k)*4+1]=lba_map->palet->couleur[lba_map->brick[shared_brick2[i].id].pixel[j2][k2]][1];
                    texture_map[((offset_y+j)*2048+offset_x+k)*4+2]=lba_map->palet->couleur[lba_map->brick[shared_brick2[i].id].pixel[j2][k2]][2];
                    texture_map[((offset_y+j)*2048+offset_x+k)*4+3]=255;
                }
            }
        }
    }


   texture_map[0]=0;
   texture_map[1]=0;
   texture_map[2]=0;
   texture_map[3]=255;




	ILuint imn;
	ilGenImages(1, &imn);
	ilBindImage(imn);
	ilTexImage( 2048, 2048, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, texture_map);
	ilSaveImage(texture_filename.c_str());
	ilDeleteImages(1, &imn);


    int texture_x,texture_y;
	int X,Y,Z;
	double h=0.5;


	int cmpt=0;
	brick_number=cmpt;

	for(Z=0;Z<64;Z++)
	{
		for(X=0;X<64;X++)
		{
			for(Y=0;Y<25;Y++)
			{
				if(lba_map->grid->info_brick[X][Z][Y].index_brick!=-1)
				{
					  cmpt++;
					  texture_x=(lba_map->grid->info_brick[X][Z][Y].index_brick)%42;
					  texture_x*=48;
					  texture_y=(lba_map->grid->info_brick[X][Z][Y].index_brick)/42;
					  texture_y*=38;

					switch(lba_map->grid->info_brick[X][Z][Y].shape)
					{
						case 1:
							face(X,Y,Z,texture_x,texture_y,h,3,11,18,false);
							face(X,Y,Z,texture_x,texture_y,h,18,14,3,false);
							face(X,Y,Z,texture_x,texture_y,h,15,19,17,false);
							face(X,Y,Z,texture_x,texture_y,h,17,9,15,false);
							face(X,Y,Z,texture_x,texture_y,h,0,2,12,false);
							face(X,Y,Z,texture_x,texture_y,h,13,8,1,false);
							nb_faces.push_back(6);
							break;
						case 2:
							face(X,Y,Z,texture_x,texture_y,h,11,18,14,false);
							face(X,Y,Z,texture_x,texture_y,h,11,13,8,false);
							face(X,Y,Z,texture_x,texture_y,h,8,6,11,false);
							face(X,Y,Z,texture_x,texture_y,h,19,17,9,false);
							face(X,Y,Z,texture_x,texture_y,h,9,15,19,false);
							face(X,Y,Z,texture_x,texture_y,h,9,16,5,false);
							nb_faces.push_back(6);
							break;
						case 3:
							face(X,Y,Z,texture_x,texture_y,h,15,19,17,false);
							face(X,Y,Z,texture_x,texture_y,h,2,12,17,false);
							face(X,Y,Z,texture_x,texture_y,h,17,7,2,false);
							face(X,Y,Z,texture_x,texture_y,h,11,18,14,false);
							face(X,Y,Z,texture_x,texture_y,h,14,3,10,false);
							face(X,Y,Z,texture_x,texture_y,h,2,4,10,false);
							nb_faces.push_back(6);
							break;
						case 4:
							face(X,Y,Z,texture_x,texture_y,h,11,18,8,false);
							face(X,Y,Z,texture_x,texture_y,h,8,1,11,false);
							face(X,Y,Z,texture_x,texture_y,h,19,17,9,false);
							face(X,Y,Z,texture_x,texture_y,h,1,8,16,false);
							face(X,Y,Z,texture_x,texture_y,h,16,5,1,false);
							face(X,Y,Z,texture_x,texture_y,h,0,4,10,false);
							nb_faces.push_back(6);
							break;
						case 5:
							face(X,Y,Z,texture_x,texture_y,h,19,17,0,false);
							face(X,Y,Z,texture_x,texture_y,h,0,2,19,false);
							face(X,Y,Z,texture_x,texture_y,h,3,11,18,false);
							face(X,Y,Z,texture_x,texture_y,h,1,16,5,false);
							face(X,Y,Z,texture_x,texture_y,h,2,0,4,false);
							face(X,Y,Z,texture_x,texture_y,h,4,10,3,false);
							nb_faces.push_back(6);
							break;
						case 6:
							face(X,Y,Z,texture_x,texture_y,h,4,2,12,false);
							face(X,Y,Z,texture_x,texture_y,h,13,8,5,false);
							face(X,Y,Z,texture_x,texture_y,h,3,11,18,false);
							face(X,Y,Z,texture_x,texture_y,h,18,14,3,false);
							face(X,Y,Z,texture_x,texture_y,h,19,17,9,false);
							face(X,Y,Z,texture_x,texture_y,h,9,15,19,false);
							face(X,Y,Z,texture_x,texture_y,h,5,9,16,false);
							face(X,Y,Z,texture_x,texture_y,h,4,3,10,false);
							nb_faces.push_back(8);
							break;
						case 7:
							face(X,Y,Z,texture_x,texture_y,h,19,8,1,false);
							face(X,Y,Z,texture_x,texture_y,h,0,2,18,false);
							face(X,Y,Z,texture_x,texture_y,h,3,11,18,false);
							face(X,Y,Z,texture_x,texture_y,h,19,17,9,false);
							face(X,Y,Z,texture_x,texture_y,h,1,8,16,false);
							face(X,Y,Z,texture_x,texture_y,h,16,5,1,false);
							face(X,Y,Z,texture_x,texture_y,h,10,2,0,false);
							face(X,Y,Z,texture_x,texture_y,h,0,4,10,false);
							nb_faces.push_back(8);
							break;
						case 8:
							face(X,Y,Z,texture_x,texture_y,h,0,4,10,false);
							face(X,Y,Z,texture_x,texture_y,h,10,13,8,false);
							face(X,Y,Z,texture_x,texture_y,h,8,1,10,false);
							face(X,Y,Z,texture_x,texture_y,h,11,18,14,false);
							face(X,Y,Z,texture_x,texture_y,h,15,19,17,false);
							face(X,Y,Z,texture_x,texture_y,h,17,9,15,false);
							face(X,Y,Z,texture_x,texture_y,h,1,8,16,false);
							face(X,Y,Z,texture_x,texture_y,h,16,5,1,false);
							nb_faces.push_back(8);
							break;
						case 9:
							face(X,Y,Z,texture_x,texture_y,h,16,0,2,false);
							face(X,Y,Z,texture_x,texture_y,h,2,12,16,false);
							face(X,Y,Z,texture_x,texture_y,h,3,11,18,false);
							face(X,Y,Z,texture_x,texture_y,h,18,14,3,false);
							face(X,Y,Z,texture_x,texture_y,h,15,19,17,false);
							face(X,Y,Z,texture_x,texture_y,h,16,5,1,false);
							face(X,Y,Z,texture_x,texture_y,h,10,2,0,false);
							face(X,Y,Z,texture_x,texture_y,h,0,4,10,false);
							nb_faces.push_back(8);
							break;
						case 10:
							face(X,Y,Z,texture_x,texture_y,h,6,11,12,false);
							face(X,Y,Z,texture_x,texture_y,h,13,17,7,false);
							face(X,Y,Z,texture_x,texture_y,h,11,18,14,false);
							face(X,Y,Z,texture_x,texture_y,h,15,19,17,false);
							nb_faces.push_back(4);
							break;
						case 11:
							face(X,Y,Z,texture_x,texture_y,h,0,11,18,false);
							face(X,Y,Z,texture_x,texture_y,h,19,17,1,false);
							face(X,Y,Z,texture_x,texture_y,h,0,4,10,false);
							face(X,Y,Z,texture_x,texture_y,h,1,5,16,false);
							nb_faces.push_back(4);
							break;
						case 12:
							face(X,Y,Z,texture_x,texture_y,h,11,18,9,false);
							face(X,Y,Z,texture_x,texture_y,h,8,4,10,false);
							face(X,Y,Z,texture_x,texture_y,h,19,17,9,false);
							face(X,Y,Z,texture_x,texture_y,h,8,16,5,false);
							nb_faces.push_back(4);
							break;
						case 13:
							face(X,Y,Z,texture_x,texture_y,h,3,19,17,false);
							face(X,Y,Z,texture_x,texture_y,h,16,5,2,false);
							face(X,Y,Z,texture_x,texture_y,h,2,4,10,false);
							face(X,Y,Z,texture_x,texture_y,h,3,18,11,false);
							nb_faces.push_back(4);
							break;
					}
				}
			}
		}
	}

	printf(" total briques lba_map : %d \n",cmpt);
}


//constructor with gr file
LBA_MAP_GL::LBA_MAP_GL(int LBA2, const std::string &grfile, int layoutused, bool forcelayout)
{
	// set filenames
	texture_filename = grfile;
	texture_filename.replace(texture_filename.size() - 3, 3, "png");
	map_filename = grfile;
	map_filename.replace(map_filename.size() - 3, 3, "ogb");
	map_filename += "b";

	// init map
    lba_map=new LBA_MAP(LBA2, grfile, layoutused, forcelayout);
	Initialize(LBA2);
}


// constructor with map number
LBA_MAP_GL::LBA_MAP_GL(int NUM_MAP,int LBA2)
{
	// set filenames
	std::stringstream filename;
	if(islba2)
		filename<<"Data/Lba2/Grids/map";
	else
		filename<<"Data/Lba1/Grids/map";
	filename<<NUM_MAP;

	texture_filename = filename.str() + ".png";
	map_filename = filename.str() + ".osgb";


	// init map
    lba_map=new LBA_MAP(NUM_MAP,LBA2);
	Initialize(LBA2);
}




unsigned int findvertexinmap(std::map<osg::Vec2, unsigned int> & map, unsigned int & curridx, 
								  osg::Vec3Array* vertexes, const osg::Vec3 & vertex,
								  osg::Vec2Array* texts, const osg::Vec2 & text)
{
	std::map<osg::Vec2, unsigned int>::iterator itm = map.find(text);
	if(itm != map.end())
		return itm->second;

	map[text] = curridx;
	vertexes->push_back(vertex);
	texts->push_back(text);
	return curridx++;
}


void LBA_MAP_GL::ExportMapOSG()
{
	osgDB::setDataFilePathList("./Data");


	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
	root->addChild(myGeode.get());

	int cc=0;
	vector<int>::iterator itnbfaces =  nb_faces.begin();	
	vector<int>::iterator endnbfaces =  nb_faces.end();
	for(;itnbfaces != endnbfaces; ++itnbfaces)
	{

		osg::ref_ptr<osg::Geometry> myGeometry = new osg::Geometry();
		myGeode->addDrawable(myGeometry.get());

		//osg::Vec4Array* colors = new osg::Vec4Array;
		osg::Vec3Array* myVertices = new osg::Vec3Array;
		osg::Vec3Array* myNormals = new osg::Vec3Array;
		osg::Vec2Array* myTexts = new osg::Vec2Array;
		osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

		std::map<osg::Vec2, unsigned int> mapvert;
		unsigned int curridx=0;

		for(int i=0; i<*itnbfaces; ++i, ++cc)
		{
			myprimitive->push_back(findvertexinmap(mapvert, curridx, myVertices, 
								osg::Vec3(lba_face[cc].v[0], lba_face[cc].v[1]*2, lba_face[cc].v[2]),
								myTexts, osg::Vec2( lba_face[cc].vt[0], lba_face[cc].vt[1])));

			myprimitive->push_back(findvertexinmap(mapvert, curridx, myVertices, 
								osg::Vec3(lba_face[cc].v[3], lba_face[cc].v[4]*2, lba_face[cc].v[5]),
								myTexts, osg::Vec2( lba_face[cc].vt[2], lba_face[cc].vt[3])));

			myprimitive->push_back(findvertexinmap(mapvert, curridx, myVertices, 
								osg::Vec3(lba_face[cc].v[6], lba_face[cc].v[7]*2, lba_face[cc].v[8]),
								myTexts, osg::Vec2( lba_face[cc].vt[4], lba_face[cc].vt[5])));

			myNormals->push_back( osg::Vec3( lba_face[cc].vn[0], lba_face[cc].vn[1], lba_face[cc].vn[2]) );
		}

		myGeometry->addPrimitiveSet(myprimitive);
		myGeometry->setVertexArray( myVertices ); 
		myGeometry->setNormalArray( myNormals );
		myGeometry->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE);
		myGeometry->setTexCoordArray( 0, myTexts);
	}


	osg::StateSet* stateSet = root->getOrCreateStateSet();

	// Enable blending, select transparent bin.
	stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
	stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );


	osg::ref_ptr<osg::Texture2D> KLN89FaceTexture = new osg::Texture2D;

	// protect from being optimized away as static state:
	KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 

	// load an image by reading a file: 
	osg::Image* klnFace = osgDB::readImageFile(texture_filename);

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

	osgDB::writeNodeFile(*root.get(), map_filename, new osgDB::Options("Compressor=zlib"));
}

