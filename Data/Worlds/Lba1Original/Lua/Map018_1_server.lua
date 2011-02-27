function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(38)
	Spawn_1:SetPosY(9)
	Spawn_1:SetPosZ(21.5)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(58.5)
	Spawn_2:SetPosY(3)
	Spawn_2:SetPosZ(62)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(27)
	Spawn_3:SetPosY(3)
	Spawn_3:SetPosZ(51.5)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map18.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map18.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 0, 1.5, 0, true)
	Trigger_1:SetPosition(1, -1, 1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map000_1")
	Trigger_1_act1:SetSpawning(5)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 0, 1.5, 0, true)
	Trigger_2:SetPosition(1, -1, 1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map000_1")
	Trigger_2_act1:SetSpawning(6)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 0, 1.5, 0, true)
	Trigger_3:SetPosition(1, -1, 1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map000_1")
	Trigger_3_act1:SetSpawning(7)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit3", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 0, 1.5, 0, true)
	Trigger_4:SetPosition(1, -1, 1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map000_1")
	Trigger_4_act1:SetSpawning(8)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit4", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 7, 4.5, 1, true)
	Trigger_5:SetPosition(58.5, 3, 63.5)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map012_1")
	Trigger_5_act1:SetSpawning(5)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit5", true, true, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 1, 4.5, 7, true)
	Trigger_6:SetPosition(25.5, 3, 51.5)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map019_1")
	Trigger_6_act1:SetSpawning(2)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit6", true, true, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 1, 3.5, 3, true)
	Trigger_7:SetPosition(36.5, 9, 21.5)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map010_1")
	Trigger_7_act1:SetSpawning(1)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

end

