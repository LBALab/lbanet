function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(511)
	Spawn_1:SetPosY(11.3)
	Spawn_1:SetPosZ(452)
	Spawn_1:SetName("Teleport")
	environment:AddSpawn(Spawn_1)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = false
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 3.60134e-043
	Actor_1.DisplayDesc.ColorG = 0
	Actor_1.DisplayDesc.ColorB = 0
	Actor_1.DisplayDesc.ColorA = 1.4013e-045
	Actor_1:SetModelState(1)
	Actor_1.PhysicDesc.Pos.X = 0
	Actor_1.PhysicDesc.Pos.Y = 0
	Actor_1.PhysicDesc.Pos.Z = 0
	Actor_1.PhysicDesc.Pos.Rotation = 0
	Actor_1.PhysicDesc.Density = 0
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 0
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 0
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = 0
	Actor_1.ExtraInfo.NameColorG = 0
	Actor_1.ExtraInfo.NameColorB = 0
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Actor_2 = ActorObjectInfo(2)
	Actor_2:SetRenderType(1)
	Actor_2.DisplayDesc.ModelId = 0
	Actor_2.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_1.osgb"
	Actor_2.DisplayDesc.Outfit = ""
	Actor_2.DisplayDesc.Weapon = ""
	Actor_2.DisplayDesc.Mode = ""
	Actor_2.DisplayDesc.UseLight = false
	Actor_2.DisplayDesc.CastShadow = false
	Actor_2.DisplayDesc.ColorR = 1.4013e-045
	Actor_2.DisplayDesc.ColorG = 0
	Actor_2.DisplayDesc.ColorB = 0
	Actor_2.DisplayDesc.ColorA = 0
	Actor_2:SetModelState(1)
	Actor_2.PhysicDesc.Pos.X = 439.021
	Actor_2.PhysicDesc.Pos.Y = 15.7422
	Actor_2.PhysicDesc.Pos.Z = 453
	Actor_2.PhysicDesc.Pos.Rotation = -90
	Actor_2.PhysicDesc.Density = 4.86642e-023
	Actor_2.PhysicDesc.Collidable = true
	Actor_2.PhysicDesc.SizeX = 0
	Actor_2.PhysicDesc.SizeY = 0
	Actor_2.PhysicDesc.SizeZ = 0
	Actor_2.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_1.phy"
	Actor_2:SetPhysicalActorType(1)
	Actor_2:SetPhysicalShape(5)
	Actor_2.ExtraInfo.Name = ""
	Actor_2.ExtraInfo.NameColorR = 3.14239e-024
	Actor_2.ExtraInfo.NameColorG = 0
	Actor_2.ExtraInfo.NameColorB = 0
	Actor_2H = ActorHandler(Actor_2)
	environment:AddActorObject(Actor_2H)

	Actor_3 = ActorObjectInfo(3)
	Actor_3:SetRenderType(1)
	Actor_3.DisplayDesc.ModelId = 0
	Actor_3.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_2.osgb"
	Actor_3.DisplayDesc.Outfit = ""
	Actor_3.DisplayDesc.Weapon = ""
	Actor_3.DisplayDesc.Mode = ""
	Actor_3.DisplayDesc.UseLight = false
	Actor_3.DisplayDesc.CastShadow = false
	Actor_3.DisplayDesc.ColorR = 1
	Actor_3.DisplayDesc.ColorG = 0
	Actor_3.DisplayDesc.ColorB = 0
	Actor_3.DisplayDesc.ColorA = 1
	Actor_3:SetModelState(1)
	Actor_3.PhysicDesc.Pos.X = 439.021
	Actor_3.PhysicDesc.Pos.Y = 15.7422
	Actor_3.PhysicDesc.Pos.Z = 453
	Actor_3.PhysicDesc.Pos.Rotation = -90
	Actor_3.PhysicDesc.Density = 1.4013e-045
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = 0
	Actor_3.PhysicDesc.SizeY = 0
	Actor_3.PhysicDesc.SizeZ = 0
	Actor_3.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_2.phy"
	Actor_3:SetPhysicalActorType(1)
	Actor_3:SetPhysicalShape(5)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 6.6651e+028
	Actor_3.ExtraInfo.NameColorG = 1.80976e+031
	Actor_3.ExtraInfo.NameColorB = 2.60903e+020
	Actor_3H = ActorHandler(Actor_3)
	environment:AddActorObject(Actor_3H)

	Actor_4 = ActorObjectInfo(4)
	Actor_4:SetRenderType(1)
	Actor_4.DisplayDesc.ModelId = 0
	Actor_4.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_3.osgb"
	Actor_4.DisplayDesc.Outfit = ""
	Actor_4.DisplayDesc.Weapon = ""
	Actor_4.DisplayDesc.Mode = ""
	Actor_4.DisplayDesc.UseLight = false
	Actor_4.DisplayDesc.CastShadow = false
	Actor_4.DisplayDesc.ColorR = 7.90601
	Actor_4.DisplayDesc.ColorG = 0.875
	Actor_4.DisplayDesc.ColorB = 7.6875
	Actor_4.DisplayDesc.ColorA = 0.875
	Actor_4:SetModelState(1)
	Actor_4.PhysicDesc.Pos.X = 439.021
	Actor_4.PhysicDesc.Pos.Y = 15.7422
	Actor_4.PhysicDesc.Pos.Z = 453
	Actor_4.PhysicDesc.Pos.Rotation = -90
	Actor_4.PhysicDesc.Density = 6.93408
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 6.93408
	Actor_4.PhysicDesc.SizeY = 10.0852
	Actor_4.PhysicDesc.SizeZ = 6.93408
	Actor_4.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_3.phy"
	Actor_4:SetPhysicalActorType(1)
	Actor_4:SetPhysicalShape(5)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 2.55796e-035
	Actor_4.ExtraInfo.NameColorG = 1.31224e-038
	Actor_4.ExtraInfo.NameColorB = 0
	Actor_4H = ActorHandler(Actor_4)
	environment:AddActorObject(Actor_4H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(1)
	Actor_5.DisplayDesc.ModelId = 131077
	Actor_5.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_4.osgb"
	Actor_5.DisplayDesc.Outfit = ""
	Actor_5.DisplayDesc.Weapon = ""
	Actor_5.DisplayDesc.Mode = ""
	Actor_5.DisplayDesc.UseLight = false
	Actor_5.DisplayDesc.CastShadow = false
	Actor_5.DisplayDesc.ColorR = 2.10195e-044
	Actor_5.DisplayDesc.ColorG = 1.4013e-045
	Actor_5.DisplayDesc.ColorB = 0
	Actor_5.DisplayDesc.ColorA = 3.12503e-024
	Actor_5:SetModelState(1)
	Actor_5.PhysicDesc.Pos.X = 451
	Actor_5.PhysicDesc.Pos.Y = 9.375
	Actor_5.PhysicDesc.Pos.Z = 432
	Actor_5.PhysicDesc.Pos.Rotation = -90
	Actor_5.PhysicDesc.Density = -4.33984
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = -0
	Actor_5.PhysicDesc.SizeY = 4.33984
	Actor_5.PhysicDesc.SizeZ = 5.38086
	Actor_5.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_4.phy"
	Actor_5:SetPhysicalActorType(1)
	Actor_5:SetPhysicalShape(5)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = -1.40442
	Actor_5.ExtraInfo.NameColorG = 0
	Actor_5.ExtraInfo.NameColorB = 0
	Actor_5H = ActorHandler(Actor_5)
	environment:AddActorObject(Actor_5H)

	Actor_6 = ActorObjectInfo(6)
	Actor_6:SetRenderType(1)
	Actor_6.DisplayDesc.ModelId = 0
	Actor_6.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_5.osgb"
	Actor_6.DisplayDesc.Outfit = ""
	Actor_6.DisplayDesc.Weapon = ""
	Actor_6.DisplayDesc.Mode = ""
	Actor_6.DisplayDesc.UseLight = false
	Actor_6.DisplayDesc.CastShadow = false
	Actor_6.DisplayDesc.ColorR = 0
	Actor_6.DisplayDesc.ColorG = -0
	Actor_6.DisplayDesc.ColorB = 0
	Actor_6.DisplayDesc.ColorA = 0
	Actor_6:SetModelState(1)
	Actor_6.PhysicDesc.Pos.X = 451
	Actor_6.PhysicDesc.Pos.Y = 9.375
	Actor_6.PhysicDesc.Pos.Z = 432
	Actor_6.PhysicDesc.Pos.Rotation = -90
	Actor_6.PhysicDesc.Density = -0.337891
	Actor_6.PhysicDesc.Collidable = true
	Actor_6.PhysicDesc.SizeX = 0
	Actor_6.PhysicDesc.SizeY = 0
	Actor_6.PhysicDesc.SizeZ = 1.28579e-039
	Actor_6.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_5.phy"
	Actor_6:SetPhysicalActorType(1)
	Actor_6:SetPhysicalShape(5)
	Actor_6.ExtraInfo.Name = ""
	Actor_6.ExtraInfo.NameColorR = 1
	Actor_6.ExtraInfo.NameColorG = 1
	Actor_6.ExtraInfo.NameColorB = 1
	Actor_6H = ActorHandler(Actor_6)
	environment:AddActorObject(Actor_6H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(1)
	Actor_7.DisplayDesc.ModelId = 131074
	Actor_7.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_6.osgb"
	Actor_7.DisplayDesc.Outfit = ""
	Actor_7.DisplayDesc.Weapon = ""
	Actor_7.DisplayDesc.Mode = ""
	Actor_7.DisplayDesc.UseLight = false
	Actor_7.DisplayDesc.CastShadow = true
	Actor_7.DisplayDesc.ColorR = 0
	Actor_7.DisplayDesc.ColorG = 0
	Actor_7.DisplayDesc.ColorB = 0
	Actor_7.DisplayDesc.ColorA = 0
	Actor_7:SetModelState(1)
	Actor_7.PhysicDesc.Pos.X = 451
	Actor_7.PhysicDesc.Pos.Y = 9.375
	Actor_7.PhysicDesc.Pos.Z = 432
	Actor_7.PhysicDesc.Pos.Rotation = -90
	Actor_7.PhysicDesc.Density = 0
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 1.05442e-030
	Actor_7.PhysicDesc.SizeY = 4.71008e-033
	Actor_7.PhysicDesc.SizeZ = 1.09191e+027
	Actor_7.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_6.phy"
	Actor_7:SetPhysicalActorType(1)
	Actor_7:SetPhysicalShape(5)
	Actor_7.ExtraInfo.Name = ""
	Actor_7.ExtraInfo.NameColorR = 0
	Actor_7.ExtraInfo.NameColorG = 0
	Actor_7.ExtraInfo.NameColorB = 0
	Actor_7H = ActorHandler(Actor_7)
	environment:AddActorObject(Actor_7H)

	Actor_8 = ActorObjectInfo(8)
	Actor_8:SetRenderType(1)
	Actor_8.DisplayDesc.ModelId = 1065353216
	Actor_8.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_7.osgb"
	Actor_8.DisplayDesc.Outfit = ""
	Actor_8.DisplayDesc.Weapon = ""
	Actor_8.DisplayDesc.Mode = ""
	Actor_8.DisplayDesc.UseLight = false
	Actor_8.DisplayDesc.CastShadow = false
	Actor_8.DisplayDesc.ColorR = 1
	Actor_8.DisplayDesc.ColorG = 1
	Actor_8.DisplayDesc.ColorB = 1
	Actor_8.DisplayDesc.ColorA = 1
	Actor_8:SetModelState(1)
	Actor_8.PhysicDesc.Pos.X = 462
	Actor_8.PhysicDesc.Pos.Y = 1.95313
	Actor_8.PhysicDesc.Pos.Z = 458
	Actor_8.PhysicDesc.Pos.Rotation = -90
	Actor_8.PhysicDesc.Density = 1
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 1
	Actor_8.PhysicDesc.SizeY = 1
	Actor_8.PhysicDesc.SizeZ = 1
	Actor_8.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_7.phy"
	Actor_8:SetPhysicalActorType(1)
	Actor_8:SetPhysicalShape(5)
	Actor_8.ExtraInfo.Name = ""
	Actor_8.ExtraInfo.NameColorR = 1
	Actor_8.ExtraInfo.NameColorG = 1
	Actor_8.ExtraInfo.NameColorB = 1
	Actor_8H = ActorHandler(Actor_8)
	environment:AddActorObject(Actor_8H)

	Actor_9 = ActorObjectInfo(9)
	Actor_9:SetRenderType(1)
	Actor_9.DisplayDesc.ModelId = 0
	Actor_9.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_8.osgb"
	Actor_9.DisplayDesc.Outfit = ""
	Actor_9.DisplayDesc.Weapon = ""
	Actor_9.DisplayDesc.Mode = ""
	Actor_9.DisplayDesc.UseLight = false
	Actor_9.DisplayDesc.CastShadow = true
	Actor_9.DisplayDesc.ColorR = 0
	Actor_9.DisplayDesc.ColorG = 9.21956e-041
	Actor_9.DisplayDesc.ColorB = 2.80529e-024
	Actor_9.DisplayDesc.ColorA = 0
	Actor_9:SetModelState(1)
	Actor_9.PhysicDesc.Pos.X = 462
	Actor_9.PhysicDesc.Pos.Y = 1.95313
	Actor_9.PhysicDesc.Pos.Z = 458
	Actor_9.PhysicDesc.Pos.Rotation = -90
	Actor_9.PhysicDesc.Density = 0
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 0
	Actor_9.PhysicDesc.SizeY = 0
	Actor_9.PhysicDesc.SizeZ = 0
	Actor_9.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_8.phy"
	Actor_9:SetPhysicalActorType(1)
	Actor_9:SetPhysicalShape(5)
	Actor_9.ExtraInfo.Name = ""
	Actor_9.ExtraInfo.NameColorR = 2.8053e-024
	Actor_9.ExtraInfo.NameColorG = -0.787872
	Actor_9.ExtraInfo.NameColorB = 0.420198
	Actor_9H = ActorHandler(Actor_9)
	environment:AddActorObject(Actor_9H)

	Actor_10 = ActorObjectInfo(10)
	Actor_10:SetRenderType(1)
	Actor_10.DisplayDesc.ModelId = 0
	Actor_10.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_9.osgb"
	Actor_10.DisplayDesc.Outfit = ""
	Actor_10.DisplayDesc.Weapon = ""
	Actor_10.DisplayDesc.Mode = ""
	Actor_10.DisplayDesc.UseLight = false
	Actor_10.DisplayDesc.CastShadow = false
	Actor_10.DisplayDesc.ColorR = 1.4013e-045
	Actor_10.DisplayDesc.ColorG = 0
	Actor_10.DisplayDesc.ColorB = 0
	Actor_10.DisplayDesc.ColorA = 0
	Actor_10:SetModelState(1)
	Actor_10.PhysicDesc.Pos.X = 462
	Actor_10.PhysicDesc.Pos.Y = 1.95313
	Actor_10.PhysicDesc.Pos.Z = 458
	Actor_10.PhysicDesc.Pos.Rotation = -90
	Actor_10.PhysicDesc.Density = 0
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 2.12676e+037
	Actor_10.PhysicDesc.SizeY = 0.240847
	Actor_10.PhysicDesc.SizeZ = 0
	Actor_10.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_9.phy"
	Actor_10:SetPhysicalActorType(1)
	Actor_10:SetPhysicalShape(5)
	Actor_10.ExtraInfo.Name = ""
	Actor_10.ExtraInfo.NameColorR = 0.240847
	Actor_10.ExtraInfo.NameColorG = 0
	Actor_10.ExtraInfo.NameColorB = 0
	Actor_10H = ActorHandler(Actor_10)
	environment:AddActorObject(Actor_10H)

	Actor_11 = ActorObjectInfo(11)
	Actor_11:SetRenderType(1)
	Actor_11.DisplayDesc.ModelId = 227853216
	Actor_11.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_10.osgb"
	Actor_11.DisplayDesc.Outfit = ""
	Actor_11.DisplayDesc.Weapon = ""
	Actor_11.DisplayDesc.Mode = ""
	Actor_11.DisplayDesc.UseLight = false
	Actor_11.DisplayDesc.CastShadow = false
	Actor_11.DisplayDesc.ColorR = 2.8026e-045
	Actor_11.DisplayDesc.ColorG = 6.84478e-023
	Actor_11.DisplayDesc.ColorB = 3.11113e-024
	Actor_11.DisplayDesc.ColorA = 3.27758e-031
	Actor_11:SetModelState(1)
	Actor_11.PhysicDesc.Pos.X = 446
	Actor_11.PhysicDesc.Pos.Y = 17.3828
	Actor_11.PhysicDesc.Pos.Z = 445
	Actor_11.PhysicDesc.Pos.Rotation = -90
	Actor_11.PhysicDesc.Density = 9.99281e-024
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 0
	Actor_11.PhysicDesc.SizeY = 1.4013e-045
	Actor_11.PhysicDesc.SizeZ = 6.84478e-023
	Actor_11.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_10.phy"
	Actor_11:SetPhysicalActorType(1)
	Actor_11:SetPhysicalShape(5)
	Actor_11.ExtraInfo.Name = ""
	Actor_11.ExtraInfo.NameColorR = 0
	Actor_11.ExtraInfo.NameColorG = 2.4763e-023
	Actor_11.ExtraInfo.NameColorB = 7.64466e-031
	Actor_11H = ActorHandler(Actor_11)
	environment:AddActorObject(Actor_11H)

	Actor_12 = ActorObjectInfo(12)
	Actor_12:SetRenderType(1)
	Actor_12.DisplayDesc.ModelId = 0
	Actor_12.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_11.osgb"
	Actor_12.DisplayDesc.Outfit = ""
	Actor_12.DisplayDesc.Weapon = ""
	Actor_12.DisplayDesc.Mode = ""
	Actor_12.DisplayDesc.UseLight = false
	Actor_12.DisplayDesc.CastShadow = false
	Actor_12.DisplayDesc.ColorR = 0
	Actor_12.DisplayDesc.ColorG = 1.05139e-030
	Actor_12.DisplayDesc.ColorB = 1.82271e-031
	Actor_12.DisplayDesc.ColorA = 0
	Actor_12:SetModelState(1)
	Actor_12.PhysicDesc.Pos.X = 446
	Actor_12.PhysicDesc.Pos.Y = 17.3828
	Actor_12.PhysicDesc.Pos.Z = 445
	Actor_12.PhysicDesc.Pos.Rotation = -90
	Actor_12.PhysicDesc.Density = 0
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 0
	Actor_12.PhysicDesc.SizeY = 0
	Actor_12.PhysicDesc.SizeZ = 0
	Actor_12.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_11.phy"
	Actor_12:SetPhysicalActorType(1)
	Actor_12:SetPhysicalShape(5)
	Actor_12.ExtraInfo.Name = ""
	Actor_12.ExtraInfo.NameColorR = 3.5337e-023
	Actor_12.ExtraInfo.NameColorG = 1.83677e-040
	Actor_12.ExtraInfo.NameColorB = 2.63314e-035
	Actor_12H = ActorHandler(Actor_12)
	environment:AddActorObject(Actor_12H)

	Actor_13 = ActorObjectInfo(13)
	Actor_13:SetRenderType(1)
	Actor_13.DisplayDesc.ModelId = 0
	Actor_13.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_12.osgb"
	Actor_13.DisplayDesc.Outfit = ""
	Actor_13.DisplayDesc.Weapon = ""
	Actor_13.DisplayDesc.Mode = ""
	Actor_13.DisplayDesc.UseLight = false
	Actor_13.DisplayDesc.CastShadow = false
	Actor_13.DisplayDesc.ColorR = 1.4013e-045
	Actor_13.DisplayDesc.ColorG = 0
	Actor_13.DisplayDesc.ColorB = 0
	Actor_13.DisplayDesc.ColorA = 0
	Actor_13:SetModelState(1)
	Actor_13.PhysicDesc.Pos.X = 446
	Actor_13.PhysicDesc.Pos.Y = 17.3828
	Actor_13.PhysicDesc.Pos.Z = 445
	Actor_13.PhysicDesc.Pos.Rotation = -90
	Actor_13.PhysicDesc.Density = 1.78902e-031
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 5.32493e-044
	Actor_13.PhysicDesc.SizeY = 0
	Actor_13.PhysicDesc.SizeZ = 0
	Actor_13.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_12.phy"
	Actor_13:SetPhysicalActorType(1)
	Actor_13:SetPhysicalShape(5)
	Actor_13.ExtraInfo.Name = ""
	Actor_13.ExtraInfo.NameColorR = 0
	Actor_13.ExtraInfo.NameColorG = 0
	Actor_13.ExtraInfo.NameColorB = 0
	Actor_13H = ActorHandler(Actor_13)
	environment:AddActorObject(Actor_13H)

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(1)
	Actor_14.DisplayDesc.ModelId = 4
	Actor_14.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_13.osgb"
	Actor_14.DisplayDesc.Outfit = ""
	Actor_14.DisplayDesc.Weapon = ""
	Actor_14.DisplayDesc.Mode = ""
	Actor_14.DisplayDesc.UseLight = false
	Actor_14.DisplayDesc.CastShadow = false
	Actor_14.DisplayDesc.ColorR = 0
	Actor_14.DisplayDesc.ColorG = 0
	Actor_14.DisplayDesc.ColorB = 0
	Actor_14.DisplayDesc.ColorA = 0
	Actor_14:SetModelState(1)
	Actor_14.PhysicDesc.Pos.X = 449
	Actor_14.PhysicDesc.Pos.Y = 23.6328
	Actor_14.PhysicDesc.Pos.Z = 452
	Actor_14.PhysicDesc.Pos.Rotation = -90
	Actor_14.PhysicDesc.Density = 4.57361e-038
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 0
	Actor_14.PhysicDesc.SizeY = 0
	Actor_14.PhysicDesc.SizeZ = 0
	Actor_14.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_13.phy"
	Actor_14:SetPhysicalActorType(1)
	Actor_14:SetPhysicalShape(5)
	Actor_14.ExtraInfo.Name = ""
	Actor_14.ExtraInfo.NameColorR = 0
	Actor_14.ExtraInfo.NameColorG = 0
	Actor_14.ExtraInfo.NameColorB = 0
	Actor_14H = ActorHandler(Actor_14)
	environment:AddActorObject(Actor_14H)

	Actor_15 = ActorObjectInfo(15)
	Actor_15:SetRenderType(1)
	Actor_15.DisplayDesc.ModelId = 0
	Actor_15.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_14.osgb"
	Actor_15.DisplayDesc.Outfit = ""
	Actor_15.DisplayDesc.Weapon = ""
	Actor_15.DisplayDesc.Mode = ""
	Actor_15.DisplayDesc.UseLight = false
	Actor_15.DisplayDesc.CastShadow = false
	Actor_15.DisplayDesc.ColorR = 1.4013e-045
	Actor_15.DisplayDesc.ColorG = 0
	Actor_15.DisplayDesc.ColorB = 2.455e-024
	Actor_15.DisplayDesc.ColorA = 0
	Actor_15:SetModelState(1)
	Actor_15.PhysicDesc.Pos.X = 449
	Actor_15.PhysicDesc.Pos.Y = 23.6328
	Actor_15.PhysicDesc.Pos.Z = 452
	Actor_15.PhysicDesc.Pos.Rotation = -90
	Actor_15.PhysicDesc.Density = -4.59177e-041
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 0
	Actor_15.PhysicDesc.SizeY = 2.10195e-044
	Actor_15.PhysicDesc.SizeZ = 0
	Actor_15.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_14.phy"
	Actor_15:SetPhysicalActorType(1)
	Actor_15:SetPhysicalShape(5)
	Actor_15.ExtraInfo.Name = ""
	Actor_15.ExtraInfo.NameColorR = 7.27699e-024
	Actor_15.ExtraInfo.NameColorG = 0
	Actor_15.ExtraInfo.NameColorB = 0
	Actor_15H = ActorHandler(Actor_15)
	environment:AddActorObject(Actor_15H)

	Actor_16 = ActorObjectInfo(16)
	Actor_16:SetRenderType(1)
	Actor_16.DisplayDesc.ModelId = 0
	Actor_16.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_15.osgb"
	Actor_16.DisplayDesc.Outfit = ""
	Actor_16.DisplayDesc.Weapon = ""
	Actor_16.DisplayDesc.Mode = ""
	Actor_16.DisplayDesc.UseLight = false
	Actor_16.DisplayDesc.CastShadow = false
	Actor_16.DisplayDesc.ColorR = 0.337891
	Actor_16.DisplayDesc.ColorG = 0.675781
	Actor_16.DisplayDesc.ColorB = 0.337891
	Actor_16.DisplayDesc.ColorA = 0
	Actor_16:SetModelState(1)
	Actor_16.PhysicDesc.Pos.X = 440.5
	Actor_16.PhysicDesc.Pos.Y = 7.8125
	Actor_16.PhysicDesc.Pos.Z = 447.5
	Actor_16.PhysicDesc.Pos.Rotation = 90
	Actor_16.PhysicDesc.Density = 0.337891
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 0
	Actor_16.PhysicDesc.SizeY = 0
	Actor_16.PhysicDesc.SizeZ = 1.28572e-039
	Actor_16.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_15.phy"
	Actor_16:SetPhysicalActorType(1)
	Actor_16:SetPhysicalShape(5)
	Actor_16.ExtraInfo.Name = ""
	Actor_16.ExtraInfo.NameColorR = 5.60519e-045
	Actor_16.ExtraInfo.NameColorG = 7.18306e-042
	Actor_16.ExtraInfo.NameColorB = 1.67899e-038
	Actor_16H = ActorHandler(Actor_16)
	environment:AddActorObject(Actor_16H)

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(1)
	Actor_17.DisplayDesc.ModelId = 0
	Actor_17.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_15.osgb"
	Actor_17.DisplayDesc.Outfit = ""
	Actor_17.DisplayDesc.Weapon = ""
	Actor_17.DisplayDesc.Mode = ""
	Actor_17.DisplayDesc.UseLight = false
	Actor_17.DisplayDesc.CastShadow = false
	Actor_17.DisplayDesc.ColorR = 0
	Actor_17.DisplayDesc.ColorG = 3.23588e-024
	Actor_17.DisplayDesc.ColorB = 0
	Actor_17.DisplayDesc.ColorA = 0
	Actor_17:SetModelState(1)
	Actor_17.PhysicDesc.Pos.X = 445.875
	Actor_17.PhysicDesc.Pos.Y = 8.98438
	Actor_17.PhysicDesc.Pos.Z = 435.5
	Actor_17.PhysicDesc.Pos.Rotation = 180
	Actor_17.PhysicDesc.Density = 1.13505e-043
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 0
	Actor_17.PhysicDesc.SizeY = 0
	Actor_17.PhysicDesc.SizeZ = 1.28577e-039
	Actor_17.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_15.phy"
	Actor_17:SetPhysicalActorType(1)
	Actor_17:SetPhysicalShape(5)
	Actor_17.ExtraInfo.Name = ""
	Actor_17.ExtraInfo.NameColorR = 5.60519e-045
	Actor_17.ExtraInfo.NameColorG = 7.18306e-042
	Actor_17.ExtraInfo.NameColorB = 1.67899e-038
	Actor_17H = ActorHandler(Actor_17)
	environment:AddActorObject(Actor_17H)

	Actor_18 = ActorObjectInfo(18)
	Actor_18:SetRenderType(1)
	Actor_18.DisplayDesc.ModelId = 0
	Actor_18.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_16.osgb"
	Actor_18.DisplayDesc.Outfit = ""
	Actor_18.DisplayDesc.Weapon = ""
	Actor_18.DisplayDesc.Mode = ""
	Actor_18.DisplayDesc.UseLight = false
	Actor_18.DisplayDesc.CastShadow = false
	Actor_18.DisplayDesc.ColorR = 0.948683
	Actor_18.DisplayDesc.ColorG = -0.325011
	Actor_18.DisplayDesc.ColorB = -0.0612587
	Actor_18.DisplayDesc.ColorA = 0.943724
	Actor_18:SetModelState(1)
	Actor_18.PhysicDesc.Pos.X = 458.5
	Actor_18.PhysicDesc.Pos.Y = 5.66406
	Actor_18.PhysicDesc.Pos.Z = 468.5
	Actor_18.PhysicDesc.Pos.Rotation = 90
	Actor_18.PhysicDesc.Density = 0
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 0.316228
	Actor_18.PhysicDesc.SizeY = 0
	Actor_18.PhysicDesc.SizeZ = 0.948683
	Actor_18.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_16.phy"
	Actor_18:SetPhysicalActorType(1)
	Actor_18:SetPhysicalShape(5)
	Actor_18.ExtraInfo.Name = ""
	Actor_18.ExtraInfo.NameColorR = 0.943724
	Actor_18.ExtraInfo.NameColorG = -0.0612587
	Actor_18.ExtraInfo.NameColorB = 0.325011
	Actor_18H = ActorHandler(Actor_18)
	environment:AddActorObject(Actor_18H)

	Actor_19 = ActorObjectInfo(19)
	Actor_19:SetRenderType(1)
	Actor_19.DisplayDesc.ModelId = 0
	Actor_19.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_17.osgb"
	Actor_19.DisplayDesc.Outfit = ""
	Actor_19.DisplayDesc.Weapon = ""
	Actor_19.DisplayDesc.Mode = ""
	Actor_19.DisplayDesc.UseLight = false
	Actor_19.DisplayDesc.CastShadow = false
	Actor_19.DisplayDesc.ColorR = -0.242536
	Actor_19.DisplayDesc.ColorG = 0.970142
	Actor_19.DisplayDesc.ColorB = 0
	Actor_19.DisplayDesc.ColorA = 1.74498e-039
	Actor_19:SetModelState(1)
	Actor_19.PhysicDesc.Pos.X = 432.5
	Actor_19.PhysicDesc.Pos.Y = 0.390625
	Actor_19.PhysicDesc.Pos.Z = 462.5
	Actor_19.PhysicDesc.Pos.Rotation = 90
	Actor_19.PhysicDesc.Density = 0.0878906
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = -0.265625
	Actor_19.PhysicDesc.SizeY = 0.0878906
	Actor_19.PhysicDesc.SizeZ = 0.798828
	Actor_19.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_17.phy"
	Actor_19:SetPhysicalActorType(1)
	Actor_19:SetPhysicalShape(5)
	Actor_19.ExtraInfo.Name = ""
	Actor_19.ExtraInfo.NameColorR = -2.73438
	Actor_19.ExtraInfo.NameColorG = -0.0878906
	Actor_19.ExtraInfo.NameColorB = 1.68555
	Actor_19H = ActorHandler(Actor_19)
	environment:AddActorObject(Actor_19H)

	Actor_20 = ActorObjectInfo(20)
	Actor_20:SetRenderType(1)
	Actor_20.DisplayDesc.ModelId = 1082413056
	Actor_20.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_17.osgb"
	Actor_20.DisplayDesc.Outfit = ""
	Actor_20.DisplayDesc.Weapon = ""
	Actor_20.DisplayDesc.Mode = ""
	Actor_20.DisplayDesc.UseLight = false
	Actor_20.DisplayDesc.CastShadow = true
	Actor_20.DisplayDesc.ColorR = 3.11719
	Actor_20.DisplayDesc.ColorG = 3.82813
	Actor_20.DisplayDesc.ColorB = 2.30078
	Actor_20.DisplayDesc.ColorA = 3.11719
	Actor_20:SetModelState(1)
	Actor_20.PhysicDesc.Pos.X = 433
	Actor_20.PhysicDesc.Pos.Y = 0.230469
	Actor_20.PhysicDesc.Pos.Z = 465.191
	Actor_20.PhysicDesc.Pos.Rotation = 0
	Actor_20.PhysicDesc.Density = 2.30078
	Actor_20.PhysicDesc.Collidable = true
	Actor_20.PhysicDesc.SizeX = 5.04883
	Actor_20.PhysicDesc.SizeY = 2.30078
	Actor_20.PhysicDesc.SizeZ = 0.304688
	Actor_20.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_17.phy"
	Actor_20:SetPhysicalActorType(1)
	Actor_20:SetPhysicalShape(5)
	Actor_20.ExtraInfo.Name = ""
	Actor_20.ExtraInfo.NameColorR = 1.99414
	Actor_20.ExtraInfo.NameColorG = 1.68945
	Actor_20.ExtraInfo.NameColorB = 3.11719
	Actor_20H = ActorHandler(Actor_20)
	environment:AddActorObject(Actor_20H)

	Actor_21 = ActorObjectInfo(21)
	Actor_21:SetRenderType(1)
	Actor_21.DisplayDesc.ModelId = 0
	Actor_21.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_18.osgb"
	Actor_21.DisplayDesc.Outfit = ""
	Actor_21.DisplayDesc.Weapon = ""
	Actor_21.DisplayDesc.Mode = ""
	Actor_21.DisplayDesc.UseLight = false
	Actor_21.DisplayDesc.CastShadow = false
	Actor_21.DisplayDesc.ColorR = -1.0614e-007
	Actor_21.DisplayDesc.ColorG = 0
	Actor_21.DisplayDesc.ColorB = 0
	Actor_21.DisplayDesc.ColorA = 0
	Actor_21:SetModelState(1)
	Actor_21.PhysicDesc.Pos.X = 432.375
	Actor_21.PhysicDesc.Pos.Y = 0.300781
	Actor_21.PhysicDesc.Pos.Z = 467.129
	Actor_21.PhysicDesc.Pos.Rotation = 180
	Actor_21.PhysicDesc.Density = 0
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 2.12676e+037
	Actor_21.PhysicDesc.SizeY = 0.240847
	Actor_21.PhysicDesc.SizeZ = 0
	Actor_21.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_18.phy"
	Actor_21:SetPhysicalActorType(1)
	Actor_21:SetPhysicalShape(5)
	Actor_21.ExtraInfo.Name = ""
	Actor_21.ExtraInfo.NameColorR = 0.240847
	Actor_21.ExtraInfo.NameColorG = 0
	Actor_21.ExtraInfo.NameColorB = 0
	Actor_21H = ActorHandler(Actor_21)
	environment:AddActorObject(Actor_21H)

	Actor_22 = ActorObjectInfo(22)
	Actor_22:SetRenderType(1)
	Actor_22.DisplayDesc.ModelId = 0
	Actor_22.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_18.osgb"
	Actor_22.DisplayDesc.Outfit = ""
	Actor_22.DisplayDesc.Weapon = ""
	Actor_22.DisplayDesc.Mode = ""
	Actor_22.DisplayDesc.UseLight = false
	Actor_22.DisplayDesc.CastShadow = true
	Actor_22.DisplayDesc.ColorR = -2.97803e-010
	Actor_22.DisplayDesc.ColorG = 0
	Actor_22.DisplayDesc.ColorB = 0
	Actor_22.DisplayDesc.ColorA = 0
	Actor_22:SetModelState(1)
	Actor_22.PhysicDesc.Pos.X = 434.75
	Actor_22.PhysicDesc.Pos.Y = 0.0976563
	Actor_22.PhysicDesc.Pos.Z = 466.25
	Actor_22.PhysicDesc.Pos.Rotation = -90
	Actor_22.PhysicDesc.Density = 0
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 0
	Actor_22.PhysicDesc.SizeY = 0
	Actor_22.PhysicDesc.SizeZ = 1.28574e-039
	Actor_22.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_18.phy"
	Actor_22:SetPhysicalActorType(1)
	Actor_22:SetPhysicalShape(5)
	Actor_22.ExtraInfo.Name = ""
	Actor_22.ExtraInfo.NameColorR = 5.60519e-045
	Actor_22.ExtraInfo.NameColorG = 7.18306e-042
	Actor_22.ExtraInfo.NameColorB = 1.67899e-038
	Actor_22H = ActorHandler(Actor_22)
	environment:AddActorObject(Actor_22H)

	Actor_23 = ActorObjectInfo(23)
	Actor_23:SetRenderType(1)
	Actor_23.DisplayDesc.ModelId = 131076
	Actor_23.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_18.osgb"
	Actor_23.DisplayDesc.Outfit = ""
	Actor_23.DisplayDesc.Weapon = ""
	Actor_23.DisplayDesc.Mode = ""
	Actor_23.DisplayDesc.UseLight = false
	Actor_23.DisplayDesc.CastShadow = true
	Actor_23.DisplayDesc.ColorR = 3.40282e+038
	Actor_23.DisplayDesc.ColorG = -3.40282e+038
	Actor_23.DisplayDesc.ColorB = -3.40282e+038
	Actor_23.DisplayDesc.ColorA = -3.40282e+038
	Actor_23:SetModelState(1)
	Actor_23.PhysicDesc.Pos.X = 435.5
	Actor_23.PhysicDesc.Pos.Y = 0
	Actor_23.PhysicDesc.Pos.Z = 463.5
	Actor_23.PhysicDesc.Pos.Rotation = 0
	Actor_23.PhysicDesc.Density = 0
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 0
	Actor_23.PhysicDesc.SizeY = 0
	Actor_23.PhysicDesc.SizeZ = 0
	Actor_23.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_18.phy"
	Actor_23:SetPhysicalActorType(1)
	Actor_23:SetPhysicalShape(5)
	Actor_23.ExtraInfo.Name = ""
	Actor_23.ExtraInfo.NameColorR = 0
	Actor_23.ExtraInfo.NameColorG = 0
	Actor_23.ExtraInfo.NameColorB = 5.60519e-045
	Actor_23H = ActorHandler(Actor_23)
	environment:AddActorObject(Actor_23H)

	Actor_24 = ActorObjectInfo(24)
	Actor_24:SetRenderType(1)
	Actor_24.DisplayDesc.ModelId = 420284536
	Actor_24.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_19.osgb"
	Actor_24.DisplayDesc.Outfit = ""
	Actor_24.DisplayDesc.Weapon = ""
	Actor_24.DisplayDesc.Mode = ""
	Actor_24.DisplayDesc.UseLight = false
	Actor_24.DisplayDesc.CastShadow = true
	Actor_24.DisplayDesc.ColorR = 3.40282e+038
	Actor_24.DisplayDesc.ColorG = 0
	Actor_24.DisplayDesc.ColorB = 0
	Actor_24.DisplayDesc.ColorA = 1.74489e-039
	Actor_24:SetModelState(1)
	Actor_24.PhysicDesc.Pos.X = 433.5
	Actor_24.PhysicDesc.Pos.Y = 0.296875
	Actor_24.PhysicDesc.Pos.Z = 466.75
	Actor_24.PhysicDesc.Pos.Rotation = 180
	Actor_24.PhysicDesc.Density = 4.57352e-038
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 2.47956e-039
	Actor_24.PhysicDesc.SizeY = 1.02321e-034
	Actor_24.PhysicDesc.SizeZ = 1.83708e-031
	Actor_24.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_19.phy"
	Actor_24:SetPhysicalActorType(1)
	Actor_24:SetPhysicalShape(5)
	Actor_24.ExtraInfo.Name = ""
	Actor_24.ExtraInfo.NameColorR = 7.03125
	Actor_24.ExtraInfo.NameColorG = -0
	Actor_24.ExtraInfo.NameColorB = -1.95313
	Actor_24H = ActorHandler(Actor_24)
	environment:AddActorObject(Actor_24H)

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(1)
	Actor_25.DisplayDesc.ModelId = 131080
	Actor_25.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_19.osgb"
	Actor_25.DisplayDesc.Outfit = ""
	Actor_25.DisplayDesc.Weapon = ""
	Actor_25.DisplayDesc.Mode = ""
	Actor_25.DisplayDesc.UseLight = false
	Actor_25.DisplayDesc.CastShadow = true
	Actor_25.DisplayDesc.ColorR = 3.40282e+038
	Actor_25.DisplayDesc.ColorG = 3.40282e+038
	Actor_25.DisplayDesc.ColorB = 0
	Actor_25.DisplayDesc.ColorA = 0
	Actor_25:SetModelState(1)
	Actor_25.PhysicDesc.Pos.X = 435.375
	Actor_25.PhysicDesc.Pos.Y = 0
	Actor_25.PhysicDesc.Pos.Z = 465.125
	Actor_25.PhysicDesc.Pos.Rotation = -90
	Actor_25.PhysicDesc.Density = 1.01025e-039
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 0
	Actor_25.PhysicDesc.SizeY = 0
	Actor_25.PhysicDesc.SizeZ = 6.47791e-031
	Actor_25.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_19.phy"
	Actor_25:SetPhysicalActorType(1)
	Actor_25:SetPhysicalShape(5)
	Actor_25.ExtraInfo.Name = ""
	Actor_25.ExtraInfo.NameColorR = 0
	Actor_25.ExtraInfo.NameColorG = 0
	Actor_25.ExtraInfo.NameColorB = 0
	Actor_25H = ActorHandler(Actor_25)
	environment:AddActorObject(Actor_25H)

	Actor_26 = ActorObjectInfo(26)
	Actor_26:SetRenderType(1)
	Actor_26.DisplayDesc.ModelId = 222948272
	Actor_26.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_18.osgb"
	Actor_26.DisplayDesc.Outfit = ""
	Actor_26.DisplayDesc.Weapon = ""
	Actor_26.DisplayDesc.Mode = ""
	Actor_26.DisplayDesc.UseLight = false
	Actor_26.DisplayDesc.CastShadow = false
	Actor_26.DisplayDesc.ColorR = 0
	Actor_26.DisplayDesc.ColorG = 0
	Actor_26.DisplayDesc.ColorB = 0
	Actor_26.DisplayDesc.ColorA = 1.7449e-039
	Actor_26:SetModelState(1)
	Actor_26.PhysicDesc.Pos.X = 431.5
	Actor_26.PhysicDesc.Pos.Y = 0
	Actor_26.PhysicDesc.Pos.Z = 464.5
	Actor_26.PhysicDesc.Pos.Rotation = -90
	Actor_26.PhysicDesc.Density = 7.734e-031
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 0
	Actor_26.PhysicDesc.SizeY = 6.86282e-031
	Actor_26.PhysicDesc.SizeZ = 2.75509e-040
	Actor_26.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_18.phy"
	Actor_26:SetPhysicalActorType(1)
	Actor_26:SetPhysicalShape(5)
	Actor_26.ExtraInfo.Name = ""
	Actor_26.ExtraInfo.NameColorR = 0
	Actor_26.ExtraInfo.NameColorG = 2.10195e-044
	Actor_26.ExtraInfo.NameColorB = 1.1911e-043
	Actor_26H = ActorHandler(Actor_26)
	environment:AddActorObject(Actor_26H)

	Actor_27 = ActorObjectInfo(27)
	Actor_27:SetRenderType(1)
	Actor_27.DisplayDesc.ModelId = 0
	Actor_27.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_20.osgb"
	Actor_27.DisplayDesc.Outfit = ""
	Actor_27.DisplayDesc.Weapon = ""
	Actor_27.DisplayDesc.Mode = ""
	Actor_27.DisplayDesc.UseLight = false
	Actor_27.DisplayDesc.CastShadow = false
	Actor_27.DisplayDesc.ColorR = 0
	Actor_27.DisplayDesc.ColorG = 9.21956e-041
	Actor_27.DisplayDesc.ColorB = 2.03743e-023
	Actor_27.DisplayDesc.ColorA = 0
	Actor_27:SetModelState(1)
	Actor_27.PhysicDesc.Pos.X = 511.5
	Actor_27.PhysicDesc.Pos.Y = 11.5234
	Actor_27.PhysicDesc.Pos.Z = 435.5
	Actor_27.PhysicDesc.Pos.Rotation = 90
	Actor_27.PhysicDesc.Density = 0
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 0
	Actor_27.PhysicDesc.SizeY = 0
	Actor_27.PhysicDesc.SizeZ = 0
	Actor_27.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_20.phy"
	Actor_27:SetPhysicalActorType(1)
	Actor_27:SetPhysicalShape(5)
	Actor_27.ExtraInfo.Name = ""
	Actor_27.ExtraInfo.NameColorR = 2.03744e-023
	Actor_27.ExtraInfo.NameColorG = 0
	Actor_27.ExtraInfo.NameColorB = 0
	Actor_27H = ActorHandler(Actor_27)
	environment:AddActorObject(Actor_27H)

	Actor_28 = ActorObjectInfo(28)
	Actor_28:SetRenderType(1)
	Actor_28.DisplayDesc.ModelId = 0
	Actor_28.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_21.osgb"
	Actor_28.DisplayDesc.Outfit = ""
	Actor_28.DisplayDesc.Weapon = ""
	Actor_28.DisplayDesc.Mode = ""
	Actor_28.DisplayDesc.UseLight = false
	Actor_28.DisplayDesc.CastShadow = true
	Actor_28.DisplayDesc.ColorR = 0
	Actor_28.DisplayDesc.ColorG = 9.21956e-041
	Actor_28.DisplayDesc.ColorB = 6.67423e-031
	Actor_28.DisplayDesc.ColorA = 6.14681e+028
	Actor_28:SetModelState(1)
	Actor_28.PhysicDesc.Pos.X = 511.5
	Actor_28.PhysicDesc.Pos.Y = 11.5234
	Actor_28.PhysicDesc.Pos.Z = 435.5
	Actor_28.PhysicDesc.Pos.Rotation = -90
	Actor_28.PhysicDesc.Density = 0
	Actor_28.PhysicDesc.Collidable = true
	Actor_28.PhysicDesc.SizeX = 0
	Actor_28.PhysicDesc.SizeY = 0
	Actor_28.PhysicDesc.SizeZ = 0
	Actor_28.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_21.phy"
	Actor_28:SetPhysicalActorType(1)
	Actor_28:SetPhysicalShape(5)
	Actor_28.ExtraInfo.Name = ""
	Actor_28.ExtraInfo.NameColorR = 1.63439e-023
	Actor_28.ExtraInfo.NameColorG = 7.9881e-041
	Actor_28.ExtraInfo.NameColorB = 7.00649e-045
	Actor_28H = ActorHandler(Actor_28)
	environment:AddActorObject(Actor_28H)

	Actor_29 = ActorObjectInfo(29)
	Actor_29:SetRenderType(1)
	Actor_29.DisplayDesc.ModelId = 0
	Actor_29.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_22.osgb"
	Actor_29.DisplayDesc.Outfit = ""
	Actor_29.DisplayDesc.Weapon = ""
	Actor_29.DisplayDesc.Mode = ""
	Actor_29.DisplayDesc.UseLight = false
	Actor_29.DisplayDesc.CastShadow = false
	Actor_29.DisplayDesc.ColorR = 0
	Actor_29.DisplayDesc.ColorG = 9.21956e-041
	Actor_29.DisplayDesc.ColorB = 2.01444e-023
	Actor_29.DisplayDesc.ColorA = 4.57358e-038
	Actor_29:SetModelState(1)
	Actor_29.PhysicDesc.Pos.X = 511.5
	Actor_29.PhysicDesc.Pos.Y = 11.5234
	Actor_29.PhysicDesc.Pos.Z = 435.5
	Actor_29.PhysicDesc.Pos.Rotation = 90
	Actor_29.PhysicDesc.Density = 0
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 0
	Actor_29.PhysicDesc.SizeY = 0
	Actor_29.PhysicDesc.SizeZ = 0
	Actor_29.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_22.phy"
	Actor_29:SetPhysicalActorType(1)
	Actor_29:SetPhysicalShape(5)
	Actor_29.ExtraInfo.Name = ""
	Actor_29.ExtraInfo.NameColorR = 1.65252e-023
	Actor_29.ExtraInfo.NameColorG = 2.8026e-045
	Actor_29.ExtraInfo.NameColorB = 0
	Actor_29H = ActorHandler(Actor_29)
	environment:AddActorObject(Actor_29H)

	Actor_30 = ActorObjectInfo(30)
	Actor_30:SetRenderType(1)
	Actor_30.DisplayDesc.ModelId = 131164
	Actor_30.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_30.DisplayDesc.Outfit = ""
	Actor_30.DisplayDesc.Weapon = ""
	Actor_30.DisplayDesc.Mode = ""
	Actor_30.DisplayDesc.UseLight = false
	Actor_30.DisplayDesc.CastShadow = false
	Actor_30.DisplayDesc.ColorR = 0
	Actor_30.DisplayDesc.ColorG = 5.60519e-045
	Actor_30.DisplayDesc.ColorB = 0
	Actor_30.DisplayDesc.ColorA = 1.30623e-038
	Actor_30:SetModelState(1)
	Actor_30.PhysicDesc.Pos.X = 505.875
	Actor_30.PhysicDesc.Pos.Y = 11.5234
	Actor_30.PhysicDesc.Pos.Z = 437.5
	Actor_30.PhysicDesc.Pos.Rotation = 180
	Actor_30.PhysicDesc.Density = 2.20405e-039
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 0
	Actor_30.PhysicDesc.SizeY = 4.57367e-038
	Actor_30.PhysicDesc.SizeZ = 2.38782e-039
	Actor_30.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_30:SetPhysicalActorType(1)
	Actor_30:SetPhysicalShape(5)
	Actor_30.ExtraInfo.Name = ""
	Actor_30.ExtraInfo.NameColorR = 0
	Actor_30.ExtraInfo.NameColorG = 0
	Actor_30.ExtraInfo.NameColorB = 0
	Actor_30H = ActorHandler(Actor_30)
	environment:AddActorObject(Actor_30H)

	Actor_31 = ActorObjectInfo(31)
	Actor_31:SetRenderType(1)
	Actor_31.DisplayDesc.ModelId = 0
	Actor_31.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_31.DisplayDesc.Outfit = ""
	Actor_31.DisplayDesc.Weapon = ""
	Actor_31.DisplayDesc.Mode = ""
	Actor_31.DisplayDesc.UseLight = false
	Actor_31.DisplayDesc.CastShadow = false
	Actor_31.DisplayDesc.ColorR = 0.999985
	Actor_31.DisplayDesc.ColorG = 0
	Actor_31.DisplayDesc.ColorB = 0
	Actor_31.DisplayDesc.ColorA = 0
	Actor_31:SetModelState(1)
	Actor_31.PhysicDesc.Pos.X = 505.875
	Actor_31.PhysicDesc.Pos.Y = 11.5234
	Actor_31.PhysicDesc.Pos.Z = 433.25
	Actor_31.PhysicDesc.Pos.Rotation = 180
	Actor_31.PhysicDesc.Density = 6.478e-031
	Actor_31.PhysicDesc.Collidable = true
	Actor_31.PhysicDesc.SizeX = 0.01
	Actor_31.PhysicDesc.SizeY = 0
	Actor_31.PhysicDesc.SizeZ = 0
	Actor_31.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_31:SetPhysicalActorType(1)
	Actor_31:SetPhysicalShape(5)
	Actor_31.ExtraInfo.Name = ""
	Actor_31.ExtraInfo.NameColorR = 0
	Actor_31.ExtraInfo.NameColorG = 0
	Actor_31.ExtraInfo.NameColorB = 0
	Actor_31H = ActorHandler(Actor_31)
	environment:AddActorObject(Actor_31H)

	Actor_32 = ActorObjectInfo(32)
	Actor_32:SetRenderType(1)
	Actor_32.DisplayDesc.ModelId = 144629820
	Actor_32.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_32.DisplayDesc.Outfit = ""
	Actor_32.DisplayDesc.Weapon = ""
	Actor_32.DisplayDesc.Mode = ""
	Actor_32.DisplayDesc.UseLight = false
	Actor_32.DisplayDesc.CastShadow = false
	Actor_32.DisplayDesc.ColorR = 1.63952e-043
	Actor_32.DisplayDesc.ColorG = 1.58347e-043
	Actor_32.DisplayDesc.ColorB = 0
	Actor_32.DisplayDesc.ColorA = 0
	Actor_32:SetModelState(1)
	Actor_32.PhysicDesc.Pos.X = 517
	Actor_32.PhysicDesc.Pos.Y = 11.5234
	Actor_32.PhysicDesc.Pos.Z = 433.25
	Actor_32.PhysicDesc.Pos.Rotation = 0
	Actor_32.PhysicDesc.Density = 0
	Actor_32.PhysicDesc.Collidable = true
	Actor_32.PhysicDesc.SizeX = 8.40779e-045
	Actor_32.PhysicDesc.SizeY = 1.54143e-044
	Actor_32.PhysicDesc.SizeZ = 2.57143e-039
	Actor_32.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_32:SetPhysicalActorType(1)
	Actor_32:SetPhysicalShape(5)
	Actor_32.ExtraInfo.Name = ""
	Actor_32.ExtraInfo.NameColorR = 0
	Actor_32.ExtraInfo.NameColorG = 0
	Actor_32.ExtraInfo.NameColorB = 0
	Actor_32H = ActorHandler(Actor_32)
	environment:AddActorObject(Actor_32H)

	Actor_33 = ActorObjectInfo(33)
	Actor_33:SetRenderType(1)
	Actor_33.DisplayDesc.ModelId = 0
	Actor_33.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_33.DisplayDesc.Outfit = ""
	Actor_33.DisplayDesc.Weapon = ""
	Actor_33.DisplayDesc.Mode = ""
	Actor_33.DisplayDesc.UseLight = false
	Actor_33.DisplayDesc.CastShadow = false
	Actor_33.DisplayDesc.ColorR = 0.251953
	Actor_33.DisplayDesc.ColorG = 0
	Actor_33.DisplayDesc.ColorB = 0
	Actor_33.DisplayDesc.ColorA = 0
	Actor_33:SetModelState(1)
	Actor_33.PhysicDesc.Pos.X = 517
	Actor_33.PhysicDesc.Pos.Y = 11.5234
	Actor_33.PhysicDesc.Pos.Z = 437.5
	Actor_33.PhysicDesc.Pos.Rotation = 0
	Actor_33.PhysicDesc.Density = 0
	Actor_33.PhysicDesc.Collidable = true
	Actor_33.PhysicDesc.SizeX = 0
	Actor_33.PhysicDesc.SizeY = 1.875
	Actor_33.PhysicDesc.SizeZ = 0
	Actor_33.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_33:SetPhysicalActorType(1)
	Actor_33:SetPhysicalShape(5)
	Actor_33.ExtraInfo.Name = ""
	Actor_33.ExtraInfo.NameColorR = 1.875
	Actor_33.ExtraInfo.NameColorG = 0
	Actor_33.ExtraInfo.NameColorB = 0
	Actor_33H = ActorHandler(Actor_33)
	environment:AddActorObject(Actor_33H)

	Actor_34 = ActorObjectInfo(34)
	Actor_34:SetRenderType(1)
	Actor_34.DisplayDesc.ModelId = 227853216
	Actor_34.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_34.DisplayDesc.Outfit = ""
	Actor_34.DisplayDesc.Weapon = ""
	Actor_34.DisplayDesc.Mode = ""
	Actor_34.DisplayDesc.UseLight = false
	Actor_34.DisplayDesc.CastShadow = false
	Actor_34.DisplayDesc.ColorR = 0
	Actor_34.DisplayDesc.ColorG = 0
	Actor_34.DisplayDesc.ColorB = 0
	Actor_34.DisplayDesc.ColorA = 0
	Actor_34:SetModelState(1)
	Actor_34.PhysicDesc.Pos.X = 509.25
	Actor_34.PhysicDesc.Pos.Y = 11.5234
	Actor_34.PhysicDesc.Pos.Z = 430.75
	Actor_34.PhysicDesc.Pos.Rotation = 90
	Actor_34.PhysicDesc.Density = 2.03941e-023
	Actor_34.PhysicDesc.Collidable = true
	Actor_34.PhysicDesc.SizeX = 1.83755e-040
	Actor_34.PhysicDesc.SizeY = 1.02319e-034
	Actor_34.PhysicDesc.SizeZ = 1.31224e-038
	Actor_34.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_34:SetPhysicalActorType(1)
	Actor_34:SetPhysicalShape(5)
	Actor_34.ExtraInfo.Name = ""
	Actor_34.ExtraInfo.NameColorR = 454.05
	Actor_34.ExtraInfo.NameColorG = 6.03717
	Actor_34.ExtraInfo.NameColorB = 506.5
	Actor_34H = ActorHandler(Actor_34)
	environment:AddActorObject(Actor_34H)

	Actor_35 = ActorObjectInfo(35)
	Actor_35:SetRenderType(1)
	Actor_35.DisplayDesc.ModelId = 214576680
	Actor_35.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_35.DisplayDesc.Outfit = ""
	Actor_35.DisplayDesc.Weapon = ""
	Actor_35.DisplayDesc.Mode = ""
	Actor_35.DisplayDesc.UseLight = false
	Actor_35.DisplayDesc.CastShadow = false
	Actor_35.DisplayDesc.ColorR = 0
	Actor_35.DisplayDesc.ColorG = 0
	Actor_35.DisplayDesc.ColorB = 0
	Actor_35.DisplayDesc.ColorA = 0
	Actor_35:SetModelState(1)
	Actor_35.PhysicDesc.Pos.X = 513.75
	Actor_35.PhysicDesc.Pos.Y = 11.5234
	Actor_35.PhysicDesc.Pos.Z = 430.75
	Actor_35.PhysicDesc.Pos.Rotation = 90
	Actor_35.PhysicDesc.Density = 0
	Actor_35.PhysicDesc.Collidable = true
	Actor_35.PhysicDesc.SizeX = 1.7038e-023
	Actor_35.PhysicDesc.SizeY = 0
	Actor_35.PhysicDesc.SizeZ = 0
	Actor_35.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_35:SetPhysicalActorType(1)
	Actor_35:SetPhysicalShape(5)
	Actor_35.ExtraInfo.Name = ""
	Actor_35.ExtraInfo.NameColorR = 0
	Actor_35.ExtraInfo.NameColorG = 0
	Actor_35.ExtraInfo.NameColorB = 2.10195e-044
	Actor_35H = ActorHandler(Actor_35)
	environment:AddActorObject(Actor_35H)

	Actor_36 = ActorObjectInfo(36)
	Actor_36:SetRenderType(1)
	Actor_36.DisplayDesc.ModelId = 499749704
	Actor_36.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_24.osgb"
	Actor_36.DisplayDesc.Outfit = ""
	Actor_36.DisplayDesc.Weapon = ""
	Actor_36.DisplayDesc.Mode = ""
	Actor_36.DisplayDesc.UseLight = false
	Actor_36.DisplayDesc.CastShadow = true
	Actor_36.DisplayDesc.ColorR = 2.38221e-044
	Actor_36.DisplayDesc.ColorG = 2.52234e-044
	Actor_36.DisplayDesc.ColorB = 0
	Actor_36.DisplayDesc.ColorA = 0
	Actor_36:SetModelState(1)
	Actor_36.PhysicDesc.Pos.X = 509.07
	Actor_36.PhysicDesc.Pos.Y = 11.5234
	Actor_36.PhysicDesc.Pos.Z = 448.098
	Actor_36.PhysicDesc.Pos.Rotation = -90
	Actor_36.PhysicDesc.Density = 6.04492
	Actor_36.PhysicDesc.Collidable = true
	Actor_36.PhysicDesc.SizeX = 1.4013e-045
	Actor_36.PhysicDesc.SizeY = 0
	Actor_36.PhysicDesc.SizeZ = 9.21956e-041
	Actor_36.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_24.phy"
	Actor_36:SetPhysicalActorType(1)
	Actor_36:SetPhysicalShape(5)
	Actor_36.ExtraInfo.Name = ""
	Actor_36.ExtraInfo.NameColorR = 0
	Actor_36.ExtraInfo.NameColorG = 0
	Actor_36.ExtraInfo.NameColorB = 0
	Actor_36H = ActorHandler(Actor_36)
	environment:AddActorObject(Actor_36H)

	Actor_37 = ActorObjectInfo(37)
	Actor_37:SetRenderType(1)
	Actor_37.DisplayDesc.ModelId = 0
	Actor_37.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_24.osgb"
	Actor_37.DisplayDesc.Outfit = ""
	Actor_37.DisplayDesc.Weapon = ""
	Actor_37.DisplayDesc.Mode = ""
	Actor_37.DisplayDesc.UseLight = false
	Actor_37.DisplayDesc.CastShadow = false
	Actor_37.DisplayDesc.ColorR = 0
	Actor_37.DisplayDesc.ColorG = 7.86e-023
	Actor_37.DisplayDesc.ColorB = 7.63061e-023
	Actor_37.DisplayDesc.ColorA = 7.63067e-023
	Actor_37:SetModelState(1)
	Actor_37.PhysicDesc.Pos.X = 513.811
	Actor_37.PhysicDesc.Pos.Y = 11.5234
	Actor_37.PhysicDesc.Pos.Z = 448.098
	Actor_37.PhysicDesc.Pos.Rotation = -90
	Actor_37.PhysicDesc.Density = 0
	Actor_37.PhysicDesc.Collidable = true
	Actor_37.PhysicDesc.SizeX = 0
	Actor_37.PhysicDesc.SizeY = 0
	Actor_37.PhysicDesc.SizeZ = 0
	Actor_37.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_24.phy"
	Actor_37:SetPhysicalActorType(1)
	Actor_37:SetPhysicalShape(5)
	Actor_37.ExtraInfo.Name = ""
	Actor_37.ExtraInfo.NameColorR = 4.81826e-034
	Actor_37.ExtraInfo.NameColorG = 0
	Actor_37.ExtraInfo.NameColorB = 0
	Actor_37H = ActorHandler(Actor_37)
	environment:AddActorObject(Actor_37H)

	Actor_38 = ActorObjectInfo(38)
	Actor_38:SetRenderType(1)
	Actor_38.DisplayDesc.ModelId = 131076
	Actor_38.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_38.DisplayDesc.Outfit = ""
	Actor_38.DisplayDesc.Weapon = ""
	Actor_38.DisplayDesc.Mode = ""
	Actor_38.DisplayDesc.UseLight = false
	Actor_38.DisplayDesc.CastShadow = false
	Actor_38.DisplayDesc.ColorR = 1.10591e-034
	Actor_38.DisplayDesc.ColorG = 9.86919e-031
	Actor_38.DisplayDesc.ColorB = 0
	Actor_38.DisplayDesc.ColorA = 0
	Actor_38:SetModelState(1)
	Actor_38.PhysicDesc.Pos.X = 505.375
	Actor_38.PhysicDesc.Pos.Y = 11.5234
	Actor_38.PhysicDesc.Pos.Z = 445.5
	Actor_38.PhysicDesc.Pos.Rotation = 180
	Actor_38.PhysicDesc.Density = 0
	Actor_38.PhysicDesc.Collidable = true
	Actor_38.PhysicDesc.SizeX = 0
	Actor_38.PhysicDesc.SizeY = 0
	Actor_38.PhysicDesc.SizeZ = 6.4703e-024
	Actor_38.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_38:SetPhysicalActorType(1)
	Actor_38:SetPhysicalShape(5)
	Actor_38.ExtraInfo.Name = ""
	Actor_38.ExtraInfo.NameColorR = 0
	Actor_38.ExtraInfo.NameColorG = 6.47032e-024
	Actor_38.ExtraInfo.NameColorB = 0
	Actor_38H = ActorHandler(Actor_38)
	environment:AddActorObject(Actor_38H)

	Actor_39 = ActorObjectInfo(39)
	Actor_39:SetRenderType(1)
	Actor_39.DisplayDesc.ModelId = 0
	Actor_39.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_39.DisplayDesc.Outfit = ""
	Actor_39.DisplayDesc.Weapon = ""
	Actor_39.DisplayDesc.Mode = ""
	Actor_39.DisplayDesc.UseLight = false
	Actor_39.DisplayDesc.CastShadow = true
	Actor_39.DisplayDesc.ColorR = 0
	Actor_39.DisplayDesc.ColorG = 0
	Actor_39.DisplayDesc.ColorB = 4.90454e-044
	Actor_39.DisplayDesc.ColorA = 0
	Actor_39:SetModelState(1)
	Actor_39.PhysicDesc.Pos.X = 517.5
	Actor_39.PhysicDesc.Pos.Y = 11.5234
	Actor_39.PhysicDesc.Pos.Z = 445.5
	Actor_39.PhysicDesc.Pos.Rotation = 0
	Actor_39.PhysicDesc.Density = 2.71191
	Actor_39.PhysicDesc.Collidable = true
	Actor_39.PhysicDesc.SizeX = 6.34439
	Actor_39.PhysicDesc.SizeY = 1.4013e-045
	Actor_39.PhysicDesc.SizeZ = 2.83713e-024
	Actor_39.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_39:SetPhysicalActorType(1)
	Actor_39:SetPhysicalShape(5)
	Actor_39.ExtraInfo.Name = ""
	Actor_39.ExtraInfo.NameColorR = 0
	Actor_39.ExtraInfo.NameColorG = 0
	Actor_39.ExtraInfo.NameColorB = 0
	Actor_39H = ActorHandler(Actor_39)
	environment:AddActorObject(Actor_39H)

	Actor_40 = ActorObjectInfo(40)
	Actor_40:SetRenderType(1)
	Actor_40.DisplayDesc.ModelId = 131080
	Actor_40.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_40.DisplayDesc.Outfit = ""
	Actor_40.DisplayDesc.Weapon = ""
	Actor_40.DisplayDesc.Mode = ""
	Actor_40.DisplayDesc.UseLight = false
	Actor_40.DisplayDesc.CastShadow = true
	Actor_40.DisplayDesc.ColorR = 0
	Actor_40.DisplayDesc.ColorG = 2.8026e-045
	Actor_40.DisplayDesc.ColorB = 0
	Actor_40.DisplayDesc.ColorA = 0
	Actor_40:SetModelState(1)
	Actor_40.PhysicDesc.Pos.X = 499.5
	Actor_40.PhysicDesc.Pos.Y = 10.1563
	Actor_40.PhysicDesc.Pos.Z = 454.5
	Actor_40.PhysicDesc.Pos.Rotation = 90
	Actor_40.PhysicDesc.Density = 5.60519e-045
	Actor_40.PhysicDesc.Collidable = true
	Actor_40.PhysicDesc.SizeX = 0
	Actor_40.PhysicDesc.SizeY = 0
	Actor_40.PhysicDesc.SizeZ = 2.94729e-024
	Actor_40.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_40:SetPhysicalActorType(1)
	Actor_40:SetPhysicalShape(5)
	Actor_40.ExtraInfo.Name = ""
	Actor_40.ExtraInfo.NameColorR = 0
	Actor_40.ExtraInfo.NameColorG = 0
	Actor_40.ExtraInfo.NameColorB = 0
	Actor_40H = ActorHandler(Actor_40)
	environment:AddActorObject(Actor_40H)

	Actor_41 = ActorObjectInfo(41)
	Actor_41:SetRenderType(1)
	Actor_41.DisplayDesc.ModelId = 131084
	Actor_41.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_41.DisplayDesc.Outfit = ""
	Actor_41.DisplayDesc.Weapon = ""
	Actor_41.DisplayDesc.Mode = ""
	Actor_41.DisplayDesc.UseLight = false
	Actor_41.DisplayDesc.CastShadow = false
	Actor_41.DisplayDesc.ColorR = 1.4013e-045
	Actor_41.DisplayDesc.ColorG = 1.65315e-039
	Actor_41.DisplayDesc.ColorB = 1.02316e-034
	Actor_41.DisplayDesc.ColorA = 1.64081e-023
	Actor_41:SetModelState(1)
	Actor_41.PhysicDesc.Pos.X = 523.5
	Actor_41.PhysicDesc.Pos.Y = 10.1563
	Actor_41.PhysicDesc.Pos.Z = 454.5
	Actor_41.PhysicDesc.Pos.Rotation = 90
	Actor_41.PhysicDesc.Density = 1
	Actor_41.PhysicDesc.Collidable = true
	Actor_41.PhysicDesc.SizeX = 0
	Actor_41.PhysicDesc.SizeY = 0
	Actor_41.PhysicDesc.SizeZ = 0
	Actor_41.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_41:SetPhysicalActorType(1)
	Actor_41:SetPhysicalShape(5)
	Actor_41.ExtraInfo.Name = ""
	Actor_41.ExtraInfo.NameColorR = 1.36332e-041
	Actor_41.ExtraInfo.NameColorG = 1
	Actor_41.ExtraInfo.NameColorB = 2.35106e-038
	Actor_41H = ActorHandler(Actor_41)
	environment:AddActorObject(Actor_41H)

	Actor_42 = ActorObjectInfo(42)
	Actor_42:SetRenderType(1)
	Actor_42.DisplayDesc.ModelId = 437649888
	Actor_42.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_42.DisplayDesc.Outfit = ""
	Actor_42.DisplayDesc.Weapon = ""
	Actor_42.DisplayDesc.Mode = ""
	Actor_42.DisplayDesc.UseLight = false
	Actor_42.DisplayDesc.CastShadow = true
	Actor_42.DisplayDesc.ColorR = 1.86373e-043
	Actor_42.DisplayDesc.ColorG = 1.87774e-043
	Actor_42.DisplayDesc.ColorB = 0
	Actor_42.DisplayDesc.ColorA = 0
	Actor_42:SetModelState(1)
	Actor_42.PhysicDesc.Pos.X = 523.5
	Actor_42.PhysicDesc.Pos.Y = 10.1563
	Actor_42.PhysicDesc.Pos.Z = 424.5
	Actor_42.PhysicDesc.Pos.Rotation = 90
	Actor_42.PhysicDesc.Density = 3.41797
	Actor_42.PhysicDesc.Collidable = true
	Actor_42.PhysicDesc.SizeX = 1.4013e-045
	Actor_42.PhysicDesc.SizeY = 0
	Actor_42.PhysicDesc.SizeZ = 9.21956e-041
	Actor_42.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_42:SetPhysicalActorType(1)
	Actor_42:SetPhysicalShape(5)
	Actor_42.ExtraInfo.Name = ""
	Actor_42.ExtraInfo.NameColorR = 0
	Actor_42.ExtraInfo.NameColorG = 0
	Actor_42.ExtraInfo.NameColorB = 0
	Actor_42H = ActorHandler(Actor_42)
	environment:AddActorObject(Actor_42H)

	Actor_43 = ActorObjectInfo(43)
	Actor_43:SetRenderType(1)
	Actor_43.DisplayDesc.ModelId = 131088
	Actor_43.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_43.DisplayDesc.Outfit = ""
	Actor_43.DisplayDesc.Weapon = ""
	Actor_43.DisplayDesc.Mode = ""
	Actor_43.DisplayDesc.UseLight = false
	Actor_43.DisplayDesc.CastShadow = false
	Actor_43.DisplayDesc.ColorR = 1.02295e-043
	Actor_43.DisplayDesc.ColorG = 1.65309e-039
	Actor_43.DisplayDesc.ColorB = 1.02318e-034
	Actor_43.DisplayDesc.ColorA = 1.31224e-038
	Actor_43:SetModelState(1)
	Actor_43.PhysicDesc.Pos.X = 499.5
	Actor_43.PhysicDesc.Pos.Y = 10.1563
	Actor_43.PhysicDesc.Pos.Z = 424.5
	Actor_43.PhysicDesc.Pos.Rotation = 90
	Actor_43.PhysicDesc.Density = 1
	Actor_43.PhysicDesc.Collidable = true
	Actor_43.PhysicDesc.SizeX = 0
	Actor_43.PhysicDesc.SizeY = 0
	Actor_43.PhysicDesc.SizeZ = 0
	Actor_43.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_43:SetPhysicalActorType(1)
	Actor_43:SetPhysicalShape(5)
	Actor_43.ExtraInfo.Name = ""
	Actor_43.ExtraInfo.NameColorR = 1.36332e-041
	Actor_43.ExtraInfo.NameColorG = 1
	Actor_43.ExtraInfo.NameColorB = 2.35106e-038
	Actor_43H = ActorHandler(Actor_43)
	environment:AddActorObject(Actor_43H)

	Actor_44 = ActorObjectInfo(44)
	Actor_44:SetRenderType(1)
	Actor_44.DisplayDesc.ModelId = 0
	Actor_44.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_26.osgb"
	Actor_44.DisplayDesc.Outfit = ""
	Actor_44.DisplayDesc.Weapon = ""
	Actor_44.DisplayDesc.Mode = ""
	Actor_44.DisplayDesc.UseLight = false
	Actor_44.DisplayDesc.CastShadow = false
	Actor_44.DisplayDesc.ColorR = 1.4013e-045
	Actor_44.DisplayDesc.ColorG = 0
	Actor_44.DisplayDesc.ColorB = 0
	Actor_44.DisplayDesc.ColorA = 0
	Actor_44:SetModelState(1)
	Actor_44.PhysicDesc.Pos.X = 509.5
	Actor_44.PhysicDesc.Pos.Y = 7.8125
	Actor_44.PhysicDesc.Pos.Z = 463.5
	Actor_44.PhysicDesc.Pos.Rotation = 0
	Actor_44.PhysicDesc.Density = 8.49879e-031
	Actor_44.PhysicDesc.Collidable = true
	Actor_44.PhysicDesc.SizeX = 0
	Actor_44.PhysicDesc.SizeY = 0
	Actor_44.PhysicDesc.SizeZ = 0
	Actor_44.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_26.phy"
	Actor_44:SetPhysicalActorType(1)
	Actor_44:SetPhysicalShape(5)
	Actor_44.ExtraInfo.Name = ""
	Actor_44.ExtraInfo.NameColorR = 0
	Actor_44.ExtraInfo.NameColorG = 0
	Actor_44.ExtraInfo.NameColorB = 0
	Actor_44H = ActorHandler(Actor_44)
	environment:AddActorObject(Actor_44H)

	Actor_45 = ActorObjectInfo(45)
	Actor_45:SetRenderType(1)
	Actor_45.DisplayDesc.ModelId = 131074
	Actor_45.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_26.osgb"
	Actor_45.DisplayDesc.Outfit = ""
	Actor_45.DisplayDesc.Weapon = ""
	Actor_45.DisplayDesc.Mode = ""
	Actor_45.DisplayDesc.UseLight = false
	Actor_45.DisplayDesc.CastShadow = true
	Actor_45.DisplayDesc.ColorR = 4.46451e-024
	Actor_45.DisplayDesc.ColorG = 3.36285e-023
	Actor_45.DisplayDesc.ColorB = 4.62428e-044
	Actor_45.DisplayDesc.ColorA = 0
	Actor_45:SetModelState(1)
	Actor_45.PhysicDesc.Pos.X = 513.5
	Actor_45.PhysicDesc.Pos.Y = 7.8125
	Actor_45.PhysicDesc.Pos.Z = 463.5
	Actor_45.PhysicDesc.Pos.Rotation = 0
	Actor_45.PhysicDesc.Density = 2.38773e-039
	Actor_45.PhysicDesc.Collidable = true
	Actor_45.PhysicDesc.SizeX = 4.57352e-038
	Actor_45.PhysicDesc.SizeY = 6.88692e-031
	Actor_45.PhysicDesc.SizeZ = 1.83675e-040
	Actor_45.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_26.phy"
	Actor_45:SetPhysicalActorType(1)
	Actor_45:SetPhysicalShape(5)
	Actor_45.ExtraInfo.Name = ""
	Actor_45.ExtraInfo.NameColorR = 9.80909e-045
	Actor_45.ExtraInfo.NameColorG = 3.60134e-043
	Actor_45.ExtraInfo.NameColorB = 1.02295e-043
	Actor_45H = ActorHandler(Actor_45)
	environment:AddActorObject(Actor_45H)

	Actor_46 = ActorObjectInfo(46)
	Actor_46:SetRenderType(1)
	Actor_46.DisplayDesc.ModelId = 39
	Actor_46.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_26.osgb"
	Actor_46.DisplayDesc.Outfit = ""
	Actor_46.DisplayDesc.Weapon = ""
	Actor_46.DisplayDesc.Mode = ""
	Actor_46.DisplayDesc.UseLight = false
	Actor_46.DisplayDesc.CastShadow = true
	Actor_46.DisplayDesc.ColorR = 0
	Actor_46.DisplayDesc.ColorG = 0
	Actor_46.DisplayDesc.ColorB = 8.68805e-044
	Actor_46.DisplayDesc.ColorA = 0
	Actor_46:SetModelState(1)
	Actor_46.PhysicDesc.Pos.X = 509.5
	Actor_46.PhysicDesc.Pos.Y = 7.8125
	Actor_46.PhysicDesc.Pos.Z = 474.5
	Actor_46.PhysicDesc.Pos.Rotation = 0
	Actor_46.PhysicDesc.Density = 0
	Actor_46.PhysicDesc.Collidable = true
	Actor_46.PhysicDesc.SizeX = 3.40282e+038
	Actor_46.PhysicDesc.SizeY = 3.40282e+038
	Actor_46.PhysicDesc.SizeZ = -3.40282e+038
	Actor_46.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_26.phy"
	Actor_46:SetPhysicalActorType(1)
	Actor_46:SetPhysicalShape(5)
	Actor_46.ExtraInfo.Name = ""
	Actor_46.ExtraInfo.NameColorR = 0
	Actor_46.ExtraInfo.NameColorG = 0
	Actor_46.ExtraInfo.NameColorB = 0
	Actor_46H = ActorHandler(Actor_46)
	environment:AddActorObject(Actor_46H)

	Actor_47 = ActorObjectInfo(47)
	Actor_47:SetRenderType(1)
	Actor_47.DisplayDesc.ModelId = 131077
	Actor_47.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_26.osgb"
	Actor_47.DisplayDesc.Outfit = ""
	Actor_47.DisplayDesc.Weapon = ""
	Actor_47.DisplayDesc.Mode = ""
	Actor_47.DisplayDesc.UseLight = false
	Actor_47.DisplayDesc.CastShadow = false
	Actor_47.DisplayDesc.ColorR = 2.10195e-044
	Actor_47.DisplayDesc.ColorG = 1.4013e-045
	Actor_47.DisplayDesc.ColorB = 0
	Actor_47.DisplayDesc.ColorA = 7.27683e-024
	Actor_47:SetModelState(1)
	Actor_47.PhysicDesc.Pos.X = 513.5
	Actor_47.PhysicDesc.Pos.Y = 7.8125
	Actor_47.PhysicDesc.Pos.Z = 474.5
	Actor_47.PhysicDesc.Pos.Rotation = 0
	Actor_47.PhysicDesc.Density = 5.05469
	Actor_47.PhysicDesc.Collidable = true
	Actor_47.PhysicDesc.SizeX = -6.15625
	Actor_47.PhysicDesc.SizeY = 5.97266
	Actor_47.PhysicDesc.SizeZ = 5.74414
	Actor_47.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_26.phy"
	Actor_47:SetPhysicalActorType(1)
	Actor_47:SetPhysicalShape(5)
	Actor_47.ExtraInfo.Name = ""
	Actor_47.ExtraInfo.NameColorR = 0
	Actor_47.ExtraInfo.NameColorG = 0
	Actor_47.ExtraInfo.NameColorB = 0
	Actor_47H = ActorHandler(Actor_47)
	environment:AddActorObject(Actor_47H)

	Actor_48 = ActorObjectInfo(48)
	Actor_48:SetRenderType(1)
	Actor_48.DisplayDesc.ModelId = 131085
	Actor_48.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_27.osgb"
	Actor_48.DisplayDesc.Outfit = ""
	Actor_48.DisplayDesc.Weapon = ""
	Actor_48.DisplayDesc.Mode = ""
	Actor_48.DisplayDesc.UseLight = false
	Actor_48.DisplayDesc.CastShadow = false
	Actor_48.DisplayDesc.ColorR = 2.63315e-035
	Actor_48.DisplayDesc.ColorG = 4.57354e-038
	Actor_48.DisplayDesc.ColorB = 1.87163e-031
	Actor_48.DisplayDesc.ColorA = 1.83678e-040
	Actor_48:SetModelState(1)
	Actor_48.PhysicDesc.Pos.X = 505.375
	Actor_48.PhysicDesc.Pos.Y = 11.5234
	Actor_48.PhysicDesc.Pos.Z = 441.25
	Actor_48.PhysicDesc.Pos.Rotation = 180
	Actor_48.PhysicDesc.Density = 1.83674e-040
	Actor_48.PhysicDesc.Collidable = true
	Actor_48.PhysicDesc.SizeX = 9.8836e-031
	Actor_48.PhysicDesc.SizeY = 4.57367e-038
	Actor_48.PhysicDesc.SizeZ = 2.5714e-039
	Actor_48.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_27.phy"
	Actor_48:SetPhysicalActorType(1)
	Actor_48:SetPhysicalShape(5)
	Actor_48.ExtraInfo.Name = ""
	Actor_48.ExtraInfo.NameColorR = 2.45227e-043
	Actor_48.ExtraInfo.NameColorG = 0
	Actor_48.ExtraInfo.NameColorB = 2.10195e-044
	Actor_48H = ActorHandler(Actor_48)
	environment:AddActorObject(Actor_48H)

	Actor_49 = ActorObjectInfo(49)
	Actor_49:SetRenderType(1)
	Actor_49.DisplayDesc.ModelId = 131161
	Actor_49.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_27.osgb"
	Actor_49.DisplayDesc.Outfit = ""
	Actor_49.DisplayDesc.Weapon = ""
	Actor_49.DisplayDesc.Mode = ""
	Actor_49.DisplayDesc.UseLight = false
	Actor_49.DisplayDesc.CastShadow = true
	Actor_49.DisplayDesc.ColorR = -0.332043
	Actor_49.DisplayDesc.ColorG = 0.544999
	Actor_49.DisplayDesc.ColorB = 0.0488114
	Actor_49.DisplayDesc.ColorA = -0.837015
	Actor_49:SetModelState(1)
	Actor_49.PhysicDesc.Pos.X = 517.5
	Actor_49.PhysicDesc.Pos.Y = 11.5234
	Actor_49.PhysicDesc.Pos.Z = 441.25
	Actor_49.PhysicDesc.Pos.Rotation = 0
	Actor_49.PhysicDesc.Density = 0.0490005
	Actor_49.PhysicDesc.Collidable = true
	Actor_49.PhysicDesc.SizeX = 0
	Actor_49.PhysicDesc.SizeY = 1
	Actor_49.PhysicDesc.SizeZ = 0
	Actor_49.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_27.phy"
	Actor_49:SetPhysicalActorType(1)
	Actor_49:SetPhysicalShape(5)
	Actor_49.ExtraInfo.Name = ""
	Actor_49.ExtraInfo.NameColorR = 0
	Actor_49.ExtraInfo.NameColorG = 1
	Actor_49.ExtraInfo.NameColorB = 0
	Actor_49H = ActorHandler(Actor_49)
	environment:AddActorObject(Actor_49H)

	Actor_50 = ActorObjectInfo(50)
	Actor_50:SetRenderType(1)
	Actor_50.DisplayDesc.ModelId = 0
	Actor_50.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_28.osgb"
	Actor_50.DisplayDesc.Outfit = ""
	Actor_50.DisplayDesc.Weapon = ""
	Actor_50.DisplayDesc.Mode = ""
	Actor_50.DisplayDesc.UseLight = false
	Actor_50.DisplayDesc.CastShadow = false
	Actor_50.DisplayDesc.ColorR = 9.86514e-043
	Actor_50.DisplayDesc.ColorG = 7.76128e-031
	Actor_50.DisplayDesc.ColorB = 0
	Actor_50.DisplayDesc.ColorA = 0
	Actor_50:SetModelState(1)
	Actor_50.PhysicDesc.Pos.X = 511.5
	Actor_50.PhysicDesc.Pos.Y = 11.5234
	Actor_50.PhysicDesc.Pos.Z = 435.5
	Actor_50.PhysicDesc.Pos.Rotation = 90
	Actor_50.PhysicDesc.Density = -3.40282e+038
	Actor_50.PhysicDesc.Collidable = true
	Actor_50.PhysicDesc.SizeX = -3.40282e+038
	Actor_50.PhysicDesc.SizeY = 0
	Actor_50.PhysicDesc.SizeZ = 0.298828
	Actor_50.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_28.phy"
	Actor_50:SetPhysicalActorType(1)
	Actor_50:SetPhysicalShape(5)
	Actor_50.ExtraInfo.Name = ""
	Actor_50.ExtraInfo.NameColorR = 0
	Actor_50.ExtraInfo.NameColorG = 0
	Actor_50.ExtraInfo.NameColorB = 8.1425e-024
	Actor_50H = ActorHandler(Actor_50)
	environment:AddActorObject(Actor_50H)

	Actor_51 = ActorObjectInfo(51)
	Actor_51:SetRenderType(1)
	Actor_51.DisplayDesc.ModelId = -1056198656
	Actor_51.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_29.osgb"
	Actor_51.DisplayDesc.Outfit = ""
	Actor_51.DisplayDesc.Weapon = ""
	Actor_51.DisplayDesc.Mode = ""
	Actor_51.DisplayDesc.UseLight = false
	Actor_51.DisplayDesc.CastShadow = true
	Actor_51.DisplayDesc.ColorR = 2.06641
	Actor_51.DisplayDesc.ColorG = 3.44531
	Actor_51.DisplayDesc.ColorB = -8.96094
	Actor_51.DisplayDesc.ColorA = 2.06641
	Actor_51:SetModelState(1)
	Actor_51.PhysicDesc.Pos.X = 511.5
	Actor_51.PhysicDesc.Pos.Y = 11.5234
	Actor_51.PhysicDesc.Pos.Z = 435.5
	Actor_51.PhysicDesc.Pos.Rotation = 90
	Actor_51.PhysicDesc.Density = -8.96094
	Actor_51.PhysicDesc.Collidable = true
	Actor_51.PhysicDesc.SizeX = 6.66211
	Actor_51.PhysicDesc.SizeY = -8.96094
	Actor_51.PhysicDesc.SizeZ = 1.37695
	Actor_51.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_29.phy"
	Actor_51:SetPhysicalActorType(1)
	Actor_51:SetPhysicalShape(5)
	Actor_51.ExtraInfo.Name = ""
	Actor_51.ExtraInfo.NameColorR = 0
	Actor_51.ExtraInfo.NameColorG = -7.35156
	Actor_51.ExtraInfo.NameColorB = 2.06641
	Actor_51H = ActorHandler(Actor_51)
	environment:AddActorObject(Actor_51H)

	Actor_52 = ActorObjectInfo(52)
	Actor_52:SetRenderType(1)
	Actor_52.DisplayDesc.ModelId = 1065353216
	Actor_52.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_30.osgb"
	Actor_52.DisplayDesc.Outfit = ""
	Actor_52.DisplayDesc.Weapon = ""
	Actor_52.DisplayDesc.Mode = ""
	Actor_52.DisplayDesc.UseLight = false
	Actor_52.DisplayDesc.CastShadow = false
	Actor_52.DisplayDesc.ColorR = 1
	Actor_52.DisplayDesc.ColorG = 1
	Actor_52.DisplayDesc.ColorB = 1
	Actor_52.DisplayDesc.ColorA = 1
	Actor_52:SetModelState(1)
	Actor_52.PhysicDesc.Pos.X = 511.5
	Actor_52.PhysicDesc.Pos.Y = 11.5234
	Actor_52.PhysicDesc.Pos.Z = 435.5
	Actor_52.PhysicDesc.Pos.Rotation = 90
	Actor_52.PhysicDesc.Density = 1
	Actor_52.PhysicDesc.Collidable = true
	Actor_52.PhysicDesc.SizeX = 1
	Actor_52.PhysicDesc.SizeY = 1
	Actor_52.PhysicDesc.SizeZ = 1
	Actor_52.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_30.phy"
	Actor_52:SetPhysicalActorType(1)
	Actor_52:SetPhysicalShape(5)
	Actor_52.ExtraInfo.Name = ""
	Actor_52.ExtraInfo.NameColorR = 1
	Actor_52.ExtraInfo.NameColorG = 1
	Actor_52.ExtraInfo.NameColorB = 1
	Actor_52H = ActorHandler(Actor_52)
	environment:AddActorObject(Actor_52H)

	Actor_53 = ActorObjectInfo(53)
	Actor_53:SetRenderType(1)
	Actor_53.DisplayDesc.ModelId = 0
	Actor_53.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_31.osgb"
	Actor_53.DisplayDesc.Outfit = ""
	Actor_53.DisplayDesc.Weapon = ""
	Actor_53.DisplayDesc.Mode = ""
	Actor_53.DisplayDesc.UseLight = false
	Actor_53.DisplayDesc.CastShadow = false
	Actor_53.DisplayDesc.ColorR = 1
	Actor_53.DisplayDesc.ColorG = 0
	Actor_53.DisplayDesc.ColorB = 0
	Actor_53.DisplayDesc.ColorA = -1
	Actor_53:SetModelState(1)
	Actor_53.PhysicDesc.Pos.X = 511.5
	Actor_53.PhysicDesc.Pos.Y = 11.5234
	Actor_53.PhysicDesc.Pos.Z = 435.5
	Actor_53.PhysicDesc.Pos.Rotation = 90
	Actor_53.PhysicDesc.Density = 4.57358e-038
	Actor_53.PhysicDesc.Collidable = true
	Actor_53.PhysicDesc.SizeX = 0
	Actor_53.PhysicDesc.SizeY = 0
	Actor_53.PhysicDesc.SizeZ = 0
	Actor_53.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_31.phy"
	Actor_53:SetPhysicalActorType(1)
	Actor_53:SetPhysicalShape(5)
	Actor_53.ExtraInfo.Name = ""
	Actor_53.ExtraInfo.NameColorR = 0
	Actor_53.ExtraInfo.NameColorG = 0
	Actor_53.ExtraInfo.NameColorB = 0
	Actor_53H = ActorHandler(Actor_53)
	environment:AddActorObject(Actor_53H)

	Actor_54 = ActorObjectInfo(54)
	Actor_54:SetRenderType(1)
	Actor_54.DisplayDesc.ModelId = 0
	Actor_54.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_32.osgb"
	Actor_54.DisplayDesc.Outfit = ""
	Actor_54.DisplayDesc.Weapon = ""
	Actor_54.DisplayDesc.Mode = ""
	Actor_54.DisplayDesc.UseLight = false
	Actor_54.DisplayDesc.CastShadow = false
	Actor_54.DisplayDesc.ColorR = 1.4013e-045
	Actor_54.DisplayDesc.ColorG = 0
	Actor_54.DisplayDesc.ColorB = 0
	Actor_54.DisplayDesc.ColorA = 1.4013e-045
	Actor_54:SetModelState(1)
	Actor_54.PhysicDesc.Pos.X = 511.5
	Actor_54.PhysicDesc.Pos.Y = 11.5234
	Actor_54.PhysicDesc.Pos.Z = 435.5
	Actor_54.PhysicDesc.Pos.Rotation = 90
	Actor_54.PhysicDesc.Density = 0
	Actor_54.PhysicDesc.Collidable = true
	Actor_54.PhysicDesc.SizeX = 0
	Actor_54.PhysicDesc.SizeY = 0
	Actor_54.PhysicDesc.SizeZ = 0
	Actor_54.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_32.phy"
	Actor_54:SetPhysicalActorType(1)
	Actor_54:SetPhysicalShape(5)
	Actor_54.ExtraInfo.Name = ""
	Actor_54.ExtraInfo.NameColorR = 0
	Actor_54.ExtraInfo.NameColorG = 0
	Actor_54.ExtraInfo.NameColorB = 0
	Actor_54H = ActorHandler(Actor_54)
	environment:AddActorObject(Actor_54H)

	Actor_55 = ActorObjectInfo(55)
	Actor_55:SetRenderType(1)
	Actor_55.DisplayDesc.ModelId = 0
	Actor_55.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_33.osgb"
	Actor_55.DisplayDesc.Outfit = ""
	Actor_55.DisplayDesc.Weapon = ""
	Actor_55.DisplayDesc.Mode = ""
	Actor_55.DisplayDesc.UseLight = false
	Actor_55.DisplayDesc.CastShadow = false
	Actor_55.DisplayDesc.ColorR = 1
	Actor_55.DisplayDesc.ColorG = 0
	Actor_55.DisplayDesc.ColorB = 0
	Actor_55.DisplayDesc.ColorA = -1
	Actor_55:SetModelState(1)
	Actor_55.PhysicDesc.Pos.X = 502.5
	Actor_55.PhysicDesc.Pos.Y = 10.1563
	Actor_55.PhysicDesc.Pos.Z = 455.5
	Actor_55.PhysicDesc.Pos.Rotation = 90
	Actor_55.PhysicDesc.Density = 4.57358e-038
	Actor_55.PhysicDesc.Collidable = true
	Actor_55.PhysicDesc.SizeX = 0
	Actor_55.PhysicDesc.SizeY = -6.90039
	Actor_55.PhysicDesc.SizeZ = 35.1563
	Actor_55.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_33.phy"
	Actor_55:SetPhysicalActorType(1)
	Actor_55:SetPhysicalShape(5)
	Actor_55.ExtraInfo.Name = ""
	Actor_55.ExtraInfo.NameColorR = 0
	Actor_55.ExtraInfo.NameColorG = 0
	Actor_55.ExtraInfo.NameColorB = 0
	Actor_55H = ActorHandler(Actor_55)
	environment:AddActorObject(Actor_55H)

	Actor_56 = ActorObjectInfo(56)
	Actor_56:SetRenderType(1)
	Actor_56.DisplayDesc.ModelId = 144629820
	Actor_56.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_34.osgb"
	Actor_56.DisplayDesc.Outfit = ""
	Actor_56.DisplayDesc.Weapon = ""
	Actor_56.DisplayDesc.Mode = ""
	Actor_56.DisplayDesc.UseLight = false
	Actor_56.DisplayDesc.CastShadow = false
	Actor_56.DisplayDesc.ColorR = 1.03696e-043
	Actor_56.DisplayDesc.ColorG = 9.80909e-044
	Actor_56.DisplayDesc.ColorB = 0
	Actor_56.DisplayDesc.ColorA = 0
	Actor_56:SetModelState(1)
	Actor_56.PhysicDesc.Pos.X = 504.5
	Actor_56.PhysicDesc.Pos.Y = 11.5234
	Actor_56.PhysicDesc.Pos.Z = 450.5
	Actor_56.PhysicDesc.Pos.Rotation = 90
	Actor_56.PhysicDesc.Density = 2.8026e-044
	Actor_56.PhysicDesc.Collidable = true
	Actor_56.PhysicDesc.SizeX = 3.36312e-044
	Actor_56.PhysicDesc.SizeY = 3.50325e-044
	Actor_56.PhysicDesc.SizeZ = 2.57149e-039
	Actor_56.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_34.phy"
	Actor_56:SetPhysicalActorType(1)
	Actor_56:SetPhysicalShape(5)
	Actor_56.ExtraInfo.Name = ""
	Actor_56.ExtraInfo.NameColorR = 9.46509e-034
	Actor_56.ExtraInfo.NameColorG = 0
	Actor_56.ExtraInfo.NameColorB = 0
	Actor_56H = ActorHandler(Actor_56)
	environment:AddActorObject(Actor_56H)

	Actor_57 = ActorObjectInfo(57)
	Actor_57:SetRenderType(1)
	Actor_57.DisplayDesc.ModelId = 0
	Actor_57.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_34.osgb"
	Actor_57.DisplayDesc.Outfit = ""
	Actor_57.DisplayDesc.Weapon = ""
	Actor_57.DisplayDesc.Mode = ""
	Actor_57.DisplayDesc.UseLight = false
	Actor_57.DisplayDesc.CastShadow = false
	Actor_57.DisplayDesc.ColorR = 0
	Actor_57.DisplayDesc.ColorG = -2.21459e+009
	Actor_57.DisplayDesc.ColorB = 4.2039e-045
	Actor_57.DisplayDesc.ColorA = 0
	Actor_57:SetModelState(1)
	Actor_57.PhysicDesc.Pos.X = 518.5
	Actor_57.PhysicDesc.Pos.Y = 11.5234
	Actor_57.PhysicDesc.Pos.Z = 450.5
	Actor_57.PhysicDesc.Pos.Rotation = -90
	Actor_57.PhysicDesc.Density = 1.10703e-043
	Actor_57.PhysicDesc.Collidable = true
	Actor_57.PhysicDesc.SizeX = 1.4013e-044
	Actor_57.PhysicDesc.SizeY = 0
	Actor_57.PhysicDesc.SizeZ = 9.18341e-041
	Actor_57.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_34.phy"
	Actor_57:SetPhysicalActorType(1)
	Actor_57:SetPhysicalShape(5)
	Actor_57.ExtraInfo.Name = ""
	Actor_57.ExtraInfo.NameColorR = 0
	Actor_57.ExtraInfo.NameColorG = 9.18341e-041
	Actor_57.ExtraInfo.NameColorB = 4.2039e-045
	Actor_57H = ActorHandler(Actor_57)
	environment:AddActorObject(Actor_57H)

	Actor_58 = ActorObjectInfo(58)
	Actor_58:SetRenderType(1)
	Actor_58.DisplayDesc.ModelId = 131074
	Actor_58.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_35.osgb"
	Actor_58.DisplayDesc.Outfit = ""
	Actor_58.DisplayDesc.Weapon = ""
	Actor_58.DisplayDesc.Mode = ""
	Actor_58.DisplayDesc.UseLight = false
	Actor_58.DisplayDesc.CastShadow = false
	Actor_58.DisplayDesc.ColorR = 4.2039e-045
	Actor_58.DisplayDesc.ColorG = 5.60519e-045
	Actor_58.DisplayDesc.ColorB = 7.00649e-045
	Actor_58.DisplayDesc.ColorA = 8.40779e-045
	Actor_58:SetModelState(1)
	Actor_58.PhysicDesc.Pos.X = 444
	Actor_58.PhysicDesc.Pos.Y = 0
	Actor_58.PhysicDesc.Pos.Z = 511
	Actor_58.PhysicDesc.Pos.Rotation = -90
	Actor_58.PhysicDesc.Density = 5.32493e-044
	Actor_58.PhysicDesc.Collidable = true
	Actor_58.PhysicDesc.SizeX = 0
	Actor_58.PhysicDesc.SizeY = 2.10195e-044
	Actor_58.PhysicDesc.SizeZ = 2.8026e-045
	Actor_58.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_35.phy"
	Actor_58:SetPhysicalActorType(1)
	Actor_58:SetPhysicalShape(5)
	Actor_58.ExtraInfo.Name = ""
	Actor_58.ExtraInfo.NameColorR = 3.19932e-024
	Actor_58.ExtraInfo.NameColorG = 0
	Actor_58.ExtraInfo.NameColorB = 2.10195e-044
	Actor_58H = ActorHandler(Actor_58)
	environment:AddActorObject(Actor_58H)

	Actor_59 = ActorObjectInfo(59)
	Actor_59:SetRenderType(1)
	Actor_59.DisplayDesc.ModelId = 0
	Actor_59.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_36.osgb"
	Actor_59.DisplayDesc.Outfit = ""
	Actor_59.DisplayDesc.Weapon = ""
	Actor_59.DisplayDesc.Mode = ""
	Actor_59.DisplayDesc.UseLight = false
	Actor_59.DisplayDesc.CastShadow = true
	Actor_59.DisplayDesc.ColorR = 0
	Actor_59.DisplayDesc.ColorG = 0
	Actor_59.DisplayDesc.ColorB = 0
	Actor_59.DisplayDesc.ColorA = 0
	Actor_59:SetModelState(1)
	Actor_59.PhysicDesc.Pos.X = 444
	Actor_59.PhysicDesc.Pos.Y = 0
	Actor_59.PhysicDesc.Pos.Z = 511
	Actor_59.PhysicDesc.Pos.Rotation = -90
	Actor_59.PhysicDesc.Density = 0
	Actor_59.PhysicDesc.Collidable = true
	Actor_59.PhysicDesc.SizeX = 0
	Actor_59.PhysicDesc.SizeY = 0
	Actor_59.PhysicDesc.SizeZ = 0
	Actor_59.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_36.phy"
	Actor_59:SetPhysicalActorType(1)
	Actor_59:SetPhysicalShape(5)
	Actor_59.ExtraInfo.Name = ""
	Actor_59.ExtraInfo.NameColorR = 0.576172
	Actor_59.ExtraInfo.NameColorG = 0.900391
	Actor_59.ExtraInfo.NameColorB = 0.599609
	Actor_59H = ActorHandler(Actor_59)
	environment:AddActorObject(Actor_59H)

	Actor_60 = ActorObjectInfo(60)
	Actor_60:SetRenderType(1)
	Actor_60.DisplayDesc.ModelId = 0
	Actor_60.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_37.osgb"
	Actor_60.DisplayDesc.Outfit = ""
	Actor_60.DisplayDesc.Weapon = ""
	Actor_60.DisplayDesc.Mode = ""
	Actor_60.DisplayDesc.UseLight = false
	Actor_60.DisplayDesc.CastShadow = true
	Actor_60.DisplayDesc.ColorR = 0
	Actor_60.DisplayDesc.ColorG = 0
	Actor_60.DisplayDesc.ColorB = 0
	Actor_60.DisplayDesc.ColorA = 0
	Actor_60:SetModelState(1)
	Actor_60.PhysicDesc.Pos.X = 444
	Actor_60.PhysicDesc.Pos.Y = 0
	Actor_60.PhysicDesc.Pos.Z = 511
	Actor_60.PhysicDesc.Pos.Rotation = -90
	Actor_60.PhysicDesc.Density = 0
	Actor_60.PhysicDesc.Collidable = true
	Actor_60.PhysicDesc.SizeX = 0
	Actor_60.PhysicDesc.SizeY = 0
	Actor_60.PhysicDesc.SizeZ = 0
	Actor_60.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_37.phy"
	Actor_60:SetPhysicalActorType(1)
	Actor_60:SetPhysicalShape(5)
	Actor_60.ExtraInfo.Name = ""
	Actor_60.ExtraInfo.NameColorR = 2.13232e-024
	Actor_60.ExtraInfo.NameColorG = 0.851563
	Actor_60.ExtraInfo.NameColorB = -3.08286e-044
	Actor_60H = ActorHandler(Actor_60)
	environment:AddActorObject(Actor_60H)

	Actor_61 = ActorObjectInfo(61)
	Actor_61:SetRenderType(1)
	Actor_61.DisplayDesc.ModelId = 3
	Actor_61.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_38.osgb"
	Actor_61.DisplayDesc.Outfit = ""
	Actor_61.DisplayDesc.Weapon = ""
	Actor_61.DisplayDesc.Mode = ""
	Actor_61.DisplayDesc.UseLight = false
	Actor_61.DisplayDesc.CastShadow = false
	Actor_61.DisplayDesc.ColorR = 0
	Actor_61.DisplayDesc.ColorG = 0
	Actor_61.DisplayDesc.ColorB = 0
	Actor_61.DisplayDesc.ColorA = 0
	Actor_61:SetModelState(1)
	Actor_61.PhysicDesc.Pos.X = 444
	Actor_61.PhysicDesc.Pos.Y = 0
	Actor_61.PhysicDesc.Pos.Z = 511
	Actor_61.PhysicDesc.Pos.Rotation = -90
	Actor_61.PhysicDesc.Density = 0
	Actor_61.PhysicDesc.Collidable = true
	Actor_61.PhysicDesc.SizeX = 0
	Actor_61.PhysicDesc.SizeY = 0
	Actor_61.PhysicDesc.SizeZ = 0
	Actor_61.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_38.phy"
	Actor_61:SetPhysicalActorType(1)
	Actor_61:SetPhysicalShape(5)
	Actor_61.ExtraInfo.Name = ""
	Actor_61.ExtraInfo.NameColorR = 0
	Actor_61.ExtraInfo.NameColorG = 0
	Actor_61.ExtraInfo.NameColorB = 0
	Actor_61H = ActorHandler(Actor_61)
	environment:AddActorObject(Actor_61H)

	Actor_62 = ActorObjectInfo(62)
	Actor_62:SetRenderType(1)
	Actor_62.DisplayDesc.ModelId = 131076
	Actor_62.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_39.osgb"
	Actor_62.DisplayDesc.Outfit = ""
	Actor_62.DisplayDesc.Weapon = ""
	Actor_62.DisplayDesc.Mode = ""
	Actor_62.DisplayDesc.UseLight = false
	Actor_62.DisplayDesc.CastShadow = true
	Actor_62.DisplayDesc.ColorR = 1.81624e-031
	Actor_62.DisplayDesc.ColorG = 0
	Actor_62.DisplayDesc.ColorB = 4.34521
	Actor_62.DisplayDesc.ColorA = 0
	Actor_62:SetModelState(1)
	Actor_62.PhysicDesc.Pos.X = 444
	Actor_62.PhysicDesc.Pos.Y = 0
	Actor_62.PhysicDesc.Pos.Z = 511
	Actor_62.PhysicDesc.Pos.Rotation = -90
	Actor_62.PhysicDesc.Density = 0
	Actor_62.PhysicDesc.Collidable = true
	Actor_62.PhysicDesc.SizeX = 1.81693e-031
	Actor_62.PhysicDesc.SizeY = 3.0134e-023
	Actor_62.PhysicDesc.SizeZ = 0.919189
	Actor_62.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_39.phy"
	Actor_62:SetPhysicalActorType(1)
	Actor_62:SetPhysicalShape(5)
	Actor_62.ExtraInfo.Name = ""
	Actor_62.ExtraInfo.NameColorR = 3.96077e-041
	Actor_62.ExtraInfo.NameColorG = 0
	Actor_62.ExtraInfo.NameColorB = 2.10195e-044
	Actor_62H = ActorHandler(Actor_62)
	environment:AddActorObject(Actor_62H)

	Actor_63 = ActorObjectInfo(63)
	Actor_63:SetRenderType(1)
	Actor_63.DisplayDesc.ModelId = 131166
	Actor_63.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_40.osgb"
	Actor_63.DisplayDesc.Outfit = ""
	Actor_63.DisplayDesc.Weapon = ""
	Actor_63.DisplayDesc.Mode = ""
	Actor_63.DisplayDesc.UseLight = false
	Actor_63.DisplayDesc.CastShadow = false
	Actor_63.DisplayDesc.ColorR = 1.02316e-034
	Actor_63.DisplayDesc.ColorG = 4.57353e-038
	Actor_63.DisplayDesc.ColorB = 6.4747e-023
	Actor_63.DisplayDesc.ColorA = 8.52005e-023
	Actor_63:SetModelState(1)
	Actor_63.PhysicDesc.Pos.X = 444
	Actor_63.PhysicDesc.Pos.Y = 0
	Actor_63.PhysicDesc.Pos.Z = 511
	Actor_63.PhysicDesc.Pos.Rotation = -90
	Actor_63.PhysicDesc.Density = 0
	Actor_63.PhysicDesc.Collidable = true
	Actor_63.PhysicDesc.SizeX = 2.29592e-039
	Actor_63.PhysicDesc.SizeY = 1.05325e-034
	Actor_63.PhysicDesc.SizeZ = 7.52805e-031
	Actor_63.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_40.phy"
	Actor_63:SetPhysicalActorType(1)
	Actor_63:SetPhysicalShape(5)
	Actor_63.ExtraInfo.Name = ""
	Actor_63.ExtraInfo.NameColorR = 0.925
	Actor_63.ExtraInfo.NameColorG = 0.925
	Actor_63.ExtraInfo.NameColorB = 0
	Actor_63H = ActorHandler(Actor_63)
	environment:AddActorObject(Actor_63H)

	Actor_64 = ActorObjectInfo(64)
	Actor_64:SetRenderType(1)
	Actor_64.DisplayDesc.ModelId = 0
	Actor_64.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_41.osgb"
	Actor_64.DisplayDesc.Outfit = ""
	Actor_64.DisplayDesc.Weapon = ""
	Actor_64.DisplayDesc.Mode = ""
	Actor_64.DisplayDesc.UseLight = false
	Actor_64.DisplayDesc.CastShadow = false
	Actor_64.DisplayDesc.ColorR = 1.05327e-034
	Actor_64.DisplayDesc.ColorG = 1.31224e-038
	Actor_64.DisplayDesc.ColorB = 0
	Actor_64.DisplayDesc.ColorA = 0
	Actor_64:SetModelState(1)
	Actor_64.PhysicDesc.Pos.X = 444
	Actor_64.PhysicDesc.Pos.Y = 0
	Actor_64.PhysicDesc.Pos.Z = 511
	Actor_64.PhysicDesc.Pos.Rotation = -90
	Actor_64.PhysicDesc.Density = 0
	Actor_64.PhysicDesc.Collidable = true
	Actor_64.PhysicDesc.SizeX = 9.27267e-024
	Actor_64.PhysicDesc.SizeY = 0
	Actor_64.PhysicDesc.SizeZ = 0
	Actor_64.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_41.phy"
	Actor_64:SetPhysicalActorType(1)
	Actor_64:SetPhysicalShape(5)
	Actor_64.ExtraInfo.Name = ""
	Actor_64.ExtraInfo.NameColorR = 0
	Actor_64.ExtraInfo.NameColorG = 9.27271e-024
	Actor_64.ExtraInfo.NameColorB = 4.88281
	Actor_64H = ActorHandler(Actor_64)
	environment:AddActorObject(Actor_64H)

	Actor_65 = ActorObjectInfo(65)
	Actor_65:SetRenderType(1)
	Actor_65.DisplayDesc.ModelId = 0
	Actor_65.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.osgb"
	Actor_65.DisplayDesc.Outfit = ""
	Actor_65.DisplayDesc.Weapon = ""
	Actor_65.DisplayDesc.Mode = ""
	Actor_65.DisplayDesc.UseLight = false
	Actor_65.DisplayDesc.CastShadow = false
	Actor_65.DisplayDesc.ColorR = 1.4013e-045
	Actor_65.DisplayDesc.ColorG = 0
	Actor_65.DisplayDesc.ColorB = 0
	Actor_65.DisplayDesc.ColorA = 1.4013e-045
	Actor_65:SetModelState(1)
	Actor_65.PhysicDesc.Pos.X = 457.5
	Actor_65.PhysicDesc.Pos.Y = 0
	Actor_65.PhysicDesc.Pos.Z = 520.5
	Actor_65.PhysicDesc.Pos.Rotation = 90
	Actor_65.PhysicDesc.Density = 0
	Actor_65.PhysicDesc.Collidable = true
	Actor_65.PhysicDesc.SizeX = 0
	Actor_65.PhysicDesc.SizeY = 0
	Actor_65.PhysicDesc.SizeZ = 0
	Actor_65.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.phy"
	Actor_65:SetPhysicalActorType(1)
	Actor_65:SetPhysicalShape(5)
	Actor_65.ExtraInfo.Name = ""
	Actor_65.ExtraInfo.NameColorR = 0
	Actor_65.ExtraInfo.NameColorG = 0
	Actor_65.ExtraInfo.NameColorB = 0
	Actor_65H = ActorHandler(Actor_65)
	environment:AddActorObject(Actor_65H)

	Actor_66 = ActorObjectInfo(66)
	Actor_66:SetRenderType(1)
	Actor_66.DisplayDesc.ModelId = 0
	Actor_66.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.osgb"
	Actor_66.DisplayDesc.Outfit = ""
	Actor_66.DisplayDesc.Weapon = ""
	Actor_66.DisplayDesc.Mode = ""
	Actor_66.DisplayDesc.UseLight = false
	Actor_66.DisplayDesc.CastShadow = false
	Actor_66.DisplayDesc.ColorR = 0
	Actor_66.DisplayDesc.ColorG = 6.00689e-031
	Actor_66.DisplayDesc.ColorB = 0
	Actor_66.DisplayDesc.ColorA = 0
	Actor_66:SetModelState(1)
	Actor_66.PhysicDesc.Pos.X = 458.5
	Actor_66.PhysicDesc.Pos.Y = 0
	Actor_66.PhysicDesc.Pos.Z = 525.5
	Actor_66.PhysicDesc.Pos.Rotation = 90
	Actor_66.PhysicDesc.Density = 0
	Actor_66.PhysicDesc.Collidable = true
	Actor_66.PhysicDesc.SizeX = 0
	Actor_66.PhysicDesc.SizeY = 0
	Actor_66.PhysicDesc.SizeZ = 0
	Actor_66.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.phy"
	Actor_66:SetPhysicalActorType(1)
	Actor_66:SetPhysicalShape(5)
	Actor_66.ExtraInfo.Name = ""
	Actor_66.ExtraInfo.NameColorR = 3.19911e-024
	Actor_66.ExtraInfo.NameColorG = 0
	Actor_66.ExtraInfo.NameColorB = 0
	Actor_66H = ActorHandler(Actor_66)
	environment:AddActorObject(Actor_66H)

	Actor_67 = ActorObjectInfo(67)
	Actor_67:SetRenderType(1)
	Actor_67.DisplayDesc.ModelId = 0
	Actor_67.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.osgb"
	Actor_67.DisplayDesc.Outfit = ""
	Actor_67.DisplayDesc.Weapon = ""
	Actor_67.DisplayDesc.Mode = ""
	Actor_67.DisplayDesc.UseLight = false
	Actor_67.DisplayDesc.CastShadow = false
	Actor_67.DisplayDesc.ColorR = 4.57351e-038
	Actor_67.DisplayDesc.ColorG = 1.65313e-039
	Actor_67.DisplayDesc.ColorB = 4.09264e-034
	Actor_67.DisplayDesc.ColorA = 4.57367e-038
	Actor_67:SetModelState(1)
	Actor_67.PhysicDesc.Pos.X = 455.5
	Actor_67.PhysicDesc.Pos.Y = 0
	Actor_67.PhysicDesc.Pos.Z = 523.5
	Actor_67.PhysicDesc.Pos.Rotation = 90
	Actor_67.PhysicDesc.Density = 0
	Actor_67.PhysicDesc.Collidable = true
	Actor_67.PhysicDesc.SizeX = 1.4013e-044
	Actor_67.PhysicDesc.SizeY = 4.2039e-045
	Actor_67.PhysicDesc.SizeZ = 7.18306e-042
	Actor_67.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.phy"
	Actor_67:SetPhysicalActorType(1)
	Actor_67:SetPhysicalShape(5)
	Actor_67.ExtraInfo.Name = ""
	Actor_67.ExtraInfo.NameColorR = 2.10195e-044
	Actor_67.ExtraInfo.NameColorG = 2.8026e-045
	Actor_67.ExtraInfo.NameColorB = 0
	Actor_67H = ActorHandler(Actor_67)
	environment:AddActorObject(Actor_67H)

	Actor_68 = ActorObjectInfo(68)
	Actor_68:SetRenderType(1)
	Actor_68.DisplayDesc.ModelId = 1065353216
	Actor_68.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.osgb"
	Actor_68.DisplayDesc.Outfit = ""
	Actor_68.DisplayDesc.Weapon = ""
	Actor_68.DisplayDesc.Mode = ""
	Actor_68.DisplayDesc.UseLight = false
	Actor_68.DisplayDesc.CastShadow = false
	Actor_68.DisplayDesc.ColorR = 1
	Actor_68.DisplayDesc.ColorG = 1
	Actor_68.DisplayDesc.ColorB = 1
	Actor_68.DisplayDesc.ColorA = 1
	Actor_68:SetModelState(1)
	Actor_68.PhysicDesc.Pos.X = 459.5
	Actor_68.PhysicDesc.Pos.Y = 0
	Actor_68.PhysicDesc.Pos.Z = 522.5
	Actor_68.PhysicDesc.Pos.Rotation = 90
	Actor_68.PhysicDesc.Density = 1
	Actor_68.PhysicDesc.Collidable = true
	Actor_68.PhysicDesc.SizeX = 1
	Actor_68.PhysicDesc.SizeY = 1
	Actor_68.PhysicDesc.SizeZ = 1
	Actor_68.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.phy"
	Actor_68:SetPhysicalActorType(1)
	Actor_68:SetPhysicalShape(5)
	Actor_68.ExtraInfo.Name = ""
	Actor_68.ExtraInfo.NameColorR = 1
	Actor_68.ExtraInfo.NameColorG = 1
	Actor_68.ExtraInfo.NameColorB = 1
	Actor_68H = ActorHandler(Actor_68)
	environment:AddActorObject(Actor_68H)

	Actor_69 = ActorObjectInfo(69)
	Actor_69:SetRenderType(1)
	Actor_69.DisplayDesc.ModelId = 0
	Actor_69.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.osgb"
	Actor_69.DisplayDesc.Outfit = ""
	Actor_69.DisplayDesc.Weapon = ""
	Actor_69.DisplayDesc.Mode = ""
	Actor_69.DisplayDesc.UseLight = false
	Actor_69.DisplayDesc.CastShadow = true
	Actor_69.DisplayDesc.ColorR = 3.29635e-024
	Actor_69.DisplayDesc.ColorG = 1.80802e-031
	Actor_69.DisplayDesc.ColorB = 3.65912e-037
	Actor_69.DisplayDesc.ColorA = 1.82489e-031
	Actor_69:SetModelState(1)
	Actor_69.PhysicDesc.Pos.X = 457.5
	Actor_69.PhysicDesc.Pos.Y = 0
	Actor_69.PhysicDesc.Pos.Z = 524.5
	Actor_69.PhysicDesc.Pos.Rotation = 0
	Actor_69.PhysicDesc.Density = 2.8026e-045
	Actor_69.PhysicDesc.Collidable = true
	Actor_69.PhysicDesc.SizeX = 2.8026e-045
	Actor_69.PhysicDesc.SizeY = 4.2039e-045
	Actor_69.PhysicDesc.SizeZ = 5.60519e-045
	Actor_69.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.phy"
	Actor_69:SetPhysicalActorType(1)
	Actor_69:SetPhysicalShape(5)
	Actor_69.ExtraInfo.Name = ""
	Actor_69.ExtraInfo.NameColorR = 2.38221e-044
	Actor_69.ExtraInfo.NameColorG = 2.52234e-044
	Actor_69.ExtraInfo.NameColorB = 2.24208e-044
	Actor_69H = ActorHandler(Actor_69)
	environment:AddActorObject(Actor_69H)

	Actor_70 = ActorObjectInfo(70)
	Actor_70:SetRenderType(1)
	Actor_70.DisplayDesc.ModelId = 0
	Actor_70.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.osgb"
	Actor_70.DisplayDesc.Outfit = ""
	Actor_70.DisplayDesc.Weapon = ""
	Actor_70.DisplayDesc.Mode = ""
	Actor_70.DisplayDesc.UseLight = false
	Actor_70.DisplayDesc.CastShadow = true
	Actor_70.DisplayDesc.ColorR = 0
	Actor_70.DisplayDesc.ColorG = 9.21956e-041
	Actor_70.DisplayDesc.ColorB = 9.03915e-031
	Actor_70.DisplayDesc.ColorA = 4.57352e-038
	Actor_70:SetModelState(1)
	Actor_70.PhysicDesc.Pos.X = 459.5
	Actor_70.PhysicDesc.Pos.Y = 0
	Actor_70.PhysicDesc.Pos.Z = 526.5
	Actor_70.PhysicDesc.Pos.Rotation = 0
	Actor_70.PhysicDesc.Density = 0
	Actor_70.PhysicDesc.Collidable = true
	Actor_70.PhysicDesc.SizeX = 0
	Actor_70.PhysicDesc.SizeY = 0
	Actor_70.PhysicDesc.SizeZ = 0
	Actor_70.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.phy"
	Actor_70:SetPhysicalActorType(1)
	Actor_70:SetPhysicalShape(5)
	Actor_70.ExtraInfo.Name = ""
	Actor_70.ExtraInfo.NameColorR = 6.51156e-031
	Actor_70.ExtraInfo.NameColorG = 2.02038e-039
	Actor_70.ExtraInfo.NameColorB = 2.63311e-035
	Actor_70H = ActorHandler(Actor_70)
	environment:AddActorObject(Actor_70H)

	Actor_71 = ActorObjectInfo(71)
	Actor_71:SetRenderType(1)
	Actor_71.DisplayDesc.ModelId = 0
	Actor_71.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.osgb"
	Actor_71.DisplayDesc.Outfit = ""
	Actor_71.DisplayDesc.Weapon = ""
	Actor_71.DisplayDesc.Mode = ""
	Actor_71.DisplayDesc.UseLight = false
	Actor_71.DisplayDesc.CastShadow = false
	Actor_71.DisplayDesc.ColorR = 0
	Actor_71.DisplayDesc.ColorG = -1
	Actor_71.DisplayDesc.ColorB = 0
	Actor_71.DisplayDesc.ColorA = 0
	Actor_71:SetModelState(1)
	Actor_71.PhysicDesc.Pos.X = 458.5
	Actor_71.PhysicDesc.Pos.Y = 0
	Actor_71.PhysicDesc.Pos.Z = 521.5
	Actor_71.PhysicDesc.Pos.Rotation = -90
	Actor_71.PhysicDesc.Density = 0
	Actor_71.PhysicDesc.Collidable = true
	Actor_71.PhysicDesc.SizeX = 1
	Actor_71.PhysicDesc.SizeY = 0
	Actor_71.PhysicDesc.SizeZ = 0
	Actor_71.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.phy"
	Actor_71:SetPhysicalActorType(1)
	Actor_71:SetPhysicalShape(5)
	Actor_71.ExtraInfo.Name = ""
	Actor_71.ExtraInfo.NameColorR = -1
	Actor_71.ExtraInfo.NameColorG = 0
	Actor_71.ExtraInfo.NameColorB = 0
	Actor_71H = ActorHandler(Actor_71)
	environment:AddActorObject(Actor_71H)

	Actor_72 = ActorObjectInfo(72)
	Actor_72:SetRenderType(1)
	Actor_72.DisplayDesc.ModelId = 408484084
	Actor_72.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.osgb"
	Actor_72.DisplayDesc.Outfit = ""
	Actor_72.DisplayDesc.Weapon = ""
	Actor_72.DisplayDesc.Mode = ""
	Actor_72.DisplayDesc.UseLight = false
	Actor_72.DisplayDesc.CastShadow = true
	Actor_72.DisplayDesc.ColorR = 7.84932e-023
	Actor_72.DisplayDesc.ColorG = 2.69314e-020
	Actor_72.DisplayDesc.ColorB = 4.62428e-044
	Actor_72.DisplayDesc.ColorA = 4.76441e-044
	Actor_72:SetModelState(1)
	Actor_72.PhysicDesc.Pos.X = 455.5
	Actor_72.PhysicDesc.Pos.Y = 0
	Actor_72.PhysicDesc.Pos.Z = 519.5
	Actor_72.PhysicDesc.Pos.Rotation = -90
	Actor_72.PhysicDesc.Density = 2.38782e-039
	Actor_72.PhysicDesc.Collidable = true
	Actor_72.PhysicDesc.SizeX = 3.26238e-024
	Actor_72.PhysicDesc.SizeY = 3.11134e-031
	Actor_72.PhysicDesc.SizeZ = 0
	Actor_72.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.phy"
	Actor_72:SetPhysicalActorType(1)
	Actor_72:SetPhysicalShape(5)
	Actor_72.ExtraInfo.Name = ""
	Actor_72.ExtraInfo.NameColorR = 2.69314e-020
	Actor_72.ExtraInfo.NameColorG = 1.00893e-043
	Actor_72.ExtraInfo.NameColorB = 1.02295e-043
	Actor_72H = ActorHandler(Actor_72)
	environment:AddActorObject(Actor_72H)

	Actor_73 = ActorObjectInfo(73)
	Actor_73:SetRenderType(1)
	Actor_73.DisplayDesc.ModelId = 6
	Actor_73.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.osgb"
	Actor_73.DisplayDesc.Outfit = ""
	Actor_73.DisplayDesc.Weapon = ""
	Actor_73.DisplayDesc.Mode = ""
	Actor_73.DisplayDesc.UseLight = false
	Actor_73.DisplayDesc.CastShadow = false
	Actor_73.DisplayDesc.ColorR = 0
	Actor_73.DisplayDesc.ColorG = 1.28581e-039
	Actor_73.DisplayDesc.ColorB = 1.02316e-034
	Actor_73.DisplayDesc.ColorA = 4.57369e-038
	Actor_73:SetModelState(1)
	Actor_73.PhysicDesc.Pos.X = 460.5
	Actor_73.PhysicDesc.Pos.Y = 0
	Actor_73.PhysicDesc.Pos.Z = 527.5
	Actor_73.PhysicDesc.Pos.Rotation = 0
	Actor_73.PhysicDesc.Density = -0.265625
	Actor_73.PhysicDesc.Collidable = true
	Actor_73.PhysicDesc.SizeX = 1.68555
	Actor_73.PhysicDesc.SizeY = -0.265625
	Actor_73.PhysicDesc.SizeZ = 0.0878906
	Actor_73.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.phy"
	Actor_73:SetPhysicalActorType(1)
	Actor_73:SetPhysicalShape(5)
	Actor_73.ExtraInfo.Name = ""
	Actor_73.ExtraInfo.NameColorR = 0.798828
	Actor_73.ExtraInfo.NameColorG = -2.73438
	Actor_73.ExtraInfo.NameColorB = -0.0878906
	Actor_73H = ActorHandler(Actor_73)
	environment:AddActorObject(Actor_73H)

	Actor_74 = ActorObjectInfo(74)
	Actor_74:SetRenderType(1)
	Actor_74.DisplayDesc.ModelId = 0
	Actor_74.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.osgb"
	Actor_74.DisplayDesc.Outfit = ""
	Actor_74.DisplayDesc.Weapon = ""
	Actor_74.DisplayDesc.Mode = ""
	Actor_74.DisplayDesc.UseLight = false
	Actor_74.DisplayDesc.CastShadow = true
	Actor_74.DisplayDesc.ColorR = 0
	Actor_74.DisplayDesc.ColorG = 0
	Actor_74.DisplayDesc.ColorB = 0
	Actor_74.DisplayDesc.ColorA = 0
	Actor_74:SetModelState(1)
	Actor_74.PhysicDesc.Pos.X = 443.5
	Actor_74.PhysicDesc.Pos.Y = 0
	Actor_74.PhysicDesc.Pos.Z = 533.5
	Actor_74.PhysicDesc.Pos.Rotation = 0
	Actor_74.PhysicDesc.Density = 0
	Actor_74.PhysicDesc.Collidable = true
	Actor_74.PhysicDesc.SizeX = 0
	Actor_74.PhysicDesc.SizeY = 0
	Actor_74.PhysicDesc.SizeZ = 0
	Actor_74.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.phy"
	Actor_74:SetPhysicalActorType(1)
	Actor_74:SetPhysicalShape(5)
	Actor_74.ExtraInfo.Name = ""
	Actor_74.ExtraInfo.NameColorR = 0
	Actor_74.ExtraInfo.NameColorG = 0
	Actor_74.ExtraInfo.NameColorB = 0
	Actor_74H = ActorHandler(Actor_74)
	environment:AddActorObject(Actor_74H)

	Actor_75 = ActorObjectInfo(75)
	Actor_75:SetRenderType(1)
	Actor_75.DisplayDesc.ModelId = 0
	Actor_75.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.osgb"
	Actor_75.DisplayDesc.Outfit = ""
	Actor_75.DisplayDesc.Weapon = ""
	Actor_75.DisplayDesc.Mode = ""
	Actor_75.DisplayDesc.UseLight = false
	Actor_75.DisplayDesc.CastShadow = true
	Actor_75.DisplayDesc.ColorR = 0
	Actor_75.DisplayDesc.ColorG = 0
	Actor_75.DisplayDesc.ColorB = 0
	Actor_75.DisplayDesc.ColorA = 0
	Actor_75:SetModelState(1)
	Actor_75.PhysicDesc.Pos.X = 446.5
	Actor_75.PhysicDesc.Pos.Y = 0
	Actor_75.PhysicDesc.Pos.Z = 535.5
	Actor_75.PhysicDesc.Pos.Rotation = 0
	Actor_75.PhysicDesc.Density = 0
	Actor_75.PhysicDesc.Collidable = true
	Actor_75.PhysicDesc.SizeX = 0
	Actor_75.PhysicDesc.SizeY = 0
	Actor_75.PhysicDesc.SizeZ = 0
	Actor_75.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_42.phy"
	Actor_75:SetPhysicalActorType(1)
	Actor_75:SetPhysicalShape(5)
	Actor_75.ExtraInfo.Name = ""
	Actor_75.ExtraInfo.NameColorR = 0
	Actor_75.ExtraInfo.NameColorG = 0
	Actor_75.ExtraInfo.NameColorB = 0
	Actor_75H = ActorHandler(Actor_75)
	environment:AddActorObject(Actor_75H)

	Actor_76 = ActorObjectInfo(76)
	Actor_76:SetRenderType(1)
	Actor_76.DisplayDesc.ModelId = 414604640
	Actor_76.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.osgb"
	Actor_76.DisplayDesc.Outfit = ""
	Actor_76.DisplayDesc.Weapon = ""
	Actor_76.DisplayDesc.Mode = ""
	Actor_76.DisplayDesc.UseLight = false
	Actor_76.DisplayDesc.CastShadow = false
	Actor_76.DisplayDesc.ColorR = 1.54143e-044
	Actor_76.DisplayDesc.ColorG = 1.68156e-044
	Actor_76.DisplayDesc.ColorB = 1.82169e-044
	Actor_76.DisplayDesc.ColorA = 1.96182e-044
	Actor_76:SetModelState(1)
	Actor_76.PhysicDesc.Pos.X = 445.5
	Actor_76.PhysicDesc.Pos.Y = 0
	Actor_76.PhysicDesc.Pos.Z = 529.5
	Actor_76.PhysicDesc.Pos.Rotation = -90
	Actor_76.PhysicDesc.Density = 3.08286e-044
	Actor_76.PhysicDesc.Collidable = true
	Actor_76.PhysicDesc.SizeX = 3.40282e+038
	Actor_76.PhysicDesc.SizeY = 3.40282e+038
	Actor_76.PhysicDesc.SizeZ = -3.40282e+038
	Actor_76.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.phy"
	Actor_76:SetPhysicalActorType(1)
	Actor_76:SetPhysicalShape(5)
	Actor_76.ExtraInfo.Name = ""
	Actor_76.ExtraInfo.NameColorR = 0
	Actor_76.ExtraInfo.NameColorG = 0
	Actor_76.ExtraInfo.NameColorB = 0
	Actor_76H = ActorHandler(Actor_76)
	environment:AddActorObject(Actor_76H)

	Actor_77 = ActorObjectInfo(77)
	Actor_77:SetRenderType(1)
	Actor_77.DisplayDesc.ModelId = 144541660
	Actor_77.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.osgb"
	Actor_77.DisplayDesc.Outfit = ""
	Actor_77.DisplayDesc.Weapon = ""
	Actor_77.DisplayDesc.Mode = ""
	Actor_77.DisplayDesc.UseLight = false
	Actor_77.DisplayDesc.CastShadow = false
	Actor_77.DisplayDesc.ColorR = 0
	Actor_77.DisplayDesc.ColorG = 0
	Actor_77.DisplayDesc.ColorB = 1
	Actor_77.DisplayDesc.ColorA = 0
	Actor_77:SetModelState(1)
	Actor_77.PhysicDesc.Pos.X = 444.5
	Actor_77.PhysicDesc.Pos.Y = 0
	Actor_77.PhysicDesc.Pos.Z = 535.5
	Actor_77.PhysicDesc.Pos.Rotation = -90
	Actor_77.PhysicDesc.Density = 9.99204e-024
	Actor_77.PhysicDesc.Collidable = true
	Actor_77.PhysicDesc.SizeX = 0.01
	Actor_77.PhysicDesc.SizeY = 0
	Actor_77.PhysicDesc.SizeZ = 0
	Actor_77.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_44.phy"
	Actor_77:SetPhysicalActorType(1)
	Actor_77:SetPhysicalShape(5)
	Actor_77.ExtraInfo.Name = ""
	Actor_77.ExtraInfo.NameColorR = 2.8026e-045
	Actor_77.ExtraInfo.NameColorG = 0
	Actor_77.ExtraInfo.NameColorB = 0
	Actor_77H = ActorHandler(Actor_77)
	environment:AddActorObject(Actor_77H)

	Actor_78 = ActorObjectInfo(78)
	Actor_78:SetRenderType(1)
	Actor_78.DisplayDesc.ModelId = 131074
	Actor_78.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.osgb"
	Actor_78.DisplayDesc.Outfit = ""
	Actor_78.DisplayDesc.Weapon = ""
	Actor_78.DisplayDesc.Mode = ""
	Actor_78.DisplayDesc.UseLight = false
	Actor_78.DisplayDesc.CastShadow = true
	Actor_78.DisplayDesc.ColorR = 1.4013e-045
	Actor_78.DisplayDesc.ColorG = 9.1736e-031
	Actor_78.DisplayDesc.ColorB = 5.32493e-044
	Actor_78.DisplayDesc.ColorA = 4.62428e-044
	Actor_78:SetModelState(1)
	Actor_78.PhysicDesc.Pos.X = 446.5
	Actor_78.PhysicDesc.Pos.Y = 0
	Actor_78.PhysicDesc.Pos.Z = 532.5
	Actor_78.PhysicDesc.Pos.Rotation = -90
	Actor_78.PhysicDesc.Density = 9.80909e-045
	Actor_78.PhysicDesc.Collidable = true
	Actor_78.PhysicDesc.SizeX = 0
	Actor_78.PhysicDesc.SizeY = 0
	Actor_78.PhysicDesc.SizeZ = 0
	Actor_78.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.phy"
	Actor_78:SetPhysicalActorType(1)
	Actor_78:SetPhysicalShape(5)
	Actor_78.ExtraInfo.Name = ""
	Actor_78.ExtraInfo.NameColorR = 2.63314e-035
	Actor_78.ExtraInfo.NameColorG = 4.57352e-038
	Actor_78.ExtraInfo.NameColorB = 2.3873e-024
	Actor_78H = ActorHandler(Actor_78)
	environment:AddActorObject(Actor_78H)

	Actor_79 = ActorObjectInfo(79)
	Actor_79:SetRenderType(1)
	Actor_79.DisplayDesc.ModelId = 0
	Actor_79.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.osgb"
	Actor_79.DisplayDesc.Outfit = ""
	Actor_79.DisplayDesc.Weapon = ""
	Actor_79.DisplayDesc.Mode = ""
	Actor_79.DisplayDesc.UseLight = false
	Actor_79.DisplayDesc.CastShadow = true
	Actor_79.DisplayDesc.ColorR = 5.33569e-021
	Actor_79.DisplayDesc.ColorG = 1.83691e-040
	Actor_79.DisplayDesc.ColorB = 2.55799e-035
	Actor_79.DisplayDesc.ColorA = 1.31224e-038
	Actor_79:SetModelState(1)
	Actor_79.PhysicDesc.Pos.X = 441.5
	Actor_79.PhysicDesc.Pos.Y = 0
	Actor_79.PhysicDesc.Pos.Z = 534.5
	Actor_79.PhysicDesc.Pos.Rotation = 180
	Actor_79.PhysicDesc.Density = 0
	Actor_79.PhysicDesc.Collidable = true
	Actor_79.PhysicDesc.SizeX = 1.4013e-044
	Actor_79.PhysicDesc.SizeY = 4.2039e-045
	Actor_79.PhysicDesc.SizeZ = 7.18306e-042
	Actor_79.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_43.phy"
	Actor_79:SetPhysicalActorType(1)
	Actor_79:SetPhysicalShape(5)
	Actor_79.ExtraInfo.Name = ""
	Actor_79.ExtraInfo.NameColorR = 2.10195e-044
	Actor_79.ExtraInfo.NameColorG = 2.8026e-045
	Actor_79.ExtraInfo.NameColorB = 0
	Actor_79H = ActorHandler(Actor_79)
	environment:AddActorObject(Actor_79H)

	Actor_80 = ActorObjectInfo(80)
	Actor_80:SetRenderType(1)
	Actor_80.DisplayDesc.ModelId = 0
	Actor_80.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_45.osgb"
	Actor_80.DisplayDesc.Outfit = ""
	Actor_80.DisplayDesc.Weapon = ""
	Actor_80.DisplayDesc.Mode = ""
	Actor_80.DisplayDesc.UseLight = false
	Actor_80.DisplayDesc.CastShadow = false
	Actor_80.DisplayDesc.ColorR = 0
	Actor_80.DisplayDesc.ColorG = 9.21956e-041
	Actor_80.DisplayDesc.ColorB = 9.18484e-024
	Actor_80.DisplayDesc.ColorA = 7.14662e-044
	Actor_80:SetModelState(1)
	Actor_80.PhysicDesc.Pos.X = 444
	Actor_80.PhysicDesc.Pos.Y = 0
	Actor_80.PhysicDesc.Pos.Z = 511
	Actor_80.PhysicDesc.Pos.Rotation = -90
	Actor_80.PhysicDesc.Density = 0
	Actor_80.PhysicDesc.Collidable = true
	Actor_80.PhysicDesc.SizeX = 0
	Actor_80.PhysicDesc.SizeY = 0
	Actor_80.PhysicDesc.SizeZ = 0
	Actor_80.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_45.phy"
	Actor_80:SetPhysicalActorType(1)
	Actor_80:SetPhysicalShape(5)
	Actor_80.ExtraInfo.Name = ""
	Actor_80.ExtraInfo.NameColorR = 9.18523e-024
	Actor_80.ExtraInfo.NameColorG = 8.12753e-044
	Actor_80.ExtraInfo.NameColorB = 8.26766e-044
	Actor_80H = ActorHandler(Actor_80)
	environment:AddActorObject(Actor_80H)

	Actor_81 = ActorObjectInfo(81)
	Actor_81:SetRenderType(1)
	Actor_81.DisplayDesc.ModelId = 0
	Actor_81.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_46.osgb"
	Actor_81.DisplayDesc.Outfit = ""
	Actor_81.DisplayDesc.Weapon = ""
	Actor_81.DisplayDesc.Mode = ""
	Actor_81.DisplayDesc.UseLight = false
	Actor_81.DisplayDesc.CastShadow = false
	Actor_81.DisplayDesc.ColorR = 0
	Actor_81.DisplayDesc.ColorG = 9.21956e-041
	Actor_81.DisplayDesc.ColorB = 1.85765e-031
	Actor_81.DisplayDesc.ColorA = 1.62192e-023
	Actor_81:SetModelState(1)
	Actor_81.PhysicDesc.Pos.X = 444
	Actor_81.PhysicDesc.Pos.Y = 0
	Actor_81.PhysicDesc.Pos.Z = 511
	Actor_81.PhysicDesc.Pos.Rotation = -90
	Actor_81.PhysicDesc.Density = 0
	Actor_81.PhysicDesc.Collidable = true
	Actor_81.PhysicDesc.SizeX = 0
	Actor_81.PhysicDesc.SizeY = 0
	Actor_81.PhysicDesc.SizeZ = 0
	Actor_81.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_46.phy"
	Actor_81:SetPhysicalActorType(1)
	Actor_81:SetPhysicalShape(5)
	Actor_81.ExtraInfo.Name = ""
	Actor_81.ExtraInfo.NameColorR = 1.85765e-031
	Actor_81.ExtraInfo.NameColorG = 1.88125e-031
	Actor_81.ExtraInfo.NameColorB = 0
	Actor_81H = ActorHandler(Actor_81)
	environment:AddActorObject(Actor_81H)

	Actor_82 = ActorObjectInfo(82)
	Actor_82:SetRenderType(1)
	Actor_82.DisplayDesc.ModelId = 0
	Actor_82.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_47.osgb"
	Actor_82.DisplayDesc.Outfit = ""
	Actor_82.DisplayDesc.Weapon = ""
	Actor_82.DisplayDesc.Mode = ""
	Actor_82.DisplayDesc.UseLight = false
	Actor_82.DisplayDesc.CastShadow = true
	Actor_82.DisplayDesc.ColorR = 1.79118e-031
	Actor_82.DisplayDesc.ColorG = 1.65304e-039
	Actor_82.DisplayDesc.ColorB = 1.0533e-034
	Actor_82.DisplayDesc.ColorA = 0
	Actor_82:SetModelState(1)
	Actor_82.PhysicDesc.Pos.X = 444
	Actor_82.PhysicDesc.Pos.Y = 0
	Actor_82.PhysicDesc.Pos.Z = 511
	Actor_82.PhysicDesc.Pos.Rotation = -90
	Actor_82.PhysicDesc.Density = 2.8026e-045
	Actor_82.PhysicDesc.Collidable = true
	Actor_82.PhysicDesc.SizeX = 0
	Actor_82.PhysicDesc.SizeY = 0
	Actor_82.PhysicDesc.SizeZ = 1.28579e-039
	Actor_82.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_47.phy"
	Actor_82:SetPhysicalActorType(1)
	Actor_82:SetPhysicalShape(5)
	Actor_82.ExtraInfo.Name = ""
	Actor_82.ExtraInfo.NameColorR = -0.608387
	Actor_82.ExtraInfo.NameColorG = 0
	Actor_82.ExtraInfo.NameColorB = -0.608387
	Actor_82H = ActorHandler(Actor_82)
	environment:AddActorObject(Actor_82H)

	Actor_83 = ActorObjectInfo(83)
	Actor_83:SetRenderType(1)
	Actor_83.DisplayDesc.ModelId = 1065353216
	Actor_83.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_48.osgb"
	Actor_83.DisplayDesc.Outfit = ""
	Actor_83.DisplayDesc.Weapon = ""
	Actor_83.DisplayDesc.Mode = ""
	Actor_83.DisplayDesc.UseLight = false
	Actor_83.DisplayDesc.CastShadow = false
	Actor_83.DisplayDesc.ColorR = 1
	Actor_83.DisplayDesc.ColorG = 1
	Actor_83.DisplayDesc.ColorB = 1
	Actor_83.DisplayDesc.ColorA = 1
	Actor_83:SetModelState(1)
	Actor_83.PhysicDesc.Pos.X = 444
	Actor_83.PhysicDesc.Pos.Y = 0
	Actor_83.PhysicDesc.Pos.Z = 511
	Actor_83.PhysicDesc.Pos.Rotation = -90
	Actor_83.PhysicDesc.Density = 1
	Actor_83.PhysicDesc.Collidable = true
	Actor_83.PhysicDesc.SizeX = 1
	Actor_83.PhysicDesc.SizeY = 1
	Actor_83.PhysicDesc.SizeZ = 1
	Actor_83.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_48.phy"
	Actor_83:SetPhysicalActorType(1)
	Actor_83:SetPhysicalShape(5)
	Actor_83.ExtraInfo.Name = ""
	Actor_83.ExtraInfo.NameColorR = 1
	Actor_83.ExtraInfo.NameColorG = 1
	Actor_83.ExtraInfo.NameColorB = 1
	Actor_83H = ActorHandler(Actor_83)
	environment:AddActorObject(Actor_83H)

	Actor_84 = ActorObjectInfo(84)
	Actor_84:SetRenderType(1)
	Actor_84.DisplayDesc.ModelId = 0
	Actor_84.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_49.osgb"
	Actor_84.DisplayDesc.Outfit = ""
	Actor_84.DisplayDesc.Weapon = ""
	Actor_84.DisplayDesc.Mode = ""
	Actor_84.DisplayDesc.UseLight = false
	Actor_84.DisplayDesc.CastShadow = false
	Actor_84.DisplayDesc.ColorR = 1.4013e-045
	Actor_84.DisplayDesc.ColorG = 0
	Actor_84.DisplayDesc.ColorB = 0
	Actor_84.DisplayDesc.ColorA = 0
	Actor_84:SetModelState(1)
	Actor_84.PhysicDesc.Pos.X = 444
	Actor_84.PhysicDesc.Pos.Y = 0
	Actor_84.PhysicDesc.Pos.Z = 511
	Actor_84.PhysicDesc.Pos.Rotation = -90
	Actor_84.PhysicDesc.Density = 0
	Actor_84.PhysicDesc.Collidable = true
	Actor_84.PhysicDesc.SizeX = 0
	Actor_84.PhysicDesc.SizeY = 1.875
	Actor_84.PhysicDesc.SizeZ = 0
	Actor_84.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_49.phy"
	Actor_84:SetPhysicalActorType(1)
	Actor_84:SetPhysicalShape(5)
	Actor_84.ExtraInfo.Name = ""
	Actor_84.ExtraInfo.NameColorR = 1.875
	Actor_84.ExtraInfo.NameColorG = 0
	Actor_84.ExtraInfo.NameColorB = 0
	Actor_84H = ActorHandler(Actor_84)
	environment:AddActorObject(Actor_84H)

	Actor_85 = ActorObjectInfo(85)
	Actor_85:SetRenderType(1)
	Actor_85.DisplayDesc.ModelId = 157418825
	Actor_85.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_50.osgb"
	Actor_85.DisplayDesc.Outfit = ""
	Actor_85.DisplayDesc.Weapon = ""
	Actor_85.DisplayDesc.Mode = ""
	Actor_85.DisplayDesc.UseLight = false
	Actor_85.DisplayDesc.CastShadow = true
	Actor_85.DisplayDesc.ColorR = 0
	Actor_85.DisplayDesc.ColorG = 0
	Actor_85.DisplayDesc.ColorB = 3.44531
	Actor_85.DisplayDesc.ColorA = -6.89258
	Actor_85:SetModelState(1)
	Actor_85.PhysicDesc.Pos.X = 444
	Actor_85.PhysicDesc.Pos.Y = 0
	Actor_85.PhysicDesc.Pos.Z = 511
	Actor_85.PhysicDesc.Pos.Rotation = -90
	Actor_85.PhysicDesc.Density = 0
	Actor_85.PhysicDesc.Collidable = true
	Actor_85.PhysicDesc.SizeX = 0
	Actor_85.PhysicDesc.SizeY = 0
	Actor_85.PhysicDesc.SizeZ = 0
	Actor_85.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_50.phy"
	Actor_85:SetPhysicalActorType(1)
	Actor_85:SetPhysicalShape(5)
	Actor_85.ExtraInfo.Name = ""
	Actor_85.ExtraInfo.NameColorR = 0
	Actor_85.ExtraInfo.NameColorG = 0
	Actor_85.ExtraInfo.NameColorB = 0
	Actor_85H = ActorHandler(Actor_85)
	environment:AddActorObject(Actor_85H)

	Actor_86 = ActorObjectInfo(86)
	Actor_86:SetRenderType(1)
	Actor_86.DisplayDesc.ModelId = 131154
	Actor_86.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_51.osgb"
	Actor_86.DisplayDesc.Outfit = ""
	Actor_86.DisplayDesc.Weapon = ""
	Actor_86.DisplayDesc.Mode = ""
	Actor_86.DisplayDesc.UseLight = false
	Actor_86.DisplayDesc.CastShadow = false
	Actor_86.DisplayDesc.ColorR = 9.03231e-024
	Actor_86.DisplayDesc.ColorG = 9.23793e-024
	Actor_86.DisplayDesc.ColorB = 1.05328e-034
	Actor_86.DisplayDesc.ColorA = 1.00626e-038
	Actor_86:SetModelState(1)
	Actor_86.PhysicDesc.Pos.X = 444
	Actor_86.PhysicDesc.Pos.Y = 0
	Actor_86.PhysicDesc.Pos.Z = 511
	Actor_86.PhysicDesc.Pos.Rotation = -90
	Actor_86.PhysicDesc.Density = 9.77257e-024
	Actor_86.PhysicDesc.Collidable = true
	Actor_86.PhysicDesc.SizeX = 2.10195e-044
	Actor_86.PhysicDesc.SizeY = 463.5
	Actor_86.PhysicDesc.SizeZ = 6.05469
	Actor_86.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_51.phy"
	Actor_86:SetPhysicalActorType(1)
	Actor_86:SetPhysicalShape(5)
	Actor_86.ExtraInfo.Name = ""
	Actor_86.ExtraInfo.NameColorR = 1.37772e-039
	Actor_86.ExtraInfo.NameColorG = 2.3602e-038
	Actor_86.ExtraInfo.NameColorB = 0
	Actor_86H = ActorHandler(Actor_86)
	environment:AddActorObject(Actor_86H)

	Actor_87 = ActorObjectInfo(87)
	Actor_87:SetRenderType(1)
	Actor_87.DisplayDesc.ModelId = 1328701794
	Actor_87.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_52.osgb"
	Actor_87.DisplayDesc.Outfit = ""
	Actor_87.DisplayDesc.Weapon = ""
	Actor_87.DisplayDesc.Mode = ""
	Actor_87.DisplayDesc.UseLight = false
	Actor_87.DisplayDesc.CastShadow = false
	Actor_87.DisplayDesc.ColorR = 1.05325e-034
	Actor_87.DisplayDesc.ColorG = 4.57352e-038
	Actor_87.DisplayDesc.ColorB = 1.01445e-030
	Actor_87.DisplayDesc.ColorA = 9.18366e-040
	Actor_87:SetModelState(1)
	Actor_87.PhysicDesc.Pos.X = 444
	Actor_87.PhysicDesc.Pos.Y = 0
	Actor_87.PhysicDesc.Pos.Z = 511
	Actor_87.PhysicDesc.Pos.Rotation = -90
	Actor_87.PhysicDesc.Density = 3.60134e-043
	Actor_87.PhysicDesc.Collidable = true
	Actor_87.PhysicDesc.SizeX = 1.65314e-039
	Actor_87.PhysicDesc.SizeY = 1.02316e-034
	Actor_87.PhysicDesc.SizeZ = 1.38162e-023
	Actor_87.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_52.phy"
	Actor_87:SetPhysicalActorType(1)
	Actor_87:SetPhysicalShape(5)
	Actor_87.ExtraInfo.Name = ""
	Actor_87.ExtraInfo.NameColorR = 1.67892e-038
	Actor_87.ExtraInfo.NameColorG = 5.14409e-024
	Actor_87.ExtraInfo.NameColorB = -2
	Actor_87H = ActorHandler(Actor_87)
	environment:AddActorObject(Actor_87H)

	Actor_88 = ActorObjectInfo(88)
	Actor_88:SetRenderType(1)
	Actor_88.DisplayDesc.ModelId = 144629820
	Actor_88.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_53.osgb"
	Actor_88.DisplayDesc.Outfit = ""
	Actor_88.DisplayDesc.Weapon = ""
	Actor_88.DisplayDesc.Mode = ""
	Actor_88.DisplayDesc.UseLight = false
	Actor_88.DisplayDesc.CastShadow = false
	Actor_88.DisplayDesc.ColorR = 1.27518e-043
	Actor_88.DisplayDesc.ColorG = 1.21913e-043
	Actor_88.DisplayDesc.ColorB = 0
	Actor_88.DisplayDesc.ColorA = 0
	Actor_88:SetModelState(1)
	Actor_88.PhysicDesc.Pos.X = 444
	Actor_88.PhysicDesc.Pos.Y = 0
	Actor_88.PhysicDesc.Pos.Z = 511
	Actor_88.PhysicDesc.Pos.Rotation = -90
	Actor_88.PhysicDesc.Density = 8.40779e-045
	Actor_88.PhysicDesc.Collidable = true
	Actor_88.PhysicDesc.SizeX = 0
	Actor_88.PhysicDesc.SizeY = 0
	Actor_88.PhysicDesc.SizeZ = 2.5714e-039
	Actor_88.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_53.phy"
	Actor_88:SetPhysicalActorType(1)
	Actor_88:SetPhysicalShape(5)
	Actor_88.ExtraInfo.Name = ""
	Actor_88.ExtraInfo.NameColorR = 1.54143e-044
	Actor_88.ExtraInfo.NameColorG = 1.68156e-044
	Actor_88.ExtraInfo.NameColorB = 1.82169e-044
	Actor_88H = ActorHandler(Actor_88)
	environment:AddActorObject(Actor_88H)

	Actor_89 = ActorObjectInfo(89)
	Actor_89:SetRenderType(1)
	Actor_89.DisplayDesc.ModelId = 0
	Actor_89.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_54.osgb"
	Actor_89.DisplayDesc.Outfit = ""
	Actor_89.DisplayDesc.Weapon = ""
	Actor_89.DisplayDesc.Mode = ""
	Actor_89.DisplayDesc.UseLight = false
	Actor_89.DisplayDesc.CastShadow = false
	Actor_89.DisplayDesc.ColorR = 1.4013e-045
	Actor_89.DisplayDesc.ColorG = 0
	Actor_89.DisplayDesc.ColorB = 0
	Actor_89.DisplayDesc.ColorA = 1.4013e-045
	Actor_89:SetModelState(1)
	Actor_89.PhysicDesc.Pos.X = 444
	Actor_89.PhysicDesc.Pos.Y = 0
	Actor_89.PhysicDesc.Pos.Z = 511
	Actor_89.PhysicDesc.Pos.Rotation = -90
	Actor_89.PhysicDesc.Density = 0
	Actor_89.PhysicDesc.Collidable = true
	Actor_89.PhysicDesc.SizeX = 0
	Actor_89.PhysicDesc.SizeY = 0
	Actor_89.PhysicDesc.SizeZ = 0
	Actor_89.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_54.phy"
	Actor_89:SetPhysicalActorType(1)
	Actor_89:SetPhysicalShape(5)
	Actor_89.ExtraInfo.Name = ""
	Actor_89.ExtraInfo.NameColorR = 0
	Actor_89.ExtraInfo.NameColorG = 0
	Actor_89.ExtraInfo.NameColorB = 0
	Actor_89H = ActorHandler(Actor_89)
	environment:AddActorObject(Actor_89H)

	Actor_90 = ActorObjectInfo(90)
	Actor_90:SetRenderType(1)
	Actor_90.DisplayDesc.ModelId = 499218620
	Actor_90.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_55.osgb"
	Actor_90.DisplayDesc.Outfit = ""
	Actor_90.DisplayDesc.Weapon = ""
	Actor_90.DisplayDesc.Mode = ""
	Actor_90.DisplayDesc.UseLight = false
	Actor_90.DisplayDesc.CastShadow = false
	Actor_90.DisplayDesc.ColorR = 1.02321e-034
	Actor_90.DisplayDesc.ColorG = 7.44287e-023
	Actor_90.DisplayDesc.ColorB = 4.48984e+021
	Actor_90.DisplayDesc.ColorA = 1.00626e-038
	Actor_90:SetModelState(1)
	Actor_90.PhysicDesc.Pos.X = 444
	Actor_90.PhysicDesc.Pos.Y = 0
	Actor_90.PhysicDesc.Pos.Z = 511
	Actor_90.PhysicDesc.Pos.Rotation = -90
	Actor_90.PhysicDesc.Density = 7.82176e-024
	Actor_90.PhysicDesc.Collidable = true
	Actor_90.PhysicDesc.SizeX = 6.72623e-044
	Actor_90.PhysicDesc.SizeY = 3.13817e-024
	Actor_90.PhysicDesc.SizeZ = 7.44292e-023
	Actor_90.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_55.phy"
	Actor_90:SetPhysicalActorType(1)
	Actor_90:SetPhysicalShape(5)
	Actor_90.ExtraInfo.Name = ""
	Actor_90.ExtraInfo.NameColorR = 7.44296e-023
	Actor_90.ExtraInfo.NameColorG = 7.44296e-023
	Actor_90.ExtraInfo.NameColorB = 7.44296e-023
	Actor_90H = ActorHandler(Actor_90)
	environment:AddActorObject(Actor_90H)

	Actor_91 = ActorObjectInfo(91)
	Actor_91:SetRenderType(1)
	Actor_91.DisplayDesc.ModelId = 420957048
	Actor_91.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_56.osgb"
	Actor_91.DisplayDesc.Outfit = ""
	Actor_91.DisplayDesc.Weapon = ""
	Actor_91.DisplayDesc.Mode = ""
	Actor_91.DisplayDesc.UseLight = false
	Actor_91.DisplayDesc.CastShadow = false
	Actor_91.DisplayDesc.ColorR = 1.4013e-045
	Actor_91.DisplayDesc.ColorG = 7.84918e-023
	Actor_91.DisplayDesc.ColorB = 6.89215e+034
	Actor_91.DisplayDesc.ColorA = 3.25159e-024
	Actor_91:SetModelState(1)
	Actor_91.PhysicDesc.Pos.X = 444
	Actor_91.PhysicDesc.Pos.Y = 0
	Actor_91.PhysicDesc.Pos.Z = 511
	Actor_91.PhysicDesc.Pos.Rotation = -90
	Actor_91.PhysicDesc.Density = 3.01864e-023
	Actor_91.PhysicDesc.Collidable = true
	Actor_91.PhysicDesc.SizeX = 0
	Actor_91.PhysicDesc.SizeY = 2.8026e-045
	Actor_91.PhysicDesc.SizeZ = 7.84918e-023
	Actor_91.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_56.phy"
	Actor_91:SetPhysicalActorType(1)
	Actor_91:SetPhysicalShape(5)
	Actor_91.ExtraInfo.Name = ""
	Actor_91.ExtraInfo.NameColorR = 2.8026e-045
	Actor_91.ExtraInfo.NameColorG = 7.84918e-023
	Actor_91.ExtraInfo.NameColorB = 1.0232e-034
	Actor_91H = ActorHandler(Actor_91)
	environment:AddActorObject(Actor_91H)

	Actor_92 = ActorObjectInfo(92)
	Actor_92:SetRenderType(1)
	Actor_92.DisplayDesc.ModelId = 410659468
	Actor_92.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_57.osgb"
	Actor_92.DisplayDesc.Outfit = ""
	Actor_92.DisplayDesc.Weapon = ""
	Actor_92.DisplayDesc.Mode = ""
	Actor_92.DisplayDesc.UseLight = false
	Actor_92.DisplayDesc.CastShadow = false
	Actor_92.DisplayDesc.ColorR = 0
	Actor_92.DisplayDesc.ColorG = 5.68648e-023
	Actor_92.DisplayDesc.ColorB = 0
	Actor_92.DisplayDesc.ColorA = 1.00626e-038
	Actor_92:SetModelState(1)
	Actor_92.PhysicDesc.Pos.X = 444
	Actor_92.PhysicDesc.Pos.Y = 0
	Actor_92.PhysicDesc.Pos.Z = 511
	Actor_92.PhysicDesc.Pos.Rotation = -90
	Actor_92.PhysicDesc.Density = 7.82176e-024
	Actor_92.PhysicDesc.Collidable = true
	Actor_92.PhysicDesc.SizeX = 6.72623e-044
	Actor_92.PhysicDesc.SizeY = 0
	Actor_92.PhysicDesc.SizeZ = 5.68653e-023
	Actor_92.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_57.phy"
	Actor_92:SetPhysicalActorType(1)
	Actor_92:SetPhysicalShape(5)
	Actor_92.ExtraInfo.Name = ""
	Actor_92.ExtraInfo.NameColorR = 0
	Actor_92.ExtraInfo.NameColorG = 5.68658e-023
	Actor_92.ExtraInfo.NameColorB = 0
	Actor_92H = ActorHandler(Actor_92)
	environment:AddActorObject(Actor_92H)

	Actor_93 = ActorObjectInfo(93)
	Actor_93:SetRenderType(1)
	Actor_93.DisplayDesc.ModelId = 0
	Actor_93.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_58.osgb"
	Actor_93.DisplayDesc.Outfit = ""
	Actor_93.DisplayDesc.Weapon = ""
	Actor_93.DisplayDesc.Mode = ""
	Actor_93.DisplayDesc.UseLight = false
	Actor_93.DisplayDesc.CastShadow = false
	Actor_93.DisplayDesc.ColorR = -1
	Actor_93.DisplayDesc.ColorG = 0
	Actor_93.DisplayDesc.ColorB = 0
	Actor_93.DisplayDesc.ColorA = 5.23633
	Actor_93:SetModelState(1)
	Actor_93.PhysicDesc.Pos.X = 444
	Actor_93.PhysicDesc.Pos.Y = 0
	Actor_93.PhysicDesc.Pos.Z = 511
	Actor_93.PhysicDesc.Pos.Rotation = -90
	Actor_93.PhysicDesc.Density = 0
	Actor_93.PhysicDesc.Collidable = true
	Actor_93.PhysicDesc.SizeX = 0
	Actor_93.PhysicDesc.SizeY = 0
	Actor_93.PhysicDesc.SizeZ = 1.4013e-045
	Actor_93.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_58.phy"
	Actor_93:SetPhysicalActorType(1)
	Actor_93:SetPhysicalShape(5)
	Actor_93.ExtraInfo.Name = ""
	Actor_93.ExtraInfo.NameColorR = 0
	Actor_93.ExtraInfo.NameColorG = 0
	Actor_93.ExtraInfo.NameColorB = 0
	Actor_93H = ActorHandler(Actor_93)
	environment:AddActorObject(Actor_93H)

	Actor_94 = ActorObjectInfo(94)
	Actor_94:SetRenderType(1)
	Actor_94.DisplayDesc.ModelId = 1328701794
	Actor_94.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_59.osgb"
	Actor_94.DisplayDesc.Outfit = ""
	Actor_94.DisplayDesc.Weapon = ""
	Actor_94.DisplayDesc.Mode = ""
	Actor_94.DisplayDesc.UseLight = false
	Actor_94.DisplayDesc.CastShadow = false
	Actor_94.DisplayDesc.ColorR = 0
	Actor_94.DisplayDesc.ColorG = 7.00649e-045
	Actor_94.DisplayDesc.ColorB = 0
	Actor_94.DisplayDesc.ColorA = 5.60519e-045
	Actor_94:SetModelState(1)
	Actor_94.PhysicDesc.Pos.X = 444
	Actor_94.PhysicDesc.Pos.Y = 0
	Actor_94.PhysicDesc.Pos.Z = 511
	Actor_94.PhysicDesc.Pos.Rotation = -90
	Actor_94.PhysicDesc.Density = 4.57352e-038
	Actor_94.PhysicDesc.Collidable = true
	Actor_94.PhysicDesc.SizeX = 1.65304e-039
	Actor_94.PhysicDesc.SizeY = 1.0533e-034
	Actor_94.PhysicDesc.SizeZ = 0
	Actor_94.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_59.phy"
	Actor_94:SetPhysicalActorType(1)
	Actor_94:SetPhysicalShape(5)
	Actor_94.ExtraInfo.Name = ""
	Actor_94.ExtraInfo.NameColorR = 0
	Actor_94.ExtraInfo.NameColorG = 0
	Actor_94.ExtraInfo.NameColorB = 0
	Actor_94H = ActorHandler(Actor_94)
	environment:AddActorObject(Actor_94H)

	Actor_95 = ActorObjectInfo(95)
	Actor_95:SetRenderType(1)
	Actor_95.DisplayDesc.ModelId = 0
	Actor_95.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_60.osgb"
	Actor_95.DisplayDesc.Outfit = ""
	Actor_95.DisplayDesc.Weapon = ""
	Actor_95.DisplayDesc.Mode = ""
	Actor_95.DisplayDesc.UseLight = false
	Actor_95.DisplayDesc.CastShadow = true
	Actor_95.DisplayDesc.ColorR = 0
	Actor_95.DisplayDesc.ColorG = 0
	Actor_95.DisplayDesc.ColorB = 0
	Actor_95.DisplayDesc.ColorA = 0
	Actor_95:SetModelState(1)
	Actor_95.PhysicDesc.Pos.X = 444
	Actor_95.PhysicDesc.Pos.Y = 0
	Actor_95.PhysicDesc.Pos.Z = 511
	Actor_95.PhysicDesc.Pos.Rotation = -90
	Actor_95.PhysicDesc.Density = 0
	Actor_95.PhysicDesc.Collidable = true
	Actor_95.PhysicDesc.SizeX = 0
	Actor_95.PhysicDesc.SizeY = 0
	Actor_95.PhysicDesc.SizeZ = 0
	Actor_95.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_60.phy"
	Actor_95:SetPhysicalActorType(1)
	Actor_95:SetPhysicalShape(5)
	Actor_95.ExtraInfo.Name = ""
	Actor_95.ExtraInfo.NameColorR = 0
	Actor_95.ExtraInfo.NameColorG = 0
	Actor_95.ExtraInfo.NameColorB = 0
	Actor_95H = ActorHandler(Actor_95)
	environment:AddActorObject(Actor_95H)

	Actor_96 = ActorObjectInfo(96)
	Actor_96:SetRenderType(1)
	Actor_96.DisplayDesc.ModelId = 0
	Actor_96.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_61.osgb"
	Actor_96.DisplayDesc.Outfit = ""
	Actor_96.DisplayDesc.Weapon = ""
	Actor_96.DisplayDesc.Mode = ""
	Actor_96.DisplayDesc.UseLight = false
	Actor_96.DisplayDesc.CastShadow = true
	Actor_96.DisplayDesc.ColorR = 0
	Actor_96.DisplayDesc.ColorG = 0
	Actor_96.DisplayDesc.ColorB = 0
	Actor_96.DisplayDesc.ColorA = 0
	Actor_96:SetModelState(1)
	Actor_96.PhysicDesc.Pos.X = 444
	Actor_96.PhysicDesc.Pos.Y = 0
	Actor_96.PhysicDesc.Pos.Z = 511
	Actor_96.PhysicDesc.Pos.Rotation = -90
	Actor_96.PhysicDesc.Density = 0
	Actor_96.PhysicDesc.Collidable = true
	Actor_96.PhysicDesc.SizeX = 0
	Actor_96.PhysicDesc.SizeY = 0
	Actor_96.PhysicDesc.SizeZ = 0
	Actor_96.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_61.phy"
	Actor_96:SetPhysicalActorType(1)
	Actor_96:SetPhysicalShape(5)
	Actor_96.ExtraInfo.Name = ""
	Actor_96.ExtraInfo.NameColorR = 0
	Actor_96.ExtraInfo.NameColorG = 0
	Actor_96.ExtraInfo.NameColorB = 0
	Actor_96H = ActorHandler(Actor_96)
	environment:AddActorObject(Actor_96H)

	Actor_97 = ActorObjectInfo(97)
	Actor_97:SetRenderType(1)
	Actor_97.DisplayDesc.ModelId = 429088192
	Actor_97.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_62.osgb"
	Actor_97.DisplayDesc.Outfit = ""
	Actor_97.DisplayDesc.Weapon = ""
	Actor_97.DisplayDesc.Mode = ""
	Actor_97.DisplayDesc.UseLight = false
	Actor_97.DisplayDesc.CastShadow = true
	Actor_97.DisplayDesc.ColorR = 3.57331e-043
	Actor_97.DisplayDesc.ColorG = 0
	Actor_97.DisplayDesc.ColorB = 0
	Actor_97.DisplayDesc.ColorA = 0
	Actor_97:SetModelState(1)
	Actor_97.PhysicDesc.Pos.X = 444
	Actor_97.PhysicDesc.Pos.Y = 0
	Actor_97.PhysicDesc.Pos.Z = 511
	Actor_97.PhysicDesc.Pos.Rotation = -90
	Actor_97.PhysicDesc.Density = -3.40282e+038
	Actor_97.PhysicDesc.Collidable = true
	Actor_97.PhysicDesc.SizeX = -3.40282e+038
	Actor_97.PhysicDesc.SizeY = 0
	Actor_97.PhysicDesc.SizeZ = -3.125
	Actor_97.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_62.phy"
	Actor_97:SetPhysicalActorType(1)
	Actor_97:SetPhysicalShape(5)
	Actor_97.ExtraInfo.Name = ""
	Actor_97.ExtraInfo.NameColorR = 0
	Actor_97.ExtraInfo.NameColorG = 0
	Actor_97.ExtraInfo.NameColorB = 1.52381e-023
	Actor_97H = ActorHandler(Actor_97)
	environment:AddActorObject(Actor_97H)

	Actor_98 = ActorObjectInfo(98)
	Actor_98:SetRenderType(1)
	Actor_98.DisplayDesc.ModelId = 0
	Actor_98.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_63.osgb"
	Actor_98.DisplayDesc.Outfit = ""
	Actor_98.DisplayDesc.Weapon = ""
	Actor_98.DisplayDesc.Mode = ""
	Actor_98.DisplayDesc.UseLight = false
	Actor_98.DisplayDesc.CastShadow = false
	Actor_98.DisplayDesc.ColorR = 0
	Actor_98.DisplayDesc.ColorG = 8.15922e-024
	Actor_98.DisplayDesc.ColorB = 4.90454e-044
	Actor_98.DisplayDesc.ColorA = 5.04467e-044
	Actor_98:SetModelState(1)
	Actor_98.PhysicDesc.Pos.X = 444
	Actor_98.PhysicDesc.Pos.Y = 0
	Actor_98.PhysicDesc.Pos.Z = 511
	Actor_98.PhysicDesc.Pos.Rotation = -90
	Actor_98.PhysicDesc.Density = 7.00649e-044
	Actor_98.PhysicDesc.Collidable = true
	Actor_98.PhysicDesc.SizeX = 0
	Actor_98.PhysicDesc.SizeY = 0
	Actor_98.PhysicDesc.SizeZ = 0
	Actor_98.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_63.phy"
	Actor_98:SetPhysicalActorType(1)
	Actor_98:SetPhysicalShape(5)
	Actor_98.ExtraInfo.Name = ""
	Actor_98.ExtraInfo.NameColorR = 2.03172e-023
	Actor_98.ExtraInfo.NameColorG = 0
	Actor_98.ExtraInfo.NameColorB = 1.05097e-043
	Actor_98H = ActorHandler(Actor_98)
	environment:AddActorObject(Actor_98H)

	Actor_99 = ActorObjectInfo(99)
	Actor_99:SetRenderType(1)
	Actor_99.DisplayDesc.ModelId = 131090
	Actor_99.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_64.osgb"
	Actor_99.DisplayDesc.Outfit = ""
	Actor_99.DisplayDesc.Weapon = ""
	Actor_99.DisplayDesc.Mode = ""
	Actor_99.DisplayDesc.UseLight = false
	Actor_99.DisplayDesc.CastShadow = true
	Actor_99.DisplayDesc.ColorR = 13.8545
	Actor_99.DisplayDesc.ColorG = 1.46937e-039
	Actor_99.DisplayDesc.ColorB = 1.05326e-034
	Actor_99.DisplayDesc.ColorA = 7.42918e-023
	Actor_99:SetModelState(1)
	Actor_99.PhysicDesc.Pos.X = 444
	Actor_99.PhysicDesc.Pos.Y = 0
	Actor_99.PhysicDesc.Pos.Z = 511
	Actor_99.PhysicDesc.Pos.Rotation = -90
	Actor_99.PhysicDesc.Density = 0
	Actor_99.PhysicDesc.Collidable = true
	Actor_99.PhysicDesc.SizeX = 0
	Actor_99.PhysicDesc.SizeY = 0
	Actor_99.PhysicDesc.SizeZ = 0
	Actor_99.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_64.phy"
	Actor_99:SetPhysicalActorType(1)
	Actor_99:SetPhysicalShape(5)
	Actor_99.ExtraInfo.Name = ""
	Actor_99.ExtraInfo.NameColorR = 0
	Actor_99.ExtraInfo.NameColorG = 0
	Actor_99.ExtraInfo.NameColorB = 0
	Actor_99H = ActorHandler(Actor_99)
	environment:AddActorObject(Actor_99H)

	Actor_100 = ActorObjectInfo(100)
	Actor_100:SetRenderType(1)
	Actor_100.DisplayDesc.ModelId = 407791864
	Actor_100.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_65.osgb"
	Actor_100.DisplayDesc.Outfit = ""
	Actor_100.DisplayDesc.Weapon = ""
	Actor_100.DisplayDesc.Mode = ""
	Actor_100.DisplayDesc.UseLight = false
	Actor_100.DisplayDesc.CastShadow = true
	Actor_100.DisplayDesc.ColorR = 6.86636e-044
	Actor_100.DisplayDesc.ColorG = 0
	Actor_100.DisplayDesc.ColorB = 0
	Actor_100.DisplayDesc.ColorA = 0
	Actor_100:SetModelState(1)
	Actor_100.PhysicDesc.Pos.X = 444
	Actor_100.PhysicDesc.Pos.Y = 0
	Actor_100.PhysicDesc.Pos.Z = 511
	Actor_100.PhysicDesc.Pos.Rotation = -90
	Actor_100.PhysicDesc.Density = 2.92969
	Actor_100.PhysicDesc.Collidable = true
	Actor_100.PhysicDesc.SizeX = 0
	Actor_100.PhysicDesc.SizeY = 0
	Actor_100.PhysicDesc.SizeZ = 9.21956e-041
	Actor_100.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_65.phy"
	Actor_100:SetPhysicalActorType(1)
	Actor_100:SetPhysicalShape(5)
	Actor_100.ExtraInfo.Name = ""
	Actor_100.ExtraInfo.NameColorR = 0
	Actor_100.ExtraInfo.NameColorG = 0
	Actor_100.ExtraInfo.NameColorB = 0
	Actor_100H = ActorHandler(Actor_100)
	environment:AddActorObject(Actor_100H)

	Actor_101 = ActorObjectInfo(101)
	Actor_101:SetRenderType(1)
	Actor_101.DisplayDesc.ModelId = 144629820
	Actor_101.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_66.osgb"
	Actor_101.DisplayDesc.Outfit = ""
	Actor_101.DisplayDesc.Weapon = ""
	Actor_101.DisplayDesc.Mode = ""
	Actor_101.DisplayDesc.UseLight = false
	Actor_101.DisplayDesc.CastShadow = false
	Actor_101.DisplayDesc.ColorR = 1.79366e-043
	Actor_101.DisplayDesc.ColorG = 1.73761e-043
	Actor_101.DisplayDesc.ColorB = 0
	Actor_101.DisplayDesc.ColorA = 0
	Actor_101:SetModelState(1)
	Actor_101.PhysicDesc.Pos.X = 444
	Actor_101.PhysicDesc.Pos.Y = 0
	Actor_101.PhysicDesc.Pos.Z = 511
	Actor_101.PhysicDesc.Pos.Rotation = -90
	Actor_101.PhysicDesc.Density = 2.8026e-045
	Actor_101.PhysicDesc.Collidable = true
	Actor_101.PhysicDesc.SizeX = 3.64338e-044
	Actor_101.PhysicDesc.SizeY = 1.96182e-044
	Actor_101.PhysicDesc.SizeZ = 2.57142e-039
	Actor_101.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_66.phy"
	Actor_101:SetPhysicalActorType(1)
	Actor_101:SetPhysicalShape(5)
	Actor_101.ExtraInfo.Name = ""
	Actor_101.ExtraInfo.NameColorR = 6.8645
	Actor_101.ExtraInfo.NameColorG = 4.5564
	Actor_101.ExtraInfo.NameColorB = 0
	Actor_101H = ActorHandler(Actor_101)
	environment:AddActorObject(Actor_101H)

	Actor_102 = ActorObjectInfo(102)
	Actor_102:SetRenderType(1)
	Actor_102.DisplayDesc.ModelId = 0
	Actor_102.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_67.osgb"
	Actor_102.DisplayDesc.Outfit = ""
	Actor_102.DisplayDesc.Weapon = ""
	Actor_102.DisplayDesc.Mode = ""
	Actor_102.DisplayDesc.UseLight = false
	Actor_102.DisplayDesc.CastShadow = false
	Actor_102.DisplayDesc.ColorR = 0
	Actor_102.DisplayDesc.ColorG = 0
	Actor_102.DisplayDesc.ColorB = 0
	Actor_102.DisplayDesc.ColorA = 0
	Actor_102:SetModelState(1)
	Actor_102.PhysicDesc.Pos.X = 444
	Actor_102.PhysicDesc.Pos.Y = 0
	Actor_102.PhysicDesc.Pos.Z = 511
	Actor_102.PhysicDesc.Pos.Rotation = -90
	Actor_102.PhysicDesc.Density = 4.57361e-038
	Actor_102.PhysicDesc.Collidable = true
	Actor_102.PhysicDesc.SizeX = 0
	Actor_102.PhysicDesc.SizeY = 0
	Actor_102.PhysicDesc.SizeZ = 0
	Actor_102.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_67.phy"
	Actor_102:SetPhysicalActorType(1)
	Actor_102:SetPhysicalShape(5)
	Actor_102.ExtraInfo.Name = ""
	Actor_102.ExtraInfo.NameColorR = 0
	Actor_102.ExtraInfo.NameColorG = 0
	Actor_102.ExtraInfo.NameColorB = 0
	Actor_102H = ActorHandler(Actor_102)
	environment:AddActorObject(Actor_102H)

	Actor_103 = ActorObjectInfo(103)
	Actor_103:SetRenderType(1)
	Actor_103.DisplayDesc.ModelId = 0
	Actor_103.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_68.osgb"
	Actor_103.DisplayDesc.Outfit = ""
	Actor_103.DisplayDesc.Weapon = ""
	Actor_103.DisplayDesc.Mode = ""
	Actor_103.DisplayDesc.UseLight = false
	Actor_103.DisplayDesc.CastShadow = false
	Actor_103.DisplayDesc.ColorR = 0
	Actor_103.DisplayDesc.ColorG = 5.19359e-023
	Actor_103.DisplayDesc.ColorB = 1.4013e-045
	Actor_103.DisplayDesc.ColorA = 238592
	Actor_103:SetModelState(1)
	Actor_103.PhysicDesc.Pos.X = 444
	Actor_103.PhysicDesc.Pos.Y = 0
	Actor_103.PhysicDesc.Pos.Z = 511
	Actor_103.PhysicDesc.Pos.Rotation = -90
	Actor_103.PhysicDesc.Density = 2.8026e-045
	Actor_103.PhysicDesc.Collidable = true
	Actor_103.PhysicDesc.SizeX = 0
	Actor_103.PhysicDesc.SizeY = 0
	Actor_103.PhysicDesc.SizeZ = 0
	Actor_103.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_68.phy"
	Actor_103:SetPhysicalActorType(1)
	Actor_103:SetPhysicalShape(5)
	Actor_103.ExtraInfo.Name = ""
	Actor_103.ExtraInfo.NameColorR = 7.8228e-024
	Actor_103.ExtraInfo.NameColorG = 1.83674e-040
	Actor_103.ExtraInfo.NameColorB = 1.05329e-034
	Actor_103H = ActorHandler(Actor_103)
	environment:AddActorObject(Actor_103H)

	Actor_104 = ActorObjectInfo(104)
	Actor_104:SetRenderType(1)
	Actor_104.DisplayDesc.ModelId = 229493832
	Actor_104.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_69.osgb"
	Actor_104.DisplayDesc.Outfit = ""
	Actor_104.DisplayDesc.Weapon = ""
	Actor_104.DisplayDesc.Mode = ""
	Actor_104.DisplayDesc.UseLight = false
	Actor_104.DisplayDesc.CastShadow = false
	Actor_104.DisplayDesc.ColorR = 2.558e-035
	Actor_104.DisplayDesc.ColorG = 1.07113e-030
	Actor_104.DisplayDesc.ColorB = 1.07113e-030
	Actor_104.DisplayDesc.ColorA = 1.07113e-030
	Actor_104:SetModelState(1)
	Actor_104.PhysicDesc.Pos.X = 444
	Actor_104.PhysicDesc.Pos.Y = 0
	Actor_104.PhysicDesc.Pos.Z = 511
	Actor_104.PhysicDesc.Pos.Rotation = -90
	Actor_104.PhysicDesc.Density = 0.344104
	Actor_104.PhysicDesc.Collidable = true
	Actor_104.PhysicDesc.SizeX = 0
	Actor_104.PhysicDesc.SizeY = 2.10195e-044
	Actor_104.PhysicDesc.SizeZ = 1.4013e-045
	Actor_104.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_69.phy"
	Actor_104:SetPhysicalActorType(1)
	Actor_104:SetPhysicalShape(5)
	Actor_104.ExtraInfo.Name = ""
	Actor_104.ExtraInfo.NameColorR = 4.33984
	Actor_104.ExtraInfo.NameColorG = 5.42383
	Actor_104.ExtraInfo.NameColorB = 4.31641
	Actor_104H = ActorHandler(Actor_104)
	environment:AddActorObject(Actor_104H)

	Actor_105 = ActorObjectInfo(105)
	Actor_105:SetRenderType(1)
	Actor_105.DisplayDesc.ModelId = 505873904
	Actor_105.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_70.osgb"
	Actor_105.DisplayDesc.Outfit = ""
	Actor_105.DisplayDesc.Weapon = ""
	Actor_105.DisplayDesc.Mode = ""
	Actor_105.DisplayDesc.UseLight = false
	Actor_105.DisplayDesc.CastShadow = true
	Actor_105.DisplayDesc.ColorR = 4.57351e-038
	Actor_105.DisplayDesc.ColorG = 5.51019e-040
	Actor_105.DisplayDesc.ColorB = 1.02316e-034
	Actor_105.DisplayDesc.ColorA = 4.57352e-038
	Actor_105:SetModelState(1)
	Actor_105.PhysicDesc.Pos.X = 444
	Actor_105.PhysicDesc.Pos.Y = 0
	Actor_105.PhysicDesc.Pos.Z = 511
	Actor_105.PhysicDesc.Pos.Rotation = -90
	Actor_105.PhysicDesc.Density = 6.81963e-023
	Actor_105.PhysicDesc.Collidable = true
	Actor_105.PhysicDesc.SizeX = 0
	Actor_105.PhysicDesc.SizeY = 3.60134e-043
	Actor_105.PhysicDesc.SizeZ = 2.20415e-039
	Actor_105.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_70.phy"
	Actor_105:SetPhysicalActorType(1)
	Actor_105:SetPhysicalShape(5)
	Actor_105.ExtraInfo.Name = ""
	Actor_105.ExtraInfo.NameColorR = 0
	Actor_105.ExtraInfo.NameColorG = 0
	Actor_105.ExtraInfo.NameColorB = 0
	Actor_105H = ActorHandler(Actor_105)
	environment:AddActorObject(Actor_105H)

	Actor_106 = ActorObjectInfo(106)
	Actor_106:SetRenderType(1)
	Actor_106.DisplayDesc.ModelId = 0
	Actor_106.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_71.osgb"
	Actor_106.DisplayDesc.Outfit = ""
	Actor_106.DisplayDesc.Weapon = ""
	Actor_106.DisplayDesc.Mode = ""
	Actor_106.DisplayDesc.UseLight = false
	Actor_106.DisplayDesc.CastShadow = false
	Actor_106.DisplayDesc.ColorR = 0
	Actor_106.DisplayDesc.ColorG = 0
	Actor_106.DisplayDesc.ColorB = 0
	Actor_106.DisplayDesc.ColorA = 0
	Actor_106:SetModelState(1)
	Actor_106.PhysicDesc.Pos.X = 444
	Actor_106.PhysicDesc.Pos.Y = 0
	Actor_106.PhysicDesc.Pos.Z = 511
	Actor_106.PhysicDesc.Pos.Rotation = -90
	Actor_106.PhysicDesc.Density = 5.50233e-023
	Actor_106.PhysicDesc.Collidable = true
	Actor_106.PhysicDesc.SizeX = 8.32371e-043
	Actor_106.PhysicDesc.SizeY = 0
	Actor_106.PhysicDesc.SizeZ = 0
	Actor_106.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_71.phy"
	Actor_106:SetPhysicalActorType(1)
	Actor_106:SetPhysicalShape(5)
	Actor_106.ExtraInfo.Name = ""
	Actor_106.ExtraInfo.NameColorR = 0
	Actor_106.ExtraInfo.NameColorG = 0
	Actor_106.ExtraInfo.NameColorB = 0
	Actor_106H = ActorHandler(Actor_106)
	environment:AddActorObject(Actor_106H)

	Actor_107 = ActorObjectInfo(107)
	Actor_107:SetRenderType(1)
	Actor_107.DisplayDesc.ModelId = 0
	Actor_107.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_72.osgb"
	Actor_107.DisplayDesc.Outfit = ""
	Actor_107.DisplayDesc.Weapon = ""
	Actor_107.DisplayDesc.Mode = ""
	Actor_107.DisplayDesc.UseLight = false
	Actor_107.DisplayDesc.CastShadow = true
	Actor_107.DisplayDesc.ColorR = 3.14109e-024
	Actor_107.DisplayDesc.ColorG = 3.11466e-031
	Actor_107.DisplayDesc.ColorB = 7.01561e-023
	Actor_107.DisplayDesc.ColorA = 0
	Actor_107:SetModelState(1)
	Actor_107.PhysicDesc.Pos.X = 444
	Actor_107.PhysicDesc.Pos.Y = 0
	Actor_107.PhysicDesc.Pos.Z = 511
	Actor_107.PhysicDesc.Pos.Rotation = -90
	Actor_107.PhysicDesc.Density = 2.35673e-023
	Actor_107.PhysicDesc.Collidable = true
	Actor_107.PhysicDesc.SizeX = 0
	Actor_107.PhysicDesc.SizeY = 0
	Actor_107.PhysicDesc.SizeZ = 0
	Actor_107.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_72.phy"
	Actor_107:SetPhysicalActorType(1)
	Actor_107:SetPhysicalShape(5)
	Actor_107.ExtraInfo.Name = ""
	Actor_107.ExtraInfo.NameColorR = 0
	Actor_107.ExtraInfo.NameColorG = -2.75195
	Actor_107.ExtraInfo.NameColorB = 0.0878906
	Actor_107H = ActorHandler(Actor_107)
	environment:AddActorObject(Actor_107H)

	Actor_108 = ActorObjectInfo(108)
	Actor_108:SetRenderType(1)
	Actor_108.DisplayDesc.ModelId = 144577628
	Actor_108.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_73.osgb"
	Actor_108.DisplayDesc.Outfit = ""
	Actor_108.DisplayDesc.Weapon = ""
	Actor_108.DisplayDesc.Mode = ""
	Actor_108.DisplayDesc.UseLight = false
	Actor_108.DisplayDesc.CastShadow = false
	Actor_108.DisplayDesc.ColorR = 0
	Actor_108.DisplayDesc.ColorG = 1.6531e-039
	Actor_108.DisplayDesc.ColorB = 1.0533e-034
	Actor_108.DisplayDesc.ColorA = 1.31224e-038
	Actor_108:SetModelState(1)
	Actor_108.PhysicDesc.Pos.X = 444
	Actor_108.PhysicDesc.Pos.Y = 0
	Actor_108.PhysicDesc.Pos.Z = 511
	Actor_108.PhysicDesc.Pos.Rotation = -90
	Actor_108.PhysicDesc.Density = 9.2817e-024
	Actor_108.PhysicDesc.Collidable = true
	Actor_108.PhysicDesc.SizeX = 0
	Actor_108.PhysicDesc.SizeY = 0
	Actor_108.PhysicDesc.SizeZ = 0
	Actor_108.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_73.phy"
	Actor_108:SetPhysicalActorType(1)
	Actor_108:SetPhysicalShape(5)
	Actor_108.ExtraInfo.Name = ""
	Actor_108.ExtraInfo.NameColorR = 2.8026e-045
	Actor_108.ExtraInfo.NameColorG = 0
	Actor_108.ExtraInfo.NameColorB = 0
	Actor_108H = ActorHandler(Actor_108)
	environment:AddActorObject(Actor_108H)

	Actor_109 = ActorObjectInfo(109)
	Actor_109:SetRenderType(1)
	Actor_109.DisplayDesc.ModelId = 225676248
	Actor_109.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_74.osgb"
	Actor_109.DisplayDesc.Outfit = ""
	Actor_109.DisplayDesc.Weapon = ""
	Actor_109.DisplayDesc.Mode = ""
	Actor_109.DisplayDesc.UseLight = false
	Actor_109.DisplayDesc.CastShadow = true
	Actor_109.DisplayDesc.ColorR = 9.24857e-044
	Actor_109.DisplayDesc.ColorG = 1.19388e-038
	Actor_109.DisplayDesc.ColorB = 0
	Actor_109.DisplayDesc.ColorA = 0
	Actor_109:SetModelState(1)
	Actor_109.PhysicDesc.Pos.X = 444
	Actor_109.PhysicDesc.Pos.Y = 0
	Actor_109.PhysicDesc.Pos.Z = 511
	Actor_109.PhysicDesc.Pos.Rotation = -90
	Actor_109.PhysicDesc.Density = 6.66211
	Actor_109.PhysicDesc.Collidable = true
	Actor_109.PhysicDesc.SizeX = 1.83672e-040
	Actor_109.PhysicDesc.SizeY = 0
	Actor_109.PhysicDesc.SizeZ = 9.21956e-041
	Actor_109.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_74.phy"
	Actor_109:SetPhysicalActorType(1)
	Actor_109:SetPhysicalShape(5)
	Actor_109.ExtraInfo.Name = ""
	Actor_109.ExtraInfo.NameColorR = 0
	Actor_109.ExtraInfo.NameColorG = 0
	Actor_109.ExtraInfo.NameColorB = 0
	Actor_109H = ActorHandler(Actor_109)
	environment:AddActorObject(Actor_109H)

	Actor_110 = ActorObjectInfo(110)
	Actor_110:SetRenderType(1)
	Actor_110.DisplayDesc.ModelId = 131171
	Actor_110.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_75.osgb"
	Actor_110.DisplayDesc.Outfit = ""
	Actor_110.DisplayDesc.Weapon = ""
	Actor_110.DisplayDesc.Mode = ""
	Actor_110.DisplayDesc.UseLight = false
	Actor_110.DisplayDesc.CastShadow = false
	Actor_110.DisplayDesc.ColorR = 2.10195e-044
	Actor_110.DisplayDesc.ColorG = 2.8026e-045
	Actor_110.DisplayDesc.ColorB = 0
	Actor_110.DisplayDesc.ColorA = 0
	Actor_110:SetModelState(1)
	Actor_110.PhysicDesc.Pos.X = 444
	Actor_110.PhysicDesc.Pos.Y = 0
	Actor_110.PhysicDesc.Pos.Z = 511
	Actor_110.PhysicDesc.Pos.Rotation = -90
	Actor_110.PhysicDesc.Density = 0
	Actor_110.PhysicDesc.Collidable = true
	Actor_110.PhysicDesc.SizeX = 0.546875
	Actor_110.PhysicDesc.SizeY = -0.546875
	Actor_110.PhysicDesc.SizeZ = 2.02038e-039
	Actor_110.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_75.phy"
	Actor_110:SetPhysicalActorType(1)
	Actor_110:SetPhysicalShape(5)
	Actor_110.ExtraInfo.Name = ""
	Actor_110.ExtraInfo.NameColorR = 1.02318e-034
	Actor_110.ExtraInfo.NameColorG = 4.57356e-038
	Actor_110.ExtraInfo.NameColorB = 2.83267e-024
	Actor_110H = ActorHandler(Actor_110)
	environment:AddActorObject(Actor_110H)

	Actor_111 = ActorObjectInfo(111)
	Actor_111:SetRenderType(1)
	Actor_111.DisplayDesc.ModelId = 0
	Actor_111.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_76.osgb"
	Actor_111.DisplayDesc.Outfit = ""
	Actor_111.DisplayDesc.Weapon = ""
	Actor_111.DisplayDesc.Mode = ""
	Actor_111.DisplayDesc.UseLight = false
	Actor_111.DisplayDesc.CastShadow = false
	Actor_111.DisplayDesc.ColorR = 0
	Actor_111.DisplayDesc.ColorG = 0
	Actor_111.DisplayDesc.ColorB = 0
	Actor_111.DisplayDesc.ColorA = 0
	Actor_111:SetModelState(1)
	Actor_111.PhysicDesc.Pos.X = 445.125
	Actor_111.PhysicDesc.Pos.Y = 0.683594
	Actor_111.PhysicDesc.Pos.Z = 522.5
	Actor_111.PhysicDesc.Pos.Rotation = 90
	Actor_111.PhysicDesc.Density = 0
	Actor_111.PhysicDesc.Collidable = true
	Actor_111.PhysicDesc.SizeX = 0
	Actor_111.PhysicDesc.SizeY = 1.875
	Actor_111.PhysicDesc.SizeZ = 0
	Actor_111.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_76.phy"
	Actor_111:SetPhysicalActorType(1)
	Actor_111:SetPhysicalShape(5)
	Actor_111.ExtraInfo.Name = ""
	Actor_111.ExtraInfo.NameColorR = 1.875
	Actor_111.ExtraInfo.NameColorG = 0
	Actor_111.ExtraInfo.NameColorB = 0
	Actor_111H = ActorHandler(Actor_111)
	environment:AddActorObject(Actor_111H)

	Actor_112 = ActorObjectInfo(112)
	Actor_112:SetRenderType(1)
	Actor_112.DisplayDesc.ModelId = 0
	Actor_112.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_77.osgb"
	Actor_112.DisplayDesc.Outfit = ""
	Actor_112.DisplayDesc.Weapon = ""
	Actor_112.DisplayDesc.Mode = ""
	Actor_112.DisplayDesc.UseLight = false
	Actor_112.DisplayDesc.CastShadow = true
	Actor_112.DisplayDesc.ColorR = 0
	Actor_112.DisplayDesc.ColorG = 9.21956e-041
	Actor_112.DisplayDesc.ColorB = 6.76191e-024
	Actor_112.DisplayDesc.ColorA = 0
	Actor_112:SetModelState(1)
	Actor_112.PhysicDesc.Pos.X = 445.125
	Actor_112.PhysicDesc.Pos.Y = 0.683594
	Actor_112.PhysicDesc.Pos.Z = 522.5
	Actor_112.PhysicDesc.Pos.Rotation = 90
	Actor_112.PhysicDesc.Density = 0
	Actor_112.PhysicDesc.Collidable = true
	Actor_112.PhysicDesc.SizeX = 0
	Actor_112.PhysicDesc.SizeY = 0
	Actor_112.PhysicDesc.SizeZ = 0
	Actor_112.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_77.phy"
	Actor_112:SetPhysicalActorType(1)
	Actor_112:SetPhysicalShape(5)
	Actor_112.ExtraInfo.Name = ""
	Actor_112.ExtraInfo.NameColorR = 6.76195e-024
	Actor_112.ExtraInfo.NameColorG = 3.30608e-039
	Actor_112.ExtraInfo.NameColorB = 1.02321e-034
	Actor_112H = ActorHandler(Actor_112)
	environment:AddActorObject(Actor_112H)

	Actor_113 = ActorObjectInfo(113)
	Actor_113:SetRenderType(1)
	Actor_113.DisplayDesc.ModelId = -1128154068
	Actor_113.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_16.osgb"
	Actor_113.DisplayDesc.Outfit = ""
	Actor_113.DisplayDesc.Weapon = ""
	Actor_113.DisplayDesc.Mode = ""
	Actor_113.DisplayDesc.UseLight = false
	Actor_113.DisplayDesc.CastShadow = true
	Actor_113.DisplayDesc.ColorR = 0
	Actor_113.DisplayDesc.ColorG = 0.904274
	Actor_113.DisplayDesc.ColorB = -0.426952
	Actor_113.DisplayDesc.ColorA = 0
	Actor_113:SetModelState(1)
	Actor_113.PhysicDesc.Pos.X = 465.5
	Actor_113.PhysicDesc.Pos.Y = 11.1797
	Actor_113.PhysicDesc.Pos.Z = 506.625
	Actor_113.PhysicDesc.Pos.Rotation = 180
	Actor_113.PhysicDesc.Density = -0.608387
	Actor_113.PhysicDesc.Collidable = true
	Actor_113.PhysicDesc.SizeX = -0.989779
	Actor_113.PhysicDesc.SizeY = 0.142613
	Actor_113.PhysicDesc.SizeZ = 0
	Actor_113.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_16.phy"
	Actor_113:SetPhysicalActorType(1)
	Actor_113:SetPhysicalShape(5)
	Actor_113.ExtraInfo.Name = ""
	Actor_113.ExtraInfo.NameColorR = -0.142313
	Actor_113.ExtraInfo.NameColorG = 0.989822
	Actor_113.ExtraInfo.NameColorB = 0
	Actor_113H = ActorHandler(Actor_113)
	environment:AddActorObject(Actor_113H)

	Actor_114 = ActorObjectInfo(114)
	Actor_114:SetRenderType(1)
	Actor_114.DisplayDesc.ModelId = 131171
	Actor_114.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_34.osgb"
	Actor_114.DisplayDesc.Outfit = ""
	Actor_114.DisplayDesc.Weapon = ""
	Actor_114.DisplayDesc.Mode = ""
	Actor_114.DisplayDesc.UseLight = false
	Actor_114.DisplayDesc.CastShadow = false
	Actor_114.DisplayDesc.ColorR = 2.10195e-044
	Actor_114.DisplayDesc.ColorG = 2.8026e-045
	Actor_114.DisplayDesc.ColorB = 0
	Actor_114.DisplayDesc.ColorA = 0
	Actor_114:SetModelState(1)
	Actor_114.PhysicDesc.Pos.X = 470.5
	Actor_114.PhysicDesc.Pos.Y = 12.207
	Actor_114.PhysicDesc.Pos.Z = 514.5
	Actor_114.PhysicDesc.Pos.Rotation = 180
	Actor_114.PhysicDesc.Density = 0
	Actor_114.PhysicDesc.Collidable = true
	Actor_114.PhysicDesc.SizeX = 0
	Actor_114.PhysicDesc.SizeY = 0
	Actor_114.PhysicDesc.SizeZ = 2.02038e-039
	Actor_114.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_34.phy"
	Actor_114:SetPhysicalActorType(1)
	Actor_114:SetPhysicalShape(5)
	Actor_114.ExtraInfo.Name = ""
	Actor_114.ExtraInfo.NameColorR = 1.02319e-034
	Actor_114.ExtraInfo.NameColorG = 9.89302e-039
	Actor_114.ExtraInfo.NameColorB = 0
	Actor_114H = ActorHandler(Actor_114)
	environment:AddActorObject(Actor_114H)

	Actor_115 = ActorObjectInfo(115)
	Actor_115:SetRenderType(1)
	Actor_115.DisplayDesc.ModelId = -2147483648
	Actor_115.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_78.osgb"
	Actor_115.DisplayDesc.Outfit = ""
	Actor_115.DisplayDesc.Weapon = ""
	Actor_115.DisplayDesc.Mode = ""
	Actor_115.DisplayDesc.UseLight = false
	Actor_115.DisplayDesc.CastShadow = false
	Actor_115.DisplayDesc.ColorR = -4.33984
	Actor_115.DisplayDesc.ColorG = 3.3418
	Actor_115.DisplayDesc.ColorB = -0.302734
	Actor_115.DisplayDesc.ColorA = -1.95313
	Actor_115:SetModelState(1)
	Actor_115.PhysicDesc.Pos.X = 433.625
	Actor_115.PhysicDesc.Pos.Y = 9.76172
	Actor_115.PhysicDesc.Pos.Z = 525.625
	Actor_115.PhysicDesc.Pos.Rotation = 90
	Actor_115.PhysicDesc.Density = -0.302734
	Actor_115.PhysicDesc.Collidable = true
	Actor_115.PhysicDesc.SizeX = 2.60352
	Actor_115.PhysicDesc.SizeY = -0
	Actor_115.PhysicDesc.SizeZ = -4.33984
	Actor_115.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_78.phy"
	Actor_115:SetPhysicalActorType(1)
	Actor_115:SetPhysicalShape(5)
	Actor_115.ExtraInfo.Name = ""
	Actor_115.ExtraInfo.NameColorR = 3.03711
	Actor_115.ExtraInfo.NameColorG = 0.433594
	Actor_115.ExtraInfo.NameColorB = -4.33984
	Actor_115H = ActorHandler(Actor_115)
	environment:AddActorObject(Actor_115H)

	Actor_116 = ActorObjectInfo(116)
	Actor_116:SetRenderType(1)
	Actor_116.DisplayDesc.ModelId = 0
	Actor_116.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_79.osgb"
	Actor_116.DisplayDesc.Outfit = ""
	Actor_116.DisplayDesc.Weapon = ""
	Actor_116.DisplayDesc.Mode = ""
	Actor_116.DisplayDesc.UseLight = false
	Actor_116.DisplayDesc.CastShadow = false
	Actor_116.DisplayDesc.ColorR = 3.35265e-024
	Actor_116.DisplayDesc.ColorG = 0
	Actor_116.DisplayDesc.ColorB = 0
	Actor_116.DisplayDesc.ColorA = 0
	Actor_116:SetModelState(1)
	Actor_116.PhysicDesc.Pos.X = 433.625
	Actor_116.PhysicDesc.Pos.Y = 9.76563
	Actor_116.PhysicDesc.Pos.Z = 525.625
	Actor_116.PhysicDesc.Pos.Rotation = 90
	Actor_116.PhysicDesc.Density = 1.26425e-023
	Actor_116.PhysicDesc.Collidable = true
	Actor_116.PhysicDesc.SizeX = 2.8026e-045
	Actor_116.PhysicDesc.SizeY = 0
	Actor_116.PhysicDesc.SizeZ = 0
	Actor_116.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_79.phy"
	Actor_116:SetPhysicalActorType(1)
	Actor_116:SetPhysicalShape(5)
	Actor_116.ExtraInfo.Name = ""
	Actor_116.ExtraInfo.NameColorR = 0
	Actor_116.ExtraInfo.NameColorG = 0
	Actor_116.ExtraInfo.NameColorB = 0
	Actor_116H = ActorHandler(Actor_116)
	environment:AddActorObject(Actor_116H)

	Actor_117 = ActorObjectInfo(117)
	Actor_117:SetRenderType(1)
	Actor_117.DisplayDesc.ModelId = 1076772864
	Actor_117.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_80.osgb"
	Actor_117.DisplayDesc.Outfit = ""
	Actor_117.DisplayDesc.Weapon = ""
	Actor_117.DisplayDesc.Mode = ""
	Actor_117.DisplayDesc.UseLight = false
	Actor_117.DisplayDesc.CastShadow = false
	Actor_117.DisplayDesc.ColorR = 2.87761e-035
	Actor_117.DisplayDesc.ColorG = 4.5737e-038
	Actor_117.DisplayDesc.ColorB = 9.55413e-024
	Actor_117.DisplayDesc.ColorA = 3.19922
	Actor_117:SetModelState(1)
	Actor_117.PhysicDesc.Pos.X = 433.375
	Actor_117.PhysicDesc.Pos.Y = 9.72266
	Actor_117.PhysicDesc.Pos.Z = 525.875
	Actor_117.PhysicDesc.Pos.Rotation = 90
	Actor_117.PhysicDesc.Density = 2.72266
	Actor_117.PhysicDesc.Collidable = true
	Actor_117.PhysicDesc.SizeX = 1
	Actor_117.PhysicDesc.SizeY = 2.72266
	Actor_117.PhysicDesc.SizeZ = 3.19922
	Actor_117.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_80.phy"
	Actor_117:SetPhysicalActorType(1)
	Actor_117:SetPhysicalShape(5)
	Actor_117.ExtraInfo.Name = ""
	Actor_117.ExtraInfo.NameColorR = 1
	Actor_117.ExtraInfo.NameColorG = 1.12109
	Actor_117.ExtraInfo.NameColorB = 0.597656
	Actor_117H = ActorHandler(Actor_117)
	environment:AddActorObject(Actor_117H)

	Actor_118 = ActorObjectInfo(118)
	Actor_118:SetRenderType(1)
	Actor_118.DisplayDesc.ModelId = 0
	Actor_118.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_80.osgb"
	Actor_118.DisplayDesc.Outfit = ""
	Actor_118.DisplayDesc.Weapon = ""
	Actor_118.DisplayDesc.Mode = ""
	Actor_118.DisplayDesc.UseLight = false
	Actor_118.DisplayDesc.CastShadow = false
	Actor_118.DisplayDesc.ColorR = 4.34403e-044
	Actor_118.DisplayDesc.ColorG = 4.48416e-044
	Actor_118.DisplayDesc.ColorB = 4.62428e-044
	Actor_118.DisplayDesc.ColorA = 4.76441e-044
	Actor_118:SetModelState(1)
	Actor_118.PhysicDesc.Pos.X = 433.375
	Actor_118.PhysicDesc.Pos.Y = 9.72266
	Actor_118.PhysicDesc.Pos.Z = 525.375
	Actor_118.PhysicDesc.Pos.Rotation = 0
	Actor_118.PhysicDesc.Density = 6.72623e-044
	Actor_118.PhysicDesc.Collidable = true
	Actor_118.PhysicDesc.SizeX = 7.00649e-044
	Actor_118.PhysicDesc.SizeY = 7.14662e-044
	Actor_118.PhysicDesc.SizeZ = 7.28675e-044
	Actor_118.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_80.phy"
	Actor_118:SetPhysicalActorType(1)
	Actor_118:SetPhysicalShape(5)
	Actor_118.ExtraInfo.Name = ""
	Actor_118.ExtraInfo.NameColorR = 9.94922e-044
	Actor_118.ExtraInfo.NameColorG = 1.00893e-043
	Actor_118.ExtraInfo.NameColorB = 1.02295e-043
	Actor_118H = ActorHandler(Actor_118)
	environment:AddActorObject(Actor_118H)

	Actor_119 = ActorObjectInfo(119)
	Actor_119:SetRenderType(1)
	Actor_119.DisplayDesc.ModelId = 0
	Actor_119.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_80.osgb"
	Actor_119.DisplayDesc.Outfit = ""
	Actor_119.DisplayDesc.Weapon = ""
	Actor_119.DisplayDesc.Mode = ""
	Actor_119.DisplayDesc.UseLight = false
	Actor_119.DisplayDesc.CastShadow = false
	Actor_119.DisplayDesc.ColorR = 4.34403e-044
	Actor_119.DisplayDesc.ColorG = 4.48416e-044
	Actor_119.DisplayDesc.ColorB = 4.62428e-044
	Actor_119.DisplayDesc.ColorA = 4.76441e-044
	Actor_119:SetModelState(1)
	Actor_119.PhysicDesc.Pos.X = 433.875
	Actor_119.PhysicDesc.Pos.Y = 9.72266
	Actor_119.PhysicDesc.Pos.Z = 525.375
	Actor_119.PhysicDesc.Pos.Rotation = -90
	Actor_119.PhysicDesc.Density = 6.72623e-044
	Actor_119.PhysicDesc.Collidable = true
	Actor_119.PhysicDesc.SizeX = 7.00649e-044
	Actor_119.PhysicDesc.SizeY = 7.14662e-044
	Actor_119.PhysicDesc.SizeZ = 7.28675e-044
	Actor_119.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_80.phy"
	Actor_119:SetPhysicalActorType(1)
	Actor_119:SetPhysicalShape(5)
	Actor_119.ExtraInfo.Name = ""
	Actor_119.ExtraInfo.NameColorR = 9.94922e-044
	Actor_119.ExtraInfo.NameColorG = 1.00893e-043
	Actor_119.ExtraInfo.NameColorB = 1.02295e-043
	Actor_119H = ActorHandler(Actor_119)
	environment:AddActorObject(Actor_119H)

	Actor_120 = ActorObjectInfo(120)
	Actor_120:SetRenderType(1)
	Actor_120.DisplayDesc.ModelId = 0
	Actor_120.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_80.osgb"
	Actor_120.DisplayDesc.Outfit = ""
	Actor_120.DisplayDesc.Weapon = ""
	Actor_120.DisplayDesc.Mode = ""
	Actor_120.DisplayDesc.UseLight = false
	Actor_120.DisplayDesc.CastShadow = false
	Actor_120.DisplayDesc.ColorR = -4.95241e-031
	Actor_120.DisplayDesc.ColorG = 0
	Actor_120.DisplayDesc.ColorB = 0
	Actor_120.DisplayDesc.ColorA = 0
	Actor_120:SetModelState(1)
	Actor_120.PhysicDesc.Pos.X = 433.875
	Actor_120.PhysicDesc.Pos.Y = 9.72266
	Actor_120.PhysicDesc.Pos.Z = 526
	Actor_120.PhysicDesc.Pos.Rotation = 180
	Actor_120.PhysicDesc.Density = 4.86166e-023
	Actor_120.PhysicDesc.Collidable = true
	Actor_120.PhysicDesc.SizeX = 0
	Actor_120.PhysicDesc.SizeY = 0
	Actor_120.PhysicDesc.SizeZ = 0
	Actor_120.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_80.phy"
	Actor_120:SetPhysicalActorType(1)
	Actor_120:SetPhysicalShape(5)
	Actor_120.ExtraInfo.Name = ""
	Actor_120.ExtraInfo.NameColorR = 2.80433e-024
	Actor_120.ExtraInfo.NameColorG = 2.80434e-024
	Actor_120.ExtraInfo.NameColorB = 2.80434e-024
	Actor_120H = ActorHandler(Actor_120)
	environment:AddActorObject(Actor_120H)

	Actor_121 = ActorObjectInfo(121)
	Actor_121:SetRenderType(1)
	Actor_121.DisplayDesc.ModelId = 224742464
	Actor_121.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_81.osgb"
	Actor_121.DisplayDesc.Outfit = ""
	Actor_121.DisplayDesc.Weapon = ""
	Actor_121.DisplayDesc.Mode = ""
	Actor_121.DisplayDesc.UseLight = false
	Actor_121.DisplayDesc.CastShadow = true
	Actor_121.DisplayDesc.ColorR = 0
	Actor_121.DisplayDesc.ColorG = 1.76563
	Actor_121.DisplayDesc.ColorB = 0
	Actor_121.DisplayDesc.ColorA = 0
	Actor_121:SetModelState(1)
	Actor_121.PhysicDesc.Pos.X = 433.625
	Actor_121.PhysicDesc.Pos.Y = 9.72266
	Actor_121.PhysicDesc.Pos.Z = 525.625
	Actor_121.PhysicDesc.Pos.Rotation = 90
	Actor_121.PhysicDesc.Density = 1.01758
	Actor_121.PhysicDesc.Collidable = true
	Actor_121.PhysicDesc.SizeX = 1.83203
	Actor_121.PhysicDesc.SizeY = 0
	Actor_121.PhysicDesc.SizeZ = 9.21956e-041
	Actor_121.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_81.phy"
	Actor_121:SetPhysicalActorType(1)
	Actor_121:SetPhysicalShape(5)
	Actor_121.ExtraInfo.Name = ""
	Actor_121.ExtraInfo.NameColorR = 0
	Actor_121.ExtraInfo.NameColorG = 0
	Actor_121.ExtraInfo.NameColorB = 0
	Actor_121H = ActorHandler(Actor_121)
	environment:AddActorObject(Actor_121H)

	Actor_122 = ActorObjectInfo(122)
	Actor_122:SetRenderType(1)
	Actor_122.DisplayDesc.ModelId = 421486488
	Actor_122.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_82.osgb"
	Actor_122.DisplayDesc.Outfit = ""
	Actor_122.DisplayDesc.Weapon = ""
	Actor_122.DisplayDesc.Mode = ""
	Actor_122.DisplayDesc.UseLight = false
	Actor_122.DisplayDesc.CastShadow = false
	Actor_122.DisplayDesc.ColorR = 4.2039e-045
	Actor_122.DisplayDesc.ColorG = 7.18306e-042
	Actor_122.DisplayDesc.ColorB = 1.67892e-038
	Actor_122.DisplayDesc.ColorA = 0
	Actor_122:SetModelState(1)
	Actor_122.PhysicDesc.Pos.X = 433.625
	Actor_122.PhysicDesc.Pos.Y = 9.72266
	Actor_122.PhysicDesc.Pos.Z = 525.625
	Actor_122.PhysicDesc.Pos.Rotation = 90
	Actor_122.PhysicDesc.Density = 8.23956e-024
	Actor_122.PhysicDesc.Collidable = true
	Actor_122.PhysicDesc.SizeX = 0
	Actor_122.PhysicDesc.SizeY = 2.10195e-044
	Actor_122.PhysicDesc.SizeZ = 2.8026e-045
	Actor_122.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_82.phy"
	Actor_122:SetPhysicalActorType(1)
	Actor_122:SetPhysicalShape(5)
	Actor_122.ExtraInfo.Name = ""
	Actor_122.ExtraInfo.NameColorR = 0
	Actor_122.ExtraInfo.NameColorG = 0
	Actor_122.ExtraInfo.NameColorB = 0
	Actor_122H = ActorHandler(Actor_122)
	environment:AddActorObject(Actor_122H)

	Actor_123 = ActorObjectInfo(123)
	Actor_123:SetRenderType(1)
	Actor_123.DisplayDesc.ModelId = 0
	Actor_123.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_82.osgb"
	Actor_123.DisplayDesc.Outfit = ""
	Actor_123.DisplayDesc.Weapon = ""
	Actor_123.DisplayDesc.Mode = ""
	Actor_123.DisplayDesc.UseLight = false
	Actor_123.DisplayDesc.CastShadow = false
	Actor_123.DisplayDesc.ColorR = 1.4013e-045
	Actor_123.DisplayDesc.ColorG = 0
	Actor_123.DisplayDesc.ColorB = 0
	Actor_123.DisplayDesc.ColorA = 0
	Actor_123:SetModelState(1)
	Actor_123.PhysicDesc.Pos.X = 433.625
	Actor_123.PhysicDesc.Pos.Y = 9.72266
	Actor_123.PhysicDesc.Pos.Z = 525.625
	Actor_123.PhysicDesc.Pos.Rotation = 180
	Actor_123.PhysicDesc.Density = 7.7004e-031
	Actor_123.PhysicDesc.Collidable = true
	Actor_123.PhysicDesc.SizeX = -7.00649e-045
	Actor_123.PhysicDesc.SizeY = 0
	Actor_123.PhysicDesc.SizeZ = 0
	Actor_123.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_82.phy"
	Actor_123:SetPhysicalActorType(1)
	Actor_123:SetPhysicalShape(5)
	Actor_123.ExtraInfo.Name = ""
	Actor_123.ExtraInfo.NameColorR = 0
	Actor_123.ExtraInfo.NameColorG = 0
	Actor_123.ExtraInfo.NameColorB = 0
	Actor_123H = ActorHandler(Actor_123)
	environment:AddActorObject(Actor_123H)

	Actor_124 = ActorObjectInfo(124)
	Actor_124:SetRenderType(1)
	Actor_124.DisplayDesc.ModelId = -1071529984
	Actor_124.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_82.osgb"
	Actor_124.DisplayDesc.Outfit = ""
	Actor_124.DisplayDesc.Weapon = ""
	Actor_124.DisplayDesc.Mode = ""
	Actor_124.DisplayDesc.UseLight = false
	Actor_124.DisplayDesc.CastShadow = false
	Actor_124.DisplayDesc.ColorR = 4.59375
	Actor_124.DisplayDesc.ColorG = 0
	Actor_124.DisplayDesc.ColorB = -3.67578
	Actor_124.DisplayDesc.ColorA = 5.05469
	Actor_124:SetModelState(1)
	Actor_124.PhysicDesc.Pos.X = 433.625
	Actor_124.PhysicDesc.Pos.Y = 9.72266
	Actor_124.PhysicDesc.Pos.Z = 525.625
	Actor_124.PhysicDesc.Pos.Rotation = -90
	Actor_124.PhysicDesc.Density = -4.59375
	Actor_124.PhysicDesc.Collidable = true
	Actor_124.PhysicDesc.SizeX = 0
	Actor_124.PhysicDesc.SizeY = -4.13477
	Actor_124.PhysicDesc.SizeZ = 4.82422
	Actor_124.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_82.phy"
	Actor_124:SetPhysicalActorType(1)
	Actor_124:SetPhysicalShape(5)
	Actor_124.ExtraInfo.Name = ""
	Actor_124.ExtraInfo.NameColorR = 0
	Actor_124.ExtraInfo.NameColorG = -5.05469
	Actor_124.ExtraInfo.NameColorB = 2.06641
	Actor_124H = ActorHandler(Actor_124)
	environment:AddActorObject(Actor_124H)

	Actor_125 = ActorObjectInfo(125)
	Actor_125:SetRenderType(1)
	Actor_125.DisplayDesc.ModelId = 0
	Actor_125.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_82.osgb"
	Actor_125.DisplayDesc.Outfit = ""
	Actor_125.DisplayDesc.Weapon = ""
	Actor_125.DisplayDesc.Mode = ""
	Actor_125.DisplayDesc.UseLight = false
	Actor_125.DisplayDesc.CastShadow = false
	Actor_125.DisplayDesc.ColorR = -0.242298
	Actor_125.DisplayDesc.ColorG = 0
	Actor_125.DisplayDesc.ColorB = 0
	Actor_125.DisplayDesc.ColorA = 0
	Actor_125:SetModelState(1)
	Actor_125.PhysicDesc.Pos.X = 433.625
	Actor_125.PhysicDesc.Pos.Y = 9.72266
	Actor_125.PhysicDesc.Pos.Z = 525.625
	Actor_125.PhysicDesc.Pos.Rotation = 0
	Actor_125.PhysicDesc.Density = 6.33471e-024
	Actor_125.PhysicDesc.Collidable = true
	Actor_125.PhysicDesc.SizeX = 0
	Actor_125.PhysicDesc.SizeY = 0
	Actor_125.PhysicDesc.SizeZ = 0
	Actor_125.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_82.phy"
	Actor_125:SetPhysicalActorType(1)
	Actor_125:SetPhysicalShape(5)
	Actor_125.ExtraInfo.Name = ""
	Actor_125.ExtraInfo.NameColorR = 0
	Actor_125.ExtraInfo.NameColorG = 0
	Actor_125.ExtraInfo.NameColorB = 0
	Actor_125H = ActorHandler(Actor_125)
	environment:AddActorObject(Actor_125H)

	Actor_126 = ActorObjectInfo(126)
	Actor_126:SetRenderType(1)
	Actor_126.DisplayDesc.ModelId = 0
	Actor_126.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_83.osgb"
	Actor_126.DisplayDesc.Outfit = ""
	Actor_126.DisplayDesc.Weapon = ""
	Actor_126.DisplayDesc.Mode = ""
	Actor_126.DisplayDesc.UseLight = false
	Actor_126.DisplayDesc.CastShadow = false
	Actor_126.DisplayDesc.ColorR = 2.66247e-044
	Actor_126.DisplayDesc.ColorG = 2.8026e-044
	Actor_126.DisplayDesc.ColorB = 2.94273e-044
	Actor_126.DisplayDesc.ColorA = 3.08286e-044
	Actor_126:SetModelState(1)
	Actor_126.PhysicDesc.Pos.X = 519
	Actor_126.PhysicDesc.Pos.Y = 11.1328
	Actor_126.PhysicDesc.Pos.Z = 500
	Actor_126.PhysicDesc.Pos.Rotation = -90
	Actor_126.PhysicDesc.Density = 2.38779e-039
	Actor_126.PhysicDesc.Collidable = true
	Actor_126.PhysicDesc.SizeX = 1.31224e-038
	Actor_126.PhysicDesc.SizeY = 0
	Actor_126.PhysicDesc.SizeZ = 0
	Actor_126.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_83.phy"
	Actor_126:SetPhysicalActorType(1)
	Actor_126:SetPhysicalShape(5)
	Actor_126.ExtraInfo.Name = ""
	Actor_126.ExtraInfo.NameColorR = 3.40282e+038
	Actor_126.ExtraInfo.NameColorG = -3.40282e+038
	Actor_126.ExtraInfo.NameColorB = -3.40282e+038
	Actor_126H = ActorHandler(Actor_126)
	environment:AddActorObject(Actor_126H)

	Actor_127 = ActorObjectInfo(127)
	Actor_127:SetRenderType(1)
	Actor_127.DisplayDesc.ModelId = 0
	Actor_127.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_84.osgb"
	Actor_127.DisplayDesc.Outfit = ""
	Actor_127.DisplayDesc.Weapon = ""
	Actor_127.DisplayDesc.Mode = ""
	Actor_127.DisplayDesc.UseLight = false
	Actor_127.DisplayDesc.CastShadow = true
	Actor_127.DisplayDesc.ColorR = 0
	Actor_127.DisplayDesc.ColorG = 0
	Actor_127.DisplayDesc.ColorB = 0
	Actor_127.DisplayDesc.ColorA = 0
	Actor_127:SetModelState(1)
	Actor_127.PhysicDesc.Pos.X = 522
	Actor_127.PhysicDesc.Pos.Y = 10.5469
	Actor_127.PhysicDesc.Pos.Z = 497.25
	Actor_127.PhysicDesc.Pos.Rotation = 0
	Actor_127.PhysicDesc.Density = 0
	Actor_127.PhysicDesc.Collidable = true
	Actor_127.PhysicDesc.SizeX = 0
	Actor_127.PhysicDesc.SizeY = 0
	Actor_127.PhysicDesc.SizeZ = 0
	Actor_127.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_84.phy"
	Actor_127:SetPhysicalActorType(1)
	Actor_127:SetPhysicalShape(5)
	Actor_127.ExtraInfo.Name = ""
	Actor_127.ExtraInfo.NameColorR = 1.4013e-045
	Actor_127.ExtraInfo.NameColorG = 1.4013e-045
	Actor_127.ExtraInfo.NameColorB = 1.4013e-045
	Actor_127H = ActorHandler(Actor_127)
	environment:AddActorObject(Actor_127H)

	Actor_128 = ActorObjectInfo(128)
	Actor_128:SetRenderType(1)
	Actor_128.DisplayDesc.ModelId = 0
	Actor_128.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_85.osgb"
	Actor_128.DisplayDesc.Outfit = ""
	Actor_128.DisplayDesc.Weapon = ""
	Actor_128.DisplayDesc.Mode = ""
	Actor_128.DisplayDesc.UseLight = false
	Actor_128.DisplayDesc.CastShadow = false
	Actor_128.DisplayDesc.ColorR = 0
	Actor_128.DisplayDesc.ColorG = 9.21956e-041
	Actor_128.DisplayDesc.ColorB = 6.87512e-031
	Actor_128.DisplayDesc.ColorA = 0
	Actor_128:SetModelState(1)
	Actor_128.PhysicDesc.Pos.X = 518
	Actor_128.PhysicDesc.Pos.Y = 11.1328
	Actor_128.PhysicDesc.Pos.Z = 513
	Actor_128.PhysicDesc.Pos.Rotation = -90
	Actor_128.PhysicDesc.Density = 0
	Actor_128.PhysicDesc.Collidable = true
	Actor_128.PhysicDesc.SizeX = 0
	Actor_128.PhysicDesc.SizeY = 0
	Actor_128.PhysicDesc.SizeZ = 0
	Actor_128.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_85.phy"
	Actor_128:SetPhysicalActorType(1)
	Actor_128:SetPhysicalShape(5)
	Actor_128.ExtraInfo.Name = ""
	Actor_128.ExtraInfo.NameColorR = 6.87514e-031
	Actor_128.ExtraInfo.NameColorG = -0.630859
	Actor_128.ExtraInfo.NameColorB = -0.419922
	Actor_128H = ActorHandler(Actor_128)
	environment:AddActorObject(Actor_128H)

	Actor_129 = ActorObjectInfo(129)
	Actor_129:SetRenderType(1)
	Actor_129.DisplayDesc.ModelId = 0
	Actor_129.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_129.DisplayDesc.Outfit = ""
	Actor_129.DisplayDesc.Weapon = ""
	Actor_129.DisplayDesc.Mode = ""
	Actor_129.DisplayDesc.UseLight = false
	Actor_129.DisplayDesc.CastShadow = true
	Actor_129.DisplayDesc.ColorR = 0
	Actor_129.DisplayDesc.ColorG = 9.21956e-041
	Actor_129.DisplayDesc.ColorB = 3.83643e-031
	Actor_129.DisplayDesc.ColorA = 2.58037e-024
	Actor_129:SetModelState(1)
	Actor_129.PhysicDesc.Pos.X = 530.5
	Actor_129.PhysicDesc.Pos.Y = 10.8398
	Actor_129.PhysicDesc.Pos.Z = 485.5
	Actor_129.PhysicDesc.Pos.Rotation = 90
	Actor_129.PhysicDesc.Density = 0
	Actor_129.PhysicDesc.Collidable = true
	Actor_129.PhysicDesc.SizeX = 0
	Actor_129.PhysicDesc.SizeY = 0
	Actor_129.PhysicDesc.SizeZ = 0
	Actor_129.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_129:SetPhysicalActorType(1)
	Actor_129:SetPhysicalShape(5)
	Actor_129.ExtraInfo.Name = ""
	Actor_129.ExtraInfo.NameColorR = 3.83644e-031
	Actor_129.ExtraInfo.NameColorG = 0
	Actor_129.ExtraInfo.NameColorB = 0
	Actor_129H = ActorHandler(Actor_129)
	environment:AddActorObject(Actor_129H)

	Actor_130 = ActorObjectInfo(130)
	Actor_130:SetRenderType(1)
	Actor_130.DisplayDesc.ModelId = 226842216
	Actor_130.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_130.DisplayDesc.Outfit = ""
	Actor_130.DisplayDesc.Weapon = ""
	Actor_130.DisplayDesc.Mode = ""
	Actor_130.DisplayDesc.UseLight = false
	Actor_130.DisplayDesc.CastShadow = false
	Actor_130.DisplayDesc.ColorR = 2.10195e-044
	Actor_130.DisplayDesc.ColorG = 2.24208e-044
	Actor_130.DisplayDesc.ColorB = 2.38221e-044
	Actor_130.DisplayDesc.ColorA = 2.52234e-044
	Actor_130:SetModelState(1)
	Actor_130.PhysicDesc.Pos.X = 525.5
	Actor_130.PhysicDesc.Pos.Y = 11.1328
	Actor_130.PhysicDesc.Pos.Z = 491.5
	Actor_130.PhysicDesc.Pos.Rotation = 90
	Actor_130.PhysicDesc.Density = 3.64338e-044
	Actor_130.PhysicDesc.Collidable = true
	Actor_130.PhysicDesc.SizeX = 4.48416e-044
	Actor_130.PhysicDesc.SizeY = 4.62428e-044
	Actor_130.PhysicDesc.SizeZ = 0
	Actor_130.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_130:SetPhysicalActorType(1)
	Actor_130:SetPhysicalShape(5)
	Actor_130.ExtraInfo.Name = ""
	Actor_130.ExtraInfo.NameColorR = 0
	Actor_130.ExtraInfo.NameColorG = 0
	Actor_130.ExtraInfo.NameColorB = 0
	Actor_130H = ActorHandler(Actor_130)
	environment:AddActorObject(Actor_130H)

	Actor_131 = ActorObjectInfo(131)
	Actor_131:SetRenderType(1)
	Actor_131.DisplayDesc.ModelId = 0
	Actor_131.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_131.DisplayDesc.Outfit = ""
	Actor_131.DisplayDesc.Weapon = ""
	Actor_131.DisplayDesc.Mode = ""
	Actor_131.DisplayDesc.UseLight = false
	Actor_131.DisplayDesc.CastShadow = true
	Actor_131.DisplayDesc.ColorR = 8.97952e-042
	Actor_131.DisplayDesc.ColorG = 7.17605e-042
	Actor_131.DisplayDesc.ColorB = 1.4013e-045
	Actor_131.DisplayDesc.ColorA = 0
	Actor_131:SetModelState(1)
	Actor_131.PhysicDesc.Pos.X = 518.75
	Actor_131.PhysicDesc.Pos.Y = 10.5469
	Actor_131.PhysicDesc.Pos.Z = 491.5
	Actor_131.PhysicDesc.Pos.Rotation = 90
	Actor_131.PhysicDesc.Density = 0
	Actor_131.PhysicDesc.Collidable = true
	Actor_131.PhysicDesc.SizeX = 0
	Actor_131.PhysicDesc.SizeY = 0
	Actor_131.PhysicDesc.SizeZ = 1.28572e-039
	Actor_131.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_131:SetPhysicalActorType(1)
	Actor_131:SetPhysicalShape(5)
	Actor_131.ExtraInfo.Name = ""
	Actor_131.ExtraInfo.NameColorR = 2.8026e-045
	Actor_131.ExtraInfo.NameColorG = 7.18306e-042
	Actor_131.ExtraInfo.NameColorB = 1.679e-038
	Actor_131H = ActorHandler(Actor_131)
	environment:AddActorObject(Actor_131H)

	Actor_132 = ActorObjectInfo(132)
	Actor_132:SetRenderType(1)
	Actor_132.DisplayDesc.ModelId = 0
	Actor_132.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_132.DisplayDesc.Outfit = ""
	Actor_132.DisplayDesc.Weapon = ""
	Actor_132.DisplayDesc.Mode = ""
	Actor_132.DisplayDesc.UseLight = false
	Actor_132.DisplayDesc.CastShadow = true
	Actor_132.DisplayDesc.ColorR = 0
	Actor_132.DisplayDesc.ColorG = 9.21956e-041
	Actor_132.DisplayDesc.ColorB = 1.72212e-023
	Actor_132.DisplayDesc.ColorA = 2.57792e-024
	Actor_132:SetModelState(1)
	Actor_132.PhysicDesc.Pos.X = 514.5
	Actor_132.PhysicDesc.Pos.Y = 10.1563
	Actor_132.PhysicDesc.Pos.Z = 486.5
	Actor_132.PhysicDesc.Pos.Rotation = 90
	Actor_132.PhysicDesc.Density = 0
	Actor_132.PhysicDesc.Collidable = true
	Actor_132.PhysicDesc.SizeX = 0
	Actor_132.PhysicDesc.SizeY = 0
	Actor_132.PhysicDesc.SizeZ = 0
	Actor_132.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_132:SetPhysicalActorType(1)
	Actor_132:SetPhysicalShape(5)
	Actor_132.ExtraInfo.Name = ""
	Actor_132.ExtraInfo.NameColorR = 1.72218e-023
	Actor_132.ExtraInfo.NameColorG = 0
	Actor_132.ExtraInfo.NameColorB = 0
	Actor_132H = ActorHandler(Actor_132)
	environment:AddActorObject(Actor_132H)

	Actor_133 = ActorObjectInfo(133)
	Actor_133:SetRenderType(1)
	Actor_133.DisplayDesc.ModelId = 0
	Actor_133.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_15.osgb"
	Actor_133.DisplayDesc.Outfit = ""
	Actor_133.DisplayDesc.Weapon = ""
	Actor_133.DisplayDesc.Mode = ""
	Actor_133.DisplayDesc.UseLight = false
	Actor_133.DisplayDesc.CastShadow = false
	Actor_133.DisplayDesc.ColorR = 6.11328
	Actor_133.DisplayDesc.ColorG = 0.337891
	Actor_133.DisplayDesc.ColorB = -0.236328
	Actor_133.DisplayDesc.ColorA = 0
	Actor_133:SetModelState(1)
	Actor_133.PhysicDesc.Pos.X = 523
	Actor_133.PhysicDesc.Pos.Y = 12.5
	Actor_133.PhysicDesc.Pos.Z = 506
	Actor_133.PhysicDesc.Pos.Rotation = 0
	Actor_133.PhysicDesc.Density = -0.236328
	Actor_133.PhysicDesc.Collidable = true
	Actor_133.PhysicDesc.SizeX = 0
	Actor_133.PhysicDesc.SizeY = 0
	Actor_133.PhysicDesc.SizeZ = 1.28572e-039
	Actor_133.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_15.phy"
	Actor_133:SetPhysicalActorType(1)
	Actor_133:SetPhysicalShape(5)
	Actor_133.ExtraInfo.Name = ""
	Actor_133.ExtraInfo.NameColorR = 5.60519e-045
	Actor_133.ExtraInfo.NameColorG = 7.18306e-042
	Actor_133.ExtraInfo.NameColorB = 1.67899e-038
	Actor_133H = ActorHandler(Actor_133)
	environment:AddActorObject(Actor_133H)

	Actor_134 = ActorObjectInfo(134)
	Actor_134:SetRenderType(1)
	Actor_134.DisplayDesc.ModelId = 16843009
	Actor_134.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_86.osgb"
	Actor_134.DisplayDesc.Outfit = ""
	Actor_134.DisplayDesc.Weapon = ""
	Actor_134.DisplayDesc.Mode = ""
	Actor_134.DisplayDesc.UseLight = false
	Actor_134.DisplayDesc.CastShadow = false
	Actor_134.DisplayDesc.ColorR = 0
	Actor_134.DisplayDesc.ColorG = 0
	Actor_134.DisplayDesc.ColorB = 0
	Actor_134.DisplayDesc.ColorA = 0
	Actor_134:SetModelState(1)
	Actor_134.PhysicDesc.Pos.X = 534
	Actor_134.PhysicDesc.Pos.Y = 2.53906
	Actor_134.PhysicDesc.Pos.Z = 537
	Actor_134.PhysicDesc.Pos.Rotation = -90
	Actor_134.PhysicDesc.Density = 0
	Actor_134.PhysicDesc.Collidable = true
	Actor_134.PhysicDesc.SizeX = 0
	Actor_134.PhysicDesc.SizeY = 0
	Actor_134.PhysicDesc.SizeZ = 0
	Actor_134.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_86.phy"
	Actor_134:SetPhysicalActorType(1)
	Actor_134:SetPhysicalShape(5)
	Actor_134.ExtraInfo.Name = ""
	Actor_134.ExtraInfo.NameColorR = 2.36943e-038
	Actor_134.ExtraInfo.NameColorG = 2.36943e-038
	Actor_134.ExtraInfo.NameColorB = 3.60134e-043
	Actor_134H = ActorHandler(Actor_134)
	environment:AddActorObject(Actor_134H)

	Actor_135 = ActorObjectInfo(135)
	Actor_135:SetRenderType(1)
	Actor_135.DisplayDesc.ModelId = 420957048
	Actor_135.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_87.osgb"
	Actor_135.DisplayDesc.Outfit = ""
	Actor_135.DisplayDesc.Weapon = ""
	Actor_135.DisplayDesc.Mode = ""
	Actor_135.DisplayDesc.UseLight = false
	Actor_135.DisplayDesc.CastShadow = false
	Actor_135.DisplayDesc.ColorR = 2.8026e-045
	Actor_135.DisplayDesc.ColorG = 7.50585e-031
	Actor_135.DisplayDesc.ColorB = 0
	Actor_135.DisplayDesc.ColorA = 3.81558e-024
	Actor_135:SetModelState(1)
	Actor_135.PhysicDesc.Pos.X = 536.998
	Actor_135.PhysicDesc.Pos.Y = 3.125
	Actor_135.PhysicDesc.Pos.Z = 531
	Actor_135.PhysicDesc.Pos.Rotation = -90
	Actor_135.PhysicDesc.Density = 0
	Actor_135.PhysicDesc.Collidable = true
	Actor_135.PhysicDesc.SizeX = 7.63123e-031
	Actor_135.PhysicDesc.SizeY = 0
	Actor_135.PhysicDesc.SizeZ = 8.40779e-045
	Actor_135.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_87.phy"
	Actor_135:SetPhysicalActorType(1)
	Actor_135:SetPhysicalShape(5)
	Actor_135.ExtraInfo.Name = ""
	Actor_135.ExtraInfo.NameColorR = 0
	Actor_135.ExtraInfo.NameColorG = 8.40779e-045
	Actor_135.ExtraInfo.NameColorB = 1.05179e-030
	Actor_135H = ActorHandler(Actor_135)
	environment:AddActorObject(Actor_135H)

	Actor_136 = ActorObjectInfo(136)
	Actor_136:SetRenderType(1)
	Actor_136.DisplayDesc.ModelId = 420957048
	Actor_136.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_88.osgb"
	Actor_136.DisplayDesc.Outfit = ""
	Actor_136.DisplayDesc.Weapon = ""
	Actor_136.DisplayDesc.Mode = ""
	Actor_136.DisplayDesc.UseLight = false
	Actor_136.DisplayDesc.CastShadow = false
	Actor_136.DisplayDesc.ColorR = 1.4013e-045
	Actor_136.DisplayDesc.ColorG = 3.92751e-024
	Actor_136.DisplayDesc.ColorB = 5.1904e-023
	Actor_136.DisplayDesc.ColorA = 3.25159e-024
	Actor_136:SetModelState(1)
	Actor_136.PhysicDesc.Pos.X = 528
	Actor_136.PhysicDesc.Pos.Y = 12.3047
	Actor_136.PhysicDesc.Pos.Z = 523.5
	Actor_136.PhysicDesc.Pos.Rotation = 0
	Actor_136.PhysicDesc.Density = 4.07455e-011
	Actor_136.PhysicDesc.Collidable = true
	Actor_136.PhysicDesc.SizeX = 0
	Actor_136.PhysicDesc.SizeY = 2.8026e-045
	Actor_136.PhysicDesc.SizeZ = 2.47169e-023
	Actor_136.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_88.phy"
	Actor_136:SetPhysicalActorType(1)
	Actor_136:SetPhysicalShape(5)
	Actor_136.ExtraInfo.Name = ""
	Actor_136.ExtraInfo.NameColorR = 1.4013e-045
	Actor_136.ExtraInfo.NameColorG = 3.81558e-024
	Actor_136.ExtraInfo.NameColorB = 1.4013e-045
	Actor_136H = ActorHandler(Actor_136)
	environment:AddActorObject(Actor_136H)

	Actor_137 = ActorObjectInfo(137)
	Actor_137:SetRenderType(1)
	Actor_137.DisplayDesc.ModelId = 420957048
	Actor_137.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_89.osgb"
	Actor_137.DisplayDesc.Outfit = ""
	Actor_137.DisplayDesc.Weapon = ""
	Actor_137.DisplayDesc.Mode = ""
	Actor_137.DisplayDesc.UseLight = false
	Actor_137.DisplayDesc.CastShadow = false
	Actor_137.DisplayDesc.ColorR = 7.00649e-045
	Actor_137.DisplayDesc.ColorG = 7.69025e-031
	Actor_137.DisplayDesc.ColorB = 0
	Actor_137.DisplayDesc.ColorA = 1.98543e-023
	Actor_137:SetModelState(1)
	Actor_137.PhysicDesc.Pos.X = 524.125
	Actor_137.PhysicDesc.Pos.Y = 12.3047
	Actor_137.PhysicDesc.Pos.Z = 520.496
	Actor_137.PhysicDesc.Pos.Rotation = 0
	Actor_137.PhysicDesc.Density = 1.05614e-005
	Actor_137.PhysicDesc.Collidable = true
	Actor_137.PhysicDesc.SizeX = 0
	Actor_137.PhysicDesc.SizeY = 0
	Actor_137.PhysicDesc.SizeZ = 6.47013e-024
	Actor_137.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_89.phy"
	Actor_137:SetPhysicalActorType(1)
	Actor_137:SetPhysicalShape(5)
	Actor_137.ExtraInfo.Name = ""
	Actor_137.ExtraInfo.NameColorR = 3.04688
	Actor_137.ExtraInfo.NameColorG = 4.2039e-045
	Actor_137.ExtraInfo.NameColorB = 7.00619e+022
	Actor_137H = ActorHandler(Actor_137)
	environment:AddActorObject(Actor_137H)

	Actor_138 = ActorObjectInfo(138)
	Actor_138:SetRenderType(1)
	Actor_138.DisplayDesc.ModelId = 420957048
	Actor_138.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_89.osgb"
	Actor_138.DisplayDesc.Outfit = ""
	Actor_138.DisplayDesc.Weapon = ""
	Actor_138.DisplayDesc.Mode = ""
	Actor_138.DisplayDesc.UseLight = false
	Actor_138.DisplayDesc.CastShadow = true
	Actor_138.DisplayDesc.ColorR = 0
	Actor_138.DisplayDesc.ColorG = 8.40779e-045
	Actor_138.DisplayDesc.ColorB = 3.28267e-031
	Actor_138.DisplayDesc.ColorA = 1.76197e-031
	Actor_138:SetModelState(1)
	Actor_138.PhysicDesc.Pos.X = 528.25
	Actor_138.PhysicDesc.Pos.Y = 12.3047
	Actor_138.PhysicDesc.Pos.Z = 520.496
	Actor_138.PhysicDesc.Pos.Rotation = 0
	Actor_138.PhysicDesc.Density = 3.71094
	Actor_138.PhysicDesc.Collidable = true
	Actor_138.PhysicDesc.SizeX = 0
	Actor_138.PhysicDesc.SizeY = 7.00649e-045
	Actor_138.PhysicDesc.SizeZ = 5.87574e-023
	Actor_138.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_89.phy"
	Actor_138:SetPhysicalActorType(1)
	Actor_138:SetPhysicalShape(5)
	Actor_138.ExtraInfo.Name = ""
	Actor_138.ExtraInfo.NameColorR = 2.40103e-024
	Actor_138.ExtraInfo.NameColorG = 0
	Actor_138.ExtraInfo.NameColorB = 2.04273e-023
	Actor_138H = ActorHandler(Actor_138)
	environment:AddActorObject(Actor_138H)

	Actor_139 = ActorObjectInfo(139)
	Actor_139:SetRenderType(1)
	Actor_139.DisplayDesc.ModelId = 420957048
	Actor_139.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_89.osgb"
	Actor_139.DisplayDesc.Outfit = ""
	Actor_139.DisplayDesc.Weapon = ""
	Actor_139.DisplayDesc.Mode = ""
	Actor_139.DisplayDesc.UseLight = false
	Actor_139.DisplayDesc.CastShadow = false
	Actor_139.DisplayDesc.ColorR = 2.8026e-045
	Actor_139.DisplayDesc.ColorG = 9.15123e-031
	Actor_139.DisplayDesc.ColorB = 0
	Actor_139.DisplayDesc.ColorA = 3.81558e-024
	Actor_139:SetModelState(1)
	Actor_139.PhysicDesc.Pos.X = 524.125
	Actor_139.PhysicDesc.Pos.Y = 12.3047
	Actor_139.PhysicDesc.Pos.Z = 526.504
	Actor_139.PhysicDesc.Pos.Rotation = 180
	Actor_139.PhysicDesc.Density = 0
	Actor_139.PhysicDesc.Collidable = true
	Actor_139.PhysicDesc.SizeX = 0
	Actor_139.PhysicDesc.SizeY = 1.4013e-045
	Actor_139.PhysicDesc.SizeZ = 9.15123e-031
	Actor_139.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_89.phy"
	Actor_139:SetPhysicalActorType(1)
	Actor_139:SetPhysicalShape(5)
	Actor_139.ExtraInfo.Name = ""
	Actor_139.ExtraInfo.NameColorR = 0
	Actor_139.ExtraInfo.NameColorG = 0
	Actor_139.ExtraInfo.NameColorB = 0
	Actor_139H = ActorHandler(Actor_139)
	environment:AddActorObject(Actor_139H)

	Actor_140 = ActorObjectInfo(140)
	Actor_140:SetRenderType(1)
	Actor_140.DisplayDesc.ModelId = 420957048
	Actor_140.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_89.osgb"
	Actor_140.DisplayDesc.Outfit = ""
	Actor_140.DisplayDesc.Weapon = ""
	Actor_140.DisplayDesc.Mode = ""
	Actor_140.DisplayDesc.UseLight = false
	Actor_140.DisplayDesc.CastShadow = true
	Actor_140.DisplayDesc.ColorR = 0
	Actor_140.DisplayDesc.ColorG = 6.30539e-031
	Actor_140.DisplayDesc.ColorB = 0
	Actor_140.DisplayDesc.ColorA = 1.74489e-039
	Actor_140:SetModelState(1)
	Actor_140.PhysicDesc.Pos.X = 528.25
	Actor_140.PhysicDesc.Pos.Y = 12.2578
	Actor_140.PhysicDesc.Pos.Z = 526.504
	Actor_140.PhysicDesc.Pos.Rotation = 180
	Actor_140.PhysicDesc.Density = 0
	Actor_140.PhysicDesc.Collidable = true
	Actor_140.PhysicDesc.SizeX = 1.0667e-030
	Actor_140.PhysicDesc.SizeY = 0
	Actor_140.PhysicDesc.SizeZ = 2.41164e-023
	Actor_140.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_89.phy"
	Actor_140:SetPhysicalActorType(1)
	Actor_140:SetPhysicalShape(5)
	Actor_140.ExtraInfo.Name = ""
	Actor_140.ExtraInfo.NameColorR = 7.99962e-023
	Actor_140.ExtraInfo.NameColorG = 3.81558e-024
	Actor_140.ExtraInfo.NameColorB = 1.4013e-045
	Actor_140H = ActorHandler(Actor_140)
	environment:AddActorObject(Actor_140H)

	Actor_141 = ActorObjectInfo(141)
	Actor_141:SetRenderType(1)
	Actor_141.DisplayDesc.ModelId = 1328701794
	Actor_141.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_90.osgb"
	Actor_141.DisplayDesc.Outfit = ""
	Actor_141.DisplayDesc.Weapon = ""
	Actor_141.DisplayDesc.Mode = ""
	Actor_141.DisplayDesc.UseLight = false
	Actor_141.DisplayDesc.CastShadow = true
	Actor_141.DisplayDesc.ColorR = -1
	Actor_141.DisplayDesc.ColorG = 2.41164e-023
	Actor_141.DisplayDesc.ColorB = 1.4013e-045
	Actor_141.DisplayDesc.ColorA = 1.74489e-039
	Actor_141:SetModelState(1)
	Actor_141.PhysicDesc.Pos.X = 528
	Actor_141.PhysicDesc.Pos.Y = 12.3047
	Actor_141.PhysicDesc.Pos.Z = 523.5
	Actor_141.PhysicDesc.Pos.Rotation = 0
	Actor_141.PhysicDesc.Density = 5.92972e-031
	Actor_141.PhysicDesc.Collidable = true
	Actor_141.PhysicDesc.SizeX = 8.40779e-045
	Actor_141.PhysicDesc.SizeY = 7.57615e-031
	Actor_141.PhysicDesc.SizeZ = 1.76197e-031
	Actor_141.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_90.phy"
	Actor_141:SetPhysicalActorType(1)
	Actor_141:SetPhysicalShape(5)
	Actor_141.ExtraInfo.Name = ""
	Actor_141.ExtraInfo.NameColorR = 2.54569e-024
	Actor_141.ExtraInfo.NameColorG = 1.76197e-031
	Actor_141.ExtraInfo.NameColorB = 0
	Actor_141H = ActorHandler(Actor_141)
	environment:AddActorObject(Actor_141H)

	Actor_142 = ActorObjectInfo(142)
	Actor_142:SetRenderType(1)
	Actor_142.DisplayDesc.ModelId = 1328701794
	Actor_142.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_91.osgb"
	Actor_142.DisplayDesc.Outfit = ""
	Actor_142.DisplayDesc.Weapon = ""
	Actor_142.DisplayDesc.Mode = ""
	Actor_142.DisplayDesc.UseLight = false
	Actor_142.DisplayDesc.CastShadow = false
	Actor_142.DisplayDesc.ColorR = 2.8026e-045
	Actor_142.DisplayDesc.ColorG = 7.89038e-023
	Actor_142.DisplayDesc.ColorB = 0
	Actor_142.DisplayDesc.ColorA = 3.81558e-024
	Actor_142:SetModelState(1)
	Actor_142.PhysicDesc.Pos.X = 528
	Actor_142.PhysicDesc.Pos.Y = 12.3047
	Actor_142.PhysicDesc.Pos.Z = 523.5
	Actor_142.PhysicDesc.Pos.Rotation = 0
	Actor_142.PhysicDesc.Density = 4.22461e-005
	Actor_142.PhysicDesc.Collidable = true
	Actor_142.PhysicDesc.SizeX = 1.37327e-043
	Actor_142.PhysicDesc.SizeY = 1.4013e-045
	Actor_142.PhysicDesc.SizeZ = 6.67448e-031
	Actor_142.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_91.phy"
	Actor_142:SetPhysicalActorType(1)
	Actor_142:SetPhysicalShape(5)
	Actor_142.ExtraInfo.Name = ""
	Actor_142.ExtraInfo.NameColorR = 0
	Actor_142.ExtraInfo.NameColorG = 0
	Actor_142.ExtraInfo.NameColorB = 6.7441e-024
	Actor_142H = ActorHandler(Actor_142)
	environment:AddActorObject(Actor_142H)

	Actor_143 = ActorObjectInfo(143)
	Actor_143:SetRenderType(1)
	Actor_143.DisplayDesc.ModelId = 420957048
	Actor_143.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_92.osgb"
	Actor_143.DisplayDesc.Outfit = ""
	Actor_143.DisplayDesc.Weapon = ""
	Actor_143.DisplayDesc.Mode = ""
	Actor_143.DisplayDesc.UseLight = false
	Actor_143.DisplayDesc.CastShadow = true
	Actor_143.DisplayDesc.ColorR = 0
	Actor_143.DisplayDesc.ColorG = 8.40779e-045
	Actor_143.DisplayDesc.ColorB = 7.67465e-031
	Actor_143.DisplayDesc.ColorA = 1.76197e-031
	Actor_143:SetModelState(1)
	Actor_143.PhysicDesc.Pos.X = 528
	Actor_143.PhysicDesc.Pos.Y = 12.3047
	Actor_143.PhysicDesc.Pos.Z = 523.5
	Actor_143.PhysicDesc.Pos.Rotation = 0
	Actor_143.PhysicDesc.Density = 0
	Actor_143.PhysicDesc.Collidable = true
	Actor_143.PhysicDesc.SizeX = 0
	Actor_143.PhysicDesc.SizeY = 7.00649e-045
	Actor_143.PhysicDesc.SizeZ = 7.76038e-031
	Actor_143.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_92.phy"
	Actor_143:SetPhysicalActorType(1)
	Actor_143:SetPhysicalShape(5)
	Actor_143.ExtraInfo.Name = ""
	Actor_143.ExtraInfo.NameColorR = 1.875
	Actor_143.ExtraInfo.NameColorG = 9.80909e-045
	Actor_143.ExtraInfo.NameColorB = 1.57956e-023
	Actor_143H = ActorHandler(Actor_143)
	environment:AddActorObject(Actor_143H)

	Actor_144 = ActorObjectInfo(144)
	Actor_144:SetRenderType(1)
	Actor_144.DisplayDesc.ModelId = 1328701794
	Actor_144.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_93.osgb"
	Actor_144.DisplayDesc.Outfit = ""
	Actor_144.DisplayDesc.Weapon = ""
	Actor_144.DisplayDesc.Mode = ""
	Actor_144.DisplayDesc.UseLight = false
	Actor_144.DisplayDesc.CastShadow = false
	Actor_144.DisplayDesc.ColorR = 0
	Actor_144.DisplayDesc.ColorG = 6.86251e-031
	Actor_144.DisplayDesc.ColorB = 5.60519e-045
	Actor_144.DisplayDesc.ColorA = 1.00626e-038
	Actor_144:SetModelState(1)
	Actor_144.PhysicDesc.Pos.X = 528
	Actor_144.PhysicDesc.Pos.Y = 12.3047
	Actor_144.PhysicDesc.Pos.Z = 523.5
	Actor_144.PhysicDesc.Pos.Rotation = 0
	Actor_144.PhysicDesc.Density = 5.64039e-038
	Actor_144.PhysicDesc.Collidable = true
	Actor_144.PhysicDesc.SizeX = 4.7504e-043
	Actor_144.PhysicDesc.SizeY = 0
	Actor_144.PhysicDesc.SizeZ = 2.55637e-024
	Actor_144.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_93.phy"
	Actor_144:SetPhysicalActorType(1)
	Actor_144:SetPhysicalShape(5)
	Actor_144.ExtraInfo.Name = ""
	Actor_144.ExtraInfo.NameColorR = 2.55794e-035
	Actor_144.ExtraInfo.NameColorG = 2.41387e-023
	Actor_144.ExtraInfo.NameColorB = 4.86137e-023
	Actor_144H = ActorHandler(Actor_144)
	environment:AddActorObject(Actor_144H)

	Actor_145 = ActorObjectInfo(145)
	Actor_145:SetRenderType(1)
	Actor_145.DisplayDesc.ModelId = 1328701794
	Actor_145.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_94.osgb"
	Actor_145.DisplayDesc.Outfit = ""
	Actor_145.DisplayDesc.Weapon = ""
	Actor_145.DisplayDesc.Mode = ""
	Actor_145.DisplayDesc.UseLight = false
	Actor_145.DisplayDesc.CastShadow = false
	Actor_145.DisplayDesc.ColorR = 0
	Actor_145.DisplayDesc.ColorG = 5.99099e-024
	Actor_145.DisplayDesc.ColorB = 5.60519e-045
	Actor_145.DisplayDesc.ColorA = 1.00626e-038
	Actor_145:SetModelState(1)
	Actor_145.PhysicDesc.Pos.X = 528
	Actor_145.PhysicDesc.Pos.Y = 12.3047
	Actor_145.PhysicDesc.Pos.Z = 523.5
	Actor_145.PhysicDesc.Pos.Rotation = 0
	Actor_145.PhysicDesc.Density = 1.76833e-023
	Actor_145.PhysicDesc.Collidable = true
	Actor_145.PhysicDesc.SizeX = 4.70836e-043
	Actor_145.PhysicDesc.SizeY = 0
	Actor_145.PhysicDesc.SizeZ = 2.89839e-034
	Actor_145.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_94.phy"
	Actor_145:SetPhysicalActorType(1)
	Actor_145:SetPhysicalShape(5)
	Actor_145.ExtraInfo.Name = ""
	Actor_145.ExtraInfo.NameColorR = 1.0533e-034
	Actor_145.ExtraInfo.NameColorG = 2.58904e-024
	Actor_145.ExtraInfo.NameColorB = 4.57352e-038
	Actor_145H = ActorHandler(Actor_145)
	environment:AddActorObject(Actor_145H)

	Actor_146 = ActorObjectInfo(146)
	Actor_146:SetRenderType(1)
	Actor_146.DisplayDesc.ModelId = 420957048
	Actor_146.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_146.DisplayDesc.Outfit = ""
	Actor_146.DisplayDesc.Weapon = ""
	Actor_146.DisplayDesc.Mode = ""
	Actor_146.DisplayDesc.UseLight = false
	Actor_146.DisplayDesc.CastShadow = false
	Actor_146.DisplayDesc.ColorR = 7.00649e-045
	Actor_146.DisplayDesc.ColorG = 4.33495e-023
	Actor_146.DisplayDesc.ColorB = -0.514496
	Actor_146.DisplayDesc.ColorA = 1.98543e-023
	Actor_146:SetModelState(1)
	Actor_146.PhysicDesc.Pos.X = 525.5
	Actor_146.PhysicDesc.Pos.Y = 10.5469
	Actor_146.PhysicDesc.Pos.Z = 495.25
	Actor_146.PhysicDesc.Pos.Rotation = 0
	Actor_146.PhysicDesc.Density = 1.06807e-005
	Actor_146.PhysicDesc.Collidable = true
	Actor_146.PhysicDesc.SizeX = 0
	Actor_146.PhysicDesc.SizeY = 0
	Actor_146.PhysicDesc.SizeZ = 4.33495e-023
	Actor_146.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_146:SetPhysicalActorType(1)
	Actor_146:SetPhysicalShape(5)
	Actor_146.ExtraInfo.Name = ""
	Actor_146.ExtraInfo.NameColorR = 2.04005e-023
	Actor_146.ExtraInfo.NameColorG = 1.83671e-040
	Actor_146.ExtraInfo.NameColorB = 1.05325e-034
	Actor_146H = ActorHandler(Actor_146)
	environment:AddActorObject(Actor_146H)

	Actor_147 = ActorObjectInfo(147)
	Actor_147:SetRenderType(1)
	Actor_147.DisplayDesc.ModelId = 420957048
	Actor_147.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.osgb"
	Actor_147.DisplayDesc.Outfit = ""
	Actor_147.DisplayDesc.Weapon = ""
	Actor_147.DisplayDesc.Mode = ""
	Actor_147.DisplayDesc.UseLight = false
	Actor_147.DisplayDesc.CastShadow = false
	Actor_147.DisplayDesc.ColorR = 7.00649e-045
	Actor_147.DisplayDesc.ColorG = 2.68638e-024
	Actor_147.DisplayDesc.ColorB = 2.10195e-044
	Actor_147.DisplayDesc.ColorA = 1.98543e-023
	Actor_147:SetModelState(1)
	Actor_147.PhysicDesc.Pos.X = 522.5
	Actor_147.PhysicDesc.Pos.Y = 10.5469
	Actor_147.PhysicDesc.Pos.Z = 492.375
	Actor_147.PhysicDesc.Pos.Rotation = 90
	Actor_147.PhysicDesc.Density = 6.48262e-010
	Actor_147.PhysicDesc.Collidable = true
	Actor_147.PhysicDesc.SizeX = 0
	Actor_147.PhysicDesc.SizeY = 0
	Actor_147.PhysicDesc.SizeZ = 2.68638e-024
	Actor_147.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_23.phy"
	Actor_147:SetPhysicalActorType(1)
	Actor_147:SetPhysicalShape(5)
	Actor_147.ExtraInfo.Name = ""
	Actor_147.ExtraInfo.NameColorR = 3.2983e-024
	Actor_147.ExtraInfo.NameColorG = 3.48978e-039
	Actor_147.ExtraInfo.NameColorB = 1.02317e-034
	Actor_147H = ActorHandler(Actor_147)
	environment:AddActorObject(Actor_147H)

	Actor_148 = ActorObjectInfo(148)
	Actor_148:SetRenderType(1)
	Actor_148.DisplayDesc.ModelId = 0
	Actor_148.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_95.osgb"
	Actor_148.DisplayDesc.Outfit = ""
	Actor_148.DisplayDesc.Weapon = ""
	Actor_148.DisplayDesc.Mode = ""
	Actor_148.DisplayDesc.UseLight = false
	Actor_148.DisplayDesc.CastShadow = false
	Actor_148.DisplayDesc.ColorR = 0
	Actor_148.DisplayDesc.ColorG = 7.30015e-031
	Actor_148.DisplayDesc.ColorB = 7.375
	Actor_148.DisplayDesc.ColorA = 14.25
	Actor_148:SetModelState(1)
	Actor_148.PhysicDesc.Pos.X = 522
	Actor_148.PhysicDesc.Pos.Y = 10.5469
	Actor_148.PhysicDesc.Pos.Z = 497.25
	Actor_148.PhysicDesc.Pos.Rotation = 0
	Actor_148.PhysicDesc.Density = 1.31224e-038
	Actor_148.PhysicDesc.Collidable = true
	Actor_148.PhysicDesc.SizeX = 0
	Actor_148.PhysicDesc.SizeY = 0
	Actor_148.PhysicDesc.SizeZ = 0
	Actor_148.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_95.phy"
	Actor_148:SetPhysicalActorType(1)
	Actor_148:SetPhysicalShape(5)
	Actor_148.ExtraInfo.Name = ""
	Actor_148.ExtraInfo.NameColorR = 9.82776e-031
	Actor_148.ExtraInfo.NameColorG = 0
	Actor_148.ExtraInfo.NameColorB = 0
	Actor_148H = ActorHandler(Actor_148)
	environment:AddActorObject(Actor_148H)

	Actor_149 = ActorObjectInfo(149)
	Actor_149:SetRenderType(1)
	Actor_149.DisplayDesc.ModelId = 0
	Actor_149.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_96.osgb"
	Actor_149.DisplayDesc.Outfit = ""
	Actor_149.DisplayDesc.Weapon = ""
	Actor_149.DisplayDesc.Mode = ""
	Actor_149.DisplayDesc.UseLight = false
	Actor_149.DisplayDesc.CastShadow = false
	Actor_149.DisplayDesc.ColorR = 0
	Actor_149.DisplayDesc.ColorG = 9.00502e-024
	Actor_149.DisplayDesc.ColorB = -0.962998
	Actor_149.DisplayDesc.ColorA = 0
	Actor_149:SetModelState(1)
	Actor_149.PhysicDesc.Pos.X = 522
	Actor_149.PhysicDesc.Pos.Y = 10.5469
	Actor_149.PhysicDesc.Pos.Z = 497.25
	Actor_149.PhysicDesc.Pos.Rotation = 0
	Actor_149.PhysicDesc.Density = -0.328792
	Actor_149.PhysicDesc.Collidable = true
	Actor_149.PhysicDesc.SizeX = 0
	Actor_149.PhysicDesc.SizeY = 0
	Actor_149.PhysicDesc.SizeZ = 0
	Actor_149.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_96.phy"
	Actor_149:SetPhysicalActorType(1)
	Actor_149:SetPhysicalShape(5)
	Actor_149.ExtraInfo.Name = ""
	Actor_149.ExtraInfo.NameColorR = 9.82776e-031
	Actor_149.ExtraInfo.NameColorG = -0.962998
	Actor_149.ExtraInfo.NameColorB = 0
	Actor_149H = ActorHandler(Actor_149)
	environment:AddActorObject(Actor_149H)

	Actor_150 = ActorObjectInfo(150)
	Actor_150:SetRenderType(1)
	Actor_150.DisplayDesc.ModelId = 0
	Actor_150.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_97.osgb"
	Actor_150.DisplayDesc.Outfit = ""
	Actor_150.DisplayDesc.Weapon = ""
	Actor_150.DisplayDesc.Mode = ""
	Actor_150.DisplayDesc.UseLight = false
	Actor_150.DisplayDesc.CastShadow = false
	Actor_150.DisplayDesc.ColorR = 0
	Actor_150.DisplayDesc.ColorG = 3.12863e-024
	Actor_150.DisplayDesc.ColorB = -0
	Actor_150.DisplayDesc.ColorA = -1.36719
	Actor_150:SetModelState(1)
	Actor_150.PhysicDesc.Pos.X = 522
	Actor_150.PhysicDesc.Pos.Y = 10.5469
	Actor_150.PhysicDesc.Pos.Z = 497.25
	Actor_150.PhysicDesc.Pos.Rotation = 0
	Actor_150.PhysicDesc.Density = 1.31224e-038
	Actor_150.PhysicDesc.Collidable = true
	Actor_150.PhysicDesc.SizeX = 0
	Actor_150.PhysicDesc.SizeY = 0
	Actor_150.PhysicDesc.SizeZ = 0
	Actor_150.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_97.phy"
	Actor_150:SetPhysicalActorType(1)
	Actor_150:SetPhysicalShape(5)
	Actor_150.ExtraInfo.Name = ""
	Actor_150.ExtraInfo.NameColorR = 1.04767e-030
	Actor_150.ExtraInfo.NameColorG = 0
	Actor_150.ExtraInfo.NameColorB = 0
	Actor_150H = ActorHandler(Actor_150)
	environment:AddActorObject(Actor_150H)

	Actor_151 = ActorObjectInfo(151)
	Actor_151:SetRenderType(1)
	Actor_151.DisplayDesc.ModelId = 0
	Actor_151.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_98.osgb"
	Actor_151.DisplayDesc.Outfit = ""
	Actor_151.DisplayDesc.Weapon = ""
	Actor_151.DisplayDesc.Mode = ""
	Actor_151.DisplayDesc.UseLight = false
	Actor_151.DisplayDesc.CastShadow = false
	Actor_151.DisplayDesc.ColorR = 0
	Actor_151.DisplayDesc.ColorG = 2.1863e-024
	Actor_151.DisplayDesc.ColorB = 5.60519e-045
	Actor_151.DisplayDesc.ColorA = 9.80909e-045
	Actor_151:SetModelState(1)
	Actor_151.PhysicDesc.Pos.X = 522
	Actor_151.PhysicDesc.Pos.Y = 10.5469
	Actor_151.PhysicDesc.Pos.Z = 497.25
	Actor_151.PhysicDesc.Pos.Rotation = 0
	Actor_151.PhysicDesc.Density = 1.4013e-044
	Actor_151.PhysicDesc.Collidable = true
	Actor_151.PhysicDesc.SizeX = 0
	Actor_151.PhysicDesc.SizeY = 0
	Actor_151.PhysicDesc.SizeZ = 0
	Actor_151.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_98.phy"
	Actor_151:SetPhysicalActorType(1)
	Actor_151:SetPhysicalShape(5)
	Actor_151.ExtraInfo.Name = ""
	Actor_151.ExtraInfo.NameColorR = 3.31671e-024
	Actor_151.ExtraInfo.NameColorG = 0
	Actor_151.ExtraInfo.NameColorB = 2.01098e-023
	Actor_151H = ActorHandler(Actor_151)
	environment:AddActorObject(Actor_151H)

	Actor_152 = ActorObjectInfo(152)
	Actor_152:SetRenderType(1)
	Actor_152.DisplayDesc.ModelId = 0
	Actor_152.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_99.osgb"
	Actor_152.DisplayDesc.Outfit = ""
	Actor_152.DisplayDesc.Weapon = ""
	Actor_152.DisplayDesc.Mode = ""
	Actor_152.DisplayDesc.UseLight = false
	Actor_152.DisplayDesc.CastShadow = false
	Actor_152.DisplayDesc.ColorR = 0
	Actor_152.DisplayDesc.ColorG = 3.12809e-024
	Actor_152.DisplayDesc.ColorB = 5.60519e-045
	Actor_152.DisplayDesc.ColorA = 9.80909e-045
	Actor_152:SetModelState(1)
	Actor_152.PhysicDesc.Pos.X = 519
	Actor_152.PhysicDesc.Pos.Y = 11.1328
	Actor_152.PhysicDesc.Pos.Z = 500.004
	Actor_152.PhysicDesc.Pos.Rotation = -90
	Actor_152.PhysicDesc.Density = 1.4013e-044
	Actor_152.PhysicDesc.Collidable = true
	Actor_152.PhysicDesc.SizeX = 0
	Actor_152.PhysicDesc.SizeY = 0
	Actor_152.PhysicDesc.SizeZ = 0
	Actor_152.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_99.phy"
	Actor_152:SetPhysicalActorType(1)
	Actor_152:SetPhysicalShape(5)
	Actor_152.ExtraInfo.Name = ""
	Actor_152.ExtraInfo.NameColorR = 6.10598e-023
	Actor_152.ExtraInfo.NameColorG = 3.32004e-024
	Actor_152.ExtraInfo.NameColorB = 1.4013e-044
	Actor_152H = ActorHandler(Actor_152)
	environment:AddActorObject(Actor_152H)

	Actor_153 = ActorObjectInfo(153)
	Actor_153:SetRenderType(1)
	Actor_153.DisplayDesc.ModelId = 0
	Actor_153.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_100.osgb"
	Actor_153.DisplayDesc.Outfit = ""
	Actor_153.DisplayDesc.Weapon = ""
	Actor_153.DisplayDesc.Mode = ""
	Actor_153.DisplayDesc.UseLight = false
	Actor_153.DisplayDesc.CastShadow = false
	Actor_153.DisplayDesc.ColorR = 0
	Actor_153.DisplayDesc.ColorG = 7.42718e-031
	Actor_153.DisplayDesc.ColorB = 6.44597e-044
	Actor_153.DisplayDesc.ColorA = 2.24208e-044
	Actor_153:SetModelState(1)
	Actor_153.PhysicDesc.Pos.X = 519
	Actor_153.PhysicDesc.Pos.Y = 11.1328
	Actor_153.PhysicDesc.Pos.Z = 500.004
	Actor_153.PhysicDesc.Pos.Rotation = -90
	Actor_153.PhysicDesc.Density = 4.2039e-044
	Actor_153.PhysicDesc.Collidable = true
	Actor_153.PhysicDesc.SizeX = 0
	Actor_153.PhysicDesc.SizeY = 0
	Actor_153.PhysicDesc.SizeZ = 0
	Actor_153.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_100.phy"
	Actor_153:SetPhysicalActorType(1)
	Actor_153:SetPhysicalShape(5)
	Actor_153.ExtraInfo.Name = ""
	Actor_153.ExtraInfo.NameColorR = 7.51667e-031
	Actor_153.ExtraInfo.NameColorG = 6.33053e-024
	Actor_153.ExtraInfo.NameColorB = 1.4013e-044
	Actor_153H = ActorHandler(Actor_153)
	environment:AddActorObject(Actor_153H)

	Actor_154 = ActorObjectInfo(154)
	Actor_154:SetRenderType(1)
	Actor_154.DisplayDesc.ModelId = 0
	Actor_154.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_101.osgb"
	Actor_154.DisplayDesc.Outfit = ""
	Actor_154.DisplayDesc.Weapon = ""
	Actor_154.DisplayDesc.Mode = ""
	Actor_154.DisplayDesc.UseLight = false
	Actor_154.DisplayDesc.CastShadow = false
	Actor_154.DisplayDesc.ColorR = 0
	Actor_154.DisplayDesc.ColorG = 1.79133e-031
	Actor_154.DisplayDesc.ColorB = 5.5908e-039
	Actor_154.DisplayDesc.ColorA = 0
	Actor_154:SetModelState(1)
	Actor_154.PhysicDesc.Pos.X = 512.805
	Actor_154.PhysicDesc.Pos.Y = 10.3828
	Actor_154.PhysicDesc.Pos.Z = 489.582
	Actor_154.PhysicDesc.Pos.Rotation = -90
	Actor_154.PhysicDesc.Density = 0
	Actor_154.PhysicDesc.Collidable = true
	Actor_154.PhysicDesc.SizeX = 0
	Actor_154.PhysicDesc.SizeY = 0
	Actor_154.PhysicDesc.SizeZ = 0
	Actor_154.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_101.phy"
	Actor_154:SetPhysicalActorType(1)
	Actor_154:SetPhysicalShape(5)
	Actor_154.ExtraInfo.Name = ""
	Actor_154.ExtraInfo.NameColorR = 4.95712e-023
	Actor_154.ExtraInfo.NameColorG = 0
	Actor_154.ExtraInfo.NameColorB = 7.77029e-031
	Actor_154H = ActorHandler(Actor_154)
	environment:AddActorObject(Actor_154H)

	Actor_155 = ActorObjectInfo(155)
	Actor_155:SetRenderType(1)
	Actor_155.DisplayDesc.ModelId = 131074
	Actor_155.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_101.osgb"
	Actor_155.DisplayDesc.Outfit = ""
	Actor_155.DisplayDesc.Weapon = ""
	Actor_155.DisplayDesc.Mode = ""
	Actor_155.DisplayDesc.UseLight = false
	Actor_155.DisplayDesc.CastShadow = true
	Actor_155.DisplayDesc.ColorR = 1.8743e-031
	Actor_155.DisplayDesc.ColorG = 1.65305e-039
	Actor_155.DisplayDesc.ColorB = 2.68959e-035
	Actor_155.DisplayDesc.ColorA = 0
	Actor_155:SetModelState(1)
	Actor_155.PhysicDesc.Pos.X = 510.91
	Actor_155.PhysicDesc.Pos.Y = 10.3828
	Actor_155.PhysicDesc.Pos.Z = 489.582
	Actor_155.PhysicDesc.Pos.Rotation = -90
	Actor_155.PhysicDesc.Density = 1.45743e+019
	Actor_155.PhysicDesc.Collidable = true
	Actor_155.PhysicDesc.SizeX = 9.14422e-024
	Actor_155.PhysicDesc.SizeY = 3.60134e-043
	Actor_155.PhysicDesc.SizeZ = 2.5714e-039
	Actor_155.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_101.phy"
	Actor_155:SetPhysicalActorType(1)
	Actor_155:SetPhysicalShape(5)
	Actor_155.ExtraInfo.Name = ""
	Actor_155.ExtraInfo.NameColorR = 0
	Actor_155.ExtraInfo.NameColorG = 0.707107
	Actor_155.ExtraInfo.NameColorB = 0
	Actor_155H = ActorHandler(Actor_155)
	environment:AddActorObject(Actor_155H)

	Actor_156 = ActorObjectInfo(156)
	Actor_156:SetRenderType(1)
	Actor_156.DisplayDesc.ModelId = 0
	Actor_156.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_102.osgb"
	Actor_156.DisplayDesc.Outfit = ""
	Actor_156.DisplayDesc.Weapon = ""
	Actor_156.DisplayDesc.Mode = ""
	Actor_156.DisplayDesc.UseLight = false
	Actor_156.DisplayDesc.CastShadow = false
	Actor_156.DisplayDesc.ColorR = 0
	Actor_156.DisplayDesc.ColorG = 2.26316e-020
	Actor_156.DisplayDesc.ColorB = 6.44597e-044
	Actor_156.DisplayDesc.ColorA = 2.24208e-044
	Actor_156:SetModelState(1)
	Actor_156.PhysicDesc.Pos.X = 517.25
	Actor_156.PhysicDesc.Pos.Y = 10.5469
	Actor_156.PhysicDesc.Pos.Z = 491.625
	Actor_156.PhysicDesc.Pos.Rotation = 90
	Actor_156.PhysicDesc.Density = 4.2039e-044
	Actor_156.PhysicDesc.Collidable = true
	Actor_156.PhysicDesc.SizeX = 0
	Actor_156.PhysicDesc.SizeY = 0
	Actor_156.PhysicDesc.SizeZ = 0
	Actor_156.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_102.phy"
	Actor_156:SetPhysicalActorType(1)
	Actor_156:SetPhysicalShape(5)
	Actor_156.ExtraInfo.Name = ""
	Actor_156.ExtraInfo.NameColorR = 2.53181e-023
	Actor_156.ExtraInfo.NameColorG = 5.60519e-045
	Actor_156.ExtraInfo.NameColorB = 0
	Actor_156H = ActorHandler(Actor_156)
	environment:AddActorObject(Actor_156H)

	Actor_157 = ActorObjectInfo(157)
	Actor_157:SetRenderType(1)
	Actor_157.DisplayDesc.ModelId = 0
	Actor_157.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_103.osgb"
	Actor_157.DisplayDesc.Outfit = ""
	Actor_157.DisplayDesc.Weapon = ""
	Actor_157.DisplayDesc.Mode = ""
	Actor_157.DisplayDesc.UseLight = false
	Actor_157.DisplayDesc.CastShadow = false
	Actor_157.DisplayDesc.ColorR = 0
	Actor_157.DisplayDesc.ColorG = 4.88203e-034
	Actor_157.DisplayDesc.ColorB = 6.44597e-044
	Actor_157.DisplayDesc.ColorA = 2.24208e-044
	Actor_157:SetModelState(1)
	Actor_157.PhysicDesc.Pos.X = 516.375
	Actor_157.PhysicDesc.Pos.Y = 10.5469
	Actor_157.PhysicDesc.Pos.Z = 493.5
	Actor_157.PhysicDesc.Pos.Rotation = 90
	Actor_157.PhysicDesc.Density = 4.2039e-044
	Actor_157.PhysicDesc.Collidable = true
	Actor_157.PhysicDesc.SizeX = 0
	Actor_157.PhysicDesc.SizeY = 0
	Actor_157.PhysicDesc.SizeZ = 0
	Actor_157.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_103.phy"
	Actor_157:SetPhysicalActorType(1)
	Actor_157:SetPhysicalShape(5)
	Actor_157.ExtraInfo.Name = ""
	Actor_157.ExtraInfo.NameColorR = 1.79425e-031
	Actor_157.ExtraInfo.NameColorG = 0
	Actor_157.ExtraInfo.NameColorB = 7.94603e-023
	Actor_157H = ActorHandler(Actor_157)
	environment:AddActorObject(Actor_157H)

	Actor_158 = ActorObjectInfo(158)
	Actor_158:SetRenderType(1)
	Actor_158.DisplayDesc.ModelId = 427068112
	Actor_158.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.osgb"
	Actor_158.DisplayDesc.Outfit = ""
	Actor_158.DisplayDesc.Weapon = ""
	Actor_158.DisplayDesc.Mode = ""
	Actor_158.DisplayDesc.UseLight = false
	Actor_158.DisplayDesc.CastShadow = true
	Actor_158.DisplayDesc.ColorR = 4.4926e-034
	Actor_158.DisplayDesc.ColorG = 1.83674e-040
	Actor_158.DisplayDesc.ColorB = 1.05329e-034
	Actor_158.DisplayDesc.ColorA = 3.27833e-024
	Actor_158:SetModelState(1)
	Actor_158.PhysicDesc.Pos.X = 533.5
	Actor_158.PhysicDesc.Pos.Y = 11.1328
	Actor_158.PhysicDesc.Pos.Z = 494.5
	Actor_158.PhysicDesc.Pos.Rotation = 0
	Actor_158.PhysicDesc.Density = 1.31224e-038
	Actor_158.PhysicDesc.Collidable = true
	Actor_158.PhysicDesc.SizeX = 0
	Actor_158.PhysicDesc.SizeY = 3.22299e-044
	Actor_158.PhysicDesc.SizeZ = 0
	Actor_158.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.phy"
	Actor_158:SetPhysicalActorType(1)
	Actor_158:SetPhysicalShape(5)
	Actor_158.ExtraInfo.Name = ""
	Actor_158.ExtraInfo.NameColorR = 1.05325e-034
	Actor_158.ExtraInfo.NameColorG = 3.1057e-023
	Actor_158.ExtraInfo.NameColorB = 9.26159e-024
	Actor_158H = ActorHandler(Actor_158)
	environment:AddActorObject(Actor_158H)

	Actor_159 = ActorObjectInfo(159)
	Actor_159:SetRenderType(1)
	Actor_159.DisplayDesc.ModelId = 131077
	Actor_159.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.osgb"
	Actor_159.DisplayDesc.Outfit = ""
	Actor_159.DisplayDesc.Weapon = ""
	Actor_159.DisplayDesc.Mode = ""
	Actor_159.DisplayDesc.UseLight = false
	Actor_159.DisplayDesc.CastShadow = true
	Actor_159.DisplayDesc.ColorR = 1.86386e-031
	Actor_159.DisplayDesc.ColorG = 1.05053e-030
	Actor_159.DisplayDesc.ColorB = 1.4013e-045
	Actor_159.DisplayDesc.ColorA = 9.18369e-040
	Actor_159:SetModelState(1)
	Actor_159.PhysicDesc.Pos.X = 535.5
	Actor_159.PhysicDesc.Pos.Y = 10.8398
	Actor_159.PhysicDesc.Pos.Z = 492.5
	Actor_159.PhysicDesc.Pos.Rotation = 0
	Actor_159.PhysicDesc.Density = 0
	Actor_159.PhysicDesc.Collidable = true
	Actor_159.PhysicDesc.SizeX = 1.88341e-031
	Actor_159.PhysicDesc.SizeY = 0.000976563
	Actor_159.PhysicDesc.SizeZ = 1.05053e-030
	Actor_159.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.phy"
	Actor_159:SetPhysicalActorType(1)
	Actor_159:SetPhysicalShape(5)
	Actor_159.ExtraInfo.Name = ""
	Actor_159.ExtraInfo.NameColorR = 9.62965e-035
	Actor_159.ExtraInfo.NameColorG = 3.35214e-024
	Actor_159.ExtraInfo.NameColorB = 1.4013e-045
	Actor_159H = ActorHandler(Actor_159)
	environment:AddActorObject(Actor_159H)

	Actor_160 = ActorObjectInfo(160)
	Actor_160:SetRenderType(1)
	Actor_160.DisplayDesc.ModelId = 436128064
	Actor_160.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.osgb"
	Actor_160.DisplayDesc.Outfit = ""
	Actor_160.DisplayDesc.Weapon = ""
	Actor_160.DisplayDesc.Mode = ""
	Actor_160.DisplayDesc.UseLight = false
	Actor_160.DisplayDesc.CastShadow = false
	Actor_160.DisplayDesc.ColorR = 1.02319e-034
	Actor_160.DisplayDesc.ColorG = 8.99243e-024
	Actor_160.DisplayDesc.ColorB = 8.94592e-024
	Actor_160.DisplayDesc.ColorA = 7.46e-031
	Actor_160:SetModelState(1)
	Actor_160.PhysicDesc.Pos.X = 533.5
	Actor_160.PhysicDesc.Pos.Y = 11.1328
	Actor_160.PhysicDesc.Pos.Z = 492.5
	Actor_160.PhysicDesc.Pos.Rotation = 0
	Actor_160.PhysicDesc.Density = 3.37021e-024
	Actor_160.PhysicDesc.Collidable = true
	Actor_160.PhysicDesc.SizeX = 2.47956e-039
	Actor_160.PhysicDesc.SizeY = 1.05328e-034
	Actor_160.PhysicDesc.SizeZ = 1.087e-023
	Actor_160.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.phy"
	Actor_160:SetPhysicalActorType(1)
	Actor_160:SetPhysicalShape(5)
	Actor_160.ExtraInfo.Name = ""
	Actor_160.ExtraInfo.NameColorR = 9.80909e-045
	Actor_160.ExtraInfo.NameColorG = 0
	Actor_160.ExtraInfo.NameColorB = 4.57348e-038
	Actor_160H = ActorHandler(Actor_160)
	environment:AddActorObject(Actor_160H)

	Actor_161 = ActorObjectInfo(161)
	Actor_161:SetRenderType(1)
	Actor_161.DisplayDesc.ModelId = 0
	Actor_161.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_105.osgb"
	Actor_161.DisplayDesc.Outfit = ""
	Actor_161.DisplayDesc.Weapon = ""
	Actor_161.DisplayDesc.Mode = ""
	Actor_161.DisplayDesc.UseLight = false
	Actor_161.DisplayDesc.CastShadow = false
	Actor_161.DisplayDesc.ColorR = 0
	Actor_161.DisplayDesc.ColorG = 3.09629e-023
	Actor_161.DisplayDesc.ColorB = 6.44597e-044
	Actor_161.DisplayDesc.ColorA = 2.24208e-044
	Actor_161:SetModelState(1)
	Actor_161.PhysicDesc.Pos.X = 534.125
	Actor_161.PhysicDesc.Pos.Y = 10.7656
	Actor_161.PhysicDesc.Pos.Z = 490.5
	Actor_161.PhysicDesc.Pos.Rotation = 90
	Actor_161.PhysicDesc.Density = 4.2039e-044
	Actor_161.PhysicDesc.Collidable = true
	Actor_161.PhysicDesc.SizeX = 0
	Actor_161.PhysicDesc.SizeY = 0
	Actor_161.PhysicDesc.SizeZ = 0
	Actor_161.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_105.phy"
	Actor_161:SetPhysicalActorType(1)
	Actor_161:SetPhysicalShape(5)
	Actor_161.ExtraInfo.Name = ""
	Actor_161.ExtraInfo.NameColorR = 7.8659e-023
	Actor_161.ExtraInfo.NameColorG = 1.82196e-031
	Actor_161.ExtraInfo.NameColorB = 2.89207e-024
	Actor_161H = ActorHandler(Actor_161)
	environment:AddActorObject(Actor_161H)

	Actor_162 = ActorObjectInfo(162)
	Actor_162:SetRenderType(1)
	Actor_162.DisplayDesc.ModelId = 0
	Actor_162.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_102.osgb"
	Actor_162.DisplayDesc.Outfit = ""
	Actor_162.DisplayDesc.Weapon = ""
	Actor_162.DisplayDesc.Mode = ""
	Actor_162.DisplayDesc.UseLight = false
	Actor_162.DisplayDesc.CastShadow = true
	Actor_162.DisplayDesc.ColorR = 4.44603e-024
	Actor_162.DisplayDesc.ColorG = 5.70731e-023
	Actor_162.DisplayDesc.ColorB = 2.89161e-024
	Actor_162.DisplayDesc.ColorA = 7.45759e-023
	Actor_162:SetModelState(1)
	Actor_162.PhysicDesc.Pos.X = 531.5
	Actor_162.PhysicDesc.Pos.Y = 10.8398
	Actor_162.PhysicDesc.Pos.Z = 487.5
	Actor_162.PhysicDesc.Pos.Rotation = 180
	Actor_162.PhysicDesc.Density = 0
	Actor_162.PhysicDesc.Collidable = true
	Actor_162.PhysicDesc.SizeX = 5.98849e-024
	Actor_162.PhysicDesc.SizeY = 1.04887e-030
	Actor_162.PhysicDesc.SizeZ = 1.83686e-040
	Actor_162.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_102.phy"
	Actor_162:SetPhysicalActorType(1)
	Actor_162:SetPhysicalShape(5)
	Actor_162.ExtraInfo.Name = ""
	Actor_162.ExtraInfo.NameColorR = 0
	Actor_162.ExtraInfo.NameColorG = 0
	Actor_162.ExtraInfo.NameColorB = 2.62769e-023
	Actor_162H = ActorHandler(Actor_162)
	environment:AddActorObject(Actor_162H)

	Actor_163 = ActorObjectInfo(163)
	Actor_163:SetRenderType(1)
	Actor_163.DisplayDesc.ModelId = 0
	Actor_163.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_106.osgb"
	Actor_163.DisplayDesc.Outfit = ""
	Actor_163.DisplayDesc.Weapon = ""
	Actor_163.DisplayDesc.Mode = ""
	Actor_163.DisplayDesc.UseLight = false
	Actor_163.DisplayDesc.CastShadow = false
	Actor_163.DisplayDesc.ColorR = 0
	Actor_163.DisplayDesc.ColorG = 9.25876e-024
	Actor_163.DisplayDesc.ColorB = 1.05328e-034
	Actor_163.DisplayDesc.ColorA = 3.13351e-024
	Actor_163:SetModelState(1)
	Actor_163.PhysicDesc.Pos.X = 528.5
	Actor_163.PhysicDesc.Pos.Y = 11.3281
	Actor_163.PhysicDesc.Pos.Z = 519
	Actor_163.PhysicDesc.Pos.Rotation = -90
	Actor_163.PhysicDesc.Density = 1.83677e-040
	Actor_163.PhysicDesc.Collidable = true
	Actor_163.PhysicDesc.SizeX = 0
	Actor_163.PhysicDesc.SizeY = 0
	Actor_163.PhysicDesc.SizeZ = 0
	Actor_163.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_106.phy"
	Actor_163:SetPhysicalActorType(1)
	Actor_163:SetPhysicalShape(5)
	Actor_163.ExtraInfo.Name = ""
	Actor_163.ExtraInfo.NameColorR = 3.23964e-024
	Actor_163.ExtraInfo.NameColorG = 0
	Actor_163.ExtraInfo.NameColorB = 4.59574e-024
	Actor_163H = ActorHandler(Actor_163)
	environment:AddActorObject(Actor_163H)

	Actor_164 = ActorObjectInfo(164)
	Actor_164:SetRenderType(1)
	Actor_164.DisplayDesc.ModelId = 0
	Actor_164.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.osgb"
	Actor_164.DisplayDesc.Outfit = ""
	Actor_164.DisplayDesc.Weapon = ""
	Actor_164.DisplayDesc.Mode = ""
	Actor_164.DisplayDesc.UseLight = false
	Actor_164.DisplayDesc.CastShadow = false
	Actor_164.DisplayDesc.ColorR = 0
	Actor_164.DisplayDesc.ColorG = 1.31412e-020
	Actor_164.DisplayDesc.ColorB = 6.44597e-044
	Actor_164.DisplayDesc.ColorA = 2.24208e-044
	Actor_164:SetModelState(1)
	Actor_164.PhysicDesc.Pos.X = 487.5
	Actor_164.PhysicDesc.Pos.Y = 11.1328
	Actor_164.PhysicDesc.Pos.Z = 495.5
	Actor_164.PhysicDesc.Pos.Rotation = 0
	Actor_164.PhysicDesc.Density = 4.2039e-044
	Actor_164.PhysicDesc.Collidable = true
	Actor_164.PhysicDesc.SizeX = 0
	Actor_164.PhysicDesc.SizeY = 0
	Actor_164.PhysicDesc.SizeZ = 0
	Actor_164.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.phy"
	Actor_164:SetPhysicalActorType(1)
	Actor_164:SetPhysicalShape(5)
	Actor_164.ExtraInfo.Name = ""
	Actor_164.ExtraInfo.NameColorR = 6.082e-038
	Actor_164.ExtraInfo.NameColorG = 0
	Actor_164.ExtraInfo.NameColorB = 1.76297e-031
	Actor_164H = ActorHandler(Actor_164)
	environment:AddActorObject(Actor_164H)

	Actor_165 = ActorObjectInfo(165)
	Actor_165:SetRenderType(1)
	Actor_165.DisplayDesc.ModelId = 131074
	Actor_165.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.osgb"
	Actor_165.DisplayDesc.Outfit = ""
	Actor_165.DisplayDesc.Weapon = ""
	Actor_165.DisplayDesc.Mode = ""
	Actor_165.DisplayDesc.UseLight = false
	Actor_165.DisplayDesc.CastShadow = false
	Actor_165.DisplayDesc.ColorR = 0
	Actor_165.DisplayDesc.ColorG = 0
	Actor_165.DisplayDesc.ColorB = 0
	Actor_165.DisplayDesc.ColorA = 0
	Actor_165:SetModelState(1)
	Actor_165.PhysicDesc.Pos.X = 489.5
	Actor_165.PhysicDesc.Pos.Y = 11.1328
	Actor_165.PhysicDesc.Pos.Z = 497.5
	Actor_165.PhysicDesc.Pos.Rotation = 0
	Actor_165.PhysicDesc.Density = 7.03592e-023
	Actor_165.PhysicDesc.Collidable = true
	Actor_165.PhysicDesc.SizeX = 2.47958e-039
	Actor_165.PhysicDesc.SizeY = 1.02315e-034
	Actor_165.PhysicDesc.SizeZ = 9.14614e-024
	Actor_165.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_104.phy"
	Actor_165:SetPhysicalActorType(1)
	Actor_165:SetPhysicalShape(5)
	Actor_165.ExtraInfo.Name = ""
	Actor_165.ExtraInfo.NameColorR = 4.57352e-038
	Actor_165.ExtraInfo.NameColorG = 0
	Actor_165.ExtraInfo.NameColorB = 0
	Actor_165H = ActorHandler(Actor_165)
	environment:AddActorObject(Actor_165H)

	Actor_166 = ActorObjectInfo(166)
	Actor_166:SetRenderType(1)
	Actor_166.DisplayDesc.ModelId = 0
	Actor_166.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_105.osgb"
	Actor_166.DisplayDesc.Outfit = ""
	Actor_166.DisplayDesc.Weapon = ""
	Actor_166.DisplayDesc.Mode = ""
	Actor_166.DisplayDesc.UseLight = false
	Actor_166.DisplayDesc.CastShadow = false
	Actor_166.DisplayDesc.ColorR = 1.05326e-034
	Actor_166.DisplayDesc.ColorG = 2.45424e-024
	Actor_166.DisplayDesc.ColorB = 2.36491e-023
	Actor_166.DisplayDesc.ColorA = 5.88545e-044
	Actor_166:SetModelState(1)
	Actor_166.PhysicDesc.Pos.X = 489.5
	Actor_166.PhysicDesc.Pos.Y = 11.1328
	Actor_166.PhysicDesc.Pos.Z = 494.5
	Actor_166.PhysicDesc.Pos.Rotation = 0
	Actor_166.PhysicDesc.Density = 0
	Actor_166.PhysicDesc.Collidable = true
	Actor_166.PhysicDesc.SizeX = 0
	Actor_166.PhysicDesc.SizeY = 2.38221e-044
	Actor_166.PhysicDesc.SizeZ = 1.01021e-039
	Actor_166.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_105.phy"
	Actor_166:SetPhysicalActorType(1)
	Actor_166:SetPhysicalShape(5)
	Actor_166.ExtraInfo.Name = ""
	Actor_166.ExtraInfo.NameColorR = 0
	Actor_166.ExtraInfo.NameColorG = 0
	Actor_166.ExtraInfo.NameColorB = 3.09737e-023
	Actor_166H = ActorHandler(Actor_166)
	environment:AddActorObject(Actor_166H)

	Actor_167 = ActorObjectInfo(167)
	Actor_167:SetRenderType(1)
	Actor_167.DisplayDesc.ModelId = 0
	Actor_167.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.osgb"
	Actor_167.DisplayDesc.Outfit = ""
	Actor_167.DisplayDesc.Weapon = ""
	Actor_167.DisplayDesc.Mode = ""
	Actor_167.DisplayDesc.UseLight = false
	Actor_167.DisplayDesc.CastShadow = false
	Actor_167.DisplayDesc.ColorR = 5.625
	Actor_167.DisplayDesc.ColorG = 0
	Actor_167.DisplayDesc.ColorB = 0
	Actor_167.DisplayDesc.ColorA = 0
	Actor_167:SetModelState(1)
	Actor_167.PhysicDesc.Pos.X = 508.5
	Actor_167.PhysicDesc.Pos.Y = 10.1563
	Actor_167.PhysicDesc.Pos.Z = 486.5
	Actor_167.PhysicDesc.Pos.Rotation = 90
	Actor_167.PhysicDesc.Density = 1.06466e-023
	Actor_167.PhysicDesc.Collidable = true
	Actor_167.PhysicDesc.SizeX = 2
	Actor_167.PhysicDesc.SizeY = 0
	Actor_167.PhysicDesc.SizeZ = 0
	Actor_167.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_25.phy"
	Actor_167:SetPhysicalActorType(1)
	Actor_167:SetPhysicalShape(5)
	Actor_167.ExtraInfo.Name = ""
	Actor_167.ExtraInfo.NameColorR = -2.00002
	Actor_167.ExtraInfo.NameColorG = 3.35214e-024
	Actor_167.ExtraInfo.NameColorB = 1.4013e-045
	Actor_167H = ActorHandler(Actor_167)
	environment:AddActorObject(Actor_167H)

	Actor_168 = ActorObjectInfo(168)
	Actor_168:SetRenderType(1)
	Actor_168.DisplayDesc.ModelId = 229391096
	Actor_168.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_33.osgb"
	Actor_168.DisplayDesc.Outfit = ""
	Actor_168.DisplayDesc.Weapon = ""
	Actor_168.DisplayDesc.Mode = ""
	Actor_168.DisplayDesc.UseLight = false
	Actor_168.DisplayDesc.CastShadow = false
	Actor_168.DisplayDesc.ColorR = -1
	Actor_168.DisplayDesc.ColorG = 0
	Actor_168.DisplayDesc.ColorB = -3.17383
	Actor_168.DisplayDesc.ColorA = 4.39453
	Actor_168:SetModelState(1)
	Actor_168.PhysicDesc.Pos.X = 525.5
	Actor_168.PhysicDesc.Pos.Y = 10.5469
	Actor_168.PhysicDesc.Pos.Z = 504.5
	Actor_168.PhysicDesc.Pos.Rotation = 0
	Actor_168.PhysicDesc.Density = 0
	Actor_168.PhysicDesc.Collidable = true
	Actor_168.PhysicDesc.SizeX = 0
	Actor_168.PhysicDesc.SizeY = 0
	Actor_168.PhysicDesc.SizeZ = 0
	Actor_168.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_33.phy"
	Actor_168:SetPhysicalActorType(1)
	Actor_168:SetPhysicalShape(5)
	Actor_168.ExtraInfo.Name = ""
	Actor_168.ExtraInfo.NameColorR = 0
	Actor_168.ExtraInfo.NameColorG = 5.90711e-023
	Actor_168.ExtraInfo.NameColorB = 9.99048e-024
	Actor_168H = ActorHandler(Actor_168)
	environment:AddActorObject(Actor_168H)

	Actor_169 = ActorObjectInfo(169)
	Actor_169:SetRenderType(1)
	Actor_169.DisplayDesc.ModelId = 3
	Actor_169.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/PLATFORM_OBJ_34.osgb"
	Actor_169.DisplayDesc.Outfit = ""
	Actor_169.DisplayDesc.Weapon = ""
	Actor_169.DisplayDesc.Mode = ""
	Actor_169.DisplayDesc.UseLight = false
	Actor_169.DisplayDesc.CastShadow = false
	Actor_169.DisplayDesc.ColorR = 0
	Actor_169.DisplayDesc.ColorG = 0
	Actor_169.DisplayDesc.ColorB = 0
	Actor_169.DisplayDesc.ColorA = 0
	Actor_169:SetModelState(1)
	Actor_169.PhysicDesc.Pos.X = 533.5
	Actor_169.PhysicDesc.Pos.Y = 11.1328
	Actor_169.PhysicDesc.Pos.Z = 501.5
	Actor_169.PhysicDesc.Pos.Rotation = 90
	Actor_169.PhysicDesc.Density = 2.04997e-023
	Actor_169.PhysicDesc.Collidable = true
	Actor_169.PhysicDesc.SizeX = 2.53444e-023
	Actor_169.PhysicDesc.SizeY = 1.02121e-023
	Actor_169.PhysicDesc.SizeZ = 1.0209e-023
	Actor_169.PhysicDesc.Filename = "Worlds/Lba2Original/Models/PLATFORM_OBJ_34.phy"
	Actor_169:SetPhysicalActorType(1)
	Actor_169:SetPhysicalShape(5)
	Actor_169.ExtraInfo.Name = ""
	Actor_169.ExtraInfo.NameColorR = 0
	Actor_169.ExtraInfo.NameColorG = 8.40779e-045
	Actor_169.ExtraInfo.NameColorB = 0
	Actor_169H = ActorHandler(Actor_169)
	environment:AddActorObject(Actor_169H)

end

