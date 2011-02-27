function InitMap(environment)
	Spawn_0 = Spawn(0)
	Spawn_0:SetPosX(14)
	Spawn_0:SetPosY(3)
	Spawn_0:SetPosZ(29)
	Spawn_0:SetName("from_cita")
	environment:AddSpawn(Spawn_0)

	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(17)
	Spawn_1:SetPosY(3)
	Spawn_1:SetPosZ(11)
	Spawn_1:SetName("from_cellar")
	Spawn_1:SetForceRotation(true)
	Spawn_1:SetRotation(0)
	environment:AddSpawn(Spawn_1)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = -1163005939
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map4.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map4.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = -0.00132704
	Actor_1.ExtraInfo.NameColorG = -0.00132704
	Actor_1.ExtraInfo.NameColorB = -0.00132704
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "to_cita", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 8, 1, true)
	Trigger_1:SetPosition(14, 3, 30.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("CITABAU")
	Trigger_1_act1:SetSpawning(7)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "to_cellar", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 8, 1, true)
	Trigger_2:SetPosition(17, 3, 9.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map005_2")
	Trigger_2_act1:SetSpawning(0)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

end

