function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(3.5)
	Spawn_1:SetPosY(16.01)
	Spawn_1:SetPosZ(3)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(61.5)
	Spawn_2:SetPosY(16.01)
	Spawn_2:SetPosZ(3)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(39.4)
	Spawn_3:SetPosY(9.01)
	Spawn_3:SetPosZ(31)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map40.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map40.phy"
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

	Actor_4 = ActorObjectInfo(4)
	Actor_4:SetRenderType(1)
	Actor_4.DisplayDesc.ModelId = 0
	Actor_4.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite014.osgb"
	Actor_4.DisplayDesc.Outfit = ""
	Actor_4.DisplayDesc.Weapon = ""
	Actor_4.DisplayDesc.Mode = ""
	Actor_4.DisplayDesc.UseLight = true
	Actor_4.DisplayDesc.CastShadow = false
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
	Actor_4.PhysicDesc.Pos.X = 4
	Actor_4.PhysicDesc.Pos.Y = 0
	Actor_4.PhysicDesc.Pos.Z = 8
	Actor_4.PhysicDesc.Pos.Rotation = 0
	Actor_4.PhysicDesc.Density = 1
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 2
	Actor_4.PhysicDesc.SizeY = 1
	Actor_4.PhysicDesc.SizeZ = 2
	Actor_4.PhysicDesc.Filename = ""
	Actor_4:SetPhysicalActorType(2)
	Actor_4:SetPhysicalShape(2)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 0
	Actor_4.ExtraInfo.NameColorG = 0
	Actor_4.ExtraInfo.NameColorB = 0
	Actor_4.ExtraInfo.Display = false
	Actor_4.LifeInfo.Display = false
	Actor_4H = ActorHandler(Actor_4)
	Actor_4_Sc0 = ASPWaitForSignal(5)
	Actor_4H:AddScriptPart(Actor_4_Sc0)
	Actor_4_Sc1 = ASPGoTo(4,16,8,0.005)
	Actor_4H:AddScriptPart(Actor_4_Sc1)
	Actor_4_Sc2 = ASPWaitForSignal(5)
	Actor_4H:AddScriptPart(Actor_4_Sc2)
	Actor_4_Sc3 = ASPGoTo(4,0,8,0.005)
	Actor_4H:AddScriptPart(Actor_4_Sc3)
	environment:AddActorObject(Actor_4H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(1)
	Actor_5.DisplayDesc.ModelId = 0
	Actor_5.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite055.osgb"
	Actor_5.DisplayDesc.Outfit = ""
	Actor_5.DisplayDesc.Weapon = ""
	Actor_5.DisplayDesc.Mode = ""
	Actor_5.DisplayDesc.UseLight = true
	Actor_5.DisplayDesc.CastShadow = false
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
	Actor_5.PhysicDesc.Pos.X = 42
	Actor_5.PhysicDesc.Pos.Y = 3
	Actor_5.PhysicDesc.Pos.Z = 30.5
	Actor_5.PhysicDesc.Pos.Rotation = 0
	Actor_5.PhysicDesc.Density = 1
	Actor_5.PhysicDesc.Collidable = false
	Actor_5.PhysicDesc.SizeX = 0.8
	Actor_5.PhysicDesc.SizeY = 3
	Actor_5.PhysicDesc.SizeZ = 0.8
	Actor_5.PhysicDesc.Filename = ""
	Actor_5:SetPhysicalActorType(1)
	Actor_5:SetPhysicalShape(2)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = 0
	Actor_5.ExtraInfo.NameColorG = 0
	Actor_5.ExtraInfo.NameColorB = 0
	Actor_5.ExtraInfo.Display = false
	Actor_5.LifeInfo.Display = false
	Actor_5H = ActorHandler(Actor_5)
	environment:AddActorObject(Actor_5H)

	Actor_6 = ActorObjectInfo(6)
	Actor_6:SetRenderType(1)
	Actor_6.DisplayDesc.ModelId = 0
	Actor_6.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite025.osgb"
	Actor_6.DisplayDesc.Outfit = ""
	Actor_6.DisplayDesc.Weapon = ""
	Actor_6.DisplayDesc.Mode = ""
	Actor_6.DisplayDesc.UseLight = true
	Actor_6.DisplayDesc.CastShadow = false
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
	Actor_6.PhysicDesc.Pos.X = 49.5
	Actor_6.PhysicDesc.Pos.Y = 3
	Actor_6.PhysicDesc.Pos.Z = 15
	Actor_6.PhysicDesc.Pos.Rotation = 0
	Actor_6.PhysicDesc.Density = 1
	Actor_6.PhysicDesc.Collidable = false
	Actor_6.PhysicDesc.SizeX = 0.8
	Actor_6.PhysicDesc.SizeY = 3
	Actor_6.PhysicDesc.SizeZ = 0.8
	Actor_6.PhysicDesc.Filename = ""
	Actor_6:SetPhysicalActorType(1)
	Actor_6:SetPhysicalShape(2)
	Actor_6.ExtraInfo.Name = ""
	Actor_6.ExtraInfo.NameColorR = 0
	Actor_6.ExtraInfo.NameColorG = 0
	Actor_6.ExtraInfo.NameColorB = 0
	Actor_6.ExtraInfo.Display = false
	Actor_6.LifeInfo.Display = false
	Actor_6H = ActorHandler(Actor_6)
	environment:AddActorObject(Actor_6H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(1)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite053.osgb"
	Actor_7.DisplayDesc.Outfit = ""
	Actor_7.DisplayDesc.Weapon = ""
	Actor_7.DisplayDesc.Mode = ""
	Actor_7.DisplayDesc.UseLight = true
	Actor_7.DisplayDesc.CastShadow = false
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
	Actor_7.PhysicDesc.Pos.X = 3
	Actor_7.PhysicDesc.Pos.Y = 0
	Actor_7.PhysicDesc.Pos.Z = 9
	Actor_7.PhysicDesc.Pos.Rotation = 0
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = false
	Actor_7.PhysicDesc.SizeX = 0.8
	Actor_7.PhysicDesc.SizeY = 3
	Actor_7.PhysicDesc.SizeZ = 0.8
	Actor_7.PhysicDesc.Filename = ""
	Actor_7:SetPhysicalActorType(1)
	Actor_7:SetPhysicalShape(2)
	Actor_7.ExtraInfo.Name = ""
	Actor_7.ExtraInfo.NameColorR = 0
	Actor_7.ExtraInfo.NameColorG = 0
	Actor_7.ExtraInfo.NameColorB = 0
	Actor_7.ExtraInfo.Display = false
	Actor_7.LifeInfo.Display = false
	Actor_7H = ActorHandler(Actor_7)
	environment:AddActorObject(Actor_7H)

	Actor_8 = ActorObjectInfo(8)
	Actor_8:SetRenderType(3)
	Actor_8.DisplayDesc.ModelId = 0
	Actor_8.DisplayDesc.ModelName = "Object"
	Actor_8.DisplayDesc.Outfit = "RollingTrap"
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
	Actor_8.PhysicDesc.Pos.X = 2
	Actor_8.PhysicDesc.Pos.Y = 20.875
	Actor_8.PhysicDesc.Pos.Z = 5.48438
	Actor_8.PhysicDesc.Pos.Rotation = 281
	Actor_8.PhysicDesc.Density = 1
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 2
	Actor_8.PhysicDesc.SizeY = 2
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
	Actor_9.DisplayDesc.Outfit = "GunTrap"
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
	Actor_9.PhysicDesc.Pos.X = 35.5938
	Actor_9.PhysicDesc.Pos.Y = 0
	Actor_9.PhysicDesc.Pos.Z = 48.5
	Actor_9.PhysicDesc.Pos.Rotation = 433
	Actor_9.PhysicDesc.Density = 1
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 0.3
	Actor_9.PhysicDesc.SizeY = 0.5
	Actor_9.PhysicDesc.SizeZ = 0.3
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
	Actor_10.DisplayDesc.Outfit = "GunTrap"
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
	Actor_10.PhysicDesc.Pos.X = 38.5938
	Actor_10.PhysicDesc.Pos.Y = 0
	Actor_10.PhysicDesc.Pos.Z = 47.5
	Actor_10.PhysicDesc.Pos.Rotation = 281
	Actor_10.PhysicDesc.Density = 1
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 0.3
	Actor_10.PhysicDesc.SizeY = 0.5
	Actor_10.PhysicDesc.SizeZ = 0.3
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
	Actor_11.DisplayDesc.ModelName = "Object"
	Actor_11.DisplayDesc.Outfit = "GunTrap"
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
	Actor_11.PhysicDesc.Pos.X = 37.5938
	Actor_11.PhysicDesc.Pos.Y = 0
	Actor_11.PhysicDesc.Pos.Z = 51.5
	Actor_11.PhysicDesc.Pos.Rotation = 25
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 0.3
	Actor_11.PhysicDesc.SizeY = 0.5
	Actor_11.PhysicDesc.SizeZ = 0.3
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
	Actor_12.DisplayDesc.ModelName = "Object"
	Actor_12.DisplayDesc.Outfit = "GunTrap"
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
	Actor_12.PhysicDesc.Pos.X = 38.5938
	Actor_12.PhysicDesc.Pos.Y = 0
	Actor_12.PhysicDesc.Pos.Z = 57.5
	Actor_12.PhysicDesc.Pos.Rotation = 325
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 0.3
	Actor_12.PhysicDesc.SizeY = 0.5
	Actor_12.PhysicDesc.SizeZ = 0.3
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
	Actor_13.DisplayDesc.ModelName = "Object"
	Actor_13.DisplayDesc.Outfit = "GunTrap"
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
	Actor_13.PhysicDesc.Pos.X = 43.5938
	Actor_13.PhysicDesc.Pos.Y = 0
	Actor_13.PhysicDesc.Pos.Z = 60.4961
	Actor_13.PhysicDesc.Pos.Rotation = 177
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 0.3
	Actor_13.PhysicDesc.SizeY = 0.5
	Actor_13.PhysicDesc.SizeZ = 0.3
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
	Actor_14.DisplayDesc.ModelName = "Object"
	Actor_14.DisplayDesc.Outfit = "GunTrap"
	Actor_14.DisplayDesc.Weapon = "No"
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
	Actor_14.PhysicDesc.Pos.X = 44.5938
	Actor_14.PhysicDesc.Pos.Y = 0
	Actor_14.PhysicDesc.Pos.Z = 57.5
	Actor_14.PhysicDesc.Pos.Rotation = 25
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 0.3
	Actor_14.PhysicDesc.SizeY = 0.5
	Actor_14.PhysicDesc.SizeZ = 0.3
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
	Actor_15.DisplayDesc.ModelName = "Object"
	Actor_15.DisplayDesc.Outfit = "GunTrap"
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
	Actor_15.PhysicDesc.Pos.X = 48.5938
	Actor_15.PhysicDesc.Pos.Y = 0
	Actor_15.PhysicDesc.Pos.Z = 54.5
	Actor_15.PhysicDesc.Pos.Rotation = 25
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 0.3
	Actor_15.PhysicDesc.SizeY = 0.5
	Actor_15.PhysicDesc.SizeZ = 0.3
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
	Actor_16.DisplayDesc.ModelName = "Object"
	Actor_16.DisplayDesc.Outfit = "GunTrap"
	Actor_16.DisplayDesc.Weapon = "No"
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
	Actor_16.PhysicDesc.Pos.X = 45.5938
	Actor_16.PhysicDesc.Pos.Y = 0
	Actor_16.PhysicDesc.Pos.Z = 47.5
	Actor_16.PhysicDesc.Pos.Rotation = 281
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 0.3
	Actor_16.PhysicDesc.SizeY = 0.5
	Actor_16.PhysicDesc.SizeZ = 0.3
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
	Actor_17.DisplayDesc.ModelName = "Object"
	Actor_17.DisplayDesc.Outfit = "GunTrap"
	Actor_17.DisplayDesc.Weapon = "No"
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
	Actor_17.PhysicDesc.Pos.X = 49.5938
	Actor_17.PhysicDesc.Pos.Y = 0
	Actor_17.PhysicDesc.Pos.Z = 50.5
	Actor_17.PhysicDesc.Pos.Rotation = 433
	Actor_17.PhysicDesc.Density = 1
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 0.3
	Actor_17.PhysicDesc.SizeY = 0.5
	Actor_17.PhysicDesc.SizeZ = 0.3
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
	Actor_18.DisplayDesc.ModelName = "Object"
	Actor_18.DisplayDesc.Outfit = "GunTrap"
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
	Actor_18.PhysicDesc.Pos.X = 48.5938
	Actor_18.PhysicDesc.Pos.Y = 0
	Actor_18.PhysicDesc.Pos.Z = 46.4648
	Actor_18.PhysicDesc.Pos.Rotation = 177
	Actor_18.PhysicDesc.Density = 1
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 0.3
	Actor_18.PhysicDesc.SizeY = 0.5
	Actor_18.PhysicDesc.SizeZ = 0.3
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
	Actor_19.DisplayDesc.ModelName = "SkeletonBu"
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
	Actor_19.PhysicDesc.Pos.X = 43
	Actor_19.PhysicDesc.Pos.Y = 0
	Actor_19.PhysicDesc.Pos.Z = 62
	Actor_19.PhysicDesc.Pos.Rotation = 177
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
	Actor_20.DisplayDesc.ModelName = "Hawk"
	Actor_20.DisplayDesc.Outfit = "Green"
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
	Actor_20.PhysicDesc.Pos.X = 53
	Actor_20.PhysicDesc.Pos.Y = 8
	Actor_20.PhysicDesc.Pos.Z = 49
	Actor_20.PhysicDesc.Pos.Rotation = 265
	Actor_20.PhysicDesc.Density = 1
	Actor_20.PhysicDesc.Collidable = true
	Actor_20.PhysicDesc.SizeX = 1
	Actor_20.PhysicDesc.SizeY = 1
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
	Actor_21.DisplayDesc.ModelName = ""
	Actor_21.DisplayDesc.Outfit = ""
	Actor_21.DisplayDesc.Weapon = ""
	Actor_21.DisplayDesc.Mode = ""
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
	Actor_21.PhysicDesc.Pos.X = 46
	Actor_21.PhysicDesc.Pos.Y = 19
	Actor_21.PhysicDesc.Pos.Z = 2.375
	Actor_21.PhysicDesc.Pos.Rotation = 45
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 1
	Actor_21.PhysicDesc.SizeY = 1
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
	Actor_22.PhysicDesc.Pos.X = 49
	Actor_22.PhysicDesc.Pos.Y = 19
	Actor_22.PhysicDesc.Pos.Z = 2.375
	Actor_22.PhysicDesc.Pos.Rotation = 25
	Actor_22.PhysicDesc.Density = 1
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 1
	Actor_22.PhysicDesc.SizeY = 1
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
	Actor_23.DisplayDesc.ModelName = ""
	Actor_23.DisplayDesc.Outfit = ""
	Actor_23.DisplayDesc.Weapon = ""
	Actor_23.DisplayDesc.Mode = ""
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
	Actor_23.PhysicDesc.Pos.X = 53
	Actor_23.PhysicDesc.Pos.Y = 19
	Actor_23.PhysicDesc.Pos.Z = 2.375
	Actor_23.PhysicDesc.Pos.Rotation = 665
	Actor_23.PhysicDesc.Density = 1
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 1
	Actor_23.PhysicDesc.SizeY = 1
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
	Actor_24.DisplayDesc.ModelName = ""
	Actor_24.DisplayDesc.Outfit = ""
	Actor_24.DisplayDesc.Weapon = ""
	Actor_24.DisplayDesc.Mode = ""
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
	Actor_24.PhysicDesc.Pos.X = 57.125
	Actor_24.PhysicDesc.Pos.Y = 19.25
	Actor_24.PhysicDesc.Pos.Z = 2.59375
	Actor_24.PhysicDesc.Pos.Rotation = 665
	Actor_24.PhysicDesc.Density = 1
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 1
	Actor_24.PhysicDesc.SizeY = 1
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
	Actor_25.DisplayDesc.ModelName = ""
	Actor_25.DisplayDesc.Outfit = ""
	Actor_25.DisplayDesc.Weapon = ""
	Actor_25.DisplayDesc.Mode = ""
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
	Actor_25.PhysicDesc.Pos.X = 57.5
	Actor_25.PhysicDesc.Pos.Y = 19.5
	Actor_25.PhysicDesc.Pos.Z = 2.875
	Actor_25.PhysicDesc.Pos.Rotation = 125
	Actor_25.PhysicDesc.Density = 1
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 1
	Actor_25.PhysicDesc.SizeY = 1
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
	Actor_26.DisplayDesc.ModelName = ""
	Actor_26.DisplayDesc.Outfit = ""
	Actor_26.DisplayDesc.Weapon = ""
	Actor_26.DisplayDesc.Mode = ""
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
	Actor_26.PhysicDesc.Pos.X = 39.5625
	Actor_26.PhysicDesc.Pos.Y = 2.4375
	Actor_26.PhysicDesc.Pos.Z = 15.8438
	Actor_26.PhysicDesc.Pos.Rotation = 281
	Actor_26.PhysicDesc.Density = 1
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 1
	Actor_26.PhysicDesc.SizeY = 1
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
	Actor_27.DisplayDesc.ModelName = "SkeletonBu"
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
	Actor_27.PhysicDesc.Pos.X = 43.3125
	Actor_27.PhysicDesc.Pos.Y = 3.3125
	Actor_27.PhysicDesc.Pos.Z = 27.5
	Actor_27.PhysicDesc.Pos.Rotation = 177
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
	Actor_28.DisplayDesc.ModelName = ""
	Actor_28.DisplayDesc.Outfit = ""
	Actor_28.DisplayDesc.Weapon = ""
	Actor_28.DisplayDesc.Mode = ""
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
	Actor_28.PhysicDesc.Pos.X = 52.0938
	Actor_28.PhysicDesc.Pos.Y = 20
	Actor_28.PhysicDesc.Pos.Z = 1.40625
	Actor_28.PhysicDesc.Pos.Rotation = 50
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
	Actor_29.DisplayDesc.ModelName = "Eyeball"
	Actor_29.DisplayDesc.Outfit = "No"
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
	Actor_29.PhysicDesc.Pos.X = 11
	Actor_29.PhysicDesc.Pos.Y = 0
	Actor_29.PhysicDesc.Pos.Z = 46
	Actor_29.PhysicDesc.Pos.Rotation = 25
	Actor_29.PhysicDesc.Density = 1
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 1
	Actor_29.PhysicDesc.SizeY = 3
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
	Actor_30.DisplayDesc.ModelName = "Eyeball"
	Actor_30.DisplayDesc.Outfit = "No"
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
	Actor_30.PhysicDesc.Pos.X = 13
	Actor_30.PhysicDesc.Pos.Y = 0
	Actor_30.PhysicDesc.Pos.Z = 38
	Actor_30.PhysicDesc.Pos.Rotation = 325
	Actor_30.PhysicDesc.Density = 1
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 1
	Actor_30.PhysicDesc.SizeY = 3
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
	Actor_31.DisplayDesc.ModelName = "Eyeball"
	Actor_31.DisplayDesc.Outfit = "No"
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
	Actor_31.PhysicDesc.Pos.X = 20
	Actor_31.PhysicDesc.Pos.Y = 0
	Actor_31.PhysicDesc.Pos.Z = 43
	Actor_31.PhysicDesc.Pos.Rotation = 415
	Actor_31.PhysicDesc.Density = 1
	Actor_31.PhysicDesc.Collidable = true
	Actor_31.PhysicDesc.SizeX = 1
	Actor_31.PhysicDesc.SizeY = 3
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
	Actor_32.DisplayDesc.ModelName = ""
	Actor_32.DisplayDesc.Outfit = ""
	Actor_32.DisplayDesc.Weapon = ""
	Actor_32.DisplayDesc.Mode = ""
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
	Actor_32.PhysicDesc.Pos.X = 17.8438
	Actor_32.PhysicDesc.Pos.Y = 4.6875
	Actor_32.PhysicDesc.Pos.Z = 35.5625
	Actor_32.PhysicDesc.Pos.Rotation = 25
	Actor_32.PhysicDesc.Density = 1
	Actor_32.PhysicDesc.Collidable = true
	Actor_32.PhysicDesc.SizeX = 1
	Actor_32.PhysicDesc.SizeY = 3
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
	Actor_33.DisplayDesc.ModelName = ""
	Actor_33.DisplayDesc.Outfit = ""
	Actor_33.DisplayDesc.Weapon = ""
	Actor_33.DisplayDesc.Mode = ""
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
	Actor_33.PhysicDesc.Pos.X = 5.0625
	Actor_33.PhysicDesc.Pos.Y = 2.6875
	Actor_33.PhysicDesc.Pos.Z = 41.5625
	Actor_33.PhysicDesc.Pos.Rotation = 281
	Actor_33.PhysicDesc.Density = 1
	Actor_33.PhysicDesc.Collidable = true
	Actor_33.PhysicDesc.SizeX = 1
	Actor_33.PhysicDesc.SizeY = 3
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
	Actor_34.DisplayDesc.ModelName = ""
	Actor_34.DisplayDesc.Outfit = ""
	Actor_34.DisplayDesc.Weapon = ""
	Actor_34.DisplayDesc.Mode = ""
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
	Actor_34.PhysicDesc.Pos.X = 8.90625
	Actor_34.PhysicDesc.Pos.Y = 3.8125
	Actor_34.PhysicDesc.Pos.Z = 34.375
	Actor_34.PhysicDesc.Pos.Rotation = 25
	Actor_34.PhysicDesc.Density = 1
	Actor_34.PhysicDesc.Collidable = true
	Actor_34.PhysicDesc.SizeX = 1
	Actor_34.PhysicDesc.SizeY = 3
	Actor_34.PhysicDesc.SizeZ = 1
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
	Actor_35.DisplayDesc.ModelName = ""
	Actor_35.DisplayDesc.Outfit = ""
	Actor_35.DisplayDesc.Weapon = ""
	Actor_35.DisplayDesc.Mode = ""
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
	Actor_35.PhysicDesc.Pos.X = 5.3125
	Actor_35.PhysicDesc.Pos.Y = 4.4375
	Actor_35.PhysicDesc.Pos.Z = 45.5
	Actor_35.PhysicDesc.Pos.Rotation = 281
	Actor_35.PhysicDesc.Density = 1
	Actor_35.PhysicDesc.Collidable = true
	Actor_35.PhysicDesc.SizeX = 1
	Actor_35.PhysicDesc.SizeY = 3
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
	Actor_36.DisplayDesc.ModelName = ""
	Actor_36.DisplayDesc.Outfit = ""
	Actor_36.DisplayDesc.Weapon = ""
	Actor_36.DisplayDesc.Mode = ""
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
	Actor_36.PhysicDesc.Pos.X = 5.3125
	Actor_36.PhysicDesc.Pos.Y = 2.6875
	Actor_36.PhysicDesc.Pos.Z = 43.5625
	Actor_36.PhysicDesc.Pos.Rotation = 281
	Actor_36.PhysicDesc.Density = 1
	Actor_36.PhysicDesc.Collidable = true
	Actor_36.PhysicDesc.SizeX = 1
	Actor_36.PhysicDesc.SizeY = 3
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
	Actor_37.DisplayDesc.ModelName = ""
	Actor_37.DisplayDesc.Outfit = ""
	Actor_37.DisplayDesc.Weapon = ""
	Actor_37.DisplayDesc.Mode = ""
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
	Actor_37.PhysicDesc.Pos.X = 12
	Actor_37.PhysicDesc.Pos.Y = 2.75
	Actor_37.PhysicDesc.Pos.Z = 35.25
	Actor_37.PhysicDesc.Pos.Rotation = 25
	Actor_37.PhysicDesc.Density = 1
	Actor_37.PhysicDesc.Collidable = true
	Actor_37.PhysicDesc.SizeX = 1
	Actor_37.PhysicDesc.SizeY = 3
	Actor_37.PhysicDesc.SizeZ = 1
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
	Actor_38.DisplayDesc.ModelName = ""
	Actor_38.DisplayDesc.Outfit = ""
	Actor_38.DisplayDesc.Weapon = ""
	Actor_38.DisplayDesc.Mode = ""
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
	Actor_38.PhysicDesc.Pos.X = 14.4688
	Actor_38.PhysicDesc.Pos.Y = 4.4375
	Actor_38.PhysicDesc.Pos.Z = 35.3438
	Actor_38.PhysicDesc.Pos.Rotation = 25
	Actor_38.PhysicDesc.Density = 1
	Actor_38.PhysicDesc.Collidable = true
	Actor_38.PhysicDesc.SizeX = 1
	Actor_38.PhysicDesc.SizeY = 3
	Actor_38.PhysicDesc.SizeZ = 1
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
	Actor_39.DisplayDesc.ModelName = ""
	Actor_39.DisplayDesc.Outfit = ""
	Actor_39.DisplayDesc.Weapon = ""
	Actor_39.DisplayDesc.Mode = ""
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
	Actor_39.PhysicDesc.Pos.X = 5.3125
	Actor_39.PhysicDesc.Pos.Y = 2.6875
	Actor_39.PhysicDesc.Pos.Z = 47.625
	Actor_39.PhysicDesc.Pos.Rotation = 281
	Actor_39.PhysicDesc.Density = 1
	Actor_39.PhysicDesc.Collidable = true
	Actor_39.PhysicDesc.SizeX = 1
	Actor_39.PhysicDesc.SizeY = 3
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
	Actor_40.DisplayDesc.ModelName = ""
	Actor_40.DisplayDesc.Outfit = ""
	Actor_40.DisplayDesc.Weapon = ""
	Actor_40.DisplayDesc.Mode = ""
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
	Actor_40.PhysicDesc.Pos.X = 5.3125
	Actor_40.PhysicDesc.Pos.Y = 4.25
	Actor_40.PhysicDesc.Pos.Z = 49.5
	Actor_40.PhysicDesc.Pos.Rotation = 281
	Actor_40.PhysicDesc.Density = 1
	Actor_40.PhysicDesc.Collidable = true
	Actor_40.PhysicDesc.SizeX = 1
	Actor_40.PhysicDesc.SizeY = 3
	Actor_40.PhysicDesc.SizeZ = 1
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
	Actor_41.DisplayDesc.ModelName = ""
	Actor_41.DisplayDesc.Outfit = ""
	Actor_41.DisplayDesc.Weapon = ""
	Actor_41.DisplayDesc.Mode = ""
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
	Actor_41.PhysicDesc.Pos.X = 34.4688
	Actor_41.PhysicDesc.Pos.Y = 0
	Actor_41.PhysicDesc.Pos.Z = 61.2188
	Actor_41.PhysicDesc.Pos.Rotation = 281
	Actor_41.PhysicDesc.Density = 1
	Actor_41.PhysicDesc.Collidable = true
	Actor_41.PhysicDesc.SizeX = 1
	Actor_41.PhysicDesc.SizeY = 3
	Actor_41.PhysicDesc.SizeZ = 1
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

	Actor_43 = ActorObjectInfo(43)
	Actor_43:SetRenderType(3)
	Actor_43.DisplayDesc.ModelId = 0
	Actor_43.DisplayDesc.ModelName = ""
	Actor_43.DisplayDesc.Outfit = ""
	Actor_43.DisplayDesc.Weapon = ""
	Actor_43.DisplayDesc.Mode = ""
	Actor_43.DisplayDesc.UseLight = true
	Actor_43.DisplayDesc.CastShadow = true
	Actor_43.DisplayDesc.ColorR = 1
	Actor_43.DisplayDesc.ColorG = 1
	Actor_43.DisplayDesc.ColorB = 1
	Actor_43.DisplayDesc.ColorA = 1
	Actor_43.DisplayDesc.TransX = 0
	Actor_43.DisplayDesc.TransY = 0
	Actor_43.DisplayDesc.TransZ = 0
	Actor_43.DisplayDesc.ScaleX = 1
	Actor_43.DisplayDesc.ScaleY = 1
	Actor_43.DisplayDesc.ScaleZ = 1
	Actor_43.DisplayDesc.RotX = 0
	Actor_43.DisplayDesc.RotY = 0
	Actor_43.DisplayDesc.RotZ = 0
	Actor_43:SetModelState(1)
	Actor_43.PhysicDesc.Pos.X = 47
	Actor_43.PhysicDesc.Pos.Y = 5
	Actor_43.PhysicDesc.Pos.Z = 14
	Actor_43.PhysicDesc.Pos.Rotation = 25
	Actor_43.PhysicDesc.Density = 1
	Actor_43.PhysicDesc.Collidable = true
	Actor_43.PhysicDesc.SizeX = 0.5
	Actor_43.PhysicDesc.SizeY = 2
	Actor_43.PhysicDesc.SizeZ = 0.6
	Actor_43.PhysicDesc.Filename = ""
	Actor_43:SetPhysicalActorType(2)
	Actor_43:SetPhysicalShape(2)
	Actor_43.ExtraInfo.Name = ""
	Actor_43.ExtraInfo.NameColorR = 0
	Actor_43.ExtraInfo.NameColorG = 0
	Actor_43.ExtraInfo.NameColorB = 0
	Actor_43.ExtraInfo.Display = false
	Actor_43.LifeInfo.Display = false
	Actor_43H = NPCHandler(Actor_43)
	Actor_43H_dia = DialogPart()
	Actor_43H_dia:SetResetDialog(false)
	Actor_43H:SetRootDialog(Actor_43H_dia)
	Actor_43H:SetNpcName(-1)
	Actor_43H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_43H)

	Trigger_1_info = TriggerInfo(1, "exit24", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 3.5, 1, true)
	Trigger_1:SetPosition(3.5, 16, 1.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map008_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit40", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 3, 1, true)
	Trigger_2:SetPosition(61.5, 16, 1.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map041_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "LadderTri_3", true, false, false)
	Trigger_3 = ActivationTrigger(Trigger_3_info, 1.66667, "Normal", "")
	Trigger_3:SetPosition(39.4688, 0, 44)
	Trigger_3_act1 = ClientScriptAction()
	Trigger_3_act1_cs = GoUpLadderScript()
	Trigger_3_act1_cs:SetLadderPositionX(39.4688)
	Trigger_3_act1_cs:SetLadderPositionY(0)
	Trigger_3_act1_cs:SetLadderPositionZ(44)
	Trigger_3_act1_cs:SetLadderHeight(9.07031)
	Trigger_3_act1_cs:SetLadderDirection(180)
	Trigger_3_act1:SetScript(Trigger_3_act1_cs)
	Trigger_3:SetAction1(Trigger_3_act1)
	Trigger_3:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "ContainerTri_4", true, false, false)
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 2.99804, 5.99609, 2.99804, "Normal", "")
	Trigger_4:SetPosition(36.499, 2, 6.49902)
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

	Trigger_5_info = TriggerInfo(5, "SwitchTri_5", true, false, false)
	Trigger_5 = ActivationTrigger(Trigger_5_info, 2, "Normal", "")
	Trigger_5:SetPosition(42, 3, 30.5)
	Trigger_5_act1 = SwitchAction()
	Trigger_5_act1:SetActorId(5)
	Trigger_5_act1:SetSwitchModel("Worlds/Lba1Original/Sprites/sprite119.osgb")
	Trigger_5:SetAction1(Trigger_5_act1)
	Trigger_5:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "SwitchTri_6", true, false, false)
	Trigger_6 = ActivationTrigger(Trigger_6_info, 2, "Normal", "")
	Trigger_6:SetPosition(49.5, 3, 15)
	Trigger_6_act1 = SwitchAction()
	Trigger_6_act1:SetActorId(6)
	Trigger_6_act1:SetSwitchModel("Worlds/Lba1Original/Sprites/sprite119.osgb")
	Trigger_6:SetAction1(Trigger_6_act1)
	Trigger_6:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "SwitchTri_7", true, false, false)
	Trigger_7 = ActivationTrigger(Trigger_7_info, 2, "Normal", "")
	Trigger_7:SetPosition(3, 0, 9)
	Trigger_7_act1 = SwitchAction()
	Trigger_7_act1:SetActorId(7)
	Trigger_7_act1:SetSwitchModel("Worlds/Lba1Original/Sprites/sprite119.osgb")
	Trigger_7_act1_act1 = SendSignalAction()
	Trigger_7_act1_act1:SetActorId(4)
	Trigger_7_act1_act1:SetSignal(5)
	Trigger_7_act1:SetActionTrue(Trigger_7_act1_act1)
	Trigger_7_act1_act1 = SendSignalAction()
	Trigger_7_act1_act1:SetActorId(4)
	Trigger_7_act1_act1:SetSignal(5)
	Trigger_7_act1:SetActionFalse(Trigger_7_act1_act1)
	Trigger_7:SetAction1(Trigger_7_act1)
	Trigger_7:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_7)

end
