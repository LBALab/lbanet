function InitMap(environment)
	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map45.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map45.phy"
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

	Actor_2 = ActorObjectInfo(2)
	Actor_2:SetRenderType(3)
	Actor_2.DisplayDesc.ColorMaterialType = 4
	Actor_2.DisplayDesc.MatAmbientColorR = -0.2
	Actor_2.DisplayDesc.MatAmbientColorG = -0.2
	Actor_2.DisplayDesc.MatAmbientColorB = -0.2
	Actor_2.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_2.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_2.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_2.DisplayDesc.ModelId = 0
	Actor_2.DisplayDesc.ModelName = "Motorcycle"
	Actor_2.DisplayDesc.Outfit = "No"
	Actor_2.DisplayDesc.Weapon = "No"
	Actor_2.DisplayDesc.Mode = "Normal"
	Actor_2.DisplayDesc.UseLight = true
	Actor_2.DisplayDesc.CastShadow = false
	Actor_2.DisplayDesc.ColorR = 1
	Actor_2.DisplayDesc.ColorG = 1
	Actor_2.DisplayDesc.ColorB = 1
	Actor_2.DisplayDesc.ColorA = 1
	Actor_2.DisplayDesc.TransX = 0
	Actor_2.DisplayDesc.TransY = 0
	Actor_2.DisplayDesc.TransZ = 0
	Actor_2.DisplayDesc.ScaleX = 1
	Actor_2.DisplayDesc.ScaleY = 1
	Actor_2.DisplayDesc.ScaleZ = 1
	Actor_2.DisplayDesc.RotX = 0
	Actor_2.DisplayDesc.RotY = 0
	Actor_2.DisplayDesc.RotZ = 0
	Actor_2:SetModelState(1)
	Actor_2.PhysicDesc.Pos.X = 27
	Actor_2.PhysicDesc.Pos.Y = 1
	Actor_2.PhysicDesc.Pos.Z = 4
	Actor_2.PhysicDesc.Pos.Rotation = 0
	Actor_2.PhysicDesc.Density = 1
	Actor_2.PhysicDesc.Collidable = true
	Actor_2.PhysicDesc.SizeX = 1
	Actor_2.PhysicDesc.SizeY = 4
	Actor_2.PhysicDesc.SizeZ = 3
	Actor_2.PhysicDesc.Filename = ""
	Actor_2:SetPhysicalActorType(2)
	Actor_2:SetPhysicalShape(2)
	Actor_2.ExtraInfo.Name = ""
	Actor_2.ExtraInfo.NameColorR = 0
	Actor_2.ExtraInfo.NameColorG = 0
	Actor_2.ExtraInfo.NameColorB = 0
	Actor_2.ExtraInfo.Display = false
	Actor_2.LifeInfo.Display = false
	Actor_2H = ActorHandler(Actor_2)
	Actor_2_Sc0 = ASPWaitForSignal(5)
	Actor_2H:AddScriptPart(Actor_2_Sc0)
	Actor_2_Sc1 = ASPRotate(180,0.05,false)
	Actor_2H:AddScriptPart(Actor_2_Sc1)
	Actor_2_Sc2 = ASPGoTo(27,1,0,0.005)
	Actor_2H:AddScriptPart(Actor_2_Sc2)
	Actor_2_Sc3 = ASPSendSignal(6,0)
	Actor_2H:AddScriptPart(Actor_2_Sc3)
	environment:AddActorObject(Actor_2H)

	Actor_3 = ActorObjectInfo(3)
	Actor_3:SetRenderType(3)
	Actor_3.DisplayDesc.ColorMaterialType = 4
	Actor_3.DisplayDesc.MatAmbientColorR = -0.2
	Actor_3.DisplayDesc.MatAmbientColorG = -0.2
	Actor_3.DisplayDesc.MatAmbientColorB = -0.2
	Actor_3.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_3.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_3.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_3.DisplayDesc.ModelId = 0
	Actor_3.DisplayDesc.ModelName = "Object"
	Actor_3.DisplayDesc.Outfit = "MekaPingouin"
	Actor_3.DisplayDesc.Weapon = "No"
	Actor_3.DisplayDesc.Mode = "Normal"
	Actor_3.DisplayDesc.UseLight = true
	Actor_3.DisplayDesc.CastShadow = true
	Actor_3.DisplayDesc.ColorR = 1
	Actor_3.DisplayDesc.ColorG = 1
	Actor_3.DisplayDesc.ColorB = 1
	Actor_3.DisplayDesc.ColorA = 1
	Actor_3.DisplayDesc.TransX = 0
	Actor_3.DisplayDesc.TransY = 0
	Actor_3.DisplayDesc.TransZ = 0
	Actor_3.DisplayDesc.ScaleX = 1
	Actor_3.DisplayDesc.ScaleY = 1
	Actor_3.DisplayDesc.ScaleZ = 1
	Actor_3.DisplayDesc.RotX = 0
	Actor_3.DisplayDesc.RotY = 0
	Actor_3.DisplayDesc.RotZ = 0
	Actor_3:SetModelState(1)
	Actor_3.PhysicDesc.Pos.X = 0
	Actor_3.PhysicDesc.Pos.Y = 7.375
	Actor_3.PhysicDesc.Pos.Z = 0
	Actor_3.PhysicDesc.Pos.Rotation = 25
	Actor_3.PhysicDesc.Density = 1
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = 0.5
	Actor_3.PhysicDesc.SizeY = 2
	Actor_3.PhysicDesc.SizeZ = 0.6
	Actor_3.PhysicDesc.Filename = ""
	Actor_3:SetPhysicalActorType(2)
	Actor_3:SetPhysicalShape(2)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 0
	Actor_3.ExtraInfo.NameColorG = 0
	Actor_3.ExtraInfo.NameColorB = 0
	Actor_3.ExtraInfo.Display = false
	Actor_3.LifeInfo.Display = false
	Actor_3H = NPCHandler(Actor_3)
	Actor_3H_dia = DialogPart()
	Actor_3H_dia:SetResetDialog(false)
	Actor_3H:SetRootDialog(Actor_3H_dia)
	Actor_3H:SetNpcName(-1)
	Actor_3H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_3H)

	Trigger_1_info = TriggerInfo(1, "exit2", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 3, 1, true)
	Trigger_1:SetPosition(1, 3, 0.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map042_1")
	Trigger_1_act1:SetSpawning(17)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

end
