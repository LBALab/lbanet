function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(61)
	Spawn_1:SetPosY(8.01)
	Spawn_1:SetPosZ(35)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(37)
	Spawn_2:SetPosY(8.01)
	Spawn_2:SetPosZ(61)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(37)
	Spawn_3:SetPosY(8.01)
	Spawn_3:SetPosZ(56)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(37)
	Spawn_4:SetPosY(8.01)
	Spawn_4:SetPosZ(51)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(38.5)
	Spawn_5:SetPosY(8.01)
	Spawn_5:SetPosZ(45)
	Spawn_5:SetName("spawning5")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(37)
	Spawn_6:SetPosY(8.01)
	Spawn_6:SetPosZ(41)
	Spawn_6:SetName("spawning6")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(44)
	Spawn_7:SetPosY(8.01)
	Spawn_7:SetPosZ(36)
	Spawn_7:SetName("spawning7")
	environment:AddSpawn(Spawn_7)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Expanded/Grids/Lbae_map1.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Expanded/Grids/Lbae_map1.phy"
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

	Actor_9 = ActorObjectInfo(9)
	Actor_9:SetRenderType(3)
	Actor_9.DisplayDesc.ModelId = 0
	Actor_9.DisplayDesc.ModelName = "Object"
	Actor_9.DisplayDesc.Outfit = "MekaPingouin"
	Actor_9.DisplayDesc.Weapon = "No"
	Actor_9.DisplayDesc.Mode = "Normal"
	Actor_9.DisplayDesc.UseLight = true
	Actor_9.DisplayDesc.CastShadow = true
	Actor_9.DisplayDesc.ColorR = 1
	Actor_9.DisplayDesc.ColorG = 1
	Actor_9.DisplayDesc.ColorB = 1
	Actor_9.DisplayDesc.ColorA = 1
	Actor_9.DisplayDesc.TransX = 0
	Actor_9.DisplayDesc.TransY = 0
	Actor_9.DisplayDesc.TransZ = 0
	Actor_9.DisplayDesc.ScaleX = 1
	Actor_9.DisplayDesc.ScaleY = 1
	Actor_9.DisplayDesc.ScaleZ = 1
	Actor_9.DisplayDesc.RotX = 0
	Actor_9.DisplayDesc.RotY = 0
	Actor_9.DisplayDesc.RotZ = 0
	Actor_9:SetModelState(1)
	Actor_9.PhysicDesc.Pos.X = 0
	Actor_9.PhysicDesc.Pos.Y = -1
	Actor_9.PhysicDesc.Pos.Z = 0
	Actor_9.PhysicDesc.Pos.Rotation = 25
	Actor_9.PhysicDesc.Density = 1
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 0.5
	Actor_9.PhysicDesc.SizeY = 2
	Actor_9.PhysicDesc.SizeZ = 0.6
	Actor_9.PhysicDesc.Filename = ""
	Actor_9:SetPhysicalActorType(2)
	Actor_9:SetPhysicalShape(2)
	Actor_9.ExtraInfo.Name = ""
	Actor_9.ExtraInfo.NameColorR = 0
	Actor_9.ExtraInfo.NameColorG = 0
	Actor_9.ExtraInfo.NameColorB = 0
	Actor_9.ExtraInfo.Display = false
	Actor_9.LifeInfo.Display = false
	Actor_9H = NPCHandler(Actor_9)
	Actor_9H_dia = DialogPart()
	Actor_9H_dia:SetResetDialog(false)
	Actor_9H:SetRootDialog(Actor_9H_dia)
	Actor_9H:SetNpcName(-1)
	Actor_9H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_9H)

	Actor_10 = ActorObjectInfo(10)
	Actor_10:SetRenderType(3)
	Actor_10.DisplayDesc.ModelId = 0
	Actor_10.DisplayDesc.ModelName = "Object"
	Actor_10.DisplayDesc.Outfit = "Computer"
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
	Actor_10.PhysicDesc.Pos.X = 52.5625
	Actor_10.PhysicDesc.Pos.Y = 6
	Actor_10.PhysicDesc.Pos.Z = 51.0313
	Actor_10.PhysicDesc.Pos.Rotation = 25
	Actor_10.PhysicDesc.Density = 1
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 1.5
	Actor_10.PhysicDesc.SizeY = 2.5
	Actor_10.PhysicDesc.SizeZ = 1
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
	Actor_11.DisplayDesc.ModelName = "Nurse"
	Actor_11.DisplayDesc.Outfit = "Tech"
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
	Actor_11.PhysicDesc.Pos.X = 53.5
	Actor_11.PhysicDesc.Pos.Y = 3
	Actor_11.PhysicDesc.Pos.Z = 53.4688
	Actor_11.PhysicDesc.Pos.Rotation = 365
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 1
	Actor_11.PhysicDesc.SizeY = 5
	Actor_11.PhysicDesc.SizeZ = 1
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
	Actor_12.DisplayDesc.ModelName = "Nurse"
	Actor_12.DisplayDesc.Outfit = "Guard"
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
	Actor_12.PhysicDesc.Pos.X = 39
	Actor_12.PhysicDesc.Pos.Y = 8
	Actor_12.PhysicDesc.Pos.Z = 42.25
	Actor_12.PhysicDesc.Pos.Rotation = 281
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 1
	Actor_12.PhysicDesc.SizeY = 5
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
	Actor_13.DisplayDesc.ModelName = "RabbiClone"
	Actor_13.DisplayDesc.Outfit = "Red"
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
	Actor_13.PhysicDesc.Pos.X = 35
	Actor_13.PhysicDesc.Pos.Y = 10
	Actor_13.PhysicDesc.Pos.Z = 40
	Actor_13.PhysicDesc.Pos.Rotation = 281
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 1
	Actor_13.PhysicDesc.SizeY = 6
	Actor_13.PhysicDesc.SizeZ = 1
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

	Trigger_1_info = TriggerInfo(1, "exit1", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 3, 4, true)
	Trigger_1:SetPosition(63.5, 8, 35)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map095_1")
	Trigger_1_act1:SetSpawning(4)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit16", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 5, 3, 1, true)
	Trigger_2:SetPosition(61.5, 0, 63.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map095_1")
	Trigger_2_act1:SetSpawning(5)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit17", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 3, 4, true)
	Trigger_3:SetPosition(63.5, 0, 61)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map095_1")
	Trigger_3_act1:SetSpawning(6)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit2", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 3, 4, 2, true)
	Trigger_4:SetPosition(35.5, 10, 60)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map003_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit3", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 3, 4, 3, true)
	Trigger_5:SetPosition(35.5, 10, 55.5)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map013_1")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit4", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 3, 4, 3, true)
	Trigger_6:SetPosition(35.5, 10, 50.5)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map044_1")
	Trigger_6_act1:SetSpawning(1)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit5", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 3, 4, 3, true)
	Trigger_7:SetPosition(35.5, 10, 45.5)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map066_1")
	Trigger_7_act1:SetSpawning(1)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "exit6", true, false, false)
	Trigger_8 = ZoneTrigger(Trigger_8_info, 3, 4, 3, true)
	Trigger_8:SetPosition(35.5, 10, 40.5)
	Trigger_8:SetStayUpdateFrequency(-1)
	Trigger_8_act1 = TeleportAction()
	Trigger_8_act1:SetMapName("Map100_1")
	Trigger_8_act1:SetSpawning(1)
	Trigger_8:SetAction1(Trigger_8_act1)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "exit7", true, false, false)
	Trigger_9 = ZoneTrigger(Trigger_9_info, 3, 4, 3, true)
	Trigger_9:SetPosition(44.5, 10, 33.5)
	Trigger_9:SetStayUpdateFrequency(-1)
	Trigger_9_act1 = TeleportAction()
	Trigger_9_act1:SetMapName("MyMap0_1")
	Trigger_9_act1:SetSpawning(2)
	Trigger_9:SetAction1(Trigger_9_act1)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "ContainerTri_10", true, false, false)
	Trigger_10 = ZoneActionTrigger(Trigger_10_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_10:SetPosition(42.999, 8, 32.999)
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
	Trigger_11 = ZoneActionTrigger(Trigger_11_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_11:SetPosition(38.999, 8, 34.999)
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

	Trigger_12_info = TriggerInfo(12, "TextTri_12", true, false, false)
	Trigger_12 = ActivationTrigger(Trigger_12_info, 2, "Normal", "")
	Trigger_12:SetPosition(40.999, 10, 32)
	Trigger_12_act1 = DisplayTextAction()
	Trigger_12_act1:SetTextId(74)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "ContainerTri_13", true, false, false)
	Trigger_13 = ZoneActionTrigger(Trigger_13_info, 2, 6, 2, "Normal", "")
	Trigger_13:SetPosition(56, 2, 38.1563)
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
	Trigger_14 = ZoneActionTrigger(Trigger_14_info, 1.99805, 5.99609, 1.99805, "Normal", "")
	Trigger_14:SetPosition(57.999, 2, 38.1553)
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
	Trigger_15 = ZoneActionTrigger(Trigger_15_info, 1.99805, 5.99609, 1.99805, "Normal", "")
	Trigger_15:SetPosition(52.999, 2, 38.1553)
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
	Trigger_16 = ZoneActionTrigger(Trigger_16_info, 2, 6, 2, "Normal", "")
	Trigger_16:SetPosition(51, 2, 38.1563)
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

end
