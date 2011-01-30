function InitMap(environment)
	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map99.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map99.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit1", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 3.5, 4, true)
	Trigger_1:SetPosition(63.5, 8, 35)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map095_1")
	Trigger_1_act1:SetSpawning(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit16", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 5, 3.5, 1, true)
	Trigger_2:SetPosition(61.5, 0, 63.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map095_1")
	Trigger_2_act1:SetSpawning(4)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit17", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 3.5, 4, true)
	Trigger_3:SetPosition(63.5, 0, 61)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map095_1")
	Trigger_3_act1:SetSpawning(5)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

end
