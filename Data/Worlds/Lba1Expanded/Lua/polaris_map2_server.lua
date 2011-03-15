function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(59)
	Spawn_1:SetPosY(0.01)
	Spawn_1:SetPosZ(47)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Expanded/Grids/Tippet_island_water.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Expanded/Grids/Tippet_island_water.phy"
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

	Trigger_1_info = TriggerInfo(1, "exit1", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4, 4, true)
	Trigger_1:SetPosition(60.5, -1, 47)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map074_1")
	Trigger_1_act1:SetSpawning(7)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "LadderTri_2", true, false, false)
	Trigger_2 = ActivationTrigger(Trigger_2_info, 1, "Normal", "")
	Trigger_2:SetPosition(52, 0, 47)
	Trigger_2_act1 = ClientScriptAction()
	Trigger_2_act1_cs = GoUpLadderScript()
	Trigger_2_act1_cs:SetLadderPositionX(52)
	Trigger_2_act1_cs:SetLadderPositionY(0)
	Trigger_2_act1_cs:SetLadderPositionZ(47)
	Trigger_2_act1_cs:SetLadderHeight(4)
	Trigger_2_act1_cs:SetLadderDirection(270)
	Trigger_2_act1:SetScript(Trigger_2_act1_cs)
	Trigger_2:SetAction1(Trigger_2_act1)
	Trigger_2:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_2)

end
