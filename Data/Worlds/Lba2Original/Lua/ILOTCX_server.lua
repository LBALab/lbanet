function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(456)
	Spawn_1:SetPosY(12.3)
	Spawn_1:SetPosZ(454)
	Spawn_1:SetName("Teleport")
	environment:AddSpawn(Spawn_1)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 750
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = false
	Actor_1.DisplayDesc.CastShadow = true
	Actor_1.DisplayDesc.ColorR = 1
	Actor_1.DisplayDesc.ColorG = 1
	Actor_1.DisplayDesc.ColorB = 2.10195e-044
	Actor_1.DisplayDesc.ColorA = 5.03608e-024
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = 0
	Actor_1.ExtraInfo.NameColorG = 7.64534e-031
	Actor_1.ExtraInfo.NameColorB = 0
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Actor_2 = ActorObjectInfo(2)
	Actor_2:SetRenderType(1)
	Actor_2.DisplayDesc.ModelId = 0
	Actor_2.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_1.osgb"
	Actor_2.DisplayDesc.Outfit = ""
	Actor_2.DisplayDesc.Weapon = ""
	Actor_2.DisplayDesc.Mode = ""
	Actor_2.DisplayDesc.UseLight = false
	Actor_2.DisplayDesc.CastShadow = true
	Actor_2.DisplayDesc.ColorR = 1
	Actor_2.DisplayDesc.ColorG = 1
	Actor_2.DisplayDesc.ColorB = 1
	Actor_2.DisplayDesc.ColorA = 1
	Actor_2:SetModelState(1)
	Actor_2.PhysicDesc.Pos.X = 448
	Actor_2.PhysicDesc.Pos.Y = 12.5
	Actor_2.PhysicDesc.Pos.Z = 448
	Actor_2.PhysicDesc.Pos.Rotation = 90
	Actor_2.PhysicDesc.Density = 2.10195e-044
	Actor_2.PhysicDesc.Collidable = true
	Actor_2.PhysicDesc.SizeX = 2.02061e-023
	Actor_2.PhysicDesc.SizeY = 0
	Actor_2.PhysicDesc.SizeZ = 0
	Actor_2.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_1.phy"
	Actor_2:SetPhysicalActorType(1)
	Actor_2:SetPhysicalShape(5)
	Actor_2.ExtraInfo.Name = ""
	Actor_2.ExtraInfo.NameColorR = 0
	Actor_2.ExtraInfo.NameColorG = 0
	Actor_2.ExtraInfo.NameColorB = 0
	Actor_2H = ActorHandler(Actor_2)
	environment:AddActorObject(Actor_2H)

	Actor_3 = ActorObjectInfo(3)
	Actor_3:SetRenderType(1)
	Actor_3.DisplayDesc.ModelId = 0
	Actor_3.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_3.osgb"
	Actor_3.DisplayDesc.Outfit = ""
	Actor_3.DisplayDesc.Weapon = ""
	Actor_3.DisplayDesc.Mode = ""
	Actor_3.DisplayDesc.UseLight = false
	Actor_3.DisplayDesc.CastShadow = true
	Actor_3.DisplayDesc.ColorR = 1.51116e+023
	Actor_3.DisplayDesc.ColorG = 1
	Actor_3.DisplayDesc.ColorB = 2.10195e-044
	Actor_3.DisplayDesc.ColorA = 3.3646e-023
	Actor_3:SetModelState(1)
	Actor_3.PhysicDesc.Pos.X = 442.5
	Actor_3.PhysicDesc.Pos.Y = 10
	Actor_3.PhysicDesc.Pos.Z = 445.5
	Actor_3.PhysicDesc.Pos.Rotation = -90
	Actor_3.PhysicDesc.Density = 2.10195e-044
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = -90
	Actor_3.PhysicDesc.SizeY = 5.60519e-045
	Actor_3.PhysicDesc.SizeZ = 0
	Actor_3.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_3.phy"
	Actor_3:SetPhysicalActorType(1)
	Actor_3:SetPhysicalShape(5)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 1.05325e-034
	Actor_3.ExtraInfo.NameColorG = 4.57362e-038
	Actor_3.ExtraInfo.NameColorB = 2.65324e-024
	Actor_3H = ActorHandler(Actor_3)
	environment:AddActorObject(Actor_3H)

	Actor_4 = ActorObjectInfo(4)
	Actor_4:SetRenderType(1)
	Actor_4.DisplayDesc.ModelId = 24707752
	Actor_4.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_3.osgb"
	Actor_4.DisplayDesc.Outfit = ""
	Actor_4.DisplayDesc.Weapon = ""
	Actor_4.DisplayDesc.Mode = ""
	Actor_4.DisplayDesc.UseLight = false
	Actor_4.DisplayDesc.CastShadow = false
	Actor_4.DisplayDesc.ColorR = 5.60519e-045
	Actor_4.DisplayDesc.ColorG = 1
	Actor_4.DisplayDesc.ColorB = 1
	Actor_4.DisplayDesc.ColorA = 1.652344
	Actor_4:SetModelState(1)
	Actor_4.PhysicDesc.Pos.X = 450.5
	Actor_4.PhysicDesc.Pos.Y = 10
	Actor_4.PhysicDesc.Pos.Z = 453.625
	Actor_4.PhysicDesc.Pos.Rotation = 90
	Actor_4.PhysicDesc.Density = 0
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 2.10195e-044
	Actor_4.PhysicDesc.SizeY = 1.05325e-034
	Actor_4.PhysicDesc.SizeZ = 13.2678
	Actor_4.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_3.phy"
	Actor_4:SetPhysicalActorType(1)
	Actor_4:SetPhysicalShape(5)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 9.62965e-035
	Actor_4.ExtraInfo.NameColorG = 1.90513e-023
	Actor_4.ExtraInfo.NameColorB = 9.88513e-031
	Actor_4H = ActorHandler(Actor_4)
	environment:AddActorObject(Actor_4H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(1)
	Actor_5.DisplayDesc.ModelId = 423430000
	Actor_5.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_4.osgb"
	Actor_5.DisplayDesc.Outfit = ""
	Actor_5.DisplayDesc.Weapon = ""
	Actor_5.DisplayDesc.Mode = ""
	Actor_5.DisplayDesc.UseLight = false
	Actor_5.DisplayDesc.CastShadow = true
	Actor_5.DisplayDesc.ColorR = 1
	Actor_5.DisplayDesc.ColorG = 2.10195e-044
	Actor_5.DisplayDesc.ColorB = 1
	Actor_5.DisplayDesc.ColorA = 8.24473e-024
	Actor_5:SetModelState(1)
	Actor_5.PhysicDesc.Pos.X = 455.875
	Actor_5.PhysicDesc.Pos.Y = 10
	Actor_5.PhysicDesc.Pos.Z = 440.125
	Actor_5.PhysicDesc.Pos.Rotation = 90
	Actor_5.PhysicDesc.Density = 4.42532e-039
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = 0.0913386
	Actor_5.PhysicDesc.SizeY = 1.01019e-039
	Actor_5.PhysicDesc.SizeZ = 0
	Actor_5.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_4.phy"
	Actor_5:SetPhysicalActorType(1)
	Actor_5:SetPhysicalShape(5)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = 5.60519e-045
	Actor_5.ExtraInfo.NameColorG = 0
	Actor_5.ExtraInfo.NameColorB = 0
	Actor_5H = ActorHandler(Actor_5)
	environment:AddActorObject(Actor_5H)

	Actor_6 = ActorObjectInfo(6)
	Actor_6:SetRenderType(1)
	Actor_6.DisplayDesc.ModelId = 0
	Actor_6.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_4.osgb"
	Actor_6.DisplayDesc.Outfit = ""
	Actor_6.DisplayDesc.Weapon = ""
	Actor_6.DisplayDesc.Mode = ""
	Actor_6.DisplayDesc.UseLight = false
	Actor_6.DisplayDesc.CastShadow = false
	Actor_6.DisplayDesc.ColorR = 5.87747e-039
	Actor_6.DisplayDesc.ColorG = 1.4013e-045
	Actor_6.DisplayDesc.ColorB = 1.4013e-045
	Actor_6.DisplayDesc.ColorA = 1.4013e-045
	Actor_6:SetModelState(1)
	Actor_6.PhysicDesc.Pos.X = 440.125
	Actor_6.PhysicDesc.Pos.Y = 10
	Actor_6.PhysicDesc.Pos.Z = 455.875
	Actor_6.PhysicDesc.Pos.Rotation = 90
	Actor_6.PhysicDesc.Density = 0
	Actor_6.PhysicDesc.Collidable = true
	Actor_6.PhysicDesc.SizeX = 1.4013e-045
	Actor_6.PhysicDesc.SizeY = 1.4013e-045
	Actor_6.PhysicDesc.SizeZ = 1.4013e-045
	Actor_6.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_4.phy"
	Actor_6:SetPhysicalActorType(1)
	Actor_6:SetPhysicalShape(5)
	Actor_6.ExtraInfo.Name = ""
	Actor_6.ExtraInfo.NameColorR = 2.10195e-044
	Actor_6.ExtraInfo.NameColorG = 1.4013e-045
	Actor_6.ExtraInfo.NameColorB = 1.4013e-045
	Actor_6H = ActorHandler(Actor_6)
	environment:AddActorObject(Actor_6H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(1)
	Actor_7.DisplayDesc.ModelId = 6
	Actor_7.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_5.osgb"
	Actor_7.DisplayDesc.Outfit = ""
	Actor_7.DisplayDesc.Weapon = ""
	Actor_7.DisplayDesc.Mode = ""
	Actor_7.DisplayDesc.UseLight = false
	Actor_7.DisplayDesc.CastShadow = false
	Actor_7.DisplayDesc.ColorR = 1
	Actor_7.DisplayDesc.ColorG = 1
	Actor_7.DisplayDesc.ColorB = 1
	Actor_7.DisplayDesc.ColorA = 1
	Actor_7:SetModelState(1)
	Actor_7.PhysicDesc.Pos.X = 439
	Actor_7.PhysicDesc.Pos.Y = 10
	Actor_7.PhysicDesc.Pos.Z = 462
	Actor_7.PhysicDesc.Pos.Rotation = -90
	Actor_7.PhysicDesc.Density = 0
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 0
	Actor_7.PhysicDesc.SizeY = 0
	Actor_7.PhysicDesc.SizeZ = 0
	Actor_7.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_5.phy"
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
	Actor_8.DisplayDesc.ModelId = 24707840
	Actor_8.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_6.osgb"
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
	Actor_8.PhysicDesc.Pos.X = 439.125
	Actor_8.PhysicDesc.Pos.Y = 10
	Actor_8.PhysicDesc.Pos.Z = 457
	Actor_8.PhysicDesc.Pos.Rotation = 0
	Actor_8.PhysicDesc.Density = 0
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 0
	Actor_8.PhysicDesc.SizeY = 0
	Actor_8.PhysicDesc.SizeZ = 0
	Actor_8.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_6.phy"
	Actor_8:SetPhysicalActorType(1)
	Actor_8:SetPhysicalShape(5)
	Actor_8.ExtraInfo.Name = ""
	Actor_8.ExtraInfo.NameColorR = 0
	Actor_8.ExtraInfo.NameColorG = 0
	Actor_8.ExtraInfo.NameColorB = 0
	Actor_8H = ActorHandler(Actor_8)
	environment:AddActorObject(Actor_8H)

	Actor_9 = ActorObjectInfo(9)
	Actor_9:SetRenderType(1)
	Actor_9.DisplayDesc.ModelId = 1701667139
	Actor_9.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_6.osgb"
	Actor_9.DisplayDesc.Outfit = ""
	Actor_9.DisplayDesc.Weapon = ""
	Actor_9.DisplayDesc.Mode = ""
	Actor_9.DisplayDesc.UseLight = false
	Actor_9.DisplayDesc.CastShadow = true
	Actor_9.DisplayDesc.ColorR = 1
	Actor_9.DisplayDesc.ColorG = 1
	Actor_9.DisplayDesc.ColorB = 1
	Actor_9.DisplayDesc.ColorA = 1
	Actor_9:SetModelState(1)
	Actor_9.PhysicDesc.Pos.X = 439
	Actor_9.PhysicDesc.Pos.Y = 10
	Actor_9.PhysicDesc.Pos.Z = 462
	Actor_9.PhysicDesc.Pos.Rotation = -90
	Actor_9.PhysicDesc.Density = 2.10195e-044
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 0
	Actor_9.PhysicDesc.SizeY = 0
	Actor_9.PhysicDesc.SizeZ = 0
	Actor_9.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_6.phy"
	Actor_9:SetPhysicalActorType(1)
	Actor_9:SetPhysicalShape(5)
	Actor_9.ExtraInfo.Name = ""
	Actor_9.ExtraInfo.NameColorR = 0
	Actor_9.ExtraInfo.NameColorG = 0
	Actor_9.ExtraInfo.NameColorB = 0
	Actor_9H = ActorHandler(Actor_9)
	environment:AddActorObject(Actor_9H)

	Actor_10 = ActorObjectInfo(10)
	Actor_10:SetRenderType(1)
	Actor_10.DisplayDesc.ModelId = 437616960
	Actor_10.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_7.osgb"
	Actor_10.DisplayDesc.Outfit = ""
	Actor_10.DisplayDesc.Weapon = ""
	Actor_10.DisplayDesc.Mode = ""
	Actor_10.DisplayDesc.UseLight = false
	Actor_10.DisplayDesc.CastShadow = true
	Actor_10.DisplayDesc.ColorR = 1
	Actor_10.DisplayDesc.ColorG = 1
	Actor_10.DisplayDesc.ColorB = 1
	Actor_10.DisplayDesc.ColorA = 1
	Actor_10:SetModelState(1)
	Actor_10.PhysicDesc.Pos.X = 439.125
	Actor_10.PhysicDesc.Pos.Y = 10
	Actor_10.PhysicDesc.Pos.Z = 457
	Actor_10.PhysicDesc.Pos.Rotation = 0
	Actor_10.PhysicDesc.Density = 0
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 0
	Actor_10.PhysicDesc.SizeY = 0
	Actor_10.PhysicDesc.SizeZ = 0
	Actor_10.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_7.phy"
	Actor_10:SetPhysicalActorType(1)
	Actor_10:SetPhysicalShape(5)
	Actor_10.ExtraInfo.Name = ""
	Actor_10.ExtraInfo.NameColorR = 0
	Actor_10.ExtraInfo.NameColorG = 0
	Actor_10.ExtraInfo.NameColorB = 0
	Actor_10H = ActorHandler(Actor_10)
	environment:AddActorObject(Actor_10H)

	Actor_11 = ActorObjectInfo(11)
	Actor_11:SetRenderType(1)
	Actor_11.DisplayDesc.ModelId = 826
	Actor_11.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_5.osgb"
	Actor_11.DisplayDesc.Outfit = ""
	Actor_11.DisplayDesc.Weapon = ""
	Actor_11.DisplayDesc.Mode = ""
	Actor_11.DisplayDesc.UseLight = false
	Actor_11.DisplayDesc.CastShadow = true
	Actor_11.DisplayDesc.ColorR = 1
	Actor_11.DisplayDesc.ColorG = 1
	Actor_11.DisplayDesc.ColorB = 1
	Actor_11.DisplayDesc.ColorA = 1
	Actor_11:SetModelState(1)
	Actor_11.PhysicDesc.Pos.X = 457
	Actor_11.PhysicDesc.Pos.Y = 10
	Actor_11.PhysicDesc.Pos.Z = 439
	Actor_11.PhysicDesc.Pos.Rotation = 180
	Actor_11.PhysicDesc.Density = 0
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 0
	Actor_11.PhysicDesc.SizeY = 0
	Actor_11.PhysicDesc.SizeZ = 0
	Actor_11.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_5.phy"
	Actor_11:SetPhysicalActorType(1)
	Actor_11:SetPhysicalShape(5)
	Actor_11.ExtraInfo.Name = ""
	Actor_11.ExtraInfo.NameColorR = 2.10195e-044
	Actor_11.ExtraInfo.NameColorG = 0
	Actor_11.ExtraInfo.NameColorB = 0
	Actor_11H = ActorHandler(Actor_11)
	environment:AddActorObject(Actor_11H)

	Actor_12 = ActorObjectInfo(12)
	Actor_12:SetRenderType(1)
	Actor_12.DisplayDesc.ModelId = 423430000
	Actor_12.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_6.osgb"
	Actor_12.DisplayDesc.Outfit = ""
	Actor_12.DisplayDesc.Weapon = ""
	Actor_12.DisplayDesc.Mode = ""
	Actor_12.DisplayDesc.UseLight = false
	Actor_12.DisplayDesc.CastShadow = false
	Actor_12.DisplayDesc.ColorR = 2.10195e-044
	Actor_12.DisplayDesc.ColorG = 2.64883e-024
	Actor_12.DisplayDesc.ColorB = 1.7958e-031
	Actor_12.DisplayDesc.ColorA = 1
	Actor_12:SetModelState(1)
	Actor_12.PhysicDesc.Pos.X = 457
	Actor_12.PhysicDesc.Pos.Y = 10
	Actor_12.PhysicDesc.Pos.Z = 439
	Actor_12.PhysicDesc.Pos.Rotation = 180
	Actor_12.PhysicDesc.Density = 0
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 0
	Actor_12.PhysicDesc.SizeY = 0
	Actor_12.PhysicDesc.SizeZ = 0
	Actor_12.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_6.phy"
	Actor_12:SetPhysicalActorType(1)
	Actor_12:SetPhysicalShape(5)
	Actor_12.ExtraInfo.Name = ""
	Actor_12.ExtraInfo.NameColorR = 0
	Actor_12.ExtraInfo.NameColorG = 0
	Actor_12.ExtraInfo.NameColorB = 0
	Actor_12H = ActorHandler(Actor_12)
	environment:AddActorObject(Actor_12H)

	Actor_13 = ActorObjectInfo(13)
	Actor_13:SetRenderType(1)
	Actor_13.DisplayDesc.ModelId = 423430000
	Actor_13.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_7.osgb"
	Actor_13.DisplayDesc.Outfit = ""
	Actor_13.DisplayDesc.Weapon = ""
	Actor_13.DisplayDesc.Mode = ""
	Actor_13.DisplayDesc.UseLight = false
	Actor_13.DisplayDesc.CastShadow = false
	Actor_13.DisplayDesc.ColorR = 7.00649e-045
	Actor_13.DisplayDesc.ColorG = 7.43888e-023
	Actor_13.DisplayDesc.ColorB = 1
	Actor_13.DisplayDesc.ColorA = 3.09797e-023
	Actor_13:SetModelState(1)
	Actor_13.PhysicDesc.Pos.X = 457
	Actor_13.PhysicDesc.Pos.Y = 10
	Actor_13.PhysicDesc.Pos.Z = 439
	Actor_13.PhysicDesc.Pos.Rotation = 180
	Actor_13.PhysicDesc.Density = 0
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 0
	Actor_13.PhysicDesc.SizeY = 2.8026e-045
	Actor_13.PhysicDesc.SizeZ = 6.74035e-024
	Actor_13.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_7.phy"
	Actor_13:SetPhysicalActorType(1)
	Actor_13:SetPhysicalShape(5)
	Actor_13.ExtraInfo.Name = ""
	Actor_13.ExtraInfo.NameColorR = 0
	Actor_13.ExtraInfo.NameColorG = 8.40779e-045
	Actor_13.ExtraInfo.NameColorB = 1.05179e-030
	Actor_13H = ActorHandler(Actor_13)
	environment:AddActorObject(Actor_13H)

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(1)
	Actor_14.DisplayDesc.ModelId = 7
	Actor_14.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_8.osgb"
	Actor_14.DisplayDesc.Outfit = ""
	Actor_14.DisplayDesc.Weapon = ""
	Actor_14.DisplayDesc.Mode = ""
	Actor_14.DisplayDesc.UseLight = false
	Actor_14.DisplayDesc.CastShadow = true
	Actor_14.DisplayDesc.ColorR = 1
	Actor_14.DisplayDesc.ColorG = 9.80909e-045
	Actor_14.DisplayDesc.ColorB = 1
	Actor_14.DisplayDesc.ColorA = 3.09315e-023
	Actor_14:SetModelState(1)
	Actor_14.PhysicDesc.Pos.X = 447
	Actor_14.PhysicDesc.Pos.Y = 10
	Actor_14.PhysicDesc.Pos.Z = 439
	Actor_14.PhysicDesc.Pos.Rotation = 90
	Actor_14.PhysicDesc.Density = 9.80909e-045
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 3.07059e-031
	Actor_14.PhysicDesc.SizeY = 1.71105e-039
	Actor_14.PhysicDesc.SizeZ = 5.60519e-045
	Actor_14.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_8.phy"
	Actor_14:SetPhysicalActorType(1)
	Actor_14:SetPhysicalShape(5)
	Actor_14.ExtraInfo.Name = ""
	Actor_14.ExtraInfo.NameColorR = 7.9881e-041
	Actor_14.ExtraInfo.NameColorG = 8.40779e-045
	Actor_14.ExtraInfo.NameColorB = 2.8026e-045
	Actor_14H = ActorHandler(Actor_14)
	environment:AddActorObject(Actor_14H)

	Actor_15 = ActorObjectInfo(15)
	Actor_15:SetRenderType(1)
	Actor_15.DisplayDesc.ModelId = 2
	Actor_15.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_9.osgb"
	Actor_15.DisplayDesc.Outfit = ""
	Actor_15.DisplayDesc.Weapon = ""
	Actor_15.DisplayDesc.Mode = ""
	Actor_15.DisplayDesc.UseLight = false
	Actor_15.DisplayDesc.CastShadow = true
	Actor_15.DisplayDesc.ColorR = 1.0546875
	Actor_15.DisplayDesc.ColorG = 2.8026e-045
	Actor_15.DisplayDesc.ColorB = 1
	Actor_15.DisplayDesc.ColorA = 7.76467e-031
	Actor_15:SetModelState(1)
	Actor_15.PhysicDesc.Pos.X = 457.125
	Actor_15.PhysicDesc.Pos.Y = 10
	Actor_15.PhysicDesc.Pos.Z = 434
	Actor_15.PhysicDesc.Pos.Rotation = 90
	Actor_15.PhysicDesc.Density = 5.60519e-045
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 1.63994e-023
	Actor_15.PhysicDesc.SizeY = 0
	Actor_15.PhysicDesc.SizeZ = 9.80909e-045
	Actor_15.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_9.phy"
	Actor_15:SetPhysicalActorType(1)
	Actor_15:SetPhysicalShape(5)
	Actor_15.ExtraInfo.Name = ""
	Actor_15.ExtraInfo.NameColorR = 0
	Actor_15.ExtraInfo.NameColorG = 5.60519e-045
	Actor_15.ExtraInfo.NameColorB = 0
	Actor_15H = ActorHandler(Actor_15)
	environment:AddActorObject(Actor_15H)

	Actor_16 = ActorObjectInfo(16)
	Actor_16:SetRenderType(1)
	Actor_16.DisplayDesc.ModelId = 2
	Actor_16.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_10.osgb"
	Actor_16.DisplayDesc.Outfit = ""
	Actor_16.DisplayDesc.Weapon = ""
	Actor_16.DisplayDesc.Mode = ""
	Actor_16.DisplayDesc.UseLight = false
	Actor_16.DisplayDesc.CastShadow = true
	Actor_16.DisplayDesc.ColorR = 2.375
	Actor_16.DisplayDesc.ColorG = 2.8026e-045
	Actor_16.DisplayDesc.ColorB = 6.30476e-031
	Actor_16.DisplayDesc.ColorA = 1
	Actor_16:SetModelState(1)
	Actor_16.PhysicDesc.Pos.X = 449
	Actor_16.PhysicDesc.Pos.Y = 2.5
	Actor_16.PhysicDesc.Pos.Z = 460.125
	Actor_16.PhysicDesc.Pos.Rotation = 0
	Actor_16.PhysicDesc.Density = 2.8026e-045
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 0
	Actor_16.PhysicDesc.SizeY = 0
	Actor_16.PhysicDesc.SizeZ = 0
	Actor_16.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_10.phy"
	Actor_16:SetPhysicalActorType(1)
	Actor_16:SetPhysicalShape(5)
	Actor_16.ExtraInfo.Name = ""
	Actor_16.ExtraInfo.NameColorR = 2.375
	Actor_16.ExtraInfo.NameColorG = 2.8026e-045
	Actor_16.ExtraInfo.NameColorB = 6.2868e-031
	Actor_16H = ActorHandler(Actor_16)
	environment:AddActorObject(Actor_16H)

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(1)
	Actor_17.DisplayDesc.ModelId = 16810076
	Actor_17.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_10.osgb"
	Actor_17.DisplayDesc.Outfit = ""
	Actor_17.DisplayDesc.Weapon = ""
	Actor_17.DisplayDesc.Mode = ""
	Actor_17.DisplayDesc.UseLight = false
	Actor_17.DisplayDesc.CastShadow = true
	Actor_17.DisplayDesc.ColorR = -5.87562e-034
	Actor_17.DisplayDesc.ColorG = 9.66896e-044
	Actor_17.DisplayDesc.ColorB = 1.80228e-038
	Actor_17.DisplayDesc.ColorA = 4.61882e-041
	Actor_17:SetModelState(1)
	Actor_17.PhysicDesc.Pos.X = 437
	Actor_17.PhysicDesc.Pos.Y = 2.5
	Actor_17.PhysicDesc.Pos.Z = 447
	Actor_17.PhysicDesc.Pos.Rotation = 90
	Actor_17.PhysicDesc.Density = 2.3602e-038
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 6.47451e-039
	Actor_17.PhysicDesc.SizeY = 5.51289e-040
	Actor_17.PhysicDesc.SizeZ = 4.71121e-038
	Actor_17.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_10.phy"
	Actor_17:SetPhysicalActorType(1)
	Actor_17:SetPhysicalShape(5)
	Actor_17.ExtraInfo.Name = ""
	Actor_17.ExtraInfo.NameColorR = 6.19986e-040
	Actor_17.ExtraInfo.NameColorG = 1.78621e-038
	Actor_17.ExtraInfo.NameColorB = 1.78851e-038
	Actor_17H = ActorHandler(Actor_17)
	environment:AddActorObject(Actor_17H)

	Actor_18 = ActorObjectInfo(18)
	Actor_18:SetRenderType(1)
	Actor_18.DisplayDesc.ModelId = 0
	Actor_18.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_10.osgb"
	Actor_18.DisplayDesc.Outfit = ""
	Actor_18.DisplayDesc.Weapon = ""
	Actor_18.DisplayDesc.Mode = ""
	Actor_18.DisplayDesc.UseLight = false
	Actor_18.DisplayDesc.CastShadow = false
	Actor_18.DisplayDesc.ColorR = 1
	Actor_18.DisplayDesc.ColorG = 2.10195e-044
	Actor_18.DisplayDesc.ColorB = 1
	Actor_18.DisplayDesc.ColorA = 1
	Actor_18:SetModelState(1)
	Actor_18.PhysicDesc.Pos.X = 459
	Actor_18.PhysicDesc.Pos.Y = 2.5
	Actor_18.PhysicDesc.Pos.Z = 449
	Actor_18.PhysicDesc.Pos.Rotation = -90
	Actor_18.PhysicDesc.Density = 4.57363e-038
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 0
	Actor_18.PhysicDesc.SizeY = 4.2039e-045
	Actor_18.PhysicDesc.SizeZ = 2.75572e-040
	Actor_18.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_10.phy"
	Actor_18:SetPhysicalActorType(1)
	Actor_18:SetPhysicalShape(5)
	Actor_18.ExtraInfo.Name = ""
	Actor_18.ExtraInfo.NameColorR = 7.69998e-031
	Actor_18.ExtraInfo.NameColorG = 7.7002e-031
	Actor_18.ExtraInfo.NameColorB = 7.69981e-031
	Actor_18H = ActorHandler(Actor_18)
	environment:AddActorObject(Actor_18H)

	Actor_19 = ActorObjectInfo(19)
	Actor_19:SetRenderType(1)
	Actor_19.DisplayDesc.ModelId = 410484320
	Actor_19.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_2.osgb"
	Actor_19.DisplayDesc.Outfit = ""
	Actor_19.DisplayDesc.Weapon = ""
	Actor_19.DisplayDesc.Mode = ""
	Actor_19.DisplayDesc.UseLight = false
	Actor_19.DisplayDesc.CastShadow = false
	Actor_19.DisplayDesc.ColorR = 2.36384e-023
	Actor_19.DisplayDesc.ColorG = 1
	Actor_19.DisplayDesc.ColorB = 3.11113e-024
	Actor_19.DisplayDesc.ColorA = 1.46863e-023
	Actor_19:SetModelState(1)
	Actor_19.PhysicDesc.Pos.X = 467.5
	Actor_19.PhysicDesc.Pos.Y = 3.125
	Actor_19.PhysicDesc.Pos.Z = 467.5
	Actor_19.PhysicDesc.Pos.Rotation = -90
	Actor_19.PhysicDesc.Density = 9.9929e-024
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = 1.83712e-031
	Actor_19.PhysicDesc.SizeY = 4.28688e-024
	Actor_19.PhysicDesc.SizeZ = 0
	Actor_19.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_2.phy"
	Actor_19:SetPhysicalActorType(1)
	Actor_19:SetPhysicalShape(5)
	Actor_19.ExtraInfo.Name = ""
	Actor_19.ExtraInfo.NameColorR = 0
	Actor_19.ExtraInfo.NameColorG = 2.4763e-023
	Actor_19.ExtraInfo.NameColorB = 7.64466e-031
	Actor_19H = ActorHandler(Actor_19)
	environment:AddActorObject(Actor_19H)

	Actor_20 = ActorObjectInfo(20)
	Actor_20:SetRenderType(1)
	Actor_20.DisplayDesc.ModelId = 417452896
	Actor_20.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_2.osgb"
	Actor_20.DisplayDesc.Outfit = ""
	Actor_20.DisplayDesc.Weapon = ""
	Actor_20.DisplayDesc.Mode = ""
	Actor_20.DisplayDesc.UseLight = false
	Actor_20.DisplayDesc.CastShadow = false
	Actor_20.DisplayDesc.ColorR = 1.79416e-031
	Actor_20.DisplayDesc.ColorG = 1
	Actor_20.DisplayDesc.ColorB = 1
	Actor_20.DisplayDesc.ColorA = 1
	Actor_20:SetModelState(1)
	Actor_20.PhysicDesc.Pos.X = 428.5
	Actor_20.PhysicDesc.Pos.Y = 3.125
	Actor_20.PhysicDesc.Pos.Z = 467.5
	Actor_20.PhysicDesc.Pos.Rotation = 180
	Actor_20.PhysicDesc.Density = 4.86526e-034
	Actor_20.PhysicDesc.Collidable = true
	Actor_20.PhysicDesc.SizeX = 0
	Actor_20.PhysicDesc.SizeY = 5.36151e-024
	Actor_20.PhysicDesc.SizeZ = 0
	Actor_20.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_2.phy"
	Actor_20:SetPhysicalActorType(1)
	Actor_20:SetPhysicalShape(5)
	Actor_20.ExtraInfo.Name = ""
	Actor_20.ExtraInfo.NameColorR = 7.03098e-031
	Actor_20.ExtraInfo.NameColorG = 4.27839e-024
	Actor_20.ExtraInfo.NameColorB = 2.64049e-023
	Actor_20H = ActorHandler(Actor_20)
	environment:AddActorObject(Actor_20H)

	Actor_21 = ActorObjectInfo(21)
	Actor_21:SetRenderType(1)
	Actor_21.DisplayDesc.ModelId = 16810076
	Actor_21.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_2.osgb"
	Actor_21.DisplayDesc.Outfit = ""
	Actor_21.DisplayDesc.Weapon = ""
	Actor_21.DisplayDesc.Mode = ""
	Actor_21.DisplayDesc.UseLight = false
	Actor_21.DisplayDesc.CastShadow = true
	Actor_21.DisplayDesc.ColorR = -6.20664e-034
	Actor_21.DisplayDesc.ColorG = 1.21692e-039
	Actor_21.DisplayDesc.ColorB = 1.80228e-038
	Actor_21.DisplayDesc.ColorA = 4.61882e-041
	Actor_21:SetModelState(1)
	Actor_21.PhysicDesc.Pos.X = 428.5
	Actor_21.PhysicDesc.Pos.Y = 3.125
	Actor_21.PhysicDesc.Pos.Z = 428.5
	Actor_21.PhysicDesc.Pos.Rotation = 90
	Actor_21.PhysicDesc.Density = 2.3602e-038
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 6.47451e-039
	Actor_21.PhysicDesc.SizeY = 1.35485e-039
	Actor_21.PhysicDesc.SizeZ = 4.71121e-038
	Actor_21.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_2.phy"
	Actor_21:SetPhysicalActorType(1)
	Actor_21:SetPhysicalShape(5)
	Actor_21.ExtraInfo.Name = ""
	Actor_21.ExtraInfo.NameColorR = 1.37763e-039
	Actor_21.ExtraInfo.NameColorG = 1.78621e-038
	Actor_21.ExtraInfo.NameColorB = 1.78851e-038
	Actor_21H = ActorHandler(Actor_21)
	environment:AddActorObject(Actor_21H)

	Actor_22 = ActorObjectInfo(22)
	Actor_22:SetRenderType(1)
	Actor_22.DisplayDesc.ModelId = 3
	Actor_22.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_2.osgb"
	Actor_22.DisplayDesc.Outfit = ""
	Actor_22.DisplayDesc.Weapon = ""
	Actor_22.DisplayDesc.Mode = ""
	Actor_22.DisplayDesc.UseLight = false
	Actor_22.DisplayDesc.CastShadow = false
	Actor_22.DisplayDesc.ColorR = 3.23438
	Actor_22.DisplayDesc.ColorG = 4.2039e-045
	Actor_22.DisplayDesc.ColorB = 1.24375
	Actor_22.DisplayDesc.ColorA = 7.66506e-031
	Actor_22:SetModelState(1)
	Actor_22.PhysicDesc.Pos.X = 467.5
	Actor_22.PhysicDesc.Pos.Y = 3.125
	Actor_22.PhysicDesc.Pos.Z = 428.5
	Actor_22.PhysicDesc.Pos.Rotation = 0
	Actor_22.PhysicDesc.Density = 1.4013e-045
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 1.94492e-031
	Actor_22.PhysicDesc.SizeY = 0
	Actor_22.PhysicDesc.SizeZ = 5.60519e-045
	Actor_22.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_2.phy"
	Actor_22:SetPhysicalActorType(1)
	Actor_22:SetPhysicalShape(5)
	Actor_22.ExtraInfo.Name = ""
	Actor_22.ExtraInfo.NameColorR = 3.20313
	Actor_22.ExtraInfo.NameColorG = 4.2039e-045
	Actor_22.ExtraInfo.NameColorB = 0.59375
	Actor_22H = ActorHandler(Actor_22)
	environment:AddActorObject(Actor_22H)

	Actor_23 = ActorObjectInfo(23)
	Actor_23:SetRenderType(1)
	Actor_23.DisplayDesc.ModelId = 0
	Actor_23.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_11.osgb"
	Actor_23.DisplayDesc.Outfit = ""
	Actor_23.DisplayDesc.Weapon = ""
	Actor_23.DisplayDesc.Mode = ""
	Actor_23.DisplayDesc.UseLight = false
	Actor_23.DisplayDesc.CastShadow = false
	Actor_23.DisplayDesc.ColorR = 1.0842e-019
	Actor_23.DisplayDesc.ColorG = 3.04923e-042
	Actor_23.DisplayDesc.ColorB = 1
	Actor_23.DisplayDesc.ColorA = 2.10195e-044
	Actor_23:SetModelState(1)
	Actor_23.PhysicDesc.Pos.X = 428.5
	Actor_23.PhysicDesc.Pos.Y = 3.125
	Actor_23.PhysicDesc.Pos.Z = 428.5
	Actor_23.PhysicDesc.Pos.Rotation = 90
	Actor_23.PhysicDesc.Density = 2.0204e-039
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 4.57354e-038
	Actor_23.PhysicDesc.SizeY = 7.67632e-031
	Actor_23.PhysicDesc.SizeZ = 0
	Actor_23.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_11.phy"
	Actor_23:SetPhysicalActorType(1)
	Actor_23:SetPhysicalShape(5)
	Actor_23.ExtraInfo.Name = ""
	Actor_23.ExtraInfo.NameColorR = 2.55799e-035
	Actor_23.ExtraInfo.NameColorG = 4.57361e-038
	Actor_23.ExtraInfo.NameColorB = 4.48984e+021
	Actor_23H = ActorHandler(Actor_23)
	environment:AddActorObject(Actor_23H)

	Actor_24 = ActorObjectInfo(24)
	Actor_24:SetRenderType(1)
	Actor_24.DisplayDesc.ModelId = 1701667139
	Actor_24.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_11.osgb"
	Actor_24.DisplayDesc.Outfit = ""
	Actor_24.DisplayDesc.Weapon = ""
	Actor_24.DisplayDesc.Mode = ""
	Actor_24.DisplayDesc.UseLight = false
	Actor_24.DisplayDesc.CastShadow = false
	Actor_24.DisplayDesc.ColorR = 1
	Actor_24.DisplayDesc.ColorG = 1
	Actor_24.DisplayDesc.ColorB = 1
	Actor_24.DisplayDesc.ColorA = 1
	Actor_24:SetModelState(1)
	Actor_24.PhysicDesc.Pos.X = 467.5
	Actor_24.PhysicDesc.Pos.Y = 3.125
	Actor_24.PhysicDesc.Pos.Z = 428.5
	Actor_24.PhysicDesc.Pos.Rotation = 0
	Actor_24.PhysicDesc.Density = 0
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 0
	Actor_24.PhysicDesc.SizeY = 1.4013e-045
	Actor_24.PhysicDesc.SizeZ = 1.1755e-038
	Actor_24.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_11.phy"
	Actor_24:SetPhysicalActorType(1)
	Actor_24:SetPhysicalShape(5)
	Actor_24.ExtraInfo.Name = ""
	Actor_24.ExtraInfo.NameColorR = 0
	Actor_24.ExtraInfo.NameColorG = 7.76989e-031
	Actor_24.ExtraInfo.NameColorB = 7.76989e-031
	Actor_24H = ActorHandler(Actor_24)
	environment:AddActorObject(Actor_24H)

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(1)
	Actor_25.DisplayDesc.ModelId = 226152000
	Actor_25.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_11.osgb"
	Actor_25.DisplayDesc.Outfit = ""
	Actor_25.DisplayDesc.Weapon = ""
	Actor_25.DisplayDesc.Mode = ""
	Actor_25.DisplayDesc.UseLight = false
	Actor_25.DisplayDesc.CastShadow = false
	Actor_25.DisplayDesc.ColorR = 2.5579e-035
	Actor_25.DisplayDesc.ColorG = 4.57354e-038
	Actor_25.DisplayDesc.ColorB = 7.69008e-031
	Actor_25.DisplayDesc.ColorA = 1
	Actor_25:SetModelState(1)
	Actor_25.PhysicDesc.Pos.X = 428.5
	Actor_25.PhysicDesc.Pos.Y = 3.125
	Actor_25.PhysicDesc.Pos.Z = 467.5
	Actor_25.PhysicDesc.Pos.Rotation = 180
	Actor_25.PhysicDesc.Density = 0
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 0
	Actor_25.PhysicDesc.SizeY = 0
	Actor_25.PhysicDesc.SizeZ = 0
	Actor_25.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_11.phy"
	Actor_25:SetPhysicalActorType(1)
	Actor_25:SetPhysicalShape(5)
	Actor_25.ExtraInfo.Name = ""
	Actor_25.ExtraInfo.NameColorR = 0
	Actor_25.ExtraInfo.NameColorG = 0
	Actor_25.ExtraInfo.NameColorB = 2.10195e-044
	Actor_25H = ActorHandler(Actor_25)
	environment:AddActorObject(Actor_25H)

	Actor_26 = ActorObjectInfo(26)
	Actor_26:SetRenderType(1)
	Actor_26.DisplayDesc.ModelId = 226071576
	Actor_26.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_11.osgb"
	Actor_26.DisplayDesc.Outfit = ""
	Actor_26.DisplayDesc.Weapon = ""
	Actor_26.DisplayDesc.Mode = ""
	Actor_26.DisplayDesc.UseLight = false
	Actor_26.DisplayDesc.CastShadow = false
	Actor_26.DisplayDesc.ColorR = 2.55792e-035
	Actor_26.DisplayDesc.ColorG = 4.57357e-038
	Actor_26.DisplayDesc.ColorB = 4.57357e-038
	Actor_26.DisplayDesc.ColorA = 7.00622e+022
	Actor_26:SetModelState(1)
	Actor_26.PhysicDesc.Pos.X = 467.5
	Actor_26.PhysicDesc.Pos.Y = 3.125
	Actor_26.PhysicDesc.Pos.Z = 467.5
	Actor_26.PhysicDesc.Pos.Rotation = -90
	Actor_26.PhysicDesc.Density = 0
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 7.69087e-031
	Actor_26.PhysicDesc.SizeY = 7.69078e-031
	Actor_26.PhysicDesc.SizeZ = 1.01021e-039
	Actor_26.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_11.phy"
	Actor_26:SetPhysicalActorType(1)
	Actor_26:SetPhysicalShape(5)
	Actor_26.ExtraInfo.Name = ""
	Actor_26.ExtraInfo.NameColorR = 0
	Actor_26.ExtraInfo.NameColorG = 0
	Actor_26.ExtraInfo.NameColorB = 0
	Actor_26H = ActorHandler(Actor_26)
	environment:AddActorObject(Actor_26H)

	Actor_27 = ActorObjectInfo(27)
	Actor_27:SetRenderType(1)
	Actor_27.DisplayDesc.ModelId = 0
	Actor_27.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_12.osgb"
	Actor_27.DisplayDesc.Outfit = ""
	Actor_27.DisplayDesc.Weapon = ""
	Actor_27.DisplayDesc.Mode = ""
	Actor_27.DisplayDesc.UseLight = false
	Actor_27.DisplayDesc.CastShadow = false
	Actor_27.DisplayDesc.ColorR = 1
	Actor_27.DisplayDesc.ColorG = 1
	Actor_27.DisplayDesc.ColorB = 1
	Actor_27.DisplayDesc.ColorA = 1
	Actor_27:SetModelState(1)
	Actor_27.PhysicDesc.Pos.X = 428.5
	Actor_27.PhysicDesc.Pos.Y = 3.125
	Actor_27.PhysicDesc.Pos.Z = 428.5
	Actor_27.PhysicDesc.Pos.Rotation = 90
	Actor_27.PhysicDesc.Density = 2.75572e-040
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 4.57362e-038
	Actor_27.PhysicDesc.SizeY = 4.57362e-038
	Actor_27.PhysicDesc.SizeZ = 0
	Actor_27.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_12.phy"
	Actor_27:SetPhysicalActorType(1)
	Actor_27:SetPhysicalShape(5)
	Actor_27.ExtraInfo.Name = ""
	Actor_27.ExtraInfo.NameColorR = 2.55794e-035
	Actor_27.ExtraInfo.NameColorG = 4.57359e-038
	Actor_27.ExtraInfo.NameColorB = 4.57359e-038
	Actor_27H = ActorHandler(Actor_27)
	environment:AddActorObject(Actor_27H)

	Actor_28 = ActorObjectInfo(28)
	Actor_28:SetRenderType(1)
	Actor_28.DisplayDesc.ModelId = 868421
	Actor_28.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_12.osgb"
	Actor_28.DisplayDesc.Outfit = ""
	Actor_28.DisplayDesc.Weapon = ""
	Actor_28.DisplayDesc.Mode = ""
	Actor_28.DisplayDesc.UseLight = false
	Actor_28.DisplayDesc.CastShadow = true
	Actor_28.DisplayDesc.ColorR = 1.37763e-039
	Actor_28.DisplayDesc.ColorG = 1.78621e-038
	Actor_28.DisplayDesc.ColorB = 1.78851e-038
	Actor_28.DisplayDesc.ColorA = -3.90736e-035
	Actor_28:SetModelState(1)
	Actor_28.PhysicDesc.Pos.X = 467.5
	Actor_28.PhysicDesc.Pos.Y = 3.125
	Actor_28.PhysicDesc.Pos.Z = 467.5
	Actor_28.PhysicDesc.Pos.Rotation = -90
	Actor_28.PhysicDesc.Density = 1.80228e-038
	Actor_28.PhysicDesc.Collidable = true
	Actor_28.PhysicDesc.SizeX = 4.71121e-038
	Actor_28.PhysicDesc.SizeY = 1.37763e-039
	Actor_28.PhysicDesc.SizeZ = 1.80458e-038
	Actor_28.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_12.phy"
	Actor_28:SetPhysicalActorType(1)
	Actor_28:SetPhysicalShape(5)
	Actor_28.ExtraInfo.Name = ""
	Actor_28.ExtraInfo.NameColorR = 1.5613e-039
	Actor_28.ExtraInfo.NameColorG = 1.5613e-039
	Actor_28.ExtraInfo.NameColorB = 1.77014e-038
	Actor_28H = ActorHandler(Actor_28)
	environment:AddActorObject(Actor_28H)

	Actor_29 = ActorObjectInfo(29)
	Actor_29:SetRenderType(1)
	Actor_29.DisplayDesc.ModelId = 311489
	Actor_29.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_12.osgb"
	Actor_29.DisplayDesc.Outfit = ""
	Actor_29.DisplayDesc.Weapon = ""
	Actor_29.DisplayDesc.Mode = ""
	Actor_29.DisplayDesc.UseLight = false
	Actor_29.DisplayDesc.CastShadow = true
	Actor_29.DisplayDesc.ColorR = 4.61882e-041
	Actor_29.DisplayDesc.ColorG = 4.71121e-038
	Actor_29.DisplayDesc.ColorB = 2.50261e-039
	Actor_29.DisplayDesc.ColorA = 1.78621e-038
	Actor_29:SetModelState(1)
	Actor_29.PhysicDesc.Pos.X = 428.5
	Actor_29.PhysicDesc.Pos.Y = 3.125
	Actor_29.PhysicDesc.Pos.Z = 467.5
	Actor_29.PhysicDesc.Pos.Rotation = 180
	Actor_29.PhysicDesc.Density = -6.02609e-034
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 1.80228e-038
	Actor_29.PhysicDesc.SizeY = 4.61882e-041
	Actor_29.PhysicDesc.SizeZ = 4.71121e-038
	Actor_29.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_12.phy"
	Actor_29:SetPhysicalActorType(1)
	Actor_29:SetPhysicalShape(5)
	Actor_29.ExtraInfo.Name = ""
	Actor_29.ExtraInfo.NameColorR = 2.66341e-039
	Actor_29.ExtraInfo.NameColorG = 2.3602e-038
	Actor_29.ExtraInfo.NameColorB = 2.64037e-039
	Actor_29H = ActorHandler(Actor_29)
	environment:AddActorObject(Actor_29H)

	Actor_30 = ActorObjectInfo(30)
	Actor_30:SetRenderType(1)
	Actor_30.DisplayDesc.ModelId = 7
	Actor_30.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_12.osgb"
	Actor_30.DisplayDesc.Outfit = ""
	Actor_30.DisplayDesc.Weapon = ""
	Actor_30.DisplayDesc.Mode = ""
	Actor_30.DisplayDesc.UseLight = false
	Actor_30.DisplayDesc.CastShadow = true
	Actor_30.DisplayDesc.ColorR = 1
	Actor_30.DisplayDesc.ColorG = 9.80909e-045
	Actor_30.DisplayDesc.ColorB = 174.388
	Actor_30.DisplayDesc.ColorA = 4.37421e-034
	Actor_30:SetModelState(1)
	Actor_30.PhysicDesc.Pos.X = 467.5
	Actor_30.PhysicDesc.Pos.Y = 3.125
	Actor_30.PhysicDesc.Pos.Z = 428.5
	Actor_30.PhysicDesc.Pos.Rotation = 0
	Actor_30.PhysicDesc.Density = 9.80909e-045
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 2.13258e-024
	Actor_30.PhysicDesc.SizeY = 5.96814e-039
	Actor_30.PhysicDesc.SizeZ = 5.60519e-045
	Actor_30.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_12.phy"
	Actor_30:SetPhysicalActorType(1)
	Actor_30:SetPhysicalShape(5)
	Actor_30.ExtraInfo.Name = ""
	Actor_30.ExtraInfo.NameColorR = 1.875
	Actor_30.ExtraInfo.NameColorG = 9.80909e-045
	Actor_30.ExtraInfo.NameColorB = 1.78637e+025
	Actor_30H = ActorHandler(Actor_30)
	environment:AddActorObject(Actor_30H)

	Actor_31 = ActorObjectInfo(31)
	Actor_31:SetRenderType(1)
	Actor_31.DisplayDesc.ModelId = 423715696
	Actor_31.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_5.osgb"
	Actor_31.DisplayDesc.Outfit = ""
	Actor_31.DisplayDesc.Weapon = ""
	Actor_31.DisplayDesc.Mode = ""
	Actor_31.DisplayDesc.UseLight = false
	Actor_31.DisplayDesc.CastShadow = false
	Actor_31.DisplayDesc.ColorR = 2.1964e-023
	Actor_31.DisplayDesc.ColorG = 2.58094e-024
	Actor_31.DisplayDesc.ColorB = 1.875
	Actor_31.DisplayDesc.ColorA = 9.80909e-045
	Actor_31:SetModelState(1)
	Actor_31.PhysicDesc.Pos.X = 439.125
	Actor_31.PhysicDesc.Pos.Y = 10
	Actor_31.PhysicDesc.Pos.Z = 457
	Actor_31.PhysicDesc.Pos.Rotation = 0
	Actor_31.PhysicDesc.Density = 7.64233e-031
	Actor_31.PhysicDesc.Collidable = true
	Actor_31.PhysicDesc.SizeX = 9.80909e-045
	Actor_31.PhysicDesc.SizeY = 1.84807e-019
	Actor_31.PhysicDesc.SizeZ = 1.76818e-023
	Actor_31.PhysicDesc.Filename = "Worlds/Lba2Original/Models/ILOTCX_OBJ_5.phy"
	Actor_31:SetPhysicalActorType(1)
	Actor_31:SetPhysicalShape(5)
	Actor_31.ExtraInfo.Name = ""
	Actor_31.ExtraInfo.NameColorR = 0
	Actor_31.ExtraInfo.NameColorG = 2.42525e-023
	Actor_31.ExtraInfo.NameColorB = 0
	Actor_31H = ActorHandler(Actor_31)
	environment:AddActorObject(Actor_31H)

	Actor_32 = ActorObjectInfo(32)
	Actor_32:SetRenderType(1)
	Actor_32.DisplayDesc.ModelId = 3
	Actor_32.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_13.osgb"
	Actor_32.DisplayDesc.Outfit = ""
	Actor_32.DisplayDesc.Weapon = ""
	Actor_32.DisplayDesc.Mode = ""
	Actor_32.DisplayDesc.UseLight = false
	Actor_32.DisplayDesc.CastShadow = false
	Actor_32.DisplayDesc.ColorR = 3.30859
	Actor_32.DisplayDesc.ColorG = 4.2039e-045
	Actor_32.DisplayDesc.ColorB = 1.54143e-044
	Actor_32.DisplayDesc.ColorA = 1
	Actor_32:SetModelState(1)
	Actor_32.PhysicDesc.Pos.X = 438
	Actor_32.PhysicDesc.Pos.Y = 2.5
	Actor_32.PhysicDesc.Pos.Z = 452.5
	Actor_32.PhysicDesc.Pos.Rotation = -90
	Actor_32.PhysicDesc.Density = 4.2039e-045
	Actor_32.PhysicDesc.Collidable = false
	Actor_32.PhysicDesc.SizeX = 0
	Actor_32.PhysicDesc.SizeY = 3.42969
	Actor_32.PhysicDesc.SizeZ = 4.2039e-045
	Actor_32.PhysicDesc.Filename = ""
	Actor_32:SetPhysicalActorType(1)
	Actor_32:SetPhysicalShape(1)
	Actor_32.ExtraInfo.Name = ""
	Actor_32.ExtraInfo.NameColorR = 3.52539
	Actor_32.ExtraInfo.NameColorG = 4.2039e-045
	Actor_32.ExtraInfo.NameColorB = 3.36312e-044
	Actor_32H = ActorHandler(Actor_32)
	environment:AddActorObject(Actor_32H)

	Actor_33 = ActorObjectInfo(33)
	Actor_33:SetRenderType(1)
	Actor_33.DisplayDesc.ModelId = 0
	Actor_33.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_13.osgb"
	Actor_33.DisplayDesc.Outfit = ""
	Actor_33.DisplayDesc.Weapon = ""
	Actor_33.DisplayDesc.Mode = ""
	Actor_33.DisplayDesc.UseLight = false
	Actor_33.DisplayDesc.CastShadow = false
	Actor_33.DisplayDesc.ColorR = 1.97583e-043
	Actor_33.DisplayDesc.ColorG = 1
	Actor_33.DisplayDesc.ColorB = 4.10645
	Actor_33.DisplayDesc.ColorA = 4.2039e-045
	Actor_33:SetModelState(1)
	Actor_33.PhysicDesc.Pos.X = 443.5
	Actor_33.PhysicDesc.Pos.Y = 2.5
	Actor_33.PhysicDesc.Pos.Z = 458.125
	Actor_33.PhysicDesc.Pos.Rotation = 0
	Actor_33.PhysicDesc.Density = 0
	Actor_33.PhysicDesc.Collidable = false
	Actor_33.PhysicDesc.SizeX = 4.2039e-045
	Actor_33.PhysicDesc.SizeY = 2.0459e-043
	Actor_33.PhysicDesc.SizeZ = 0
	Actor_33.PhysicDesc.Filename = ""
	Actor_33:SetPhysicalActorType(1)
	Actor_33:SetPhysicalShape(1)
	Actor_33.ExtraInfo.Name = ""
	Actor_33.ExtraInfo.NameColorR = 2.11596e-043
	Actor_33.ExtraInfo.NameColorG = 0
	Actor_33.ExtraInfo.NameColorB = 4.15332
	Actor_33H = ActorHandler(Actor_33)
	environment:AddActorObject(Actor_33H)

	Actor_34 = ActorObjectInfo(34)
	Actor_34:SetRenderType(1)
	Actor_34.DisplayDesc.ModelId = 3
	Actor_34.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_14.osgb"
	Actor_34.DisplayDesc.Outfit = ""
	Actor_34.DisplayDesc.Weapon = ""
	Actor_34.DisplayDesc.Mode = ""
	Actor_34.DisplayDesc.UseLight = false
	Actor_34.DisplayDesc.CastShadow = false
	Actor_34.DisplayDesc.ColorR = 4.56396
	Actor_34.DisplayDesc.ColorG = 4.2039e-045
	Actor_34.DisplayDesc.ColorB = 2.91587e-039
	Actor_34.DisplayDesc.ColorA = 1
	Actor_34:SetModelState(1)
	Actor_34.PhysicDesc.Pos.X = 435
	Actor_34.PhysicDesc.Pos.Y = 2.5
	Actor_34.PhysicDesc.Pos.Z = 454
	Actor_34.PhysicDesc.Pos.Rotation = -90
	Actor_34.PhysicDesc.Density = 4.2039e-045
	Actor_34.PhysicDesc.Collidable = false
	Actor_34.PhysicDesc.SizeX = 0
	Actor_34.PhysicDesc.SizeY = 4.57471
	Actor_34.PhysicDesc.SizeZ = 4.2039e-045
	Actor_34.PhysicDesc.Filename = ""
	Actor_34:SetPhysicalActorType(1)
	Actor_34:SetPhysicalShape(1)
	Actor_34.ExtraInfo.Name = ""
	Actor_34.ExtraInfo.NameColorR = 4.5874
	Actor_34.ExtraInfo.NameColorG = 4.2039e-045
	Actor_34.ExtraInfo.NameColorB = 3.07659e-039
	Actor_34H = ActorHandler(Actor_34)
	environment:AddActorObject(Actor_34H)

	Actor_35 = ActorObjectInfo(35)
	Actor_35:SetRenderType(1)
	Actor_35.DisplayDesc.ModelId = 3
	Actor_35.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_14.osgb"
	Actor_35.DisplayDesc.Outfit = ""
	Actor_35.DisplayDesc.Weapon = ""
	Actor_35.DisplayDesc.Mode = ""
	Actor_35.DisplayDesc.UseLight = false
	Actor_35.DisplayDesc.CastShadow = true
	Actor_35.DisplayDesc.ColorR = 1.71105e-039
	Actor_35.DisplayDesc.ColorG = 5.60519e-045
	Actor_35.DisplayDesc.ColorB = 1.875
	Actor_35.DisplayDesc.ColorA = 1
	Actor_35:SetModelState(1)
	Actor_35.PhysicDesc.Pos.X = 442
	Actor_35.PhysicDesc.Pos.Y = 2.5
	Actor_35.PhysicDesc.Pos.Z = 461
	Actor_35.PhysicDesc.Pos.Rotation = 0
	Actor_35.PhysicDesc.Density = 5.60519e-045
	Actor_35.PhysicDesc.Collidable = false
	Actor_35.PhysicDesc.SizeX = 9.25985e-031
	Actor_35.PhysicDesc.SizeY = 1.71105e-039
	Actor_35.PhysicDesc.SizeZ = 5.60519e-045
	Actor_35.PhysicDesc.Filename = ""
	Actor_35:SetPhysicalActorType(1)
	Actor_35:SetPhysicalShape(1)
	Actor_35.ExtraInfo.Name = ""
	Actor_35.ExtraInfo.NameColorR = 2.13379
	Actor_35.ExtraInfo.NameColorG = 4.2039e-045
	Actor_35.ExtraInfo.NameColorB = 1.875
	Actor_35H = ActorHandler(Actor_35)
	environment:AddActorObject(Actor_35H)

	Actor_36 = ActorObjectInfo(36)
	Actor_36:SetRenderType(1)
	Actor_36.DisplayDesc.ModelId = 407747888
	Actor_36.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_14.osgb"
	Actor_36.DisplayDesc.Outfit = ""
	Actor_36.DisplayDesc.Weapon = ""
	Actor_36.DisplayDesc.Mode = ""
	Actor_36.DisplayDesc.UseLight = false
	Actor_36.DisplayDesc.CastShadow = false
	Actor_36.DisplayDesc.ColorR = 1
	Actor_36.DisplayDesc.ColorG = 1
	Actor_36.DisplayDesc.ColorB = 2.82813
	Actor_36.DisplayDesc.ColorA = 4.2039e-045
	Actor_36:SetModelState(1)
	Actor_36.PhysicDesc.Pos.X = 461
	Actor_36.PhysicDesc.Pos.Y = 2.5
	Actor_36.PhysicDesc.Pos.Z = 442
	Actor_36.PhysicDesc.Pos.Rotation = 90
	Actor_36.PhysicDesc.Density = 9.87225e-031
	Actor_36.PhysicDesc.Collidable = false
	Actor_36.PhysicDesc.SizeX = 5.60519e-045
	Actor_36.PhysicDesc.SizeY = 0
	Actor_36.PhysicDesc.SizeZ = 0
	Actor_36.PhysicDesc.Filename = ""
	Actor_36:SetPhysicalActorType(1)
	Actor_36:SetPhysicalShape(1)
	Actor_36.ExtraInfo.Name = ""
	Actor_36.ExtraInfo.NameColorR = 0
	Actor_36.ExtraInfo.NameColorG = 0
	Actor_36.ExtraInfo.NameColorB = 3.95068
	Actor_36H = ActorHandler(Actor_36)
	environment:AddActorObject(Actor_36H)

	Actor_37 = ActorObjectInfo(37)
	Actor_37:SetRenderType(1)
	Actor_37.DisplayDesc.ModelId = 4
	Actor_37.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_14.osgb"
	Actor_37.DisplayDesc.Outfit = ""
	Actor_37.DisplayDesc.Weapon = ""
	Actor_37.DisplayDesc.Mode = ""
	Actor_37.DisplayDesc.UseLight = false
	Actor_37.DisplayDesc.CastShadow = true
	Actor_37.DisplayDesc.ColorR = 1.14833e+027
	Actor_37.DisplayDesc.ColorG = 4.84192e+030
	Actor_37.DisplayDesc.ColorB = 8.68805e-044
	Actor_37.DisplayDesc.ColorA = 1
	Actor_37:SetModelState(1)
	Actor_37.PhysicDesc.Pos.X = 454.125
	Actor_37.PhysicDesc.Pos.Y = 2.5
	Actor_37.PhysicDesc.Pos.Z = 435
	Actor_37.PhysicDesc.Pos.Rotation = 180
	Actor_37.PhysicDesc.Density = 7.70435e-031
	Actor_37.PhysicDesc.Collidable = false
	Actor_37.PhysicDesc.SizeX = 2.29596e-039
	Actor_37.PhysicDesc.SizeY = 2.55792e-035
	Actor_37.PhysicDesc.SizeZ = 4.57363e-038
	Actor_37.PhysicDesc.Filename = ""
	Actor_37:SetPhysicalActorType(1)
	Actor_37:SetPhysicalShape(1)
	Actor_37.ExtraInfo.Name = ""
	Actor_37.ExtraInfo.NameColorR = 0
	Actor_37.ExtraInfo.NameColorG = 0
	Actor_37.ExtraInfo.NameColorB = 7.70439e-031
	Actor_37H = ActorHandler(Actor_37)
	environment:AddActorObject(Actor_37H)

	Actor_38 = ActorObjectInfo(38)
	Actor_38:SetRenderType(1)
	Actor_38.DisplayDesc.ModelId = 3
	Actor_38.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_13.osgb"
	Actor_38.DisplayDesc.Outfit = ""
	Actor_38.DisplayDesc.Weapon = ""
	Actor_38.DisplayDesc.Mode = ""
	Actor_38.DisplayDesc.UseLight = false
	Actor_38.DisplayDesc.CastShadow = false
	Actor_38.DisplayDesc.ColorR = 3.39063
	Actor_38.DisplayDesc.ColorG = 4.2039e-045
	Actor_38.DisplayDesc.ColorB = 1
	Actor_38.DisplayDesc.ColorA = 8.19475e+014
	Actor_38:SetModelState(1)
	Actor_38.PhysicDesc.Pos.X = 458
	Actor_38.PhysicDesc.Pos.Y = 2.5
	Actor_38.PhysicDesc.Pos.Z = 443.625
	Actor_38.PhysicDesc.Pos.Rotation = 90
	Actor_38.PhysicDesc.Density = 4.2039e-045
	Actor_38.PhysicDesc.Collidable = false
	Actor_38.PhysicDesc.SizeX = 1.87813e-031
	Actor_38.PhysicDesc.SizeY = 0
	Actor_38.PhysicDesc.SizeZ = 5.60519e-045
	Actor_38.PhysicDesc.Filename = ""
	Actor_38:SetPhysicalActorType(1)
	Actor_38:SetPhysicalShape(1)
	Actor_38.ExtraInfo.Name = ""
	Actor_38.ExtraInfo.NameColorR = 3.04688
	Actor_38.ExtraInfo.NameColorG = 4.2039e-045
	Actor_38.ExtraInfo.NameColorB = 7.00619e+022
	Actor_38H = ActorHandler(Actor_38)
	environment:AddActorObject(Actor_38H)

	Actor_39 = ActorObjectInfo(39)
	Actor_39:SetRenderType(1)
	Actor_39.DisplayDesc.ModelId = 416246224
	Actor_39.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/ILOTCX_OBJ_13.osgb"
	Actor_39.DisplayDesc.Outfit = ""
	Actor_39.DisplayDesc.Weapon = ""
	Actor_39.DisplayDesc.Mode = ""
	Actor_39.DisplayDesc.UseLight = false
	Actor_39.DisplayDesc.CastShadow = false
	Actor_39.DisplayDesc.ColorR = 1
	Actor_39.DisplayDesc.ColorG = 2.40103e-024
	Actor_39.DisplayDesc.ColorB = 1
	Actor_39.DisplayDesc.ColorA = 5.60519e-045
	Actor_39:SetModelState(1)
	Actor_39.PhysicDesc.Pos.X = 452
	Actor_39.PhysicDesc.Pos.Y = 2.5
	Actor_39.PhysicDesc.Pos.Z = 438
	Actor_39.PhysicDesc.Pos.Rotation = 180
	Actor_39.PhysicDesc.Density = 4.28688e-024
	Actor_39.PhysicDesc.Collidable = false
	Actor_39.PhysicDesc.SizeX = 5.60519e-045
	Actor_39.PhysicDesc.SizeY = 7.69742e-031
	Actor_39.PhysicDesc.SizeZ = 0
	Actor_39.PhysicDesc.Filename = ""
	Actor_39:SetPhysicalActorType(1)
	Actor_39:SetPhysicalShape(1)
	Actor_39.ExtraInfo.Name = ""
	Actor_39.ExtraInfo.NameColorR = 9.12854e-031
	Actor_39.ExtraInfo.NameColorG = 7.72818e-031
	Actor_39.ExtraInfo.NameColorB = 0
	Actor_39H = ActorHandler(Actor_39)
	environment:AddActorObject(Actor_39H)

end

