function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(20)
	Spawn_1:SetPosY(7.01)
	Spawn_1:SetPosZ(38)
	Spawn_1:SetName("fromhouse")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(27)
	Spawn_2:SetPosY(7.01)
	Spawn_2:SetPosZ(33)
	Spawn_2:SetName("fromquestc")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(46.0582)
	Spawn_3:SetPosY(14.111)
	Spawn_3:SetPosZ(5)
	Spawn_3:SetName("fromroyal")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(7)
	Spawn_4:SetPosY(7.01)
	Spawn_4:SetPosZ(43)
	Spawn_4:SetName("fromschool")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(17)
	Spawn_5:SetPosY(2.01)
	Spawn_5:SetPosZ(18)
	Spawn_5:SetName("fromstore")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(7)
	Spawn_6:SetPosY(8.01)
	Spawn_6:SetPosZ(10)
	Spawn_6:SetName("fromvillage1")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(6)
	Spawn_7:SetPosY(13.01)
	Spawn_7:SetPosZ(29)
	Spawn_7:SetName("fromvillage2")
	environment:AddSpawn(Spawn_7)

	Spawn_8 = Spawn(8)
	Spawn_8:SetPosX(47)
	Spawn_8:SetPosY(1.01)
	Spawn_8:SetPosZ(43)
	Spawn_8:SetName("laddercave")
	environment:AddSpawn(Spawn_8)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Colozen/Grids/ColobeeMountain/Village2-simple1.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Colozen/Grids/ColobeeMountain/Village2-simple1.phy"
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

	Trigger_1_info = TriggerInfo(1, "ladderdown", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 3, 2, true)
	Trigger_1:SetPosition(46.5, 0, 45)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Colobee_Cave")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "tohouse", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 4, 2, true)
	Trigger_2:SetPosition(18.5, 7, 38)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Colobee_House")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "toquestc", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 4, 2, true)
	Trigger_3:SetPosition(25.5, 7, 33)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Colobee_Quest_Center")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "toroyal", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 4, 4, 1, true)
	Trigger_4:SetPosition(45, 13, 2.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Colobee_Royal_Court")
	Trigger_4_act1:SetSpawning(2)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "toschool", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 4, 2, true)
	Trigger_5:SetPosition(5.5, 7, 43)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Colobee_School")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "tostore", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 1, 4, 2, true)
	Trigger_6:SetPosition(15.5, 2, 18)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Colobee_Shop")
	Trigger_6_act1:SetSpawning(1)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "tovillage1", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 1, 4, 2, true)
	Trigger_7:SetPosition(5.5, 8, 10)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Colobee_Village")
	Trigger_7_act1:SetSpawning(2)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "tovillage2", true, false, false)
	Trigger_8 = ZoneTrigger(Trigger_8_info, 1, 4, 2, true)
	Trigger_8:SetPosition(4.5, 13, 29)
	Trigger_8:SetStayUpdateFrequency(-1)
	Trigger_8_act1 = TeleportAction()
	Trigger_8_act1:SetMapName("Colobee_Village")
	Trigger_8_act1:SetSpawning(3)
	Trigger_8:SetAction1(Trigger_8_act1)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "LadderTri_9", true, false, false)
	Trigger_9 = ActivationTrigger(Trigger_9_info, 1.66667, "Normal", "")
	Trigger_9:SetPosition(42, 1, 43)
	Trigger_9_act1 = ClientScriptAction()
	Trigger_9_act1_cs = GoUpLadderScript()
	Trigger_9_act1_cs:SetLadderPositionX(42)
	Trigger_9_act1_cs:SetLadderPositionY(1)
	Trigger_9_act1_cs:SetLadderPositionZ(43)
	Trigger_9_act1_cs:SetLadderHeight(6)
	Trigger_9_act1_cs:SetLadderDirection(270)
	Trigger_9_act1:SetScript(Trigger_9_act1_cs)
	Trigger_9:SetAction1(Trigger_9_act1)
	Trigger_9:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "LadderTri_10", true, false, false)
	Trigger_10 = ActivationTrigger(Trigger_10_info, 1.66667, "Normal", "")
	Trigger_10:SetPosition(46, 8, 9)
	Trigger_10_act1 = ClientScriptAction()
	Trigger_10_act1_cs = GoUpLadderScript()
	Trigger_10_act1_cs:SetLadderPositionX(46)
	Trigger_10_act1_cs:SetLadderPositionY(8)
	Trigger_10_act1_cs:SetLadderPositionZ(9)
	Trigger_10_act1_cs:SetLadderHeight(4)
	Trigger_10_act1_cs:SetLadderDirection(180)
	Trigger_10_act1:SetScript(Trigger_10_act1_cs)
	Trigger_10:SetAction1(Trigger_10_act1)
	Trigger_10:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "LadderTri_11", true, false, false)
	Trigger_11 = ActivationTrigger(Trigger_11_info, 1.66667, "Normal", "")
	Trigger_11:SetPosition(8, 7, 31)
	Trigger_11_act1 = ClientScriptAction()
	Trigger_11_act1_cs = GoUpLadderScript()
	Trigger_11_act1_cs:SetLadderPositionX(8)
	Trigger_11_act1_cs:SetLadderPositionY(7)
	Trigger_11_act1_cs:SetLadderPositionZ(31)
	Trigger_11_act1_cs:SetLadderHeight(6)
	Trigger_11_act1_cs:SetLadderDirection(180)
	Trigger_11_act1:SetScript(Trigger_11_act1_cs)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "LadderTri_12", true, false, false)
	Trigger_12 = ActivationTrigger(Trigger_12_info, 1.66667, "Normal", "")
	Trigger_12:SetPosition(21, 2, 20)
	Trigger_12_act1 = ClientScriptAction()
	Trigger_12_act1_cs = GoUpLadderScript()
	Trigger_12_act1_cs:SetLadderPositionX(21)
	Trigger_12_act1_cs:SetLadderPositionY(2)
	Trigger_12_act1_cs:SetLadderPositionZ(20)
	Trigger_12_act1_cs:SetLadderHeight(5)
	Trigger_12_act1_cs:SetLadderDirection(180)
	Trigger_12_act1:SetScript(Trigger_12_act1_cs)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_12)

end
