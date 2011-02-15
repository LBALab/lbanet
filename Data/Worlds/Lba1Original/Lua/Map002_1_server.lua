function InitMap(environment)
	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = -842150451
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map2.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = -4.31602e+008
	Actor_1.DisplayDesc.ColorG = -4.31602e+008
	Actor_1.DisplayDesc.ColorB = -4.31602e+008
	Actor_1.DisplayDesc.ColorA = -4.31602e+008
	Actor_1.DisplayDesc.TransX = 0
	Actor_1.DisplayDesc.TransY = 0
	Actor_1.DisplayDesc.TransZ = 0
	Actor_1.DisplayDesc.ScaleX = 1
	Actor_1.DisplayDesc.ScaleY = 1
	Actor_1.DisplayDesc.ScaleZ = 1
	Actor_1.DisplayDesc.RotX = 0
	Actor_1.DisplayDesc.RotY = 0
	Actor_1.DisplayDesc.RotZ = 0
	Actor_1:SetModelState(1)
	Actor_1.PhysicDesc.Pos.X = 0
	Actor_1.PhysicDesc.Pos.Y = 0
	Actor_1.PhysicDesc.Pos.Z = 0
	Actor_1.PhysicDesc.Pos.Rotation = 0
	Actor_1.PhysicDesc.Density = -4.31602e+008
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = -4.31602e+008
	Actor_1.PhysicDesc.SizeY = -4.31602e+008
	Actor_1.PhysicDesc.SizeZ = -4.31602e+008
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map2.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = -4.31602e+008
	Actor_1.ExtraInfo.NameColorG = -4.31602e+008
	Actor_1.ExtraInfo.NameColorB = -4.31602e+008
	Actor_1.ExtraInfo.Display = false
	Actor_1.LifeInfo.Display = false
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 11, 6, 1, true)
	Trigger_1:SetPosition(19.5, 0, 0.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map003_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 8, 5.5, 1, true)
	Trigger_2:SetPosition(50, 0, 0.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map003_1")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 3, 4, 1, true)
	Trigger_3:SetPosition(2.5, 5, 0.5)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map003_1")
	Trigger_3_act1:SetSpawning(4)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit3", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 8, 10.5, 1, true)
	Trigger_4:SetPosition(21, 0, 63.5)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map004_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit4", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 9, 6, 1, true)
	Trigger_5:SetPosition(45.5, 0, 63.5)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map004_1")
	Trigger_5_act1:SetSpawning(2)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit5", true, true, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 1, 4.5, 8, true)
	Trigger_6:SetPosition(2.5, 0, 39)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map006_1")
	Trigger_6_act1:SetSpawning(1)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit6", true, true, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 3, 5, 1, true)
	Trigger_7:SetPosition(40.5, 0, 12.5)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map014_1")
	Trigger_7_act1:SetSpawning(1)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "testtext", true, true, false)
	Trigger_8 = ActivationTrigger(Trigger_8_info, 3, "Normal", "None")
	Trigger_8:SetPosition(23.5, 0, 60)
	Trigger_8_act1 = DisplayTextAction()
	Trigger_8_act1:SetTextId(199)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "dfgdg", true, true, false)
	Trigger_9 = ActivationTrigger(Trigger_9_info, 1.5, "Normal", "None")
	Trigger_9:SetPosition(56, 0, 18.5)
	Trigger_9_act1 = AddRemoveItemAction()
	Trigger_9_act1:SetItemId(2)
	Trigger_9_act1:SetNumber(1)
	Trigger_9_act1:SetInformClientType(2)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_9)

end
