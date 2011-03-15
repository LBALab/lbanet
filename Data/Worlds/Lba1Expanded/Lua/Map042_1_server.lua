function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(1)
	Spawn_1:SetPosY(3.01)
	Spawn_1:SetPosZ(63)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(50)
	Spawn_2:SetPosY(4.01)
	Spawn_2:SetPosZ(1)
	Spawn_2:SetName("spawning10")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(27)
	Spawn_3:SetPosY(1.01)
	Spawn_3:SetPosZ(51.5)
	Spawn_3:SetName("spawning11")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(7)
	Spawn_4:SetPosY(1.01)
	Spawn_4:SetPosZ(20.5)
	Spawn_4:SetName("spawning12")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(23)
	Spawn_5:SetPosY(5.01)
	Spawn_5:SetPosZ(58)
	Spawn_5:SetName("spawning13")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(5.5)
	Spawn_6:SetPosY(5.01)
	Spawn_6:SetPosZ(8)
	Spawn_6:SetName("spawning14")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(1)
	Spawn_7:SetPosY(3.01)
	Spawn_7:SetPosZ(63)
	Spawn_7:SetName("spawning15")
	environment:AddSpawn(Spawn_7)

	Spawn_8 = Spawn(8)
	Spawn_8:SetPosX(1)
	Spawn_8:SetPosY(3.01)
	Spawn_8:SetPosZ(63)
	Spawn_8:SetName("spawning16")
	environment:AddSpawn(Spawn_8)

	Spawn_9 = Spawn(9)
	Spawn_9:SetPosX(1)
	Spawn_9:SetPosY(3.01)
	Spawn_9:SetPosZ(63)
	Spawn_9:SetName("spawning17")
	environment:AddSpawn(Spawn_9)

	Spawn_10 = Spawn(10)
	Spawn_10:SetPosX(5.5)
	Spawn_10:SetPosY(3.01)
	Spawn_10:SetPosZ(41)
	Spawn_10:SetName("spawning2")
	environment:AddSpawn(Spawn_10)

	Spawn_11 = Spawn(11)
	Spawn_11:SetPosX(1)
	Spawn_11:SetPosY(3.01)
	Spawn_11:SetPosZ(63)
	Spawn_11:SetName("spawning3")
	environment:AddSpawn(Spawn_11)

	Spawn_12 = Spawn(12)
	Spawn_12:SetPosX(1)
	Spawn_12:SetPosY(3.01)
	Spawn_12:SetPosZ(63)
	Spawn_12:SetName("spawning4")
	environment:AddSpawn(Spawn_12)

	Spawn_13 = Spawn(13)
	Spawn_13:SetPosX(27.5)
	Spawn_13:SetPosY(4.01)
	Spawn_13:SetPosZ(11)
	Spawn_13:SetName("spawning5")
	environment:AddSpawn(Spawn_13)

	Spawn_14 = Spawn(14)
	Spawn_14:SetPosX(21.5)
	Spawn_14:SetPosY(1.01)
	Spawn_14:SetPosZ(16)
	Spawn_14:SetName("spawning6")
	environment:AddSpawn(Spawn_14)

	Spawn_15 = Spawn(15)
	Spawn_15:SetPosX(30)
	Spawn_15:SetPosY(13.01)
	Spawn_15:SetPosZ(8)
	Spawn_15:SetName("spawning7")
	environment:AddSpawn(Spawn_15)

	Spawn_16 = Spawn(16)
	Spawn_16:SetPosX(2)
	Spawn_16:SetPosY(5.01)
	Spawn_16:SetPosZ(34)
	Spawn_16:SetName("spawning8")
	environment:AddSpawn(Spawn_16)

	Spawn_17 = Spawn(17)
	Spawn_17:SetPosX(50)
	Spawn_17:SetPosY(4.01)
	Spawn_17:SetPosZ(62)
	Spawn_17:SetName("spawning9")
	environment:AddSpawn(Spawn_17)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map42.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map42.phy"
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

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(1)
	Actor_14.DisplayDesc.ModelId = 0
	Actor_14.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite029.osgb"
	Actor_14.DisplayDesc.Outfit = ""
	Actor_14.DisplayDesc.Weapon = ""
	Actor_14.DisplayDesc.Mode = ""
	Actor_14.DisplayDesc.UseLight = true
	Actor_14.DisplayDesc.CastShadow = false
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
	Actor_14.PhysicDesc.Pos.X = 24
	Actor_14.PhysicDesc.Pos.Y = 4
	Actor_14.PhysicDesc.Pos.Z = 58
	Actor_14.PhysicDesc.Pos.Rotation = 0
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 2
	Actor_14.PhysicDesc.SizeY = 1
	Actor_14.PhysicDesc.SizeZ = 2
	Actor_14.PhysicDesc.Filename = ""
	Actor_14:SetPhysicalActorType(2)
	Actor_14:SetPhysicalShape(2)
	Actor_14.ExtraInfo.Name = ""
	Actor_14.ExtraInfo.NameColorR = 0
	Actor_14.ExtraInfo.NameColorG = 0
	Actor_14.ExtraInfo.NameColorB = 0
	Actor_14.ExtraInfo.Display = false
	Actor_14.LifeInfo.Display = false
	Actor_14H = ActorHandler(Actor_14)
	Actor_14_Sc0 = ASPWaitForSignal(5)
	Actor_14H:AddScriptPart(Actor_14_Sc0)
	Actor_14_Sc1 = ASPGoTo(24,-1,58,0.005)
	Actor_14H:AddScriptPart(Actor_14_Sc1)
	Actor_14_Sc2 = ASPGoTo(24,4,58,0.005)
	Actor_14H:AddScriptPart(Actor_14_Sc2)
	environment:AddActorObject(Actor_14H)

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(3)
	Actor_17.DisplayDesc.ModelId = 0
	Actor_17.DisplayDesc.ModelName = ""
	Actor_17.DisplayDesc.Outfit = ""
	Actor_17.DisplayDesc.Weapon = ""
	Actor_17.DisplayDesc.Mode = ""
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
	Actor_17.PhysicDesc.Pos.X = 49.1875
	Actor_17.PhysicDesc.Pos.Y = 8
	Actor_17.PhysicDesc.Pos.Z = 54.1563
	Actor_17.PhysicDesc.Pos.Rotation = 25
	Actor_17.PhysicDesc.Density = 1
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = -1.07374e+008
	Actor_17.PhysicDesc.SizeY = -1.07374e+008
	Actor_17.PhysicDesc.SizeZ = -1.07374e+008
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
	Actor_18.DisplayDesc.ModelName = "Boat"
	Actor_18.DisplayDesc.Outfit = "FishBoat"
	Actor_18.DisplayDesc.Weapon = "No"
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
	Actor_18.PhysicDesc.Pos.X = 5.90625
	Actor_18.PhysicDesc.Pos.Y = 0
	Actor_18.PhysicDesc.Pos.Z = 60.625
	Actor_18.PhysicDesc.Pos.Rotation = 177
	Actor_18.PhysicDesc.Density = 1
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 3
	Actor_18.PhysicDesc.SizeY = 7
	Actor_18.PhysicDesc.SizeZ = 7
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
	Actor_19.DisplayDesc.ModelName = "Fisherman"
	Actor_19.DisplayDesc.Outfit = "No"
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
	Actor_19.PhysicDesc.Pos.X = 6
	Actor_19.PhysicDesc.Pos.Y = 2
	Actor_19.PhysicDesc.Pos.Z = 42
	Actor_19.PhysicDesc.Pos.Rotation = 365
	Actor_19.PhysicDesc.Density = 1
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = 1
	Actor_19.PhysicDesc.SizeY = 5
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
	Actor_20.DisplayDesc.ModelName = "Rabbibunny"
	Actor_20.DisplayDesc.Outfit = "Orange"
	Actor_20.DisplayDesc.Weapon = "No"
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
	Actor_20.PhysicDesc.Pos.X = 34.2188
	Actor_20.PhysicDesc.Pos.Y = 1
	Actor_20.PhysicDesc.Pos.Z = 9
	Actor_20.PhysicDesc.Pos.Rotation = 25
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
	Actor_21.DisplayDesc.ModelName = "Motorcycle"
	Actor_21.DisplayDesc.Outfit = "No"
	Actor_21.DisplayDesc.Weapon = "No"
	Actor_21.DisplayDesc.Mode = "Normal"
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
	Actor_21.PhysicDesc.Pos.X = 54
	Actor_21.PhysicDesc.Pos.Y = 4
	Actor_21.PhysicDesc.Pos.Z = 57
	Actor_21.PhysicDesc.Pos.Rotation = 0
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 1
	Actor_21.PhysicDesc.SizeY = 4
	Actor_21.PhysicDesc.SizeZ = 3
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
	Actor_21_Sc1 = ASPRotate(0,0.05,false)
	Actor_21H:AddScriptPart(Actor_21_Sc1)
	Actor_21_Sc2 = ASPGoTo(54,4,64,0.005)
	Actor_21H:AddScriptPart(Actor_21_Sc2)
	Actor_21_Sc3 = ASPSendSignal(6,0)
	Actor_21H:AddScriptPart(Actor_21_Sc3)
	environment:AddActorObject(Actor_21H)

	Actor_22 = ActorObjectInfo(22)
	Actor_22:SetRenderType(3)
	Actor_22.DisplayDesc.ModelId = 0
	Actor_22.DisplayDesc.ModelName = "SoldierCar"
	Actor_22.DisplayDesc.Outfit = "Empty"
	Actor_22.DisplayDesc.Weapon = "No"
	Actor_22.DisplayDesc.Mode = "Normal"
	Actor_22.DisplayDesc.UseLight = true
	Actor_22.DisplayDesc.CastShadow = false
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
	Actor_22.PhysicDesc.Pos.X = 53
	Actor_22.PhysicDesc.Pos.Y = 4
	Actor_22.PhysicDesc.Pos.Z = 5
	Actor_22.PhysicDesc.Pos.Rotation = 0
	Actor_22.PhysicDesc.Density = 1
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 2
	Actor_22.PhysicDesc.SizeY = 2
	Actor_22.PhysicDesc.SizeZ = 2.5
	Actor_22.PhysicDesc.Filename = ""
	Actor_22:SetPhysicalActorType(2)
	Actor_22:SetPhysicalShape(2)
	Actor_22.ExtraInfo.Name = ""
	Actor_22.ExtraInfo.NameColorR = 0
	Actor_22.ExtraInfo.NameColorG = 0
	Actor_22.ExtraInfo.NameColorB = 0
	Actor_22.ExtraInfo.Display = false
	Actor_22.LifeInfo.Display = false
	Actor_22H = ActorHandler(Actor_22)
	Actor_22_Sc0 = ASPWaitForSignal(5)
	Actor_22H:AddScriptPart(Actor_22_Sc0)
	Actor_22_Sc1 = ASPRotate(180,0.05,false)
	Actor_22H:AddScriptPart(Actor_22_Sc1)
	Actor_22_Sc2 = ASPGoTo(53,4,0,0.005)
	Actor_22H:AddScriptPart(Actor_22_Sc2)
	Actor_22_Sc3 = ASPSendSignal(6,0)
	Actor_22H:AddScriptPart(Actor_22_Sc3)
	environment:AddActorObject(Actor_22H)

	Actor_23 = ActorObjectInfo(23)
	Actor_23:SetRenderType(3)
	Actor_23.DisplayDesc.ModelId = 0
	Actor_23.DisplayDesc.ModelName = "RabbiClone"
	Actor_23.DisplayDesc.Outfit = "Green"
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
	Actor_23.PhysicDesc.Pos.X = 28
	Actor_23.PhysicDesc.Pos.Y = 1
	Actor_23.PhysicDesc.Pos.Z = 24.1875
	Actor_23.PhysicDesc.Pos.Rotation = 25
	Actor_23.PhysicDesc.Density = 1
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 1
	Actor_23.PhysicDesc.SizeY = 6
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
	Actor_24.DisplayDesc.ModelName = "Quetch"
	Actor_24.DisplayDesc.Outfit = "Salesman"
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
	Actor_24.PhysicDesc.Pos.X = 47
	Actor_24.PhysicDesc.Pos.Y = 4
	Actor_24.PhysicDesc.Pos.Z = 33
	Actor_24.PhysicDesc.Pos.Rotation = 433
	Actor_24.PhysicDesc.Density = 1
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 1
	Actor_24.PhysicDesc.SizeY = 5
	Actor_24.PhysicDesc.SizeZ = 1
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
	Actor_24H_dia_c0 = DialogPart()
	Actor_24H_dia_c0_cond = QuestStartedCondition()
	Actor_24H_dia_c0_cond:SetTextid(-1)
	Actor_24H_dia_c0_cond:SetQuestId(1)
	Actor_24H_dia_c0:Setcondition(Actor_24H_dia_c0_cond)
	Actor_24H_dia_c0:SetResetDialog(false)
	Actor_24H_dia_c0:AddText(653)
	Actor_24H_dia_c0_c0 = DialogPart()
	Actor_24H_dia_c0_c0_act = OpenShopAction()
	Actor_24H_dia_c0_c0_act:SetCurrencyItem(8)
	Actor_24H_dia_c0_c0_act:AddItem(18, 30)
	Actor_24H_dia_c0_c0:SetAction(Actor_24H_dia_c0_c0_act)
	Actor_24H_dia_c0_c0:SetResetDialog(false)
	Actor_24H_dia_c0_c0:AddText(834)
	Actor_24H_dia_c0:AddChild(Actor_24H_dia_c0_c0)
	Actor_24H_dia:AddChild(Actor_24H_dia_c0)
	Actor_24H_dia_c1 = DialogPart()
	Actor_24H_dia_c1:SetResetDialog(false)
	Actor_24H_dia_c1:AddText(0)
	Actor_24H_dia_c1_c0 = DialogPart()
	Actor_24H_dia_c1_c0:SetResetDialog(false)
	Actor_24H_dia_c1_c0:AddText(829)
	Actor_24H_dia_c1:AddChild(Actor_24H_dia_c1_c0)
	Actor_24H_dia:AddChild(Actor_24H_dia_c1)
	Actor_24H:SetRootDialog(Actor_24H_dia)
	Actor_24H:SetNpcName(-1)
	Actor_24H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_24H)

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(3)
	Actor_25.DisplayDesc.ModelId = 0
	Actor_25.DisplayDesc.ModelName = "Grobo"
	Actor_25.DisplayDesc.Outfit = "Baldino"
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
	Actor_25.PhysicDesc.Pos.X = 31
	Actor_25.PhysicDesc.Pos.Y = 1
	Actor_25.PhysicDesc.Pos.Z = 30
	Actor_25.PhysicDesc.Pos.Rotation = 25
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
	Actor_26.PhysicDesc.Pos.X = 32
	Actor_26.PhysicDesc.Pos.Y = 1
	Actor_26.PhysicDesc.Pos.Z = 53
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
	Actor_27.DisplayDesc.ModelName = "Catamaran"
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
	Actor_27.PhysicDesc.Pos.X = 5
	Actor_27.PhysicDesc.Pos.Y = 0
	Actor_27.PhysicDesc.Pos.Z = 60.5469
	Actor_27.PhysicDesc.Pos.Rotation = 177
	Actor_27.PhysicDesc.Density = 1
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 5
	Actor_27.PhysicDesc.SizeY = 1
	Actor_27.PhysicDesc.SizeZ = 5
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
	Actor_28.DisplayDesc.ModelName = "Sphero"
	Actor_28.DisplayDesc.Outfit = "Green"
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
	Actor_28.PhysicDesc.Pos.X = 51.0625
	Actor_28.PhysicDesc.Pos.Y = 14.625
	Actor_28.PhysicDesc.Pos.Z = 32
	Actor_28.PhysicDesc.Pos.Rotation = 433
	Actor_28.PhysicDesc.Density = 1
	Actor_28.PhysicDesc.Collidable = true
	Actor_28.PhysicDesc.SizeX = 1
	Actor_28.PhysicDesc.SizeY = 3
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
	Actor_29.DisplayDesc.ModelName = "Rabbibunny"
	Actor_29.DisplayDesc.Outfit = "Orange"
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
	Actor_29.PhysicDesc.Pos.X = 28
	Actor_29.PhysicDesc.Pos.Y = 20
	Actor_29.PhysicDesc.Pos.Z = 6
	Actor_29.PhysicDesc.Pos.Rotation = 25
	Actor_29.PhysicDesc.Density = 1
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 1
	Actor_29.PhysicDesc.SizeY = 5
	Actor_29.PhysicDesc.SizeZ = 1
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
	Actor_30.DisplayDesc.ModelName = "Object"
	Actor_30.DisplayDesc.Outfit = "MekaPingouin"
	Actor_30.DisplayDesc.Weapon = "No"
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
	Actor_30.PhysicDesc.Pos.X = 0
	Actor_30.PhysicDesc.Pos.Y = -1
	Actor_30.PhysicDesc.Pos.Z = 0
	Actor_30.PhysicDesc.Pos.Rotation = 25
	Actor_30.PhysicDesc.Density = 1
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 0.5
	Actor_30.PhysicDesc.SizeY = 2
	Actor_30.PhysicDesc.SizeZ = 0.6
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
	Actor_31.DisplayDesc.ModelName = "Soldier"
	Actor_31.DisplayDesc.Outfit = "Grass"
	Actor_31.DisplayDesc.Weapon = "rifle"
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
	Actor_31.PhysicDesc.Pos.X = 28.5313
	Actor_31.PhysicDesc.Pos.Y = 1
	Actor_31.PhysicDesc.Pos.Z = 44.0625
	Actor_31.PhysicDesc.Pos.Rotation = 25
	Actor_31.PhysicDesc.Density = 1
	Actor_31.PhysicDesc.Collidable = true
	Actor_31.PhysicDesc.SizeX = 1
	Actor_31.PhysicDesc.SizeY = 5
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
	Actor_32.DisplayDesc.ModelName = "RabbiClone"
	Actor_32.DisplayDesc.Outfit = "Green"
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
	Actor_32.PhysicDesc.Pos.X = 49
	Actor_32.PhysicDesc.Pos.Y = 4
	Actor_32.PhysicDesc.Pos.Z = 12.7188
	Actor_32.PhysicDesc.Pos.Rotation = 281
	Actor_32.PhysicDesc.Density = 1
	Actor_32.PhysicDesc.Collidable = true
	Actor_32.PhysicDesc.SizeX = 1
	Actor_32.PhysicDesc.SizeY = 6
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

	Trigger_1_info = TriggerInfo(1, "exit14", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 4, 3.5, 1, true)
	Trigger_1:SetPosition(27, 4, 9.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map043_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit21", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 5, 6, true)
	Trigger_2:SetPosition(0.5, 5, 34)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map044_1")
	Trigger_2_act1:SetSpawning(2)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit25", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 3, 3, 1, true)
	Trigger_3:SetPosition(62.5, 3, 0.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map047_1")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit26", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 3, 4, true)
	Trigger_4:SetPosition(25.5, 1, 51)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map049_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit27", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 3.5, 4, true)
	Trigger_5:SetPosition(5.5, 1, 20)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map050_1")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit28", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 2, 1.5, 2, true)
	Trigger_6:SetPosition(24, 0, 58)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map051_1")
	Trigger_6_act1:SetSpawning(1)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit30", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 4, 3.5, 1, true)
	Trigger_7:SetPosition(5, 5, 6.5)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map053_1")
	Trigger_7_act1:SetSpawning(1)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "exit33", true, false, false)
	Trigger_8 = ZoneTrigger(Trigger_8_info, 2, 3, 1, true)
	Trigger_8:SetPosition(1, 3, 49.5)
	Trigger_8:SetStayUpdateFrequency(-1)
	Trigger_8_act1 = TeleportAction()
	Trigger_8_act1:SetMapName("Map059_1")
	Trigger_8_act1:SetSpawning(4)
	Trigger_8:SetAction1(Trigger_8_act1)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "exit34", true, false, false)
	Trigger_9 = ZoneTrigger(Trigger_9_info, 2, 3, 1, true)
	Trigger_9:SetPosition(1, 3, 50.5)
	Trigger_9:SetStayUpdateFrequency(-1)
	Trigger_9_act1 = TeleportAction()
	Trigger_9_act1:SetMapName("Map039_1")
	Trigger_9_act1:SetSpawning(6)
	Trigger_9:SetAction1(Trigger_9_act1)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "exit35", true, false, false)
	Trigger_10 = ZoneTrigger(Trigger_10_info, 2, 3, 1, true)
	Trigger_10:SetPosition(1, 3, 51.5)
	Trigger_10:SetStayUpdateFrequency(-1)
	Trigger_10_act1 = TeleportAction()
	Trigger_10_act1:SetMapName("Map024_1")
	Trigger_10_act1:SetSpawning(6)
	Trigger_10:SetAction1(Trigger_10_act1)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "exit36", true, false, false)
	Trigger_11 = ZoneTrigger(Trigger_11_info, 2, 3, 1, true)
	Trigger_11:SetPosition(1, 3, 52.5)
	Trigger_11:SetStayUpdateFrequency(-1)
	Trigger_11_act1 = TeleportAction()
	Trigger_11_act1:SetMapName("Map004_1")
	Trigger_11_act1:SetSpawning(9)
	Trigger_11:SetAction1(Trigger_11_act1)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "exit38", true, false, false)
	Trigger_12 = ZoneTrigger(Trigger_12_info, 3, 3, 1, true)
	Trigger_12:SetPosition(30.5, 13, 4.5)
	Trigger_12:SetStayUpdateFrequency(-1)
	Trigger_12_act1 = TeleportAction()
	Trigger_12_act1:SetMapName("Map043_1")
	Trigger_12_act1:SetSpawning(2)
	Trigger_12:SetAction1(Trigger_12_act1)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "exit43", true, false, false)
	Trigger_13 = ZoneTrigger(Trigger_13_info, 3, 3, 1, true)
	Trigger_13:SetPosition(21.5, 1, 14.5)
	Trigger_13:SetStayUpdateFrequency(-1)
	Trigger_13_act1 = TeleportAction()
	Trigger_13_act1:SetMapName("Map043_1")
	Trigger_13_act1:SetSpawning(3)
	Trigger_13:SetAction1(Trigger_13_act1)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "exit8", true, false, false)
	Trigger_14 = ZoneTrigger(Trigger_14_info, 2, 3.5, 3, true)
	Trigger_14:SetPosition(6, 3, 62.5)
	Trigger_14:SetStayUpdateFrequency(-1)
	Trigger_14_act1 = TeleportAction()
	Trigger_14_act1:SetMapName("Map024_1")
	Trigger_14_act1:SetSpawning(5)
	Trigger_14:SetAction1(Trigger_14_act1)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "exit9", true, false, false)
	Trigger_15 = ZoneTrigger(Trigger_15_info, 3, 3.5, 2, true)
	Trigger_15:SetPosition(8.5, 3, 62)
	Trigger_15:SetStayUpdateFrequency(-1)
	Trigger_15_act1 = TeleportAction()
	Trigger_15_act1:SetMapName("Map006_1")
	Trigger_15_act1:SetSpawning(5)
	Trigger_15:SetAction1(Trigger_15_act1)
	environment:AddTrigger(Trigger_15)

	Trigger_16_info = TriggerInfo(16, "ContainerTri_16", true, false, false)
	Trigger_16 = ZoneActionTrigger(Trigger_16_info, 2.50586, 5.82422, 3.00586, "Normal", "")
	Trigger_16:SetPosition(8.25293, 5, 24.0029)
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
	Trigger_17 = ZoneActionTrigger(Trigger_17_info, 1.99805, 4.99609, 2.99804, "Normal", "")
	Trigger_17:SetPosition(19.999, 1, 29.499)
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

	Trigger_18_info = TriggerInfo(18, "TextTri_18", true, false, false)
	Trigger_18 = ActivationTrigger(Trigger_18_info, 2, "Normal", "")
	Trigger_18:SetPosition(8, 5, 31.8438)
	Trigger_18_act1 = DisplayTextAction()
	Trigger_18_act1:SetTextId(612)
	Trigger_18:SetAction1(Trigger_18_act1)
	Trigger_18:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_18)

	Trigger_19_info = TriggerInfo(19, "TextTri_19", true, false, false)
	Trigger_19 = ActivationTrigger(Trigger_19_info, 2, "Normal", "")
	Trigger_19:SetPosition(27, 1, 46)
	Trigger_19_act1 = DisplayTextAction()
	Trigger_19_act1:SetTextId(613)
	Trigger_19:SetAction1(Trigger_19_act1)
	Trigger_19:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_19)

	Trigger_20_info = TriggerInfo(20, "TextTri_20", true, false, false)
	Trigger_20 = ActivationTrigger(Trigger_20_info, 2, "Normal", "")
	Trigger_20:SetPosition(31.999, 1, 15.3584)
	Trigger_20_act1 = DisplayTextAction()
	Trigger_20_act1:SetTextId(611)
	Trigger_20:SetAction1(Trigger_20_act1)
	Trigger_20:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_20)

	Trigger_21_info = TriggerInfo(21, "TextTri_21", true, false, false)
	Trigger_21 = ActivationTrigger(Trigger_21_info, 2, "Normal", "")
	Trigger_21:SetPosition(25, 4, 12)
	Trigger_21_act1 = DisplayTextAction()
	Trigger_21_act1:SetTextId(614)
	Trigger_21:SetAction1(Trigger_21_act1)
	Trigger_21:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_21)

	Trigger_22_info = TriggerInfo(22, "ContainerTri_22", true, false, false)
	Trigger_22 = ZoneActionTrigger(Trigger_22_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_22:SetPosition(24.999, 5, 38.999)
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
	Trigger_23 = ZoneActionTrigger(Trigger_23_info, 2, 5, 2, "Normal", "")
	Trigger_23:SetPosition(31.5938, 1, 11.625)
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

	Trigger_24_info = TriggerInfo(24, "TextTri_24", true, false, false)
	Trigger_24 = ActivationTrigger(Trigger_24_info, 2, "Normal", "")
	Trigger_24:SetPosition(9, 5, 5.99902)
	Trigger_24_act1 = DisplayTextAction()
	Trigger_24_act1:SetTextId(662)
	Trigger_24:SetAction1(Trigger_24_act1)
	Trigger_24:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_24)

	Trigger_25_info = TriggerInfo(25, "TextTri_25", true, false, false)
	Trigger_25 = ActivationTrigger(Trigger_25_info, 2, "Normal", "")
	Trigger_25:SetPosition(2, 5, 26)
	Trigger_25_act1 = DisplayTextAction()
	Trigger_25_act1:SetTextId(662)
	Trigger_25:SetAction1(Trigger_25_act1)
	Trigger_25:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_25)

	Trigger_26_info = TriggerInfo(26, "ContainerTri_26", true, false, false)
	Trigger_26 = ZoneActionTrigger(Trigger_26_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_26:SetPosition(1.99902, 2, 38.999)
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
	Trigger_27 = ZoneActionTrigger(Trigger_27_info, 1.99805, 5.99609, 2.99804, "Normal", "")
	Trigger_27:SetPosition(46.999, 4, 46.499)
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

	Trigger_28_info = TriggerInfo(28, "FloorSwitchTri_28", true, false, false)
	Trigger_28 = ZoneActionTrigger(Trigger_28_info, 2, 2, 2, "Normal", "")
	Trigger_28:SetPosition(24, 4, 58)
	Trigger_28_act1 = SendSignalAction()
	Trigger_28_act1:SetActorId(14)
	Trigger_28_act1:SetSignal(5)
	Trigger_28:SetAction1(Trigger_28_act1)
	Trigger_28:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_28)

	Trigger_29_info = TriggerInfo(29, "ExitDownTri_29", true, false, false)
	Trigger_29 = ActivationTrigger(Trigger_29_info, 2, "Normal", "")
	Trigger_29:SetPosition(30.5, 13, 7)
	Trigger_29_act1 = ClientScriptAction()
	Trigger_29_act1_cs = TakeExitDownScript()
	Trigger_29_act1_cs:SetExitPositionX(30.5)
	Trigger_29_act1_cs:SetExitPositionY(13)
	Trigger_29_act1_cs:SetExitPositionZ(7)
	Trigger_29_act1_cs:SetExitDirection(180)
	Trigger_29_act1:SetScript(Trigger_29_act1_cs)
	Trigger_29:SetAction1(Trigger_29_act1)
	Trigger_29:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_29)

end
