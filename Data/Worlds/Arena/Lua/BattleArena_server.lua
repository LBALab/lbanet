function InitMap(environment)
	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = -1163005939
	Actor_1.DisplayDesc.ModelName = "Worlds/Arena/Grids/TheComplexPvpArena.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = -0.00132704
	Actor_1.DisplayDesc.ColorG = -0.00132704
	Actor_1.DisplayDesc.ColorB = -0.00132704
	Actor_1.DisplayDesc.ColorA = -0.00132704
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
	Actor_1.PhysicDesc.Density = -0.00132704
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = -0.00132704
	Actor_1.PhysicDesc.SizeY = -0.00132704
	Actor_1.PhysicDesc.SizeZ = -0.00132704
	Actor_1.PhysicDesc.Filename = "Worlds/Arena/Grids/TheComplexPvpArena.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = -0.00132704
	Actor_1.ExtraInfo.NameColorG = -0.00132704
	Actor_1.ExtraInfo.NameColorB = -0.00132704
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Actor_3 = ActorObjectInfo(3)
	Actor_3:SetRenderType(3)
	Actor_3.DisplayDesc.ModelId = 0
	Actor_3.DisplayDesc.ModelName = "FunFrock"
	Actor_3.DisplayDesc.Outfit = "No"
	Actor_3.DisplayDesc.Weapon = "No"
	Actor_3.DisplayDesc.Mode = "Normal"
	Actor_3.DisplayDesc.UseLight = true
	Actor_3.DisplayDesc.CastShadow = false
	Actor_3.DisplayDesc.ColorR = 1
	Actor_3.DisplayDesc.ColorG = 1
	Actor_3.DisplayDesc.ColorB = 1
	Actor_3.DisplayDesc.ColorA = 1
	Actor_3.DisplayDesc.TransX = 0
	Actor_3.DisplayDesc.TransY = 0
	Actor_3.DisplayDesc.TransZ = 0
	Actor_3.DisplayDesc.ScaleX = 5
	Actor_3.DisplayDesc.ScaleY = 5
	Actor_3.DisplayDesc.ScaleZ = 5
	Actor_3.DisplayDesc.RotX = 0
	Actor_3.DisplayDesc.RotY = 0
	Actor_3.DisplayDesc.RotZ = 0
	Actor_3:SetModelState(2)
	Actor_3:AddColorSwap(1,240,236)
	Actor_3:AddColorSwap(2,52,84)
	Actor_3:AddColorSwap(3,191,228)
	Actor_3.PhysicDesc.Pos.X = 37.5
	Actor_3.PhysicDesc.Pos.Y = 7
	Actor_3.PhysicDesc.Pos.Z = 8.5
	Actor_3.PhysicDesc.Pos.Rotation = 0
	Actor_3.PhysicDesc.Density = 1
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = 5
	Actor_3.PhysicDesc.SizeY = 22
	Actor_3.PhysicDesc.SizeZ = 5
	Actor_3.PhysicDesc.Filename = ""
	Actor_3:SetPhysicalActorType(1)
	Actor_3:SetPhysicalShape(1)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 1
	Actor_3.ExtraInfo.NameColorG = 1
	Actor_3.ExtraInfo.NameColorB = 1
	Actor_3H = ActorHandler(Actor_3)
	environment:AddActorObject(Actor_3H)

	Actor_4 = ActorObjectInfo(4)
	Actor_4:SetRenderType(3)
	Actor_4.DisplayDesc.ModelId = 0
	Actor_4.DisplayDesc.ModelName = "Ameba"
	Actor_4.DisplayDesc.Outfit = "No"
	Actor_4.DisplayDesc.Weapon = "No"
	Actor_4.DisplayDesc.Mode = "Normal"
	Actor_4.DisplayDesc.UseLight = true
	Actor_4.DisplayDesc.CastShadow = true
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
	Actor_4:SetModelState(2)
	Actor_4:AddColorSwap(1,112,136)
	Actor_4:AddColorSwap(1,192,202)
	Actor_4.PhysicDesc.Pos.X = 42.5
	Actor_4.PhysicDesc.Pos.Y = 7
	Actor_4.PhysicDesc.Pos.Z = 9.5
	Actor_4.PhysicDesc.Pos.Rotation = 0
	Actor_4.PhysicDesc.Density = 1
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 2
	Actor_4.PhysicDesc.SizeY = 1
	Actor_4.PhysicDesc.SizeZ = 2.5
	Actor_4.PhysicDesc.Filename = ""
	Actor_4:SetPhysicalActorType(1)
	Actor_4:SetPhysicalShape(2)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 1
	Actor_4.ExtraInfo.NameColorG = 1
	Actor_4.ExtraInfo.NameColorB = 1
	Actor_4H = ActorHandler(Actor_4)
	environment:AddActorObject(Actor_4H)

	Trigger_1_info = TriggerInfo(1, "test", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 2, 2, true)
	Trigger_1:SetPosition(45.8, 7, 10)
	Trigger_1_act1 = CustomAction()
	Trigger_1_act1:SetLuaFunctionName("TestServerC")
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

end
