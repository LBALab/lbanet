function InitMap(environment)
	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba2Original/Grids/Map107.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = 0
	Actor_1.DisplayDesc.ColorG = 7.30015e-031
	Actor_1.DisplayDesc.ColorB = 7.375
	Actor_1.DisplayDesc.ColorA = 14.25
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
	Actor_1.PhysicDesc.Density = 1.31224e-038
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 0
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 0
	Actor_1.PhysicDesc.Filename = "Worlds/Lba2Original/Grids/Map107.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = 9.82776e-031
	Actor_1.ExtraInfo.NameColorG = 0
	Actor_1.ExtraInfo.NameColorB = 0
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Trigger_1_info = TriggerInfo(1, "to_8", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 2, 8, 1, true)
	Trigger_1:SetPosition(11, 0, 16.5)
	Trigger_1:SetAction1(217)
	Trigger_1:SetAction2(-1)
	Trigger_1:SetAction3(-1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "to_11", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 7, 2, true)
	Trigger_2:SetPosition(3.5, 0, 9)
	Trigger_2:SetAction1(218)
	Trigger_2:SetAction2(-1)
	Trigger_2:SetAction3(-1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "to_16", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 7, 1, true)
	Trigger_3:SetPosition(11, 0, 1.5)
	Trigger_3:SetAction1(219)
	Trigger_3:SetAction2(-1)
	Trigger_3:SetAction3(-1)
	environment:AddTrigger(Trigger_3)

end
