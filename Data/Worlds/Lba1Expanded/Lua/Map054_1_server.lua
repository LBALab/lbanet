function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(57.5)
	Spawn_1:SetPosY(0.01)
	Spawn_1:SetPosZ(61)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(61)
	Spawn_2:SetPosY(0.01)
	Spawn_2:SetPosZ(55)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map54.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map54.phy"
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
	Actor_3:SetRenderType(3)
	Actor_3.DisplayDesc.ModelId = 0
	Actor_3.DisplayDesc.ModelName = "Grobo"
	Actor_3.DisplayDesc.Outfit = "Baldino"
	Actor_3.DisplayDesc.Weapon = "No"
	Actor_3.DisplayDesc.Mode = "Normal"
	Actor_3.DisplayDesc.UseLight = true
	Actor_3.DisplayDesc.CastShadow = true
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
	Actor_3.PhysicDesc.Pos.X = 54.9
	Actor_3.PhysicDesc.Pos.Y = 0
	Actor_3.PhysicDesc.Pos.Z = 52
	Actor_3.PhysicDesc.Pos.Rotation = 45
	Actor_3.PhysicDesc.Density = 1
	Actor_3.PhysicDesc.Collidable = true
	Actor_3.PhysicDesc.SizeX = 1.5
	Actor_3.PhysicDesc.SizeY = 5
	Actor_3.PhysicDesc.SizeZ = 1.5
	Actor_3.PhysicDesc.Filename = ""
	Actor_3:SetPhysicalActorType(2)
	Actor_3:SetPhysicalShape(2)
	Actor_3.ExtraInfo.Name = ""
	Actor_3.ExtraInfo.NameColorR = 0
	Actor_3.ExtraInfo.NameColorG = 0
	Actor_3.ExtraInfo.NameColorB = 0
	Actor_3.ExtraInfo.Display = false
	Actor_3.LifeInfo.Display = false
	Actor_3H = NPCHandler(Actor_3)
	Actor_3H_dia = DialogPart()
	Actor_3H_dia:SetResetDialog(false)
	Actor_3H_dia_c0 = DialogPart()
	Actor_3H_dia_c0_cond = AndCondition()
	Actor_3H_dia_c0_cond:SetTextid(-1)
	Actor_3H_dia_c0_cond_c1 = NegateCondition()
	Actor_3H_dia_c0_cond_c1:SetTextid(-1)
	Actor_3H_dia_c0_cond_c1_c = QuestStartedCondition()
	Actor_3H_dia_c0_cond_c1_c:SetTextid(-1)
	Actor_3H_dia_c0_cond_c1_c:SetQuestId(1)
	Actor_3H_dia_c0_cond_c1:SetCondition(Actor_3H_dia_c0_cond_c1_c)
	Actor_3H_dia_c0_cond:SetCondition1(Actor_3H_dia_c0_cond_c1)
	Actor_3H_dia_c0_cond_c2 = NegateCondition()
	Actor_3H_dia_c0_cond_c2:SetTextid(-1)
	Actor_3H_dia_c0_cond_c2_c = QuestFinishedCondition()
	Actor_3H_dia_c0_cond_c2_c:SetTextid(-1)
	Actor_3H_dia_c0_cond_c2_c:SetQuestId(1)
	Actor_3H_dia_c0_cond_c2:SetCondition(Actor_3H_dia_c0_cond_c2_c)
	Actor_3H_dia_c0_cond:SetCondition2(Actor_3H_dia_c0_cond_c2)
	Actor_3H_dia_c0:Setcondition(Actor_3H_dia_c0_cond)
	Actor_3H_dia_c0:SetResetDialog(false)
	Actor_3H_dia_c0:AddText(658)
	Actor_3H_dia_c0_c0 = DialogPart()
	Actor_3H_dia_c0_c0_act = StartQuestAction()
	Actor_3H_dia_c0_c0_act:SetQuestId(1)
	Actor_3H_dia_c0_c0:SetAction(Actor_3H_dia_c0_c0_act)
	Actor_3H_dia_c0_c0:SetResetDialog(false)
	Actor_3H_dia_c0_c0:AddText(814)
	Actor_3H_dia_c0:AddChild(Actor_3H_dia_c0_c0)
	Actor_3H_dia_c0_c1 = DialogPart()
	Actor_3H_dia_c0_c1:SetResetDialog(false)
	Actor_3H_dia_c0_c1:AddText(847)
	Actor_3H_dia_c0:AddChild(Actor_3H_dia_c0_c1)
	Actor_3H_dia:AddChild(Actor_3H_dia_c0)
	Actor_3H_dia_c1 = DialogPart()
	Actor_3H_dia_c1_cond = QuestStartedCondition()
	Actor_3H_dia_c1_cond:SetTextid(-1)
	Actor_3H_dia_c1_cond:SetQuestId(1)
	Actor_3H_dia_c1:Setcondition(Actor_3H_dia_c1_cond)
	Actor_3H_dia_c1:SetResetDialog(false)
	Actor_3H_dia_c1:AddText(824)
	Actor_3H_dia_c1_c0 = DialogPart()
	Actor_3H_dia_c1_c0_act = FinishQuestAction()
	Actor_3H_dia_c1_c0_act:SetQuestId(1)
	Actor_3H_dia_c1_c0:SetAction(Actor_3H_dia_c1_c0_act)
	Actor_3H_dia_c1_c0:SetResetDialog(false)
	Actor_3H_dia_c1_c0:AddText(826)
	Actor_3H_dia_c1_c0_c0 = DialogPart()
	Actor_3H_dia_c1_c0_c0_cond = QuestFinishedCondition()
	Actor_3H_dia_c1_c0_c0_cond:SetTextid(-1)
	Actor_3H_dia_c1_c0_c0_cond:SetQuestId(1)
	Actor_3H_dia_c1_c0_c0:Setcondition(Actor_3H_dia_c1_c0_c0_cond)
	Actor_3H_dia_c1_c0_c0:SetResetDialog(false)
	Actor_3H_dia_c1_c0_c0:AddText(659)
	Actor_3H_dia_c1_c0_c0_c0 = DialogPart()
	Actor_3H_dia_c1_c0_c0_c0:SetResetDialog(false)
	Actor_3H_dia_c1_c0_c0_c0:AddText(847)
	Actor_3H_dia_c1_c0_c0:AddChild(Actor_3H_dia_c1_c0_c0_c0)
	Actor_3H_dia_c1_c0:AddChild(Actor_3H_dia_c1_c0_c0)
	Actor_3H_dia_c1_c0_c1 = DialogPart()
	Actor_3H_dia_c1_c0_c1:SetResetDialog(false)
	Actor_3H_dia_c1_c0_c1:AddText(864)
	Actor_3H_dia_c1_c0_c1_c0 = DialogPart()
	Actor_3H_dia_c1_c0_c1_c0:SetResetDialog(false)
	Actor_3H_dia_c1_c0_c1_c0:AddText(847)
	Actor_3H_dia_c1_c0_c1:AddChild(Actor_3H_dia_c1_c0_c1_c0)
	Actor_3H_dia_c1_c0:AddChild(Actor_3H_dia_c1_c0_c1)
	Actor_3H_dia_c1:AddChild(Actor_3H_dia_c1_c0)
	Actor_3H_dia:AddChild(Actor_3H_dia_c1)
	Actor_3H_dia_c2 = DialogPart()
	Actor_3H_dia_c2_cond = QuestFinishedCondition()
	Actor_3H_dia_c2_cond:SetTextid(-1)
	Actor_3H_dia_c2_cond:SetQuestId(1)
	Actor_3H_dia_c2:Setcondition(Actor_3H_dia_c2_cond)
	Actor_3H_dia_c2:SetResetDialog(false)
	Actor_3H_dia_c2:AddText(661)
	Actor_3H_dia_c2_c0 = DialogPart()
	Actor_3H_dia_c2_c0:SetResetDialog(false)
	Actor_3H_dia_c2_c0:AddText(817)
	Actor_3H_dia_c2:AddChild(Actor_3H_dia_c2_c0)
	Actor_3H_dia:AddChild(Actor_3H_dia_c2)
	Actor_3H_dia_c3 = DialogPart()
	Actor_3H_dia_c3:SetResetDialog(false)
	Actor_3H_dia_c3:AddText(0)
	Actor_3H_dia_c3_c0 = DialogPart()
	Actor_3H_dia_c3_c0:SetResetDialog(false)
	Actor_3H_dia_c3_c0:AddText(847)
	Actor_3H_dia_c3:AddChild(Actor_3H_dia_c3_c0)
	Actor_3H_dia:AddChild(Actor_3H_dia_c3)
	Actor_3H:SetRootDialog(Actor_3H_dia)
	Actor_3H:SetNpcName(-1)
	Actor_3H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_3H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 3.5, 1, true)
	Trigger_1:SetPosition(57.5, 0, 62.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map044_1")
	Trigger_1_act1:SetSpawning(4)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 3, 3, true)
	Trigger_2:SetPosition(63.5, 1, 56.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map044_1")
	Trigger_2_act1:SetSpawning(5)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 2.99804, 3.99609, 2.99804, "Normal", "")
	Trigger_3:SetPosition(61.499, 0, 61.499)
	Trigger_3_act1 = OpenContainerAction()
	Trigger_3_act1:SetTimeToReset(300)
		Trigger_3_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_3_act1:AddItem(Trigger_3_act1ContItem0)
		Trigger_3_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_3_act1:AddItem(Trigger_3_act1ContItem1)
		Trigger_3_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_3_act1:AddItem(Trigger_3_act1ContItem2)
		Trigger_3_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_3_act1:AddItem(Trigger_3_act1ContItem3)
	Trigger_3:SetAction1(Trigger_3_act1)
	Trigger_3:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_3)

end
