function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map43.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map43.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit21", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 4, 1, true)
	Trigger_1:SetPosition(45.5, 0, 49.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map042_1")
	Trigger_1_act1:SetSpawning(13)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit22", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 4, 1, true)
	Trigger_2:SetPosition(21.5, 0, 63.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map042_1")
	Trigger_2_act1:SetSpawning(14)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit40", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 2, 2, true)
	Trigger_3:SetPosition(5, 0, 49)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map051_1")
	Trigger_3_act1:SetSpawning(2)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit48", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 4, 2, true)
	Trigger_4:SetPosition(25.5, 14, 5)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map042_1")
	Trigger_4_act1:SetSpawning(15)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

end
