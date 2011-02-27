function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(60)
	Spawn_1:SetPosY(11)
	Spawn_1:SetPosZ(4.5)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(57)
	Spawn_2:SetPosY(2)
	Spawn_2:SetPosZ(23)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(31)
	Spawn_3:SetPosY(11)
	Spawn_3:SetPosZ(7)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(27.5)
	Spawn_4:SetPosY(15)
	Spawn_4:SetPosZ(49)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(29)
	Spawn_5:SetPosY(15)
	Spawn_5:SetPosZ(47)
	Spawn_5:SetName("spawning5")
	environment:AddSpawn(Spawn_5)

	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map95.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map95.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4, 5, true)
	Trigger_1:SetPosition(62.5, 11, 4.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map094_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 3.5, 1, true)
	Trigger_2:SetPosition(29, 6, 63.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map094_1")
	Trigger_2_act1:SetSpawning(2)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit13", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 5, 3.5, 1, true)
	Trigger_3:SetPosition(56.5, 2, 21.5)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map098_1")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit15", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 3.5, 4, true)
	Trigger_4:SetPosition(29.5, 11, 7)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map099_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

end

