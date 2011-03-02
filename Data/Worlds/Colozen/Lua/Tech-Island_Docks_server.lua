function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(15)
	Spawn_1:SetPosY(0.01)
	Spawn_1:SetPosZ(39)
	Spawn_1:SetName("fromtunnel")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(4)
	Spawn_2:SetPosY(11.01)
	Spawn_2:SetPosZ(52)
	Spawn_2:SetName("fromvillage1")
	environment:AddSpawn(Spawn_2)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Colozen/Grids/Island/TheDocks1.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Colozen/Grids/Island/TheDocks1.phy"
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

	Trigger_1_info = TriggerInfo(1, "totunnel", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 4, 1, true)
	Trigger_1:SetPosition(15, 0, 37.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Tinkers_Tunnel")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "tovillage", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 4, 1, true)
	Trigger_2:SetPosition(4, 10, 50.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Colobee_Village")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ExitUpTri_3", true, false, false)
	Trigger_3 = ActivationTrigger(Trigger_3_info, 1.66667, "Normal", "")
	Trigger_3:SetPosition(4, 11, 51)
	Trigger_3_act1 = ClientScriptAction()
	Trigger_3_act1_cs = TakeExitUpScript()
	Trigger_3_act1_cs:SetExitPositionX(4)
	Trigger_3_act1_cs:SetExitPositionY(11)
	Trigger_3_act1_cs:SetExitPositionZ(51)
	Trigger_3_act1_cs:SetExitDirection(180)
	Trigger_3_act1:SetScript(Trigger_3_act1_cs)
	Trigger_3:SetAction1(Trigger_3_act1)
	Trigger_3:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "TextTri_4", true, false, false)
	Trigger_4 = ActivationTrigger(Trigger_4_info, 0.333333, "Normal", "")
	Trigger_4:SetPosition(52, 2, 49)
	Trigger_4_act1 = DisplayTextAction()
	Trigger_4_act1:SetTextId(0)
	Trigger_4:SetAction1(Trigger_4_act1)
	Trigger_4:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_4)

end
