function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(524)
	Spawn_1:SetPosY(1.3)
	Spawn_1:SetPosZ(602)
	Spawn_1:SetName("Teleport")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(517)
	Spawn_2:SetPosY(1)
	Spawn_2:SetPosZ(618.5)
	Spawn_2:SetName("from_twinsenH")
	Spawn_2:SetForceRotation(true)
	Spawn_2:SetRotation(90)
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(535)
	Spawn_3:SetPosY(1)
	Spawn_3:SetPosZ(613)
	Spawn_3:SetName("from_architect")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(465)
	Spawn_4:SetPosY(3)
	Spawn_4:SetPosZ(562)
	Spawn_4:SetName("from_tickeshop")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(453)
	Spawn_5:SetPosY(3)
	Spawn_5:SetPosZ(562)
	Spawn_5:SetName("from_mrpaul")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(493)
	Spawn_6:SetPosY(1)
	Spawn_6:SetPosZ(573)
	Spawn_6:SetName("from_shop")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(515)
	Spawn_7:SetPosY(1)
	Spawn_7:SetPosZ(559)
	Spawn_7:SetName("from_tave")
	environment:AddSpawn(Spawn_7)

	Spawn_8 = Spawn(8)
	Spawn_8:SetPosX(494)
	Spawn_8:SetPosY(1)
	Spawn_8:SetPosZ(538)
	Spawn_8:SetName("from_muse")
	environment:AddSpawn(Spawn_8)

	Spawn_9 = Spawn(9)
	Spawn_9:SetPosX(502)
	Spawn_9:SetPosY(1)
	Spawn_9:SetPosZ(515)
	Spawn_9:SetName("from_pharm")
	environment:AddSpawn(Spawn_9)

	Spawn_10 = Spawn(10)
	Spawn_10:SetPosX(504.5)
	Spawn_10:SetPosY(1)
	Spawn_10:SetPosZ(509.5)
	Spawn_10:SetName("from_bag")
	environment:AddSpawn(Spawn_10)

	Spawn_11 = Spawn(11)
	Spawn_11:SetPosX(533.9)
	Spawn_11:SetPosY(1)
	Spawn_11:SetPosZ(501.5)
	Spawn_11:SetName("from_school")
	environment:AddSpawn(Spawn_11)

	Spawn_12 = Spawn(12)
	Spawn_12:SetPosX(452)
	Spawn_12:SetPosY(32.5)
	Spawn_12:SetPosZ(446.5)
	Spawn_12:SetName("from_magician")
	Spawn_12:SetForceRotation(true)
	Spawn_12:SetRotation(90)
	environment:AddSpawn(Spawn_12)

	Spawn_13 = Spawn(13)
	Spawn_13:SetPosX(541)
	Spawn_13:SetPosY(27.5)
	Spawn_13:SetPosZ(448)
	Spawn_13:SetName("from_spiderfirst")
	Spawn_13:SetForceRotation(true)
	Spawn_13:SetRotation(180)
	environment:AddSpawn(Spawn_13)

	Spawn_14 = Spawn(14)
	Spawn_14:SetPosX(537.5)
	Spawn_14:SetPosY(22.5)
	Spawn_14:SetPosZ(427)
	Spawn_14:SetName("from_spidersecond")
	Spawn_14:SetForceRotation(true)
	Spawn_14:SetRotation(180)
	environment:AddSpawn(Spawn_14)

	Spawn_15 = Spawn(15)
	Spawn_15:SetPosX(477)
	Spawn_15:SetPosY(22.5)
	Spawn_15:SetPosZ(439.5)
	Spawn_15:SetName("from_tralumain")
	environment:AddSpawn(Spawn_15)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = false
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 1
	Actor_1.DisplayDesc.ColorG = 1
	Actor_1.DisplayDesc.ColorB = 1
	Actor_1.DisplayDesc.ColorA = 1
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL.phy"
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
	Actor_2.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_2.DisplayDesc.Outfit = ""
	Actor_2.DisplayDesc.Weapon = ""
	Actor_2.DisplayDesc.Mode = ""
	Actor_2.DisplayDesc.UseLight = false
	Actor_2.DisplayDesc.CastShadow = false
	Actor_2.DisplayDesc.ColorR = 1
	Actor_2.DisplayDesc.ColorG = 1
	Actor_2.DisplayDesc.ColorB = 1
	Actor_2.DisplayDesc.ColorA = 1
	Actor_2:SetModelState(1)
	Actor_2.PhysicDesc.Pos.X = 462.75
	Actor_2.PhysicDesc.Pos.Y = 33.6914
	Actor_2.PhysicDesc.Pos.Z = 437.75
	Actor_2.PhysicDesc.Pos.Rotation = -90
	Actor_2.PhysicDesc.Density = 0
	Actor_2.PhysicDesc.Collidable = true
	Actor_2.PhysicDesc.SizeX = 0
	Actor_2.PhysicDesc.SizeY = 0
	Actor_2.PhysicDesc.SizeZ = 0
	Actor_2.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
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
	Actor_3.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_3.DisplayDesc.Outfit = ""
	Actor_3.DisplayDesc.Weapon = ""
	Actor_3.DisplayDesc.Mode = ""
	Actor_3.DisplayDesc.UseLight = false
	Actor_3.DisplayDesc.CastShadow = false
	Actor_3.DisplayDesc.ColorR = 1
	Actor_3.DisplayDesc.ColorG = 1
	Actor_3.DisplayDesc.ColorB = 1
	Actor_3.DisplayDesc.ColorA = 1
	Actor_3:SetModelState(1)
	Actor_3.PhysicDesc.Pos.X = 469.125
	Actor_3.PhysicDesc.Pos.Y = 31.7383
	Actor_3.PhysicDesc.Pos.Z = 453.5
	Actor_3.PhysicDesc.Pos.Rotation = -90
	Actor_3.PhysicDesc.Density = 0
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = 0
	Actor_3.PhysicDesc.SizeY = 0
	Actor_3.PhysicDesc.SizeZ = 0
	Actor_3.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_3:SetPhysicalActorType(1)
	Actor_3:SetPhysicalShape(5)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 0
	Actor_3.ExtraInfo.NameColorG = 0
	Actor_3.ExtraInfo.NameColorB = 0
	Actor_3H = ActorHandler(Actor_3)
	environment:AddActorObject(Actor_3H)

	Actor_4 = ActorObjectInfo(4)
	Actor_4:SetRenderType(1)
	Actor_4.DisplayDesc.ModelId = 0
	Actor_4.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_4.DisplayDesc.Outfit = ""
	Actor_4.DisplayDesc.Weapon = ""
	Actor_4.DisplayDesc.Mode = ""
	Actor_4.DisplayDesc.UseLight = false
	Actor_4.DisplayDesc.CastShadow = false
	Actor_4.DisplayDesc.ColorR = 1
	Actor_4.DisplayDesc.ColorG = 1
	Actor_4.DisplayDesc.ColorB = 1
	Actor_4.DisplayDesc.ColorA = 1
	Actor_4:SetModelState(1)
	Actor_4.PhysicDesc.Pos.X = 464.75
	Actor_4.PhysicDesc.Pos.Y = 32.957
	Actor_4.PhysicDesc.Pos.Z = 444.25
	Actor_4.PhysicDesc.Pos.Rotation = 90
	Actor_4.PhysicDesc.Density = 0
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 0
	Actor_4.PhysicDesc.SizeY = 0
	Actor_4.PhysicDesc.SizeZ = 0
	Actor_4.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_4:SetPhysicalActorType(1)
	Actor_4:SetPhysicalShape(5)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 0
	Actor_4.ExtraInfo.NameColorG = 0
	Actor_4.ExtraInfo.NameColorB = 0
	Actor_4H = ActorHandler(Actor_4)
	environment:AddActorObject(Actor_4H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(1)
	Actor_5.DisplayDesc.ModelId = 0
	Actor_5.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_5.DisplayDesc.Outfit = ""
	Actor_5.DisplayDesc.Weapon = ""
	Actor_5.DisplayDesc.Mode = ""
	Actor_5.DisplayDesc.UseLight = false
	Actor_5.DisplayDesc.CastShadow = false
	Actor_5.DisplayDesc.ColorR = 1
	Actor_5.DisplayDesc.ColorG = 1
	Actor_5.DisplayDesc.ColorB = 1
	Actor_5.DisplayDesc.ColorA = 1
	Actor_5:SetModelState(1)
	Actor_5.PhysicDesc.Pos.X = 459.5
	Actor_5.PhysicDesc.Pos.Y = 32.2266
	Actor_5.PhysicDesc.Pos.Z = 451.5
	Actor_5.PhysicDesc.Pos.Rotation = 90
	Actor_5.PhysicDesc.Density = 0
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = 0
	Actor_5.PhysicDesc.SizeY = 0
	Actor_5.PhysicDesc.SizeZ = 0
	Actor_5.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_5:SetPhysicalActorType(1)
	Actor_5:SetPhysicalShape(5)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = 0
	Actor_5.ExtraInfo.NameColorG = 0
	Actor_5.ExtraInfo.NameColorB = 0
	Actor_5H = ActorHandler(Actor_5)
	environment:AddActorObject(Actor_5H)

	Actor_6 = ActorObjectInfo(6)
	Actor_6:SetRenderType(1)
	Actor_6.DisplayDesc.ModelId = 0
	Actor_6.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_6.DisplayDesc.Outfit = ""
	Actor_6.DisplayDesc.Weapon = ""
	Actor_6.DisplayDesc.Mode = ""
	Actor_6.DisplayDesc.UseLight = false
	Actor_6.DisplayDesc.CastShadow = false
	Actor_6.DisplayDesc.ColorR = 1
	Actor_6.DisplayDesc.ColorG = 1
	Actor_6.DisplayDesc.ColorB = 1
	Actor_6.DisplayDesc.ColorA = 1
	Actor_6:SetModelState(1)
	Actor_6.PhysicDesc.Pos.X = 476.5
	Actor_6.PhysicDesc.Pos.Y = 30.5195
	Actor_6.PhysicDesc.Pos.Z = 456.5
	Actor_6.PhysicDesc.Pos.Rotation = 90
	Actor_6.PhysicDesc.Density = 0
	Actor_6.PhysicDesc.Collidable = true
	Actor_6.PhysicDesc.SizeX = 0
	Actor_6.PhysicDesc.SizeY = 0
	Actor_6.PhysicDesc.SizeZ = 0
	Actor_6.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_6:SetPhysicalActorType(1)
	Actor_6:SetPhysicalShape(5)
	Actor_6.ExtraInfo.Name = ""
	Actor_6.ExtraInfo.NameColorR = 0
	Actor_6.ExtraInfo.NameColorG = 0
	Actor_6.ExtraInfo.NameColorB = 0
	Actor_6H = ActorHandler(Actor_6)
	environment:AddActorObject(Actor_6H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(1)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_4.osgb"
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
	Actor_7.PhysicDesc.Pos.X = 446.289
	Actor_7.PhysicDesc.Pos.Y = 33.8984
	Actor_7.PhysicDesc.Pos.Z = 446.5
	Actor_7.PhysicDesc.Pos.Rotation = 0
	Actor_7.PhysicDesc.Density = 0
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 0
	Actor_7.PhysicDesc.SizeY = 0
	Actor_7.PhysicDesc.SizeZ = 0
	Actor_7.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_4.phy"
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
	Actor_8.DisplayDesc.ModelId = 0
	Actor_8.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
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
	Actor_8.PhysicDesc.Pos.X = 434.5
	Actor_8.PhysicDesc.Pos.Y = 32.2266
	Actor_8.PhysicDesc.Pos.Z = 431.5
	Actor_8.PhysicDesc.Pos.Rotation = 90
	Actor_8.PhysicDesc.Density = 0
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 0
	Actor_8.PhysicDesc.SizeY = 0
	Actor_8.PhysicDesc.SizeZ = 0
	Actor_8.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
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
	Actor_9.DisplayDesc.ModelId = 0
	Actor_9.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_9.DisplayDesc.Outfit = ""
	Actor_9.DisplayDesc.Weapon = ""
	Actor_9.DisplayDesc.Mode = ""
	Actor_9.DisplayDesc.UseLight = false
	Actor_9.DisplayDesc.CastShadow = false
	Actor_9.DisplayDesc.ColorR = 1
	Actor_9.DisplayDesc.ColorG = 1
	Actor_9.DisplayDesc.ColorB = 1
	Actor_9.DisplayDesc.ColorA = 1
	Actor_9:SetModelState(1)
	Actor_9.PhysicDesc.Pos.X = 424.5
	Actor_9.PhysicDesc.Pos.Y = 32.2266
	Actor_9.PhysicDesc.Pos.Z = 442.5
	Actor_9.PhysicDesc.Pos.Rotation = 180
	Actor_9.PhysicDesc.Density = 0
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 0
	Actor_9.PhysicDesc.SizeY = 0
	Actor_9.PhysicDesc.SizeZ = 0
	Actor_9.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
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
	Actor_10.DisplayDesc.ModelId = 0
	Actor_10.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_10.DisplayDesc.Outfit = ""
	Actor_10.DisplayDesc.Weapon = ""
	Actor_10.DisplayDesc.Mode = ""
	Actor_10.DisplayDesc.UseLight = false
	Actor_10.DisplayDesc.CastShadow = false
	Actor_10.DisplayDesc.ColorR = 1
	Actor_10.DisplayDesc.ColorG = 1
	Actor_10.DisplayDesc.ColorB = 1
	Actor_10.DisplayDesc.ColorA = 1
	Actor_10:SetModelState(1)
	Actor_10.PhysicDesc.Pos.X = 457.125
	Actor_10.PhysicDesc.Pos.Y = 33.2031
	Actor_10.PhysicDesc.Pos.Z = 449.5
	Actor_10.PhysicDesc.Pos.Rotation = 0
	Actor_10.PhysicDesc.Density = 0
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 0
	Actor_10.PhysicDesc.SizeY = 0
	Actor_10.PhysicDesc.SizeZ = 0
	Actor_10.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
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
	Actor_11.DisplayDesc.ModelId = 0
	Actor_11.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_3.osgb"
	Actor_11.DisplayDesc.Outfit = ""
	Actor_11.DisplayDesc.Weapon = ""
	Actor_11.DisplayDesc.Mode = ""
	Actor_11.DisplayDesc.UseLight = false
	Actor_11.DisplayDesc.CastShadow = false
	Actor_11.DisplayDesc.ColorR = 1
	Actor_11.DisplayDesc.ColorG = 1
	Actor_11.DisplayDesc.ColorB = 1
	Actor_11.DisplayDesc.ColorA = 1
	Actor_11:SetModelState(1)
	Actor_11.PhysicDesc.Pos.X = 474
	Actor_11.PhysicDesc.Pos.Y = 21.9727
	Actor_11.PhysicDesc.Pos.Z = 439.484
	Actor_11.PhysicDesc.Pos.Rotation = 0
	Actor_11.PhysicDesc.Density = 0
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 0
	Actor_11.PhysicDesc.SizeY = 0
	Actor_11.PhysicDesc.SizeZ = 0
	Actor_11.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_3.phy"
	Actor_11:SetPhysicalActorType(1)
	Actor_11:SetPhysicalShape(5)
	Actor_11.ExtraInfo.Name = ""
	Actor_11.ExtraInfo.NameColorR = 0
	Actor_11.ExtraInfo.NameColorG = 0
	Actor_11.ExtraInfo.NameColorB = 0
	Actor_11H = ActorHandler(Actor_11)
	environment:AddActorObject(Actor_11H)

	Actor_12 = ActorObjectInfo(12)
	Actor_12:SetRenderType(1)
	Actor_12.DisplayDesc.ModelId = 0
	Actor_12.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.osgb"
	Actor_12.DisplayDesc.Outfit = ""
	Actor_12.DisplayDesc.Weapon = ""
	Actor_12.DisplayDesc.Mode = ""
	Actor_12.DisplayDesc.UseLight = false
	Actor_12.DisplayDesc.CastShadow = false
	Actor_12.DisplayDesc.ColorR = 1
	Actor_12.DisplayDesc.ColorG = 1
	Actor_12.DisplayDesc.ColorB = 1
	Actor_12.DisplayDesc.ColorA = 1
	Actor_12:SetModelState(1)
	Actor_12.PhysicDesc.Pos.X = 459.75
	Actor_12.PhysicDesc.Pos.Y = 33.6914
	Actor_12.PhysicDesc.Pos.Z = 431.5
	Actor_12.PhysicDesc.Pos.Rotation = 0
	Actor_12.PhysicDesc.Density = 0
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 0
	Actor_12.PhysicDesc.SizeY = 0
	Actor_12.PhysicDesc.SizeZ = 0
	Actor_12.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.phy"
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
	Actor_13.DisplayDesc.ModelId = 0
	Actor_13.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.osgb"
	Actor_13.DisplayDesc.Outfit = ""
	Actor_13.DisplayDesc.Weapon = ""
	Actor_13.DisplayDesc.Mode = ""
	Actor_13.DisplayDesc.UseLight = false
	Actor_13.DisplayDesc.CastShadow = false
	Actor_13.DisplayDesc.ColorR = 1
	Actor_13.DisplayDesc.ColorG = 1
	Actor_13.DisplayDesc.ColorB = 1
	Actor_13.DisplayDesc.ColorA = 1
	Actor_13:SetModelState(1)
	Actor_13.PhysicDesc.Pos.X = 458
	Actor_13.PhysicDesc.Pos.Y = 32.7148
	Actor_13.PhysicDesc.Pos.Z = 430.75
	Actor_13.PhysicDesc.Pos.Rotation = 180
	Actor_13.PhysicDesc.Density = 0
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 0
	Actor_13.PhysicDesc.SizeY = 0
	Actor_13.PhysicDesc.SizeZ = 0
	Actor_13.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.phy"
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
	Actor_14.DisplayDesc.ModelId = 0
	Actor_14.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_14.DisplayDesc.Outfit = ""
	Actor_14.DisplayDesc.Weapon = ""
	Actor_14.DisplayDesc.Mode = ""
	Actor_14.DisplayDesc.UseLight = false
	Actor_14.DisplayDesc.CastShadow = false
	Actor_14.DisplayDesc.ColorR = 1
	Actor_14.DisplayDesc.ColorG = 1
	Actor_14.DisplayDesc.ColorB = 1
	Actor_14.DisplayDesc.ColorA = 1
	Actor_14:SetModelState(1)
	Actor_14.PhysicDesc.Pos.X = 537.5
	Actor_14.PhysicDesc.Pos.Y = 34.1797
	Actor_14.PhysicDesc.Pos.Z = 456.125
	Actor_14.PhysicDesc.Pos.Rotation = 90
	Actor_14.PhysicDesc.Density = 0
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 0
	Actor_14.PhysicDesc.SizeY = 0
	Actor_14.PhysicDesc.SizeZ = 0
	Actor_14.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
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
	Actor_15.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_15.DisplayDesc.Outfit = ""
	Actor_15.DisplayDesc.Weapon = ""
	Actor_15.DisplayDesc.Mode = ""
	Actor_15.DisplayDesc.UseLight = false
	Actor_15.DisplayDesc.CastShadow = false
	Actor_15.DisplayDesc.ColorR = 1
	Actor_15.DisplayDesc.ColorG = 1
	Actor_15.DisplayDesc.ColorB = 1
	Actor_15.DisplayDesc.ColorA = 1
	Actor_15:SetModelState(1)
	Actor_15.PhysicDesc.Pos.X = 533.5
	Actor_15.PhysicDesc.Pos.Y = 34.1797
	Actor_15.PhysicDesc.Pos.Z = 462.5
	Actor_15.PhysicDesc.Pos.Rotation = 90
	Actor_15.PhysicDesc.Density = 0
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 0
	Actor_15.PhysicDesc.SizeY = 0
	Actor_15.PhysicDesc.SizeZ = 0
	Actor_15.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_15:SetPhysicalActorType(1)
	Actor_15:SetPhysicalShape(5)
	Actor_15.ExtraInfo.Name = ""
	Actor_15.ExtraInfo.NameColorR = 0
	Actor_15.ExtraInfo.NameColorG = 0
	Actor_15.ExtraInfo.NameColorB = 0
	Actor_15H = ActorHandler(Actor_15)
	environment:AddActorObject(Actor_15H)

	Actor_16 = ActorObjectInfo(16)
	Actor_16:SetRenderType(1)
	Actor_16.DisplayDesc.ModelId = 0
	Actor_16.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_16.DisplayDesc.Outfit = ""
	Actor_16.DisplayDesc.Weapon = ""
	Actor_16.DisplayDesc.Mode = ""
	Actor_16.DisplayDesc.UseLight = false
	Actor_16.DisplayDesc.CastShadow = false
	Actor_16.DisplayDesc.ColorR = 1
	Actor_16.DisplayDesc.ColorG = 1
	Actor_16.DisplayDesc.ColorB = 1
	Actor_16.DisplayDesc.ColorA = 1
	Actor_16:SetModelState(1)
	Actor_16.PhysicDesc.Pos.X = 529.5
	Actor_16.PhysicDesc.Pos.Y = 34.1797
	Actor_16.PhysicDesc.Pos.Z = 460.5
	Actor_16.PhysicDesc.Pos.Rotation = 90
	Actor_16.PhysicDesc.Density = 0
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 0
	Actor_16.PhysicDesc.SizeY = 0
	Actor_16.PhysicDesc.SizeZ = 0
	Actor_16.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_16:SetPhysicalActorType(1)
	Actor_16:SetPhysicalShape(5)
	Actor_16.ExtraInfo.Name = ""
	Actor_16.ExtraInfo.NameColorR = 0
	Actor_16.ExtraInfo.NameColorG = 0
	Actor_16.ExtraInfo.NameColorB = 0
	Actor_16H = ActorHandler(Actor_16)
	environment:AddActorObject(Actor_16H)

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(1)
	Actor_17.DisplayDesc.ModelId = 0
	Actor_17.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_17.DisplayDesc.Outfit = ""
	Actor_17.DisplayDesc.Weapon = ""
	Actor_17.DisplayDesc.Mode = ""
	Actor_17.DisplayDesc.UseLight = false
	Actor_17.DisplayDesc.CastShadow = false
	Actor_17.DisplayDesc.ColorR = 1
	Actor_17.DisplayDesc.ColorG = 1
	Actor_17.DisplayDesc.ColorB = 1
	Actor_17.DisplayDesc.ColorA = 1
	Actor_17:SetModelState(1)
	Actor_17.PhysicDesc.Pos.X = 524.5
	Actor_17.PhysicDesc.Pos.Y = 34.1797
	Actor_17.PhysicDesc.Pos.Z = 453.5
	Actor_17.PhysicDesc.Pos.Rotation = 90
	Actor_17.PhysicDesc.Density = 0
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 0
	Actor_17.PhysicDesc.SizeY = 0
	Actor_17.PhysicDesc.SizeZ = 0
	Actor_17.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_17:SetPhysicalActorType(1)
	Actor_17:SetPhysicalShape(5)
	Actor_17.ExtraInfo.Name = ""
	Actor_17.ExtraInfo.NameColorR = 0
	Actor_17.ExtraInfo.NameColorG = 0
	Actor_17.ExtraInfo.NameColorB = 0
	Actor_17H = ActorHandler(Actor_17)
	environment:AddActorObject(Actor_17H)

	Actor_18 = ActorObjectInfo(18)
	Actor_18:SetRenderType(1)
	Actor_18.DisplayDesc.ModelId = 0
	Actor_18.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_18.DisplayDesc.Outfit = ""
	Actor_18.DisplayDesc.Weapon = ""
	Actor_18.DisplayDesc.Mode = ""
	Actor_18.DisplayDesc.UseLight = false
	Actor_18.DisplayDesc.CastShadow = false
	Actor_18.DisplayDesc.ColorR = 1
	Actor_18.DisplayDesc.ColorG = 1
	Actor_18.DisplayDesc.ColorB = 1
	Actor_18.DisplayDesc.ColorA = 1
	Actor_18:SetModelState(1)
	Actor_18.PhysicDesc.Pos.X = 529.5
	Actor_18.PhysicDesc.Pos.Y = 34.1797
	Actor_18.PhysicDesc.Pos.Z = 449.5
	Actor_18.PhysicDesc.Pos.Rotation = 90
	Actor_18.PhysicDesc.Density = 0
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 0
	Actor_18.PhysicDesc.SizeY = 0
	Actor_18.PhysicDesc.SizeZ = 0
	Actor_18.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_18:SetPhysicalActorType(1)
	Actor_18:SetPhysicalShape(5)
	Actor_18.ExtraInfo.Name = ""
	Actor_18.ExtraInfo.NameColorR = 0
	Actor_18.ExtraInfo.NameColorG = 0
	Actor_18.ExtraInfo.NameColorB = 0
	Actor_18H = ActorHandler(Actor_18)
	environment:AddActorObject(Actor_18H)

	Actor_19 = ActorObjectInfo(19)
	Actor_19:SetRenderType(1)
	Actor_19.DisplayDesc.ModelId = 0
	Actor_19.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_19.DisplayDesc.Outfit = ""
	Actor_19.DisplayDesc.Weapon = ""
	Actor_19.DisplayDesc.Mode = ""
	Actor_19.DisplayDesc.UseLight = false
	Actor_19.DisplayDesc.CastShadow = false
	Actor_19.DisplayDesc.ColorR = 1
	Actor_19.DisplayDesc.ColorG = 1
	Actor_19.DisplayDesc.ColorB = 1
	Actor_19.DisplayDesc.ColorA = 1
	Actor_19:SetModelState(1)
	Actor_19.PhysicDesc.Pos.X = 493.625
	Actor_19.PhysicDesc.Pos.Y = 24.5977
	Actor_19.PhysicDesc.Pos.Z = 470.875
	Actor_19.PhysicDesc.Pos.Rotation = 180
	Actor_19.PhysicDesc.Density = 0
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = 0
	Actor_19.PhysicDesc.SizeY = 0
	Actor_19.PhysicDesc.SizeZ = 0
	Actor_19.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_19:SetPhysicalActorType(1)
	Actor_19:SetPhysicalShape(5)
	Actor_19.ExtraInfo.Name = ""
	Actor_19.ExtraInfo.NameColorR = 0
	Actor_19.ExtraInfo.NameColorG = 0
	Actor_19.ExtraInfo.NameColorB = 0
	Actor_19H = ActorHandler(Actor_19)
	environment:AddActorObject(Actor_19H)

	Actor_20 = ActorObjectInfo(20)
	Actor_20:SetRenderType(1)
	Actor_20.DisplayDesc.ModelId = 0
	Actor_20.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_20.DisplayDesc.Outfit = ""
	Actor_20.DisplayDesc.Weapon = ""
	Actor_20.DisplayDesc.Mode = ""
	Actor_20.DisplayDesc.UseLight = false
	Actor_20.DisplayDesc.CastShadow = false
	Actor_20.DisplayDesc.ColorR = 1
	Actor_20.DisplayDesc.ColorG = 1
	Actor_20.DisplayDesc.ColorB = 1
	Actor_20.DisplayDesc.ColorA = 1
	Actor_20:SetModelState(1)
	Actor_20.PhysicDesc.Pos.X = 498.5
	Actor_20.PhysicDesc.Pos.Y = 24.9023
	Actor_20.PhysicDesc.Pos.Z = 474.25
	Actor_20.PhysicDesc.Pos.Rotation = 180
	Actor_20.PhysicDesc.Density = 0
	Actor_20.PhysicDesc.Collidable = true
	Actor_20.PhysicDesc.SizeX = 0
	Actor_20.PhysicDesc.SizeY = 0
	Actor_20.PhysicDesc.SizeZ = 0
	Actor_20.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_20:SetPhysicalActorType(1)
	Actor_20:SetPhysicalShape(5)
	Actor_20.ExtraInfo.Name = ""
	Actor_20.ExtraInfo.NameColorR = 0
	Actor_20.ExtraInfo.NameColorG = 0
	Actor_20.ExtraInfo.NameColorB = 0
	Actor_20H = ActorHandler(Actor_20)
	environment:AddActorObject(Actor_20H)

	Actor_21 = ActorObjectInfo(21)
	Actor_21:SetRenderType(1)
	Actor_21.DisplayDesc.ModelId = 0
	Actor_21.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_21.DisplayDesc.Outfit = ""
	Actor_21.DisplayDesc.Weapon = ""
	Actor_21.DisplayDesc.Mode = ""
	Actor_21.DisplayDesc.UseLight = false
	Actor_21.DisplayDesc.CastShadow = false
	Actor_21.DisplayDesc.ColorR = 1
	Actor_21.DisplayDesc.ColorG = 1
	Actor_21.DisplayDesc.ColorB = 1
	Actor_21.DisplayDesc.ColorA = 1
	Actor_21:SetModelState(1)
	Actor_21.PhysicDesc.Pos.X = 525.5
	Actor_21.PhysicDesc.Pos.Y = 34
	Actor_21.PhysicDesc.Pos.Z = 459.375
	Actor_21.PhysicDesc.Pos.Rotation = 90
	Actor_21.PhysicDesc.Density = 0
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 0
	Actor_21.PhysicDesc.SizeY = 0
	Actor_21.PhysicDesc.SizeZ = 0
	Actor_21.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_21:SetPhysicalActorType(1)
	Actor_21:SetPhysicalShape(5)
	Actor_21.ExtraInfo.Name = ""
	Actor_21.ExtraInfo.NameColorR = 0
	Actor_21.ExtraInfo.NameColorG = 0
	Actor_21.ExtraInfo.NameColorB = 0
	Actor_21H = ActorHandler(Actor_21)
	environment:AddActorObject(Actor_21H)

	Actor_22 = ActorObjectInfo(22)
	Actor_22:SetRenderType(1)
	Actor_22.DisplayDesc.ModelId = 0
	Actor_22.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_22.DisplayDesc.Outfit = ""
	Actor_22.DisplayDesc.Weapon = ""
	Actor_22.DisplayDesc.Mode = ""
	Actor_22.DisplayDesc.UseLight = false
	Actor_22.DisplayDesc.CastShadow = false
	Actor_22.DisplayDesc.ColorR = 1
	Actor_22.DisplayDesc.ColorG = 1
	Actor_22.DisplayDesc.ColorB = 1
	Actor_22.DisplayDesc.ColorA = 1
	Actor_22:SetModelState(1)
	Actor_22.PhysicDesc.Pos.X = 531.5
	Actor_22.PhysicDesc.Pos.Y = 34.1797
	Actor_22.PhysicDesc.Pos.Z = 455.5
	Actor_22.PhysicDesc.Pos.Rotation = 90
	Actor_22.PhysicDesc.Density = 0
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 0
	Actor_22.PhysicDesc.SizeY = 0
	Actor_22.PhysicDesc.SizeZ = 0
	Actor_22.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_22:SetPhysicalActorType(1)
	Actor_22:SetPhysicalShape(5)
	Actor_22.ExtraInfo.Name = ""
	Actor_22.ExtraInfo.NameColorR = 0
	Actor_22.ExtraInfo.NameColorG = 0
	Actor_22.ExtraInfo.NameColorB = 0
	Actor_22H = ActorHandler(Actor_22)
	environment:AddActorObject(Actor_22H)

	Actor_23 = ActorObjectInfo(23)
	Actor_23:SetRenderType(1)
	Actor_23.DisplayDesc.ModelId = 0
	Actor_23.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_23.DisplayDesc.Outfit = ""
	Actor_23.DisplayDesc.Weapon = ""
	Actor_23.DisplayDesc.Mode = ""
	Actor_23.DisplayDesc.UseLight = false
	Actor_23.DisplayDesc.CastShadow = false
	Actor_23.DisplayDesc.ColorR = 1
	Actor_23.DisplayDesc.ColorG = 1
	Actor_23.DisplayDesc.ColorB = 1
	Actor_23.DisplayDesc.ColorA = 1
	Actor_23:SetModelState(1)
	Actor_23.PhysicDesc.Pos.X = 538.5
	Actor_23.PhysicDesc.Pos.Y = 34.1797
	Actor_23.PhysicDesc.Pos.Z = 464.5
	Actor_23.PhysicDesc.Pos.Rotation = 90
	Actor_23.PhysicDesc.Density = 0
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 0
	Actor_23.PhysicDesc.SizeY = 0
	Actor_23.PhysicDesc.SizeZ = 0
	Actor_23.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_23:SetPhysicalActorType(1)
	Actor_23:SetPhysicalShape(5)
	Actor_23.ExtraInfo.Name = ""
	Actor_23.ExtraInfo.NameColorR = 0
	Actor_23.ExtraInfo.NameColorG = 0
	Actor_23.ExtraInfo.NameColorB = 0
	Actor_23H = ActorHandler(Actor_23)
	environment:AddActorObject(Actor_23H)

	Actor_24 = ActorObjectInfo(24)
	Actor_24:SetRenderType(1)
	Actor_24.DisplayDesc.ModelId = 0
	Actor_24.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
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
	Actor_24.PhysicDesc.Pos.X = 522.5
	Actor_24.PhysicDesc.Pos.Y = 34.1797
	Actor_24.PhysicDesc.Pos.Z = 448.5
	Actor_24.PhysicDesc.Pos.Rotation = 90
	Actor_24.PhysicDesc.Density = 0
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 0
	Actor_24.PhysicDesc.SizeY = 0
	Actor_24.PhysicDesc.SizeZ = 0
	Actor_24.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_24:SetPhysicalActorType(1)
	Actor_24:SetPhysicalShape(5)
	Actor_24.ExtraInfo.Name = ""
	Actor_24.ExtraInfo.NameColorR = 0
	Actor_24.ExtraInfo.NameColorG = 0
	Actor_24.ExtraInfo.NameColorB = 0
	Actor_24H = ActorHandler(Actor_24)
	environment:AddActorObject(Actor_24H)

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(1)
	Actor_25.DisplayDesc.ModelId = 0
	Actor_25.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_3.osgb"
	Actor_25.DisplayDesc.Outfit = ""
	Actor_25.DisplayDesc.Weapon = ""
	Actor_25.DisplayDesc.Mode = ""
	Actor_25.DisplayDesc.UseLight = false
	Actor_25.DisplayDesc.CastShadow = false
	Actor_25.DisplayDesc.ColorR = 1
	Actor_25.DisplayDesc.ColorG = 1
	Actor_25.DisplayDesc.ColorB = 1
	Actor_25.DisplayDesc.ColorA = 1
	Actor_25:SetModelState(1)
	Actor_25.PhysicDesc.Pos.X = 540.5
	Actor_25.PhysicDesc.Pos.Y = 28.8086
	Actor_25.PhysicDesc.Pos.Z = 450.875
	Actor_25.PhysicDesc.Pos.Rotation = 90
	Actor_25.PhysicDesc.Density = 0
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 0
	Actor_25.PhysicDesc.SizeY = 0
	Actor_25.PhysicDesc.SizeZ = 0
	Actor_25.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_3.phy"
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
	Actor_26.DisplayDesc.ModelId = 0
	Actor_26.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_3.osgb"
	Actor_26.DisplayDesc.Outfit = ""
	Actor_26.DisplayDesc.Weapon = ""
	Actor_26.DisplayDesc.Mode = ""
	Actor_26.DisplayDesc.UseLight = false
	Actor_26.DisplayDesc.CastShadow = false
	Actor_26.DisplayDesc.ColorR = 1
	Actor_26.DisplayDesc.ColorG = 1
	Actor_26.DisplayDesc.ColorB = 1.3
	Actor_26.DisplayDesc.ColorA = 1
	Actor_26:SetModelState(1)
	Actor_26.PhysicDesc.Pos.X = 538.5
	Actor_26.PhysicDesc.Pos.Y = 21.9727
	Actor_26.PhysicDesc.Pos.Z = 428.875
	Actor_26.PhysicDesc.Pos.Rotation = 90
	Actor_26.PhysicDesc.Density = 0.00784314
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 0.45098
	Actor_26.PhysicDesc.SizeY = 0
	Actor_26.PhysicDesc.SizeZ = 0.00784314
	Actor_26.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_3.phy"
	Actor_26:SetPhysicalActorType(1)
	Actor_26:SetPhysicalShape(5)
	Actor_26.ExtraInfo.Name = ""
	Actor_26.ExtraInfo.NameColorR = 9.94922e-044
	Actor_26.ExtraInfo.NameColorG = 4.62428e-044
	Actor_26.ExtraInfo.NameColorB = 5.88545e-044
	Actor_26H = ActorHandler(Actor_26)
	environment:AddActorObject(Actor_26H)

	Actor_27 = ActorObjectInfo(27)
	Actor_27:SetRenderType(1)
	Actor_27.DisplayDesc.ModelId = 0
	Actor_27.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_27.DisplayDesc.Outfit = ""
	Actor_27.DisplayDesc.Weapon = ""
	Actor_27.DisplayDesc.Mode = ""
	Actor_27.DisplayDesc.UseLight = false
	Actor_27.DisplayDesc.CastShadow = false
	Actor_27.DisplayDesc.ColorR = 1.96182e-044
	Actor_27.DisplayDesc.ColorG = 4.62428e-044
	Actor_27.DisplayDesc.ColorB = 4.76441e-044
	Actor_27.DisplayDesc.ColorA = 6.30584e-044
	Actor_27:SetModelState(1)
	Actor_27.PhysicDesc.Pos.X = 501.5
	Actor_27.PhysicDesc.Pos.Y = 33.1992
	Actor_27.PhysicDesc.Pos.Z = 457.5
	Actor_27.PhysicDesc.Pos.Rotation = 90
	Actor_27.PhysicDesc.Density = 4.06377e-044
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 3.64338e-044
	Actor_27.PhysicDesc.SizeY = 3.78351e-044
	Actor_27.PhysicDesc.SizeZ = 5.46506e-044
	Actor_27.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_27:SetPhysicalActorType(1)
	Actor_27:SetPhysicalShape(5)
	Actor_27.ExtraInfo.Name = ""
	Actor_27.ExtraInfo.NameColorR = 3.08286e-044
	Actor_27.ExtraInfo.NameColorG = 2.66247e-044
	Actor_27.ExtraInfo.NameColorB = 2.8026e-044
	Actor_27H = ActorHandler(Actor_27)
	environment:AddActorObject(Actor_27H)

	Actor_28 = ActorObjectInfo(28)
	Actor_28:SetRenderType(1)
	Actor_28.DisplayDesc.ModelId = -1
	Actor_28.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_28.DisplayDesc.Outfit = ""
	Actor_28.DisplayDesc.Weapon = ""
	Actor_28.DisplayDesc.Mode = ""
	Actor_28.DisplayDesc.UseLight = false
	Actor_28.DisplayDesc.CastShadow = false
	Actor_28.DisplayDesc.ColorR = 7.70714e-044
	Actor_28.DisplayDesc.ColorG = 7.84727e-044
	Actor_28.DisplayDesc.ColorB = 7.9874e-044
	Actor_28.DisplayDesc.ColorA = 8.12753e-044
	Actor_28:SetModelState(1)
	Actor_28.PhysicDesc.Pos.X = 539.5
	Actor_28.PhysicDesc.Pos.Y = 33.082
	Actor_28.PhysicDesc.Pos.Z = 471.25
	Actor_28.PhysicDesc.Pos.Rotation = -90
	Actor_28.PhysicDesc.Density = 4.62428e-044
	Actor_28.PhysicDesc.Collidable = true
	Actor_28.PhysicDesc.SizeX = 1.96182e-044
	Actor_28.PhysicDesc.SizeY = 2.10195e-044
	Actor_28.PhysicDesc.SizeZ = 2.52234e-044
	Actor_28.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_28:SetPhysicalActorType(1)
	Actor_28:SetPhysicalShape(5)
	Actor_28.ExtraInfo.Name = ""
	Actor_28.ExtraInfo.NameColorR = 9.94922e-044
	Actor_28.ExtraInfo.NameColorG = 1.00893e-043
	Actor_28.ExtraInfo.NameColorB = 1.02295e-043
	Actor_28H = ActorHandler(Actor_28)
	environment:AddActorObject(Actor_28H)

	Actor_29 = ActorObjectInfo(29)
	Actor_29:SetRenderType(1)
	Actor_29.DisplayDesc.ModelId = -1
	Actor_29.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_29.DisplayDesc.Outfit = ""
	Actor_29.DisplayDesc.Weapon = ""
	Actor_29.DisplayDesc.Mode = ""
	Actor_29.DisplayDesc.UseLight = false
	Actor_29.DisplayDesc.CastShadow = true
	Actor_29.DisplayDesc.ColorR = 1
	Actor_29.DisplayDesc.ColorG = 1
	Actor_29.DisplayDesc.ColorB = 1
	Actor_29.DisplayDesc.ColorA = 1
	Actor_29:SetModelState(1)
	Actor_29.PhysicDesc.Pos.X = 510.5
	Actor_29.PhysicDesc.Pos.Y = 33.9375
	Actor_29.PhysicDesc.Pos.Z = 453.5
	Actor_29.PhysicDesc.Pos.Rotation = 90
	Actor_29.PhysicDesc.Density = 0
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 0
	Actor_29.PhysicDesc.SizeY = 0
	Actor_29.PhysicDesc.SizeZ = 0
	Actor_29.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_29:SetPhysicalActorType(1)
	Actor_29:SetPhysicalShape(5)
	Actor_29.ExtraInfo.Name = ""
	Actor_29.ExtraInfo.NameColorR = 0
	Actor_29.ExtraInfo.NameColorG = 0
	Actor_29.ExtraInfo.NameColorB = 0
	Actor_29H = ActorHandler(Actor_29)
	environment:AddActorObject(Actor_29H)

	Actor_30 = ActorObjectInfo(30)
	Actor_30:SetRenderType(1)
	Actor_30.DisplayDesc.ModelId = 1
	Actor_30.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_30.DisplayDesc.Outfit = ""
	Actor_30.DisplayDesc.Weapon = ""
	Actor_30.DisplayDesc.Mode = ""
	Actor_30.DisplayDesc.UseLight = false
	Actor_30.DisplayDesc.CastShadow = false
	Actor_30.DisplayDesc.ColorR = 1.4013e-045
	Actor_30.DisplayDesc.ColorG = 1.4013e-045
	Actor_30.DisplayDesc.ColorB = 1.4013e-045
	Actor_30.DisplayDesc.ColorA = 1.4013e-045
	Actor_30:SetModelState(1)
	Actor_30.PhysicDesc.Pos.X = 503.859
	Actor_30.PhysicDesc.Pos.Y = 29.7852
	Actor_30.PhysicDesc.Pos.Z = 462
	Actor_30.PhysicDesc.Pos.Rotation = 180
	Actor_30.PhysicDesc.Density = 1.4013e-045
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 1.4013e-045
	Actor_30.PhysicDesc.SizeY = 1.4013e-045
	Actor_30.PhysicDesc.SizeZ = 1.4013e-045
	Actor_30.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_30:SetPhysicalActorType(1)
	Actor_30:SetPhysicalShape(5)
	Actor_30.ExtraInfo.Name = ""
	Actor_30.ExtraInfo.NameColorR = 1.4013e-045
	Actor_30.ExtraInfo.NameColorG = 1.4013e-045
	Actor_30.ExtraInfo.NameColorB = 1.4013e-045
	Actor_30H = ActorHandler(Actor_30)
	environment:AddActorObject(Actor_30H)

	Actor_31 = ActorObjectInfo(31)
	Actor_31:SetRenderType(1)
	Actor_31.DisplayDesc.ModelId = 7
	Actor_31.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_31.DisplayDesc.Outfit = ""
	Actor_31.DisplayDesc.Weapon = ""
	Actor_31.DisplayDesc.Mode = ""
	Actor_31.DisplayDesc.UseLight = false
	Actor_31.DisplayDesc.CastShadow = true
	Actor_31.DisplayDesc.ColorR = 1
	Actor_31.DisplayDesc.ColorG = 9.80909e-045
	Actor_31.DisplayDesc.ColorB = 1
	Actor_31.DisplayDesc.ColorA = 1.76999e-031
	Actor_31:SetModelState(1)
	Actor_31.PhysicDesc.Pos.X = 538.5
	Actor_31.PhysicDesc.Pos.Y = 28.8086
	Actor_31.PhysicDesc.Pos.Z = 449.5
	Actor_31.PhysicDesc.Pos.Rotation = 90
	Actor_31.PhysicDesc.Density = 9.80909e-045
	Actor_31.PhysicDesc.Collidable = true
	Actor_31.PhysicDesc.SizeX = 5.4793e-034
	Actor_31.PhysicDesc.SizeY = 1.71105e-039
	Actor_31.PhysicDesc.SizeZ = 5.60519e-045
	Actor_31.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
	Actor_31:SetPhysicalActorType(1)
	Actor_31:SetPhysicalShape(5)
	Actor_31.ExtraInfo.Name = ""
	Actor_31.ExtraInfo.NameColorR = 0
	Actor_31.ExtraInfo.NameColorG = 9.80909e-045
	Actor_31.ExtraInfo.NameColorB = 0
	Actor_31H = ActorHandler(Actor_31)
	environment:AddActorObject(Actor_31H)

	Actor_32 = ActorObjectInfo(32)
	Actor_32:SetRenderType(1)
	Actor_32.DisplayDesc.ModelId = 0
	Actor_32.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.osgb"
	Actor_32.DisplayDesc.Outfit = ""
	Actor_32.DisplayDesc.Weapon = ""
	Actor_32.DisplayDesc.Mode = ""
	Actor_32.DisplayDesc.UseLight = false
	Actor_32.DisplayDesc.CastShadow = false
	Actor_32.DisplayDesc.ColorR = 1
	Actor_32.DisplayDesc.ColorG = 1
	Actor_32.DisplayDesc.ColorB = 1.3
	Actor_32.DisplayDesc.ColorA = 1
	Actor_32:SetModelState(1)
	Actor_32.PhysicDesc.Pos.X = 525.5
	Actor_32.PhysicDesc.Pos.Y = 33.2031
	Actor_32.PhysicDesc.Pos.Z = 434.5
	Actor_32.PhysicDesc.Pos.Rotation = 90
	Actor_32.PhysicDesc.Density = 0.00784314
	Actor_32.PhysicDesc.Collidable = true
	Actor_32.PhysicDesc.SizeX = 0.45098
	Actor_32.PhysicDesc.SizeY = 0
	Actor_32.PhysicDesc.SizeZ = 0.00784314
	Actor_32.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.phy"
	Actor_32:SetPhysicalActorType(1)
	Actor_32:SetPhysicalShape(5)
	Actor_32.ExtraInfo.Name = ""
	Actor_32.ExtraInfo.NameColorR = 1.875
	Actor_32.ExtraInfo.NameColorG = 9.80909e-045
	Actor_32.ExtraInfo.NameColorB = 0
	Actor_32H = ActorHandler(Actor_32)
	environment:AddActorObject(Actor_32H)

	Actor_33 = ActorObjectInfo(33)
	Actor_33:SetRenderType(1)
	Actor_33.DisplayDesc.ModelId = 0
	Actor_33.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.osgb"
	Actor_33.DisplayDesc.Outfit = ""
	Actor_33.DisplayDesc.Weapon = ""
	Actor_33.DisplayDesc.Mode = ""
	Actor_33.DisplayDesc.UseLight = false
	Actor_33.DisplayDesc.CastShadow = false
	Actor_33.DisplayDesc.ColorR = 1.96182e-044
	Actor_33.DisplayDesc.ColorG = 4.62428e-044
	Actor_33.DisplayDesc.ColorB = 4.76441e-044
	Actor_33.DisplayDesc.ColorA = 6.30584e-044
	Actor_33:SetModelState(1)
	Actor_33.PhysicDesc.Pos.X = 532.5
	Actor_33.PhysicDesc.Pos.Y = 34.1797
	Actor_33.PhysicDesc.Pos.Z = 430.5
	Actor_33.PhysicDesc.Pos.Rotation = 90
	Actor_33.PhysicDesc.Density = 4.06377e-044
	Actor_33.PhysicDesc.Collidable = true
	Actor_33.PhysicDesc.SizeX = 3.64338e-044
	Actor_33.PhysicDesc.SizeY = 3.78351e-044
	Actor_33.PhysicDesc.SizeZ = 5.46506e-044
	Actor_33.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.phy"
	Actor_33:SetPhysicalActorType(1)
	Actor_33:SetPhysicalShape(5)
	Actor_33.ExtraInfo.Name = ""
	Actor_33.ExtraInfo.NameColorR = 3.08286e-044
	Actor_33.ExtraInfo.NameColorG = 2.66247e-044
	Actor_33.ExtraInfo.NameColorB = 2.8026e-044
	Actor_33H = ActorHandler(Actor_33)
	environment:AddActorObject(Actor_33H)

	Actor_34 = ActorObjectInfo(34)
	Actor_34:SetRenderType(1)
	Actor_34.DisplayDesc.ModelId = -1
	Actor_34.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.osgb"
	Actor_34.DisplayDesc.Outfit = ""
	Actor_34.DisplayDesc.Weapon = ""
	Actor_34.DisplayDesc.Mode = ""
	Actor_34.DisplayDesc.UseLight = false
	Actor_34.DisplayDesc.CastShadow = false
	Actor_34.DisplayDesc.ColorR = 7.70714e-044
	Actor_34.DisplayDesc.ColorG = 7.84727e-044
	Actor_34.DisplayDesc.ColorB = 7.9874e-044
	Actor_34.DisplayDesc.ColorA = 8.12753e-044
	Actor_34:SetModelState(1)
	Actor_34.PhysicDesc.Pos.X = 519.5
	Actor_34.PhysicDesc.Pos.Y = 34.1797
	Actor_34.PhysicDesc.Pos.Z = 432.5
	Actor_34.PhysicDesc.Pos.Rotation = 180
	Actor_34.PhysicDesc.Density = 4.62428e-044
	Actor_34.PhysicDesc.Collidable = true
	Actor_34.PhysicDesc.SizeX = 1.96182e-044
	Actor_34.PhysicDesc.SizeY = 2.10195e-044
	Actor_34.PhysicDesc.SizeZ = 2.52234e-044
	Actor_34.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.phy"
	Actor_34:SetPhysicalActorType(1)
	Actor_34:SetPhysicalShape(5)
	Actor_34.ExtraInfo.Name = ""
	Actor_34.ExtraInfo.NameColorR = 9.94922e-044
	Actor_34.ExtraInfo.NameColorG = 1.00893e-043
	Actor_34.ExtraInfo.NameColorB = 1.02295e-043
	Actor_34H = ActorHandler(Actor_34)
	environment:AddActorObject(Actor_34H)

	Actor_35 = ActorObjectInfo(35)
	Actor_35:SetRenderType(1)
	Actor_35.DisplayDesc.ModelId = -1
	Actor_35.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.osgb"
	Actor_35.DisplayDesc.Outfit = ""
	Actor_35.DisplayDesc.Weapon = ""
	Actor_35.DisplayDesc.Mode = ""
	Actor_35.DisplayDesc.UseLight = false
	Actor_35.DisplayDesc.CastShadow = true
	Actor_35.DisplayDesc.ColorR = 1
	Actor_35.DisplayDesc.ColorG = 1
	Actor_35.DisplayDesc.ColorB = 1
	Actor_35.DisplayDesc.ColorA = 1
	Actor_35:SetModelState(1)
	Actor_35.PhysicDesc.Pos.X = 522.5
	Actor_35.PhysicDesc.Pos.Y = 24.9023
	Actor_35.PhysicDesc.Pos.Z = 476.5
	Actor_35.PhysicDesc.Pos.Rotation = 0
	Actor_35.PhysicDesc.Density = 0
	Actor_35.PhysicDesc.Collidable = true
	Actor_35.PhysicDesc.SizeX = 0
	Actor_35.PhysicDesc.SizeY = 0
	Actor_35.PhysicDesc.SizeZ = 0
	Actor_35.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_7.phy"
	Actor_35:SetPhysicalActorType(1)
	Actor_35:SetPhysicalShape(5)
	Actor_35.ExtraInfo.Name = ""
	Actor_35.ExtraInfo.NameColorR = 0
	Actor_35.ExtraInfo.NameColorG = 0
	Actor_35.ExtraInfo.NameColorB = 0
	Actor_35H = ActorHandler(Actor_35)
	environment:AddActorObject(Actor_35H)

	Actor_36 = ActorObjectInfo(36)
	Actor_36:SetRenderType(1)
	Actor_36.DisplayDesc.ModelId = 1
	Actor_36.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_9.osgb"
	Actor_36.DisplayDesc.Outfit = ""
	Actor_36.DisplayDesc.Weapon = ""
	Actor_36.DisplayDesc.Mode = ""
	Actor_36.DisplayDesc.UseLight = false
	Actor_36.DisplayDesc.CastShadow = false
	Actor_36.DisplayDesc.ColorR = 1.4013e-045
	Actor_36.DisplayDesc.ColorG = 1.4013e-045
	Actor_36.DisplayDesc.ColorB = 1.4013e-045
	Actor_36.DisplayDesc.ColorA = 1.4013e-045
	Actor_36:SetModelState(1)
	Actor_36.PhysicDesc.Pos.X = 514.5
	Actor_36.PhysicDesc.Pos.Y = 33.2031
	Actor_36.PhysicDesc.Pos.Z = 462.5
	Actor_36.PhysicDesc.Pos.Rotation = 90
	Actor_36.PhysicDesc.Density = 1.4013e-045
	Actor_36.PhysicDesc.Collidable = true
	Actor_36.PhysicDesc.SizeX = 1.4013e-045
	Actor_36.PhysicDesc.SizeY = 1.4013e-045
	Actor_36.PhysicDesc.SizeZ = 1.4013e-045
	Actor_36.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_9.phy"
	Actor_36:SetPhysicalActorType(1)
	Actor_36:SetPhysicalShape(5)
	Actor_36.ExtraInfo.Name = ""
	Actor_36.ExtraInfo.NameColorR = 1.4013e-045
	Actor_36.ExtraInfo.NameColorG = 1.4013e-045
	Actor_36.ExtraInfo.NameColorB = 1.4013e-045
	Actor_36H = ActorHandler(Actor_36)
	environment:AddActorObject(Actor_36H)

	Actor_37 = ActorObjectInfo(37)
	Actor_37:SetRenderType(1)
	Actor_37.DisplayDesc.ModelId = 0
	Actor_37.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_10.osgb"
	Actor_37.DisplayDesc.Outfit = ""
	Actor_37.DisplayDesc.Weapon = ""
	Actor_37.DisplayDesc.Mode = ""
	Actor_37.DisplayDesc.UseLight = false
	Actor_37.DisplayDesc.CastShadow = false
	Actor_37.DisplayDesc.ColorR = 1
	Actor_37.DisplayDesc.ColorG = 1
	Actor_37.DisplayDesc.ColorB = 1
	Actor_37.DisplayDesc.ColorA = 1
	Actor_37:SetModelState(1)
	Actor_37.PhysicDesc.Pos.X = 518.5
	Actor_37.PhysicDesc.Pos.Y = 33.2031
	Actor_37.PhysicDesc.Pos.Z = 463.5
	Actor_37.PhysicDesc.Pos.Rotation = 90
	Actor_37.PhysicDesc.Density = 0
	Actor_37.PhysicDesc.Collidable = true
	Actor_37.PhysicDesc.SizeX = 0
	Actor_37.PhysicDesc.SizeY = 0
	Actor_37.PhysicDesc.SizeZ = 0
	Actor_37.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_10.phy"
	Actor_37:SetPhysicalActorType(1)
	Actor_37:SetPhysicalShape(5)
	Actor_37.ExtraInfo.Name = ""
	Actor_37.ExtraInfo.NameColorR = 0
	Actor_37.ExtraInfo.NameColorG = 0
	Actor_37.ExtraInfo.NameColorB = 0
	Actor_37H = ActorHandler(Actor_37)
	environment:AddActorObject(Actor_37H)

	Actor_38 = ActorObjectInfo(38)
	Actor_38:SetRenderType(1)
	Actor_38.DisplayDesc.ModelId = 0
	Actor_38.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_11.osgb"
	Actor_38.DisplayDesc.Outfit = ""
	Actor_38.DisplayDesc.Weapon = ""
	Actor_38.DisplayDesc.Mode = ""
	Actor_38.DisplayDesc.UseLight = false
	Actor_38.DisplayDesc.CastShadow = false
	Actor_38.DisplayDesc.ColorR = 1
	Actor_38.DisplayDesc.ColorG = 1
	Actor_38.DisplayDesc.ColorB = 1
	Actor_38.DisplayDesc.ColorA = 1
	Actor_38:SetModelState(1)
	Actor_38.PhysicDesc.Pos.X = 518.5
	Actor_38.PhysicDesc.Pos.Y = 34.1797
	Actor_38.PhysicDesc.Pos.Z = 458.5
	Actor_38.PhysicDesc.Pos.Rotation = 0
	Actor_38.PhysicDesc.Density = 0
	Actor_38.PhysicDesc.Collidable = true
	Actor_38.PhysicDesc.SizeX = 0
	Actor_38.PhysicDesc.SizeY = 0
	Actor_38.PhysicDesc.SizeZ = 0
	Actor_38.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_11.phy"
	Actor_38:SetPhysicalActorType(1)
	Actor_38:SetPhysicalShape(5)
	Actor_38.ExtraInfo.Name = ""
	Actor_38.ExtraInfo.NameColorR = 0
	Actor_38.ExtraInfo.NameColorG = 0
	Actor_38.ExtraInfo.NameColorB = 0
	Actor_38H = ActorHandler(Actor_38)
	environment:AddActorObject(Actor_38H)

	Actor_39 = ActorObjectInfo(39)
	Actor_39:SetRenderType(1)
	Actor_39.DisplayDesc.ModelId = 0
	Actor_39.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_39.DisplayDesc.Outfit = ""
	Actor_39.DisplayDesc.Weapon = ""
	Actor_39.DisplayDesc.Mode = ""
	Actor_39.DisplayDesc.UseLight = false
	Actor_39.DisplayDesc.CastShadow = false
	Actor_39.DisplayDesc.ColorR = 1
	Actor_39.DisplayDesc.ColorG = 1
	Actor_39.DisplayDesc.ColorB = 1
	Actor_39.DisplayDesc.ColorA = 1
	Actor_39:SetModelState(1)
	Actor_39.PhysicDesc.Pos.X = 514.5
	Actor_39.PhysicDesc.Pos.Y = 33.9336
	Actor_39.PhysicDesc.Pos.Z = 456.5
	Actor_39.PhysicDesc.Pos.Rotation = 90
	Actor_39.PhysicDesc.Density = 0
	Actor_39.PhysicDesc.Collidable = true
	Actor_39.PhysicDesc.SizeX = 0
	Actor_39.PhysicDesc.SizeY = 0
	Actor_39.PhysicDesc.SizeZ = 0
	Actor_39.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
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
	Actor_40.DisplayDesc.ModelId = 0
	Actor_40.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_12.osgb"
	Actor_40.DisplayDesc.Outfit = ""
	Actor_40.DisplayDesc.Weapon = ""
	Actor_40.DisplayDesc.Mode = ""
	Actor_40.DisplayDesc.UseLight = false
	Actor_40.DisplayDesc.CastShadow = false
	Actor_40.DisplayDesc.ColorR = 1
	Actor_40.DisplayDesc.ColorG = 1
	Actor_40.DisplayDesc.ColorB = 1
	Actor_40.DisplayDesc.ColorA = 1
	Actor_40:SetModelState(1)
	Actor_40.PhysicDesc.Pos.X = 514.5
	Actor_40.PhysicDesc.Pos.Y = 33.2031
	Actor_40.PhysicDesc.Pos.Z = 462.5
	Actor_40.PhysicDesc.Pos.Rotation = 90
	Actor_40.PhysicDesc.Density = 0
	Actor_40.PhysicDesc.Collidable = true
	Actor_40.PhysicDesc.SizeX = 0
	Actor_40.PhysicDesc.SizeY = 0
	Actor_40.PhysicDesc.SizeZ = 0
	Actor_40.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_12.phy"
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
	Actor_41.DisplayDesc.ModelId = 0
	Actor_41.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_13.osgb"
	Actor_41.DisplayDesc.Outfit = ""
	Actor_41.DisplayDesc.Weapon = ""
	Actor_41.DisplayDesc.Mode = ""
	Actor_41.DisplayDesc.UseLight = false
	Actor_41.DisplayDesc.CastShadow = false
	Actor_41.DisplayDesc.ColorR = 1
	Actor_41.DisplayDesc.ColorG = 1
	Actor_41.DisplayDesc.ColorB = 1
	Actor_41.DisplayDesc.ColorA = 1
	Actor_41:SetModelState(1)
	Actor_41.PhysicDesc.Pos.X = 514.5
	Actor_41.PhysicDesc.Pos.Y = 33.2031
	Actor_41.PhysicDesc.Pos.Z = 462.5
	Actor_41.PhysicDesc.Pos.Rotation = 90
	Actor_41.PhysicDesc.Density = 0
	Actor_41.PhysicDesc.Collidable = true
	Actor_41.PhysicDesc.SizeX = 0
	Actor_41.PhysicDesc.SizeY = 0
	Actor_41.PhysicDesc.SizeZ = 0
	Actor_41.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_13.phy"
	Actor_41:SetPhysicalActorType(1)
	Actor_41:SetPhysicalShape(5)
	Actor_41.ExtraInfo.Name = ""
	Actor_41.ExtraInfo.NameColorR = 0
	Actor_41.ExtraInfo.NameColorG = 0
	Actor_41.ExtraInfo.NameColorB = 0
	Actor_41H = ActorHandler(Actor_41)
	environment:AddActorObject(Actor_41H)

	Actor_42 = ActorObjectInfo(42)
	Actor_42:SetRenderType(1)
	Actor_42.DisplayDesc.ModelId = 0
	Actor_42.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_14.osgb"
	Actor_42.DisplayDesc.Outfit = ""
	Actor_42.DisplayDesc.Weapon = ""
	Actor_42.DisplayDesc.Mode = ""
	Actor_42.DisplayDesc.UseLight = false
	Actor_42.DisplayDesc.CastShadow = false
	Actor_42.DisplayDesc.ColorR = 1
	Actor_42.DisplayDesc.ColorG = 1
	Actor_42.DisplayDesc.ColorB = 1
	Actor_42.DisplayDesc.ColorA = 1
	Actor_42:SetModelState(1)
	Actor_42.PhysicDesc.Pos.X = 507.5
	Actor_42.PhysicDesc.Pos.Y = 29.2969
	Actor_42.PhysicDesc.Pos.Z = 479.25
	Actor_42.PhysicDesc.Pos.Rotation = 90
	Actor_42.PhysicDesc.Density = 0
	Actor_42.PhysicDesc.Collidable = true
	Actor_42.PhysicDesc.SizeX = 0
	Actor_42.PhysicDesc.SizeY = 0
	Actor_42.PhysicDesc.SizeZ = 0
	Actor_42.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_14.phy"
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
	Actor_43.DisplayDesc.ModelId = 0
	Actor_43.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_43.DisplayDesc.Outfit = ""
	Actor_43.DisplayDesc.Weapon = ""
	Actor_43.DisplayDesc.Mode = ""
	Actor_43.DisplayDesc.UseLight = false
	Actor_43.DisplayDesc.CastShadow = false
	Actor_43.DisplayDesc.ColorR = 1
	Actor_43.DisplayDesc.ColorG = 1
	Actor_43.DisplayDesc.ColorB = 1
	Actor_43.DisplayDesc.ColorA = 1
	Actor_43:SetModelState(1)
	Actor_43.PhysicDesc.Pos.X = 575.5
	Actor_43.PhysicDesc.Pos.Y = 33.2031
	Actor_43.PhysicDesc.Pos.Z = 431.5
	Actor_43.PhysicDesc.Pos.Rotation = 0
	Actor_43.PhysicDesc.Density = 0
	Actor_43.PhysicDesc.Collidable = true
	Actor_43.PhysicDesc.SizeX = 0
	Actor_43.PhysicDesc.SizeY = 0
	Actor_43.PhysicDesc.SizeZ = 0
	Actor_43.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_43:SetPhysicalActorType(1)
	Actor_43:SetPhysicalShape(5)
	Actor_43.ExtraInfo.Name = ""
	Actor_43.ExtraInfo.NameColorR = 0
	Actor_43.ExtraInfo.NameColorG = 0
	Actor_43.ExtraInfo.NameColorB = 0
	Actor_43H = ActorHandler(Actor_43)
	environment:AddActorObject(Actor_43H)

	Actor_44 = ActorObjectInfo(44)
	Actor_44:SetRenderType(1)
	Actor_44.DisplayDesc.ModelId = 0
	Actor_44.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_44.DisplayDesc.Outfit = ""
	Actor_44.DisplayDesc.Weapon = ""
	Actor_44.DisplayDesc.Mode = ""
	Actor_44.DisplayDesc.UseLight = false
	Actor_44.DisplayDesc.CastShadow = false
	Actor_44.DisplayDesc.ColorR = 1
	Actor_44.DisplayDesc.ColorG = 1
	Actor_44.DisplayDesc.ColorB = 1
	Actor_44.DisplayDesc.ColorA = 1
	Actor_44:SetModelState(1)
	Actor_44.PhysicDesc.Pos.X = 578.5
	Actor_44.PhysicDesc.Pos.Y = 33.2031
	Actor_44.PhysicDesc.Pos.Z = 433.5
	Actor_44.PhysicDesc.Pos.Rotation = 90
	Actor_44.PhysicDesc.Density = 0
	Actor_44.PhysicDesc.Collidable = true
	Actor_44.PhysicDesc.SizeX = 0
	Actor_44.PhysicDesc.SizeY = 0
	Actor_44.PhysicDesc.SizeZ = 0
	Actor_44.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
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
	Actor_45.DisplayDesc.ModelId = 0
	Actor_45.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_45.DisplayDesc.Outfit = ""
	Actor_45.DisplayDesc.Weapon = ""
	Actor_45.DisplayDesc.Mode = ""
	Actor_45.DisplayDesc.UseLight = false
	Actor_45.DisplayDesc.CastShadow = false
	Actor_45.DisplayDesc.ColorR = 1
	Actor_45.DisplayDesc.ColorG = 1
	Actor_45.DisplayDesc.ColorB = 1
	Actor_45.DisplayDesc.ColorA = 1
	Actor_45:SetModelState(1)
	Actor_45.PhysicDesc.Pos.X = 574.5
	Actor_45.PhysicDesc.Pos.Y = 33.2031
	Actor_45.PhysicDesc.Pos.Z = 438.5
	Actor_45.PhysicDesc.Pos.Rotation = 90
	Actor_45.PhysicDesc.Density = 0
	Actor_45.PhysicDesc.Collidable = true
	Actor_45.PhysicDesc.SizeX = 0
	Actor_45.PhysicDesc.SizeY = 0
	Actor_45.PhysicDesc.SizeZ = 0
	Actor_45.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_45:SetPhysicalActorType(1)
	Actor_45:SetPhysicalShape(5)
	Actor_45.ExtraInfo.Name = ""
	Actor_45.ExtraInfo.NameColorR = 0
	Actor_45.ExtraInfo.NameColorG = 0
	Actor_45.ExtraInfo.NameColorB = 0
	Actor_45H = ActorHandler(Actor_45)
	environment:AddActorObject(Actor_45H)

	Actor_46 = ActorObjectInfo(46)
	Actor_46:SetRenderType(1)
	Actor_46.DisplayDesc.ModelId = 0
	Actor_46.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_46.DisplayDesc.Outfit = ""
	Actor_46.DisplayDesc.Weapon = ""
	Actor_46.DisplayDesc.Mode = ""
	Actor_46.DisplayDesc.UseLight = false
	Actor_46.DisplayDesc.CastShadow = false
	Actor_46.DisplayDesc.ColorR = 1
	Actor_46.DisplayDesc.ColorG = 1
	Actor_46.DisplayDesc.ColorB = 1
	Actor_46.DisplayDesc.ColorA = 1
	Actor_46:SetModelState(1)
	Actor_46.PhysicDesc.Pos.X = 547.5
	Actor_46.PhysicDesc.Pos.Y = 32.7148
	Actor_46.PhysicDesc.Pos.Z = 462.5
	Actor_46.PhysicDesc.Pos.Rotation = 180
	Actor_46.PhysicDesc.Density = 0
	Actor_46.PhysicDesc.Collidable = true
	Actor_46.PhysicDesc.SizeX = 0
	Actor_46.PhysicDesc.SizeY = 0
	Actor_46.PhysicDesc.SizeZ = 0
	Actor_46.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
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
	Actor_47.DisplayDesc.ModelId = 0
	Actor_47.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_47.DisplayDesc.Outfit = ""
	Actor_47.DisplayDesc.Weapon = ""
	Actor_47.DisplayDesc.Mode = ""
	Actor_47.DisplayDesc.UseLight = false
	Actor_47.DisplayDesc.CastShadow = false
	Actor_47.DisplayDesc.ColorR = 1
	Actor_47.DisplayDesc.ColorG = 1
	Actor_47.DisplayDesc.ColorB = 1
	Actor_47.DisplayDesc.ColorA = 1
	Actor_47:SetModelState(1)
	Actor_47.PhysicDesc.Pos.X = 563.5
	Actor_47.PhysicDesc.Pos.Y = 30.5195
	Actor_47.PhysicDesc.Pos.Z = 454.5
	Actor_47.PhysicDesc.Pos.Rotation = 90
	Actor_47.PhysicDesc.Density = 0
	Actor_47.PhysicDesc.Collidable = true
	Actor_47.PhysicDesc.SizeX = 0
	Actor_47.PhysicDesc.SizeY = 0
	Actor_47.PhysicDesc.SizeZ = 0
	Actor_47.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
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
	Actor_48.DisplayDesc.ModelId = 0
	Actor_48.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_48.DisplayDesc.Outfit = ""
	Actor_48.DisplayDesc.Weapon = ""
	Actor_48.DisplayDesc.Mode = ""
	Actor_48.DisplayDesc.UseLight = false
	Actor_48.DisplayDesc.CastShadow = false
	Actor_48.DisplayDesc.ColorR = 1
	Actor_48.DisplayDesc.ColorG = 1
	Actor_48.DisplayDesc.ColorB = 1
	Actor_48.DisplayDesc.ColorA = 1
	Actor_48:SetModelState(1)
	Actor_48.PhysicDesc.Pos.X = 554.5
	Actor_48.PhysicDesc.Pos.Y = 26.3672
	Actor_48.PhysicDesc.Pos.Z = 467.5
	Actor_48.PhysicDesc.Pos.Rotation = 90
	Actor_48.PhysicDesc.Density = 0
	Actor_48.PhysicDesc.Collidable = true
	Actor_48.PhysicDesc.SizeX = 0
	Actor_48.PhysicDesc.SizeY = 0
	Actor_48.PhysicDesc.SizeZ = 0
	Actor_48.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_48:SetPhysicalActorType(1)
	Actor_48:SetPhysicalShape(5)
	Actor_48.ExtraInfo.Name = ""
	Actor_48.ExtraInfo.NameColorR = 0
	Actor_48.ExtraInfo.NameColorG = 0
	Actor_48.ExtraInfo.NameColorB = 0
	Actor_48H = ActorHandler(Actor_48)
	environment:AddActorObject(Actor_48H)

	Actor_49 = ActorObjectInfo(49)
	Actor_49:SetRenderType(1)
	Actor_49.DisplayDesc.ModelId = 0
	Actor_49.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_49.DisplayDesc.Outfit = ""
	Actor_49.DisplayDesc.Weapon = ""
	Actor_49.DisplayDesc.Mode = ""
	Actor_49.DisplayDesc.UseLight = false
	Actor_49.DisplayDesc.CastShadow = false
	Actor_49.DisplayDesc.ColorR = 1
	Actor_49.DisplayDesc.ColorG = 1
	Actor_49.DisplayDesc.ColorB = 1
	Actor_49.DisplayDesc.ColorA = 1
	Actor_49:SetModelState(1)
	Actor_49.PhysicDesc.Pos.X = 551.5
	Actor_49.PhysicDesc.Pos.Y = 32.2266
	Actor_49.PhysicDesc.Pos.Z = 441.5
	Actor_49.PhysicDesc.Pos.Rotation = 90
	Actor_49.PhysicDesc.Density = 0
	Actor_49.PhysicDesc.Collidable = true
	Actor_49.PhysicDesc.SizeX = 0
	Actor_49.PhysicDesc.SizeY = 0
	Actor_49.PhysicDesc.SizeZ = 0
	Actor_49.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_49:SetPhysicalActorType(1)
	Actor_49:SetPhysicalShape(5)
	Actor_49.ExtraInfo.Name = ""
	Actor_49.ExtraInfo.NameColorR = 0
	Actor_49.ExtraInfo.NameColorG = 0
	Actor_49.ExtraInfo.NameColorB = 0
	Actor_49H = ActorHandler(Actor_49)
	environment:AddActorObject(Actor_49H)

	Actor_50 = ActorObjectInfo(50)
	Actor_50:SetRenderType(1)
	Actor_50.DisplayDesc.ModelId = 0
	Actor_50.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_15.osgb"
	Actor_50.DisplayDesc.Outfit = ""
	Actor_50.DisplayDesc.Weapon = ""
	Actor_50.DisplayDesc.Mode = ""
	Actor_50.DisplayDesc.UseLight = false
	Actor_50.DisplayDesc.CastShadow = false
	Actor_50.DisplayDesc.ColorR = 1
	Actor_50.DisplayDesc.ColorG = 1
	Actor_50.DisplayDesc.ColorB = 1
	Actor_50.DisplayDesc.ColorA = 1
	Actor_50:SetModelState(1)
	Actor_50.PhysicDesc.Pos.X = 564.25
	Actor_50.PhysicDesc.Pos.Y = 33.2031
	Actor_50.PhysicDesc.Pos.Z = 435
	Actor_50.PhysicDesc.Pos.Rotation = 180
	Actor_50.PhysicDesc.Density = 0
	Actor_50.PhysicDesc.Collidable = true
	Actor_50.PhysicDesc.SizeX = 0
	Actor_50.PhysicDesc.SizeY = 0
	Actor_50.PhysicDesc.SizeZ = 0
	Actor_50.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_15.phy"
	Actor_50:SetPhysicalActorType(1)
	Actor_50:SetPhysicalShape(5)
	Actor_50.ExtraInfo.Name = ""
	Actor_50.ExtraInfo.NameColorR = 0
	Actor_50.ExtraInfo.NameColorG = 0
	Actor_50.ExtraInfo.NameColorB = 0
	Actor_50H = ActorHandler(Actor_50)
	environment:AddActorObject(Actor_50H)

	Actor_51 = ActorObjectInfo(51)
	Actor_51:SetRenderType(1)
	Actor_51.DisplayDesc.ModelId = 0
	Actor_51.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_16.osgb"
	Actor_51.DisplayDesc.Outfit = ""
	Actor_51.DisplayDesc.Weapon = ""
	Actor_51.DisplayDesc.Mode = ""
	Actor_51.DisplayDesc.UseLight = false
	Actor_51.DisplayDesc.CastShadow = false
	Actor_51.DisplayDesc.ColorR = 1
	Actor_51.DisplayDesc.ColorG = 1
	Actor_51.DisplayDesc.ColorB = 1
	Actor_51.DisplayDesc.ColorA = 1
	Actor_51:SetModelState(1)
	Actor_51.PhysicDesc.Pos.X = 564.25
	Actor_51.PhysicDesc.Pos.Y = 33.2031
	Actor_51.PhysicDesc.Pos.Z = 435
	Actor_51.PhysicDesc.Pos.Rotation = 180
	Actor_51.PhysicDesc.Density = 0
	Actor_51.PhysicDesc.Collidable = true
	Actor_51.PhysicDesc.SizeX = 0
	Actor_51.PhysicDesc.SizeY = 0
	Actor_51.PhysicDesc.SizeZ = 0
	Actor_51.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_16.phy"
	Actor_51:SetPhysicalActorType(1)
	Actor_51:SetPhysicalShape(5)
	Actor_51.ExtraInfo.Name = ""
	Actor_51.ExtraInfo.NameColorR = 0
	Actor_51.ExtraInfo.NameColorG = 0
	Actor_51.ExtraInfo.NameColorB = 0
	Actor_51H = ActorHandler(Actor_51)
	environment:AddActorObject(Actor_51H)

	Actor_52 = ActorObjectInfo(52)
	Actor_52:SetRenderType(1)
	Actor_52.DisplayDesc.ModelId = 0
	Actor_52.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_17.osgb"
	Actor_52.DisplayDesc.Outfit = ""
	Actor_52.DisplayDesc.Weapon = ""
	Actor_52.DisplayDesc.Mode = ""
	Actor_52.DisplayDesc.UseLight = false
	Actor_52.DisplayDesc.CastShadow = false
	Actor_52.DisplayDesc.ColorR = 1
	Actor_52.DisplayDesc.ColorG = 1
	Actor_52.DisplayDesc.ColorB = 1.3
	Actor_52.DisplayDesc.ColorA = 1
	Actor_52:SetModelState(1)
	Actor_52.PhysicDesc.Pos.X = 564.25
	Actor_52.PhysicDesc.Pos.Y = 33.2031
	Actor_52.PhysicDesc.Pos.Z = 435
	Actor_52.PhysicDesc.Pos.Rotation = 180
	Actor_52.PhysicDesc.Density = 0.00784314
	Actor_52.PhysicDesc.Collidable = true
	Actor_52.PhysicDesc.SizeX = 0.45098
	Actor_52.PhysicDesc.SizeY = 0
	Actor_52.PhysicDesc.SizeZ = 0.00784314
	Actor_52.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_17.phy"
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
	Actor_53.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_18.osgb"
	Actor_53.DisplayDesc.Outfit = ""
	Actor_53.DisplayDesc.Weapon = ""
	Actor_53.DisplayDesc.Mode = ""
	Actor_53.DisplayDesc.UseLight = false
	Actor_53.DisplayDesc.CastShadow = false
	Actor_53.DisplayDesc.ColorR = 1
	Actor_53.DisplayDesc.ColorG = 1
	Actor_53.DisplayDesc.ColorB = 1
	Actor_53.DisplayDesc.ColorA = 1
	Actor_53:SetModelState(1)
	Actor_53.PhysicDesc.Pos.X = 564.25
	Actor_53.PhysicDesc.Pos.Y = 33.2031
	Actor_53.PhysicDesc.Pos.Z = 435
	Actor_53.PhysicDesc.Pos.Rotation = 180
	Actor_53.PhysicDesc.Density = 0
	Actor_53.PhysicDesc.Collidable = true
	Actor_53.PhysicDesc.SizeX = 0
	Actor_53.PhysicDesc.SizeY = 0
	Actor_53.PhysicDesc.SizeZ = 0
	Actor_53.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_18.phy"
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
	Actor_54.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_19.osgb"
	Actor_54.DisplayDesc.Outfit = ""
	Actor_54.DisplayDesc.Weapon = ""
	Actor_54.DisplayDesc.Mode = ""
	Actor_54.DisplayDesc.UseLight = false
	Actor_54.DisplayDesc.CastShadow = false
	Actor_54.DisplayDesc.ColorR = 1
	Actor_54.DisplayDesc.ColorG = 1
	Actor_54.DisplayDesc.ColorB = 1
	Actor_54.DisplayDesc.ColorA = 1
	Actor_54:SetModelState(1)
	Actor_54.PhysicDesc.Pos.X = 564.25
	Actor_54.PhysicDesc.Pos.Y = 33.2031
	Actor_54.PhysicDesc.Pos.Z = 435
	Actor_54.PhysicDesc.Pos.Rotation = 180
	Actor_54.PhysicDesc.Density = 0
	Actor_54.PhysicDesc.Collidable = true
	Actor_54.PhysicDesc.SizeX = 0
	Actor_54.PhysicDesc.SizeY = 0
	Actor_54.PhysicDesc.SizeZ = 0
	Actor_54.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_19.phy"
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
	Actor_55.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_20.osgb"
	Actor_55.DisplayDesc.Outfit = ""
	Actor_55.DisplayDesc.Weapon = ""
	Actor_55.DisplayDesc.Mode = ""
	Actor_55.DisplayDesc.UseLight = false
	Actor_55.DisplayDesc.CastShadow = false
	Actor_55.DisplayDesc.ColorR = 1
	Actor_55.DisplayDesc.ColorG = 1
	Actor_55.DisplayDesc.ColorB = 1
	Actor_55.DisplayDesc.ColorA = 1
	Actor_55:SetModelState(1)
	Actor_55.PhysicDesc.Pos.X = 560.5
	Actor_55.PhysicDesc.Pos.Y = 33.2031
	Actor_55.PhysicDesc.Pos.Z = 448.5
	Actor_55.PhysicDesc.Pos.Rotation = -90
	Actor_55.PhysicDesc.Density = 0
	Actor_55.PhysicDesc.Collidable = true
	Actor_55.PhysicDesc.SizeX = 0
	Actor_55.PhysicDesc.SizeY = 0
	Actor_55.PhysicDesc.SizeZ = 0
	Actor_55.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_20.phy"
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
	Actor_56.DisplayDesc.ModelId = 0
	Actor_56.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_15.osgb"
	Actor_56.DisplayDesc.Outfit = ""
	Actor_56.DisplayDesc.Weapon = ""
	Actor_56.DisplayDesc.Mode = ""
	Actor_56.DisplayDesc.UseLight = false
	Actor_56.DisplayDesc.CastShadow = false
	Actor_56.DisplayDesc.ColorR = 1
	Actor_56.DisplayDesc.ColorG = 1
	Actor_56.DisplayDesc.ColorB = 1
	Actor_56.DisplayDesc.ColorA = 1
	Actor_56:SetModelState(1)
	Actor_56.PhysicDesc.Pos.X = 564.428
	Actor_56.PhysicDesc.Pos.Y = 33.2031
	Actor_56.PhysicDesc.Pos.Z = 447
	Actor_56.PhysicDesc.Pos.Rotation = 0
	Actor_56.PhysicDesc.Density = 0
	Actor_56.PhysicDesc.Collidable = true
	Actor_56.PhysicDesc.SizeX = 0
	Actor_56.PhysicDesc.SizeY = 0
	Actor_56.PhysicDesc.SizeZ = 0
	Actor_56.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_15.phy"
	Actor_56:SetPhysicalActorType(1)
	Actor_56:SetPhysicalShape(5)
	Actor_56.ExtraInfo.Name = ""
	Actor_56.ExtraInfo.NameColorR = 0
	Actor_56.ExtraInfo.NameColorG = 0
	Actor_56.ExtraInfo.NameColorB = 0
	Actor_56H = ActorHandler(Actor_56)
	environment:AddActorObject(Actor_56H)

	Actor_57 = ActorObjectInfo(57)
	Actor_57:SetRenderType(1)
	Actor_57.DisplayDesc.ModelId = 0
	Actor_57.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_18.osgb"
	Actor_57.DisplayDesc.Outfit = ""
	Actor_57.DisplayDesc.Weapon = ""
	Actor_57.DisplayDesc.Mode = ""
	Actor_57.DisplayDesc.UseLight = false
	Actor_57.DisplayDesc.CastShadow = false
	Actor_57.DisplayDesc.ColorR = 1
	Actor_57.DisplayDesc.ColorG = 1
	Actor_57.DisplayDesc.ColorB = 1
	Actor_57.DisplayDesc.ColorA = 1
	Actor_57:SetModelState(1)
	Actor_57.PhysicDesc.Pos.X = 564.428
	Actor_57.PhysicDesc.Pos.Y = 33.2031
	Actor_57.PhysicDesc.Pos.Z = 447
	Actor_57.PhysicDesc.Pos.Rotation = 0
	Actor_57.PhysicDesc.Density = 0
	Actor_57.PhysicDesc.Collidable = true
	Actor_57.PhysicDesc.SizeX = 0
	Actor_57.PhysicDesc.SizeY = 0
	Actor_57.PhysicDesc.SizeZ = 0
	Actor_57.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_18.phy"
	Actor_57:SetPhysicalActorType(1)
	Actor_57:SetPhysicalShape(5)
	Actor_57.ExtraInfo.Name = ""
	Actor_57.ExtraInfo.NameColorR = 0
	Actor_57.ExtraInfo.NameColorG = 0
	Actor_57.ExtraInfo.NameColorB = 0
	Actor_57H = ActorHandler(Actor_57)
	environment:AddActorObject(Actor_57H)

	Actor_58 = ActorObjectInfo(58)
	Actor_58:SetRenderType(1)
	Actor_58.DisplayDesc.ModelId = 0
	Actor_58.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_19.osgb"
	Actor_58.DisplayDesc.Outfit = ""
	Actor_58.DisplayDesc.Weapon = ""
	Actor_58.DisplayDesc.Mode = ""
	Actor_58.DisplayDesc.UseLight = false
	Actor_58.DisplayDesc.CastShadow = false
	Actor_58.DisplayDesc.ColorR = 1
	Actor_58.DisplayDesc.ColorG = 1
	Actor_58.DisplayDesc.ColorB = 1
	Actor_58.DisplayDesc.ColorA = 1
	Actor_58:SetModelState(1)
	Actor_58.PhysicDesc.Pos.X = 564.428
	Actor_58.PhysicDesc.Pos.Y = 33.2031
	Actor_58.PhysicDesc.Pos.Z = 447
	Actor_58.PhysicDesc.Pos.Rotation = 0
	Actor_58.PhysicDesc.Density = 0
	Actor_58.PhysicDesc.Collidable = true
	Actor_58.PhysicDesc.SizeX = 0
	Actor_58.PhysicDesc.SizeY = 0
	Actor_58.PhysicDesc.SizeZ = 0
	Actor_58.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_19.phy"
	Actor_58:SetPhysicalActorType(1)
	Actor_58:SetPhysicalShape(5)
	Actor_58.ExtraInfo.Name = ""
	Actor_58.ExtraInfo.NameColorR = 0
	Actor_58.ExtraInfo.NameColorG = 0
	Actor_58.ExtraInfo.NameColorB = 0
	Actor_58H = ActorHandler(Actor_58)
	environment:AddActorObject(Actor_58H)

	Actor_59 = ActorObjectInfo(59)
	Actor_59:SetRenderType(1)
	Actor_59.DisplayDesc.ModelId = 0
	Actor_59.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_16.osgb"
	Actor_59.DisplayDesc.Outfit = ""
	Actor_59.DisplayDesc.Weapon = ""
	Actor_59.DisplayDesc.Mode = ""
	Actor_59.DisplayDesc.UseLight = false
	Actor_59.DisplayDesc.CastShadow = false
	Actor_59.DisplayDesc.ColorR = 1
	Actor_59.DisplayDesc.ColorG = 1
	Actor_59.DisplayDesc.ColorB = 1
	Actor_59.DisplayDesc.ColorA = 1
	Actor_59:SetModelState(1)
	Actor_59.PhysicDesc.Pos.X = 564.428
	Actor_59.PhysicDesc.Pos.Y = 33.2031
	Actor_59.PhysicDesc.Pos.Z = 447
	Actor_59.PhysicDesc.Pos.Rotation = 0
	Actor_59.PhysicDesc.Density = 0
	Actor_59.PhysicDesc.Collidable = true
	Actor_59.PhysicDesc.SizeX = 0
	Actor_59.PhysicDesc.SizeY = 0
	Actor_59.PhysicDesc.SizeZ = 0
	Actor_59.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_16.phy"
	Actor_59:SetPhysicalActorType(1)
	Actor_59:SetPhysicalShape(5)
	Actor_59.ExtraInfo.Name = ""
	Actor_59.ExtraInfo.NameColorR = 0
	Actor_59.ExtraInfo.NameColorG = 0
	Actor_59.ExtraInfo.NameColorB = 0
	Actor_59H = ActorHandler(Actor_59)
	environment:AddActorObject(Actor_59H)

	Actor_60 = ActorObjectInfo(60)
	Actor_60:SetRenderType(1)
	Actor_60.DisplayDesc.ModelId = 0
	Actor_60.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_17.osgb"
	Actor_60.DisplayDesc.Outfit = ""
	Actor_60.DisplayDesc.Weapon = ""
	Actor_60.DisplayDesc.Mode = ""
	Actor_60.DisplayDesc.UseLight = false
	Actor_60.DisplayDesc.CastShadow = false
	Actor_60.DisplayDesc.ColorR = 1
	Actor_60.DisplayDesc.ColorG = 1
	Actor_60.DisplayDesc.ColorB = 1
	Actor_60.DisplayDesc.ColorA = 1
	Actor_60:SetModelState(1)
	Actor_60.PhysicDesc.Pos.X = 564.428
	Actor_60.PhysicDesc.Pos.Y = 33.2031
	Actor_60.PhysicDesc.Pos.Z = 447
	Actor_60.PhysicDesc.Pos.Rotation = 0
	Actor_60.PhysicDesc.Density = 0
	Actor_60.PhysicDesc.Collidable = true
	Actor_60.PhysicDesc.SizeX = 0
	Actor_60.PhysicDesc.SizeY = 0
	Actor_60.PhysicDesc.SizeZ = 0
	Actor_60.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_17.phy"
	Actor_60:SetPhysicalActorType(1)
	Actor_60:SetPhysicalShape(5)
	Actor_60.ExtraInfo.Name = ""
	Actor_60.ExtraInfo.NameColorR = 0
	Actor_60.ExtraInfo.NameColorG = 0
	Actor_60.ExtraInfo.NameColorB = 0
	Actor_60H = ActorHandler(Actor_60)
	environment:AddActorObject(Actor_60H)

	Actor_61 = ActorObjectInfo(61)
	Actor_61:SetRenderType(1)
	Actor_61.DisplayDesc.ModelId = 0
	Actor_61.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_21.osgb"
	Actor_61.DisplayDesc.Outfit = ""
	Actor_61.DisplayDesc.Weapon = ""
	Actor_61.DisplayDesc.Mode = ""
	Actor_61.DisplayDesc.UseLight = false
	Actor_61.DisplayDesc.CastShadow = false
	Actor_61.DisplayDesc.ColorR = 1
	Actor_61.DisplayDesc.ColorG = 1
	Actor_61.DisplayDesc.ColorB = 1
	Actor_61.DisplayDesc.ColorA = 1
	Actor_61:SetModelState(1)
	Actor_61.PhysicDesc.Pos.X = 560.5
	Actor_61.PhysicDesc.Pos.Y = 33.2031
	Actor_61.PhysicDesc.Pos.Z = 448.5
	Actor_61.PhysicDesc.Pos.Rotation = -90
	Actor_61.PhysicDesc.Density = 0
	Actor_61.PhysicDesc.Collidable = true
	Actor_61.PhysicDesc.SizeX = 0
	Actor_61.PhysicDesc.SizeY = 0
	Actor_61.PhysicDesc.SizeZ = 0
	Actor_61.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_21.phy"
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
	Actor_62.DisplayDesc.ModelId = 0
	Actor_62.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_22.osgb"
	Actor_62.DisplayDesc.Outfit = ""
	Actor_62.DisplayDesc.Weapon = ""
	Actor_62.DisplayDesc.Mode = ""
	Actor_62.DisplayDesc.UseLight = false
	Actor_62.DisplayDesc.CastShadow = false
	Actor_62.DisplayDesc.ColorR = 1
	Actor_62.DisplayDesc.ColorG = 1
	Actor_62.DisplayDesc.ColorB = 1
	Actor_62.DisplayDesc.ColorA = 1
	Actor_62:SetModelState(1)
	Actor_62.PhysicDesc.Pos.X = 382.25
	Actor_62.PhysicDesc.Pos.Y = 28.3203
	Actor_62.PhysicDesc.Pos.Z = 513.625
	Actor_62.PhysicDesc.Pos.Rotation = -90
	Actor_62.PhysicDesc.Density = 0
	Actor_62.PhysicDesc.Collidable = true
	Actor_62.PhysicDesc.SizeX = 0
	Actor_62.PhysicDesc.SizeY = 0
	Actor_62.PhysicDesc.SizeZ = 0
	Actor_62.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_22.phy"
	Actor_62:SetPhysicalActorType(1)
	Actor_62:SetPhysicalShape(5)
	Actor_62.ExtraInfo.Name = ""
	Actor_62.ExtraInfo.NameColorR = 0
	Actor_62.ExtraInfo.NameColorG = 0
	Actor_62.ExtraInfo.NameColorB = 0
	Actor_62H = ActorHandler(Actor_62)
	environment:AddActorObject(Actor_62H)

	Actor_63 = ActorObjectInfo(63)
	Actor_63:SetRenderType(1)
	Actor_63.DisplayDesc.ModelId = 0
	Actor_63.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_23.osgb"
	Actor_63.DisplayDesc.Outfit = ""
	Actor_63.DisplayDesc.Weapon = ""
	Actor_63.DisplayDesc.Mode = ""
	Actor_63.DisplayDesc.UseLight = false
	Actor_63.DisplayDesc.CastShadow = false
	Actor_63.DisplayDesc.ColorR = 1
	Actor_63.DisplayDesc.ColorG = 1
	Actor_63.DisplayDesc.ColorB = 1
	Actor_63.DisplayDesc.ColorA = 1
	Actor_63:SetModelState(1)
	Actor_63.PhysicDesc.Pos.X = 383.5
	Actor_63.PhysicDesc.Pos.Y = 18.0664
	Actor_63.PhysicDesc.Pos.Z = 497.875
	Actor_63.PhysicDesc.Pos.Rotation = 90
	Actor_63.PhysicDesc.Density = 0
	Actor_63.PhysicDesc.Collidable = true
	Actor_63.PhysicDesc.SizeX = 0
	Actor_63.PhysicDesc.SizeY = 0
	Actor_63.PhysicDesc.SizeZ = 0
	Actor_63.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_23.phy"
	Actor_63:SetPhysicalActorType(1)
	Actor_63:SetPhysicalShape(5)
	Actor_63.ExtraInfo.Name = ""
	Actor_63.ExtraInfo.NameColorR = 0
	Actor_63.ExtraInfo.NameColorG = 0
	Actor_63.ExtraInfo.NameColorB = 0
	Actor_63H = ActorHandler(Actor_63)
	environment:AddActorObject(Actor_63H)

	Actor_64 = ActorObjectInfo(64)
	Actor_64:SetRenderType(1)
	Actor_64.DisplayDesc.ModelId = 0
	Actor_64.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_64.DisplayDesc.Outfit = ""
	Actor_64.DisplayDesc.Weapon = ""
	Actor_64.DisplayDesc.Mode = ""
	Actor_64.DisplayDesc.UseLight = false
	Actor_64.DisplayDesc.CastShadow = false
	Actor_64.DisplayDesc.ColorR = 1
	Actor_64.DisplayDesc.ColorG = 1
	Actor_64.DisplayDesc.ColorB = 1
	Actor_64.DisplayDesc.ColorA = 1
	Actor_64:SetModelState(1)
	Actor_64.PhysicDesc.Pos.X = 379.5
	Actor_64.PhysicDesc.Pos.Y = 28.3203
	Actor_64.PhysicDesc.Pos.Z = 525.5
	Actor_64.PhysicDesc.Pos.Rotation = 90
	Actor_64.PhysicDesc.Density = 0
	Actor_64.PhysicDesc.Collidable = true
	Actor_64.PhysicDesc.SizeX = 0
	Actor_64.PhysicDesc.SizeY = 0
	Actor_64.PhysicDesc.SizeZ = 0
	Actor_64.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
	Actor_64:SetPhysicalActorType(1)
	Actor_64:SetPhysicalShape(5)
	Actor_64.ExtraInfo.Name = ""
	Actor_64.ExtraInfo.NameColorR = 0
	Actor_64.ExtraInfo.NameColorG = 0
	Actor_64.ExtraInfo.NameColorB = 0
	Actor_64H = ActorHandler(Actor_64)
	environment:AddActorObject(Actor_64H)

	Actor_65 = ActorObjectInfo(65)
	Actor_65:SetRenderType(1)
	Actor_65.DisplayDesc.ModelId = 0
	Actor_65.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_24.osgb"
	Actor_65.DisplayDesc.Outfit = ""
	Actor_65.DisplayDesc.Weapon = ""
	Actor_65.DisplayDesc.Mode = ""
	Actor_65.DisplayDesc.UseLight = false
	Actor_65.DisplayDesc.CastShadow = false
	Actor_65.DisplayDesc.ColorR = 1
	Actor_65.DisplayDesc.ColorG = 1
	Actor_65.DisplayDesc.ColorB = 1
	Actor_65.DisplayDesc.ColorA = 1
	Actor_65:SetModelState(1)
	Actor_65.PhysicDesc.Pos.X = 385
	Actor_65.PhysicDesc.Pos.Y = 28.3203
	Actor_65.PhysicDesc.Pos.Z = 529
	Actor_65.PhysicDesc.Pos.Rotation = -90
	Actor_65.PhysicDesc.Density = 0
	Actor_65.PhysicDesc.Collidable = true
	Actor_65.PhysicDesc.SizeX = 0
	Actor_65.PhysicDesc.SizeY = 0
	Actor_65.PhysicDesc.SizeZ = 0
	Actor_65.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_24.phy"
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
	Actor_66.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_25.osgb"
	Actor_66.DisplayDesc.Outfit = ""
	Actor_66.DisplayDesc.Weapon = ""
	Actor_66.DisplayDesc.Mode = ""
	Actor_66.DisplayDesc.UseLight = false
	Actor_66.DisplayDesc.CastShadow = false
	Actor_66.DisplayDesc.ColorR = 1
	Actor_66.DisplayDesc.ColorG = 1
	Actor_66.DisplayDesc.ColorB = 1
	Actor_66.DisplayDesc.ColorA = 1
	Actor_66:SetModelState(1)
	Actor_66.PhysicDesc.Pos.X = 520.125
	Actor_66.PhysicDesc.Pos.Y = 2.44141
	Actor_66.PhysicDesc.Pos.Z = 520.125
	Actor_66.PhysicDesc.Pos.Rotation = 90
	Actor_66.PhysicDesc.Density = 0
	Actor_66.PhysicDesc.Collidable = true
	Actor_66.PhysicDesc.SizeX = 0
	Actor_66.PhysicDesc.SizeY = 0
	Actor_66.PhysicDesc.SizeZ = 0
	Actor_66.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_25.phy"
	Actor_66:SetPhysicalActorType(1)
	Actor_66:SetPhysicalShape(5)
	Actor_66.ExtraInfo.Name = ""
	Actor_66.ExtraInfo.NameColorR = 0
	Actor_66.ExtraInfo.NameColorG = 0
	Actor_66.ExtraInfo.NameColorB = 0
	Actor_66H = ActorHandler(Actor_66)
	environment:AddActorObject(Actor_66H)

	Actor_67 = ActorObjectInfo(67)
	Actor_67:SetRenderType(1)
	Actor_67.DisplayDesc.ModelId = 0
	Actor_67.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_67.DisplayDesc.Outfit = ""
	Actor_67.DisplayDesc.Weapon = ""
	Actor_67.DisplayDesc.Mode = ""
	Actor_67.DisplayDesc.UseLight = false
	Actor_67.DisplayDesc.CastShadow = false
	Actor_67.DisplayDesc.ColorR = 1
	Actor_67.DisplayDesc.ColorG = 1
	Actor_67.DisplayDesc.ColorB = 1
	Actor_67.DisplayDesc.ColorA = 1
	Actor_67:SetModelState(1)
	Actor_67.PhysicDesc.Pos.X = 514.5
	Actor_67.PhysicDesc.Pos.Y = 0.976563
	Actor_67.PhysicDesc.Pos.Z = 535.5
	Actor_67.PhysicDesc.Pos.Rotation = 90
	Actor_67.PhysicDesc.Density = 0
	Actor_67.PhysicDesc.Collidable = true
	Actor_67.PhysicDesc.SizeX = 0
	Actor_67.PhysicDesc.SizeY = 0
	Actor_67.PhysicDesc.SizeZ = 0
	Actor_67.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_67:SetPhysicalActorType(1)
	Actor_67:SetPhysicalShape(5)
	Actor_67.ExtraInfo.Name = ""
	Actor_67.ExtraInfo.NameColorR = 0
	Actor_67.ExtraInfo.NameColorG = 0
	Actor_67.ExtraInfo.NameColorB = 0
	Actor_67H = ActorHandler(Actor_67)
	environment:AddActorObject(Actor_67H)

	Actor_68 = ActorObjectInfo(68)
	Actor_68:SetRenderType(1)
	Actor_68.DisplayDesc.ModelId = 0
	Actor_68.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
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
	Actor_68.PhysicDesc.Pos.X = 515.5
	Actor_68.PhysicDesc.Pos.Y = 0.976563
	Actor_68.PhysicDesc.Pos.Z = 535.5
	Actor_68.PhysicDesc.Pos.Rotation = 90
	Actor_68.PhysicDesc.Density = 0
	Actor_68.PhysicDesc.Collidable = true
	Actor_68.PhysicDesc.SizeX = 0
	Actor_68.PhysicDesc.SizeY = 0
	Actor_68.PhysicDesc.SizeZ = 0
	Actor_68.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_68:SetPhysicalActorType(1)
	Actor_68:SetPhysicalShape(5)
	Actor_68.ExtraInfo.Name = ""
	Actor_68.ExtraInfo.NameColorR = 0
	Actor_68.ExtraInfo.NameColorG = 0
	Actor_68.ExtraInfo.NameColorB = 0
	Actor_68H = ActorHandler(Actor_68)
	environment:AddActorObject(Actor_68H)

	Actor_69 = ActorObjectInfo(69)
	Actor_69:SetRenderType(1)
	Actor_69.DisplayDesc.ModelId = 0
	Actor_69.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_69.DisplayDesc.Outfit = ""
	Actor_69.DisplayDesc.Weapon = ""
	Actor_69.DisplayDesc.Mode = ""
	Actor_69.DisplayDesc.UseLight = false
	Actor_69.DisplayDesc.CastShadow = false
	Actor_69.DisplayDesc.ColorR = 1
	Actor_69.DisplayDesc.ColorG = 1
	Actor_69.DisplayDesc.ColorB = 1
	Actor_69.DisplayDesc.ColorA = 1
	Actor_69:SetModelState(1)
	Actor_69.PhysicDesc.Pos.X = 516.5
	Actor_69.PhysicDesc.Pos.Y = 0.976563
	Actor_69.PhysicDesc.Pos.Z = 535.5
	Actor_69.PhysicDesc.Pos.Rotation = 90
	Actor_69.PhysicDesc.Density = 0
	Actor_69.PhysicDesc.Collidable = true
	Actor_69.PhysicDesc.SizeX = 0
	Actor_69.PhysicDesc.SizeY = 0
	Actor_69.PhysicDesc.SizeZ = 0
	Actor_69.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_69:SetPhysicalActorType(1)
	Actor_69:SetPhysicalShape(5)
	Actor_69.ExtraInfo.Name = ""
	Actor_69.ExtraInfo.NameColorR = 0
	Actor_69.ExtraInfo.NameColorG = 0
	Actor_69.ExtraInfo.NameColorB = 0
	Actor_69H = ActorHandler(Actor_69)
	environment:AddActorObject(Actor_69H)

	Actor_70 = ActorObjectInfo(70)
	Actor_70:SetRenderType(1)
	Actor_70.DisplayDesc.ModelId = 0
	Actor_70.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_70.DisplayDesc.Outfit = ""
	Actor_70.DisplayDesc.Weapon = ""
	Actor_70.DisplayDesc.Mode = ""
	Actor_70.DisplayDesc.UseLight = false
	Actor_70.DisplayDesc.CastShadow = false
	Actor_70.DisplayDesc.ColorR = 1
	Actor_70.DisplayDesc.ColorG = 1
	Actor_70.DisplayDesc.ColorB = 1
	Actor_70.DisplayDesc.ColorA = 1
	Actor_70:SetModelState(1)
	Actor_70.PhysicDesc.Pos.X = 517.5
	Actor_70.PhysicDesc.Pos.Y = 0.976563
	Actor_70.PhysicDesc.Pos.Z = 535.5
	Actor_70.PhysicDesc.Pos.Rotation = 90
	Actor_70.PhysicDesc.Density = 0
	Actor_70.PhysicDesc.Collidable = true
	Actor_70.PhysicDesc.SizeX = 0
	Actor_70.PhysicDesc.SizeY = 0
	Actor_70.PhysicDesc.SizeZ = 0
	Actor_70.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_70:SetPhysicalActorType(1)
	Actor_70:SetPhysicalShape(5)
	Actor_70.ExtraInfo.Name = ""
	Actor_70.ExtraInfo.NameColorR = 0
	Actor_70.ExtraInfo.NameColorG = 0
	Actor_70.ExtraInfo.NameColorB = 0
	Actor_70H = ActorHandler(Actor_70)
	environment:AddActorObject(Actor_70H)

	Actor_71 = ActorObjectInfo(71)
	Actor_71:SetRenderType(1)
	Actor_71.DisplayDesc.ModelId = 0
	Actor_71.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_71.DisplayDesc.Outfit = ""
	Actor_71.DisplayDesc.Weapon = ""
	Actor_71.DisplayDesc.Mode = ""
	Actor_71.DisplayDesc.UseLight = false
	Actor_71.DisplayDesc.CastShadow = false
	Actor_71.DisplayDesc.ColorR = 1
	Actor_71.DisplayDesc.ColorG = 1
	Actor_71.DisplayDesc.ColorB = 1
	Actor_71.DisplayDesc.ColorA = 1
	Actor_71:SetModelState(1)
	Actor_71.PhysicDesc.Pos.X = 521.5
	Actor_71.PhysicDesc.Pos.Y = 0.976563
	Actor_71.PhysicDesc.Pos.Z = 535.5
	Actor_71.PhysicDesc.Pos.Rotation = 90
	Actor_71.PhysicDesc.Density = 0
	Actor_71.PhysicDesc.Collidable = true
	Actor_71.PhysicDesc.SizeX = 0
	Actor_71.PhysicDesc.SizeY = 0
	Actor_71.PhysicDesc.SizeZ = 0
	Actor_71.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_71:SetPhysicalActorType(1)
	Actor_71:SetPhysicalShape(5)
	Actor_71.ExtraInfo.Name = ""
	Actor_71.ExtraInfo.NameColorR = 0
	Actor_71.ExtraInfo.NameColorG = 0
	Actor_71.ExtraInfo.NameColorB = 0
	Actor_71H = ActorHandler(Actor_71)
	environment:AddActorObject(Actor_71H)

	Actor_72 = ActorObjectInfo(72)
	Actor_72:SetRenderType(1)
	Actor_72.DisplayDesc.ModelId = 0
	Actor_72.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_72.DisplayDesc.Outfit = ""
	Actor_72.DisplayDesc.Weapon = ""
	Actor_72.DisplayDesc.Mode = ""
	Actor_72.DisplayDesc.UseLight = false
	Actor_72.DisplayDesc.CastShadow = false
	Actor_72.DisplayDesc.ColorR = 1
	Actor_72.DisplayDesc.ColorG = 1
	Actor_72.DisplayDesc.ColorB = 1
	Actor_72.DisplayDesc.ColorA = 1
	Actor_72:SetModelState(1)
	Actor_72.PhysicDesc.Pos.X = 522.5
	Actor_72.PhysicDesc.Pos.Y = 0.976563
	Actor_72.PhysicDesc.Pos.Z = 535.5
	Actor_72.PhysicDesc.Pos.Rotation = 90
	Actor_72.PhysicDesc.Density = 0
	Actor_72.PhysicDesc.Collidable = true
	Actor_72.PhysicDesc.SizeX = 0
	Actor_72.PhysicDesc.SizeY = 0
	Actor_72.PhysicDesc.SizeZ = 0
	Actor_72.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_72:SetPhysicalActorType(1)
	Actor_72:SetPhysicalShape(5)
	Actor_72.ExtraInfo.Name = ""
	Actor_72.ExtraInfo.NameColorR = 0
	Actor_72.ExtraInfo.NameColorG = 0
	Actor_72.ExtraInfo.NameColorB = 0
	Actor_72H = ActorHandler(Actor_72)
	environment:AddActorObject(Actor_72H)

	Actor_73 = ActorObjectInfo(73)
	Actor_73:SetRenderType(1)
	Actor_73.DisplayDesc.ModelId = 0
	Actor_73.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_73.DisplayDesc.Outfit = ""
	Actor_73.DisplayDesc.Weapon = ""
	Actor_73.DisplayDesc.Mode = ""
	Actor_73.DisplayDesc.UseLight = false
	Actor_73.DisplayDesc.CastShadow = false
	Actor_73.DisplayDesc.ColorR = 1
	Actor_73.DisplayDesc.ColorG = 1
	Actor_73.DisplayDesc.ColorB = 1
	Actor_73.DisplayDesc.ColorA = 1
	Actor_73:SetModelState(1)
	Actor_73.PhysicDesc.Pos.X = 523.5
	Actor_73.PhysicDesc.Pos.Y = 0.976563
	Actor_73.PhysicDesc.Pos.Z = 535.5
	Actor_73.PhysicDesc.Pos.Rotation = 90
	Actor_73.PhysicDesc.Density = 0
	Actor_73.PhysicDesc.Collidable = true
	Actor_73.PhysicDesc.SizeX = 0
	Actor_73.PhysicDesc.SizeY = 0
	Actor_73.PhysicDesc.SizeZ = 0
	Actor_73.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_73:SetPhysicalActorType(1)
	Actor_73:SetPhysicalShape(5)
	Actor_73.ExtraInfo.Name = ""
	Actor_73.ExtraInfo.NameColorR = 0
	Actor_73.ExtraInfo.NameColorG = 0
	Actor_73.ExtraInfo.NameColorB = 0
	Actor_73H = ActorHandler(Actor_73)
	environment:AddActorObject(Actor_73H)

	Actor_74 = ActorObjectInfo(74)
	Actor_74:SetRenderType(1)
	Actor_74.DisplayDesc.ModelId = 0
	Actor_74.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_74.DisplayDesc.Outfit = ""
	Actor_74.DisplayDesc.Weapon = ""
	Actor_74.DisplayDesc.Mode = ""
	Actor_74.DisplayDesc.UseLight = false
	Actor_74.DisplayDesc.CastShadow = false
	Actor_74.DisplayDesc.ColorR = 1
	Actor_74.DisplayDesc.ColorG = 1
	Actor_74.DisplayDesc.ColorB = 1
	Actor_74.DisplayDesc.ColorA = 1
	Actor_74:SetModelState(1)
	Actor_74.PhysicDesc.Pos.X = 524.5
	Actor_74.PhysicDesc.Pos.Y = 0.976563
	Actor_74.PhysicDesc.Pos.Z = 535.5
	Actor_74.PhysicDesc.Pos.Rotation = 90
	Actor_74.PhysicDesc.Density = 0
	Actor_74.PhysicDesc.Collidable = true
	Actor_74.PhysicDesc.SizeX = 0
	Actor_74.PhysicDesc.SizeY = 0
	Actor_74.PhysicDesc.SizeZ = 0
	Actor_74.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
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
	Actor_75.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_75.DisplayDesc.Outfit = ""
	Actor_75.DisplayDesc.Weapon = ""
	Actor_75.DisplayDesc.Mode = ""
	Actor_75.DisplayDesc.UseLight = false
	Actor_75.DisplayDesc.CastShadow = false
	Actor_75.DisplayDesc.ColorR = 1
	Actor_75.DisplayDesc.ColorG = 1
	Actor_75.DisplayDesc.ColorB = 1
	Actor_75.DisplayDesc.ColorA = 1
	Actor_75:SetModelState(1)
	Actor_75.PhysicDesc.Pos.X = 496.5
	Actor_75.PhysicDesc.Pos.Y = 0.976563
	Actor_75.PhysicDesc.Pos.Z = 536.5
	Actor_75.PhysicDesc.Pos.Rotation = -90
	Actor_75.PhysicDesc.Density = 0
	Actor_75.PhysicDesc.Collidable = true
	Actor_75.PhysicDesc.SizeX = 0
	Actor_75.PhysicDesc.SizeY = 0
	Actor_75.PhysicDesc.SizeZ = 0
	Actor_75.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
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
	Actor_76.DisplayDesc.ModelId = 0
	Actor_76.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_76.DisplayDesc.Outfit = ""
	Actor_76.DisplayDesc.Weapon = ""
	Actor_76.DisplayDesc.Mode = ""
	Actor_76.DisplayDesc.UseLight = false
	Actor_76.DisplayDesc.CastShadow = false
	Actor_76.DisplayDesc.ColorR = 1
	Actor_76.DisplayDesc.ColorG = 1
	Actor_76.DisplayDesc.ColorB = 1
	Actor_76.DisplayDesc.ColorA = 1
	Actor_76:SetModelState(1)
	Actor_76.PhysicDesc.Pos.X = 525.5
	Actor_76.PhysicDesc.Pos.Y = 1.95313
	Actor_76.PhysicDesc.Pos.Z = 515.5
	Actor_76.PhysicDesc.Pos.Rotation = 90
	Actor_76.PhysicDesc.Density = 0
	Actor_76.PhysicDesc.Collidable = true
	Actor_76.PhysicDesc.SizeX = 0
	Actor_76.PhysicDesc.SizeY = 0
	Actor_76.PhysicDesc.SizeZ = 0
	Actor_76.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
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
	Actor_77.DisplayDesc.ModelId = 0
	Actor_77.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_77.DisplayDesc.Outfit = ""
	Actor_77.DisplayDesc.Weapon = ""
	Actor_77.DisplayDesc.Mode = ""
	Actor_77.DisplayDesc.UseLight = false
	Actor_77.DisplayDesc.CastShadow = false
	Actor_77.DisplayDesc.ColorR = 1
	Actor_77.DisplayDesc.ColorG = 1
	Actor_77.DisplayDesc.ColorB = 1
	Actor_77.DisplayDesc.ColorA = 1
	Actor_77:SetModelState(1)
	Actor_77.PhysicDesc.Pos.X = 525.5
	Actor_77.PhysicDesc.Pos.Y = 1.95313
	Actor_77.PhysicDesc.Pos.Z = 524.5
	Actor_77.PhysicDesc.Pos.Rotation = 90
	Actor_77.PhysicDesc.Density = 0
	Actor_77.PhysicDesc.Collidable = true
	Actor_77.PhysicDesc.SizeX = 0
	Actor_77.PhysicDesc.SizeY = 0
	Actor_77.PhysicDesc.SizeZ = 0
	Actor_77.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
	Actor_77:SetPhysicalActorType(1)
	Actor_77:SetPhysicalShape(5)
	Actor_77.ExtraInfo.Name = ""
	Actor_77.ExtraInfo.NameColorR = 0
	Actor_77.ExtraInfo.NameColorG = 0
	Actor_77.ExtraInfo.NameColorB = 0
	Actor_77H = ActorHandler(Actor_77)
	environment:AddActorObject(Actor_77H)

	Actor_78 = ActorObjectInfo(78)
	Actor_78:SetRenderType(1)
	Actor_78.DisplayDesc.ModelId = 0
	Actor_78.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_78.DisplayDesc.Outfit = ""
	Actor_78.DisplayDesc.Weapon = ""
	Actor_78.DisplayDesc.Mode = ""
	Actor_78.DisplayDesc.UseLight = false
	Actor_78.DisplayDesc.CastShadow = false
	Actor_78.DisplayDesc.ColorR = 1
	Actor_78.DisplayDesc.ColorG = 1
	Actor_78.DisplayDesc.ColorB = 1
	Actor_78.DisplayDesc.ColorA = 1
	Actor_78:SetModelState(1)
	Actor_78.PhysicDesc.Pos.X = 514.5
	Actor_78.PhysicDesc.Pos.Y = 1.95313
	Actor_78.PhysicDesc.Pos.Z = 524.5
	Actor_78.PhysicDesc.Pos.Rotation = 90
	Actor_78.PhysicDesc.Density = 0
	Actor_78.PhysicDesc.Collidable = true
	Actor_78.PhysicDesc.SizeX = 0
	Actor_78.PhysicDesc.SizeY = 0
	Actor_78.PhysicDesc.SizeZ = 0
	Actor_78.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
	Actor_78:SetPhysicalActorType(1)
	Actor_78:SetPhysicalShape(5)
	Actor_78.ExtraInfo.Name = ""
	Actor_78.ExtraInfo.NameColorR = 0
	Actor_78.ExtraInfo.NameColorG = 0
	Actor_78.ExtraInfo.NameColorB = 0
	Actor_78H = ActorHandler(Actor_78)
	environment:AddActorObject(Actor_78H)

	Actor_79 = ActorObjectInfo(79)
	Actor_79:SetRenderType(1)
	Actor_79.DisplayDesc.ModelId = 0
	Actor_79.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_79.DisplayDesc.Outfit = ""
	Actor_79.DisplayDesc.Weapon = ""
	Actor_79.DisplayDesc.Mode = ""
	Actor_79.DisplayDesc.UseLight = false
	Actor_79.DisplayDesc.CastShadow = false
	Actor_79.DisplayDesc.ColorR = 1
	Actor_79.DisplayDesc.ColorG = 1
	Actor_79.DisplayDesc.ColorB = 1
	Actor_79.DisplayDesc.ColorA = 1
	Actor_79:SetModelState(1)
	Actor_79.PhysicDesc.Pos.X = 514.5
	Actor_79.PhysicDesc.Pos.Y = 1.95313
	Actor_79.PhysicDesc.Pos.Z = 515.5
	Actor_79.PhysicDesc.Pos.Rotation = 90
	Actor_79.PhysicDesc.Density = 0
	Actor_79.PhysicDesc.Collidable = true
	Actor_79.PhysicDesc.SizeX = 0
	Actor_79.PhysicDesc.SizeY = 0
	Actor_79.PhysicDesc.SizeZ = 0
	Actor_79.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
	Actor_79:SetPhysicalActorType(1)
	Actor_79:SetPhysicalShape(5)
	Actor_79.ExtraInfo.Name = ""
	Actor_79.ExtraInfo.NameColorR = 0
	Actor_79.ExtraInfo.NameColorG = 0
	Actor_79.ExtraInfo.NameColorB = 0
	Actor_79H = ActorHandler(Actor_79)
	environment:AddActorObject(Actor_79H)

	Actor_80 = ActorObjectInfo(80)
	Actor_80:SetRenderType(1)
	Actor_80.DisplayDesc.ModelId = 0
	Actor_80.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_80.DisplayDesc.Outfit = ""
	Actor_80.DisplayDesc.Weapon = ""
	Actor_80.DisplayDesc.Mode = ""
	Actor_80.DisplayDesc.UseLight = false
	Actor_80.DisplayDesc.CastShadow = false
	Actor_80.DisplayDesc.ColorR = 1
	Actor_80.DisplayDesc.ColorG = 1
	Actor_80.DisplayDesc.ColorB = 1
	Actor_80.DisplayDesc.ColorA = 1
	Actor_80:SetModelState(1)
	Actor_80.PhysicDesc.Pos.X = 481.5
	Actor_80.PhysicDesc.Pos.Y = 9.76563
	Actor_80.PhysicDesc.Pos.Z = 496
	Actor_80.PhysicDesc.Pos.Rotation = 180
	Actor_80.PhysicDesc.Density = 0
	Actor_80.PhysicDesc.Collidable = true
	Actor_80.PhysicDesc.SizeX = 0
	Actor_80.PhysicDesc.SizeY = 0
	Actor_80.PhysicDesc.SizeZ = 0
	Actor_80.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_80:SetPhysicalActorType(1)
	Actor_80:SetPhysicalShape(5)
	Actor_80.ExtraInfo.Name = ""
	Actor_80.ExtraInfo.NameColorR = 0
	Actor_80.ExtraInfo.NameColorG = 0
	Actor_80.ExtraInfo.NameColorB = 0
	Actor_80H = ActorHandler(Actor_80)
	environment:AddActorObject(Actor_80H)

	Actor_81 = ActorObjectInfo(81)
	Actor_81:SetRenderType(1)
	Actor_81.DisplayDesc.ModelId = 0
	Actor_81.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_81.DisplayDesc.Outfit = ""
	Actor_81.DisplayDesc.Weapon = ""
	Actor_81.DisplayDesc.Mode = ""
	Actor_81.DisplayDesc.UseLight = false
	Actor_81.DisplayDesc.CastShadow = false
	Actor_81.DisplayDesc.ColorR = 1
	Actor_81.DisplayDesc.ColorG = 1
	Actor_81.DisplayDesc.ColorB = 1
	Actor_81.DisplayDesc.ColorA = 1
	Actor_81:SetModelState(1)
	Actor_81.PhysicDesc.Pos.X = 481.5
	Actor_81.PhysicDesc.Pos.Y = 9.76563
	Actor_81.PhysicDesc.Pos.Z = 507
	Actor_81.PhysicDesc.Pos.Rotation = 180
	Actor_81.PhysicDesc.Density = 0
	Actor_81.PhysicDesc.Collidable = true
	Actor_81.PhysicDesc.SizeX = 0
	Actor_81.PhysicDesc.SizeY = 0
	Actor_81.PhysicDesc.SizeZ = 0
	Actor_81.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_81:SetPhysicalActorType(1)
	Actor_81:SetPhysicalShape(5)
	Actor_81.ExtraInfo.Name = ""
	Actor_81.ExtraInfo.NameColorR = 0
	Actor_81.ExtraInfo.NameColorG = 0
	Actor_81.ExtraInfo.NameColorB = 0
	Actor_81H = ActorHandler(Actor_81)
	environment:AddActorObject(Actor_81H)

	Actor_82 = ActorObjectInfo(82)
	Actor_82:SetRenderType(1)
	Actor_82.DisplayDesc.ModelId = 0
	Actor_82.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_82.DisplayDesc.Outfit = ""
	Actor_82.DisplayDesc.Weapon = ""
	Actor_82.DisplayDesc.Mode = ""
	Actor_82.DisplayDesc.UseLight = false
	Actor_82.DisplayDesc.CastShadow = false
	Actor_82.DisplayDesc.ColorR = 1
	Actor_82.DisplayDesc.ColorG = 1
	Actor_82.DisplayDesc.ColorB = 1
	Actor_82.DisplayDesc.ColorA = 1
	Actor_82:SetModelState(1)
	Actor_82.PhysicDesc.Pos.X = 481.5
	Actor_82.PhysicDesc.Pos.Y = 9.76563
	Actor_82.PhysicDesc.Pos.Z = 518
	Actor_82.PhysicDesc.Pos.Rotation = 180
	Actor_82.PhysicDesc.Density = 0
	Actor_82.PhysicDesc.Collidable = true
	Actor_82.PhysicDesc.SizeX = 0
	Actor_82.PhysicDesc.SizeY = 0
	Actor_82.PhysicDesc.SizeZ = 0
	Actor_82.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_82:SetPhysicalActorType(1)
	Actor_82:SetPhysicalShape(5)
	Actor_82.ExtraInfo.Name = ""
	Actor_82.ExtraInfo.NameColorR = 0
	Actor_82.ExtraInfo.NameColorG = 0
	Actor_82.ExtraInfo.NameColorB = 0
	Actor_82H = ActorHandler(Actor_82)
	environment:AddActorObject(Actor_82H)

	Actor_83 = ActorObjectInfo(83)
	Actor_83:SetRenderType(1)
	Actor_83.DisplayDesc.ModelId = 0
	Actor_83.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
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
	Actor_83.PhysicDesc.Pos.X = 481.5
	Actor_83.PhysicDesc.Pos.Y = 9.76563
	Actor_83.PhysicDesc.Pos.Z = 529
	Actor_83.PhysicDesc.Pos.Rotation = 180
	Actor_83.PhysicDesc.Density = 0
	Actor_83.PhysicDesc.Collidable = true
	Actor_83.PhysicDesc.SizeX = 0
	Actor_83.PhysicDesc.SizeY = 0
	Actor_83.PhysicDesc.SizeZ = 0
	Actor_83.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_83:SetPhysicalActorType(1)
	Actor_83:SetPhysicalShape(5)
	Actor_83.ExtraInfo.Name = ""
	Actor_83.ExtraInfo.NameColorR = 0
	Actor_83.ExtraInfo.NameColorG = 0
	Actor_83.ExtraInfo.NameColorB = 0
	Actor_83H = ActorHandler(Actor_83)
	environment:AddActorObject(Actor_83H)

	Actor_84 = ActorObjectInfo(84)
	Actor_84:SetRenderType(1)
	Actor_84.DisplayDesc.ModelId = 0
	Actor_84.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_84.DisplayDesc.Outfit = ""
	Actor_84.DisplayDesc.Weapon = ""
	Actor_84.DisplayDesc.Mode = ""
	Actor_84.DisplayDesc.UseLight = false
	Actor_84.DisplayDesc.CastShadow = false
	Actor_84.DisplayDesc.ColorR = 1
	Actor_84.DisplayDesc.ColorG = 1
	Actor_84.DisplayDesc.ColorB = 1
	Actor_84.DisplayDesc.ColorA = 1
	Actor_84:SetModelState(1)
	Actor_84.PhysicDesc.Pos.X = 481.5
	Actor_84.PhysicDesc.Pos.Y = 9.76563
	Actor_84.PhysicDesc.Pos.Z = 540
	Actor_84.PhysicDesc.Pos.Rotation = 180
	Actor_84.PhysicDesc.Density = 0
	Actor_84.PhysicDesc.Collidable = true
	Actor_84.PhysicDesc.SizeX = 0
	Actor_84.PhysicDesc.SizeY = 0
	Actor_84.PhysicDesc.SizeZ = 0
	Actor_84.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_84:SetPhysicalActorType(1)
	Actor_84:SetPhysicalShape(5)
	Actor_84.ExtraInfo.Name = ""
	Actor_84.ExtraInfo.NameColorR = 0
	Actor_84.ExtraInfo.NameColorG = 0
	Actor_84.ExtraInfo.NameColorB = 0
	Actor_84H = ActorHandler(Actor_84)
	environment:AddActorObject(Actor_84H)

	Actor_85 = ActorObjectInfo(85)
	Actor_85:SetRenderType(1)
	Actor_85.DisplayDesc.ModelId = 0
	Actor_85.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.osgb"
	Actor_85.DisplayDesc.Outfit = ""
	Actor_85.DisplayDesc.Weapon = ""
	Actor_85.DisplayDesc.Mode = ""
	Actor_85.DisplayDesc.UseLight = false
	Actor_85.DisplayDesc.CastShadow = false
	Actor_85.DisplayDesc.ColorR = 1
	Actor_85.DisplayDesc.ColorG = 1
	Actor_85.DisplayDesc.ColorB = 1
	Actor_85.DisplayDesc.ColorA = 1
	Actor_85:SetModelState(1)
	Actor_85.PhysicDesc.Pos.X = 518.5
	Actor_85.PhysicDesc.Pos.Y = 13.6719
	Actor_85.PhysicDesc.Pos.Z = 498.5
	Actor_85.PhysicDesc.Pos.Rotation = 90
	Actor_85.PhysicDesc.Density = 0
	Actor_85.PhysicDesc.Collidable = true
	Actor_85.PhysicDesc.SizeX = 0
	Actor_85.PhysicDesc.SizeY = 0
	Actor_85.PhysicDesc.SizeZ = 0
	Actor_85.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.phy"
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
	Actor_86.DisplayDesc.ModelId = 0
	Actor_86.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.osgb"
	Actor_86.DisplayDesc.Outfit = ""
	Actor_86.DisplayDesc.Weapon = ""
	Actor_86.DisplayDesc.Mode = ""
	Actor_86.DisplayDesc.UseLight = false
	Actor_86.DisplayDesc.CastShadow = false
	Actor_86.DisplayDesc.ColorR = 1
	Actor_86.DisplayDesc.ColorG = 1
	Actor_86.DisplayDesc.ColorB = 1
	Actor_86.DisplayDesc.ColorA = 1
	Actor_86:SetModelState(1)
	Actor_86.PhysicDesc.Pos.X = 503.5
	Actor_86.PhysicDesc.Pos.Y = 13.6719
	Actor_86.PhysicDesc.Pos.Z = 498.5
	Actor_86.PhysicDesc.Pos.Rotation = 90
	Actor_86.PhysicDesc.Density = 0
	Actor_86.PhysicDesc.Collidable = true
	Actor_86.PhysicDesc.SizeX = 0
	Actor_86.PhysicDesc.SizeY = 0
	Actor_86.PhysicDesc.SizeZ = 0
	Actor_86.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.phy"
	Actor_86:SetPhysicalActorType(1)
	Actor_86:SetPhysicalShape(5)
	Actor_86.ExtraInfo.Name = ""
	Actor_86.ExtraInfo.NameColorR = 0
	Actor_86.ExtraInfo.NameColorG = 0
	Actor_86.ExtraInfo.NameColorB = 0
	Actor_86H = ActorHandler(Actor_86)
	environment:AddActorObject(Actor_86H)

	Actor_87 = ActorObjectInfo(87)
	Actor_87:SetRenderType(1)
	Actor_87.DisplayDesc.ModelId = 0
	Actor_87.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.osgb"
	Actor_87.DisplayDesc.Outfit = ""
	Actor_87.DisplayDesc.Weapon = ""
	Actor_87.DisplayDesc.Mode = ""
	Actor_87.DisplayDesc.UseLight = false
	Actor_87.DisplayDesc.CastShadow = false
	Actor_87.DisplayDesc.ColorR = 1
	Actor_87.DisplayDesc.ColorG = 1
	Actor_87.DisplayDesc.ColorB = 1
	Actor_87.DisplayDesc.ColorA = 1
	Actor_87:SetModelState(1)
	Actor_87.PhysicDesc.Pos.X = 498.5
	Actor_87.PhysicDesc.Pos.Y = 9.76563
	Actor_87.PhysicDesc.Pos.Z = 498.5
	Actor_87.PhysicDesc.Pos.Rotation = 90
	Actor_87.PhysicDesc.Density = 0
	Actor_87.PhysicDesc.Collidable = true
	Actor_87.PhysicDesc.SizeX = 0
	Actor_87.PhysicDesc.SizeY = 0
	Actor_87.PhysicDesc.SizeZ = 0
	Actor_87.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.phy"
	Actor_87:SetPhysicalActorType(1)
	Actor_87:SetPhysicalShape(5)
	Actor_87.ExtraInfo.Name = ""
	Actor_87.ExtraInfo.NameColorR = 0
	Actor_87.ExtraInfo.NameColorG = 0
	Actor_87.ExtraInfo.NameColorB = 0
	Actor_87H = ActorHandler(Actor_87)
	environment:AddActorObject(Actor_87H)

	Actor_88 = ActorObjectInfo(88)
	Actor_88:SetRenderType(1)
	Actor_88.DisplayDesc.ModelId = 0
	Actor_88.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_88.DisplayDesc.Outfit = ""
	Actor_88.DisplayDesc.Weapon = ""
	Actor_88.DisplayDesc.Mode = ""
	Actor_88.DisplayDesc.UseLight = false
	Actor_88.DisplayDesc.CastShadow = false
	Actor_88.DisplayDesc.ColorR = 1
	Actor_88.DisplayDesc.ColorG = 1
	Actor_88.DisplayDesc.ColorB = 1
	Actor_88.DisplayDesc.ColorA = 1
	Actor_88:SetModelState(1)
	Actor_88.PhysicDesc.Pos.X = 513.5
	Actor_88.PhysicDesc.Pos.Y = 0.976563
	Actor_88.PhysicDesc.Pos.Z = 540.75
	Actor_88.PhysicDesc.Pos.Rotation = 180
	Actor_88.PhysicDesc.Density = 0
	Actor_88.PhysicDesc.Collidable = true
	Actor_88.PhysicDesc.SizeX = 0
	Actor_88.PhysicDesc.SizeY = 0
	Actor_88.PhysicDesc.SizeZ = 0
	Actor_88.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_88:SetPhysicalActorType(1)
	Actor_88:SetPhysicalShape(5)
	Actor_88.ExtraInfo.Name = ""
	Actor_88.ExtraInfo.NameColorR = 0
	Actor_88.ExtraInfo.NameColorG = 0
	Actor_88.ExtraInfo.NameColorB = 0
	Actor_88H = ActorHandler(Actor_88)
	environment:AddActorObject(Actor_88H)

	Actor_89 = ActorObjectInfo(89)
	Actor_89:SetRenderType(1)
	Actor_89.DisplayDesc.ModelId = 0
	Actor_89.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.osgb"
	Actor_89.DisplayDesc.Outfit = ""
	Actor_89.DisplayDesc.Weapon = ""
	Actor_89.DisplayDesc.Mode = ""
	Actor_89.DisplayDesc.UseLight = false
	Actor_89.DisplayDesc.CastShadow = false
	Actor_89.DisplayDesc.ColorR = 1
	Actor_89.DisplayDesc.ColorG = 1
	Actor_89.DisplayDesc.ColorB = 1
	Actor_89.DisplayDesc.ColorA = 1
	Actor_89:SetModelState(1)
	Actor_89.PhysicDesc.Pos.X = 526.375
	Actor_89.PhysicDesc.Pos.Y = 9.76563
	Actor_89.PhysicDesc.Pos.Z = 504.375
	Actor_89.PhysicDesc.Pos.Rotation = 90
	Actor_89.PhysicDesc.Density = 0
	Actor_89.PhysicDesc.Collidable = true
	Actor_89.PhysicDesc.SizeX = 0
	Actor_89.PhysicDesc.SizeY = 0
	Actor_89.PhysicDesc.SizeZ = 0
	Actor_89.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.phy"
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
	Actor_90.DisplayDesc.ModelId = 0
	Actor_90.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_33.osgb"
	Actor_90.DisplayDesc.Outfit = ""
	Actor_90.DisplayDesc.Weapon = ""
	Actor_90.DisplayDesc.Mode = ""
	Actor_90.DisplayDesc.UseLight = false
	Actor_90.DisplayDesc.CastShadow = false
	Actor_90.DisplayDesc.ColorR = 1
	Actor_90.DisplayDesc.ColorG = 1
	Actor_90.DisplayDesc.ColorB = 1
	Actor_90.DisplayDesc.ColorA = 1
	Actor_90:SetModelState(1)
	Actor_90.PhysicDesc.Pos.X = 496.859
	Actor_90.PhysicDesc.Pos.Y = 0.976563
	Actor_90.PhysicDesc.Pos.Z = 514.75
	Actor_90.PhysicDesc.Pos.Rotation = 0
	Actor_90.PhysicDesc.Density = 0
	Actor_90.PhysicDesc.Collidable = true
	Actor_90.PhysicDesc.SizeX = 0
	Actor_90.PhysicDesc.SizeY = 0
	Actor_90.PhysicDesc.SizeZ = 0
	Actor_90.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_33.phy"
	Actor_90:SetPhysicalActorType(1)
	Actor_90:SetPhysicalShape(5)
	Actor_90.ExtraInfo.Name = ""
	Actor_90.ExtraInfo.NameColorR = 0
	Actor_90.ExtraInfo.NameColorG = 0
	Actor_90.ExtraInfo.NameColorB = 0
	Actor_90H = ActorHandler(Actor_90)
	environment:AddActorObject(Actor_90H)

	Actor_91 = ActorObjectInfo(91)
	Actor_91:SetRenderType(1)
	Actor_91.DisplayDesc.ModelId = 0
	Actor_91.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_34.osgb"
	Actor_91.DisplayDesc.Outfit = ""
	Actor_91.DisplayDesc.Weapon = ""
	Actor_91.DisplayDesc.Mode = ""
	Actor_91.DisplayDesc.UseLight = false
	Actor_91.DisplayDesc.CastShadow = false
	Actor_91.DisplayDesc.ColorR = 1
	Actor_91.DisplayDesc.ColorG = 1
	Actor_91.DisplayDesc.ColorB = 1
	Actor_91.DisplayDesc.ColorA = 1
	Actor_91:SetModelState(1)
	Actor_91.PhysicDesc.Pos.X = 496.859
	Actor_91.PhysicDesc.Pos.Y = 0.976563
	Actor_91.PhysicDesc.Pos.Z = 514.75
	Actor_91.PhysicDesc.Pos.Rotation = 0
	Actor_91.PhysicDesc.Density = 0
	Actor_91.PhysicDesc.Collidable = true
	Actor_91.PhysicDesc.SizeX = 0
	Actor_91.PhysicDesc.SizeY = 0
	Actor_91.PhysicDesc.SizeZ = 0
	Actor_91.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_34.phy"
	Actor_91:SetPhysicalActorType(1)
	Actor_91:SetPhysicalShape(5)
	Actor_91.ExtraInfo.Name = ""
	Actor_91.ExtraInfo.NameColorR = 0
	Actor_91.ExtraInfo.NameColorG = 0
	Actor_91.ExtraInfo.NameColorB = 0
	Actor_91H = ActorHandler(Actor_91)
	environment:AddActorObject(Actor_91H)

	Actor_92 = ActorObjectInfo(92)
	Actor_92:SetRenderType(1)
	Actor_92.DisplayDesc.ModelId = 0
	Actor_92.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_31.osgb"
	Actor_92.DisplayDesc.Outfit = ""
	Actor_92.DisplayDesc.Weapon = ""
	Actor_92.DisplayDesc.Mode = ""
	Actor_92.DisplayDesc.UseLight = false
	Actor_92.DisplayDesc.CastShadow = false
	Actor_92.DisplayDesc.ColorR = 1
	Actor_92.DisplayDesc.ColorG = 1
	Actor_92.DisplayDesc.ColorB = 1
	Actor_92.DisplayDesc.ColorA = 1
	Actor_92:SetModelState(1)
	Actor_92.PhysicDesc.Pos.X = 488.5
	Actor_92.PhysicDesc.Pos.Y = 0.976563
	Actor_92.PhysicDesc.Pos.Z = 538.508
	Actor_92.PhysicDesc.Pos.Rotation = 0
	Actor_92.PhysicDesc.Density = 0
	Actor_92.PhysicDesc.Collidable = true
	Actor_92.PhysicDesc.SizeX = 0
	Actor_92.PhysicDesc.SizeY = 0
	Actor_92.PhysicDesc.SizeZ = 0
	Actor_92.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_31.phy"
	Actor_92:SetPhysicalActorType(1)
	Actor_92:SetPhysicalShape(5)
	Actor_92.ExtraInfo.Name = ""
	Actor_92.ExtraInfo.NameColorR = 0
	Actor_92.ExtraInfo.NameColorG = 0
	Actor_92.ExtraInfo.NameColorB = 0
	Actor_92H = ActorHandler(Actor_92)
	environment:AddActorObject(Actor_92H)

	Actor_93 = ActorObjectInfo(93)
	Actor_93:SetRenderType(1)
	Actor_93.DisplayDesc.ModelId = 0
	Actor_93.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_32.osgb"
	Actor_93.DisplayDesc.Outfit = ""
	Actor_93.DisplayDesc.Weapon = ""
	Actor_93.DisplayDesc.Mode = ""
	Actor_93.DisplayDesc.UseLight = false
	Actor_93.DisplayDesc.CastShadow = false
	Actor_93.DisplayDesc.ColorR = 1
	Actor_93.DisplayDesc.ColorG = 1
	Actor_93.DisplayDesc.ColorB = 1
	Actor_93.DisplayDesc.ColorA = 1
	Actor_93:SetModelState(1)
	Actor_93.PhysicDesc.Pos.X = 488.5
	Actor_93.PhysicDesc.Pos.Y = 0.976563
	Actor_93.PhysicDesc.Pos.Z = 538.508
	Actor_93.PhysicDesc.Pos.Rotation = 0
	Actor_93.PhysicDesc.Density = 0
	Actor_93.PhysicDesc.Collidable = true
	Actor_93.PhysicDesc.SizeX = 0
	Actor_93.PhysicDesc.SizeY = 0
	Actor_93.PhysicDesc.SizeZ = 0
	Actor_93.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_32.phy"
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
	Actor_94.DisplayDesc.ModelId = 0
	Actor_94.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_94.DisplayDesc.Outfit = ""
	Actor_94.DisplayDesc.Weapon = ""
	Actor_94.DisplayDesc.Mode = ""
	Actor_94.DisplayDesc.UseLight = false
	Actor_94.DisplayDesc.CastShadow = false
	Actor_94.DisplayDesc.ColorR = 1
	Actor_94.DisplayDesc.ColorG = 1
	Actor_94.DisplayDesc.ColorB = 1
	Actor_94.DisplayDesc.ColorA = 1
	Actor_94:SetModelState(1)
	Actor_94.PhysicDesc.Pos.X = 499.5
	Actor_94.PhysicDesc.Pos.Y = 0.976563
	Actor_94.PhysicDesc.Pos.Z = 525.5
	Actor_94.PhysicDesc.Pos.Rotation = 90
	Actor_94.PhysicDesc.Density = 0
	Actor_94.PhysicDesc.Collidable = true
	Actor_94.PhysicDesc.SizeX = 0
	Actor_94.PhysicDesc.SizeY = 0
	Actor_94.PhysicDesc.SizeZ = 0
	Actor_94.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
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
	Actor_95.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_35.osgb"
	Actor_95.DisplayDesc.Outfit = ""
	Actor_95.DisplayDesc.Weapon = ""
	Actor_95.DisplayDesc.Mode = ""
	Actor_95.DisplayDesc.UseLight = false
	Actor_95.DisplayDesc.CastShadow = false
	Actor_95.DisplayDesc.ColorR = 1
	Actor_95.DisplayDesc.ColorG = 1
	Actor_95.DisplayDesc.ColorB = 1
	Actor_95.DisplayDesc.ColorA = 1
	Actor_95:SetModelState(1)
	Actor_95.PhysicDesc.Pos.X = 494.5
	Actor_95.PhysicDesc.Pos.Y = 0.976563
	Actor_95.PhysicDesc.Pos.Z = 520.5
	Actor_95.PhysicDesc.Pos.Rotation = 90
	Actor_95.PhysicDesc.Density = 0
	Actor_95.PhysicDesc.Collidable = true
	Actor_95.PhysicDesc.SizeX = 0
	Actor_95.PhysicDesc.SizeY = 0
	Actor_95.PhysicDesc.SizeZ = 0
	Actor_95.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_35.phy"
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
	Actor_96.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_36.osgb"
	Actor_96.DisplayDesc.Outfit = ""
	Actor_96.DisplayDesc.Weapon = ""
	Actor_96.DisplayDesc.Mode = ""
	Actor_96.DisplayDesc.UseLight = false
	Actor_96.DisplayDesc.CastShadow = false
	Actor_96.DisplayDesc.ColorR = 1
	Actor_96.DisplayDesc.ColorG = 1
	Actor_96.DisplayDesc.ColorB = 1
	Actor_96.DisplayDesc.ColorA = 1
	Actor_96:SetModelState(1)
	Actor_96.PhysicDesc.Pos.X = 531.734
	Actor_96.PhysicDesc.Pos.Y = 0.976563
	Actor_96.PhysicDesc.Pos.Z = 495.891
	Actor_96.PhysicDesc.Pos.Rotation = -90
	Actor_96.PhysicDesc.Density = 0
	Actor_96.PhysicDesc.Collidable = true
	Actor_96.PhysicDesc.SizeX = 0
	Actor_96.PhysicDesc.SizeY = 0
	Actor_96.PhysicDesc.SizeZ = 0
	Actor_96.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_36.phy"
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
	Actor_97.DisplayDesc.ModelId = 0
	Actor_97.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_37.osgb"
	Actor_97.DisplayDesc.Outfit = ""
	Actor_97.DisplayDesc.Weapon = ""
	Actor_97.DisplayDesc.Mode = ""
	Actor_97.DisplayDesc.UseLight = false
	Actor_97.DisplayDesc.CastShadow = false
	Actor_97.DisplayDesc.ColorR = 1
	Actor_97.DisplayDesc.ColorG = 1
	Actor_97.DisplayDesc.ColorB = 1
	Actor_97.DisplayDesc.ColorA = 1
	Actor_97:SetModelState(1)
	Actor_97.PhysicDesc.Pos.X = 542.43
	Actor_97.PhysicDesc.Pos.Y = 0.976563
	Actor_97.PhysicDesc.Pos.Z = 500.867
	Actor_97.PhysicDesc.Pos.Rotation = 180
	Actor_97.PhysicDesc.Density = 0
	Actor_97.PhysicDesc.Collidable = true
	Actor_97.PhysicDesc.SizeX = 0
	Actor_97.PhysicDesc.SizeY = 0
	Actor_97.PhysicDesc.SizeZ = 0
	Actor_97.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_37.phy"
	Actor_97:SetPhysicalActorType(1)
	Actor_97:SetPhysicalShape(5)
	Actor_97.ExtraInfo.Name = ""
	Actor_97.ExtraInfo.NameColorR = 0
	Actor_97.ExtraInfo.NameColorG = 0
	Actor_97.ExtraInfo.NameColorB = 0
	Actor_97H = ActorHandler(Actor_97)
	environment:AddActorObject(Actor_97H)

	Actor_98 = ActorObjectInfo(98)
	Actor_98:SetRenderType(1)
	Actor_98.DisplayDesc.ModelId = 0
	Actor_98.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_37.osgb"
	Actor_98.DisplayDesc.Outfit = ""
	Actor_98.DisplayDesc.Weapon = ""
	Actor_98.DisplayDesc.Mode = ""
	Actor_98.DisplayDesc.UseLight = false
	Actor_98.DisplayDesc.CastShadow = false
	Actor_98.DisplayDesc.ColorR = 1
	Actor_98.DisplayDesc.ColorG = 1
	Actor_98.DisplayDesc.ColorB = 1
	Actor_98.DisplayDesc.ColorA = 1
	Actor_98:SetModelState(1)
	Actor_98.PhysicDesc.Pos.X = 538.719
	Actor_98.PhysicDesc.Pos.Y = 0.976563
	Actor_98.PhysicDesc.Pos.Z = 504.578
	Actor_98.PhysicDesc.Pos.Rotation = -90
	Actor_98.PhysicDesc.Density = 0
	Actor_98.PhysicDesc.Collidable = true
	Actor_98.PhysicDesc.SizeX = 0
	Actor_98.PhysicDesc.SizeY = 0
	Actor_98.PhysicDesc.SizeZ = 0
	Actor_98.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_37.phy"
	Actor_98:SetPhysicalActorType(1)
	Actor_98:SetPhysicalShape(5)
	Actor_98.ExtraInfo.Name = ""
	Actor_98.ExtraInfo.NameColorR = 0
	Actor_98.ExtraInfo.NameColorG = 0
	Actor_98.ExtraInfo.NameColorB = 0
	Actor_98H = ActorHandler(Actor_98)
	environment:AddActorObject(Actor_98H)

	Actor_99 = ActorObjectInfo(99)
	Actor_99:SetRenderType(1)
	Actor_99.DisplayDesc.ModelId = 0
	Actor_99.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_38.osgb"
	Actor_99.DisplayDesc.Outfit = ""
	Actor_99.DisplayDesc.Weapon = ""
	Actor_99.DisplayDesc.Mode = ""
	Actor_99.DisplayDesc.UseLight = false
	Actor_99.DisplayDesc.CastShadow = false
	Actor_99.DisplayDesc.ColorR = 1
	Actor_99.DisplayDesc.ColorG = 1
	Actor_99.DisplayDesc.ColorB = 1
	Actor_99.DisplayDesc.ColorA = 1
	Actor_99:SetModelState(1)
	Actor_99.PhysicDesc.Pos.X = 529.547
	Actor_99.PhysicDesc.Pos.Y = 0.976563
	Actor_99.PhysicDesc.Pos.Z = 504.813
	Actor_99.PhysicDesc.Pos.Rotation = -90
	Actor_99.PhysicDesc.Density = 0
	Actor_99.PhysicDesc.Collidable = true
	Actor_99.PhysicDesc.SizeX = 0
	Actor_99.PhysicDesc.SizeY = 0
	Actor_99.PhysicDesc.SizeZ = 0
	Actor_99.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_38.phy"
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
	Actor_100.DisplayDesc.ModelId = 0
	Actor_100.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_38.osgb"
	Actor_100.DisplayDesc.Outfit = ""
	Actor_100.DisplayDesc.Weapon = ""
	Actor_100.DisplayDesc.Mode = ""
	Actor_100.DisplayDesc.UseLight = false
	Actor_100.DisplayDesc.CastShadow = false
	Actor_100.DisplayDesc.ColorR = 1
	Actor_100.DisplayDesc.ColorG = 1
	Actor_100.DisplayDesc.ColorB = 1
	Actor_100.DisplayDesc.ColorA = 1
	Actor_100:SetModelState(1)
	Actor_100.PhysicDesc.Pos.X = 542.43
	Actor_100.PhysicDesc.Pos.Y = 0.976563
	Actor_100.PhysicDesc.Pos.Z = 496.57
	Actor_100.PhysicDesc.Pos.Rotation = 180
	Actor_100.PhysicDesc.Density = 0
	Actor_100.PhysicDesc.Collidable = true
	Actor_100.PhysicDesc.SizeX = 0
	Actor_100.PhysicDesc.SizeY = 0
	Actor_100.PhysicDesc.SizeZ = 0
	Actor_100.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_38.phy"
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
	Actor_101.DisplayDesc.ModelId = 0
	Actor_101.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_39.osgb"
	Actor_101.DisplayDesc.Outfit = ""
	Actor_101.DisplayDesc.Weapon = ""
	Actor_101.DisplayDesc.Mode = ""
	Actor_101.DisplayDesc.UseLight = false
	Actor_101.DisplayDesc.CastShadow = false
	Actor_101.DisplayDesc.ColorR = 1
	Actor_101.DisplayDesc.ColorG = 1
	Actor_101.DisplayDesc.ColorB = 1
	Actor_101.DisplayDesc.ColorA = 1
	Actor_101:SetModelState(1)
	Actor_101.PhysicDesc.Pos.X = 538.719
	Actor_101.PhysicDesc.Pos.Y = 0.976563
	Actor_101.PhysicDesc.Pos.Z = 504.578
	Actor_101.PhysicDesc.Pos.Rotation = -90
	Actor_101.PhysicDesc.Density = 0
	Actor_101.PhysicDesc.Collidable = true
	Actor_101.PhysicDesc.SizeX = 0
	Actor_101.PhysicDesc.SizeY = 0
	Actor_101.PhysicDesc.SizeZ = 0
	Actor_101.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_39.phy"
	Actor_101:SetPhysicalActorType(1)
	Actor_101:SetPhysicalShape(5)
	Actor_101.ExtraInfo.Name = ""
	Actor_101.ExtraInfo.NameColorR = 0
	Actor_101.ExtraInfo.NameColorG = 0
	Actor_101.ExtraInfo.NameColorB = 0
	Actor_101H = ActorHandler(Actor_101)
	environment:AddActorObject(Actor_101H)

	Actor_102 = ActorObjectInfo(102)
	Actor_102:SetRenderType(1)
	Actor_102.DisplayDesc.ModelId = 0
	Actor_102.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_40.osgb"
	Actor_102.DisplayDesc.Outfit = ""
	Actor_102.DisplayDesc.Weapon = ""
	Actor_102.DisplayDesc.Mode = ""
	Actor_102.DisplayDesc.UseLight = false
	Actor_102.DisplayDesc.CastShadow = false
	Actor_102.DisplayDesc.ColorR = 1
	Actor_102.DisplayDesc.ColorG = 1
	Actor_102.DisplayDesc.ColorB = 1
	Actor_102.DisplayDesc.ColorA = 1
	Actor_102:SetModelState(1)
	Actor_102.PhysicDesc.Pos.X = 537.5
	Actor_102.PhysicDesc.Pos.Y = 0.976563
	Actor_102.PhysicDesc.Pos.Z = 503.5
	Actor_102.PhysicDesc.Pos.Rotation = 90
	Actor_102.PhysicDesc.Density = 0
	Actor_102.PhysicDesc.Collidable = true
	Actor_102.PhysicDesc.SizeX = 0
	Actor_102.PhysicDesc.SizeY = 0
	Actor_102.PhysicDesc.SizeZ = 0
	Actor_102.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_40.phy"
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
	Actor_103.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_103.DisplayDesc.Outfit = ""
	Actor_103.DisplayDesc.Weapon = ""
	Actor_103.DisplayDesc.Mode = ""
	Actor_103.DisplayDesc.UseLight = false
	Actor_103.DisplayDesc.CastShadow = false
	Actor_103.DisplayDesc.ColorR = 1
	Actor_103.DisplayDesc.ColorG = 1
	Actor_103.DisplayDesc.ColorB = 1
	Actor_103.DisplayDesc.ColorA = 1
	Actor_103:SetModelState(1)
	Actor_103.PhysicDesc.Pos.X = 540.5
	Actor_103.PhysicDesc.Pos.Y = 0.976563
	Actor_103.PhysicDesc.Pos.Z = 502.5
	Actor_103.PhysicDesc.Pos.Rotation = 90
	Actor_103.PhysicDesc.Density = 0
	Actor_103.PhysicDesc.Collidable = true
	Actor_103.PhysicDesc.SizeX = 0
	Actor_103.PhysicDesc.SizeY = 0
	Actor_103.PhysicDesc.SizeZ = 0
	Actor_103.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_103:SetPhysicalActorType(1)
	Actor_103:SetPhysicalShape(5)
	Actor_103.ExtraInfo.Name = ""
	Actor_103.ExtraInfo.NameColorR = 0
	Actor_103.ExtraInfo.NameColorG = 0
	Actor_103.ExtraInfo.NameColorB = 0
	Actor_103H = ActorHandler(Actor_103)
	environment:AddActorObject(Actor_103H)

	Actor_104 = ActorObjectInfo(104)
	Actor_104:SetRenderType(1)
	Actor_104.DisplayDesc.ModelId = 0
	Actor_104.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_41.osgb"
	Actor_104.DisplayDesc.Outfit = ""
	Actor_104.DisplayDesc.Weapon = ""
	Actor_104.DisplayDesc.Mode = ""
	Actor_104.DisplayDesc.UseLight = false
	Actor_104.DisplayDesc.CastShadow = false
	Actor_104.DisplayDesc.ColorR = 1
	Actor_104.DisplayDesc.ColorG = 1
	Actor_104.DisplayDesc.ColorB = 1
	Actor_104.DisplayDesc.ColorA = 1
	Actor_104:SetModelState(1)
	Actor_104.PhysicDesc.Pos.X = 527.875
	Actor_104.PhysicDesc.Pos.Y = 17.5781
	Actor_104.PhysicDesc.Pos.Z = 491.75
	Actor_104.PhysicDesc.Pos.Rotation = 0
	Actor_104.PhysicDesc.Density = 0
	Actor_104.PhysicDesc.Collidable = true
	Actor_104.PhysicDesc.SizeX = 0
	Actor_104.PhysicDesc.SizeY = 0
	Actor_104.PhysicDesc.SizeZ = 0
	Actor_104.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_41.phy"
	Actor_104:SetPhysicalActorType(1)
	Actor_104:SetPhysicalShape(5)
	Actor_104.ExtraInfo.Name = ""
	Actor_104.ExtraInfo.NameColorR = 0
	Actor_104.ExtraInfo.NameColorG = 0
	Actor_104.ExtraInfo.NameColorB = 0
	Actor_104H = ActorHandler(Actor_104)
	environment:AddActorObject(Actor_104H)

	Actor_105 = ActorObjectInfo(105)
	Actor_105:SetRenderType(1)
	Actor_105.DisplayDesc.ModelId = 0
	Actor_105.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_105.DisplayDesc.Outfit = ""
	Actor_105.DisplayDesc.Weapon = ""
	Actor_105.DisplayDesc.Mode = ""
	Actor_105.DisplayDesc.UseLight = false
	Actor_105.DisplayDesc.CastShadow = false
	Actor_105.DisplayDesc.ColorR = 1
	Actor_105.DisplayDesc.ColorG = 1
	Actor_105.DisplayDesc.ColorB = 1
	Actor_105.DisplayDesc.ColorA = 1
	Actor_105:SetModelState(1)
	Actor_105.PhysicDesc.Pos.X = 482
	Actor_105.PhysicDesc.Pos.Y = 9.76563
	Actor_105.PhysicDesc.Pos.Z = 535.25
	Actor_105.PhysicDesc.Pos.Rotation = 90
	Actor_105.PhysicDesc.Density = 0
	Actor_105.PhysicDesc.Collidable = true
	Actor_105.PhysicDesc.SizeX = 0
	Actor_105.PhysicDesc.SizeY = 0
	Actor_105.PhysicDesc.SizeZ = 0
	Actor_105.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
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
	Actor_106.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_106.DisplayDesc.Outfit = ""
	Actor_106.DisplayDesc.Weapon = ""
	Actor_106.DisplayDesc.Mode = ""
	Actor_106.DisplayDesc.UseLight = false
	Actor_106.DisplayDesc.CastShadow = false
	Actor_106.DisplayDesc.ColorR = 1
	Actor_106.DisplayDesc.ColorG = 1
	Actor_106.DisplayDesc.ColorB = 1
	Actor_106.DisplayDesc.ColorA = 1
	Actor_106:SetModelState(1)
	Actor_106.PhysicDesc.Pos.X = 482
	Actor_106.PhysicDesc.Pos.Y = 9.76563
	Actor_106.PhysicDesc.Pos.Z = 533.5
	Actor_106.PhysicDesc.Pos.Rotation = 90
	Actor_106.PhysicDesc.Density = 0
	Actor_106.PhysicDesc.Collidable = true
	Actor_106.PhysicDesc.SizeX = 0
	Actor_106.PhysicDesc.SizeY = 0
	Actor_106.PhysicDesc.SizeZ = 0
	Actor_106.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_106:SetPhysicalActorType(1)
	Actor_106:SetPhysicalShape(5)
	Actor_106.ExtraInfo.Name = ""
	Actor_106.ExtraInfo.NameColorR = 0
	Actor_106.ExtraInfo.NameColorG = 3.49047e-039
	Actor_106.ExtraInfo.NameColorB = 2.40859e-035
	Actor_106H = ActorHandler(Actor_106)
	environment:AddActorObject(Actor_106H)

	Actor_107 = ActorObjectInfo(107)
	Actor_107:SetRenderType(1)
	Actor_107.DisplayDesc.ModelId = 0
	Actor_107.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_107.DisplayDesc.Outfit = ""
	Actor_107.DisplayDesc.Weapon = ""
	Actor_107.DisplayDesc.Mode = ""
	Actor_107.DisplayDesc.UseLight = false
	Actor_107.DisplayDesc.CastShadow = false
	Actor_107.DisplayDesc.ColorR = 1
	Actor_107.DisplayDesc.ColorG = 1
	Actor_107.DisplayDesc.ColorB = 1
	Actor_107.DisplayDesc.ColorA = 1
	Actor_107:SetModelState(1)
	Actor_107.PhysicDesc.Pos.X = 482
	Actor_107.PhysicDesc.Pos.Y = 9.76563
	Actor_107.PhysicDesc.Pos.Z = 524.25
	Actor_107.PhysicDesc.Pos.Rotation = 90
	Actor_107.PhysicDesc.Density = 0
	Actor_107.PhysicDesc.Collidable = true
	Actor_107.PhysicDesc.SizeX = 0
	Actor_107.PhysicDesc.SizeY = 0
	Actor_107.PhysicDesc.SizeZ = 0
	Actor_107.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_107:SetPhysicalActorType(1)
	Actor_107:SetPhysicalShape(5)
	Actor_107.ExtraInfo.Name = ""
	Actor_107.ExtraInfo.NameColorR = 0
	Actor_107.ExtraInfo.NameColorG = 0
	Actor_107.ExtraInfo.NameColorB = 0
	Actor_107H = ActorHandler(Actor_107)
	environment:AddActorObject(Actor_107H)

	Actor_108 = ActorObjectInfo(108)
	Actor_108:SetRenderType(1)
	Actor_108.DisplayDesc.ModelId = 0
	Actor_108.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_108.DisplayDesc.Outfit = ""
	Actor_108.DisplayDesc.Weapon = ""
	Actor_108.DisplayDesc.Mode = ""
	Actor_108.DisplayDesc.UseLight = false
	Actor_108.DisplayDesc.CastShadow = false
	Actor_108.DisplayDesc.ColorR = 1
	Actor_108.DisplayDesc.ColorG = 1
	Actor_108.DisplayDesc.ColorB = 1
	Actor_108.DisplayDesc.ColorA = 1
	Actor_108:SetModelState(1)
	Actor_108.PhysicDesc.Pos.X = 482
	Actor_108.PhysicDesc.Pos.Y = 9.76563
	Actor_108.PhysicDesc.Pos.Z = 522.5
	Actor_108.PhysicDesc.Pos.Rotation = 90
	Actor_108.PhysicDesc.Density = 0
	Actor_108.PhysicDesc.Collidable = true
	Actor_108.PhysicDesc.SizeX = 0
	Actor_108.PhysicDesc.SizeY = 0
	Actor_108.PhysicDesc.SizeZ = 0
	Actor_108.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_108:SetPhysicalActorType(1)
	Actor_108:SetPhysicalShape(5)
	Actor_108.ExtraInfo.Name = ""
	Actor_108.ExtraInfo.NameColorR = 0
	Actor_108.ExtraInfo.NameColorG = 0
	Actor_108.ExtraInfo.NameColorB = 0
	Actor_108H = ActorHandler(Actor_108)
	environment:AddActorObject(Actor_108H)

	Actor_109 = ActorObjectInfo(109)
	Actor_109:SetRenderType(1)
	Actor_109.DisplayDesc.ModelId = 0
	Actor_109.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_109.DisplayDesc.Outfit = ""
	Actor_109.DisplayDesc.Weapon = ""
	Actor_109.DisplayDesc.Mode = ""
	Actor_109.DisplayDesc.UseLight = false
	Actor_109.DisplayDesc.CastShadow = false
	Actor_109.DisplayDesc.ColorR = 1
	Actor_109.DisplayDesc.ColorG = 1
	Actor_109.DisplayDesc.ColorB = 1
	Actor_109.DisplayDesc.ColorA = 1
	Actor_109:SetModelState(1)
	Actor_109.PhysicDesc.Pos.X = 482
	Actor_109.PhysicDesc.Pos.Y = 9.76563
	Actor_109.PhysicDesc.Pos.Z = 513.25
	Actor_109.PhysicDesc.Pos.Rotation = 90
	Actor_109.PhysicDesc.Density = 0
	Actor_109.PhysicDesc.Collidable = true
	Actor_109.PhysicDesc.SizeX = 0
	Actor_109.PhysicDesc.SizeY = 0
	Actor_109.PhysicDesc.SizeZ = 0
	Actor_109.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
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
	Actor_110.DisplayDesc.ModelId = 0
	Actor_110.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_110.DisplayDesc.Outfit = ""
	Actor_110.DisplayDesc.Weapon = ""
	Actor_110.DisplayDesc.Mode = ""
	Actor_110.DisplayDesc.UseLight = false
	Actor_110.DisplayDesc.CastShadow = false
	Actor_110.DisplayDesc.ColorR = 1
	Actor_110.DisplayDesc.ColorG = 1
	Actor_110.DisplayDesc.ColorB = 1
	Actor_110.DisplayDesc.ColorA = 1
	Actor_110:SetModelState(1)
	Actor_110.PhysicDesc.Pos.X = 482
	Actor_110.PhysicDesc.Pos.Y = 9.76563
	Actor_110.PhysicDesc.Pos.Z = 511.5
	Actor_110.PhysicDesc.Pos.Rotation = 90
	Actor_110.PhysicDesc.Density = 0
	Actor_110.PhysicDesc.Collidable = true
	Actor_110.PhysicDesc.SizeX = 0
	Actor_110.PhysicDesc.SizeY = 0
	Actor_110.PhysicDesc.SizeZ = 0
	Actor_110.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_110:SetPhysicalActorType(1)
	Actor_110:SetPhysicalShape(5)
	Actor_110.ExtraInfo.Name = ""
	Actor_110.ExtraInfo.NameColorR = 0
	Actor_110.ExtraInfo.NameColorG = 0
	Actor_110.ExtraInfo.NameColorB = 0
	Actor_110H = ActorHandler(Actor_110)
	environment:AddActorObject(Actor_110H)

	Actor_111 = ActorObjectInfo(111)
	Actor_111:SetRenderType(1)
	Actor_111.DisplayDesc.ModelId = 0
	Actor_111.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_111.DisplayDesc.Outfit = ""
	Actor_111.DisplayDesc.Weapon = ""
	Actor_111.DisplayDesc.Mode = ""
	Actor_111.DisplayDesc.UseLight = false
	Actor_111.DisplayDesc.CastShadow = false
	Actor_111.DisplayDesc.ColorR = 1
	Actor_111.DisplayDesc.ColorG = 1
	Actor_111.DisplayDesc.ColorB = 1
	Actor_111.DisplayDesc.ColorA = 1
	Actor_111:SetModelState(1)
	Actor_111.PhysicDesc.Pos.X = 482
	Actor_111.PhysicDesc.Pos.Y = 9.76563
	Actor_111.PhysicDesc.Pos.Z = 502.25
	Actor_111.PhysicDesc.Pos.Rotation = 90
	Actor_111.PhysicDesc.Density = 0
	Actor_111.PhysicDesc.Collidable = true
	Actor_111.PhysicDesc.SizeX = 0
	Actor_111.PhysicDesc.SizeY = 0
	Actor_111.PhysicDesc.SizeZ = 0
	Actor_111.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_111:SetPhysicalActorType(1)
	Actor_111:SetPhysicalShape(5)
	Actor_111.ExtraInfo.Name = ""
	Actor_111.ExtraInfo.NameColorR = 0
	Actor_111.ExtraInfo.NameColorG = 0
	Actor_111.ExtraInfo.NameColorB = 0
	Actor_111H = ActorHandler(Actor_111)
	environment:AddActorObject(Actor_111H)

	Actor_112 = ActorObjectInfo(112)
	Actor_112:SetRenderType(1)
	Actor_112.DisplayDesc.ModelId = 0
	Actor_112.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_112.DisplayDesc.Outfit = ""
	Actor_112.DisplayDesc.Weapon = ""
	Actor_112.DisplayDesc.Mode = ""
	Actor_112.DisplayDesc.UseLight = false
	Actor_112.DisplayDesc.CastShadow = false
	Actor_112.DisplayDesc.ColorR = 1
	Actor_112.DisplayDesc.ColorG = 1
	Actor_112.DisplayDesc.ColorB = 1
	Actor_112.DisplayDesc.ColorA = 1
	Actor_112:SetModelState(1)
	Actor_112.PhysicDesc.Pos.X = 482
	Actor_112.PhysicDesc.Pos.Y = 9.76563
	Actor_112.PhysicDesc.Pos.Z = 500.5
	Actor_112.PhysicDesc.Pos.Rotation = 90
	Actor_112.PhysicDesc.Density = 0
	Actor_112.PhysicDesc.Collidable = true
	Actor_112.PhysicDesc.SizeX = 0
	Actor_112.PhysicDesc.SizeY = 0
	Actor_112.PhysicDesc.SizeZ = 0
	Actor_112.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_112:SetPhysicalActorType(1)
	Actor_112:SetPhysicalShape(5)
	Actor_112.ExtraInfo.Name = ""
	Actor_112.ExtraInfo.NameColorR = 0
	Actor_112.ExtraInfo.NameColorG = 0
	Actor_112.ExtraInfo.NameColorB = 0
	Actor_112H = ActorHandler(Actor_112)
	environment:AddActorObject(Actor_112H)

	Actor_113 = ActorObjectInfo(113)
	Actor_113:SetRenderType(1)
	Actor_113.DisplayDesc.ModelId = 0
	Actor_113.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_113.DisplayDesc.Outfit = ""
	Actor_113.DisplayDesc.Weapon = ""
	Actor_113.DisplayDesc.Mode = ""
	Actor_113.DisplayDesc.UseLight = false
	Actor_113.DisplayDesc.CastShadow = false
	Actor_113.DisplayDesc.ColorR = 1
	Actor_113.DisplayDesc.ColorG = 1
	Actor_113.DisplayDesc.ColorB = 1
	Actor_113.DisplayDesc.ColorA = 1
	Actor_113:SetModelState(1)
	Actor_113.PhysicDesc.Pos.X = 482
	Actor_113.PhysicDesc.Pos.Y = 9.76563
	Actor_113.PhysicDesc.Pos.Z = 491.25
	Actor_113.PhysicDesc.Pos.Rotation = 90
	Actor_113.PhysicDesc.Density = 0
	Actor_113.PhysicDesc.Collidable = true
	Actor_113.PhysicDesc.SizeX = 0
	Actor_113.PhysicDesc.SizeY = 0
	Actor_113.PhysicDesc.SizeZ = 0
	Actor_113.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_113:SetPhysicalActorType(1)
	Actor_113:SetPhysicalShape(5)
	Actor_113.ExtraInfo.Name = ""
	Actor_113.ExtraInfo.NameColorR = 0
	Actor_113.ExtraInfo.NameColorG = 0
	Actor_113.ExtraInfo.NameColorB = 0
	Actor_113H = ActorHandler(Actor_113)
	environment:AddActorObject(Actor_113H)

	Actor_114 = ActorObjectInfo(114)
	Actor_114:SetRenderType(1)
	Actor_114.DisplayDesc.ModelId = 0
	Actor_114.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_114.DisplayDesc.Outfit = ""
	Actor_114.DisplayDesc.Weapon = ""
	Actor_114.DisplayDesc.Mode = ""
	Actor_114.DisplayDesc.UseLight = false
	Actor_114.DisplayDesc.CastShadow = false
	Actor_114.DisplayDesc.ColorR = 1
	Actor_114.DisplayDesc.ColorG = 1
	Actor_114.DisplayDesc.ColorB = 1
	Actor_114.DisplayDesc.ColorA = 1
	Actor_114:SetModelState(1)
	Actor_114.PhysicDesc.Pos.X = 482
	Actor_114.PhysicDesc.Pos.Y = 9.76563
	Actor_114.PhysicDesc.Pos.Z = 489.5
	Actor_114.PhysicDesc.Pos.Rotation = 90
	Actor_114.PhysicDesc.Density = 0
	Actor_114.PhysicDesc.Collidable = true
	Actor_114.PhysicDesc.SizeX = 0
	Actor_114.PhysicDesc.SizeY = 0
	Actor_114.PhysicDesc.SizeZ = 0
	Actor_114.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_114:SetPhysicalActorType(1)
	Actor_114:SetPhysicalShape(5)
	Actor_114.ExtraInfo.Name = ""
	Actor_114.ExtraInfo.NameColorR = 0
	Actor_114.ExtraInfo.NameColorG = 0
	Actor_114.ExtraInfo.NameColorB = 0
	Actor_114H = ActorHandler(Actor_114)
	environment:AddActorObject(Actor_114H)

	Actor_115 = ActorObjectInfo(115)
	Actor_115:SetRenderType(1)
	Actor_115.DisplayDesc.ModelId = 0
	Actor_115.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.osgb"
	Actor_115.DisplayDesc.Outfit = ""
	Actor_115.DisplayDesc.Weapon = ""
	Actor_115.DisplayDesc.Mode = ""
	Actor_115.DisplayDesc.UseLight = false
	Actor_115.DisplayDesc.CastShadow = false
	Actor_115.DisplayDesc.ColorR = 1
	Actor_115.DisplayDesc.ColorG = 1
	Actor_115.DisplayDesc.ColorB = 1
	Actor_115.DisplayDesc.ColorA = 1
	Actor_115:SetModelState(1)
	Actor_115.PhysicDesc.Pos.X = 501.5
	Actor_115.PhysicDesc.Pos.Y = 0.976563
	Actor_115.PhysicDesc.Pos.Z = 517.5
	Actor_115.PhysicDesc.Pos.Rotation = 0
	Actor_115.PhysicDesc.Density = 0
	Actor_115.PhysicDesc.Collidable = true
	Actor_115.PhysicDesc.SizeX = 0
	Actor_115.PhysicDesc.SizeY = 0
	Actor_115.PhysicDesc.SizeZ = 0
	Actor_115.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.phy"
	Actor_115:SetPhysicalActorType(1)
	Actor_115:SetPhysicalShape(5)
	Actor_115.ExtraInfo.Name = ""
	Actor_115.ExtraInfo.NameColorR = 0
	Actor_115.ExtraInfo.NameColorG = 0
	Actor_115.ExtraInfo.NameColorB = 0
	Actor_115H = ActorHandler(Actor_115)
	environment:AddActorObject(Actor_115H)

	Actor_116 = ActorObjectInfo(116)
	Actor_116:SetRenderType(1)
	Actor_116.DisplayDesc.ModelId = 0
	Actor_116.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_116.DisplayDesc.Outfit = ""
	Actor_116.DisplayDesc.Weapon = ""
	Actor_116.DisplayDesc.Mode = ""
	Actor_116.DisplayDesc.UseLight = false
	Actor_116.DisplayDesc.CastShadow = false
	Actor_116.DisplayDesc.ColorR = 1
	Actor_116.DisplayDesc.ColorG = 1
	Actor_116.DisplayDesc.ColorB = 1
	Actor_116.DisplayDesc.ColorA = 1
	Actor_116:SetModelState(1)
	Actor_116.PhysicDesc.Pos.X = 520.5
	Actor_116.PhysicDesc.Pos.Y = 17.5781
	Actor_116.PhysicDesc.Pos.Z = 487.5
	Actor_116.PhysicDesc.Pos.Rotation = 0
	Actor_116.PhysicDesc.Density = 0
	Actor_116.PhysicDesc.Collidable = true
	Actor_116.PhysicDesc.SizeX = 0
	Actor_116.PhysicDesc.SizeY = 0
	Actor_116.PhysicDesc.SizeZ = 0
	Actor_116.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
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
	Actor_117.DisplayDesc.ModelId = 0
	Actor_117.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_117.DisplayDesc.Outfit = ""
	Actor_117.DisplayDesc.Weapon = ""
	Actor_117.DisplayDesc.Mode = ""
	Actor_117.DisplayDesc.UseLight = false
	Actor_117.DisplayDesc.CastShadow = false
	Actor_117.DisplayDesc.ColorR = 1
	Actor_117.DisplayDesc.ColorG = 1
	Actor_117.DisplayDesc.ColorB = 1
	Actor_117.DisplayDesc.ColorA = 1
	Actor_117:SetModelState(1)
	Actor_117.PhysicDesc.Pos.X = 504.5
	Actor_117.PhysicDesc.Pos.Y = 13.6719
	Actor_117.PhysicDesc.Pos.Z = 491.5
	Actor_117.PhysicDesc.Pos.Rotation = 180
	Actor_117.PhysicDesc.Density = 0
	Actor_117.PhysicDesc.Collidable = true
	Actor_117.PhysicDesc.SizeX = 0
	Actor_117.PhysicDesc.SizeY = 0
	Actor_117.PhysicDesc.SizeZ = 0
	Actor_117.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_117:SetPhysicalActorType(1)
	Actor_117:SetPhysicalShape(5)
	Actor_117.ExtraInfo.Name = ""
	Actor_117.ExtraInfo.NameColorR = 0
	Actor_117.ExtraInfo.NameColorG = 0
	Actor_117.ExtraInfo.NameColorB = 0
	Actor_117H = ActorHandler(Actor_117)
	environment:AddActorObject(Actor_117H)

	Actor_118 = ActorObjectInfo(118)
	Actor_118:SetRenderType(1)
	Actor_118.DisplayDesc.ModelId = 0
	Actor_118.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_43.osgb"
	Actor_118.DisplayDesc.Outfit = ""
	Actor_118.DisplayDesc.Weapon = ""
	Actor_118.DisplayDesc.Mode = ""
	Actor_118.DisplayDesc.UseLight = false
	Actor_118.DisplayDesc.CastShadow = false
	Actor_118.DisplayDesc.ColorR = 1
	Actor_118.DisplayDesc.ColorG = 1
	Actor_118.DisplayDesc.ColorB = 1
	Actor_118.DisplayDesc.ColorA = 1
	Actor_118:SetModelState(1)
	Actor_118.PhysicDesc.Pos.X = 488.508
	Actor_118.PhysicDesc.Pos.Y = 0.976563
	Actor_118.PhysicDesc.Pos.Z = 538.508
	Actor_118.PhysicDesc.Pos.Rotation = 0
	Actor_118.PhysicDesc.Density = 0
	Actor_118.PhysicDesc.Collidable = true
	Actor_118.PhysicDesc.SizeX = 0
	Actor_118.PhysicDesc.SizeY = 0
	Actor_118.PhysicDesc.SizeZ = 0
	Actor_118.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_43.phy"
	Actor_118:SetPhysicalActorType(1)
	Actor_118:SetPhysicalShape(5)
	Actor_118.ExtraInfo.Name = ""
	Actor_118.ExtraInfo.NameColorR = 0
	Actor_118.ExtraInfo.NameColorG = 0
	Actor_118.ExtraInfo.NameColorB = 0
	Actor_118H = ActorHandler(Actor_118)
	environment:AddActorObject(Actor_118H)

	Actor_119 = ActorObjectInfo(119)
	Actor_119:SetRenderType(1)
	Actor_119.DisplayDesc.ModelId = 0
	Actor_119.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_44.osgb"
	Actor_119.DisplayDesc.Outfit = ""
	Actor_119.DisplayDesc.Weapon = ""
	Actor_119.DisplayDesc.Mode = ""
	Actor_119.DisplayDesc.UseLight = false
	Actor_119.DisplayDesc.CastShadow = false
	Actor_119.DisplayDesc.ColorR = 1
	Actor_119.DisplayDesc.ColorG = 1
	Actor_119.DisplayDesc.ColorB = 1
	Actor_119.DisplayDesc.ColorA = 1
	Actor_119:SetModelState(1)
	Actor_119.PhysicDesc.Pos.X = 541
	Actor_119.PhysicDesc.Pos.Y = 17.5781
	Actor_119.PhysicDesc.Pos.Z = 487
	Actor_119.PhysicDesc.Pos.Rotation = 90
	Actor_119.PhysicDesc.Density = 0
	Actor_119.PhysicDesc.Collidable = true
	Actor_119.PhysicDesc.SizeX = 0
	Actor_119.PhysicDesc.SizeY = 0
	Actor_119.PhysicDesc.SizeZ = 0
	Actor_119.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_44.phy"
	Actor_119:SetPhysicalActorType(1)
	Actor_119:SetPhysicalShape(5)
	Actor_119.ExtraInfo.Name = ""
	Actor_119.ExtraInfo.NameColorR = 0
	Actor_119.ExtraInfo.NameColorG = 0
	Actor_119.ExtraInfo.NameColorB = 0
	Actor_119H = ActorHandler(Actor_119)
	environment:AddActorObject(Actor_119H)

	Actor_120 = ActorObjectInfo(120)
	Actor_120:SetRenderType(1)
	Actor_120.DisplayDesc.ModelId = 0
	Actor_120.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_45.osgb"
	Actor_120.DisplayDesc.Outfit = ""
	Actor_120.DisplayDesc.Weapon = ""
	Actor_120.DisplayDesc.Mode = ""
	Actor_120.DisplayDesc.UseLight = false
	Actor_120.DisplayDesc.CastShadow = false
	Actor_120.DisplayDesc.ColorR = 1
	Actor_120.DisplayDesc.ColorG = 1
	Actor_120.DisplayDesc.ColorB = 1
	Actor_120.DisplayDesc.ColorA = 1
	Actor_120:SetModelState(1)
	Actor_120.PhysicDesc.Pos.X = 541
	Actor_120.PhysicDesc.Pos.Y = 17.5781
	Actor_120.PhysicDesc.Pos.Z = 487
	Actor_120.PhysicDesc.Pos.Rotation = 90
	Actor_120.PhysicDesc.Density = 0
	Actor_120.PhysicDesc.Collidable = true
	Actor_120.PhysicDesc.SizeX = 0
	Actor_120.PhysicDesc.SizeY = 0
	Actor_120.PhysicDesc.SizeZ = 0
	Actor_120.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_45.phy"
	Actor_120:SetPhysicalActorType(1)
	Actor_120:SetPhysicalShape(5)
	Actor_120.ExtraInfo.Name = ""
	Actor_120.ExtraInfo.NameColorR = 0
	Actor_120.ExtraInfo.NameColorG = 0
	Actor_120.ExtraInfo.NameColorB = 0
	Actor_120H = ActorHandler(Actor_120)
	environment:AddActorObject(Actor_120H)

	Actor_121 = ActorObjectInfo(121)
	Actor_121:SetRenderType(1)
	Actor_121.DisplayDesc.ModelId = 0
	Actor_121.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_46.osgb"
	Actor_121.DisplayDesc.Outfit = ""
	Actor_121.DisplayDesc.Weapon = ""
	Actor_121.DisplayDesc.Mode = ""
	Actor_121.DisplayDesc.UseLight = false
	Actor_121.DisplayDesc.CastShadow = false
	Actor_121.DisplayDesc.ColorR = 1
	Actor_121.DisplayDesc.ColorG = 1
	Actor_121.DisplayDesc.ColorB = 1
	Actor_121.DisplayDesc.ColorA = 1
	Actor_121:SetModelState(1)
	Actor_121.PhysicDesc.Pos.X = 541
	Actor_121.PhysicDesc.Pos.Y = 17.5781
	Actor_121.PhysicDesc.Pos.Z = 487
	Actor_121.PhysicDesc.Pos.Rotation = 90
	Actor_121.PhysicDesc.Density = 0
	Actor_121.PhysicDesc.Collidable = true
	Actor_121.PhysicDesc.SizeX = 0
	Actor_121.PhysicDesc.SizeY = 0
	Actor_121.PhysicDesc.SizeZ = 0
	Actor_121.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_46.phy"
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
	Actor_122.DisplayDesc.ModelId = 0
	Actor_122.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_47.osgb"
	Actor_122.DisplayDesc.Outfit = ""
	Actor_122.DisplayDesc.Weapon = ""
	Actor_122.DisplayDesc.Mode = ""
	Actor_122.DisplayDesc.UseLight = false
	Actor_122.DisplayDesc.CastShadow = false
	Actor_122.DisplayDesc.ColorR = 1
	Actor_122.DisplayDesc.ColorG = 1
	Actor_122.DisplayDesc.ColorB = 1
	Actor_122.DisplayDesc.ColorA = 1
	Actor_122:SetModelState(1)
	Actor_122.PhysicDesc.Pos.X = 541
	Actor_122.PhysicDesc.Pos.Y = 17.5781
	Actor_122.PhysicDesc.Pos.Z = 487
	Actor_122.PhysicDesc.Pos.Rotation = 90
	Actor_122.PhysicDesc.Density = 0
	Actor_122.PhysicDesc.Collidable = true
	Actor_122.PhysicDesc.SizeX = 0
	Actor_122.PhysicDesc.SizeY = 0
	Actor_122.PhysicDesc.SizeZ = 0
	Actor_122.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_47.phy"
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
	Actor_123.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_123.DisplayDesc.Outfit = ""
	Actor_123.DisplayDesc.Weapon = ""
	Actor_123.DisplayDesc.Mode = ""
	Actor_123.DisplayDesc.UseLight = false
	Actor_123.DisplayDesc.CastShadow = false
	Actor_123.DisplayDesc.ColorR = 1
	Actor_123.DisplayDesc.ColorG = 1
	Actor_123.DisplayDesc.ColorB = 1
	Actor_123.DisplayDesc.ColorA = 1
	Actor_123:SetModelState(1)
	Actor_123.PhysicDesc.Pos.X = 532
	Actor_123.PhysicDesc.Pos.Y = 17.5781
	Actor_123.PhysicDesc.Pos.Z = 492.5
	Actor_123.PhysicDesc.Pos.Rotation = 90
	Actor_123.PhysicDesc.Density = 0
	Actor_123.PhysicDesc.Collidable = true
	Actor_123.PhysicDesc.SizeX = 0
	Actor_123.PhysicDesc.SizeY = 0
	Actor_123.PhysicDesc.SizeZ = 0
	Actor_123.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
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
	Actor_124.DisplayDesc.ModelId = 0
	Actor_124.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_124.DisplayDesc.Outfit = ""
	Actor_124.DisplayDesc.Weapon = ""
	Actor_124.DisplayDesc.Mode = ""
	Actor_124.DisplayDesc.UseLight = false
	Actor_124.DisplayDesc.CastShadow = false
	Actor_124.DisplayDesc.ColorR = 1
	Actor_124.DisplayDesc.ColorG = 1
	Actor_124.DisplayDesc.ColorB = 1
	Actor_124.DisplayDesc.ColorA = 1
	Actor_124:SetModelState(1)
	Actor_124.PhysicDesc.Pos.X = 539.125
	Actor_124.PhysicDesc.Pos.Y = 17.5781
	Actor_124.PhysicDesc.Pos.Z = 492.5
	Actor_124.PhysicDesc.Pos.Rotation = 90
	Actor_124.PhysicDesc.Density = 0
	Actor_124.PhysicDesc.Collidable = true
	Actor_124.PhysicDesc.SizeX = 0
	Actor_124.PhysicDesc.SizeY = 0
	Actor_124.PhysicDesc.SizeZ = 0
	Actor_124.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_124:SetPhysicalActorType(1)
	Actor_124:SetPhysicalShape(5)
	Actor_124.ExtraInfo.Name = ""
	Actor_124.ExtraInfo.NameColorR = 0
	Actor_124.ExtraInfo.NameColorG = 0
	Actor_124.ExtraInfo.NameColorB = 0
	Actor_124H = ActorHandler(Actor_124)
	environment:AddActorObject(Actor_124H)

	Actor_125 = ActorObjectInfo(125)
	Actor_125:SetRenderType(1)
	Actor_125.DisplayDesc.ModelId = 0
	Actor_125.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_125.DisplayDesc.Outfit = ""
	Actor_125.DisplayDesc.Weapon = ""
	Actor_125.DisplayDesc.Mode = ""
	Actor_125.DisplayDesc.UseLight = false
	Actor_125.DisplayDesc.CastShadow = false
	Actor_125.DisplayDesc.ColorR = 1
	Actor_125.DisplayDesc.ColorG = 1
	Actor_125.DisplayDesc.ColorB = 1
	Actor_125.DisplayDesc.ColorA = 1
	Actor_125:SetModelState(1)
	Actor_125.PhysicDesc.Pos.X = 542.5
	Actor_125.PhysicDesc.Pos.Y = 17.5781
	Actor_125.PhysicDesc.Pos.Z = 487.875
	Actor_125.PhysicDesc.Pos.Rotation = 0
	Actor_125.PhysicDesc.Density = 0
	Actor_125.PhysicDesc.Collidable = true
	Actor_125.PhysicDesc.SizeX = 0
	Actor_125.PhysicDesc.SizeY = 0
	Actor_125.PhysicDesc.SizeZ = 0
	Actor_125.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
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
	Actor_126.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_126.DisplayDesc.Outfit = ""
	Actor_126.DisplayDesc.Weapon = ""
	Actor_126.DisplayDesc.Mode = ""
	Actor_126.DisplayDesc.UseLight = false
	Actor_126.DisplayDesc.CastShadow = false
	Actor_126.DisplayDesc.ColorR = 1
	Actor_126.DisplayDesc.ColorG = 1
	Actor_126.DisplayDesc.ColorB = 1
	Actor_126.DisplayDesc.ColorA = 1
	Actor_126:SetModelState(1)
	Actor_126.PhysicDesc.Pos.X = 523.375
	Actor_126.PhysicDesc.Pos.Y = 17.5781
	Actor_126.PhysicDesc.Pos.Z = 492.5
	Actor_126.PhysicDesc.Pos.Rotation = 90
	Actor_126.PhysicDesc.Density = 0
	Actor_126.PhysicDesc.Collidable = true
	Actor_126.PhysicDesc.SizeX = 0
	Actor_126.PhysicDesc.SizeY = 0
	Actor_126.PhysicDesc.SizeZ = 0
	Actor_126.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_126:SetPhysicalActorType(1)
	Actor_126:SetPhysicalShape(5)
	Actor_126.ExtraInfo.Name = ""
	Actor_126.ExtraInfo.NameColorR = 0
	Actor_126.ExtraInfo.NameColorG = 0
	Actor_126.ExtraInfo.NameColorB = 0
	Actor_126H = ActorHandler(Actor_126)
	environment:AddActorObject(Actor_126H)

	Actor_127 = ActorObjectInfo(127)
	Actor_127:SetRenderType(1)
	Actor_127.DisplayDesc.ModelId = 0
	Actor_127.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_48.osgb"
	Actor_127.DisplayDesc.Outfit = ""
	Actor_127.DisplayDesc.Weapon = ""
	Actor_127.DisplayDesc.Mode = ""
	Actor_127.DisplayDesc.UseLight = false
	Actor_127.DisplayDesc.CastShadow = false
	Actor_127.DisplayDesc.ColorR = 1
	Actor_127.DisplayDesc.ColorG = 1
	Actor_127.DisplayDesc.ColorB = 1
	Actor_127.DisplayDesc.ColorA = 1
	Actor_127:SetModelState(1)
	Actor_127.PhysicDesc.Pos.X = 539.5
	Actor_127.PhysicDesc.Pos.Y = 17.75
	Actor_127.PhysicDesc.Pos.Z = 488.508
	Actor_127.PhysicDesc.Pos.Rotation = 90
	Actor_127.PhysicDesc.Density = 0
	Actor_127.PhysicDesc.Collidable = true
	Actor_127.PhysicDesc.SizeX = 0
	Actor_127.PhysicDesc.SizeY = 0
	Actor_127.PhysicDesc.SizeZ = 0
	Actor_127.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_48.phy"
	Actor_127:SetPhysicalActorType(1)
	Actor_127:SetPhysicalShape(5)
	Actor_127.ExtraInfo.Name = ""
	Actor_127.ExtraInfo.NameColorR = 0
	Actor_127.ExtraInfo.NameColorG = 0
	Actor_127.ExtraInfo.NameColorB = 0
	Actor_127H = ActorHandler(Actor_127)
	environment:AddActorObject(Actor_127H)

	Actor_128 = ActorObjectInfo(128)
	Actor_128:SetRenderType(1)
	Actor_128.DisplayDesc.ModelId = 0
	Actor_128.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_49.osgb"
	Actor_128.DisplayDesc.Outfit = ""
	Actor_128.DisplayDesc.Weapon = ""
	Actor_128.DisplayDesc.Mode = ""
	Actor_128.DisplayDesc.UseLight = false
	Actor_128.DisplayDesc.CastShadow = false
	Actor_128.DisplayDesc.ColorR = 1
	Actor_128.DisplayDesc.ColorG = 1
	Actor_128.DisplayDesc.ColorB = 1
	Actor_128.DisplayDesc.ColorA = 1
	Actor_128:SetModelState(1)
	Actor_128.PhysicDesc.Pos.X = 470.375
	Actor_128.PhysicDesc.Pos.Y = 2.92969
	Actor_128.PhysicDesc.Pos.Z = 555
	Actor_128.PhysicDesc.Pos.Rotation = 90
	Actor_128.PhysicDesc.Density = 0
	Actor_128.PhysicDesc.Collidable = true
	Actor_128.PhysicDesc.SizeX = 0
	Actor_128.PhysicDesc.SizeY = 0
	Actor_128.PhysicDesc.SizeZ = 0
	Actor_128.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_49.phy"
	Actor_128:SetPhysicalActorType(1)
	Actor_128:SetPhysicalShape(5)
	Actor_128.ExtraInfo.Name = ""
	Actor_128.ExtraInfo.NameColorR = 0
	Actor_128.ExtraInfo.NameColorG = 0
	Actor_128.ExtraInfo.NameColorB = 0
	Actor_128H = ActorHandler(Actor_128)
	environment:AddActorObject(Actor_128H)

	Actor_129 = ActorObjectInfo(129)
	Actor_129:SetRenderType(1)
	Actor_129.DisplayDesc.ModelId = 0
	Actor_129.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_50.osgb"
	Actor_129.DisplayDesc.Outfit = ""
	Actor_129.DisplayDesc.Weapon = ""
	Actor_129.DisplayDesc.Mode = ""
	Actor_129.DisplayDesc.UseLight = false
	Actor_129.DisplayDesc.CastShadow = false
	Actor_129.DisplayDesc.ColorR = 1
	Actor_129.DisplayDesc.ColorG = 1
	Actor_129.DisplayDesc.ColorB = 1
	Actor_129.DisplayDesc.ColorA = 1
	Actor_129:SetModelState(1)
	Actor_129.PhysicDesc.Pos.X = 451
	Actor_129.PhysicDesc.Pos.Y = 2.92969
	Actor_129.PhysicDesc.Pos.Z = 556.125
	Actor_129.PhysicDesc.Pos.Rotation = 90
	Actor_129.PhysicDesc.Density = 0
	Actor_129.PhysicDesc.Collidable = true
	Actor_129.PhysicDesc.SizeX = 0
	Actor_129.PhysicDesc.SizeY = 0
	Actor_129.PhysicDesc.SizeZ = 0
	Actor_129.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_50.phy"
	Actor_129:SetPhysicalActorType(1)
	Actor_129:SetPhysicalShape(5)
	Actor_129.ExtraInfo.Name = ""
	Actor_129.ExtraInfo.NameColorR = 0
	Actor_129.ExtraInfo.NameColorG = 0
	Actor_129.ExtraInfo.NameColorB = 0
	Actor_129H = ActorHandler(Actor_129)
	environment:AddActorObject(Actor_129H)

	Actor_130 = ActorObjectInfo(130)
	Actor_130:SetRenderType(1)
	Actor_130.DisplayDesc.ModelId = 0
	Actor_130.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.osgb"
	Actor_130.DisplayDesc.Outfit = ""
	Actor_130.DisplayDesc.Weapon = ""
	Actor_130.DisplayDesc.Mode = ""
	Actor_130.DisplayDesc.UseLight = false
	Actor_130.DisplayDesc.CastShadow = false
	Actor_130.DisplayDesc.ColorR = 1
	Actor_130.DisplayDesc.ColorG = 1
	Actor_130.DisplayDesc.ColorB = 1
	Actor_130.DisplayDesc.ColorA = 1
	Actor_130:SetModelState(1)
	Actor_130.PhysicDesc.Pos.X = 467.5
	Actor_130.PhysicDesc.Pos.Y = 2.92969
	Actor_130.PhysicDesc.Pos.Z = 579.25
	Actor_130.PhysicDesc.Pos.Rotation = 180
	Actor_130.PhysicDesc.Density = 0
	Actor_130.PhysicDesc.Collidable = true
	Actor_130.PhysicDesc.SizeX = 0
	Actor_130.PhysicDesc.SizeY = 0
	Actor_130.PhysicDesc.SizeZ = 0
	Actor_130.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_30.phy"
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
	Actor_131.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_131.DisplayDesc.Outfit = ""
	Actor_131.DisplayDesc.Weapon = ""
	Actor_131.DisplayDesc.Mode = ""
	Actor_131.DisplayDesc.UseLight = false
	Actor_131.DisplayDesc.CastShadow = false
	Actor_131.DisplayDesc.ColorR = 1
	Actor_131.DisplayDesc.ColorG = 1
	Actor_131.DisplayDesc.ColorB = 1
	Actor_131.DisplayDesc.ColorA = 1
	Actor_131:SetModelState(1)
	Actor_131.PhysicDesc.Pos.X = 473.5
	Actor_131.PhysicDesc.Pos.Y = 2.92969
	Actor_131.PhysicDesc.Pos.Z = 571.5
	Actor_131.PhysicDesc.Pos.Rotation = 0
	Actor_131.PhysicDesc.Density = 0
	Actor_131.PhysicDesc.Collidable = true
	Actor_131.PhysicDesc.SizeX = 0
	Actor_131.PhysicDesc.SizeY = 0
	Actor_131.PhysicDesc.SizeZ = 0
	Actor_131.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_131:SetPhysicalActorType(1)
	Actor_131:SetPhysicalShape(5)
	Actor_131.ExtraInfo.Name = ""
	Actor_131.ExtraInfo.NameColorR = 0
	Actor_131.ExtraInfo.NameColorG = 0
	Actor_131.ExtraInfo.NameColorB = 0
	Actor_131H = ActorHandler(Actor_131)
	environment:AddActorObject(Actor_131H)

	Actor_132 = ActorObjectInfo(132)
	Actor_132:SetRenderType(1)
	Actor_132.DisplayDesc.ModelId = 131073
	Actor_132.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_132.DisplayDesc.Outfit = ""
	Actor_132.DisplayDesc.Weapon = ""
	Actor_132.DisplayDesc.Mode = ""
	Actor_132.DisplayDesc.UseLight = false
	Actor_132.DisplayDesc.CastShadow = false
	Actor_132.DisplayDesc.ColorR = 3.78351e-044
	Actor_132.DisplayDesc.ColorG = 1.83671e-040
	Actor_132.DisplayDesc.ColorB = 4.06377e-044
	Actor_132.DisplayDesc.ColorA = 1.83672e-040
	Actor_132:SetModelState(1)
	Actor_132.PhysicDesc.Pos.X = 462.875
	Actor_132.PhysicDesc.Pos.Y = 2.92969
	Actor_132.PhysicDesc.Pos.Z = 560.875
	Actor_132.PhysicDesc.Pos.Rotation = 90
	Actor_132.PhysicDesc.Density = 9.18369e-041
	Actor_132.PhysicDesc.Collidable = true
	Actor_132.PhysicDesc.SizeX = 1.83671e-040
	Actor_132.PhysicDesc.SizeY = 5.88545e-044
	Actor_132.PhysicDesc.SizeZ = 9.18369e-041
	Actor_132.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_132:SetPhysicalActorType(1)
	Actor_132:SetPhysicalShape(5)
	Actor_132.ExtraInfo.Name = ""
	Actor_132.ExtraInfo.NameColorR = 8.54792e-044
	Actor_132.ExtraInfo.NameColorG = 9.18369e-041
	Actor_132.ExtraInfo.NameColorB = 8.68805e-044
	Actor_132H = ActorHandler(Actor_132)
	environment:AddActorObject(Actor_132H)

	Actor_133 = ActorObjectInfo(133)
	Actor_133:SetRenderType(1)
	Actor_133.DisplayDesc.ModelId = 0
	Actor_133.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_133.DisplayDesc.Outfit = ""
	Actor_133.DisplayDesc.Weapon = ""
	Actor_133.DisplayDesc.Mode = ""
	Actor_133.DisplayDesc.UseLight = false
	Actor_133.DisplayDesc.CastShadow = false
	Actor_133.DisplayDesc.ColorR = 1
	Actor_133.DisplayDesc.ColorG = 2.10195e-044
	Actor_133.DisplayDesc.ColorB = 1
	Actor_133.DisplayDesc.ColorA = 1.74108e+025
	Actor_133:SetModelState(1)
	Actor_133.PhysicDesc.Pos.X = 467.75
	Actor_133.PhysicDesc.Pos.Y = 2.92969
	Actor_133.PhysicDesc.Pos.Z = 560.875
	Actor_133.PhysicDesc.Pos.Rotation = 90
	Actor_133.PhysicDesc.Density = 2.10195e-044
	Actor_133.PhysicDesc.Collidable = true
	Actor_133.PhysicDesc.SizeX = 3.49797e-009
	Actor_133.PhysicDesc.SizeY = 1.29926e-008
	Actor_133.PhysicDesc.SizeZ = 2.75506e-040
	Actor_133.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_133:SetPhysicalActorType(1)
	Actor_133:SetPhysicalShape(5)
	Actor_133.ExtraInfo.Name = ""
	Actor_133.ExtraInfo.NameColorR = 1.80642e-031
	Actor_133.ExtraInfo.NameColorG = 1.8064e-031
	Actor_133.ExtraInfo.NameColorB = 1.80642e-031
	Actor_133H = ActorHandler(Actor_133)
	environment:AddActorObject(Actor_133H)

	Actor_134 = ActorObjectInfo(134)
	Actor_134:SetRenderType(1)
	Actor_134.DisplayDesc.ModelId = 750
	Actor_134.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_134.DisplayDesc.Outfit = ""
	Actor_134.DisplayDesc.Weapon = ""
	Actor_134.DisplayDesc.Mode = ""
	Actor_134.DisplayDesc.UseLight = false
	Actor_134.DisplayDesc.CastShadow = true
	Actor_134.DisplayDesc.ColorR = 1
	Actor_134.DisplayDesc.ColorG = 1
	Actor_134.DisplayDesc.ColorB = 2.10195e-044
	Actor_134.DisplayDesc.ColorA = 4.32043e-023
	Actor_134:SetModelState(1)
	Actor_134.PhysicDesc.Pos.X = 457.5
	Actor_134.PhysicDesc.Pos.Y = 2.92969
	Actor_134.PhysicDesc.Pos.Z = 555.25
	Actor_134.PhysicDesc.Pos.Rotation = 90
	Actor_134.PhysicDesc.Density = 0
	Actor_134.PhysicDesc.Collidable = true
	Actor_134.PhysicDesc.SizeX = 0
	Actor_134.PhysicDesc.SizeY = 0
	Actor_134.PhysicDesc.SizeZ = 0
	Actor_134.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_134:SetPhysicalActorType(1)
	Actor_134:SetPhysicalShape(5)
	Actor_134.ExtraInfo.Name = ""
	Actor_134.ExtraInfo.NameColorR = 0
	Actor_134.ExtraInfo.NameColorG = 3.49797e-009
	Actor_134.ExtraInfo.NameColorB = 1.29922e-008
	Actor_134H = ActorHandler(Actor_134)
	environment:AddActorObject(Actor_134H)

	Actor_135 = ActorObjectInfo(135)
	Actor_135:SetRenderType(1)
	Actor_135.DisplayDesc.ModelId = 24707536
	Actor_135.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.osgb"
	Actor_135.DisplayDesc.Outfit = ""
	Actor_135.DisplayDesc.Weapon = ""
	Actor_135.DisplayDesc.Mode = ""
	Actor_135.DisplayDesc.UseLight = false
	Actor_135.DisplayDesc.CastShadow = true
	Actor_135.DisplayDesc.ColorR = 1
	Actor_135.DisplayDesc.ColorG = 1
	Actor_135.DisplayDesc.ColorB = 1
	Actor_135.DisplayDesc.ColorA = 1
	Actor_135:SetModelState(1)
	Actor_135.PhysicDesc.Pos.X = 458.5
	Actor_135.PhysicDesc.Pos.Y = 2.92969
	Actor_135.PhysicDesc.Pos.Z = 560.75
	Actor_135.PhysicDesc.Pos.Rotation = -90
	Actor_135.PhysicDesc.Density = 0
	Actor_135.PhysicDesc.Collidable = true
	Actor_135.PhysicDesc.SizeX = 0
	Actor_135.PhysicDesc.SizeY = 0
	Actor_135.PhysicDesc.SizeZ = 0
	Actor_135.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.phy"
	Actor_135:SetPhysicalActorType(1)
	Actor_135:SetPhysicalShape(5)
	Actor_135.ExtraInfo.Name = ""
	Actor_135.ExtraInfo.NameColorR = 0
	Actor_135.ExtraInfo.NameColorG = 2.10195e-044
	Actor_135.ExtraInfo.NameColorB = 0
	Actor_135H = ActorHandler(Actor_135)
	environment:AddActorObject(Actor_135H)

	Actor_136 = ActorObjectInfo(136)
	Actor_136:SetRenderType(1)
	Actor_136.DisplayDesc.ModelId = 1920234593
	Actor_136.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_136.DisplayDesc.Outfit = ""
	Actor_136.DisplayDesc.Weapon = ""
	Actor_136.DisplayDesc.Mode = ""
	Actor_136.DisplayDesc.UseLight = false
	Actor_136.DisplayDesc.CastShadow = true
	Actor_136.DisplayDesc.ColorR = 1
	Actor_136.DisplayDesc.ColorG = 1
	Actor_136.DisplayDesc.ColorB = 1
	Actor_136.DisplayDesc.ColorA = 1
	Actor_136:SetModelState(1)
	Actor_136.PhysicDesc.Pos.X = 457.5
	Actor_136.PhysicDesc.Pos.Y = 2.92969
	Actor_136.PhysicDesc.Pos.Z = 563.5
	Actor_136.PhysicDesc.Pos.Rotation = 90
	Actor_136.PhysicDesc.Density = 2.10195e-044
	Actor_136.PhysicDesc.Collidable = true
	Actor_136.PhysicDesc.SizeX = 3.49797e-009
	Actor_136.PhysicDesc.SizeY = 1.29913e-008
	Actor_136.PhysicDesc.SizeZ = 0
	Actor_136.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_136:SetPhysicalActorType(1)
	Actor_136:SetPhysicalShape(5)
	Actor_136.ExtraInfo.Name = ""
	Actor_136.ExtraInfo.NameColorR = 0
	Actor_136.ExtraInfo.NameColorG = 0
	Actor_136.ExtraInfo.NameColorB = 0
	Actor_136H = ActorHandler(Actor_136)
	environment:AddActorObject(Actor_136H)

	Actor_137 = ActorObjectInfo(137)
	Actor_137:SetRenderType(1)
	Actor_137.DisplayDesc.ModelId = 750
	Actor_137.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_137.DisplayDesc.Outfit = ""
	Actor_137.DisplayDesc.Weapon = ""
	Actor_137.DisplayDesc.Mode = ""
	Actor_137.DisplayDesc.UseLight = false
	Actor_137.DisplayDesc.CastShadow = true
	Actor_137.DisplayDesc.ColorR = 1
	Actor_137.DisplayDesc.ColorG = 1
	Actor_137.DisplayDesc.ColorB = 2.10195e-044
	Actor_137.DisplayDesc.ColorA = 9.77255e-024
	Actor_137:SetModelState(1)
	Actor_137.PhysicDesc.Pos.X = 458.5
	Actor_137.PhysicDesc.Pos.Y = 2.92969
	Actor_137.PhysicDesc.Pos.Z = 563.5
	Actor_137.PhysicDesc.Pos.Rotation = 90
	Actor_137.PhysicDesc.Density = 0
	Actor_137.PhysicDesc.Collidable = true
	Actor_137.PhysicDesc.SizeX = 0
	Actor_137.PhysicDesc.SizeY = 0
	Actor_137.PhysicDesc.SizeZ = 0
	Actor_137.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_137:SetPhysicalActorType(1)
	Actor_137:SetPhysicalShape(5)
	Actor_137.ExtraInfo.Name = ""
	Actor_137.ExtraInfo.NameColorR = 0
	Actor_137.ExtraInfo.NameColorG = 0
	Actor_137.ExtraInfo.NameColorB = 0
	Actor_137H = ActorHandler(Actor_137)
	environment:AddActorObject(Actor_137H)

	Actor_138 = ActorObjectInfo(138)
	Actor_138:SetRenderType(1)
	Actor_138.DisplayDesc.ModelId = 24707808
	Actor_138.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_138.DisplayDesc.Outfit = ""
	Actor_138.DisplayDesc.Weapon = ""
	Actor_138.DisplayDesc.Mode = ""
	Actor_138.DisplayDesc.UseLight = false
	Actor_138.DisplayDesc.CastShadow = true
	Actor_138.DisplayDesc.ColorR = 1
	Actor_138.DisplayDesc.ColorG = 1
	Actor_138.DisplayDesc.ColorB = 1
	Actor_138.DisplayDesc.ColorA = 1
	Actor_138:SetModelState(1)
	Actor_138.PhysicDesc.Pos.X = 459.5
	Actor_138.PhysicDesc.Pos.Y = 2.92969
	Actor_138.PhysicDesc.Pos.Z = 563.5
	Actor_138.PhysicDesc.Pos.Rotation = 90
	Actor_138.PhysicDesc.Density = 0
	Actor_138.PhysicDesc.Collidable = true
	Actor_138.PhysicDesc.SizeX = 0
	Actor_138.PhysicDesc.SizeY = 0
	Actor_138.PhysicDesc.SizeZ = 0
	Actor_138.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_138:SetPhysicalActorType(1)
	Actor_138:SetPhysicalShape(5)
	Actor_138.ExtraInfo.Name = ""
	Actor_138.ExtraInfo.NameColorR = 0
	Actor_138.ExtraInfo.NameColorG = 2.10195e-044
	Actor_138.ExtraInfo.NameColorB = 0
	Actor_138H = ActorHandler(Actor_138)
	environment:AddActorObject(Actor_138H)

	Actor_139 = ActorObjectInfo(139)
	Actor_139:SetRenderType(1)
	Actor_139.DisplayDesc.ModelId = 0
	Actor_139.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_139.DisplayDesc.Outfit = ""
	Actor_139.DisplayDesc.Weapon = ""
	Actor_139.DisplayDesc.Mode = ""
	Actor_139.DisplayDesc.UseLight = false
	Actor_139.DisplayDesc.CastShadow = true
	Actor_139.DisplayDesc.ColorR = 1
	Actor_139.DisplayDesc.ColorG = 2.10195e-044
	Actor_139.DisplayDesc.ColorB = 1.05326e-034
	Actor_139.DisplayDesc.ColorA = 8.74493e-010
	Actor_139:SetModelState(1)
	Actor_139.PhysicDesc.Pos.X = 460.375
	Actor_139.PhysicDesc.Pos.Y = 2.92969
	Actor_139.PhysicDesc.Pos.Z = 575.125
	Actor_139.PhysicDesc.Pos.Rotation = 90
	Actor_139.PhysicDesc.Density = 2.10195e-044
	Actor_139.PhysicDesc.Collidable = true
	Actor_139.PhysicDesc.SizeX = 4.05562e-008
	Actor_139.PhysicDesc.SizeY = 0
	Actor_139.PhysicDesc.SizeZ = 0
	Actor_139.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_139:SetPhysicalActorType(1)
	Actor_139:SetPhysicalShape(5)
	Actor_139.ExtraInfo.Name = ""
	Actor_139.ExtraInfo.NameColorR = 9.99876e-024
	Actor_139.ExtraInfo.NameColorG = 0
	Actor_139.ExtraInfo.NameColorB = 0
	Actor_139H = ActorHandler(Actor_139)
	environment:AddActorObject(Actor_139H)

	Actor_140 = ActorObjectInfo(140)
	Actor_140:SetRenderType(1)
	Actor_140.DisplayDesc.ModelId = 144541660
	Actor_140.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_140.DisplayDesc.Outfit = ""
	Actor_140.DisplayDesc.Weapon = ""
	Actor_140.DisplayDesc.Mode = ""
	Actor_140.DisplayDesc.UseLight = false
	Actor_140.DisplayDesc.CastShadow = false
	Actor_140.DisplayDesc.ColorR = 1
	Actor_140.DisplayDesc.ColorG = 1
	Actor_140.DisplayDesc.ColorB = 2.10195e-044
	Actor_140.DisplayDesc.ColorA = 1.02219e-023
	Actor_140:SetModelState(1)
	Actor_140.PhysicDesc.Pos.X = 454.375
	Actor_140.PhysicDesc.Pos.Y = 2.92969
	Actor_140.PhysicDesc.Pos.Z = 575.125
	Actor_140.PhysicDesc.Pos.Rotation = 90
	Actor_140.PhysicDesc.Density = 4.57358e-038
	Actor_140.PhysicDesc.Collidable = true
	Actor_140.PhysicDesc.SizeX = 0.01
	Actor_140.PhysicDesc.SizeY = 9.80909e-045
	Actor_140.PhysicDesc.SizeZ = 2.75547e-040
	Actor_140.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_140:SetPhysicalActorType(1)
	Actor_140:SetPhysicalShape(5)
	Actor_140.ExtraInfo.Name = ""
	Actor_140.ExtraInfo.NameColorR = 1.61054e-023
	Actor_140.ExtraInfo.NameColorG = 1.93131e-023
	Actor_140.ExtraInfo.NameColorB = 6.35964e-024
	Actor_140H = ActorHandler(Actor_140)
	environment:AddActorObject(Actor_140H)

	Actor_141 = ActorObjectInfo(141)
	Actor_141:SetRenderType(1)
	Actor_141.DisplayDesc.ModelId = 1953524082
	Actor_141.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_141.DisplayDesc.Outfit = ""
	Actor_141.DisplayDesc.Weapon = ""
	Actor_141.DisplayDesc.Mode = ""
	Actor_141.DisplayDesc.UseLight = false
	Actor_141.DisplayDesc.CastShadow = true
	Actor_141.DisplayDesc.ColorR = 1
	Actor_141.DisplayDesc.ColorG = 1
	Actor_141.DisplayDesc.ColorB = 1
	Actor_141.DisplayDesc.ColorA = 1
	Actor_141:SetModelState(1)
	Actor_141.PhysicDesc.Pos.X = 442.625
	Actor_141.PhysicDesc.Pos.Y = 2.92969
	Actor_141.PhysicDesc.Pos.Z = 575.125
	Actor_141.PhysicDesc.Pos.Rotation = 90
	Actor_141.PhysicDesc.Density = 2.10195e-044
	Actor_141.PhysicDesc.Collidable = true
	Actor_141.PhysicDesc.SizeX = 0
	Actor_141.PhysicDesc.SizeY = 0
	Actor_141.PhysicDesc.SizeZ = 0
	Actor_141.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_141:SetPhysicalActorType(1)
	Actor_141:SetPhysicalShape(5)
	Actor_141.ExtraInfo.Name = ""
	Actor_141.ExtraInfo.NameColorR = 0
	Actor_141.ExtraInfo.NameColorG = 0
	Actor_141.ExtraInfo.NameColorB = 0
	Actor_141H = ActorHandler(Actor_141)
	environment:AddActorObject(Actor_141H)

	Actor_142 = ActorObjectInfo(142)
	Actor_142:SetRenderType(1)
	Actor_142.DisplayDesc.ModelId = 131074
	Actor_142.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_142.DisplayDesc.Outfit = ""
	Actor_142.DisplayDesc.Weapon = ""
	Actor_142.DisplayDesc.Mode = ""
	Actor_142.DisplayDesc.UseLight = false
	Actor_142.DisplayDesc.CastShadow = false
	Actor_142.DisplayDesc.ColorR = 2.10195e-044
	Actor_142.DisplayDesc.ColorG = 1
	Actor_142.DisplayDesc.ColorB = 2.10195e-044
	Actor_142.DisplayDesc.ColorA = 3.02379e-023
	Actor_142:SetModelState(1)
	Actor_142.PhysicDesc.Pos.X = 436.625
	Actor_142.PhysicDesc.Pos.Y = 2.92969
	Actor_142.PhysicDesc.Pos.Z = 575.125
	Actor_142.PhysicDesc.Pos.Rotation = 90
	Actor_142.PhysicDesc.Density = -0.9375
	Actor_142.PhysicDesc.Collidable = true
	Actor_142.PhysicDesc.SizeX = -0.9375
	Actor_142.PhysicDesc.SizeY = 0.9375
	Actor_142.PhysicDesc.SizeZ = 6.25
	Actor_142.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_142:SetPhysicalActorType(1)
	Actor_142:SetPhysicalShape(5)
	Actor_142.ExtraInfo.Name = ""
	Actor_142.ExtraInfo.NameColorR = 0
	Actor_142.ExtraInfo.NameColorG = 4.05607e-008
	Actor_142.ExtraInfo.NameColorB = 0
	Actor_142H = ActorHandler(Actor_142)
	environment:AddActorObject(Actor_142H)

	Actor_143 = ActorObjectInfo(143)
	Actor_143:SetRenderType(1)
	Actor_143.DisplayDesc.ModelId = 24707816
	Actor_143.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_143.DisplayDesc.Outfit = ""
	Actor_143.DisplayDesc.Weapon = ""
	Actor_143.DisplayDesc.Mode = ""
	Actor_143.DisplayDesc.UseLight = false
	Actor_143.DisplayDesc.CastShadow = true
	Actor_143.DisplayDesc.ColorR = 1
	Actor_143.DisplayDesc.ColorG = 1
	Actor_143.DisplayDesc.ColorB = 1
	Actor_143.DisplayDesc.ColorA = 1
	Actor_143:SetModelState(1)
	Actor_143.PhysicDesc.Pos.X = 430.875
	Actor_143.PhysicDesc.Pos.Y = 2.92969
	Actor_143.PhysicDesc.Pos.Z = 571.875
	Actor_143.PhysicDesc.Pos.Rotation = 90
	Actor_143.PhysicDesc.Density = 3.63889e-041
	Actor_143.PhysicDesc.Collidable = true
	Actor_143.PhysicDesc.SizeX = 2.10195e-044
	Actor_143.PhysicDesc.SizeY = 0
	Actor_143.PhysicDesc.SizeZ = 0
	Actor_143.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_143:SetPhysicalActorType(1)
	Actor_143:SetPhysicalShape(5)
	Actor_143.ExtraInfo.Name = ""
	Actor_143.ExtraInfo.NameColorR = 0
	Actor_143.ExtraInfo.NameColorG = 0
	Actor_143.ExtraInfo.NameColorB = 0
	Actor_143H = ActorHandler(Actor_143)
	environment:AddActorObject(Actor_143H)

	Actor_144 = ActorObjectInfo(144)
	Actor_144:SetRenderType(1)
	Actor_144.DisplayDesc.ModelId = 144541660
	Actor_144.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_144.DisplayDesc.Outfit = ""
	Actor_144.DisplayDesc.Weapon = ""
	Actor_144.DisplayDesc.Mode = ""
	Actor_144.DisplayDesc.UseLight = false
	Actor_144.DisplayDesc.CastShadow = false
	Actor_144.DisplayDesc.ColorR = 1
	Actor_144.DisplayDesc.ColorG = 1
	Actor_144.DisplayDesc.ColorB = 1
	Actor_144.DisplayDesc.ColorA = 1
	Actor_144:SetModelState(1)
	Actor_144.PhysicDesc.Pos.X = 446.875
	Actor_144.PhysicDesc.Pos.Y = 2.92969
	Actor_144.PhysicDesc.Pos.Z = 571.875
	Actor_144.PhysicDesc.Pos.Rotation = 90
	Actor_144.PhysicDesc.Density = 5.9044e-023
	Actor_144.PhysicDesc.Collidable = true
	Actor_144.PhysicDesc.SizeX = 0.01
	Actor_144.PhysicDesc.SizeY = 0
	Actor_144.PhysicDesc.SizeZ = 0
	Actor_144.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_144:SetPhysicalActorType(1)
	Actor_144:SetPhysicalShape(5)
	Actor_144.ExtraInfo.Name = ""
	Actor_144.ExtraInfo.NameColorR = 2.8026e-045
	Actor_144.ExtraInfo.NameColorG = 0
	Actor_144.ExtraInfo.NameColorB = 0
	Actor_144H = ActorHandler(Actor_144)
	environment:AddActorObject(Actor_144H)

	Actor_145 = ActorObjectInfo(145)
	Actor_145:SetRenderType(1)
	Actor_145.DisplayDesc.ModelId = 1065353216
	Actor_145.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_145.DisplayDesc.Outfit = ""
	Actor_145.DisplayDesc.Weapon = ""
	Actor_145.DisplayDesc.Mode = ""
	Actor_145.DisplayDesc.UseLight = false
	Actor_145.DisplayDesc.CastShadow = false
	Actor_145.DisplayDesc.ColorR = 1
	Actor_145.DisplayDesc.ColorG = 1
	Actor_145.DisplayDesc.ColorB = 1
	Actor_145.DisplayDesc.ColorA = 1
	Actor_145:SetModelState(1)
	Actor_145.PhysicDesc.Pos.X = 430.875
	Actor_145.PhysicDesc.Pos.Y = 2.92969
	Actor_145.PhysicDesc.Pos.Z = 582.5
	Actor_145.PhysicDesc.Pos.Rotation = 90
	Actor_145.PhysicDesc.Density = 1
	Actor_145.PhysicDesc.Collidable = true
	Actor_145.PhysicDesc.SizeX = 1
	Actor_145.PhysicDesc.SizeY = 1
	Actor_145.PhysicDesc.SizeZ = 1
	Actor_145.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_145:SetPhysicalActorType(1)
	Actor_145:SetPhysicalShape(5)
	Actor_145.ExtraInfo.Name = ""
	Actor_145.ExtraInfo.NameColorR = 1
	Actor_145.ExtraInfo.NameColorG = 1
	Actor_145.ExtraInfo.NameColorB = 1
	Actor_145H = ActorHandler(Actor_145)
	environment:AddActorObject(Actor_145H)

	Actor_146 = ActorObjectInfo(146)
	Actor_146:SetRenderType(1)
	Actor_146.DisplayDesc.ModelId = 1065353216
	Actor_146.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_146.DisplayDesc.Outfit = ""
	Actor_146.DisplayDesc.Weapon = ""
	Actor_146.DisplayDesc.Mode = ""
	Actor_146.DisplayDesc.UseLight = false
	Actor_146.DisplayDesc.CastShadow = false
	Actor_146.DisplayDesc.ColorR = 1
	Actor_146.DisplayDesc.ColorG = 1
	Actor_146.DisplayDesc.ColorB = 1
	Actor_146.DisplayDesc.ColorA = 1
	Actor_146:SetModelState(1)
	Actor_146.PhysicDesc.Pos.X = 470.5
	Actor_146.PhysicDesc.Pos.Y = 2.92969
	Actor_146.PhysicDesc.Pos.Z = 564.5
	Actor_146.PhysicDesc.Pos.Rotation = 90
	Actor_146.PhysicDesc.Density = 1
	Actor_146.PhysicDesc.Collidable = true
	Actor_146.PhysicDesc.SizeX = 1
	Actor_146.PhysicDesc.SizeY = 1
	Actor_146.PhysicDesc.SizeZ = 1
	Actor_146.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
	Actor_146:SetPhysicalActorType(1)
	Actor_146:SetPhysicalShape(5)
	Actor_146.ExtraInfo.Name = ""
	Actor_146.ExtraInfo.NameColorR = 1
	Actor_146.ExtraInfo.NameColorG = 1
	Actor_146.ExtraInfo.NameColorB = 1
	Actor_146H = ActorHandler(Actor_146)
	environment:AddActorObject(Actor_146H)

	Actor_147 = ActorObjectInfo(147)
	Actor_147:SetRenderType(1)
	Actor_147.DisplayDesc.ModelId = 750
	Actor_147.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_147.DisplayDesc.Outfit = ""
	Actor_147.DisplayDesc.Weapon = ""
	Actor_147.DisplayDesc.Mode = ""
	Actor_147.DisplayDesc.UseLight = false
	Actor_147.DisplayDesc.CastShadow = true
	Actor_147.DisplayDesc.ColorR = 1
	Actor_147.DisplayDesc.ColorG = 1
	Actor_147.DisplayDesc.ColorB = 1
	Actor_147.DisplayDesc.ColorA = 1
	Actor_147:SetModelState(1)
	Actor_147.PhysicDesc.Pos.X = 479
	Actor_147.PhysicDesc.Pos.Y = 2.92969
	Actor_147.PhysicDesc.Pos.Z = 563.969
	Actor_147.PhysicDesc.Pos.Rotation = 0
	Actor_147.PhysicDesc.Density = 0
	Actor_147.PhysicDesc.Collidable = true
	Actor_147.PhysicDesc.SizeX = 0
	Actor_147.PhysicDesc.SizeY = 0
	Actor_147.PhysicDesc.SizeZ = 0
	Actor_147.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_147:SetPhysicalActorType(1)
	Actor_147:SetPhysicalShape(5)
	Actor_147.ExtraInfo.Name = ""
	Actor_147.ExtraInfo.NameColorR = 0
	Actor_147.ExtraInfo.NameColorG = 0
	Actor_147.ExtraInfo.NameColorB = 0
	Actor_147H = ActorHandler(Actor_147)
	environment:AddActorObject(Actor_147H)

	Actor_148 = ActorObjectInfo(148)
	Actor_148:SetRenderType(1)
	Actor_148.DisplayDesc.ModelId = -1
	Actor_148.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_148.DisplayDesc.Outfit = ""
	Actor_148.DisplayDesc.Weapon = ""
	Actor_148.DisplayDesc.Mode = ""
	Actor_148.DisplayDesc.UseLight = false
	Actor_148.DisplayDesc.CastShadow = false
	Actor_148.DisplayDesc.ColorR = 1
	Actor_148.DisplayDesc.ColorG = 1
	Actor_148.DisplayDesc.ColorB = 1
	Actor_148.DisplayDesc.ColorA = 1
	Actor_148:SetModelState(1)
	Actor_148.PhysicDesc.Pos.X = 479
	Actor_148.PhysicDesc.Pos.Y = 2.92969
	Actor_148.PhysicDesc.Pos.Z = 570
	Actor_148.PhysicDesc.Pos.Rotation = 0
	Actor_148.PhysicDesc.Density = 3.30611e-039
	Actor_148.PhysicDesc.Collidable = true
	Actor_148.PhysicDesc.SizeX = 4.57356e-038
	Actor_148.PhysicDesc.SizeY = 5.29617e-023
	Actor_148.PhysicDesc.SizeZ = 1.83699e-040
	Actor_148.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_148:SetPhysicalActorType(1)
	Actor_148:SetPhysicalShape(5)
	Actor_148.ExtraInfo.Name = ""
	Actor_148.ExtraInfo.NameColorR = 5.49743e-023
	Actor_148.ExtraInfo.NameColorG = 1.83682e-040
	Actor_148.ExtraInfo.NameColorB = 1.05325e-034
	Actor_148H = ActorHandler(Actor_148)
	environment:AddActorObject(Actor_148H)

	Actor_149 = ActorObjectInfo(149)
	Actor_149:SetRenderType(1)
	Actor_149.DisplayDesc.ModelId = 144577628
	Actor_149.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_149.DisplayDesc.Outfit = ""
	Actor_149.DisplayDesc.Weapon = ""
	Actor_149.DisplayDesc.Mode = ""
	Actor_149.DisplayDesc.UseLight = false
	Actor_149.DisplayDesc.CastShadow = false
	Actor_149.DisplayDesc.ColorR = 4.34403e-044
	Actor_149.DisplayDesc.ColorG = 1.65309e-039
	Actor_149.DisplayDesc.ColorB = 2.55791e-035
	Actor_149.DisplayDesc.ColorA = 4.5736e-038
	Actor_149:SetModelState(1)
	Actor_149.PhysicDesc.Pos.X = 478.992
	Actor_149.PhysicDesc.Pos.Y = 2.92969
	Actor_149.PhysicDesc.Pos.Z = 576
	Actor_149.PhysicDesc.Pos.Rotation = 0
	Actor_149.PhysicDesc.Density = 0
	Actor_149.PhysicDesc.Collidable = true
	Actor_149.PhysicDesc.SizeX = 0
	Actor_149.PhysicDesc.SizeY = 0.0625
	Actor_149.PhysicDesc.SizeZ = 4.33984
	Actor_149.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_149:SetPhysicalActorType(1)
	Actor_149:SetPhysicalShape(5)
	Actor_149.ExtraInfo.Name = ""
	Actor_149.ExtraInfo.NameColorR = 7.0521e-031
	Actor_149.ExtraInfo.NameColorG = 9.18369e-040
	Actor_149.ExtraInfo.NameColorB = 7.34698e-040
	Actor_149H = ActorHandler(Actor_149)
	environment:AddActorObject(Actor_149H)

	Actor_150 = ActorObjectInfo(150)
	Actor_150:SetRenderType(1)
	Actor_150.DisplayDesc.ModelId = 0
	Actor_150.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_150.DisplayDesc.Outfit = ""
	Actor_150.DisplayDesc.Weapon = ""
	Actor_150.DisplayDesc.Mode = ""
	Actor_150.DisplayDesc.UseLight = false
	Actor_150.DisplayDesc.CastShadow = false
	Actor_150.DisplayDesc.ColorR = 1.4013e-045
	Actor_150.DisplayDesc.ColorG = 1
	Actor_150.DisplayDesc.ColorB = 1
	Actor_150.DisplayDesc.ColorA = 1
	Actor_150:SetModelState(1)
	Actor_150.PhysicDesc.Pos.X = 478.5
	Actor_150.PhysicDesc.Pos.Y = 2.92969
	Actor_150.PhysicDesc.Pos.Z = 561
	Actor_150.PhysicDesc.Pos.Rotation = 90
	Actor_150.PhysicDesc.Density = 6.33541e-024
	Actor_150.PhysicDesc.Collidable = true
	Actor_150.PhysicDesc.SizeX = 7.00649e-044
	Actor_150.PhysicDesc.SizeY = 0
	Actor_150.PhysicDesc.SizeZ = 0
	Actor_150.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_150:SetPhysicalActorType(1)
	Actor_150:SetPhysicalShape(5)
	Actor_150.ExtraInfo.Name = ""
	Actor_150.ExtraInfo.NameColorR = -1
	Actor_150.ExtraInfo.NameColorG = 0
	Actor_150.ExtraInfo.NameColorB = 0
	Actor_150H = ActorHandler(Actor_150)
	environment:AddActorObject(Actor_150H)

	Actor_151 = ActorObjectInfo(151)
	Actor_151:SetRenderType(1)
	Actor_151.DisplayDesc.ModelId = 445578216
	Actor_151.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.osgb"
	Actor_151.DisplayDesc.Outfit = ""
	Actor_151.DisplayDesc.Weapon = ""
	Actor_151.DisplayDesc.Mode = ""
	Actor_151.DisplayDesc.UseLight = false
	Actor_151.DisplayDesc.CastShadow = false
	Actor_151.DisplayDesc.ColorR = 1.82169e-044
	Actor_151.DisplayDesc.ColorG = 1.54143e-044
	Actor_151.DisplayDesc.ColorB = 1.82169e-044
	Actor_151.DisplayDesc.ColorA = 1.96182e-044
	Actor_151:SetModelState(1)
	Actor_151.PhysicDesc.Pos.X = 458.5
	Actor_151.PhysicDesc.Pos.Y = 2.92969
	Actor_151.PhysicDesc.Pos.Z = 560.75
	Actor_151.PhysicDesc.Pos.Rotation = -90
	Actor_151.PhysicDesc.Density = 3.36312e-044
	Actor_151.PhysicDesc.Collidable = true
	Actor_151.PhysicDesc.SizeX = 3.22299e-044
	Actor_151.PhysicDesc.SizeY = 3.50325e-044
	Actor_151.PhysicDesc.SizeZ = 3.64338e-044
	Actor_151.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.phy"
	Actor_151:SetPhysicalActorType(1)
	Actor_151:SetPhysicalShape(5)
	Actor_151.ExtraInfo.Name = ""
	Actor_151.ExtraInfo.NameColorR = 0
	Actor_151.ExtraInfo.NameColorG = 0
	Actor_151.ExtraInfo.NameColorB = 0
	Actor_151H = ActorHandler(Actor_151)
	environment:AddActorObject(Actor_151H)

	Actor_152 = ActorObjectInfo(152)
	Actor_152:SetRenderType(1)
	Actor_152.DisplayDesc.ModelId = 131074
	Actor_152.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_152.DisplayDesc.Outfit = ""
	Actor_152.DisplayDesc.Weapon = ""
	Actor_152.DisplayDesc.Mode = ""
	Actor_152.DisplayDesc.UseLight = false
	Actor_152.DisplayDesc.CastShadow = false
	Actor_152.DisplayDesc.ColorR = 1
	Actor_152.DisplayDesc.ColorG = 1
	Actor_152.DisplayDesc.ColorB = 2.10195e-044
	Actor_152.DisplayDesc.ColorA = 9.03444e-024
	Actor_152:SetModelState(1)
	Actor_152.PhysicDesc.Pos.X = 459.188
	Actor_152.PhysicDesc.Pos.Y = 2.92969
	Actor_152.PhysicDesc.Pos.Z = 550.5
	Actor_152.PhysicDesc.Pos.Rotation = -90
	Actor_152.PhysicDesc.Density = -6.25926e+018
	Actor_152.PhysicDesc.Collidable = true
	Actor_152.PhysicDesc.SizeX = 9.51407e-034
	Actor_152.PhysicDesc.SizeY = 9.12055e-024
	Actor_152.PhysicDesc.SizeZ = 9.56017e-034
	Actor_152.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_152:SetPhysicalActorType(1)
	Actor_152:SetPhysicalShape(5)
	Actor_152.ExtraInfo.Name = ""
	Actor_152.ExtraInfo.NameColorR = 1.06071e-030
	Actor_152.ExtraInfo.NameColorG = 1
	Actor_152.ExtraInfo.NameColorB = 0
	Actor_152H = ActorHandler(Actor_152)
	environment:AddActorObject(Actor_152H)

	Actor_153 = ActorObjectInfo(153)
	Actor_153:SetRenderType(1)
	Actor_153.DisplayDesc.ModelId = 750
	Actor_153.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_153.DisplayDesc.Outfit = ""
	Actor_153.DisplayDesc.Weapon = ""
	Actor_153.DisplayDesc.Mode = ""
	Actor_153.DisplayDesc.UseLight = false
	Actor_153.DisplayDesc.CastShadow = true
	Actor_153.DisplayDesc.ColorR = 1
	Actor_153.DisplayDesc.ColorG = 1
	Actor_153.DisplayDesc.ColorB = 1
	Actor_153.DisplayDesc.ColorA = 1
	Actor_153:SetModelState(1)
	Actor_153.PhysicDesc.Pos.X = 457.234
	Actor_153.PhysicDesc.Pos.Y = 2.92969
	Actor_153.PhysicDesc.Pos.Z = 550.5
	Actor_153.PhysicDesc.Pos.Rotation = -90
	Actor_153.PhysicDesc.Density = 0
	Actor_153.PhysicDesc.Collidable = true
	Actor_153.PhysicDesc.SizeX = 0
	Actor_153.PhysicDesc.SizeY = 0
	Actor_153.PhysicDesc.SizeZ = 0
	Actor_153.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_153:SetPhysicalActorType(1)
	Actor_153:SetPhysicalShape(5)
	Actor_153.ExtraInfo.Name = ""
	Actor_153.ExtraInfo.NameColorR = 0
	Actor_153.ExtraInfo.NameColorG = 0
	Actor_153.ExtraInfo.NameColorB = 0
	Actor_153H = ActorHandler(Actor_153)
	environment:AddActorObject(Actor_153H)

	Actor_154 = ActorObjectInfo(154)
	Actor_154:SetRenderType(1)
	Actor_154.DisplayDesc.ModelId = 1065353216
	Actor_154.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_154.DisplayDesc.Outfit = ""
	Actor_154.DisplayDesc.Weapon = ""
	Actor_154.DisplayDesc.Mode = ""
	Actor_154.DisplayDesc.UseLight = false
	Actor_154.DisplayDesc.CastShadow = true
	Actor_154.DisplayDesc.ColorR = 1
	Actor_154.DisplayDesc.ColorG = 1
	Actor_154.DisplayDesc.ColorB = 1
	Actor_154.DisplayDesc.ColorA = 1
	Actor_154:SetModelState(1)
	Actor_154.PhysicDesc.Pos.X = 455.281
	Actor_154.PhysicDesc.Pos.Y = 2.92969
	Actor_154.PhysicDesc.Pos.Z = 550.5
	Actor_154.PhysicDesc.Pos.Rotation = -90
	Actor_154.PhysicDesc.Density = -3.40282e+038
	Actor_154.PhysicDesc.Collidable = true
	Actor_154.PhysicDesc.SizeX = 7.77941e-024
	Actor_154.PhysicDesc.SizeY = 2.8026e-045
	Actor_154.PhysicDesc.SizeZ = 0
	Actor_154.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_154:SetPhysicalActorType(1)
	Actor_154:SetPhysicalShape(5)
	Actor_154.ExtraInfo.Name = ""
	Actor_154.ExtraInfo.NameColorR = 0
	Actor_154.ExtraInfo.NameColorG = 7.77941e-024
	Actor_154.ExtraInfo.NameColorB = 0
	Actor_154H = ActorHandler(Actor_154)
	environment:AddActorObject(Actor_154H)

	Actor_155 = ActorObjectInfo(155)
	Actor_155:SetRenderType(1)
	Actor_155.DisplayDesc.ModelId = 0
	Actor_155.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_55.osgb"
	Actor_155.DisplayDesc.Outfit = ""
	Actor_155.DisplayDesc.Weapon = ""
	Actor_155.DisplayDesc.Mode = ""
	Actor_155.DisplayDesc.UseLight = false
	Actor_155.DisplayDesc.CastShadow = true
	Actor_155.DisplayDesc.ColorR = 1
	Actor_155.DisplayDesc.ColorG = 1
	Actor_155.DisplayDesc.ColorB = 1
	Actor_155.DisplayDesc.ColorA = 1
	Actor_155:SetModelState(1)
	Actor_155.PhysicDesc.Pos.X = 461.031
	Actor_155.PhysicDesc.Pos.Y = 2.92969
	Actor_155.PhysicDesc.Pos.Z = 550.5
	Actor_155.PhysicDesc.Pos.Rotation = 90
	Actor_155.PhysicDesc.Density = 1.4013e-044
	Actor_155.PhysicDesc.Collidable = true
	Actor_155.PhysicDesc.SizeX = 5.5103e-040
	Actor_155.PhysicDesc.SizeY = 1.05327e-034
	Actor_155.PhysicDesc.SizeZ = 1.13133e-023
	Actor_155.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_55.phy"
	Actor_155:SetPhysicalActorType(1)
	Actor_155:SetPhysicalShape(5)
	Actor_155.ExtraInfo.Name = ""
	Actor_155.ExtraInfo.NameColorR = 0
	Actor_155.ExtraInfo.NameColorG = 3.60134e-043
	Actor_155.ExtraInfo.NameColorB = 2.10195e-044
	Actor_155H = ActorHandler(Actor_155)
	environment:AddActorObject(Actor_155H)

	Actor_156 = ActorObjectInfo(156)
	Actor_156:SetRenderType(1)
	Actor_156.DisplayDesc.ModelId = 128
	Actor_156.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_56.osgb"
	Actor_156.DisplayDesc.Outfit = ""
	Actor_156.DisplayDesc.Weapon = ""
	Actor_156.DisplayDesc.Mode = ""
	Actor_156.DisplayDesc.UseLight = false
	Actor_156.DisplayDesc.CastShadow = false
	Actor_156.DisplayDesc.ColorR = 1
	Actor_156.DisplayDesc.ColorG = 1
	Actor_156.DisplayDesc.ColorB = 1
	Actor_156.DisplayDesc.ColorA = 1
	Actor_156:SetModelState(1)
	Actor_156.PhysicDesc.Pos.X = 432.008
	Actor_156.PhysicDesc.Pos.Y = 0.015625
	Actor_156.PhysicDesc.Pos.Z = 584.992
	Actor_156.PhysicDesc.Pos.Rotation = -90
	Actor_156.PhysicDesc.Density = 0
	Actor_156.PhysicDesc.Collidable = true
	Actor_156.PhysicDesc.SizeX = 0
	Actor_156.PhysicDesc.SizeY = 0
	Actor_156.PhysicDesc.SizeZ = 0
	Actor_156.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_56.phy"
	Actor_156:SetPhysicalActorType(1)
	Actor_156:SetPhysicalShape(5)
	Actor_156.ExtraInfo.Name = ""
	Actor_156.ExtraInfo.NameColorR = 1.37753e-039
	Actor_156.ExtraInfo.NameColorG = 3.67342e-040
	Actor_156.ExtraInfo.NameColorB = 0
	Actor_156H = ActorHandler(Actor_156)
	environment:AddActorObject(Actor_156H)

	Actor_157 = ActorObjectInfo(157)
	Actor_157:SetRenderType(1)
	Actor_157.DisplayDesc.ModelId = 427058952
	Actor_157.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_57.osgb"
	Actor_157.DisplayDesc.Outfit = ""
	Actor_157.DisplayDesc.Weapon = ""
	Actor_157.DisplayDesc.Mode = ""
	Actor_157.DisplayDesc.UseLight = false
	Actor_157.DisplayDesc.CastShadow = false
	Actor_157.DisplayDesc.ColorR = 3.08286e-044
	Actor_157.DisplayDesc.ColorG = 1
	Actor_157.DisplayDesc.ColorB = 1
	Actor_157.DisplayDesc.ColorA = 1
	Actor_157:SetModelState(1)
	Actor_157.PhysicDesc.Pos.X = 433.656
	Actor_157.PhysicDesc.Pos.Y = 0
	Actor_157.PhysicDesc.Pos.Z = 589.25
	Actor_157.PhysicDesc.Pos.Rotation = 0
	Actor_157.PhysicDesc.Density = 0
	Actor_157.PhysicDesc.Collidable = true
	Actor_157.PhysicDesc.SizeX = 0
	Actor_157.PhysicDesc.SizeY = 0
	Actor_157.PhysicDesc.SizeZ = 0
	Actor_157.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_57.phy"
	Actor_157:SetPhysicalActorType(1)
	Actor_157:SetPhysicalShape(5)
	Actor_157.ExtraInfo.Name = ""
	Actor_157.ExtraInfo.NameColorR = 0
	Actor_157.ExtraInfo.NameColorG = 0
	Actor_157.ExtraInfo.NameColorB = -5.88545e-044
	Actor_157H = ActorHandler(Actor_157)
	environment:AddActorObject(Actor_157H)

	Actor_158 = ActorObjectInfo(158)
	Actor_158:SetRenderType(1)
	Actor_158.DisplayDesc.ModelId = 0
	Actor_158.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_158.DisplayDesc.Outfit = ""
	Actor_158.DisplayDesc.Weapon = ""
	Actor_158.DisplayDesc.Mode = ""
	Actor_158.DisplayDesc.UseLight = false
	Actor_158.DisplayDesc.CastShadow = false
	Actor_158.DisplayDesc.ColorR = 1.47094e-041
	Actor_158.DisplayDesc.ColorG = 1.47094e-041
	Actor_158.DisplayDesc.ColorB = 1.4708e-041
	Actor_158.DisplayDesc.ColorA = 1.36332e-041
	Actor_158:SetModelState(1)
	Actor_158.PhysicDesc.Pos.X = 506.5
	Actor_158.PhysicDesc.Pos.Y = 2.44141
	Actor_158.PhysicDesc.Pos.Z = 583.5
	Actor_158.PhysicDesc.Pos.Rotation = 90
	Actor_158.PhysicDesc.Density = 0
	Actor_158.PhysicDesc.Collidable = true
	Actor_158.PhysicDesc.SizeX = 0
	Actor_158.PhysicDesc.SizeY = 0
	Actor_158.PhysicDesc.SizeZ = 0
	Actor_158.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_158:SetPhysicalActorType(1)
	Actor_158:SetPhysicalShape(5)
	Actor_158.ExtraInfo.Name = ""
	Actor_158.ExtraInfo.NameColorR = 1.26117e-044
	Actor_158.ExtraInfo.NameColorG = 0
	Actor_158.ExtraInfo.NameColorB = 0
	Actor_158H = ActorHandler(Actor_158)
	environment:AddActorObject(Actor_158H)

	Actor_159 = ActorObjectInfo(159)
	Actor_159:SetRenderType(1)
	Actor_159.DisplayDesc.ModelId = 440897104
	Actor_159.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_159.DisplayDesc.Outfit = ""
	Actor_159.DisplayDesc.Weapon = ""
	Actor_159.DisplayDesc.Mode = ""
	Actor_159.DisplayDesc.UseLight = false
	Actor_159.DisplayDesc.CastShadow = false
	Actor_159.DisplayDesc.ColorR = 1.240847
	Actor_159.DisplayDesc.ColorG = 1
	Actor_159.DisplayDesc.ColorB = 1
	Actor_159.DisplayDesc.ColorA = 1
	Actor_159:SetModelState(1)
	Actor_159.PhysicDesc.Pos.X = 507.5
	Actor_159.PhysicDesc.Pos.Y = 2.44141
	Actor_159.PhysicDesc.Pos.Z = 583.5
	Actor_159.PhysicDesc.Pos.Rotation = 90
	Actor_159.PhysicDesc.Density = 0
	Actor_159.PhysicDesc.Collidable = true
	Actor_159.PhysicDesc.SizeX = 2.12676e+037
	Actor_159.PhysicDesc.SizeY = 0.240847
	Actor_159.PhysicDesc.SizeZ = 0
	Actor_159.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_159:SetPhysicalActorType(1)
	Actor_159:SetPhysicalShape(5)
	Actor_159.ExtraInfo.Name = ""
	Actor_159.ExtraInfo.NameColorR = 0
	Actor_159.ExtraInfo.NameColorG = 0
	Actor_159.ExtraInfo.NameColorB = 1.875
	Actor_159H = ActorHandler(Actor_159)
	environment:AddActorObject(Actor_159H)

	Actor_160 = ActorObjectInfo(160)
	Actor_160:SetRenderType(1)
	Actor_160.DisplayDesc.ModelId = 750
	Actor_160.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_160.DisplayDesc.Outfit = ""
	Actor_160.DisplayDesc.Weapon = ""
	Actor_160.DisplayDesc.Mode = ""
	Actor_160.DisplayDesc.UseLight = false
	Actor_160.DisplayDesc.CastShadow = true
	Actor_160.DisplayDesc.ColorR = 1
	Actor_160.DisplayDesc.ColorG = 1
	Actor_160.DisplayDesc.ColorB = 1
	Actor_160.DisplayDesc.ColorA = 1
	Actor_160:SetModelState(1)
	Actor_160.PhysicDesc.Pos.X = 508.5
	Actor_160.PhysicDesc.Pos.Y = 2.92969
	Actor_160.PhysicDesc.Pos.Z = 583.5
	Actor_160.PhysicDesc.Pos.Rotation = 90
	Actor_160.PhysicDesc.Density = 0
	Actor_160.PhysicDesc.Collidable = true
	Actor_160.PhysicDesc.SizeX = 0
	Actor_160.PhysicDesc.SizeY = 0
	Actor_160.PhysicDesc.SizeZ = 0
	Actor_160.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_160:SetPhysicalActorType(1)
	Actor_160:SetPhysicalShape(5)
	Actor_160.ExtraInfo.Name = ""
	Actor_160.ExtraInfo.NameColorR = 0
	Actor_160.ExtraInfo.NameColorG = 0
	Actor_160.ExtraInfo.NameColorB = 0
	Actor_160H = ActorHandler(Actor_160)
	environment:AddActorObject(Actor_160H)

	Actor_161 = ActorObjectInfo(161)
	Actor_161:SetRenderType(1)
	Actor_161.DisplayDesc.ModelId = 26685408
	Actor_161.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_161.DisplayDesc.Outfit = ""
	Actor_161.DisplayDesc.Weapon = ""
	Actor_161.DisplayDesc.Mode = ""
	Actor_161.DisplayDesc.UseLight = false
	Actor_161.DisplayDesc.CastShadow = false
	Actor_161.DisplayDesc.ColorR = 1
	Actor_161.DisplayDesc.ColorG = 1
	Actor_161.DisplayDesc.ColorB = 3.69934e-024
	Actor_161.DisplayDesc.ColorA = 1.19311e-008
	Actor_161:SetModelState(1)
	Actor_161.PhysicDesc.Pos.X = 513.5
	Actor_161.PhysicDesc.Pos.Y = 2.44141
	Actor_161.PhysicDesc.Pos.Z = 583.5
	Actor_161.PhysicDesc.Pos.Rotation = 90
	Actor_161.PhysicDesc.Density = 0
	Actor_161.PhysicDesc.Collidable = true
	Actor_161.PhysicDesc.SizeX = 0
	Actor_161.PhysicDesc.SizeY = 0
	Actor_161.PhysicDesc.SizeZ = 0
	Actor_161.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_161:SetPhysicalActorType(1)
	Actor_161:SetPhysicalShape(5)
	Actor_161.ExtraInfo.Name = ""
	Actor_161.ExtraInfo.NameColorR = -6.41908e-019
	Actor_161.ExtraInfo.NameColorG = 0
	Actor_161.ExtraInfo.NameColorB = 3.58732e-043
	Actor_161H = ActorHandler(Actor_161)
	environment:AddActorObject(Actor_161H)

	Actor_162 = ActorObjectInfo(162)
	Actor_162:SetRenderType(1)
	Actor_162.DisplayDesc.ModelId = 0
	Actor_162.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_162.DisplayDesc.Outfit = ""
	Actor_162.DisplayDesc.Weapon = ""
	Actor_162.DisplayDesc.Mode = ""
	Actor_162.DisplayDesc.UseLight = false
	Actor_162.DisplayDesc.CastShadow = true
	Actor_162.DisplayDesc.ColorR = 1
	Actor_162.DisplayDesc.ColorG = 1
	Actor_162.DisplayDesc.ColorB = 1
	Actor_162.DisplayDesc.ColorA = 1
	Actor_162:SetModelState(1)
	Actor_162.PhysicDesc.Pos.X = 512.5
	Actor_162.PhysicDesc.Pos.Y = 2.6875
	Actor_162.PhysicDesc.Pos.Z = 583.5
	Actor_162.PhysicDesc.Pos.Rotation = 90
	Actor_162.PhysicDesc.Density = 0
	Actor_162.PhysicDesc.Collidable = true
	Actor_162.PhysicDesc.SizeX = 0
	Actor_162.PhysicDesc.SizeY = 0
	Actor_162.PhysicDesc.SizeZ = 0
	Actor_162.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_162:SetPhysicalActorType(1)
	Actor_162:SetPhysicalShape(5)
	Actor_162.ExtraInfo.Name = ""
	Actor_162.ExtraInfo.NameColorR = 0
	Actor_162.ExtraInfo.NameColorG = 0
	Actor_162.ExtraInfo.NameColorB = 0
	Actor_162H = ActorHandler(Actor_162)
	environment:AddActorObject(Actor_162H)

	Actor_163 = ActorObjectInfo(163)
	Actor_163:SetRenderType(1)
	Actor_163.DisplayDesc.ModelId = 1044906018
	Actor_163.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_163.DisplayDesc.Outfit = ""
	Actor_163.DisplayDesc.Weapon = ""
	Actor_163.DisplayDesc.Mode = ""
	Actor_163.DisplayDesc.UseLight = false
	Actor_163.DisplayDesc.CastShadow = false
	Actor_163.DisplayDesc.ColorR = 1
	Actor_163.DisplayDesc.ColorG = 1
	Actor_163.DisplayDesc.ColorB = 1
	Actor_163.DisplayDesc.ColorA = 2.63726e-023
	Actor_163:SetModelState(1)
	Actor_163.PhysicDesc.Pos.X = 511.5
	Actor_163.PhysicDesc.Pos.Y = 2.44141
	Actor_163.PhysicDesc.Pos.Z = 583.5
	Actor_163.PhysicDesc.Pos.Rotation = 90
	Actor_163.PhysicDesc.Density = 0
	Actor_163.PhysicDesc.Collidable = true
	Actor_163.PhysicDesc.SizeX = 2.8026e-045
	Actor_163.PhysicDesc.SizeY = 1.8367e-040
	Actor_163.PhysicDesc.SizeZ = 0
	Actor_163.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_163:SetPhysicalActorType(1)
	Actor_163:SetPhysicalShape(5)
	Actor_163.ExtraInfo.Name = ""
	Actor_163.ExtraInfo.NameColorR = 2.8026e-045
	Actor_163.ExtraInfo.NameColorG = 0
	Actor_163.ExtraInfo.NameColorB = 0
	Actor_163H = ActorHandler(Actor_163)
	environment:AddActorObject(Actor_163H)

	Actor_164 = ActorObjectInfo(164)
	Actor_164:SetRenderType(1)
	Actor_164.DisplayDesc.ModelId = 0
	Actor_164.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_164.DisplayDesc.Outfit = ""
	Actor_164.DisplayDesc.Weapon = ""
	Actor_164.DisplayDesc.Mode = ""
	Actor_164.DisplayDesc.UseLight = false
	Actor_164.DisplayDesc.CastShadow = false
	Actor_164.DisplayDesc.ColorR = 1.999985
	Actor_164.DisplayDesc.ColorG = 1
	Actor_164.DisplayDesc.ColorB = 1
	Actor_164.DisplayDesc.ColorA = 1
	Actor_164:SetModelState(1)
	Actor_164.PhysicDesc.Pos.X = 509.5
	Actor_164.PhysicDesc.Pos.Y = 0.976563
	Actor_164.PhysicDesc.Pos.Z = 595.5
	Actor_164.PhysicDesc.Pos.Rotation = 90
	Actor_164.PhysicDesc.Density = 0
	Actor_164.PhysicDesc.Collidable = true
	Actor_164.PhysicDesc.SizeX = 0
	Actor_164.PhysicDesc.SizeY = -1.875
	Actor_164.PhysicDesc.SizeZ = 0
	Actor_164.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_164:SetPhysicalActorType(1)
	Actor_164:SetPhysicalShape(5)
	Actor_164.ExtraInfo.Name = ""
	Actor_164.ExtraInfo.NameColorR = -1.875
	Actor_164.ExtraInfo.NameColorG = 0
	Actor_164.ExtraInfo.NameColorB = 0
	Actor_164H = ActorHandler(Actor_164)
	environment:AddActorObject(Actor_164H)

	Actor_165 = ActorObjectInfo(165)
	Actor_165:SetRenderType(1)
	Actor_165.DisplayDesc.ModelId = 0
	Actor_165.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_165.DisplayDesc.Outfit = ""
	Actor_165.DisplayDesc.Weapon = ""
	Actor_165.DisplayDesc.Mode = ""
	Actor_165.DisplayDesc.UseLight = false
	Actor_165.DisplayDesc.CastShadow = false
	Actor_165.DisplayDesc.ColorR = 1.4013e-045
	Actor_165.DisplayDesc.ColorG = 1
	Actor_165.DisplayDesc.ColorB = 1
	Actor_165.DisplayDesc.ColorA = 1
	Actor_165:SetModelState(1)
	Actor_165.PhysicDesc.Pos.X = 502.375
	Actor_165.PhysicDesc.Pos.Y = 0.976563
	Actor_165.PhysicDesc.Pos.Z = 595.5
	Actor_165.PhysicDesc.Pos.Rotation = 90
	Actor_165.PhysicDesc.Density = 0
	Actor_165.PhysicDesc.Collidable = true
	Actor_165.PhysicDesc.SizeX = 0
	Actor_165.PhysicDesc.SizeY = -1.875
	Actor_165.PhysicDesc.SizeZ = 0
	Actor_165.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_165:SetPhysicalActorType(1)
	Actor_165:SetPhysicalShape(5)
	Actor_165.ExtraInfo.Name = ""
	Actor_165.ExtraInfo.NameColorR = -1.875
	Actor_165.ExtraInfo.NameColorG = 0
	Actor_165.ExtraInfo.NameColorB = 0
	Actor_165H = ActorHandler(Actor_165)
	environment:AddActorObject(Actor_165H)

	Actor_166 = ActorObjectInfo(166)
	Actor_166:SetRenderType(1)
	Actor_166.DisplayDesc.ModelId = 443608456
	Actor_166.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.osgb"
	Actor_166.DisplayDesc.Outfit = ""
	Actor_166.DisplayDesc.Weapon = ""
	Actor_166.DisplayDesc.Mode = ""
	Actor_166.DisplayDesc.UseLight = false
	Actor_166.DisplayDesc.CastShadow = false
	Actor_166.DisplayDesc.ColorR = 4.57352e-038
	Actor_166.DisplayDesc.ColorG = 9.18415e-040
	Actor_166.DisplayDesc.ColorB = 1.11345e-034
	Actor_166.DisplayDesc.ColorA = 4.57361e-038
	Actor_166:SetModelState(1)
	Actor_166.PhysicDesc.Pos.X = 516.625
	Actor_166.PhysicDesc.Pos.Y = 0.976563
	Actor_166.PhysicDesc.Pos.Z = 595.5
	Actor_166.PhysicDesc.Pos.Rotation = 90
	Actor_166.PhysicDesc.Density = 0
	Actor_166.PhysicDesc.Collidable = true
	Actor_166.PhysicDesc.SizeX = 0
	Actor_166.PhysicDesc.SizeY = 0
	Actor_166.PhysicDesc.SizeZ = 4.97944e-023
	Actor_166.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_28.phy"
	Actor_166:SetPhysicalActorType(1)
	Actor_166:SetPhysicalShape(5)
	Actor_166.ExtraInfo.Name = ""
	Actor_166.ExtraInfo.NameColorR = 0
	Actor_166.ExtraInfo.NameColorG = 0
	Actor_166.ExtraInfo.NameColorB = 1.47094e-041
	Actor_166H = ActorHandler(Actor_166)
	environment:AddActorObject(Actor_166H)

	Actor_167 = ActorObjectInfo(167)
	Actor_167:SetRenderType(1)
	Actor_167.DisplayDesc.ModelId = 1376110031
	Actor_167.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_167.DisplayDesc.Outfit = ""
	Actor_167.DisplayDesc.Weapon = ""
	Actor_167.DisplayDesc.Mode = ""
	Actor_167.DisplayDesc.UseLight = false
	Actor_167.DisplayDesc.CastShadow = true
	Actor_167.DisplayDesc.ColorR = 1
	Actor_167.DisplayDesc.ColorG = 1
	Actor_167.DisplayDesc.ColorB = 3.08662e-023
	Actor_167.DisplayDesc.ColorA = 3.08662e-023
	Actor_167:SetModelState(1)
	Actor_167.PhysicDesc.Pos.X = 501.5
	Actor_167.PhysicDesc.Pos.Y = 0.976563
	Actor_167.PhysicDesc.Pos.Z = 598.5
	Actor_167.PhysicDesc.Pos.Rotation = 90
	Actor_167.PhysicDesc.Density = 8.74493e-010
	Actor_167.PhysicDesc.Collidable = true
	Actor_167.PhysicDesc.SizeX = 0
	Actor_167.PhysicDesc.SizeY = 0
	Actor_167.PhysicDesc.SizeZ = 0
	Actor_167.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
	Actor_167:SetPhysicalActorType(1)
	Actor_167:SetPhysicalShape(5)
	Actor_167.ExtraInfo.Name = ""
	Actor_167.ExtraInfo.NameColorR = 1
	Actor_167.ExtraInfo.NameColorG = 1
	Actor_167.ExtraInfo.NameColorB = 1
	Actor_167H = ActorHandler(Actor_167)
	environment:AddActorObject(Actor_167H)

	Actor_168 = ActorObjectInfo(168)
	Actor_168:SetRenderType(1)
	Actor_168.DisplayDesc.ModelId = 0
	Actor_168.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_168.DisplayDesc.Outfit = ""
	Actor_168.DisplayDesc.Weapon = ""
	Actor_168.DisplayDesc.Mode = ""
	Actor_168.DisplayDesc.UseLight = false
	Actor_168.DisplayDesc.CastShadow = true
	Actor_168.DisplayDesc.ColorR = 1
	Actor_168.DisplayDesc.ColorG = 1
	Actor_168.DisplayDesc.ColorB = 1
	Actor_168.DisplayDesc.ColorA = 1
	Actor_168:SetModelState(1)
	Actor_168.PhysicDesc.Pos.X = 506.5
	Actor_168.PhysicDesc.Pos.Y = 2.44141
	Actor_168.PhysicDesc.Pos.Z = 574.625
	Actor_168.PhysicDesc.Pos.Rotation = 90
	Actor_168.PhysicDesc.Density = 0
	Actor_168.PhysicDesc.Collidable = true
	Actor_168.PhysicDesc.SizeX = 0
	Actor_168.PhysicDesc.SizeY = 0
	Actor_168.PhysicDesc.SizeZ = 0
	Actor_168.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_168:SetPhysicalActorType(1)
	Actor_168:SetPhysicalShape(5)
	Actor_168.ExtraInfo.Name = ""
	Actor_168.ExtraInfo.NameColorR = 0
	Actor_168.ExtraInfo.NameColorG = 0
	Actor_168.ExtraInfo.NameColorB = 0
	Actor_168H = ActorHandler(Actor_168)
	environment:AddActorObject(Actor_168H)

	Actor_169 = ActorObjectInfo(169)
	Actor_169:SetRenderType(1)
	Actor_169.DisplayDesc.ModelId = 4
	Actor_169.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_169.DisplayDesc.Outfit = ""
	Actor_169.DisplayDesc.Weapon = ""
	Actor_169.DisplayDesc.Mode = ""
	Actor_169.DisplayDesc.UseLight = false
	Actor_169.DisplayDesc.CastShadow = false
	Actor_169.DisplayDesc.ColorR = 1.16016
	Actor_169.DisplayDesc.ColorG = -1.47656
	Actor_169.DisplayDesc.ColorB = 1.105469
	Actor_169.DisplayDesc.ColorA = 2.2168
	Actor_169:SetModelState(1)
	Actor_169.PhysicDesc.Pos.X = 512.5
	Actor_169.PhysicDesc.Pos.Y = 2.44141
	Actor_169.PhysicDesc.Pos.Z = 574.375
	Actor_169.PhysicDesc.Pos.Rotation = 90
	Actor_169.PhysicDesc.Density = 0
	Actor_169.PhysicDesc.Collidable = true
	Actor_169.PhysicDesc.SizeX = 0
	Actor_169.PhysicDesc.SizeY = 7.42812e-023
	Actor_169.PhysicDesc.SizeZ = 0
	Actor_169.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_169:SetPhysicalActorType(1)
	Actor_169:SetPhysicalShape(5)
	Actor_169.ExtraInfo.Name = ""
	Actor_169.ExtraInfo.NameColorR = 0
	Actor_169.ExtraInfo.NameColorG = 0
	Actor_169.ExtraInfo.NameColorB = 0
	Actor_169H = ActorHandler(Actor_169)
	environment:AddActorObject(Actor_169H)

	Actor_170 = ActorObjectInfo(170)
	Actor_170:SetRenderType(1)
	Actor_170.DisplayDesc.ModelId = 0
	Actor_170.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_170.DisplayDesc.Outfit = ""
	Actor_170.DisplayDesc.Weapon = ""
	Actor_170.DisplayDesc.Mode = ""
	Actor_170.DisplayDesc.UseLight = false
	Actor_170.DisplayDesc.CastShadow = true
	Actor_170.DisplayDesc.ColorR = 1
	Actor_170.DisplayDesc.ColorG = 1
	Actor_170.DisplayDesc.ColorB = 1
	Actor_170.DisplayDesc.ColorA = 1
	Actor_170:SetModelState(1)
	Actor_170.PhysicDesc.Pos.X = 509.5
	Actor_170.PhysicDesc.Pos.Y = 2.44141
	Actor_170.PhysicDesc.Pos.Z = 579.875
	Actor_170.PhysicDesc.Pos.Rotation = 90
	Actor_170.PhysicDesc.Density = 0
	Actor_170.PhysicDesc.Collidable = true
	Actor_170.PhysicDesc.SizeX = 0
	Actor_170.PhysicDesc.SizeY = 0
	Actor_170.PhysicDesc.SizeZ = 0
	Actor_170.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_170:SetPhysicalActorType(1)
	Actor_170:SetPhysicalShape(5)
	Actor_170.ExtraInfo.Name = ""
	Actor_170.ExtraInfo.NameColorR = 0
	Actor_170.ExtraInfo.NameColorG = 0
	Actor_170.ExtraInfo.NameColorB = 0
	Actor_170H = ActorHandler(Actor_170)
	environment:AddActorObject(Actor_170H)

	Actor_171 = ActorObjectInfo(171)
	Actor_171:SetRenderType(1)
	Actor_171.DisplayDesc.ModelId = -1
	Actor_171.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_58.osgb"
	Actor_171.DisplayDesc.Outfit = ""
	Actor_171.DisplayDesc.Weapon = ""
	Actor_171.DisplayDesc.Mode = ""
	Actor_171.DisplayDesc.UseLight = false
	Actor_171.DisplayDesc.CastShadow = false
	Actor_171.DisplayDesc.ColorR = 1
	Actor_171.DisplayDesc.ColorG = 1
	Actor_171.DisplayDesc.ColorB = 1
	Actor_171.DisplayDesc.ColorA = 1
	Actor_171:SetModelState(1)
	Actor_171.PhysicDesc.Pos.X = 512.5
	Actor_171.PhysicDesc.Pos.Y = 0.976563
	Actor_171.PhysicDesc.Pos.Z = 552.5
	Actor_171.PhysicDesc.Pos.Rotation = -90
	Actor_171.PhysicDesc.Density = 1
	Actor_171.PhysicDesc.Collidable = true
	Actor_171.PhysicDesc.SizeX = 1
	Actor_171.PhysicDesc.SizeY = 1
	Actor_171.PhysicDesc.SizeZ = 1
	Actor_171.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_58.phy"
	Actor_171:SetPhysicalActorType(1)
	Actor_171:SetPhysicalShape(5)
	Actor_171.ExtraInfo.Name = ""
	Actor_171.ExtraInfo.NameColorR = 1
	Actor_171.ExtraInfo.NameColorG = 1
	Actor_171.ExtraInfo.NameColorB = 1
	Actor_171H = ActorHandler(Actor_171)
	environment:AddActorObject(Actor_171H)

	Actor_172 = ActorObjectInfo(172)
	Actor_172:SetRenderType(1)
	Actor_172.DisplayDesc.ModelId = 0
	Actor_172.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_59.osgb"
	Actor_172.DisplayDesc.Outfit = ""
	Actor_172.DisplayDesc.Weapon = ""
	Actor_172.DisplayDesc.Mode = ""
	Actor_172.DisplayDesc.UseLight = false
	Actor_172.DisplayDesc.CastShadow = false
	Actor_172.DisplayDesc.ColorR = 1
	Actor_172.DisplayDesc.ColorG = 1.05127e-030
	Actor_172.DisplayDesc.ColorB = 1
	Actor_172.DisplayDesc.ColorA = 1
	Actor_172:SetModelState(1)
	Actor_172.PhysicDesc.Pos.X = 512.5
	Actor_172.PhysicDesc.Pos.Y = 0.976563
	Actor_172.PhysicDesc.Pos.Z = 552.5
	Actor_172.PhysicDesc.Pos.Rotation = -90
	Actor_172.PhysicDesc.Density = 0
	Actor_172.PhysicDesc.Collidable = true
	Actor_172.PhysicDesc.SizeX = 0
	Actor_172.PhysicDesc.SizeY = 0
	Actor_172.PhysicDesc.SizeZ = 0
	Actor_172.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_59.phy"
	Actor_172:SetPhysicalActorType(1)
	Actor_172:SetPhysicalShape(5)
	Actor_172.ExtraInfo.Name = ""
	Actor_172.ExtraInfo.NameColorR = 1.05498e-030
	Actor_172.ExtraInfo.NameColorG = 1.83699e-040
	Actor_172.ExtraInfo.NameColorB = 2.63312e-035
	Actor_172H = ActorHandler(Actor_172)
	environment:AddActorObject(Actor_172H)

	Actor_173 = ActorObjectInfo(173)
	Actor_173:SetRenderType(1)
	Actor_173.DisplayDesc.ModelId = 0
	Actor_173.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_173.DisplayDesc.Outfit = ""
	Actor_173.DisplayDesc.Weapon = ""
	Actor_173.DisplayDesc.Mode = ""
	Actor_173.DisplayDesc.UseLight = false
	Actor_173.DisplayDesc.CastShadow = true
	Actor_173.DisplayDesc.ColorR = 3.58732e-043
	Actor_173.DisplayDesc.ColorG = 9.21956e-041
	Actor_173.DisplayDesc.ColorB = 9.18369e-041
	Actor_173.DisplayDesc.ColorA = 1
	Actor_173:SetModelState(1)
	Actor_173.PhysicDesc.Pos.X = 520.625
	Actor_173.PhysicDesc.Pos.Y = 2.19531
	Actor_173.PhysicDesc.Pos.Z = 550.75
	Actor_173.PhysicDesc.Pos.Rotation = 90
	Actor_173.PhysicDesc.Density = 9.18355e-041
	Actor_173.PhysicDesc.Collidable = true
	Actor_173.PhysicDesc.SizeX = 0
	Actor_173.PhysicDesc.SizeY = 0
	Actor_173.PhysicDesc.SizeZ = 2.57141e-039
	Actor_173.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_173:SetPhysicalActorType(1)
	Actor_173:SetPhysicalShape(5)
	Actor_173.ExtraInfo.Name = ""
	Actor_173.ExtraInfo.NameColorR = 0
	Actor_173.ExtraInfo.NameColorG = 4.99544e-034
	Actor_173.ExtraInfo.NameColorB = 0
	Actor_173H = ActorHandler(Actor_173)
	environment:AddActorObject(Actor_173H)

	Actor_174 = ActorObjectInfo(174)
	Actor_174:SetRenderType(1)
	Actor_174.DisplayDesc.ModelId = 2
	Actor_174.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_174.DisplayDesc.Outfit = ""
	Actor_174.DisplayDesc.Weapon = ""
	Actor_174.DisplayDesc.Mode = ""
	Actor_174.DisplayDesc.UseLight = false
	Actor_174.DisplayDesc.CastShadow = false
	Actor_174.DisplayDesc.ColorR = 1.05325e-034
	Actor_174.DisplayDesc.ColorG = 4.57352e-038
	Actor_174.DisplayDesc.ColorB = 2.94771e-024
	Actor_174.DisplayDesc.ColorA = 1.74488e-039
	Actor_174:SetModelState(1)
	Actor_174.PhysicDesc.Pos.X = 504
	Actor_174.PhysicDesc.Pos.Y = 0.976563
	Actor_174.PhysicDesc.Pos.Z = 549.75
	Actor_174.PhysicDesc.Pos.Rotation = 90
	Actor_174.PhysicDesc.Density = 0
	Actor_174.PhysicDesc.Collidable = true
	Actor_174.PhysicDesc.SizeX = 2.8026e-045
	Actor_174.PhysicDesc.SizeY = 0
	Actor_174.PhysicDesc.SizeZ = 0
	Actor_174.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_174:SetPhysicalActorType(1)
	Actor_174:SetPhysicalShape(5)
	Actor_174.ExtraInfo.Name = ""
	Actor_174.ExtraInfo.NameColorR = 4.57357e-038
	Actor_174.ExtraInfo.NameColorG = 3.48978e-039
	Actor_174.ExtraInfo.NameColorB = 1.05327e-034
	Actor_174H = ActorHandler(Actor_174)
	environment:AddActorObject(Actor_174H)

	Actor_175 = ActorObjectInfo(175)
	Actor_175:SetRenderType(1)
	Actor_175.DisplayDesc.ModelId = 414310112
	Actor_175.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_175.DisplayDesc.Outfit = ""
	Actor_175.DisplayDesc.Weapon = ""
	Actor_175.DisplayDesc.Mode = ""
	Actor_175.DisplayDesc.UseLight = false
	Actor_175.DisplayDesc.CastShadow = false
	Actor_175.DisplayDesc.ColorR = 2.76056e-043
	Actor_175.DisplayDesc.ColorG = 1
	Actor_175.DisplayDesc.ColorB = 1.4013e-045
	Actor_175.DisplayDesc.ColorA = 1
	Actor_175:SetModelState(1)
	Actor_175.PhysicDesc.Pos.X = 526.5
	Actor_175.PhysicDesc.Pos.Y = 1.95313
	Actor_175.PhysicDesc.Pos.Z = 548
	Actor_175.PhysicDesc.Pos.Rotation = 90
	Actor_175.PhysicDesc.Density = 1.30623e-038
	Actor_175.PhysicDesc.Collidable = true
	Actor_175.PhysicDesc.SizeX = 0
	Actor_175.PhysicDesc.SizeY = 0
	Actor_175.PhysicDesc.SizeZ = 0
	Actor_175.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_175:SetPhysicalActorType(1)
	Actor_175:SetPhysicalShape(5)
	Actor_175.ExtraInfo.Name = ""
	Actor_175.ExtraInfo.NameColorR = 1.11344e-034
	Actor_175.ExtraInfo.NameColorG = 4.57353e-038
	Actor_175.ExtraInfo.NameColorB = 4.71148e-024
	Actor_175H = ActorHandler(Actor_175)
	environment:AddActorObject(Actor_175H)

	Actor_176 = ActorObjectInfo(176)
	Actor_176:SetRenderType(1)
	Actor_176.DisplayDesc.ModelId = 440630416
	Actor_176.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_176.DisplayDesc.Outfit = ""
	Actor_176.DisplayDesc.Weapon = ""
	Actor_176.DisplayDesc.Mode = ""
	Actor_176.DisplayDesc.UseLight = false
	Actor_176.DisplayDesc.CastShadow = false
	Actor_176.DisplayDesc.ColorR = 2.558e-035
	Actor_176.DisplayDesc.ColorG = 4.57362e-038
	Actor_176.DisplayDesc.ColorB = 1.03204e-038
	Actor_176.DisplayDesc.ColorA = 1
	Actor_176:SetModelState(1)
	Actor_176.PhysicDesc.Pos.X = 505.5
	Actor_176.PhysicDesc.Pos.Y = 0.976563
	Actor_176.PhysicDesc.Pos.Z = 559.5
	Actor_176.PhysicDesc.Pos.Rotation = 90
	Actor_176.PhysicDesc.Density = 1.78908e-031
	Actor_176.PhysicDesc.Collidable = true
	Actor_176.PhysicDesc.SizeX = 1.78908e-031
	Actor_176.PhysicDesc.SizeY = 5.17717e-031
	Actor_176.PhysicDesc.SizeZ = 2.02043e-039
	Actor_176.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
	Actor_176:SetPhysicalActorType(1)
	Actor_176:SetPhysicalShape(5)
	Actor_176.ExtraInfo.Name = ""
	Actor_176.ExtraInfo.NameColorR = 1.79122e-031
	Actor_176.ExtraInfo.NameColorG = 1.79122e-031
	Actor_176.ExtraInfo.NameColorB = 1.78689e-031
	Actor_176H = ActorHandler(Actor_176)
	environment:AddActorObject(Actor_176H)

	Actor_177 = ActorObjectInfo(177)
	Actor_177:SetRenderType(1)
	Actor_177.DisplayDesc.ModelId = 131074
	Actor_177.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_177.DisplayDesc.Outfit = ""
	Actor_177.DisplayDesc.Weapon = ""
	Actor_177.DisplayDesc.Mode = ""
	Actor_177.DisplayDesc.UseLight = false
	Actor_177.DisplayDesc.CastShadow = false
	Actor_177.DisplayDesc.ColorR = 1
	Actor_177.DisplayDesc.ColorG = 1
	Actor_177.DisplayDesc.ColorB = 1
	Actor_177.DisplayDesc.ColorA = 1
	Actor_177:SetModelState(1)
	Actor_177.PhysicDesc.Pos.X = 517.375
	Actor_177.PhysicDesc.Pos.Y = 0.976563
	Actor_177.PhysicDesc.Pos.Z = 586.25
	Actor_177.PhysicDesc.Pos.Rotation = 90
	Actor_177.PhysicDesc.Density = 0
	Actor_177.PhysicDesc.Collidable = true
	Actor_177.PhysicDesc.SizeX = 564.428
	Actor_177.PhysicDesc.SizeY = 33.2031
	Actor_177.PhysicDesc.SizeZ = 447
	Actor_177.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
	Actor_177:SetPhysicalActorType(1)
	Actor_177:SetPhysicalShape(5)
	Actor_177.ExtraInfo.Name = ""
	Actor_177.ExtraInfo.NameColorR = 1
	Actor_177.ExtraInfo.NameColorG = 9.88336e-031
	Actor_177.ExtraInfo.NameColorB = 1.4013e-045
	Actor_177H = ActorHandler(Actor_177)
	environment:AddActorObject(Actor_177H)

	Actor_178 = ActorObjectInfo(178)
	Actor_178:SetRenderType(1)
	Actor_178.DisplayDesc.ModelId = 131077
	Actor_178.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_178.DisplayDesc.Outfit = ""
	Actor_178.DisplayDesc.Weapon = ""
	Actor_178.DisplayDesc.Mode = ""
	Actor_178.DisplayDesc.UseLight = false
	Actor_178.DisplayDesc.CastShadow = false
	Actor_178.DisplayDesc.ColorR = 2.10195e-044
	Actor_178.DisplayDesc.ColorG = 1.4013e-045
	Actor_178.DisplayDesc.ColorB = 1
	Actor_178.DisplayDesc.ColorA = 4.4746e-024
	Actor_178:SetModelState(1)
	Actor_178.PhysicDesc.Pos.X = 502.625
	Actor_178.PhysicDesc.Pos.Y = 0.976563
	Actor_178.PhysicDesc.Pos.Z = 586.25
	Actor_178.PhysicDesc.Pos.Rotation = 90
	Actor_178.PhysicDesc.Density = -0.105469
	Actor_178.PhysicDesc.Collidable = true
	Actor_178.PhysicDesc.SizeX = -1.47656
	Actor_178.PhysicDesc.SizeY = 0.105469
	Actor_178.PhysicDesc.SizeZ = 2.2168
	Actor_178.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
	Actor_178:SetPhysicalActorType(1)
	Actor_178:SetPhysicalShape(5)
	Actor_178.ExtraInfo.Name = ""
	Actor_178.ExtraInfo.NameColorR = 2.10195e-044
	Actor_178.ExtraInfo.NameColorG = 0
	Actor_178.ExtraInfo.NameColorB = 0
	Actor_178H = ActorHandler(Actor_178)
	environment:AddActorObject(Actor_178H)

	Actor_179 = ActorObjectInfo(179)
	Actor_179:SetRenderType(1)
	Actor_179.DisplayDesc.ModelId = 428754696
	Actor_179.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_179.DisplayDesc.Outfit = ""
	Actor_179.DisplayDesc.Weapon = ""
	Actor_179.DisplayDesc.Mode = ""
	Actor_179.DisplayDesc.UseLight = false
	Actor_179.DisplayDesc.CastShadow = true
	Actor_179.DisplayDesc.ColorR = -0
	Actor_179.DisplayDesc.ColorG = 2.67648e-043
	Actor_179.DisplayDesc.ColorB = 1
	Actor_179.DisplayDesc.ColorA = 1
	Actor_179:SetModelState(1)
	Actor_179.PhysicDesc.Pos.X = 502.625
	Actor_179.PhysicDesc.Pos.Y = 0.976563
	Actor_179.PhysicDesc.Pos.Z = 565.75
	Actor_179.PhysicDesc.Pos.Rotation = 90
	Actor_179.PhysicDesc.Density = 1.26367
	Actor_179.PhysicDesc.Collidable = true
	Actor_179.PhysicDesc.SizeX = 1.4013e-045
	Actor_179.PhysicDesc.SizeY = 0
	Actor_179.PhysicDesc.SizeZ = 9.21956e-041
	Actor_179.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
	Actor_179:SetPhysicalActorType(1)
	Actor_179:SetPhysicalShape(5)
	Actor_179.ExtraInfo.Name = ""
	Actor_179.ExtraInfo.NameColorR = 0
	Actor_179.ExtraInfo.NameColorG = 0
	Actor_179.ExtraInfo.NameColorB = 0
	Actor_179H = ActorHandler(Actor_179)
	environment:AddActorObject(Actor_179H)

	Actor_180 = ActorObjectInfo(180)
	Actor_180:SetRenderType(1)
	Actor_180.DisplayDesc.ModelId = 0
	Actor_180.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_180.DisplayDesc.Outfit = ""
	Actor_180.DisplayDesc.Weapon = ""
	Actor_180.DisplayDesc.Mode = ""
	Actor_180.DisplayDesc.UseLight = false
	Actor_180.DisplayDesc.CastShadow = false
	Actor_180.DisplayDesc.ColorR = 1
	Actor_180.DisplayDesc.ColorG = 1
	Actor_180.DisplayDesc.ColorB = 1
	Actor_180.DisplayDesc.ColorA = 1
	Actor_180:SetModelState(1)
	Actor_180.PhysicDesc.Pos.X = 517.375
	Actor_180.PhysicDesc.Pos.Y = 0.976563
	Actor_180.PhysicDesc.Pos.Z = 565.75
	Actor_180.PhysicDesc.Pos.Rotation = 90
	Actor_180.PhysicDesc.Density = 0
	Actor_180.PhysicDesc.Collidable = true
	Actor_180.PhysicDesc.SizeX = 0
	Actor_180.PhysicDesc.SizeY = 0
	Actor_180.PhysicDesc.SizeZ = 0
	Actor_180.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
	Actor_180:SetPhysicalActorType(1)
	Actor_180:SetPhysicalShape(5)
	Actor_180.ExtraInfo.Name = ""
	Actor_180.ExtraInfo.NameColorR = 0
	Actor_180.ExtraInfo.NameColorG = 0
	Actor_180.ExtraInfo.NameColorB = 0
	Actor_180H = ActorHandler(Actor_180)
	environment:AddActorObject(Actor_180H)

	Actor_181 = ActorObjectInfo(181)
	Actor_181:SetRenderType(1)
	Actor_181.DisplayDesc.ModelId = 750
	Actor_181.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.osgb"
	Actor_181.DisplayDesc.Outfit = ""
	Actor_181.DisplayDesc.Weapon = ""
	Actor_181.DisplayDesc.Mode = ""
	Actor_181.DisplayDesc.UseLight = false
	Actor_181.DisplayDesc.CastShadow = true
	Actor_181.DisplayDesc.ColorR = 1
	Actor_181.DisplayDesc.ColorG = 1
	Actor_181.DisplayDesc.ColorB = 1
	Actor_181.DisplayDesc.ColorA = 1
	Actor_181:SetModelState(1)
	Actor_181.PhysicDesc.Pos.X = 517.5
	Actor_181.PhysicDesc.Pos.Y = 0.976563
	Actor_181.PhysicDesc.Pos.Z = 558.5
	Actor_181.PhysicDesc.Pos.Rotation = 90
	Actor_181.PhysicDesc.Density = 0
	Actor_181.PhysicDesc.Collidable = true
	Actor_181.PhysicDesc.SizeX = 0
	Actor_181.PhysicDesc.SizeY = 0
	Actor_181.PhysicDesc.SizeZ = 0
	Actor_181.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.phy"
	Actor_181:SetPhysicalActorType(1)
	Actor_181:SetPhysicalShape(5)
	Actor_181.ExtraInfo.Name = ""
	Actor_181.ExtraInfo.NameColorR = 0
	Actor_181.ExtraInfo.NameColorG = 0
	Actor_181.ExtraInfo.NameColorB = 0
	Actor_181H = ActorHandler(Actor_181)
	environment:AddActorObject(Actor_181H)

	Actor_182 = ActorObjectInfo(182)
	Actor_182:SetRenderType(1)
	Actor_182.DisplayDesc.ModelId = 750
	Actor_182.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.osgb"
	Actor_182.DisplayDesc.Outfit = ""
	Actor_182.DisplayDesc.Weapon = ""
	Actor_182.DisplayDesc.Mode = ""
	Actor_182.DisplayDesc.UseLight = false
	Actor_182.DisplayDesc.CastShadow = true
	Actor_182.DisplayDesc.ColorR = 1
	Actor_182.DisplayDesc.ColorG = 1
	Actor_182.DisplayDesc.ColorB = 1
	Actor_182.DisplayDesc.ColorA = 1
	Actor_182:SetModelState(1)
	Actor_182.PhysicDesc.Pos.X = 512.5
	Actor_182.PhysicDesc.Pos.Y = 0.976563
	Actor_182.PhysicDesc.Pos.Z = 558.5
	Actor_182.PhysicDesc.Pos.Rotation = 90
	Actor_182.PhysicDesc.Density = 0
	Actor_182.PhysicDesc.Collidable = true
	Actor_182.PhysicDesc.SizeX = 0
	Actor_182.PhysicDesc.SizeY = 0
	Actor_182.PhysicDesc.SizeZ = 0
	Actor_182.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.phy"
	Actor_182:SetPhysicalActorType(1)
	Actor_182:SetPhysicalShape(5)
	Actor_182.ExtraInfo.Name = ""
	Actor_182.ExtraInfo.NameColorR = 0
	Actor_182.ExtraInfo.NameColorG = 0
	Actor_182.ExtraInfo.NameColorB = 0
	Actor_182H = ActorHandler(Actor_182)
	environment:AddActorObject(Actor_182H)

	Actor_183 = ActorObjectInfo(183)
	Actor_183:SetRenderType(1)
	Actor_183.DisplayDesc.ModelId = 0
	Actor_183.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_60.osgb"
	Actor_183.DisplayDesc.Outfit = ""
	Actor_183.DisplayDesc.Weapon = ""
	Actor_183.DisplayDesc.Mode = ""
	Actor_183.DisplayDesc.UseLight = false
	Actor_183.DisplayDesc.CastShadow = false
	Actor_183.DisplayDesc.ColorR = 1
	Actor_183.DisplayDesc.ColorG = 1
	Actor_183.DisplayDesc.ColorB = 1
	Actor_183.DisplayDesc.ColorA = 1
	Actor_183:SetModelState(1)
	Actor_183.PhysicDesc.Pos.X = 484.5
	Actor_183.PhysicDesc.Pos.Y = 0.976563
	Actor_183.PhysicDesc.Pos.Z = 575.25
	Actor_183.PhysicDesc.Pos.Rotation = 180
	Actor_183.PhysicDesc.Density = 7.13744e-031
	Actor_183.PhysicDesc.Collidable = true
	Actor_183.PhysicDesc.SizeX = 7.15509e-031
	Actor_183.PhysicDesc.SizeY = 0
	Actor_183.PhysicDesc.SizeZ = 0
	Actor_183.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_60.phy"
	Actor_183:SetPhysicalActorType(1)
	Actor_183:SetPhysicalShape(5)
	Actor_183.ExtraInfo.Name = ""
	Actor_183.ExtraInfo.NameColorR = 1.875
	Actor_183.ExtraInfo.NameColorG = 0
	Actor_183.ExtraInfo.NameColorB = 2
	Actor_183H = ActorHandler(Actor_183)
	environment:AddActorObject(Actor_183H)

	Actor_184 = ActorObjectInfo(184)
	Actor_184:SetRenderType(1)
	Actor_184.DisplayDesc.ModelId = 227830528
	Actor_184.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_61.osgb"
	Actor_184.DisplayDesc.Outfit = ""
	Actor_184.DisplayDesc.Weapon = ""
	Actor_184.DisplayDesc.Mode = ""
	Actor_184.DisplayDesc.UseLight = false
	Actor_184.DisplayDesc.CastShadow = true
	Actor_184.DisplayDesc.ColorR = 8.67404e-043
	Actor_184.DisplayDesc.ColorG = 1
	Actor_184.DisplayDesc.ColorB = 1
	Actor_184.DisplayDesc.ColorA = 1
	Actor_184:SetModelState(1)
	Actor_184.PhysicDesc.Pos.X = 484.5
	Actor_184.PhysicDesc.Pos.Y = 0.976563
	Actor_184.PhysicDesc.Pos.Z = 575.25
	Actor_184.PhysicDesc.Pos.Rotation = 180
	Actor_184.PhysicDesc.Density = 0
	Actor_184.PhysicDesc.Collidable = true
	Actor_184.PhysicDesc.SizeX = 0
	Actor_184.PhysicDesc.SizeY = 0
	Actor_184.PhysicDesc.SizeZ = 0
	Actor_184.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_61.phy"
	Actor_184:SetPhysicalActorType(1)
	Actor_184:SetPhysicalShape(5)
	Actor_184.ExtraInfo.Name = ""
	Actor_184.ExtraInfo.NameColorR = 0
	Actor_184.ExtraInfo.NameColorG = 0
	Actor_184.ExtraInfo.NameColorB = 9.0664e-043
	Actor_184H = ActorHandler(Actor_184)
	environment:AddActorObject(Actor_184H)

	Actor_185 = ActorObjectInfo(185)
	Actor_185:SetRenderType(1)
	Actor_185.DisplayDesc.ModelId = 1042062493
	Actor_185.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_62.osgb"
	Actor_185.DisplayDesc.Outfit = ""
	Actor_185.DisplayDesc.Weapon = ""
	Actor_185.DisplayDesc.Mode = ""
	Actor_185.DisplayDesc.UseLight = false
	Actor_185.DisplayDesc.CastShadow = true
	Actor_185.DisplayDesc.ColorR = 1.513726
	Actor_185.DisplayDesc.ColorG = 1.498039
	Actor_185.DisplayDesc.ColorB = 1
	Actor_185.DisplayDesc.ColorA = 1.027451
	Actor_185:SetModelState(1)
	Actor_185.PhysicDesc.Pos.X = 484.5
	Actor_185.PhysicDesc.Pos.Y = 0.976563
	Actor_185.PhysicDesc.Pos.Z = 575.25
	Actor_185.PhysicDesc.Pos.Rotation = 180
	Actor_185.PhysicDesc.Density = 0.152941
	Actor_185.PhysicDesc.Collidable = true
	Actor_185.PhysicDesc.SizeX = 0.027451
	Actor_185.PhysicDesc.SizeY = 0.121569
	Actor_185.PhysicDesc.SizeZ = 0.152941
	Actor_185.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_62.phy"
	Actor_185:SetPhysicalActorType(1)
	Actor_185:SetPhysicalShape(5)
	Actor_185.ExtraInfo.Name = ""
	Actor_185.ExtraInfo.NameColorR = 0.121569
	Actor_185.ExtraInfo.NameColorG = 0.152941
	Actor_185.ExtraInfo.NameColorB = 1
	Actor_185H = ActorHandler(Actor_185)
	environment:AddActorObject(Actor_185H)

	Actor_186 = ActorObjectInfo(186)
	Actor_186:SetRenderType(1)
	Actor_186.DisplayDesc.ModelId = 131076
	Actor_186.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_35.osgb"
	Actor_186.DisplayDesc.Outfit = ""
	Actor_186.DisplayDesc.Weapon = ""
	Actor_186.DisplayDesc.Mode = ""
	Actor_186.DisplayDesc.UseLight = false
	Actor_186.DisplayDesc.CastShadow = false
	Actor_186.DisplayDesc.ColorR = -0.128906
	Actor_186.DisplayDesc.ColorG = 1.95313
	Actor_186.DisplayDesc.ColorB = -0
	Actor_186.DisplayDesc.ColorA = 1
	Actor_186:SetModelState(1)
	Actor_186.PhysicDesc.Pos.X = 489.125
	Actor_186.PhysicDesc.Pos.Y = 1.16016
	Actor_186.PhysicDesc.Pos.Z = 562.625
	Actor_186.PhysicDesc.Pos.Rotation = 90
	Actor_186.PhysicDesc.Density = 2.99951e-023
	Actor_186.PhysicDesc.Collidable = true
	Actor_186.PhysicDesc.SizeX = 1.95313
	Actor_186.PhysicDesc.SizeY = 0
	Actor_186.PhysicDesc.SizeZ = 0
	Actor_186.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_35.phy"
	Actor_186:SetPhysicalActorType(1)
	Actor_186:SetPhysicalShape(5)
	Actor_186.ExtraInfo.Name = ""
	Actor_186.ExtraInfo.NameColorR = 3.25391
	Actor_186.ExtraInfo.NameColorG = -0.650391
	Actor_186.ExtraInfo.NameColorB = 0
	Actor_186H = ActorHandler(Actor_186)
	environment:AddActorObject(Actor_186H)

	Actor_187 = ActorObjectInfo(187)
	Actor_187:SetRenderType(1)
	Actor_187.DisplayDesc.ModelId = -45424530
	Actor_187.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.osgb"
	Actor_187.DisplayDesc.Outfit = ""
	Actor_187.DisplayDesc.Weapon = ""
	Actor_187.DisplayDesc.Mode = ""
	Actor_187.DisplayDesc.UseLight = false
	Actor_187.DisplayDesc.CastShadow = false
	Actor_187.DisplayDesc.ColorR = 1
	Actor_187.DisplayDesc.ColorG = 3.13953e-024
	Actor_187.DisplayDesc.ColorB = 3.13953e-024
	Actor_187.DisplayDesc.ColorA = 3.13953e-024
	Actor_187:SetModelState(1)
	Actor_187.PhysicDesc.Pos.X = 494.75
	Actor_187.PhysicDesc.Pos.Y = 0.976563
	Actor_187.PhysicDesc.Pos.Z = 564.625
	Actor_187.PhysicDesc.Pos.Rotation = 90
	Actor_187.PhysicDesc.Density = 0
	Actor_187.PhysicDesc.Collidable = true
	Actor_187.PhysicDesc.SizeX = 0
	Actor_187.PhysicDesc.SizeY = 2.10195e-044
	Actor_187.PhysicDesc.SizeZ = 1.83543e-031
	Actor_187.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.phy"
	Actor_187:SetPhysicalActorType(1)
	Actor_187:SetPhysicalShape(5)
	Actor_187.ExtraInfo.Name = ""
	Actor_187.ExtraInfo.NameColorR = 1.02316e-034
	Actor_187.ExtraInfo.NameColorG = 4.57358e-038
	Actor_187.ExtraInfo.NameColorB = 9.24293e-031
	Actor_187H = ActorHandler(Actor_187)
	environment:AddActorObject(Actor_187H)

	Actor_188 = ActorObjectInfo(188)
	Actor_188:SetRenderType(1)
	Actor_188.DisplayDesc.ModelId = 109838442
	Actor_188.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.osgb"
	Actor_188.DisplayDesc.Outfit = ""
	Actor_188.DisplayDesc.Weapon = ""
	Actor_188.DisplayDesc.Mode = ""
	Actor_188.DisplayDesc.UseLight = false
	Actor_188.DisplayDesc.CastShadow = false
	Actor_188.DisplayDesc.ColorR = 1
	Actor_188.DisplayDesc.ColorG = 1
	Actor_188.DisplayDesc.ColorB = 1
	Actor_188.DisplayDesc.ColorA = 1
	Actor_188:SetModelState(1)
	Actor_188.PhysicDesc.Pos.X = 492
	Actor_188.PhysicDesc.Pos.Y = 0.976563
	Actor_188.PhysicDesc.Pos.Z = 575.875
	Actor_188.PhysicDesc.Pos.Rotation = 90
	Actor_188.PhysicDesc.Density = 0
	Actor_188.PhysicDesc.Collidable = true
	Actor_188.PhysicDesc.SizeX = 0
	Actor_188.PhysicDesc.SizeY = 0
	Actor_188.PhysicDesc.SizeZ = 0
	Actor_188.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.phy"
	Actor_188:SetPhysicalActorType(1)
	Actor_188:SetPhysicalShape(5)
	Actor_188.ExtraInfo.Name = ""
	Actor_188.ExtraInfo.NameColorR = 0
	Actor_188.ExtraInfo.NameColorG = 0
	Actor_188.ExtraInfo.NameColorB = 0
	Actor_188H = ActorHandler(Actor_188)
	environment:AddActorObject(Actor_188H)

	Actor_189 = ActorObjectInfo(189)
	Actor_189:SetRenderType(1)
	Actor_189.DisplayDesc.ModelId = 1328701794
	Actor_189.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_63.osgb"
	Actor_189.DisplayDesc.Outfit = ""
	Actor_189.DisplayDesc.Weapon = ""
	Actor_189.DisplayDesc.Mode = ""
	Actor_189.DisplayDesc.UseLight = false
	Actor_189.DisplayDesc.CastShadow = false
	Actor_189.DisplayDesc.ColorR = 1
	Actor_189.DisplayDesc.ColorG = 1
	Actor_189.DisplayDesc.ColorB = 1
	Actor_189.DisplayDesc.ColorA = 1
	Actor_189:SetModelState(1)
	Actor_189.PhysicDesc.Pos.X = 484.5
	Actor_189.PhysicDesc.Pos.Y = 0.976563
	Actor_189.PhysicDesc.Pos.Z = 575.25
	Actor_189.PhysicDesc.Pos.Rotation = 180
	Actor_189.PhysicDesc.Density = 0
	Actor_189.PhysicDesc.Collidable = true
	Actor_189.PhysicDesc.SizeX = 0
	Actor_189.PhysicDesc.SizeY = 0
	Actor_189.PhysicDesc.SizeZ = 0
	Actor_189.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_63.phy"
	Actor_189:SetPhysicalActorType(1)
	Actor_189:SetPhysicalShape(5)
	Actor_189.ExtraInfo.Name = ""
	Actor_189.ExtraInfo.NameColorR = 0
	Actor_189.ExtraInfo.NameColorG = 0
	Actor_189.ExtraInfo.NameColorB = 0
	Actor_189H = ActorHandler(Actor_189)
	environment:AddActorObject(Actor_189H)

	Actor_190 = ActorObjectInfo(190)
	Actor_190:SetRenderType(1)
	Actor_190.DisplayDesc.ModelId = 226299370
	Actor_190.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.osgb"
	Actor_190.DisplayDesc.Outfit = ""
	Actor_190.DisplayDesc.Weapon = ""
	Actor_190.DisplayDesc.Mode = ""
	Actor_190.DisplayDesc.UseLight = false
	Actor_190.DisplayDesc.CastShadow = false
	Actor_190.DisplayDesc.ColorR = 1
	Actor_190.DisplayDesc.ColorG = 1
	Actor_190.DisplayDesc.ColorB = 1
	Actor_190.DisplayDesc.ColorA = 1
	Actor_190:SetModelState(1)
	Actor_190.PhysicDesc.Pos.X = 494.5
	Actor_190.PhysicDesc.Pos.Y = 0.976563
	Actor_190.PhysicDesc.Pos.Z = 555.875
	Actor_190.PhysicDesc.Pos.Rotation = 90
	Actor_190.PhysicDesc.Density = 0
	Actor_190.PhysicDesc.Collidable = true
	Actor_190.PhysicDesc.SizeX = 0
	Actor_190.PhysicDesc.SizeY = 0
	Actor_190.PhysicDesc.SizeZ = 0
	Actor_190.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_27.phy"
	Actor_190:SetPhysicalActorType(1)
	Actor_190:SetPhysicalShape(5)
	Actor_190.ExtraInfo.Name = ""
	Actor_190.ExtraInfo.NameColorR = 0
	Actor_190.ExtraInfo.NameColorG = 0
	Actor_190.ExtraInfo.NameColorB = 0
	Actor_190H = ActorHandler(Actor_190)
	environment:AddActorObject(Actor_190H)

	Actor_191 = ActorObjectInfo(191)
	Actor_191:SetRenderType(1)
	Actor_191.DisplayDesc.ModelId = 826
	Actor_191.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.osgb"
	Actor_191.DisplayDesc.Outfit = ""
	Actor_191.DisplayDesc.Weapon = ""
	Actor_191.DisplayDesc.Mode = ""
	Actor_191.DisplayDesc.UseLight = false
	Actor_191.DisplayDesc.CastShadow = false
	Actor_191.DisplayDesc.ColorR = 1
	Actor_191.DisplayDesc.ColorG = 1
	Actor_191.DisplayDesc.ColorB = 1
	Actor_191.DisplayDesc.ColorA = 1
	Actor_191:SetModelState(1)
	Actor_191.PhysicDesc.Pos.X = 489.508
	Actor_191.PhysicDesc.Pos.Y = 1.22656
	Actor_191.PhysicDesc.Pos.Z = 558.5
	Actor_191.PhysicDesc.Pos.Rotation = 0
	Actor_191.PhysicDesc.Density = 0
	Actor_191.PhysicDesc.Collidable = true
	Actor_191.PhysicDesc.SizeX = 0
	Actor_191.PhysicDesc.SizeY = 0
	Actor_191.PhysicDesc.SizeZ = 0
	Actor_191.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.phy"
	Actor_191:SetPhysicalActorType(1)
	Actor_191:SetPhysicalShape(5)
	Actor_191.ExtraInfo.Name = ""
	Actor_191.ExtraInfo.NameColorR = 0
	Actor_191.ExtraInfo.NameColorG = 0
	Actor_191.ExtraInfo.NameColorB = 0
	Actor_191H = ActorHandler(Actor_191)
	environment:AddActorObject(Actor_191H)

	Actor_192 = ActorObjectInfo(192)
	Actor_192:SetRenderType(1)
	Actor_192.DisplayDesc.ModelId = 431224608
	Actor_192.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_192.DisplayDesc.Outfit = ""
	Actor_192.DisplayDesc.Weapon = ""
	Actor_192.DisplayDesc.Mode = ""
	Actor_192.DisplayDesc.UseLight = false
	Actor_192.DisplayDesc.CastShadow = true
	Actor_192.DisplayDesc.ColorR = 1.7485e+025
	Actor_192.DisplayDesc.ColorG = 2.14987e-010
	Actor_192.DisplayDesc.ColorB = 2.72609e+020
	Actor_192.DisplayDesc.ColorA = 2.21364e-010
	Actor_192:SetModelState(1)
	Actor_192.PhysicDesc.Pos.X = 489.125
	Actor_192.PhysicDesc.Pos.Y = 9.94531
	Actor_192.PhysicDesc.Pos.Z = 547.125
	Actor_192.PhysicDesc.Pos.Rotation = 90
	Actor_192.PhysicDesc.Density = 2.9927e+009
	Actor_192.PhysicDesc.Collidable = true
	Actor_192.PhysicDesc.SizeX = 2.14987e-010
	Actor_192.PhysicDesc.SizeY = 0
	Actor_192.PhysicDesc.SizeZ = 2.10195e-044
	Actor_192.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_192:SetPhysicalActorType(1)
	Actor_192:SetPhysicalShape(5)
	Actor_192.ExtraInfo.Name = ""
	Actor_192.ExtraInfo.NameColorR = 0
	Actor_192.ExtraInfo.NameColorG = 4.88095e-034
	Actor_192.ExtraInfo.NameColorB = 2.0459e-043
	Actor_192H = ActorHandler(Actor_192)
	environment:AddActorObject(Actor_192H)

	Actor_193 = ActorObjectInfo(193)
	Actor_193:SetRenderType(1)
	Actor_193.DisplayDesc.ModelId = 1801009580
	Actor_193.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.osgb"
	Actor_193.DisplayDesc.Outfit = ""
	Actor_193.DisplayDesc.Weapon = ""
	Actor_193.DisplayDesc.Mode = ""
	Actor_193.DisplayDesc.UseLight = false
	Actor_193.DisplayDesc.CastShadow = false
	Actor_193.DisplayDesc.ColorR = 1
	Actor_193.DisplayDesc.ColorG = 1
	Actor_193.DisplayDesc.ColorB = 1
	Actor_193.DisplayDesc.ColorA = 1
	Actor_193:SetModelState(1)
	Actor_193.PhysicDesc.Pos.X = 483.75
	Actor_193.PhysicDesc.Pos.Y = 9.94531
	Actor_193.PhysicDesc.Pos.Z = 547.125
	Actor_193.PhysicDesc.Pos.Rotation = 90
	Actor_193.PhysicDesc.Density = 0
	Actor_193.PhysicDesc.Collidable = true
	Actor_193.PhysicDesc.SizeX = 0
	Actor_193.PhysicDesc.SizeY = 0
	Actor_193.PhysicDesc.SizeZ = 0
	Actor_193.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_51.phy"
	Actor_193:SetPhysicalActorType(1)
	Actor_193:SetPhysicalShape(5)
	Actor_193.ExtraInfo.Name = ""
	Actor_193.ExtraInfo.NameColorR = 0
	Actor_193.ExtraInfo.NameColorG = 0
	Actor_193.ExtraInfo.NameColorB = 0
	Actor_193H = ActorHandler(Actor_193)
	environment:AddActorObject(Actor_193H)

	Actor_194 = ActorObjectInfo(194)
	Actor_194:SetRenderType(1)
	Actor_194.DisplayDesc.ModelId = 3
	Actor_194.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_64.osgb"
	Actor_194.DisplayDesc.Outfit = ""
	Actor_194.DisplayDesc.Weapon = ""
	Actor_194.DisplayDesc.Mode = ""
	Actor_194.DisplayDesc.UseLight = false
	Actor_194.DisplayDesc.CastShadow = false
	Actor_194.DisplayDesc.ColorR = 1
	Actor_194.DisplayDesc.ColorG = 1
	Actor_194.DisplayDesc.ColorB = 1
	Actor_194.DisplayDesc.ColorA = 1
	Actor_194:SetModelState(1)
	Actor_194.PhysicDesc.Pos.X = 484.5
	Actor_194.PhysicDesc.Pos.Y = 0.976563
	Actor_194.PhysicDesc.Pos.Z = 575.25
	Actor_194.PhysicDesc.Pos.Rotation = 180
	Actor_194.PhysicDesc.Density = 0
	Actor_194.PhysicDesc.Collidable = true
	Actor_194.PhysicDesc.SizeX = 0
	Actor_194.PhysicDesc.SizeY = 0
	Actor_194.PhysicDesc.SizeZ = 0
	Actor_194.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_64.phy"
	Actor_194:SetPhysicalActorType(1)
	Actor_194:SetPhysicalShape(5)
	Actor_194.ExtraInfo.Name = ""
	Actor_194.ExtraInfo.NameColorR = 0
	Actor_194.ExtraInfo.NameColorG = 0
	Actor_194.ExtraInfo.NameColorB = 0
	Actor_194H = ActorHandler(Actor_194)
	environment:AddActorObject(Actor_194H)

	Actor_195 = ActorObjectInfo(195)
	Actor_195:SetRenderType(1)
	Actor_195.DisplayDesc.ModelId = 131077
	Actor_195.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_66.osgb"
	Actor_195.DisplayDesc.Outfit = ""
	Actor_195.DisplayDesc.Weapon = ""
	Actor_195.DisplayDesc.Mode = ""
	Actor_195.DisplayDesc.UseLight = false
	Actor_195.DisplayDesc.CastShadow = false
	Actor_195.DisplayDesc.ColorR = 2.10195e-044
	Actor_195.DisplayDesc.ColorG = 1.4013e-045
	Actor_195.DisplayDesc.ColorB = 1
	Actor_195.DisplayDesc.ColorA = 2.35688e-023
	Actor_195:SetModelState(1)
	Actor_195.PhysicDesc.Pos.X = 484.5
	Actor_195.PhysicDesc.Pos.Y = 0.976563
	Actor_195.PhysicDesc.Pos.Z = 575.25
	Actor_195.PhysicDesc.Pos.Rotation = 180
	Actor_195.PhysicDesc.Density = -8.30078
	Actor_195.PhysicDesc.Collidable = true
	Actor_195.PhysicDesc.SizeX = 4.78516
	Actor_195.PhysicDesc.SizeY = -6.83594
	Actor_195.PhysicDesc.SizeZ = 3.90625
	Actor_195.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_66.phy"
	Actor_195:SetPhysicalActorType(1)
	Actor_195:SetPhysicalShape(5)
	Actor_195.ExtraInfo.Name = ""
	Actor_195.ExtraInfo.NameColorR = 0
	Actor_195.ExtraInfo.NameColorG = 0
	Actor_195.ExtraInfo.NameColorB = 0
	Actor_195H = ActorHandler(Actor_195)
	environment:AddActorObject(Actor_195H)

	Actor_196 = ActorObjectInfo(196)
	Actor_196:SetRenderType(1)
	Actor_196.DisplayDesc.ModelId = 430928264
	Actor_196.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_65.osgb"
	Actor_196.DisplayDesc.Outfit = ""
	Actor_196.DisplayDesc.Weapon = ""
	Actor_196.DisplayDesc.Mode = ""
	Actor_196.DisplayDesc.UseLight = false
	Actor_196.DisplayDesc.CastShadow = false
	Actor_196.DisplayDesc.ColorR = 5.60519e-045
	Actor_196.DisplayDesc.ColorG = 1.07648e+021
	Actor_196.DisplayDesc.ColorB = 7.84591e-040
	Actor_196.DisplayDesc.ColorA = 1
	Actor_196:SetModelState(1)
	Actor_196.PhysicDesc.Pos.X = 484.5
	Actor_196.PhysicDesc.Pos.Y = 0.976563
	Actor_196.PhysicDesc.Pos.Z = 575.25
	Actor_196.PhysicDesc.Pos.Rotation = 180
	Actor_196.PhysicDesc.Density = 1.71677e-023
	Actor_196.PhysicDesc.Collidable = true
	Actor_196.PhysicDesc.SizeX = 151523
	Actor_196.PhysicDesc.SizeY = 0
	Actor_196.PhysicDesc.SizeZ = 0
	Actor_196.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_65.phy"
	Actor_196:SetPhysicalActorType(1)
	Actor_196:SetPhysicalShape(5)
	Actor_196.ExtraInfo.Name = ""
	Actor_196.ExtraInfo.NameColorR = -2.81444e+035
	Actor_196.ExtraInfo.NameColorG = -3.2533e+010
	Actor_196.ExtraInfo.NameColorB = 0
	Actor_196H = ActorHandler(Actor_196)
	environment:AddActorObject(Actor_196H)

	Actor_197 = ActorObjectInfo(197)
	Actor_197:SetRenderType(1)
	Actor_197.DisplayDesc.ModelId = 131087
	Actor_197.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.osgb"
	Actor_197.DisplayDesc.Outfit = ""
	Actor_197.DisplayDesc.Weapon = ""
	Actor_197.DisplayDesc.Mode = ""
	Actor_197.DisplayDesc.UseLight = false
	Actor_197.DisplayDesc.CastShadow = false
	Actor_197.DisplayDesc.ColorR = 1.0232e-034
	Actor_197.DisplayDesc.ColorG = 1.890196
	Actor_197.DisplayDesc.ColorB = 1.796078
	Actor_197.DisplayDesc.ColorA = 1.623529
	Actor_197:SetModelState(1)
	Actor_197.PhysicDesc.Pos.X = 506.5
	Actor_197.PhysicDesc.Pos.Y = 0.976563
	Actor_197.PhysicDesc.Pos.Z = 565.5
	Actor_197.PhysicDesc.Pos.Rotation = 90
	Actor_197.PhysicDesc.Density = 0.890196
	Actor_197.PhysicDesc.Collidable = true
	Actor_197.PhysicDesc.SizeX = 0.623529
	Actor_197.PhysicDesc.SizeY = 1
	Actor_197.PhysicDesc.SizeZ = 0.890196
	Actor_197.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.phy"
	Actor_197:SetPhysicalActorType(1)
	Actor_197:SetPhysicalShape(5)
	Actor_197.ExtraInfo.Name = ""
	Actor_197.ExtraInfo.NameColorR = 1
	Actor_197.ExtraInfo.NameColorG = 0.890196
	Actor_197.ExtraInfo.NameColorB = 0.796078
	Actor_197H = ActorHandler(Actor_197)
	environment:AddActorObject(Actor_197H)

	Actor_198 = ActorObjectInfo(198)
	Actor_198:SetRenderType(1)
	Actor_198.DisplayDesc.ModelId = 436470048
	Actor_198.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.osgb"
	Actor_198.DisplayDesc.Outfit = ""
	Actor_198.DisplayDesc.Weapon = ""
	Actor_198.DisplayDesc.Mode = ""
	Actor_198.DisplayDesc.UseLight = false
	Actor_198.DisplayDesc.CastShadow = true
	Actor_198.DisplayDesc.ColorR = 1.81114e+022
	Actor_198.DisplayDesc.ColorG = 2.79387e+020
	Actor_198.DisplayDesc.ColorB = 7.13211e+028
	Actor_198.DisplayDesc.ColorA = 1
	Actor_198:SetModelState(1)
	Actor_198.PhysicDesc.Pos.X = 513.5
	Actor_198.PhysicDesc.Pos.Y = 0.976563
	Actor_198.PhysicDesc.Pos.Z = 565.5
	Actor_198.PhysicDesc.Pos.Rotation = 90
	Actor_198.PhysicDesc.Density = 2.5818e-023
	Actor_198.PhysicDesc.Collidable = true
	Actor_198.PhysicDesc.SizeX = 0
	Actor_198.PhysicDesc.SizeY = 0
	Actor_198.PhysicDesc.SizeZ = 0
	Actor_198.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.phy"
	Actor_198:SetPhysicalActorType(1)
	Actor_198:SetPhysicalShape(5)
	Actor_198.ExtraInfo.Name = ""
	Actor_198.ExtraInfo.NameColorR = 9.855e+011
	Actor_198.ExtraInfo.NameColorG = 4.09096e-040
	Actor_198.ExtraInfo.NameColorB = 0
	Actor_198H = ActorHandler(Actor_198)
	environment:AddActorObject(Actor_198H)

	Actor_199 = ActorObjectInfo(199)
	Actor_199:SetRenderType(1)
	Actor_199.DisplayDesc.ModelId = 9364492
	Actor_199.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_199.DisplayDesc.Outfit = ""
	Actor_199.DisplayDesc.Weapon = ""
	Actor_199.DisplayDesc.Mode = ""
	Actor_199.DisplayDesc.UseLight = false
	Actor_199.DisplayDesc.CastShadow = false
	Actor_199.DisplayDesc.ColorR = 1
	Actor_199.DisplayDesc.ColorG = 1
	Actor_199.DisplayDesc.ColorB = 1.4013e-045
	Actor_199.DisplayDesc.ColorA = 1
	Actor_199:SetModelState(1)
	Actor_199.PhysicDesc.Pos.X = 539.25
	Actor_199.PhysicDesc.Pos.Y = 1.46484
	Actor_199.PhysicDesc.Pos.Z = 601.5
	Actor_199.PhysicDesc.Pos.Rotation = 90
	Actor_199.PhysicDesc.Density = 0
	Actor_199.PhysicDesc.Collidable = true
	Actor_199.PhysicDesc.SizeX = 0
	Actor_199.PhysicDesc.SizeY = 0
	Actor_199.PhysicDesc.SizeZ = 0
	Actor_199.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_199:SetPhysicalActorType(1)
	Actor_199:SetPhysicalShape(5)
	Actor_199.ExtraInfo.Name = ""
	Actor_199.ExtraInfo.NameColorR = 0
	Actor_199.ExtraInfo.NameColorG = 0
	Actor_199.ExtraInfo.NameColorB = -1.875
	Actor_199H = ActorHandler(Actor_199)
	environment:AddActorObject(Actor_199H)

	Actor_200 = ActorObjectInfo(200)
	Actor_200:SetRenderType(1)
	Actor_200.DisplayDesc.ModelId = 9364492
	Actor_200.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_200.DisplayDesc.Outfit = ""
	Actor_200.DisplayDesc.Weapon = ""
	Actor_200.DisplayDesc.Mode = ""
	Actor_200.DisplayDesc.UseLight = false
	Actor_200.DisplayDesc.CastShadow = false
	Actor_200.DisplayDesc.ColorR = 2.16016
	Actor_200.DisplayDesc.ColorG = 2.88653e+018
	Actor_200.DisplayDesc.ColorB = 1
	Actor_200.DisplayDesc.ColorA = 9.21956e-041
	Actor_200:SetModelState(1)
	Actor_200.PhysicDesc.Pos.X = 481.625
	Actor_200.PhysicDesc.Pos.Y = 9.76563
	Actor_200.PhysicDesc.Pos.Z = 544.75
	Actor_200.PhysicDesc.Pos.Rotation = 90
	Actor_200.PhysicDesc.Density = -1.73327e-038
	Actor_200.PhysicDesc.Collidable = true
	Actor_200.PhysicDesc.SizeX = 0
	Actor_200.PhysicDesc.SizeY = 0
	Actor_200.PhysicDesc.SizeZ = 0
	Actor_200.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_200:SetPhysicalActorType(1)
	Actor_200:SetPhysicalShape(5)
	Actor_200.ExtraInfo.Name = ""
	Actor_200.ExtraInfo.NameColorR = 0
	Actor_200.ExtraInfo.NameColorG = 0.519531
	Actor_200.ExtraInfo.NameColorB = 6.3585e-024
	Actor_200H = ActorHandler(Actor_200)
	environment:AddActorObject(Actor_200H)

	Actor_201 = ActorObjectInfo(201)
	Actor_201:SetRenderType(1)
	Actor_201.DisplayDesc.ModelId = 7197960
	Actor_201.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.osgb"
	Actor_201.DisplayDesc.Outfit = ""
	Actor_201.DisplayDesc.Weapon = ""
	Actor_201.DisplayDesc.Mode = ""
	Actor_201.DisplayDesc.UseLight = false
	Actor_201.DisplayDesc.CastShadow = false
	Actor_201.DisplayDesc.ColorR = 1
	Actor_201.DisplayDesc.ColorG = 1
	Actor_201.DisplayDesc.ColorB = 1
	Actor_201.DisplayDesc.ColorA = 9.14734e-024
	Actor_201:SetModelState(1)
	Actor_201.PhysicDesc.Pos.X = 481.625
	Actor_201.PhysicDesc.Pos.Y = 9.76563
	Actor_201.PhysicDesc.Pos.Z = 546.25
	Actor_201.PhysicDesc.Pos.Rotation = 90
	Actor_201.PhysicDesc.Density = 0
	Actor_201.PhysicDesc.Collidable = true
	Actor_201.PhysicDesc.SizeX = 9.14737e-024
	Actor_201.PhysicDesc.SizeY = 0
	Actor_201.PhysicDesc.SizeZ = 0
	Actor_201.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_29.phy"
	Actor_201:SetPhysicalActorType(1)
	Actor_201:SetPhysicalShape(5)
	Actor_201.ExtraInfo.Name = ""
	Actor_201.ExtraInfo.NameColorR = 0
	Actor_201.ExtraInfo.NameColorG = 0
	Actor_201.ExtraInfo.NameColorB = 0
	Actor_201H = ActorHandler(Actor_201)
	environment:AddActorObject(Actor_201H)

	Actor_202 = ActorObjectInfo(202)
	Actor_202:SetRenderType(1)
	Actor_202.DisplayDesc.ModelId = 1048968704
	Actor_202.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.osgb"
	Actor_202.DisplayDesc.Outfit = ""
	Actor_202.DisplayDesc.Weapon = ""
	Actor_202.DisplayDesc.Mode = ""
	Actor_202.DisplayDesc.UseLight = false
	Actor_202.DisplayDesc.CastShadow = false
	Actor_202.DisplayDesc.ColorR = 1
	Actor_202.DisplayDesc.ColorG = 5.87173e-039
	Actor_202.DisplayDesc.ColorB = 1
	Actor_202.DisplayDesc.ColorA = 1
	Actor_202:SetModelState(1)
	Actor_202.PhysicDesc.Pos.X = 513.5
	Actor_202.PhysicDesc.Pos.Y = 0.976563
	Actor_202.PhysicDesc.Pos.Z = 565.5
	Actor_202.PhysicDesc.Pos.Rotation = 90
	Actor_202.PhysicDesc.Density = 0.589393
	Actor_202.PhysicDesc.Collidable = true
	Actor_202.PhysicDesc.SizeX = -0.590746
	Actor_202.PhysicDesc.SizeY = 0.644608
	Actor_202.PhysicDesc.SizeZ = -0.154244
	Actor_202.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.phy"
	Actor_202:SetPhysicalActorType(1)
	Actor_202:SetPhysicalShape(5)
	Actor_202.ExtraInfo.Name = ""
	Actor_202.ExtraInfo.NameColorR = -0.748792
	Actor_202.ExtraInfo.NameColorG = -0.132817
	Actor_202.ExtraInfo.NameColorB = -0.55035
	Actor_202H = ActorHandler(Actor_202)
	environment:AddActorObject(Actor_202H)

	Actor_203 = ActorObjectInfo(203)
	Actor_203:SetRenderType(1)
	Actor_203.DisplayDesc.ModelId = 26685408
	Actor_203.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.osgb"
	Actor_203.DisplayDesc.Outfit = ""
	Actor_203.DisplayDesc.Weapon = ""
	Actor_203.DisplayDesc.Mode = ""
	Actor_203.DisplayDesc.UseLight = false
	Actor_203.DisplayDesc.CastShadow = true
	Actor_203.DisplayDesc.ColorR = 9.46509e-034
	Actor_203.DisplayDesc.ColorG = 1
	Actor_203.DisplayDesc.ColorB = 1
	Actor_203.DisplayDesc.ColorA = 1
	Actor_203:SetModelState(1)
	Actor_203.PhysicDesc.Pos.X = 506.5
	Actor_203.PhysicDesc.Pos.Y = 0.976563
	Actor_203.PhysicDesc.Pos.Z = 565.5
	Actor_203.PhysicDesc.Pos.Rotation = 90
	Actor_203.PhysicDesc.Density = 1
	Actor_203.PhysicDesc.Collidable = true
	Actor_203.PhysicDesc.SizeX = 1
	Actor_203.PhysicDesc.SizeY = 0
	Actor_203.PhysicDesc.SizeZ = -1
	Actor_203.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.phy"
	Actor_203:SetPhysicalActorType(1)
	Actor_203:SetPhysicalShape(5)
	Actor_203.ExtraInfo.Name = ""
	Actor_203.ExtraInfo.NameColorR = 518.5
	Actor_203.ExtraInfo.NameColorG = 33.2031
	Actor_203.ExtraInfo.NameColorB = 463.5
	Actor_203H = ActorHandler(Actor_203)
	environment:AddActorObject(Actor_203H)

	Actor_204 = ActorObjectInfo(204)
	Actor_204:SetRenderType(1)
	Actor_204.DisplayDesc.ModelId = 0
	Actor_204.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.osgb"
	Actor_204.DisplayDesc.Outfit = ""
	Actor_204.DisplayDesc.Weapon = ""
	Actor_204.DisplayDesc.Mode = ""
	Actor_204.DisplayDesc.UseLight = false
	Actor_204.DisplayDesc.CastShadow = false
	Actor_204.DisplayDesc.ColorR = 1
	Actor_204.DisplayDesc.ColorG = 1
	Actor_204.DisplayDesc.ColorB = 1
	Actor_204.DisplayDesc.ColorA = 1
	Actor_204:SetModelState(1)
	Actor_204.PhysicDesc.Pos.X = 489.508
	Actor_204.PhysicDesc.Pos.Y = 1.22656
	Actor_204.PhysicDesc.Pos.Z = 558.5
	Actor_204.PhysicDesc.Pos.Rotation = 0
	Actor_204.PhysicDesc.Density = 5.03867e-024
	Actor_204.PhysicDesc.Collidable = true
	Actor_204.PhysicDesc.SizeX = 0
	Actor_204.PhysicDesc.SizeY = 0
	Actor_204.PhysicDesc.SizeZ = 0
	Actor_204.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.phy"
	Actor_204:SetPhysicalActorType(1)
	Actor_204:SetPhysicalShape(5)
	Actor_204.ExtraInfo.Name = ""
	Actor_204.ExtraInfo.NameColorR = 1.05326e-034
	Actor_204.ExtraInfo.NameColorG = 4.5736e-038
	Actor_204.ExtraInfo.NameColorB = 5.83106e-024
	Actor_204H = ActorHandler(Actor_204)
	environment:AddActorObject(Actor_204H)

	Actor_205 = ActorObjectInfo(205)
	Actor_205:SetRenderType(1)
	Actor_205.DisplayDesc.ModelId = -1
	Actor_205.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_205.DisplayDesc.Outfit = ""
	Actor_205.DisplayDesc.Weapon = ""
	Actor_205.DisplayDesc.Mode = ""
	Actor_205.DisplayDesc.UseLight = false
	Actor_205.DisplayDesc.CastShadow = true
	Actor_205.DisplayDesc.ColorR = 1
	Actor_205.DisplayDesc.ColorG = 1
	Actor_205.DisplayDesc.ColorB = -1.7064e+038
	Actor_205.DisplayDesc.ColorA = -1.7064e+038
	Actor_205:SetModelState(1)
	Actor_205.PhysicDesc.Pos.X = 487.5
	Actor_205.PhysicDesc.Pos.Y = 0.976563
	Actor_205.PhysicDesc.Pos.Z = 591.5
	Actor_205.PhysicDesc.Pos.Rotation = -90
	Actor_205.PhysicDesc.Density = 0
	Actor_205.PhysicDesc.Collidable = true
	Actor_205.PhysicDesc.SizeX = 0
	Actor_205.PhysicDesc.SizeY = 0
	Actor_205.PhysicDesc.SizeZ = 0
	Actor_205.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_205:SetPhysicalActorType(1)
	Actor_205:SetPhysicalShape(5)
	Actor_205.ExtraInfo.Name = ""
	Actor_205.ExtraInfo.NameColorR = 0
	Actor_205.ExtraInfo.NameColorG = -1.70141e+038
	Actor_205.ExtraInfo.NameColorB = 0
	Actor_205H = ActorHandler(Actor_205)
	environment:AddActorObject(Actor_205H)

	Actor_206 = ActorObjectInfo(206)
	Actor_206:SetRenderType(1)
	Actor_206.DisplayDesc.ModelId = 0
	Actor_206.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_206.DisplayDesc.Outfit = ""
	Actor_206.DisplayDesc.Weapon = ""
	Actor_206.DisplayDesc.Mode = ""
	Actor_206.DisplayDesc.UseLight = false
	Actor_206.DisplayDesc.CastShadow = false
	Actor_206.DisplayDesc.ColorR = 3.96059
	Actor_206.DisplayDesc.ColorG = 1
	Actor_206.DisplayDesc.ColorB = 2.5
	Actor_206.DisplayDesc.ColorA = 1
	Actor_206:SetModelState(1)
	Actor_206.PhysicDesc.Pos.X = 502.5
	Actor_206.PhysicDesc.Pos.Y = 0.976563
	Actor_206.PhysicDesc.Pos.Z = 554.5
	Actor_206.PhysicDesc.Pos.Rotation = 0
	Actor_206.PhysicDesc.Density = 0
	Actor_206.PhysicDesc.Collidable = true
	Actor_206.PhysicDesc.SizeX = 0
	Actor_206.PhysicDesc.SizeY = 0
	Actor_206.PhysicDesc.SizeZ = 0
	Actor_206.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_206:SetPhysicalActorType(1)
	Actor_206:SetPhysicalShape(5)
	Actor_206.ExtraInfo.Name = ""
	Actor_206.ExtraInfo.NameColorR = 1.02148e-023
	Actor_206.ExtraInfo.NameColorG = 1
	Actor_206.ExtraInfo.NameColorB = -1
	Actor_206H = ActorHandler(Actor_206)
	environment:AddActorObject(Actor_206H)

	Actor_207 = ActorObjectInfo(207)
	Actor_207:SetRenderType(1)
	Actor_207.DisplayDesc.ModelId = 418764772
	Actor_207.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_207.DisplayDesc.Outfit = ""
	Actor_207.DisplayDesc.Weapon = ""
	Actor_207.DisplayDesc.Mode = ""
	Actor_207.DisplayDesc.UseLight = false
	Actor_207.DisplayDesc.CastShadow = true
	Actor_207.DisplayDesc.ColorR = 1
	Actor_207.DisplayDesc.ColorG = 1
	Actor_207.DisplayDesc.ColorB = 8.07688e-012
	Actor_207.DisplayDesc.ColorA = 2.2095e-027
	Actor_207:SetModelState(1)
	Actor_207.PhysicDesc.Pos.X = 502.5
	Actor_207.PhysicDesc.Pos.Y = 0.976563
	Actor_207.PhysicDesc.Pos.Z = 556.5
	Actor_207.PhysicDesc.Pos.Rotation = 180
	Actor_207.PhysicDesc.Density = 0
	Actor_207.PhysicDesc.Collidable = true
	Actor_207.PhysicDesc.SizeX = 3.40282e+038
	Actor_207.PhysicDesc.SizeY = 3.40282e+038
	Actor_207.PhysicDesc.SizeZ = -3.40282e+038
	Actor_207.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_207:SetPhysicalActorType(1)
	Actor_207:SetPhysicalShape(5)
	Actor_207.ExtraInfo.Name = ""
	Actor_207.ExtraInfo.NameColorR = 0
	Actor_207.ExtraInfo.NameColorG = 0
	Actor_207.ExtraInfo.NameColorB = 0
	Actor_207H = ActorHandler(Actor_207)
	environment:AddActorObject(Actor_207H)

	Actor_208 = ActorObjectInfo(208)
	Actor_208:SetRenderType(1)
	Actor_208.DisplayDesc.ModelId = 2
	Actor_208.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_208.DisplayDesc.Outfit = ""
	Actor_208.DisplayDesc.Weapon = ""
	Actor_208.DisplayDesc.Mode = ""
	Actor_208.DisplayDesc.UseLight = false
	Actor_208.DisplayDesc.CastShadow = false
	Actor_208.DisplayDesc.ColorR = 1.05326e-034
	Actor_208.DisplayDesc.ColorG = 1.70657e-023
	Actor_208.DisplayDesc.ColorB = 1.81414e-023
	Actor_208.DisplayDesc.ColorA = 1.83674e-040
	Actor_208:SetModelState(1)
	Actor_208.PhysicDesc.Pos.X = 525.5
	Actor_208.PhysicDesc.Pos.Y = 0.976563
	Actor_208.PhysicDesc.Pos.Z = 607.25
	Actor_208.PhysicDesc.Pos.Rotation = -90
	Actor_208.PhysicDesc.Density = 0
	Actor_208.PhysicDesc.Collidable = true
	Actor_208.PhysicDesc.SizeX = 1.4013e-045
	Actor_208.PhysicDesc.SizeY = 0
	Actor_208.PhysicDesc.SizeZ = 1.72407e-023
	Actor_208.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_208:SetPhysicalActorType(1)
	Actor_208:SetPhysicalShape(5)
	Actor_208.ExtraInfo.Name = ""
	Actor_208.ExtraInfo.NameColorR = 3.71094
	Actor_208.ExtraInfo.NameColorG = 1.4013e-045
	Actor_208.ExtraInfo.NameColorB = 0
	Actor_208H = ActorHandler(Actor_208)
	environment:AddActorObject(Actor_208H)

	Actor_209 = ActorObjectInfo(209)
	Actor_209:SetRenderType(1)
	Actor_209.DisplayDesc.ModelId = 144585652
	Actor_209.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_209.DisplayDesc.Outfit = ""
	Actor_209.DisplayDesc.Weapon = ""
	Actor_209.DisplayDesc.Mode = ""
	Actor_209.DisplayDesc.UseLight = false
	Actor_209.DisplayDesc.CastShadow = false
	Actor_209.DisplayDesc.ColorR = 1.05328e-034
	Actor_209.DisplayDesc.ColorG = 1
	Actor_209.DisplayDesc.ColorB = 1
	Actor_209.DisplayDesc.ColorA = 1
	Actor_209:SetModelState(1)
	Actor_209.PhysicDesc.Pos.X = 523.75
	Actor_209.PhysicDesc.Pos.Y = 0.976563
	Actor_209.PhysicDesc.Pos.Z = 607.25
	Actor_209.PhysicDesc.Pos.Rotation = -90
	Actor_209.PhysicDesc.Density = -0.234375
	Actor_209.PhysicDesc.Collidable = true
	Actor_209.PhysicDesc.SizeX = 0
	Actor_209.PhysicDesc.SizeY = 2.10195e-044
	Actor_209.PhysicDesc.SizeZ = 2.8026e-045
	Actor_209.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_209:SetPhysicalActorType(1)
	Actor_209:SetPhysicalShape(5)
	Actor_209.ExtraInfo.Name = ""
	Actor_209.ExtraInfo.NameColorR = 0
	Actor_209.ExtraInfo.NameColorG = 0
	Actor_209.ExtraInfo.NameColorB = 0
	Actor_209H = ActorHandler(Actor_209)
	environment:AddActorObject(Actor_209H)

	Actor_210 = ActorObjectInfo(210)
	Actor_210:SetRenderType(1)
	Actor_210.DisplayDesc.ModelId = 27508352
	Actor_210.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_210.DisplayDesc.Outfit = ""
	Actor_210.DisplayDesc.Weapon = ""
	Actor_210.DisplayDesc.Mode = ""
	Actor_210.DisplayDesc.UseLight = false
	Actor_210.DisplayDesc.CastShadow = false
	Actor_210.DisplayDesc.ColorR = 1
	Actor_210.DisplayDesc.ColorG = 1
	Actor_210.DisplayDesc.ColorB = -1
	Actor_210.DisplayDesc.ColorA = 1
	Actor_210:SetModelState(1)
	Actor_210.PhysicDesc.Pos.X = 527.25
	Actor_210.PhysicDesc.Pos.Y = 0.976563
	Actor_210.PhysicDesc.Pos.Z = 607.25
	Actor_210.PhysicDesc.Pos.Rotation = -90
	Actor_210.PhysicDesc.Density = 0
	Actor_210.PhysicDesc.Collidable = true
	Actor_210.PhysicDesc.SizeX = 0
	Actor_210.PhysicDesc.SizeY = 0
	Actor_210.PhysicDesc.SizeZ = 0
	Actor_210.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_210:SetPhysicalActorType(1)
	Actor_210:SetPhysicalShape(5)
	Actor_210.ExtraInfo.Name = ""
	Actor_210.ExtraInfo.NameColorR = 0
	Actor_210.ExtraInfo.NameColorG = 0
	Actor_210.ExtraInfo.NameColorB = 0
	Actor_210H = ActorHandler(Actor_210)
	environment:AddActorObject(Actor_210H)

	Actor_211 = ActorObjectInfo(211)
	Actor_211:SetRenderType(1)
	Actor_211.DisplayDesc.ModelId = 0
	Actor_211.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_211.DisplayDesc.Outfit = ""
	Actor_211.DisplayDesc.Weapon = ""
	Actor_211.DisplayDesc.Mode = ""
	Actor_211.DisplayDesc.UseLight = false
	Actor_211.DisplayDesc.CastShadow = true
	Actor_211.DisplayDesc.ColorR = 1.72663e-031
	Actor_211.DisplayDesc.ColorG = 1.8374e-040
	Actor_211.DisplayDesc.ColorB = 1.02317e-034
	Actor_211.DisplayDesc.ColorA = 4.57362e-038
	Actor_211:SetModelState(1)
	Actor_211.PhysicDesc.Pos.X = 529
	Actor_211.PhysicDesc.Pos.Y = 0.976563
	Actor_211.PhysicDesc.Pos.Z = 607.25
	Actor_211.PhysicDesc.Pos.Rotation = -90
	Actor_211.PhysicDesc.Density = 1.4013e-045
	Actor_211.PhysicDesc.Collidable = true
	Actor_211.PhysicDesc.SizeX = 0
	Actor_211.PhysicDesc.SizeY = 0
	Actor_211.PhysicDesc.SizeZ = 0
	Actor_211.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_211:SetPhysicalActorType(1)
	Actor_211:SetPhysicalShape(5)
	Actor_211.ExtraInfo.Name = ""
	Actor_211.ExtraInfo.NameColorR = 0
	Actor_211.ExtraInfo.NameColorG = 2.10195e-044
	Actor_211.ExtraInfo.NameColorB = 2.60903e+020
	Actor_211H = ActorHandler(Actor_211)
	environment:AddActorObject(Actor_211H)

	Actor_212 = ActorObjectInfo(212)
	Actor_212:SetRenderType(1)
	Actor_212.DisplayDesc.ModelId = 131147
	Actor_212.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_212.DisplayDesc.Outfit = ""
	Actor_212.DisplayDesc.Weapon = ""
	Actor_212.DisplayDesc.Mode = ""
	Actor_212.DisplayDesc.UseLight = false
	Actor_212.DisplayDesc.CastShadow = false
	Actor_212.DisplayDesc.ColorR = 3.60134e-043
	Actor_212.DisplayDesc.ColorG = 1.10208e-039
	Actor_212.DisplayDesc.ColorB = 2.55798e-035
	Actor_212.DisplayDesc.ColorA = 1.31224e-038
	Actor_212:SetModelState(1)
	Actor_212.PhysicDesc.Pos.X = 530.75
	Actor_212.PhysicDesc.Pos.Y = 0.976563
	Actor_212.PhysicDesc.Pos.Z = 607.25
	Actor_212.PhysicDesc.Pos.Rotation = -90
	Actor_212.PhysicDesc.Density = -0
	Actor_212.PhysicDesc.Collidable = true
	Actor_212.PhysicDesc.SizeX = 0
	Actor_212.PhysicDesc.SizeY = 0
	Actor_212.PhysicDesc.SizeZ = 0
	Actor_212.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_212:SetPhysicalActorType(1)
	Actor_212:SetPhysicalShape(5)
	Actor_212.ExtraInfo.Name = ""
	Actor_212.ExtraInfo.NameColorR = 1.36332e-041
	Actor_212.ExtraInfo.NameColorG = 1
	Actor_212.ExtraInfo.NameColorB = 2.35106e-038
	Actor_212H = ActorHandler(Actor_212)
	environment:AddActorObject(Actor_212H)

	Actor_213 = ActorObjectInfo(213)
	Actor_213:SetRenderType(1)
	Actor_213.DisplayDesc.ModelId = 0
	Actor_213.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_213.DisplayDesc.Outfit = ""
	Actor_213.DisplayDesc.Weapon = ""
	Actor_213.DisplayDesc.Mode = ""
	Actor_213.DisplayDesc.UseLight = false
	Actor_213.DisplayDesc.CastShadow = false
	Actor_213.DisplayDesc.ColorR = 1.47094e-041
	Actor_213.DisplayDesc.ColorG = 1.47094e-041
	Actor_213.DisplayDesc.ColorB = 1.4708e-041
	Actor_213.DisplayDesc.ColorA = 1.36332e-041
	Actor_213:SetModelState(1)
	Actor_213.PhysicDesc.Pos.X = 522
	Actor_213.PhysicDesc.Pos.Y = 0.976563
	Actor_213.PhysicDesc.Pos.Z = 607.25
	Actor_213.PhysicDesc.Pos.Rotation = -90
	Actor_213.PhysicDesc.Density = 0
	Actor_213.PhysicDesc.Collidable = true
	Actor_213.PhysicDesc.SizeX = 0
	Actor_213.PhysicDesc.SizeY = 0
	Actor_213.PhysicDesc.SizeZ = 3.58732e-043
	Actor_213.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_213:SetPhysicalActorType(1)
	Actor_213:SetPhysicalShape(5)
	Actor_213.ExtraInfo.Name = ""
	Actor_213.ExtraInfo.NameColorR = 4.09179e-043
	Actor_213.ExtraInfo.NameColorG = 0
	Actor_213.ExtraInfo.NameColorB = 0
	Actor_213H = ActorHandler(Actor_213)
	environment:AddActorObject(Actor_213H)

	Actor_214 = ActorObjectInfo(214)
	Actor_214:SetRenderType(1)
	Actor_214.DisplayDesc.ModelId = 144577628
	Actor_214.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_214.DisplayDesc.Outfit = ""
	Actor_214.DisplayDesc.Weapon = ""
	Actor_214.DisplayDesc.Mode = ""
	Actor_214.DisplayDesc.UseLight = false
	Actor_214.DisplayDesc.CastShadow = false
	Actor_214.DisplayDesc.ColorR = 5.04467e-044
	Actor_214.DisplayDesc.ColorG = 1.65304e-039
	Actor_214.DisplayDesc.ColorB = 1.0533e-034
	Actor_214.DisplayDesc.ColorA = 4.14789e-024
	Actor_214:SetModelState(1)
	Actor_214.PhysicDesc.Pos.X = 520.25
	Actor_214.PhysicDesc.Pos.Y = 0.976563
	Actor_214.PhysicDesc.Pos.Z = 607.25
	Actor_214.PhysicDesc.Pos.Rotation = -90
	Actor_214.PhysicDesc.Density = 0
	Actor_214.PhysicDesc.Collidable = true
	Actor_214.PhysicDesc.SizeX = 0
	Actor_214.PhysicDesc.SizeY = 0
	Actor_214.PhysicDesc.SizeZ = 0
	Actor_214.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_214:SetPhysicalActorType(1)
	Actor_214:SetPhysicalShape(5)
	Actor_214.ExtraInfo.Name = ""
	Actor_214.ExtraInfo.NameColorR = 482
	Actor_214.ExtraInfo.NameColorG = 9.76563
	Actor_214.ExtraInfo.NameColorB = 522.5
	Actor_214H = ActorHandler(Actor_214)
	environment:AddActorObject(Actor_214H)

	Actor_215 = ActorObjectInfo(215)
	Actor_215:SetRenderType(1)
	Actor_215.DisplayDesc.ModelId = 144629820
	Actor_215.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.osgb"
	Actor_215.DisplayDesc.Outfit = ""
	Actor_215.DisplayDesc.Weapon = ""
	Actor_215.DisplayDesc.Mode = ""
	Actor_215.DisplayDesc.UseLight = false
	Actor_215.DisplayDesc.CastShadow = false
	Actor_215.DisplayDesc.ColorR = 2.8026e-044
	Actor_215.DisplayDesc.ColorG = 2.24208e-044
	Actor_215.DisplayDesc.ColorB = 1
	Actor_215.DisplayDesc.ColorA = 1
	Actor_215:SetModelState(1)
	Actor_215.PhysicDesc.Pos.X = 532.5
	Actor_215.PhysicDesc.Pos.Y = 0.976563
	Actor_215.PhysicDesc.Pos.Z = 607.258
	Actor_215.PhysicDesc.Pos.Rotation = -90
	Actor_215.PhysicDesc.Density = 5.26888e-043
	Actor_215.PhysicDesc.Collidable = true
	Actor_215.PhysicDesc.SizeX = 5.26888e-043
	Actor_215.PhysicDesc.SizeY = 5.2829e-043
	Actor_215.PhysicDesc.SizeZ = 2.57146e-039
	Actor_215.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_26.phy"
	Actor_215:SetPhysicalActorType(1)
	Actor_215:SetPhysicalShape(5)
	Actor_215.ExtraInfo.Name = ""
	Actor_215.ExtraInfo.NameColorR = 2.55788e-035
	Actor_215.ExtraInfo.NameColorG = 7.0313e-031
	Actor_215.ExtraInfo.NameColorB = 7.94852e-031
	Actor_215H = ActorHandler(Actor_215)
	environment:AddActorObject(Actor_215H)

	Actor_216 = ActorObjectInfo(216)
	Actor_216:SetRenderType(1)
	Actor_216.DisplayDesc.ModelId = 0
	Actor_216.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_67.osgb"
	Actor_216.DisplayDesc.Outfit = ""
	Actor_216.DisplayDesc.Weapon = ""
	Actor_216.DisplayDesc.Mode = ""
	Actor_216.DisplayDesc.UseLight = false
	Actor_216.DisplayDesc.CastShadow = false
	Actor_216.DisplayDesc.ColorR = -1
	Actor_216.DisplayDesc.ColorG = 1
	Actor_216.DisplayDesc.ColorB = -0.259766
	Actor_216.DisplayDesc.ColorA = 1.650391
	Actor_216:SetModelState(1)
	Actor_216.PhysicDesc.Pos.X = 537
	Actor_216.PhysicDesc.Pos.Y = 0.976563
	Actor_216.PhysicDesc.Pos.Z = 556
	Actor_216.PhysicDesc.Pos.Rotation = 90
	Actor_216.PhysicDesc.Density = 0
	Actor_216.PhysicDesc.Collidable = true
	Actor_216.PhysicDesc.SizeX = 0
	Actor_216.PhysicDesc.SizeY = 0
	Actor_216.PhysicDesc.SizeZ = 0
	Actor_216.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_67.phy"
	Actor_216:SetPhysicalActorType(1)
	Actor_216:SetPhysicalShape(5)
	Actor_216.ExtraInfo.Name = ""
	Actor_216.ExtraInfo.NameColorR = 0
	Actor_216.ExtraInfo.NameColorG = 2.84691e-039
	Actor_216.ExtraInfo.NameColorB = 1.05325e-034
	Actor_216H = ActorHandler(Actor_216)
	environment:AddActorObject(Actor_216H)

	Actor_217 = ActorObjectInfo(217)
	Actor_217:SetRenderType(1)
	Actor_217.DisplayDesc.ModelId = 0
	Actor_217.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_68.osgb"
	Actor_217.DisplayDesc.Outfit = ""
	Actor_217.DisplayDesc.Weapon = ""
	Actor_217.DisplayDesc.Mode = ""
	Actor_217.DisplayDesc.UseLight = false
	Actor_217.DisplayDesc.CastShadow = false
	Actor_217.DisplayDesc.ColorR = 1
	Actor_217.DisplayDesc.ColorG = 1
	Actor_217.DisplayDesc.ColorB = 1
	Actor_217.DisplayDesc.ColorA = 1
	Actor_217:SetModelState(1)
	Actor_217.PhysicDesc.Pos.X = 537
	Actor_217.PhysicDesc.Pos.Y = 0.976563
	Actor_217.PhysicDesc.Pos.Z = 556
	Actor_217.PhysicDesc.Pos.Rotation = 90
	Actor_217.PhysicDesc.Density = 0
	Actor_217.PhysicDesc.Collidable = true
	Actor_217.PhysicDesc.SizeX = 0
	Actor_217.PhysicDesc.SizeY = 0
	Actor_217.PhysicDesc.SizeZ = 1.28577e-039
	Actor_217.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_68.phy"
	Actor_217:SetPhysicalActorType(1)
	Actor_217:SetPhysicalShape(5)
	Actor_217.ExtraInfo.Name = ""
	Actor_217.ExtraInfo.NameColorR = -0.819232
	Actor_217.ExtraInfo.NameColorG = 0
	Actor_217.ExtraInfo.NameColorB = 0.573462
	Actor_217H = ActorHandler(Actor_217)
	environment:AddActorObject(Actor_217H)

	Actor_218 = ActorObjectInfo(218)
	Actor_218:SetRenderType(1)
	Actor_218.DisplayDesc.ModelId = 0
	Actor_218.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_69.osgb"
	Actor_218.DisplayDesc.Outfit = ""
	Actor_218.DisplayDesc.Weapon = ""
	Actor_218.DisplayDesc.Mode = ""
	Actor_218.DisplayDesc.UseLight = false
	Actor_218.DisplayDesc.CastShadow = false
	Actor_218.DisplayDesc.ColorR = 2.10195e-044
	Actor_218.DisplayDesc.ColorG = 1.4013e-045
	Actor_218.DisplayDesc.ColorB = 1
	Actor_218.DisplayDesc.ColorA = 3.67061e-037
	Actor_218:SetModelState(1)
	Actor_218.PhysicDesc.Pos.X = 537
	Actor_218.PhysicDesc.Pos.Y = 0.976563
	Actor_218.PhysicDesc.Pos.Z = 556
	Actor_218.PhysicDesc.Pos.Rotation = 90
	Actor_218.PhysicDesc.Density = 3.67061e-037
	Actor_218.PhysicDesc.Collidable = true
	Actor_218.PhysicDesc.SizeX = 12.7461
	Actor_218.PhysicDesc.SizeY = -2.05469
	Actor_218.PhysicDesc.SizeZ = -0.513672
	Actor_218.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_69.phy"
	Actor_218:SetPhysicalActorType(1)
	Actor_218:SetPhysicalShape(5)
	Actor_218.ExtraInfo.Name = ""
	Actor_218.ExtraInfo.NameColorR = 14.9023
	Actor_218.ExtraInfo.NameColorG = -2.05469
	Actor_218.ExtraInfo.NameColorB = -0.513672
	Actor_218H = ActorHandler(Actor_218)
	environment:AddActorObject(Actor_218H)

	Actor_219 = ActorObjectInfo(219)
	Actor_219:SetRenderType(1)
	Actor_219.DisplayDesc.ModelId = 0
	Actor_219.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_70.osgb"
	Actor_219.DisplayDesc.Outfit = ""
	Actor_219.DisplayDesc.Weapon = ""
	Actor_219.DisplayDesc.Mode = ""
	Actor_219.DisplayDesc.UseLight = false
	Actor_219.DisplayDesc.CastShadow = false
	Actor_219.DisplayDesc.ColorR = 1.4013e-045
	Actor_219.DisplayDesc.ColorG = 1
	Actor_219.DisplayDesc.ColorB = 1
	Actor_219.DisplayDesc.ColorA = 1
	Actor_219:SetModelState(1)
	Actor_219.PhysicDesc.Pos.X = 537
	Actor_219.PhysicDesc.Pos.Y = 0.976563
	Actor_219.PhysicDesc.Pos.Z = 556
	Actor_219.PhysicDesc.Pos.Rotation = 90
	Actor_219.PhysicDesc.Density = 8.25763e-024
	Actor_219.PhysicDesc.Collidable = true
	Actor_219.PhysicDesc.SizeX = 2.38221e-044
	Actor_219.PhysicDesc.SizeY = 0
	Actor_219.PhysicDesc.SizeZ = 0
	Actor_219.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_70.phy"
	Actor_219:SetPhysicalActorType(1)
	Actor_219:SetPhysicalShape(5)
	Actor_219.ExtraInfo.Name = ""
	Actor_219.ExtraInfo.NameColorR = 3.08286e-044
	Actor_219.ExtraInfo.NameColorG = 0
	Actor_219.ExtraInfo.NameColorB = 4.06377e-044
	Actor_219H = ActorHandler(Actor_219)
	environment:AddActorObject(Actor_219H)

	Actor_220 = ActorObjectInfo(220)
	Actor_220:SetRenderType(1)
	Actor_220.DisplayDesc.ModelId = 0
	Actor_220.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_71.osgb"
	Actor_220.DisplayDesc.Outfit = ""
	Actor_220.DisplayDesc.Weapon = ""
	Actor_220.DisplayDesc.Mode = ""
	Actor_220.DisplayDesc.UseLight = false
	Actor_220.DisplayDesc.CastShadow = true
	Actor_220.DisplayDesc.ColorR = 1
	Actor_220.DisplayDesc.ColorG = 9.21956e-041
	Actor_220.DisplayDesc.ColorB = 2.03966e-023
	Actor_220.DisplayDesc.ColorA = 5.83155e-039
	Actor_220:SetModelState(1)
	Actor_220.PhysicDesc.Pos.X = 533.375
	Actor_220.PhysicDesc.Pos.Y = 0.976563
	Actor_220.PhysicDesc.Pos.Z = 555.875
	Actor_220.PhysicDesc.Pos.Rotation = 90
	Actor_220.PhysicDesc.Density = 0
	Actor_220.PhysicDesc.Collidable = true
	Actor_220.PhysicDesc.SizeX = 0
	Actor_220.PhysicDesc.SizeY = 0
	Actor_220.PhysicDesc.SizeZ = 0
	Actor_220.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_71.phy"
	Actor_220:SetPhysicalActorType(1)
	Actor_220:SetPhysicalShape(5)
	Actor_220.ExtraInfo.Name = ""
	Actor_220.ExtraInfo.NameColorR = 2.03976e-023
	Actor_220.ExtraInfo.NameColorG = 5.83155e-039
	Actor_220.ExtraInfo.NameColorB = 5.83155e-039
	Actor_220H = ActorHandler(Actor_220)
	environment:AddActorObject(Actor_220H)

	Actor_221 = ActorObjectInfo(221)
	Actor_221:SetRenderType(1)
	Actor_221.DisplayDesc.ModelId = 0
	Actor_221.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_71.osgb"
	Actor_221.DisplayDesc.Outfit = ""
	Actor_221.DisplayDesc.Weapon = ""
	Actor_221.DisplayDesc.Mode = ""
	Actor_221.DisplayDesc.UseLight = false
	Actor_221.DisplayDesc.CastShadow = false
	Actor_221.DisplayDesc.ColorR = 1.4013e-045
	Actor_221.DisplayDesc.ColorG = 1
	Actor_221.DisplayDesc.ColorB = 1
	Actor_221.DisplayDesc.ColorA = 1.4013e-045
	Actor_221:SetModelState(1)
	Actor_221.PhysicDesc.Pos.X = 533.375
	Actor_221.PhysicDesc.Pos.Y = 0.976563
	Actor_221.PhysicDesc.Pos.Z = 559.125
	Actor_221.PhysicDesc.Pos.Rotation = 90
	Actor_221.PhysicDesc.Density = 0
	Actor_221.PhysicDesc.Collidable = true
	Actor_221.PhysicDesc.SizeX = 0
	Actor_221.PhysicDesc.SizeY = 0
	Actor_221.PhysicDesc.SizeZ = 0
	Actor_221.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_71.phy"
	Actor_221:SetPhysicalActorType(1)
	Actor_221:SetPhysicalShape(5)
	Actor_221.ExtraInfo.Name = ""
	Actor_221.ExtraInfo.NameColorR = 0
	Actor_221.ExtraInfo.NameColorG = 0
	Actor_221.ExtraInfo.NameColorB = 0
	Actor_221H = ActorHandler(Actor_221)
	environment:AddActorObject(Actor_221H)

	Actor_222 = ActorObjectInfo(222)
	Actor_222:SetRenderType(1)
	Actor_222.DisplayDesc.ModelId = 0
	Actor_222.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_72.osgb"
	Actor_222.DisplayDesc.Outfit = ""
	Actor_222.DisplayDesc.Weapon = ""
	Actor_222.DisplayDesc.Mode = ""
	Actor_222.DisplayDesc.UseLight = false
	Actor_222.DisplayDesc.CastShadow = false
	Actor_222.DisplayDesc.ColorR = 4.34403e-044
	Actor_222.DisplayDesc.ColorG = 4.48416e-044
	Actor_222.DisplayDesc.ColorB = 4.62428e-044
	Actor_222.DisplayDesc.ColorA = 4.76441e-044
	Actor_222:SetModelState(1)
	Actor_222.PhysicDesc.Pos.X = 537.25
	Actor_222.PhysicDesc.Pos.Y = 0.976563
	Actor_222.PhysicDesc.Pos.Z = 557.5
	Actor_222.PhysicDesc.Pos.Rotation = 0
	Actor_222.PhysicDesc.Density = 6.72623e-044
	Actor_222.PhysicDesc.Collidable = true
	Actor_222.PhysicDesc.SizeX = 7.00649e-044
	Actor_222.PhysicDesc.SizeY = 7.14662e-044
	Actor_222.PhysicDesc.SizeZ = 7.28675e-044
	Actor_222.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_72.phy"
	Actor_222:SetPhysicalActorType(1)
	Actor_222:SetPhysicalShape(5)
	Actor_222.ExtraInfo.Name = ""
	Actor_222.ExtraInfo.NameColorR = 9.94922e-044
	Actor_222.ExtraInfo.NameColorG = 1.00893e-043
	Actor_222.ExtraInfo.NameColorB = 1.02295e-043
	Actor_222H = ActorHandler(Actor_222)
	environment:AddActorObject(Actor_222H)

	Actor_223 = ActorObjectInfo(223)
	Actor_223:SetRenderType(1)
	Actor_223.DisplayDesc.ModelId = 78
	Actor_223.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_72.osgb"
	Actor_223.DisplayDesc.Outfit = ""
	Actor_223.DisplayDesc.Weapon = ""
	Actor_223.DisplayDesc.Mode = ""
	Actor_223.DisplayDesc.UseLight = false
	Actor_223.DisplayDesc.CastShadow = false
	Actor_223.DisplayDesc.ColorR = 1.52742e-043
	Actor_223.DisplayDesc.ColorG = 1.54143e-043
	Actor_223.DisplayDesc.ColorB = 1.55544e-043
	Actor_223.DisplayDesc.ColorA = 1.56945e-043
	Actor_223:SetModelState(1)
	Actor_223.PhysicDesc.Pos.X = 535.5
	Actor_223.PhysicDesc.Pos.Y = 0.976563
	Actor_223.PhysicDesc.Pos.Z = 559.25
	Actor_223.PhysicDesc.Pos.Rotation = 90
	Actor_223.PhysicDesc.Density = 1.76564e-043
	Actor_223.PhysicDesc.Collidable = true
	Actor_223.PhysicDesc.SizeX = 1.79366e-043
	Actor_223.PhysicDesc.SizeY = 1.80768e-043
	Actor_223.PhysicDesc.SizeZ = 1.82169e-043
	Actor_223.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_72.phy"
	Actor_223:SetPhysicalActorType(1)
	Actor_223:SetPhysicalShape(5)
	Actor_223.ExtraInfo.Name = ""
	Actor_223.ExtraInfo.NameColorR = 2.08793e-043
	Actor_223.ExtraInfo.NameColorG = 2.10195e-043
	Actor_223.ExtraInfo.NameColorB = 2.11596e-043
	Actor_223H = ActorHandler(Actor_223)
	environment:AddActorObject(Actor_223H)

	Actor_224 = ActorObjectInfo(224)
	Actor_224:SetRenderType(1)
	Actor_224.DisplayDesc.ModelId = 0
	Actor_224.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_72.osgb"
	Actor_224.DisplayDesc.Outfit = ""
	Actor_224.DisplayDesc.Weapon = ""
	Actor_224.DisplayDesc.Mode = ""
	Actor_224.DisplayDesc.UseLight = false
	Actor_224.DisplayDesc.CastShadow = false
	Actor_224.DisplayDesc.ColorR = 9.86919e-031
	Actor_224.DisplayDesc.ColorG = 1
	Actor_224.DisplayDesc.ColorB = 1
	Actor_224.DisplayDesc.ColorA = 1
	Actor_224:SetModelState(1)
	Actor_224.PhysicDesc.Pos.X = 535.5
	Actor_224.PhysicDesc.Pos.Y = 0.976563
	Actor_224.PhysicDesc.Pos.Z = 555.75
	Actor_224.PhysicDesc.Pos.Rotation = 90
	Actor_224.PhysicDesc.Density = 9.80911e-031
	Actor_224.PhysicDesc.Collidable = true
	Actor_224.PhysicDesc.SizeX = 9.86956e-031
	Actor_224.PhysicDesc.SizeY = 0
	Actor_224.PhysicDesc.SizeZ = 0
	Actor_224.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_72.phy"
	Actor_224:SetPhysicalActorType(1)
	Actor_224:SetPhysicalShape(5)
	Actor_224.ExtraInfo.Name = ""
	Actor_224.ExtraInfo.NameColorR = 0
	Actor_224.ExtraInfo.NameColorG = 0
	Actor_224.ExtraInfo.NameColorB = 0
	Actor_224H = ActorHandler(Actor_224)
	environment:AddActorObject(Actor_224H)

	Actor_225 = ActorObjectInfo(225)
	Actor_225:SetRenderType(1)
	Actor_225.DisplayDesc.ModelId = 1073741888
	Actor_225.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_73.osgb"
	Actor_225.DisplayDesc.Outfit = ""
	Actor_225.DisplayDesc.Weapon = ""
	Actor_225.DisplayDesc.Mode = ""
	Actor_225.DisplayDesc.UseLight = false
	Actor_225.DisplayDesc.CastShadow = false
	Actor_225.DisplayDesc.ColorR = 1
	Actor_225.DisplayDesc.ColorG = 1
	Actor_225.DisplayDesc.ColorB = 7.21669e-043
	Actor_225.DisplayDesc.ColorA = 8.98092e-042
	Actor_225:SetModelState(1)
	Actor_225.PhysicDesc.Pos.X = 484.5
	Actor_225.PhysicDesc.Pos.Y = 0.976563
	Actor_225.PhysicDesc.Pos.Z = 575.25
	Actor_225.PhysicDesc.Pos.Rotation = 180
	Actor_225.PhysicDesc.Density = 0
	Actor_225.PhysicDesc.Collidable = true
	Actor_225.PhysicDesc.SizeX = 1.97583e-043
	Actor_225.PhysicDesc.SizeY = 1.93379e-043
	Actor_225.PhysicDesc.SizeZ = 0
	Actor_225.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_73.phy"
	Actor_225:SetPhysicalActorType(1)
	Actor_225:SetPhysicalShape(5)
	Actor_225.ExtraInfo.Name = ""
	Actor_225.ExtraInfo.NameColorR = 3.329e-035
	Actor_225.ExtraInfo.NameColorG = 4.70568e-024
	Actor_225.ExtraInfo.NameColorB = 2.34879e-023
	Actor_225H = ActorHandler(Actor_225)
	environment:AddActorObject(Actor_225H)

	Actor_226 = ActorObjectInfo(226)
	Actor_226:SetRenderType(1)
	Actor_226.DisplayDesc.ModelId = 131148
	Actor_226.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_48.osgb"
	Actor_226.DisplayDesc.Outfit = ""
	Actor_226.DisplayDesc.Weapon = ""
	Actor_226.DisplayDesc.Mode = ""
	Actor_226.DisplayDesc.UseLight = false
	Actor_226.DisplayDesc.CastShadow = false
	Actor_226.DisplayDesc.ColorR = 1.0390625
	Actor_226.DisplayDesc.ColorG = 1.06383
	Actor_226.DisplayDesc.ColorB = 1.0390625
	Actor_226.DisplayDesc.ColorA = 5.88234
	Actor_226:SetModelState(1)
	Actor_226.PhysicDesc.Pos.X = 535.5
	Actor_226.PhysicDesc.Pos.Y = 1.14844
	Actor_226.PhysicDesc.Pos.Z = 557.5
	Actor_226.PhysicDesc.Pos.Rotation = 90
	Actor_226.PhysicDesc.Density = 0
	Actor_226.PhysicDesc.Collidable = true
	Actor_226.PhysicDesc.SizeX = 1.4013e-045
	Actor_226.PhysicDesc.SizeY = 6.75426e-024
	Actor_226.PhysicDesc.SizeZ = 2.10195e-044
	Actor_226.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_48.phy"
	Actor_226:SetPhysicalActorType(1)
	Actor_226:SetPhysicalShape(5)
	Actor_226.ExtraInfo.Name = ""
	Actor_226.ExtraInfo.NameColorR = 0
	Actor_226.ExtraInfo.NameColorG = 0
	Actor_226.ExtraInfo.NameColorB = 0
	Actor_226H = ActorHandler(Actor_226)
	environment:AddActorObject(Actor_226H)

	Actor_227 = ActorObjectInfo(227)
	Actor_227:SetRenderType(1)
	Actor_227.DisplayDesc.ModelId = 0
	Actor_227.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.osgb"
	Actor_227.DisplayDesc.Outfit = ""
	Actor_227.DisplayDesc.Weapon = ""
	Actor_227.DisplayDesc.Mode = ""
	Actor_227.DisplayDesc.UseLight = false
	Actor_227.DisplayDesc.CastShadow = false
	Actor_227.DisplayDesc.ColorR = 1.05327e-034
	Actor_227.DisplayDesc.ColorG = 4.57356e-038
	Actor_227.DisplayDesc.ColorB = 7.77577e-024
	Actor_227.DisplayDesc.ColorA = 1.83682e-040
	Actor_227:SetModelState(1)
	Actor_227.PhysicDesc.Pos.X = 431.75
	Actor_227.PhysicDesc.Pos.Y = 2.92969
	Actor_227.PhysicDesc.Pos.Z = 634
	Actor_227.PhysicDesc.Pos.Rotation = 180
	Actor_227.PhysicDesc.Density = 4.57352e-038
	Actor_227.PhysicDesc.Collidable = true
	Actor_227.PhysicDesc.SizeX = 9.18358e-040
	Actor_227.PhysicDesc.SizeY = 1.0533e-034
	Actor_227.PhysicDesc.SizeZ = 6.754e-024
	Actor_227.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.phy"
	Actor_227:SetPhysicalActorType(1)
	Actor_227:SetPhysicalShape(5)
	Actor_227.ExtraInfo.Name = ""
	Actor_227.ExtraInfo.NameColorR = 1.05326e-034
	Actor_227.ExtraInfo.NameColorG = 4.57352e-038
	Actor_227.ExtraInfo.NameColorB = 6.35708e-024
	Actor_227H = ActorHandler(Actor_227)
	environment:AddActorObject(Actor_227H)

	Actor_228 = ActorObjectInfo(228)
	Actor_228:SetRenderType(1)
	Actor_228.DisplayDesc.ModelId = 131075
	Actor_228.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_228.DisplayDesc.Outfit = ""
	Actor_228.DisplayDesc.Weapon = ""
	Actor_228.DisplayDesc.Mode = ""
	Actor_228.DisplayDesc.UseLight = false
	Actor_228.DisplayDesc.CastShadow = true
	Actor_228.DisplayDesc.ColorR = 1.01176e+038
	Actor_228.DisplayDesc.ColorG = -2
	Actor_228.DisplayDesc.ColorB = 1
	Actor_228.DisplayDesc.ColorA = 1
	Actor_228:SetModelState(1)
	Actor_228.PhysicDesc.Pos.X = 444.5
	Actor_228.PhysicDesc.Pos.Y = 3.90625
	Actor_228.PhysicDesc.Pos.Z = 649.5
	Actor_228.PhysicDesc.Pos.Rotation = 90
	Actor_228.PhysicDesc.Density = 0
	Actor_228.PhysicDesc.Collidable = true
	Actor_228.PhysicDesc.SizeX = 0
	Actor_228.PhysicDesc.SizeY = 0
	Actor_228.PhysicDesc.SizeZ = -4.39453
	Actor_228.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_228:SetPhysicalActorType(1)
	Actor_228:SetPhysicalShape(5)
	Actor_228.ExtraInfo.Name = ""
	Actor_228.ExtraInfo.NameColorR = -70.7966
	Actor_228.ExtraInfo.NameColorG = -5.23627e-037
	Actor_228.ExtraInfo.NameColorB = 4.2039e-044
	Actor_228H = ActorHandler(Actor_228)
	environment:AddActorObject(Actor_228H)

	Actor_229 = ActorObjectInfo(229)
	Actor_229:SetRenderType(1)
	Actor_229.DisplayDesc.ModelId = 0
	Actor_229.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_229.DisplayDesc.Outfit = ""
	Actor_229.DisplayDesc.Weapon = ""
	Actor_229.DisplayDesc.Mode = ""
	Actor_229.DisplayDesc.UseLight = false
	Actor_229.DisplayDesc.CastShadow = false
	Actor_229.DisplayDesc.ColorR = 1
	Actor_229.DisplayDesc.ColorG = 3.81798e-024
	Actor_229.DisplayDesc.ColorB = 7.36867
	Actor_229.DisplayDesc.ColorA = 1.86062e-034
	Actor_229:SetModelState(1)
	Actor_229.PhysicDesc.Pos.X = 447.5
	Actor_229.PhysicDesc.Pos.Y = 3.90625
	Actor_229.PhysicDesc.Pos.Z = 650.5
	Actor_229.PhysicDesc.Pos.Rotation = 180
	Actor_229.PhysicDesc.Density = 0
	Actor_229.PhysicDesc.Collidable = true
	Actor_229.PhysicDesc.SizeX = 0
	Actor_229.PhysicDesc.SizeY = 0
	Actor_229.PhysicDesc.SizeZ = 0
	Actor_229.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_229:SetPhysicalActorType(1)
	Actor_229:SetPhysicalShape(5)
	Actor_229.ExtraInfo.Name = ""
	Actor_229.ExtraInfo.NameColorR = 1.05325e-034
	Actor_229.ExtraInfo.NameColorG = 1.42442e-023
	Actor_229.ExtraInfo.NameColorB = 1.52369e-023
	Actor_229H = ActorHandler(Actor_229)
	environment:AddActorObject(Actor_229H)

	Actor_230 = ActorObjectInfo(230)
	Actor_230:SetRenderType(1)
	Actor_230.DisplayDesc.ModelId = 1083572224
	Actor_230.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_35.osgb"
	Actor_230.DisplayDesc.Outfit = ""
	Actor_230.DisplayDesc.Weapon = ""
	Actor_230.DisplayDesc.Mode = ""
	Actor_230.DisplayDesc.UseLight = false
	Actor_230.DisplayDesc.CastShadow = false
	Actor_230.DisplayDesc.ColorR = 3.51563
	Actor_230.DisplayDesc.ColorG = -1.5625
	Actor_230.DisplayDesc.ColorB = 3.125
	Actor_230.DisplayDesc.ColorA = 3.51563
	Actor_230:SetModelState(1)
	Actor_230.PhysicDesc.Pos.X = 437.25
	Actor_230.PhysicDesc.Pos.Y = 3.41797
	Actor_230.PhysicDesc.Pos.Z = 641
	Actor_230.PhysicDesc.Pos.Rotation = 90
	Actor_230.PhysicDesc.Density = 3.90625
	Actor_230.PhysicDesc.Collidable = true
	Actor_230.PhysicDesc.SizeX = 6.15299e-039
	Actor_230.PhysicDesc.SizeY = 2.55792e-035
	Actor_230.PhysicDesc.SizeZ = 1.87161e-031
	Actor_230.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_35.phy"
	Actor_230:SetPhysicalActorType(1)
	Actor_230:SetPhysicalShape(5)
	Actor_230.ExtraInfo.Name = ""
	Actor_230.ExtraInfo.NameColorR = 4.1044e-042
	Actor_230.ExtraInfo.NameColorG = 0
	Actor_230.ExtraInfo.NameColorB = 1.4013e-045
	Actor_230H = ActorHandler(Actor_230)
	environment:AddActorObject(Actor_230H)

	Actor_231 = ActorObjectInfo(231)
	Actor_231:SetRenderType(1)
	Actor_231.DisplayDesc.ModelId = 13369553
	Actor_231.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_231.DisplayDesc.Outfit = ""
	Actor_231.DisplayDesc.Weapon = ""
	Actor_231.DisplayDesc.Mode = ""
	Actor_231.DisplayDesc.UseLight = false
	Actor_231.DisplayDesc.CastShadow = true
	Actor_231.DisplayDesc.ColorR = 1
	Actor_231.DisplayDesc.ColorG = 1
	Actor_231.DisplayDesc.ColorB = 1
	Actor_231.DisplayDesc.ColorA = 1
	Actor_231:SetModelState(1)
	Actor_231.PhysicDesc.Pos.X = 461.5
	Actor_231.PhysicDesc.Pos.Y = 1.95313
	Actor_231.PhysicDesc.Pos.Z = 640.5
	Actor_231.PhysicDesc.Pos.Rotation = 180
	Actor_231.PhysicDesc.Density = 6.36077e-024
	Actor_231.PhysicDesc.Collidable = true
	Actor_231.PhysicDesc.SizeX = 1.45743e+019
	Actor_231.PhysicDesc.SizeY = 1.53002e+019
	Actor_231.PhysicDesc.SizeZ = 5.19669e-008
	Actor_231.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
	Actor_231:SetPhysicalActorType(1)
	Actor_231:SetPhysicalShape(5)
	Actor_231.ExtraInfo.Name = ""
	Actor_231.ExtraInfo.NameColorR = 2.64305e-006
	Actor_231.ExtraInfo.NameColorG = 5.4973e-023
	Actor_231.ExtraInfo.NameColorB = 9.45942e-039
	Actor_231H = ActorHandler(Actor_231)
	environment:AddActorObject(Actor_231H)

	Actor_232 = ActorObjectInfo(232)
	Actor_232:SetRenderType(1)
	Actor_232.DisplayDesc.ModelId = 1080098816
	Actor_232.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_74.osgb"
	Actor_232.DisplayDesc.Outfit = ""
	Actor_232.DisplayDesc.Weapon = ""
	Actor_232.DisplayDesc.Mode = ""
	Actor_232.DisplayDesc.UseLight = false
	Actor_232.DisplayDesc.CastShadow = true
	Actor_232.DisplayDesc.ColorR = 6.25
	Actor_232.DisplayDesc.ColorG = -0.78125
	Actor_232.DisplayDesc.ColorB = 2.92969
	Actor_232.DisplayDesc.ColorA = 6.25
	Actor_232:SetModelState(1)
	Actor_232.PhysicDesc.Pos.X = 443.25
	Actor_232.PhysicDesc.Pos.Y = 12.6953
	Actor_232.PhysicDesc.Pos.Z = 631
	Actor_232.PhysicDesc.Pos.Rotation = -90
	Actor_232.PhysicDesc.Density = 3.51563
	Actor_232.PhysicDesc.Collidable = true
	Actor_232.PhysicDesc.SizeX = 0.585938
	Actor_232.PhysicDesc.SizeY = 3.51563
	Actor_232.PhysicDesc.SizeZ = 6.64063
	Actor_232.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_74.phy"
	Actor_232:SetPhysicalActorType(1)
	Actor_232:SetPhysicalShape(5)
	Actor_232.ExtraInfo.Name = ""
	Actor_232.ExtraInfo.NameColorR = 0.585938
	Actor_232.ExtraInfo.NameColorG = 2.34375
	Actor_232.ExtraInfo.NameColorB = 6.83594
	Actor_232H = ActorHandler(Actor_232)
	environment:AddActorObject(Actor_232H)

	Actor_233 = ActorObjectInfo(233)
	Actor_233:SetRenderType(1)
	Actor_233.DisplayDesc.ModelId = 0
	Actor_233.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_75.osgb"
	Actor_233.DisplayDesc.Outfit = ""
	Actor_233.DisplayDesc.Weapon = ""
	Actor_233.DisplayDesc.Mode = ""
	Actor_233.DisplayDesc.UseLight = false
	Actor_233.DisplayDesc.CastShadow = false
	Actor_233.DisplayDesc.ColorR = 1.02316e-034
	Actor_233.DisplayDesc.ColorG = 2.8379e-024
	Actor_233.DisplayDesc.ColorB = 3.4681e-024
	Actor_233.DisplayDesc.ColorA = 1
	Actor_233:SetModelState(1)
	Actor_233.PhysicDesc.Pos.X = 443.25
	Actor_233.PhysicDesc.Pos.Y = 12.6953
	Actor_233.PhysicDesc.Pos.Z = 631
	Actor_233.PhysicDesc.Pos.Rotation = -90
	Actor_233.PhysicDesc.Density = 1
	Actor_233.PhysicDesc.Collidable = true
	Actor_233.PhysicDesc.SizeX = -4.37114e-008
	Actor_233.PhysicDesc.SizeY = 2.31214e-043
	Actor_233.PhysicDesc.SizeZ = 1.01021e-039
	Actor_233.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_75.phy"
	Actor_233:SetPhysicalActorType(1)
	Actor_233:SetPhysicalShape(5)
	Actor_233.ExtraInfo.Name = ""
	Actor_233.ExtraInfo.NameColorR = 0
	Actor_233.ExtraInfo.NameColorG = 0
	Actor_233.ExtraInfo.NameColorB = 2.62043e-043
	Actor_233H = ActorHandler(Actor_233)
	environment:AddActorObject(Actor_233H)

	Actor_234 = ActorObjectInfo(234)
	Actor_234:SetRenderType(1)
	Actor_234.DisplayDesc.ModelId = 131084
	Actor_234.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.osgb"
	Actor_234.DisplayDesc.Outfit = ""
	Actor_234.DisplayDesc.Weapon = ""
	Actor_234.DisplayDesc.Mode = ""
	Actor_234.DisplayDesc.UseLight = false
	Actor_234.DisplayDesc.CastShadow = false
	Actor_234.DisplayDesc.ColorR = 1
	Actor_234.DisplayDesc.ColorG = 1
	Actor_234.DisplayDesc.ColorB = 1
	Actor_234.DisplayDesc.ColorA = 5.41832e-039
	Actor_234:SetModelState(1)
	Actor_234.PhysicDesc.Pos.X = 431.75
	Actor_234.PhysicDesc.Pos.Y = 2.92969
	Actor_234.PhysicDesc.Pos.Z = 634
	Actor_234.PhysicDesc.Pos.Rotation = 180
	Actor_234.PhysicDesc.Density = 1.45743e+019
	Actor_234.PhysicDesc.Collidable = true
	Actor_234.PhysicDesc.SizeX = 8.1204e-010
	Actor_234.PhysicDesc.SizeY = 1.31284e+019
	Actor_234.PhysicDesc.SizeZ = 0
	Actor_234.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.phy"
	Actor_234:SetPhysicalActorType(1)
	Actor_234:SetPhysicalShape(5)
	Actor_234.ExtraInfo.Name = ""
	Actor_234.ExtraInfo.NameColorR = 2.6332e-035
	Actor_234.ExtraInfo.NameColorG = 1.17496e-023
	Actor_234.ExtraInfo.NameColorB = 6.28707e-023
	Actor_234H = ActorHandler(Actor_234)
	environment:AddActorObject(Actor_234H)

	Actor_235 = ActorObjectInfo(235)
	Actor_235:SetRenderType(1)
	Actor_235.DisplayDesc.ModelId = 0
	Actor_235.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_76.osgb"
	Actor_235.DisplayDesc.Outfit = ""
	Actor_235.DisplayDesc.Weapon = ""
	Actor_235.DisplayDesc.Mode = ""
	Actor_235.DisplayDesc.UseLight = false
	Actor_235.DisplayDesc.CastShadow = true
	Actor_235.DisplayDesc.ColorR = 7.85817e-023
	Actor_235.DisplayDesc.ColorG = 1.83674e-040
	Actor_235.DisplayDesc.ColorB = 1.05328e-034
	Actor_235.DisplayDesc.ColorA = 6.84312e-023
	Actor_235:SetModelState(1)
	Actor_235.PhysicDesc.Pos.X = 443.25
	Actor_235.PhysicDesc.Pos.Y = 12.6953
	Actor_235.PhysicDesc.Pos.Z = 631
	Actor_235.PhysicDesc.Pos.Rotation = -90
	Actor_235.PhysicDesc.Density = 1.83677e-040
	Actor_235.PhysicDesc.Collidable = true
	Actor_235.PhysicDesc.SizeX = 4.57352e-038
	Actor_235.PhysicDesc.SizeY = 6.47764e-023
	Actor_235.PhysicDesc.SizeZ = 1.83674e-040
	Actor_235.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_76.phy"
	Actor_235:SetPhysicalActorType(1)
	Actor_235:SetPhysicalShape(5)
	Actor_235.ExtraInfo.Name = ""
	Actor_235.ExtraInfo.NameColorR = 6.84355e-023
	Actor_235.ExtraInfo.NameColorG = 9.18369e-041
	Actor_235.ExtraInfo.NameColorB = 1.26818e-042
	Actor_235H = ActorHandler(Actor_235)
	environment:AddActorObject(Actor_235H)

	Actor_236 = ActorObjectInfo(236)
	Actor_236:SetRenderType(1)
	Actor_236.DisplayDesc.ModelId = 1179648
	Actor_236.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_77.osgb"
	Actor_236.DisplayDesc.Outfit = ""
	Actor_236.DisplayDesc.Weapon = ""
	Actor_236.DisplayDesc.Mode = ""
	Actor_236.DisplayDesc.UseLight = false
	Actor_236.DisplayDesc.CastShadow = false
	Actor_236.DisplayDesc.ColorR = 1
	Actor_236.DisplayDesc.ColorG = 4.2039e-045
	Actor_236.DisplayDesc.ColorB = 4.37676e-031
	Actor_236.DisplayDesc.ColorA = 9.18369e-040
	Actor_236:SetModelState(1)
	Actor_236.PhysicDesc.Pos.X = 443.25
	Actor_236.PhysicDesc.Pos.Y = 12.6953
	Actor_236.PhysicDesc.Pos.Z = 631
	Actor_236.PhysicDesc.Pos.Rotation = -90
	Actor_236.PhysicDesc.Density = 0
	Actor_236.PhysicDesc.Collidable = true
	Actor_236.PhysicDesc.SizeX = 0
	Actor_236.PhysicDesc.SizeY = 0
	Actor_236.PhysicDesc.SizeZ = 0
	Actor_236.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_77.phy"
	Actor_236:SetPhysicalActorType(1)
	Actor_236:SetPhysicalShape(5)
	Actor_236.ExtraInfo.Name = ""
	Actor_236.ExtraInfo.NameColorR = 0
	Actor_236.ExtraInfo.NameColorG = 0
	Actor_236.ExtraInfo.NameColorB = 0
	Actor_236H = ActorHandler(Actor_236)
	environment:AddActorObject(Actor_236H)

	Actor_237 = ActorObjectInfo(237)
	Actor_237:SetRenderType(1)
	Actor_237.DisplayDesc.ModelId = 24707528
	Actor_237.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_78.osgb"
	Actor_237.DisplayDesc.Outfit = ""
	Actor_237.DisplayDesc.Weapon = ""
	Actor_237.DisplayDesc.Mode = ""
	Actor_237.DisplayDesc.UseLight = false
	Actor_237.DisplayDesc.CastShadow = false
	Actor_237.DisplayDesc.ColorR = 1
	Actor_237.DisplayDesc.ColorG = 1
	Actor_237.DisplayDesc.ColorB = 1
	Actor_237.DisplayDesc.ColorA = 1
	Actor_237:SetModelState(1)
	Actor_237.PhysicDesc.Pos.X = 443.25
	Actor_237.PhysicDesc.Pos.Y = 12.6953
	Actor_237.PhysicDesc.Pos.Z = 631
	Actor_237.PhysicDesc.Pos.Rotation = -90
	Actor_237.PhysicDesc.Density = 5.51021e-040
	Actor_237.PhysicDesc.Collidable = true
	Actor_237.PhysicDesc.SizeX = 4.22074e-034
	Actor_237.PhysicDesc.SizeY = 9.48103e-034
	Actor_237.PhysicDesc.SizeZ = 0
	Actor_237.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_78.phy"
	Actor_237:SetPhysicalActorType(1)
	Actor_237:SetPhysicalShape(5)
	Actor_237.ExtraInfo.Name = ""
	Actor_237.ExtraInfo.NameColorR = 0
	Actor_237.ExtraInfo.NameColorG = 2.8026e-045
	Actor_237.ExtraInfo.NameColorB = 1.83674e-040
	Actor_237H = ActorHandler(Actor_237)
	environment:AddActorObject(Actor_237H)

	Actor_238 = ActorObjectInfo(238)
	Actor_238:SetRenderType(1)
	Actor_238.DisplayDesc.ModelId = 0
	Actor_238.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_79.osgb"
	Actor_238.DisplayDesc.Outfit = ""
	Actor_238.DisplayDesc.Weapon = ""
	Actor_238.DisplayDesc.Mode = ""
	Actor_238.DisplayDesc.UseLight = false
	Actor_238.DisplayDesc.CastShadow = false
	Actor_238.DisplayDesc.ColorR = 1
	Actor_238.DisplayDesc.ColorG = 1
	Actor_238.DisplayDesc.ColorB = 1
	Actor_238.DisplayDesc.ColorA = 1
	Actor_238:SetModelState(1)
	Actor_238.PhysicDesc.Pos.X = 443.25
	Actor_238.PhysicDesc.Pos.Y = 12.6953
	Actor_238.PhysicDesc.Pos.Z = 631
	Actor_238.PhysicDesc.Pos.Rotation = -90
	Actor_238.PhysicDesc.Density = 1.83689e-040
	Actor_238.PhysicDesc.Collidable = true
	Actor_238.PhysicDesc.SizeX = 4.57354e-038
	Actor_238.PhysicDesc.SizeY = 4.69415e-023
	Actor_238.PhysicDesc.SizeZ = 1.83674e-040
	Actor_238.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_79.phy"
	Actor_238:SetPhysicalActorType(1)
	Actor_238:SetPhysicalShape(5)
	Actor_238.ExtraInfo.Name = ""
	Actor_238.ExtraInfo.NameColorR = 0.650391
	Actor_238.ExtraInfo.NameColorG = 0.259766
	Actor_238.ExtraInfo.NameColorB = 0.128906
	Actor_238H = ActorHandler(Actor_238)
	environment:AddActorObject(Actor_238H)

	Actor_239 = ActorObjectInfo(239)
	Actor_239:SetRenderType(1)
	Actor_239.DisplayDesc.ModelId = 1062396000
	Actor_239.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_80.osgb"
	Actor_239.DisplayDesc.Outfit = ""
	Actor_239.DisplayDesc.Weapon = ""
	Actor_239.DisplayDesc.Mode = ""
	Actor_239.DisplayDesc.UseLight = false
	Actor_239.DisplayDesc.CastShadow = true
	Actor_239.DisplayDesc.ColorR = 1.200058
	Actor_239.DisplayDesc.ColorG = 1.92285
	Actor_239.DisplayDesc.ColorB = -0.0674075
	Actor_239.DisplayDesc.ColorA = 1.398025
	Actor_239:SetModelState(1)
	Actor_239.PhysicDesc.Pos.X = 443.25
	Actor_239.PhysicDesc.Pos.Y = 12.6953
	Actor_239.PhysicDesc.Pos.Z = 631
	Actor_239.PhysicDesc.Pos.Rotation = -90
	Actor_239.PhysicDesc.Density = -0.0674075
	Actor_239.PhysicDesc.Collidable = true
	Actor_239.PhysicDesc.SizeX = 0.914895
	Actor_239.PhysicDesc.SizeY = 0.329128
	Actor_239.PhysicDesc.SizeZ = 0.200058
	Actor_239.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_80.phy"
	Actor_239:SetPhysicalActorType(1)
	Actor_239:SetPhysicalShape(5)
	Actor_239.ExtraInfo.Name = ""
	Actor_239.ExtraInfo.NameColorR = 2.63319e-035
	Actor_239.ExtraInfo.NameColorG = 9.12882e-031
	Actor_239.ExtraInfo.NameColorB = 4.57351e-038
	Actor_239H = ActorHandler(Actor_239)
	environment:AddActorObject(Actor_239H)

	Actor_240 = ActorObjectInfo(240)
	Actor_240:SetRenderType(1)
	Actor_240.DisplayDesc.ModelId = 131109
	Actor_240.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_240.DisplayDesc.Outfit = ""
	Actor_240.DisplayDesc.Weapon = ""
	Actor_240.DisplayDesc.Mode = ""
	Actor_240.DisplayDesc.UseLight = false
	Actor_240.DisplayDesc.CastShadow = true
	Actor_240.DisplayDesc.ColorR = 3.40282e+038
	Actor_240.DisplayDesc.ColorG = -3.40282e+038
	Actor_240.DisplayDesc.ColorB = -3.40282e+038
	Actor_240.DisplayDesc.ColorA = -3.40282e+038
	Actor_240:SetModelState(1)
	Actor_240.PhysicDesc.Pos.X = 489.5
	Actor_240.PhysicDesc.Pos.Y = 5.85938
	Actor_240.PhysicDesc.Pos.Z = 651.5
	Actor_240.PhysicDesc.Pos.Rotation = 90
	Actor_240.PhysicDesc.Density = 0
	Actor_240.PhysicDesc.Collidable = true
	Actor_240.PhysicDesc.SizeX = 0
	Actor_240.PhysicDesc.SizeY = 0
	Actor_240.PhysicDesc.SizeZ = 0
	Actor_240.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_240:SetPhysicalActorType(1)
	Actor_240:SetPhysicalShape(5)
	Actor_240.ExtraInfo.Name = ""
	Actor_240.ExtraInfo.NameColorR = 1.05326e-034
	Actor_240.ExtraInfo.NameColorG = 4.57352e-038
	Actor_240.ExtraInfo.NameColorB = 2.65676e-024
	Actor_240H = ActorHandler(Actor_240)
	environment:AddActorObject(Actor_240H)

	Actor_241 = ActorObjectInfo(241)
	Actor_241:SetRenderType(1)
	Actor_241.DisplayDesc.ModelId = 0
	Actor_241.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_81.osgb"
	Actor_241.DisplayDesc.Outfit = ""
	Actor_241.DisplayDesc.Weapon = ""
	Actor_241.DisplayDesc.Mode = ""
	Actor_241.DisplayDesc.UseLight = false
	Actor_241.DisplayDesc.CastShadow = false
	Actor_241.DisplayDesc.ColorR = 1
	Actor_241.DisplayDesc.ColorG = 1.576471
	Actor_241.DisplayDesc.ColorB = 1.403922
	Actor_241.DisplayDesc.ColorA = 1
	Actor_241:SetModelState(1)
	Actor_241.PhysicDesc.Pos.X = 529.5
	Actor_241.PhysicDesc.Pos.Y = 0.976563
	Actor_241.PhysicDesc.Pos.Z = 613.25
	Actor_241.PhysicDesc.Pos.Rotation = 0
	Actor_241.PhysicDesc.Density = 3.67355e-040
	Actor_241.PhysicDesc.Collidable = true
	Actor_241.PhysicDesc.SizeX = 1.31224e-038
	Actor_241.PhysicDesc.SizeY = 0
	Actor_241.PhysicDesc.SizeZ = 0
	Actor_241.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_81.phy"
	Actor_241:SetPhysicalActorType(1)
	Actor_241:SetPhysicalShape(5)
	Actor_241.ExtraInfo.Name = ""
	Actor_241.ExtraInfo.NameColorR = 4.05816e-042
	Actor_241.ExtraInfo.NameColorG = 0
	Actor_241.ExtraInfo.NameColorB = 1.4013e-045
	Actor_241H = ActorHandler(Actor_241)
	environment:AddActorObject(Actor_241H)

	Actor_242 = ActorObjectInfo(242)
	Actor_242:SetRenderType(1)
	Actor_242.DisplayDesc.ModelId = 0
	Actor_242.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_242.DisplayDesc.Outfit = ""
	Actor_242.DisplayDesc.Weapon = ""
	Actor_242.DisplayDesc.Mode = ""
	Actor_242.DisplayDesc.UseLight = false
	Actor_242.DisplayDesc.CastShadow = false
	Actor_242.DisplayDesc.ColorR = 1.02315e-034
	Actor_242.DisplayDesc.ColorG = 4.57352e-038
	Actor_242.DisplayDesc.ColorB = 3.05946e-024
	Actor_242.DisplayDesc.ColorA = 1
	Actor_242:SetModelState(1)
	Actor_242.PhysicDesc.Pos.X = 534.5
	Actor_242.PhysicDesc.Pos.Y = 10.2539
	Actor_242.PhysicDesc.Pos.Z = 649.5
	Actor_242.PhysicDesc.Pos.Rotation = -90
	Actor_242.PhysicDesc.Density = 8.40779e-045
	Actor_242.PhysicDesc.Collidable = true
	Actor_242.PhysicDesc.SizeX = 3.60134e-043
	Actor_242.PhysicDesc.SizeY = 3.90625
	Actor_242.PhysicDesc.SizeZ = 5.41831e-039
	Actor_242.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_242:SetPhysicalActorType(1)
	Actor_242:SetPhysicalShape(5)
	Actor_242.ExtraInfo.Name = ""
	Actor_242.ExtraInfo.NameColorR = 0
	Actor_242.ExtraInfo.NameColorG = 0
	Actor_242.ExtraInfo.NameColorB = -3.125
	Actor_242H = ActorHandler(Actor_242)
	environment:AddActorObject(Actor_242H)

	Actor_243 = ActorObjectInfo(243)
	Actor_243:SetRenderType(1)
	Actor_243.DisplayDesc.ModelId = 1737210879
	Actor_243.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.osgb"
	Actor_243.DisplayDesc.Outfit = ""
	Actor_243.DisplayDesc.Weapon = ""
	Actor_243.DisplayDesc.Mode = ""
	Actor_243.DisplayDesc.UseLight = false
	Actor_243.DisplayDesc.CastShadow = true
	Actor_243.DisplayDesc.ColorR = 1.31975e+024
	Actor_243.DisplayDesc.ColorG = 1
	Actor_243.DisplayDesc.ColorB = 1
	Actor_243.DisplayDesc.ColorA = 1
	Actor_243:SetModelState(1)
	Actor_243.PhysicDesc.Pos.X = 525.5
	Actor_243.PhysicDesc.Pos.Y = 4.14844
	Actor_243.PhysicDesc.Pos.Z = 622.5
	Actor_243.PhysicDesc.Pos.Rotation = 90
	Actor_243.PhysicDesc.Density = 4.57354e-038
	Actor_243.PhysicDesc.Collidable = true
	Actor_243.PhysicDesc.SizeX = 1.83688e-040
	Actor_243.PhysicDesc.SizeY = 1.05325e-034
	Actor_243.PhysicDesc.SizeZ = 4.57354e-038
	Actor_243.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_2.phy"
	Actor_243:SetPhysicalActorType(1)
	Actor_243:SetPhysicalShape(5)
	Actor_243.ExtraInfo.Name = ""
	Actor_243.ExtraInfo.NameColorR = 3.12055e-024
	Actor_243.ExtraInfo.NameColorG = 3.00405e-024
	Actor_243.ExtraInfo.NameColorB = 0
	Actor_243H = ActorHandler(Actor_243)
	environment:AddActorObject(Actor_243H)

	Actor_244 = ActorObjectInfo(244)
	Actor_244:SetRenderType(1)
	Actor_244.DisplayDesc.ModelId = 1088225280
	Actor_244.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.osgb"
	Actor_244.DisplayDesc.Outfit = ""
	Actor_244.DisplayDesc.Weapon = ""
	Actor_244.DisplayDesc.Mode = ""
	Actor_244.DisplayDesc.UseLight = false
	Actor_244.DisplayDesc.CastShadow = false
	Actor_244.DisplayDesc.ColorR = 1.46875
	Actor_244.DisplayDesc.ColorG = 4.46875
	Actor_244.DisplayDesc.ColorB = 1.28125
	Actor_244.DisplayDesc.ColorA = 5.03125
	Actor_244:SetModelState(1)
	Actor_244.PhysicDesc.Pos.X = 511.125
	Actor_244.PhysicDesc.Pos.Y = 0.976563
	Actor_244.PhysicDesc.Pos.Z = 613
	Actor_244.PhysicDesc.Pos.Rotation = 90
	Actor_244.PhysicDesc.Density = 5.03125
	Actor_244.PhysicDesc.Collidable = true
	Actor_244.PhysicDesc.SizeX = 4.90625
	Actor_244.PhysicDesc.SizeY = 1.28125
	Actor_244.PhysicDesc.SizeZ = 5.03125
	Actor_244.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_52.phy"
	Actor_244:SetPhysicalActorType(1)
	Actor_244:SetPhysicalShape(5)
	Actor_244.ExtraInfo.Name = ""
	Actor_244.ExtraInfo.NameColorR = 1.40625
	Actor_244.ExtraInfo.NameColorG = 6.96875
	Actor_244.ExtraInfo.NameColorB = 1.53125
	Actor_244H = ActorHandler(Actor_244)
	environment:AddActorObject(Actor_244H)

	Actor_245 = ActorObjectInfo(245)
	Actor_245:SetRenderType(1)
	Actor_245.DisplayDesc.ModelId = 0
	Actor_245.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_245.DisplayDesc.Outfit = ""
	Actor_245.DisplayDesc.Weapon = ""
	Actor_245.DisplayDesc.Mode = ""
	Actor_245.DisplayDesc.UseLight = false
	Actor_245.DisplayDesc.CastShadow = false
	Actor_245.DisplayDesc.ColorR = 1.05325e-034
	Actor_245.DisplayDesc.ColorG = 4.57356e-038
	Actor_245.DisplayDesc.ColorB = 6.09609e-023
	Actor_245.DisplayDesc.ColorA = 1.83699e-040
	Actor_245:SetModelState(1)
	Actor_245.PhysicDesc.Pos.X = 522.5
	Actor_245.PhysicDesc.Pos.Y = 7.8125
	Actor_245.PhysicDesc.Pos.Z = 666.5
	Actor_245.PhysicDesc.Pos.Rotation = 180
	Actor_245.PhysicDesc.Density = 6.09987e-023
	Actor_245.PhysicDesc.Collidable = true
	Actor_245.PhysicDesc.SizeX = 7.34701e-040
	Actor_245.PhysicDesc.SizeY = 1.05325e-034
	Actor_245.PhysicDesc.SizeZ = 4.57354e-038
	Actor_245.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_245:SetPhysicalActorType(1)
	Actor_245:SetPhysicalShape(5)
	Actor_245.ExtraInfo.Name = ""
	Actor_245.ExtraInfo.NameColorR = 1.05325e-034
	Actor_245.ExtraInfo.NameColorG = 4.57352e-038
	Actor_245.ExtraInfo.NameColorB = 5.88659e-023
	Actor_245H = ActorHandler(Actor_245)
	environment:AddActorObject(Actor_245H)

	Actor_246 = ActorObjectInfo(246)
	Actor_246:SetRenderType(1)
	Actor_246.DisplayDesc.ModelId = 24707704
	Actor_246.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_82.osgb"
	Actor_246.DisplayDesc.Outfit = ""
	Actor_246.DisplayDesc.Weapon = ""
	Actor_246.DisplayDesc.Mode = ""
	Actor_246.DisplayDesc.UseLight = false
	Actor_246.DisplayDesc.CastShadow = false
	Actor_246.DisplayDesc.ColorR = 1
	Actor_246.DisplayDesc.ColorG = 1
	Actor_246.DisplayDesc.ColorB = 1
	Actor_246.DisplayDesc.ColorA = 1
	Actor_246:SetModelState(1)
	Actor_246.PhysicDesc.Pos.X = 509
	Actor_246.PhysicDesc.Pos.Y = 0.976563
	Actor_246.PhysicDesc.Pos.Z = 621
	Actor_246.PhysicDesc.Pos.Rotation = 0
	Actor_246.PhysicDesc.Density = 6.09291e-023
	Actor_246.PhysicDesc.Collidable = true
	Actor_246.PhysicDesc.SizeX = 0
	Actor_246.PhysicDesc.SizeY = 0
	Actor_246.PhysicDesc.SizeZ = 0
	Actor_246.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_82.phy"
	Actor_246:SetPhysicalActorType(1)
	Actor_246:SetPhysicalShape(5)
	Actor_246.ExtraInfo.Name = ""
	Actor_246.ExtraInfo.NameColorR = 1.05328e-034
	Actor_246.ExtraInfo.NameColorG = 5.90986e-023
	Actor_246.ExtraInfo.NameColorB = 4.57352e-038
	Actor_246H = ActorHandler(Actor_246)
	environment:AddActorObject(Actor_246H)

	Actor_247 = ActorObjectInfo(247)
	Actor_247:SetRenderType(1)
	Actor_247.DisplayDesc.ModelId = 2752550
	Actor_247.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_83.osgb"
	Actor_247.DisplayDesc.Outfit = ""
	Actor_247.DisplayDesc.Weapon = ""
	Actor_247.DisplayDesc.Mode = ""
	Actor_247.DisplayDesc.UseLight = false
	Actor_247.DisplayDesc.CastShadow = false
	Actor_247.DisplayDesc.ColorR = 6.29205e-023
	Actor_247.DisplayDesc.ColorG = 3.65487e-031
	Actor_247.DisplayDesc.ColorB = 1
	Actor_247.DisplayDesc.ColorA = 1
	Actor_247:SetModelState(1)
	Actor_247.PhysicDesc.Pos.X = 509
	Actor_247.PhysicDesc.Pos.Y = 0.976563
	Actor_247.PhysicDesc.Pos.Z = 621
	Actor_247.PhysicDesc.Pos.Rotation = 0
	Actor_247.PhysicDesc.Density = 4.59184e-040
	Actor_247.PhysicDesc.Collidable = true
	Actor_247.PhysicDesc.SizeX = 6.29213e-023
	Actor_247.PhysicDesc.SizeY = 1.53666e+019
	Actor_247.PhysicDesc.SizeZ = 1.45743e+019
	Actor_247.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_83.phy"
	Actor_247:SetPhysicalActorType(1)
	Actor_247:SetPhysicalShape(5)
	Actor_247.ExtraInfo.Name = ""
	Actor_247.ExtraInfo.NameColorR = 4.75219e-034
	Actor_247.ExtraInfo.NameColorG = 8.50983e-039
	Actor_247.ExtraInfo.NameColorB = 0
	Actor_247H = ActorHandler(Actor_247)
	environment:AddActorObject(Actor_247H)

	Actor_248 = ActorObjectInfo(248)
	Actor_248:SetRenderType(1)
	Actor_248.DisplayDesc.ModelId = 2752545
	Actor_248.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_84.osgb"
	Actor_248.DisplayDesc.Outfit = ""
	Actor_248.DisplayDesc.Weapon = ""
	Actor_248.DisplayDesc.Mode = ""
	Actor_248.DisplayDesc.UseLight = false
	Actor_248.DisplayDesc.CastShadow = true
	Actor_248.DisplayDesc.ColorR = 6.28193e-023
	Actor_248.DisplayDesc.ColorG = 6.28193e-023
	Actor_248.DisplayDesc.ColorB = 1
	Actor_248.DisplayDesc.ColorA = 1
	Actor_248:SetModelState(1)
	Actor_248.PhysicDesc.Pos.X = 509
	Actor_248.PhysicDesc.Pos.Y = 0.976563
	Actor_248.PhysicDesc.Pos.Z = 621
	Actor_248.PhysicDesc.Pos.Rotation = 0
	Actor_248.PhysicDesc.Density = 7.61896e+031
	Actor_248.PhysicDesc.Collidable = true
	Actor_248.PhysicDesc.SizeX = 6.2802e-023
	Actor_248.PhysicDesc.SizeY = 0
	Actor_248.PhysicDesc.SizeZ = 2.10195e-044
	Actor_248.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_84.phy"
	Actor_248:SetPhysicalActorType(1)
	Actor_248:SetPhysicalShape(5)
	Actor_248.ExtraInfo.Name = ""
	Actor_248.ExtraInfo.NameColorR = 4.75219e-034
	Actor_248.ExtraInfo.NameColorG = 5.60519e-045
	Actor_248.ExtraInfo.NameColorB = 5.32197e-005
	Actor_248H = ActorHandler(Actor_248)
	environment:AddActorObject(Actor_248H)

	Actor_249 = ActorObjectInfo(249)
	Actor_249:SetRenderType(1)
	Actor_249.DisplayDesc.ModelId = -8388609
	Actor_249.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_85.osgb"
	Actor_249.DisplayDesc.Outfit = ""
	Actor_249.DisplayDesc.Weapon = ""
	Actor_249.DisplayDesc.Mode = ""
	Actor_249.DisplayDesc.UseLight = false
	Actor_249.DisplayDesc.CastShadow = false
	Actor_249.DisplayDesc.ColorR = 1
	Actor_249.DisplayDesc.ColorG = 1
	Actor_249.DisplayDesc.ColorB = 1
	Actor_249.DisplayDesc.ColorA = 1
	Actor_249:SetModelState(1)
	Actor_249.PhysicDesc.Pos.X = 509
	Actor_249.PhysicDesc.Pos.Y = 0.976563
	Actor_249.PhysicDesc.Pos.Z = 621
	Actor_249.PhysicDesc.Pos.Rotation = 0
	Actor_249.PhysicDesc.Density = 0
	Actor_249.PhysicDesc.Collidable = true
	Actor_249.PhysicDesc.SizeX = 0
	Actor_249.PhysicDesc.SizeY = 0
	Actor_249.PhysicDesc.SizeZ = 0
	Actor_249.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_85.phy"
	Actor_249:SetPhysicalActorType(1)
	Actor_249:SetPhysicalShape(5)
	Actor_249.ExtraInfo.Name = ""
	Actor_249.ExtraInfo.NameColorR = 6.30452e-024
	Actor_249.ExtraInfo.NameColorG = 1.83674e-040
	Actor_249.ExtraInfo.NameColorB = 1.05326e-034
	Actor_249H = ActorHandler(Actor_249)
	environment:AddActorObject(Actor_249H)

	Actor_250 = ActorObjectInfo(250)
	Actor_250:SetRenderType(1)
	Actor_250.DisplayDesc.ModelId = 0
	Actor_250.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.osgb"
	Actor_250.DisplayDesc.Outfit = ""
	Actor_250.DisplayDesc.Weapon = ""
	Actor_250.DisplayDesc.Mode = ""
	Actor_250.DisplayDesc.UseLight = false
	Actor_250.DisplayDesc.CastShadow = true
	Actor_250.DisplayDesc.ColorR = 1
	Actor_250.DisplayDesc.ColorG = 2.10195e-044
	Actor_250.DisplayDesc.ColorB = 1.05327e-034
	Actor_250.DisplayDesc.ColorA = 4.63155e+027
	Actor_250:SetModelState(1)
	Actor_250.PhysicDesc.Pos.X = 506.5
	Actor_250.PhysicDesc.Pos.Y = 0.976563
	Actor_250.PhysicDesc.Pos.Z = 615.5
	Actor_250.PhysicDesc.Pos.Rotation = 90
	Actor_250.PhysicDesc.Density = 4.57354e-038
	Actor_250.PhysicDesc.Collidable = true
	Actor_250.PhysicDesc.SizeX = 3.60134e-043
	Actor_250.PhysicDesc.SizeY = 2.10195e-044
	Actor_250.PhysicDesc.SizeZ = 9.18358e-040
	Actor_250.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_42.phy"
	Actor_250:SetPhysicalActorType(1)
	Actor_250:SetPhysicalShape(5)
	Actor_250.ExtraInfo.Name = ""
	Actor_250.ExtraInfo.NameColorR = 1.86126e-031
	Actor_250.ExtraInfo.NameColorG = 1.83674e-040
	Actor_250.ExtraInfo.NameColorB = 0
	Actor_250H = ActorHandler(Actor_250)
	environment:AddActorObject(Actor_250H)

	Actor_251 = ActorObjectInfo(251)
	Actor_251:SetRenderType(1)
	Actor_251.DisplayDesc.ModelId = 131106
	Actor_251.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.osgb"
	Actor_251.DisplayDesc.Outfit = ""
	Actor_251.DisplayDesc.Weapon = ""
	Actor_251.DisplayDesc.Mode = ""
	Actor_251.DisplayDesc.UseLight = false
	Actor_251.DisplayDesc.CastShadow = true
	Actor_251.DisplayDesc.ColorR = 3.6706e-037
	Actor_251.DisplayDesc.ColorG = 9.18358e-040
	Actor_251.DisplayDesc.ColorB = 1.02861e-037
	Actor_251.DisplayDesc.ColorA = 3.67052e-037
	Actor_251:SetModelState(1)
	Actor_251.PhysicDesc.Pos.X = 495
	Actor_251.PhysicDesc.Pos.Y = 6.83594
	Actor_251.PhysicDesc.Pos.Z = 647.5
	Actor_251.PhysicDesc.Pos.Rotation = 90
	Actor_251.PhysicDesc.Density = 1.83685e-040
	Actor_251.PhysicDesc.Collidable = true
	Actor_251.PhysicDesc.SizeX = 4.57354e-038
	Actor_251.PhysicDesc.SizeY = 3.30794e-024
	Actor_251.PhysicDesc.SizeZ = 1.83682e-040
	Actor_251.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_6.phy"
	Actor_251:SetPhysicalActorType(1)
	Actor_251:SetPhysicalShape(5)
	Actor_251.ExtraInfo.Name = ""
	Actor_251.ExtraInfo.NameColorR = 4.57352e-038
	Actor_251.ExtraInfo.NameColorG = 7.16317e-039
	Actor_251.ExtraInfo.NameColorB = 1.02858e-037
	Actor_251H = ActorHandler(Actor_251)
	environment:AddActorObject(Actor_251H)

	Actor_252 = ActorObjectInfo(252)
	Actor_252:SetRenderType(1)
	Actor_252.DisplayDesc.ModelId = 229377904
	Actor_252.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_252.DisplayDesc.Outfit = ""
	Actor_252.DisplayDesc.Weapon = ""
	Actor_252.DisplayDesc.Mode = ""
	Actor_252.DisplayDesc.UseLight = false
	Actor_252.DisplayDesc.CastShadow = true
	Actor_252.DisplayDesc.ColorR = 4.57351e-038
	Actor_252.DisplayDesc.ColorG = 5.32646e-039
	Actor_252.DisplayDesc.ColorB = 2.558e-035
	Actor_252.DisplayDesc.ColorA = -6.25926e+018
	Actor_252:SetModelState(1)
	Actor_252.PhysicDesc.Pos.X = 489.5
	Actor_252.PhysicDesc.Pos.Y = 1.95313
	Actor_252.PhysicDesc.Pos.Z = 636
	Actor_252.PhysicDesc.Pos.Rotation = 90
	Actor_252.PhysicDesc.Density = 3.67345e-040
	Actor_252.PhysicDesc.Collidable = true
	Actor_252.PhysicDesc.SizeX = 3.02069e-034
	Actor_252.PhysicDesc.SizeY = 1.06622e-030
	Actor_252.PhysicDesc.SizeZ = 6.24482e-039
	Actor_252.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_252:SetPhysicalActorType(1)
	Actor_252:SetPhysicalShape(5)
	Actor_252.ExtraInfo.Name = ""
	Actor_252.ExtraInfo.NameColorR = 2.5579e-035
	Actor_252.ExtraInfo.NameColorG = 2.66315e-024
	Actor_252.ExtraInfo.NameColorB = 3.11692e-031
	Actor_252H = ActorHandler(Actor_252)
	environment:AddActorObject(Actor_252H)

	Actor_253 = ActorObjectInfo(253)
	Actor_253:SetRenderType(1)
	Actor_253.DisplayDesc.ModelId = 0
	Actor_253.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.osgb"
	Actor_253.DisplayDesc.Outfit = ""
	Actor_253.DisplayDesc.Weapon = ""
	Actor_253.DisplayDesc.Mode = ""
	Actor_253.DisplayDesc.UseLight = false
	Actor_253.DisplayDesc.CastShadow = false
	Actor_253.DisplayDesc.ColorR = 1
	Actor_253.DisplayDesc.ColorG = 1.10916e-023
	Actor_253.DisplayDesc.ColorB = -0.679688
	Actor_253.DisplayDesc.ColorA = 1.349609
	Actor_253:SetModelState(1)
	Actor_253.PhysicDesc.Pos.X = 492.5
	Actor_253.PhysicDesc.Pos.Y = 1.95313
	Actor_253.PhysicDesc.Pos.Z = 613.5
	Actor_253.PhysicDesc.Pos.Rotation = -90
	Actor_253.PhysicDesc.Density = 2.8026e-045
	Actor_253.PhysicDesc.Collidable = true
	Actor_253.PhysicDesc.SizeX = 0
	Actor_253.PhysicDesc.SizeY = 4.22074e-034
	Actor_253.PhysicDesc.SizeZ = 0
	Actor_253.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_5.phy"
	Actor_253:SetPhysicalActorType(1)
	Actor_253:SetPhysicalShape(5)
	Actor_253.ExtraInfo.Name = ""
	Actor_253.ExtraInfo.NameColorR = 0
	Actor_253.ExtraInfo.NameColorG = 0
	Actor_253.ExtraInfo.NameColorB = 0.460938
	Actor_253H = ActorHandler(Actor_253)
	environment:AddActorObject(Actor_253H)

	Actor_254 = ActorObjectInfo(254)
	Actor_254:SetRenderType(1)
	Actor_254.DisplayDesc.ModelId = 24707496
	Actor_254.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.osgb"
	Actor_254.DisplayDesc.Outfit = ""
	Actor_254.DisplayDesc.Weapon = ""
	Actor_254.DisplayDesc.Mode = ""
	Actor_254.DisplayDesc.UseLight = false
	Actor_254.DisplayDesc.CastShadow = false
	Actor_254.DisplayDesc.ColorR = 3.40282e+038
	Actor_254.DisplayDesc.ColorG = 3.40282e+038
	Actor_254.DisplayDesc.ColorB = 3.40282e+038
	Actor_254.DisplayDesc.ColorA = -3.40282e+038
	Actor_254:SetModelState(1)
	Actor_254.PhysicDesc.Pos.X = 511.125
	Actor_254.PhysicDesc.Pos.Y = 0.976563
	Actor_254.PhysicDesc.Pos.Z = 613
	Actor_254.PhysicDesc.Pos.Rotation = 90
	Actor_254.PhysicDesc.Density = 0.822354
	Actor_254.PhysicDesc.Collidable = true
	Actor_254.PhysicDesc.SizeX = 0
	Actor_254.PhysicDesc.SizeY = 0
	Actor_254.PhysicDesc.SizeZ = 0
	Actor_254.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_53.phy"
	Actor_254:SetPhysicalActorType(1)
	Actor_254:SetPhysicalShape(5)
	Actor_254.ExtraInfo.Name = ""
	Actor_254.ExtraInfo.NameColorR = 3.01824e-023
	Actor_254.ExtraInfo.NameColorG = 1.83674e-040
	Actor_254.ExtraInfo.NameColorB = 1.05325e-034
	Actor_254H = ActorHandler(Actor_254)
	environment:AddActorObject(Actor_254H)

	Actor_255 = ActorObjectInfo(255)
	Actor_255:SetRenderType(1)
	Actor_255.DisplayDesc.ModelId = 1337357312
	Actor_255.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_255.DisplayDesc.Outfit = ""
	Actor_255.DisplayDesc.Weapon = ""
	Actor_255.DisplayDesc.Mode = ""
	Actor_255.DisplayDesc.UseLight = false
	Actor_255.DisplayDesc.CastShadow = true
	Actor_255.DisplayDesc.ColorR = 4.57351e-038
	Actor_255.DisplayDesc.ColorG = 5.51035e-040
	Actor_255.DisplayDesc.ColorB = 1.05328e-034
	Actor_255.DisplayDesc.ColorA = 1.31224e-038
	Actor_255:SetModelState(1)
	Actor_255.PhysicDesc.Pos.X = 514.5
	Actor_255.PhysicDesc.Pos.Y = 0.976563
	Actor_255.PhysicDesc.Pos.Z = 614.25
	Actor_255.PhysicDesc.Pos.Rotation = 0
	Actor_255.PhysicDesc.Density = 0
	Actor_255.PhysicDesc.Collidable = true
	Actor_255.PhysicDesc.SizeX = 7.00649e-045
	Actor_255.PhysicDesc.SizeY = 0
	Actor_255.PhysicDesc.SizeZ = 5.60519e-045
	Actor_255.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_255:SetPhysicalActorType(1)
	Actor_255:SetPhysicalShape(5)
	Actor_255.ExtraInfo.Name = ""
	Actor_255.ExtraInfo.NameColorR = 4.57351e-038
	Actor_255.ExtraInfo.NameColorG = 2.38773e-039
	Actor_255.ExtraInfo.NameColorB = 1.05325e-034
	Actor_255H = ActorHandler(Actor_255)
	environment:AddActorObject(Actor_255H)

	Actor_256 = ActorObjectInfo(256)
	Actor_256:SetRenderType(1)
	Actor_256.DisplayDesc.ModelId = 1066795008
	Actor_256.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.osgb"
	Actor_256.DisplayDesc.Outfit = ""
	Actor_256.DisplayDesc.Weapon = ""
	Actor_256.DisplayDesc.Mode = ""
	Actor_256.DisplayDesc.UseLight = false
	Actor_256.DisplayDesc.CastShadow = true
	Actor_256.DisplayDesc.ColorR = 3.47479e-024
	Actor_256.DisplayDesc.ColorG = 9.56017e-034
	Actor_256.DisplayDesc.ColorB = 5.98861e-038
	Actor_256.DisplayDesc.ColorA = 4.22068e-034
	Actor_256:SetModelState(1)
	Actor_256.PhysicDesc.Pos.X = 499.75
	Actor_256.PhysicDesc.Pos.Y = 1.10156
	Actor_256.PhysicDesc.Pos.Z = 610.75
	Actor_256.PhysicDesc.Pos.Rotation = 180
	Actor_256.PhysicDesc.Density = 3.42285e-008
	Actor_256.PhysicDesc.Collidable = true
	Actor_256.PhysicDesc.SizeX = -1
	Actor_256.PhysicDesc.SizeY = 0
	Actor_256.PhysicDesc.SizeZ = 1
	Actor_256.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_8.phy"
	Actor_256:SetPhysicalActorType(1)
	Actor_256:SetPhysicalShape(5)
	Actor_256.ExtraInfo.Name = ""
	Actor_256.ExtraInfo.NameColorR = 4.22068e-034
	Actor_256.ExtraInfo.NameColorG = 3.43966e-024
	Actor_256.ExtraInfo.NameColorB = 3.32115e-024
	Actor_256H = ActorHandler(Actor_256)
	environment:AddActorObject(Actor_256H)

	Actor_257 = ActorObjectInfo(257)
	Actor_257:SetRenderType(1)
	Actor_257.DisplayDesc.ModelId = 0
	Actor_257.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_257.DisplayDesc.Outfit = ""
	Actor_257.DisplayDesc.Weapon = ""
	Actor_257.DisplayDesc.Mode = ""
	Actor_257.DisplayDesc.UseLight = false
	Actor_257.DisplayDesc.CastShadow = true
	Actor_257.DisplayDesc.ColorR = 4.57351e-038
	Actor_257.DisplayDesc.ColorG = 5.51035e-040
	Actor_257.DisplayDesc.ColorB = 1.0533e-034
	Actor_257.DisplayDesc.ColorA = 1.31224e-038
	Actor_257:SetModelState(1)
	Actor_257.PhysicDesc.Pos.X = 529.742
	Actor_257.PhysicDesc.Pos.Y = 0.976563
	Actor_257.PhysicDesc.Pos.Z = 608.125
	Actor_257.PhysicDesc.Pos.Rotation = -90
	Actor_257.PhysicDesc.Density = 0
	Actor_257.PhysicDesc.Collidable = true
	Actor_257.PhysicDesc.SizeX = 7.00649e-045
	Actor_257.PhysicDesc.SizeY = 0
	Actor_257.PhysicDesc.SizeZ = 5.60519e-045
	Actor_257.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_257:SetPhysicalActorType(1)
	Actor_257:SetPhysicalShape(5)
	Actor_257.ExtraInfo.Name = ""
	Actor_257.ExtraInfo.NameColorR = 4.57351e-038
	Actor_257.ExtraInfo.NameColorG = 2.38773e-039
	Actor_257.ExtraInfo.NameColorB = 1.05327e-034
	Actor_257H = ActorHandler(Actor_257)
	environment:AddActorObject(Actor_257H)

	Actor_258 = ActorObjectInfo(258)
	Actor_258:SetRenderType(1)
	Actor_258.DisplayDesc.ModelId = 0
	Actor_258.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_258.DisplayDesc.Outfit = ""
	Actor_258.DisplayDesc.Weapon = ""
	Actor_258.DisplayDesc.Mode = ""
	Actor_258.DisplayDesc.UseLight = false
	Actor_258.DisplayDesc.CastShadow = false
	Actor_258.DisplayDesc.ColorR = 1.4013e-045
	Actor_258.DisplayDesc.ColorG = 1
	Actor_258.DisplayDesc.ColorB = 1
	Actor_258.DisplayDesc.ColorA = 1.4013e-045
	Actor_258:SetModelState(1)
	Actor_258.PhysicDesc.Pos.X = 527.797
	Actor_258.PhysicDesc.Pos.Y = 0.976563
	Actor_258.PhysicDesc.Pos.Z = 608.125
	Actor_258.PhysicDesc.Pos.Rotation = -90
	Actor_258.PhysicDesc.Density = 0
	Actor_258.PhysicDesc.Collidable = true
	Actor_258.PhysicDesc.SizeX = 0
	Actor_258.PhysicDesc.SizeY = 0
	Actor_258.PhysicDesc.SizeZ = 0
	Actor_258.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_258:SetPhysicalActorType(1)
	Actor_258:SetPhysicalShape(5)
	Actor_258.ExtraInfo.Name = ""
	Actor_258.ExtraInfo.NameColorR = 0
	Actor_258.ExtraInfo.NameColorG = 0
	Actor_258.ExtraInfo.NameColorB = 0
	Actor_258H = ActorHandler(Actor_258)
	environment:AddActorObject(Actor_258H)

	Actor_259 = ActorObjectInfo(259)
	Actor_259:SetRenderType(1)
	Actor_259.DisplayDesc.ModelId = 423430000
	Actor_259.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_259.DisplayDesc.Outfit = ""
	Actor_259.DisplayDesc.Weapon = ""
	Actor_259.DisplayDesc.Mode = ""
	Actor_259.DisplayDesc.UseLight = false
	Actor_259.DisplayDesc.CastShadow = false
	Actor_259.DisplayDesc.ColorR = 1.4013e-045
	Actor_259.DisplayDesc.ColorG = 7.24764e-023
	Actor_259.DisplayDesc.ColorB = 2.10195e-044
	Actor_259.DisplayDesc.ColorA = 4.21265e-023
	Actor_259:SetModelState(1)
	Actor_259.PhysicDesc.Pos.X = 525.852
	Actor_259.PhysicDesc.Pos.Y = 0.976563
	Actor_259.PhysicDesc.Pos.Z = 608.125
	Actor_259.PhysicDesc.Pos.Rotation = -90
	Actor_259.PhysicDesc.Density = 0
	Actor_259.PhysicDesc.Collidable = true
	Actor_259.PhysicDesc.SizeX = 0
	Actor_259.PhysicDesc.SizeY = 2.8026e-045
	Actor_259.PhysicDesc.SizeZ = 7.24764e-023
	Actor_259.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_259:SetPhysicalActorType(1)
	Actor_259:SetPhysicalShape(5)
	Actor_259.ExtraInfo.Name = ""
	Actor_259.ExtraInfo.NameColorR = 2.8026e-045
	Actor_259.ExtraInfo.NameColorG = 7.24764e-023
	Actor_259.ExtraInfo.NameColorB = 0
	Actor_259H = ActorHandler(Actor_259)
	environment:AddActorObject(Actor_259H)

	Actor_260 = ActorObjectInfo(260)
	Actor_260:SetRenderType(1)
	Actor_260.DisplayDesc.ModelId = 423430000
	Actor_260.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_260.DisplayDesc.Outfit = ""
	Actor_260.DisplayDesc.Weapon = ""
	Actor_260.DisplayDesc.Mode = ""
	Actor_260.DisplayDesc.UseLight = false
	Actor_260.DisplayDesc.CastShadow = false
	Actor_260.DisplayDesc.ColorR = 1.4013e-045
	Actor_260.DisplayDesc.ColorG = 1.88402e-031
	Actor_260.DisplayDesc.ColorB = 3.28882
	Actor_260.DisplayDesc.ColorA = 4.21265e-023
	Actor_260:SetModelState(1)
	Actor_260.PhysicDesc.Pos.X = 523.906
	Actor_260.PhysicDesc.Pos.Y = 0.976563
	Actor_260.PhysicDesc.Pos.Z = 608.125
	Actor_260.PhysicDesc.Pos.Rotation = -90
	Actor_260.PhysicDesc.Density = 0
	Actor_260.PhysicDesc.Collidable = true
	Actor_260.PhysicDesc.SizeX = 0
	Actor_260.PhysicDesc.SizeY = 2.8026e-045
	Actor_260.PhysicDesc.SizeZ = 1.88402e-031
	Actor_260.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_260:SetPhysicalActorType(1)
	Actor_260:SetPhysicalShape(5)
	Actor_260.ExtraInfo.Name = ""
	Actor_260.ExtraInfo.NameColorR = 2.8026e-045
	Actor_260.ExtraInfo.NameColorG = 1.88402e-031
	Actor_260.ExtraInfo.NameColorB = 0.598389
	Actor_260H = ActorHandler(Actor_260)
	environment:AddActorObject(Actor_260H)

	Actor_261 = ActorObjectInfo(261)
	Actor_261:SetRenderType(1)
	Actor_261.DisplayDesc.ModelId = 423430000
	Actor_261.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_261.DisplayDesc.Outfit = ""
	Actor_261.DisplayDesc.Weapon = ""
	Actor_261.DisplayDesc.Mode = ""
	Actor_261.DisplayDesc.UseLight = false
	Actor_261.DisplayDesc.CastShadow = false
	Actor_261.DisplayDesc.ColorR = 1.4013e-045
	Actor_261.DisplayDesc.ColorG = 1.88343e-031
	Actor_261.DisplayDesc.ColorB = 2.10195e-044
	Actor_261.DisplayDesc.ColorA = 4.21265e-023
	Actor_261:SetModelState(1)
	Actor_261.PhysicDesc.Pos.X = 521.961
	Actor_261.PhysicDesc.Pos.Y = 0.976563
	Actor_261.PhysicDesc.Pos.Z = 608.125
	Actor_261.PhysicDesc.Pos.Rotation = -90
	Actor_261.PhysicDesc.Density = 0
	Actor_261.PhysicDesc.Collidable = true
	Actor_261.PhysicDesc.SizeX = 0
	Actor_261.PhysicDesc.SizeY = 2.8026e-045
	Actor_261.PhysicDesc.SizeZ = 1.88343e-031
	Actor_261.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_261:SetPhysicalActorType(1)
	Actor_261:SetPhysicalShape(5)
	Actor_261.ExtraInfo.Name = ""
	Actor_261.ExtraInfo.NameColorR = 2.8026e-045
	Actor_261.ExtraInfo.NameColorG = 1.88343e-031
	Actor_261.ExtraInfo.NameColorB = 0
	Actor_261H = ActorHandler(Actor_261)
	environment:AddActorObject(Actor_261H)

	Actor_262 = ActorObjectInfo(262)
	Actor_262:SetRenderType(1)
	Actor_262.DisplayDesc.ModelId = 423430000
	Actor_262.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_262.DisplayDesc.Outfit = ""
	Actor_262.DisplayDesc.Weapon = ""
	Actor_262.DisplayDesc.Mode = ""
	Actor_262.DisplayDesc.UseLight = false
	Actor_262.DisplayDesc.CastShadow = false
	Actor_262.DisplayDesc.ColorR = 1.4013e-045
	Actor_262.DisplayDesc.ColorG = 1.88313e-031
	Actor_262.DisplayDesc.ColorB = 1
	Actor_262.DisplayDesc.ColorA = 4.21265e-023
	Actor_262:SetModelState(1)
	Actor_262.PhysicDesc.Pos.X = 520.016
	Actor_262.PhysicDesc.Pos.Y = 0.976563
	Actor_262.PhysicDesc.Pos.Z = 608.125
	Actor_262.PhysicDesc.Pos.Rotation = -90
	Actor_262.PhysicDesc.Density = 0
	Actor_262.PhysicDesc.Collidable = true
	Actor_262.PhysicDesc.SizeX = 0
	Actor_262.PhysicDesc.SizeY = 2.8026e-045
	Actor_262.PhysicDesc.SizeZ = 1.88313e-031
	Actor_262.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_262:SetPhysicalActorType(1)
	Actor_262:SetPhysicalShape(5)
	Actor_262.ExtraInfo.Name = ""
	Actor_262.ExtraInfo.NameColorR = 2.8026e-045
	Actor_262.ExtraInfo.NameColorG = 1.88313e-031
	Actor_262.ExtraInfo.NameColorB = 0
	Actor_262H = ActorHandler(Actor_262)
	environment:AddActorObject(Actor_262H)

	Actor_263 = ActorObjectInfo(263)
	Actor_263:SetRenderType(1)
	Actor_263.DisplayDesc.ModelId = 423430000
	Actor_263.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_55.osgb"
	Actor_263.DisplayDesc.Outfit = ""
	Actor_263.DisplayDesc.Weapon = ""
	Actor_263.DisplayDesc.Mode = ""
	Actor_263.DisplayDesc.UseLight = false
	Actor_263.DisplayDesc.CastShadow = false
	Actor_263.DisplayDesc.ColorR = 1.4013e-045
	Actor_263.DisplayDesc.ColorG = 1.8838e-031
	Actor_263.DisplayDesc.ColorB = 1
	Actor_263.DisplayDesc.ColorA = 4.21265e-023
	Actor_263:SetModelState(1)
	Actor_263.PhysicDesc.Pos.X = 531.57
	Actor_263.PhysicDesc.Pos.Y = 0.976563
	Actor_263.PhysicDesc.Pos.Z = 608.125
	Actor_263.PhysicDesc.Pos.Rotation = 90
	Actor_263.PhysicDesc.Density = 3.6232e-041
	Actor_263.PhysicDesc.Collidable = true
	Actor_263.PhysicDesc.SizeX = 0
	Actor_263.PhysicDesc.SizeY = 2.8026e-045
	Actor_263.PhysicDesc.SizeZ = 1.8838e-031
	Actor_263.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_55.phy"
	Actor_263:SetPhysicalActorType(1)
	Actor_263:SetPhysicalShape(5)
	Actor_263.ExtraInfo.Name = ""
	Actor_263.ExtraInfo.NameColorR = 2.8026e-045
	Actor_263.ExtraInfo.NameColorG = 1.8838e-031
	Actor_263.ExtraInfo.NameColorB = 6.08654e-023
	Actor_263H = ActorHandler(Actor_263)
	environment:AddActorObject(Actor_263H)

	Actor_264 = ActorObjectInfo(264)
	Actor_264:SetRenderType(1)
	Actor_264.DisplayDesc.ModelId = 441169424
	Actor_264.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_264.DisplayDesc.Outfit = ""
	Actor_264.DisplayDesc.Weapon = ""
	Actor_264.DisplayDesc.Mode = ""
	Actor_264.DisplayDesc.UseLight = false
	Actor_264.DisplayDesc.CastShadow = true
	Actor_264.DisplayDesc.ColorR = 2.00001
	Actor_264.DisplayDesc.ColorG = 1.00626e-038
	Actor_264.DisplayDesc.ColorB = 4.21265e-023
	Actor_264.DisplayDesc.ColorA = 1
	Actor_264:SetModelState(1)
	Actor_264.PhysicDesc.Pos.X = 519.906
	Actor_264.PhysicDesc.Pos.Y = 0.976563
	Actor_264.PhysicDesc.Pos.Z = 610.07
	Actor_264.PhysicDesc.Pos.Rotation = 0
	Actor_264.PhysicDesc.Density = 6.72623e-044
	Actor_264.PhysicDesc.Collidable = true
	Actor_264.PhysicDesc.SizeX = 1.72297e-023
	Actor_264.PhysicDesc.SizeY = 1.03204e-038
	Actor_264.PhysicDesc.SizeZ = 1.00626e-038
	Actor_264.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_264:SetPhysicalActorType(1)
	Actor_264:SetPhysicalShape(5)
	Actor_264.ExtraInfo.Name = ""
	Actor_264.ExtraInfo.NameColorR = 1.08334e-034
	Actor_264.ExtraInfo.NameColorG = 1.00626e-038
	Actor_264.ExtraInfo.NameColorB = 4.22058e-023
	Actor_264H = ActorHandler(Actor_264)
	environment:AddActorObject(Actor_264H)

	Actor_265 = ActorObjectInfo(265)
	Actor_265:SetRenderType(1)
	Actor_265.DisplayDesc.ModelId = 423430000
	Actor_265.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_265.DisplayDesc.Outfit = ""
	Actor_265.DisplayDesc.Weapon = ""
	Actor_265.DisplayDesc.Mode = ""
	Actor_265.DisplayDesc.UseLight = false
	Actor_265.DisplayDesc.CastShadow = false
	Actor_265.DisplayDesc.ColorR = 1.4013e-045
	Actor_265.DisplayDesc.ColorG = 1.8821e-031
	Actor_265.DisplayDesc.ColorB = 2.10195e-044
	Actor_265.DisplayDesc.ColorA = 4.21265e-023
	Actor_265:SetModelState(1)
	Actor_265.PhysicDesc.Pos.X = 519.906
	Actor_265.PhysicDesc.Pos.Y = 0.976563
	Actor_265.PhysicDesc.Pos.Z = 612.016
	Actor_265.PhysicDesc.Pos.Rotation = 0
	Actor_265.PhysicDesc.Density = 9.12807e-024
	Actor_265.PhysicDesc.Collidable = true
	Actor_265.PhysicDesc.SizeX = 0
	Actor_265.PhysicDesc.SizeY = 2.8026e-045
	Actor_265.PhysicDesc.SizeZ = 1.8821e-031
	Actor_265.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_265:SetPhysicalActorType(1)
	Actor_265:SetPhysicalShape(5)
	Actor_265.ExtraInfo.Name = ""
	Actor_265.ExtraInfo.NameColorR = 2.8026e-045
	Actor_265.ExtraInfo.NameColorG = 1.8821e-031
	Actor_265.ExtraInfo.NameColorB = 0
	Actor_265H = ActorHandler(Actor_265)
	environment:AddActorObject(Actor_265H)

	Actor_266 = ActorObjectInfo(266)
	Actor_266:SetRenderType(1)
	Actor_266.DisplayDesc.ModelId = 441169424
	Actor_266.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_266.DisplayDesc.Outfit = ""
	Actor_266.DisplayDesc.Weapon = ""
	Actor_266.DisplayDesc.Mode = ""
	Actor_266.DisplayDesc.UseLight = false
	Actor_266.DisplayDesc.CastShadow = true
	Actor_266.DisplayDesc.ColorR = 1.01419e-038
	Actor_266.DisplayDesc.ColorG = 1.00626e-038
	Actor_266.DisplayDesc.ColorB = 4.21265e-023
	Actor_266.DisplayDesc.ColorA = 1
	Actor_266:SetModelState(1)
	Actor_266.PhysicDesc.Pos.X = 519.906
	Actor_266.PhysicDesc.Pos.Y = 0.976563
	Actor_266.PhysicDesc.Pos.Z = 613.961
	Actor_266.PhysicDesc.Pos.Rotation = 0
	Actor_266.PhysicDesc.Density = 6.72623e-044
	Actor_266.PhysicDesc.Collidable = true
	Actor_266.PhysicDesc.SizeX = 5.59059e-024
	Actor_266.PhysicDesc.SizeY = 1.76175e-031
	Actor_266.PhysicDesc.SizeZ = 1.00626e-038
	Actor_266.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_266:SetPhysicalActorType(1)
	Actor_266:SetPhysicalShape(5)
	Actor_266.ExtraInfo.Name = ""
	Actor_266.ExtraInfo.NameColorR = 1.02319e-034
	Actor_266.ExtraInfo.NameColorG = 1.00626e-038
	Actor_266.ExtraInfo.NameColorB = 4.22058e-023
	Actor_266H = ActorHandler(Actor_266)
	environment:AddActorObject(Actor_266H)

	Actor_267 = ActorObjectInfo(267)
	Actor_267:SetRenderType(1)
	Actor_267.DisplayDesc.ModelId = 1065353216
	Actor_267.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_267.DisplayDesc.Outfit = ""
	Actor_267.DisplayDesc.Weapon = ""
	Actor_267.DisplayDesc.Mode = ""
	Actor_267.DisplayDesc.UseLight = false
	Actor_267.DisplayDesc.CastShadow = false
	Actor_267.DisplayDesc.ColorR = 1
	Actor_267.DisplayDesc.ColorG = 1
	Actor_267.DisplayDesc.ColorB = 1
	Actor_267.DisplayDesc.ColorA = 1
	Actor_267:SetModelState(1)
	Actor_267.PhysicDesc.Pos.X = 519.898
	Actor_267.PhysicDesc.Pos.Y = 0.976563
	Actor_267.PhysicDesc.Pos.Z = 615.906
	Actor_267.PhysicDesc.Pos.Rotation = 0
	Actor_267.PhysicDesc.Density = 1
	Actor_267.PhysicDesc.Collidable = true
	Actor_267.PhysicDesc.SizeX = 0
	Actor_267.PhysicDesc.SizeY = 1
	Actor_267.PhysicDesc.SizeZ = 0
	Actor_267.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_267:SetPhysicalActorType(1)
	Actor_267:SetPhysicalShape(5)
	Actor_267.ExtraInfo.Name = ""
	Actor_267.ExtraInfo.NameColorR = 0
	Actor_267.ExtraInfo.NameColorG = 1
	Actor_267.ExtraInfo.NameColorB = 0
	Actor_267H = ActorHandler(Actor_267)
	environment:AddActorObject(Actor_267H)

	Actor_268 = ActorObjectInfo(268)
	Actor_268:SetRenderType(1)
	Actor_268.DisplayDesc.ModelId = 0
	Actor_268.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_268.DisplayDesc.Outfit = ""
	Actor_268.DisplayDesc.Weapon = ""
	Actor_268.DisplayDesc.Mode = ""
	Actor_268.DisplayDesc.UseLight = false
	Actor_268.DisplayDesc.CastShadow = false
	Actor_268.DisplayDesc.ColorR = 4.34403e-044
	Actor_268.DisplayDesc.ColorG = 1
	Actor_268.DisplayDesc.ColorB = 2.10195e-044
	Actor_268.DisplayDesc.ColorA = 1.96182e-044
	Actor_268:SetModelState(1)
	Actor_268.PhysicDesc.Pos.X = 521.844
	Actor_268.PhysicDesc.Pos.Y = 0.976563
	Actor_268.PhysicDesc.Pos.Z = 616.016
	Actor_268.PhysicDesc.Pos.Rotation = 90
	Actor_268.PhysicDesc.Density = 1.30623e-038
	Actor_268.PhysicDesc.Collidable = true
	Actor_268.PhysicDesc.SizeX = 2.38221e-044
	Actor_268.PhysicDesc.SizeY = 2.66247e-044
	Actor_268.PhysicDesc.SizeZ = 0
	Actor_268.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_268:SetPhysicalActorType(1)
	Actor_268:SetPhysicalShape(5)
	Actor_268.ExtraInfo.Name = ""
	Actor_268.ExtraInfo.NameColorR = 1.02318e-034
	Actor_268.ExtraInfo.NameColorG = 0
	Actor_268.ExtraInfo.NameColorB = 0
	Actor_268H = ActorHandler(Actor_268)
	environment:AddActorObject(Actor_268H)

	Actor_269 = ActorObjectInfo(269)
	Actor_269:SetRenderType(1)
	Actor_269.DisplayDesc.ModelId = 0
	Actor_269.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.osgb"
	Actor_269.DisplayDesc.Outfit = ""
	Actor_269.DisplayDesc.Weapon = ""
	Actor_269.DisplayDesc.Mode = ""
	Actor_269.DisplayDesc.UseLight = false
	Actor_269.DisplayDesc.CastShadow = false
	Actor_269.DisplayDesc.ColorR = 2.11621
	Actor_269.DisplayDesc.ColorG = 1
	Actor_269.DisplayDesc.ColorB = 4.0376
	Actor_269.DisplayDesc.ColorA = 1
	Actor_269:SetModelState(1)
	Actor_269.PhysicDesc.Pos.X = 523.789
	Actor_269.PhysicDesc.Pos.Y = 0.976563
	Actor_269.PhysicDesc.Pos.Z = 616.016
	Actor_269.PhysicDesc.Pos.Rotation = 90
	Actor_269.PhysicDesc.Density = 0
	Actor_269.PhysicDesc.Collidable = true
	Actor_269.PhysicDesc.SizeX = 0
	Actor_269.PhysicDesc.SizeY = 0
	Actor_269.PhysicDesc.SizeZ = 0
	Actor_269.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_54.phy"
	Actor_269:SetPhysicalActorType(1)
	Actor_269:SetPhysicalShape(5)
	Actor_269.ExtraInfo.Name = ""
	Actor_269.ExtraInfo.NameColorR = 1.02316e-034
	Actor_269.ExtraInfo.NameColorG = 1.65714e-023
	Actor_269.ExtraInfo.NameColorB = 1.7659e-023
	Actor_269H = ActorHandler(Actor_269)
	environment:AddActorObject(Actor_269H)

	Actor_270 = ActorObjectInfo(270)
	Actor_270:SetRenderType(1)
	Actor_270.DisplayDesc.ModelId = 512
	Actor_270.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.osgb"
	Actor_270.DisplayDesc.Outfit = ""
	Actor_270.DisplayDesc.Weapon = ""
	Actor_270.DisplayDesc.Mode = ""
	Actor_270.DisplayDesc.UseLight = false
	Actor_270.DisplayDesc.CastShadow = true
	Actor_270.DisplayDesc.ColorR = 1.65627e-023
	Actor_270.DisplayDesc.ColorG = 3.67345e-040
	Actor_270.DisplayDesc.ColorB = 1.05328e-034
	Actor_270.DisplayDesc.ColorA = 1.71707e-023
	Actor_270:SetModelState(1)
	Actor_270.PhysicDesc.Pos.X = 522.25
	Actor_270.PhysicDesc.Pos.Y = 0.976563
	Actor_270.PhysicDesc.Pos.Z = 613.25
	Actor_270.PhysicDesc.Pos.Rotation = 0
	Actor_270.PhysicDesc.Density = 1.83691e-040
	Actor_270.PhysicDesc.Collidable = true
	Actor_270.PhysicDesc.SizeX = 1.31224e-038
	Actor_270.PhysicDesc.SizeY = 0
	Actor_270.PhysicDesc.SizeZ = 0
	Actor_270.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_1.phy"
	Actor_270:SetPhysicalActorType(1)
	Actor_270:SetPhysicalShape(5)
	Actor_270.ExtraInfo.Name = ""
	Actor_270.ExtraInfo.NameColorR = 1.09021e-042
	Actor_270.ExtraInfo.NameColorG = 1.09161e-042
	Actor_270.ExtraInfo.NameColorB = 0
	Actor_270H = ActorHandler(Actor_270)
	environment:AddActorObject(Actor_270H)

	Actor_271 = ActorObjectInfo(271)
	Actor_271:SetRenderType(1)
	Actor_271.DisplayDesc.ModelId = 0
	Actor_271.DisplayDesc.ModelName = "Worlds/Lba2Original/Models/CITADEL_OBJ_86.osgb"
	Actor_271.DisplayDesc.Outfit = ""
	Actor_271.DisplayDesc.Weapon = ""
	Actor_271.DisplayDesc.Mode = ""
	Actor_271.DisplayDesc.UseLight = false
	Actor_271.DisplayDesc.CastShadow = true
	Actor_271.DisplayDesc.ColorR = -5.08443e+037
	Actor_271.DisplayDesc.ColorG = 3.6737e-040
	Actor_271.DisplayDesc.ColorB = 1.05326e-034
	Actor_271.DisplayDesc.ColorA = 4.57356e-038
	Actor_271:SetModelState(1)
	Actor_271.PhysicDesc.Pos.X = 512.125
	Actor_271.PhysicDesc.Pos.Y = 0.976563
	Actor_271.PhysicDesc.Pos.Z = 622.75
	Actor_271.PhysicDesc.Pos.Rotation = 0
	Actor_271.PhysicDesc.Density = 1.83688e-040
	Actor_271.PhysicDesc.Collidable = true
	Actor_271.PhysicDesc.SizeX = 4.57354e-038
	Actor_271.PhysicDesc.SizeY = 2.35401e-023
	Actor_271.PhysicDesc.SizeZ = 2.03949e-023
	Actor_271.PhysicDesc.Filename = "Worlds/Lba2Original/Models/CITADEL_OBJ_86.phy"
	Actor_271:SetPhysicalActorType(1)
	Actor_271:SetPhysicalShape(5)
	Actor_271.ExtraInfo.Name = ""
	Actor_271.ExtraInfo.NameColorR = 0.00527966
	Actor_271.ExtraInfo.NameColorG = 2.38773e-039
	Actor_271.ExtraInfo.NameColorB = 1.05329e-034
	Actor_271H = ActorHandler(Actor_271)
	environment:AddActorObject(Actor_271H)

	Trigger_1_info = TriggerInfo(1, "to_twinsenH", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 6, 2, true)
	Trigger_1:SetPosition(515.4, 1, 618.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map001_2")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "to_architect", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 6, 2, true)
	Trigger_2:SetPosition(533, 1, 613.25)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map010_2")
	Trigger_2_act1:SetSpawning(0)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "to_ticket", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 6, 1, true)
	Trigger_3:SetPosition(465, 3, 560.7)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map009_2")
	Trigger_3_act1:SetSpawning(0)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "tp_cita_mrpaul", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 2, 6, 1, true)
	Trigger_4:SetPosition(453, 3, 561)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map008_2")
	Trigger_4_act1:SetSpawning(0)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "to_shop", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 6, 2, true)
	Trigger_5:SetPosition(491.5, 1, 573.3)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map015_2")
	Trigger_5_act1:SetSpawning(0)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "to_tave", true, true, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 2, 6, 1, true)
	Trigger_6:SetPosition(515, 1, 557.8)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map004_2")
	Trigger_6_act1:SetSpawning(0)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "to_muse", true, true, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 1, 6, 2, true)
	Trigger_7:SetPosition(492.5, 1, 538.1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map016_2")
	Trigger_7_act1:SetSpawning(0)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_10_info = TriggerInfo(10, "to_pharmacy3", true, true, false)
	Trigger_10 = ZoneTrigger(Trigger_10_info, 1, 6, 2, true)
	Trigger_10:SetPosition(500.6, 1, 515.05)
	Trigger_10_act1 = TeleportAction()
	Trigger_10_act1:SetMapName("Map023_2")
	Trigger_10_act1:SetSpawning(1)
	Trigger_10:SetAction1(Trigger_10_act1)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "to_bag", true, true, false)
	Trigger_11 = ZoneTrigger(Trigger_11_info, 1, 6, 2, true)
	Trigger_11:SetPosition(502.5, 1, 509.65)
	Trigger_11_act1 = TeleportAction()
	Trigger_11_act1:SetMapName("Map006_2")
	Trigger_11_act1:SetSpawning(1)
	Trigger_11:SetAction1(Trigger_11_act1)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "to_school", true, true, false)
	Trigger_12 = ZoneTrigger(Trigger_12_info, 2, 6, 1, true)
	Trigger_12:SetPosition(533.8, 1, 500)
	Trigger_12_act1 = TeleportAction()
	Trigger_12_act1:SetMapName("Map038_2")
	Trigger_12_act1:SetSpawning(1)
	Trigger_12:SetAction1(Trigger_12_act1)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "to_magician", true, true, false)
	Trigger_13 = ZoneTrigger(Trigger_13_info, 1, 7, 3, true)
	Trigger_13:SetPosition(449.5, 32, 446.5)
	Trigger_13_act1 = TeleportAction()
	Trigger_13_act1:SetMapName("Map022_2")
	Trigger_13_act1:SetSpawning(1)
	Trigger_13:SetAction1(Trigger_13_act1)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "to_spider", true, true, false)
	Trigger_14 = ZoneTrigger(Trigger_14_info, 2, 8, 1, true)
	Trigger_14:SetPosition(540.4, 28.4, 451.6)
	Trigger_14_act1 = TeleportAction()
	Trigger_14_act1:SetMapName("Map043_2")
	Trigger_14_act1:SetSpawning(1)
	Trigger_14:SetAction1(Trigger_14_act1)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "to_spidersecond", true, true, false)
	Trigger_15 = ZoneTrigger(Trigger_15_info, 2, 8, 1, true)
	Trigger_15:SetPosition(538.6, 22, 429.6)
	Trigger_15_act1 = TeleportAction()
	Trigger_15_act1:SetMapName("Map043_2")
	Trigger_15_act1:SetSpawning(2)
	Trigger_15:SetAction1(Trigger_15_act1)
	environment:AddTrigger(Trigger_15)

	Trigger_16_info = TriggerInfo(16, "to_tralumain", true, true, false)
	Trigger_16 = ZoneTrigger(Trigger_16_info, 1, 8, 2, true)
	Trigger_16:SetPosition(473.3, 21.8, 439.3)
	Trigger_16_act1 = TeleportAction()
	Trigger_16_act1:SetMapName("Map003_2")
	Trigger_16_act1:SetSpawning(1)
	Trigger_16:SetAction1(Trigger_16_act1)
	environment:AddTrigger(Trigger_16)

end

