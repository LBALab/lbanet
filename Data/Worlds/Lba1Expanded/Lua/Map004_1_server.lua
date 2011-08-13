function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(28)
	Spawn_1:SetPosY(1.01)
	Spawn_1:SetPosZ(38.5)
	Spawn_1:SetName("spawning0")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(21.5)
	Spawn_2:SetPosY(0.01)
	Spawn_2:SetPosZ(2.5)
	Spawn_2:SetName("spawning1")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(4)
	Spawn_3:SetPosY(16.01)
	Spawn_3:SetPosZ(56.5)
	Spawn_3:SetName("spawning10")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(45.5)
	Spawn_4:SetPosY(0.01)
	Spawn_4:SetPosZ(2)
	Spawn_4:SetName("spawning2")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(52)
	Spawn_5:SetPosY(1.01)
	Spawn_5:SetPosZ(25.5)
	Spawn_5:SetName("spawning3")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(17)
	Spawn_6:SetPosY(0.01)
	Spawn_6:SetPosZ(51)
	Spawn_6:SetName("spawning4")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(45)
	Spawn_7:SetPosY(1.01)
	Spawn_7:SetPosZ(59)
	Spawn_7:SetName("spawning5")
	environment:AddSpawn(Spawn_7)

	Spawn_8 = Spawn(8)
	Spawn_8:SetPosX(45)
	Spawn_8:SetPosY(1.01)
	Spawn_8:SetPosZ(59)
	Spawn_8:SetName("spawning6")
	environment:AddSpawn(Spawn_8)

	Spawn_9 = Spawn(9)
	Spawn_9:SetPosX(45)
	Spawn_9:SetPosY(1.01)
	Spawn_9:SetPosZ(59)
	Spawn_9:SetName("spawning7")
	environment:AddSpawn(Spawn_9)

	Spawn_10 = Spawn(10)
	Spawn_10:SetPosX(45)
	Spawn_10:SetPosY(1.01)
	Spawn_10:SetPosZ(59)
	Spawn_10:SetName("spawning8")
	environment:AddSpawn(Spawn_10)

	Spawn_11 = Spawn(11)
	Spawn_11:SetPosX(45)
	Spawn_11:SetPosY(1.01)
	Spawn_11:SetPosZ(59)
	Spawn_11:SetName("spawning9")
	environment:AddSpawn(Spawn_11)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.HitPowerOnTouch = -1
	Actor_1.ExcludeFromNavMesh = false
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map4.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map4.phy"
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
	Actor_4.HitPowerOnTouch = -1
	Actor_4.ExcludeFromNavMesh = false
	Actor_4.DisplayDesc.ModelId = 0
	Actor_4.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite011.osgb"
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
	Actor_4.DisplayDesc.UseBillboard = false
	Actor_4.PhysicDesc.Pos.X = 27.5
	Actor_4.PhysicDesc.Pos.Y = 1
	Actor_4.PhysicDesc.Pos.Z = 38.5
	Actor_4.PhysicDesc.Pos.Rotation = 0
	Actor_4.PhysicDesc.Density = 1
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 1
	Actor_4.PhysicDesc.SizeY = 8
	Actor_4.PhysicDesc.SizeZ = 3.2
	Actor_4.PhysicDesc.AllowFreeMove = true
	Actor_4.PhysicDesc.Filename = ""
	Actor_4:SetPhysicalActorType(2)
	Actor_4:SetPhysicalShape(2)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 0
	Actor_4.ExtraInfo.NameColorG = 0
	Actor_4.ExtraInfo.NameColorB = 0
	Actor_4.ExtraInfo.Display = false
	Actor_4.LifeInfo.Display = false
	Actor_4H = DoorHandler(Actor_4,0,1,3.3,0.004,false)
	Actor_4_Sc0 = ASPWaitForSignal(1)
	Actor_4H:AddScriptPart(Actor_4_Sc0)
	Actor_4_Sc1 = ASPGoTo(27.5,1,41.8,0.004)
	Actor_4H:AddScriptPart(Actor_4_Sc1)
	Actor_4_Sc2 = ASPWaitForSignal(2)
	Actor_4H:AddScriptPart(Actor_4_Sc2)
	Actor_4_Sc3 = ASPGoTo(27.5,1,38.5,0.004)
	Actor_4H:AddScriptPart(Actor_4_Sc3)
	environment:AddActorObject(Actor_4H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(1)
	Actor_5.HitPowerOnTouch = -1
	Actor_5.ExcludeFromNavMesh = false
	Actor_5.DisplayDesc.ModelId = 0
	Actor_5.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite011.osgb"
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
	Actor_5.DisplayDesc.UseBillboard = false
	Actor_5.PhysicDesc.Pos.X = 50.5
	Actor_5.PhysicDesc.Pos.Y = 1
	Actor_5.PhysicDesc.Pos.Z = 25.5
	Actor_5.PhysicDesc.Pos.Rotation = 0
	Actor_5.PhysicDesc.Density = 1
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = 1
	Actor_5.PhysicDesc.SizeY = 8
	Actor_5.PhysicDesc.SizeZ = 3.2
	Actor_5.PhysicDesc.AllowFreeMove = true
	Actor_5.PhysicDesc.Filename = ""
	Actor_5:SetPhysicalActorType(2)
	Actor_5:SetPhysicalShape(2)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = 0
	Actor_5.ExtraInfo.NameColorG = 0
	Actor_5.ExtraInfo.NameColorB = 0
	Actor_5.ExtraInfo.Display = false
	Actor_5.LifeInfo.Display = false
	Actor_5H = DoorHandler(Actor_5,1,1,90,0.1,false)
	Actor_5_Sc0 = ASPWaitForSignal(1)
	Actor_5H:AddScriptPart(Actor_5_Sc0)
	Actor_5_Sc1 = ASPRotateFromPoint(90,50.5,1,27.1,0.1)
	Actor_5H:AddScriptPart(Actor_5_Sc1)
	Actor_5_Sc2 = ASPWaitForSignal(2)
	Actor_5H:AddScriptPart(Actor_5_Sc2)
	Actor_5_Sc3 = ASPRotateFromPoint(0,50.5,1,27.1,0.1)
	Actor_5H:AddScriptPart(Actor_5_Sc3)
	Actor_5_Sc4 = ASPTeleportTo(50.5,1,25.5)
	Actor_5H:AddScriptPart(Actor_5_Sc4)
	Actor_5_Sc5 = ASPSetRotation(0)
	Actor_5H:AddScriptPart(Actor_5_Sc5)
	environment:AddActorObject(Actor_5H)

	Actor_6 = ActorObjectInfo(6)
	Actor_6:SetRenderType(1)
	Actor_6.HitPowerOnTouch = -1
	Actor_6.ExcludeFromNavMesh = false
	Actor_6.DisplayDesc.ModelId = 0
	Actor_6.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite027.osgb"
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
	Actor_6.DisplayDesc.UseBillboard = false
	Actor_6.PhysicDesc.Pos.X = 5
	Actor_6.PhysicDesc.Pos.Y = 15.1
	Actor_6.PhysicDesc.Pos.Z = 58
	Actor_6.PhysicDesc.Pos.Rotation = 0
	Actor_6.PhysicDesc.Density = 1
	Actor_6.PhysicDesc.Collidable = true
	Actor_6.PhysicDesc.SizeX = 2
	Actor_6.PhysicDesc.SizeY = 1
	Actor_6.PhysicDesc.SizeZ = 2
	Actor_6.PhysicDesc.AllowFreeMove = true
	Actor_6.PhysicDesc.Filename = ""
	Actor_6:SetPhysicalActorType(2)
	Actor_6:SetPhysicalShape(2)
	Actor_6.ExtraInfo.Name = ""
	Actor_6.ExtraInfo.NameColorR = 0
	Actor_6.ExtraInfo.NameColorG = 0
	Actor_6.ExtraInfo.NameColorB = 0
	Actor_6.ExtraInfo.Display = false
	Actor_6.LifeInfo.Display = false
	Actor_6H = DoorHandler(Actor_6,0,0,1.6,0.006,false)
	Actor_6_Sc0 = ASPWaitForSignal(1)
	Actor_6H:AddScriptPart(Actor_6_Sc0)
	Actor_6_Sc1 = ASPGoTo(5,15.1,56.4,0.006)
	Actor_6H:AddScriptPart(Actor_6_Sc1)
	Actor_6_Sc2 = ASPWaitForSignal(2)
	Actor_6H:AddScriptPart(Actor_6_Sc2)
	Actor_6_Sc3 = ASPGoTo(5,15.1,58,0.006)
	Actor_6H:AddScriptPart(Actor_6_Sc3)
	environment:AddActorObject(Actor_6H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(3)
	Actor_7.HitPowerOnTouch = -1
	Actor_7.ExcludeFromNavMesh = false
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "RabbiClone"
	Actor_7.DisplayDesc.Outfit = "Yellow"
	Actor_7.DisplayDesc.Weapon = "No"
	Actor_7.DisplayDesc.Mode = "Normal"
	Actor_7.DisplayDesc.UseLight = true
	Actor_7.DisplayDesc.CastShadow = true
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
	Actor_7.DisplayDesc.UseBillboard = false
	Actor_7.DisplayDesc.ColorMaterialType = 4
	Actor_7.DisplayDesc.MatAmbientColorR = -0.2
	Actor_7.DisplayDesc.MatAmbientColorG = -0.2
	Actor_7.DisplayDesc.MatAmbientColorB = -0.2
	Actor_7.DisplayDesc.MatAmbientColorA = 1
	Actor_7.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_7.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_7.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_7.DisplayDesc.MatDiffuseColorA = 1
	Actor_7.DisplayDesc.MatSpecularColorR = 0
	Actor_7.DisplayDesc.MatSpecularColorG = 0
	Actor_7.DisplayDesc.MatSpecularColorB = 0
	Actor_7.DisplayDesc.MatSpecularColorA = 1
	Actor_7.DisplayDesc.MatEmissionColorR = 0
	Actor_7.DisplayDesc.MatEmissionColorG = 0
	Actor_7.DisplayDesc.MatEmissionColorB = 0
	Actor_7.DisplayDesc.MatEmissionColorA = 1
	Actor_7.DisplayDesc.MatShininess = 0
	Actor_7.PhysicDesc.Pos.X = 47.1172
	Actor_7.PhysicDesc.Pos.Y = 0
	Actor_7.PhysicDesc.Pos.Z = 9.26563
	Actor_7.PhysicDesc.Pos.Rotation = 514
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 1
	Actor_7.PhysicDesc.SizeY = 6
	Actor_7.PhysicDesc.SizeZ = 1
	Actor_7.PhysicDesc.AllowFreeMove = true
	Actor_7.PhysicDesc.Filename = ""
	Actor_7:SetPhysicalActorType(2)
	Actor_7:SetPhysicalShape(2)
	Actor_7.ExtraInfo.Name = ""
	Actor_7.ExtraInfo.NameColorR = 0
	Actor_7.ExtraInfo.NameColorG = 0
	Actor_7.ExtraInfo.NameColorB = 0
	Actor_7.ExtraInfo.Display = false
	Actor_7.LifeInfo.Display = false
	Actor_7H = NPCHandler(Actor_7)
	Actor_7H_dia = DialogPart()
	Actor_7H_dia:SetResetDialog(false)
	Actor_7H:SetRootDialog(Actor_7H_dia)
	Actor_7H:SetNpcName(-1)
	Actor_7H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_7H)

	Actor_9 = ActorObjectInfo(9)
	Actor_9:SetRenderType(3)
	Actor_9.HitPowerOnTouch = -1
	Actor_9.ExcludeFromNavMesh = false
	Actor_9.DisplayDesc.ModelId = 0
	Actor_9.DisplayDesc.ModelName = "Quetch"
	Actor_9.DisplayDesc.Outfit = "Zoe"
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
	Actor_9.DisplayDesc.UseBillboard = false
	Actor_9.DisplayDesc.ColorMaterialType = 4
	Actor_9.DisplayDesc.MatAmbientColorR = -0.2
	Actor_9.DisplayDesc.MatAmbientColorG = -0.2
	Actor_9.DisplayDesc.MatAmbientColorB = -0.2
	Actor_9.DisplayDesc.MatAmbientColorA = 1
	Actor_9.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_9.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_9.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_9.DisplayDesc.MatDiffuseColorA = 1
	Actor_9.DisplayDesc.MatSpecularColorR = 0
	Actor_9.DisplayDesc.MatSpecularColorG = 0
	Actor_9.DisplayDesc.MatSpecularColorB = 0
	Actor_9.DisplayDesc.MatSpecularColorA = 1
	Actor_9.DisplayDesc.MatEmissionColorR = 0
	Actor_9.DisplayDesc.MatEmissionColorG = 0
	Actor_9.DisplayDesc.MatEmissionColorB = 0
	Actor_9.DisplayDesc.MatEmissionColorA = 1
	Actor_9.DisplayDesc.MatShininess = 0
	Actor_9.PhysicDesc.Pos.X = 29
	Actor_9.PhysicDesc.Pos.Y = 1
	Actor_9.PhysicDesc.Pos.Z = 38
	Actor_9.PhysicDesc.Pos.Rotation = 25
	Actor_9.PhysicDesc.Density = 1
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 1
	Actor_9.PhysicDesc.SizeY = 5
	Actor_9.PhysicDesc.SizeZ = 1
	Actor_9.PhysicDesc.AllowFreeMove = true
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
	Actor_9H_dia_c0 = DialogPart()
	Actor_9H_dia_c0:SetResetDialog(false)
	Actor_9H_dia_c0:AddText(1090)
	Actor_9H_dia_c0_c0 = DialogPart()
	Actor_9H_dia_c0_c0_act = OpenShopAction()
	Actor_9H_dia_c0_c0_act:SetCurrencyItem(8)
	Actor_9H_dia_c0_c0_act:AddItem(31, 5)
	Actor_9H_dia_c0_c0_act:AddItem(32, 5)
	Actor_9H_dia_c0_c0_act:AddItem(33, 5)
	Actor_9H_dia_c0_c0_act:AddItem(34, 5)
	Actor_9H_dia_c0_c0_act:AddItem(35, 5)
	Actor_9H_dia_c0_c0_act:AddItem(36, 10)
	Actor_9H_dia_c0_c0_act:AddItem(37, 10)
	Actor_9H_dia_c0_c0_act:AddItem(38, 10)
	Actor_9H_dia_c0_c0_act:AddItem(39, 10)
	Actor_9H_dia_c0_c0_act:AddItem(40, 10)
	Actor_9H_dia_c0_c0:SetAction(Actor_9H_dia_c0_c0_act)
	Actor_9H_dia_c0_c0:SetResetDialog(false)
	Actor_9H_dia_c0_c0:AddText(1060)
	Actor_9H_dia_c0:AddChild(Actor_9H_dia_c0_c0)
	Actor_9H_dia:AddChild(Actor_9H_dia_c0)
	Actor_9H:SetRootDialog(Actor_9H_dia)
	Actor_9H:SetNpcName(1)
	Actor_9H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_9H)

	Actor_10 = ActorObjectInfo(10)
	Actor_10:SetRenderType(3)
	Actor_10.HitPowerOnTouch = -1
	Actor_10.ExcludeFromNavMesh = false
	Actor_10.DisplayDesc.ModelId = 0
	Actor_10.DisplayDesc.ModelName = "Rabbibunny"
	Actor_10.DisplayDesc.Outfit = "Orange"
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
	Actor_10.DisplayDesc.UseBillboard = false
	Actor_10.DisplayDesc.ColorMaterialType = 4
	Actor_10.DisplayDesc.MatAmbientColorR = -0.2
	Actor_10.DisplayDesc.MatAmbientColorG = -0.2
	Actor_10.DisplayDesc.MatAmbientColorB = -0.2
	Actor_10.DisplayDesc.MatAmbientColorA = 1
	Actor_10.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_10.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_10.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_10.DisplayDesc.MatDiffuseColorA = 1
	Actor_10.DisplayDesc.MatSpecularColorR = 0
	Actor_10.DisplayDesc.MatSpecularColorG = 0
	Actor_10.DisplayDesc.MatSpecularColorB = 0
	Actor_10.DisplayDesc.MatSpecularColorA = 1
	Actor_10.DisplayDesc.MatEmissionColorR = 0
	Actor_10.DisplayDesc.MatEmissionColorG = 0
	Actor_10.DisplayDesc.MatEmissionColorB = 0
	Actor_10.DisplayDesc.MatEmissionColorA = 1
	Actor_10.DisplayDesc.MatShininess = 0
	Actor_10.PhysicDesc.Pos.X = 53.3125
	Actor_10.PhysicDesc.Pos.Y = 1
	Actor_10.PhysicDesc.Pos.Z = 26.1875
	Actor_10.PhysicDesc.Pos.Rotation = 347
	Actor_10.PhysicDesc.Density = 1
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 1
	Actor_10.PhysicDesc.SizeY = 5
	Actor_10.PhysicDesc.SizeZ = 1
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
	Actor_10H = NPCHandler(Actor_10)
	Actor_10H_dia = DialogPart()
	Actor_10H_dia:SetResetDialog(false)
	Actor_10H:SetRootDialog(Actor_10H_dia)
	Actor_10H:SetNpcName(-1)
	Actor_10H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_10H)

	Actor_11 = ActorObjectInfo(11)
	Actor_11:SetRenderType(3)
	Actor_11.HitPowerOnTouch = -1
	Actor_11.ExcludeFromNavMesh = false
	Actor_11.DisplayDesc.ModelId = 0
	Actor_11.DisplayDesc.ModelName = "Rabbibunny"
	Actor_11.DisplayDesc.Outfit = "Orange"
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
	Actor_11.DisplayDesc.UseBillboard = false
	Actor_11.DisplayDesc.ColorMaterialType = 4
	Actor_11.DisplayDesc.MatAmbientColorR = -0.2
	Actor_11.DisplayDesc.MatAmbientColorG = -0.2
	Actor_11.DisplayDesc.MatAmbientColorB = -0.2
	Actor_11.DisplayDesc.MatAmbientColorA = 1
	Actor_11.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_11.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_11.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_11.DisplayDesc.MatDiffuseColorA = 1
	Actor_11.DisplayDesc.MatSpecularColorR = 0
	Actor_11.DisplayDesc.MatSpecularColorG = 0
	Actor_11.DisplayDesc.MatSpecularColorB = 0
	Actor_11.DisplayDesc.MatSpecularColorA = 1
	Actor_11.DisplayDesc.MatEmissionColorR = 0
	Actor_11.DisplayDesc.MatEmissionColorG = 0
	Actor_11.DisplayDesc.MatEmissionColorB = 0
	Actor_11.DisplayDesc.MatEmissionColorA = 1
	Actor_11.DisplayDesc.MatShininess = 0
	Actor_11.PhysicDesc.Pos.X = 44
	Actor_11.PhysicDesc.Pos.Y = 1
	Actor_11.PhysicDesc.Pos.Z = 29
	Actor_11.PhysicDesc.Pos.Rotation = 25
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 1
	Actor_11.PhysicDesc.SizeY = 5
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
	Actor_11H = NPCHandler(Actor_11)
	Actor_11H_dia = DialogPart()
	Actor_11H_dia:SetResetDialog(false)
	Actor_11H:SetRootDialog(Actor_11H_dia)
	Actor_11H:SetNpcName(-1)
	Actor_11H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_11H)

	Actor_13 = ActorObjectInfo(13)
	Actor_13:SetRenderType(3)
	Actor_13.HitPowerOnTouch = -1
	Actor_13.ExcludeFromNavMesh = false
	Actor_13.DisplayDesc.ModelId = 0
	Actor_13.DisplayDesc.ModelName = "RabbiClone"
	Actor_13.DisplayDesc.Outfit = "Yellow"
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
	Actor_13.DisplayDesc.UseBillboard = false
	Actor_13.DisplayDesc.ColorMaterialType = 4
	Actor_13.DisplayDesc.MatAmbientColorR = -0.2
	Actor_13.DisplayDesc.MatAmbientColorG = -0.2
	Actor_13.DisplayDesc.MatAmbientColorB = -0.2
	Actor_13.DisplayDesc.MatAmbientColorA = 1
	Actor_13.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_13.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_13.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_13.DisplayDesc.MatDiffuseColorA = 1
	Actor_13.DisplayDesc.MatSpecularColorR = 0
	Actor_13.DisplayDesc.MatSpecularColorG = 0
	Actor_13.DisplayDesc.MatSpecularColorB = 0
	Actor_13.DisplayDesc.MatSpecularColorA = 1
	Actor_13.DisplayDesc.MatEmissionColorR = 0
	Actor_13.DisplayDesc.MatEmissionColorG = 0
	Actor_13.DisplayDesc.MatEmissionColorB = 0
	Actor_13.DisplayDesc.MatEmissionColorA = 1
	Actor_13.DisplayDesc.MatShininess = 0
	Actor_13.PhysicDesc.Pos.X = 16
	Actor_13.PhysicDesc.Pos.Y = 6
	Actor_13.PhysicDesc.Pos.Z = 36
	Actor_13.PhysicDesc.Pos.Rotation = 25
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 1
	Actor_13.PhysicDesc.SizeY = 6
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
	Actor_13H = NPCHandler(Actor_13)
	Actor_13H_dia = DialogPart()
	Actor_13H_dia:SetResetDialog(false)
	Actor_13H:SetRootDialog(Actor_13H_dia)
	Actor_13H:SetNpcName(-1)
	Actor_13H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_13H)

	Actor_14 = ActorObjectInfo(14)
	Actor_14:SetRenderType(3)
	Actor_14.HitPowerOnTouch = -1
	Actor_14.ExcludeFromNavMesh = false
	Actor_14.DisplayDesc.ModelId = 0
	Actor_14.DisplayDesc.ModelName = "Catamaran"
	Actor_14.DisplayDesc.Outfit = "No"
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
	Actor_14.DisplayDesc.UseBillboard = false
	Actor_14.DisplayDesc.ColorMaterialType = 4
	Actor_14.DisplayDesc.MatAmbientColorR = -0.2
	Actor_14.DisplayDesc.MatAmbientColorG = -0.2
	Actor_14.DisplayDesc.MatAmbientColorB = -0.2
	Actor_14.DisplayDesc.MatAmbientColorA = 1
	Actor_14.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_14.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_14.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_14.DisplayDesc.MatDiffuseColorA = 1
	Actor_14.DisplayDesc.MatSpecularColorR = 0
	Actor_14.DisplayDesc.MatSpecularColorG = 0
	Actor_14.DisplayDesc.MatSpecularColorB = 0
	Actor_14.DisplayDesc.MatSpecularColorA = 1
	Actor_14.DisplayDesc.MatEmissionColorR = 0
	Actor_14.DisplayDesc.MatEmissionColorG = 0
	Actor_14.DisplayDesc.MatEmissionColorB = 0
	Actor_14.DisplayDesc.MatEmissionColorA = 1
	Actor_14.DisplayDesc.MatShininess = 0
	Actor_14.PhysicDesc.Pos.X = 60.375
	Actor_14.PhysicDesc.Pos.Y = 0
	Actor_14.PhysicDesc.Pos.Z = 56
	Actor_14.PhysicDesc.Pos.Rotation = 433
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 5
	Actor_14.PhysicDesc.SizeY = 1
	Actor_14.PhysicDesc.SizeZ = 5
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
	Actor_14H = NPCHandler(Actor_14)
	Actor_14H_dia = DialogPart()
	Actor_14H_dia:SetResetDialog(false)
	Actor_14H:SetRootDialog(Actor_14H_dia)
	Actor_14H:SetNpcName(-1)
	Actor_14H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_14H)

	Actor_15 = ActorObjectInfo(15)
	Actor_15:SetRenderType(3)
	Actor_15.HitPowerOnTouch = -1
	Actor_15.ExcludeFromNavMesh = false
	Actor_15.DisplayDesc.ModelId = 0
	Actor_15.DisplayDesc.ModelName = "Object"
	Actor_15.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_15.DisplayDesc.UseBillboard = false
	Actor_15.DisplayDesc.ColorMaterialType = 4
	Actor_15.DisplayDesc.MatAmbientColorR = -0.2
	Actor_15.DisplayDesc.MatAmbientColorG = -0.2
	Actor_15.DisplayDesc.MatAmbientColorB = -0.2
	Actor_15.DisplayDesc.MatAmbientColorA = 1
	Actor_15.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_15.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_15.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_15.DisplayDesc.MatDiffuseColorA = 1
	Actor_15.DisplayDesc.MatSpecularColorR = 0
	Actor_15.DisplayDesc.MatSpecularColorG = 0
	Actor_15.DisplayDesc.MatSpecularColorB = 0
	Actor_15.DisplayDesc.MatSpecularColorA = 1
	Actor_15.DisplayDesc.MatEmissionColorR = 0
	Actor_15.DisplayDesc.MatEmissionColorG = 0
	Actor_15.DisplayDesc.MatEmissionColorB = 0
	Actor_15.DisplayDesc.MatEmissionColorA = 1
	Actor_15.DisplayDesc.MatShininess = 0
	Actor_15.PhysicDesc.Pos.X = 0
	Actor_15.PhysicDesc.Pos.Y = -1
	Actor_15.PhysicDesc.Pos.Z = 0
	Actor_15.PhysicDesc.Pos.Rotation = 25
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 0.5
	Actor_15.PhysicDesc.SizeY = 2
	Actor_15.PhysicDesc.SizeZ = 0.6
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
	Actor_15H = NPCHandler(Actor_15)
	Actor_15H_dia = DialogPart()
	Actor_15H_dia:SetResetDialog(false)
	Actor_15H:SetRootDialog(Actor_15H_dia)
	Actor_15H:SetNpcName(-1)
	Actor_15H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_15H)

	Actor_16 = ActorObjectInfo(16)
	Actor_16:SetRenderType(1)
	Actor_16.HitPowerOnTouch = -1
	Actor_16.ExcludeFromNavMesh = false
	Actor_16.DisplayDesc.ModelId = 0
	Actor_16.DisplayDesc.ModelName = "Worlds/Lba1Expanded/Models/mailbox.osgb"
	Actor_16.DisplayDesc.Outfit = ""
	Actor_16.DisplayDesc.Weapon = ""
	Actor_16.DisplayDesc.Mode = ""
	Actor_16.DisplayDesc.UseLight = true
	Actor_16.DisplayDesc.CastShadow = true
	Actor_16.DisplayDesc.ColorR = 1
	Actor_16.DisplayDesc.ColorG = 1
	Actor_16.DisplayDesc.ColorB = 1
	Actor_16.DisplayDesc.ColorA = 1
	Actor_16.DisplayDesc.TransX = 0
	Actor_16.DisplayDesc.TransY = 3.5
	Actor_16.DisplayDesc.TransZ = 0
	Actor_16.DisplayDesc.ScaleX = 0.005
	Actor_16.DisplayDesc.ScaleY = 0.005
	Actor_16.DisplayDesc.ScaleZ = 0.008
	Actor_16.DisplayDesc.RotX = -90
	Actor_16.DisplayDesc.RotY = 0
	Actor_16.DisplayDesc.RotZ = 90
	Actor_16:SetModelState(2)
	Actor_16.DisplayDesc.UseBillboard = false
	Actor_16.PhysicDesc.Pos.X = 33
	Actor_16.PhysicDesc.Pos.Y = 1
	Actor_16.PhysicDesc.Pos.Z = 42
	Actor_16.PhysicDesc.Pos.Rotation = 0
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 1
	Actor_16.PhysicDesc.SizeY = 4
	Actor_16.PhysicDesc.SizeZ = 0.5
	Actor_16.PhysicDesc.AllowFreeMove = true
	Actor_16.PhysicDesc.Filename = ""
	Actor_16:SetPhysicalActorType(1)
	Actor_16:SetPhysicalShape(2)
	Actor_16.ExtraInfo.Name = ""
	Actor_16.ExtraInfo.NameColorR = 1
	Actor_16.ExtraInfo.NameColorG = 1
	Actor_16.ExtraInfo.NameColorB = 1
	Actor_16.ExtraInfo.Display = false
	Actor_16.LifeInfo.Display = false
	Actor_16H = ActorHandler(Actor_16)
	environment:AddActorObject(Actor_16H)

	Actor_17 = ActorObjectInfo(17)
	Actor_17:SetRenderType(3)
	Actor_17.HitPowerOnTouch = -1
	Actor_17.ExcludeFromNavMesh = false
	Actor_17.DisplayDesc.ModelId = 0
	Actor_17.DisplayDesc.ModelName = "Soldier"
	Actor_17.DisplayDesc.Outfit = "Grass"
	Actor_17.DisplayDesc.Weapon = "rifle"
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
	Actor_17.PhysicDesc.Pos.X = 27
	Actor_17.PhysicDesc.Pos.Y = 1
	Actor_17.PhysicDesc.Pos.Z = 20
	Actor_17.PhysicDesc.Pos.Rotation = 90
	Actor_17.PhysicDesc.Density = 1
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 2
	Actor_17.PhysicDesc.SizeY = 5
	Actor_17.PhysicDesc.SizeZ = 2
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
	Actor_17H:SetAggresive(true)
	Actor_17H:SetLife(50)
	Actor_17H:SetMana(0)
	Actor_17H:SetArmor(0)
	Actor_17H:SetAttackActiDist(7)
	Actor_17H:SetAttackActiDistDiscrete(4)
	Actor_17H:SetAttackActiDistHidden(2)
	Actor_17H:SetAttackStopDist(10)
	Actor_17H:SetRespawnTimeInSec(10)
	Actor_17H:SetWeaponAnimAtStart(true)
	Actor_17H:SetWeapon1Type(1)
	Actor_17H:SetWeapon1Power(10)
	Actor_17H:SetWeapon1ReachDistance(2)
	Actor_17H:Setuseweapon1animation("Use1Weapon")
	Actor_17H:SetWeapon2Type(2)
	Actor_17H:SetWeapon2Power(0)
	Actor_17H:SetWeapon2ReachDistance(7)
	Actor_17H:Setuseweapon2animation("UseWeapon")
	Actor_17H_weapon2proj0 = ProjectileObjectDef()
	Actor_17H_weapon2proj0:SetRenderType(2)
	Actor_17H_weapon2proj0.DisplayDesc.ModelId = 0
	Actor_17H_weapon2proj0.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_17H_weapon2proj0.DisplayDesc.Outfit = ""
	Actor_17H_weapon2proj0.DisplayDesc.Weapon = ""
	Actor_17H_weapon2proj0.DisplayDesc.Mode = ""
	Actor_17H_weapon2proj0.DisplayDesc.UseLight = true
	Actor_17H_weapon2proj0.DisplayDesc.CastShadow = true
	Actor_17H_weapon2proj0.DisplayDesc.ColorR = 1
	Actor_17H_weapon2proj0.DisplayDesc.ColorG = 1
	Actor_17H_weapon2proj0.DisplayDesc.ColorB = 1
	Actor_17H_weapon2proj0.DisplayDesc.ColorA = 0.9
	Actor_17H_weapon2proj0.DisplayDesc.TransX = 0
	Actor_17H_weapon2proj0.DisplayDesc.TransY = 0
	Actor_17H_weapon2proj0.DisplayDesc.TransZ = 0
	Actor_17H_weapon2proj0.DisplayDesc.ScaleX = 0.05
	Actor_17H_weapon2proj0.DisplayDesc.ScaleY = 0.05
	Actor_17H_weapon2proj0.DisplayDesc.ScaleZ = 0.05
	Actor_17H_weapon2proj0.DisplayDesc.RotX = 0
	Actor_17H_weapon2proj0.DisplayDesc.RotY = 0
	Actor_17H_weapon2proj0.DisplayDesc.RotZ = 0
	Actor_17H_weapon2proj0.DisplayDesc.UseBillboard = true
	Actor_17H_weapon2proj0.PhysicDesc.Pos.X = 0
	Actor_17H_weapon2proj0.PhysicDesc.Pos.Y = 0
	Actor_17H_weapon2proj0.PhysicDesc.Pos.Z = 0
	Actor_17H_weapon2proj0.PhysicDesc.Pos.Rotation = 0
	Actor_17H_weapon2proj0.PhysicDesc.Density = 1
	Actor_17H_weapon2proj0.PhysicDesc.Collidable = false
	Actor_17H_weapon2proj0.PhysicDesc.SizeX = 0.05
	Actor_17H_weapon2proj0.PhysicDesc.SizeY = 0.05
	Actor_17H_weapon2proj0.PhysicDesc.SizeZ = 0.05
	Actor_17H_weapon2proj0.PhysicDesc.AllowFreeMove = true
	Actor_17H_weapon2proj0.PhysicDesc.Filename = ""
	Actor_17H_weapon2proj0:SetPhysicalActorType(3)
	Actor_17H_weapon2proj0:SetPhysicalShape(4)
	Actor_17H_weapon2proj0.UsableMode = ""
	Actor_17H_weapon2proj0.Power = 10
	Actor_17H_weapon2proj0.UseMana = 0
	Actor_17H_weapon2proj0.OffsetX = 2.5
	Actor_17H_weapon2proj0.OffsetY = 2.5
	Actor_17H_weapon2proj0.OffsetZ = 0
	Actor_17H_weapon2proj0.ForceX = 0.0005
	Actor_17H_weapon2proj0.ForceY = -0.0002
	Actor_17H_weapon2proj0.ForceYOnImpact = 0
	Actor_17H_weapon2proj0.NbBounce = 1
	Actor_17H_weapon2proj0.IgnoreGravity = true
	Actor_17H_weapon2proj0.LifeTime = 4000
	Actor_17H_weapon2proj0.Comeback = false
	Actor_17H_weapon2proj0.StartAnimFrame = 4
	Actor_17H_weapon2proj0.AngleOffset = 0
	Actor_17H_weapon2proj0.SoundAtStart = "Worlds/Lba1Original/Sound/SAMPLES027.voc.MP3"
	Actor_17H_weapon2proj0.SoundOnBounce = ""
	Actor_17H_weapon2proj0.ForceHurt = false
	Actor_17H_weapon2proj0.MultiShoot = false
	Actor_17H_weapon2proj0.UseTimer = false
	Actor_17H_weapon2proj0.Frequency = 1
	Actor_17H_weapon2proj0.FollowTarget = false
	Actor_17H:AddProjectileWeapon2(Actor_17H_weapon2proj0)
	Actor_17H_weapon2proj1 = ProjectileObjectDef()
	Actor_17H_weapon2proj1:SetRenderType(2)
	Actor_17H_weapon2proj1.DisplayDesc.ModelId = 0
	Actor_17H_weapon2proj1.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_17H_weapon2proj1.DisplayDesc.Outfit = ""
	Actor_17H_weapon2proj1.DisplayDesc.Weapon = ""
	Actor_17H_weapon2proj1.DisplayDesc.Mode = ""
	Actor_17H_weapon2proj1.DisplayDesc.UseLight = true
	Actor_17H_weapon2proj1.DisplayDesc.CastShadow = true
	Actor_17H_weapon2proj1.DisplayDesc.ColorR = 1
	Actor_17H_weapon2proj1.DisplayDesc.ColorG = 1
	Actor_17H_weapon2proj1.DisplayDesc.ColorB = 1
	Actor_17H_weapon2proj1.DisplayDesc.ColorA = 0.9
	Actor_17H_weapon2proj1.DisplayDesc.TransX = 0
	Actor_17H_weapon2proj1.DisplayDesc.TransY = 0
	Actor_17H_weapon2proj1.DisplayDesc.TransZ = 0
	Actor_17H_weapon2proj1.DisplayDesc.ScaleX = 0.05
	Actor_17H_weapon2proj1.DisplayDesc.ScaleY = 0.05
	Actor_17H_weapon2proj1.DisplayDesc.ScaleZ = 0.05
	Actor_17H_weapon2proj1.DisplayDesc.RotX = 0
	Actor_17H_weapon2proj1.DisplayDesc.RotY = 0
	Actor_17H_weapon2proj1.DisplayDesc.RotZ = 0
	Actor_17H_weapon2proj1.DisplayDesc.UseBillboard = true
	Actor_17H_weapon2proj1.PhysicDesc.Pos.X = 0
	Actor_17H_weapon2proj1.PhysicDesc.Pos.Y = 0
	Actor_17H_weapon2proj1.PhysicDesc.Pos.Z = 0
	Actor_17H_weapon2proj1.PhysicDesc.Pos.Rotation = 0
	Actor_17H_weapon2proj1.PhysicDesc.Density = 1
	Actor_17H_weapon2proj1.PhysicDesc.Collidable = false
	Actor_17H_weapon2proj1.PhysicDesc.SizeX = 0.05
	Actor_17H_weapon2proj1.PhysicDesc.SizeY = 0.05
	Actor_17H_weapon2proj1.PhysicDesc.SizeZ = 0.05
	Actor_17H_weapon2proj1.PhysicDesc.AllowFreeMove = true
	Actor_17H_weapon2proj1.PhysicDesc.Filename = ""
	Actor_17H_weapon2proj1:SetPhysicalActorType(3)
	Actor_17H_weapon2proj1:SetPhysicalShape(4)
	Actor_17H_weapon2proj1.UsableMode = ""
	Actor_17H_weapon2proj1.Power = 10
	Actor_17H_weapon2proj1.UseMana = 0
	Actor_17H_weapon2proj1.OffsetX = 2.5
	Actor_17H_weapon2proj1.OffsetY = 2.5
	Actor_17H_weapon2proj1.OffsetZ = 0
	Actor_17H_weapon2proj1.ForceX = 0.0005
	Actor_17H_weapon2proj1.ForceY = -0.0002
	Actor_17H_weapon2proj1.ForceYOnImpact = 0
	Actor_17H_weapon2proj1.NbBounce = 1
	Actor_17H_weapon2proj1.IgnoreGravity = true
	Actor_17H_weapon2proj1.LifeTime = 4000
	Actor_17H_weapon2proj1.Comeback = false
	Actor_17H_weapon2proj1.StartAnimFrame = 4
	Actor_17H_weapon2proj1.AngleOffset = 4
	Actor_17H_weapon2proj1.SoundAtStart = ""
	Actor_17H_weapon2proj1.SoundOnBounce = ""
	Actor_17H_weapon2proj1.ForceHurt = false
	Actor_17H_weapon2proj1.MultiShoot = false
	Actor_17H_weapon2proj1.UseTimer = false
	Actor_17H_weapon2proj1.Frequency = 1
	Actor_17H_weapon2proj1.FollowTarget = false
	Actor_17H:AddProjectileWeapon2(Actor_17H_weapon2proj1)
	Actor_17H_weapon2proj2 = ProjectileObjectDef()
	Actor_17H_weapon2proj2:SetRenderType(2)
	Actor_17H_weapon2proj2.DisplayDesc.ModelId = 0
	Actor_17H_weapon2proj2.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite064.png"
	Actor_17H_weapon2proj2.DisplayDesc.Outfit = ""
	Actor_17H_weapon2proj2.DisplayDesc.Weapon = ""
	Actor_17H_weapon2proj2.DisplayDesc.Mode = ""
	Actor_17H_weapon2proj2.DisplayDesc.UseLight = true
	Actor_17H_weapon2proj2.DisplayDesc.CastShadow = true
	Actor_17H_weapon2proj2.DisplayDesc.ColorR = 1
	Actor_17H_weapon2proj2.DisplayDesc.ColorG = 1
	Actor_17H_weapon2proj2.DisplayDesc.ColorB = 1
	Actor_17H_weapon2proj2.DisplayDesc.ColorA = 0.9
	Actor_17H_weapon2proj2.DisplayDesc.TransX = 0
	Actor_17H_weapon2proj2.DisplayDesc.TransY = 0
	Actor_17H_weapon2proj2.DisplayDesc.TransZ = 0
	Actor_17H_weapon2proj2.DisplayDesc.ScaleX = 0.05
	Actor_17H_weapon2proj2.DisplayDesc.ScaleY = 0.05
	Actor_17H_weapon2proj2.DisplayDesc.ScaleZ = 0.05
	Actor_17H_weapon2proj2.DisplayDesc.RotX = 0
	Actor_17H_weapon2proj2.DisplayDesc.RotY = 0
	Actor_17H_weapon2proj2.DisplayDesc.RotZ = 0
	Actor_17H_weapon2proj2.DisplayDesc.UseBillboard = true
	Actor_17H_weapon2proj2.PhysicDesc.Pos.X = 0
	Actor_17H_weapon2proj2.PhysicDesc.Pos.Y = 0
	Actor_17H_weapon2proj2.PhysicDesc.Pos.Z = 0
	Actor_17H_weapon2proj2.PhysicDesc.Pos.Rotation = 0
	Actor_17H_weapon2proj2.PhysicDesc.Density = 1
	Actor_17H_weapon2proj2.PhysicDesc.Collidable = false
	Actor_17H_weapon2proj2.PhysicDesc.SizeX = 0.05
	Actor_17H_weapon2proj2.PhysicDesc.SizeY = 0.05
	Actor_17H_weapon2proj2.PhysicDesc.SizeZ = 0.05
	Actor_17H_weapon2proj2.PhysicDesc.AllowFreeMove = true
	Actor_17H_weapon2proj2.PhysicDesc.Filename = ""
	Actor_17H_weapon2proj2:SetPhysicalActorType(3)
	Actor_17H_weapon2proj2:SetPhysicalShape(4)
	Actor_17H_weapon2proj2.UsableMode = ""
	Actor_17H_weapon2proj2.Power = 10
	Actor_17H_weapon2proj2.UseMana = 0
	Actor_17H_weapon2proj2.OffsetX = 2.5
	Actor_17H_weapon2proj2.OffsetY = 2.5
	Actor_17H_weapon2proj2.OffsetZ = 0
	Actor_17H_weapon2proj2.ForceX = 0.0005
	Actor_17H_weapon2proj2.ForceY = -0.0002
	Actor_17H_weapon2proj2.ForceYOnImpact = 0
	Actor_17H_weapon2proj2.NbBounce = 1
	Actor_17H_weapon2proj2.IgnoreGravity = true
	Actor_17H_weapon2proj2.LifeTime = 4000
	Actor_17H_weapon2proj2.Comeback = false
	Actor_17H_weapon2proj2.StartAnimFrame = 4
	Actor_17H_weapon2proj2.AngleOffset = -4
	Actor_17H_weapon2proj2.SoundAtStart = ""
	Actor_17H_weapon2proj2.SoundOnBounce = ""
	Actor_17H_weapon2proj2.ForceHurt = false
	Actor_17H_weapon2proj2.MultiShoot = false
	Actor_17H_weapon2proj2.UseTimer = false
	Actor_17H_weapon2proj2.Frequency = 1
	Actor_17H_weapon2proj2.FollowTarget = false
	Actor_17H:AddProjectileWeapon2(Actor_17H_weapon2proj2)
	Actor_17H:SetAttackFunction("ActorRotateAttackDistanceAndContactPlayer")
	Actor_17H:AddGivenItem(1,1,1,0.3,1)
	Actor_17H:AddGivenItem(2,1,1,0.3,1)
	Actor_17H:AddGivenItem(8,2,2,0.4,1)
	Actor_17H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_17H)

	Actor_18 = ActorObjectInfo(18)
	Actor_18:SetRenderType(3)
	Actor_18.HitPowerOnTouch = -1
	Actor_18.ExcludeFromNavMesh = false
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
	Actor_18.DisplayDesc.UseBillboard = false
	Actor_18.DisplayDesc.ColorMaterialType = 4
	Actor_18.DisplayDesc.MatAmbientColorR = -0.2
	Actor_18.DisplayDesc.MatAmbientColorG = -0.2
	Actor_18.DisplayDesc.MatAmbientColorB = -0.2
	Actor_18.DisplayDesc.MatAmbientColorA = 1
	Actor_18.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_18.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_18.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_18.DisplayDesc.MatDiffuseColorA = 1
	Actor_18.DisplayDesc.MatSpecularColorR = 0
	Actor_18.DisplayDesc.MatSpecularColorG = 0
	Actor_18.DisplayDesc.MatSpecularColorB = 0
	Actor_18.DisplayDesc.MatSpecularColorA = 1
	Actor_18.DisplayDesc.MatEmissionColorR = 0
	Actor_18.DisplayDesc.MatEmissionColorG = 0
	Actor_18.DisplayDesc.MatEmissionColorB = 0
	Actor_18.DisplayDesc.MatEmissionColorA = 1
	Actor_18.DisplayDesc.MatShininess = 0
	Actor_18.PhysicDesc.Pos.X = 32.5
	Actor_18.PhysicDesc.Pos.Y = 1
	Actor_18.PhysicDesc.Pos.Z = 33
	Actor_18.PhysicDesc.Pos.Rotation = 40
	Actor_18.PhysicDesc.Density = 1
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 1.5
	Actor_18.PhysicDesc.SizeY = 5
	Actor_18.PhysicDesc.SizeZ = 1.5
	Actor_18.PhysicDesc.AllowFreeMove = true
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
	Actor_18_Sc0 = ASPStartWaypoint(34,1,33,true)
	Actor_18H:AddScriptPart(Actor_18_Sc0)
	Actor_18_Sc1 = ASPFollowWaypoint(38,1,33)
	Actor_18H:AddScriptPart(Actor_18_Sc1)
	Actor_18_Sc2 = ASPFollowWaypoint(38,1,40)
	Actor_18H:AddScriptPart(Actor_18_Sc2)
	Actor_18_Sc3 = ASPFollowWaypoint(34,1,40)
	Actor_18H:AddScriptPart(Actor_18_Sc3)
	Actor_18H_dia = DialogPart()
	Actor_18H_dia:SetResetDialog(false)
	Actor_18H_dia_c0 = DialogPart()
	Actor_18H_dia_c0:SetResetDialog(false)
	Actor_18H_dia_c0:AddText(1033)
	Actor_18H_dia_c0_c0 = DialogPart()
	Actor_18H_dia_c0_c0:SetResetDialog(false)
	Actor_18H_dia_c0_c0:AddText(953)
	Actor_18H_dia_c0:AddChild(Actor_18H_dia_c0_c0)
	Actor_18H_dia:AddChild(Actor_18H_dia_c0)
	Actor_18H:SetRootDialog(Actor_18H_dia)
	Actor_18H:SetNpcName(-1)
	Actor_18H:SetSimpleDialog(false)
	Actor_18H:SetAggresive(true)
	Actor_18H:SetLife(50)
	Actor_18H:SetMana(50)
	Actor_18H:SetArmor(0)
	Actor_18H:SetAttackActiDist(6)
	Actor_18H:SetAttackActiDistDiscrete(4)
	Actor_18H:SetAttackActiDistHidden(2)
	Actor_18H:SetAttackStopDist(16)
	Actor_18H:SetRespawnTimeInSec(10)
	Actor_18H:SetWeaponAnimAtStart(true)
	Actor_18H:SetWeapon1Type(1)
	Actor_18H:SetWeapon1Power(10)
	Actor_18H:SetWeapon1ReachDistance(2)
	Actor_18H:Setuseweapon1animation("Use1Weapon")
	Actor_18H:SetWeapon2Type(2)
	Actor_18H:SetWeapon2Power(0)
	Actor_18H:SetWeapon2ReachDistance(1)
	Actor_18H:Setuseweapon2animation("UseWeapon")
	Actor_18H:SetAttackFunction("ActorAttackContactPlayer")
	Actor_18H:Setchasinganimation("Run")
	Actor_18H:AddGivenItem(1,1,1,0.3,1)
	Actor_18H:AddGivenItem(2,1,1,0.3,1)
	Actor_18H:AddGivenItem(8,2,2,0.4,1)
	Actor_18H:AddGivenItem(3,1,1,0.05,2)
	environment:AddActorObject(Actor_18H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4, 3, true)
	Trigger_1:SetPosition(26.5, 1, 38.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1:SetActivateOnJump(true)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map005_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 8, 6, 1, true)
	Trigger_2:SetPosition(21, 0, 0.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2:SetActivateOnJump(true)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map002_1")
	Trigger_2_act1:SetSpawning(6)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit12", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 3, 1, true)
	Trigger_3:SetPosition(63, 3, 43.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3:SetActivateOnJump(true)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map024_1")
	Trigger_3_act1:SetSpawning(2)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit13", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 2, 3, 1, true)
	Trigger_4:SetPosition(63, 3, 42.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4:SetActivateOnJump(true)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map039_1")
	Trigger_4_act1:SetSpawning(2)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit14", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 2, 3, 1, true)
	Trigger_5:SetPosition(63, 3, 41.5)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5:SetActivateOnJump(true)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map042_1")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit15", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 2, 3, 1, true)
	Trigger_6:SetPosition(63, 3, 40.5)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6:SetActivateOnJump(true)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map059_1")
	Trigger_6_act1:SetSpawning(1)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit2", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 9, 5, 1, true)
	Trigger_7:SetPosition(45.5, 0, 0.5)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7:SetActivateOnJump(true)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map002_1")
	Trigger_7_act1:SetSpawning(7)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "exit4", true, false, false)
	Trigger_8 = ZoneTrigger(Trigger_8_info, 2, 2, 2, true)
	Trigger_8:SetPosition(5, 10, 58)
	Trigger_8:SetStayUpdateFrequency(-1)
	Trigger_8:SetActivateOnJump(true)
	Trigger_8_act1 = TeleportAction()
	Trigger_8_act1:SetMapName("Map005_1")
	Trigger_8_act1:SetSpawning(2)
	Trigger_8:SetAction1(Trigger_8_act1)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "exit7", true, false, false)
	Trigger_9 = ZoneTrigger(Trigger_9_info, 1, 4.5, 3, true)
	Trigger_9:SetPosition(50.5, 1, 25.5)
	Trigger_9:SetStayUpdateFrequency(-1)
	Trigger_9:SetActivateOnJump(true)
	Trigger_9_act1 = TeleportAction()
	Trigger_9_act1:SetMapName("Map020_1")
	Trigger_9_act1:SetSpawning(1)
	Trigger_9:SetAction1(Trigger_9_act1)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "exit8", true, false, false)
	Trigger_10 = ZoneTrigger(Trigger_10_info, 4, 4, 1, true)
	Trigger_10:SetPosition(17, 0, 49.5)
	Trigger_10:SetStayUpdateFrequency(-1)
	Trigger_10:SetActivateOnJump(true)
	Trigger_10_act1 = TeleportAction()
	Trigger_10_act1:SetMapName("Map021_1")
	Trigger_10_act1:SetSpawning(1)
	Trigger_10:SetAction1(Trigger_10_act1)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "ContainerTri_11", true, false, false)
	Trigger_11 = ZoneActionTrigger(Trigger_11_info, 3.99804, 6.99609, 3.99804, "Normal", "")
	Trigger_11:SetPosition(28.999, 1, 35.999)
	Trigger_11_act1 = OpenContainerAction()
	Trigger_11_act1:SetTimeToReset(300)
		Trigger_11_act1ContItem0 = ContainerItemGroupElement(4,1,1,1,1)
		Trigger_11_act1:AddItem(Trigger_11_act1ContItem0)
		Trigger_11_act1ContItem1 = ContainerItemGroupElement(10,1,1,1,2)
		Trigger_11_act1:AddItem(Trigger_11_act1ContItem1)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "TextTri_12", true, false, false)
	Trigger_12 = ActivationTrigger(Trigger_12_info, 2, "Normal", "")
	Trigger_12:SetPosition(27.999, 0, 3.49902)
	Trigger_12_act1 = DisplayTextAction()
	Trigger_12_act1:SetTextId(254)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "DoorTri_13", true, false, false)
	Trigger_13 = ZoneTrigger(Trigger_13_info, 4, 8, 4, false)
	Trigger_13:SetPosition(27.5, 1, 38.5)
	Trigger_13:SetStayUpdateFrequency(-1)
	Trigger_13:SetActivateOnJump(true)
	Trigger_13_act1 = OpenDoorAction()
	Trigger_13_act1:SetActorId(4)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13_act2 = CloseDoorAction()
	Trigger_13_act2:SetActorId(4)
	Trigger_13:SetAction2(Trigger_13_act2)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "DoorTri_14", true, false, false)
	Trigger_14 = ZoneTrigger(Trigger_14_info, 5, 8, 5, false)
	Trigger_14:SetPosition(50.5, 1, 25.5)
	Trigger_14:SetStayUpdateFrequency(-1)
	Trigger_14:SetActivateOnJump(true)
	Trigger_14_act1 = ConditionalAction()
	Trigger_14_act1_act1 = MultiAction()
	Trigger_14_act1_act1_act0 = OpenDoorAction()
	Trigger_14_act1_act1_act0:SetActorId(5)
	Trigger_14_act1_act1:AddAction(Trigger_14_act1_act1_act0)
	Trigger_14_act1_act1_act1 = AddRemoveItemAction()
	Trigger_14_act1_act1_act1:SetItemId(4)
	Trigger_14_act1_act1_act1:SetNumber(-1)
	Trigger_14_act1_act1_act1:SetInformClientType(1)
	Trigger_14_act1_act1:AddAction(Trigger_14_act1_act1_act1)
	Trigger_14_act1:SetActionTrue(Trigger_14_act1_act1)
	Trigger_14_act1_cond = ItemInInventoryCondition()
	Trigger_14_act1_cond:SetTextid(-1)
	Trigger_14_act1_cond:SetItemId(4)
	Trigger_14_act1_cond:SetItemNumber(1)
	Trigger_14_act1:SetCondition(Trigger_14_act1_cond)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14_act2 = CloseDoorAction()
	Trigger_14_act2:SetActorId(5)
	Trigger_14:SetAction2(Trigger_14_act2)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "DoorTri_15", true, false, false)
	Trigger_15 = ZoneTrigger(Trigger_15_info, 4, 2, 4, false)
	Trigger_15:SetPosition(5, 15.1, 58)
	Trigger_15:SetStayUpdateFrequency(-1)
	Trigger_15:SetActivateOnJump(true)
	Trigger_15_act1 = OpenDoorAction()
	Trigger_15_act1:SetActorId(6)
	Trigger_15:SetAction1(Trigger_15_act1)
	Trigger_15_act2 = CloseDoorAction()
	Trigger_15_act2:SetActorId(6)
	Trigger_15:SetAction2(Trigger_15_act2)
	environment:AddTrigger(Trigger_15)

	Trigger_16_info = TriggerInfo(16, "mailboxtrigger", true, true, false)
	Trigger_16 = ActivationTrigger(Trigger_16_info, 1.5, "Normal", "None")
	Trigger_16:SetPosition(32.7, 1, 42)
	Trigger_16_act1 = OpenMailboxAction()
	Trigger_16:SetAction1(Trigger_16_act1)
	Trigger_16:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_16)

	Trigger_17_info = TriggerInfo(17, "ttttttttt", true, true, false)
	Trigger_17 = ZoneTrigger(Trigger_17_info, 3, 3, 3, true)
	Trigger_17:SetPosition(14, 1, 6)
	Trigger_17:SetStayUpdateFrequency(-1)
	Trigger_17:SetActivateOnJump(true)
	Trigger_17_act1 = ClientScriptAction()
	Trigger_17_act1_cs = CustomScript()
	Trigger_17_act1_cs:SetLuaFunctionName("PlayIntro")
	Trigger_17_act1:SetScript(Trigger_17_act1_cs)
	Trigger_17:SetAction1(Trigger_17_act1)
	environment:AddTrigger(Trigger_17)

end
