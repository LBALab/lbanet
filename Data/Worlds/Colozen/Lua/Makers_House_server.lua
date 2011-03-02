function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(7)
	Spawn_1:SetPosY(0.01)
	Spawn_1:SetPosZ(15)
	Spawn_1:SetName("fromcolobee")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(9)
	Spawn_2:SetPosY(0.01)
	Spawn_2:SetPosZ(30.5)
	Spawn_2:SetName("frommakerinside")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(15)
	Spawn_3:SetPosY(0.01)
	Spawn_3:SetPosZ(59)
	Spawn_3:SetName("fromtown")
	environment:AddSpawn(Spawn_3)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Colozen/Grids/Island/Outside1.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Colozen/Grids/Island/Outside1.phy"
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

	Trigger_1_info = TriggerInfo(1, "tocolobee", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 4, 1, true)
	Trigger_1:SetPosition(8, 0, 12.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Colobee_Village")
	Trigger_1_act1:SetSpawning(4)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "tomakerinside", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 4.5, 3, true)
	Trigger_2:SetPosition(7.5, 0, 30.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Inside_Makers_House")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "totown", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 4, 5, 1, true)
	Trigger_3:SetPosition(15, 0, 60.5)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Tech-Island_Research_Centre")
	Trigger_3_act1:SetSpawning(2)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "ExitUpTri_4", true, false, false)
	Trigger_4 = ActivationTrigger(Trigger_4_info, 1.66667, "Normal", "")
	Trigger_4:SetPosition(8, 0, 13)
	Trigger_4_act1 = ClientScriptAction()
	Trigger_4_act1_cs = TakeExitUpScript()
	Trigger_4_act1_cs:SetExitPositionX(8)
	Trigger_4_act1_cs:SetExitPositionY(0)
	Trigger_4_act1_cs:SetExitPositionZ(13)
	Trigger_4_act1_cs:SetExitDirection(180)
	Trigger_4_act1:SetScript(Trigger_4_act1_cs)
	Trigger_4:SetAction1(Trigger_4_act1)
	Trigger_4:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "TextTri_5", true, false, false)
	Trigger_5 = ActivationTrigger(Trigger_5_info, 0.333333, "Normal", "")
	Trigger_5:SetPosition(28, 0, 48)
	Trigger_5_act1 = DisplayTextAction()
	Trigger_5_act1:SetTextId(0)
	Trigger_5:SetAction1(Trigger_5_act1)
	Trigger_5:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_5)

end
