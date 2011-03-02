function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(21)
	Spawn_1:SetPosY(1.01)
	Spawn_1:SetPosZ(59)
	Spawn_1:SetName("fromdock")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(30)
	Spawn_2:SetPosY(5.01)
	Spawn_2:SetPosZ(6)
	Spawn_2:SetName("fromsquare1")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(38)
	Spawn_3:SetPosY(9.01)
	Spawn_3:SetPosZ(33)
	Spawn_3:SetName("fromsquare2")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(7)
	Spawn_4:SetPosY(11.01)
	Spawn_4:SetPosZ(5)
	Spawn_4:SetName("fromtech")
	environment:AddSpawn(Spawn_4)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Colozen/Grids/ColobeeMountain/Village1-1.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 0
	Actor_1.DisplayDesc.ColorG = 0
	Actor_1.DisplayDesc.ColorB = 0
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
	Actor_1.PhysicDesc.Density = 1
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 0
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 0
	Actor_1.PhysicDesc.Filename = "Worlds/Colozen/Grids/ColobeeMountain/Village1-1.phy"
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

	Trigger_1_info = TriggerInfo(1, "todock", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 4, 1, true)
	Trigger_1:SetPosition(21, 1, 61.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Tech-Island_Docks")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "tomaker", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 4, 2, true)
	Trigger_2:SetPosition(2.5, 14, 6)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Makers_House")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "tosquare1", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 4, 2, true)
	Trigger_3:SetPosition(33.5, 5, 6)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Colobee_Village_Square")
	Trigger_3_act1:SetSpawning(6)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "tosquare2", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 4, 2, true)
	Trigger_4:SetPosition(40.5, 9, 33)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Colobee_Village_Square")
	Trigger_4_act1:SetSpawning(7)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "LadderTri_5", true, false, false)
	Trigger_5 = ActivationTrigger(Trigger_5_info, 1.66667, "Normal", "")
	Trigger_5:SetPosition(11, 5, 6)
	Trigger_5_act1 = ClientScriptAction()
	Trigger_5_act1_cs = GoUpLadderScript()
	Trigger_5_act1_cs:SetLadderPositionX(11)
	Trigger_5_act1_cs:SetLadderPositionY(5)
	Trigger_5_act1_cs:SetLadderPositionZ(6)
	Trigger_5_act1_cs:SetLadderHeight(6)
	Trigger_5_act1_cs:SetLadderDirection(270)
	Trigger_5_act1:SetScript(Trigger_5_act1_cs)
	Trigger_5:SetAction1(Trigger_5_act1)
	Trigger_5:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "LadderTri_6", true, false, false)
	Trigger_6 = ActivationTrigger(Trigger_6_info, 1.66667, "Normal", "")
	Trigger_6:SetPosition(12, 1, 16)
	Trigger_6_act1 = ClientScriptAction()
	Trigger_6_act1_cs = GoUpLadderScript()
	Trigger_6_act1_cs:SetLadderPositionX(12)
	Trigger_6_act1_cs:SetLadderPositionY(1)
	Trigger_6_act1_cs:SetLadderPositionZ(16)
	Trigger_6_act1_cs:SetLadderHeight(8)
	Trigger_6_act1_cs:SetLadderDirection(270)
	Trigger_6_act1:SetScript(Trigger_6_act1_cs)
	Trigger_6:SetAction1(Trigger_6_act1)
	Trigger_6:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_6)

end
