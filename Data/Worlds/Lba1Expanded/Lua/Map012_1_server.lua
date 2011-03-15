function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(57.5)
	Spawn_1:SetPosY(4.01)
	Spawn_1:SetPosZ(62)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(19)
	Spawn_2:SetPosY(4.01)
	Spawn_2:SetPosZ(62)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(2)
	Spawn_3:SetPosY(4.01)
	Spawn_3:SetPosZ(52)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(62)
	Spawn_4:SetPosY(4.01)
	Spawn_4:SetPosZ(39)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(57.5)
	Spawn_5:SetPosY(4.01)
	Spawn_5:SetPosZ(2)
	Spawn_5:SetName("spawning5")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(6)
	Spawn_6:SetPosY(14.01)
	Spawn_6:SetPosZ(6.5)
	Spawn_6:SetName("spawning6")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(56)
	Spawn_7:SetPosY(4.01)
	Spawn_7:SetPosZ(4)
	Spawn_7:SetName("spawning7")
	environment:AddSpawn(Spawn_7)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map12.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map12.phy"
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
	Actor_9:SetRenderType(1)
	Actor_9.DisplayDesc.ModelId = 0
	Actor_9.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite036.osgb"
	Actor_9.DisplayDesc.Outfit = ""
	Actor_9.DisplayDesc.Weapon = ""
	Actor_9.DisplayDesc.Mode = ""
	Actor_9.DisplayDesc.UseLight = true
	Actor_9.DisplayDesc.CastShadow = false
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
	Actor_9.PhysicDesc.Pos.X = 53.9
	Actor_9.PhysicDesc.Pos.Y = 8
	Actor_9.PhysicDesc.Pos.Z = 3
	Actor_9.PhysicDesc.Pos.Rotation = 0
	Actor_9.PhysicDesc.Density = 1
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 0
	Actor_9.PhysicDesc.SizeY = 0
	Actor_9.PhysicDesc.SizeZ = 0
	Actor_9.PhysicDesc.Filename = ""
	Actor_9:SetPhysicalActorType(2)
	Actor_9:SetPhysicalShape(2)
	Actor_9.ExtraInfo.Name = ""
	Actor_9.ExtraInfo.NameColorR = 0
	Actor_9.ExtraInfo.NameColorG = 0
	Actor_9.ExtraInfo.NameColorB = 0
	Actor_9.ExtraInfo.Display = false
	Actor_9.LifeInfo.Display = false
	Actor_9H = DoorHandler(Actor_9,0,0,2,0.005,false)
	Actor_9_Sc0 = ASPWaitForSignal(1)
	Actor_9H:AddScriptPart(Actor_9_Sc0)
	Actor_9_Sc1 = ASPGoTo(53.9,8,1,0.005)
	Actor_9H:AddScriptPart(Actor_9_Sc1)
	Actor_9_Sc2 = ASPWaitForSignal(2)
	Actor_9H:AddScriptPart(Actor_9_Sc2)
	Actor_9_Sc3 = ASPGoTo(53.9,8,3,0.005)
	Actor_9H:AddScriptPart(Actor_9_Sc3)
	environment:AddActorObject(Actor_9H)

	Actor_10 = ActorObjectInfo(10)
	Actor_10:SetRenderType(3)
	Actor_10.DisplayDesc.ModelId = 0
	Actor_10.DisplayDesc.ModelName = "Soldier"
	Actor_10.DisplayDesc.Outfit = "Grass"
	Actor_10.DisplayDesc.Weapon = "Machinegun"
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
	Actor_10.PhysicDesc.Pos.X = 30
	Actor_10.PhysicDesc.Pos.Y = 4
	Actor_10.PhysicDesc.Pos.Z = 35.0625
	Actor_10.PhysicDesc.Pos.Rotation = 45
	Actor_10.PhysicDesc.Density = 1
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 1
	Actor_10.PhysicDesc.SizeY = 3
	Actor_10.PhysicDesc.SizeZ = 2
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
	Actor_11.DisplayDesc.ModelName = "Tank"
	Actor_11.DisplayDesc.Outfit = "Grass"
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
	Actor_11.PhysicDesc.Pos.X = 2.0625
	Actor_11.PhysicDesc.Pos.Y = 4
	Actor_11.PhysicDesc.Pos.Z = 37.125
	Actor_11.PhysicDesc.Pos.Rotation = 165
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 2
	Actor_11.PhysicDesc.SizeY = 5
	Actor_11.PhysicDesc.SizeZ = 4
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
	Actor_12.DisplayDesc.ModelName = "RabbiClone"
	Actor_12.DisplayDesc.Outfit = "Yellow"
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
	Actor_12.PhysicDesc.Pos.X = 34.8125
	Actor_12.PhysicDesc.Pos.Y = 4
	Actor_12.PhysicDesc.Pos.Z = 32.7188
	Actor_12.PhysicDesc.Pos.Rotation = 119
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
	Actor_13.DisplayDesc.ModelName = "Soldier"
	Actor_13.DisplayDesc.Outfit = "Grass"
	Actor_13.DisplayDesc.Weapon = "rifle"
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
	Actor_13.PhysicDesc.Pos.X = 12.5
	Actor_13.PhysicDesc.Pos.Y = 2
	Actor_13.PhysicDesc.Pos.Z = 33.7813
	Actor_13.PhysicDesc.Pos.Rotation = 25
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 1
	Actor_13.PhysicDesc.SizeY = 5
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

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(3)
	Actor_14.DisplayDesc.ModelId = 0
	Actor_14.DisplayDesc.ModelName = "Soldier"
	Actor_14.DisplayDesc.Outfit = "Grass"
	Actor_14.DisplayDesc.Weapon = "rifle"
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
	Actor_14.PhysicDesc.Pos.X = 46.4688
	Actor_14.PhysicDesc.Pos.Y = 2
	Actor_14.PhysicDesc.Pos.Z = 33.2188
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
	Actor_15.DisplayDesc.ModelName = "GroboClone"
	Actor_15.DisplayDesc.Outfit = "Yellow"
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
	Actor_15.PhysicDesc.Pos.X = 29
	Actor_15.PhysicDesc.Pos.Y = 11
	Actor_15.PhysicDesc.Pos.Z = 12
	Actor_15.PhysicDesc.Pos.Rotation = 25
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 1.5
	Actor_15.PhysicDesc.SizeY = 5
	Actor_15.PhysicDesc.SizeZ = 1.5
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
	Actor_16.DisplayDesc.ModelName = "Soldier"
	Actor_16.DisplayDesc.Outfit = "Grass"
	Actor_16.DisplayDesc.Weapon = "rifle"
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
	Actor_16.PhysicDesc.Pos.X = 2
	Actor_16.PhysicDesc.Pos.Y = 4
	Actor_16.PhysicDesc.Pos.Z = 57.0313
	Actor_16.PhysicDesc.Pos.Rotation = 281
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 1
	Actor_16.PhysicDesc.SizeY = 5
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

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(3)
	Actor_17.DisplayDesc.ModelId = 0
	Actor_17.DisplayDesc.ModelName = "Soldier"
	Actor_17.DisplayDesc.Outfit = "Grass"
	Actor_17.DisplayDesc.Weapon = "rifle"
	Actor_17.DisplayDesc.Mode = "Normal"
	Actor_17.DisplayDesc.UseLight = true
	Actor_17.DisplayDesc.CastShadow = true
	Actor_17.DisplayDesc.ColorR = 1
	Actor_17.DisplayDesc.ColorG = 1
	Actor_17.DisplayDesc.ColorB = 1
	Actor_17.DisplayDesc.ColorA = 1
	Actor_17.DisplayDesc.TransX = 0
	Actor_17.DisplayDesc.TransY = 0
	Actor_17.DisplayDesc.TransZ = 0
	Actor_17.DisplayDesc.ScaleX = 1
	Actor_17.DisplayDesc.ScaleY = 1
	Actor_17.DisplayDesc.ScaleZ = 1
	Actor_17.DisplayDesc.RotX = 0
	Actor_17.DisplayDesc.RotY = 0
	Actor_17.DisplayDesc.RotZ = 0
	Actor_17:SetModelState(1)
	Actor_17.PhysicDesc.Pos.X = 2
	Actor_17.PhysicDesc.Pos.Y = 4
	Actor_17.PhysicDesc.Pos.Z = 58.2031
	Actor_17.PhysicDesc.Pos.Rotation = 281
	Actor_17.PhysicDesc.Density = 1
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 1
	Actor_17.PhysicDesc.SizeY = 5
	Actor_17.PhysicDesc.SizeZ = 1
	Actor_17.PhysicDesc.Filename = ""
	Actor_17:SetPhysicalActorType(2)
	Actor_17:SetPhysicalShape(2)
	Actor_17.ExtraInfo.Name = ""
	Actor_17.ExtraInfo.NameColorR = 0
	Actor_17.ExtraInfo.NameColorG = 0
	Actor_17.ExtraInfo.NameColorB = 0
	Actor_17.ExtraInfo.Display = false
	Actor_17.LifeInfo.Display = false
	Actor_17H = NPCHandler(Actor_17)
	Actor_17H_dia = DialogPart()
	Actor_17H_dia:SetResetDialog(false)
	Actor_17H:SetRootDialog(Actor_17H_dia)
	Actor_17H:SetNpcName(-1)
	Actor_17H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_17H)

	Actor_18 = ActorObjectInfo(18)
	Actor_18:SetRenderType(3)
	Actor_18.DisplayDesc.ModelId = 0
	Actor_18.DisplayDesc.ModelName = "Soldier"
	Actor_18.DisplayDesc.Outfit = "Grass"
	Actor_18.DisplayDesc.Weapon = "Machinegun"
	Actor_18.DisplayDesc.Mode = "Normal"
	Actor_18.DisplayDesc.UseLight = true
	Actor_18.DisplayDesc.CastShadow = true
	Actor_18.DisplayDesc.ColorR = 1
	Actor_18.DisplayDesc.ColorG = 1
	Actor_18.DisplayDesc.ColorB = 1
	Actor_18.DisplayDesc.ColorA = 1
	Actor_18.DisplayDesc.TransX = 0
	Actor_18.DisplayDesc.TransY = 0
	Actor_18.DisplayDesc.TransZ = 0
	Actor_18.DisplayDesc.ScaleX = 1
	Actor_18.DisplayDesc.ScaleY = 1
	Actor_18.DisplayDesc.ScaleZ = 1
	Actor_18.DisplayDesc.RotX = 0
	Actor_18.DisplayDesc.RotY = 0
	Actor_18.DisplayDesc.RotZ = 0
	Actor_18:SetModelState(1)
	Actor_18.PhysicDesc.Pos.X = 50.3438
	Actor_18.PhysicDesc.Pos.Y = 9
	Actor_18.PhysicDesc.Pos.Z = 6.59375
	Actor_18.PhysicDesc.Pos.Rotation = 25
	Actor_18.PhysicDesc.Density = 1
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 1
	Actor_18.PhysicDesc.SizeY = 3
	Actor_18.PhysicDesc.SizeZ = 2
	Actor_18.PhysicDesc.Filename = ""
	Actor_18:SetPhysicalActorType(2)
	Actor_18:SetPhysicalShape(2)
	Actor_18.ExtraInfo.Name = ""
	Actor_18.ExtraInfo.NameColorR = 0
	Actor_18.ExtraInfo.NameColorG = 0
	Actor_18.ExtraInfo.NameColorB = 0
	Actor_18.ExtraInfo.Display = false
	Actor_18.LifeInfo.Display = false
	Actor_18H = NPCHandler(Actor_18)
	Actor_18H_dia = DialogPart()
	Actor_18H_dia:SetResetDialog(false)
	Actor_18H:SetRootDialog(Actor_18H_dia)
	Actor_18H:SetNpcName(-1)
	Actor_18H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_18H)

	Actor_19 = ActorObjectInfo(19)
	Actor_19:SetRenderType(3)
	Actor_19.DisplayDesc.ModelId = 0
	Actor_19.DisplayDesc.ModelName = "RabbiClone"
	Actor_19.DisplayDesc.Outfit = "Yellow"
	Actor_19.DisplayDesc.Weapon = "No"
	Actor_19.DisplayDesc.Mode = "Normal"
	Actor_19.DisplayDesc.UseLight = true
	Actor_19.DisplayDesc.CastShadow = true
	Actor_19.DisplayDesc.ColorR = 1
	Actor_19.DisplayDesc.ColorG = 1
	Actor_19.DisplayDesc.ColorB = 1
	Actor_19.DisplayDesc.ColorA = 1
	Actor_19.DisplayDesc.TransX = 0
	Actor_19.DisplayDesc.TransY = 0
	Actor_19.DisplayDesc.TransZ = 0
	Actor_19.DisplayDesc.ScaleX = 1
	Actor_19.DisplayDesc.ScaleY = 1
	Actor_19.DisplayDesc.ScaleZ = 1
	Actor_19.DisplayDesc.RotX = 0
	Actor_19.DisplayDesc.RotY = 0
	Actor_19.DisplayDesc.RotZ = 0
	Actor_19:SetModelState(1)
	Actor_19.PhysicDesc.Pos.X = 46
	Actor_19.PhysicDesc.Pos.Y = 7
	Actor_19.PhysicDesc.Pos.Z = 16.2813
	Actor_19.PhysicDesc.Pos.Rotation = 281
	Actor_19.PhysicDesc.Density = 1
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = 1
	Actor_19.PhysicDesc.SizeY = 6
	Actor_19.PhysicDesc.SizeZ = 1
	Actor_19.PhysicDesc.Filename = ""
	Actor_19:SetPhysicalActorType(2)
	Actor_19:SetPhysicalShape(2)
	Actor_19.ExtraInfo.Name = ""
	Actor_19.ExtraInfo.NameColorR = 0
	Actor_19.ExtraInfo.NameColorG = 0
	Actor_19.ExtraInfo.NameColorB = 0
	Actor_19.ExtraInfo.Display = false
	Actor_19.LifeInfo.Display = false
	Actor_19H = NPCHandler(Actor_19)
	Actor_19H_dia = DialogPart()
	Actor_19H_dia:SetResetDialog(false)
	Actor_19H:SetRootDialog(Actor_19H_dia)
	Actor_19H:SetNpcName(-1)
	Actor_19H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_19H)

	Actor_20 = ActorObjectInfo(20)
	Actor_20:SetRenderType(3)
	Actor_20.DisplayDesc.ModelId = 0
	Actor_20.DisplayDesc.ModelName = "Soldier"
	Actor_20.DisplayDesc.Outfit = "Grass"
	Actor_20.DisplayDesc.Weapon = "rifle"
	Actor_20.DisplayDesc.Mode = "Normal"
	Actor_20.DisplayDesc.UseLight = true
	Actor_20.DisplayDesc.CastShadow = true
	Actor_20.DisplayDesc.ColorR = 1
	Actor_20.DisplayDesc.ColorG = 1
	Actor_20.DisplayDesc.ColorB = 1
	Actor_20.DisplayDesc.ColorA = 1
	Actor_20.DisplayDesc.TransX = 0
	Actor_20.DisplayDesc.TransY = 0
	Actor_20.DisplayDesc.TransZ = 0
	Actor_20.DisplayDesc.ScaleX = 1
	Actor_20.DisplayDesc.ScaleY = 1
	Actor_20.DisplayDesc.ScaleZ = 1
	Actor_20.DisplayDesc.RotX = 0
	Actor_20.DisplayDesc.RotY = 0
	Actor_20.DisplayDesc.RotZ = 0
	Actor_20:SetModelState(1)
	Actor_20.PhysicDesc.Pos.X = 39.5938
	Actor_20.PhysicDesc.Pos.Y = 11
	Actor_20.PhysicDesc.Pos.Z = 10.4375
	Actor_20.PhysicDesc.Pos.Rotation = 95
	Actor_20.PhysicDesc.Density = 1
	Actor_20.PhysicDesc.Collidable = true
	Actor_20.PhysicDesc.SizeX = 1
	Actor_20.PhysicDesc.SizeY = 5
	Actor_20.PhysicDesc.SizeZ = 1
	Actor_20.PhysicDesc.Filename = ""
	Actor_20:SetPhysicalActorType(2)
	Actor_20:SetPhysicalShape(2)
	Actor_20.ExtraInfo.Name = ""
	Actor_20.ExtraInfo.NameColorR = 0
	Actor_20.ExtraInfo.NameColorG = 0
	Actor_20.ExtraInfo.NameColorB = 0
	Actor_20.ExtraInfo.Display = false
	Actor_20.LifeInfo.Display = false
	Actor_20H = NPCHandler(Actor_20)
	Actor_20H_dia = DialogPart()
	Actor_20H_dia:SetResetDialog(false)
	Actor_20H:SetRootDialog(Actor_20H_dia)
	Actor_20H:SetNpcName(-1)
	Actor_20H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_20H)

	Actor_21 = ActorObjectInfo(21)
	Actor_21:SetRenderType(3)
	Actor_21.DisplayDesc.ModelId = 0
	Actor_21.DisplayDesc.ModelName = "GroboClone"
	Actor_21.DisplayDesc.Outfit = "Yellow"
	Actor_21.DisplayDesc.Weapon = "No"
	Actor_21.DisplayDesc.Mode = "Normal"
	Actor_21.DisplayDesc.UseLight = true
	Actor_21.DisplayDesc.CastShadow = true
	Actor_21.DisplayDesc.ColorR = 1
	Actor_21.DisplayDesc.ColorG = 1
	Actor_21.DisplayDesc.ColorB = 1
	Actor_21.DisplayDesc.ColorA = 1
	Actor_21.DisplayDesc.TransX = 0
	Actor_21.DisplayDesc.TransY = 0
	Actor_21.DisplayDesc.TransZ = 0
	Actor_21.DisplayDesc.ScaleX = 1
	Actor_21.DisplayDesc.ScaleY = 1
	Actor_21.DisplayDesc.ScaleZ = 1
	Actor_21.DisplayDesc.RotX = 0
	Actor_21.DisplayDesc.RotY = 0
	Actor_21.DisplayDesc.RotZ = 0
	Actor_21:SetModelState(1)
	Actor_21.PhysicDesc.Pos.X = 24
	Actor_21.PhysicDesc.Pos.Y = 11
	Actor_21.PhysicDesc.Pos.Z = 4.5
	Actor_21.PhysicDesc.Pos.Rotation = 25
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 1.5
	Actor_21.PhysicDesc.SizeY = 5
	Actor_21.PhysicDesc.SizeZ = 1.5
	Actor_21.PhysicDesc.Filename = ""
	Actor_21:SetPhysicalActorType(2)
	Actor_21:SetPhysicalShape(2)
	Actor_21.ExtraInfo.Name = ""
	Actor_21.ExtraInfo.NameColorR = 0
	Actor_21.ExtraInfo.NameColorG = 0
	Actor_21.ExtraInfo.NameColorB = 0
	Actor_21.ExtraInfo.Display = false
	Actor_21.LifeInfo.Display = false
	Actor_21H = NPCHandler(Actor_21)
	Actor_21H_dia = DialogPart()
	Actor_21H_dia:SetResetDialog(false)
	Actor_21H:SetRootDialog(Actor_21H_dia)
	Actor_21H:SetNpcName(-1)
	Actor_21H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_21H)

	Actor_22 = ActorObjectInfo(22)
	Actor_22:SetRenderType(3)
	Actor_22.DisplayDesc.ModelId = 0
	Actor_22.DisplayDesc.ModelName = ""
	Actor_22.DisplayDesc.Outfit = ""
	Actor_22.DisplayDesc.Weapon = ""
	Actor_22.DisplayDesc.Mode = ""
	Actor_22.DisplayDesc.UseLight = true
	Actor_22.DisplayDesc.CastShadow = true
	Actor_22.DisplayDesc.ColorR = 1
	Actor_22.DisplayDesc.ColorG = 1
	Actor_22.DisplayDesc.ColorB = 1
	Actor_22.DisplayDesc.ColorA = 1
	Actor_22.DisplayDesc.TransX = 0
	Actor_22.DisplayDesc.TransY = 0
	Actor_22.DisplayDesc.TransZ = 0
	Actor_22.DisplayDesc.ScaleX = 1
	Actor_22.DisplayDesc.ScaleY = 1
	Actor_22.DisplayDesc.ScaleZ = 1
	Actor_22.DisplayDesc.RotX = 0
	Actor_22.DisplayDesc.RotY = 0
	Actor_22.DisplayDesc.RotZ = 0
	Actor_22:SetModelState(1)
	Actor_22.PhysicDesc.Pos.X = 32.2813
	Actor_22.PhysicDesc.Pos.Y = 7.5
	Actor_22.PhysicDesc.Pos.Z = 23.3125
	Actor_22.PhysicDesc.Pos.Rotation = 25
	Actor_22.PhysicDesc.Density = 1
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 1.5
	Actor_22.PhysicDesc.SizeY = 5
	Actor_22.PhysicDesc.SizeZ = 1.5
	Actor_22.PhysicDesc.Filename = ""
	Actor_22:SetPhysicalActorType(2)
	Actor_22:SetPhysicalShape(2)
	Actor_22.ExtraInfo.Name = ""
	Actor_22.ExtraInfo.NameColorR = 0
	Actor_22.ExtraInfo.NameColorG = 0
	Actor_22.ExtraInfo.NameColorB = 0
	Actor_22.ExtraInfo.Display = false
	Actor_22.LifeInfo.Display = false
	Actor_22H = NPCHandler(Actor_22)
	Actor_22H_dia = DialogPart()
	Actor_22H_dia:SetResetDialog(false)
	Actor_22H:SetRootDialog(Actor_22H_dia)
	Actor_22H:SetNpcName(-1)
	Actor_22H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_22H)

	Actor_23 = ActorObjectInfo(23)
	Actor_23:SetRenderType(3)
	Actor_23.DisplayDesc.ModelId = 0
	Actor_23.DisplayDesc.ModelName = "Rabbibunny"
	Actor_23.DisplayDesc.Outfit = "Orange"
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
	Actor_23.PhysicDesc.Pos.X = 49.4688
	Actor_23.PhysicDesc.Pos.Y = 0
	Actor_23.PhysicDesc.Pos.Z = 7.78125
	Actor_23.PhysicDesc.Pos.Rotation = 25
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
	Actor_23.ExtraInfo.Display = false
	Actor_23.LifeInfo.Display = false
	Actor_23H = NPCHandler(Actor_23)
	Actor_23H_dia = DialogPart()
	Actor_23H_dia:SetResetDialog(false)
	Actor_23H:SetRootDialog(Actor_23H_dia)
	Actor_23H:SetNpcName(-1)
	Actor_23H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_23H)

	Actor_24 = ActorObjectInfo(24)
	Actor_24:SetRenderType(3)
	Actor_24.DisplayDesc.ModelId = 0
	Actor_24.DisplayDesc.ModelName = "Grobo"
	Actor_24.DisplayDesc.Outfit = "Sailor"
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
	Actor_24.PhysicDesc.Pos.X = 5.5625
	Actor_24.PhysicDesc.Pos.Y = 2
	Actor_24.PhysicDesc.Pos.Z = 31.5
	Actor_24.PhysicDesc.Pos.Rotation = 250
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
	Actor_25.DisplayDesc.ModelName = "Object"
	Actor_25.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_25.PhysicDesc.Pos.X = 0
	Actor_25.PhysicDesc.Pos.Y = -1
	Actor_25.PhysicDesc.Pos.Z = 0
	Actor_25.PhysicDesc.Pos.Rotation = 25
	Actor_25.PhysicDesc.Density = 1
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 0.5
	Actor_25.PhysicDesc.SizeY = 2
	Actor_25.PhysicDesc.SizeZ = 0.6
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
	Actor_26.DisplayDesc.ModelName = "GroboClone"
	Actor_26.DisplayDesc.Outfit = "SuperGro"
	Actor_26.DisplayDesc.Weapon = "No"
	Actor_26.DisplayDesc.Mode = "Normal"
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
	Actor_26.PhysicDesc.Pos.X = 10.1563
	Actor_26.PhysicDesc.Pos.Y = 16
	Actor_26.PhysicDesc.Pos.Z = 1.0625
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
	Actor_27.DisplayDesc.ModelName = "RabbiClone"
	Actor_27.DisplayDesc.Outfit = "Green"
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
	Actor_27.PhysicDesc.Pos.X = 6
	Actor_27.PhysicDesc.Pos.Y = 14
	Actor_27.PhysicDesc.Pos.Z = 6
	Actor_27.PhysicDesc.Pos.Rotation = 281
	Actor_27.PhysicDesc.Density = 1
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 1
	Actor_27.PhysicDesc.SizeY = 6
	Actor_27.PhysicDesc.SizeZ = 1
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
	Trigger_1 = ZoneTrigger(Trigger_1_info, 7, 4.5, 1, true)
	Trigger_1:SetPosition(57.5, 4, 63.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map011_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit19", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 7, 6, 1, true)
	Trigger_2:SetPosition(57.5, 4, 0.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map018_1")
	Trigger_2_act1:SetSpawning(2)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 3, 8, true)
	Trigger_3:SetPosition(0.5, 4, 52)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map013_1")
	Trigger_3_act1:SetSpawning(2)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit23", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 3.5, 5, true)
	Trigger_4:SetPosition(4.5, 14, 6.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map105_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit3", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 3, 2, true)
	Trigger_5:SetPosition(53.5, 6, 3)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map105_1")
	Trigger_5_act1:SetSpawning(2)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit8", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 1, 4, 6, true)
	Trigger_6:SetPosition(63.5, 4, 39)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map017_1")
	Trigger_6_act1:SetSpawning(1)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit9", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 4, 4, 1, true)
	Trigger_7:SetPosition(19, 4, 63.5)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map011_1")
	Trigger_7_act1:SetSpawning(3)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "ContainerTri_8", true, false, false)
	Trigger_8 = ZoneActionTrigger(Trigger_8_info, 1.62305, 4.99609, 1.5918, "Normal", "")
	Trigger_8:SetPosition(34.8115, 4, 22.7959)
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

	Trigger_9_info = TriggerInfo(9, "TextTri_9", true, false, false)
	Trigger_9 = ActivationTrigger(Trigger_9_info, 2, "Normal", "")
	Trigger_9:SetPosition(37.999, 4, 48.999)
	Trigger_9_act1 = DisplayTextAction()
	Trigger_9_act1:SetTextId(331)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "TextTri_10", true, false, false)
	Trigger_10 = ActivationTrigger(Trigger_10_info, 2, "Normal", "")
	Trigger_10:SetPosition(24.999, 4, 48.999)
	Trigger_10_act1 = DisplayTextAction()
	Trigger_10_act1:SetTextId(331)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "LadderTri_11", true, false, false)
	Trigger_11 = ActivationTrigger(Trigger_11_info, 1.66667, "Normal", "")
	Trigger_11:SetPosition(41.7705, 0, 31)
	Trigger_11_act1 = ClientScriptAction()
	Trigger_11_act1_cs = GoUpLadderScript()
	Trigger_11_act1_cs:SetLadderPositionX(41.7705)
	Trigger_11_act1_cs:SetLadderPositionY(0)
	Trigger_11_act1_cs:SetLadderPositionZ(31)
	Trigger_11_act1_cs:SetLadderHeight(4)
	Trigger_11_act1_cs:SetLadderDirection(180)
	Trigger_11_act1:SetScript(Trigger_11_act1_cs)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "LadderTri_12", true, false, false)
	Trigger_12 = ActivationTrigger(Trigger_12_info, 1.66667, "Normal", "")
	Trigger_12:SetPosition(21.8652, 0, 30.9688)
	Trigger_12_act1 = ClientScriptAction()
	Trigger_12_act1_cs = GoUpLadderScript()
	Trigger_12_act1_cs:SetLadderPositionX(21.8652)
	Trigger_12_act1_cs:SetLadderPositionY(0)
	Trigger_12_act1_cs:SetLadderPositionZ(30.9688)
	Trigger_12_act1_cs:SetLadderHeight(4)
	Trigger_12_act1_cs:SetLadderDirection(180)
	Trigger_12_act1:SetScript(Trigger_12_act1_cs)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "LadderTri_13", true, false, false)
	Trigger_13 = ActivationTrigger(Trigger_13_info, 2, "Normal", "")
	Trigger_13:SetPosition(54, 4, 3)
	Trigger_13_act1 = ClientScriptAction()
	Trigger_13_act1_cs = GoUpLadderScript()
	Trigger_13_act1_cs:SetLadderPositionX(54)
	Trigger_13_act1_cs:SetLadderPositionY(4)
	Trigger_13_act1_cs:SetLadderPositionZ(3)
	Trigger_13_act1_cs:SetLadderHeight(4)
	Trigger_13_act1_cs:SetLadderDirection(270)
	Trigger_13_act1:SetScript(Trigger_13_act1_cs)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "DoorTri_14", true, false, false)
	Trigger_14 = ZoneTrigger(Trigger_14_info, 0, 0, 0, false)
	Trigger_14:SetPosition(53.9, 8, 3)
	Trigger_14:SetStayUpdateFrequency(-1)
	Trigger_14_act1 = OpenDoorAction()
	Trigger_14_act1:SetActorId(9)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14_act2 = CloseDoorAction()
	Trigger_14_act2:SetActorId(9)
	Trigger_14:SetAction2(Trigger_14_act2)
	environment:AddTrigger(Trigger_14)

end
