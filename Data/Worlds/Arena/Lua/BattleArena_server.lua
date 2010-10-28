function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Arena/Grids/TheComplexPvpArena.osgb"
	MapObject.DisplayDesc.CastShadow = false
	MapObject.DisplayDesc.UseLight = true
	MapObject:SetModelState(1)
	MapObject.PhysicDesc.Pos.X = 0
	MapObject.PhysicDesc.Pos.Y = 0
	MapObject.PhysicDesc.Pos.Z = 0
	MapObject.PhysicDesc.Pos.Rotation = 0
	MapObject:SetPhysicalActorType(1)
	MapObject:SetPhysicalShape(5)
	MapObject.PhysicDesc.Collidable = true
	MapObject.PhysicDesc.Filename = "Worlds/Arena/Grids/TheComplexPvpArena.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)
end
