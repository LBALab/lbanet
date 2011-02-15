function InitMap(environment)
	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = -1163005939
	Actor_1.DisplayDesc.ModelName = "Worlds/Arena/Grids/TheComplexPvpArena.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = -0.00132704
	Actor_1.DisplayDesc.ColorG = -0.00132704
	Actor_1.DisplayDesc.ColorB = -0.00132704
	Actor_1.DisplayDesc.ColorA = -0.00132704
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
	Actor_1.PhysicDesc.Density = -0.00132704
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = -0.00132704
	Actor_1.PhysicDesc.SizeY = -0.00132704
	Actor_1.PhysicDesc.SizeZ = -0.00132704
	Actor_1.PhysicDesc.Filename = "Worlds/Arena/Grids/TheComplexPvpArena.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = -0.00132704
	Actor_1.ExtraInfo.NameColorG = -0.00132704
	Actor_1.ExtraInfo.NameColorB = -0.00132704
	Actor_1.ExtraInfo.Display = false
	Actor_1.LifeInfo.Display = false
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Actor_2 = ActorObjectInfo(2)
	Actor_2:SetRenderType(3)
	Actor_2.DisplayDesc.ModelId = 0
	Actor_2.DisplayDesc.ModelName = "Ameba"
	Actor_2.DisplayDesc.Outfit = "No"
	Actor_2.DisplayDesc.Weapon = "No"
	Actor_2.DisplayDesc.Mode = "Normal"
	Actor_2.DisplayDesc.UseLight = true
	Actor_2.DisplayDesc.CastShadow = true
	Actor_2.DisplayDesc.ColorR = 1
	Actor_2.DisplayDesc.ColorG = 1
	Actor_2.DisplayDesc.ColorB = 1
	Actor_2.DisplayDesc.ColorA = 1
	Actor_2.DisplayDesc.TransX = 0
	Actor_2.DisplayDesc.TransY = 0
	Actor_2.DisplayDesc.TransZ = 0
	Actor_2.DisplayDesc.ScaleX = 1
	Actor_2.DisplayDesc.ScaleY = 1
	Actor_2.DisplayDesc.ScaleZ = 1
	Actor_2.DisplayDesc.RotX = 0
	Actor_2.DisplayDesc.RotY = 0
	Actor_2.DisplayDesc.RotZ = 0
	Actor_2:SetModelState(2)
	Actor_2.PhysicDesc.Pos.X = 43
	Actor_2.PhysicDesc.Pos.Y = 14.1
	Actor_2.PhysicDesc.Pos.Z = 9.5
	Actor_2.PhysicDesc.Pos.Rotation = 90
	Actor_2.PhysicDesc.Density = 1
	Actor_2.PhysicDesc.Collidable = true
	Actor_2.PhysicDesc.SizeX = 2
	Actor_2.PhysicDesc.SizeY = 1
	Actor_2.PhysicDesc.SizeZ = 2.5
	Actor_2.PhysicDesc.Filename = ""
	Actor_2:SetPhysicalActorType(2)
	Actor_2:SetPhysicalShape(2)
	Actor_2.ExtraInfo.Name = ""
	Actor_2.ExtraInfo.NameColorR = 1
	Actor_2.ExtraInfo.NameColorG = 1
	Actor_2.ExtraInfo.NameColorB = 1
	Actor_2.ExtraInfo.Display = false
	Actor_2.LifeInfo.Display = false
	Actor_2H = ActorHandler(Actor_2)
	Actor_2_Sc0 = ASPStartWaypoint(46,7,9.5,true)
	Actor_2H:AddScriptPart(Actor_2_Sc0)
	Actor_2_Sc1 = ASPCustom("")
	Actor_2H:AddScriptPart(Actor_2_Sc1)
	Actor_2_Sc2 = ASPFollowWaypoint(53.5,7,9.5)
	Actor_2H:AddScriptPart(Actor_2_Sc2)
	Actor_2_Sc3 = ASPFollowWaypoint(57.5,7,12.5)
	Actor_2H:AddScriptPart(Actor_2_Sc3)
	Actor_2_Sc4 = ASPFollowWaypoint(61,7,20)
	Actor_2H:AddScriptPart(Actor_2_Sc4)
	Actor_2_Sc5 = ASPFollowWaypoint(56,7,21.5)
	Actor_2H:AddScriptPart(Actor_2_Sc5)
	Actor_2_Sc6 = ASPFollowWaypoint(53,7,26)
	Actor_2H:AddScriptPart(Actor_2_Sc6)
	Actor_2_Sc7 = ASPFollowWaypoint(49,7,26)
	Actor_2H:AddScriptPart(Actor_2_Sc7)
	Actor_2_Sc8 = ASPFollowWaypoint(47.5,8,28.5)
	Actor_2H:AddScriptPart(Actor_2_Sc8)
	Actor_2_Sc9 = ASPFollowWaypoint(47.5,9,32)
	Actor_2H:AddScriptPart(Actor_2_Sc9)
	Actor_2_Sc10 = ASPShowHide(false)
	Actor_2H:AddScriptPart(Actor_2_Sc10)
	Actor_2_Sc11 = ASPFollowWaypoint(43,7,35)
	Actor_2H:AddScriptPart(Actor_2_Sc11)
	Actor_2_Sc12 = ASPFollowWaypoint(38.5,7,35)
	Actor_2H:AddScriptPart(Actor_2_Sc12)
	Actor_2_Sc13 = ASPFollowWaypoint(39,7,26)
	Actor_2H:AddScriptPart(Actor_2_Sc13)
	Actor_2_Sc14 = ASPFollowWaypoint(35,7,29.5)
	Actor_2H:AddScriptPart(Actor_2_Sc14)
	Actor_2_Sc15 = ASPShowHide(true)
	Actor_2H:AddScriptPart(Actor_2_Sc15)
	Actor_2_Sc16 = ASPFollowWaypoint(31.5,8,33.5)
	Actor_2H:AddScriptPart(Actor_2_Sc16)
	Actor_2_Sc17 = ASPFollowWaypoint(36,7,36)
	Actor_2H:AddScriptPart(Actor_2_Sc17)
	Actor_2_Sc18 = ASPFollowWaypoint(40.5,7,40)
	Actor_2H:AddScriptPart(Actor_2_Sc18)
	Actor_2_Sc19 = ASPFollowWaypoint(47.5,7,35)
	Actor_2H:AddScriptPart(Actor_2_Sc19)
	Actor_2_Sc20 = ASPFollowWaypoint(48,9,27.5)
	Actor_2H:AddScriptPart(Actor_2_Sc20)
	environment:AddActorObject(Actor_2H)

	Actor_3 = ActorObjectInfo(3)
	Actor_3:SetRenderType(3)
	Actor_3.DisplayDesc.ModelId = 0
	Actor_3.DisplayDesc.ModelName = "Ameba"
	Actor_3.DisplayDesc.Outfit = "No"
	Actor_3.DisplayDesc.Weapon = "No"
	Actor_3.DisplayDesc.Mode = "Normal"
	Actor_3.DisplayDesc.UseLight = true
	Actor_3.DisplayDesc.CastShadow = true
	Actor_3.DisplayDesc.ColorR = 1
	Actor_3.DisplayDesc.ColorG = 1
	Actor_3.DisplayDesc.ColorB = 1
	Actor_3.DisplayDesc.ColorA = 1
	Actor_3.DisplayDesc.TransX = 0
	Actor_3.DisplayDesc.TransY = 0
	Actor_3.DisplayDesc.TransZ = 0
	Actor_3.DisplayDesc.ScaleX = 1
	Actor_3.DisplayDesc.ScaleY = 1
	Actor_3.DisplayDesc.ScaleZ = 1
	Actor_3.DisplayDesc.RotX = 0
	Actor_3.DisplayDesc.RotY = 0
	Actor_3.DisplayDesc.RotZ = 0
	Actor_3:SetModelState(2)
	Actor_3.PhysicDesc.Pos.X = 34.5
	Actor_3.PhysicDesc.Pos.Y = 7
	Actor_3.PhysicDesc.Pos.Z = 13.5
	Actor_3.PhysicDesc.Pos.Rotation = 0
	Actor_3.PhysicDesc.Density = 1
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = 2
	Actor_3.PhysicDesc.SizeY = 1
	Actor_3.PhysicDesc.SizeZ = 2.5
	Actor_3.PhysicDesc.Filename = ""
	Actor_3:SetPhysicalActorType(2)
	Actor_3:SetPhysicalShape(2)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 1
	Actor_3.ExtraInfo.NameColorG = 1
	Actor_3.ExtraInfo.NameColorB = 1
	Actor_3.ExtraInfo.Display = false
	Actor_3.LifeInfo.Display = false
	Actor_3H = ActorHandler(Actor_3)
	Actor_3_Sc0 = ASPCustom("FunctionCustom")
	Actor_3H:AddScriptPart(Actor_3_Sc0)
	environment:AddActorObject(Actor_3H)

	Actor_4 = ActorObjectInfo(4)
	Actor_4:SetRenderType(2)
	Actor_4.DisplayDesc.ModelId = 0
	Actor_4.DisplayDesc.ModelName = "Worlds/Lba1Original/InventoryImages/02-20-10_18_13_24_164.png"
	Actor_4.DisplayDesc.Outfit = ""
	Actor_4.DisplayDesc.Weapon = ""
	Actor_4.DisplayDesc.Mode = ""
	Actor_4.DisplayDesc.UseLight = true
	Actor_4.DisplayDesc.CastShadow = true
	Actor_4.DisplayDesc.ColorR = 1
	Actor_4.DisplayDesc.ColorG = 1
	Actor_4.DisplayDesc.ColorB = 1
	Actor_4.DisplayDesc.ColorA = 1
	Actor_4.DisplayDesc.TransX = 0
	Actor_4.DisplayDesc.TransY = 0
	Actor_4.DisplayDesc.TransZ = 0
	Actor_4.DisplayDesc.ScaleX = 1
	Actor_4.DisplayDesc.ScaleY = 1
	Actor_4.DisplayDesc.ScaleZ = 1
	Actor_4.DisplayDesc.RotX = 0
	Actor_4.DisplayDesc.RotY = 0
	Actor_4.DisplayDesc.RotZ = 0
	Actor_4:SetModelState(2)
	Actor_4.PhysicDesc.Pos.X = 39
	Actor_4.PhysicDesc.Pos.Y = 7
	Actor_4.PhysicDesc.Pos.Z = 33.5
	Actor_4.PhysicDesc.Pos.Rotation = 0
	Actor_4.PhysicDesc.Density = 1
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 2
	Actor_4.PhysicDesc.SizeY = 5
	Actor_4.PhysicDesc.SizeZ = 0.5
	Actor_4.PhysicDesc.Filename = ""
	Actor_4:SetPhysicalActorType(2)
	Actor_4:SetPhysicalShape(2)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 1
	Actor_4.ExtraInfo.NameColorG = 1
	Actor_4.ExtraInfo.NameColorB = 1
	Actor_4.ExtraInfo.Display = false
	Actor_4.LifeInfo.Display = false
	Actor_4H = DoorHandler(Actor_4,1,0,-90,0.11,false)
	Actor_4_Sc0 = ASPWaitForSignal(1)
	Actor_4H:AddScriptPart(Actor_4_Sc0)
	Actor_4_Sc1 = ASPRotateFromPoint(-90,37,7,33.5,0.11)
	Actor_4H:AddScriptPart(Actor_4_Sc1)
	Actor_4_Sc2 = ASPWaitForSignal(2)
	Actor_4H:AddScriptPart(Actor_4_Sc2)
	Actor_4_Sc3 = ASPRotateFromPoint(90,37,7,33.5,0.11)
	Actor_4H:AddScriptPart(Actor_4_Sc3)
	environment:AddActorObject(Actor_4H)

	Trigger_1_info = TriggerInfo(1, "bvbcb", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 1, 1, true)
	Trigger_1:SetPosition(33, 7, 14)
	Trigger_1_act1 = SendSignalAction()
	Trigger_1_act1:SetActorId(3)
	Trigger_1_act1:SetSignal(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "testlift", true, true, false)
	Trigger_2 = ZoneActionTrigger(Trigger_2_info, 2, 1, 2, "Normal", "None")
	Trigger_2:SetPosition(45, 8, 9)
	Trigger_2_act1 = SendSignalAction()
	Trigger_2_act1:SetActorId(2)
	Trigger_2_act1:SetSignal(5)
	Trigger_2:SetAction1(Trigger_2_act1)
	Trigger_2:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "xcvxc", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 2, 2, true)
	Trigger_3:SetPosition(55.5, 7, 38)
	Trigger_3_act1 = ClientScriptAction()
	Trigger_3_act1_cs = CustomScript()
	Trigger_3_act1_cs:SetLuaFunctionName("ExampleClientFct")
	Trigger_3_act1:SetScript(Trigger_3_act1_cs)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_5_info = TriggerInfo(5, "testanim", true, true, false)
	Trigger_5 = ActivationTrigger(Trigger_5_info, 1.5, "Normal", "None")
	Trigger_5:SetPosition(39.5, 7, 28)
	Trigger_5_act1 = SwitchAction()
	Trigger_5_act1:SetActorId(4)
	Trigger_5_act1:SetSwitchModel("Worlds/Lba1Original/InventoryImages/test3.png")
	Trigger_5_act1_act1 = OpenDoorAction()
	Trigger_5_act1_act1:SetActorId(4)
	Trigger_5_act1:SetActionTrue(Trigger_5_act1_act1)
	Trigger_5_act1_act1 = CloseDoorAction()
	Trigger_5_act1_act1:SetActorId(4)
	Trigger_5_act1:SetActionFalse(Trigger_5_act1_act1)
	Trigger_5:SetAction1(Trigger_5_act1)
	Trigger_5:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_5)

end
