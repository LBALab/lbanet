function InitMap(environment)
	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = -1163005939
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map7.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = -0.00132704
	Actor_1.DisplayDesc.ColorG = -0.00132704
	Actor_1.DisplayDesc.ColorB = -0.00132704
	Actor_1.DisplayDesc.ColorA = -0.00132704
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map7.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = -0.00132704
	Actor_1.ExtraInfo.NameColorG = -0.00132704
	Actor_1.ExtraInfo.NameColorB = -0.00132704
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "to_baggagebag", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 7, 1, true)
	Trigger_1:SetPosition(39, 8, 63.6)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map006_2")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "to_baggage", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 8, 2, true)
	Trigger_2:SetPosition(0.5, 7, 59)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map006_2")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "to_baggagesecret", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 7, 3, true)
	Trigger_3:SetPosition(49, 10, 5.5)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map017_2")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

end
