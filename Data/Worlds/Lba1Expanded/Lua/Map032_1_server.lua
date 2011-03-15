function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(57.5)
	Spawn_1:SetPosY(0.01)
	Spawn_1:SetPosZ(62)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(46.5)
	Spawn_2:SetPosY(0.01)
	Spawn_2:SetPosZ(62)
	Spawn_2:SetName("spawning2")
	environment:AddSpawn(Spawn_2)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map32.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map32.phy"
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

	Actor_4 = ActorObjectInfo(4)
	Actor_4:SetRenderType(3)
	Actor_4.DisplayDesc.ModelId = 0
	Actor_4.DisplayDesc.ModelName = "Horse"
	Actor_4.DisplayDesc.Outfit = "Empty"
	Actor_4.DisplayDesc.Weapon = "No"
	Actor_4.DisplayDesc.Mode = "Normal"
	Actor_4.DisplayDesc.UseLight = true
	Actor_4.DisplayDesc.CastShadow = true
	Actor_4.DisplayDesc.ColorR = 1
	Actor_4.DisplayDesc.ColorG = 1
	Actor_4.DisplayDesc.ColorB = 1
	Actor_4.DisplayDesc.ColorA = 1
	Actor_4.DisplayDesc.TransX = 0
	Actor_4.DisplayDesc.TransY = 0
	Actor_4.DisplayDesc.TransZ = 0
	Actor_4.DisplayDesc.ScaleX = 1
	Actor_4.DisplayDesc.ScaleY = 1
	Actor_4.DisplayDesc.ScaleZ = 1
	Actor_4.DisplayDesc.RotX = 0
	Actor_4.DisplayDesc.RotY = 0
	Actor_4.DisplayDesc.RotZ = 0
	Actor_4:SetModelState(1)
	Actor_4.PhysicDesc.Pos.X = 51.375
	Actor_4.PhysicDesc.Pos.Y = 0
	Actor_4.PhysicDesc.Pos.Z = 55.1875
	Actor_4.PhysicDesc.Pos.Rotation = 148
	Actor_4.PhysicDesc.Density = 1
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 2
	Actor_4.PhysicDesc.SizeY = 7
	Actor_4.PhysicDesc.SizeZ = 2
	Actor_4.PhysicDesc.Filename = ""
	Actor_4:SetPhysicalActorType(2)
	Actor_4:SetPhysicalShape(2)
	Actor_4.ExtraInfo.Name = ""
	Actor_4.ExtraInfo.NameColorR = 0
	Actor_4.ExtraInfo.NameColorG = 0
	Actor_4.ExtraInfo.NameColorB = 0
	Actor_4.ExtraInfo.Display = false
	Actor_4.LifeInfo.Display = false
	Actor_4H = NPCHandler(Actor_4)
	Actor_4H_dia = DialogPart()
	Actor_4H_dia:SetResetDialog(false)
	Actor_4H_dia_c0 = DialogPart()
	Actor_4H_dia_c0_cond = AndCondition()
	Actor_4H_dia_c0_cond:SetTextid(-1)
	Actor_4H_dia_c0_cond_c1 = NegateCondition()
	Actor_4H_dia_c0_cond_c1:SetTextid(-1)
	Actor_4H_dia_c0_cond_c1_c = QuestStartedCondition()
	Actor_4H_dia_c0_cond_c1_c:SetTextid(-1)
	Actor_4H_dia_c0_cond_c1_c:SetQuestId(2)
	Actor_4H_dia_c0_cond_c1:SetCondition(Actor_4H_dia_c0_cond_c1_c)
	Actor_4H_dia_c0_cond:SetCondition1(Actor_4H_dia_c0_cond_c1)
	Actor_4H_dia_c0_cond_c2 = NegateCondition()
	Actor_4H_dia_c0_cond_c2:SetTextid(-1)
	Actor_4H_dia_c0_cond_c2_c = QuestFinishedCondition()
	Actor_4H_dia_c0_cond_c2_c:SetTextid(-1)
	Actor_4H_dia_c0_cond_c2_c:SetQuestId(2)
	Actor_4H_dia_c0_cond_c2:SetCondition(Actor_4H_dia_c0_cond_c2_c)
	Actor_4H_dia_c0_cond:SetCondition2(Actor_4H_dia_c0_cond_c2)
	Actor_4H_dia_c0:Setcondition(Actor_4H_dia_c0_cond)
	Actor_4H_dia_c0:SetResetDialog(false)
	Actor_4H_dia_c0:AddText(822)
	Actor_4H_dia_c0_c0 = DialogPart()
	Actor_4H_dia_c0_c0_act = StartQuestAction()
	Actor_4H_dia_c0_c0_act:SetQuestId(2)
	Actor_4H_dia_c0_c0:SetAction(Actor_4H_dia_c0_c0_act)
	Actor_4H_dia_c0_c0:SetResetDialog(false)
	Actor_4H_dia_c0_c0:AddText(823)
	Actor_4H_dia_c0_c0_c0 = DialogPart()
	Actor_4H_dia_c0_c0_c0:SetResetDialog(false)
	Actor_4H_dia_c0_c0_c0:AddText(825)
	Actor_4H_dia_c0_c0:AddChild(Actor_4H_dia_c0_c0_c0)
	Actor_4H_dia_c0:AddChild(Actor_4H_dia_c0_c0)
	Actor_4H_dia_c0_c1 = DialogPart()
	Actor_4H_dia_c0_c1:SetResetDialog(false)
	Actor_4H_dia_c0_c1:AddText(847)
	Actor_4H_dia_c0:AddChild(Actor_4H_dia_c0_c1)
	Actor_4H_dia:AddChild(Actor_4H_dia_c0)
	Actor_4H_dia_c1 = DialogPart()
	Actor_4H_dia_c1_cond = QuestStartedCondition()
	Actor_4H_dia_c1_cond:SetTextid(-1)
	Actor_4H_dia_c1_cond:SetQuestId(2)
	Actor_4H_dia_c1:Setcondition(Actor_4H_dia_c1_cond)
	Actor_4H_dia_c1:SetResetDialog(false)
	Actor_4H_dia_c1:AddText(824)
	Actor_4H_dia_c1_c0 = DialogPart()
	Actor_4H_dia_c1_c0_act = FinishQuestAction()
	Actor_4H_dia_c1_c0_act:SetQuestId(2)
	Actor_4H_dia_c1_c0:SetAction(Actor_4H_dia_c1_c0_act)
	Actor_4H_dia_c1_c0:SetResetDialog(false)
	Actor_4H_dia_c1_c0:AddText(826)
	Actor_4H_dia_c1_c0_c0 = DialogPart()
	Actor_4H_dia_c1_c0_c0_cond = QuestFinishedCondition()
	Actor_4H_dia_c1_c0_c0_cond:SetTextid(-1)
	Actor_4H_dia_c1_c0_c0_cond:SetQuestId(2)
	Actor_4H_dia_c1_c0_c0:Setcondition(Actor_4H_dia_c1_c0_c0_cond)
	Actor_4H_dia_c1_c0_c0:SetResetDialog(false)
	Actor_4H_dia_c1_c0_c0:AddText(827)
	Actor_4H_dia_c1_c0:AddChild(Actor_4H_dia_c1_c0_c0)
	Actor_4H_dia_c1_c0_c1 = DialogPart()
	Actor_4H_dia_c1_c0_c1:SetResetDialog(false)
	Actor_4H_dia_c1_c0_c1:AddText(828)
	Actor_4H_dia_c1_c0:AddChild(Actor_4H_dia_c1_c0_c1)
	Actor_4H_dia_c1:AddChild(Actor_4H_dia_c1_c0)
	Actor_4H_dia:AddChild(Actor_4H_dia_c1)
	Actor_4H:SetRootDialog(Actor_4H_dia)
	Actor_4H:SetNpcName(-1)
	Actor_4H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_4H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(3)
	Actor_5.DisplayDesc.ModelId = 0
	Actor_5.DisplayDesc.ModelName = "Object"
	Actor_5.DisplayDesc.Outfit = "MekaPingouin"
	Actor_5.DisplayDesc.Weapon = "No"
	Actor_5.DisplayDesc.Mode = "Normal"
	Actor_5.DisplayDesc.UseLight = true
	Actor_5.DisplayDesc.CastShadow = true
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
	Actor_5.PhysicDesc.Pos.X = 0
	Actor_5.PhysicDesc.Pos.Y = -1
	Actor_5.PhysicDesc.Pos.Z = 0
	Actor_5.PhysicDesc.Pos.Rotation = 25
	Actor_5.PhysicDesc.Density = 1
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = 0.5
	Actor_5.PhysicDesc.SizeY = 2
	Actor_5.PhysicDesc.SizeZ = 0.6
	Actor_5.PhysicDesc.Filename = ""
	Actor_5:SetPhysicalActorType(2)
	Actor_5:SetPhysicalShape(2)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = 0
	Actor_5.ExtraInfo.NameColorG = 0
	Actor_5.ExtraInfo.NameColorB = 0
	Actor_5.ExtraInfo.Display = false
	Actor_5.LifeInfo.Display = false
	Actor_5H = NPCHandler(Actor_5)
	Actor_5H_dia = DialogPart()
	Actor_5H_dia:SetResetDialog(false)
	Actor_5H:SetRootDialog(Actor_5H_dia)
	Actor_5H:SetNpcName(-1)
	Actor_5H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_5H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 3.5, 1, true)
	Trigger_1:SetPosition(57.5, 0, 63.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map013_1")
	Trigger_1_act1:SetSpawning(14)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit3", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 3, 3.5, 1, true)
	Trigger_2:SetPosition(46.5, 0, 63.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map013_1")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_3:SetPosition(58.999, 0, 55.999)
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

	Trigger_4_info = TriggerInfo(4, "ContainerTri_4", true, false, false)
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 0.998046, 3.99609, 1.99805, "Normal", "")
	Trigger_4:SetPosition(43.499, 0, 53.999)
	Trigger_4_act1 = OpenContainerAction()
	Trigger_4_act1:SetTimeToReset(300)
		Trigger_4_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_4_act1:AddItem(Trigger_4_act1ContItem0)
		Trigger_4_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_4_act1:AddItem(Trigger_4_act1ContItem1)
		Trigger_4_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_4_act1:AddItem(Trigger_4_act1ContItem2)
		Trigger_4_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_4_act1:AddItem(Trigger_4_act1ContItem3)
	Trigger_4:SetAction1(Trigger_4_act1)
	Trigger_4:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_4)

end
