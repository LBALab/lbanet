function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(37)
	Spawn_1:SetPosY(2.01)
	Spawn_1:SetPosZ(15.5)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(53)
	Spawn_2:SetPosY(0.01)
	Spawn_2:SetPosZ(47)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(32)
	Spawn_3:SetPosY(0.01)
	Spawn_3:SetPosZ(62)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(22.5)
	Spawn_4:SetPosY(0.01)
	Spawn_4:SetPosZ(57)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.HitPowerOnTouch = -1
	Actor_1.ExcludeFromNavMesh = false
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map1.osgb"
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
	Actor_1.DisplayDesc.UseBillboard = false
	Actor_1.PhysicDesc.Pos.X = 0
	Actor_1.PhysicDesc.Pos.Y = 0
	Actor_1.PhysicDesc.Pos.Z = 0
	Actor_1.PhysicDesc.Pos.Rotation = 0
	Actor_1.PhysicDesc.Density = 1
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 0
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 0
	Actor_1.PhysicDesc.AllowFreeMove = true
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map1.phy"
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

	Actor_10 = ActorObjectInfo(10)
	Actor_10:SetRenderType(1)
	Actor_10.HitPowerOnTouch = -1
	Actor_10.ExcludeFromNavMesh = false
	Actor_10.DisplayDesc.ModelId = 0
	Actor_10.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite034.osgb"
	Actor_10.DisplayDesc.Outfit = ""
	Actor_10.DisplayDesc.Weapon = ""
	Actor_10.DisplayDesc.Mode = ""
	Actor_10.DisplayDesc.UseLight = true
	Actor_10.DisplayDesc.CastShadow = false
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
	Actor_10.DisplayDesc.UseBillboard = false
	Actor_10.PhysicDesc.Pos.X = 53
	Actor_10.PhysicDesc.Pos.Y = 2
	Actor_10.PhysicDesc.Pos.Z = 45.8
	Actor_10.PhysicDesc.Pos.Rotation = 0
	Actor_10.PhysicDesc.Density = 1
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 2
	Actor_10.PhysicDesc.SizeY = 4
	Actor_10.PhysicDesc.SizeZ = 0.2
	Actor_10.PhysicDesc.AllowFreeMove = true
	Actor_10.PhysicDesc.Filename = ""
	Actor_10:SetPhysicalActorType(2)
	Actor_10:SetPhysicalShape(2)
	Actor_10.ExtraInfo.Name = ""
	Actor_10.ExtraInfo.NameColorR = 0
	Actor_10.ExtraInfo.NameColorG = 0
	Actor_10.ExtraInfo.NameColorB = 0
	Actor_10.ExtraInfo.Display = false
	Actor_10.LifeInfo.Display = false
	Actor_10H = DoorHandler(Actor_10,0,1,2,0.01,false)
	Actor_10_Sc0 = ASPWaitForSignal(1)
	Actor_10H:AddScriptPart(Actor_10_Sc0)
	Actor_10_Sc1 = ASPGoTo(55,2,45.8,0.01)
	Actor_10H:AddScriptPart(Actor_10_Sc1)
	Actor_10_Sc2 = ASPWaitForSignal(2)
	Actor_10H:AddScriptPart(Actor_10_Sc2)
	Actor_10_Sc3 = ASPGoTo(53,2,45.8,0.01)
	Actor_10H:AddScriptPart(Actor_10_Sc3)
	environment:AddActorObject(Actor_10H)

	Actor_11 = ActorObjectInfo(11)
	Actor_11:SetRenderType(1)
	Actor_11.HitPowerOnTouch = -1
	Actor_11.ExcludeFromNavMesh = false
	Actor_11.DisplayDesc.ModelId = 0
	Actor_11.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite012.osgb"
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
	Actor_11.DisplayDesc.UseBillboard = false
	Actor_11.PhysicDesc.Pos.X = 22.5
	Actor_11.PhysicDesc.Pos.Y = 0
	Actor_11.PhysicDesc.Pos.Z = 55.4
	Actor_11.PhysicDesc.Pos.Rotation = 0
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 3
	Actor_11.PhysicDesc.SizeY = 8
	Actor_11.PhysicDesc.SizeZ = 1
	Actor_11.PhysicDesc.AllowFreeMove = true
	Actor_11.PhysicDesc.Filename = ""
	Actor_11:SetPhysicalActorType(2)
	Actor_11:SetPhysicalShape(2)
	Actor_11.ExtraInfo.Name = ""
	Actor_11.ExtraInfo.NameColorR = 0
	Actor_11.ExtraInfo.NameColorG = 0
	Actor_11.ExtraInfo.NameColorB = 0
	Actor_11.ExtraInfo.Display = false
	Actor_11.LifeInfo.Display = false
	Actor_11H = DoorHandler(Actor_11,0,0,3,0.004,false)
	Actor_11_Sc0 = ASPWaitForSignal(1)
	Actor_11H:AddScriptPart(Actor_11_Sc0)
	Actor_11_Sc1 = ASPGoTo(19.5,0,55.4,0.004)
	Actor_11H:AddScriptPart(Actor_11_Sc1)
	Actor_11_Sc2 = ASPWaitForSignal(2)
	Actor_11H:AddScriptPart(Actor_11_Sc2)
	Actor_11_Sc3 = ASPGoTo(22.5,0,55.4,0.004)
	Actor_11H:AddScriptPart(Actor_11_Sc3)
	environment:AddActorObject(Actor_11H)

	Actor_12 = ActorObjectInfo(12)
	Actor_12:SetRenderType(1)
	Actor_12.HitPowerOnTouch = -1
	Actor_12.ExcludeFromNavMesh = false
	Actor_12.DisplayDesc.ModelId = 0
	Actor_12.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite019.osgb"
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
	Actor_12.DisplayDesc.UseBillboard = false
	Actor_12.PhysicDesc.Pos.X = 29.5
	Actor_12.PhysicDesc.Pos.Y = 6
	Actor_12.PhysicDesc.Pos.Z = 40.5
	Actor_12.PhysicDesc.Pos.Rotation = 0
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 3
	Actor_12.PhysicDesc.SizeY = 5
	Actor_12.PhysicDesc.SizeZ = 1
	Actor_12.PhysicDesc.AllowFreeMove = true
	Actor_12.PhysicDesc.Filename = ""
	Actor_12:SetPhysicalActorType(2)
	Actor_12:SetPhysicalShape(2)
	Actor_12.ExtraInfo.Name = ""
	Actor_12.ExtraInfo.NameColorR = 0
	Actor_12.ExtraInfo.NameColorG = 0
	Actor_12.ExtraInfo.NameColorB = 0
	Actor_12.ExtraInfo.Display = false
	Actor_12.LifeInfo.Display = false
	Actor_12H = DoorHandler(Actor_12,0,0,3,0.004,false)
	Actor_12_Sc0 = ASPWaitForSignal(1)
	Actor_12H:AddScriptPart(Actor_12_Sc0)
	Actor_12_Sc1 = ASPGoTo(26.5,6,40.5,0.004)
	Actor_12H:AddScriptPart(Actor_12_Sc1)
	Actor_12_Sc2 = ASPWaitForSignal(2)
	Actor_12H:AddScriptPart(Actor_12_Sc2)
	Actor_12_Sc3 = ASPGoTo(29.5,6,40.5,0.004)
	Actor_12H:AddScriptPart(Actor_12_Sc3)
	environment:AddActorObject(Actor_12H)

	Actor_13 = ActorObjectInfo(13)
	Actor_13:SetRenderType(1)
	Actor_13.HitPowerOnTouch = -1
	Actor_13.ExcludeFromNavMesh = false
	Actor_13.DisplayDesc.ModelId = 0
	Actor_13.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite018.osgb"
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
	Actor_13.DisplayDesc.UseBillboard = false
	Actor_13.PhysicDesc.Pos.X = 32.5
	Actor_13.PhysicDesc.Pos.Y = 6
	Actor_13.PhysicDesc.Pos.Z = 40.5
	Actor_13.PhysicDesc.Pos.Rotation = 0
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 3
	Actor_13.PhysicDesc.SizeY = 5
	Actor_13.PhysicDesc.SizeZ = 1
	Actor_13.PhysicDesc.AllowFreeMove = true
	Actor_13.PhysicDesc.Filename = ""
	Actor_13:SetPhysicalActorType(2)
	Actor_13:SetPhysicalShape(2)
	Actor_13.ExtraInfo.Name = ""
	Actor_13.ExtraInfo.NameColorR = 0
	Actor_13.ExtraInfo.NameColorG = 0
	Actor_13.ExtraInfo.NameColorB = 0
	Actor_13.ExtraInfo.Display = false
	Actor_13.LifeInfo.Display = false
	Actor_13H = DoorHandler(Actor_13,0,1,3,0.004,false)
	Actor_13_Sc0 = ASPWaitForSignal(1)
	Actor_13H:AddScriptPart(Actor_13_Sc0)
	Actor_13_Sc1 = ASPGoTo(35.5,6,40.5,0.004)
	Actor_13H:AddScriptPart(Actor_13_Sc1)
	Actor_13_Sc2 = ASPWaitForSignal(2)
	Actor_13H:AddScriptPart(Actor_13_Sc2)
	Actor_13_Sc3 = ASPGoTo(32.5,6,40.5,0.004)
	Actor_13H:AddScriptPart(Actor_13_Sc3)
	environment:AddActorObject(Actor_13H)

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(1)
	Actor_14.HitPowerOnTouch = -1
	Actor_14.ExcludeFromNavMesh = false
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
	Actor_14.DisplayDesc.UseBillboard = false
	Actor_14.PhysicDesc.Pos.X = 36
	Actor_14.PhysicDesc.Pos.Y = 2
	Actor_14.PhysicDesc.Pos.Z = 14.5
	Actor_14.PhysicDesc.Pos.Rotation = 0
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 1
	Actor_14.PhysicDesc.SizeY = 8
	Actor_14.PhysicDesc.SizeZ = 2.5
	Actor_14.PhysicDesc.AllowFreeMove = true
	Actor_14.PhysicDesc.Filename = ""
	Actor_14:SetPhysicalActorType(2)
	Actor_14:SetPhysicalShape(2)
	Actor_14.ExtraInfo.Name = ""
	Actor_14.ExtraInfo.NameColorR = 0
	Actor_14.ExtraInfo.NameColorG = 0
	Actor_14.ExtraInfo.NameColorB = 0
	Actor_14.ExtraInfo.Display = false
	Actor_14.LifeInfo.Display = false
	Actor_14H = DoorHandler(Actor_14,1,0,-90,0.1,false)
	Actor_14_Sc0 = ASPWaitForSignal(1)
	Actor_14H:AddScriptPart(Actor_14_Sc0)
	Actor_14_Sc1 = ASPRotateFromPoint(-90,36,2,13.25,0.1)
	Actor_14H:AddScriptPart(Actor_14_Sc1)
	Actor_14_Sc2 = ASPWaitForSignal(2)
	Actor_14H:AddScriptPart(Actor_14_Sc2)
	Actor_14_Sc3 = ASPRotateFromPoint(0,36,2,13.25,0.1)
	Actor_14H:AddScriptPart(Actor_14_Sc3)
	Actor_14_Sc4 = ASPTeleportTo(36,2,14.5)
	Actor_14H:AddScriptPart(Actor_14_Sc4)
	Actor_14_Sc5 = ASPSetRotation(0)
	Actor_14H:AddScriptPart(Actor_14_Sc5)
	environment:AddActorObject(Actor_14H)

	Actor_15 = ActorObjectInfo(15)
	Actor_15:SetRenderType(1)
	Actor_15.HitPowerOnTouch = -1
	Actor_15.ExcludeFromNavMesh = false
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
	Actor_15.DisplayDesc.UseBillboard = false
	Actor_15.PhysicDesc.Pos.X = 36
	Actor_15.PhysicDesc.Pos.Y = 2
	Actor_15.PhysicDesc.Pos.Z = 17
	Actor_15.PhysicDesc.Pos.Rotation = 0
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 1
	Actor_15.PhysicDesc.SizeY = 8
	Actor_15.PhysicDesc.SizeZ = 2.5
	Actor_15.PhysicDesc.AllowFreeMove = true
	Actor_15.PhysicDesc.Filename = ""
	Actor_15:SetPhysicalActorType(2)
	Actor_15:SetPhysicalShape(2)
	Actor_15.ExtraInfo.Name = ""
	Actor_15.ExtraInfo.NameColorR = 0
	Actor_15.ExtraInfo.NameColorG = 0
	Actor_15.ExtraInfo.NameColorB = 0
	Actor_15.ExtraInfo.Display = false
	Actor_15.LifeInfo.Display = false
	Actor_15H = DoorHandler(Actor_15,1,1,90,0.1,false)
	Actor_15_Sc0 = ASPWaitForSignal(1)
	Actor_15H:AddScriptPart(Actor_15_Sc0)
	Actor_15_Sc1 = ASPRotateFromPoint(90,36,2,18.25,0.1)
	Actor_15H:AddScriptPart(Actor_15_Sc1)
	Actor_15_Sc2 = ASPWaitForSignal(2)
	Actor_15H:AddScriptPart(Actor_15_Sc2)
	Actor_15_Sc3 = ASPRotateFromPoint(0,36,2,18.25,0.1)
	Actor_15H:AddScriptPart(Actor_15_Sc3)
	Actor_15_Sc4 = ASPTeleportTo(36,2,17)
	Actor_15H:AddScriptPart(Actor_15_Sc4)
	Actor_15_Sc5 = ASPSetRotation(0)
	Actor_15H:AddScriptPart(Actor_15_Sc5)
	environment:AddActorObject(Actor_15H)

	Actor_16 = ActorObjectInfo(16)
	Actor_16:SetRenderType(3)
	Actor_16.HitPowerOnTouch = 20
	Actor_16.ExcludeFromNavMesh = false
	Actor_16.DisplayDesc.ModelId = 0
	Actor_16.DisplayDesc.ModelName = "GarbageTruck"
	Actor_16.DisplayDesc.Outfit = "No"
	Actor_16.DisplayDesc.Weapon = "No"
	Actor_16.DisplayDesc.Mode = "Normal"
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
	Actor_16.DisplayDesc.UseBillboard = false
	Actor_16.DisplayDesc.ColorMaterialType = 4
	Actor_16.DisplayDesc.MatAmbientColorR = -0.2
	Actor_16.DisplayDesc.MatAmbientColorG = -0.2
	Actor_16.DisplayDesc.MatAmbientColorB = -0.2
	Actor_16.DisplayDesc.MatAmbientColorA = 1
	Actor_16.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_16.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_16.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_16.DisplayDesc.MatDiffuseColorA = 1
	Actor_16.DisplayDesc.MatSpecularColorR = 0
	Actor_16.DisplayDesc.MatSpecularColorG = 0
	Actor_16.DisplayDesc.MatSpecularColorB = 0
	Actor_16.DisplayDesc.MatSpecularColorA = 1
	Actor_16.DisplayDesc.MatEmissionColorR = 0
	Actor_16.DisplayDesc.MatEmissionColorG = 0
	Actor_16.DisplayDesc.MatEmissionColorB = 0
	Actor_16.DisplayDesc.MatEmissionColorA = 1
	Actor_16.DisplayDesc.MatShininess = 0
	Actor_16.PhysicDesc.Pos.X = 10
	Actor_16.PhysicDesc.Pos.Y = 7
	Actor_16.PhysicDesc.Pos.Z = 45
	Actor_16.PhysicDesc.Pos.Rotation = 0
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 2
	Actor_16.PhysicDesc.SizeY = 5
	Actor_16.PhysicDesc.SizeZ = 4
	Actor_16.PhysicDesc.AllowFreeMove = true
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
	Actor_16_Sc0 = ASPStartWaypoint(28.5,6,44.5,true)
	Actor_16H:AddScriptPart(Actor_16_Sc0)
	Actor_16_Sc1 = ASPSendSignal(1,12)
	Actor_16H:AddScriptPart(Actor_16_Sc1)
	Actor_16_Sc2 = ASPSendSignal(1,13)
	Actor_16H:AddScriptPart(Actor_16_Sc2)
	Actor_16_Sc3 = ASPFollowWaypoint(30.5,6,42)
	Actor_16H:AddScriptPart(Actor_16_Sc3)
	Actor_16_Sc4 = ASPFollowWaypoint(31,6,37.5)
	Actor_16H:AddScriptPart(Actor_16_Sc4)
	Actor_16_Sc5 = ASPSendSignal(2,12)
	Actor_16H:AddScriptPart(Actor_16_Sc5)
	Actor_16_Sc6 = ASPSendSignal(2,13)
	Actor_16H:AddScriptPart(Actor_16_Sc6)
	Actor_16_Sc7 = ASPFollowWaypoint(34,6,35.5)
	Actor_16H:AddScriptPart(Actor_16_Sc7)
	Actor_16_Sc8 = ASPFollowWaypoint(49.5,6,35.5)
	Actor_16H:AddScriptPart(Actor_16_Sc8)
	Actor_16_Sc9 = ASPFollowWaypoint(54.5,6,36.5)
	Actor_16H:AddScriptPart(Actor_16_Sc9)
	Actor_16_Sc10 = ASPFollowWaypoint(55.5,6,41)
	Actor_16H:AddScriptPart(Actor_16_Sc10)
	Actor_16_Sc11 = ASPStartWaypoint(56,6,34.5,false)
	Actor_16H:AddScriptPart(Actor_16_Sc11)
	Actor_16_Sc12 = ASPFollowWaypoint(55.5,6,17)
	Actor_16H:AddScriptPart(Actor_16_Sc12)
	Actor_16_Sc13 = ASPSendSignal(20,-1)
	Actor_16H:AddScriptPart(Actor_16_Sc13)
	Actor_16_Sc14 = ASPStartWaypoint(55.5,6,24,true)
	Actor_16H:AddScriptPart(Actor_16_Sc14)
	Actor_16_Sc15 = ASPFollowWaypoint(56,6,32.5)
	Actor_16H:AddScriptPart(Actor_16_Sc15)
	Actor_16_Sc16 = ASPFollowWaypoint(51,6,36.5)
	Actor_16H:AddScriptPart(Actor_16_Sc16)
	Actor_16_Sc17 = ASPFollowWaypoint(35.5,6,37)
	Actor_16H:AddScriptPart(Actor_16_Sc17)
	Actor_16_Sc18 = ASPSendSignal(1,12)
	Actor_16H:AddScriptPart(Actor_16_Sc18)
	Actor_16_Sc19 = ASPSendSignal(1,13)
	Actor_16H:AddScriptPart(Actor_16_Sc19)
	Actor_16_Sc20 = ASPFollowWaypoint(31.5,6,37.5)
	Actor_16H:AddScriptPart(Actor_16_Sc20)
	Actor_16_Sc21 = ASPFollowWaypoint(31,6,41)
	Actor_16H:AddScriptPart(Actor_16_Sc21)
	Actor_16_Sc22 = ASPFollowWaypoint(29.5,6,44.5)
	Actor_16H:AddScriptPart(Actor_16_Sc22)
	Actor_16_Sc23 = ASPSendSignal(2,12)
	Actor_16H:AddScriptPart(Actor_16_Sc23)
	Actor_16_Sc24 = ASPSendSignal(2,13)
	Actor_16H:AddScriptPart(Actor_16_Sc24)
	Actor_16_Sc25 = ASPFollowWaypoint(20.5,6,45)
	Actor_16H:AddScriptPart(Actor_16_Sc25)
	Actor_16_Sc26 = ASPFollowWaypoint(16,6,45.5)
	Actor_16H:AddScriptPart(Actor_16_Sc26)
	Actor_16_Sc27 = ASPFollowWaypoint(12.5,6,48)
	Actor_16H:AddScriptPart(Actor_16_Sc27)
	Actor_16_Sc28 = ASPFollowWaypoint(13,6,52)
	Actor_16H:AddScriptPart(Actor_16_Sc28)
	Actor_16_Sc29 = ASPStartWaypoint(13,6,48,false)
	Actor_16H:AddScriptPart(Actor_16_Sc29)
	Actor_16_Sc30 = ASPFollowWaypoint(11.5,6,45.5)
	Actor_16H:AddScriptPart(Actor_16_Sc30)
	Actor_16_Sc31 = ASPFollowWaypoint(9.5,6,45)
	Actor_16H:AddScriptPart(Actor_16_Sc31)
	Actor_16_Sc32 = ASPChangeAnimation("#3")
	Actor_16H:AddScriptPart(Actor_16_Sc32)
	Actor_16_Sc33 = ASPPlayAnimation(true)
	Actor_16H:AddScriptPart(Actor_16_Sc33)
	Actor_16_Sc34 = ASPSendSignal(30,-1)
	Actor_16H:AddScriptPart(Actor_16_Sc34)
	environment:AddActorObject(Actor_16H)

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(3)
	Actor_17.HitPowerOnTouch = -1
	Actor_17.ExcludeFromNavMesh = false
	Actor_17.DisplayDesc.ModelId = 0
	Actor_17.DisplayDesc.ModelName = "Grobo"
	Actor_17.DisplayDesc.Outfit = "Baldino"
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
	Actor_17.DisplayDesc.UseBillboard = false
	Actor_17.DisplayDesc.ColorMaterialType = 4
	Actor_17.DisplayDesc.MatAmbientColorR = -0.2
	Actor_17.DisplayDesc.MatAmbientColorG = -0.2
	Actor_17.DisplayDesc.MatAmbientColorB = -0.2
	Actor_17.DisplayDesc.MatAmbientColorA = 1
	Actor_17.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_17.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_17.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_17.DisplayDesc.MatDiffuseColorA = 1
	Actor_17.DisplayDesc.MatSpecularColorR = 0
	Actor_17.DisplayDesc.MatSpecularColorG = 0
	Actor_17.DisplayDesc.MatSpecularColorB = 0
	Actor_17.DisplayDesc.MatSpecularColorA = 1
	Actor_17.DisplayDesc.MatEmissionColorR = 0
	Actor_17.DisplayDesc.MatEmissionColorG = 0
	Actor_17.DisplayDesc.MatEmissionColorB = 0
	Actor_17.DisplayDesc.MatEmissionColorA = 1
	Actor_17.DisplayDesc.MatShininess = 0
	Actor_17.PhysicDesc.Pos.X = 20.3125
	Actor_17.PhysicDesc.Pos.Y = 0.0625
	Actor_17.PhysicDesc.Pos.Z = 57.5625
	Actor_17.PhysicDesc.Pos.Rotation = 25
	Actor_17.PhysicDesc.Density = 1
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 1.5
	Actor_17.PhysicDesc.SizeY = 5
	Actor_17.PhysicDesc.SizeZ = 1.5
	Actor_17.PhysicDesc.AllowFreeMove = true
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

	Actor_21 = ActorObjectInfo(21)
	Actor_21:SetRenderType(3)
	Actor_21.HitPowerOnTouch = -1
	Actor_21.ExcludeFromNavMesh = false
	Actor_21.DisplayDesc.ModelId = 0
	Actor_21.DisplayDesc.ModelName = "Rabbibunny"
	Actor_21.DisplayDesc.Outfit = "Orange"
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
	Actor_21.DisplayDesc.UseBillboard = false
	Actor_21.DisplayDesc.ColorMaterialType = 4
	Actor_21.DisplayDesc.MatAmbientColorR = -0.2
	Actor_21.DisplayDesc.MatAmbientColorG = -0.2
	Actor_21.DisplayDesc.MatAmbientColorB = -0.2
	Actor_21.DisplayDesc.MatAmbientColorA = 1
	Actor_21.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_21.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_21.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_21.DisplayDesc.MatDiffuseColorA = 1
	Actor_21.DisplayDesc.MatSpecularColorR = 0
	Actor_21.DisplayDesc.MatSpecularColorG = 0
	Actor_21.DisplayDesc.MatSpecularColorB = 0
	Actor_21.DisplayDesc.MatSpecularColorA = 1
	Actor_21.DisplayDesc.MatEmissionColorR = 0
	Actor_21.DisplayDesc.MatEmissionColorG = 0
	Actor_21.DisplayDesc.MatEmissionColorB = 0
	Actor_21.DisplayDesc.MatEmissionColorA = 1
	Actor_21.DisplayDesc.MatShininess = 0
	Actor_21.PhysicDesc.Pos.X = 57
	Actor_21.PhysicDesc.Pos.Y = 6
	Actor_21.PhysicDesc.Pos.Z = 11
	Actor_21.PhysicDesc.Pos.Rotation = 25
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 1
	Actor_21.PhysicDesc.SizeY = 5
	Actor_21.PhysicDesc.SizeZ = 1
	Actor_21.PhysicDesc.AllowFreeMove = true
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
	Actor_22.HitPowerOnTouch = -1
	Actor_22.ExcludeFromNavMesh = false
	Actor_22.DisplayDesc.ModelId = 0
	Actor_22.DisplayDesc.ModelName = "Object"
	Actor_22.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_22.DisplayDesc.UseBillboard = false
	Actor_22.DisplayDesc.ColorMaterialType = 4
	Actor_22.DisplayDesc.MatAmbientColorR = -0.2
	Actor_22.DisplayDesc.MatAmbientColorG = -0.2
	Actor_22.DisplayDesc.MatAmbientColorB = -0.2
	Actor_22.DisplayDesc.MatAmbientColorA = 1
	Actor_22.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_22.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_22.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_22.DisplayDesc.MatDiffuseColorA = 1
	Actor_22.DisplayDesc.MatSpecularColorR = 0
	Actor_22.DisplayDesc.MatSpecularColorG = 0
	Actor_22.DisplayDesc.MatSpecularColorB = 0
	Actor_22.DisplayDesc.MatSpecularColorA = 1
	Actor_22.DisplayDesc.MatEmissionColorR = 0
	Actor_22.DisplayDesc.MatEmissionColorG = 0
	Actor_22.DisplayDesc.MatEmissionColorB = 0
	Actor_22.DisplayDesc.MatEmissionColorA = 1
	Actor_22.DisplayDesc.MatShininess = 0
	Actor_22.PhysicDesc.Pos.X = 0
	Actor_22.PhysicDesc.Pos.Y = -1
	Actor_22.PhysicDesc.Pos.Z = 0
	Actor_22.PhysicDesc.Pos.Rotation = 25
	Actor_22.PhysicDesc.Density = 1
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 0.5
	Actor_22.PhysicDesc.SizeY = 2
	Actor_22.PhysicDesc.SizeZ = 0.6
	Actor_22.PhysicDesc.AllowFreeMove = true
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
	Actor_23.HitPowerOnTouch = -1
	Actor_23.ExcludeFromNavMesh = false
	Actor_23.DisplayDesc.ModelId = 0
	Actor_23.DisplayDesc.ModelName = "Soldier"
	Actor_23.DisplayDesc.Outfit = "Grass"
	Actor_23.DisplayDesc.Weapon = "rifle"
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
	Actor_23.DisplayDesc.UseBillboard = false
	Actor_23.DisplayDesc.ColorMaterialType = 4
	Actor_23.DisplayDesc.MatAmbientColorR = -0.2
	Actor_23.DisplayDesc.MatAmbientColorG = -0.2
	Actor_23.DisplayDesc.MatAmbientColorB = -0.2
	Actor_23.DisplayDesc.MatAmbientColorA = 1
	Actor_23.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_23.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_23.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_23.DisplayDesc.MatDiffuseColorA = 1
	Actor_23.DisplayDesc.MatSpecularColorR = 0
	Actor_23.DisplayDesc.MatSpecularColorG = 0
	Actor_23.DisplayDesc.MatSpecularColorB = 0
	Actor_23.DisplayDesc.MatSpecularColorA = 1
	Actor_23.DisplayDesc.MatEmissionColorR = 0
	Actor_23.DisplayDesc.MatEmissionColorG = 0
	Actor_23.DisplayDesc.MatEmissionColorB = 0
	Actor_23.DisplayDesc.MatEmissionColorA = 1
	Actor_23.DisplayDesc.MatShininess = 0
	Actor_23.PhysicDesc.Pos.X = 45.2
	Actor_23.PhysicDesc.Pos.Y = 6
	Actor_23.PhysicDesc.Pos.Z = 30.5
	Actor_23.PhysicDesc.Pos.Rotation = 0
	Actor_23.PhysicDesc.Density = 1
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 2
	Actor_23.PhysicDesc.SizeY = 5
	Actor_23.PhysicDesc.SizeZ = 2
	Actor_23.PhysicDesc.AllowFreeMove = true
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
	Actor_23H:SetAggresive(true)
	Actor_23H:SetLife(50)
	Actor_23H:SetMana(0)
	Actor_23H:SetArmor(0)
	Actor_23H:SetAttackActiDist(7)
	Actor_23H:SetAttackActiDistDiscrete(4)
	Actor_23H:SetAttackActiDistHidden(2)
	Actor_23H:SetAttackStopDist(10)
	Actor_23H:SetRespawnTimeInSec(10)
	Actor_23H:SetWeapon1Type(1)
	Actor_23H:SetWeapon1Power(10)
	Actor_23H:SetWeapon1ReachDistance(2)
	Actor_23H:Setuseweapon1animation("Use1Weapon")
	Actor_23H:SetWeapon2Type(2)
	Actor_23H:SetWeapon2Power(0)
	Actor_23H:SetWeapon2ReachDistance(7)
	Actor_23H:Setuseweapon2animation("UseWeapon")
	Actor_23H_weapon2proj0 = ProjectileObjectDef()
	Actor_23H_weapon2proj0:SetRenderType(2)
	Actor_23H_weapon2proj0.DisplayDesc.ModelId = 0
	Actor_23H_weapon2proj0.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_23H_weapon2proj0.DisplayDesc.Outfit = ""
	Actor_23H_weapon2proj0.DisplayDesc.Weapon = ""
	Actor_23H_weapon2proj0.DisplayDesc.Mode = ""
	Actor_23H_weapon2proj0.DisplayDesc.UseLight = true
	Actor_23H_weapon2proj0.DisplayDesc.CastShadow = true
	Actor_23H_weapon2proj0.DisplayDesc.ColorR = 1
	Actor_23H_weapon2proj0.DisplayDesc.ColorG = 1
	Actor_23H_weapon2proj0.DisplayDesc.ColorB = 1
	Actor_23H_weapon2proj0.DisplayDesc.ColorA = 0.9
	Actor_23H_weapon2proj0.DisplayDesc.TransX = 0
	Actor_23H_weapon2proj0.DisplayDesc.TransY = 0
	Actor_23H_weapon2proj0.DisplayDesc.TransZ = 0
	Actor_23H_weapon2proj0.DisplayDesc.ScaleX = 0.05
	Actor_23H_weapon2proj0.DisplayDesc.ScaleY = 0.05
	Actor_23H_weapon2proj0.DisplayDesc.ScaleZ = 0.05
	Actor_23H_weapon2proj0.DisplayDesc.RotX = 0
	Actor_23H_weapon2proj0.DisplayDesc.RotY = 0
	Actor_23H_weapon2proj0.DisplayDesc.RotZ = 0
	Actor_23H_weapon2proj0.DisplayDesc.UseBillboard = true
	Actor_23H_weapon2proj0.PhysicDesc.Pos.X = 0
	Actor_23H_weapon2proj0.PhysicDesc.Pos.Y = 0
	Actor_23H_weapon2proj0.PhysicDesc.Pos.Z = 0
	Actor_23H_weapon2proj0.PhysicDesc.Pos.Rotation = 0
	Actor_23H_weapon2proj0.PhysicDesc.Density = 1
	Actor_23H_weapon2proj0.PhysicDesc.Collidable = false
	Actor_23H_weapon2proj0.PhysicDesc.SizeX = 0.05
	Actor_23H_weapon2proj0.PhysicDesc.SizeY = 0.05
	Actor_23H_weapon2proj0.PhysicDesc.SizeZ = 0.05
	Actor_23H_weapon2proj0.PhysicDesc.AllowFreeMove = true
	Actor_23H_weapon2proj0.PhysicDesc.Filename = ""
	Actor_23H_weapon2proj0:SetPhysicalActorType(3)
	Actor_23H_weapon2proj0:SetPhysicalShape(4)
	Actor_23H_weapon2proj0.UsableMode = ""
	Actor_23H_weapon2proj0.Power = 10
	Actor_23H_weapon2proj0.UseMana = 0
	Actor_23H_weapon2proj0.OffsetX = 2.5
	Actor_23H_weapon2proj0.OffsetY = 2.5
	Actor_23H_weapon2proj0.OffsetZ = 0
	Actor_23H_weapon2proj0.ForceX = 0.0005
	Actor_23H_weapon2proj0.ForceY = -0.0002
	Actor_23H_weapon2proj0.ForceYOnImpact = 0
	Actor_23H_weapon2proj0.NbBounce = 1
	Actor_23H_weapon2proj0.IgnoreGravity = true
	Actor_23H_weapon2proj0.LifeTime = 4000
	Actor_23H_weapon2proj0.Comeback = false
	Actor_23H_weapon2proj0.StartAnimFrame = 4
	Actor_23H_weapon2proj0.AngleOffset = 0
	Actor_23H_weapon2proj0.SoundAtStart = "Worlds/Lba1Original/Sound/SAMPLES027.voc.MP3"
	Actor_23H_weapon2proj0.SoundOnBounce = ""
	Actor_23H_weapon2proj0.ForceHurt = false
	Actor_23H_weapon2proj0.MultiShoot = false
	Actor_23H_weapon2proj0.UseTimer = false
	Actor_23H_weapon2proj0.Frequency = 1
	Actor_23H_weapon2proj0.FollowTarget = false
	Actor_23H:AddProjectileWeapon2(Actor_23H_weapon2proj0)
	Actor_23H_weapon2proj1 = ProjectileObjectDef()
	Actor_23H_weapon2proj1:SetRenderType(2)
	Actor_23H_weapon2proj1.DisplayDesc.ModelId = 0
	Actor_23H_weapon2proj1.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_23H_weapon2proj1.DisplayDesc.Outfit = ""
	Actor_23H_weapon2proj1.DisplayDesc.Weapon = ""
	Actor_23H_weapon2proj1.DisplayDesc.Mode = ""
	Actor_23H_weapon2proj1.DisplayDesc.UseLight = true
	Actor_23H_weapon2proj1.DisplayDesc.CastShadow = true
	Actor_23H_weapon2proj1.DisplayDesc.ColorR = 1
	Actor_23H_weapon2proj1.DisplayDesc.ColorG = 1
	Actor_23H_weapon2proj1.DisplayDesc.ColorB = 1
	Actor_23H_weapon2proj1.DisplayDesc.ColorA = 0.9
	Actor_23H_weapon2proj1.DisplayDesc.TransX = 0
	Actor_23H_weapon2proj1.DisplayDesc.TransY = 0
	Actor_23H_weapon2proj1.DisplayDesc.TransZ = 0
	Actor_23H_weapon2proj1.DisplayDesc.ScaleX = 0.05
	Actor_23H_weapon2proj1.DisplayDesc.ScaleY = 0.05
	Actor_23H_weapon2proj1.DisplayDesc.ScaleZ = 0.05
	Actor_23H_weapon2proj1.DisplayDesc.RotX = 0
	Actor_23H_weapon2proj1.DisplayDesc.RotY = 0
	Actor_23H_weapon2proj1.DisplayDesc.RotZ = 0
	Actor_23H_weapon2proj1.DisplayDesc.UseBillboard = true
	Actor_23H_weapon2proj1.PhysicDesc.Pos.X = 0
	Actor_23H_weapon2proj1.PhysicDesc.Pos.Y = 0
	Actor_23H_weapon2proj1.PhysicDesc.Pos.Z = 0
	Actor_23H_weapon2proj1.PhysicDesc.Pos.Rotation = 0
	Actor_23H_weapon2proj1.PhysicDesc.Density = 1
	Actor_23H_weapon2proj1.PhysicDesc.Collidable = false
	Actor_23H_weapon2proj1.PhysicDesc.SizeX = 0.05
	Actor_23H_weapon2proj1.PhysicDesc.SizeY = 0.05
	Actor_23H_weapon2proj1.PhysicDesc.SizeZ = 0.05
	Actor_23H_weapon2proj1.PhysicDesc.AllowFreeMove = true
	Actor_23H_weapon2proj1.PhysicDesc.Filename = ""
	Actor_23H_weapon2proj1:SetPhysicalActorType(3)
	Actor_23H_weapon2proj1:SetPhysicalShape(4)
	Actor_23H_weapon2proj1.UsableMode = ""
	Actor_23H_weapon2proj1.Power = 10
	Actor_23H_weapon2proj1.UseMana = 0
	Actor_23H_weapon2proj1.OffsetX = 2.5
	Actor_23H_weapon2proj1.OffsetY = 2.5
	Actor_23H_weapon2proj1.OffsetZ = 0
	Actor_23H_weapon2proj1.ForceX = 0.0005
	Actor_23H_weapon2proj1.ForceY = -0.0002
	Actor_23H_weapon2proj1.ForceYOnImpact = 0
	Actor_23H_weapon2proj1.NbBounce = 1
	Actor_23H_weapon2proj1.IgnoreGravity = true
	Actor_23H_weapon2proj1.LifeTime = 4000
	Actor_23H_weapon2proj1.Comeback = false
	Actor_23H_weapon2proj1.StartAnimFrame = 4
	Actor_23H_weapon2proj1.AngleOffset = 4
	Actor_23H_weapon2proj1.SoundAtStart = ""
	Actor_23H_weapon2proj1.SoundOnBounce = ""
	Actor_23H_weapon2proj1.ForceHurt = false
	Actor_23H_weapon2proj1.MultiShoot = false
	Actor_23H_weapon2proj1.UseTimer = false
	Actor_23H_weapon2proj1.Frequency = 1
	Actor_23H_weapon2proj1.FollowTarget = false
	Actor_23H:AddProjectileWeapon2(Actor_23H_weapon2proj1)
	Actor_23H_weapon2proj2 = ProjectileObjectDef()
	Actor_23H_weapon2proj2:SetRenderType(2)
	Actor_23H_weapon2proj2.DisplayDesc.ModelId = 0
	Actor_23H_weapon2proj2.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_23H_weapon2proj2.DisplayDesc.Outfit = ""
	Actor_23H_weapon2proj2.DisplayDesc.Weapon = ""
	Actor_23H_weapon2proj2.DisplayDesc.Mode = ""
	Actor_23H_weapon2proj2.DisplayDesc.UseLight = true
	Actor_23H_weapon2proj2.DisplayDesc.CastShadow = true
	Actor_23H_weapon2proj2.DisplayDesc.ColorR = 1
	Actor_23H_weapon2proj2.DisplayDesc.ColorG = 1
	Actor_23H_weapon2proj2.DisplayDesc.ColorB = 1
	Actor_23H_weapon2proj2.DisplayDesc.ColorA = 0.9
	Actor_23H_weapon2proj2.DisplayDesc.TransX = 0
	Actor_23H_weapon2proj2.DisplayDesc.TransY = 0
	Actor_23H_weapon2proj2.DisplayDesc.TransZ = 0
	Actor_23H_weapon2proj2.DisplayDesc.ScaleX = 0.05
	Actor_23H_weapon2proj2.DisplayDesc.ScaleY = 0.05
	Actor_23H_weapon2proj2.DisplayDesc.ScaleZ = 0.05
	Actor_23H_weapon2proj2.DisplayDesc.RotX = 0
	Actor_23H_weapon2proj2.DisplayDesc.RotY = 0
	Actor_23H_weapon2proj2.DisplayDesc.RotZ = 0
	Actor_23H_weapon2proj2.DisplayDesc.UseBillboard = true
	Actor_23H_weapon2proj2.PhysicDesc.Pos.X = 0
	Actor_23H_weapon2proj2.PhysicDesc.Pos.Y = 0
	Actor_23H_weapon2proj2.PhysicDesc.Pos.Z = 0
	Actor_23H_weapon2proj2.PhysicDesc.Pos.Rotation = 0
	Actor_23H_weapon2proj2.PhysicDesc.Density = 1
	Actor_23H_weapon2proj2.PhysicDesc.Collidable = false
	Actor_23H_weapon2proj2.PhysicDesc.SizeX = 0.05
	Actor_23H_weapon2proj2.PhysicDesc.SizeY = 0.05
	Actor_23H_weapon2proj2.PhysicDesc.SizeZ = 0.05
	Actor_23H_weapon2proj2.PhysicDesc.AllowFreeMove = true
	Actor_23H_weapon2proj2.PhysicDesc.Filename = ""
	Actor_23H_weapon2proj2:SetPhysicalActorType(3)
	Actor_23H_weapon2proj2:SetPhysicalShape(4)
	Actor_23H_weapon2proj2.UsableMode = ""
	Actor_23H_weapon2proj2.Power = 10
	Actor_23H_weapon2proj2.UseMana = 0
	Actor_23H_weapon2proj2.OffsetX = 2.5
	Actor_23H_weapon2proj2.OffsetY = 2.5
	Actor_23H_weapon2proj2.OffsetZ = 0
	Actor_23H_weapon2proj2.ForceX = 0.0005
	Actor_23H_weapon2proj2.ForceY = -0.0002
	Actor_23H_weapon2proj2.ForceYOnImpact = 0
	Actor_23H_weapon2proj2.NbBounce = 1
	Actor_23H_weapon2proj2.IgnoreGravity = true
	Actor_23H_weapon2proj2.LifeTime = 4000
	Actor_23H_weapon2proj2.Comeback = false
	Actor_23H_weapon2proj2.StartAnimFrame = 4
	Actor_23H_weapon2proj2.AngleOffset = -4
	Actor_23H_weapon2proj2.SoundAtStart = ""
	Actor_23H_weapon2proj2.SoundOnBounce = ""
	Actor_23H_weapon2proj2.ForceHurt = false
	Actor_23H_weapon2proj2.MultiShoot = false
	Actor_23H_weapon2proj2.UseTimer = false
	Actor_23H_weapon2proj2.Frequency = 1
	Actor_23H_weapon2proj2.FollowTarget = false
	Actor_23H:AddProjectileWeapon2(Actor_23H_weapon2proj2)
	Actor_23H:SetAttackFunction("ActorRotateAttackDistanceAndContactPlayer")
	Actor_23H:AddGivenItem(1,1,1,0.3,1)
	Actor_23H:AddGivenItem(2,1,1,0.3,1)
	Actor_23H:AddGivenItem(8,2,2,0.4,1)
	Actor_23H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_23H)

	Actor_24 = ActorObjectInfo(24)
	Actor_24:SetRenderType(3)
	Actor_24.HitPowerOnTouch = -1
	Actor_24.ExcludeFromNavMesh = false
	Actor_24.DisplayDesc.ModelId = 0
	Actor_24.DisplayDesc.ModelName = "Soldier"
	Actor_24.DisplayDesc.Outfit = "Grass"
	Actor_24.DisplayDesc.Weapon = "rifle"
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
	Actor_24.DisplayDesc.UseBillboard = false
	Actor_24.DisplayDesc.ColorMaterialType = 4
	Actor_24.DisplayDesc.MatAmbientColorR = -0.2
	Actor_24.DisplayDesc.MatAmbientColorG = -0.2
	Actor_24.DisplayDesc.MatAmbientColorB = -0.2
	Actor_24.DisplayDesc.MatAmbientColorA = 1
	Actor_24.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_24.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_24.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_24.DisplayDesc.MatDiffuseColorA = 1
	Actor_24.DisplayDesc.MatSpecularColorR = 0
	Actor_24.DisplayDesc.MatSpecularColorG = 0
	Actor_24.DisplayDesc.MatSpecularColorB = 0
	Actor_24.DisplayDesc.MatSpecularColorA = 1
	Actor_24.DisplayDesc.MatEmissionColorR = 0
	Actor_24.DisplayDesc.MatEmissionColorG = 0
	Actor_24.DisplayDesc.MatEmissionColorB = 0
	Actor_24.DisplayDesc.MatEmissionColorA = 1
	Actor_24.DisplayDesc.MatShininess = 0
	Actor_24.PhysicDesc.Pos.X = 27.3
	Actor_24.PhysicDesc.Pos.Y = 6
	Actor_24.PhysicDesc.Pos.Z = 32.5
	Actor_24.PhysicDesc.Pos.Rotation = 25
	Actor_24.PhysicDesc.Density = 1
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 2
	Actor_24.PhysicDesc.SizeY = 5
	Actor_24.PhysicDesc.SizeZ = 2
	Actor_24.PhysicDesc.AllowFreeMove = true
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
	Actor_24H:SetAggresive(true)
	Actor_24H:SetLife(50)
	Actor_24H:SetMana(0)
	Actor_24H:SetArmor(0)
	Actor_24H:SetAttackActiDist(7)
	Actor_24H:SetAttackActiDistDiscrete(4)
	Actor_24H:SetAttackActiDistHidden(2)
	Actor_24H:SetAttackStopDist(10)
	Actor_24H:SetRespawnTimeInSec(10)
	Actor_24H:SetWeapon1Type(1)
	Actor_24H:SetWeapon1Power(10)
	Actor_24H:SetWeapon1ReachDistance(2)
	Actor_24H:Setuseweapon1animation("Use1Weapon")
	Actor_24H:SetWeapon2Type(2)
	Actor_24H:SetWeapon2Power(0)
	Actor_24H:SetWeapon2ReachDistance(7)
	Actor_24H:Setuseweapon2animation("UseWeapon")
	Actor_24H_weapon2proj0 = ProjectileObjectDef()
	Actor_24H_weapon2proj0:SetRenderType(2)
	Actor_24H_weapon2proj0.DisplayDesc.ModelId = 0
	Actor_24H_weapon2proj0.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_24H_weapon2proj0.DisplayDesc.Outfit = ""
	Actor_24H_weapon2proj0.DisplayDesc.Weapon = ""
	Actor_24H_weapon2proj0.DisplayDesc.Mode = ""
	Actor_24H_weapon2proj0.DisplayDesc.UseLight = true
	Actor_24H_weapon2proj0.DisplayDesc.CastShadow = true
	Actor_24H_weapon2proj0.DisplayDesc.ColorR = 1
	Actor_24H_weapon2proj0.DisplayDesc.ColorG = 1
	Actor_24H_weapon2proj0.DisplayDesc.ColorB = 1
	Actor_24H_weapon2proj0.DisplayDesc.ColorA = 0.9
	Actor_24H_weapon2proj0.DisplayDesc.TransX = 0
	Actor_24H_weapon2proj0.DisplayDesc.TransY = 0
	Actor_24H_weapon2proj0.DisplayDesc.TransZ = 0
	Actor_24H_weapon2proj0.DisplayDesc.ScaleX = 0.05
	Actor_24H_weapon2proj0.DisplayDesc.ScaleY = 0.05
	Actor_24H_weapon2proj0.DisplayDesc.ScaleZ = 0.05
	Actor_24H_weapon2proj0.DisplayDesc.RotX = 0
	Actor_24H_weapon2proj0.DisplayDesc.RotY = 0
	Actor_24H_weapon2proj0.DisplayDesc.RotZ = 0
	Actor_24H_weapon2proj0.DisplayDesc.UseBillboard = true
	Actor_24H_weapon2proj0.PhysicDesc.Pos.X = 0
	Actor_24H_weapon2proj0.PhysicDesc.Pos.Y = 0
	Actor_24H_weapon2proj0.PhysicDesc.Pos.Z = 0
	Actor_24H_weapon2proj0.PhysicDesc.Pos.Rotation = 0
	Actor_24H_weapon2proj0.PhysicDesc.Density = 1
	Actor_24H_weapon2proj0.PhysicDesc.Collidable = false
	Actor_24H_weapon2proj0.PhysicDesc.SizeX = 0.05
	Actor_24H_weapon2proj0.PhysicDesc.SizeY = 0.05
	Actor_24H_weapon2proj0.PhysicDesc.SizeZ = 0.05
	Actor_24H_weapon2proj0.PhysicDesc.AllowFreeMove = true
	Actor_24H_weapon2proj0.PhysicDesc.Filename = ""
	Actor_24H_weapon2proj0:SetPhysicalActorType(3)
	Actor_24H_weapon2proj0:SetPhysicalShape(4)
	Actor_24H_weapon2proj0.UsableMode = ""
	Actor_24H_weapon2proj0.Power = 10
	Actor_24H_weapon2proj0.UseMana = 0
	Actor_24H_weapon2proj0.OffsetX = 2.5
	Actor_24H_weapon2proj0.OffsetY = 2.5
	Actor_24H_weapon2proj0.OffsetZ = 0
	Actor_24H_weapon2proj0.ForceX = 0.0005
	Actor_24H_weapon2proj0.ForceY = -0.0002
	Actor_24H_weapon2proj0.ForceYOnImpact = 0
	Actor_24H_weapon2proj0.NbBounce = 1
	Actor_24H_weapon2proj0.IgnoreGravity = true
	Actor_24H_weapon2proj0.LifeTime = 4000
	Actor_24H_weapon2proj0.Comeback = false
	Actor_24H_weapon2proj0.StartAnimFrame = 4
	Actor_24H_weapon2proj0.AngleOffset = 0
	Actor_24H_weapon2proj0.SoundAtStart = "Worlds/Lba1Original/Sound/SAMPLES027.voc.MP3"
	Actor_24H_weapon2proj0.SoundOnBounce = ""
	Actor_24H_weapon2proj0.ForceHurt = false
	Actor_24H_weapon2proj0.MultiShoot = false
	Actor_24H_weapon2proj0.UseTimer = false
	Actor_24H_weapon2proj0.Frequency = 1
	Actor_24H_weapon2proj0.FollowTarget = false
	Actor_24H:AddProjectileWeapon2(Actor_24H_weapon2proj0)
	Actor_24H_weapon2proj1 = ProjectileObjectDef()
	Actor_24H_weapon2proj1:SetRenderType(2)
	Actor_24H_weapon2proj1.DisplayDesc.ModelId = 0
	Actor_24H_weapon2proj1.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_24H_weapon2proj1.DisplayDesc.Outfit = ""
	Actor_24H_weapon2proj1.DisplayDesc.Weapon = ""
	Actor_24H_weapon2proj1.DisplayDesc.Mode = ""
	Actor_24H_weapon2proj1.DisplayDesc.UseLight = true
	Actor_24H_weapon2proj1.DisplayDesc.CastShadow = true
	Actor_24H_weapon2proj1.DisplayDesc.ColorR = 1
	Actor_24H_weapon2proj1.DisplayDesc.ColorG = 1
	Actor_24H_weapon2proj1.DisplayDesc.ColorB = 1
	Actor_24H_weapon2proj1.DisplayDesc.ColorA = 0.9
	Actor_24H_weapon2proj1.DisplayDesc.TransX = 0
	Actor_24H_weapon2proj1.DisplayDesc.TransY = 0
	Actor_24H_weapon2proj1.DisplayDesc.TransZ = 0
	Actor_24H_weapon2proj1.DisplayDesc.ScaleX = 0.05
	Actor_24H_weapon2proj1.DisplayDesc.ScaleY = 0.05
	Actor_24H_weapon2proj1.DisplayDesc.ScaleZ = 0.05
	Actor_24H_weapon2proj1.DisplayDesc.RotX = 0
	Actor_24H_weapon2proj1.DisplayDesc.RotY = 0
	Actor_24H_weapon2proj1.DisplayDesc.RotZ = 0
	Actor_24H_weapon2proj1.DisplayDesc.UseBillboard = true
	Actor_24H_weapon2proj1.PhysicDesc.Pos.X = 0
	Actor_24H_weapon2proj1.PhysicDesc.Pos.Y = 0
	Actor_24H_weapon2proj1.PhysicDesc.Pos.Z = 0
	Actor_24H_weapon2proj1.PhysicDesc.Pos.Rotation = 0
	Actor_24H_weapon2proj1.PhysicDesc.Density = 1
	Actor_24H_weapon2proj1.PhysicDesc.Collidable = false
	Actor_24H_weapon2proj1.PhysicDesc.SizeX = 0.05
	Actor_24H_weapon2proj1.PhysicDesc.SizeY = 0.05
	Actor_24H_weapon2proj1.PhysicDesc.SizeZ = 0.05
	Actor_24H_weapon2proj1.PhysicDesc.AllowFreeMove = true
	Actor_24H_weapon2proj1.PhysicDesc.Filename = ""
	Actor_24H_weapon2proj1:SetPhysicalActorType(3)
	Actor_24H_weapon2proj1:SetPhysicalShape(4)
	Actor_24H_weapon2proj1.UsableMode = ""
	Actor_24H_weapon2proj1.Power = 10
	Actor_24H_weapon2proj1.UseMana = 0
	Actor_24H_weapon2proj1.OffsetX = 2.5
	Actor_24H_weapon2proj1.OffsetY = 2.5
	Actor_24H_weapon2proj1.OffsetZ = 0
	Actor_24H_weapon2proj1.ForceX = 0.0005
	Actor_24H_weapon2proj1.ForceY = -0.0002
	Actor_24H_weapon2proj1.ForceYOnImpact = 0
	Actor_24H_weapon2proj1.NbBounce = 1
	Actor_24H_weapon2proj1.IgnoreGravity = true
	Actor_24H_weapon2proj1.LifeTime = 4000
	Actor_24H_weapon2proj1.Comeback = false
	Actor_24H_weapon2proj1.StartAnimFrame = 4
	Actor_24H_weapon2proj1.AngleOffset = 4
	Actor_24H_weapon2proj1.SoundAtStart = ""
	Actor_24H_weapon2proj1.SoundOnBounce = ""
	Actor_24H_weapon2proj1.ForceHurt = false
	Actor_24H_weapon2proj1.MultiShoot = false
	Actor_24H_weapon2proj1.UseTimer = false
	Actor_24H_weapon2proj1.Frequency = 1
	Actor_24H_weapon2proj1.FollowTarget = false
	Actor_24H:AddProjectileWeapon2(Actor_24H_weapon2proj1)
	Actor_24H_weapon2proj2 = ProjectileObjectDef()
	Actor_24H_weapon2proj2:SetRenderType(2)
	Actor_24H_weapon2proj2.DisplayDesc.ModelId = 0
	Actor_24H_weapon2proj2.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_24H_weapon2proj2.DisplayDesc.Outfit = ""
	Actor_24H_weapon2proj2.DisplayDesc.Weapon = ""
	Actor_24H_weapon2proj2.DisplayDesc.Mode = ""
	Actor_24H_weapon2proj2.DisplayDesc.UseLight = true
	Actor_24H_weapon2proj2.DisplayDesc.CastShadow = true
	Actor_24H_weapon2proj2.DisplayDesc.ColorR = 1
	Actor_24H_weapon2proj2.DisplayDesc.ColorG = 1
	Actor_24H_weapon2proj2.DisplayDesc.ColorB = 1
	Actor_24H_weapon2proj2.DisplayDesc.ColorA = 0.9
	Actor_24H_weapon2proj2.DisplayDesc.TransX = 0
	Actor_24H_weapon2proj2.DisplayDesc.TransY = 0
	Actor_24H_weapon2proj2.DisplayDesc.TransZ = 0
	Actor_24H_weapon2proj2.DisplayDesc.ScaleX = 0.05
	Actor_24H_weapon2proj2.DisplayDesc.ScaleY = 0.05
	Actor_24H_weapon2proj2.DisplayDesc.ScaleZ = 0.05
	Actor_24H_weapon2proj2.DisplayDesc.RotX = 0
	Actor_24H_weapon2proj2.DisplayDesc.RotY = 0
	Actor_24H_weapon2proj2.DisplayDesc.RotZ = 0
	Actor_24H_weapon2proj2.DisplayDesc.UseBillboard = true
	Actor_24H_weapon2proj2.PhysicDesc.Pos.X = 0
	Actor_24H_weapon2proj2.PhysicDesc.Pos.Y = 0
	Actor_24H_weapon2proj2.PhysicDesc.Pos.Z = 0
	Actor_24H_weapon2proj2.PhysicDesc.Pos.Rotation = 0
	Actor_24H_weapon2proj2.PhysicDesc.Density = 1
	Actor_24H_weapon2proj2.PhysicDesc.Collidable = false
	Actor_24H_weapon2proj2.PhysicDesc.SizeX = 0.05
	Actor_24H_weapon2proj2.PhysicDesc.SizeY = 0.05
	Actor_24H_weapon2proj2.PhysicDesc.SizeZ = 0.05
	Actor_24H_weapon2proj2.PhysicDesc.AllowFreeMove = true
	Actor_24H_weapon2proj2.PhysicDesc.Filename = ""
	Actor_24H_weapon2proj2:SetPhysicalActorType(3)
	Actor_24H_weapon2proj2:SetPhysicalShape(4)
	Actor_24H_weapon2proj2.UsableMode = ""
	Actor_24H_weapon2proj2.Power = 10
	Actor_24H_weapon2proj2.UseMana = 0
	Actor_24H_weapon2proj2.OffsetX = 2.5
	Actor_24H_weapon2proj2.OffsetY = 2.5
	Actor_24H_weapon2proj2.OffsetZ = 0
	Actor_24H_weapon2proj2.ForceX = 0.0005
	Actor_24H_weapon2proj2.ForceY = -0.0002
	Actor_24H_weapon2proj2.ForceYOnImpact = 0
	Actor_24H_weapon2proj2.NbBounce = 1
	Actor_24H_weapon2proj2.IgnoreGravity = true
	Actor_24H_weapon2proj2.LifeTime = 4000
	Actor_24H_weapon2proj2.Comeback = false
	Actor_24H_weapon2proj2.StartAnimFrame = 4
	Actor_24H_weapon2proj2.AngleOffset = -4
	Actor_24H_weapon2proj2.SoundAtStart = ""
	Actor_24H_weapon2proj2.SoundOnBounce = ""
	Actor_24H_weapon2proj2.ForceHurt = false
	Actor_24H_weapon2proj2.MultiShoot = false
	Actor_24H_weapon2proj2.UseTimer = false
	Actor_24H_weapon2proj2.Frequency = 1
	Actor_24H_weapon2proj2.FollowTarget = false
	Actor_24H:AddProjectileWeapon2(Actor_24H_weapon2proj2)
	Actor_24H:SetAttackFunction("ActorRotateAttackDistanceAndContactPlayer")
	Actor_24H:AddGivenItem(1,1,1,0.3,1)
	Actor_24H:AddGivenItem(2,1,1,0.3,1)
	Actor_24H:AddGivenItem(8,2,2,0.4,1)
	Actor_24H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_24H)

	Actor_25 = ActorObjectInfo(25)
	Actor_25:SetRenderType(3)
	Actor_25.HitPowerOnTouch = -1
	Actor_25.ExcludeFromNavMesh = false
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
	Actor_25.DisplayDesc.UseBillboard = false
	Actor_25.DisplayDesc.ColorMaterialType = 4
	Actor_25.DisplayDesc.MatAmbientColorR = -0.2
	Actor_25.DisplayDesc.MatAmbientColorG = -0.2
	Actor_25.DisplayDesc.MatAmbientColorB = -0.2
	Actor_25.DisplayDesc.MatAmbientColorA = 1
	Actor_25.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_25.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_25.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_25.DisplayDesc.MatDiffuseColorA = 1
	Actor_25.DisplayDesc.MatSpecularColorR = 0
	Actor_25.DisplayDesc.MatSpecularColorG = 0
	Actor_25.DisplayDesc.MatSpecularColorB = 0
	Actor_25.DisplayDesc.MatSpecularColorA = 1
	Actor_25.DisplayDesc.MatEmissionColorR = 0
	Actor_25.DisplayDesc.MatEmissionColorG = 0
	Actor_25.DisplayDesc.MatEmissionColorB = 0
	Actor_25.DisplayDesc.MatEmissionColorA = 1
	Actor_25.DisplayDesc.MatShininess = 0
	Actor_25.PhysicDesc.Pos.X = 34.4
	Actor_25.PhysicDesc.Pos.Y = 6
	Actor_25.PhysicDesc.Pos.Z = 47.6
	Actor_25.PhysicDesc.Pos.Rotation = 25
	Actor_25.PhysicDesc.Density = 1
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 2
	Actor_25.PhysicDesc.SizeY = 5
	Actor_25.PhysicDesc.SizeZ = 2
	Actor_25.PhysicDesc.AllowFreeMove = true
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
	Actor_25H:SetAggresive(true)
	Actor_25H:SetLife(50)
	Actor_25H:SetMana(0)
	Actor_25H:SetArmor(0)
	Actor_25H:SetAttackActiDist(7)
	Actor_25H:SetAttackActiDistDiscrete(4)
	Actor_25H:SetAttackActiDistHidden(2)
	Actor_25H:SetAttackStopDist(10)
	Actor_25H:SetRespawnTimeInSec(10)
	Actor_25H:SetWeapon1Type(1)
	Actor_25H:SetWeapon1Power(10)
	Actor_25H:SetWeapon1ReachDistance(2)
	Actor_25H:Setuseweapon1animation("Use1Weapon")
	Actor_25H:SetWeapon2Type(2)
	Actor_25H:SetWeapon2Power(0)
	Actor_25H:SetWeapon2ReachDistance(7)
	Actor_25H:Setuseweapon2animation("UseWeapon")
	Actor_25H_weapon2proj0 = ProjectileObjectDef()
	Actor_25H_weapon2proj0:SetRenderType(2)
	Actor_25H_weapon2proj0.DisplayDesc.ModelId = 0
	Actor_25H_weapon2proj0.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_25H_weapon2proj0.DisplayDesc.Outfit = ""
	Actor_25H_weapon2proj0.DisplayDesc.Weapon = ""
	Actor_25H_weapon2proj0.DisplayDesc.Mode = ""
	Actor_25H_weapon2proj0.DisplayDesc.UseLight = true
	Actor_25H_weapon2proj0.DisplayDesc.CastShadow = true
	Actor_25H_weapon2proj0.DisplayDesc.ColorR = 1
	Actor_25H_weapon2proj0.DisplayDesc.ColorG = 1
	Actor_25H_weapon2proj0.DisplayDesc.ColorB = 1
	Actor_25H_weapon2proj0.DisplayDesc.ColorA = 0.9
	Actor_25H_weapon2proj0.DisplayDesc.TransX = 0
	Actor_25H_weapon2proj0.DisplayDesc.TransY = 0
	Actor_25H_weapon2proj0.DisplayDesc.TransZ = 0
	Actor_25H_weapon2proj0.DisplayDesc.ScaleX = 0.05
	Actor_25H_weapon2proj0.DisplayDesc.ScaleY = 0.05
	Actor_25H_weapon2proj0.DisplayDesc.ScaleZ = 0.05
	Actor_25H_weapon2proj0.DisplayDesc.RotX = 0
	Actor_25H_weapon2proj0.DisplayDesc.RotY = 0
	Actor_25H_weapon2proj0.DisplayDesc.RotZ = 0
	Actor_25H_weapon2proj0.DisplayDesc.UseBillboard = true
	Actor_25H_weapon2proj0.PhysicDesc.Pos.X = 0
	Actor_25H_weapon2proj0.PhysicDesc.Pos.Y = 0
	Actor_25H_weapon2proj0.PhysicDesc.Pos.Z = 0
	Actor_25H_weapon2proj0.PhysicDesc.Pos.Rotation = 0
	Actor_25H_weapon2proj0.PhysicDesc.Density = 1
	Actor_25H_weapon2proj0.PhysicDesc.Collidable = false
	Actor_25H_weapon2proj0.PhysicDesc.SizeX = 0.05
	Actor_25H_weapon2proj0.PhysicDesc.SizeY = 0.05
	Actor_25H_weapon2proj0.PhysicDesc.SizeZ = 0.05
	Actor_25H_weapon2proj0.PhysicDesc.AllowFreeMove = true
	Actor_25H_weapon2proj0.PhysicDesc.Filename = ""
	Actor_25H_weapon2proj0:SetPhysicalActorType(3)
	Actor_25H_weapon2proj0:SetPhysicalShape(4)
	Actor_25H_weapon2proj0.UsableMode = ""
	Actor_25H_weapon2proj0.Power = 10
	Actor_25H_weapon2proj0.UseMana = 0
	Actor_25H_weapon2proj0.OffsetX = 2.5
	Actor_25H_weapon2proj0.OffsetY = 2.5
	Actor_25H_weapon2proj0.OffsetZ = 0
	Actor_25H_weapon2proj0.ForceX = 0.0005
	Actor_25H_weapon2proj0.ForceY = -0.0002
	Actor_25H_weapon2proj0.ForceYOnImpact = 0
	Actor_25H_weapon2proj0.NbBounce = 1
	Actor_25H_weapon2proj0.IgnoreGravity = true
	Actor_25H_weapon2proj0.LifeTime = 4000
	Actor_25H_weapon2proj0.Comeback = false
	Actor_25H_weapon2proj0.StartAnimFrame = 4
	Actor_25H_weapon2proj0.AngleOffset = 0
	Actor_25H_weapon2proj0.SoundAtStart = "Worlds/Lba1Original/Sound/SAMPLES027.voc.MP3"
	Actor_25H_weapon2proj0.SoundOnBounce = ""
	Actor_25H_weapon2proj0.ForceHurt = false
	Actor_25H_weapon2proj0.MultiShoot = false
	Actor_25H_weapon2proj0.UseTimer = false
	Actor_25H_weapon2proj0.Frequency = 1
	Actor_25H_weapon2proj0.FollowTarget = false
	Actor_25H:AddProjectileWeapon2(Actor_25H_weapon2proj0)
	Actor_25H_weapon2proj1 = ProjectileObjectDef()
	Actor_25H_weapon2proj1:SetRenderType(2)
	Actor_25H_weapon2proj1.DisplayDesc.ModelId = 0
	Actor_25H_weapon2proj1.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_25H_weapon2proj1.DisplayDesc.Outfit = ""
	Actor_25H_weapon2proj1.DisplayDesc.Weapon = ""
	Actor_25H_weapon2proj1.DisplayDesc.Mode = ""
	Actor_25H_weapon2proj1.DisplayDesc.UseLight = true
	Actor_25H_weapon2proj1.DisplayDesc.CastShadow = true
	Actor_25H_weapon2proj1.DisplayDesc.ColorR = 1
	Actor_25H_weapon2proj1.DisplayDesc.ColorG = 1
	Actor_25H_weapon2proj1.DisplayDesc.ColorB = 1
	Actor_25H_weapon2proj1.DisplayDesc.ColorA = 0.9
	Actor_25H_weapon2proj1.DisplayDesc.TransX = 0
	Actor_25H_weapon2proj1.DisplayDesc.TransY = 0
	Actor_25H_weapon2proj1.DisplayDesc.TransZ = 0
	Actor_25H_weapon2proj1.DisplayDesc.ScaleX = 0.05
	Actor_25H_weapon2proj1.DisplayDesc.ScaleY = 0.05
	Actor_25H_weapon2proj1.DisplayDesc.ScaleZ = 0.05
	Actor_25H_weapon2proj1.DisplayDesc.RotX = 0
	Actor_25H_weapon2proj1.DisplayDesc.RotY = 0
	Actor_25H_weapon2proj1.DisplayDesc.RotZ = 0
	Actor_25H_weapon2proj1.DisplayDesc.UseBillboard = true
	Actor_25H_weapon2proj1.PhysicDesc.Pos.X = 0
	Actor_25H_weapon2proj1.PhysicDesc.Pos.Y = 0
	Actor_25H_weapon2proj1.PhysicDesc.Pos.Z = 0
	Actor_25H_weapon2proj1.PhysicDesc.Pos.Rotation = 0
	Actor_25H_weapon2proj1.PhysicDesc.Density = 1
	Actor_25H_weapon2proj1.PhysicDesc.Collidable = false
	Actor_25H_weapon2proj1.PhysicDesc.SizeX = 0.05
	Actor_25H_weapon2proj1.PhysicDesc.SizeY = 0.05
	Actor_25H_weapon2proj1.PhysicDesc.SizeZ = 0.05
	Actor_25H_weapon2proj1.PhysicDesc.AllowFreeMove = true
	Actor_25H_weapon2proj1.PhysicDesc.Filename = ""
	Actor_25H_weapon2proj1:SetPhysicalActorType(3)
	Actor_25H_weapon2proj1:SetPhysicalShape(4)
	Actor_25H_weapon2proj1.UsableMode = ""
	Actor_25H_weapon2proj1.Power = 10
	Actor_25H_weapon2proj1.UseMana = 0
	Actor_25H_weapon2proj1.OffsetX = 2.5
	Actor_25H_weapon2proj1.OffsetY = 2.5
	Actor_25H_weapon2proj1.OffsetZ = 0
	Actor_25H_weapon2proj1.ForceX = 0.0005
	Actor_25H_weapon2proj1.ForceY = -0.0002
	Actor_25H_weapon2proj1.ForceYOnImpact = 0
	Actor_25H_weapon2proj1.NbBounce = 1
	Actor_25H_weapon2proj1.IgnoreGravity = true
	Actor_25H_weapon2proj1.LifeTime = 4000
	Actor_25H_weapon2proj1.Comeback = false
	Actor_25H_weapon2proj1.StartAnimFrame = 4
	Actor_25H_weapon2proj1.AngleOffset = 4
	Actor_25H_weapon2proj1.SoundAtStart = ""
	Actor_25H_weapon2proj1.SoundOnBounce = ""
	Actor_25H_weapon2proj1.ForceHurt = false
	Actor_25H_weapon2proj1.MultiShoot = false
	Actor_25H_weapon2proj1.UseTimer = false
	Actor_25H_weapon2proj1.Frequency = 1
	Actor_25H_weapon2proj1.FollowTarget = false
	Actor_25H:AddProjectileWeapon2(Actor_25H_weapon2proj1)
	Actor_25H_weapon2proj2 = ProjectileObjectDef()
	Actor_25H_weapon2proj2:SetRenderType(2)
	Actor_25H_weapon2proj2.DisplayDesc.ModelId = 0
	Actor_25H_weapon2proj2.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_25H_weapon2proj2.DisplayDesc.Outfit = ""
	Actor_25H_weapon2proj2.DisplayDesc.Weapon = ""
	Actor_25H_weapon2proj2.DisplayDesc.Mode = ""
	Actor_25H_weapon2proj2.DisplayDesc.UseLight = true
	Actor_25H_weapon2proj2.DisplayDesc.CastShadow = true
	Actor_25H_weapon2proj2.DisplayDesc.ColorR = 1
	Actor_25H_weapon2proj2.DisplayDesc.ColorG = 1
	Actor_25H_weapon2proj2.DisplayDesc.ColorB = 1
	Actor_25H_weapon2proj2.DisplayDesc.ColorA = 0.9
	Actor_25H_weapon2proj2.DisplayDesc.TransX = 0
	Actor_25H_weapon2proj2.DisplayDesc.TransY = 0
	Actor_25H_weapon2proj2.DisplayDesc.TransZ = 0
	Actor_25H_weapon2proj2.DisplayDesc.ScaleX = 0.05
	Actor_25H_weapon2proj2.DisplayDesc.ScaleY = 0.05
	Actor_25H_weapon2proj2.DisplayDesc.ScaleZ = 0.05
	Actor_25H_weapon2proj2.DisplayDesc.RotX = 0
	Actor_25H_weapon2proj2.DisplayDesc.RotY = 0
	Actor_25H_weapon2proj2.DisplayDesc.RotZ = 0
	Actor_25H_weapon2proj2.DisplayDesc.UseBillboard = true
	Actor_25H_weapon2proj2.PhysicDesc.Pos.X = 0
	Actor_25H_weapon2proj2.PhysicDesc.Pos.Y = 0
	Actor_25H_weapon2proj2.PhysicDesc.Pos.Z = 0
	Actor_25H_weapon2proj2.PhysicDesc.Pos.Rotation = 0
	Actor_25H_weapon2proj2.PhysicDesc.Density = 1
	Actor_25H_weapon2proj2.PhysicDesc.Collidable = false
	Actor_25H_weapon2proj2.PhysicDesc.SizeX = 0.05
	Actor_25H_weapon2proj2.PhysicDesc.SizeY = 0.05
	Actor_25H_weapon2proj2.PhysicDesc.SizeZ = 0.05
	Actor_25H_weapon2proj2.PhysicDesc.AllowFreeMove = true
	Actor_25H_weapon2proj2.PhysicDesc.Filename = ""
	Actor_25H_weapon2proj2:SetPhysicalActorType(3)
	Actor_25H_weapon2proj2:SetPhysicalShape(4)
	Actor_25H_weapon2proj2.UsableMode = ""
	Actor_25H_weapon2proj2.Power = 10
	Actor_25H_weapon2proj2.UseMana = 0
	Actor_25H_weapon2proj2.OffsetX = 2.5
	Actor_25H_weapon2proj2.OffsetY = 2.5
	Actor_25H_weapon2proj2.OffsetZ = 0
	Actor_25H_weapon2proj2.ForceX = 0.0005
	Actor_25H_weapon2proj2.ForceY = -0.0002
	Actor_25H_weapon2proj2.ForceYOnImpact = 0
	Actor_25H_weapon2proj2.NbBounce = 1
	Actor_25H_weapon2proj2.IgnoreGravity = true
	Actor_25H_weapon2proj2.LifeTime = 4000
	Actor_25H_weapon2proj2.Comeback = false
	Actor_25H_weapon2proj2.StartAnimFrame = 4
	Actor_25H_weapon2proj2.AngleOffset = -4
	Actor_25H_weapon2proj2.SoundAtStart = ""
	Actor_25H_weapon2proj2.SoundOnBounce = ""
	Actor_25H_weapon2proj2.ForceHurt = false
	Actor_25H_weapon2proj2.MultiShoot = false
	Actor_25H_weapon2proj2.UseTimer = false
	Actor_25H_weapon2proj2.Frequency = 1
	Actor_25H_weapon2proj2.FollowTarget = false
	Actor_25H:AddProjectileWeapon2(Actor_25H_weapon2proj2)
	Actor_25H:SetAttackFunction("ActorRotateAttackDistanceAndContactPlayer")
	Actor_25H:AddGivenItem(1,1,1,0.3,1)
	Actor_25H:AddGivenItem(2,1,1,0.3,1)
	Actor_25H:AddGivenItem(8,2,2,0.4,1)
	Actor_25H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_25H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 11, 3.5, 1, true)
	Trigger_1:SetPosition(32.5, 0, 63.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1:SetActivateOnJump(true)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map003_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 4.5, 5, true)
	Trigger_2:SetPosition(35.5, 2, 15.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2:SetActivateOnJump(true)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map000_1")
	Trigger_2_act1:SetSpawning(2)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit14", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 4.5, 1, true)
	Trigger_3:SetPosition(53, -1, 45.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3:SetActivateOnJump(true)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map000_1")
	Trigger_3_act1:SetSpawning(3)
	Trigger_3:SetAction1(Trigger_3_act1)
	Trigger_3_act2 = CloseDoorAction()
	Trigger_3_act2:SetActorId(10)
	Trigger_3:SetAction2(Trigger_3_act2)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit9", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 3, 4.5, 1, true)
	Trigger_4:SetPosition(22.5, 0, 55.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4:SetActivateOnJump(true)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map016_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "TextTri_5", true, false, false)
	Trigger_5 = ActivationTrigger(Trigger_5_info, 2, "Normal", "")
	Trigger_5:SetPosition(14.999, 0, 56)
	Trigger_5_act1 = DisplayTextAction()
	Trigger_5_act1:SetTextId(177)
	Trigger_5:SetAction1(Trigger_5_act1)
	Trigger_5:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "TextTri_6", true, false, false)
	Trigger_6 = ActivationTrigger(Trigger_6_info, 2, "Normal", "")
	Trigger_6:SetPosition(11.999, 0, 56)
	Trigger_6_act1 = DisplayTextAction()
	Trigger_6_act1:SetTextId(193)
	Trigger_6:SetAction1(Trigger_6_act1)
	Trigger_6:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "ContainerTri_7", true, false, false)
	Trigger_7 = ZoneActionTrigger(Trigger_7_info, 1.5332, 2.63281, 1.81445, "Normal", "")
	Trigger_7:SetPosition(1.73535, 1, 51.626)
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
	Trigger_8 = ZoneActionTrigger(Trigger_8_info, 1.78516, 3.44922, 1.91016, "Normal", "")
	Trigger_8:SetPosition(3.23633, 0, 58.9863)
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
	Trigger_9 = ZoneActionTrigger(Trigger_9_info, 2.3418, 4.49609, 2.2168, "Normal", "")
	Trigger_9:SetPosition(50.4834, 0, 48.6709)
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

	Trigger_10_info = TriggerInfo(10, "TextTri_10", true, false, false)
	Trigger_10 = ActivationTrigger(Trigger_10_info, 2, "Normal", "")
	Trigger_10:SetPosition(54.999, 0, 46)
	Trigger_10_act1 = DisplayTextAction()
	Trigger_10_act1:SetTextId(223)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "ContainerTri_11", true, false, false)
	Trigger_11 = ZoneActionTrigger(Trigger_11_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_11:SetPosition(42.999, 2, 9.99902)
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

	Trigger_12_info = TriggerInfo(12, "ExitUpTri_12", true, false, false)
	Trigger_12 = ActivationTrigger(Trigger_12_info, 2, "Normal", "")
	Trigger_12:SetPosition(53, 0, 46)
	Trigger_12_act1 = MultiAction()
	Trigger_12_act1_act0 = OpenDoorAction()
	Trigger_12_act1_act0:SetActorId(10)
	Trigger_12_act1:AddAction(Trigger_12_act1_act0)
	Trigger_12_act1_act1 = ClientScriptAction()
	Trigger_12_act1_act1_cs = TakeExitUpScript()
	Trigger_12_act1_act1_cs:SetExitPositionX(53)
	Trigger_12_act1_act1_cs:SetExitPositionY(0)
	Trigger_12_act1_act1_cs:SetExitPositionZ(46)
	Trigger_12_act1_act1_cs:SetExitDirection(180)
	Trigger_12_act1_act1:SetScript(Trigger_12_act1_act1_cs)
	Trigger_12_act1:AddAction(Trigger_12_act1_act1)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "DoorTri_13", true, false, false)
	Trigger_13 = ZoneTrigger(Trigger_13_info, 0, 0, 0, false)
	Trigger_13:SetPosition(53, 2, 45.8)
	Trigger_13:SetStayUpdateFrequency(-1)
	Trigger_13:SetActivateOnJump(true)
	Trigger_13_act1 = OpenDoorAction()
	Trigger_13_act1:SetActorId(10)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13_act2 = CloseDoorAction()
	Trigger_13_act2:SetActorId(10)
	Trigger_13:SetAction2(Trigger_13_act2)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "DoorTri_14", true, false, false)
	Trigger_14 = ZoneTrigger(Trigger_14_info, 4, 8, 4, false)
	Trigger_14:SetPosition(22.5, 0, 55.4)
	Trigger_14:SetStayUpdateFrequency(-1)
	Trigger_14:SetActivateOnJump(true)
	Trigger_14_act1 = OpenDoorAction()
	Trigger_14_act1:SetActorId(11)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14_act2 = CloseDoorAction()
	Trigger_14_act2:SetActorId(11)
	Trigger_14:SetAction2(Trigger_14_act2)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "DoorTri_15", true, false, false)
	Trigger_15 = ZoneTrigger(Trigger_15_info, 6, 5, 5, false)
	Trigger_15:SetPosition(31, 6, 40.5)
	Trigger_15:SetStayUpdateFrequency(-1)
	Trigger_15:SetActivateOnJump(true)
	Trigger_15_act1 = MultiAction()
	Trigger_15_act1_act0 = OpenDoorAction()
	Trigger_15_act1_act0:SetActorId(12)
	Trigger_15_act1:AddAction(Trigger_15_act1_act0)
	Trigger_15_act1_act1 = OpenDoorAction()
	Trigger_15_act1_act1:SetActorId(13)
	Trigger_15_act1:AddAction(Trigger_15_act1_act1)
	Trigger_15:SetAction1(Trigger_15_act1)
	Trigger_15_act2 = MultiAction()
	Trigger_15_act2_act0 = CloseDoorAction()
	Trigger_15_act2_act0:SetActorId(12)
	Trigger_15_act2:AddAction(Trigger_15_act2_act0)
	Trigger_15_act2_act1 = CloseDoorAction()
	Trigger_15_act2_act1:SetActorId(13)
	Trigger_15_act2:AddAction(Trigger_15_act2_act1)
	Trigger_15:SetAction2(Trigger_15_act2)
	environment:AddTrigger(Trigger_15)

	Trigger_17_info = TriggerInfo(17, "DoorTri_17", true, false, false)
	Trigger_17 = ZoneTrigger(Trigger_17_info, 4, 8, 5, false)
	Trigger_17:SetPosition(36, 2, 15.5)
	Trigger_17:SetStayUpdateFrequency(-1)
	Trigger_17:SetActivateOnJump(true)
	Trigger_17_act1 = MultiAction()
	Trigger_17_act1_act0 = OpenDoorAction()
	Trigger_17_act1_act0:SetActorId(14)
	Trigger_17_act1:AddAction(Trigger_17_act1_act0)
	Trigger_17_act1_act1 = OpenDoorAction()
	Trigger_17_act1_act1:SetActorId(15)
	Trigger_17_act1:AddAction(Trigger_17_act1_act1)
	Trigger_17:SetAction1(Trigger_17_act1)
	Trigger_17_act2 = MultiAction()
	Trigger_17_act2_act0 = CloseDoorAction()
	Trigger_17_act2_act0:SetActorId(14)
	Trigger_17_act2:AddAction(Trigger_17_act2_act0)
	Trigger_17_act2_act1 = CloseDoorAction()
	Trigger_17_act2_act1:SetActorId(15)
	Trigger_17_act2:AddAction(Trigger_17_act2_act1)
	Trigger_17:SetAction2(Trigger_17_act2)
	environment:AddTrigger(Trigger_17)

	Trigger_18_info = TriggerInfo(18, "gototrashtrigger", true, true, false)
	Trigger_18 = ActivationTrigger(Trigger_18_info, 2.4, "Discrete", "None")
	Trigger_18:SetPosition(53.7, 8, 13.5)
	Trigger_18_act1 = ClientScriptAction()
	Trigger_18_act1_cs = CustomScript()
	Trigger_18_act1_cs:SetLuaFunctionName("UseTrashTruck")
	Trigger_18_act1:SetScript(Trigger_18_act1_cs)
	Trigger_18:SetAction1(Trigger_18_act1)
	Trigger_18:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_18)

end
