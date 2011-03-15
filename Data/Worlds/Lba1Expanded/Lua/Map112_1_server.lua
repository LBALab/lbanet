function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(55)
	Spawn_1:SetPosY(18.01)
	Spawn_1:SetPosZ(53)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map112.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map112.phy"
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

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(3)
	Actor_5.DisplayDesc.ModelId = 0
	Actor_5.DisplayDesc.ModelName = "Object"
	Actor_5.DisplayDesc.Outfit = "MekaPingouin"
	Actor_5.DisplayDesc.Weapon = "No"
	Actor_5.DisplayDesc.Mode = "Normal"
	Actor_5.DisplayDesc.UseLight = true
	Actor_5.DisplayDesc.CastShadow = true
	Actor_5.DisplayDesc.ColorR = 1
	Actor_5.DisplayDesc.ColorG = 1
	Actor_5.DisplayDesc.ColorB = 1
	Actor_5.DisplayDesc.ColorA = 1
	Actor_5.DisplayDesc.TransX = 0
	Actor_5.DisplayDesc.TransY = 0
	Actor_5.DisplayDesc.TransZ = 0
	Actor_5.DisplayDesc.ScaleX = 1
	Actor_5.DisplayDesc.ScaleY = 1
	Actor_5.DisplayDesc.ScaleZ = 1
	Actor_5.DisplayDesc.RotX = 0
	Actor_5.DisplayDesc.RotY = 0
	Actor_5.DisplayDesc.RotZ = 0
	Actor_5:SetModelState(1)
	Actor_5.PhysicDesc.Pos.X = 0
	Actor_5.PhysicDesc.Pos.Y = -1
	Actor_5.PhysicDesc.Pos.Z = 0
	Actor_5.PhysicDesc.Pos.Rotation = 25
	Actor_5.PhysicDesc.Density = 1
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = 0.5
	Actor_5.PhysicDesc.SizeY = 2
	Actor_5.PhysicDesc.SizeZ = 0.6
	Actor_5.PhysicDesc.Filename = ""
	Actor_5:SetPhysicalActorType(2)
	Actor_5:SetPhysicalShape(2)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = 0
	Actor_5.ExtraInfo.NameColorG = 0
	Actor_5.ExtraInfo.NameColorB = 0
	Actor_5.ExtraInfo.Display = false
	Actor_5.LifeInfo.Display = false
	Actor_5H = NPCHandler(Actor_5)
	Actor_5H_dia = DialogPart()
	Actor_5H_dia:SetResetDialog(false)
	Actor_5H:SetRootDialog(Actor_5H_dia)
	Actor_5H:SetNpcName(-1)
	Actor_5H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_5H)

	Actor_6 = ActorObjectInfo(6)
	Actor_6:SetRenderType(3)
	Actor_6.DisplayDesc.ModelId = 0
	Actor_6.DisplayDesc.ModelName = "Quetch"
	Actor_6.DisplayDesc.Outfit = "Zoe"
	Actor_6.DisplayDesc.Weapon = "No"
	Actor_6.DisplayDesc.Mode = "Normal"
	Actor_6.DisplayDesc.UseLight = true
	Actor_6.DisplayDesc.CastShadow = true
	Actor_6.DisplayDesc.ColorR = 1
	Actor_6.DisplayDesc.ColorG = 1
	Actor_6.DisplayDesc.ColorB = 1
	Actor_6.DisplayDesc.ColorA = 1
	Actor_6.DisplayDesc.TransX = 0
	Actor_6.DisplayDesc.TransY = 0
	Actor_6.DisplayDesc.TransZ = 0
	Actor_6.DisplayDesc.ScaleX = 1
	Actor_6.DisplayDesc.ScaleY = 1
	Actor_6.DisplayDesc.ScaleZ = 1
	Actor_6.DisplayDesc.RotX = 0
	Actor_6.DisplayDesc.RotY = 0
	Actor_6.DisplayDesc.RotZ = 0
	Actor_6:SetModelState(1)
	Actor_6.PhysicDesc.Pos.X = 55
	Actor_6.PhysicDesc.Pos.Y = 21.6563
	Actor_6.PhysicDesc.Pos.Z = 52
	Actor_6.PhysicDesc.Pos.Rotation = 25
	Actor_6.PhysicDesc.Density = 1
	Actor_6.PhysicDesc.Collidable = true
	Actor_6.PhysicDesc.SizeX = 1
	Actor_6.PhysicDesc.SizeY = 5
	Actor_6.PhysicDesc.SizeZ = 1
	Actor_6.PhysicDesc.Filename = ""
	Actor_6:SetPhysicalActorType(2)
	Actor_6:SetPhysicalShape(2)
	Actor_6.ExtraInfo.Name = ""
	Actor_6.ExtraInfo.NameColorR = 0
	Actor_6.ExtraInfo.NameColorG = 0
	Actor_6.ExtraInfo.NameColorB = 0
	Actor_6.ExtraInfo.Display = false
	Actor_6.LifeInfo.Display = false
	Actor_6H = NPCHandler(Actor_6)
	Actor_6H_dia = DialogPart()
	Actor_6H_dia:SetResetDialog(false)
	Actor_6H:SetRootDialog(Actor_6H_dia)
	Actor_6H:SetNpcName(-1)
	Actor_6H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_6H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 1.5, 2, true)
	Trigger_1:SetPosition(56, -1, 60)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map113_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "ContainerTri_2", true, false, false)
	Trigger_2 = ZoneActionTrigger(Trigger_2_info, 2.99804, 4.99609, 2.99804, "Normal", "")
	Trigger_2:SetPosition(61.499, 0, 52.499)
	Trigger_2_act1 = OpenContainerAction()
	Trigger_2_act1:SetTimeToReset(300)
		Trigger_2_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_2_act1:AddItem(Trigger_2_act1ContItem0)
		Trigger_2_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_2_act1:AddItem(Trigger_2_act1ContItem1)
		Trigger_2_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_2_act1:AddItem(Trigger_2_act1ContItem2)
		Trigger_2_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_2_act1:AddItem(Trigger_2_act1ContItem3)
	Trigger_2:SetAction1(Trigger_2_act1)
	Trigger_2:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 2.99804, 4.99609, 2.99804, "Normal", "")
	Trigger_3:SetPosition(62.499, 0, 62.499)
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
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 2.99804, 4.99609, 2.99804, "Normal", "")
	Trigger_4:SetPosition(53.499, 0, 62.499)
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

end
