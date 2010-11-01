function InitMap(environment)
	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 750
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map24.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 0
	Actor_1.DisplayDesc.ColorG = 0
	Actor_1.DisplayDesc.ColorB = 2.10195e-044
	Actor_1.DisplayDesc.ColorA = 5.03608e-024
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
	Actor_1.PhysicDesc.Density = 0
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 0
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 0
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map24.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = 0
	Actor_1.ExtraInfo.NameColorG = 7.64534e-031
	Actor_1.ExtraInfo.NameColorB = 0
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "to_square", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 8, 2, true)
	Trigger_1:SetPosition(62.5, 1, 23)
	Trigger_1:SetAction1(95)
	Trigger_1:SetAction2(-1)
	Trigger_1:SetAction3(-1)
	environment:AddTrigger(Trigger_1)

	Trigger_3_info = TriggerInfo(3, "to_inmain", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 4, 8, 1, true)
	Trigger_3:SetPosition(47, 1, 63.5)
	Trigger_3:SetAction1(96)
	Trigger_3:SetAction2(-1)
	Trigger_3:SetAction3(-1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "to_cross", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 1, 8, 2, true)
	Trigger_4:SetPosition(32, 1, 25)
	Trigger_4:SetAction1(98)
	Trigger_4:SetAction2(-1)
	Trigger_4:SetAction3(-1)
	environment:AddTrigger(Trigger_4)

end
