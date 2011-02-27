function InitMap(environment)
	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(24)
	Spawn_2:SetPosY(2)
	Spawn_2:SetPosZ(19)
	Spawn_2:SetName("FromCitadel")
	Spawn_2:SetForceRotation(true)
	Spawn_2:SetRotation(180)
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(6)
	Spawn_3:SetPosY(7)
	Spawn_3:SetPosZ(7)
	Spawn_3:SetName("From2ndroom")
	environment:AddSpawn(Spawn_3)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map1.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 0
	Actor_1.DisplayDesc.ColorG = 0
	Actor_1.DisplayDesc.ColorB = 0
	Actor_1.DisplayDesc.ColorA = 0
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map1.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = 0
	Actor_1.ExtraInfo.NameColorG = 0
	Actor_1.ExtraInfo.NameColorB = 0
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "To2ndroom", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 6, 2, true)
	Trigger_1:SetPosition(4.5, 6.8, 7)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map002_2")
	Trigger_1_act1:SetSpawning(0)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "Tocitadel", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 8, 1, true)
	Trigger_2:SetPosition(24, 2, 20.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("CITABAU")
	Trigger_2_act1:SetSpawning(2)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

end

