function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(32)
	Spawn_1:SetPosY(8.01)
	Spawn_1:SetPosZ(28.5)
	Spawn_1:SetName("from research2")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(32)
	Spawn_2:SetPosY(0.01)
	Spawn_2:SetPosZ(3)
	Spawn_2:SetName("frommaker")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(3)
	Spawn_3:SetPosY(0.01)
	Spawn_3:SetPosZ(32)
	Spawn_3:SetName("frompark")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(31)
	Spawn_4:SetPosY(4.01)
	Spawn_4:SetPosZ(48.5)
	Spawn_4:SetName("fromresearch1")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(4)
	Spawn_5:SetPosY(0.01)
	Spawn_5:SetPosZ(3)
	Spawn_5:SetName("fromriver")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(4)
	Spawn_6:SetPosY(0.01)
	Spawn_6:SetPosZ(61)
	Spawn_6:SetName("fromtown")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(49)
	Spawn_7:SetPosY(0.01)
	Spawn_7:SetPosZ(60)
	Spawn_7:SetName("fromtown2")
	environment:AddSpawn(Spawn_7)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Colozen/Grids/Island/OutsideResearch1.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Colozen/Grids/Island/OutsideResearch1.phy"
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

	Trigger_1_info = TriggerInfo(1, "tomaker", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 4, 5, 1, true)
	Trigger_1:SetPosition(32, 0, 1.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Makers_House")
	Trigger_1_act1:SetSpawning(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "topark", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 5, 4, true)
	Trigger_2:SetPosition(1.5, 0, 32)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Solidirity_Park")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "toresearch1", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 4.5, 5, true)
	Trigger_3:SetPosition(29.5, 4, 48.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Dtech_fuel_supplies")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "toresearch2", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 4.5, 6, true)
	Trigger_4:SetPosition(30.5, 8, 28)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Dtech_Research_Facility")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "toriver", true, false, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 4, 5, 1, true)
	Trigger_5:SetPosition(4, 0, 1.5)
	Trigger_5:SetStayUpdateFrequency(-1)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Techside_River")
	Trigger_5_act1:SetSpawning(2)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "totown1", true, false, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 4, 5, 1, true)
	Trigger_6:SetPosition(4, 0, 62.5)
	Trigger_6:SetStayUpdateFrequency(-1)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Tinker_Town")
	Trigger_6_act1:SetSpawning(5)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "totown2", true, false, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 4, 5, 1, true)
	Trigger_7:SetPosition(49, 0, 61.5)
	Trigger_7:SetStayUpdateFrequency(-1)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Tinker_Town")
	Trigger_7_act1:SetSpawning(6)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "TextTri_8", true, false, false)
	Trigger_8 = ActivationTrigger(Trigger_8_info, 0.333333, "Normal", "")
	Trigger_8:SetPosition(40, 4, 52)
	Trigger_8_act1 = DisplayTextAction()
	Trigger_8_act1:SetTextId(0)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_8)

end
