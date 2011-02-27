function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(62)
	Spawn_1:SetPosY(11)
	Spawn_1:SetPosZ(60)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(52)
	Spawn_2:SetPosY(7.2)
	Spawn_2:SetPosZ(57)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(53)
	Spawn_3:SetPosY(3)
	Spawn_3:SetPosZ(35)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(60)
	Spawn_4:SetPosY(7)
	Spawn_4:SetPosZ(32)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map49.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map49.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit1", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4, 3, true)
	Trigger_1:SetPosition(63.5, 11, 60.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map042_1")
	Trigger_1_act1:SetSpawning(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit2", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 2.5, 2, true)
	Trigger_2:SetPosition(53, 4, 57)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map051_1")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit3", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 2, 2, true)
	Trigger_3:SetPosition(53, 2, 35)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map051_1")
	Trigger_3_act1:SetSpawning(4)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit4", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 2, 2.5, 2, true)
	Trigger_4:SetPosition(60, 7, 30)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map051_1")
	Trigger_4_act1:SetSpawning(5)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

end

