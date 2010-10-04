

#ifndef LBA_MAP_GL_H
#define LBA_MAP_GL_H

#include "globals.h"
#include "virtual_file.h"
#include "string_append.h"


using namespace std;


class LBA_ENTRY
{
public :
    int datalenght;
    vector<unsigned char> data;

    //ENTRY();
	LBA_ENTRY(const std::string &buffer)
	{
		for(size_t i=0; i<buffer.size(); ++i)
			data.push_back(buffer[i]);
	}

    //ENTRY();
    LBA_ENTRY(VIRTUAL_FILE_READ_ONLY &pack,int entry)
    {
        int i;
        long compressed_size;
        int compression_type;
        int pack_offset=0;
        pack.rewind_virtual();
        pack_offset=entry*4;
        pack.move_cursor(pack_offset);
        pack_offset=(long)(pack.read_char()+pack.read_char()*256.+pack.read_char()*65536.+pack.read_char()*16777216.);
        pack.move_cursor(pack_offset);
//        datalenght=(long)(+pack.read_char()*256.+pack.read_char()*65536.+pack.read_char()*16777216.);
//        pack_offset
//        pack.rewind_virtual();

        datalenght=(long)(pack.read_char()+pack.read_char()*256.+pack.read_char()*65536.+pack.read_char()*16777216.);
        compressed_size=(long)(pack.read_char()+pack.read_char()*256.+pack.read_char()*65536.+pack.read_char()*16777216.);
        compression_type=(long)(pack.read_char()+pack.read_char()*256.);
        data.reserve(datalenght);


        if(compression_type>0)
        {

            int e;
            int e2;
            unsigned char b,d,f,g;
            unsigned char c1,c2;
            int data_offset=0;
                do
                {
                    b=pack.read_char();
                    for(d=0;d<8;d++)
                    {

                            if((b & (1<<d))!=0)
                            {
                                data.push_back(pack.read_char());
                                data_offset++;
                            }
                            else
                            {
                                c1=pack.read_char();
                                c2=pack.read_char();
                                e=(c1*256+c2)%0x10000;
                                f=(((e>>8)&0x000f)+compression_type+1)%0x10000;
                                e2=(((e<<4)&0x0ff0)+((e>>12)&0x000f))%0x10000;
                                for(g=0;g<f;g++)
                                {
                                    data.push_back(data[data_offset+1-e2-2]);
                                    data_offset++;
                                }

                            }

                            if(data_offset>=datalenght)break;
                    }
                }
                while(data_offset<datalenght);
            }
            else
            {
                for(i=0;i<datalenght;i++)
                data.push_back(pack.read_char());
            }
            pack.rewind_virtual();
    }
};

class LBA_PALET
{
    public :
    unsigned char couleur[256][3];
    LBA_PALET(VIRTUAL_FILE_READ_ONLY &pack)
    {
        int i;
        int offset_data=0;

        LBA_ENTRY *entry=new LBA_ENTRY(pack,0);

        for(i=0;i<256;i++)
        {
            couleur[i][0]=entry->data[offset_data++]; //rouge
            couleur[i][1]=entry->data[offset_data++]; //vert
            couleur[i][2]=entry->data[offset_data++]; //bleu
        }
        delete entry;
    }
};

class LBA_BRICK
{
    public:

    int lenght;
    int height;
    unsigned char pixel[38][48];


    LBA_BRICK(VIRTUAL_FILE_READ_ONLY &pack,int n)
    {
        int data_offset=0;
        int i,j,k;
        unsigned char c;
        int offset;
        LBA_ENTRY entry(pack,n);
        lenght=48;
        height=38;
        unsigned char brick_width=entry.data[data_offset++];
        unsigned char brick_height=entry.data[data_offset++];
        unsigned char brick_offsetx=entry.data[data_offset++];
        unsigned char brick_offsety=entry.data[data_offset++];
        unsigned char brick_nombre_subline;
        unsigned char brick_type_subline;
        unsigned char brick_lenght_subline;
        for(i=0;i<38;i++)
        for(j=0;j<48;j++)
        {
            pixel[i][j]=0;
        }
        for(i=0;i<brick_height;i++)
        {
            c=entry.data[data_offset++];
            brick_nombre_subline=c;
            offset=0;

            for(j=0;j<brick_nombre_subline;j++)
            {

                c=entry.data[data_offset++];
                brick_type_subline=c/64;
                brick_lenght_subline=c*4;
                brick_lenght_subline/=4;
                brick_lenght_subline=brick_lenght_subline+1;
                if(brick_type_subline==0)
                {
                    offset+=brick_lenght_subline;
                }
                if(brick_type_subline==1)
                {
                    for(k=0;k<brick_lenght_subline;k++)
                    {
                        c=entry.data[data_offset++];
                        pixel[i+brick_offsety][brick_offsetx+offset]=c;
                        offset++;
                    }


                }
                if(brick_type_subline==3)
                {
                    for(k=0;k<brick_lenght_subline;k++)
                    {
                        c=entry.data[data_offset++];
                        pixel[i+brick_offsety][brick_offsetx+offset]=c;
                        offset++;
                    }
                }

                if(brick_type_subline==2)
                {
                    c=entry.data[data_offset++];
                    for(k=0;k<brick_lenght_subline;k++)
                    {
                        pixel[i+brick_offsety][brick_offsetx+offset]=c;
                        offset++;
                    }
                }
            }
        }


                //duplicate borders:
        for(int px=0;px<22;px++)
        {

            pixel[10-px/2][px]=pixel[11-px/2][px],
            pixel[27+px/2][px]=pixel[26+px/2][px];
        }
        for(int px=26;px<48;px++)
        {
            pixel[0+(px-26)/2][px]=pixel[1+(px-26)/2][px],
            pixel[37-(px-26)/2][px]=pixel[36-(px-26)/2][px];
        }


/*        pixel[0][20]=pixel[1][20];*/


    }
};





struct LBA_INFO_BRICK{
int index_brick;
int new_index_brick;
unsigned char shape;
unsigned char material;
unsigned int object;

};

class LBA_OBJECT
{
    public:
    unsigned char taille_X,taille_Y,taille_Z;
    vector <LBA_INFO_BRICK> info_brick;
    LBA_OBJECT(int X,int Y,int Z)
    {
        taille_X=X;
        taille_Y=Y;
        taille_Z=Z;
        info_brick.reserve(X*Y*Z);
    }
};

class LBA_LAYOUT
{
    public:
    int number_objects;
    vector<LBA_OBJECT> object;
	int number_bricks;


    LBA_LAYOUT(VIRTUAL_FILE_READ_ONLY &pack,int n, bool LBA2, bool customlayout)
		: number_bricks(0)
    {
		bool usespecialroof = false;
		if(!LBA2)
		{
			if(n == 12 || n == 42 || n == 44)
				usespecialroof = true;
		}

        int index_data=0;
        LBA_ENTRY *entry;
		if(customlayout)
			entry =new LBA_ENTRY(pack.GetBuffer());
		else
			entry =new LBA_ENTRY(pack,n);
        number_objects=(entry->data[0]+entry->data[1]*256+entry->data[2]*65536+entry->data[3]*16777216)/4;

        object.reserve(number_objects);
        for(int i=0;i<number_objects;i++)//
        {
            index_data=(entry->data[i*4]+entry->data[i*4+1]*256+entry->data[i*4+2]*65536+entry->data[i*4+3]*16777216);

            LBA_OBJECT obj(entry->data[index_data],entry->data[index_data+1],entry->data[index_data+2]);

			index_data+=3;	


            for(int j=0;j<obj.taille_X*obj.taille_Y*obj.taille_Z;j++)
            {
				++number_bricks;

                LBA_INFO_BRICK info;
                info.object=i;
                info.shape=entry->data[index_data++];
                info.material=entry->data[index_data++];
                info.index_brick=entry->data[index_data]+(entry->data[index_data+1])*256-1;


				// solve the issue in proxima city with the roof not being slope shapes
				if(usespecialroof)
				{
					{
						if(info.object == 186)
						{
							if(j==5 || j==7 || j == 9)
								info.shape=5;

							if(j==5)
								info.index_brick = 1429;
							if(j==7)
								info.index_brick = 1427;
							if(j==9)
								info.index_brick = 1426;

							if(j==0 || j==1 || j==2 || j==3 || j==4 || j == 6)
								info.shape=1;

							if(j==8 || j==10 || j==11)
								info.shape=0;
						}

						if(info.object == 187)
						{
							if(j==5 || j==7 || j == 9)
								info.shape=5;

							if(j==5)
								info.index_brick = 1435;
							if(j==7)
								info.index_brick = 1433;
							if(j==9)
								info.index_brick = 1431;


							if(j==0 || j==1 || j==2 || j==3 || j==4 || j == 6)
								info.shape=1;

							if(j==8 || j==10 || j==11)
								info.shape=0;
						}

						if(info.object == 188)
						{
							if(j==5 || j==7 || j == 9)
								info.shape=5;

							if(j==5)
								info.index_brick = 1425;
							if(j==7)
								info.index_brick = 1423;
							if(j==9)
								info.index_brick = 1422;

							if(j==0 || j==1 || j==2 || j==3 || j==4 || j == 6)
								info.shape=1;

							if(j==8 || j==10 || j==11)
								info.shape=0;
						}



						if(info.object == 189)
						{
							if(j==3 || j==7 || j == 11)
								info.shape=2;

							if(j==3)
								info.index_brick = 3663;
							if(j==7)
								info.index_brick = 1439;
							if(j==11)
								info.index_brick = 1437;

							if(j==0 || j==1 || j==2 || j==4 || j==5 || j == 8)
								info.shape=1;

							if(j==6 || j==9 || j==10)
								info.shape=0;
						}
						if(info.object == 190)
						{
							if(j==0 || j==4 || j == 8)
								info.shape=2;

							if(j==0)
								info.index_brick = 1442;
							if(j==4)
								info.index_brick = 1441;
							if(j==8)
								info.index_brick = 1440;


							if(/*j==0 || */j==1 || j==2 || /*j==4 || */j==5 /*|| j == 8*/)
								info.shape=1;

							if(j==6 || j==9 || j==10 || j==3 || j==7 || j==11)
								info.shape=0;
						}
					}
				}



                obj.info_brick.push_back(info);
                index_data+=2;



            }
            object.push_back(obj);
        }
        delete entry;
}

};



class LBA_GRID
{

    public:
    LBA_INFO_BRICK ***info_brick;
    LBA_LAYOUT *layout;

	LBA_INFO_BRICK *** GetBricks()
	{ return info_brick; }

    LBA_GRID(VIRTUAL_FILE_READ_ONLY &pack_grid,VIRTUAL_FILE_READ_ONLY &pack_layout,int n,
				int LBA2, bool customlayout, bool forcedlayout = false)
    {
        int index_data=0;
        unsigned char flag,number_sub_colomn;
        int height_subcolumn,offset_column;
		LBA_ENTRY *entry=new LBA_ENTRY(pack_grid.GetBuffer());

        if(LBA2 && !forcedlayout)
			n=entry->data[0]+180-1;


        layout=new LBA_LAYOUT(pack_layout,n, LBA2 == 1, customlayout);
        info_brick=new LBA_INFO_BRICK **[64];

        for(int i=0;i<64;i++)
			info_brick[i]=new LBA_INFO_BRICK *[64];

        for(int i=0;i<64;i++)
		{
			for(int j=0;j<64;j++)
				info_brick[i][j]=new LBA_INFO_BRICK [25];
		}

        for(int i=0;i<64;i++)
		{
			for(int j=0;j<64;j++)
			{
				for(int k=0;k<25;k++)
				{
					info_brick[i][j][k].index_brick=-1;
					info_brick[i][j][k].material=0xF0;
					info_brick[i][j][k].shape=0;
				}
			}
		}



        for(int j=0;j<64;j++)
		{
			for(int i=0;i<64;i++)
			{
				if(LBA2)
					index_data=entry->data[2*(j*64+i)+34]+entry->data[2*(j*64+i)+1+34]*256+34;///////////////LBA2 +34 +34 +34
				else 
					index_data=entry->data[2*(j*64+i)]+entry->data[2*(j*64+i)+1]*256;

				number_sub_colomn=entry->data[index_data++];



				offset_column=0;
				for(int k=0;k<number_sub_colomn;k++)
				{
					flag=entry->data[index_data]>>6;
					height_subcolumn=entry->data[index_data]%0x20+1;
					index_data++;

					if(flag==0)
					{
						offset_column+=height_subcolumn;
					}

					if(flag==1)
					{
						for(int l=0;l<height_subcolumn;l++)
						{
							if(entry->data[index_data]==0)
							{
								info_brick[i][j][offset_column].index_brick=-1;
								info_brick[i][j][offset_column].material=0xF0;
								info_brick[i][j][offset_column].shape=0;
							}
							else
							{
								int index1 = entry->data[index_data]-1;
								int index2 = entry->data[index_data+1];
								info_brick[i][j][offset_column]=layout->object[index1].info_brick[index2];
							}

							offset_column++;
							index_data+=2;
						}
					}

					if(flag==2)
					{
						for(int l=0;l<height_subcolumn;l++)
						{
							if(entry->data[index_data]==0)
							{
								info_brick[i][j][offset_column].index_brick=-1;
								info_brick[i][j][offset_column].material=0xF0;
								info_brick[i][j][offset_column].shape=0;
							}
							else
							{
								info_brick[i][j][offset_column]=layout->object[entry->data[index_data]-1].info_brick[entry->data[index_data+1]];
							}
							offset_column++;
						}
						index_data+=2;
					}

				}
			}
		}



        delete entry;

    }

    ~LBA_GRID()
    {
            for(int i=0;i<64;i++)
				for(int j=0;j<64;j++)
					delete info_brick[i][j];

            for(int i=0;i<64;i++)
				delete [] info_brick[i];

            delete [] info_brick;
            delete layout;
    }
};


class LBA_MAP
{
private:
	void Initialize(int LBA2, VIRTUAL_FILE_READ_ONLY *pack_brick)
	{
        int i,j,k,l;
        number_brick=0;

        printf(" >%d ",number_brick);

        for(i=0;i<64;i++)
        for(j=0;j<64;j++)
        for(k=0;k<25;k++)
        {
            if(grid->info_brick[i][j][k].index_brick!=-1)
            {
                for(l=0;l<number_brick;l++)
                if(brick_list[l]==grid->info_brick[i][j][k].index_brick)
                    break;
                if(l==number_brick)
                {
                    brick_list[l]=grid->info_brick[i][j][k].index_brick;
                    number_brick++;
                }
            }
        }


        //changement d´indices : on passe de 8000 briques à 600-700 briques
        //attention brique 0
        for(i=0;i<64;i++)
        for(j=0;j<64;j++)
        for(k=0;k<25;k++)
        {
            if(grid->info_brick[i][j][k].index_brick!=-1)
            {
                l=0;
                while(grid->info_brick[i][j][k].index_brick!=brick_list[l])l++;
                grid->info_brick[i][j][k].index_brick=l;
            }
        }

        brick.reserve(number_brick);
        for(i=0;i<number_brick;i++)
        {
			if(LBA2)
				brick.push_back(LBA_BRICK(*pack_brick,brick_list[i]-1+198-1+1));//////////////LBA2 +198-1
			else 
				brick.push_back(LBA_BRICK(*pack_brick,brick_list[i]-1+1));
        }


	}


public:
    LBA_PALET *palet;
    LBA_GRID *grid;
    vector<LBA_BRICK> brick;
    int number_brick;
    vector<int> nb_faces;
    int brick_list[10000];




	// constructor with grid file
	LBA_MAP(int LBA2, const std::string &grfile, 
				bool custombrickfile, const std::string &brkfile,
				bool customlayoutfile, const std::string &layoutfile,
				int layoutused, bool forcelayout = false)
	{
		VIRTUAL_FILE_READ_ONLY *pack_brick;
		VIRTUAL_FILE_READ_ONLY *pack_grid;
		VIRTUAL_FILE_READ_ONLY *pack_ress;
		VIRTUAL_FILE_READ_ONLY *pack_layout;
		if(LBA2)
		{
			 if(!custombrickfile)
				pack_brick=new VIRTUAL_FILE_READ_ONLY("data//map//lba2//LBA_BKG.HQR");

			 pack_ress=new VIRTUAL_FILE_READ_ONLY("data//map//lba2//RESS2.HQR");

			 if(!customlayoutfile)
				 pack_layout=new VIRTUAL_FILE_READ_ONLY("data//map//lba2//LBA_BKG.HQR");
		}
		else
		{
			 if(!custombrickfile)
				pack_brick=new VIRTUAL_FILE_READ_ONLY("data//map//lba1//LBA_BRK.HQR");

			 pack_ress=new VIRTUAL_FILE_READ_ONLY("data//map//lba1//RESS.HQR");

			 if(!customlayoutfile)
				pack_layout=new VIRTUAL_FILE_READ_ONLY("data//map//lba1//LBA_BLL.HQR");
		}

		// use file for pack grid
		pack_grid=new VIRTUAL_FILE_READ_ONLY(grfile);

		if(custombrickfile)
			pack_brick=new VIRTUAL_FILE_READ_ONLY(brkfile);

		if(customlayoutfile)
			pack_layout=new VIRTUAL_FILE_READ_ONLY(layoutfile);


        palet=new LBA_PALET(*pack_ress);
        grid=new LBA_GRID(*pack_grid, *pack_layout, layoutused, LBA2, customlayoutfile, forcelayout);

		Initialize(LBA2, pack_brick);

        delete pack_brick;
        delete pack_grid;
        delete pack_layout;
        delete pack_ress;
	}



	// constructor with grid number
    LBA_MAP(int n,int LBA2)
    {
		VIRTUAL_FILE_READ_ONLY *pack_brick;
		VIRTUAL_FILE_READ_ONLY *pack_grid;
		VIRTUAL_FILE_READ_ONLY *pack_ress;
		VIRTUAL_FILE_READ_ONLY *pack_layout;
		if(LBA2)
		{
			 pack_brick=new VIRTUAL_FILE_READ_ONLY("data//map//lba2//LBA_BKG.HQR");
			 pack_grid=new VIRTUAL_FILE_READ_ONLY("data//map//lba2//LBA_BKG.HQR");
			 pack_ress=new VIRTUAL_FILE_READ_ONLY("data//map//lba2//RESS2.HQR");
			 pack_layout=new VIRTUAL_FILE_READ_ONLY("data//map//lba2//LBA_BKG.HQR");
		}
		else
		{
			 pack_brick=new VIRTUAL_FILE_READ_ONLY("data//map//lba1//LBA_BRK.HQR");
			 pack_grid=new VIRTUAL_FILE_READ_ONLY("data//map//lba1//LBA_GRI.HQR");
			 pack_ress=new VIRTUAL_FILE_READ_ONLY("data//map//lba1//RESS.HQR");
			 pack_layout=new VIRTUAL_FILE_READ_ONLY("data//map//lba1//LBA_BLL.HQR");
		}
        palet=new LBA_PALET(*pack_ress);
        grid=new LBA_GRID(*pack_grid,*pack_layout,n,LBA2, false);

		Initialize(LBA2, pack_brick);

        delete pack_brick;
        delete pack_grid;
        delete pack_layout;
        delete pack_ress;
    }

	//destructor
    ~LBA_MAP()
    {
        delete palet;
        delete grid;
    }
};

struct LBA_SHARED_BRICK
{
    int id;
    int dx;
    int dz;
};


struct LBA_FACE
{
    double v[9];
    double vt[6];
    double vn[3];


    int dx;
    int dz;
};

class LBA_MAP_GL
{
private:
    LBA_MAP *lba_map;
    unsigned int list_name;
    unsigned int texture_name;
    int brick_number;
	int islba2;
    unsigned char *texture_map;
    vector<LBA_FACE> lba_face;
    vector<int> nb_faces;
	std::string texture_filename;
	std::string map_filename;

protected:
	void Initialize(int LBA2);

public:
	// constructor with map number
    LBA_MAP_GL(int NUM_MAP,int LBA2);

	//constructor with gr file
	LBA_MAP_GL(int LBA2, const std::string &grfile, 
						bool custombrickfile, const std::string &brkfile,
						bool customlayoutfile, const std::string &layoutfile,
						int layoutused, bool forcelayout = false);


    void face(double X,double Y,double Z,double texture_x,double texture_y,
									double h,int a,int b,int c,bool hidden);



	// export map to osg format
	void ExportMapOSG();


	int GetNumberBricks()
	{
		return lba_map->number_brick;
	}


	// destructor
    ~LBA_MAP_GL()
    {
        delete texture_map;
        delete lba_map;
    }
};









#endif
