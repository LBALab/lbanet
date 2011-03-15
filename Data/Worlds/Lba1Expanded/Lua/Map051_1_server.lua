function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(47)
	Spawn_1:SetPosY(5.01)
	Spawn_1:SetPosZ(61)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(60)
	Spawn_2:SetPosY(5.01)
	Spawn_2:SetPosZ(2)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(49)
	Spawn_3:SetPosY(5.01)
	Spawn_3:SetPosZ(47)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(56)
	Spawn_4:SetPosY(5.01)
	Spawn_4:SetPosZ(27)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(57)
	Spawn_5:SetPosY(5.01)
	Spawn_5:SetPosZ(17)
	Spawn_5:SetName("spawning5")
	environment:AddSpawn(Spawn_5)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map51.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map51.phy"
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

	Actor_15 = ActorObjectInfo(15)
	Actor_15:SetRenderType(1)
	Actor_15.DisplayDesc.ModelId = 0
	Actor_15.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite029.osgb"
	Actor_15.DisplayDesc.Outfit = ""
	Actor_15.DisplayDesc.Weapon = ""
	Actor_15.DisplayDesc.Mode = ""
	Actor_15.DisplayDesc.UseLight = true
	Actor_15.DisplayDesc.CastShadow = false
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
	Actor_15.PhysicDesc.Pos.X = 48
	Actor_15.PhysicDesc.Pos.Y = 5
	Actor_15.PhysicDesc.Pos.Z = 61
	Actor_15.PhysicDesc.Pos.Rotation = 0
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 2
	Actor_15.PhysicDesc.SizeY = 1
	Actor_15.PhysicDesc.SizeZ = 2
	Actor_15.PhysicDesc.Filename = ""
	Actor_15:SetPhysicalActorType(2)
	Actor_15:SetPhysicalShape(2)
	Actor_15.ExtraInfo.Name = ""
	Actor_15.ExtraInfo.NameColorR = 0
	Actor_15.ExtraInfo.NameColorG = 0
	Actor_15.ExtraInfo.NameColorB = 0
	Actor_15.ExtraInfo.Display = false
	Actor_15.LifeInfo.Display = false
	Actor_15H = ActorHandler(Actor_15)
	Actor_15_Sc0 = ASPWaitForSignal(5)
	Actor_15H:AddScriptPart(Actor_15_Sc0)
	Actor_15_Sc1 = ASPGoTo(48,15,61,0.005)
	Actor_15H:AddScriptPart(Actor_15_Sc1)
	Actor_15_Sc2 = ASPGoTo(48,5,61,0.005)
	Actor_15H:AddScriptPart(Actor_15_Sc2)
	environment:AddActorObject(Actor_15H)

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(1)
	Actor_17.DisplayDesc.ModelId = 0
	Actor_17.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite029.osgb"
	Actor_17.DisplayDesc.Outfit = ""
	Actor_17.DisplayDesc.Weapon = ""
	Actor_17.DisplayDesc.Mode = ""
	Actor_17.DisplayDesc.UseLight = true
	Actor_17.DisplayDesc.CastShadow = false
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
	Actor_17.PhysicDesc.Pos.X = 58
	Actor_17.PhysicDesc.Pos.Y = 5
	Actor_17.PhysicDesc.Pos.Z = 18
	Actor_17.PhysicDesc.Pos.Rotation = 0
	Actor_17.PhysicDesc.Density = 1
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 2
	Actor_17.PhysicDesc.SizeY = 1
	Actor_17.PhysicDesc.SizeZ = 2
	Actor_17.PhysicDesc.Filename = ""
	Actor_17:SetPhysicalActorType(2)
	Actor_17:SetPhysicalShape(2)
	Actor_17.ExtraInfo.Name = ""
	Actor_17.ExtraInfo.NameColorR = 0
	Actor_17.ExtraInfo.NameColorG = 0
	Actor_17.ExtraInfo.NameColorB = 0
	Actor_17.ExtraInfo.Display = false
	Actor_17.LifeInfo.Display = false
	Actor_17H = ActorHandler(Actor_17)
	Actor_17_Sc0 = ASPWaitForSignal(5)
	Actor_17H:AddScriptPart(Actor_17_Sc0)
	Actor_17_Sc1 = ASPGoTo(58,15,18,0.005)
	Actor_17H:AddScriptPart(Actor_17_Sc1)
	Actor_17_Sc2 = ASPGoTo(58,5,18,0.005)
	Actor_17H:AddScriptPart(Actor_17_Sc2)
	environment:AddActorObject(Actor_17H)

	Actor_19 = ActorObjectInfo(19)
	Actor_19:SetRenderType(1)
	Actor_19.DisplayDesc.ModelId = 0
	Actor_19.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite029.osgb"
	Actor_19.DisplayDesc.Outfit = ""
	Actor_19.DisplayDesc.Weapon = ""
	Actor_19.DisplayDesc.Mode = ""
	Actor_19.DisplayDesc.UseLight = true
	Actor_19.DisplayDesc.CastShadow = false
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
	Actor_19.PhysicDesc.Pos.X = 61
	Actor_19.PhysicDesc.Pos.Y = 5
	Actor_19.PhysicDesc.Pos.Z = 2
	Actor_19.PhysicDesc.Pos.Rotation = 0
	Actor_19.PhysicDesc.Density = 1
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = 2
	Actor_19.PhysicDesc.SizeY = 1
	Actor_19.PhysicDesc.SizeZ = 2
	Actor_19.PhysicDesc.Filename = ""
	Actor_19:SetPhysicalActorType(2)
	Actor_19:SetPhysicalShape(2)
	Actor_19.ExtraInfo.Name = ""
	Actor_19.ExtraInfo.NameColorR = 0
	Actor_19.ExtraInfo.NameColorG = 0
	Actor_19.ExtraInfo.NameColorB = 0
	Actor_19.ExtraInfo.Display = false
	Actor_19.LifeInfo.Display = false
	Actor_19H = ActorHandler(Actor_19)
	Actor_19_Sc0 = ASPWaitForSignal(5)
	Actor_19H:AddScriptPart(Actor_19_Sc0)
	Actor_19_Sc1 = ASPGoTo(61,15,2,0.005)
	Actor_19H:AddScriptPart(Actor_19_Sc1)
	Actor_19_Sc2 = ASPGoTo(61,5,2,0.005)
	Actor_19H:AddScriptPart(Actor_19_Sc2)
	environment:AddActorObject(Actor_19H)

	Actor_21 = ActorObjectInfo(21)
	Actor_21:SetRenderType(1)
	Actor_21.DisplayDesc.ModelId = 0
	Actor_21.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite029.osgb"
	Actor_21.DisplayDesc.Outfit = ""
	Actor_21.DisplayDesc.Weapon = ""
	Actor_21.DisplayDesc.Mode = ""
	Actor_21.DisplayDesc.UseLight = true
	Actor_21.DisplayDesc.CastShadow = false
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
	Actor_21.PhysicDesc.Pos.X = 50
	Actor_21.PhysicDesc.Pos.Y = 5
	Actor_21.PhysicDesc.Pos.Z = 47
	Actor_21.PhysicDesc.Pos.Rotation = 0
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 2
	Actor_21.PhysicDesc.SizeY = 1
	Actor_21.PhysicDesc.SizeZ = 2
	Actor_21.PhysicDesc.Filename = ""
	Actor_21:SetPhysicalActorType(2)
	Actor_21:SetPhysicalShape(2)
	Actor_21.ExtraInfo.Name = ""
	Actor_21.ExtraInfo.NameColorR = 0
	Actor_21.ExtraInfo.NameColorG = 0
	Actor_21.ExtraInfo.NameColorB = 0
	Actor_21.ExtraInfo.Display = false
	Actor_21.LifeInfo.Display = false
	Actor_21H = ActorHandler(Actor_21)
	Actor_21_Sc0 = ASPWaitForSignal(5)
	Actor_21H:AddScriptPart(Actor_21_Sc0)
	Actor_21_Sc1 = ASPGoTo(50,15,47,0.005)
	Actor_21H:AddScriptPart(Actor_21_Sc1)
	Actor_21_Sc2 = ASPGoTo(50,5,47,0.005)
	Actor_21H:AddScriptPart(Actor_21_Sc2)
	environment:AddActorObject(Actor_21H)

	Actor_23 = ActorObjectInfo(23)
	Actor_23:SetRenderType(1)
	Actor_23.DisplayDesc.ModelId = 0
	Actor_23.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite121.osgb"
	Actor_23.DisplayDesc.Outfit = ""
	Actor_23.DisplayDesc.Weapon = ""
	Actor_23.DisplayDesc.Mode = ""
	Actor_23.DisplayDesc.UseLight = true
	Actor_23.DisplayDesc.CastShadow = false
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
	Actor_23.PhysicDesc.Pos.X = 57
	Actor_23.PhysicDesc.Pos.Y = 5
	Actor_23.PhysicDesc.Pos.Z = 27
	Actor_23.PhysicDesc.Pos.Rotation = 0
	Actor_23.PhysicDesc.Density = 1
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 2
	Actor_23.PhysicDesc.SizeY = 1
	Actor_23.PhysicDesc.SizeZ = 2
	Actor_23.PhysicDesc.Filename = ""
	Actor_23:SetPhysicalActorType(2)
	Actor_23:SetPhysicalShape(2)
	Actor_23.ExtraInfo.Name = ""
	Actor_23.ExtraInfo.NameColorR = 0
	Actor_23.ExtraInfo.NameColorG = 0
	Actor_23.ExtraInfo.NameColorB = 0
	Actor_23.ExtraInfo.Display = false
	Actor_23.LifeInfo.Display = false
	Actor_23H = ActorHandler(Actor_23)
	Actor_23_Sc0 = ASPWaitForSignal(5)
	Actor_23H:AddScriptPart(Actor_23_Sc0)
	Actor_23_Sc1 = ASPGoTo(57,15,27,0.005)
	Actor_23H:AddScriptPart(Actor_23_Sc1)
	Actor_23_Sc2 = ASPGoTo(57,5,27,0.005)
	Actor_23H:AddScriptPart(Actor_23_Sc2)
	environment:AddActorObject(Actor_23H)

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(3)
	Actor_25.DisplayDesc.ModelId = 0
	Actor_25.DisplayDesc.ModelName = "Snake"
	Actor_25.DisplayDesc.Outfit = "No"
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
	Actor_25.PhysicDesc.Pos.X = 58
	Actor_25.PhysicDesc.Pos.Y = 5
	Actor_25.PhysicDesc.Pos.Z = 56
	Actor_25.PhysicDesc.Pos.Rotation = 25
	Actor_25.PhysicDesc.Density = 1
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 1
	Actor_25.PhysicDesc.SizeY = 0.5
	Actor_25.PhysicDesc.SizeZ = 1
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
	Actor_26.DisplayDesc.ModelName = "Snake"
	Actor_26.DisplayDesc.Outfit = "No"
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
	Actor_26.PhysicDesc.Pos.X = 56.7813
	Actor_26.PhysicDesc.Pos.Y = 0
	Actor_26.PhysicDesc.Pos.Z = 50.8438
	Actor_26.PhysicDesc.Pos.Rotation = 281
	Actor_26.PhysicDesc.Density = 1
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 1
	Actor_26.PhysicDesc.SizeY = 0.5
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
	Actor_27.DisplayDesc.ModelName = "Snake"
	Actor_27.DisplayDesc.Outfit = "No"
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
	Actor_27.PhysicDesc.Pos.X = 53.5313
	Actor_27.PhysicDesc.Pos.Y = 5
	Actor_27.PhysicDesc.Pos.Z = 37
	Actor_27.PhysicDesc.Pos.Rotation = 177
	Actor_27.PhysicDesc.Density = 1
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 1
	Actor_27.PhysicDesc.SizeY = 0.5
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
	Actor_28.DisplayDesc.ModelName = "Snake"
	Actor_28.DisplayDesc.Outfit = "No"
	Actor_28.DisplayDesc.Weapon = "No"
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
	Actor_28.PhysicDesc.Pos.X = 63
	Actor_28.PhysicDesc.Pos.Y = 0
	Actor_28.PhysicDesc.Pos.Z = 10
	Actor_28.PhysicDesc.Pos.Rotation = 25
	Actor_28.PhysicDesc.Density = 1
	Actor_28.PhysicDesc.Collidable = true
	Actor_28.PhysicDesc.SizeX = 1
	Actor_28.PhysicDesc.SizeY = 0.5
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
	Actor_29.DisplayDesc.ModelName = "Object"
	Actor_29.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_29.PhysicDesc.Pos.X = 0
	Actor_29.PhysicDesc.Pos.Y = -1
	Actor_29.PhysicDesc.Pos.Z = 0
	Actor_29.PhysicDesc.Pos.Rotation = 25
	Actor_29.PhysicDesc.Density = 1
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 0.5
	Actor_29.PhysicDesc.SizeY = 2
	Actor_29.PhysicDesc.SizeZ = 0.6
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

	Trigger_1_info = TriggerInfo(1, "exit11", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 2, 2, true)
	Trigger_1:SetPosition(58, 14, 18)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map049_1")
	Trigger_1_act1:SetSpawning(4)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit14", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 2, 2, true)
	Trigger_2:SetPosition(61, 14, 2)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map043_1")
	Trigger_2_act1:SetSpawning(4)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 2.5, 2, true)
	Trigger_3:SetPosition(48, 15, 61)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map042_1")
	Trigger_3_act1:SetSpawning(5)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit4", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 2, 2.5, 2, true)
	Trigger_4:SetPosition(50, 15, 47)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map049_1")
	Trigger_4_act1:SetSpawning(2)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit8", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 2, 2, 2, true)
	Trigger_5:SetPosition(57, 14, 27)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map049_1")
	Trigger_5_act1:SetSpawning(3)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "LadderTri_6", true, false, false)
	Trigger_6 = ActivationTrigger(Trigger_6_info, 1.66667, "Normal", "")
	Trigger_6:SetPosition(53.999, 0, 58.999)
	Trigger_6_act1 = ClientScriptAction()
	Trigger_6_act1_cs = GoUpLadderScript()
	Trigger_6_act1_cs:SetLadderPositionX(53.999)
	Trigger_6_act1_cs:SetLadderPositionY(0)
	Trigger_6_act1_cs:SetLadderPositionZ(58.999)
	Trigger_6_act1_cs:SetLadderHeight(5)
	Trigger_6_act1_cs:SetLadderDirection(270)
	Trigger_6_act1:SetScript(Trigger_6_act1_cs)
	Trigger_6:SetAction1(Trigger_6_act1)
	Trigger_6:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "TextTri_7", true, false, false)
	Trigger_7 = ActivationTrigger(Trigger_7_info, 2, "Normal", "")
	Trigger_7:SetPosition(48.999, 5, 58)
	Trigger_7_act1 = DisplayTextAction()
	Trigger_7_act1:SetTextId(651)
	Trigger_7:SetAction1(Trigger_7_act1)
	Trigger_7:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "TextTri_8", true, false, false)
	Trigger_8 = ActivationTrigger(Trigger_8_info, 2, "Normal", "")
	Trigger_8:SetPosition(52.999, 5, 37)
	Trigger_8_act1 = DisplayTextAction()
	Trigger_8_act1:SetTextId(651)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "TextTri_9", true, false, false)
	Trigger_9 = ActivationTrigger(Trigger_9_info, 2, "Normal", "")
	Trigger_9:SetPosition(58, 5, 21.999)
	Trigger_9_act1 = DisplayTextAction()
	Trigger_9_act1:SetTextId(651)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "TextTri_10", true, false, false)
	Trigger_10 = ActivationTrigger(Trigger_10_info, 2, "Normal", "")
	Trigger_10:SetPosition(58, 5, 2.99902)
	Trigger_10_act1 = DisplayTextAction()
	Trigger_10_act1:SetTextId(800)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "LadderTri_11", true, false, false)
	Trigger_11 = ActivationTrigger(Trigger_11_info, 1.66667, "Normal", "")
	Trigger_11:SetPosition(60.999, 0, 7.99902)
	Trigger_11_act1 = ClientScriptAction()
	Trigger_11_act1_cs = GoUpLadderScript()
	Trigger_11_act1_cs:SetLadderPositionX(60.999)
	Trigger_11_act1_cs:SetLadderPositionY(0)
	Trigger_11_act1_cs:SetLadderPositionZ(7.99902)
	Trigger_11_act1_cs:SetLadderHeight(5)
	Trigger_11_act1_cs:SetLadderDirection(180)
	Trigger_11_act1:SetScript(Trigger_11_act1_cs)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "LadderTri_12", true, false, false)
	Trigger_12 = ActivationTrigger(Trigger_12_info, 1.66667, "Normal", "")
	Trigger_12:SetPosition(59.999, 0, 13.999)
	Trigger_12_act1 = ClientScriptAction()
	Trigger_12_act1_cs = GoUpLadderScript()
	Trigger_12_act1_cs:SetLadderPositionX(59.999)
	Trigger_12_act1_cs:SetLadderPositionY(0)
	Trigger_12_act1_cs:SetLadderPositionZ(13.999)
	Trigger_12_act1_cs:SetLadderHeight(5)
	Trigger_12_act1_cs:SetLadderDirection(270)
	Trigger_12_act1:SetScript(Trigger_12_act1_cs)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "LadderTri_13", true, false, false)
	Trigger_13 = ActivationTrigger(Trigger_13_info, 1.66667, "Normal", "")
	Trigger_13:SetPosition(55.999, 0, 33.999)
	Trigger_13_act1 = ClientScriptAction()
	Trigger_13_act1_cs = GoUpLadderScript()
	Trigger_13_act1_cs:SetLadderPositionX(55.999)
	Trigger_13_act1_cs:SetLadderPositionY(0)
	Trigger_13_act1_cs:SetLadderPositionZ(33.999)
	Trigger_13_act1_cs:SetLadderHeight(5)
	Trigger_13_act1_cs:SetLadderDirection(270)
	Trigger_13_act1:SetScript(Trigger_13_act1_cs)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "LadderTri_14", true, false, false)
	Trigger_14 = ActivationTrigger(Trigger_14_info, 1.66667, "Normal", "")
	Trigger_14:SetPosition(52.999, 0, 49.999)
	Trigger_14_act1 = ClientScriptAction()
	Trigger_14_act1_cs = GoUpLadderScript()
	Trigger_14_act1_cs:SetLadderPositionX(52.999)
	Trigger_14_act1_cs:SetLadderPositionY(0)
	Trigger_14_act1_cs:SetLadderPositionZ(49.999)
	Trigger_14_act1_cs:SetLadderHeight(5)
	Trigger_14_act1_cs:SetLadderDirection(180)
	Trigger_14_act1:SetScript(Trigger_14_act1_cs)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "ContainerTri_15", true, false, false)
	Trigger_15 = ZoneActionTrigger(Trigger_15_info, 3.99804, 4.99609, 1.99805, "Normal", "")
	Trigger_15:SetPosition(59.999, 5, 27.999)
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
	Trigger_16 = ZoneActionTrigger(Trigger_16_info, 2.99804, 4.99609, 2.99804, "Normal", "")
	Trigger_16:SetPosition(53.499, 5, 62.499)
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
	Trigger_17:SetPosition(56.499, 5, 48.499)
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
	Trigger_18 = ZoneActionTrigger(Trigger_18_info, 2.99804, 5.99609, 3.99804, "Normal", "")
	Trigger_18:SetPosition(59.499, 5, 47.999)
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

	Trigger_19_info = TriggerInfo(19, "FloorSwitchTri_19", true, false, false)
	Trigger_19 = ZoneActionTrigger(Trigger_19_info, 2, 2, 2, "Normal", "")
	Trigger_19:SetPosition(48, 5, 61)
	Trigger_19_act1 = SendSignalAction()
	Trigger_19_act1:SetActorId(15)
	Trigger_19_act1:SetSignal(5)
	Trigger_19:SetAction1(Trigger_19_act1)
	Trigger_19:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_19)

	Trigger_20_info = TriggerInfo(20, "FloorSwitchTri_20", true, false, false)
	Trigger_20 = ZoneActionTrigger(Trigger_20_info, 2, 2, 2, "Normal", "")
	Trigger_20:SetPosition(58, 5, 18)
	Trigger_20_act1 = SendSignalAction()
	Trigger_20_act1:SetActorId(17)
	Trigger_20_act1:SetSignal(5)
	Trigger_20:SetAction1(Trigger_20_act1)
	Trigger_20:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_20)

	Trigger_21_info = TriggerInfo(21, "FloorSwitchTri_21", true, false, false)
	Trigger_21 = ZoneActionTrigger(Trigger_21_info, 2, 2, 2, "Normal", "")
	Trigger_21:SetPosition(61, 5, 2)
	Trigger_21_act1 = SendSignalAction()
	Trigger_21_act1:SetActorId(19)
	Trigger_21_act1:SetSignal(5)
	Trigger_21:SetAction1(Trigger_21_act1)
	Trigger_21:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_21)

	Trigger_22_info = TriggerInfo(22, "FloorSwitchTri_22", true, false, false)
	Trigger_22 = ZoneActionTrigger(Trigger_22_info, 2, 2, 2, "Normal", "")
	Trigger_22:SetPosition(50, 5, 47)
	Trigger_22_act1 = SendSignalAction()
	Trigger_22_act1:SetActorId(21)
	Trigger_22_act1:SetSignal(5)
	Trigger_22:SetAction1(Trigger_22_act1)
	Trigger_22:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_22)

	Trigger_23_info = TriggerInfo(23, "FloorSwitchTri_23", true, false, false)
	Trigger_23 = ZoneActionTrigger(Trigger_23_info, 2, 2, 2, "Normal", "")
	Trigger_23:SetPosition(57, 5, 27)
	Trigger_23_act1 = SendSignalAction()
	Trigger_23_act1:SetActorId(23)
	Trigger_23_act1:SetSignal(5)
	Trigger_23:SetAction1(Trigger_23_act1)
	Trigger_23:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_23)

end
