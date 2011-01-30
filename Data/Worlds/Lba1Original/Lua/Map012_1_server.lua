function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map12.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map12.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit1", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 7, 5, 1, true)
	Trigger_1:SetPosition(57.5, 4, 63.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map011_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit19", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 7, 6.5, 1, true)
	Trigger_2:SetPosition(57.5, 4, 0.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map018_1")
	Trigger_2_act1:SetSpawning(2)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 3.5, 8, true)
	Trigger_3:SetPosition(0.5, 4, 52)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map013_1")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit23", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 4, 5, true)
	Trigger_4:SetPosition(4.5, 14, 6.5)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map105_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit8", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 4.5, 6, true)
	Trigger_5:SetPosition(63.5, 4, 39)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map017_1")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit9", true, true, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 4, 4.5, 1, true)
	Trigger_6:SetPosition(19, 4, 63.5)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map011_1")
	Trigger_6_act1:SetSpawning(3)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

end
