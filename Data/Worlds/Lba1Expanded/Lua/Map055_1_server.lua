function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(62)
	Spawn_1:SetPosY(8.01)
	Spawn_1:SetPosZ(56)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(55)
	Spawn_2:SetPosY(8.01)
	Spawn_2:SetPosZ(51)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map55.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map55.phy"
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
	Actor_7:SetRenderType(3)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "Object"
	Actor_7.DisplayDesc.Outfit = "MekaPingouin"
	Actor_7.DisplayDesc.Weapon = "No"
	Actor_7.DisplayDesc.Mode = "Normal"
	Actor_7.DisplayDesc.UseLight = true
	Actor_7.DisplayDesc.CastShadow = true
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
	Actor_7.PhysicDesc.Pos.X = 0
	Actor_7.PhysicDesc.Pos.Y = -1
	Actor_7.PhysicDesc.Pos.Z = 0
	Actor_7.PhysicDesc.Pos.Rotation = 25
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 0.5
	Actor_7.PhysicDesc.SizeY = 2
	Actor_7.PhysicDesc.SizeZ = 0.6
	Actor_7.PhysicDesc.Filename = ""
	Actor_7:SetPhysicalActorType(2)
	Actor_7:SetPhysicalShape(2)
	Actor_7.ExtraInfo.Name = ""
	Actor_7.ExtraInfo.NameColorR = 0
	Actor_7.ExtraInfo.NameColorG = 0
	Actor_7.ExtraInfo.NameColorB = 0
	Actor_7.ExtraInfo.Display = false
	Actor_7.LifeInfo.Display = false
	Actor_7H = NPCHandler(Actor_7)
	Actor_7H_dia = DialogPart()
	Actor_7H_dia:SetResetDialog(false)
	Actor_7H:SetRootDialog(Actor_7H_dia)
	Actor_7H:SetNpcName(-1)
	Actor_7H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_7H)

	Actor_8 = ActorObjectInfo(8)
	Actor_8:SetRenderType(3)
	Actor_8.DisplayDesc.ModelId = 0
	Actor_8.DisplayDesc.ModelName = ""
	Actor_8.DisplayDesc.Outfit = ""
	Actor_8.DisplayDesc.Weapon = ""
	Actor_8.DisplayDesc.Mode = ""
	Actor_8.DisplayDesc.UseLight = true
	Actor_8.DisplayDesc.CastShadow = true
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
	Actor_8.PhysicDesc.Pos.X = 50.5313
	Actor_8.PhysicDesc.Pos.Y = 12.5
	Actor_8.PhysicDesc.Pos.Z = 55
	Actor_8.PhysicDesc.Pos.Rotation = 281
	Actor_8.PhysicDesc.Density = 1
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 0.5
	Actor_8.PhysicDesc.SizeY = 2
	Actor_8.PhysicDesc.SizeZ = 0.6
	Actor_8.PhysicDesc.Filename = ""
	Actor_8:SetPhysicalActorType(2)
	Actor_8:SetPhysicalShape(2)
	Actor_8.ExtraInfo.Name = ""
	Actor_8.ExtraInfo.NameColorR = 0
	Actor_8.ExtraInfo.NameColorG = 0
	Actor_8.ExtraInfo.NameColorB = 0
	Actor_8.ExtraInfo.Display = false
	Actor_8.LifeInfo.Display = false
	Actor_8H = NPCHandler(Actor_8)
	Actor_8H_dia = DialogPart()
	Actor_8H_dia:SetResetDialog(false)
	Actor_8H:SetRootDialog(Actor_8H_dia)
	Actor_8H:SetNpcName(-1)
	Actor_8H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_8H)

	Trigger_1_info = TriggerInfo(1, "exit1", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 3, 2, true)
	Trigger_1:SetPosition(56, 15, 50)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map002_1")
	Trigger_1_act1:SetSpawning(11)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit3", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 3, 4, true)
	Trigger_2:SetPosition(63.5, 8, 56)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map034_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "LadderTri_3", true, false, false)
	Trigger_3 = ActivationTrigger(Trigger_3_info, 1.66667, "Normal", "")
	Trigger_3:SetPosition(56, 8, 49.7969)
	Trigger_3_act1 = ClientScriptAction()
	Trigger_3_act1_cs = GoUpLadderScript()
	Trigger_3_act1_cs:SetLadderPositionX(56)
	Trigger_3_act1_cs:SetLadderPositionY(8)
	Trigger_3_act1_cs:SetLadderPositionZ(49.7969)
	Trigger_3_act1_cs:SetLadderHeight(13.6289)
	Trigger_3_act1_cs:SetLadderDirection(180)
	Trigger_3_act1:SetScript(Trigger_3_act1_cs)
	Trigger_3:SetAction1(Trigger_3_act1)
	Trigger_3:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "TextTri_4", true, false, false)
	Trigger_4 = ActivationTrigger(Trigger_4_info, 2, "Normal", "")
	Trigger_4:SetPosition(59.999, 8, 49)
	Trigger_4_act1 = DisplayTextAction()
	Trigger_4_act1:SetTextId(234)
	Trigger_4:SetAction1(Trigger_4_act1)
	Trigger_4:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "ContainerTri_5", true, false, false)
	Trigger_5 = ZoneActionTrigger(Trigger_5_info, 1.99805, 5.99609, 1.99805, "Normal", "")
	Trigger_5:SetPosition(50.999, 8, 50.999)
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
	Trigger_6 = ZoneActionTrigger(Trigger_6_info, 1.99805, 5.99609, 1.99805, "Normal", "")
	Trigger_6:SetPosition(52.999, 8, 50.999)
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

	Trigger_7_info = TriggerInfo(7, "LadderTri_7", true, false, false)
	Trigger_7 = ActivationTrigger(Trigger_7_info, 1.66667, "Normal", "")
	Trigger_7:SetPosition(50.999, 3, 58.8271)
	Trigger_7_act1 = ClientScriptAction()
	Trigger_7_act1_cs = GoUpLadderScript()
	Trigger_7_act1_cs:SetLadderPositionX(50.999)
	Trigger_7_act1_cs:SetLadderPositionY(3)
	Trigger_7_act1_cs:SetLadderPositionZ(58.8271)
	Trigger_7_act1_cs:SetLadderHeight(5)
	Trigger_7_act1_cs:SetLadderDirection(180)
	Trigger_7_act1:SetScript(Trigger_7_act1_cs)
	Trigger_7:SetAction1(Trigger_7_act1)
	Trigger_7:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_7)

end
