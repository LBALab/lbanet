function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(9)
	Spawn_1:SetPosY(6.01)
	Spawn_1:SetPosZ(18)
	Spawn_1:SetName("spawning0")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(9)
	Spawn_2:SetPosY(1.01)
	Spawn_2:SetPosZ(37)
	Spawn_2:SetName("spawning1")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(8)
	Spawn_3:SetPosY(3.01)
	Spawn_3:SetPosZ(58)
	Spawn_3:SetName("spawning2")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(50)
	Spawn_4:SetPosY(1.01)
	Spawn_4:SetPosZ(18.5)
	Spawn_4:SetName("spawning3")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(27)
	Spawn_5:SetPosY(3.01)
	Spawn_5:SetPosZ(52)
	Spawn_5:SetName("spawning4")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(24.5)
	Spawn_6:SetPosY(1.01)
	Spawn_6:SetPosZ(19)
	Spawn_6:SetName("spawning5")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(28)
	Spawn_7:SetPosY(9.01)
	Spawn_7:SetPosZ(36.5)
	Spawn_7:SetName("spawning6")
	environment:AddSpawn(Spawn_7)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Expanded/Grids/Lbae_map2.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Expanded/Grids/Lbae_map2.phy"
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
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 4, 1, true)
	Trigger_1:SetPosition(10, 5, 16.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("MyMap1_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit2", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 5, 2, true)
	Trigger_2:SetPosition(7.5, 0, 38)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map027_2")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit3", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 3.5, 2, true)
	Trigger_3:SetPosition(6.5, 2, 58)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map003_2")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit4", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 2, 3.5, 1, true)
	Trigger_4:SetPosition(49, 0, 16.5)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map071_2")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit5", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 4.5, 2, true)
	Trigger_5:SetPosition(25.5, 2, 47)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map032_2")
	Trigger_5_act1:SetSpawning(1)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit6", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 2, 3, 1, true)
	Trigger_6:SetPosition(24, 0, 17.5)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map128_2")
	Trigger_6_act1:SetSpawning(1)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit7", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 2, 3, 1, true)
	Trigger_7:SetPosition(29, 9, 33.5)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map076_2")
	Trigger_7_act1:SetSpawning(1)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

end
