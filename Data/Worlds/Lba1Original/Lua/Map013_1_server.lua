function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map13.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map13.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 3.5, 8, true)
	Trigger_1:SetPosition(63.5, 0, 52)
	Trigger_1:SetAction1(49)
	Trigger_1:SetAction2(-1)
	Trigger_1:SetAction3(-1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 8, 5, 1, true)
	Trigger_2:SetPosition(60, 0, 0.5)
	Trigger_2:SetAction1(50)
	Trigger_2:SetAction2(-1)
	Trigger_2:SetAction3(-1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit11", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 5, 4.5, 1, true)
	Trigger_3:SetPosition(18.5, 6, 31.5)
	Trigger_3:SetAction1(51)
	Trigger_3:SetAction2(-1)
	Trigger_3:SetAction3(-1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit12", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 5, 4.5, 1, true)
	Trigger_4:SetPosition(47.5, 3, 23.5)
	Trigger_4:SetAction1(52)
	Trigger_4:SetAction2(-1)
	Trigger_4:SetAction3(-1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit18", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 4, 5, true)
	Trigger_5:SetPosition(36.5, 0, 54.5)
	Trigger_5:SetAction1(53)
	Trigger_5:SetAction2(-1)
	Trigger_5:SetAction3(-1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit20", true, true, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 1, 4.5, 5, true)
	Trigger_6:SetPosition(5.5, 6, 39.5)
	Trigger_6:SetAction1(54)
	Trigger_6:SetAction2(-1)
	Trigger_6:SetAction3(-1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit21", true, true, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 2, 3, 2, true)
	Trigger_7:SetPosition(8, 16, 4)
	Trigger_7:SetAction1(55)
	Trigger_7:SetAction2(-1)
	Trigger_7:SetAction3(-1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "exit22", true, true, false)
	Trigger_8 = ZoneTrigger(Trigger_8_info, 1, 4, 5, true)
	Trigger_8:SetPosition(8.5, 9, 20.5)
	Trigger_8:SetAction1(56)
	Trigger_8:SetAction2(-1)
	Trigger_8:SetAction3(-1)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "exit23", true, true, false)
	Trigger_9 = ZoneTrigger(Trigger_9_info, 5, 4.5, 1, true)
	Trigger_9:SetPosition(21.5, 3, 54.5)
	Trigger_9:SetAction1(57)
	Trigger_9:SetAction2(-1)
	Trigger_9:SetAction3(-1)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "exit26", true, true, false)
	Trigger_10 = ZoneTrigger(Trigger_10_info, 7, 8, 1, true)
	Trigger_10:SetPosition(59.5, 0, 63.5)
	Trigger_10:SetAction1(58)
	Trigger_10:SetAction2(-1)
	Trigger_10:SetAction3(-1)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "exit27", true, true, false)
	Trigger_11 = ZoneTrigger(Trigger_11_info, 5, 4, 1, true)
	Trigger_11:SetPosition(12.5, 3, 54.5)
	Trigger_11:SetAction1(59)
	Trigger_11:SetAction2(-1)
	Trigger_11:SetAction3(-1)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "exit30", true, true, false)
	Trigger_12 = ZoneTrigger(Trigger_12_info, 1, 5.5, 3, true)
	Trigger_12:SetPosition(55.5, 0, 42.5)
	Trigger_12:SetAction1(60)
	Trigger_12:SetAction2(-1)
	Trigger_12:SetAction3(-1)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "exit31", true, true, false)
	Trigger_13 = ZoneTrigger(Trigger_13_info, 2, 2, 2, true)
	Trigger_13:SetPosition(23, 6, 29)
	Trigger_13:SetAction1(61)
	Trigger_13:SetAction2(-1)
	Trigger_13:SetAction3(-1)
	environment:AddTrigger(Trigger_13)

end