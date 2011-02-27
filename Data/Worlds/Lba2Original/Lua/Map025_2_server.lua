function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(20)
	Spawn_1:SetPosY(0)
	Spawn_1:SetPosZ(16)
	Spawn_1:SetName("from_desertent1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(17)
	Spawn_2:SetPosY(0)
	Spawn_2:SetPosZ(19)
	Spawn_2:SetName("from_desertent2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(17)
	Spawn_3:SetPosY(0)
	Spawn_3:SetPosZ(3)
	Spawn_3:SetName("from_hacienda2")
	environment:AddSpawn(Spawn_3)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map25.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map25.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = 0
	Actor_1.ExtraInfo.NameColorG = 0
	Actor_1.ExtraInfo.NameColorB = 0
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "to_desertent1", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 8, 2, true)
	Trigger_1:SetPosition(22.5, 0, 16)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("DESERT")
	Trigger_1_act1:SetSpawning(8)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "to_desertent2", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 8, 1, true)
	Trigger_2:SetPosition(17, 0, 21.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("DESERT")
	Trigger_2_act1:SetSpawning(9)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "to_hacienda2", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 8, 1, true)
	Trigger_3:SetPosition(17, 0, 0.5)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map030_2")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

end

