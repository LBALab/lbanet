function InitMap(environment)
	Spawn_1 = Spawn(1)
	Spawn_1:SetPosX(53)
	Spawn_1:SetPosY(0.01)
	Spawn_1:SetPosZ(62)
	Spawn_1:SetName("spawning1")
	environment:AddSpawn(Spawn_1)

	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map35.osgb"
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
	Actor_1.DisplayDesc.UseBillboard = false
	Actor_1.PhysicDesc.Pos.X = 0
	Actor_1.PhysicDesc.Pos.Y = 0
	Actor_1.PhysicDesc.Pos.Z = 0
	Actor_1.PhysicDesc.Pos.Rotation = 0
	Actor_1.PhysicDesc.Density = 1
	Actor_1.PhysicDesc.Collidable = true
	Actor_1.PhysicDesc.SizeX = 0
	Actor_1.PhysicDesc.SizeY = 0
	Actor_1.PhysicDesc.SizeZ = 0
	Actor_1.PhysicDesc.AllowFreeMove = true
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map35.phy"
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
	Actor_4.DisplayDesc.ModelName = "Object"
	Actor_4.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_4.DisplayDesc.UseBillboard = false
	Actor_4.DisplayDesc.ColorMaterialType = 4
	Actor_4.DisplayDesc.MatAmbientColorR = -0.2
	Actor_4.DisplayDesc.MatAmbientColorG = -0.2
	Actor_4.DisplayDesc.MatAmbientColorB = -0.2
	Actor_4.DisplayDesc.MatAmbientColorA = 1
	Actor_4.DisplayDesc.MatDiffuseColorR = 0.4
	Actor_4.DisplayDesc.MatDiffuseColorG = 0.4
	Actor_4.DisplayDesc.MatDiffuseColorB = 0.4
	Actor_4.DisplayDesc.MatDiffuseColorA = 1
	Actor_4.DisplayDesc.MatSpecularColorR = 0
	Actor_4.DisplayDesc.MatSpecularColorG = 0
	Actor_4.DisplayDesc.MatSpecularColorB = 0
	Actor_4.DisplayDesc.MatSpecularColorA = 1
	Actor_4.DisplayDesc.MatEmissionColorR = 0
	Actor_4.DisplayDesc.MatEmissionColorG = 0
	Actor_4.DisplayDesc.MatEmissionColorB = 0
	Actor_4.DisplayDesc.MatEmissionColorA = 1
	Actor_4.DisplayDesc.MatShininess = 0
	Actor_4.PhysicDesc.Pos.X = 0
	Actor_4.PhysicDesc.Pos.Y = -1
	Actor_4.PhysicDesc.Pos.Z = 0
	Actor_4.PhysicDesc.Pos.Rotation = 25
	Actor_4.PhysicDesc.Density = 1
	Actor_4.PhysicDesc.Collidable = true
	Actor_4.PhysicDesc.SizeX = 0.5
	Actor_4.PhysicDesc.SizeY = 2
	Actor_4.PhysicDesc.SizeZ = 0.6
	Actor_4.PhysicDesc.AllowFreeMove = true
	Actor_4.PhysicDesc.Filename = ""
	Actor_4:SetPhysicalActorType(2)
	Actor_4:SetPhysicalShape(2)
	Actor_4.ExtraInfo.Name = "NPC"
	Actor_4.ExtraInfo.NameColorR = 0
	Actor_4.ExtraInfo.NameColorG = 0
	Actor_4.ExtraInfo.NameColorB = 0
	Actor_4.ExtraInfo.Display = false
	Actor_4.LifeInfo.Display = false
	Actor_4H = NPCHandler(Actor_4)
	Actor_4H_dia = DialogPart()
	Actor_4H_dia:SetResetDialog(false)
	Actor_4H:SetRootDialog(Actor_4H_dia)
	Actor_4H:SetNpcName(-1)
	Actor_4H:SetSimpleDialog(false)
	environment:AddActorObject(Actor_4H)

	Actor_5 = ActorObjectInfo(5)
	Actor_5:SetRenderType(1)
	Actor_5.DisplayDesc.ModelId = 0
	Actor_5.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite047.osgb"
	Actor_5.DisplayDesc.Outfit = ""
	Actor_5.DisplayDesc.Weapon = ""
	Actor_5.DisplayDesc.Mode = ""
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
	Actor_5:SetModelState(2)
	Actor_5.DisplayDesc.UseBillboard = false
	Actor_5.PhysicDesc.Pos.X = 50
	Actor_5.PhysicDesc.Pos.Y = 0.0001
	Actor_5.PhysicDesc.Pos.Z = 36
	Actor_5.PhysicDesc.Pos.Rotation = 0
	Actor_5.PhysicDesc.Density = 1
	Actor_5.PhysicDesc.Collidable = true
	Actor_5.PhysicDesc.SizeX = 1.99
	Actor_5.PhysicDesc.SizeY = 4
	Actor_5.PhysicDesc.SizeZ = 1.99
	Actor_5.PhysicDesc.AllowFreeMove = false
	Actor_5.PhysicDesc.Filename = ""
	Actor_5:SetPhysicalActorType(4)
	Actor_5:SetPhysicalShape(3)
	Actor_5.ExtraInfo.Name = ""
	Actor_5.ExtraInfo.NameColorR = 1
	Actor_5.ExtraInfo.NameColorG = 1
	Actor_5.ExtraInfo.NameColorB = 1
	Actor_5.ExtraInfo.Display = false
	Actor_5.LifeInfo.Display = false
	Actor_5H = ActorHandler(Actor_5)
	environment:AddActorObject(Actor_5H)

	Actor_6 = ActorObjectInfo(6)
	Actor_6:SetRenderType(1)
	Actor_6.DisplayDesc.ModelId = 0
	Actor_6.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite047.osgb"
	Actor_6.DisplayDesc.Outfit = ""
	Actor_6.DisplayDesc.Weapon = ""
	Actor_6.DisplayDesc.Mode = ""
	Actor_6.DisplayDesc.UseLight = true
	Actor_6.DisplayDesc.CastShadow = true
	Actor_6.DisplayDesc.ColorR = 1
	Actor_6.DisplayDesc.ColorG = 1
	Actor_6.DisplayDesc.ColorB = 1
	Actor_6.DisplayDesc.ColorA = 1
	Actor_6.DisplayDesc.TransX = 0
	Actor_6.DisplayDesc.TransY = 0
	Actor_6.DisplayDesc.TransZ = 0
	Actor_6.DisplayDesc.ScaleX = 1
	Actor_6.DisplayDesc.ScaleY = 1
	Actor_6.DisplayDesc.ScaleZ = 1
	Actor_6.DisplayDesc.RotX = 0
	Actor_6.DisplayDesc.RotY = 0
	Actor_6.DisplayDesc.RotZ = 0
	Actor_6:SetModelState(2)
	Actor_6.DisplayDesc.UseBillboard = false
	Actor_6.PhysicDesc.Pos.X = 46
	Actor_6.PhysicDesc.Pos.Y = 0.0001
	Actor_6.PhysicDesc.Pos.Z = 40
	Actor_6.PhysicDesc.Pos.Rotation = 0
	Actor_6.PhysicDesc.Density = 1
	Actor_6.PhysicDesc.Collidable = true
	Actor_6.PhysicDesc.SizeX = 1.99
	Actor_6.PhysicDesc.SizeY = 4
	Actor_6.PhysicDesc.SizeZ = 1.99
	Actor_6.PhysicDesc.AllowFreeMove = false
	Actor_6.PhysicDesc.Filename = ""
	Actor_6:SetPhysicalActorType(4)
	Actor_6:SetPhysicalShape(3)
	Actor_6.ExtraInfo.Name = ""
	Actor_6.ExtraInfo.NameColorR = 1
	Actor_6.ExtraInfo.NameColorG = 1
	Actor_6.ExtraInfo.NameColorB = 1
	Actor_6.ExtraInfo.Display = false
	Actor_6.LifeInfo.Display = false
	Actor_6H = ActorHandler(Actor_6)
	environment:AddActorObject(Actor_6H)

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(1)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite047.osgb"
	Actor_7.DisplayDesc.Outfit = ""
	Actor_7.DisplayDesc.Weapon = ""
	Actor_7.DisplayDesc.Mode = ""
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
	Actor_7:SetModelState(2)
	Actor_7.DisplayDesc.UseBillboard = false
	Actor_7.PhysicDesc.Pos.X = 46
	Actor_7.PhysicDesc.Pos.Y = 0.0001
	Actor_7.PhysicDesc.Pos.Z = 46
	Actor_7.PhysicDesc.Pos.Rotation = 0
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 1.99
	Actor_7.PhysicDesc.SizeY = 4
	Actor_7.PhysicDesc.SizeZ = 1.99
	Actor_7.PhysicDesc.AllowFreeMove = false
	Actor_7.PhysicDesc.Filename = ""
	Actor_7:SetPhysicalActorType(4)
	Actor_7:SetPhysicalShape(3)
	Actor_7.ExtraInfo.Name = ""
	Actor_7.ExtraInfo.NameColorR = 1
	Actor_7.ExtraInfo.NameColorG = 1
	Actor_7.ExtraInfo.NameColorB = 1
	Actor_7.ExtraInfo.Display = false
	Actor_7.LifeInfo.Display = false
	Actor_7H = ActorHandler(Actor_7)
	environment:AddActorObject(Actor_7H)

	Actor_8 = ActorObjectInfo(8)
	Actor_8:SetRenderType(1)
	Actor_8.DisplayDesc.ModelId = 0
	Actor_8.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/sprite047.osgb"
	Actor_8.DisplayDesc.Outfit = ""
	Actor_8.DisplayDesc.Weapon = ""
	Actor_8.DisplayDesc.Mode = ""
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
	Actor_8:SetModelState(2)
	Actor_8.DisplayDesc.UseBillboard = false
	Actor_8.PhysicDesc.Pos.X = 54
	Actor_8.PhysicDesc.Pos.Y = 0.0001
	Actor_8.PhysicDesc.Pos.Z = 50
	Actor_8.PhysicDesc.Pos.Rotation = 0
	Actor_8.PhysicDesc.Density = 1
	Actor_8.PhysicDesc.Collidable = true
	Actor_8.PhysicDesc.SizeX = 1.99
	Actor_8.PhysicDesc.SizeY = 4
	Actor_8.PhysicDesc.SizeZ = 1.99
	Actor_8.PhysicDesc.AllowFreeMove = false
	Actor_8.PhysicDesc.Filename = ""
	Actor_8:SetPhysicalActorType(4)
	Actor_8:SetPhysicalShape(3)
	Actor_8.ExtraInfo.Name = ""
	Actor_8.ExtraInfo.NameColorR = 1
	Actor_8.ExtraInfo.NameColorG = 1
	Actor_8.ExtraInfo.NameColorB = 1
	Actor_8.ExtraInfo.Display = false
	Actor_8.LifeInfo.Display = false
	Actor_8H = ActorHandler(Actor_8)
	environment:AddActorObject(Actor_8H)

	Trigger_1_info = TriggerInfo(1, "exit0", true, false, false)
	Trigger_1 = ZoneTrigger(Trigger_1_info, 3, 4, 1, true)
	Trigger_1:SetPosition(53.5, 0, 63.5)
	Trigger_1:SetStayUpdateFrequency(-1)
	Trigger_1:SetActivateOnJump(true)
	Trigger_1_act1 = TeleportAction()
	Trigger_1_act1:SetMapName("Map006_1")
	Trigger_1_act1:SetSpawning(3)
	Trigger_1:SetAction1(Trigger_1_act1)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "exit1", true, false, false)
	Trigger_2 = ZoneTrigger(Trigger_2_info, 1, 1, 1, true)
	Trigger_2:SetPosition(3.5, 0, 33.5)
	Trigger_2:SetStayUpdateFrequency(-1)
	Trigger_2:SetActivateOnJump(true)
	Trigger_2_act1 = TeleportAction()
	Trigger_2_act1:SetMapName("Map000_1")
	Trigger_2_act1:SetSpawning(9)
	Trigger_2:SetAction1(Trigger_2_act1)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 0.998046, 3.99609, 1.99805, "Normal", "")
	Trigger_3:SetPosition(48.499, 0, 54.999)
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
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 1.99805, 3.99609, 1.99805, "Normal", "")
	Trigger_4:SetPosition(49.999, 0, 54.999)
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

	Trigger_5_info = TriggerInfo(5, "crateplacetrigger1", false, false, true)
	Trigger_5 = ZoneTrigger(Trigger_5_info, 1, 1, 1, true)
	Trigger_5:SetPosition(46.1, 0, 36)
	Trigger_5:SetStayUpdateFrequency(1)
	Trigger_5:SetActivateOnJump(true)
	Trigger_5_act3 = ConditionalAction()
	Trigger_5_act3_act1 = FinishQuestAction()
	Trigger_5_act3_act1:SetQuestId(4)
	Trigger_5_act3:SetActionTrue(Trigger_5_act3_act1)
	Trigger_5_act3_cond = QuestStartedCondition()
	Trigger_5_act3_cond:SetTextid(-1)
	Trigger_5_act3_cond:SetQuestId(4)
	Trigger_5_act3:SetCondition(Trigger_5_act3_cond)
	Trigger_5:SetAction3(Trigger_5_act3)
	environment:AddTrigger(Trigger_5)

end
