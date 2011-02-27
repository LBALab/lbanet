function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(17)
	Spawn_1:SetPosY(7)
	Spawn_1:SetPosZ(42)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(25)
	Spawn_2:SetPosY(10)
	Spawn_2:SetPosZ(12.5)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(13)
	Spawn_3:SetPosY(7)
	Spawn_3:SetPosZ(36)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	MapObject = ActorObjectInfo(1)
	MapObject:SetRenderType(1)
	MapObject.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map83.osgb"
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
	MapObject.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map83.phy"
	MapObjectH = ActorHandler(MapObject)
	environment:AddActorObject(MapObjectH)

	Trigger_1_info = TriggerInfo(1, "exit10", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 4, 4, true)
	Trigger_1:SetPosition(11.5, 7, 36)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map089_1")
	Trigger_1_act1:SetSpawning(1)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit13", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 4, 3, true)
	Trigger_2:SetPosition(26.5, 10, 12.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map087_1")
	Trigger_2_act1:SetSpawning(1)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit7", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 2, 2, true)
	Trigger_3:SetPosition(20, 3, 42)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map086_1")
	Trigger_3_act1:SetSpawning(1)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

end

