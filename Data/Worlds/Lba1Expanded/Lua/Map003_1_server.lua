function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(21.5)
	Spawn_1:SetPosY(0.01)
	Spawn_1:SetPosZ(53)
	Spawn_1:SetName("spawning")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(32.5)
	Spawn_2:SetPosY(15.01)
	Spawn_2:SetPosZ(2)
	Spawn_2:SetName("spawning1")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(19.5)
	Spawn_3:SetPosY(0.01)
	Spawn_3:SetPosZ(62)
	Spawn_3:SetName("spawning2")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(51)
	Spawn_4:SetPosY(0.01)
	Spawn_4:SetPosZ(62)
	Spawn_4:SetName("spawning3")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(2.5)
	Spawn_5:SetPosY(5.01)
	Spawn_5:SetPosZ(61)
	Spawn_5:SetName("spawning4")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(17)
	Spawn_6:SetPosY(0.01)
	Spawn_6:SetPosZ(41.5)
	Spawn_6:SetName("spawning5")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(37)
	Spawn_7:SetPosY(15.01)
	Spawn_7:SetPosZ(5)
	Spawn_7:SetName("spawning6")
	environment:AddSpawn(Spawn_7)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map3.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map3.phy"
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

	Actor_12 = ActorObjectInfo(12)
	Actor_12:SetRenderType(1)
	Actor_12.DisplayDesc.ModelId = 0
	Actor_12.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite012.osgb"
	Actor_12.DisplayDesc.Outfit = ""
	Actor_12.DisplayDesc.Weapon = ""
	Actor_12.DisplayDesc.Mode = ""
	Actor_12.DisplayDesc.UseLight = true
	Actor_12.DisplayDesc.CastShadow = false
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
	Actor_12.PhysicDesc.Pos.X = 10.5
	Actor_12.PhysicDesc.Pos.Y = 7
	Actor_12.PhysicDesc.Pos.Z = 11.4
	Actor_12.PhysicDesc.Pos.Rotation = 0
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 3.2
	Actor_12.PhysicDesc.SizeY = 8
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
	Actor_12H = DoorHandler(Actor_12,0,1,0,0,false)
	Actor_12_Sc0 = ASPWaitForSignal(1)
	Actor_12H:AddScriptPart(Actor_12_Sc0)
	Actor_12_Sc1 = ASPGoTo(10.5,7,11.4,0)
	Actor_12H:AddScriptPart(Actor_12_Sc1)
	Actor_12_Sc2 = ASPWaitForSignal(2)
	Actor_12H:AddScriptPart(Actor_12_Sc2)
	Actor_12_Sc3 = ASPGoTo(10.5,7,11.4,0)
	Actor_12H:AddScriptPart(Actor_12_Sc3)
	environment:AddActorObject(Actor_12H)

	Actor_13 = ActorObjectInfo(13)
	Actor_13:SetRenderType(1)
	Actor_13.DisplayDesc.ModelId = 0
	Actor_13.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite011.osgb"
	Actor_13.DisplayDesc.Outfit = ""
	Actor_13.DisplayDesc.Weapon = ""
	Actor_13.DisplayDesc.Mode = ""
	Actor_13.DisplayDesc.UseLight = true
	Actor_13.DisplayDesc.CastShadow = false
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
	Actor_13.PhysicDesc.Pos.X = 18.5
	Actor_13.PhysicDesc.Pos.Y = 0
	Actor_13.PhysicDesc.Pos.Z = 28.5
	Actor_13.PhysicDesc.Pos.Rotation = 0
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 1
	Actor_13.PhysicDesc.SizeY = 8
	Actor_13.PhysicDesc.SizeZ = 3.2
	Actor_13.PhysicDesc.Filename = ""
	Actor_13:SetPhysicalActorType(2)
	Actor_13:SetPhysicalShape(2)
	Actor_13.ExtraInfo.Name = ""
	Actor_13.ExtraInfo.NameColorR = 0
	Actor_13.ExtraInfo.NameColorG = 0
	Actor_13.ExtraInfo.NameColorB = 0
	Actor_13.ExtraInfo.Display = false
	Actor_13.LifeInfo.Display = false
	Actor_13H = DoorHandler(Actor_13,0,1,0,0,false)
	Actor_13_Sc0 = ASPWaitForSignal(1)
	Actor_13H:AddScriptPart(Actor_13_Sc0)
	Actor_13_Sc1 = ASPGoTo(18.5,0,28.5,0)
	Actor_13H:AddScriptPart(Actor_13_Sc1)
	Actor_13_Sc2 = ASPWaitForSignal(2)
	Actor_13H:AddScriptPart(Actor_13_Sc2)
	Actor_13_Sc3 = ASPGoTo(18.5,0,28.5,0)
	Actor_13H:AddScriptPart(Actor_13_Sc3)
	environment:AddActorObject(Actor_13H)

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(1)
	Actor_14.DisplayDesc.ModelId = 0
	Actor_14.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite011.osgb"
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
	Actor_14.PhysicDesc.Pos.X = 15.5
	Actor_14.PhysicDesc.Pos.Y = 0
	Actor_14.PhysicDesc.Pos.Z = 41.5
	Actor_14.PhysicDesc.Pos.Rotation = 0
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 1
	Actor_14.PhysicDesc.SizeY = 8
	Actor_14.PhysicDesc.SizeZ = 3.2
	Actor_14.PhysicDesc.Filename = ""
	Actor_14:SetPhysicalActorType(2)
	Actor_14:SetPhysicalShape(2)
	Actor_14.ExtraInfo.Name = ""
	Actor_14.ExtraInfo.NameColorR = 0
	Actor_14.ExtraInfo.NameColorG = 0
	Actor_14.ExtraInfo.NameColorB = 0
	Actor_14.ExtraInfo.Display = false
	Actor_14.LifeInfo.Display = false
	Actor_14H = DoorHandler(Actor_14,0,0,3,0.004,false)
	Actor_14_Sc0 = ASPWaitForSignal(1)
	Actor_14H:AddScriptPart(Actor_14_Sc0)
	Actor_14_Sc1 = ASPGoTo(15.5,0,38.5,0.004)
	Actor_14H:AddScriptPart(Actor_14_Sc1)
	Actor_14_Sc2 = ASPWaitForSignal(2)
	Actor_14H:AddScriptPart(Actor_14_Sc2)
	Actor_14_Sc3 = ASPGoTo(15.5,0,41.5,0.004)
	Actor_14H:AddScriptPart(Actor_14_Sc3)
	environment:AddActorObject(Actor_14H)

	Actor_15 = ActorObjectInfo(15)
	Actor_15:SetRenderType(1)
	Actor_15.DisplayDesc.ModelId = 0
	Actor_15.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite018.osgb"
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
	Actor_15.PhysicDesc.Pos.X = 2.5
	Actor_15.PhysicDesc.Pos.Y = 5
	Actor_15.PhysicDesc.Pos.Z = 63.5
	Actor_15.PhysicDesc.Pos.Rotation = 0
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 3.2
	Actor_15.PhysicDesc.SizeY = 5
	Actor_15.PhysicDesc.SizeZ = 1
	Actor_15.PhysicDesc.Filename = ""
	Actor_15:SetPhysicalActorType(2)
	Actor_15:SetPhysicalShape(2)
	Actor_15.ExtraInfo.Name = ""
	Actor_15.ExtraInfo.NameColorR = 0
	Actor_15.ExtraInfo.NameColorG = 0
	Actor_15.ExtraInfo.NameColorB = 0
	Actor_15.ExtraInfo.Display = false
	Actor_15.LifeInfo.Display = false
	Actor_15H = DoorHandler(Actor_15,0,1,0,0,false)
	Actor_15_Sc0 = ASPWaitForSignal(1)
	Actor_15H:AddScriptPart(Actor_15_Sc0)
	Actor_15_Sc1 = ASPGoTo(2.5,5,63.5,0)
	Actor_15H:AddScriptPart(Actor_15_Sc1)
	Actor_15_Sc2 = ASPWaitForSignal(2)
	Actor_15H:AddScriptPart(Actor_15_Sc2)
	Actor_15_Sc3 = ASPGoTo(2.5,5,63.5,0)
	Actor_15H:AddScriptPart(Actor_15_Sc3)
	environment:AddActorObject(Actor_15H)

	Actor_16 = ActorObjectInfo(16)
	Actor_16:SetRenderType(1)
	Actor_16.DisplayDesc.ModelId = 0
	Actor_16.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite029.osgb"
	Actor_16.DisplayDesc.Outfit = ""
	Actor_16.DisplayDesc.Weapon = ""
	Actor_16.DisplayDesc.Mode = ""
	Actor_16.DisplayDesc.UseLight = true
	Actor_16.DisplayDesc.CastShadow = false
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
	Actor_16.PhysicDesc.Pos.X = 38
	Actor_16.PhysicDesc.Pos.Y = 14
	Actor_16.PhysicDesc.Pos.Z = 7
	Actor_16.PhysicDesc.Pos.Rotation = 0
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 2
	Actor_16.PhysicDesc.SizeY = 1
	Actor_16.PhysicDesc.SizeZ = 2
	Actor_16.PhysicDesc.Filename = ""
	Actor_16:SetPhysicalActorType(2)
	Actor_16:SetPhysicalShape(2)
	Actor_16.ExtraInfo.Name = ""
	Actor_16.ExtraInfo.NameColorR = 0
	Actor_16.ExtraInfo.NameColorG = 0
	Actor_16.ExtraInfo.NameColorB = 0
	Actor_16.ExtraInfo.Display = false
	Actor_16.LifeInfo.Display = false
	Actor_16H = ActorHandler(Actor_16)
	Actor_16_Sc0 = ASPWaitForSignal(5)
	Actor_16H:AddScriptPart(Actor_16_Sc0)
	Actor_16_Sc1 = ASPGoTo(38,5,7,0.005)
	Actor_16H:AddScriptPart(Actor_16_Sc1)
	Actor_16_Sc2 = ASPGoTo(38,14,7,0.005)
	Actor_16H:AddScriptPart(Actor_16_Sc2)
	environment:AddActorObject(Actor_16H)

	Actor_18 = ActorObjectInfo(18)
	Actor_18:SetRenderType(3)
	Actor_18.DisplayDesc.ModelId = 0
	Actor_18.DisplayDesc.ModelName = "GroboClone"
	Actor_18.DisplayDesc.Outfit = "Yellow"
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
	Actor_18.PhysicDesc.Pos.X = 2.78125
	Actor_18.PhysicDesc.Pos.Y = 5
	Actor_18.PhysicDesc.Pos.Z = 57.0352
	Actor_18.PhysicDesc.Pos.Rotation = 165
	Actor_18.PhysicDesc.Density = 1
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 1.5
	Actor_18.PhysicDesc.SizeY = 5
	Actor_18.PhysicDesc.SizeZ = 1.5
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
	Actor_19.DisplayDesc.ModelName = "Robot"
	Actor_19.DisplayDesc.Outfit = "SpheroClosed"
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
	Actor_19.PhysicDesc.Pos.X = 53.6406
	Actor_19.PhysicDesc.Pos.Y = 0
	Actor_19.PhysicDesc.Pos.Z = 8
	Actor_19.PhysicDesc.Pos.Rotation = 25
	Actor_19.PhysicDesc.Density = 1
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = 2
	Actor_19.PhysicDesc.SizeY = 5
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
	Actor_20.DisplayDesc.ModelName = "Grobo"
	Actor_20.DisplayDesc.Outfit = "Baldino"
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
	Actor_20.PhysicDesc.Pos.X = 51
	Actor_20.PhysicDesc.Pos.Y = 0
	Actor_20.PhysicDesc.Pos.Z = 11
	Actor_20.PhysicDesc.Pos.Rotation = 25
	Actor_20.PhysicDesc.Density = 1
	Actor_20.PhysicDesc.Collidable = true
	Actor_20.PhysicDesc.SizeX = 1.5
	Actor_20.PhysicDesc.SizeY = 5
	Actor_20.PhysicDesc.SizeZ = 1.5
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
	Actor_21.DisplayDesc.ModelName = "RabbiClone"
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
	Actor_21.PhysicDesc.Pos.X = 19
	Actor_21.PhysicDesc.Pos.Y = 1
	Actor_21.PhysicDesc.Pos.Z = 49
	Actor_21.PhysicDesc.Pos.Rotation = 25
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 1
	Actor_21.PhysicDesc.SizeY = 6
	Actor_21.PhysicDesc.SizeZ = 1
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
	Actor_22.DisplayDesc.ModelName = "Soldier"
	Actor_22.DisplayDesc.Outfit = "Grass"
	Actor_22.DisplayDesc.Weapon = "rifle"
	Actor_22.DisplayDesc.Mode = "Normal"
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
	Actor_22.PhysicDesc.Pos.X = 2
	Actor_22.PhysicDesc.Pos.Y = 7
	Actor_22.PhysicDesc.Pos.Z = 16
	Actor_22.PhysicDesc.Pos.Rotation = 25
	Actor_22.PhysicDesc.Density = 1
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 1
	Actor_22.PhysicDesc.SizeY = 5
	Actor_22.PhysicDesc.SizeZ = 1
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
	Actor_23.DisplayDesc.ModelName = "Quetch"
	Actor_23.DisplayDesc.Outfit = "Salesman"
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
	Actor_23.PhysicDesc.Pos.X = 12
	Actor_23.PhysicDesc.Pos.Y = 7
	Actor_23.PhysicDesc.Pos.Z = 12.7813
	Actor_23.PhysicDesc.Pos.Rotation = 628
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
	Actor_24.DisplayDesc.ModelName = "Tank"
	Actor_24.DisplayDesc.Outfit = "Grass"
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
	Actor_24.PhysicDesc.Pos.X = 34
	Actor_24.PhysicDesc.Pos.Y = 0
	Actor_24.PhysicDesc.Pos.Z = 40
	Actor_24.PhysicDesc.Pos.Rotation = 25
	Actor_24.PhysicDesc.Density = 1
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 2
	Actor_24.PhysicDesc.SizeY = 5
	Actor_24.PhysicDesc.SizeZ = 4
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
	Actor_25.DisplayDesc.ModelName = "Soldier"
	Actor_25.DisplayDesc.Outfit = "Grass"
	Actor_25.DisplayDesc.Weapon = "rifle"
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
	Actor_25.PhysicDesc.Pos.X = 41
	Actor_25.PhysicDesc.Pos.Y = 7
	Actor_25.PhysicDesc.Pos.Z = 17
	Actor_25.PhysicDesc.Pos.Rotation = 25
	Actor_25.PhysicDesc.Density = 1
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 1
	Actor_25.PhysicDesc.SizeY = 5
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
	Actor_26.DisplayDesc.ModelName = "Rabbibunny"
	Actor_26.DisplayDesc.Outfit = "FemaleOrange"
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
	Actor_26.PhysicDesc.Pos.X = 19.875
	Actor_26.PhysicDesc.Pos.Y = 0
	Actor_26.PhysicDesc.Pos.Z = 32.375
	Actor_26.PhysicDesc.Pos.Rotation = 221
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
	Actor_27.PhysicDesc.Pos.X = 24.4063
	Actor_27.PhysicDesc.Pos.Y = 0
	Actor_27.PhysicDesc.Pos.Z = 20.6563
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
	Actor_28.PhysicDesc.Pos.X = 54.8789
	Actor_28.PhysicDesc.Pos.Y = 0
	Actor_28.PhysicDesc.Pos.Z = 34
	Actor_28.PhysicDesc.Pos.Rotation = 177
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
	Actor_29.PhysicDesc.Pos.X = 19
	Actor_29.PhysicDesc.Pos.Y = 1
	Actor_29.PhysicDesc.Pos.Z = 49
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

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 10, 4, 1, true)
	Trigger_1:SetPosition(32, 15, 0.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map001_1")
	Trigger_1_act1:SetSpawning(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 4, 1, true)
	Trigger_2:SetPosition(2.5, 5, 63.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map002_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 11, 5.5, 1, true)
	Trigger_3:SetPosition(19.5, 0, 63.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map002_1")
	Trigger_3_act1:SetSpawning(4)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit3", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 8, 5.5, 1, true)
	Trigger_4:SetPosition(51, 0, 63.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map002_1")
	Trigger_4_act1:SetSpawning(5)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit4", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 4, 3, true)
	Trigger_5:SetPosition(15.5, 0, 41.5)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map007_1")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit5", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 2, 5, 2, true)
	Trigger_6:SetPosition(20, 0, 50)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map099_1")
	Trigger_6_act1:SetSpawning(2)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit6", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 3, 2.5, 3, true)
	Trigger_7:SetPosition(37.5, 8, 7.5)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map034_1")
	Trigger_7_act1:SetSpawning(2)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "TextTri_8", true, false, false)
	Trigger_8 = ActivationTrigger(Trigger_8_info, 2, "Normal", "")
	Trigger_8:SetPosition(16.999, 0, 19)
	Trigger_8_act1 = DisplayTextAction()
	Trigger_8_act1:SetTextId(140)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "TextTri_9", true, false, false)
	Trigger_9 = ActivationTrigger(Trigger_9_info, 2, "Normal", "")
	Trigger_9:SetPosition(19, 0, 31.999)
	Trigger_9_act1 = DisplayTextAction()
	Trigger_9_act1:SetTextId(158)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "TextTri_10", true, false, false)
	Trigger_10 = ActivationTrigger(Trigger_10_info, 2, "Normal", "")
	Trigger_10:SetPosition(28.999, 0, 19)
	Trigger_10_act1 = DisplayTextAction()
	Trigger_10_act1:SetTextId(139)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "TextTri_11", true, false, false)
	Trigger_11 = ActivationTrigger(Trigger_11_info, 2, "Normal", "")
	Trigger_11:SetPosition(44, 0, 16.999)
	Trigger_11_act1 = DisplayTextAction()
	Trigger_11_act1:SetTextId(140)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "ContainerTri_12", true, false, false)
	Trigger_12 = ZoneActionTrigger(Trigger_12_info, 2.10546, 4.02734, 2.10546, "Normal", "")
	Trigger_12:SetPosition(16.8027, 0, 38.8027)
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
	Trigger_13 = ZoneActionTrigger(Trigger_13_info, 3.5625, 4.9375, 3.59376, "Normal", "")
	Trigger_13:SetPosition(30.2188, 0, 25.2031)
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
	Trigger_14 = ZoneActionTrigger(Trigger_14_info, 2.1582, 4.07031, 2.1582, "Normal", "")
	Trigger_14:SetPosition(44.7979, 0, 10.7979)
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

	Trigger_15_info = TriggerInfo(15, "TextTri_15", true, false, false)
	Trigger_15 = ActivationTrigger(Trigger_15_info, 2, "Normal", "")
	Trigger_15:SetPosition(5, 0, 45.999)
	Trigger_15_act1 = DisplayTextAction()
	Trigger_15_act1:SetTextId(139)
	Trigger_15:SetAction1(Trigger_15_act1)
	Trigger_15:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_15)

	Trigger_16_info = TriggerInfo(16, "TextTri_16", true, false, false)
	Trigger_16 = ActivationTrigger(Trigger_16_info, 2, "Normal", "")
	Trigger_16:SetPosition(25.999, 11, 10.5146)
	Trigger_16_act1 = DisplayTextAction()
	Trigger_16_act1:SetTextId(201)
	Trigger_16:SetAction1(Trigger_16_act1)
	Trigger_16:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_16)

	Trigger_17_info = TriggerInfo(17, "ContainerTri_17", true, false, false)
	Trigger_17 = ZoneActionTrigger(Trigger_17_info, 1.8125, 5.00391, 1.84375, "Normal", "")
	Trigger_17:SetPosition(46.9063, 0, 7.92188)
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

	Trigger_18_info = TriggerInfo(18, "FloorSwitchTri_18", true, false, false)
	Trigger_18 = ZoneActionTrigger(Trigger_18_info, 2, 2, 2, "Normal", "")
	Trigger_18:SetPosition(38, 15, 7)
	Trigger_18_act1 = SendSignalAction()
	Trigger_18_act1:SetActorId(16)
	Trigger_18_act1:SetSignal(5)
	Trigger_18:SetAction1(Trigger_18_act1)
	Trigger_18:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_18)

	Trigger_19_info = TriggerInfo(19, "DoorTri_19", true, false, false)
	Trigger_19 = ZoneTrigger(Trigger_19_info, 0, 0, 0, false)
	Trigger_19:SetPosition(10.5, 7, 11.4)
	Trigger_19:SetStayUpdateFrequency(-1)
	Trigger_19_act1 = OpenDoorAction()
	Trigger_19_act1:SetActorId(12)
	Trigger_19:SetAction1(Trigger_19_act1)
	Trigger_19_act2 = CloseDoorAction()
	Trigger_19_act2:SetActorId(12)
	Trigger_19:SetAction2(Trigger_19_act2)
	environment:AddTrigger(Trigger_19)

	Trigger_20_info = TriggerInfo(20, "DoorTri_20", true, false, false)
	Trigger_20 = ZoneTrigger(Trigger_20_info, 0, 0, 0, false)
	Trigger_20:SetPosition(18.5, 0, 28.5)
	Trigger_20:SetStayUpdateFrequency(-1)
	Trigger_20_act1 = OpenDoorAction()
	Trigger_20_act1:SetActorId(13)
	Trigger_20:SetAction1(Trigger_20_act1)
	Trigger_20_act2 = CloseDoorAction()
	Trigger_20_act2:SetActorId(13)
	Trigger_20:SetAction2(Trigger_20_act2)
	environment:AddTrigger(Trigger_20)

	Trigger_21_info = TriggerInfo(21, "DoorTri_21", true, false, false)
	Trigger_21 = ZoneTrigger(Trigger_21_info, 4, 8, 4, false)
	Trigger_21:SetPosition(15.5, 0, 41.5)
	Trigger_21:SetStayUpdateFrequency(-1)
	Trigger_21_act1 = OpenDoorAction()
	Trigger_21_act1:SetActorId(14)
	Trigger_21:SetAction1(Trigger_21_act1)
	Trigger_21_act2 = CloseDoorAction()
	Trigger_21_act2:SetActorId(14)
	Trigger_21:SetAction2(Trigger_21_act2)
	environment:AddTrigger(Trigger_21)

	Trigger_22_info = TriggerInfo(22, "DoorTri_22", true, false, false)
	Trigger_22 = ZoneTrigger(Trigger_22_info, 4.4, 5, 5, false)
	Trigger_22:SetPosition(2.5, 5, 63.5)
	Trigger_22:SetStayUpdateFrequency(-1)
	Trigger_22_act1 = OpenDoorAction()
	Trigger_22_act1:SetActorId(15)
	Trigger_22:SetAction1(Trigger_22_act1)
	Trigger_22_act2 = CloseDoorAction()
	Trigger_22_act2:SetActorId(15)
	Trigger_22:SetAction2(Trigger_22_act2)
	environment:AddTrigger(Trigger_22)

end
