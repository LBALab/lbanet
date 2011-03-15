function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(22)
	Spawn_1:SetPosY(1.01)
	Spawn_1:SetPosZ(48)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(9)
	Spawn_2:SetPosY(8.01)
	Spawn_2:SetPosZ(27)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(20)
	Spawn_3:SetPosY(7.01)
	Spawn_3:SetPosZ(14)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(21)
	Spawn_4:SetPosY(1.01)
	Spawn_4:SetPosZ(49)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(21)
	Spawn_5:SetPosY(1.01)
	Spawn_5:SetPosZ(49)
	Spawn_5:SetName("spawning5")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(8)
	Spawn_6:SetPosY(8.01)
	Spawn_6:SetPosZ(29.5)
	Spawn_6:SetName("spawning6")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(14)
	Spawn_7:SetPosY(3.01)
	Spawn_7:SetPosZ(42)
	Spawn_7:SetName("spawning7")
	environment:AddSpawn(Spawn_7)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Expanded/Grids/Tippett_island_village.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Expanded/Grids/Tippett_island_village.phy"
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

	Actor_11 = ActorObjectInfo(11)
	Actor_11:SetRenderType(3)
	Actor_11.DisplayDesc.ModelId = 0
	Actor_11.DisplayDesc.ModelName = "Hydroglider"
	Actor_11.DisplayDesc.Outfit = "Twinsen"
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
	Actor_11.PhysicDesc.Pos.X = 22.0625
	Actor_11.PhysicDesc.Pos.Y = 0
	Actor_11.PhysicDesc.Pos.Z = 51
	Actor_11.PhysicDesc.Pos.Rotation = 281
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 2
	Actor_11.PhysicDesc.SizeY = 3
	Actor_11.PhysicDesc.SizeZ = 3
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
	Actor_12.DisplayDesc.ModelName = "Rabbibunny"
	Actor_12.DisplayDesc.Outfit = "Afro"
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
	Actor_12.PhysicDesc.Pos.X = 57
	Actor_12.PhysicDesc.Pos.Y = 8
	Actor_12.PhysicDesc.Pos.Z = 21
	Actor_12.PhysicDesc.Pos.Rotation = 433
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 1
	Actor_12.PhysicDesc.SizeY = 6
	Actor_12.PhysicDesc.SizeZ = 1
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

	Actor_13 = ActorObjectInfo(13)
	Actor_13:SetRenderType(3)
	Actor_13.DisplayDesc.ModelId = 0
	Actor_13.DisplayDesc.ModelName = "GroboClone"
	Actor_13.DisplayDesc.Outfit = "Yellow"
	Actor_13.DisplayDesc.Weapon = "No"
	Actor_13.DisplayDesc.Mode = "Normal"
	Actor_13.DisplayDesc.UseLight = true
	Actor_13.DisplayDesc.CastShadow = true
	Actor_13.DisplayDesc.ColorR = 1
	Actor_13.DisplayDesc.ColorG = 1
	Actor_13.DisplayDesc.ColorB = 1
	Actor_13.DisplayDesc.ColorA = 1
	Actor_13.DisplayDesc.TransX = 0
	Actor_13.DisplayDesc.TransY = 0
	Actor_13.DisplayDesc.TransZ = 0
	Actor_13.DisplayDesc.ScaleX = 1
	Actor_13.DisplayDesc.ScaleY = 1
	Actor_13.DisplayDesc.ScaleZ = 1
	Actor_13.DisplayDesc.RotX = 0
	Actor_13.DisplayDesc.RotY = 0
	Actor_13.DisplayDesc.RotZ = 0
	Actor_13:SetModelState(1)
	Actor_13.PhysicDesc.Pos.X = 14.3125
	Actor_13.PhysicDesc.Pos.Y = 5
	Actor_13.PhysicDesc.Pos.Z = 34.0938
	Actor_13.PhysicDesc.Pos.Rotation = 281
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 1.5
	Actor_13.PhysicDesc.SizeY = 5
	Actor_13.PhysicDesc.SizeZ = 1.5
	Actor_13.PhysicDesc.Filename = ""
	Actor_13:SetPhysicalActorType(2)
	Actor_13:SetPhysicalShape(2)
	Actor_13.ExtraInfo.Name = ""
	Actor_13.ExtraInfo.NameColorR = 0
	Actor_13.ExtraInfo.NameColorG = 0
	Actor_13.ExtraInfo.NameColorB = 0
	Actor_13.ExtraInfo.Display = false
	Actor_13.LifeInfo.Display = false
	Actor_13H = NPCHandler(Actor_13)
	Actor_13H_dia = DialogPart()
	Actor_13H_dia:SetResetDialog(false)
	Actor_13H:SetRootDialog(Actor_13H_dia)
	Actor_13H:SetNpcName(-1)
	Actor_13H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_13H)

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(3)
	Actor_14.DisplayDesc.ModelId = 0
	Actor_14.DisplayDesc.ModelName = "Fisherman"
	Actor_14.DisplayDesc.Outfit = "No"
	Actor_14.DisplayDesc.Weapon = "No"
	Actor_14.DisplayDesc.Mode = "Normal"
	Actor_14.DisplayDesc.UseLight = true
	Actor_14.DisplayDesc.CastShadow = true
	Actor_14.DisplayDesc.ColorR = 1
	Actor_14.DisplayDesc.ColorG = 1
	Actor_14.DisplayDesc.ColorB = 1
	Actor_14.DisplayDesc.ColorA = 1
	Actor_14.DisplayDesc.TransX = 0
	Actor_14.DisplayDesc.TransY = 0
	Actor_14.DisplayDesc.TransZ = 0
	Actor_14.DisplayDesc.ScaleX = 1
	Actor_14.DisplayDesc.ScaleY = 1
	Actor_14.DisplayDesc.ScaleZ = 1
	Actor_14.DisplayDesc.RotX = 0
	Actor_14.DisplayDesc.RotY = 0
	Actor_14.DisplayDesc.RotZ = 0
	Actor_14:SetModelState(1)
	Actor_14.PhysicDesc.Pos.X = 54.5
	Actor_14.PhysicDesc.Pos.Y = 1
	Actor_14.PhysicDesc.Pos.Z = 49
	Actor_14.PhysicDesc.Pos.Rotation = 25
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 1
	Actor_14.PhysicDesc.SizeY = 5
	Actor_14.PhysicDesc.SizeZ = 1
	Actor_14.PhysicDesc.Filename = ""
	Actor_14:SetPhysicalActorType(2)
	Actor_14:SetPhysicalShape(2)
	Actor_14.ExtraInfo.Name = ""
	Actor_14.ExtraInfo.NameColorR = 0
	Actor_14.ExtraInfo.NameColorG = 0
	Actor_14.ExtraInfo.NameColorB = 0
	Actor_14.ExtraInfo.Display = false
	Actor_14.LifeInfo.Display = false
	Actor_14H = NPCHandler(Actor_14)
	Actor_14H_dia = DialogPart()
	Actor_14H_dia:SetResetDialog(false)
	Actor_14H:SetRootDialog(Actor_14H_dia)
	Actor_14H:SetNpcName(-1)
	Actor_14H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_14H)

	Actor_15 = ActorObjectInfo(15)
	Actor_15:SetRenderType(3)
	Actor_15.DisplayDesc.ModelId = 0
	Actor_15.DisplayDesc.ModelName = "Object"
	Actor_15.DisplayDesc.Outfit = "MekaPingouin"
	Actor_15.DisplayDesc.Weapon = "No"
	Actor_15.DisplayDesc.Mode = "Normal"
	Actor_15.DisplayDesc.UseLight = true
	Actor_15.DisplayDesc.CastShadow = true
	Actor_15.DisplayDesc.ColorR = 1
	Actor_15.DisplayDesc.ColorG = 1
	Actor_15.DisplayDesc.ColorB = 1
	Actor_15.DisplayDesc.ColorA = 1
	Actor_15.DisplayDesc.TransX = 0
	Actor_15.DisplayDesc.TransY = 0
	Actor_15.DisplayDesc.TransZ = 0
	Actor_15.DisplayDesc.ScaleX = 1
	Actor_15.DisplayDesc.ScaleY = 1
	Actor_15.DisplayDesc.ScaleZ = 1
	Actor_15.DisplayDesc.RotX = 0
	Actor_15.DisplayDesc.RotY = 0
	Actor_15.DisplayDesc.RotZ = 0
	Actor_15:SetModelState(1)
	Actor_15.PhysicDesc.Pos.X = 0
	Actor_15.PhysicDesc.Pos.Y = -1
	Actor_15.PhysicDesc.Pos.Z = 0
	Actor_15.PhysicDesc.Pos.Rotation = 25
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 0.5
	Actor_15.PhysicDesc.SizeY = 2
	Actor_15.PhysicDesc.SizeZ = 0.6
	Actor_15.PhysicDesc.Filename = ""
	Actor_15:SetPhysicalActorType(2)
	Actor_15:SetPhysicalShape(2)
	Actor_15.ExtraInfo.Name = ""
	Actor_15.ExtraInfo.NameColorR = 0
	Actor_15.ExtraInfo.NameColorG = 0
	Actor_15.ExtraInfo.NameColorB = 0
	Actor_15.ExtraInfo.Display = false
	Actor_15.LifeInfo.Display = false
	Actor_15H = NPCHandler(Actor_15)
	Actor_15H_dia = DialogPart()
	Actor_15H_dia:SetResetDialog(false)
	Actor_15H:SetRootDialog(Actor_15H_dia)
	Actor_15H:SetNpcName(-1)
	Actor_15H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_15H)

	Actor_16 = ActorObjectInfo(16)
	Actor_16:SetRenderType(3)
	Actor_16.DisplayDesc.ModelId = 0
	Actor_16.DisplayDesc.ModelName = "Sphero"
	Actor_16.DisplayDesc.Outfit = "Green"
	Actor_16.DisplayDesc.Weapon = "No"
	Actor_16.DisplayDesc.Mode = "Normal"
	Actor_16.DisplayDesc.UseLight = true
	Actor_16.DisplayDesc.CastShadow = true
	Actor_16.DisplayDesc.ColorR = 1
	Actor_16.DisplayDesc.ColorG = 1
	Actor_16.DisplayDesc.ColorB = 1
	Actor_16.DisplayDesc.ColorA = 1
	Actor_16.DisplayDesc.TransX = 0
	Actor_16.DisplayDesc.TransY = 0
	Actor_16.DisplayDesc.TransZ = 0
	Actor_16.DisplayDesc.ScaleX = 1
	Actor_16.DisplayDesc.ScaleY = 1
	Actor_16.DisplayDesc.ScaleZ = 1
	Actor_16.DisplayDesc.RotX = 0
	Actor_16.DisplayDesc.RotY = 0
	Actor_16.DisplayDesc.RotZ = 0
	Actor_16:SetModelState(1)
	Actor_16.PhysicDesc.Pos.X = 22.0938
	Actor_16.PhysicDesc.Pos.Y = 5
	Actor_16.PhysicDesc.Pos.Z = 44.25
	Actor_16.PhysicDesc.Pos.Rotation = 25
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 1
	Actor_16.PhysicDesc.SizeY = 3
	Actor_16.PhysicDesc.SizeZ = 1
	Actor_16.PhysicDesc.Filename = ""
	Actor_16:SetPhysicalActorType(2)
	Actor_16:SetPhysicalShape(2)
	Actor_16.ExtraInfo.Name = ""
	Actor_16.ExtraInfo.NameColorR = 0
	Actor_16.ExtraInfo.NameColorG = 0
	Actor_16.ExtraInfo.NameColorB = 0
	Actor_16.ExtraInfo.Display = false
	Actor_16.LifeInfo.Display = false
	Actor_16H = NPCHandler(Actor_16)
	Actor_16H_dia = DialogPart()
	Actor_16H_dia:SetResetDialog(false)
	Actor_16H:SetRootDialog(Actor_16H_dia)
	Actor_16H:SetNpcName(-1)
	Actor_16H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_16H)

	Trigger_1_info = TriggerInfo(1, "exit1", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 3, 1, true)
	Trigger_1:SetPosition(60, 3, 63.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map091_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit11", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 4, 3, true)
	Trigger_2:SetPosition(6.5, 8, 29.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map101_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit12", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 4, 4, true)
	Trigger_3:SetPosition(12.5, 3, 42)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("polaris_map2")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit13", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 3.5, 4, true)
	Trigger_4:SetPosition(18.5, 7, 14)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map076_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit18", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 2, 2.5, 2, true)
	Trigger_5:SetPosition(62, 3, 63)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map097_1")
	Trigger_5_act1:SetSpawning(2)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "LadderTri_6", true, false, false)
	Trigger_6 = ActivationTrigger(Trigger_6_info, 1.66667, "Normal", "")
	Trigger_6:SetPosition(19.0039, 1, 47.7695)
	Trigger_6_act1 = ClientScriptAction()
	Trigger_6_act1_cs = GoUpLadderScript()
	Trigger_6_act1_cs:SetLadderPositionX(19.0039)
	Trigger_6_act1_cs:SetLadderPositionY(1)
	Trigger_6_act1_cs:SetLadderPositionZ(47.7695)
	Trigger_6_act1_cs:SetLadderHeight(4)
	Trigger_6_act1_cs:SetLadderDirection(180)
	Trigger_6_act1:SetScript(Trigger_6_act1_cs)
	Trigger_6:SetAction1(Trigger_6_act1)
	Trigger_6:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "ContainerTri_7", true, false, false)
	Trigger_7 = ZoneActionTrigger(Trigger_7_info, 2.99804, 5.99609, 1.99805, "Normal", "")
	Trigger_7:SetPosition(7.49902, 1, 54.999)
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

	Trigger_8_info = TriggerInfo(8, "TextTri_8", true, false, false)
	Trigger_8 = ActivationTrigger(Trigger_8_info, 2, "Normal", "")
	Trigger_8:SetPosition(6, 5, 52.999)
	Trigger_8_act1 = DisplayTextAction()
	Trigger_8_act1:SetTextId(14)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "ContainerTri_9", true, false, false)
	Trigger_9 = ZoneActionTrigger(Trigger_9_info, 2.99804, 4.99609, 2.99804, "Normal", "")
	Trigger_9:SetPosition(15.499, 5, 30.499)
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
	Trigger_10 = ZoneActionTrigger(Trigger_10_info, 3.99804, 5.99609, 2.99804, "Normal", "")
	Trigger_10:SetPosition(51.999, 5, 31.499)
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

	Trigger_11_info = TriggerInfo(11, "LadderTri_11", true, false, false)
	Trigger_11 = ActivationTrigger(Trigger_11_info, 1.66667, "Normal", "")
	Trigger_11:SetPosition(57, 1, 47.7803)
	Trigger_11_act1 = ClientScriptAction()
	Trigger_11_act1_cs = GoUpLadderScript()
	Trigger_11_act1_cs:SetLadderPositionX(57)
	Trigger_11_act1_cs:SetLadderPositionY(1)
	Trigger_11_act1_cs:SetLadderPositionZ(47.7803)
	Trigger_11_act1_cs:SetLadderHeight(4)
	Trigger_11_act1_cs:SetLadderDirection(180)
	Trigger_11_act1:SetScript(Trigger_11_act1_cs)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "LadderTri_12", true, false, false)
	Trigger_12 = ActivationTrigger(Trigger_12_info, 1.66667, "Normal", "")
	Trigger_12:SetPosition(23.001, 1, 3.78223)
	Trigger_12_act1 = ClientScriptAction()
	Trigger_12_act1_cs = GoUpLadderScript()
	Trigger_12_act1_cs:SetLadderPositionX(23.001)
	Trigger_12_act1_cs:SetLadderPositionY(1)
	Trigger_12_act1_cs:SetLadderPositionZ(3.78223)
	Trigger_12_act1_cs:SetLadderHeight(4)
	Trigger_12_act1_cs:SetLadderDirection(180)
	Trigger_12_act1:SetScript(Trigger_12_act1_cs)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "TextTri_13", true, false, false)
	Trigger_13 = ActivationTrigger(Trigger_13_info, 2, "Normal", "")
	Trigger_13:SetPosition(14, 6.4375, 25)
	Trigger_13_act1 = DisplayTextAction()
	Trigger_13_act1:SetTextId(14)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "TextTri_14", true, false, false)
	Trigger_14 = ActivationTrigger(Trigger_14_info, 2, "Normal", "")
	Trigger_14:SetPosition(6, 8, 35)
	Trigger_14_act1 = DisplayTextAction()
	Trigger_14_act1:SetTextId(14)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_14)

end
