function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(51)
	Spawn_1:SetPosY(3)
	Spawn_1:SetPosZ(16.5)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(22)
	Spawn_2:SetPosY(14.6)
	Spawn_2:SetPosZ(25)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(40.5)
	Spawn_3:SetPosY(0)
	Spawn_3:SetPosZ(61)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(27)
	Spawn_4:SetPosY(3)
	Spawn_4:SetPosZ(29.5)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map94.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map94.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit11", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 3.5, 3, true)
	Trigger_1:SetPosition(25.5, 3, 29.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map103_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit13", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 4, 5, true)
	Trigger_2:SetPosition(49.5, 3, 16.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map095_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit8", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 13, 4.5, 1, true)
	Trigger_3:SetPosition(40.5, 0, 62.5)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map097_1")
	Trigger_3_act1:SetSpawning(6)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

end

