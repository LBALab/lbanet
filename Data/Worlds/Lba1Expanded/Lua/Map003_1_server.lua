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
	Actor_1.HitPowerOnTouch = -1
	Actor_1.ExcludeFromNavMesh = false
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
	Actor_1.PhysicDesc.AllowFreeMove = false
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
	Actor_12.HitPowerOnTouch = -1
	Actor_12.ExcludeFromNavMesh = false
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
	Actor_12.DisplayDesc.UseBillboard = false
	Actor_12.PhysicDesc.Pos.X = 10.5
	Actor_12.PhysicDesc.Pos.Y = 7
	Actor_12.PhysicDesc.Pos.Z = 11.4
	Actor_12.PhysicDesc.Pos.Rotation = 0
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 3.2
	Actor_12.PhysicDesc.SizeY = 8
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
	Actor_13.HitPowerOnTouch = -1
	Actor_13.ExcludeFromNavMesh = false
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
	Actor_13.DisplayDesc.UseBillboard = false
	Actor_13.PhysicDesc.Pos.X = 18.5
	Actor_13.PhysicDesc.Pos.Y = 0
	Actor_13.PhysicDesc.Pos.Z = 28.5
	Actor_13.PhysicDesc.Pos.Rotation = 0
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 1
	Actor_13.PhysicDesc.SizeY = 8
	Actor_13.PhysicDesc.SizeZ = 3.2
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
	Actor_14.HitPowerOnTouch = -1
	Actor_14.ExcludeFromNavMesh = false
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
	Actor_14.DisplayDesc.UseBillboard = false
	Actor_14.PhysicDesc.Pos.X = 15.5
	Actor_14.PhysicDesc.Pos.Y = 0
	Actor_14.PhysicDesc.Pos.Z = 41.5
	Actor_14.PhysicDesc.Pos.Rotation = 0
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 1
	Actor_14.PhysicDesc.SizeY = 8
	Actor_14.PhysicDesc.SizeZ = 3.2
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
	Actor_15.HitPowerOnTouch = -1
	Actor_15.ExcludeFromNavMesh = false
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
	Actor_15.DisplayDesc.UseBillboard = false
	Actor_15.PhysicDesc.Pos.X = 2.5
	Actor_15.PhysicDesc.Pos.Y = 5
	Actor_15.PhysicDesc.Pos.Z = 63.5
	Actor_15.PhysicDesc.Pos.Rotation = 0
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 3.2
	Actor_15.PhysicDesc.SizeY = 5
	Actor_15.PhysicDesc.SizeZ = 1
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
	Actor_16.HitPowerOnTouch = -1
	Actor_16.ExcludeFromNavMesh = false
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
	Actor_16.DisplayDesc.UseBillboard = false
	Actor_16.PhysicDesc.Pos.X = 38
	Actor_16.PhysicDesc.Pos.Y = 14
	Actor_16.PhysicDesc.Pos.Z = 7
	Actor_16.PhysicDesc.Pos.Rotation = 0
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 2
	Actor_16.PhysicDesc.SizeY = 1
	Actor_16.PhysicDesc.SizeZ = 2
	Actor_16.PhysicDesc.AllowFreeMove = false
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

	Actor_19 = ActorObjectInfo(19)
	Actor_19:SetRenderType(3)
	Actor_19.HitPowerOnTouch = -1
	Actor_19.ExcludeFromNavMesh = false
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
	Actor_19.DisplayDesc.UseBillboard = false
	Actor_19.DisplayDesc.ColorMaterialType = 4
	Actor_19.DisplayDesc.MatAmbientColorR = -0.2
	Actor_19.DisplayDesc.MatAmbientColorG = -0.2
	Actor_19.DisplayDesc.MatAmbientColorB = -0.2
	Actor_19.DisplayDesc.MatAmbientColorA = 1
	Actor_19.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_19.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_19.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_19.DisplayDesc.MatDiffuseColorA = 1
	Actor_19.DisplayDesc.MatSpecularColorR = 0
	Actor_19.DisplayDesc.MatSpecularColorG = 0
	Actor_19.DisplayDesc.MatSpecularColorB = 0
	Actor_19.DisplayDesc.MatSpecularColorA = 1
	Actor_19.DisplayDesc.MatEmissionColorR = 0
	Actor_19.DisplayDesc.MatEmissionColorG = 0
	Actor_19.DisplayDesc.MatEmissionColorB = 0
	Actor_19.DisplayDesc.MatEmissionColorA = 1
	Actor_19.DisplayDesc.MatShininess = 0
	Actor_19.PhysicDesc.Pos.X = 53.6406
	Actor_19.PhysicDesc.Pos.Y = 0
	Actor_19.PhysicDesc.Pos.Z = 8
	Actor_19.PhysicDesc.Pos.Rotation = 25
	Actor_19.PhysicDesc.Density = 1
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = 2
	Actor_19.PhysicDesc.SizeY = 5
	Actor_19.PhysicDesc.SizeZ = 2
	Actor_19.PhysicDesc.AllowFreeMove = false
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
	Actor_20.HitPowerOnTouch = -1
	Actor_20.ExcludeFromNavMesh = false
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
	Actor_20.DisplayDesc.UseBillboard = false
	Actor_20.DisplayDesc.ColorMaterialType = 4
	Actor_20.DisplayDesc.MatAmbientColorR = -0.2
	Actor_20.DisplayDesc.MatAmbientColorG = -0.2
	Actor_20.DisplayDesc.MatAmbientColorB = -0.2
	Actor_20.DisplayDesc.MatAmbientColorA = 1
	Actor_20.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_20.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_20.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_20.DisplayDesc.MatDiffuseColorA = 1
	Actor_20.DisplayDesc.MatSpecularColorR = 0
	Actor_20.DisplayDesc.MatSpecularColorG = 0
	Actor_20.DisplayDesc.MatSpecularColorB = 0
	Actor_20.DisplayDesc.MatSpecularColorA = 1
	Actor_20.DisplayDesc.MatEmissionColorR = 0
	Actor_20.DisplayDesc.MatEmissionColorG = 0
	Actor_20.DisplayDesc.MatEmissionColorB = 0
	Actor_20.DisplayDesc.MatEmissionColorA = 1
	Actor_20.DisplayDesc.MatShininess = 0
	Actor_20.PhysicDesc.Pos.X = 51
	Actor_20.PhysicDesc.Pos.Y = 0
	Actor_20.PhysicDesc.Pos.Z = 11
	Actor_20.PhysicDesc.Pos.Rotation = 25
	Actor_20.PhysicDesc.Density = 1
	Actor_20.PhysicDesc.Collidable = true
	Actor_20.PhysicDesc.SizeX = 1.5
	Actor_20.PhysicDesc.SizeY = 5
	Actor_20.PhysicDesc.SizeZ = 1.5
	Actor_20.PhysicDesc.AllowFreeMove = false
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
	Actor_21.HitPowerOnTouch = -1
	Actor_21.ExcludeFromNavMesh = false
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
	Actor_21.PhysicDesc.Pos.X = 19
	Actor_21.PhysicDesc.Pos.Y = 1
	Actor_21.PhysicDesc.Pos.Z = 49
	Actor_21.PhysicDesc.Pos.Rotation = 25
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 1
	Actor_21.PhysicDesc.SizeY = 6
	Actor_21.PhysicDesc.SizeZ = 1
	Actor_21.PhysicDesc.AllowFreeMove = false
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

	Actor_23 = ActorObjectInfo(23)
	Actor_23:SetRenderType(3)
	Actor_23.HitPowerOnTouch = -1
	Actor_23.ExcludeFromNavMesh = false
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
	Actor_23.PhysicDesc.Pos.X = 12
	Actor_23.PhysicDesc.Pos.Y = 7
	Actor_23.PhysicDesc.Pos.Z = 12.7813
	Actor_23.PhysicDesc.Pos.Rotation = 628
	Actor_23.PhysicDesc.Density = 1
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 1
	Actor_23.PhysicDesc.SizeY = 5
	Actor_23.PhysicDesc.SizeZ = 1
	Actor_23.PhysicDesc.AllowFreeMove = false
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
	Actor_24.HitPowerOnTouch = -1
	Actor_24.ExcludeFromNavMesh = false
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
	Actor_24.PhysicDesc.Pos.X = 34
	Actor_24.PhysicDesc.Pos.Y = 0
	Actor_24.PhysicDesc.Pos.Z = 40
	Actor_24.PhysicDesc.Pos.Rotation = 25
	Actor_24.PhysicDesc.Density = 1
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 2
	Actor_24.PhysicDesc.SizeY = 5
	Actor_24.PhysicDesc.SizeZ = 4
	Actor_24.PhysicDesc.AllowFreeMove = false
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

	Actor_26 = ActorObjectInfo(26)
	Actor_26:SetRenderType(3)
	Actor_26.HitPowerOnTouch = -1
	Actor_26.ExcludeFromNavMesh = false
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
	Actor_26.DisplayDesc.UseBillboard = false
	Actor_26.DisplayDesc.ColorMaterialType = 4
	Actor_26.DisplayDesc.MatAmbientColorR = -0.2
	Actor_26.DisplayDesc.MatAmbientColorG = -0.2
	Actor_26.DisplayDesc.MatAmbientColorB = -0.2
	Actor_26.DisplayDesc.MatAmbientColorA = 1
	Actor_26.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_26.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_26.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_26.DisplayDesc.MatDiffuseColorA = 1
	Actor_26.DisplayDesc.MatSpecularColorR = 0
	Actor_26.DisplayDesc.MatSpecularColorG = 0
	Actor_26.DisplayDesc.MatSpecularColorB = 0
	Actor_26.DisplayDesc.MatSpecularColorA = 1
	Actor_26.DisplayDesc.MatEmissionColorR = 0
	Actor_26.DisplayDesc.MatEmissionColorG = 0
	Actor_26.DisplayDesc.MatEmissionColorB = 0
	Actor_26.DisplayDesc.MatEmissionColorA = 1
	Actor_26.DisplayDesc.MatShininess = 0
	Actor_26.PhysicDesc.Pos.X = 19.875
	Actor_26.PhysicDesc.Pos.Y = 0
	Actor_26.PhysicDesc.Pos.Z = 32.375
	Actor_26.PhysicDesc.Pos.Rotation = 221
	Actor_26.PhysicDesc.Density = 1
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 1
	Actor_26.PhysicDesc.SizeY = 5
	Actor_26.PhysicDesc.SizeZ = 1
	Actor_26.PhysicDesc.AllowFreeMove = false
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

	Actor_29 = ActorObjectInfo(29)
	Actor_29:SetRenderType(3)
	Actor_29.HitPowerOnTouch = -1
	Actor_29.ExcludeFromNavMesh = false
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
	Actor_29.DisplayDesc.UseBillboard = false
	Actor_29.DisplayDesc.ColorMaterialType = 4
	Actor_29.DisplayDesc.MatAmbientColorR = -0.2
	Actor_29.DisplayDesc.MatAmbientColorG = -0.2
	Actor_29.DisplayDesc.MatAmbientColorB = -0.2
	Actor_29.DisplayDesc.MatAmbientColorA = 1
	Actor_29.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_29.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_29.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_29.DisplayDesc.MatDiffuseColorA = 1
	Actor_29.DisplayDesc.MatSpecularColorR = 0
	Actor_29.DisplayDesc.MatSpecularColorG = 0
	Actor_29.DisplayDesc.MatSpecularColorB = 0
	Actor_29.DisplayDesc.MatSpecularColorA = 1
	Actor_29.DisplayDesc.MatEmissionColorR = 0
	Actor_29.DisplayDesc.MatEmissionColorG = 0
	Actor_29.DisplayDesc.MatEmissionColorB = 0
	Actor_29.DisplayDesc.MatEmissionColorA = 1
	Actor_29.DisplayDesc.MatShininess = 0
	Actor_29.PhysicDesc.Pos.X = 19
	Actor_29.PhysicDesc.Pos.Y = 1
	Actor_29.PhysicDesc.Pos.Z = 49
	Actor_29.PhysicDesc.Pos.Rotation = 25
	Actor_29.PhysicDesc.Density = 1
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 1.5
	Actor_29.PhysicDesc.SizeY = 5
	Actor_29.PhysicDesc.SizeZ = 1.5
	Actor_29.PhysicDesc.AllowFreeMove = false
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
	Actor_30.HitPowerOnTouch = -1
	Actor_30.ExcludeFromNavMesh = false
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
	Actor_30.DisplayDesc.UseBillboard = false
	Actor_30.DisplayDesc.ColorMaterialType = 4
	Actor_30.DisplayDesc.MatAmbientColorR = -0.2
	Actor_30.DisplayDesc.MatAmbientColorG = -0.2
	Actor_30.DisplayDesc.MatAmbientColorB = -0.2
	Actor_30.DisplayDesc.MatAmbientColorA = 1
	Actor_30.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_30.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_30.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_30.DisplayDesc.MatDiffuseColorA = 1
	Actor_30.DisplayDesc.MatSpecularColorR = 0
	Actor_30.DisplayDesc.MatSpecularColorG = 0
	Actor_30.DisplayDesc.MatSpecularColorB = 0
	Actor_30.DisplayDesc.MatSpecularColorA = 1
	Actor_30.DisplayDesc.MatEmissionColorR = 0
	Actor_30.DisplayDesc.MatEmissionColorG = 0
	Actor_30.DisplayDesc.MatEmissionColorB = 0
	Actor_30.DisplayDesc.MatEmissionColorA = 1
	Actor_30.DisplayDesc.MatShininess = 0
	Actor_30.PhysicDesc.Pos.X = 0
	Actor_30.PhysicDesc.Pos.Y = -1
	Actor_30.PhysicDesc.Pos.Z = 0
	Actor_30.PhysicDesc.Pos.Rotation = 25
	Actor_30.PhysicDesc.Density = 1
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 0.5
	Actor_30.PhysicDesc.SizeY = 2
	Actor_30.PhysicDesc.SizeZ = 0.6
	Actor_30.PhysicDesc.AllowFreeMove = false
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
	Actor_31.HitPowerOnTouch = -1
	Actor_31.ExcludeFromNavMesh = false
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
	Actor_31.DisplayDesc.UseBillboard = false
	Actor_31.DisplayDesc.ColorMaterialType = 4
	Actor_31.DisplayDesc.MatAmbientColorR = -0.2
	Actor_31.DisplayDesc.MatAmbientColorG = -0.2
	Actor_31.DisplayDesc.MatAmbientColorB = -0.2
	Actor_31.DisplayDesc.MatAmbientColorA = 1
	Actor_31.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_31.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_31.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_31.DisplayDesc.MatDiffuseColorA = 1
	Actor_31.DisplayDesc.MatSpecularColorR = 0
	Actor_31.DisplayDesc.MatSpecularColorG = 0
	Actor_31.DisplayDesc.MatSpecularColorB = 0
	Actor_31.DisplayDesc.MatSpecularColorA = 1
	Actor_31.DisplayDesc.MatEmissionColorR = 0
	Actor_31.DisplayDesc.MatEmissionColorG = 0
	Actor_31.DisplayDesc.MatEmissionColorB = 0
	Actor_31.DisplayDesc.MatEmissionColorA = 1
	Actor_31.DisplayDesc.MatShininess = 0
	Actor_31.PhysicDesc.Pos.X = 41
	Actor_31.PhysicDesc.Pos.Y = 7
	Actor_31.PhysicDesc.Pos.Z = 17
	Actor_31.PhysicDesc.Pos.Rotation = 25
	Actor_31.PhysicDesc.Density = 1
	Actor_31.PhysicDesc.Collidable = true
	Actor_31.PhysicDesc.SizeX = 2
	Actor_31.PhysicDesc.SizeY = 5
	Actor_31.PhysicDesc.SizeZ = 2
	Actor_31.PhysicDesc.AllowFreeMove = true
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
	Actor_31H:SetAggresive(true)
	Actor_31H:SetLife(50)
	Actor_31H:SetMana(0)
	Actor_31H:SetArmor(0)
	Actor_31H:SetAttackActiDist(7)
	Actor_31H:SetAttackActiDistDiscrete(4)
	Actor_31H:SetAttackActiDistHidden(2)
	Actor_31H:SetAttackStopDist(10)
	Actor_31H:SetRespawnTimeInSec(10)
	Actor_31H:SetWeapon1Type(1)
	Actor_31H:SetWeapon1Power(10)
	Actor_31H:SetWeapon1ReachDistance(2)
	Actor_31H:Setuseweapon1animation("Use1Weapon")
	Actor_31H:SetWeapon2Type(2)
	Actor_31H:SetWeapon2Power(0)
	Actor_31H:SetWeapon2ReachDistance(7)
	Actor_31H:Setuseweapon2animation("UseWeapon")
	Actor_31H_weapon2proj0 = ProjectileObjectDef()
	Actor_31H_weapon2proj0:SetRenderType(2)
	Actor_31H_weapon2proj0.DisplayDesc.ModelId = 0
	Actor_31H_weapon2proj0.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_31H_weapon2proj0.DisplayDesc.Outfit = ""
	Actor_31H_weapon2proj0.DisplayDesc.Weapon = ""
	Actor_31H_weapon2proj0.DisplayDesc.Mode = ""
	Actor_31H_weapon2proj0.DisplayDesc.UseLight = true
	Actor_31H_weapon2proj0.DisplayDesc.CastShadow = true
	Actor_31H_weapon2proj0.DisplayDesc.ColorR = 1
	Actor_31H_weapon2proj0.DisplayDesc.ColorG = 1
	Actor_31H_weapon2proj0.DisplayDesc.ColorB = 1
	Actor_31H_weapon2proj0.DisplayDesc.ColorA = 0.9
	Actor_31H_weapon2proj0.DisplayDesc.TransX = 0
	Actor_31H_weapon2proj0.DisplayDesc.TransY = 0
	Actor_31H_weapon2proj0.DisplayDesc.TransZ = 0
	Actor_31H_weapon2proj0.DisplayDesc.ScaleX = 0.05
	Actor_31H_weapon2proj0.DisplayDesc.ScaleY = 0.05
	Actor_31H_weapon2proj0.DisplayDesc.ScaleZ = 0.05
	Actor_31H_weapon2proj0.DisplayDesc.RotX = 0
	Actor_31H_weapon2proj0.DisplayDesc.RotY = 0
	Actor_31H_weapon2proj0.DisplayDesc.RotZ = 0
	Actor_31H_weapon2proj0.DisplayDesc.UseBillboard = true
	Actor_31H_weapon2proj0.PhysicDesc.Pos.X = 0
	Actor_31H_weapon2proj0.PhysicDesc.Pos.Y = 0
	Actor_31H_weapon2proj0.PhysicDesc.Pos.Z = 0
	Actor_31H_weapon2proj0.PhysicDesc.Pos.Rotation = 0
	Actor_31H_weapon2proj0.PhysicDesc.Density = 1
	Actor_31H_weapon2proj0.PhysicDesc.Collidable = false
	Actor_31H_weapon2proj0.PhysicDesc.SizeX = 0.05
	Actor_31H_weapon2proj0.PhysicDesc.SizeY = 0.05
	Actor_31H_weapon2proj0.PhysicDesc.SizeZ = 0.05
	Actor_31H_weapon2proj0.PhysicDesc.AllowFreeMove = true
	Actor_31H_weapon2proj0.PhysicDesc.Filename = ""
	Actor_31H_weapon2proj0:SetPhysicalActorType(3)
	Actor_31H_weapon2proj0:SetPhysicalShape(4)
	Actor_31H_weapon2proj0.UsableMode = ""
	Actor_31H_weapon2proj0.Power = 10
	Actor_31H_weapon2proj0.UseMana = 0
	Actor_31H_weapon2proj0.OffsetX = 2.5
	Actor_31H_weapon2proj0.OffsetY = 2.5
	Actor_31H_weapon2proj0.OffsetZ = 0
	Actor_31H_weapon2proj0.ForceX = 0.0005
	Actor_31H_weapon2proj0.ForceY = -0.0002
	Actor_31H_weapon2proj0.ForceYOnImpact = 0
	Actor_31H_weapon2proj0.NbBounce = 1
	Actor_31H_weapon2proj0.IgnoreGravity = true
	Actor_31H_weapon2proj0.LifeTime = 4000
	Actor_31H_weapon2proj0.Comeback = false
	Actor_31H_weapon2proj0.StartAnimFrame = 4
	Actor_31H_weapon2proj0.AngleOffset = 0
	Actor_31H_weapon2proj0.SoundAtStart = "Worlds/Lba1Original/Sound/SAMPLES027.voc.MP3"
	Actor_31H_weapon2proj0.SoundOnBounce = ""
	Actor_31H_weapon2proj0.ForceHurt = false
	Actor_31H_weapon2proj0.MultiShoot = false
	Actor_31H_weapon2proj0.UseTimer = false
	Actor_31H_weapon2proj0.Frequency = 1
	Actor_31H_weapon2proj0.FollowTarget = false
	Actor_31H:AddProjectileWeapon2(Actor_31H_weapon2proj0)
	Actor_31H_weapon2proj1 = ProjectileObjectDef()
	Actor_31H_weapon2proj1:SetRenderType(2)
	Actor_31H_weapon2proj1.DisplayDesc.ModelId = 0
	Actor_31H_weapon2proj1.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_31H_weapon2proj1.DisplayDesc.Outfit = ""
	Actor_31H_weapon2proj1.DisplayDesc.Weapon = ""
	Actor_31H_weapon2proj1.DisplayDesc.Mode = ""
	Actor_31H_weapon2proj1.DisplayDesc.UseLight = true
	Actor_31H_weapon2proj1.DisplayDesc.CastShadow = true
	Actor_31H_weapon2proj1.DisplayDesc.ColorR = 1
	Actor_31H_weapon2proj1.DisplayDesc.ColorG = 1
	Actor_31H_weapon2proj1.DisplayDesc.ColorB = 1
	Actor_31H_weapon2proj1.DisplayDesc.ColorA = 0.9
	Actor_31H_weapon2proj1.DisplayDesc.TransX = 0
	Actor_31H_weapon2proj1.DisplayDesc.TransY = 0
	Actor_31H_weapon2proj1.DisplayDesc.TransZ = 0
	Actor_31H_weapon2proj1.DisplayDesc.ScaleX = 0.05
	Actor_31H_weapon2proj1.DisplayDesc.ScaleY = 0.05
	Actor_31H_weapon2proj1.DisplayDesc.ScaleZ = 0.05
	Actor_31H_weapon2proj1.DisplayDesc.RotX = 0
	Actor_31H_weapon2proj1.DisplayDesc.RotY = 0
	Actor_31H_weapon2proj1.DisplayDesc.RotZ = 0
	Actor_31H_weapon2proj1.DisplayDesc.UseBillboard = true
	Actor_31H_weapon2proj1.PhysicDesc.Pos.X = 0
	Actor_31H_weapon2proj1.PhysicDesc.Pos.Y = 0
	Actor_31H_weapon2proj1.PhysicDesc.Pos.Z = 0
	Actor_31H_weapon2proj1.PhysicDesc.Pos.Rotation = 0
	Actor_31H_weapon2proj1.PhysicDesc.Density = 1
	Actor_31H_weapon2proj1.PhysicDesc.Collidable = false
	Actor_31H_weapon2proj1.PhysicDesc.SizeX = 0.05
	Actor_31H_weapon2proj1.PhysicDesc.SizeY = 0.05
	Actor_31H_weapon2proj1.PhysicDesc.SizeZ = 0.05
	Actor_31H_weapon2proj1.PhysicDesc.AllowFreeMove = true
	Actor_31H_weapon2proj1.PhysicDesc.Filename = ""
	Actor_31H_weapon2proj1:SetPhysicalActorType(3)
	Actor_31H_weapon2proj1:SetPhysicalShape(4)
	Actor_31H_weapon2proj1.UsableMode = ""
	Actor_31H_weapon2proj1.Power = 10
	Actor_31H_weapon2proj1.UseMana = 0
	Actor_31H_weapon2proj1.OffsetX = 2.5
	Actor_31H_weapon2proj1.OffsetY = 2.5
	Actor_31H_weapon2proj1.OffsetZ = 0
	Actor_31H_weapon2proj1.ForceX = 0.0005
	Actor_31H_weapon2proj1.ForceY = -0.0002
	Actor_31H_weapon2proj1.ForceYOnImpact = 0
	Actor_31H_weapon2proj1.NbBounce = 1
	Actor_31H_weapon2proj1.IgnoreGravity = true
	Actor_31H_weapon2proj1.LifeTime = 4000
	Actor_31H_weapon2proj1.Comeback = false
	Actor_31H_weapon2proj1.StartAnimFrame = 4
	Actor_31H_weapon2proj1.AngleOffset = 4
	Actor_31H_weapon2proj1.SoundAtStart = ""
	Actor_31H_weapon2proj1.SoundOnBounce = ""
	Actor_31H_weapon2proj1.ForceHurt = false
	Actor_31H_weapon2proj1.MultiShoot = false
	Actor_31H_weapon2proj1.UseTimer = false
	Actor_31H_weapon2proj1.Frequency = 1
	Actor_31H_weapon2proj1.FollowTarget = false
	Actor_31H:AddProjectileWeapon2(Actor_31H_weapon2proj1)
	Actor_31H_weapon2proj2 = ProjectileObjectDef()
	Actor_31H_weapon2proj2:SetRenderType(2)
	Actor_31H_weapon2proj2.DisplayDesc.ModelId = 0
	Actor_31H_weapon2proj2.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_31H_weapon2proj2.DisplayDesc.Outfit = ""
	Actor_31H_weapon2proj2.DisplayDesc.Weapon = ""
	Actor_31H_weapon2proj2.DisplayDesc.Mode = ""
	Actor_31H_weapon2proj2.DisplayDesc.UseLight = true
	Actor_31H_weapon2proj2.DisplayDesc.CastShadow = true
	Actor_31H_weapon2proj2.DisplayDesc.ColorR = 1
	Actor_31H_weapon2proj2.DisplayDesc.ColorG = 1
	Actor_31H_weapon2proj2.DisplayDesc.ColorB = 1
	Actor_31H_weapon2proj2.DisplayDesc.ColorA = 0.9
	Actor_31H_weapon2proj2.DisplayDesc.TransX = 0
	Actor_31H_weapon2proj2.DisplayDesc.TransY = 0
	Actor_31H_weapon2proj2.DisplayDesc.TransZ = 0
	Actor_31H_weapon2proj2.DisplayDesc.ScaleX = 0.05
	Actor_31H_weapon2proj2.DisplayDesc.ScaleY = 0.05
	Actor_31H_weapon2proj2.DisplayDesc.ScaleZ = 0.05
	Actor_31H_weapon2proj2.DisplayDesc.RotX = 0
	Actor_31H_weapon2proj2.DisplayDesc.RotY = 0
	Actor_31H_weapon2proj2.DisplayDesc.RotZ = 0
	Actor_31H_weapon2proj2.DisplayDesc.UseBillboard = true
	Actor_31H_weapon2proj2.PhysicDesc.Pos.X = 0
	Actor_31H_weapon2proj2.PhysicDesc.Pos.Y = 0
	Actor_31H_weapon2proj2.PhysicDesc.Pos.Z = 0
	Actor_31H_weapon2proj2.PhysicDesc.Pos.Rotation = 0
	Actor_31H_weapon2proj2.PhysicDesc.Density = 1
	Actor_31H_weapon2proj2.PhysicDesc.Collidable = false
	Actor_31H_weapon2proj2.PhysicDesc.SizeX = 0.05
	Actor_31H_weapon2proj2.PhysicDesc.SizeY = 0.05
	Actor_31H_weapon2proj2.PhysicDesc.SizeZ = 0.05
	Actor_31H_weapon2proj2.PhysicDesc.AllowFreeMove = true
	Actor_31H_weapon2proj2.PhysicDesc.Filename = ""
	Actor_31H_weapon2proj2:SetPhysicalActorType(3)
	Actor_31H_weapon2proj2:SetPhysicalShape(4)
	Actor_31H_weapon2proj2.UsableMode = ""
	Actor_31H_weapon2proj2.Power = 10
	Actor_31H_weapon2proj2.UseMana = 0
	Actor_31H_weapon2proj2.OffsetX = 2.5
	Actor_31H_weapon2proj2.OffsetY = 2.5
	Actor_31H_weapon2proj2.OffsetZ = 0
	Actor_31H_weapon2proj2.ForceX = 0.0005
	Actor_31H_weapon2proj2.ForceY = -0.0002
	Actor_31H_weapon2proj2.ForceYOnImpact = 0
	Actor_31H_weapon2proj2.NbBounce = 1
	Actor_31H_weapon2proj2.IgnoreGravity = true
	Actor_31H_weapon2proj2.LifeTime = 4000
	Actor_31H_weapon2proj2.Comeback = false
	Actor_31H_weapon2proj2.StartAnimFrame = 4
	Actor_31H_weapon2proj2.AngleOffset = -4
	Actor_31H_weapon2proj2.SoundAtStart = ""
	Actor_31H_weapon2proj2.SoundOnBounce = ""
	Actor_31H_weapon2proj2.ForceHurt = false
	Actor_31H_weapon2proj2.MultiShoot = false
	Actor_31H_weapon2proj2.UseTimer = false
	Actor_31H_weapon2proj2.Frequency = 1
	Actor_31H_weapon2proj2.FollowTarget = false
	Actor_31H:AddProjectileWeapon2(Actor_31H_weapon2proj2)
	Actor_31H:SetAttackFunction("ActorRotateAttackDistanceAndContactPlayer")
	Actor_31H:AddGivenItem(1,1,1,0.3,1)
	Actor_31H:AddGivenItem(2,1,1,0.3,1)
	Actor_31H:AddGivenItem(8,2,2,0.4,1)
	Actor_31H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_31H)

	Actor_32 = ActorObjectInfo(32)
	Actor_32:SetRenderType(3)
	Actor_32.HitPowerOnTouch = -1
	Actor_32.ExcludeFromNavMesh = false
	Actor_32.DisplayDesc.ModelId = 0
	Actor_32.DisplayDesc.ModelName = "Soldier"
	Actor_32.DisplayDesc.Outfit = "Grass"
	Actor_32.DisplayDesc.Weapon = "rifle"
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
	Actor_32.DisplayDesc.UseBillboard = false
	Actor_32.DisplayDesc.ColorMaterialType = 4
	Actor_32.DisplayDesc.MatAmbientColorR = -0.2
	Actor_32.DisplayDesc.MatAmbientColorG = -0.2
	Actor_32.DisplayDesc.MatAmbientColorB = -0.2
	Actor_32.DisplayDesc.MatAmbientColorA = 1
	Actor_32.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_32.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_32.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_32.DisplayDesc.MatDiffuseColorA = 1
	Actor_32.DisplayDesc.MatSpecularColorR = 0
	Actor_32.DisplayDesc.MatSpecularColorG = 0
	Actor_32.DisplayDesc.MatSpecularColorB = 0
	Actor_32.DisplayDesc.MatSpecularColorA = 1
	Actor_32.DisplayDesc.MatEmissionColorR = 0
	Actor_32.DisplayDesc.MatEmissionColorG = 0
	Actor_32.DisplayDesc.MatEmissionColorB = 0
	Actor_32.DisplayDesc.MatEmissionColorA = 1
	Actor_32.DisplayDesc.MatShininess = 0
	Actor_32.PhysicDesc.Pos.X = 24.5
	Actor_32.PhysicDesc.Pos.Y = 0
	Actor_32.PhysicDesc.Pos.Z = 20.5
	Actor_32.PhysicDesc.Pos.Rotation = 25
	Actor_32.PhysicDesc.Density = 1
	Actor_32.PhysicDesc.Collidable = true
	Actor_32.PhysicDesc.SizeX = 2
	Actor_32.PhysicDesc.SizeY = 5
	Actor_32.PhysicDesc.SizeZ = 2
	Actor_32.PhysicDesc.AllowFreeMove = true
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
	Actor_32H:SetAggresive(true)
	Actor_32H:SetLife(50)
	Actor_32H:SetMana(0)
	Actor_32H:SetArmor(0)
	Actor_32H:SetAttackActiDist(7)
	Actor_32H:SetAttackActiDistDiscrete(4)
	Actor_32H:SetAttackActiDistHidden(2)
	Actor_32H:SetAttackStopDist(10)
	Actor_32H:SetRespawnTimeInSec(10)
	Actor_32H:SetWeapon1Type(1)
	Actor_32H:SetWeapon1Power(10)
	Actor_32H:SetWeapon1ReachDistance(2)
	Actor_32H:Setuseweapon1animation("Use1Weapon")
	Actor_32H:SetWeapon2Type(2)
	Actor_32H:SetWeapon2Power(0)
	Actor_32H:SetWeapon2ReachDistance(7)
	Actor_32H:Setuseweapon2animation("UseWeapon")
	Actor_32H_weapon2proj0 = ProjectileObjectDef()
	Actor_32H_weapon2proj0:SetRenderType(2)
	Actor_32H_weapon2proj0.DisplayDesc.ModelId = 0
	Actor_32H_weapon2proj0.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_32H_weapon2proj0.DisplayDesc.Outfit = ""
	Actor_32H_weapon2proj0.DisplayDesc.Weapon = ""
	Actor_32H_weapon2proj0.DisplayDesc.Mode = ""
	Actor_32H_weapon2proj0.DisplayDesc.UseLight = true
	Actor_32H_weapon2proj0.DisplayDesc.CastShadow = true
	Actor_32H_weapon2proj0.DisplayDesc.ColorR = 1
	Actor_32H_weapon2proj0.DisplayDesc.ColorG = 1
	Actor_32H_weapon2proj0.DisplayDesc.ColorB = 1
	Actor_32H_weapon2proj0.DisplayDesc.ColorA = 0.9
	Actor_32H_weapon2proj0.DisplayDesc.TransX = 0
	Actor_32H_weapon2proj0.DisplayDesc.TransY = 0
	Actor_32H_weapon2proj0.DisplayDesc.TransZ = 0
	Actor_32H_weapon2proj0.DisplayDesc.ScaleX = 0.05
	Actor_32H_weapon2proj0.DisplayDesc.ScaleY = 0.05
	Actor_32H_weapon2proj0.DisplayDesc.ScaleZ = 0.05
	Actor_32H_weapon2proj0.DisplayDesc.RotX = 0
	Actor_32H_weapon2proj0.DisplayDesc.RotY = 0
	Actor_32H_weapon2proj0.DisplayDesc.RotZ = 0
	Actor_32H_weapon2proj0.DisplayDesc.UseBillboard = true
	Actor_32H_weapon2proj0.PhysicDesc.Pos.X = 0
	Actor_32H_weapon2proj0.PhysicDesc.Pos.Y = 0
	Actor_32H_weapon2proj0.PhysicDesc.Pos.Z = 0
	Actor_32H_weapon2proj0.PhysicDesc.Pos.Rotation = 0
	Actor_32H_weapon2proj0.PhysicDesc.Density = 1
	Actor_32H_weapon2proj0.PhysicDesc.Collidable = false
	Actor_32H_weapon2proj0.PhysicDesc.SizeX = 0.05
	Actor_32H_weapon2proj0.PhysicDesc.SizeY = 0.05
	Actor_32H_weapon2proj0.PhysicDesc.SizeZ = 0.05
	Actor_32H_weapon2proj0.PhysicDesc.AllowFreeMove = true
	Actor_32H_weapon2proj0.PhysicDesc.Filename = ""
	Actor_32H_weapon2proj0:SetPhysicalActorType(3)
	Actor_32H_weapon2proj0:SetPhysicalShape(4)
	Actor_32H_weapon2proj0.UsableMode = ""
	Actor_32H_weapon2proj0.Power = 10
	Actor_32H_weapon2proj0.UseMana = 0
	Actor_32H_weapon2proj0.OffsetX = 2.5
	Actor_32H_weapon2proj0.OffsetY = 2.5
	Actor_32H_weapon2proj0.OffsetZ = 0
	Actor_32H_weapon2proj0.ForceX = 0.0005
	Actor_32H_weapon2proj0.ForceY = -0.0002
	Actor_32H_weapon2proj0.ForceYOnImpact = 0
	Actor_32H_weapon2proj0.NbBounce = 1
	Actor_32H_weapon2proj0.IgnoreGravity = true
	Actor_32H_weapon2proj0.LifeTime = 4000
	Actor_32H_weapon2proj0.Comeback = false
	Actor_32H_weapon2proj0.StartAnimFrame = 4
	Actor_32H_weapon2proj0.AngleOffset = 0
	Actor_32H_weapon2proj0.SoundAtStart = "Worlds/Lba1Original/Sound/SAMPLES027.voc.MP3"
	Actor_32H_weapon2proj0.SoundOnBounce = ""
	Actor_32H_weapon2proj0.ForceHurt = false
	Actor_32H_weapon2proj0.MultiShoot = false
	Actor_32H_weapon2proj0.UseTimer = false
	Actor_32H_weapon2proj0.Frequency = 1
	Actor_32H_weapon2proj0.FollowTarget = false
	Actor_32H:AddProjectileWeapon2(Actor_32H_weapon2proj0)
	Actor_32H_weapon2proj1 = ProjectileObjectDef()
	Actor_32H_weapon2proj1:SetRenderType(2)
	Actor_32H_weapon2proj1.DisplayDesc.ModelId = 0
	Actor_32H_weapon2proj1.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_32H_weapon2proj1.DisplayDesc.Outfit = ""
	Actor_32H_weapon2proj1.DisplayDesc.Weapon = ""
	Actor_32H_weapon2proj1.DisplayDesc.Mode = ""
	Actor_32H_weapon2proj1.DisplayDesc.UseLight = true
	Actor_32H_weapon2proj1.DisplayDesc.CastShadow = true
	Actor_32H_weapon2proj1.DisplayDesc.ColorR = 1
	Actor_32H_weapon2proj1.DisplayDesc.ColorG = 1
	Actor_32H_weapon2proj1.DisplayDesc.ColorB = 1
	Actor_32H_weapon2proj1.DisplayDesc.ColorA = 0.9
	Actor_32H_weapon2proj1.DisplayDesc.TransX = 0
	Actor_32H_weapon2proj1.DisplayDesc.TransY = 0
	Actor_32H_weapon2proj1.DisplayDesc.TransZ = 0
	Actor_32H_weapon2proj1.DisplayDesc.ScaleX = 0.05
	Actor_32H_weapon2proj1.DisplayDesc.ScaleY = 0.05
	Actor_32H_weapon2proj1.DisplayDesc.ScaleZ = 0.05
	Actor_32H_weapon2proj1.DisplayDesc.RotX = 0
	Actor_32H_weapon2proj1.DisplayDesc.RotY = 0
	Actor_32H_weapon2proj1.DisplayDesc.RotZ = 0
	Actor_32H_weapon2proj1.DisplayDesc.UseBillboard = true
	Actor_32H_weapon2proj1.PhysicDesc.Pos.X = 0
	Actor_32H_weapon2proj1.PhysicDesc.Pos.Y = 0
	Actor_32H_weapon2proj1.PhysicDesc.Pos.Z = 0
	Actor_32H_weapon2proj1.PhysicDesc.Pos.Rotation = 0
	Actor_32H_weapon2proj1.PhysicDesc.Density = 1
	Actor_32H_weapon2proj1.PhysicDesc.Collidable = false
	Actor_32H_weapon2proj1.PhysicDesc.SizeX = 0.05
	Actor_32H_weapon2proj1.PhysicDesc.SizeY = 0.05
	Actor_32H_weapon2proj1.PhysicDesc.SizeZ = 0.05
	Actor_32H_weapon2proj1.PhysicDesc.AllowFreeMove = true
	Actor_32H_weapon2proj1.PhysicDesc.Filename = ""
	Actor_32H_weapon2proj1:SetPhysicalActorType(3)
	Actor_32H_weapon2proj1:SetPhysicalShape(4)
	Actor_32H_weapon2proj1.UsableMode = ""
	Actor_32H_weapon2proj1.Power = 10
	Actor_32H_weapon2proj1.UseMana = 0
	Actor_32H_weapon2proj1.OffsetX = 2.5
	Actor_32H_weapon2proj1.OffsetY = 2.5
	Actor_32H_weapon2proj1.OffsetZ = 0
	Actor_32H_weapon2proj1.ForceX = 0.0005
	Actor_32H_weapon2proj1.ForceY = -0.0002
	Actor_32H_weapon2proj1.ForceYOnImpact = 0
	Actor_32H_weapon2proj1.NbBounce = 1
	Actor_32H_weapon2proj1.IgnoreGravity = true
	Actor_32H_weapon2proj1.LifeTime = 4000
	Actor_32H_weapon2proj1.Comeback = false
	Actor_32H_weapon2proj1.StartAnimFrame = 4
	Actor_32H_weapon2proj1.AngleOffset = 4
	Actor_32H_weapon2proj1.SoundAtStart = ""
	Actor_32H_weapon2proj1.SoundOnBounce = ""
	Actor_32H_weapon2proj1.ForceHurt = false
	Actor_32H_weapon2proj1.MultiShoot = false
	Actor_32H_weapon2proj1.UseTimer = false
	Actor_32H_weapon2proj1.Frequency = 1
	Actor_32H_weapon2proj1.FollowTarget = false
	Actor_32H:AddProjectileWeapon2(Actor_32H_weapon2proj1)
	Actor_32H_weapon2proj2 = ProjectileObjectDef()
	Actor_32H_weapon2proj2:SetRenderType(2)
	Actor_32H_weapon2proj2.DisplayDesc.ModelId = 0
	Actor_32H_weapon2proj2.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_32H_weapon2proj2.DisplayDesc.Outfit = ""
	Actor_32H_weapon2proj2.DisplayDesc.Weapon = ""
	Actor_32H_weapon2proj2.DisplayDesc.Mode = ""
	Actor_32H_weapon2proj2.DisplayDesc.UseLight = true
	Actor_32H_weapon2proj2.DisplayDesc.CastShadow = true
	Actor_32H_weapon2proj2.DisplayDesc.ColorR = 1
	Actor_32H_weapon2proj2.DisplayDesc.ColorG = 1
	Actor_32H_weapon2proj2.DisplayDesc.ColorB = 1
	Actor_32H_weapon2proj2.DisplayDesc.ColorA = 0.9
	Actor_32H_weapon2proj2.DisplayDesc.TransX = 0
	Actor_32H_weapon2proj2.DisplayDesc.TransY = 0
	Actor_32H_weapon2proj2.DisplayDesc.TransZ = 0
	Actor_32H_weapon2proj2.DisplayDesc.ScaleX = 0.05
	Actor_32H_weapon2proj2.DisplayDesc.ScaleY = 0.05
	Actor_32H_weapon2proj2.DisplayDesc.ScaleZ = 0.05
	Actor_32H_weapon2proj2.DisplayDesc.RotX = 0
	Actor_32H_weapon2proj2.DisplayDesc.RotY = 0
	Actor_32H_weapon2proj2.DisplayDesc.RotZ = 0
	Actor_32H_weapon2proj2.DisplayDesc.UseBillboard = true
	Actor_32H_weapon2proj2.PhysicDesc.Pos.X = 0
	Actor_32H_weapon2proj2.PhysicDesc.Pos.Y = 0
	Actor_32H_weapon2proj2.PhysicDesc.Pos.Z = 0
	Actor_32H_weapon2proj2.PhysicDesc.Pos.Rotation = 0
	Actor_32H_weapon2proj2.PhysicDesc.Density = 1
	Actor_32H_weapon2proj2.PhysicDesc.Collidable = false
	Actor_32H_weapon2proj2.PhysicDesc.SizeX = 0.05
	Actor_32H_weapon2proj2.PhysicDesc.SizeY = 0.05
	Actor_32H_weapon2proj2.PhysicDesc.SizeZ = 0.05
	Actor_32H_weapon2proj2.PhysicDesc.AllowFreeMove = true
	Actor_32H_weapon2proj2.PhysicDesc.Filename = ""
	Actor_32H_weapon2proj2:SetPhysicalActorType(3)
	Actor_32H_weapon2proj2:SetPhysicalShape(4)
	Actor_32H_weapon2proj2.UsableMode = ""
	Actor_32H_weapon2proj2.Power = 10
	Actor_32H_weapon2proj2.UseMana = 0
	Actor_32H_weapon2proj2.OffsetX = 2.5
	Actor_32H_weapon2proj2.OffsetY = 2.5
	Actor_32H_weapon2proj2.OffsetZ = 0
	Actor_32H_weapon2proj2.ForceX = 0.0005
	Actor_32H_weapon2proj2.ForceY = -0.0002
	Actor_32H_weapon2proj2.ForceYOnImpact = 0
	Actor_32H_weapon2proj2.NbBounce = 1
	Actor_32H_weapon2proj2.IgnoreGravity = true
	Actor_32H_weapon2proj2.LifeTime = 4000
	Actor_32H_weapon2proj2.Comeback = false
	Actor_32H_weapon2proj2.StartAnimFrame = 4
	Actor_32H_weapon2proj2.AngleOffset = -4
	Actor_32H_weapon2proj2.SoundAtStart = ""
	Actor_32H_weapon2proj2.SoundOnBounce = ""
	Actor_32H_weapon2proj2.ForceHurt = false
	Actor_32H_weapon2proj2.MultiShoot = false
	Actor_32H_weapon2proj2.UseTimer = false
	Actor_32H_weapon2proj2.Frequency = 1
	Actor_32H_weapon2proj2.FollowTarget = false
	Actor_32H:AddProjectileWeapon2(Actor_32H_weapon2proj2)
	Actor_32H:SetAttackFunction("ActorRotateAttackDistanceAndContactPlayer")
	Actor_32H:AddGivenItem(1,1,1,0.3,1)
	Actor_32H:AddGivenItem(2,1,1,0.3,1)
	Actor_32H:AddGivenItem(8,2,2,0.4,1)
	Actor_32H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_32H)

	Actor_33 = ActorObjectInfo(33)
	Actor_33:SetRenderType(3)
	Actor_33.HitPowerOnTouch = -1
	Actor_33.ExcludeFromNavMesh = false
	Actor_33.DisplayDesc.ModelId = 0
	Actor_33.DisplayDesc.ModelName = "Soldier"
	Actor_33.DisplayDesc.Outfit = "Grass"
	Actor_33.DisplayDesc.Weapon = "rifle"
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
	Actor_33.DisplayDesc.UseBillboard = false
	Actor_33.DisplayDesc.ColorMaterialType = 4
	Actor_33.DisplayDesc.MatAmbientColorR = -0.2
	Actor_33.DisplayDesc.MatAmbientColorG = -0.2
	Actor_33.DisplayDesc.MatAmbientColorB = -0.2
	Actor_33.DisplayDesc.MatAmbientColorA = 1
	Actor_33.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_33.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_33.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_33.DisplayDesc.MatDiffuseColorA = 1
	Actor_33.DisplayDesc.MatSpecularColorR = 0
	Actor_33.DisplayDesc.MatSpecularColorG = 0
	Actor_33.DisplayDesc.MatSpecularColorB = 0
	Actor_33.DisplayDesc.MatSpecularColorA = 1
	Actor_33.DisplayDesc.MatEmissionColorR = 0
	Actor_33.DisplayDesc.MatEmissionColorG = 0
	Actor_33.DisplayDesc.MatEmissionColorB = 0
	Actor_33.DisplayDesc.MatEmissionColorA = 1
	Actor_33.DisplayDesc.MatShininess = 0
	Actor_33.PhysicDesc.Pos.X = 2
	Actor_33.PhysicDesc.Pos.Y = 7
	Actor_33.PhysicDesc.Pos.Z = 16
	Actor_33.PhysicDesc.Pos.Rotation = 25
	Actor_33.PhysicDesc.Density = 1
	Actor_33.PhysicDesc.Collidable = true
	Actor_33.PhysicDesc.SizeX = 2
	Actor_33.PhysicDesc.SizeY = 5
	Actor_33.PhysicDesc.SizeZ = 2
	Actor_33.PhysicDesc.AllowFreeMove = true
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
	Actor_33H:SetAggresive(true)
	Actor_33H:SetLife(50)
	Actor_33H:SetMana(0)
	Actor_33H:SetArmor(0)
	Actor_33H:SetAttackActiDist(7)
	Actor_33H:SetAttackActiDistDiscrete(4)
	Actor_33H:SetAttackActiDistHidden(2)
	Actor_33H:SetAttackStopDist(10)
	Actor_33H:SetRespawnTimeInSec(10)
	Actor_33H:SetWeapon1Type(1)
	Actor_33H:SetWeapon1Power(10)
	Actor_33H:SetWeapon1ReachDistance(2)
	Actor_33H:Setuseweapon1animation("Use1Weapon")
	Actor_33H:SetWeapon2Type(2)
	Actor_33H:SetWeapon2Power(0)
	Actor_33H:SetWeapon2ReachDistance(7)
	Actor_33H:Setuseweapon2animation("UseWeapon")
	Actor_33H_weapon2proj0 = ProjectileObjectDef()
	Actor_33H_weapon2proj0:SetRenderType(2)
	Actor_33H_weapon2proj0.DisplayDesc.ModelId = 0
	Actor_33H_weapon2proj0.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_33H_weapon2proj0.DisplayDesc.Outfit = ""
	Actor_33H_weapon2proj0.DisplayDesc.Weapon = ""
	Actor_33H_weapon2proj0.DisplayDesc.Mode = ""
	Actor_33H_weapon2proj0.DisplayDesc.UseLight = true
	Actor_33H_weapon2proj0.DisplayDesc.CastShadow = true
	Actor_33H_weapon2proj0.DisplayDesc.ColorR = 1
	Actor_33H_weapon2proj0.DisplayDesc.ColorG = 1
	Actor_33H_weapon2proj0.DisplayDesc.ColorB = 1
	Actor_33H_weapon2proj0.DisplayDesc.ColorA = 0.9
	Actor_33H_weapon2proj0.DisplayDesc.TransX = 0
	Actor_33H_weapon2proj0.DisplayDesc.TransY = 0
	Actor_33H_weapon2proj0.DisplayDesc.TransZ = 0
	Actor_33H_weapon2proj0.DisplayDesc.ScaleX = 0.05
	Actor_33H_weapon2proj0.DisplayDesc.ScaleY = 0.05
	Actor_33H_weapon2proj0.DisplayDesc.ScaleZ = 0.05
	Actor_33H_weapon2proj0.DisplayDesc.RotX = 0
	Actor_33H_weapon2proj0.DisplayDesc.RotY = 0
	Actor_33H_weapon2proj0.DisplayDesc.RotZ = 0
	Actor_33H_weapon2proj0.DisplayDesc.UseBillboard = true
	Actor_33H_weapon2proj0.PhysicDesc.Pos.X = 0
	Actor_33H_weapon2proj0.PhysicDesc.Pos.Y = 0
	Actor_33H_weapon2proj0.PhysicDesc.Pos.Z = 0
	Actor_33H_weapon2proj0.PhysicDesc.Pos.Rotation = 0
	Actor_33H_weapon2proj0.PhysicDesc.Density = 1
	Actor_33H_weapon2proj0.PhysicDesc.Collidable = false
	Actor_33H_weapon2proj0.PhysicDesc.SizeX = 0.05
	Actor_33H_weapon2proj0.PhysicDesc.SizeY = 0.05
	Actor_33H_weapon2proj0.PhysicDesc.SizeZ = 0.05
	Actor_33H_weapon2proj0.PhysicDesc.AllowFreeMove = true
	Actor_33H_weapon2proj0.PhysicDesc.Filename = ""
	Actor_33H_weapon2proj0:SetPhysicalActorType(3)
	Actor_33H_weapon2proj0:SetPhysicalShape(4)
	Actor_33H_weapon2proj0.UsableMode = ""
	Actor_33H_weapon2proj0.Power = 10
	Actor_33H_weapon2proj0.UseMana = 0
	Actor_33H_weapon2proj0.OffsetX = 2.5
	Actor_33H_weapon2proj0.OffsetY = 2.5
	Actor_33H_weapon2proj0.OffsetZ = 0
	Actor_33H_weapon2proj0.ForceX = 0.0005
	Actor_33H_weapon2proj0.ForceY = -0.0002
	Actor_33H_weapon2proj0.ForceYOnImpact = 0
	Actor_33H_weapon2proj0.NbBounce = 1
	Actor_33H_weapon2proj0.IgnoreGravity = true
	Actor_33H_weapon2proj0.LifeTime = 4000
	Actor_33H_weapon2proj0.Comeback = false
	Actor_33H_weapon2proj0.StartAnimFrame = 4
	Actor_33H_weapon2proj0.AngleOffset = 0
	Actor_33H_weapon2proj0.SoundAtStart = "Worlds/Lba1Original/Sound/SAMPLES027.voc.MP3"
	Actor_33H_weapon2proj0.SoundOnBounce = ""
	Actor_33H_weapon2proj0.ForceHurt = false
	Actor_33H_weapon2proj0.MultiShoot = false
	Actor_33H_weapon2proj0.UseTimer = false
	Actor_33H_weapon2proj0.Frequency = 1
	Actor_33H_weapon2proj0.FollowTarget = false
	Actor_33H:AddProjectileWeapon2(Actor_33H_weapon2proj0)
	Actor_33H_weapon2proj1 = ProjectileObjectDef()
	Actor_33H_weapon2proj1:SetRenderType(2)
	Actor_33H_weapon2proj1.DisplayDesc.ModelId = 0
	Actor_33H_weapon2proj1.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_33H_weapon2proj1.DisplayDesc.Outfit = ""
	Actor_33H_weapon2proj1.DisplayDesc.Weapon = ""
	Actor_33H_weapon2proj1.DisplayDesc.Mode = ""
	Actor_33H_weapon2proj1.DisplayDesc.UseLight = true
	Actor_33H_weapon2proj1.DisplayDesc.CastShadow = true
	Actor_33H_weapon2proj1.DisplayDesc.ColorR = 1
	Actor_33H_weapon2proj1.DisplayDesc.ColorG = 1
	Actor_33H_weapon2proj1.DisplayDesc.ColorB = 1
	Actor_33H_weapon2proj1.DisplayDesc.ColorA = 0.9
	Actor_33H_weapon2proj1.DisplayDesc.TransX = 0
	Actor_33H_weapon2proj1.DisplayDesc.TransY = 0
	Actor_33H_weapon2proj1.DisplayDesc.TransZ = 0
	Actor_33H_weapon2proj1.DisplayDesc.ScaleX = 0.05
	Actor_33H_weapon2proj1.DisplayDesc.ScaleY = 0.05
	Actor_33H_weapon2proj1.DisplayDesc.ScaleZ = 0.05
	Actor_33H_weapon2proj1.DisplayDesc.RotX = 0
	Actor_33H_weapon2proj1.DisplayDesc.RotY = 0
	Actor_33H_weapon2proj1.DisplayDesc.RotZ = 0
	Actor_33H_weapon2proj1.DisplayDesc.UseBillboard = true
	Actor_33H_weapon2proj1.PhysicDesc.Pos.X = 0
	Actor_33H_weapon2proj1.PhysicDesc.Pos.Y = 0
	Actor_33H_weapon2proj1.PhysicDesc.Pos.Z = 0
	Actor_33H_weapon2proj1.PhysicDesc.Pos.Rotation = 0
	Actor_33H_weapon2proj1.PhysicDesc.Density = 1
	Actor_33H_weapon2proj1.PhysicDesc.Collidable = false
	Actor_33H_weapon2proj1.PhysicDesc.SizeX = 0.05
	Actor_33H_weapon2proj1.PhysicDesc.SizeY = 0.05
	Actor_33H_weapon2proj1.PhysicDesc.SizeZ = 0.05
	Actor_33H_weapon2proj1.PhysicDesc.AllowFreeMove = true
	Actor_33H_weapon2proj1.PhysicDesc.Filename = ""
	Actor_33H_weapon2proj1:SetPhysicalActorType(3)
	Actor_33H_weapon2proj1:SetPhysicalShape(4)
	Actor_33H_weapon2proj1.UsableMode = ""
	Actor_33H_weapon2proj1.Power = 10
	Actor_33H_weapon2proj1.UseMana = 0
	Actor_33H_weapon2proj1.OffsetX = 2.5
	Actor_33H_weapon2proj1.OffsetY = 2.5
	Actor_33H_weapon2proj1.OffsetZ = 0
	Actor_33H_weapon2proj1.ForceX = 0.0005
	Actor_33H_weapon2proj1.ForceY = -0.0002
	Actor_33H_weapon2proj1.ForceYOnImpact = 0
	Actor_33H_weapon2proj1.NbBounce = 1
	Actor_33H_weapon2proj1.IgnoreGravity = true
	Actor_33H_weapon2proj1.LifeTime = 4000
	Actor_33H_weapon2proj1.Comeback = false
	Actor_33H_weapon2proj1.StartAnimFrame = 4
	Actor_33H_weapon2proj1.AngleOffset = 4
	Actor_33H_weapon2proj1.SoundAtStart = ""
	Actor_33H_weapon2proj1.SoundOnBounce = ""
	Actor_33H_weapon2proj1.ForceHurt = false
	Actor_33H_weapon2proj1.MultiShoot = false
	Actor_33H_weapon2proj1.UseTimer = false
	Actor_33H_weapon2proj1.Frequency = 1
	Actor_33H_weapon2proj1.FollowTarget = false
	Actor_33H:AddProjectileWeapon2(Actor_33H_weapon2proj1)
	Actor_33H_weapon2proj2 = ProjectileObjectDef()
	Actor_33H_weapon2proj2:SetRenderType(2)
	Actor_33H_weapon2proj2.DisplayDesc.ModelId = 0
	Actor_33H_weapon2proj2.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_33H_weapon2proj2.DisplayDesc.Outfit = ""
	Actor_33H_weapon2proj2.DisplayDesc.Weapon = ""
	Actor_33H_weapon2proj2.DisplayDesc.Mode = ""
	Actor_33H_weapon2proj2.DisplayDesc.UseLight = true
	Actor_33H_weapon2proj2.DisplayDesc.CastShadow = true
	Actor_33H_weapon2proj2.DisplayDesc.ColorR = 1
	Actor_33H_weapon2proj2.DisplayDesc.ColorG = 1
	Actor_33H_weapon2proj2.DisplayDesc.ColorB = 1
	Actor_33H_weapon2proj2.DisplayDesc.ColorA = 0.9
	Actor_33H_weapon2proj2.DisplayDesc.TransX = 0
	Actor_33H_weapon2proj2.DisplayDesc.TransY = 0
	Actor_33H_weapon2proj2.DisplayDesc.TransZ = 0
	Actor_33H_weapon2proj2.DisplayDesc.ScaleX = 0.05
	Actor_33H_weapon2proj2.DisplayDesc.ScaleY = 0.05
	Actor_33H_weapon2proj2.DisplayDesc.ScaleZ = 0.05
	Actor_33H_weapon2proj2.DisplayDesc.RotX = 0
	Actor_33H_weapon2proj2.DisplayDesc.RotY = 0
	Actor_33H_weapon2proj2.DisplayDesc.RotZ = 0
	Actor_33H_weapon2proj2.DisplayDesc.UseBillboard = true
	Actor_33H_weapon2proj2.PhysicDesc.Pos.X = 0
	Actor_33H_weapon2proj2.PhysicDesc.Pos.Y = 0
	Actor_33H_weapon2proj2.PhysicDesc.Pos.Z = 0
	Actor_33H_weapon2proj2.PhysicDesc.Pos.Rotation = 0
	Actor_33H_weapon2proj2.PhysicDesc.Density = 1
	Actor_33H_weapon2proj2.PhysicDesc.Collidable = false
	Actor_33H_weapon2proj2.PhysicDesc.SizeX = 0.05
	Actor_33H_weapon2proj2.PhysicDesc.SizeY = 0.05
	Actor_33H_weapon2proj2.PhysicDesc.SizeZ = 0.05
	Actor_33H_weapon2proj2.PhysicDesc.AllowFreeMove = true
	Actor_33H_weapon2proj2.PhysicDesc.Filename = ""
	Actor_33H_weapon2proj2:SetPhysicalActorType(3)
	Actor_33H_weapon2proj2:SetPhysicalShape(4)
	Actor_33H_weapon2proj2.UsableMode = ""
	Actor_33H_weapon2proj2.Power = 10
	Actor_33H_weapon2proj2.UseMana = 0
	Actor_33H_weapon2proj2.OffsetX = 2.5
	Actor_33H_weapon2proj2.OffsetY = 2.5
	Actor_33H_weapon2proj2.OffsetZ = 0
	Actor_33H_weapon2proj2.ForceX = 0.0005
	Actor_33H_weapon2proj2.ForceY = -0.0002
	Actor_33H_weapon2proj2.ForceYOnImpact = 0
	Actor_33H_weapon2proj2.NbBounce = 1
	Actor_33H_weapon2proj2.IgnoreGravity = true
	Actor_33H_weapon2proj2.LifeTime = 4000
	Actor_33H_weapon2proj2.Comeback = false
	Actor_33H_weapon2proj2.StartAnimFrame = 4
	Actor_33H_weapon2proj2.AngleOffset = -4
	Actor_33H_weapon2proj2.SoundAtStart = ""
	Actor_33H_weapon2proj2.SoundOnBounce = ""
	Actor_33H_weapon2proj2.ForceHurt = false
	Actor_33H_weapon2proj2.MultiShoot = false
	Actor_33H_weapon2proj2.UseTimer = false
	Actor_33H_weapon2proj2.Frequency = 1
	Actor_33H_weapon2proj2.FollowTarget = false
	Actor_33H:AddProjectileWeapon2(Actor_33H_weapon2proj2)
	Actor_33H:SetAttackFunction("ActorRotateAttackDistanceAndContactPlayer")
	Actor_33H:AddGivenItem(1,1,1,0.3,1)
	Actor_33H:AddGivenItem(2,1,1,0.3,1)
	Actor_33H:AddGivenItem(8,2,2,0.4,1)
	Actor_33H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_33H)

	Actor_34 = ActorObjectInfo(34)
	Actor_34:SetRenderType(3)
	Actor_34.HitPowerOnTouch = -1
	Actor_34.ExcludeFromNavMesh = false
	Actor_34.DisplayDesc.ModelId = 0
	Actor_34.DisplayDesc.ModelName = "Soldier"
	Actor_34.DisplayDesc.Outfit = "Grass"
	Actor_34.DisplayDesc.Weapon = "rifle"
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
	Actor_34.DisplayDesc.UseBillboard = false
	Actor_34.DisplayDesc.ColorMaterialType = 4
	Actor_34.DisplayDesc.MatAmbientColorR = -0.2
	Actor_34.DisplayDesc.MatAmbientColorG = -0.2
	Actor_34.DisplayDesc.MatAmbientColorB = -0.2
	Actor_34.DisplayDesc.MatAmbientColorA = 1
	Actor_34.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_34.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_34.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_34.DisplayDesc.MatDiffuseColorA = 1
	Actor_34.DisplayDesc.MatSpecularColorR = 0
	Actor_34.DisplayDesc.MatSpecularColorG = 0
	Actor_34.DisplayDesc.MatSpecularColorB = 0
	Actor_34.DisplayDesc.MatSpecularColorA = 1
	Actor_34.DisplayDesc.MatEmissionColorR = 0
	Actor_34.DisplayDesc.MatEmissionColorG = 0
	Actor_34.DisplayDesc.MatEmissionColorB = 0
	Actor_34.DisplayDesc.MatEmissionColorA = 1
	Actor_34.DisplayDesc.MatShininess = 0
	Actor_34.PhysicDesc.Pos.X = 54.4
	Actor_34.PhysicDesc.Pos.Y = 0
	Actor_34.PhysicDesc.Pos.Z = 34
	Actor_34.PhysicDesc.Pos.Rotation = 270
	Actor_34.PhysicDesc.Density = 1
	Actor_34.PhysicDesc.Collidable = true
	Actor_34.PhysicDesc.SizeX = 2
	Actor_34.PhysicDesc.SizeY = 5
	Actor_34.PhysicDesc.SizeZ = 2
	Actor_34.PhysicDesc.AllowFreeMove = true
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
	Actor_34H:SetAggresive(true)
	Actor_34H:SetLife(50)
	Actor_34H:SetMana(0)
	Actor_34H:SetArmor(0)
	Actor_34H:SetAttackActiDist(7)
	Actor_34H:SetAttackActiDistDiscrete(4)
	Actor_34H:SetAttackActiDistHidden(2)
	Actor_34H:SetAttackStopDist(10)
	Actor_34H:SetRespawnTimeInSec(10)
	Actor_34H:SetWeapon1Type(1)
	Actor_34H:SetWeapon1Power(10)
	Actor_34H:SetWeapon1ReachDistance(2)
	Actor_34H:Setuseweapon1animation("Use1Weapon")
	Actor_34H:SetWeapon2Type(2)
	Actor_34H:SetWeapon2Power(0)
	Actor_34H:SetWeapon2ReachDistance(7)
	Actor_34H:Setuseweapon2animation("UseWeapon")
	Actor_34H_weapon2proj0 = ProjectileObjectDef()
	Actor_34H_weapon2proj0:SetRenderType(2)
	Actor_34H_weapon2proj0.DisplayDesc.ModelId = 0
	Actor_34H_weapon2proj0.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_34H_weapon2proj0.DisplayDesc.Outfit = ""
	Actor_34H_weapon2proj0.DisplayDesc.Weapon = ""
	Actor_34H_weapon2proj0.DisplayDesc.Mode = ""
	Actor_34H_weapon2proj0.DisplayDesc.UseLight = true
	Actor_34H_weapon2proj0.DisplayDesc.CastShadow = true
	Actor_34H_weapon2proj0.DisplayDesc.ColorR = 1
	Actor_34H_weapon2proj0.DisplayDesc.ColorG = 1
	Actor_34H_weapon2proj0.DisplayDesc.ColorB = 1
	Actor_34H_weapon2proj0.DisplayDesc.ColorA = 0.9
	Actor_34H_weapon2proj0.DisplayDesc.TransX = 0
	Actor_34H_weapon2proj0.DisplayDesc.TransY = 0
	Actor_34H_weapon2proj0.DisplayDesc.TransZ = 0
	Actor_34H_weapon2proj0.DisplayDesc.ScaleX = 0.05
	Actor_34H_weapon2proj0.DisplayDesc.ScaleY = 0.05
	Actor_34H_weapon2proj0.DisplayDesc.ScaleZ = 0.05
	Actor_34H_weapon2proj0.DisplayDesc.RotX = 0
	Actor_34H_weapon2proj0.DisplayDesc.RotY = 0
	Actor_34H_weapon2proj0.DisplayDesc.RotZ = 0
	Actor_34H_weapon2proj0.DisplayDesc.UseBillboard = true
	Actor_34H_weapon2proj0.PhysicDesc.Pos.X = 0
	Actor_34H_weapon2proj0.PhysicDesc.Pos.Y = 0
	Actor_34H_weapon2proj0.PhysicDesc.Pos.Z = 0
	Actor_34H_weapon2proj0.PhysicDesc.Pos.Rotation = 0
	Actor_34H_weapon2proj0.PhysicDesc.Density = 1
	Actor_34H_weapon2proj0.PhysicDesc.Collidable = false
	Actor_34H_weapon2proj0.PhysicDesc.SizeX = 0.05
	Actor_34H_weapon2proj0.PhysicDesc.SizeY = 0.05
	Actor_34H_weapon2proj0.PhysicDesc.SizeZ = 0.05
	Actor_34H_weapon2proj0.PhysicDesc.AllowFreeMove = true
	Actor_34H_weapon2proj0.PhysicDesc.Filename = ""
	Actor_34H_weapon2proj0:SetPhysicalActorType(3)
	Actor_34H_weapon2proj0:SetPhysicalShape(4)
	Actor_34H_weapon2proj0.UsableMode = ""
	Actor_34H_weapon2proj0.Power = 10
	Actor_34H_weapon2proj0.UseMana = 0
	Actor_34H_weapon2proj0.OffsetX = 2.5
	Actor_34H_weapon2proj0.OffsetY = 2.5
	Actor_34H_weapon2proj0.OffsetZ = 0
	Actor_34H_weapon2proj0.ForceX = 0.0005
	Actor_34H_weapon2proj0.ForceY = -0.0002
	Actor_34H_weapon2proj0.ForceYOnImpact = 0
	Actor_34H_weapon2proj0.NbBounce = 1
	Actor_34H_weapon2proj0.IgnoreGravity = true
	Actor_34H_weapon2proj0.LifeTime = 4000
	Actor_34H_weapon2proj0.Comeback = false
	Actor_34H_weapon2proj0.StartAnimFrame = 4
	Actor_34H_weapon2proj0.AngleOffset = 0
	Actor_34H_weapon2proj0.SoundAtStart = "Worlds/Lba1Original/Sound/SAMPLES027.voc.MP3"
	Actor_34H_weapon2proj0.SoundOnBounce = ""
	Actor_34H_weapon2proj0.ForceHurt = false
	Actor_34H_weapon2proj0.MultiShoot = false
	Actor_34H_weapon2proj0.UseTimer = false
	Actor_34H_weapon2proj0.Frequency = 1
	Actor_34H_weapon2proj0.FollowTarget = false
	Actor_34H:AddProjectileWeapon2(Actor_34H_weapon2proj0)
	Actor_34H_weapon2proj1 = ProjectileObjectDef()
	Actor_34H_weapon2proj1:SetRenderType(2)
	Actor_34H_weapon2proj1.DisplayDesc.ModelId = 0
	Actor_34H_weapon2proj1.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_34H_weapon2proj1.DisplayDesc.Outfit = ""
	Actor_34H_weapon2proj1.DisplayDesc.Weapon = ""
	Actor_34H_weapon2proj1.DisplayDesc.Mode = ""
	Actor_34H_weapon2proj1.DisplayDesc.UseLight = true
	Actor_34H_weapon2proj1.DisplayDesc.CastShadow = true
	Actor_34H_weapon2proj1.DisplayDesc.ColorR = 1
	Actor_34H_weapon2proj1.DisplayDesc.ColorG = 1
	Actor_34H_weapon2proj1.DisplayDesc.ColorB = 1
	Actor_34H_weapon2proj1.DisplayDesc.ColorA = 0.9
	Actor_34H_weapon2proj1.DisplayDesc.TransX = 0
	Actor_34H_weapon2proj1.DisplayDesc.TransY = 0
	Actor_34H_weapon2proj1.DisplayDesc.TransZ = 0
	Actor_34H_weapon2proj1.DisplayDesc.ScaleX = 0.05
	Actor_34H_weapon2proj1.DisplayDesc.ScaleY = 0.05
	Actor_34H_weapon2proj1.DisplayDesc.ScaleZ = 0.05
	Actor_34H_weapon2proj1.DisplayDesc.RotX = 0
	Actor_34H_weapon2proj1.DisplayDesc.RotY = 0
	Actor_34H_weapon2proj1.DisplayDesc.RotZ = 0
	Actor_34H_weapon2proj1.DisplayDesc.UseBillboard = true
	Actor_34H_weapon2proj1.PhysicDesc.Pos.X = 0
	Actor_34H_weapon2proj1.PhysicDesc.Pos.Y = 0
	Actor_34H_weapon2proj1.PhysicDesc.Pos.Z = 0
	Actor_34H_weapon2proj1.PhysicDesc.Pos.Rotation = 0
	Actor_34H_weapon2proj1.PhysicDesc.Density = 1
	Actor_34H_weapon2proj1.PhysicDesc.Collidable = false
	Actor_34H_weapon2proj1.PhysicDesc.SizeX = 0.05
	Actor_34H_weapon2proj1.PhysicDesc.SizeY = 0.05
	Actor_34H_weapon2proj1.PhysicDesc.SizeZ = 0.05
	Actor_34H_weapon2proj1.PhysicDesc.AllowFreeMove = true
	Actor_34H_weapon2proj1.PhysicDesc.Filename = ""
	Actor_34H_weapon2proj1:SetPhysicalActorType(3)
	Actor_34H_weapon2proj1:SetPhysicalShape(4)
	Actor_34H_weapon2proj1.UsableMode = ""
	Actor_34H_weapon2proj1.Power = 10
	Actor_34H_weapon2proj1.UseMana = 0
	Actor_34H_weapon2proj1.OffsetX = 2.5
	Actor_34H_weapon2proj1.OffsetY = 2.5
	Actor_34H_weapon2proj1.OffsetZ = 0
	Actor_34H_weapon2proj1.ForceX = 0.0005
	Actor_34H_weapon2proj1.ForceY = -0.0002
	Actor_34H_weapon2proj1.ForceYOnImpact = 0
	Actor_34H_weapon2proj1.NbBounce = 1
	Actor_34H_weapon2proj1.IgnoreGravity = true
	Actor_34H_weapon2proj1.LifeTime = 4000
	Actor_34H_weapon2proj1.Comeback = false
	Actor_34H_weapon2proj1.StartAnimFrame = 4
	Actor_34H_weapon2proj1.AngleOffset = 4
	Actor_34H_weapon2proj1.SoundAtStart = ""
	Actor_34H_weapon2proj1.SoundOnBounce = ""
	Actor_34H_weapon2proj1.ForceHurt = false
	Actor_34H_weapon2proj1.MultiShoot = false
	Actor_34H_weapon2proj1.UseTimer = false
	Actor_34H_weapon2proj1.Frequency = 1
	Actor_34H_weapon2proj1.FollowTarget = false
	Actor_34H:AddProjectileWeapon2(Actor_34H_weapon2proj1)
	Actor_34H_weapon2proj2 = ProjectileObjectDef()
	Actor_34H_weapon2proj2:SetRenderType(2)
	Actor_34H_weapon2proj2.DisplayDesc.ModelId = 0
	Actor_34H_weapon2proj2.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_34H_weapon2proj2.DisplayDesc.Outfit = ""
	Actor_34H_weapon2proj2.DisplayDesc.Weapon = ""
	Actor_34H_weapon2proj2.DisplayDesc.Mode = ""
	Actor_34H_weapon2proj2.DisplayDesc.UseLight = true
	Actor_34H_weapon2proj2.DisplayDesc.CastShadow = true
	Actor_34H_weapon2proj2.DisplayDesc.ColorR = 1
	Actor_34H_weapon2proj2.DisplayDesc.ColorG = 1
	Actor_34H_weapon2proj2.DisplayDesc.ColorB = 1
	Actor_34H_weapon2proj2.DisplayDesc.ColorA = 0.9
	Actor_34H_weapon2proj2.DisplayDesc.TransX = 0
	Actor_34H_weapon2proj2.DisplayDesc.TransY = 0
	Actor_34H_weapon2proj2.DisplayDesc.TransZ = 0
	Actor_34H_weapon2proj2.DisplayDesc.ScaleX = 0.05
	Actor_34H_weapon2proj2.DisplayDesc.ScaleY = 0.05
	Actor_34H_weapon2proj2.DisplayDesc.ScaleZ = 0.05
	Actor_34H_weapon2proj2.DisplayDesc.RotX = 0
	Actor_34H_weapon2proj2.DisplayDesc.RotY = 0
	Actor_34H_weapon2proj2.DisplayDesc.RotZ = 0
	Actor_34H_weapon2proj2.DisplayDesc.UseBillboard = true
	Actor_34H_weapon2proj2.PhysicDesc.Pos.X = 0
	Actor_34H_weapon2proj2.PhysicDesc.Pos.Y = 0
	Actor_34H_weapon2proj2.PhysicDesc.Pos.Z = 0
	Actor_34H_weapon2proj2.PhysicDesc.Pos.Rotation = 0
	Actor_34H_weapon2proj2.PhysicDesc.Density = 1
	Actor_34H_weapon2proj2.PhysicDesc.Collidable = false
	Actor_34H_weapon2proj2.PhysicDesc.SizeX = 0.05
	Actor_34H_weapon2proj2.PhysicDesc.SizeY = 0.05
	Actor_34H_weapon2proj2.PhysicDesc.SizeZ = 0.05
	Actor_34H_weapon2proj2.PhysicDesc.AllowFreeMove = true
	Actor_34H_weapon2proj2.PhysicDesc.Filename = ""
	Actor_34H_weapon2proj2:SetPhysicalActorType(3)
	Actor_34H_weapon2proj2:SetPhysicalShape(4)
	Actor_34H_weapon2proj2.UsableMode = ""
	Actor_34H_weapon2proj2.Power = 10
	Actor_34H_weapon2proj2.UseMana = 0
	Actor_34H_weapon2proj2.OffsetX = 2.5
	Actor_34H_weapon2proj2.OffsetY = 2.5
	Actor_34H_weapon2proj2.OffsetZ = 0
	Actor_34H_weapon2proj2.ForceX = 0.0005
	Actor_34H_weapon2proj2.ForceY = -0.0002
	Actor_34H_weapon2proj2.ForceYOnImpact = 0
	Actor_34H_weapon2proj2.NbBounce = 1
	Actor_34H_weapon2proj2.IgnoreGravity = true
	Actor_34H_weapon2proj2.LifeTime = 4000
	Actor_34H_weapon2proj2.Comeback = false
	Actor_34H_weapon2proj2.StartAnimFrame = 4
	Actor_34H_weapon2proj2.AngleOffset = -4
	Actor_34H_weapon2proj2.SoundAtStart = ""
	Actor_34H_weapon2proj2.SoundOnBounce = ""
	Actor_34H_weapon2proj2.ForceHurt = false
	Actor_34H_weapon2proj2.MultiShoot = false
	Actor_34H_weapon2proj2.UseTimer = false
	Actor_34H_weapon2proj2.Frequency = 1
	Actor_34H_weapon2proj2.FollowTarget = false
	Actor_34H:AddProjectileWeapon2(Actor_34H_weapon2proj2)
	Actor_34H:SetAttackFunction("ActorRotateAttackDistanceAndContactPlayer")
	Actor_34H:AddGivenItem(1,1,1,0.3,1)
	Actor_34H:AddGivenItem(2,1,1,0.3,1)
	Actor_34H:AddGivenItem(8,2,2,0.4,1)
	Actor_34H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_34H)

	Actor_35 = ActorObjectInfo(35)
	Actor_35:SetRenderType(3)
	Actor_35.HitPowerOnTouch = -1
	Actor_35.ExcludeFromNavMesh = false
	Actor_35.DisplayDesc.ModelId = 0
	Actor_35.DisplayDesc.ModelName = "GroboClone"
	Actor_35.DisplayDesc.Outfit = "Yellow"
	Actor_35.DisplayDesc.Weapon = "No"
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
	Actor_35.DisplayDesc.UseBillboard = false
	Actor_35.DisplayDesc.ColorMaterialType = 4
	Actor_35.DisplayDesc.MatAmbientColorR = -0.2
	Actor_35.DisplayDesc.MatAmbientColorG = -0.2
	Actor_35.DisplayDesc.MatAmbientColorB = -0.2
	Actor_35.DisplayDesc.MatAmbientColorA = 1
	Actor_35.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_35.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_35.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_35.DisplayDesc.MatDiffuseColorA = 1
	Actor_35.DisplayDesc.MatSpecularColorR = 0
	Actor_35.DisplayDesc.MatSpecularColorG = 0
	Actor_35.DisplayDesc.MatSpecularColorB = 0
	Actor_35.DisplayDesc.MatSpecularColorA = 1
	Actor_35.DisplayDesc.MatEmissionColorR = 0
	Actor_35.DisplayDesc.MatEmissionColorG = 0
	Actor_35.DisplayDesc.MatEmissionColorB = 0
	Actor_35.DisplayDesc.MatEmissionColorA = 1
	Actor_35.DisplayDesc.MatShininess = 0
	Actor_35.PhysicDesc.Pos.X = 4.5
	Actor_35.PhysicDesc.Pos.Y = 5
	Actor_35.PhysicDesc.Pos.Z = 56.5
	Actor_35.PhysicDesc.Pos.Rotation = 180
	Actor_35.PhysicDesc.Density = 1
	Actor_35.PhysicDesc.Collidable = true
	Actor_35.PhysicDesc.SizeX = 1.5
	Actor_35.PhysicDesc.SizeY = 5
	Actor_35.PhysicDesc.SizeZ = 1.5
	Actor_35.PhysicDesc.AllowFreeMove = true
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
	Actor_35H_dia_c0 = DialogPart()
	Actor_35H_dia_c0:SetResetDialog(false)
	Actor_35H_dia_c0:AddText(0)
	Actor_35H_dia_c0_c0 = DialogPart()
	Actor_35H_dia_c0_c0:SetResetDialog(false)
	Actor_35H_dia_c0_c0:AddText(52)
	Actor_35H_dia_c0:AddChild(Actor_35H_dia_c0_c0)
	Actor_35H_dia:AddChild(Actor_35H_dia_c0)
	Actor_35H:SetRootDialog(Actor_35H_dia)
	Actor_35H:SetNpcName(-1)
	Actor_35H:SetSimpleDialog(false)
	Actor_35H:SetAggresive(true)
	Actor_35H:SetLife(50)
	Actor_35H:SetMana(50)
	Actor_35H:SetArmor(0)
	Actor_35H:SetAttackActiDist(6)
	Actor_35H:SetAttackActiDistDiscrete(4)
	Actor_35H:SetAttackActiDistHidden(2)
	Actor_35H:SetAttackStopDist(16)
	Actor_35H:SetRespawnTimeInSec(10)
	Actor_35H:SetWeapon1Type(1)
	Actor_35H:SetWeapon1Power(10)
	Actor_35H:SetWeapon1ReachDistance(2)
	Actor_35H:Setuseweapon1animation("Use1Weapon")
	Actor_35H:SetWeapon2Type(2)
	Actor_35H:SetWeapon2Power(0)
	Actor_35H:SetWeapon2ReachDistance(1)
	Actor_35H:Setuseweapon2animation("UseWeapon")
	Actor_35H:SetAttackFunction("ActorAttackContactPlayer")
	Actor_35H:Setchasinganimation("Run")
	Actor_35H:AddGivenItem(1,1,1,0.3,1)
	Actor_35H:AddGivenItem(2,1,1,0.3,1)
	Actor_35H:AddGivenItem(8,2,2,0.4,1)
	Actor_35H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_35H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 10, 4, 1, true)
	Trigger_1:SetPosition(32, 15, 0.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1:SetActivateOnJump(true)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map001_1")
	Trigger_1_act1:SetSpawning(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 4, 1, true)
	Trigger_2:SetPosition(2.5, 5, 63.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2:SetActivateOnJump(true)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map002_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 11, 5.5, 1, true)
	Trigger_3:SetPosition(19.5, 0, 63.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3:SetActivateOnJump(true)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map002_1")
	Trigger_3_act1:SetSpawning(4)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit3", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 8, 5.5, 1, true)
	Trigger_4:SetPosition(51, 0, 63.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4:SetActivateOnJump(true)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map002_1")
	Trigger_4_act1:SetSpawning(5)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit4", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 4, 3, true)
	Trigger_5:SetPosition(15.5, 0, 41.5)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5:SetActivateOnJump(true)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map007_1")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit5", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 2, 5, 2, true)
	Trigger_6:SetPosition(20, 0, 50)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6:SetActivateOnJump(true)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map099_1")
	Trigger_6_act1:SetSpawning(2)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit6", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 3, 2.5, 3, true)
	Trigger_7:SetPosition(37.5, 8, 7.5)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7:SetActivateOnJump(true)
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
	Trigger_19:SetActivateOnJump(true)
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
	Trigger_20:SetActivateOnJump(true)
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
	Trigger_21:SetActivateOnJump(true)
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
	Trigger_22:SetActivateOnJump(true)
	Trigger_22_act1 = OpenDoorAction()
	Trigger_22_act1:SetActorId(15)
	Trigger_22:SetAction1(Trigger_22_act1)
	Trigger_22_act2 = CloseDoorAction()
	Trigger_22_act2:SetActorId(15)
	Trigger_22:SetAction2(Trigger_22_act2)
	environment:AddTrigger(Trigger_22)

end
