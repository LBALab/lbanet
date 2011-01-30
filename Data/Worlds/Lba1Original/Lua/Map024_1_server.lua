function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map24.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map24.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit1", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 4, 1, true)
	Trigger_1:SetPosition(42.5, 7, 0.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map039_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit13", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 3.5, 3, true)
	Trigger_2:SetPosition(18.5, 2, 30.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map102_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit3", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 3, 3.5, 2, true)
	Trigger_3:SetPosition(37.5, 7, 1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map042_1")
	Trigger_3_act1:SetSpawning(10)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit5", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 2, 3.5, 1, true)
	Trigger_4:SetPosition(63, 7, 6.5)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map059_1")
	Trigger_4_act1:SetSpawning(2)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit6", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 2, 3.5, 1, true)
	Trigger_5:SetPosition(63, 7, 7.5)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map042_1")
	Trigger_5_act1:SetSpawning(11)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit7", true, true, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 2, 3.5, 1, true)
	Trigger_6:SetPosition(63, 7, 8.5)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map039_1")
	Trigger_6_act1:SetSpawning(3)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit8", true, true, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 2, 3.5, 1, true)
	Trigger_7:SetPosition(63, 7, 9.5)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map004_1")
	Trigger_7_act1:SetSpawning(5)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

end
