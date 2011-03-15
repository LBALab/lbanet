function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(52)
	Spawn_1:SetPosY(2.01)
	Spawn_1:SetPosZ(34)
	Spawn_1:SetName("door1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(38.5)
	Spawn_2:SetPosY(2.01)
	Spawn_2:SetPosZ(22)
	Spawn_2:SetName("ladder")
	environment:AddSpawn(Spawn_2)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Colozen/Grids/ColobeeMountain/start-village2-1.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Colozen/Grids/ColobeeMountain/start-village2-1.phy"
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

	Trigger_1_info = TriggerInfo(1, "door1ex", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4, 4, true)
	Trigger_1:SetPosition(54.5, 2, 34)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Cloning_Chamber")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "ladder", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 2, 1, true)
	Trigger_2:SetPosition(37, 9, 20.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Colobee_Village_Square")
	Trigger_2_act1:SetSpawning(8)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "LadderTri_3", true, false, false)
	Trigger_3 = ActivationTrigger(Trigger_3_info, 1.66667, "Normal", "")
	Trigger_3:SetPosition(37, 2, 20)
	Trigger_3_act1 = ClientScriptAction()
	Trigger_3_act1_cs = GoUpLadderScript()
	Trigger_3_act1_cs:SetLadderPositionX(37)
	Trigger_3_act1_cs:SetLadderPositionY(2)
	Trigger_3_act1_cs:SetLadderPositionZ(20)
	Trigger_3_act1_cs:SetLadderHeight(12)
	Trigger_3_act1_cs:SetLadderDirection(180)
	Trigger_3_act1:SetScript(Trigger_3_act1_cs)
	Trigger_3:SetAction1(Trigger_3_act1)
	Trigger_3:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_3)

end
