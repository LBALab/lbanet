function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(3)
	Spawn_1:SetPosY(10.01)
	Spawn_1:SetPosZ(58)
	Spawn_1:SetName("spawning0")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(51.5)
	Spawn_2:SetPosY(8.01)
	Spawn_2:SetPosZ(60)
	Spawn_2:SetName("spawning1")
	environment:AddSpawn(Spawn_2)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map8.osgb"
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
	Actor_1.PhysicDesc.AllowFreeMove = true
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map8.phy"
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
	Actor_14:SetRenderType(3)
	Actor_14.DisplayDesc.ModelId = 0
	Actor_14.DisplayDesc.ModelName = "SkeletonBu"
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
	Actor_14.PhysicDesc.Pos.X = 6.78125
	Actor_14.PhysicDesc.Pos.Y = 8.3125
	Actor_14.PhysicDesc.Pos.Z = 53.0938
	Actor_14.PhysicDesc.Pos.Rotation = 281
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 1
	Actor_14.PhysicDesc.SizeY = 5
	Actor_14.PhysicDesc.SizeZ = 1
	Actor_14.PhysicDesc.AllowFreeMove = true
	Actor_14.PhysicDesc.Filename = ""
	Actor_14:SetPhysicalActorType(2)
	Actor_14:SetPhysicalShape(2)
	Actor_14.ExtraInfo.Name = "NPC"
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
	Actor_15.DisplayDesc.Outfit = "Cutter"
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
	Actor_15.PhysicDesc.Pos.X = 5
	Actor_15.PhysicDesc.Pos.Y = 8
	Actor_15.PhysicDesc.Pos.Z = 18
	Actor_15.PhysicDesc.Pos.Rotation = 73
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 0.5
	Actor_15.PhysicDesc.SizeY = 10
	Actor_15.PhysicDesc.SizeZ = 1.5
	Actor_15.PhysicDesc.AllowFreeMove = true
	Actor_15.PhysicDesc.Filename = ""
	Actor_15:SetPhysicalActorType(2)
	Actor_15:SetPhysicalShape(2)
	Actor_15.ExtraInfo.Name = "NPC"
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
	Actor_16.DisplayDesc.Outfit = "Cutter"
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
	Actor_16.PhysicDesc.Pos.X = 22.8438
	Actor_16.PhysicDesc.Pos.Y = 8
	Actor_16.PhysicDesc.Pos.Z = 15
	Actor_16.PhysicDesc.Pos.Rotation = 73
	Actor_16.PhysicDesc.Density = 1
	Actor_16.PhysicDesc.Collidable = true
	Actor_16.PhysicDesc.SizeX = 0.5
	Actor_16.PhysicDesc.SizeY = 10
	Actor_16.PhysicDesc.SizeZ = 1.5
	Actor_16.PhysicDesc.AllowFreeMove = true
	Actor_16.PhysicDesc.Filename = ""
	Actor_16:SetPhysicalActorType(2)
	Actor_16:SetPhysicalShape(2)
	Actor_16.ExtraInfo.Name = "NPC"
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
	Actor_17.DisplayDesc.Outfit = "RollingTrap"
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
	Actor_17.PhysicDesc.Pos.X = 2.09375
	Actor_17.PhysicDesc.Pos.Y = 18
	Actor_17.PhysicDesc.Pos.Z = 39.5
	Actor_17.PhysicDesc.Pos.Rotation = 281
	Actor_17.PhysicDesc.Density = 1
	Actor_17.PhysicDesc.Collidable = true
	Actor_17.PhysicDesc.SizeX = 2
	Actor_17.PhysicDesc.SizeY = 2
	Actor_17.PhysicDesc.SizeZ = 1
	Actor_17.PhysicDesc.AllowFreeMove = true
	Actor_17.PhysicDesc.Filename = ""
	Actor_17:SetPhysicalActorType(2)
	Actor_17:SetPhysicalShape(2)
	Actor_17.ExtraInfo.Name = "NPC"
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
	Actor_18.DisplayDesc.ModelName = "SkeletonBu"
	Actor_18.DisplayDesc.Outfit = "No"
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
	Actor_18.PhysicDesc.Pos.X = 57.4688
	Actor_18.PhysicDesc.Pos.Y = 0.6875
	Actor_18.PhysicDesc.Pos.Z = 29.5938
	Actor_18.PhysicDesc.Pos.Rotation = 177
	Actor_18.PhysicDesc.Density = 1
	Actor_18.PhysicDesc.Collidable = true
	Actor_18.PhysicDesc.SizeX = 1
	Actor_18.PhysicDesc.SizeY = 5
	Actor_18.PhysicDesc.SizeZ = 1
	Actor_18.PhysicDesc.AllowFreeMove = true
	Actor_18.PhysicDesc.Filename = ""
	Actor_18:SetPhysicalActorType(2)
	Actor_18:SetPhysicalShape(2)
	Actor_18.ExtraInfo.Name = "NPC"
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
	Actor_19.PhysicDesc.Pos.X = 57.4063
	Actor_19.PhysicDesc.Pos.Y = 0.6875
	Actor_19.PhysicDesc.Pos.Z = 23.5625
	Actor_19.PhysicDesc.Pos.Rotation = 177
	Actor_19.PhysicDesc.Density = 1
	Actor_19.PhysicDesc.Collidable = true
	Actor_19.PhysicDesc.SizeX = 1
	Actor_19.PhysicDesc.SizeY = 5
	Actor_19.PhysicDesc.SizeZ = 1
	Actor_19.PhysicDesc.AllowFreeMove = true
	Actor_19.PhysicDesc.Filename = ""
	Actor_19:SetPhysicalActorType(2)
	Actor_19:SetPhysicalShape(2)
	Actor_19.ExtraInfo.Name = "NPC"
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
	Actor_20.DisplayDesc.ModelName = ""
	Actor_20.DisplayDesc.Outfit = ""
	Actor_20.DisplayDesc.Weapon = ""
	Actor_20.DisplayDesc.Mode = ""
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
	Actor_20.PhysicDesc.Pos.X = 51.5
	Actor_20.PhysicDesc.Pos.Y = 11.5625
	Actor_20.PhysicDesc.Pos.Z = 4.53125
	Actor_20.PhysicDesc.Pos.Rotation = 281
	Actor_20.PhysicDesc.Density = 1
	Actor_20.PhysicDesc.Collidable = true
	Actor_20.PhysicDesc.SizeX = 1
	Actor_20.PhysicDesc.SizeY = 5
	Actor_20.PhysicDesc.SizeZ = 1
	Actor_20.PhysicDesc.AllowFreeMove = true
	Actor_20.PhysicDesc.Filename = ""
	Actor_20:SetPhysicalActorType(2)
	Actor_20:SetPhysicalShape(2)
	Actor_20.ExtraInfo.Name = "NPC"
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
	Actor_21.PhysicDesc.Pos.X = 53
	Actor_21.PhysicDesc.Pos.Y = 11
	Actor_21.PhysicDesc.Pos.Z = 53
	Actor_21.PhysicDesc.Pos.Rotation = 95
	Actor_21.PhysicDesc.Density = 1
	Actor_21.PhysicDesc.Collidable = true
	Actor_21.PhysicDesc.SizeX = 1
	Actor_21.PhysicDesc.SizeY = 5
	Actor_21.PhysicDesc.SizeZ = 1
	Actor_21.PhysicDesc.AllowFreeMove = true
	Actor_21.PhysicDesc.Filename = ""
	Actor_21:SetPhysicalActorType(2)
	Actor_21:SetPhysicalShape(2)
	Actor_21.ExtraInfo.Name = "NPC"
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
	Actor_22.PhysicDesc.Pos.Y = 11
	Actor_22.PhysicDesc.Pos.Z = 53
	Actor_22.PhysicDesc.Pos.Rotation = 155
	Actor_22.PhysicDesc.Density = 1
	Actor_22.PhysicDesc.Collidable = true
	Actor_22.PhysicDesc.SizeX = 1
	Actor_22.PhysicDesc.SizeY = 5
	Actor_22.PhysicDesc.SizeZ = 1
	Actor_22.PhysicDesc.AllowFreeMove = true
	Actor_22.PhysicDesc.Filename = ""
	Actor_22:SetPhysicalActorType(2)
	Actor_22:SetPhysicalShape(2)
	Actor_22.ExtraInfo.Name = "NPC"
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
	Actor_23.PhysicDesc.Pos.X = 49.1563
	Actor_23.PhysicDesc.Pos.Y = 11
	Actor_23.PhysicDesc.Pos.Z = 49
	Actor_23.PhysicDesc.Pos.Rotation = 295
	Actor_23.PhysicDesc.Density = 1
	Actor_23.PhysicDesc.Collidable = true
	Actor_23.PhysicDesc.SizeX = 1
	Actor_23.PhysicDesc.SizeY = 5
	Actor_23.PhysicDesc.SizeZ = 1
	Actor_23.PhysicDesc.AllowFreeMove = true
	Actor_23.PhysicDesc.Filename = ""
	Actor_23:SetPhysicalActorType(2)
	Actor_23:SetPhysicalShape(2)
	Actor_23.ExtraInfo.Name = "NPC"
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
	Actor_24.PhysicDesc.Pos.X = 53
	Actor_24.PhysicDesc.Pos.Y = 11
	Actor_24.PhysicDesc.Pos.Z = 49
	Actor_24.PhysicDesc.Pos.Rotation = 320
	Actor_24.PhysicDesc.Density = 1
	Actor_24.PhysicDesc.Collidable = true
	Actor_24.PhysicDesc.SizeX = 1
	Actor_24.PhysicDesc.SizeY = 5
	Actor_24.PhysicDesc.SizeZ = 1
	Actor_24.PhysicDesc.AllowFreeMove = true
	Actor_24.PhysicDesc.Filename = ""
	Actor_24:SetPhysicalActorType(2)
	Actor_24:SetPhysicalShape(2)
	Actor_24.ExtraInfo.Name = "NPC"
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
	Actor_25.PhysicDesc.Pos.X = 8
	Actor_25.PhysicDesc.Pos.Y = 11
	Actor_25.PhysicDesc.Pos.Z = 12.625
	Actor_25.PhysicDesc.Pos.Rotation = 25
	Actor_25.PhysicDesc.Density = 1
	Actor_25.PhysicDesc.Collidable = true
	Actor_25.PhysicDesc.SizeX = 1
	Actor_25.PhysicDesc.SizeY = 5
	Actor_25.PhysicDesc.SizeZ = 1
	Actor_25.PhysicDesc.AllowFreeMove = true
	Actor_25.PhysicDesc.Filename = ""
	Actor_25:SetPhysicalActorType(2)
	Actor_25:SetPhysicalShape(2)
	Actor_25.ExtraInfo.Name = "NPC"
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
	Actor_26.PhysicDesc.Pos.X = 20.0938
	Actor_26.PhysicDesc.Pos.Y = 11
	Actor_26.PhysicDesc.Pos.Z = 5.5625
	Actor_26.PhysicDesc.Pos.Rotation = 25
	Actor_26.PhysicDesc.Density = 1
	Actor_26.PhysicDesc.Collidable = true
	Actor_26.PhysicDesc.SizeX = 1
	Actor_26.PhysicDesc.SizeY = 5
	Actor_26.PhysicDesc.SizeZ = 1
	Actor_26.PhysicDesc.AllowFreeMove = true
	Actor_26.PhysicDesc.Filename = ""
	Actor_26:SetPhysicalActorType(2)
	Actor_26:SetPhysicalShape(2)
	Actor_26.ExtraInfo.Name = "NPC"
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
	Actor_27.DisplayDesc.ModelName = "Object"
	Actor_27.DisplayDesc.Outfit = "GunTrap"
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
	Actor_27.PhysicDesc.Pos.X = 29.5625
	Actor_27.PhysicDesc.Pos.Y = 8
	Actor_27.PhysicDesc.Pos.Z = 39.5
	Actor_27.PhysicDesc.Pos.Rotation = 281
	Actor_27.PhysicDesc.Density = 1
	Actor_27.PhysicDesc.Collidable = true
	Actor_27.PhysicDesc.SizeX = 0.3
	Actor_27.PhysicDesc.SizeY = 0.5
	Actor_27.PhysicDesc.SizeZ = 0.3
	Actor_27.PhysicDesc.AllowFreeMove = true
	Actor_27.PhysicDesc.Filename = ""
	Actor_27:SetPhysicalActorType(2)
	Actor_27:SetPhysicalShape(2)
	Actor_27.ExtraInfo.Name = "NPC"
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
	Actor_28.PhysicDesc.Pos.X = 43.5938
	Actor_28.PhysicDesc.Pos.Y = 8
	Actor_28.PhysicDesc.Pos.Z = 45.25
	Actor_28.PhysicDesc.Pos.Rotation = 281
	Actor_28.PhysicDesc.Density = 1
	Actor_28.PhysicDesc.Collidable = true
	Actor_28.PhysicDesc.SizeX = 0.3
	Actor_28.PhysicDesc.SizeY = 0.5
	Actor_28.PhysicDesc.SizeZ = 0.3
	Actor_28.PhysicDesc.AllowFreeMove = true
	Actor_28.PhysicDesc.Filename = ""
	Actor_28:SetPhysicalActorType(2)
	Actor_28:SetPhysicalShape(2)
	Actor_28.ExtraInfo.Name = "NPC"
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
	Actor_29.DisplayDesc.ModelName = "Object"
	Actor_29.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_29.PhysicDesc.Pos.X = 0
	Actor_29.PhysicDesc.Pos.Y = -1
	Actor_29.PhysicDesc.Pos.Z = 0
	Actor_29.PhysicDesc.Pos.Rotation = 25
	Actor_29.PhysicDesc.Density = 1
	Actor_29.PhysicDesc.Collidable = true
	Actor_29.PhysicDesc.SizeX = 0.5
	Actor_29.PhysicDesc.SizeY = 2
	Actor_29.PhysicDesc.SizeZ = 0.6
	Actor_29.PhysicDesc.AllowFreeMove = true
	Actor_29.PhysicDesc.Filename = ""
	Actor_29:SetPhysicalActorType(2)
	Actor_29:SetPhysicalShape(2)
	Actor_29.ExtraInfo.Name = "NPC"
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
	Actor_30:SetRenderType(1)
	Actor_30.DisplayDesc.ModelId = 0
	Actor_30.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite014.osgb"
	Actor_30.DisplayDesc.Outfit = ""
	Actor_30.DisplayDesc.Weapon = ""
	Actor_30.DisplayDesc.Mode = ""
	Actor_30.DisplayDesc.UseLight = true
	Actor_30.DisplayDesc.CastShadow = false
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
	Actor_30.PhysicDesc.Pos.X = 58
	Actor_30.PhysicDesc.Pos.Y = 6.5
	Actor_30.PhysicDesc.Pos.Z = 18
	Actor_30.PhysicDesc.Pos.Rotation = 0
	Actor_30.PhysicDesc.Density = 1
	Actor_30.PhysicDesc.Collidable = true
	Actor_30.PhysicDesc.SizeX = 2
	Actor_30.PhysicDesc.SizeY = 0.5
	Actor_30.PhysicDesc.SizeZ = 2
	Actor_30.PhysicDesc.AllowFreeMove = true
	Actor_30.PhysicDesc.Filename = ""
	Actor_30:SetPhysicalActorType(2)
	Actor_30:SetPhysicalShape(2)
	Actor_30.ExtraInfo.Name = ""
	Actor_30.ExtraInfo.NameColorR = 0
	Actor_30.ExtraInfo.NameColorG = 0
	Actor_30.ExtraInfo.NameColorB = 0
	Actor_30.ExtraInfo.Display = false
	Actor_30.LifeInfo.Display = false
	Actor_30H = ActorHandler(Actor_30)
	Actor_30_Sc0 = ASPWaitForSignal(5)
	Actor_30H:AddScriptPart(Actor_30_Sc0)
	Actor_30_Sc1 = ASPGoTo(58,7.5,43,0.004)
	Actor_30H:AddScriptPart(Actor_30_Sc1)
	Actor_30_Sc2 = ASPWaitForSignal(5)
	Actor_30H:AddScriptPart(Actor_30_Sc2)
	Actor_30_Sc3 = ASPGoTo(58,6.5,18,0.004)
	Actor_30H:AddScriptPart(Actor_30_Sc3)
	environment:AddActorObject(Actor_30H)

	Actor_31 = ActorObjectInfo(31)
	Actor_31:SetRenderType(1)
	Actor_31.DisplayDesc.ModelId = 0
	Actor_31.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite119.osgb"
	Actor_31.DisplayDesc.Outfit = ""
	Actor_31.DisplayDesc.Weapon = ""
	Actor_31.DisplayDesc.Mode = ""
	Actor_31.DisplayDesc.UseLight = true
	Actor_31.DisplayDesc.CastShadow = false
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
	Actor_31.PhysicDesc.Pos.X = 57
	Actor_31.PhysicDesc.Pos.Y = 0
	Actor_31.PhysicDesc.Pos.Z = 26.5
	Actor_31.PhysicDesc.Pos.Rotation = 0
	Actor_31.PhysicDesc.Density = 1
	Actor_31.PhysicDesc.Collidable = false
	Actor_31.PhysicDesc.SizeX = 0.8
	Actor_31.PhysicDesc.SizeY = 3
	Actor_31.PhysicDesc.SizeZ = 0.8
	Actor_31.PhysicDesc.AllowFreeMove = true
	Actor_31.PhysicDesc.Filename = ""
	Actor_31:SetPhysicalActorType(1)
	Actor_31:SetPhysicalShape(2)
	Actor_31.ExtraInfo.Name = ""
	Actor_31.ExtraInfo.NameColorR = 0
	Actor_31.ExtraInfo.NameColorG = 0
	Actor_31.ExtraInfo.NameColorB = 0
	Actor_31.ExtraInfo.Display = false
	Actor_31.LifeInfo.Display = false
	Actor_31H = ActorHandler(Actor_31)
	environment:AddActorObject(Actor_31H)

	Actor_34 = ActorObjectInfo(34)
	Actor_34:SetRenderType(1)
	Actor_34.DisplayDesc.ModelId = 0
	Actor_34.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite032.osgb"
	Actor_34.DisplayDesc.Outfit = ""
	Actor_34.DisplayDesc.Weapon = ""
	Actor_34.DisplayDesc.Mode = ""
	Actor_34.DisplayDesc.UseLight = true
	Actor_34.DisplayDesc.CastShadow = false
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
	Actor_34.PhysicDesc.Pos.X = 51.5
	Actor_34.PhysicDesc.Pos.Y = 8
	Actor_34.PhysicDesc.Pos.Z = 62.2
	Actor_34.PhysicDesc.Pos.Rotation = 0
	Actor_34.PhysicDesc.Density = 1
	Actor_34.PhysicDesc.Collidable = true
	Actor_34.PhysicDesc.SizeX = 4
	Actor_34.PhysicDesc.SizeY = 6
	Actor_34.PhysicDesc.SizeZ = 0.6
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
	Actor_34H = DoorHandler(Actor_34,1,0,-90,0.1,false)
	Actor_34_Sc0 = ASPWaitForSignal(1)
	Actor_34H:AddScriptPart(Actor_34_Sc0)
	Actor_34_Sc1 = ASPRotateFromPoint(-90,49.5,8,62.2,0.1)
	Actor_34H:AddScriptPart(Actor_34_Sc1)
	Actor_34_Sc2 = ASPWaitForSignal(2)
	Actor_34H:AddScriptPart(Actor_34_Sc2)
	Actor_34_Sc3 = ASPRotateFromPoint(0,49.5,8,62.2,0.1)
	Actor_34H:AddScriptPart(Actor_34_Sc3)
	Actor_34_Sc4 = ASPTeleportTo(51.5,8,62.2)
	Actor_34H:AddScriptPart(Actor_34_Sc4)
	Actor_34_Sc5 = ASPSetRotation(0)
	Actor_34H:AddScriptPart(Actor_34_Sc5)
	environment:AddActorObject(Actor_34H)

	Actor_35 = ActorObjectInfo(35)
	Actor_35:SetRenderType(1)
	Actor_35.DisplayDesc.ModelId = 0
	Actor_35.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite049.osgb"
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
	Actor_35:SetModelState(2)
	Actor_35.PhysicDesc.Pos.X = 53.6
	Actor_35.PhysicDesc.Pos.Y = 8.1
	Actor_35.PhysicDesc.Pos.Z = 11
	Actor_35.PhysicDesc.Pos.Rotation = 0
	Actor_35.PhysicDesc.Density = 1
	Actor_35.PhysicDesc.Collidable = true
	Actor_35.PhysicDesc.SizeX = 1
	Actor_35.PhysicDesc.SizeY = 4
	Actor_35.PhysicDesc.SizeZ = 1
	Actor_35.PhysicDesc.AllowFreeMove = true
	Actor_35.PhysicDesc.Filename = ""
	Actor_35:SetPhysicalActorType(4)
	Actor_35:SetPhysicalShape(2)
	Actor_35.ExtraInfo.Name = ""
	Actor_35.ExtraInfo.NameColorR = 1
	Actor_35.ExtraInfo.NameColorG = 1
	Actor_35.ExtraInfo.NameColorB = 1
	Actor_35.ExtraInfo.Display = false
	Actor_35.LifeInfo.Display = false
	Actor_35H = ActorHandler(Actor_35)
	environment:AddActorObject(Actor_35H)

	Trigger_1_info = TriggerInfo(1, "exit31", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 3.5, 1, true)
	Trigger_1:SetPosition(51.5, 8, 62.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1:SetActivateOnJump(true)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map040_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "LadderTri_2", true, false, false)
	Trigger_2 = ActivationTrigger(Trigger_2_info, 1.66667, "Normal", "")
	Trigger_2:SetPosition(19.5, 0, 52)
	Trigger_2_act1 = ClientScriptAction()
	Trigger_2_act1_cs = GoUpLadderScript()
	Trigger_2_act1_cs:SetLadderPositionX(19.5)
	Trigger_2_act1_cs:SetLadderPositionY(0)
	Trigger_2_act1_cs:SetLadderPositionZ(52)
	Trigger_2_act1_cs:SetLadderHeight(15.0039)
	Trigger_2_act1_cs:SetLadderDirection(180)
	Trigger_2_act1:SetScript(Trigger_2_act1_cs)
	Trigger_2:SetAction1(Trigger_2_act1)
	Trigger_2:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 1.99805, 5.99609, 1.99805, "Normal", "")
	Trigger_3:SetPosition(2.99902, 8, 53.999)
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
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 1.99805, 6.99609, 2.99804, "Normal", "")
	Trigger_4:SetPosition(7.99902, 8, 28.499)
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
	Trigger_5 = ZoneActionTrigger(Trigger_5_info, 1.99805, 5.99609, 1.99805, "Normal", "")
	Trigger_5:SetPosition(23.999, 8, 49.999)
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
	Trigger_6 = ZoneActionTrigger(Trigger_6_info, 2.99804, 6.99609, 1.99805, "Normal", "")
	Trigger_6:SetPosition(52.499, 8, 1.99902)
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
	Trigger_7 = ZoneActionTrigger(Trigger_7_info, 2.99804, 5.99609, 2.99804, "Normal", "")
	Trigger_7:SetPosition(21.499, 8, 35.499)
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

	Trigger_8_info = TriggerInfo(8, "HurtTri_8", true, false, false)
	Trigger_8 = ZoneTrigger(Trigger_8_info, 1, 2.3, 12, true)
	Trigger_8:SetPosition(40.5, 8, 58)
	Trigger_8:SetStayUpdateFrequency(2)
	Trigger_8:SetActivateOnJump(false)
	Trigger_8_act1 = HurtAction()
	Trigger_8_act1:SetHurtValue(5)
	Trigger_8_act1:SetPlayedAnimation(3)
	Trigger_8_act1:HurtLifeOrMana(true)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8_act3 = HurtAction()
	Trigger_8_act3:SetHurtValue(5)
	Trigger_8_act3:SetPlayedAnimation(3)
	Trigger_8_act3:HurtLifeOrMana(true)
	Trigger_8:SetAction3(Trigger_8_act3)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "HurtTri_9", true, false, false)
	Trigger_9 = ZoneTrigger(Trigger_9_info, 3, 2.3, 2, true)
	Trigger_9:SetPosition(26.5, 0, 58)
	Trigger_9:SetStayUpdateFrequency(2)
	Trigger_9:SetActivateOnJump(true)
	Trigger_9_act1 = HurtAction()
	Trigger_9_act1:SetHurtValue(5)
	Trigger_9_act1:SetPlayedAnimation(3)
	Trigger_9_act1:HurtLifeOrMana(true)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9_act3 = HurtAction()
	Trigger_9_act3:SetHurtValue(5)
	Trigger_9_act3:SetPlayedAnimation(3)
	Trigger_9_act3:HurtLifeOrMana(true)
	Trigger_9:SetAction3(Trigger_9_act3)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "HurtTri_10", true, false, false)
	Trigger_10 = ZoneTrigger(Trigger_10_info, 1, 2.3, 4, true)
	Trigger_10:SetPosition(16.5, 0, 60)
	Trigger_10:SetStayUpdateFrequency(2)
	Trigger_10:SetActivateOnJump(true)
	Trigger_10_act1 = HurtAction()
	Trigger_10_act1:SetHurtValue(5)
	Trigger_10_act1:SetPlayedAnimation(3)
	Trigger_10_act1:HurtLifeOrMana(true)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10_act3 = HurtAction()
	Trigger_10_act3:SetHurtValue(5)
	Trigger_10_act3:SetPlayedAnimation(3)
	Trigger_10_act3:HurtLifeOrMana(true)
	Trigger_10:SetAction3(Trigger_10_act3)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "HurtTri_11", true, false, false)
	Trigger_11 = ZoneTrigger(Trigger_11_info, 3, 2.3, 1, true)
	Trigger_11:SetPosition(17.5, 0, 52.5)
	Trigger_11:SetStayUpdateFrequency(2)
	Trigger_11:SetActivateOnJump(true)
	Trigger_11_act1 = HurtAction()
	Trigger_11_act1:SetHurtValue(5)
	Trigger_11_act1:SetPlayedAnimation(3)
	Trigger_11_act1:HurtLifeOrMana(true)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11_act3 = HurtAction()
	Trigger_11_act3:SetHurtValue(5)
	Trigger_11_act3:SetPlayedAnimation(3)
	Trigger_11_act3:HurtLifeOrMana(true)
	Trigger_11:SetAction3(Trigger_11_act3)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "HurtTri_12", true, false, false)
	Trigger_12 = ZoneTrigger(Trigger_12_info, 4, 2.3, 1, true)
	Trigger_12:SetPosition(29, 0, 52.5)
	Trigger_12:SetStayUpdateFrequency(2)
	Trigger_12:SetActivateOnJump(true)
	Trigger_12_act1 = HurtAction()
	Trigger_12_act1:SetHurtValue(5)
	Trigger_12_act1:SetPlayedAnimation(3)
	Trigger_12_act1:HurtLifeOrMana(true)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12_act3 = HurtAction()
	Trigger_12_act3:SetHurtValue(5)
	Trigger_12_act3:SetPlayedAnimation(3)
	Trigger_12_act3:HurtLifeOrMana(true)
	Trigger_12:SetAction3(Trigger_12_act3)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "HurtTri_13", true, false, false)
	Trigger_13 = ZoneTrigger(Trigger_13_info, 8, 2.3, 2, true)
	Trigger_13:SetPosition(32, 0, 61)
	Trigger_13:SetStayUpdateFrequency(2)
	Trigger_13:SetActivateOnJump(true)
	Trigger_13_act1 = HurtAction()
	Trigger_13_act1:SetHurtValue(5)
	Trigger_13_act1:SetPlayedAnimation(3)
	Trigger_13_act1:HurtLifeOrMana(true)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13_act3 = HurtAction()
	Trigger_13_act3:SetHurtValue(5)
	Trigger_13_act3:SetPlayedAnimation(3)
	Trigger_13_act3:HurtLifeOrMana(true)
	Trigger_13:SetAction3(Trigger_13_act3)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "SwitchTri_14", true, false, false)
	Trigger_14 = ActivationTrigger(Trigger_14_info, 1.66667, "Normal", "")
	Trigger_14:SetPosition(57, 0, 26.5)
	Trigger_14_act1 = SwitchAction()
	Trigger_14_act1:SetActorId(31)
	Trigger_14_act1:SetSwitchModel("Worlds/Lba1Original/Sprites/sprite119.osgb")
	Trigger_14_act1_act1 = SendSignalAction()
	Trigger_14_act1_act1:SetActorId(30)
	Trigger_14_act1_act1:SetSignal(5)
	Trigger_14_act1:SetActionTrue(Trigger_14_act1_act1)
	Trigger_14_act1_act1 = SendSignalAction()
	Trigger_14_act1_act1:SetActorId(30)
	Trigger_14_act1_act1:SetSignal(5)
	Trigger_14_act1:SetActionFalse(Trigger_14_act1_act1)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_14)

	Trigger_15_info = TriggerInfo(15, "DoorTri_15", true, false, false)
	Trigger_15 = ZoneTrigger(Trigger_15_info, 0, 0, 0, false)
	Trigger_15:SetPosition(51.5, 8, 62.2)
	Trigger_15:SetStayUpdateFrequency(-1)
	Trigger_15:SetActivateOnJump(true)
	Trigger_15_act1 = OpenDoorAction()
	Trigger_15_act1:SetActorId(34)
	Trigger_15:SetAction1(Trigger_15_act1)
	Trigger_15_act2 = CloseDoorAction()
	Trigger_15_act2:SetActorId(34)
	Trigger_15:SetAction2(Trigger_15_act2)
	environment:AddTrigger(Trigger_15)

	Trigger_16_info = TriggerInfo(16, "opendoor", true, true, true)
	Trigger_16 = ZoneTrigger(Trigger_16_info, 1, 1, 1, true)
	Trigger_16:SetPosition(51.6, 9, 51.5)
	Trigger_16:SetStayUpdateFrequency(-1)
	Trigger_16:SetActivateOnJump(true)
	Trigger_16_act1 = OpenDoorAction()
	Trigger_16_act1:SetActorId(34)
	Trigger_16:SetAction1(Trigger_16_act1)
	Trigger_16_act2 = CloseDoorAction()
	Trigger_16_act2:SetActorId(34)
	Trigger_16:SetAction2(Trigger_16_act2)
	environment:AddTrigger(Trigger_16)

end
