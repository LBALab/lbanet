#ifndef _LBANET_LBA_MAP_H_
#define _LBANET_LBA_MAP_H_

#include <string>

class LBA_PACK_PHYS
{
public :

	// constructors
	LBA_PACK_PHYS(){}
	LBA_PACK_PHYS(const std::string & file);

	// destructor
    ~LBA_PACK_PHYS();

	// class members
    unsigned char *data;
    long datalenght;
};



class LBA_ENTRY_PHYS
{
public :

    //constructor
    LBA_ENTRY_PHYS(LBA_PACK_PHYS *pack,int entry);

	// destructor
    ~LBA_ENTRY_PHYS();

    LBA_ENTRY_PHYS(unsigned char *dt,int lenght);

	// class members
    long datalenght;
    unsigned char *data;
};




class LBA_PALET_PHYS
{
public :

	// constructor
    LBA_PALET_PHYS(LBA_PACK_PHYS *pack);

	// destructor
    ~LBA_PALET_PHYS(){}

	// class members
    unsigned char couleur[256][3];
};



class LBA_BRICK_PHYS
{
public:

	// constructor
    LBA_BRICK_PHYS(LBA_PACK_PHYS *pack,int n);

	// destructor
    ~LBA_BRICK_PHYS(){}

	// class members
    int lenght;
    int height;
    unsigned char pixel[38][48];
};





struct LBA_INFO_BRICK_PHYS
{
	unsigned int index_brick;
	unsigned char shape;
	unsigned char material;
	short sound;
};



class LBA_OBJECT_PHYS
{
public:

	// constructor
    LBA_OBJECT_PHYS(int X,int Y,int Z);

	// destructor
    ~LBA_OBJECT_PHYS();

	// class members
    unsigned char taille_X;
	unsigned char taille_Y;
	unsigned char taille_Z;
    LBA_INFO_BRICK_PHYS *info_brick;
};



class LBA_LAYOUT_PHYS
{
public:

	// constructor
    LBA_LAYOUT_PHYS(LBA_PACK_PHYS *pack,int n, bool customlayout);

	// destructor
	~LBA_LAYOUT_PHYS();

	// class members
    int number_objects;
    LBA_OBJECT_PHYS **object;

};



class LBA_GRID_PHYS
{
public:
	// constructor
    LBA_GRID_PHYS(LBA_PACK_PHYS *pack_grid,LBA_PACK_PHYS *pack_layout,int n,bool LBA2, 
					bool customlayout, bool forcelayout = false);

	// destructor
    ~LBA_GRID_PHYS();

	// class members
    LBA_INFO_BRICK_PHYS ***info_brick;


	LBA_INFO_BRICK_PHYS *** GetBricks()
	{ return info_brick; }
};




class LBA_MAP_PHYS
{
public:
	// constructor with grid number
    LBA_MAP_PHYS(int n, bool LBA2);

	// constructor with grid file
	LBA_MAP_PHYS(bool LBA2, const std::string &grfile, 
		bool custombrickfile, const std::string &brkfile,
		bool customlayoutfile, const std::string &layoutfile,
		int layoutused, bool forcelayout = false);


	// destructor
    ~LBA_MAP_PHYS();

	// class members
    LBA_PALET_PHYS *palet;
    LBA_GRID_PHYS *grid;
    int number_brick;


	LBA_GRID_PHYS * GetGrid()
	{return grid;}
};




#endif
