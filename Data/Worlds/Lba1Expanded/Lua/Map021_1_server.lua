function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(33)
	Spawn_1:SetPosY(3.01)
	Spawn_1:SetPosZ(62)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(33)
	Spawn_2:SetPosY(3.01)
	Spawn_2:SetPosZ(62)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(54.5)
	Spawn_3:SetPosY(4.01)
	Spawn_3:SetPosZ(58)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map21.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 1
	Actor_1.DisplayDesc.ColorG = 1
	Actor_1.DisplayDesc.ColorB = 1
	Actor_1.DisplayDesc.ColorA = 1
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
	Actor_1.PhysicDesc.Density = 1
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 0
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 0
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map21.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = "Map"
	Actor_1.ExtraInfo.NameColorR = 0
	Actor_1.ExtraInfo.NameColorG = 0
	Actor_1.ExtraInfo.NameColorB = 0
	Actor_1.ExtraInfo.Display = false
	Actor_1.LifeInfo.Display = false
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(1)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite032.osgb"
	Actor_7.DisplayDesc.Outfit = ""
	Actor_7.DisplayDesc.Weapon = ""
	Actor_7.DisplayDesc.Mode = ""
	Actor_7.DisplayDesc.UseLight = true
	Actor_7.DisplayDesc.CastShadow = false
	Actor_7.DisplayDesc.ColorR = 1
	Actor_7.DisplayDesc.ColorG = 1
	Actor_7.DisplayDesc.ColorB = 1
	Actor_7.DisplayDesc.ColorA = 1
	Actor_7.DisplayDesc.TransX = 0
	Actor_7.DisplayDesc.TransY = 0
	Actor_7.DisplayDesc.TransZ = 0
	Actor_7.DisplayDesc.ScaleX = 1
	Actor_7.DisplayDesc.ScaleY = 1
	Actor_7.DisplayDesc.ScaleZ = 1
	Actor_7.DisplayDesc.RotX = 0
	Actor_7.DisplayDesc.RotY = 0
	Actor_7.DisplayDesc.RotZ = 0
	Actor_7:SetModelState(1)
	Actor_7.PhysicDesc.Pos.X = 49.5
	Actor_7.PhysicDesc.Pos.Y = 6
	Actor_7.PhysicDesc.Pos.Z = 46.5
	Actor_7.PhysicDesc.Pos.Rotation = 0
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 3
	Actor_7.PhysicDesc.SizeY = 10
	Actor_7.PhysicDesc.SizeZ = 1
	Actor_7.PhysicDesc.Filename = ""
	Actor_7:SetPhysicalActorType(2)
	Actor_7:SetPhysicalShape(2)
	Actor_7.ExtraInfo.Name = ""
	Actor_7.ExtraInfo.NameColorR = 0
	Actor_7.ExtraInfo.NameColorG = 0
	Actor_7.ExtraInfo.NameColorB = 0
	Actor_7.ExtraInfo.Display = false
	Actor_7.LifeInfo.Display = false
	Actor_7H = DoorHandler(Actor_7,0,0,3,0.004,false)
	Actor_7_Sc0 = ASPWaitForSignal(1)
	Actor_7H:AddScriptPart(Actor_7_Sc0)
	Actor_7_Sc1 = ASPGoTo(46.5,6,46.5,0.004)
	Actor_7H:AddScriptPart(Actor_7_Sc1)
	Actor_7_Sc2 = ASPWaitForSignal(2)
	Actor_7H:AddScriptPart(Actor_7_Sc2)
	Actor_7_Sc3 = ASPGoTo(49.5,6,46.5,0.004)
	Actor_7H:AddScriptPart(Actor_7_Sc3)
	environment:AddActorObject(Actor_7H)

	Actor_8 = ActorObjectInfo(8)
	Actor_8:SetRenderType(1)
	Actor_8.DisplayDesc.ModelId = 0
	Actor_8.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite032.osgb"
	Actor_8.DisplayDesc.Outfit = ""
	Actor_8.DisplayDesc.Weapon = ""
	Actor_8.DisplayDesc.Mode = ""
	Actor_8.DisplayDesc.UseLight = true
	Actor_8.DisplayDesc.CastShadow = false
	Actor_8.DisplayDesc.ColorR = 1
	Actor_8.DisplayDesc.ColorG = 1
	Actor_8.DisplayDesc.ColorB = 1
	Actor_8.DisplayDesc.ColorA = 1
	Actor_8.DisplayDesc.TransX = 0
	Actor_8.DisplayDesc.TransY = 0
	Actor_8.DisplayDesc.TransZ = 0
	Actor_8.DisplayDesc.ScaleX = 1
	Actor_8.DisplayDesc.ScaleY = 1
	Actor_8.DisplayDesc.ScaleZ = 1
	Actor_8.DisplayDesc.RotX = 0
	Actor_8.DisplayDesc.RotY = 0
	Actor_8.DisplayDesc.RotZ = 0
	Actor_8:SetModelState(1)
	Actor_8.PhysicDesc.Pos.X = 35.5
	Actor_8.PhysicDesc.Pos.Y = 6
	Actor_8.PhysicDesc.Pos.Z = 46.5
	Actor_8.PhysicDesc.Pos.Rotation = 0
	Actor_8.PhysicDesc.Density = 1
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 3
	Actor_8.PhysicDesc.SizeY = 10
	Actor_8.PhysicDesc.SizeZ = 1
	Actor_8.PhysicDesc.Filename = ""
	Actor_8:SetPhysicalActorType(2)
	Actor_8:SetPhysicalShape(2)
	Actor_8.ExtraInfo.Name = ""
	Actor_8.ExtraInfo.NameColorR = 0
	Actor_8.ExtraInfo.NameColorG = 0
	Actor_8.ExtraInfo.NameColorB = 0
	Actor_8.ExtraInfo.Display = false
	Actor_8.LifeInfo.Display = false
	Actor_8H = DoorHandler(Actor_8,0,1,3,0.004,false)
	Actor_8_Sc0 = ASPWaitForSignal(1)
	Actor_8H:AddScriptPart(Actor_8_Sc0)
	Actor_8_Sc1 = ASPGoTo(38.5,6,46.5,0.004)
	Actor_8H:AddScriptPart(Actor_8_Sc1)
	Actor_8_Sc2 = ASPWaitForSignal(2)
	Actor_8H:AddScriptPart(Actor_8_Sc2)
	Actor_8_Sc3 = ASPGoTo(35.5,6,46.5,0.004)
	Actor_8H:AddScriptPart(Actor_8_Sc3)
	environment:AddActorObject(Actor_8H)

	Actor_10 = ActorObjectInfo(10)
	Actor_10:SetRenderType(3)
	Actor_10.DisplayDesc.ModelId = 0
	Actor_10.DisplayDesc.ModelName = "Object"
	Actor_10.DisplayDesc.Outfit = "BuCor"
	Actor_10.DisplayDesc.Weapon = "No"
	Actor_10.DisplayDesc.Mode = "Normal"
	Actor_10.DisplayDesc.UseLight = true
	Actor_10.DisplayDesc.CastShadow = true
	Actor_10.DisplayDesc.ColorR = 1
	Actor_10.DisplayDesc.ColorG = 1
	Actor_10.DisplayDesc.ColorB = 1
	Actor_10.DisplayDesc.ColorA = 1
	Actor_10.DisplayDesc.TransX = 0
	Actor_10.DisplayDesc.TransY = 0
	Actor_10.DisplayDesc.TransZ = 0
	Actor_10.DisplayDesc.ScaleX = 1
	Actor_10.DisplayDesc.ScaleY = 1
	Actor_10.DisplayDesc.ScaleZ = 1
	Actor_10.DisplayDesc.RotX = 0
	Actor_10.DisplayDesc.RotY = 0
	Actor_10.DisplayDesc.RotZ = 0
	Actor_10:SetModelState(1)
	Actor_10.PhysicDesc.Pos.X = 41.5938
	Actor_10.PhysicDesc.Pos.Y = 8.6875
	Actor_10.PhysicDesc.Pos.Z = 39
	Actor_10.PhysicDesc.Pos.Rotation = 25
	Actor_10.PhysicDesc.Density = 1
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 0.5
	Actor_10.PhysicDesc.SizeY = 0.5
	Actor_10.PhysicDesc.SizeZ = 0.5
	Actor_10.PhysicDesc.Filename = ""
	Actor_10:SetPhysicalActorType(2)
	Actor_10:SetPhysicalShape(2)
	Actor_10.ExtraInfo.Name = ""
	Actor_10.ExtraInfo.NameColorR = 0
	Actor_10.ExtraInfo.NameColorG = 0
	Actor_10.ExtraInfo.NameColorB = 0
	Actor_10.ExtraInfo.Display = false
	Actor_10.LifeInfo.Display = false
	Actor_10H = NPCHandler(Actor_10)
	Actor_10H_dia = DialogPart()
	Actor_10H_dia:SetResetDialog(false)
	Actor_10H:SetRootDialog(Actor_10H_dia)
	Actor_10H:SetNpcName(-1)
	Actor_10H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_10H)

	Actor_11 = ActorObjectInfo(11)
	Actor_11:SetRenderType(3)
	Actor_11.DisplayDesc.ModelId = 0
	Actor_11.DisplayDesc.ModelName = "Object"
	Actor_11.DisplayDesc.Outfit = "BuMedaillon"
	Actor_11.DisplayDesc.Weapon = "No"
	Actor_11.DisplayDesc.Mode = "Normal"
	Actor_11.DisplayDesc.UseLight = true
	Actor_11.DisplayDesc.CastShadow = true
	Actor_11.DisplayDesc.ColorR = 1
	Actor_11.DisplayDesc.ColorG = 1
	Actor_11.DisplayDesc.ColorB = 1
	Actor_11.DisplayDesc.ColorA = 1
	Actor_11.DisplayDesc.TransX = 0
	Actor_11.DisplayDesc.TransY = 0
	Actor_11.DisplayDesc.TransZ = 0
	Actor_11.DisplayDesc.ScaleX = 1
	Actor_11.DisplayDesc.ScaleY = 1
	Actor_11.DisplayDesc.ScaleZ = 1
	Actor_11.DisplayDesc.RotX = 0
	Actor_11.DisplayDesc.RotY = 0
	Actor_11.DisplayDesc.RotZ = 0
	Actor_11:SetModelState(1)
	Actor_11.PhysicDesc.Pos.X = 42.4375
	Actor_11.PhysicDesc.Pos.Y = 8.6875
	Actor_11.PhysicDesc.Pos.Z = 39
	Actor_11.PhysicDesc.Pos.Rotation = 25
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 0.5
	Actor_11.PhysicDesc.SizeY = 0.5
	Actor_11.PhysicDesc.SizeZ = 0.5
	Actor_11.PhysicDesc.Filename = ""
	Actor_11:SetPhysicalActorType(2)
	Actor_11:SetPhysicalShape(2)
	Actor_11.ExtraInfo.Name = ""
	Actor_11.ExtraInfo.NameColorR = 0
	Actor_11.ExtraInfo.NameColorG = 0
	Actor_11.ExtraInfo.NameColorB = 0
	Actor_11.ExtraInfo.Display = false
	Actor_11.LifeInfo.Display = false
	Actor_11H = NPCHandler(Actor_11)
	Actor_11H_dia = DialogPart()
	Actor_11H_dia:SetResetDialog(false)
	Actor_11H:SetRootDialog(Actor_11H_dia)
	Actor_11H:SetNpcName(-1)
	Actor_11H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_11H)

	Actor_12 = ActorObjectInfo(12)
	Actor_12:SetRenderType(3)
	Actor_12.DisplayDesc.ModelId = 0
	Actor_12.DisplayDesc.ModelName = "Object"
	Actor_12.DisplayDesc.Outfit = "MekaPingouin"
	Actor_12.DisplayDesc.Weapon = "No"
	Actor_12.DisplayDesc.Mode = "Normal"
	Actor_12.DisplayDesc.UseLight = true
	Actor_12.DisplayDesc.CastShadow = true
	Actor_12.DisplayDesc.ColorR = 1
	Actor_12.DisplayDesc.ColorG = 1
	Actor_12.DisplayDesc.ColorB = 1
	Actor_12.DisplayDesc.ColorA = 1
	Actor_12.DisplayDesc.TransX = 0
	Actor_12.DisplayDesc.TransY = 0
	Actor_12.DisplayDesc.TransZ = 0
	Actor_12.DisplayDesc.ScaleX = 1
	Actor_12.DisplayDesc.ScaleY = 1
	Actor_12.DisplayDesc.ScaleZ = 1
	Actor_12.DisplayDesc.RotX = 0
	Actor_12.DisplayDesc.RotY = 0
	Actor_12.DisplayDesc.RotZ = 0
	Actor_12:SetModelState(1)
	Actor_12.PhysicDesc.Pos.X = 0
	Actor_12.PhysicDesc.Pos.Y = -1
	Actor_12.PhysicDesc.Pos.Z = 0
	Actor_12.PhysicDesc.Pos.Rotation = 25
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 0.5
	Actor_12.PhysicDesc.SizeY = 2
	Actor_12.PhysicDesc.SizeZ = 0.6
	Actor_12.PhysicDesc.Filename = ""
	Actor_12:SetPhysicalActorType(2)
	Actor_12:SetPhysicalShape(2)
	Actor_12.ExtraInfo.Name = ""
	Actor_12.ExtraInfo.NameColorR = 0
	Actor_12.ExtraInfo.NameColorG = 0
	Actor_12.ExtraInfo.NameColorB = 0
	Actor_12.ExtraInfo.Display = false
	Actor_12.LifeInfo.Display = false
	Actor_12H = NPCHandler(Actor_12)
	Actor_12H_dia = DialogPart()
	Actor_12H_dia:SetResetDialog(false)
	Actor_12H:SetRootDialog(Actor_12H_dia)
	Actor_12H:SetNpcName(-1)
	Actor_12H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_12H)

	Trigger_1_info = TriggerInfo(1, "exit1", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 4, 5, 1, true)
	Trigger_1:SetPosition(33, 2, 63.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map004_1")
	Trigger_1_act1:SetSpawning(6)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit2", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 4, 1, true)
	Trigger_2:SetPosition(53.5, 4, 61.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map005_1")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 3.00196, 5.44141, 2.5957, "Normal", "")
	Trigger_3:SetPosition(53.501, 4, 51.2979)
	Trigger_3_act1 = OpenContainerAction()
	Trigger_3_act1:SetTimeToReset(300)
		Trigger_3_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_3_act1:AddItem(Trigger_3_act1ContItem0)
		Trigger_3_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_3_act1:AddItem(Trigger_3_act1ContItem1)
		Trigger_3_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_3_act1:AddItem(Trigger_3_act1ContItem2)
		Trigger_3_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_3_act1:AddItem(Trigger_3_act1ContItem3)
	Trigger_3:SetAction1(Trigger_3_act1)
	Trigger_3:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "ContainerTri_4", true, false, false)
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 1.99805, 2.99609, 2.99804, "Normal", "")
	Trigger_4:SetPosition(34.999, 6, 35.499)
	Trigger_4_act1 = OpenContainerAction()
	Trigger_4_act1:SetTimeToReset(300)
		Trigger_4_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_4_act1:AddItem(Trigger_4_act1ContItem0)
		Trigger_4_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_4_act1:AddItem(Trigger_4_act1ContItem1)
		Trigger_4_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_4_act1:AddItem(Trigger_4_act1ContItem2)
		Trigger_4_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_4_act1:AddItem(Trigger_4_act1ContItem3)
	Trigger_4:SetAction1(Trigger_4_act1)
	Trigger_4:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "ContainerTri_5", true, false, false)
	Trigger_5 = ZoneActionTrigger(Trigger_5_info, 1.99805, 4.99609, 0.998046, "Normal", "")
	Trigger_5:SetPosition(34.999, 6, 37.499)
	Trigger_5_act1 = OpenContainerAction()
	Trigger_5_act1:SetTimeToReset(300)
		Trigger_5_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_5_act1:AddItem(Trigger_5_act1ContItem0)
		Trigger_5_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_5_act1:AddItem(Trigger_5_act1ContItem1)
		Trigger_5_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_5_act1:AddItem(Trigger_5_act1ContItem2)
		Trigger_5_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_5_act1:AddItem(Trigger_5_act1ContItem3)
	Trigger_5:SetAction1(Trigger_5_act1)
	Trigger_5:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "ContainerTri_6", true, false, false)
	Trigger_6 = ZoneActionTrigger(Trigger_6_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_6:SetPosition(34.999, 6, 41.999)
	Trigger_6_act1 = OpenContainerAction()
	Trigger_6_act1:SetTimeToReset(300)
		Trigger_6_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_6_act1:AddItem(Trigger_6_act1ContItem0)
		Trigger_6_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_6_act1:AddItem(Trigger_6_act1ContItem1)
		Trigger_6_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_6_act1:AddItem(Trigger_6_act1ContItem2)
		Trigger_6_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_6_act1:AddItem(Trigger_6_act1ContItem3)
	Trigger_6:SetAction1(Trigger_6_act1)
	Trigger_6:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "ContainerTri_7", true, false, false)
	Trigger_7 = ZoneActionTrigger(Trigger_7_info, 2.99804, 4.99609, 2.99804, "Normal", "")
	Trigger_7:SetPosition(49.499, 6, 35.499)
	Trigger_7_act1 = OpenContainerAction()
	Trigger_7_act1:SetTimeToReset(300)
		Trigger_7_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_7_act1:AddItem(Trigger_7_act1ContItem0)
		Trigger_7_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_7_act1:AddItem(Trigger_7_act1ContItem1)
		Trigger_7_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_7_act1:AddItem(Trigger_7_act1ContItem2)
		Trigger_7_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_7_act1:AddItem(Trigger_7_act1ContItem3)
	Trigger_7:SetAction1(Trigger_7_act1)
	Trigger_7:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "ExitDownTri_8", true, false, false)
	Trigger_8 = ActivationTrigger(Trigger_8_info, 2, "Normal", "")
	Trigger_8:SetPosition(54, 4, 60.5)
	Trigger_8_act1 = ClientScriptAction()
	Trigger_8_act1_cs = TakeExitDownScript()
	Trigger_8_act1_cs:SetExitPositionX(54)
	Trigger_8_act1_cs:SetExitPositionY(4)
	Trigger_8_act1_cs:SetExitPositionZ(60.5)
	Trigger_8_act1_cs:SetExitDirection(0)
	Trigger_8_act1:SetScript(Trigger_8_act1_cs)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "DoorTri_9", true, false, false)
	Trigger_9 = ZoneTrigger(Trigger_9_info, 4, 10, 4, false)
	Trigger_9:SetPosition(49.5, 6, 46.5)
	Trigger_9:SetStayUpdateFrequency(-1)
	Trigger_9_act1 = OpenDoorAction()
	Trigger_9_act1:SetActorId(7)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9_act2 = CloseDoorAction()
	Trigger_9_act2:SetActorId(7)
	Trigger_9:SetAction2(Trigger_9_act2)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "DoorTri_10", true, false, false)
	Trigger_10 = ZoneTrigger(Trigger_10_info, 4, 10, 4, false)
	Trigger_10:SetPosition(35.5, 6, 46.5)
	Trigger_10:SetStayUpdateFrequency(-1)
	Trigger_10_act1 = OpenDoorAction()
	Trigger_10_act1:SetActorId(8)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10_act2 = CloseDoorAction()
	Trigger_10_act2:SetActorId(8)
	Trigger_10:SetAction2(Trigger_10_act2)
	environment:AddTrigger(Trigger_10)

end
