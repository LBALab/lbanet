function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(2.5)
	Spawn_1:SetPosY(5)
	Spawn_1:SetPosZ(2)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Spawn_2 = Spawn(2)
	Spawn_2:SetPosX(21.5)
	Spawn_2:SetPosY(0)
	Spawn_2:SetPosZ(61.5)
	Spawn_2:SetName("spawning10")
	environment:AddSpawn(Spawn_2)

	Spawn_3 = Spawn(3)
	Spawn_3:SetPosX(45.5)
	Spawn_3:SetPosY(0)
	Spawn_3:SetPosZ(62)
	Spawn_3:SetName("spawning11")
	environment:AddSpawn(Spawn_3)

	Spawn_4 = Spawn(4)
	Spawn_4:SetPosX(19.5)
	Spawn_4:SetPosY(0)
	Spawn_4:SetPosZ(2)
	Spawn_4:SetName("spawning2")
	environment:AddSpawn(Spawn_4)

	Spawn_5 = Spawn(5)
	Spawn_5:SetPosX(50)
	Spawn_5:SetPosY(0)
	Spawn_5:SetPosZ(2)
	Spawn_5:SetName("spawning3")
	environment:AddSpawn(Spawn_5)

	Spawn_6 = Spawn(6)
	Spawn_6:SetPosX(21.5)
	Spawn_6:SetPosY(0)
	Spawn_6:SetPosZ(61.5)
	Spawn_6:SetName("spawning4")
	environment:AddSpawn(Spawn_6)

	Spawn_7 = Spawn(7)
	Spawn_7:SetPosX(45.5)
	Spawn_7:SetPosY(0)
	Spawn_7:SetPosZ(62)
	Spawn_7:SetName("spawning5")
	environment:AddSpawn(Spawn_7)

	Spawn_8 = Spawn(8)
	Spawn_8:SetPosX(4)
	Spawn_8:SetPosY(0)
	Spawn_8:SetPosZ(39)
	Spawn_8:SetName("spawning6")
	environment:AddSpawn(Spawn_8)

	Spawn_9 = Spawn(9)
	Spawn_9:SetPosX(40.5)
	Spawn_9:SetPosY(0)
	Spawn_9:SetPosZ(14)
	Spawn_9:SetName("spawning7")
	environment:AddSpawn(Spawn_9)

	Spawn_10 = Spawn(10)
	Spawn_10:SetPosX(1.5)
	Spawn_10:SetPosY(-1)
	Spawn_10:SetPosZ(0.5)
	Spawn_10:SetName("spawning8")
	environment:AddSpawn(Spawn_10)

	Spawn_11 = Spawn(11)
	Spawn_11:SetPosX(36)
	Spawn_11:SetPosY(0)
	Spawn_11:SetPosZ(39)
	Spawn_11:SetName("spawning9")
	environment:AddSpawn(Spawn_11)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = -842150451
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map2.osgb"
	Actor_1.DisplayDesc.Outfit = ""
	Actor_1.DisplayDesc.Weapon = ""
	Actor_1.DisplayDesc.Mode = ""
	Actor_1.DisplayDesc.UseLight = true
	Actor_1.DisplayDesc.CastShadow = false
	Actor_1.DisplayDesc.ColorR = -4.31602e+008
	Actor_1.DisplayDesc.ColorG = -4.31602e+008
	Actor_1.DisplayDesc.ColorB = -4.31602e+008
	Actor_1.DisplayDesc.ColorA = -4.31602e+008
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
	Actor_1.PhysicDesc.Density = -4.31602e+008
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = -4.31602e+008
	Actor_1.PhysicDesc.SizeY = -4.31602e+008
	Actor_1.PhysicDesc.SizeZ = -4.31602e+008
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map2.phy"
	Actor_1:SetPhysicalActorType(1)
	Actor_1:SetPhysicalShape(5)
	Actor_1.ExtraInfo.Name = ""
	Actor_1.ExtraInfo.NameColorR = -4.31602e+008
	Actor_1.ExtraInfo.NameColorG = -4.31602e+008
	Actor_1.ExtraInfo.NameColorB = -4.31602e+008
	Actor_1.ExtraInfo.Display = false
	Actor_1.LifeInfo.Display = false
	Actor_1H = ActorHandler(Actor_1)
	environment:AddActorObject(Actor_1H)

	Actor_2 = ActorObjectInfo(2)
	Actor_2:SetRenderType(3)
	Actor_2.DisplayDesc.ModelId = 0
	Actor_2.DisplayDesc.ModelName = "FunFrock"
	Actor_2.DisplayDesc.Outfit = "No"
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
	Actor_2:SetModelState(2)
	Actor_2.PhysicDesc.Pos.X = 57.5
	Actor_2.PhysicDesc.Pos.Y = 0
	Actor_2.PhysicDesc.Pos.Z = 20
	Actor_2.PhysicDesc.Pos.Rotation = 0
	Actor_2.PhysicDesc.Density = 1
	Actor_2.PhysicDesc.Collidable = true
	Actor_2.PhysicDesc.SizeX = 1
	Actor_2.PhysicDesc.SizeY = 5
	Actor_2.PhysicDesc.SizeZ = 1
	Actor_2.PhysicDesc.Filename = ""
	Actor_2:SetPhysicalActorType(2)
	Actor_2:SetPhysicalShape(2)
	Actor_2.ExtraInfo.Name = "#0"
	Actor_2.ExtraInfo.NameColorR = 1
	Actor_2.ExtraInfo.NameColorG = 1
	Actor_2.ExtraInfo.NameColorB = 1
	Actor_2.ExtraInfo.Display = false
	Actor_2.LifeInfo.Display = false
	Actor_2H = NPCHandler(Actor_2)
	Actor_2H_dia = DialogPart()
	Actor_2H_dia:SetResetDialog(false)
	Actor_2H_dia_c0 = DialogPart()
	Actor_2H_dia_c0:SetResetDialog(false)
	Actor_2H_dia_c0:AddText(8)
	Actor_2H_dia_c0_c0 = DialogPart()
	Actor_2H_dia_c0_c0_act = OpenShopAction()
	Actor_2H_dia_c0_c0_act:SetCurrencyItem(8)
	Actor_2H_dia_c0_c0_act:AddItem(1, 1)
	Actor_2H_dia_c0_c0_act:AddItem(2, 1)
	Actor_2H_dia_c0_c0_act:AddItem(19, 50)
	Actor_2H_dia_c0_c0:SetAction(Actor_2H_dia_c0_c0_act)
	Actor_2H_dia_c0_c0:SetResetDialog(false)
	Actor_2H_dia_c0_c0:AddText(9)
	Actor_2H_dia_c0_c0_c0 = DialogPart()
	Actor_2H_dia_c0_c0_c0_cond = NegateCondition()
	Actor_2H_dia_c0_c0_c0_cond:SetTextid(-1)
	Actor_2H_dia_c0_c0_c0_cond_c = AlwaysTrueCondition()
	Actor_2H_dia_c0_c0_c0_cond_c:SetTextid(-1)
	Actor_2H_dia_c0_c0_c0_cond:SetCondition(Actor_2H_dia_c0_c0_c0_cond_c)
	Actor_2H_dia_c0_c0_c0:Setcondition(Actor_2H_dia_c0_c0_c0_cond)
	Actor_2H_dia_c0_c0_c0:SetResetDialog(false)
	Actor_2H_dia_c0_c0_c0:AddText(10)
	Actor_2H_dia_c0_c0_c0_c0 = DialogPart()
	Actor_2H_dia_c0_c0_c0_c0:SetResetDialog(false)
	Actor_2H_dia_c0_c0_c0_c0:AddText(4)
	Actor_2H_dia_c0_c0_c0:AddChild(Actor_2H_dia_c0_c0_c0_c0)
	Actor_2H_dia_c0_c0_c0_c1 = DialogPart()
	Actor_2H_dia_c0_c0_c0_c1:SetResetDialog(false)
	Actor_2H_dia_c0_c0_c0_c1:AddText(28)
	Actor_2H_dia_c0_c0_c0:AddChild(Actor_2H_dia_c0_c0_c0_c1)
	Actor_2H_dia_c0_c0:AddChild(Actor_2H_dia_c0_c0_c0)
	Actor_2H_dia_c0_c0_c1 = DialogPart()
	Actor_2H_dia_c0_c0_c1:SetResetDialog(true)
	Actor_2H_dia_c0_c0_c1:AddText(24)
	Actor_2H_dia_c0_c0_c1_c0 = DialogPart()
	Actor_2H_dia_c0_c0_c1_c0_act = HurtAction()
	Actor_2H_dia_c0_c0_c1_c0_act:SetHurtValue(10)
	Actor_2H_dia_c0_c0_c1_c0_act:SetPlayedAnimation(1)
	Actor_2H_dia_c0_c0_c1_c0_act:HurtLifeOrMana(true)
	Actor_2H_dia_c0_c0_c1_c0:SetAction(Actor_2H_dia_c0_c0_c1_c0_act)
	Actor_2H_dia_c0_c0_c1_c0:SetResetDialog(true)
	Actor_2H_dia_c0_c0_c1_c0:AddText(33)
	Actor_2H_dia_c0_c0_c1:AddChild(Actor_2H_dia_c0_c0_c1_c0)
	Actor_2H_dia_c0_c0:AddChild(Actor_2H_dia_c0_c0_c1)
	Actor_2H_dia_c0:AddChild(Actor_2H_dia_c0_c0)
	Actor_2H_dia:AddChild(Actor_2H_dia_c0)
	Actor_2H:SetRootDialog(Actor_2H_dia)
	Actor_2H:SetNpcName(0)
	Actor_2H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_2H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, true, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 11, 6, 1, true)
	Trigger_1:SetPosition(19.5, 0, 0.5)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map003_1")
	Trigger_1_act1:SetSpawning(2)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, true, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 8, 5.5, 1, true)
	Trigger_2:SetPosition(50, 0, 0.5)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map003_1")
	Trigger_2_act1:SetSpawning(3)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "exit2", true, true, false)
	Trigger_3 = ZoneTrigger(Trigger_3_info, 3, 4, 1, true)
	Trigger_3:SetPosition(2.5, 5, 0.5)
	Trigger_3_act1 = TeleportAction()
	Trigger_3_act1:SetMapName("Map003_1")
	Trigger_3_act1:SetSpawning(4)
	Trigger_3:SetAction1(Trigger_3_act1)
	environment:AddTrigger(Trigger_3)

	Trigger_4_info = TriggerInfo(4, "exit3", true, true, false)
	Trigger_4 = ZoneTrigger(Trigger_4_info, 8, 10.5, 1, true)
	Trigger_4:SetPosition(21, 0, 63.5)
	Trigger_4_act1 = TeleportAction()
	Trigger_4_act1:SetMapName("Map004_1")
	Trigger_4_act1:SetSpawning(1)
	Trigger_4:SetAction1(Trigger_4_act1)
	environment:AddTrigger(Trigger_4)

	Trigger_5_info = TriggerInfo(5, "exit4", true, true, false)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 9, 6, 1, true)
	Trigger_5:SetPosition(45.5, 0, 63.5)
	Trigger_5_act1 = TeleportAction()
	Trigger_5_act1:SetMapName("Map004_1")
	Trigger_5_act1:SetSpawning(2)
	Trigger_5:SetAction1(Trigger_5_act1)
	environment:AddTrigger(Trigger_5)

	Trigger_6_info = TriggerInfo(6, "exit5", true, true, false)
	Trigger_6 = ZoneTrigger(Trigger_6_info, 1, 4.5, 8, true)
	Trigger_6:SetPosition(2.5, 0, 39)
	Trigger_6_act1 = TeleportAction()
	Trigger_6_act1:SetMapName("Map006_1")
	Trigger_6_act1:SetSpawning(1)
	Trigger_6:SetAction1(Trigger_6_act1)
	environment:AddTrigger(Trigger_6)

	Trigger_7_info = TriggerInfo(7, "exit6", true, true, false)
	Trigger_7 = ZoneTrigger(Trigger_7_info, 3, 5, 1, true)
	Trigger_7:SetPosition(40.5, 0, 12.5)
	Trigger_7_act1 = TeleportAction()
	Trigger_7_act1:SetMapName("Map014_1")
	Trigger_7_act1:SetSpawning(1)
	Trigger_7:SetAction1(Trigger_7_act1)
	environment:AddTrigger(Trigger_7)

	Trigger_8_info = TriggerInfo(8, "testtext", true, true, false)
	Trigger_8 = ActivationTrigger(Trigger_8_info, 3, "Normal", "None")
	Trigger_8:SetPosition(23.5, 0, 60)
	Trigger_8_act1 = DisplayTextAction()
	Trigger_8_act1:SetTextId(199)
	Trigger_8:SetAction1(Trigger_8_act1)
	Trigger_8:SetPlayAnimation(false)
	environment:AddTrigger(Trigger_8)

	Trigger_9_info = TriggerInfo(9, "ttt", true, true, false)
	Trigger_9 = ZoneTrigger(Trigger_9_info, 1, 1, 1, true)
	Trigger_9:SetPosition(47, 0, 19.5)
	Trigger_9_act1 = AddRemoveItemAction()
	Trigger_9_act1:SetItemId(30)
	Trigger_9_act1:SetNumber(1)
	Trigger_9_act1:SetInformClientType(2)
	Trigger_9:SetAction1(Trigger_9_act1)
	environment:AddTrigger(Trigger_9)

end

