function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map3.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map3.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 10, 4.5, 1, true)
	Trigger_1:SetPosition(32, 15, 0.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map001_1")
	Trigger_1_act1:SetSpawning(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 4.5, 1, true)
	Trigger_2:SetPosition(2.5, 5, 63.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map002_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 11, 6, 1, true)
	Trigger_3:SetPosition(19.5, 0, 63.5)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map002_1")
	Trigger_3_act1:SetSpawning(4)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit3", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 8, 6, 1, true)
	Trigger_4:SetPosition(51, 0, 63.5)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map002_1")
	Trigger_4_act1:SetSpawning(5)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit4", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 4.5, 3, true)
	Trigger_5:SetPosition(15.5, 0, 41.5)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map007_1")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

end
