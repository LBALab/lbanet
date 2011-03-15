function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(56.5)
	Spawn_1:SetPosY(0.01)
	Spawn_1:SetPosZ(62)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map26.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map26.phy"
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

	Actor_2 = ActorObjectInfo(2)
	Actor_2:SetRenderType(3)
	Actor_2.DisplayDesc.ModelId = 0
	Actor_2.DisplayDesc.ModelName = "Rabbibunny"
	Actor_2.DisplayDesc.Outfit = "Orange"
	Actor_2.DisplayDesc.Weapon = "No"
	Actor_2.DisplayDesc.Mode = "Normal"
	Actor_2.DisplayDesc.UseLight = true
	Actor_2.DisplayDesc.CastShadow = true
	Actor_2.DisplayDesc.ColorR = 1
	Actor_2.DisplayDesc.ColorG = 1
	Actor_2.DisplayDesc.ColorB = 1
	Actor_2.DisplayDesc.ColorA = 1
	Actor_2.DisplayDesc.TransX = 0
	Actor_2.DisplayDesc.TransY = 0
	Actor_2.DisplayDesc.TransZ = 0
	Actor_2.DisplayDesc.ScaleX = 1
	Actor_2.DisplayDesc.ScaleY = 1
	Actor_2.DisplayDesc.ScaleZ = 1
	Actor_2.DisplayDesc.RotX = 0
	Actor_2.DisplayDesc.RotY = 0
	Actor_2.DisplayDesc.RotZ = 0
	Actor_2:SetModelState(1)
	Actor_2.PhysicDesc.Pos.X = 53.4375
	Actor_2.PhysicDesc.Pos.Y = 0
	Actor_2.PhysicDesc.Pos.Z = 56
	Actor_2.PhysicDesc.Pos.Rotation = 281
	Actor_2.PhysicDesc.Density = 1
	Actor_2.PhysicDesc.Collidable = true
	Actor_2.PhysicDesc.SizeX = 1
	Actor_2.PhysicDesc.SizeY = 5
	Actor_2.PhysicDesc.SizeZ = 1
	Actor_2.PhysicDesc.Filename = ""
	Actor_2:SetPhysicalActorType(2)
	Actor_2:SetPhysicalShape(2)
	Actor_2.ExtraInfo.Name = ""
	Actor_2.ExtraInfo.NameColorR = 0
	Actor_2.ExtraInfo.NameColorG = 0
	Actor_2.ExtraInfo.NameColorB = 0
	Actor_2.ExtraInfo.Display = false
	Actor_2.LifeInfo.Display = false
	Actor_2H = NPCHandler(Actor_2)
	Actor_2H_dia = DialogPart()
	Actor_2H_dia:SetResetDialog(false)
	Actor_2H_dia_c0 = DialogPart()
	Actor_2H_dia_c0_cond = QuestStartedCondition()
	Actor_2H_dia_c0_cond:SetTextid(-1)
	Actor_2H_dia_c0_cond:SetQuestId(2)
	Actor_2H_dia_c0:Setcondition(Actor_2H_dia_c0_cond)
	Actor_2H_dia_c0:SetResetDialog(false)
	Actor_2H_dia_c0:AddText(835)
	Actor_2H_dia_c0_c0 = DialogPart()
	Actor_2H_dia_c0_c0_act = OpenShopAction()
	Actor_2H_dia_c0_c0_act:SetCurrencyItem(8)
	Actor_2H_dia_c0_c0_act:AddItem(1, 5)
	Actor_2H_dia_c0_c0_act:AddItem(2, 5)
	Actor_2H_dia_c0_c0_act:AddItem(11, 5)
	Actor_2H_dia_c0_c0_act:AddItem(19, 40)
	Actor_2H_dia_c0_c0:SetAction(Actor_2H_dia_c0_c0_act)
	Actor_2H_dia_c0_c0:SetResetDialog(false)
	Actor_2H_dia_c0_c0:AddText(834)
	Actor_2H_dia_c0:AddChild(Actor_2H_dia_c0_c0)
	Actor_2H_dia:AddChild(Actor_2H_dia_c0)
	Actor_2H_dia_c1 = DialogPart()
	Actor_2H_dia_c1:SetResetDialog(false)
	Actor_2H_dia_c1:AddText(836)
	Actor_2H_dia_c1_c0 = DialogPart()
	Actor_2H_dia_c1_c0_act = OpenShopAction()
	Actor_2H_dia_c1_c0_act:SetCurrencyItem(8)
	Actor_2H_dia_c1_c0_act:AddItem(1, 5)
	Actor_2H_dia_c1_c0_act:AddItem(2, 5)
	Actor_2H_dia_c1_c0_act:AddItem(11, 5)
	Actor_2H_dia_c1_c0:SetAction(Actor_2H_dia_c1_c0_act)
	Actor_2H_dia_c1_c0:SetResetDialog(false)
	Actor_2H_dia_c1_c0:AddText(834)
	Actor_2H_dia_c1:AddChild(Actor_2H_dia_c1_c0)
	Actor_2H_dia:AddChild(Actor_2H_dia_c1)
	Actor_2H:SetRootDialog(Actor_2H_dia)
	Actor_2H:SetNpcName(-1)
	Actor_2H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_2H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 4, 1, true)
	Trigger_1:SetPosition(56.5, 0, 63.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map013_1")
	Trigger_1_act1:SetSpawning(9)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

end
