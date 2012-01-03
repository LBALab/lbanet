#include "Holomap.h"

#include <fstream>
#include <sstream>


/***********************************************************
constructor
***********************************************************/
DisplayInfoHandler::DisplayInfoHandler()
{
	Dinfo.State = LbaNet::NoState;

	Dinfo.RotX = 0;
	Dinfo.RotY = 0;
	Dinfo.RotZ = 0;

	Dinfo.TransX = 0;
	Dinfo.TransY = 0;
	Dinfo.TransZ = 0;

	Dinfo.ScaleX = 1;
	Dinfo.ScaleY = 1;
	Dinfo.ScaleZ = 1;

	Dinfo.SkinColor = -1;
	Dinfo.EyesColor = -1;
	Dinfo.HairColor = -1;
	Dinfo.OutfitColor = -1;
	Dinfo.WeaponColor = -1;
	Dinfo.MountSkinColor = -1;
	Dinfo.MountHairColor = -1;

	Dinfo.ModelId = 0;
	Dinfo.ColorR = 1;
	Dinfo.ColorG = 1;
	Dinfo.ColorB = 1;
	Dinfo.ColorA = 1;

	Dinfo.UseBillboard = false;

	Dinfo.UseTransparentMaterial = false;
	Dinfo.MatAlpha = 1;
		
	Dinfo.TypeRenderer = LbaNet::NoRender;
	Dinfo.ColorMaterialType = 0;
	Dinfo.MatAmbientColorR = 0.2f;
	Dinfo.MatAmbientColorG = 0.2f;
	Dinfo.MatAmbientColorB = 0.2f;
	Dinfo.MatAmbientColorA = 1;			
	Dinfo.MatDiffuseColorR = 0.8f;
	Dinfo.MatDiffuseColorG = 0.8f;
	Dinfo.MatDiffuseColorB = 0.8f;
	Dinfo.MatDiffuseColorA = 1;
	Dinfo.MatSpecularColorR = 0;
	Dinfo.MatSpecularColorG = 0;
	Dinfo.MatSpecularColorB = 0;
	Dinfo.MatSpecularColorA = 1;	
	Dinfo.MatEmissionColorR = 0;
	Dinfo.MatEmissionColorG = 0;
	Dinfo.MatEmissionColorB = 0;
	Dinfo.MatEmissionColorA = 1;
	Dinfo.MatShininess = 0;	
}


/***********************************************************
save to lua file
***********************************************************/
void DisplayInfoHandler::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = DisplayInfoHandler()"<<std::endl;

	file<<"\t\t"<<name<<":SetRenderType("<<GetRenderType()<<")"<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ModelId = "<<Dinfo.ModelId<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ModelName = \""<<Dinfo.ModelName<<"\""<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.Outfit = \""<<Dinfo.Outfit<<"\""<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.Weapon = \""<<Dinfo.Weapon<<"\""<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.Mode = \""<<Dinfo.Mode<<"\""<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.UseLight = "<<(Dinfo.UseLight?"true":"false")<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.CastShadow = "<<(Dinfo.CastShadow?"true":"false")<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ColorR = "<<Dinfo.ColorR<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ColorG = "<<Dinfo.ColorG<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ColorB = "<<Dinfo.ColorB<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ColorA = "<<Dinfo.ColorA<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.TransX = "<<Dinfo.TransX<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.TransY = "<<Dinfo.TransY<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.TransZ = "<<Dinfo.TransZ<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ScaleX = "<<Dinfo.ScaleX<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ScaleY = "<<Dinfo.ScaleY<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.ScaleZ = "<<Dinfo.ScaleZ<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.RotX = "<<Dinfo.RotX<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.RotY = "<<Dinfo.RotY<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.RotZ = "<<Dinfo.RotZ<<std::endl;
	file<<"\t\t"<<name<<".Dinfo.UseBillboard = "<<(Dinfo.UseBillboard?"true":"false")<<std::endl;
	
	if(Dinfo.UseTransparentMaterial)
	{
		file<<"\t\t"<<name<<".Dinfo.UseTransparentMaterial = true"<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatAlpha = "<<Dinfo.MatAlpha<<std::endl;
	}

	if(Dinfo.ColorMaterialType > 0)
	{
		file<<"\t\t"<<name<<".Dinfo.ColorMaterialType = "<<Dinfo.ColorMaterialType<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatAmbientColorR = "<<Dinfo.MatAmbientColorR<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatAmbientColorG = "<<Dinfo.MatAmbientColorG<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatAmbientColorB = "<<Dinfo.MatAmbientColorB<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatAmbientColorA = "<<Dinfo.MatAmbientColorA<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatDiffuseColorR = "<<Dinfo.MatDiffuseColorR<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatDiffuseColorG = "<<Dinfo.MatDiffuseColorG<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatDiffuseColorB = "<<Dinfo.MatDiffuseColorB<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatDiffuseColorA = "<<Dinfo.MatDiffuseColorA<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatSpecularColorR = "<<Dinfo.MatSpecularColorR<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatSpecularColorG = "<<Dinfo.MatSpecularColorG<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatSpecularColorB = "<<Dinfo.MatSpecularColorB<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatSpecularColorA = "<<Dinfo.MatSpecularColorA<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatEmissionColorR = "<<Dinfo.MatEmissionColorR<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatEmissionColorG = "<<Dinfo.MatEmissionColorG<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatEmissionColorB = "<<Dinfo.MatEmissionColorB<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatEmissionColorA = "<<Dinfo.MatEmissionColorA<<std::endl;
		file<<"\t\t"<<name<<".Dinfo.MatShininess = "<<Dinfo.MatShininess<<std::endl;
	}
}



/***********************************************************
	// set enum for render type as lua does not map enum
	//1 - RenderOsgModel
	//2 - RenderSprite
	//3 - RenderLba1M
	//4 - RenderLba2M
***********************************************************/
void DisplayInfoHandler::SetRenderType(int rtype)
{
	switch(rtype)
	{
		case 0:
			Dinfo.TypeRenderer = LbaNet::NoRender;
		break;
		case 1:
			Dinfo.TypeRenderer = LbaNet::RenderOsgModel;
		break;
		case 2:
			Dinfo.TypeRenderer = LbaNet::RenderSprite;
		break;
		case 3:
			Dinfo.TypeRenderer = LbaNet::RenderLba1M;
		break;
		case 4:
			Dinfo.TypeRenderer = LbaNet::RenderLba2M;
		break;
		case 5:
			Dinfo.TypeRenderer = LbaNet::RenderCross;
		break;
		case 6:
			Dinfo.TypeRenderer = LbaNet::RenderBox;
		break;
		case 7:
			Dinfo.TypeRenderer = LbaNet::RenderCapsule;
		break;
		case 8:
			Dinfo.TypeRenderer = LbaNet::RenderSphere;
		break;
	}
}

/***********************************************************
accessor
***********************************************************/
int DisplayInfoHandler::GetRenderType()
{
	switch(Dinfo.TypeRenderer)
	{
		case LbaNet::RenderOsgModel:
			return 1;
		break;
		case LbaNet::RenderSprite:
			return 2;
		break;
		case LbaNet::RenderLba1M:
			return 3;
		break;
		case LbaNet::RenderLba2M:
			return 4;
		break;
		case LbaNet::RenderCross:
			return 5;
		break;
		case LbaNet::RenderBox:
			return 6;
		break;
		case LbaNet::RenderCapsule:
			return 7;
		break;
		case LbaNet::RenderSphere:
			return 8;
		break;
	}

	return 0;
}

/***********************************************************
save HolomapTravelPath to lua file
***********************************************************/
void HolomapLocation::SaveToLuaFile(std::ostream & file)
{
	std::stringstream names;
	names<<"HolomapLoc_"<<_Id;

	file<<"\t"<<names.str()<<" = HolomapLocation("<<_Id<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetTextId("<<_textid<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetName(\""<<_Name<<"\")"<<std::endl;
	file<<"\t"<<names.str()<<":SetParentLocId("<<_parentholomaplocid<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetChildHoloId("<<_childholomapid<<")"<<std::endl;

	std::stringstream m1name;
	m1name<<names.str()<<"_coord";
	file<<"\t"<<m1name.str()<<" = HoloCoordinate()"<<std::endl;
	file<<"\t\t"<<m1name.str()<<".polarcoords ="<<_coordinate.polarcoords<<std::endl;
	file<<"\t\t"<<m1name.str()<<".posX ="<<_coordinate.posX<<std::endl;
	file<<"\t\t"<<m1name.str()<<".posY ="<<_coordinate.posY<<std::endl;
	file<<"\t\t"<<m1name.str()<<".posZ ="<<_coordinate.posZ<<std::endl;
	file<<"\t\t"<<m1name.str()<<".dir_cen_X ="<<_coordinate.dir_cen_X<<std::endl;
	file<<"\t\t"<<m1name.str()<<".dir_cen_Y ="<<_coordinate.dir_cen_Y<<std::endl;
	file<<"\t\t"<<m1name.str()<<".dir_cen_Z ="<<_coordinate.dir_cen_Z<<std::endl;
	file<<"\t"<<names.str()<<":SetCoordinate("<<m1name.str()<<")"<<std::endl;	

	file<<"\tenvironment:AddHolomapLoc("<<names.str()<<")"<<std::endl<<std::endl;
}


/***********************************************************
save HolomapTravelPath to lua file
***********************************************************/
void HolomapTravelPath::SaveToLuaFile(std::ostream & file)
{
	std::stringstream names;
	names<<"HolomapPath_"<<_Id;

	file<<"\t"<<names.str()<<" = HolomapTravelPath("<<_Id<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetName(\""<<_Name<<"\")"<<std::endl;
	file<<"\t"<<names.str()<<":SetParentHoloId("<<_parentholomapid<<")"<<std::endl;

	//save model
	{
		std::stringstream m1name;
		m1name<<names.str()<<"_model1";
		_vehiclemodel.SaveToLuaFile(file, "\t"+m1name.str());
		file<<"\t\t"<<names.str()<<":SetVehicleModel("<<m1name.str()<<")"<<std::endl;
	}

	// save coordinates
	for(size_t i=0; i<_coordinates.size(); ++i)
	{
		std::stringstream m1name;
		m1name<<names.str()<<"_coord_"<<i;
		file<<"\t"<<m1name.str()<<" = HoloCoordinate()"<<std::endl;
		file<<"\t\t"<<m1name.str()<<".polarcoords ="<<_coordinates[i].polarcoords<<std::endl;
		file<<"\t\t"<<m1name.str()<<".posX ="<<_coordinates[i].posX<<std::endl;
		file<<"\t\t"<<m1name.str()<<".posY ="<<_coordinates[i].posY<<std::endl;
		file<<"\t\t"<<m1name.str()<<".posZ ="<<_coordinates[i].posZ<<std::endl;
		file<<"\t\t"<<m1name.str()<<".dir_cen_X ="<<_coordinates[i].dir_cen_X<<std::endl;
		file<<"\t\t"<<m1name.str()<<".dir_cen_Y ="<<_coordinates[i].dir_cen_Y<<std::endl;
		file<<"\t\t"<<m1name.str()<<".dir_cen_Z ="<<_coordinates[i].dir_cen_Z<<std::endl;
		file<<"\t"<<names.str()<<":AddCoordinate("<<m1name.str()<<")"<<std::endl;	
	}

	file<<"\tenvironment:AddHolomapPath("<<names.str()<<")"<<std::endl<<std::endl;
}


/***********************************************************
save holomap to lua file
***********************************************************/
void Holomap::SaveToLuaFile(std::ostream & file)
{

	std::stringstream names;
	names<<"Holomap_"<<_Id;


	file<<"\t"<<names.str()<<" = Holomap("<<_Id<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetName(\""<<_Name<<"\")"<<std::endl;
	file<<"\t"<<names.str()<<":SetUsePCoordinates("<<(_usePlayerCoordinates?"true":"false")<<")"<<std::endl;
	file<<"\t"<<names.str()<<":Set3DMap("<<(_3dmap?"true":"false")<<")"<<std::endl;
		

	//save models
	{
		std::stringstream m1name;
		m1name<<names.str()<<"_model1";
		_mapmodel.SaveToLuaFile(file, m1name.str());
		file<<"\t"<<names.str()<<":SetMapModel("<<m1name.str()<<")"<<std::endl;
	}
	{
		std::stringstream m1name;
		m1name<<names.str()<<"_model2";
		_arrowmodel.SaveToLuaFile(file, m1name.str());
		file<<"\t"<<names.str()<<":SetArrowModel("<<m1name.str()<<")"<<std::endl;
	}
	{
		std::stringstream m1name;
		m1name<<names.str()<<"_model3";
		_playermodel.SaveToLuaFile(file, m1name.str());
		file<<"\t"<<names.str()<<":SetPlayerModel("<<m1name.str()<<")"<<std::endl;
	}
	{
		std::stringstream m1name;
		m1name<<names.str()<<"_model4";
		_arrowplayermodel.SaveToLuaFile(file, m1name.str());
		file<<"\t"<<names.str()<<":SetArrowPlayerModel("<<m1name.str()<<")"<<std::endl;
	}
	{
		std::stringstream m1name;
		m1name<<names.str()<<"_model5";
		_traveldotmodel.SaveToLuaFile(file, m1name.str());
		file<<"\t"<<names.str()<<":SetTravelDotModel("<<m1name.str()<<")"<<std::endl;
	}

	file<<"\tenvironment:AddHolomap("<<names.str()<<")"<<std::endl<<std::endl;

}
