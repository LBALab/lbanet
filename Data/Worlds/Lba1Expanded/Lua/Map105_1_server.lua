function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(37)
	Spawn_1:SetPosY(13.01)
	Spawn_1:SetPosZ(11.5)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(61)
	Spawn_2:SetPosY(0.01)
	Spawn_2:SetPosZ(35)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map105.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map105.phy"
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

	Actor_6 = ActorObjectInfo(6)
	Actor_6:SetRenderType(3)
	Actor_6.DisplayDesc.ModelId = 0
	Actor_6.DisplayDesc.ModelName = "Nurse"
	Actor_6.DisplayDesc.Outfit = "Guard"
	Actor_6.DisplayDesc.Weapon = "No"
	Actor_6.DisplayDesc.Mode = "Normal"
	Actor_6.DisplayDesc.UseLight = true
	Actor_6.DisplayDesc.CastShadow = true
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
	Actor_6.PhysicDesc.Pos.X = 27.2813
	Actor_6.PhysicDesc.Pos.Y = 13
	Actor_6.PhysicDesc.Pos.Z = 10.875
	Actor_6.PhysicDesc.Pos.Rotation = 177
	Actor_6.PhysicDesc.Density = 1
	Actor_6.PhysicDesc.Collidable = true
	Actor_6.PhysicDesc.SizeX = 1
	Actor_6.PhysicDesc.SizeY = 5
	Actor_6.PhysicDesc.SizeZ = 1
	Actor_6.PhysicDesc.Filename = ""
	Actor_6:SetPhysicalActorType(2)
	Actor_6:SetPhysicalShape(2)
	Actor_6.ExtraInfo.Name = ""
	Actor_6.ExtraInfo.NameColorR = 0
	Actor_6.ExtraInfo.NameColorG = 0
	Actor_6.ExtraInfo.NameColorB = 0
	Actor_6.ExtraInfo.Display = false
	Actor_6.LifeInfo.Display = false
	Actor_6H = NPCHandler(Actor_6)
	Actor_6H_dia = DialogPart()
	Actor_6H_dia:SetResetDialog(false)
	Actor_6H:SetRootDialog(Actor_6H_dia)
	Actor_6H:SetNpcName(-1)
	Actor_6H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_6H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(3)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "GroboClone"
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
	Actor_7.PhysicDesc.Pos.X = 39
	Actor_7.PhysicDesc.Pos.Y = 7
	Actor_7.PhysicDesc.Pos.Z = 26.0625
	Actor_7.PhysicDesc.Pos.Rotation = 25
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 1.5
	Actor_7.PhysicDesc.SizeY = 5
	Actor_7.PhysicDesc.SizeZ = 1.5
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

	Actor_8 = ActorObjectInfo(8)
	Actor_8:SetRenderType(3)
	Actor_8.DisplayDesc.ModelId = 0
	Actor_8.DisplayDesc.ModelName = "RabbiClone"
	Actor_8.DisplayDesc.Outfit = "Green"
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
	Actor_8.PhysicDesc.Pos.X = 13.4375
	Actor_8.PhysicDesc.Pos.Y = 5
	Actor_8.PhysicDesc.Pos.Z = 30.5313
	Actor_8.PhysicDesc.Pos.Rotation = 281
	Actor_8.PhysicDesc.Density = 1
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 1
	Actor_8.PhysicDesc.SizeY = 6
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
	Actor_9.DisplayDesc.ModelName = "Nurse"
	Actor_9.DisplayDesc.Outfit = "Tech"
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
	Actor_9.PhysicDesc.Pos.X = 47.9688
	Actor_9.PhysicDesc.Pos.Y = 5
	Actor_9.PhysicDesc.Pos.Z = 30.6875
	Actor_9.PhysicDesc.Pos.Rotation = 433
	Actor_9.PhysicDesc.Density = 1
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 1
	Actor_9.PhysicDesc.SizeY = 5
	Actor_9.PhysicDesc.SizeZ = 1
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
	Actor_10.DisplayDesc.ModelName = "Grobo"
	Actor_10.DisplayDesc.Outfit = "Sailor"
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
	Actor_10.PhysicDesc.Pos.X = 3.40625
	Actor_10.PhysicDesc.Pos.Y = 0
	Actor_10.PhysicDesc.Pos.Z = 57.7188
	Actor_10.PhysicDesc.Pos.Rotation = 281
	Actor_10.PhysicDesc.Density = 1
	Actor_10.PhysicDesc.Collidable = true
	Actor_10.PhysicDesc.SizeX = 1.5
	Actor_10.PhysicDesc.SizeY = 5
	Actor_10.PhysicDesc.SizeZ = 1.5
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
	Actor_11.PhysicDesc.Pos.X = 59.75
	Actor_11.PhysicDesc.Pos.Y = 0
	Actor_11.PhysicDesc.Pos.Z = 36.2188
	Actor_11.PhysicDesc.Pos.Rotation = 25
	Actor_11.PhysicDesc.Density = 1
	Actor_11.PhysicDesc.Collidable = true
	Actor_11.PhysicDesc.SizeX = 1
	Actor_11.PhysicDesc.SizeY = 5
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
	Actor_12.DisplayDesc.ModelName = "FunFrock"
	Actor_12.DisplayDesc.Outfit = "No"
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
	Actor_12.PhysicDesc.Pos.X = 19.3125
	Actor_12.PhysicDesc.Pos.Y = 0
	Actor_12.PhysicDesc.Pos.Z = 51
	Actor_12.PhysicDesc.Pos.Rotation = 25
	Actor_12.PhysicDesc.Density = 1
	Actor_12.PhysicDesc.Collidable = true
	Actor_12.PhysicDesc.SizeX = 1
	Actor_12.PhysicDesc.SizeY = 5
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
	Actor_13.DisplayDesc.ModelName = "GroboClone"
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
	Actor_13.PhysicDesc.Pos.X = 15.375
	Actor_13.PhysicDesc.Pos.Y = 0
	Actor_13.PhysicDesc.Pos.Z = 45.9063
	Actor_13.PhysicDesc.Pos.Rotation = 25
	Actor_13.PhysicDesc.Density = 1
	Actor_13.PhysicDesc.Collidable = true
	Actor_13.PhysicDesc.SizeX = 1.5
	Actor_13.PhysicDesc.SizeY = 5
	Actor_13.PhysicDesc.SizeZ = 1.5
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
	Actor_14.DisplayDesc.ModelName = "GroboClone"
	Actor_14.DisplayDesc.Outfit = "Yellow"
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
	Actor_14.PhysicDesc.Pos.X = 39.3125
	Actor_14.PhysicDesc.Pos.Y = 13
	Actor_14.PhysicDesc.Pos.Z = 11
	Actor_14.PhysicDesc.Pos.Rotation = 433
	Actor_14.PhysicDesc.Density = 1
	Actor_14.PhysicDesc.Collidable = true
	Actor_14.PhysicDesc.SizeX = 1.5
	Actor_14.PhysicDesc.SizeY = 5
	Actor_14.PhysicDesc.SizeZ = 1.5
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
	Actor_15.PhysicDesc.Pos.X = 0
	Actor_15.PhysicDesc.Pos.Y = -1
	Actor_15.PhysicDesc.Pos.Z = 0
	Actor_15.PhysicDesc.Pos.Rotation = 25
	Actor_15.PhysicDesc.Density = 1
	Actor_15.PhysicDesc.Collidable = true
	Actor_15.PhysicDesc.SizeX = 0.5
	Actor_15.PhysicDesc.SizeY = 2
	Actor_15.PhysicDesc.SizeZ = 0.6
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

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 3.5, 5, true)
	Trigger_1:SetPosition(38.5, 13, 11.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map012_1")
	Trigger_1_act1:SetSpawning(6)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit8", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 3.5, 2, true)
	Trigger_2:SetPosition(63.5, 3, 34)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map012_1")
	Trigger_2_act1:SetSpawning(7)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_3:SetPosition(34.999, 5, 25.999)
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
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 1.99805, 4.99609, 1.99805, "Normal", "")
	Trigger_4:SetPosition(33.999, 5, 27.999)
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
	Trigger_5 = ZoneActionTrigger(Trigger_5_info, 2.99804, 7.99609, 1.99805, "Normal", "")
	Trigger_5:SetPosition(54.9365, 0, 32.999)
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

	Trigger_6_info = TriggerInfo(6, "ExitUpTri_6", true, false, false)
	Trigger_6 = ActivationTrigger(Trigger_6_info, 2, "Normal", "")
	Trigger_6:SetPosition(63, 1, 34)
	Trigger_6_act1 = ClientScriptAction()
	Trigger_6_act1_cs = TakeExitUpScript()
	Trigger_6_act1_cs:SetExitPositionX(63)
	Trigger_6_act1_cs:SetExitPositionY(1)
	Trigger_6_act1_cs:SetExitPositionZ(34)
	Trigger_6_act1_cs:SetExitDirection(90)
	Trigger_6_act1:SetScript(Trigger_6_act1_cs)
	Trigger_6:SetAction1(Trigger_6_act1)
	Trigger_6:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_6)

end
