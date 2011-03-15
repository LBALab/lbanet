function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(35)
	Spawn_1:SetPosY(8)
	Spawn_1:SetPosZ(52)
	Spawn_1:SetName("from_lowelelow")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(21.5)
	Spawn_2:SetPosY(14)
	Spawn_2:SetPosZ(37)
	Spawn_2:SetName("from_otr2")
	Spawn_2:SetForceRotation(true)
	Spawn_2:SetRotation(90)
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(48)
	Spawn_3:SetPosY(14)
	Spawn_3:SetPosZ(37)
	Spawn_3:SetName("from_otr1")
	Spawn_3:SetForceRotation(true)
	Spawn_3:SetRotation(270)
	environment:AddSpawn(Spawn_3)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map84.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 1
	Actor_1.DisplayDesc.ColorG = -2.21459e+009
	Actor_1.DisplayDesc.ColorB = 4.2039e-045
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
	Actor_1.PhysicDesc.Density = 1.10703e-043
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 1.4013e-044
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 9.18341e-041
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map84.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = 0
	Actor_1.ExtraInfo.NameColorG = 9.18341e-041
	Actor_1.ExtraInfo.NameColorB = 4.2039e-045
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "to_lowelelow", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 16, 7, 1, true)
	Trigger_1:SetPosition(35, 8, 55)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map051_2")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "to_otr1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 8, 4, true)
	Trigger_2:SetPosition(50.5, 14, 37)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("OTRINGAL")
	Trigger_2_act1:SetSpawning(10)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "to_otr2", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 8, 4, true)
	Trigger_3:SetPosition(19.5, 14, 37)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("OTRINGAL")
	Trigger_3_act1:SetSpawning(11)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

end

