function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(63)
	Spawn_1:SetPosY(3.01)
	Spawn_1:SetPosZ(51)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map60.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map60.phy"
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

	Actor_3 = ActorObjectInfo(3)
	Actor_3:SetRenderType(3)
	Actor_3.DisplayDesc.ModelId = 0
	Actor_3.DisplayDesc.ModelName = "SoldierCar"
	Actor_3.DisplayDesc.Outfit = "Twinsen"
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
	Actor_3:SetModelState(1)
	Actor_3.PhysicDesc.Pos.X = 52
	Actor_3.PhysicDesc.Pos.Y = 0
	Actor_3.PhysicDesc.Pos.Z = 57
	Actor_3.PhysicDesc.Pos.Rotation = 177
	Actor_3.PhysicDesc.Density = 1
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = 2
	Actor_3.PhysicDesc.SizeY = 2
	Actor_3.PhysicDesc.SizeZ = 2.5
	Actor_3.PhysicDesc.Filename = ""
	Actor_3:SetPhysicalActorType(2)
	Actor_3:SetPhysicalShape(2)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 0
	Actor_3.ExtraInfo.NameColorG = 0
	Actor_3.ExtraInfo.NameColorB = 0
	Actor_3.ExtraInfo.Display = false
	Actor_3.LifeInfo.Display = false
	Actor_3H = NPCHandler(Actor_3)
	Actor_3H_dia = DialogPart()
	Actor_3H_dia:SetResetDialog(false)
	Actor_3H:SetRootDialog(Actor_3H_dia)
	Actor_3H:SetNpcName(-1)
	Actor_3H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_3H)

	Actor_4 = ActorObjectInfo(4)
	Actor_4:SetRenderType(3)
	Actor_4.DisplayDesc.ModelId = 0
	Actor_4.DisplayDesc.ModelName = "Sphero"
	Actor_4.DisplayDesc.Outfit = "Rebel"
	Actor_4.DisplayDesc.Weapon = "No"
	Actor_4.DisplayDesc.Mode = "Normal"
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
	Actor_4:SetModelState(1)
	Actor_4.PhysicDesc.Pos.X = 46
	Actor_4.PhysicDesc.Pos.Y = 0
	Actor_4.PhysicDesc.Pos.Z = 34.3438
	Actor_4.PhysicDesc.Pos.Rotation = 25
	Actor_4.PhysicDesc.Density = 1
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 1
	Actor_4.PhysicDesc.SizeY = 3
	Actor_4.PhysicDesc.SizeZ = 1
	Actor_4.PhysicDesc.Filename = ""
	Actor_4:SetPhysicalActorType(2)
	Actor_4:SetPhysicalShape(2)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 0
	Actor_4.ExtraInfo.NameColorG = 0
	Actor_4.ExtraInfo.NameColorB = 0
	Actor_4.ExtraInfo.Display = false
	Actor_4.LifeInfo.Display = false
	Actor_4H = NPCHandler(Actor_4)
	Actor_4H_dia = DialogPart()
	Actor_4H_dia:SetResetDialog(false)
	Actor_4H:SetRootDialog(Actor_4H_dia)
	Actor_4H:SetNpcName(-1)
	Actor_4H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_4H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(3)
	Actor_5.DisplayDesc.ModelId = 0
	Actor_5.DisplayDesc.ModelName = ""
	Actor_5.DisplayDesc.Outfit = ""
	Actor_5.DisplayDesc.Weapon = ""
	Actor_5.DisplayDesc.Mode = ""
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
	Actor_5.PhysicDesc.Pos.X = 45.2813
	Actor_5.PhysicDesc.Pos.Y = 4.85938
	Actor_5.PhysicDesc.Pos.Z = 53.7188
	Actor_5.PhysicDesc.Pos.Rotation = 225
	Actor_5.PhysicDesc.Density = 1
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = 1
	Actor_5.PhysicDesc.SizeY = 3
	Actor_5.PhysicDesc.SizeZ = 1
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
	Actor_6.DisplayDesc.ModelName = "Object"
	Actor_6.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_6.PhysicDesc.Pos.X = 0
	Actor_6.PhysicDesc.Pos.Y = -1
	Actor_6.PhysicDesc.Pos.Z = 0
	Actor_6.PhysicDesc.Pos.Rotation = 25
	Actor_6.PhysicDesc.Density = 1
	Actor_6.PhysicDesc.Collidable = true
	Actor_6.PhysicDesc.SizeX = 0.5
	Actor_6.PhysicDesc.SizeY = 2
	Actor_6.PhysicDesc.SizeZ = 0.6
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

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(3)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "Rabbibunny"
	Actor_7.DisplayDesc.Outfit = "Rebel"
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
	Actor_7.PhysicDesc.Pos.X = 55
	Actor_7.PhysicDesc.Pos.Y = 0
	Actor_7.PhysicDesc.Pos.Z = 38
	Actor_7.PhysicDesc.Pos.Rotation = 281
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 1
	Actor_7.PhysicDesc.SizeY = 5
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
	Actor_8.DisplayDesc.ModelName = "Rabbibunny"
	Actor_8.DisplayDesc.Outfit = "Rebel"
	Actor_8.DisplayDesc.Weapon = "No"
	Actor_8.DisplayDesc.Mode = "Normal"
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
	Actor_8.PhysicDesc.Pos.X = 53.4688
	Actor_8.PhysicDesc.Pos.Y = 0
	Actor_8.PhysicDesc.Pos.Z = 41
	Actor_8.PhysicDesc.Pos.Rotation = 281
	Actor_8.PhysicDesc.Density = 1
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 1
	Actor_8.PhysicDesc.SizeY = 5
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
	Actor_8H = NPCHandler(Actor_8)
	Actor_8H_dia = DialogPart()
	Actor_8H_dia:SetResetDialog(false)
	Actor_8H:SetRootDialog(Actor_8H_dia)
	Actor_8H:SetNpcName(-1)
	Actor_8H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_8H)

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
	Actor_9.PhysicDesc.Pos.X = 61.4375
	Actor_9.PhysicDesc.Pos.Y = 0
	Actor_9.PhysicDesc.Pos.Z = 37
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

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 3.5, 1, true)
	Trigger_1:SetPosition(38, 5, 31.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map059_1")
	Trigger_1_act1:SetSpawning(5)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "ContainerTri_2", true, false, false)
	Trigger_2 = ZoneActionTrigger(Trigger_2_info, 3.59376, 6, 3.53126, "Normal", "")
	Trigger_2:SetPosition(51.0156, 0, 52.7656)
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

end
