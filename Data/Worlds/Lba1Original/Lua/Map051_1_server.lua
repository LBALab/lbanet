function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map51.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map51.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit11", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 2.5, 2, true)
	Trigger_1:SetPosition(58, 14, 18)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map049_1")
	Trigger_1_act1:SetSpawning(4)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit14", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 2.5, 2, true)
	Trigger_2:SetPosition(61, 14, 2)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map043_1")
	Trigger_2_act1:SetSpawning(4)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 3, 2, true)
	Trigger_3:SetPosition(48, 15, 61)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map042_1")
	Trigger_3_act1:SetSpawning(5)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit4", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 2, 3, 2, true)
	Trigger_4:SetPosition(50, 15, 47)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map049_1")
	Trigger_4_act1:SetSpawning(2)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit8", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 2, 2.5, 2, true)
	Trigger_5:SetPosition(57, 14, 27)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map049_1")
	Trigger_5_act1:SetSpawning(3)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

end
