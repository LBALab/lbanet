function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(20.5)
	Spawn_1:SetPosY(1)
	Spawn_1:SetPosZ(31.5)
	Spawn_1:SetName("from_otringal")
	Spawn_1:SetForceRotation(true)
	Spawn_1:SetRotation(180)
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(20.5)
	Spawn_2:SetPosY(9)
	Spawn_2:SetPosZ(14)
	Spawn_2:SetName("from_loweleup")
	environment:AddSpawn(Spawn_2)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map51.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 0
	Actor_1.DisplayDesc.ColorG = -2.21459e+009
	Actor_1.DisplayDesc.ColorB = 4.2039e-045
	Actor_1.DisplayDesc.ColorA = 0
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
	Actor_1.PhysicDesc.Density = 1.10703e-043
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 1.4013e-044
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 9.18341e-041
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map51.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = 0
	Actor_1.ExtraInfo.NameColorG = 9.18341e-041
	Actor_1.ExtraInfo.NameColorB = 4.2039e-045
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "to_otringal", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 7, 1, true)
	Trigger_1:SetPosition(20.5, 1, 33.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("OTRINGAL")
	Trigger_1_act1:SetSpawning(6)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "to_loweleup", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 7, 8, 1, true)
	Trigger_2:SetPosition(20.5, 9, 11.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map084_2")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

end

