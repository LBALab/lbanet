function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(62)
	Spawn_1:SetPosY(11.01)
	Spawn_1:SetPosZ(60)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(52)
	Spawn_2:SetPosY(11.01)
	Spawn_2:SetPosZ(57)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(52)
	Spawn_3:SetPosY(9.01)
	Spawn_3:SetPosZ(35)
	Spawn_3:SetName("spawning3")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(59)
	Spawn_4:SetPosY(7.01)
	Spawn_4:SetPosZ(35)
	Spawn_4:SetName("spawning4")
	environment:AddSpawn(Spawn_4)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map49.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map49.phy"
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

	Actor_3 = ActorObjectInfo(3)
	Actor_3:SetRenderType(1)
	Actor_3.DisplayDesc.ModelId = 0
	Actor_3.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite029.osgb"
	Actor_3.DisplayDesc.Outfit = ""
	Actor_3.DisplayDesc.Weapon = ""
	Actor_3.DisplayDesc.Mode = ""
	Actor_3.DisplayDesc.UseLight = true
	Actor_3.DisplayDesc.CastShadow = false
	Actor_3.DisplayDesc.ColorR = 1
	Actor_3.DisplayDesc.ColorG = 1
	Actor_3.DisplayDesc.ColorB = 1
	Actor_3.DisplayDesc.ColorA = 1
	Actor_3.DisplayDesc.TransX = 0
	Actor_3.DisplayDesc.TransY = 0
	Actor_3.DisplayDesc.TransZ = 0
	Actor_3.DisplayDesc.ScaleX = 1
	Actor_3.DisplayDesc.ScaleY = 1
	Actor_3.DisplayDesc.ScaleZ = 1
	Actor_3.DisplayDesc.RotX = 0
	Actor_3.DisplayDesc.RotY = 0
	Actor_3.DisplayDesc.RotZ = 0
	Actor_3:SetModelState(1)
	Actor_3.PhysicDesc.Pos.X = 53
	Actor_3.PhysicDesc.Pos.Y = 10
	Actor_3.PhysicDesc.Pos.Z = 57
	Actor_3.PhysicDesc.Pos.Rotation = 0
	Actor_3.PhysicDesc.Density = 1
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = 2
	Actor_3.PhysicDesc.SizeY = 1
	Actor_3.PhysicDesc.SizeZ = 2
	Actor_3.PhysicDesc.Filename = ""
	Actor_3:SetPhysicalActorType(2)
	Actor_3:SetPhysicalShape(2)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 0
	Actor_3.ExtraInfo.NameColorG = 0
	Actor_3.ExtraInfo.NameColorB = 0
	Actor_3.ExtraInfo.Display = false
	Actor_3.LifeInfo.Display = false
	Actor_3H = ActorHandler(Actor_3)
	Actor_3_Sc0 = ASPWaitForSignal(5)
	Actor_3H:AddScriptPart(Actor_3_Sc0)
	Actor_3_Sc1 = ASPGoTo(53,3,57,0.005)
	Actor_3H:AddScriptPart(Actor_3_Sc1)
	Actor_3_Sc2 = ASPGoTo(53,10,57,0.005)
	Actor_3H:AddScriptPart(Actor_3_Sc2)
	environment:AddActorObject(Actor_3H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(1)
	Actor_5.DisplayDesc.ModelId = 0
	Actor_5.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite073.osgb"
	Actor_5.DisplayDesc.Outfit = ""
	Actor_5.DisplayDesc.Weapon = ""
	Actor_5.DisplayDesc.Mode = ""
	Actor_5.DisplayDesc.UseLight = true
	Actor_5.DisplayDesc.CastShadow = false
	Actor_5.DisplayDesc.ColorR = 1
	Actor_5.DisplayDesc.ColorG = 1
	Actor_5.DisplayDesc.ColorB = 1
	Actor_5.DisplayDesc.ColorA = 1
	Actor_5.DisplayDesc.TransX = 0
	Actor_5.DisplayDesc.TransY = 0
	Actor_5.DisplayDesc.TransZ = 0
	Actor_5.DisplayDesc.ScaleX = 1
	Actor_5.DisplayDesc.ScaleY = 1
	Actor_5.DisplayDesc.ScaleZ = 1
	Actor_5.DisplayDesc.RotX = 0
	Actor_5.DisplayDesc.RotY = 0
	Actor_5.DisplayDesc.RotZ = 0
	Actor_5:SetModelState(1)
	Actor_5.PhysicDesc.Pos.X = 53
	Actor_5.PhysicDesc.Pos.Y = 7
	Actor_5.PhysicDesc.Pos.Z = 35
	Actor_5.PhysicDesc.Pos.Rotation = 0
	Actor_5.PhysicDesc.Density = 1
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = 2
	Actor_5.PhysicDesc.SizeY = 1
	Actor_5.PhysicDesc.SizeZ = 2
	Actor_5.PhysicDesc.Filename = ""
	Actor_5:SetPhysicalActorType(2)
	Actor_5:SetPhysicalShape(2)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = 0
	Actor_5.ExtraInfo.NameColorG = 0
	Actor_5.ExtraInfo.NameColorB = 0
	Actor_5.ExtraInfo.Display = false
	Actor_5.LifeInfo.Display = false
	Actor_5H = ActorHandler(Actor_5)
	Actor_5_Sc0 = ASPWaitForSignal(5)
	Actor_5H:AddScriptPart(Actor_5_Sc0)
	Actor_5_Sc1 = ASPGoTo(53,1,35,0.005)
	Actor_5H:AddScriptPart(Actor_5_Sc1)
	Actor_5_Sc2 = ASPGoTo(53,7,35,0.005)
	Actor_5H:AddScriptPart(Actor_5_Sc2)
	environment:AddActorObject(Actor_5H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(3)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "Nurse"
	Actor_7.DisplayDesc.Outfit = "Guard"
	Actor_7.DisplayDesc.Weapon = "No"
	Actor_7.DisplayDesc.Mode = "Normal"
	Actor_7.DisplayDesc.UseLight = true
	Actor_7.DisplayDesc.CastShadow = true
	Actor_7.DisplayDesc.ColorR = 1
	Actor_7.DisplayDesc.ColorG = 1
	Actor_7.DisplayDesc.ColorB = 1
	Actor_7.DisplayDesc.ColorA = 1
	Actor_7.DisplayDesc.TransX = 0
	Actor_7.DisplayDesc.TransY = 0
	Actor_7.DisplayDesc.TransZ = 0
	Actor_7.DisplayDesc.ScaleX = 1
	Actor_7.DisplayDesc.ScaleY = 1
	Actor_7.DisplayDesc.ScaleZ = 1
	Actor_7.DisplayDesc.RotX = 0
	Actor_7.DisplayDesc.RotY = 0
	Actor_7.DisplayDesc.RotZ = 0
	Actor_7:SetModelState(1)
	Actor_7.PhysicDesc.Pos.X = 55
	Actor_7.PhysicDesc.Pos.Y = 11
	Actor_7.PhysicDesc.Pos.Z = 51
	Actor_7.PhysicDesc.Pos.Rotation = 25
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 1
	Actor_7.PhysicDesc.SizeY = 5
	Actor_7.PhysicDesc.SizeZ = 1
	Actor_7.PhysicDesc.Filename = ""
	Actor_7:SetPhysicalActorType(2)
	Actor_7:SetPhysicalShape(2)
	Actor_7.ExtraInfo.Name = ""
	Actor_7.ExtraInfo.NameColorR = 0
	Actor_7.ExtraInfo.NameColorG = 0
	Actor_7.ExtraInfo.NameColorB = 0
	Actor_7.ExtraInfo.Display = false
	Actor_7.LifeInfo.Display = false
	Actor_7H = NPCHandler(Actor_7)
	Actor_7H_dia = DialogPart()
	Actor_7H_dia:SetResetDialog(false)
	Actor_7H:SetRootDialog(Actor_7H_dia)
	Actor_7H:SetNpcName(-1)
	Actor_7H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_7H)

	Actor_8 = ActorObjectInfo(8)
	Actor_8:SetRenderType(3)
	Actor_8.DisplayDesc.ModelId = 0
	Actor_8.DisplayDesc.ModelName = "Grobo"
	Actor_8.DisplayDesc.Outfit = "Baldino"
	Actor_8.DisplayDesc.Weapon = "No"
	Actor_8.DisplayDesc.Mode = "Normal"
	Actor_8.DisplayDesc.UseLight = true
	Actor_8.DisplayDesc.CastShadow = true
	Actor_8.DisplayDesc.ColorR = 1
	Actor_8.DisplayDesc.ColorG = 1
	Actor_8.DisplayDesc.ColorB = 1
	Actor_8.DisplayDesc.ColorA = 1
	Actor_8.DisplayDesc.TransX = 0
	Actor_8.DisplayDesc.TransY = 0
	Actor_8.DisplayDesc.TransZ = 0
	Actor_8.DisplayDesc.ScaleX = 1
	Actor_8.DisplayDesc.ScaleY = 1
	Actor_8.DisplayDesc.ScaleZ = 1
	Actor_8.DisplayDesc.RotX = 0
	Actor_8.DisplayDesc.RotY = 0
	Actor_8.DisplayDesc.RotZ = 0
	Actor_8:SetModelState(1)
	Actor_8.PhysicDesc.Pos.X = 48.875
	Actor_8.PhysicDesc.Pos.Y = 11
	Actor_8.PhysicDesc.Pos.Z = 46.0938
	Actor_8.PhysicDesc.Pos.Rotation = 433
	Actor_8.PhysicDesc.Density = 1
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 1.5
	Actor_8.PhysicDesc.SizeY = 5
	Actor_8.PhysicDesc.SizeZ = 1.5
	Actor_8.PhysicDesc.Filename = ""
	Actor_8:SetPhysicalActorType(2)
	Actor_8:SetPhysicalShape(2)
	Actor_8.ExtraInfo.Name = ""
	Actor_8.ExtraInfo.NameColorR = 0
	Actor_8.ExtraInfo.NameColorG = 0
	Actor_8.ExtraInfo.NameColorB = 0
	Actor_8.ExtraInfo.Display = false
	Actor_8.LifeInfo.Display = false
	Actor_8H = NPCHandler(Actor_8)
	Actor_8H_dia = DialogPart()
	Actor_8H_dia:SetResetDialog(false)
	Actor_8H:SetRootDialog(Actor_8H_dia)
	Actor_8H:SetNpcName(-1)
	Actor_8H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_8H)

	Actor_9 = ActorObjectInfo(9)
	Actor_9:SetRenderType(3)
	Actor_9.DisplayDesc.ModelId = 0
	Actor_9.DisplayDesc.ModelName = "Object"
	Actor_9.DisplayDesc.Outfit = "MekaPingouin"
	Actor_9.DisplayDesc.Weapon = "No"
	Actor_9.DisplayDesc.Mode = "Normal"
	Actor_9.DisplayDesc.UseLight = true
	Actor_9.DisplayDesc.CastShadow = true
	Actor_9.DisplayDesc.ColorR = 1
	Actor_9.DisplayDesc.ColorG = 1
	Actor_9.DisplayDesc.ColorB = 1
	Actor_9.DisplayDesc.ColorA = 1
	Actor_9.DisplayDesc.TransX = 0
	Actor_9.DisplayDesc.TransY = 0
	Actor_9.DisplayDesc.TransZ = 0
	Actor_9.DisplayDesc.ScaleX = 1
	Actor_9.DisplayDesc.ScaleY = 1
	Actor_9.DisplayDesc.ScaleZ = 1
	Actor_9.DisplayDesc.RotX = 0
	Actor_9.DisplayDesc.RotY = 0
	Actor_9.DisplayDesc.RotZ = 0
	Actor_9:SetModelState(1)
	Actor_9.PhysicDesc.Pos.X = 0
	Actor_9.PhysicDesc.Pos.Y = -1
	Actor_9.PhysicDesc.Pos.Z = 0
	Actor_9.PhysicDesc.Pos.Rotation = 25
	Actor_9.PhysicDesc.Density = 1
	Actor_9.PhysicDesc.Collidable = true
	Actor_9.PhysicDesc.SizeX = 0.5
	Actor_9.PhysicDesc.SizeY = 2
	Actor_9.PhysicDesc.SizeZ = 0.6
	Actor_9.PhysicDesc.Filename = ""
	Actor_9:SetPhysicalActorType(2)
	Actor_9:SetPhysicalShape(2)
	Actor_9.ExtraInfo.Name = ""
	Actor_9.ExtraInfo.NameColorR = 0
	Actor_9.ExtraInfo.NameColorG = 0
	Actor_9.ExtraInfo.NameColorB = 0
	Actor_9.ExtraInfo.Display = false
	Actor_9.LifeInfo.Display = false
	Actor_9H = NPCHandler(Actor_9)
	Actor_9H_dia = DialogPart()
	Actor_9H_dia:SetResetDialog(false)
	Actor_9H:SetRootDialog(Actor_9H_dia)
	Actor_9H:SetNpcName(-1)
	Actor_9H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_9H)

	Trigger_1_info = TriggerInfo(1, "exit1", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 1, 3.5, 3, true)
	Trigger_1:SetPosition(63.5, 11, 60.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map042_1")
	Trigger_1_act1:SetSpawning(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit2", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 2, 2, 2, true)
	Trigger_2:SetPosition(53, 4, 57)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map051_1")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit3", true, false, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 2, 1.5, 2, true)
	Trigger_3:SetPosition(53, 2, 35)
	Trigger_3:SetStayUpdateFrequency(-1)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map051_1")
	Trigger_3_act1:SetSpawning(4)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit4", true, false, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 2, 2, 2, true)
	Trigger_4:SetPosition(60, 7, 30)
	Trigger_4:SetStayUpdateFrequency(-1)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map051_1")
	Trigger_4_act1:SetSpawning(5)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "ExitDownTri_5", true, false, false)
	Trigger_5 = ActivationTrigger(Trigger_5_info, 2, "Normal", "")
	Trigger_5:SetPosition(60, 7, 34)
	Trigger_5_act1 = ClientScriptAction()
	Trigger_5_act1_cs = TakeExitDownScript()
	Trigger_5_act1_cs:SetExitPositionX(60)
	Trigger_5_act1_cs:SetExitPositionY(7)
	Trigger_5_act1_cs:SetExitPositionZ(34)
	Trigger_5_act1_cs:SetExitDirection(180)
	Trigger_5_act1:SetScript(Trigger_5_act1_cs)
	Trigger_5:SetAction1(Trigger_5_act1)
	Trigger_5:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "FloorSwitchTri_6", true, false, false)
	Trigger_6 = ZoneActionTrigger(Trigger_6_info, 2, 2, 2, "Normal", "")
	Trigger_6:SetPosition(53, 10, 57)
	Trigger_6_act1 = SendSignalAction()
	Trigger_6_act1:SetActorId(3)
	Trigger_6_act1:SetSignal(5)
	Trigger_6:SetAction1(Trigger_6_act1)
	Trigger_6:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "FloorSwitchTri_7", true, false, false)
	Trigger_7 = ZoneActionTrigger(Trigger_7_info, 2, 2, 2, "Normal", "")
	Trigger_7:SetPosition(53, 7, 35)
	Trigger_7_act1 = SendSignalAction()
	Trigger_7_act1:SetActorId(5)
	Trigger_7_act1:SetSignal(5)
	Trigger_7:SetAction1(Trigger_7_act1)
	Trigger_7:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_7)

end
