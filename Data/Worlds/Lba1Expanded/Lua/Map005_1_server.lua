function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(57)
	Spawn_1:SetPosY(7.01)
	Spawn_1:SetPosZ(28.5)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(23)
	Spawn_2:SetPosY(6.01)
	Spawn_2:SetPosZ(22)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(20.5)
	Spawn_3:SetPosY(2.01)
	Spawn_3:SetPosZ(11)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map5.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map5.phy"
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

	Actor_23 = ActorObjectInfo(23)
	Actor_23:SetRenderType(3)
	Actor_23.DisplayDesc.ModelId = 0
	Actor_23.DisplayDesc.ModelName = "Quetch"
	Actor_23.DisplayDesc.Outfit = "Zoe"
	Actor_23.DisplayDesc.Weapon = "No"
	Actor_23.DisplayDesc.Mode = "Normal"
	Actor_23.DisplayDesc.UseLight = true
	Actor_23.DisplayDesc.CastShadow = true
	Actor_23.DisplayDesc.ColorR = 1
	Actor_23.DisplayDesc.ColorG = 1
	Actor_23.DisplayDesc.ColorB = 1
	Actor_23.DisplayDesc.ColorA = 1
	Actor_23.DisplayDesc.TransX = 0
	Actor_23.DisplayDesc.TransY = 0
	Actor_23.DisplayDesc.TransZ = 0
	Actor_23.DisplayDesc.ScaleX = 1
	Actor_23.DisplayDesc.ScaleY = 1
	Actor_23.DisplayDesc.ScaleZ = 1
	Actor_23.DisplayDesc.RotX = 0
	Actor_23.DisplayDesc.RotY = 0
	Actor_23.DisplayDesc.RotZ = 0
	Actor_23:SetModelState(1)
	Actor_23.PhysicDesc.Pos.X = 56
	Actor_23.PhysicDesc.Pos.Y = 7
	Actor_23.PhysicDesc.Pos.Z = 27.5938
	Actor_23.PhysicDesc.Pos.Rotation = 433
	Actor_23.PhysicDesc.Density = 1
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 1
	Actor_23.PhysicDesc.SizeY = 5
	Actor_23.PhysicDesc.SizeZ = 1
	Actor_23.PhysicDesc.Filename = ""
	Actor_23:SetPhysicalActorType(2)
	Actor_23:SetPhysicalShape(2)
	Actor_23.ExtraInfo.Name = ""
	Actor_23.ExtraInfo.NameColorR = 0
	Actor_23.ExtraInfo.NameColorG = 0
	Actor_23.ExtraInfo.NameColorB = 0
	Actor_23.ExtraInfo.Display = true
	Actor_23.LifeInfo.Display = false
	Actor_23H = NPCHandler(Actor_23)
	Actor_23H_dia = DialogPart()
	Actor_23H_dia:SetResetDialog(false)	
	Actor_23H:SetRootDialog(Actor_23H_dia)
	Actor_23H:SetNpcName(1)
	Actor_23H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_23H)

	Actor_24 = ActorObjectInfo(24)
	Actor_24:SetRenderType(3)
	Actor_24.DisplayDesc.ModelId = 0
	Actor_24.DisplayDesc.ModelName = "GroboClone"
	Actor_24.DisplayDesc.Outfit = "Yellow"
	Actor_24.DisplayDesc.Weapon = "No"
	Actor_24.DisplayDesc.Mode = "Normal"
	Actor_24.DisplayDesc.UseLight = true
	Actor_24.DisplayDesc.CastShadow = true
	Actor_24.DisplayDesc.ColorR = 1
	Actor_24.DisplayDesc.ColorG = 1
	Actor_24.DisplayDesc.ColorB = 1
	Actor_24.DisplayDesc.ColorA = 1
	Actor_24.DisplayDesc.TransX = 0
	Actor_24.DisplayDesc.TransY = 0
	Actor_24.DisplayDesc.TransZ = 0
	Actor_24.DisplayDesc.ScaleX = 1
	Actor_24.DisplayDesc.ScaleY = 1
	Actor_24.DisplayDesc.ScaleZ = 1
	Actor_24.DisplayDesc.RotX = 0
	Actor_24.DisplayDesc.RotY = 0
	Actor_24.DisplayDesc.RotZ = 0
	Actor_24:SetModelState(1)
	Actor_24.PhysicDesc.Pos.X = 61
	Actor_24.PhysicDesc.Pos.Y = 7
	Actor_24.PhysicDesc.Pos.Z = 28
	Actor_24.PhysicDesc.Pos.Rotation = 433
	Actor_24.PhysicDesc.Density = 1
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 1.5
	Actor_24.PhysicDesc.SizeY = 5
	Actor_24.PhysicDesc.SizeZ = 1.5
	Actor_24.PhysicDesc.Filename = ""
	Actor_24:SetPhysicalActorType(2)
	Actor_24:SetPhysicalShape(2)
	Actor_24.ExtraInfo.Name = ""
	Actor_24.ExtraInfo.NameColorR = 0
	Actor_24.ExtraInfo.NameColorG = 0
	Actor_24.ExtraInfo.NameColorB = 0
	Actor_24.ExtraInfo.Display = false
	Actor_24.LifeInfo.Display = false
	Actor_24H = NPCHandler(Actor_24)
	Actor_24H_dia = DialogPart()
	Actor_24H_dia:SetResetDialog(false)
	Actor_24H:SetRootDialog(Actor_24H_dia)
	Actor_24H:SetNpcName(-1)
	Actor_24H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_24H)

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(3)
	Actor_25.DisplayDesc.ModelId = 0
	Actor_25.DisplayDesc.ModelName = "GroboClone"
	Actor_25.DisplayDesc.Outfit = "SuperGro"
	Actor_25.DisplayDesc.Weapon = "No"
	Actor_25.DisplayDesc.Mode = "Normal"
	Actor_25.DisplayDesc.UseLight = true
	Actor_25.DisplayDesc.CastShadow = true
	Actor_25.DisplayDesc.ColorR = 1
	Actor_25.DisplayDesc.ColorG = 1
	Actor_25.DisplayDesc.ColorB = 1
	Actor_25.DisplayDesc.ColorA = 1
	Actor_25.DisplayDesc.TransX = 0
	Actor_25.DisplayDesc.TransY = 0
	Actor_25.DisplayDesc.TransZ = 0
	Actor_25.DisplayDesc.ScaleX = 1
	Actor_25.DisplayDesc.ScaleY = 1
	Actor_25.DisplayDesc.ScaleZ = 1
	Actor_25.DisplayDesc.RotX = 0
	Actor_25.DisplayDesc.RotY = 0
	Actor_25.DisplayDesc.RotZ = 0
	Actor_25:SetModelState(1)
	Actor_25.PhysicDesc.Pos.X = 61
	Actor_25.PhysicDesc.Pos.Y = 7
	Actor_25.PhysicDesc.Pos.Z = 26.8125
	Actor_25.PhysicDesc.Pos.Rotation = 433
	Actor_25.PhysicDesc.Density = 1
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 1.5
	Actor_25.PhysicDesc.SizeY = 5
	Actor_25.PhysicDesc.SizeZ = 1.5
	Actor_25.PhysicDesc.Filename = ""
	Actor_25:SetPhysicalActorType(2)
	Actor_25:SetPhysicalShape(2)
	Actor_25.ExtraInfo.Name = ""
	Actor_25.ExtraInfo.NameColorR = 0
	Actor_25.ExtraInfo.NameColorG = 0
	Actor_25.ExtraInfo.NameColorB = 0
	Actor_25.ExtraInfo.Display = false
	Actor_25.LifeInfo.Display = false
	Actor_25H = NPCHandler(Actor_25)
	Actor_25H_dia = DialogPart()
	Actor_25H_dia:SetResetDialog(false)
	Actor_25H:SetRootDialog(Actor_25H_dia)
	Actor_25H:SetNpcName(-1)
	Actor_25H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_25H)

	Actor_26 = ActorObjectInfo(26)
	Actor_26:SetRenderType(3)
	Actor_26.DisplayDesc.ModelId = 0
	Actor_26.DisplayDesc.ModelName = ""
	Actor_26.DisplayDesc.Outfit = ""
	Actor_26.DisplayDesc.Weapon = ""
	Actor_26.DisplayDesc.Mode = ""
	Actor_26.DisplayDesc.UseLight = true
	Actor_26.DisplayDesc.CastShadow = true
	Actor_26.DisplayDesc.ColorR = 1
	Actor_26.DisplayDesc.ColorG = 1
	Actor_26.DisplayDesc.ColorB = 1
	Actor_26.DisplayDesc.ColorA = 1
	Actor_26.DisplayDesc.TransX = 0
	Actor_26.DisplayDesc.TransY = 0
	Actor_26.DisplayDesc.TransZ = 0
	Actor_26.DisplayDesc.ScaleX = 1
	Actor_26.DisplayDesc.ScaleY = 1
	Actor_26.DisplayDesc.ScaleZ = 1
	Actor_26.DisplayDesc.RotX = 0
	Actor_26.DisplayDesc.RotY = 0
	Actor_26.DisplayDesc.RotZ = 0
	Actor_26:SetModelState(1)
	Actor_26.PhysicDesc.Pos.X = 30.6563
	Actor_26.PhysicDesc.Pos.Y = 7
	Actor_26.PhysicDesc.Pos.Z = 17.0313
	Actor_26.PhysicDesc.Pos.Rotation = 25
	Actor_26.PhysicDesc.Density = 1
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 1.5
	Actor_26.PhysicDesc.SizeY = 5
	Actor_26.PhysicDesc.SizeZ = 1.5
	Actor_26.PhysicDesc.Filename = ""
	Actor_26:SetPhysicalActorType(2)
	Actor_26:SetPhysicalShape(2)
	Actor_26.ExtraInfo.Name = ""
	Actor_26.ExtraInfo.NameColorR = 0
	Actor_26.ExtraInfo.NameColorG = 0
	Actor_26.ExtraInfo.NameColorB = 0
	Actor_26.ExtraInfo.Display = false
	Actor_26.LifeInfo.Display = false
	Actor_26H = NPCHandler(Actor_26)
	Actor_26H_dia = DialogPart()
	Actor_26H_dia:SetResetDialog(false)
	Actor_26H:SetRootDialog(Actor_26H_dia)
	Actor_26H:SetNpcName(-1)
	Actor_26H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_26H)

	Actor_27 = ActorObjectInfo(27)
	Actor_27:SetRenderType(3)
	Actor_27.DisplayDesc.ModelId = 0
	Actor_27.DisplayDesc.ModelName = "Object"
	Actor_27.DisplayDesc.Outfit = "MekaPingouin"
	Actor_27.DisplayDesc.Weapon = "No"
	Actor_27.DisplayDesc.Mode = "Normal"
	Actor_27.DisplayDesc.UseLight = true
	Actor_27.DisplayDesc.CastShadow = true
	Actor_27.DisplayDesc.ColorR = 1
	Actor_27.DisplayDesc.ColorG = 1
	Actor_27.DisplayDesc.ColorB = 1
	Actor_27.DisplayDesc.ColorA = 1
	Actor_27.DisplayDesc.TransX = 0
	Actor_27.DisplayDesc.TransY = 0
	Actor_27.DisplayDesc.TransZ = 0
	Actor_27.DisplayDesc.ScaleX = 1
	Actor_27.DisplayDesc.ScaleY = 1
	Actor_27.DisplayDesc.ScaleZ = 1
	Actor_27.DisplayDesc.RotX = 0
	Actor_27.DisplayDesc.RotY = 0
	Actor_27.DisplayDesc.RotZ = 0
	Actor_27:SetModelState(1)
	Actor_27.PhysicDesc.Pos.X = 0
	Actor_27.PhysicDesc.Pos.Y = -1
	Actor_27.PhysicDesc.Pos.Z = 0
	Actor_27.PhysicDesc.Pos.Rotation = 25
	Actor_27.PhysicDesc.Density = 1
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 0.5
	Actor_27.PhysicDesc.SizeY = 2
	Actor_27.PhysicDesc.SizeZ = 0.6
	Actor_27.PhysicDesc.Filename = ""
	Actor_27:SetPhysicalActorType(2)
	Actor_27:SetPhysicalShape(2)
	Actor_27.ExtraInfo.Name = ""
	Actor_27.ExtraInfo.NameColorR = 0
	Actor_27.ExtraInfo.NameColorG = 0
	Actor_27.ExtraInfo.NameColorB = 0
	Actor_27.ExtraInfo.Display = false
	Actor_27.LifeInfo.Display = false
	Actor_27H = NPCHandler(Actor_27)
	Actor_27H_dia = DialogPart()
	Actor_27H_dia:SetResetDialog(false)
	Actor_27H:SetRootDialog(Actor_27H_dia)
	Actor_27H:SetNpcName(-1)
	Actor_27H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_27H)

	Trigger_1_info = TriggerInfo(1, "exit1", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4.5, 3, true)
	Trigger_1:SetPosition(58.5, 7, 28.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map004_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit2", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 3, 2, true)
	Trigger_2:SetPosition(21.5, 0, 8)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map021_1")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit3", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 3.5, 1, true)
	Trigger_3:SetPosition(22.5, 5, 20.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map004_1")
	Trigger_3_act1:SetSpawning(3)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "ContainerTri_4", true, false, false)
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 2.99804, 7.99609, 1.99805, "Normal", "")
	Trigger_4:SetPosition(33.499, 5, 8.99902)
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
	Trigger_5 = ZoneActionTrigger(Trigger_5_info, 2.46876, 4, 2.53126, "Normal", "")
	Trigger_5:SetPosition(34.2344, 5, 39.2656)
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
	Trigger_6 = ZoneActionTrigger(Trigger_6_info, 2.4043, 3.99609, 2.43554, "Normal", "")
	Trigger_6:SetPosition(34.3271, 5, 43.7178)
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
	Trigger_7 = ZoneActionTrigger(Trigger_7_info, 2.5957, 4.00391, 3.06446, "Normal", "")
	Trigger_7:SetPosition(47.2979, 5, 43.2822)
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

	Trigger_8_info = TriggerInfo(8, "ContainerTri_8", true, false, false)
	Trigger_8 = ZoneActionTrigger(Trigger_8_info, 2.7832, 4.00391, 2.5957, "Normal", "")
	Trigger_8:SetPosition(47.6104, 5, 39.2979)
	Trigger_8_act1 = OpenContainerAction()
	Trigger_8_act1:SetTimeToReset(300)
		Trigger_8_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_8_act1:AddItem(Trigger_8_act1ContItem0)
		Trigger_8_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_8_act1:AddItem(Trigger_8_act1ContItem1)
		Trigger_8_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_8_act1:AddItem(Trigger_8_act1ContItem2)
		Trigger_8_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_8_act1:AddItem(Trigger_8_act1ContItem3)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "ContainerTri_9", true, false, false)
	Trigger_9 = ZoneActionTrigger(Trigger_9_info, 3, 5.74609, 2, "Normal", "")
	Trigger_9:SetPosition(36.5, 5, 9)
	Trigger_9_act1 = OpenContainerAction()
	Trigger_9_act1:SetTimeToReset(300)
		Trigger_9_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_9_act1:AddItem(Trigger_9_act1ContItem0)
		Trigger_9_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_9_act1:AddItem(Trigger_9_act1ContItem1)
		Trigger_9_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_9_act1:AddItem(Trigger_9_act1ContItem2)
		Trigger_9_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_9_act1:AddItem(Trigger_9_act1ContItem3)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "ContainerTri_10", true, false, false)
	Trigger_10 = ZoneActionTrigger(Trigger_10_info, 3, 5.74609, 2, "Normal", "")
	Trigger_10:SetPosition(39.5, 5, 9)
	Trigger_10_act1 = OpenContainerAction()
	Trigger_10_act1:SetTimeToReset(300)
		Trigger_10_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_10_act1:AddItem(Trigger_10_act1ContItem0)
		Trigger_10_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_10_act1:AddItem(Trigger_10_act1ContItem1)
		Trigger_10_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_10_act1:AddItem(Trigger_10_act1ContItem2)
		Trigger_10_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_10_act1:AddItem(Trigger_10_act1ContItem3)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "ContainerTri_11", true, false, false)
	Trigger_11 = ZoneActionTrigger(Trigger_11_info, 3.15626, 7, 3.15626, "Normal", "")
	Trigger_11:SetPosition(45.5781, 5, 8.60938)
	Trigger_11_act1 = OpenContainerAction()
	Trigger_11_act1:SetTimeToReset(300)
		Trigger_11_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_11_act1:AddItem(Trigger_11_act1ContItem0)
		Trigger_11_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_11_act1:AddItem(Trigger_11_act1ContItem1)
		Trigger_11_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_11_act1:AddItem(Trigger_11_act1ContItem2)
		Trigger_11_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_11_act1:AddItem(Trigger_11_act1ContItem3)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "ContainerTri_12", true, false, false)
	Trigger_12 = ZoneActionTrigger(Trigger_12_info, 2.99804, 5.99609, 1.99805, "Normal", "")
	Trigger_12:SetPosition(23.499, 5, 27.999)
	Trigger_12_act1 = OpenContainerAction()
	Trigger_12_act1:SetTimeToReset(300)
		Trigger_12_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_12_act1:AddItem(Trigger_12_act1ContItem0)
		Trigger_12_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_12_act1:AddItem(Trigger_12_act1ContItem1)
		Trigger_12_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_12_act1:AddItem(Trigger_12_act1ContItem2)
		Trigger_12_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_12_act1:AddItem(Trigger_12_act1ContItem3)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "ContainerTri_13", true, false, false)
	Trigger_13 = ZoneActionTrigger(Trigger_13_info, 1.6582, 4, 1.56445, "Normal", "")
	Trigger_13:SetPosition(22.8291, 5, 50.8447)
	Trigger_13_act1 = OpenContainerAction()
	Trigger_13_act1:SetTimeToReset(300)
		Trigger_13_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_13_act1:AddItem(Trigger_13_act1ContItem0)
		Trigger_13_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_13_act1:AddItem(Trigger_13_act1ContItem1)
		Trigger_13_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_13_act1:AddItem(Trigger_13_act1ContItem2)
		Trigger_13_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_13_act1:AddItem(Trigger_13_act1ContItem3)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "ContainerTri_14", true, false, false)
	Trigger_14 = ZoneActionTrigger(Trigger_14_info, 1.65625, 4.00391, 1.5625, "Normal", "")
	Trigger_14:SetPosition(22.7656, 5, 46.2188)
	Trigger_14_act1 = OpenContainerAction()
	Trigger_14_act1:SetTimeToReset(300)
		Trigger_14_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_14_act1:AddItem(Trigger_14_act1ContItem0)
		Trigger_14_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_14_act1:AddItem(Trigger_14_act1ContItem1)
		Trigger_14_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_14_act1:AddItem(Trigger_14_act1ContItem2)
		Trigger_14_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_14_act1:AddItem(Trigger_14_act1ContItem3)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "ContainerTri_15", true, false, false)
	Trigger_15 = ZoneActionTrigger(Trigger_15_info, 1.59375, 4, 1.375, "Normal", "")
	Trigger_15:SetPosition(22.7969, 5, 44.6875)
	Trigger_15_act1 = OpenContainerAction()
	Trigger_15_act1:SetTimeToReset(300)
		Trigger_15_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_15_act1:AddItem(Trigger_15_act1ContItem0)
		Trigger_15_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_15_act1:AddItem(Trigger_15_act1ContItem1)
		Trigger_15_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_15_act1:AddItem(Trigger_15_act1ContItem2)
		Trigger_15_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_15_act1:AddItem(Trigger_15_act1ContItem3)
	Trigger_15:SetAction1(Trigger_15_act1)
	Trigger_15:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_15)

	Trigger_16_info = TriggerInfo(16, "ContainerTri_16", true, false, false)
	Trigger_16 = ZoneActionTrigger(Trigger_16_info, 1.68945, 4, 1.18945, "Normal", "")
	Trigger_16:SetPosition(22.8447, 5, 40.3447)
	Trigger_16_act1 = OpenContainerAction()
	Trigger_16_act1:SetTimeToReset(300)
		Trigger_16_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_16_act1:AddItem(Trigger_16_act1ContItem0)
		Trigger_16_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_16_act1:AddItem(Trigger_16_act1ContItem1)
		Trigger_16_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_16_act1:AddItem(Trigger_16_act1ContItem2)
		Trigger_16_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_16_act1:AddItem(Trigger_16_act1ContItem3)
	Trigger_16:SetAction1(Trigger_16_act1)
	Trigger_16:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_16)

	Trigger_17_info = TriggerInfo(17, "ContainerTri_17", true, false, false)
	Trigger_17 = ZoneActionTrigger(Trigger_17_info, 2.99804, 5.99609, 2.99804, "Normal", "")
	Trigger_17:SetPosition(53.499, 5, 8.49902)
	Trigger_17_act1 = OpenContainerAction()
	Trigger_17_act1:SetTimeToReset(300)
		Trigger_17_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_17_act1:AddItem(Trigger_17_act1ContItem0)
		Trigger_17_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_17_act1:AddItem(Trigger_17_act1ContItem1)
		Trigger_17_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_17_act1:AddItem(Trigger_17_act1ContItem2)
		Trigger_17_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_17_act1:AddItem(Trigger_17_act1ContItem3)
	Trigger_17:SetAction1(Trigger_17_act1)
	Trigger_17:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_17)

	Trigger_18_info = TriggerInfo(18, "ContainerTri_18", true, false, false)
	Trigger_18 = ZoneActionTrigger(Trigger_18_info, 1.99805, 3.99609, 2.99804, "Normal", "")
	Trigger_18:SetPosition(34.999, 5, 46.499)
	Trigger_18_act1 = OpenContainerAction()
	Trigger_18_act1:SetTimeToReset(300)
		Trigger_18_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_18_act1:AddItem(Trigger_18_act1ContItem0)
		Trigger_18_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_18_act1:AddItem(Trigger_18_act1ContItem1)
		Trigger_18_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_18_act1:AddItem(Trigger_18_act1ContItem2)
		Trigger_18_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_18_act1:AddItem(Trigger_18_act1ContItem3)
	Trigger_18:SetAction1(Trigger_18_act1)
	Trigger_18:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_18)

	Trigger_19_info = TriggerInfo(19, "ContainerTri_19", true, false, false)
	Trigger_19 = ZoneActionTrigger(Trigger_19_info, 2.72852, 4.21094, 2.94726, "Normal", "")
	Trigger_19:SetPosition(43.2393, 5, 35.4736)
	Trigger_19_act1 = OpenContainerAction()
	Trigger_19_act1:SetTimeToReset(300)
		Trigger_19_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_19_act1:AddItem(Trigger_19_act1ContItem0)
		Trigger_19_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_19_act1:AddItem(Trigger_19_act1ContItem1)
		Trigger_19_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_19_act1:AddItem(Trigger_19_act1ContItem2)
		Trigger_19_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_19_act1:AddItem(Trigger_19_act1ContItem3)
	Trigger_19:SetAction1(Trigger_19_act1)
	Trigger_19:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_19)

	Trigger_20_info = TriggerInfo(20, "ContainerTri_20", true, false, false)
	Trigger_20 = ZoneActionTrigger(Trigger_20_info, 2.38086, 4.07813, 2.5371, "Normal", "")
	Trigger_20:SetPosition(47.5029, 5, 21.2686)
	Trigger_20_act1 = OpenContainerAction()
	Trigger_20_act1:SetTimeToReset(300)
		Trigger_20_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_20_act1:AddItem(Trigger_20_act1ContItem0)
		Trigger_20_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_20_act1:AddItem(Trigger_20_act1ContItem1)
		Trigger_20_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_20_act1:AddItem(Trigger_20_act1ContItem2)
		Trigger_20_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_20_act1:AddItem(Trigger_20_act1ContItem3)
	Trigger_20:SetAction1(Trigger_20_act1)
	Trigger_20:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_20)

	Trigger_21_info = TriggerInfo(21, "ContainerTri_21", true, false, false)
	Trigger_21 = ZoneActionTrigger(Trigger_21_info, 3.99804, 5.99609, 2.99804, "Normal", "")
	Trigger_21:SetPosition(19.999, 1, 15.499)
	Trigger_21_act1 = OpenContainerAction()
	Trigger_21_act1:SetTimeToReset(300)
		Trigger_21_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_21_act1:AddItem(Trigger_21_act1ContItem0)
		Trigger_21_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_21_act1:AddItem(Trigger_21_act1ContItem1)
		Trigger_21_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_21_act1:AddItem(Trigger_21_act1ContItem2)
		Trigger_21_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_21_act1:AddItem(Trigger_21_act1ContItem3)
	Trigger_21:SetAction1(Trigger_21_act1)
	Trigger_21:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_21)

	Trigger_22_info = TriggerInfo(22, "ContainerTri_22", true, false, false)
	Trigger_22 = ZoneActionTrigger(Trigger_22_info, 2.99804, 5.74609, 1.99805, "Normal", "")
	Trigger_22:SetPosition(42.499, 5, 8.99902)
	Trigger_22_act1 = OpenContainerAction()
	Trigger_22_act1:SetTimeToReset(300)
		Trigger_22_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_22_act1:AddItem(Trigger_22_act1ContItem0)
		Trigger_22_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_22_act1:AddItem(Trigger_22_act1ContItem1)
		Trigger_22_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_22_act1:AddItem(Trigger_22_act1ContItem2)
		Trigger_22_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_22_act1:AddItem(Trigger_22_act1ContItem3)
	Trigger_22:SetAction1(Trigger_22_act1)
	Trigger_22:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_22)

	Trigger_23_info = TriggerInfo(23, "ExitDownTri_23", true, false, false)
	Trigger_23 = ActivationTrigger(Trigger_23_info, 2, "Normal", "")
	Trigger_23:SetPosition(21.5, 1, 10.5)
	Trigger_23_act1 = ClientScriptAction()
	Trigger_23_act1_cs = TakeExitDownScript()
	Trigger_23_act1_cs:SetExitPositionX(21.5)
	Trigger_23_act1_cs:SetExitPositionY(1)
	Trigger_23_act1_cs:SetExitPositionZ(10.5)
	Trigger_23_act1_cs:SetExitDirection(180)
	Trigger_23_act1:SetScript(Trigger_23_act1_cs)
	Trigger_23:SetAction1(Trigger_23_act1)
	Trigger_23:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_23)

	Trigger_24_info = TriggerInfo(24, "armoire", true, true, false)
	Trigger_24 = ZoneActionTrigger(Trigger_24_info, 3, 3, 2, "Normal", "None")
	Trigger_24:SetPosition(45.9, 5, 47.3)
	Trigger_24_act1 = MultiAction()
	Trigger_24_act1_act0 = AddRemoveItemAction()
	Trigger_24_act1_act0:SetItemId(24)
	Trigger_24_act1_act0:SetNumber(1)
	Trigger_24_act1_act0:SetInformClientType(1)
	Trigger_24_act1:AddAction(Trigger_24_act1_act0)
	Trigger_24_act1_act1 = AddRemoveItemAction()
	Trigger_24_act1_act1:SetItemId(27)
	Trigger_24_act1_act1:SetNumber(1)
	Trigger_24_act1_act1:SetInformClientType(1)
	Trigger_24_act1:AddAction(Trigger_24_act1_act1)
	Trigger_24_act1_act2 = AddRemoveItemAction()
	Trigger_24_act1_act2:SetItemId(23)
	Trigger_24_act1_act2:SetNumber(1)
	Trigger_24_act1_act2:SetInformClientType(1)
	Trigger_24_act1:AddAction(Trigger_24_act1_act2)
	Trigger_24_act1_act3 = AddRemoveItemAction()
	Trigger_24_act1_act3:SetItemId(22)
	Trigger_24_act1_act3:SetNumber(1)
	Trigger_24_act1_act3:SetInformClientType(2)
	Trigger_24_act1:AddAction(Trigger_24_act1_act3)
	Trigger_24:SetAction1(Trigger_24_act1)
	Trigger_24:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_24)

end
