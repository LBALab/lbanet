function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(34)
	Spawn_1:SetPosY(4.01)
	Spawn_1:SetPosZ(34)
	Spawn_1:SetName("FirstSpawning")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(35)
	Spawn_2:SetPosY(13.01)
	Spawn_2:SetPosZ(12.5)
	Spawn_2:SetName("spawning1")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(11)
	Spawn_3:SetPosY(0.01)
	Spawn_3:SetPosZ(46)
	Spawn_3:SetName("spawning2")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(0.5)
	Spawn_4:SetPosY(-0.99)
	Spawn_4:SetPosZ(0.5)
	Spawn_4:SetName("spawning3")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(0.5)
	Spawn_5:SetPosY(-0.99)
	Spawn_5:SetPosZ(0.5)
	Spawn_5:SetName("spawning4")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(0.5)
	Spawn_6:SetPosY(-0.99)
	Spawn_6:SetPosZ(0.5)
	Spawn_6:SetName("spawning5")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(0.5)
	Spawn_7:SetPosY(-0.99)
	Spawn_7:SetPosZ(0.5)
	Spawn_7:SetName("spawning6")
	environment:AddSpawn(Spawn_7)

	Spawn_8 = Spawn(8)
	Spawn_8:SetPosX(0.5)
	Spawn_8:SetPosY(-0.99)
	Spawn_8:SetPosZ(0.5)
	Spawn_8:SetName("spawning7")
	environment:AddSpawn(Spawn_8)

	Spawn_9 = Spawn(9)
	Spawn_9:SetPosX(0.5)
	Spawn_9:SetPosY(-0.99)
	Spawn_9:SetPosZ(1)
	Spawn_9:SetName("spawning8")
	environment:AddSpawn(Spawn_9)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map0.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map0.phy"
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
	Actor_11:SetRenderType(1)
	Actor_11.DisplayDesc.ModelId = 0
	Actor_11.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite016.osgb"
	Actor_11.DisplayDesc.Outfit = ""
	Actor_11.DisplayDesc.Weapon = ""
	Actor_11.DisplayDesc.Mode = ""
	Actor_11.DisplayDesc.UseLight = true
	Actor_11.DisplayDesc.CastShadow = false
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
	Actor_11.PhysicDesc.Pos.X = 34
	Actor_11.PhysicDesc.Pos.Y = 4
	Actor_11.PhysicDesc.Pos.Z = 31.5
	Actor_11.PhysicDesc.Pos.Rotation = 0
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 4
	Actor_11.PhysicDesc.SizeY = 8
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
	Actor_11H = DoorHandler(Actor_11,0,0,4,0.004,false)
	Actor_11_Sc0 = ASPWaitForSignal(1)
	Actor_11H:AddScriptPart(Actor_11_Sc0)
	Actor_11_Sc1 = ASPGoTo(30,4,31.5,0.004)
	Actor_11H:AddScriptPart(Actor_11_Sc1)
	Actor_11_Sc2 = ASPWaitForSignal(2)
	Actor_11H:AddScriptPart(Actor_11_Sc2)
	Actor_11_Sc3 = ASPGoTo(34,4,31.5,0.004)
	Actor_11H:AddScriptPart(Actor_11_Sc3)
	environment:AddActorObject(Actor_11H)

	Actor_12 = ActorObjectInfo(12)
	Actor_12:SetRenderType(1)
	Actor_12.DisplayDesc.ModelId = 0
	Actor_12.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite016.osgb"
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
	Actor_12.PhysicDesc.Pos.X = 3
	Actor_12.PhysicDesc.Pos.Y = 4
	Actor_12.PhysicDesc.Pos.Z = 45.5
	Actor_12.PhysicDesc.Pos.Rotation = 0
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 4
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
	Actor_12H = DoorHandler(Actor_12,0,0,4,0.004,false)
	Actor_12_Sc0 = ASPWaitForSignal(1)
	Actor_12H:AddScriptPart(Actor_12_Sc0)
	Actor_12_Sc1 = ASPGoTo(-1,4,45.5,0.004)
	Actor_12H:AddScriptPart(Actor_12_Sc1)
	Actor_12_Sc2 = ASPWaitForSignal(2)
	Actor_12H:AddScriptPart(Actor_12_Sc2)
	Actor_12_Sc3 = ASPGoTo(3,4,45.5,0.004)
	Actor_12H:AddScriptPart(Actor_12_Sc3)
	environment:AddActorObject(Actor_12H)

	Actor_13 = ActorObjectInfo(13)
	Actor_13:SetRenderType(1)
	Actor_13.DisplayDesc.ModelId = 0
	Actor_13.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite015.osgb"
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
	Actor_13.PhysicDesc.Pos.X = 44.5
	Actor_13.PhysicDesc.Pos.Y = 4
	Actor_13.PhysicDesc.Pos.Z = 35
	Actor_13.PhysicDesc.Pos.Rotation = 0
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 1
	Actor_13.PhysicDesc.SizeY = 8
	Actor_13.PhysicDesc.SizeZ = 4
	Actor_13.PhysicDesc.Filename = ""
	Actor_13:SetPhysicalActorType(2)
	Actor_13:SetPhysicalShape(2)
	Actor_13.ExtraInfo.Name = ""
	Actor_13.ExtraInfo.NameColorR = 0
	Actor_13.ExtraInfo.NameColorG = 0
	Actor_13.ExtraInfo.NameColorB = 0
	Actor_13.ExtraInfo.Display = false
	Actor_13.LifeInfo.Display = false
	Actor_13H = DoorHandler(Actor_13,0,0,4,0.004,false)
	Actor_13_Sc0 = ASPWaitForSignal(1)
	Actor_13H:AddScriptPart(Actor_13_Sc0)
	Actor_13_Sc1 = ASPGoTo(44.5,4,31,0.004)
	Actor_13H:AddScriptPart(Actor_13_Sc1)
	Actor_13_Sc2 = ASPWaitForSignal(2)
	Actor_13H:AddScriptPart(Actor_13_Sc2)
	Actor_13_Sc3 = ASPGoTo(44.5,4,35,0.004)
	Actor_13H:AddScriptPart(Actor_13_Sc3)
	environment:AddActorObject(Actor_13H)

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(1)
	Actor_14.DisplayDesc.ModelId = 0
	Actor_14.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite017.osgb"
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
	Actor_14.PhysicDesc.Pos.X = 37
	Actor_14.PhysicDesc.Pos.Y = 13
	Actor_14.PhysicDesc.Pos.Z = 11.25
	Actor_14.PhysicDesc.Pos.Rotation = 0
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 1
	Actor_14.PhysicDesc.SizeY = 8
	Actor_14.PhysicDesc.SizeZ = 2.5
	Actor_14.PhysicDesc.Filename = ""
	Actor_14:SetPhysicalActorType(2)
	Actor_14:SetPhysicalShape(2)
	Actor_14.ExtraInfo.Name = ""
	Actor_14.ExtraInfo.NameColorR = 0
	Actor_14.ExtraInfo.NameColorG = 0
	Actor_14.ExtraInfo.NameColorB = 0
	Actor_14.ExtraInfo.Display = false
	Actor_14.LifeInfo.Display = false
	Actor_14H = DoorHandler(Actor_14,1,0,90,0.1,false)
	Actor_14_Sc0 = ASPWaitForSignal(1)
	Actor_14H:AddScriptPart(Actor_14_Sc0)
	Actor_14_Sc1 = ASPRotateFromPoint(90,37,13,10,0.1)
	Actor_14H:AddScriptPart(Actor_14_Sc1)
	Actor_14_Sc2 = ASPWaitForSignal(2)
	Actor_14H:AddScriptPart(Actor_14_Sc2)
	Actor_14_Sc3 = ASPRotateFromPoint(0,37,13,10,0.1)
	Actor_14H:AddScriptPart(Actor_14_Sc3)
	Actor_14_Sc4 = ASPTeleportTo(37,13,11.25)
	Actor_14H:AddScriptPart(Actor_14_Sc4)
	Actor_14_Sc5 = ASPSetRotation(0)
	Actor_14H:AddScriptPart(Actor_14_Sc5)
	environment:AddActorObject(Actor_14H)

	Actor_15 = ActorObjectInfo(15)
	Actor_15:SetRenderType(1)
	Actor_15.DisplayDesc.ModelId = 0
	Actor_15.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite017.osgb"
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
	Actor_15.PhysicDesc.Pos.X = 37
	Actor_15.PhysicDesc.Pos.Y = 13
	Actor_15.PhysicDesc.Pos.Z = 13.75
	Actor_15.PhysicDesc.Pos.Rotation = 0
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 1
	Actor_15.PhysicDesc.SizeY = 8
	Actor_15.PhysicDesc.SizeZ = 2.5
	Actor_15.PhysicDesc.Filename = ""
	Actor_15:SetPhysicalActorType(2)
	Actor_15:SetPhysicalShape(2)
	Actor_15.ExtraInfo.Name = ""
	Actor_15.ExtraInfo.NameColorR = 0
	Actor_15.ExtraInfo.NameColorG = 0
	Actor_15.ExtraInfo.NameColorB = 0
	Actor_15.ExtraInfo.Display = false
	Actor_15.LifeInfo.Display = false
	Actor_15H = DoorHandler(Actor_15,1,1,-90,0.1,false)
	Actor_15_Sc0 = ASPWaitForSignal(1)
	Actor_15H:AddScriptPart(Actor_15_Sc0)
	Actor_15_Sc1 = ASPRotateFromPoint(-90,37,13,15,0.1)
	Actor_15H:AddScriptPart(Actor_15_Sc1)
	Actor_15_Sc2 = ASPWaitForSignal(2)
	Actor_15H:AddScriptPart(Actor_15_Sc2)
	Actor_15_Sc3 = ASPRotateFromPoint(0,37,13,15,0.1)
	Actor_15H:AddScriptPart(Actor_15_Sc3)
	Actor_15_Sc4 = ASPTeleportTo(37,13,13.75)
	Actor_15H:AddScriptPart(Actor_15_Sc4)
	Actor_15_Sc5 = ASPSetRotation(0)
	Actor_15H:AddScriptPart(Actor_15_Sc5)
	environment:AddActorObject(Actor_15H)

	Actor_16 = ActorObjectInfo(16)
	Actor_16:SetRenderType(1)
	Actor_16.DisplayDesc.ModelId = 0
	Actor_16.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite034.osgb"
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
	Actor_16.PhysicDesc.Pos.X = 11
	Actor_16.PhysicDesc.Pos.Y = 0
	Actor_16.PhysicDesc.Pos.Z = 45.4
	Actor_16.PhysicDesc.Pos.Rotation = 0
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 0
	Actor_16.PhysicDesc.SizeY = 0
	Actor_16.PhysicDesc.SizeZ = 0
	Actor_16.PhysicDesc.Filename = ""
	Actor_16:SetPhysicalActorType(2)
	Actor_16:SetPhysicalShape(2)
	Actor_16.ExtraInfo.Name = ""
	Actor_16.ExtraInfo.NameColorR = 0
	Actor_16.ExtraInfo.NameColorG = 0
	Actor_16.ExtraInfo.NameColorB = 0
	Actor_16.ExtraInfo.Display = false
	Actor_16.LifeInfo.Display = false
	Actor_16H = DoorHandler(Actor_16,0,0,2,0.01,false)
	Actor_16_Sc0 = ASPWaitForSignal(1)
	Actor_16H:AddScriptPart(Actor_16_Sc0)
	Actor_16_Sc1 = ASPGoTo(11,0,43.4,0.01)
	Actor_16H:AddScriptPart(Actor_16_Sc1)
	Actor_16_Sc2 = ASPWaitForSignal(2)
	Actor_16H:AddScriptPart(Actor_16_Sc2)
	Actor_16_Sc3 = ASPGoTo(11,0,45.4,0.01)
	Actor_16H:AddScriptPart(Actor_16_Sc3)
	environment:AddActorObject(Actor_16H)

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(1)
	Actor_17.DisplayDesc.ModelId = 0
	Actor_17.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite085.osgb"
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
	Actor_17.PhysicDesc.Pos.X = 22.5
	Actor_17.PhysicDesc.Pos.Y = 4
	Actor_17.PhysicDesc.Pos.Z = 21
	Actor_17.PhysicDesc.Pos.Rotation = 0
	Actor_17.PhysicDesc.Density = 1
	Actor_17.PhysicDesc.Collidable = false
	Actor_17.PhysicDesc.SizeX = 0.8
	Actor_17.PhysicDesc.SizeY = 3
	Actor_17.PhysicDesc.SizeZ = 0.8
	Actor_17.PhysicDesc.Filename = ""
	Actor_17:SetPhysicalActorType(1)
	Actor_17:SetPhysicalShape(2)
	Actor_17.ExtraInfo.Name = ""
	Actor_17.ExtraInfo.NameColorR = 0
	Actor_17.ExtraInfo.NameColorG = 0
	Actor_17.ExtraInfo.NameColorB = 0
	Actor_17.ExtraInfo.Display = false
	Actor_17.LifeInfo.Display = false
	Actor_17H = ActorHandler(Actor_17)
	environment:AddActorObject(Actor_17H)

	Actor_18 = ActorObjectInfo(18)
	Actor_18:SetRenderType(1)
	Actor_18.DisplayDesc.ModelId = 0
	Actor_18.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite016.osgb"
	Actor_18.DisplayDesc.Outfit = ""
	Actor_18.DisplayDesc.Weapon = ""
	Actor_18.DisplayDesc.Mode = ""
	Actor_18.DisplayDesc.UseLight = true
	Actor_18.DisplayDesc.CastShadow = false
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
	Actor_18.PhysicDesc.Pos.X = 20
	Actor_18.PhysicDesc.Pos.Y = 4
	Actor_18.PhysicDesc.Pos.Z = 20.5
	Actor_18.PhysicDesc.Pos.Rotation = 0
	Actor_18.PhysicDesc.Density = 1
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 4
	Actor_18.PhysicDesc.SizeY = 8
	Actor_18.PhysicDesc.SizeZ = 1
	Actor_18.PhysicDesc.Filename = ""
	Actor_18:SetPhysicalActorType(2)
	Actor_18:SetPhysicalShape(2)
	Actor_18.ExtraInfo.Name = ""
	Actor_18.ExtraInfo.NameColorR = 0
	Actor_18.ExtraInfo.NameColorG = 0
	Actor_18.ExtraInfo.NameColorB = 0
	Actor_18.ExtraInfo.Display = false
	Actor_18.LifeInfo.Display = false
	Actor_18H = DoorHandler(Actor_18,0,0,4,0.004,false)
	Actor_18_Sc0 = ASPWaitForSignal(1)
	Actor_18H:AddScriptPart(Actor_18_Sc0)
	Actor_18_Sc1 = ASPGoTo(16,4,20.5,0.004)
	Actor_18H:AddScriptPart(Actor_18_Sc1)
	Actor_18_Sc2 = ASPWaitForSignal(2)
	Actor_18H:AddScriptPart(Actor_18_Sc2)
	Actor_18_Sc3 = ASPGoTo(20,4,20.5,0.004)
	Actor_18H:AddScriptPart(Actor_18_Sc3)
	environment:AddActorObject(Actor_18H)

	Actor_19 = ActorObjectInfo(19)
	Actor_19:SetRenderType(3)
	Actor_19.DisplayDesc.ModelId = 0
	Actor_19.DisplayDesc.ModelName = "Nurse"
	Actor_19.DisplayDesc.Outfit = "Tech"
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
	Actor_19.PhysicDesc.Pos.X = 58.0742
	Actor_19.PhysicDesc.Pos.Y = 9
	Actor_19.PhysicDesc.Pos.Z = 22.75
	Actor_19.PhysicDesc.Pos.Rotation = 25
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
	Actor_20.DisplayDesc.ModelName = "Nurse"
	Actor_20.DisplayDesc.Outfit = "Guard"
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
	Actor_20.PhysicDesc.Pos.X = 46.4063
	Actor_20.PhysicDesc.Pos.Y = 9
	Actor_20.PhysicDesc.Pos.Z = 24.3438
	Actor_20.PhysicDesc.Pos.Rotation = 260
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
	Actor_21.DisplayDesc.ModelName = "Nurse"
	Actor_21.DisplayDesc.Outfit = "Guard"
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
	Actor_21.PhysicDesc.Pos.X = 18
	Actor_21.PhysicDesc.Pos.Y = 4
	Actor_21.PhysicDesc.Pos.Z = 22
	Actor_21.PhysicDesc.Pos.Rotation = 160
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 1
	Actor_21.PhysicDesc.SizeY = 5
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
	Actor_22.DisplayDesc.ModelName = "Nurse"
	Actor_22.DisplayDesc.Outfit = "Guard"
	Actor_22.DisplayDesc.Weapon = "No"
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
	Actor_22.PhysicDesc.Pos.X = 14
	Actor_22.PhysicDesc.Pos.Y = 13
	Actor_22.PhysicDesc.Pos.Z = 5.09375
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
	Actor_23.DisplayDesc.ModelName = "Nurse"
	Actor_23.DisplayDesc.Outfit = "Tech"
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
	Actor_23.PhysicDesc.Pos.X = 20.9063
	Actor_23.PhysicDesc.Pos.Y = 13
	Actor_23.PhysicDesc.Pos.Z = 4
	Actor_23.PhysicDesc.Pos.Rotation = 231
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
	Actor_24.DisplayDesc.ModelName = "Nurse"
	Actor_24.DisplayDesc.Outfit = "Guard"
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
	Actor_24.PhysicDesc.Pos.X = 14.0625
	Actor_24.PhysicDesc.Pos.Y = 4
	Actor_24.PhysicDesc.Pos.Z = 11.2813
	Actor_24.PhysicDesc.Pos.Rotation = 25
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
	Actor_24H:SetRootDialog(Actor_24H_dia)
	Actor_24H:SetNpcName(-1)
	Actor_24H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_24H)

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(3)
	Actor_25.DisplayDesc.ModelId = 0
	Actor_25.DisplayDesc.ModelName = "Nurse"
	Actor_25.DisplayDesc.Outfit = "Guard"
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
	Actor_25.PhysicDesc.Pos.X = 55
	Actor_25.PhysicDesc.Pos.Y = 9
	Actor_25.PhysicDesc.Pos.Z = 25.3438
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
	Actor_26.PhysicDesc.Pos.X = 48
	Actor_26.PhysicDesc.Pos.Y = 11
	Actor_26.PhysicDesc.Pos.Z = 22
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
	Actor_27.DisplayDesc.ModelName = "GroboClone"
	Actor_27.DisplayDesc.Outfit = "SuperGro"
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
	Actor_27.PhysicDesc.Pos.X = 16
	Actor_27.PhysicDesc.Pos.Y = 6
	Actor_27.PhysicDesc.Pos.Z = 22
	Actor_27.PhysicDesc.Pos.Rotation = 96
	Actor_27.PhysicDesc.Density = 1
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 1.5
	Actor_27.PhysicDesc.SizeY = 5
	Actor_27.PhysicDesc.SizeZ = 1.5
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
	Actor_28.DisplayDesc.ModelName = "GroboClone"
	Actor_28.DisplayDesc.Outfit = "SuperGro"
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
	Actor_28.PhysicDesc.Pos.X = 2
	Actor_28.PhysicDesc.Pos.Y = 16
	Actor_28.PhysicDesc.Pos.Z = 8
	Actor_28.PhysicDesc.Pos.Rotation = 139
	Actor_28.PhysicDesc.Density = 1
	Actor_28.PhysicDesc.Collidable = true
	Actor_28.PhysicDesc.SizeX = 1.5
	Actor_28.PhysicDesc.SizeY = 5
	Actor_28.PhysicDesc.SizeZ = 1.5
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
	Actor_29.DisplayDesc.Outfit = "SuperGro"
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
	Actor_29.PhysicDesc.Pos.X = 34
	Actor_29.PhysicDesc.Pos.Y = 15
	Actor_29.PhysicDesc.Pos.Z = 18
	Actor_29.PhysicDesc.Pos.Rotation = 345
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
	Actor_30.DisplayDesc.Outfit = "NurseOutfit"
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
	Actor_30.PhysicDesc.Pos.X = 26.5
	Actor_30.PhysicDesc.Pos.Y = 7.9375
	Actor_30.PhysicDesc.Pos.Z = 7.9375
	Actor_30.PhysicDesc.Pos.Rotation = 265
	Actor_30.PhysicDesc.Density = 1
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 1
	Actor_30.PhysicDesc.SizeY = 3
	Actor_30.PhysicDesc.SizeZ = 0.1
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
	Actor_31.DisplayDesc.ModelName = "GroboClone"
	Actor_31.DisplayDesc.Outfit = "SuperGro"
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
	Actor_31.PhysicDesc.Pos.X = 2
	Actor_31.PhysicDesc.Pos.Y = 4
	Actor_31.PhysicDesc.Pos.Z = 46.875
	Actor_31.PhysicDesc.Pos.Rotation = 177
	Actor_31.PhysicDesc.Density = 1
	Actor_31.PhysicDesc.Collidable = true
	Actor_31.PhysicDesc.SizeX = 1.5
	Actor_31.PhysicDesc.SizeY = 5
	Actor_31.PhysicDesc.SizeZ = 1.5
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
	Actor_32.DisplayDesc.ModelName = "Object"
	Actor_32.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_32.PhysicDesc.Pos.X = 0
	Actor_32.PhysicDesc.Pos.Y = -1
	Actor_32.PhysicDesc.Pos.Z = 0
	Actor_32.PhysicDesc.Pos.Rotation = 25
	Actor_32.PhysicDesc.Density = 1
	Actor_32.PhysicDesc.Collidable = true
	Actor_32.PhysicDesc.SizeX = 0.5
	Actor_32.PhysicDesc.SizeY = 2
	Actor_32.PhysicDesc.SizeZ = 0.6
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

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4, 5, true)
	Trigger_1:SetPosition(37.5, 13, 12.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map001_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit17", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 3, 1, true)
	Trigger_2:SetPosition(11, 0, 43.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map001_1")
	Trigger_2_act1:SetSpawning(2)
	Trigger_2:SetAction1(Trigger_2_act1)
	Trigger_2_act2 = CloseDoorAction()
	Trigger_2_act2:SetActorId(16)
	Trigger_2:SetAction2(Trigger_2_act2)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 2.00196, 7.19141, 2.00196, "Normal", "")
	Trigger_3:SetPosition(9.90723, 4, 7.00098)
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
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 2.00196, 7.00391, 4.2207, "Normal", "")
	Trigger_4:SetPosition(30.001, 4, 7.04785)
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

	Trigger_5_info = TriggerInfo(5, "ContainerTri_5", true, false, false)
	Trigger_5 = ZoneActionTrigger(Trigger_5_info, 2.00196, 7.06641, 4.0957, "Normal", "")
	Trigger_5:SetPosition(34.001, 4, 7.11035)
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
	Trigger_6 = ZoneActionTrigger(Trigger_6_info, 3.99804, 3.99609, 2.99804, "Normal", "")
	Trigger_6:SetPosition(11.999, 4, 22.499)
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
	Trigger_7 = ZoneActionTrigger(Trigger_7_info, 1.99805, 3.99609, 2.99804, "Normal", "")
	Trigger_7:SetPosition(4.99902, 4, 27.499)
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
	Trigger_8 = ZoneActionTrigger(Trigger_8_info, 2.0039, 7.00781, 4.1914, "Normal", "")
	Trigger_8:SetPosition(32.002, 4, 7.06445)
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

	Trigger_9_info = TriggerInfo(9, "ContainerTri_9", true, false, false)
	Trigger_9 = ZoneActionTrigger(Trigger_9_info, 1.99805, 3.99609, 0.998046, "Normal", "")
	Trigger_9:SetPosition(7.99902, 0, 46.499)
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

	Trigger_10_info = TriggerInfo(10, "ExitDownTri_10", true, false, false)
	Trigger_10 = ActivationTrigger(Trigger_10_info, 2, "Normal", "")
	Trigger_10:SetPosition(11, 0, 46.0001)
	Trigger_10_act1 = MultiAction()
	Trigger_10_act1_act0 = OpenDoorAction()
	Trigger_10_act1_act0:SetActorId(16)
	Trigger_10_act1:AddAction(Trigger_10_act1_act0)
	Trigger_10_act1_act1 = ClientScriptAction()
	Trigger_10_act1_act1_cs = TakeExitDownScript()
	Trigger_10_act1_act1_cs:SetExitPositionX(11)
	Trigger_10_act1_act1_cs:SetExitPositionY(0)
	Trigger_10_act1_act1_cs:SetExitPositionZ(46.0001)
	Trigger_10_act1_act1_cs:SetExitDirection(180)
	Trigger_10_act1_act1:SetScript(Trigger_10_act1_act1_cs)
	Trigger_10_act1:AddAction(Trigger_10_act1_act1)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "SwitchTri_11", true, false, false)
	Trigger_11 = ActivationTrigger(Trigger_11_info, 2, "Normal", "")
	Trigger_11:SetPosition(22.5, 4, 21)
	Trigger_11_act1 = SwitchAction()
	Trigger_11_act1:SetActorId(17)
	Trigger_11_act1:SetSwitchModel("Worlds/Lba1Original/Sprites/sprite086.osgb")
	Trigger_11_act1_act1 = SendSignalAction()
	Trigger_11_act1_act1:SetActorId(18)
	Trigger_11_act1_act1:SetSignal(4)
	Trigger_11_act1:SetActionTrue(Trigger_11_act1_act1)
	Trigger_11_act1_act1 = SendSignalAction()
	Trigger_11_act1_act1:SetActorId(18)
	Trigger_11_act1_act1:SetSignal(4)
	Trigger_11_act1:SetActionFalse(Trigger_11_act1_act1)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "DoorTri_12", true, false, false)
	Trigger_12 = ZoneTrigger(Trigger_12_info, 5, 8, 4, false)
	Trigger_12:SetPosition(34, 4, 31.5)
	Trigger_12:SetStayUpdateFrequency(-1)
	Trigger_12_act1 = OpenDoorAction()
	Trigger_12_act1:SetActorId(11)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12_act2 = CloseDoorAction()
	Trigger_12_act2:SetActorId(11)
	Trigger_12:SetAction2(Trigger_12_act2)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "DoorTri_13", true, false, false)
	Trigger_13 = ZoneTrigger(Trigger_13_info, 4.8, 8, 4, false)
	Trigger_13:SetPosition(3, 4, 45.5)
	Trigger_13:SetStayUpdateFrequency(-1)
	Trigger_13_act1 = OpenDoorAction()
	Trigger_13_act1:SetActorId(12)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13_act2 = CloseDoorAction()
	Trigger_13_act2:SetActorId(12)
	Trigger_13:SetAction2(Trigger_13_act2)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "DoorTri_14", true, false, false)
	Trigger_14 = ZoneTrigger(Trigger_14_info, 4, 8, 5, false)
	Trigger_14:SetPosition(44.5, 4, 35)
	Trigger_14:SetStayUpdateFrequency(-1)
	Trigger_14_act1 = OpenDoorAction()
	Trigger_14_act1:SetActorId(13)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14_act2 = CloseDoorAction()
	Trigger_14_act2:SetActorId(13)
	Trigger_14:SetAction2(Trigger_14_act2)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "DoorTri_15", true, false, false)
	Trigger_15 = ZoneTrigger(Trigger_15_info, 4, 8, 5, false)
	Trigger_15:SetPosition(37, 13, 12.5)
	Trigger_15:SetStayUpdateFrequency(-1)
	Trigger_15_act1 = MultiAction()
	Trigger_15_act1_act0 = OpenDoorAction()
	Trigger_15_act1_act0:SetActorId(14)
	Trigger_15_act1:AddAction(Trigger_15_act1_act0)
	Trigger_15_act1_act1 = OpenDoorAction()
	Trigger_15_act1_act1:SetActorId(15)
	Trigger_15_act1:AddAction(Trigger_15_act1_act1)
	Trigger_15:SetAction1(Trigger_15_act1)
	Trigger_15_act2 = MultiAction()
	Trigger_15_act2_act0 = CloseDoorAction()
	Trigger_15_act2_act0:SetActorId(14)
	Trigger_15_act2:AddAction(Trigger_15_act2_act0)
	Trigger_15_act2_act1 = CloseDoorAction()
	Trigger_15_act2_act1:SetActorId(15)
	Trigger_15_act2:AddAction(Trigger_15_act2_act1)
	Trigger_15:SetAction2(Trigger_15_act2)
	environment:AddTrigger(Trigger_15)

	Trigger_17_info = TriggerInfo(17, "DoorTri_17", true, false, false)
	Trigger_17 = ZoneTrigger(Trigger_17_info, 0, 0, 0, false)
	Trigger_17:SetPosition(11, 0, 45.4)
	Trigger_17:SetStayUpdateFrequency(-1)
	Trigger_17_act1 = OpenDoorAction()
	Trigger_17_act1:SetActorId(16)
	Trigger_17:SetAction1(Trigger_17_act1)
	Trigger_17_act2 = CloseDoorAction()
	Trigger_17_act2:SetActorId(16)
	Trigger_17:SetAction2(Trigger_17_act2)
	environment:AddTrigger(Trigger_17)

	Trigger_18_info = TriggerInfo(18, "DoorTri_18", true, false, false)
	Trigger_18 = ZoneTrigger(Trigger_18_info, 0, 0, 0, false)
	Trigger_18:SetPosition(20, 4, 20.5)
	Trigger_18:SetStayUpdateFrequency(-1)
	Trigger_18_act1 = OpenDoorAction()
	Trigger_18_act1:SetActorId(18)
	Trigger_18:SetAction1(Trigger_18_act1)
	Trigger_18_act2 = CloseDoorAction()
	Trigger_18_act2:SetActorId(18)
	Trigger_18:SetAction2(Trigger_18_act2)
	environment:AddTrigger(Trigger_18)

end
