function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(25)
	Spawn_1:SetPosY(5.01)
	Spawn_1:SetPosZ(18.5)
	Spawn_1:SetName("fromcafe")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(32.5)
	Spawn_2:SetPosY(6.01)
	Spawn_2:SetPosZ(11)
	Spawn_2:SetName("fromfactory")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(35)
	Spawn_3:SetPosY(3.01)
	Spawn_3:SetPosZ(34.5)
	Spawn_3:SetName("fromflower")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(15.5)
	Spawn_4:SetPosY(3.01)
	Spawn_4:SetPosZ(57)
	Spawn_4:SetName("frommuseum")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(6)
	Spawn_5:SetPosY(3.01)
	Spawn_5:SetPosZ(3)
	Spawn_5:SetName("fromout1")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(50)
	Spawn_6:SetPosY(3.01)
	Spawn_6:SetPosZ(3)
	Spawn_6:SetName("fromout2")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(7)
	Spawn_7:SetPosY(3.01)
	Spawn_7:SetPosZ(25)
	Spawn_7:SetName("frompolice")
	environment:AddSpawn(Spawn_7)

	Spawn_8 = Spawn(8)
	Spawn_8:SetPosX(21.5)
	Spawn_8:SetPosY(3.01)
	Spawn_8:SetPosZ(27)
	Spawn_8:SetName("fromsewer")
	environment:AddSpawn(Spawn_8)

	Spawn_9 = Spawn(9)
	Spawn_9:SetPosX(49)
	Spawn_9:SetPosY(3.01)
	Spawn_9:SetPosZ(16.5)
	Spawn_9:SetName("fromsewer2")
	environment:AddSpawn(Spawn_9)

	Spawn_10 = Spawn(10)
	Spawn_10:SetPosX(42.5)
	Spawn_10:SetPosY(5.01)
	Spawn_10:SetPosZ(21)
	Spawn_10:SetName("fromshop")
	environment:AddSpawn(Spawn_10)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Colozen/Grids/Island/Town1.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Colozen/Grids/Island/Town1.phy"
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

	Trigger_1_info = TriggerInfo(1, "tocafe", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4.5, 3, true)
	Trigger_1:SetPosition(23.5, 5, 18.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("The_Tinkers_Cafe")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "tofactory", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 4.5, 1, true)
	Trigger_2:SetPosition(32.5, 6, 9.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Dtech_Industries")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "toflower", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 4.5, 3, true)
	Trigger_3:SetPosition(33.5, 3, 34.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("The_Innovation_house")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "tomuseum", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 3, 4.5, 1, true)
	Trigger_4:SetPosition(15.5, 3, 55.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Colozen_Museum")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "toout1", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 4, 5, 1, true)
	Trigger_5:SetPosition(6, 3, 1.5)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Tech-Island_Research_Centre")
	Trigger_5_act1:SetSpawning(6)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "toout2", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 4, 5, 1, true)
	Trigger_6:SetPosition(50, 3, 1.5)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Tech-Island_Research_Centre")
	Trigger_6_act1:SetSpawning(7)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "topolice", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 1, 4.5, 4, true)
	Trigger_7:SetPosition(5.5, 3, 25)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Tinker-Town_Police_Station")
	Trigger_7_act1:SetSpawning(1)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "tosewer1", true, false, false)
	Trigger_8 = ZoneTrigger(Trigger_8_info, 3, 2.5, 1, true)
	Trigger_8:SetPosition(21.5, 3, 24.5)
	Trigger_8:SetStayUpdateFrequency(-1)
	Trigger_8_act1 = TeleportAction()
	Trigger_8_act1:SetMapName("Tinker-town_Sewers")
	Trigger_8_act1:SetSpawning(1)
	Trigger_8:SetAction1(Trigger_8_act1)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "tosewer2", true, false, false)
	Trigger_9 = ZoneTrigger(Trigger_9_info, 1, 2.5, 3, true)
	Trigger_9:SetPosition(46.5, 3, 16.5)
	Trigger_9:SetStayUpdateFrequency(-1)
	Trigger_9_act1 = TeleportAction()
	Trigger_9_act1:SetMapName("Tinker-town_Sewers")
	Trigger_9_act1:SetSpawning(2)
	Trigger_9:SetAction1(Trigger_9_act1)
	environment:AddTrigger(Trigger_9)

	Trigger_10_info = TriggerInfo(10, "toshop", true, false, false)
	Trigger_10 = ZoneTrigger(Trigger_10_info, 3, 4.5, 1, true)
	Trigger_10:SetPosition(42.5, 4, 18.5)
	Trigger_10:SetStayUpdateFrequency(-1)
	Trigger_10_act1 = TeleportAction()
	Trigger_10_act1:SetMapName("Tinker-Town_Shop")
	Trigger_10_act1:SetSpawning(1)
	Trigger_10:SetAction1(Trigger_10_act1)
	environment:AddTrigger(Trigger_10)

	Trigger_11_info = TriggerInfo(11, "ExitDownTri_11", true, false, false)
	Trigger_11 = ActivationTrigger(Trigger_11_info, 1.66667, "Normal", "")
	Trigger_11:SetPosition(48, 3, 16.5)
	Trigger_11_act1 = ClientScriptAction()
	Trigger_11_act1_cs = TakeExitDownScript()
	Trigger_11_act1_cs:SetExitPositionX(48)
	Trigger_11_act1_cs:SetExitPositionY(3)
	Trigger_11_act1_cs:SetExitPositionZ(16.5)
	Trigger_11_act1_cs:SetExitDirection(270)
	Trigger_11_act1:SetScript(Trigger_11_act1_cs)
	Trigger_11:SetAction1(Trigger_11_act1)
	Trigger_11:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_11)

	Trigger_12_info = TriggerInfo(12, "ExitDownTri_12", true, false, false)
	Trigger_12 = ActivationTrigger(Trigger_12_info, 1.66667, "Normal", "")
	Trigger_12:SetPosition(21.5, 3, 26)
	Trigger_12_act1 = ClientScriptAction()
	Trigger_12_act1_cs = TakeExitDownScript()
	Trigger_12_act1_cs:SetExitPositionX(21.5)
	Trigger_12_act1_cs:SetExitPositionY(3)
	Trigger_12_act1_cs:SetExitPositionZ(26)
	Trigger_12_act1_cs:SetExitDirection(180)
	Trigger_12_act1:SetScript(Trigger_12_act1_cs)
	Trigger_12:SetAction1(Trigger_12_act1)
	Trigger_12:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_12)

	Trigger_13_info = TriggerInfo(13, "TextTri_13", true, false, false)
	Trigger_13 = ActivationTrigger(Trigger_13_info, 0.666667, "Normal", "")
	Trigger_13:SetPosition(5.99, 3, 19.7)
	Trigger_13_act1 = DisplayTextAction()
	Trigger_13_act1:SetTextId(0)
	Trigger_13:SetAction1(Trigger_13_act1)
	Trigger_13:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_13)

	Trigger_14_info = TriggerInfo(14, "TextTri_14", true, false, false)
	Trigger_14 = ActivationTrigger(Trigger_14_info, 0.333333, "Normal", "")
	Trigger_14:SetPosition(35, 4, 21)
	Trigger_14_act1 = DisplayTextAction()
	Trigger_14_act1:SetTextId(0)
	Trigger_14:SetAction1(Trigger_14_act1)
	Trigger_14:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_14)

end
