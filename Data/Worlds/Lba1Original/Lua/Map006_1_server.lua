function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(62)
	Spawn_1:SetPosY(0)
	Spawn_1:SetPosZ(49)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(39.5)
	Spawn_2:SetPosY(4)
	Spawn_2:SetPosZ(25)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(30)
	Spawn_3:SetPosY(4)
	Spawn_3:SetPosZ(44)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(31.5)
	Spawn_4:SetPosY(4)
	Spawn_4:SetPosZ(43)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(57.5)
	Spawn_5:SetPosY(4)
	Spawn_5:SetPosZ(26)
	Spawn_5:SetName("spawning5")
	environment:AddSpawn(Spawn_5)

	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map6.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map6.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 5.5, 8, true)
	Trigger_1:SetPosition(63.5, 0, 49)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map002_1")
	Trigger_1_act1:SetSpawning(8)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit12", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 4, 4.5, 1, true)
	Trigger_2:SetPosition(39, 4, 23.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map035_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit15", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 3.5, 2, true)
	Trigger_3:SetPosition(0.5, 3, 1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map011_1")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit17", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 3, 3.5, 1, true)
	Trigger_4:SetPosition(57.5, 4, 24.5)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map104_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

end

