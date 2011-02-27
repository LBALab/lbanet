function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(28)
	Spawn_1:SetPosY(12)
	Spawn_1:SetPosZ(23.5)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(34)
	Spawn_2:SetPosY(5)
	Spawn_2:SetPosZ(58.5)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map67.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map67.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 3.5, 6, true)
	Trigger_1:SetPosition(26.5, 12, 23)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map068_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 3.5, 9, true)
	Trigger_2:SetPosition(32.5, 5, 58.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map068_1")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit11", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 1, 3.5, 2, true)
	Trigger_3:SetPosition(62.5, 5, 59)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map066_1")
	Trigger_3_act1:SetSpawning(2)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

end

