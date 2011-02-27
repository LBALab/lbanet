function InitMap(environment)
	Spawn_0 = Spawn(0)
	Spawn_0:SetPosX(0)
	Spawn_0:SetPosY(0)
	Spawn_0:SetPosZ(0)
	Spawn_0:SetName("DefaultSpawning")
	Spawn_0:SetForceRotation(true)
	Spawn_0:SetRotation(0)
	environment:AddSpawn(Spawn_0)

	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map116.osgb"
	MapObject.DisplayDesc.UseLight = true
	MapObject.DisplayDesc.CastShadow = false
	MapObject:SetModelState(1)
	MapObject.PhysicDesc.Pos.X = 0
	MapObject.PhysicDesc.Pos.Y = 0
	MapObject.PhysicDesc.Pos.Z = 0
	MapObject.PhysicDesc.Pos.Rotation = 0
	MapObject:SetPhysicalActorType(1)
	MapObject:SetPhysicalShape(5)
	MapObject.PhysicDesc.Collidable = true
	MapObject.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map116.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)
end

