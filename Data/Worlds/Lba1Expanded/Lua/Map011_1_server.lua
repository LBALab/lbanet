function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(41)
	Spawn_1:SetPosY(4.01)
	Spawn_1:SetPosZ(37)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(57.5)
	Spawn_2:SetPosY(4.01)
	Spawn_2:SetPosZ(2)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(19)
	Spawn_3:SetPosY(4.01)
	Spawn_3:SetPosZ(5)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(8)
	Spawn_4:SetPosY(12.01)
	Spawn_4:SetPosZ(3.5)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(12.5)
	Spawn_5:SetPosY(4.01)
	Spawn_5:SetPosZ(15)
	Spawn_5:SetName("spawning5")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(11)
	Spawn_6:SetPosY(4.01)
	Spawn_6:SetPosZ(38.5)
	Spawn_6:SetName("spawning6")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(6)
	Spawn_7:SetPosY(6.01)
	Spawn_7:SetPosZ(49)
	Spawn_7:SetName("spawning7")
	environment:AddSpawn(Spawn_7)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map11.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map11.phy"
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

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(3)
	Actor_25.DisplayDesc.ModelId = 0
	Actor_25.DisplayDesc.ModelName = "Boat"
	Actor_25.DisplayDesc.Outfit = "Ferry"
	Actor_25.DisplayDesc.Weapon = "No"
	Actor_25.DisplayDesc.Mode = "Normal"
	Actor_25.DisplayDesc.UseLight = true
	Actor_25.DisplayDesc.CastShadow = false
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
	Actor_25.PhysicDesc.Pos.X = 37
	Actor_25.PhysicDesc.Pos.Y = 0
	Actor_25.PhysicDesc.Pos.Z = 33
	Actor_25.PhysicDesc.Pos.Rotation = 0
	Actor_25.PhysicDesc.Density = 1
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 5
	Actor_25.PhysicDesc.SizeY = 10
	Actor_25.PhysicDesc.SizeZ = 15
	Actor_25.PhysicDesc.Filename = ""
	Actor_25:SetPhysicalActorType(2)
	Actor_25:SetPhysicalShape(2)
	Actor_25.ExtraInfo.Name = ""
	Actor_25.ExtraInfo.NameColorR = 0
	Actor_25.ExtraInfo.NameColorG = 0
	Actor_25.ExtraInfo.NameColorB = 0
	Actor_25.ExtraInfo.Display = false
	Actor_25.LifeInfo.Display = false
	Actor_25H = ActorHandler(Actor_25)
	Actor_25_Sc0 = ASPWaitForSignal(5)
	Actor_25H:AddScriptPart(Actor_25_Sc0)
	Actor_25_Sc1 = ASPGoTo(31,0,33,0.0012)
	Actor_25H:AddScriptPart(Actor_25_Sc1)
	Actor_25_Sc2 = ASPGoTo(31,0,55,0.0025)
	Actor_25H:AddScriptPart(Actor_25_Sc2)
	Actor_25_Sc3 = ASPSendSignal(6,0)
	Actor_25H:AddScriptPart(Actor_25_Sc3)
	environment:AddActorObject(Actor_25H)

	Actor_26 = ActorObjectInfo(26)
	Actor_26:SetRenderType(3)
	Actor_26.DisplayDesc.ModelId = 0
	Actor_26.DisplayDesc.ModelName = "Rabbibunny"
	Actor_26.DisplayDesc.Outfit = "FerryOwner"
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
	Actor_26.PhysicDesc.Pos.X = 41.2813
	Actor_26.PhysicDesc.Pos.Y = 4
	Actor_26.PhysicDesc.Pos.Z = 39.7813
	Actor_26.PhysicDesc.Pos.Rotation = 281
	Actor_26.PhysicDesc.Density = 1
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 1
	Actor_26.PhysicDesc.SizeY = 5
	Actor_26.PhysicDesc.SizeZ = 1
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
	Actor_27.DisplayDesc.ModelName = "Soldier"
	Actor_27.DisplayDesc.Outfit = "Grass"
	Actor_27.DisplayDesc.Weapon = "rifle"
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
	Actor_27.PhysicDesc.Pos.X = 43
	Actor_27.PhysicDesc.Pos.Y = 4
	Actor_27.PhysicDesc.Pos.Z = 53
	Actor_27.PhysicDesc.Pos.Rotation = 25
	Actor_27.PhysicDesc.Density = 1
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 1
	Actor_27.PhysicDesc.SizeY = 5
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

	Actor_28 = ActorObjectInfo(28)
	Actor_28:SetRenderType(3)
	Actor_28.DisplayDesc.ModelId = 0
	Actor_28.DisplayDesc.ModelName = "Soldier"
	Actor_28.DisplayDesc.Outfit = "Grass"
	Actor_28.DisplayDesc.Weapon = "rifle"
	Actor_28.DisplayDesc.Mode = "Normal"
	Actor_28.DisplayDesc.UseLight = true
	Actor_28.DisplayDesc.CastShadow = true
	Actor_28.DisplayDesc.ColorR = 1
	Actor_28.DisplayDesc.ColorG = 1
	Actor_28.DisplayDesc.ColorB = 1
	Actor_28.DisplayDesc.ColorA = 1
	Actor_28.DisplayDesc.TransX = 0
	Actor_28.DisplayDesc.TransY = 0
	Actor_28.DisplayDesc.TransZ = 0
	Actor_28.DisplayDesc.ScaleX = 1
	Actor_28.DisplayDesc.ScaleY = 1
	Actor_28.DisplayDesc.ScaleZ = 1
	Actor_28.DisplayDesc.RotX = 0
	Actor_28.DisplayDesc.RotY = 0
	Actor_28.DisplayDesc.RotZ = 0
	Actor_28:SetModelState(1)
	Actor_28.PhysicDesc.Pos.X = 55.25
	Actor_28.PhysicDesc.Pos.Y = 4
	Actor_28.PhysicDesc.Pos.Z = 15.75
	Actor_28.PhysicDesc.Pos.Rotation = 121
	Actor_28.PhysicDesc.Density = 1
	Actor_28.PhysicDesc.Collidable = true
	Actor_28.PhysicDesc.SizeX = 1
	Actor_28.PhysicDesc.SizeY = 5
	Actor_28.PhysicDesc.SizeZ = 1
	Actor_28.PhysicDesc.Filename = ""
	Actor_28:SetPhysicalActorType(2)
	Actor_28:SetPhysicalShape(2)
	Actor_28.ExtraInfo.Name = ""
	Actor_28.ExtraInfo.NameColorR = 0
	Actor_28.ExtraInfo.NameColorG = 0
	Actor_28.ExtraInfo.NameColorB = 0
	Actor_28.ExtraInfo.Display = false
	Actor_28.LifeInfo.Display = false
	Actor_28H = NPCHandler(Actor_28)
	Actor_28H_dia = DialogPart()
	Actor_28H_dia:SetResetDialog(false)
	Actor_28H:SetRootDialog(Actor_28H_dia)
	Actor_28H:SetNpcName(-1)
	Actor_28H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_28H)

	Actor_29 = ActorObjectInfo(29)
	Actor_29:SetRenderType(3)
	Actor_29.DisplayDesc.ModelId = 0
	Actor_29.DisplayDesc.ModelName = "GroboClone"
	Actor_29.DisplayDesc.Outfit = "Yellow"
	Actor_29.DisplayDesc.Weapon = "No"
	Actor_29.DisplayDesc.Mode = "Normal"
	Actor_29.DisplayDesc.UseLight = true
	Actor_29.DisplayDesc.CastShadow = true
	Actor_29.DisplayDesc.ColorR = 1
	Actor_29.DisplayDesc.ColorG = 1
	Actor_29.DisplayDesc.ColorB = 1
	Actor_29.DisplayDesc.ColorA = 1
	Actor_29.DisplayDesc.TransX = 0
	Actor_29.DisplayDesc.TransY = 0
	Actor_29.DisplayDesc.TransZ = 0
	Actor_29.DisplayDesc.ScaleX = 1
	Actor_29.DisplayDesc.ScaleY = 1
	Actor_29.DisplayDesc.ScaleZ = 1
	Actor_29.DisplayDesc.RotX = 0
	Actor_29.DisplayDesc.RotY = 0
	Actor_29.DisplayDesc.RotZ = 0
	Actor_29:SetModelState(1)
	Actor_29.PhysicDesc.Pos.X = 50.75
	Actor_29.PhysicDesc.Pos.Y = 4
	Actor_29.PhysicDesc.Pos.Z = 20.0313
	Actor_29.PhysicDesc.Pos.Rotation = 25
	Actor_29.PhysicDesc.Density = 1
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 1.5
	Actor_29.PhysicDesc.SizeY = 5
	Actor_29.PhysicDesc.SizeZ = 1.5
	Actor_29.PhysicDesc.Filename = ""
	Actor_29:SetPhysicalActorType(2)
	Actor_29:SetPhysicalShape(2)
	Actor_29.ExtraInfo.Name = ""
	Actor_29.ExtraInfo.NameColorR = 0
	Actor_29.ExtraInfo.NameColorG = 0
	Actor_29.ExtraInfo.NameColorB = 0
	Actor_29.ExtraInfo.Display = false
	Actor_29.LifeInfo.Display = false
	Actor_29H = NPCHandler(Actor_29)
	Actor_29H_dia = DialogPart()
	Actor_29H_dia:SetResetDialog(false)
	Actor_29H:SetRootDialog(Actor_29H_dia)
	Actor_29H:SetNpcName(-1)
	Actor_29H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_29H)

	Actor_30 = ActorObjectInfo(30)
	Actor_30:SetRenderType(3)
	Actor_30.DisplayDesc.ModelId = 0
	Actor_30.DisplayDesc.ModelName = "Soldier"
	Actor_30.DisplayDesc.Outfit = "Grass"
	Actor_30.DisplayDesc.Weapon = "rifle"
	Actor_30.DisplayDesc.Mode = "Normal"
	Actor_30.DisplayDesc.UseLight = true
	Actor_30.DisplayDesc.CastShadow = true
	Actor_30.DisplayDesc.ColorR = 1
	Actor_30.DisplayDesc.ColorG = 1
	Actor_30.DisplayDesc.ColorB = 1
	Actor_30.DisplayDesc.ColorA = 1
	Actor_30.DisplayDesc.TransX = 0
	Actor_30.DisplayDesc.TransY = 0
	Actor_30.DisplayDesc.TransZ = 0
	Actor_30.DisplayDesc.ScaleX = 1
	Actor_30.DisplayDesc.ScaleY = 1
	Actor_30.DisplayDesc.ScaleZ = 1
	Actor_30.DisplayDesc.RotX = 0
	Actor_30.DisplayDesc.RotY = 0
	Actor_30.DisplayDesc.RotZ = 0
	Actor_30:SetModelState(1)
	Actor_30.PhysicDesc.Pos.X = 19
	Actor_30.PhysicDesc.Pos.Y = 4
	Actor_30.PhysicDesc.Pos.Z = 10.9688
	Actor_30.PhysicDesc.Pos.Rotation = 341
	Actor_30.PhysicDesc.Density = 1
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 1
	Actor_30.PhysicDesc.SizeY = 5
	Actor_30.PhysicDesc.SizeZ = 1
	Actor_30.PhysicDesc.Filename = ""
	Actor_30:SetPhysicalActorType(2)
	Actor_30:SetPhysicalShape(2)
	Actor_30.ExtraInfo.Name = ""
	Actor_30.ExtraInfo.NameColorR = 0
	Actor_30.ExtraInfo.NameColorG = 0
	Actor_30.ExtraInfo.NameColorB = 0
	Actor_30.ExtraInfo.Display = false
	Actor_30.LifeInfo.Display = false
	Actor_30H = NPCHandler(Actor_30)
	Actor_30H_dia = DialogPart()
	Actor_30H_dia:SetResetDialog(false)
	Actor_30H:SetRootDialog(Actor_30H_dia)
	Actor_30H:SetNpcName(-1)
	Actor_30H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_30H)

	Actor_31 = ActorObjectInfo(31)
	Actor_31:SetRenderType(3)
	Actor_31.DisplayDesc.ModelId = 0
	Actor_31.DisplayDesc.ModelName = "RabbiClone"
	Actor_31.DisplayDesc.Outfit = "Yellow"
	Actor_31.DisplayDesc.Weapon = "No"
	Actor_31.DisplayDesc.Mode = "Normal"
	Actor_31.DisplayDesc.UseLight = true
	Actor_31.DisplayDesc.CastShadow = true
	Actor_31.DisplayDesc.ColorR = 1
	Actor_31.DisplayDesc.ColorG = 1
	Actor_31.DisplayDesc.ColorB = 1
	Actor_31.DisplayDesc.ColorA = 1
	Actor_31.DisplayDesc.TransX = 0
	Actor_31.DisplayDesc.TransY = 0
	Actor_31.DisplayDesc.TransZ = 0
	Actor_31.DisplayDesc.ScaleX = 1
	Actor_31.DisplayDesc.ScaleY = 1
	Actor_31.DisplayDesc.ScaleZ = 1
	Actor_31.DisplayDesc.RotX = 0
	Actor_31.DisplayDesc.RotY = 0
	Actor_31.DisplayDesc.RotZ = 0
	Actor_31:SetModelState(1)
	Actor_31.PhysicDesc.Pos.X = 56.9375
	Actor_31.PhysicDesc.Pos.Y = 4
	Actor_31.PhysicDesc.Pos.Z = 5.25
	Actor_31.PhysicDesc.Pos.Rotation = 182
	Actor_31.PhysicDesc.Density = 1
	Actor_31.PhysicDesc.Collidable = true
	Actor_31.PhysicDesc.SizeX = 1
	Actor_31.PhysicDesc.SizeY = 6
	Actor_31.PhysicDesc.SizeZ = 1
	Actor_31.PhysicDesc.Filename = ""
	Actor_31:SetPhysicalActorType(2)
	Actor_31:SetPhysicalShape(2)
	Actor_31.ExtraInfo.Name = ""
	Actor_31.ExtraInfo.NameColorR = 0
	Actor_31.ExtraInfo.NameColorG = 0
	Actor_31.ExtraInfo.NameColorB = 0
	Actor_31.ExtraInfo.Display = false
	Actor_31.LifeInfo.Display = false
	Actor_31H = NPCHandler(Actor_31)
	Actor_31H_dia = DialogPart()
	Actor_31H_dia:SetResetDialog(false)
	Actor_31H:SetRootDialog(Actor_31H_dia)
	Actor_31H:SetNpcName(-1)
	Actor_31H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_31H)

	Actor_32 = ActorObjectInfo(32)
	Actor_32:SetRenderType(3)
	Actor_32.DisplayDesc.ModelId = 0
	Actor_32.DisplayDesc.ModelName = "Quetch"
	Actor_32.DisplayDesc.Outfit = "Salesman"
	Actor_32.DisplayDesc.Weapon = "No"
	Actor_32.DisplayDesc.Mode = "Normal"
	Actor_32.DisplayDesc.UseLight = true
	Actor_32.DisplayDesc.CastShadow = true
	Actor_32.DisplayDesc.ColorR = 1
	Actor_32.DisplayDesc.ColorG = 1
	Actor_32.DisplayDesc.ColorB = 1
	Actor_32.DisplayDesc.ColorA = 1
	Actor_32.DisplayDesc.TransX = 0
	Actor_32.DisplayDesc.TransY = 0
	Actor_32.DisplayDesc.TransZ = 0
	Actor_32.DisplayDesc.ScaleX = 1
	Actor_32.DisplayDesc.ScaleY = 1
	Actor_32.DisplayDesc.ScaleZ = 1
	Actor_32.DisplayDesc.RotX = 0
	Actor_32.DisplayDesc.RotY = 0
	Actor_32.DisplayDesc.RotZ = 0
	Actor_32:SetModelState(1)
	Actor_32.PhysicDesc.Pos.X = 44.625
	Actor_32.PhysicDesc.Pos.Y = 4
	Actor_32.PhysicDesc.Pos.Z = 43
	Actor_32.PhysicDesc.Pos.Rotation = 177
	Actor_32.PhysicDesc.Density = 1
	Actor_32.PhysicDesc.Collidable = true
	Actor_32.PhysicDesc.SizeX = 1
	Actor_32.PhysicDesc.SizeY = 5
	Actor_32.PhysicDesc.SizeZ = 1
	Actor_32.PhysicDesc.Filename = ""
	Actor_32:SetPhysicalActorType(2)
	Actor_32:SetPhysicalShape(2)
	Actor_32.ExtraInfo.Name = ""
	Actor_32.ExtraInfo.NameColorR = 0
	Actor_32.ExtraInfo.NameColorG = 0
	Actor_32.ExtraInfo.NameColorB = 0
	Actor_32.ExtraInfo.Display = false
	Actor_32.LifeInfo.Display = false
	Actor_32H = NPCHandler(Actor_32)
	Actor_32H_dia = DialogPart()
	Actor_32H_dia:SetResetDialog(false)
	Actor_32H:SetRootDialog(Actor_32H_dia)
	Actor_32H:SetNpcName(-1)
	Actor_32H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_32H)

	Actor_33 = ActorObjectInfo(33)
	Actor_33:SetRenderType(3)
	Actor_33.DisplayDesc.ModelId = 0
	Actor_33.DisplayDesc.ModelName = "Rabbibunny"
	Actor_33.DisplayDesc.Outfit = "Orange"
	Actor_33.DisplayDesc.Weapon = "No"
	Actor_33.DisplayDesc.Mode = "Normal"
	Actor_33.DisplayDesc.UseLight = true
	Actor_33.DisplayDesc.CastShadow = true
	Actor_33.DisplayDesc.ColorR = 1
	Actor_33.DisplayDesc.ColorG = 1
	Actor_33.DisplayDesc.ColorB = 1
	Actor_33.DisplayDesc.ColorA = 1
	Actor_33.DisplayDesc.TransX = 0
	Actor_33.DisplayDesc.TransY = 0
	Actor_33.DisplayDesc.TransZ = 0
	Actor_33.DisplayDesc.ScaleX = 1
	Actor_33.DisplayDesc.ScaleY = 1
	Actor_33.DisplayDesc.ScaleZ = 1
	Actor_33.DisplayDesc.RotX = 0
	Actor_33.DisplayDesc.RotY = 0
	Actor_33.DisplayDesc.RotZ = 0
	Actor_33:SetModelState(1)
	Actor_33.PhysicDesc.Pos.X = 45
	Actor_33.PhysicDesc.Pos.Y = 4
	Actor_33.PhysicDesc.Pos.Z = 28.875
	Actor_33.PhysicDesc.Pos.Rotation = 178
	Actor_33.PhysicDesc.Density = 1
	Actor_33.PhysicDesc.Collidable = true
	Actor_33.PhysicDesc.SizeX = 1
	Actor_33.PhysicDesc.SizeY = 5
	Actor_33.PhysicDesc.SizeZ = 1
	Actor_33.PhysicDesc.Filename = ""
	Actor_33:SetPhysicalActorType(2)
	Actor_33:SetPhysicalShape(2)
	Actor_33.ExtraInfo.Name = ""
	Actor_33.ExtraInfo.NameColorR = 0
	Actor_33.ExtraInfo.NameColorG = 0
	Actor_33.ExtraInfo.NameColorB = 0
	Actor_33.ExtraInfo.Display = false
	Actor_33.LifeInfo.Display = false
	Actor_33H = NPCHandler(Actor_33)
	Actor_33H_dia = DialogPart()
	Actor_33H_dia:SetResetDialog(false)
	Actor_33H:SetRootDialog(Actor_33H_dia)
	Actor_33H:SetNpcName(-1)
	Actor_33H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_33H)

	Actor_34 = ActorObjectInfo(34)
	Actor_34:SetRenderType(3)
	Actor_34.DisplayDesc.ModelId = 0
	Actor_34.DisplayDesc.ModelName = "Grobo"
	Actor_34.DisplayDesc.Outfit = "Sailor"
	Actor_34.DisplayDesc.Weapon = "No"
	Actor_34.DisplayDesc.Mode = "Normal"
	Actor_34.DisplayDesc.UseLight = true
	Actor_34.DisplayDesc.CastShadow = true
	Actor_34.DisplayDesc.ColorR = 1
	Actor_34.DisplayDesc.ColorG = 1
	Actor_34.DisplayDesc.ColorB = 1
	Actor_34.DisplayDesc.ColorA = 1
	Actor_34.DisplayDesc.TransX = 0
	Actor_34.DisplayDesc.TransY = 0
	Actor_34.DisplayDesc.TransZ = 0
	Actor_34.DisplayDesc.ScaleX = 1
	Actor_34.DisplayDesc.ScaleY = 1
	Actor_34.DisplayDesc.ScaleZ = 1
	Actor_34.DisplayDesc.RotX = 0
	Actor_34.DisplayDesc.RotY = 0
	Actor_34.DisplayDesc.RotZ = 0
	Actor_34:SetModelState(1)
	Actor_34.PhysicDesc.Pos.X = 60.1875
	Actor_34.PhysicDesc.Pos.Y = 4
	Actor_34.PhysicDesc.Pos.Z = 25.375
	Actor_34.PhysicDesc.Pos.Rotation = 158
	Actor_34.PhysicDesc.Density = 1
	Actor_34.PhysicDesc.Collidable = true
	Actor_34.PhysicDesc.SizeX = 1.5
	Actor_34.PhysicDesc.SizeY = 5
	Actor_34.PhysicDesc.SizeZ = 1.5
	Actor_34.PhysicDesc.Filename = ""
	Actor_34:SetPhysicalActorType(2)
	Actor_34:SetPhysicalShape(2)
	Actor_34.ExtraInfo.Name = ""
	Actor_34.ExtraInfo.NameColorR = 0
	Actor_34.ExtraInfo.NameColorG = 0
	Actor_34.ExtraInfo.NameColorB = 0
	Actor_34.ExtraInfo.Display = false
	Actor_34.LifeInfo.Display = false
	Actor_34H = NPCHandler(Actor_34)
	Actor_34H_dia = DialogPart()
	Actor_34H_dia:SetResetDialog(false)
	Actor_34H:SetRootDialog(Actor_34H_dia)
	Actor_34H:SetNpcName(-1)
	Actor_34H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_34H)

	Actor_35 = ActorObjectInfo(35)
	Actor_35:SetRenderType(3)
	Actor_35.DisplayDesc.ModelId = 0
	Actor_35.DisplayDesc.ModelName = "Soldier"
	Actor_35.DisplayDesc.Outfit = "Grass"
	Actor_35.DisplayDesc.Weapon = "rifle"
	Actor_35.DisplayDesc.Mode = "Normal"
	Actor_35.DisplayDesc.UseLight = true
	Actor_35.DisplayDesc.CastShadow = true
	Actor_35.DisplayDesc.ColorR = 1
	Actor_35.DisplayDesc.ColorG = 1
	Actor_35.DisplayDesc.ColorB = 1
	Actor_35.DisplayDesc.ColorA = 1
	Actor_35.DisplayDesc.TransX = 0
	Actor_35.DisplayDesc.TransY = 0
	Actor_35.DisplayDesc.TransZ = 0
	Actor_35.DisplayDesc.ScaleX = 1
	Actor_35.DisplayDesc.ScaleY = 1
	Actor_35.DisplayDesc.ScaleZ = 1
	Actor_35.DisplayDesc.RotX = 0
	Actor_35.DisplayDesc.RotY = 0
	Actor_35.DisplayDesc.RotZ = 0
	Actor_35:SetModelState(1)
	Actor_35.PhysicDesc.Pos.X = 6
	Actor_35.PhysicDesc.Pos.Y = 4
	Actor_35.PhysicDesc.Pos.Z = 17
	Actor_35.PhysicDesc.Pos.Rotation = 153
	Actor_35.PhysicDesc.Density = 1
	Actor_35.PhysicDesc.Collidable = true
	Actor_35.PhysicDesc.SizeX = 1
	Actor_35.PhysicDesc.SizeY = 5
	Actor_35.PhysicDesc.SizeZ = 1
	Actor_35.PhysicDesc.Filename = ""
	Actor_35:SetPhysicalActorType(2)
	Actor_35:SetPhysicalShape(2)
	Actor_35.ExtraInfo.Name = ""
	Actor_35.ExtraInfo.NameColorR = 0
	Actor_35.ExtraInfo.NameColorG = 0
	Actor_35.ExtraInfo.NameColorB = 0
	Actor_35.ExtraInfo.Display = false
	Actor_35.LifeInfo.Display = false
	Actor_35H = NPCHandler(Actor_35)
	Actor_35H_dia = DialogPart()
	Actor_35H_dia:SetResetDialog(false)
	Actor_35H:SetRootDialog(Actor_35H_dia)
	Actor_35H:SetNpcName(-1)
	Actor_35H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_35H)

	Actor_36 = ActorObjectInfo(36)
	Actor_36:SetRenderType(3)
	Actor_36.DisplayDesc.ModelId = 0
	Actor_36.DisplayDesc.ModelName = "Soldier"
	Actor_36.DisplayDesc.Outfit = "Grass"
	Actor_36.DisplayDesc.Weapon = "rifle"
	Actor_36.DisplayDesc.Mode = "Normal"
	Actor_36.DisplayDesc.UseLight = true
	Actor_36.DisplayDesc.CastShadow = true
	Actor_36.DisplayDesc.ColorR = 1
	Actor_36.DisplayDesc.ColorG = 1
	Actor_36.DisplayDesc.ColorB = 1
	Actor_36.DisplayDesc.ColorA = 1
	Actor_36.DisplayDesc.TransX = 0
	Actor_36.DisplayDesc.TransY = 0
	Actor_36.DisplayDesc.TransZ = 0
	Actor_36.DisplayDesc.ScaleX = 1
	Actor_36.DisplayDesc.ScaleY = 1
	Actor_36.DisplayDesc.ScaleZ = 1
	Actor_36.DisplayDesc.RotX = 0
	Actor_36.DisplayDesc.RotY = 0
	Actor_36.DisplayDesc.RotZ = 0
	Actor_36:SetModelState(1)
	Actor_36.PhysicDesc.Pos.X = 13
	Actor_36.PhysicDesc.Pos.Y = 4
	Actor_36.PhysicDesc.Pos.Z = 54
	Actor_36.PhysicDesc.Pos.Rotation = 177
	Actor_36.PhysicDesc.Density = 1
	Actor_36.PhysicDesc.Collidable = true
	Actor_36.PhysicDesc.SizeX = 1
	Actor_36.PhysicDesc.SizeY = 5
	Actor_36.PhysicDesc.SizeZ = 1
	Actor_36.PhysicDesc.Filename = ""
	Actor_36:SetPhysicalActorType(2)
	Actor_36:SetPhysicalShape(2)
	Actor_36.ExtraInfo.Name = ""
	Actor_36.ExtraInfo.NameColorR = 0
	Actor_36.ExtraInfo.NameColorG = 0
	Actor_36.ExtraInfo.NameColorB = 0
	Actor_36.ExtraInfo.Display = false
	Actor_36.LifeInfo.Display = false
	Actor_36H = NPCHandler(Actor_36)
	Actor_36H_dia = DialogPart()
	Actor_36H_dia:SetResetDialog(false)
	Actor_36H:SetRootDialog(Actor_36H_dia)
	Actor_36H:SetNpcName(-1)
	Actor_36H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_36H)

	Actor_37 = ActorObjectInfo(37)
	Actor_37:SetRenderType(3)
	Actor_37.DisplayDesc.ModelId = 0
	Actor_37.DisplayDesc.ModelName = "GroboClone"
	Actor_37.DisplayDesc.Outfit = "Yellow"
	Actor_37.DisplayDesc.Weapon = "No"
	Actor_37.DisplayDesc.Mode = "Normal"
	Actor_37.DisplayDesc.UseLight = true
	Actor_37.DisplayDesc.CastShadow = true
	Actor_37.DisplayDesc.ColorR = 1
	Actor_37.DisplayDesc.ColorG = 1
	Actor_37.DisplayDesc.ColorB = 1
	Actor_37.DisplayDesc.ColorA = 1
	Actor_37.DisplayDesc.TransX = 0
	Actor_37.DisplayDesc.TransY = 0
	Actor_37.DisplayDesc.TransZ = 0
	Actor_37.DisplayDesc.ScaleX = 1
	Actor_37.DisplayDesc.ScaleY = 1
	Actor_37.DisplayDesc.ScaleZ = 1
	Actor_37.DisplayDesc.RotX = 0
	Actor_37.DisplayDesc.RotY = 0
	Actor_37.DisplayDesc.RotZ = 0
	Actor_37:SetModelState(1)
	Actor_37.PhysicDesc.Pos.X = 3
	Actor_37.PhysicDesc.Pos.Y = 14
	Actor_37.PhysicDesc.Pos.Z = 34
	Actor_37.PhysicDesc.Pos.Rotation = 192
	Actor_37.PhysicDesc.Density = 1
	Actor_37.PhysicDesc.Collidable = true
	Actor_37.PhysicDesc.SizeX = 1.5
	Actor_37.PhysicDesc.SizeY = 5
	Actor_37.PhysicDesc.SizeZ = 1.5
	Actor_37.PhysicDesc.Filename = ""
	Actor_37:SetPhysicalActorType(2)
	Actor_37:SetPhysicalShape(2)
	Actor_37.ExtraInfo.Name = ""
	Actor_37.ExtraInfo.NameColorR = 0
	Actor_37.ExtraInfo.NameColorG = 0
	Actor_37.ExtraInfo.NameColorB = 0
	Actor_37.ExtraInfo.Display = false
	Actor_37.LifeInfo.Display = false
	Actor_37H = NPCHandler(Actor_37)
	Actor_37H_dia = DialogPart()
	Actor_37H_dia:SetResetDialog(false)
	Actor_37H:SetRootDialog(Actor_37H_dia)
	Actor_37H:SetNpcName(-1)
	Actor_37H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_37H)

	Actor_38 = ActorObjectInfo(38)
	Actor_38:SetRenderType(3)
	Actor_38.DisplayDesc.ModelId = 0
	Actor_38.DisplayDesc.ModelName = "Grobo"
	Actor_38.DisplayDesc.Outfit = "Sailor"
	Actor_38.DisplayDesc.Weapon = "No"
	Actor_38.DisplayDesc.Mode = "Normal"
	Actor_38.DisplayDesc.UseLight = true
	Actor_38.DisplayDesc.CastShadow = true
	Actor_38.DisplayDesc.ColorR = 1
	Actor_38.DisplayDesc.ColorG = 1
	Actor_38.DisplayDesc.ColorB = 1
	Actor_38.DisplayDesc.ColorA = 1
	Actor_38.DisplayDesc.TransX = 0
	Actor_38.DisplayDesc.TransY = 0
	Actor_38.DisplayDesc.TransZ = 0
	Actor_38.DisplayDesc.ScaleX = 1
	Actor_38.DisplayDesc.ScaleY = 1
	Actor_38.DisplayDesc.ScaleZ = 1
	Actor_38.DisplayDesc.RotX = 0
	Actor_38.DisplayDesc.RotY = 0
	Actor_38.DisplayDesc.RotZ = 0
	Actor_38:SetModelState(1)
	Actor_38.PhysicDesc.Pos.X = 12
	Actor_38.PhysicDesc.Pos.Y = 14
	Actor_38.PhysicDesc.Pos.Z = 1
	Actor_38.PhysicDesc.Pos.Rotation = 25
	Actor_38.PhysicDesc.Density = 1
	Actor_38.PhysicDesc.Collidable = true
	Actor_38.PhysicDesc.SizeX = 1.5
	Actor_38.PhysicDesc.SizeY = 5
	Actor_38.PhysicDesc.SizeZ = 1.5
	Actor_38.PhysicDesc.Filename = ""
	Actor_38:SetPhysicalActorType(2)
	Actor_38:SetPhysicalShape(2)
	Actor_38.ExtraInfo.Name = ""
	Actor_38.ExtraInfo.NameColorR = 0
	Actor_38.ExtraInfo.NameColorG = 0
	Actor_38.ExtraInfo.NameColorB = 0
	Actor_38.ExtraInfo.Display = false
	Actor_38.LifeInfo.Display = false
	Actor_38H = NPCHandler(Actor_38)
	Actor_38H_dia = DialogPart()
	Actor_38H_dia:SetResetDialog(false)
	Actor_38H:SetRootDialog(Actor_38H_dia)
	Actor_38H:SetNpcName(-1)
	Actor_38H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_38H)

	Actor_39 = ActorObjectInfo(39)
	Actor_39:SetRenderType(3)
	Actor_39.DisplayDesc.ModelId = 0
	Actor_39.DisplayDesc.ModelName = "RabbiClone"
	Actor_39.DisplayDesc.Outfit = "Yellow"
	Actor_39.DisplayDesc.Weapon = "No"
	Actor_39.DisplayDesc.Mode = "Normal"
	Actor_39.DisplayDesc.UseLight = true
	Actor_39.DisplayDesc.CastShadow = true
	Actor_39.DisplayDesc.ColorR = 1
	Actor_39.DisplayDesc.ColorG = 1
	Actor_39.DisplayDesc.ColorB = 1
	Actor_39.DisplayDesc.ColorA = 1
	Actor_39.DisplayDesc.TransX = 0
	Actor_39.DisplayDesc.TransY = 0
	Actor_39.DisplayDesc.TransZ = 0
	Actor_39.DisplayDesc.ScaleX = 1
	Actor_39.DisplayDesc.ScaleY = 1
	Actor_39.DisplayDesc.ScaleZ = 1
	Actor_39.DisplayDesc.RotX = 0
	Actor_39.DisplayDesc.RotY = 0
	Actor_39.DisplayDesc.RotZ = 0
	Actor_39:SetModelState(1)
	Actor_39.PhysicDesc.Pos.X = 21.7188
	Actor_39.PhysicDesc.Pos.Y = 4
	Actor_39.PhysicDesc.Pos.Z = 17.6563
	Actor_39.PhysicDesc.Pos.Rotation = 129
	Actor_39.PhysicDesc.Density = 1
	Actor_39.PhysicDesc.Collidable = true
	Actor_39.PhysicDesc.SizeX = 1
	Actor_39.PhysicDesc.SizeY = 6
	Actor_39.PhysicDesc.SizeZ = 1
	Actor_39.PhysicDesc.Filename = ""
	Actor_39:SetPhysicalActorType(2)
	Actor_39:SetPhysicalShape(2)
	Actor_39.ExtraInfo.Name = ""
	Actor_39.ExtraInfo.NameColorR = 0
	Actor_39.ExtraInfo.NameColorG = 0
	Actor_39.ExtraInfo.NameColorB = 0
	Actor_39.ExtraInfo.Display = false
	Actor_39.LifeInfo.Display = false
	Actor_39H = NPCHandler(Actor_39)
	Actor_39H_dia = DialogPart()
	Actor_39H_dia:SetResetDialog(false)
	Actor_39H:SetRootDialog(Actor_39H_dia)
	Actor_39H:SetNpcName(-1)
	Actor_39H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_39H)

	Actor_40 = ActorObjectInfo(40)
	Actor_40:SetRenderType(3)
	Actor_40.DisplayDesc.ModelId = 0
	Actor_40.DisplayDesc.ModelName = "GroboClone"
	Actor_40.DisplayDesc.Outfit = "Yellow"
	Actor_40.DisplayDesc.Weapon = "No"
	Actor_40.DisplayDesc.Mode = "Normal"
	Actor_40.DisplayDesc.UseLight = true
	Actor_40.DisplayDesc.CastShadow = true
	Actor_40.DisplayDesc.ColorR = 1
	Actor_40.DisplayDesc.ColorG = 1
	Actor_40.DisplayDesc.ColorB = 1
	Actor_40.DisplayDesc.ColorA = 1
	Actor_40.DisplayDesc.TransX = 0
	Actor_40.DisplayDesc.TransY = 0
	Actor_40.DisplayDesc.TransZ = 0
	Actor_40.DisplayDesc.ScaleX = 1
	Actor_40.DisplayDesc.ScaleY = 1
	Actor_40.DisplayDesc.ScaleZ = 1
	Actor_40.DisplayDesc.RotX = 0
	Actor_40.DisplayDesc.RotY = 0
	Actor_40.DisplayDesc.RotZ = 0
	Actor_40:SetModelState(1)
	Actor_40.PhysicDesc.Pos.X = 2
	Actor_40.PhysicDesc.Pos.Y = 14
	Actor_40.PhysicDesc.Pos.Z = 13
	Actor_40.PhysicDesc.Pos.Rotation = 25
	Actor_40.PhysicDesc.Density = 1
	Actor_40.PhysicDesc.Collidable = true
	Actor_40.PhysicDesc.SizeX = 1.5
	Actor_40.PhysicDesc.SizeY = 5
	Actor_40.PhysicDesc.SizeZ = 1.5
	Actor_40.PhysicDesc.Filename = ""
	Actor_40:SetPhysicalActorType(2)
	Actor_40:SetPhysicalShape(2)
	Actor_40.ExtraInfo.Name = ""
	Actor_40.ExtraInfo.NameColorR = 0
	Actor_40.ExtraInfo.NameColorG = 0
	Actor_40.ExtraInfo.NameColorB = 0
	Actor_40.ExtraInfo.Display = false
	Actor_40.LifeInfo.Display = false
	Actor_40H = NPCHandler(Actor_40)
	Actor_40H_dia = DialogPart()
	Actor_40H_dia:SetResetDialog(false)
	Actor_40H:SetRootDialog(Actor_40H_dia)
	Actor_40H:SetNpcName(-1)
	Actor_40H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_40H)

	Actor_41 = ActorObjectInfo(41)
	Actor_41:SetRenderType(3)
	Actor_41.DisplayDesc.ModelId = 0
	Actor_41.DisplayDesc.ModelName = "GroboClone"
	Actor_41.DisplayDesc.Outfit = "SuperGro"
	Actor_41.DisplayDesc.Weapon = "No"
	Actor_41.DisplayDesc.Mode = "Normal"
	Actor_41.DisplayDesc.UseLight = true
	Actor_41.DisplayDesc.CastShadow = true
	Actor_41.DisplayDesc.ColorR = 1
	Actor_41.DisplayDesc.ColorG = 1
	Actor_41.DisplayDesc.ColorB = 1
	Actor_41.DisplayDesc.ColorA = 1
	Actor_41.DisplayDesc.TransX = 0
	Actor_41.DisplayDesc.TransY = 0
	Actor_41.DisplayDesc.TransZ = 0
	Actor_41.DisplayDesc.ScaleX = 1
	Actor_41.DisplayDesc.ScaleY = 1
	Actor_41.DisplayDesc.ScaleZ = 1
	Actor_41.DisplayDesc.RotX = 0
	Actor_41.DisplayDesc.RotY = 0
	Actor_41.DisplayDesc.RotZ = 0
	Actor_41:SetModelState(1)
	Actor_41.PhysicDesc.Pos.X = 12
	Actor_41.PhysicDesc.Pos.Y = 4
	Actor_41.PhysicDesc.Pos.Z = 38
	Actor_41.PhysicDesc.Pos.Rotation = 433
	Actor_41.PhysicDesc.Density = 1
	Actor_41.PhysicDesc.Collidable = true
	Actor_41.PhysicDesc.SizeX = 1.5
	Actor_41.PhysicDesc.SizeY = 5
	Actor_41.PhysicDesc.SizeZ = 1.5
	Actor_41.PhysicDesc.Filename = ""
	Actor_41:SetPhysicalActorType(2)
	Actor_41:SetPhysicalShape(2)
	Actor_41.ExtraInfo.Name = ""
	Actor_41.ExtraInfo.NameColorR = 0
	Actor_41.ExtraInfo.NameColorG = 0
	Actor_41.ExtraInfo.NameColorB = 0
	Actor_41.ExtraInfo.Display = false
	Actor_41.LifeInfo.Display = false
	Actor_41H = NPCHandler(Actor_41)
	Actor_41H_dia = DialogPart()
	Actor_41H_dia:SetResetDialog(false)
	Actor_41H:SetRootDialog(Actor_41H_dia)
	Actor_41H:SetNpcName(-1)
	Actor_41H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_41H)

	Actor_42 = ActorObjectInfo(42)
	Actor_42:SetRenderType(3)
	Actor_42.DisplayDesc.ModelId = 0
	Actor_42.DisplayDesc.ModelName = "Object"
	Actor_42.DisplayDesc.Outfit = "MekaPingouin"
	Actor_42.DisplayDesc.Weapon = "No"
	Actor_42.DisplayDesc.Mode = "Normal"
	Actor_42.DisplayDesc.UseLight = true
	Actor_42.DisplayDesc.CastShadow = true
	Actor_42.DisplayDesc.ColorR = 1
	Actor_42.DisplayDesc.ColorG = 1
	Actor_42.DisplayDesc.ColorB = 1
	Actor_42.DisplayDesc.ColorA = 1
	Actor_42.DisplayDesc.TransX = 0
	Actor_42.DisplayDesc.TransY = 0
	Actor_42.DisplayDesc.TransZ = 0
	Actor_42.DisplayDesc.ScaleX = 1
	Actor_42.DisplayDesc.ScaleY = 1
	Actor_42.DisplayDesc.ScaleZ = 1
	Actor_42.DisplayDesc.RotX = 0
	Actor_42.DisplayDesc.RotY = 0
	Actor_42.DisplayDesc.RotZ = 0
	Actor_42:SetModelState(1)
	Actor_42.PhysicDesc.Pos.X = 0
	Actor_42.PhysicDesc.Pos.Y = -1
	Actor_42.PhysicDesc.Pos.Z = 0
	Actor_42.PhysicDesc.Pos.Rotation = 25
	Actor_42.PhysicDesc.Density = 1
	Actor_42.PhysicDesc.Collidable = true
	Actor_42.PhysicDesc.SizeX = 0.5
	Actor_42.PhysicDesc.SizeY = 2
	Actor_42.PhysicDesc.SizeZ = 0.6
	Actor_42.PhysicDesc.Filename = ""
	Actor_42:SetPhysicalActorType(2)
	Actor_42:SetPhysicalShape(2)
	Actor_42.ExtraInfo.Name = ""
	Actor_42.ExtraInfo.NameColorR = 0
	Actor_42.ExtraInfo.NameColorG = 0
	Actor_42.ExtraInfo.NameColorB = 0
	Actor_42.ExtraInfo.Display = false
	Actor_42.LifeInfo.Display = false
	Actor_42H = NPCHandler(Actor_42)
	Actor_42H_dia = DialogPart()
	Actor_42H_dia:SetResetDialog(false)
	Actor_42H:SetRootDialog(Actor_42H_dia)
	Actor_42H:SetNpcName(-1)
	Actor_42H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_42H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 7, 4, 1, true)
	Trigger_1:SetPosition(57.5, 4, 0.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map012_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit14", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 3.5, 3, true)
	Trigger_2:SetPosition(6.5, 12, 3.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map022_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit15", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 3, 3.5, 1, true)
	Trigger_3:SetPosition(12.5, 4, 13.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map022_1")
	Trigger_3_act1:SetSpawning(2)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit16", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 3.5, 3, true)
	Trigger_4:SetPosition(9.5, 4, 38.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map023_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit9", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 4, 3.5, 1, true)
	Trigger_5:SetPosition(19, 4, 3.5)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map012_1")
	Trigger_5_act1:SetSpawning(2)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "ContainerTri_6", true, false, false)
	Trigger_6 = ZoneActionTrigger(Trigger_6_info, 1.99805, 5.375, 2.37304, "Normal", "")
	Trigger_6:SetPosition(10.999, 4, 30.3115)
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
	Trigger_7 = ZoneActionTrigger(Trigger_7_info, 1.96875, 5.12891, 2.3125, "Normal", "")
	Trigger_7:SetPosition(4.42188, 14, 31.375)
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
	Trigger_8 = ZoneActionTrigger(Trigger_8_info, 2.68946, 5.69531, 2.75196, "Normal", "")
	Trigger_8:SetPosition(8.34473, 14, 8.37598)
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
	Trigger_9:SetPosition(28.999, 4, 8)
	Trigger_9_act1 = DisplayTextAction()
	Trigger_9_act1:SetTextId(382)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "TextTri_10", true, false, false)
	Trigger_10 = ActivationTrigger(Trigger_10_info, 2, "Normal", "")
	Trigger_10:SetPosition(17, 4, 10.999)
	Trigger_10_act1 = DisplayTextAction()
	Trigger_10_act1:SetTextId(382)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "ContainerTri_11", true, false, false)
	Trigger_11 = ZoneActionTrigger(Trigger_11_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_11:SetPosition(34.999, 10, 6.99902)
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
	Trigger_12 = ZoneActionTrigger(Trigger_12_info, 2.99804, 3.99609, 1.99805, "Normal", "")
	Trigger_12:SetPosition(42.499, 10, 0.999023)
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
	Trigger_13 = ZoneActionTrigger(Trigger_13_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_13:SetPosition(48.999, 10, 0.999023)
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

	Trigger_14_info = TriggerInfo(14, "TextTri_14", true, false, false)
	Trigger_14 = ActivationTrigger(Trigger_14_info, 2, "Normal", "")
	Trigger_14:SetPosition(37.1582, 4, 44.5176)
	Trigger_14_act1 = DisplayTextAction()
	Trigger_14_act1:SetTextId(382)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "ContainerTri_15", true, false, false)
	Trigger_15 = ZoneActionTrigger(Trigger_15_info, 2.99804, 4.99609, 2.99804, "Normal", "")
	Trigger_15:SetPosition(4.49902, 14, 44.499)
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
	Trigger_16 = ZoneActionTrigger(Trigger_16_info, 2.99804, 3.99609, 1.99805, "Normal", "")
	Trigger_16:SetPosition(59.499, 4, 25.999)
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
	Trigger_17 = ZoneActionTrigger(Trigger_17_info, 2.99804, 3.99609, 1.99805, "Normal", "")
	Trigger_17:SetPosition(55.499, 4, 25.999)
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
	Trigger_18 = ZoneActionTrigger(Trigger_18_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_18:SetPosition(47.999, 9, 6.99902)
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
	Trigger_19 = ZoneActionTrigger(Trigger_19_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_19:SetPosition(51.999, 9, 6.99902)
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
	Trigger_20 = ZoneActionTrigger(Trigger_20_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_20:SetPosition(44.999, 4, 12.999)
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
	Trigger_21 = ZoneActionTrigger(Trigger_21_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_21:SetPosition(40.999, 4, 9.99902)
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
	Trigger_22 = ZoneActionTrigger(Trigger_22_info, 1.99805, 3.99609, 2.99804, "Normal", "")
	Trigger_22:SetPosition(1.99902, 14, 36.499)
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

	Trigger_23_info = TriggerInfo(23, "ContainerTri_23", true, false, false)
	Trigger_23 = ZoneActionTrigger(Trigger_23_info, 2.99804, 3.99609, 0.998046, "Normal", "")
	Trigger_23:SetPosition(40.499, 10, 4.49902)
	Trigger_23_act1 = OpenContainerAction()
	Trigger_23_act1:SetTimeToReset(300)
		Trigger_23_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_23_act1:AddItem(Trigger_23_act1ContItem0)
		Trigger_23_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_23_act1:AddItem(Trigger_23_act1ContItem1)
		Trigger_23_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_23_act1:AddItem(Trigger_23_act1ContItem2)
		Trigger_23_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_23_act1:AddItem(Trigger_23_act1ContItem3)
	Trigger_23:SetAction1(Trigger_23_act1)
	Trigger_23:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_23)

	Trigger_24_info = TriggerInfo(24, "ContainerTri_24", true, false, false)
	Trigger_24 = ZoneActionTrigger(Trigger_24_info, 2.99804, 3.99609, 0.998046, "Normal", "")
	Trigger_24:SetPosition(40.499, 10, 5.49902)
	Trigger_24_act1 = OpenContainerAction()
	Trigger_24_act1:SetTimeToReset(300)
		Trigger_24_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_24_act1:AddItem(Trigger_24_act1ContItem0)
		Trigger_24_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_24_act1:AddItem(Trigger_24_act1ContItem1)
		Trigger_24_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_24_act1:AddItem(Trigger_24_act1ContItem2)
		Trigger_24_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_24_act1:AddItem(Trigger_24_act1ContItem3)
	Trigger_24:SetAction1(Trigger_24_act1)
	Trigger_24:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_24)

	Trigger_25_info = TriggerInfo(25, "ContainerTri_25", true, false, false)
	Trigger_25 = ZoneActionTrigger(Trigger_25_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_25:SetPosition(40.999, 10, 6.99902)
	Trigger_25_act1 = OpenContainerAction()
	Trigger_25_act1:SetTimeToReset(300)
		Trigger_25_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_25_act1:AddItem(Trigger_25_act1ContItem0)
		Trigger_25_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_25_act1:AddItem(Trigger_25_act1ContItem1)
		Trigger_25_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_25_act1:AddItem(Trigger_25_act1ContItem2)
		Trigger_25_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_25_act1:AddItem(Trigger_25_act1ContItem3)
	Trigger_25:SetAction1(Trigger_25_act1)
	Trigger_25:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_25)

	Trigger_26_info = TriggerInfo(26, "ContainerTri_26", true, false, false)
	Trigger_26 = ZoneActionTrigger(Trigger_26_info, 2.99804, 3.99609, 0.998046, "Normal", "")
	Trigger_26:SetPosition(47.499, 10, 2.49902)
	Trigger_26_act1 = OpenContainerAction()
	Trigger_26_act1:SetTimeToReset(300)
		Trigger_26_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_26_act1:AddItem(Trigger_26_act1ContItem0)
		Trigger_26_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_26_act1:AddItem(Trigger_26_act1ContItem1)
		Trigger_26_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_26_act1:AddItem(Trigger_26_act1ContItem2)
		Trigger_26_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_26_act1:AddItem(Trigger_26_act1ContItem3)
	Trigger_26:SetAction1(Trigger_26_act1)
	Trigger_26:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_26)

	Trigger_27_info = TriggerInfo(27, "ContainerTri_27", true, false, false)
	Trigger_27 = ZoneActionTrigger(Trigger_27_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_27:SetPosition(52.999, 10, 0.999023)
	Trigger_27_act1 = OpenContainerAction()
	Trigger_27_act1:SetTimeToReset(300)
		Trigger_27_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_27_act1:AddItem(Trigger_27_act1ContItem0)
		Trigger_27_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_27_act1:AddItem(Trigger_27_act1ContItem1)
		Trigger_27_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_27_act1:AddItem(Trigger_27_act1ContItem2)
		Trigger_27_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_27_act1:AddItem(Trigger_27_act1ContItem3)
	Trigger_27:SetAction1(Trigger_27_act1)
	Trigger_27:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_27)

	Trigger_28_info = TriggerInfo(28, "ContainerTri_28", true, false, false)
	Trigger_28 = ZoneActionTrigger(Trigger_28_info, 1.99805, 3.99609, 0.998046, "Normal", "")
	Trigger_28:SetPosition(1.99902, 14, 40.499)
	Trigger_28_act1 = OpenContainerAction()
	Trigger_28_act1:SetTimeToReset(300)
		Trigger_28_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_28_act1:AddItem(Trigger_28_act1ContItem0)
		Trigger_28_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_28_act1:AddItem(Trigger_28_act1ContItem1)
		Trigger_28_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_28_act1:AddItem(Trigger_28_act1ContItem2)
		Trigger_28_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_28_act1:AddItem(Trigger_28_act1ContItem3)
	Trigger_28:SetAction1(Trigger_28_act1)
	Trigger_28:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_28)

end
