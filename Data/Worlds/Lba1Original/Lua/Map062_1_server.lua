function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map62.osgb"
	MapObject.DisplayDesc.UseLight = true
	MapObject.DisplayDesc.CastShadow = false
	MapObject:SetModelState(1)
	MapObject.PhysicDesc.Pos.X = 0
	MapObject.PhysicDesc.Pos.Y = 0
	MapObject.PhysicDesc.Pos.Z = 0
	MapObject.PhysicDesc.Pos.Rotation = 0
	MapObject:SetPhysicalActorType(1)
	MapObject:SetPhysicalShape(5)
	MapObject.PhysicDesc.Collidable = true
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map62.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 11, 4.5, 1, true)
	Trigger_1:SetPosition(47.5, 8, 0.5)
	Trigger_1:SetAction1(176)
	Trigger_1:SetAction2(-1)
	Trigger_1:SetAction3(-1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 6, 4, 1, true)
	Trigger_2:SetPosition(50, 0, 63.5)
	Trigger_2:SetAction1(177)
	Trigger_2:SetAction2(-1)
	Trigger_2:SetAction3(-1)
	environment:AddTrigger(Trigger_2)

end