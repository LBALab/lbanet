function InitMap(environment)
	Actor_1 = ActorObjectInfo(1)
	Actor_1:SetRenderType(1)
	Actor_1.DisplayDesc.ModelId = 0
	Actor_1.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map61.osgb"
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
	Actor_1.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map61.phy"
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

	Actor_7 = ActorObjectInfo(7)
	Actor_7:SetRenderType(3)
	Actor_7.DisplayDesc.ModelId = 0
	Actor_7.DisplayDesc.ModelName = "Object"
	Actor_7.DisplayDesc.Outfit = "MekaPingouin"
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
	Actor_7.PhysicDesc.Pos.X = 0
	Actor_7.PhysicDesc.Pos.Y = -1
	Actor_7.PhysicDesc.Pos.Z = 0
	Actor_7.PhysicDesc.Pos.Rotation = 25
	Actor_7.PhysicDesc.Density = 1
	Actor_7.PhysicDesc.Collidable = true
	Actor_7.PhysicDesc.SizeX = 0.5
	Actor_7.PhysicDesc.SizeY = 2
	Actor_7.PhysicDesc.SizeZ = 0.6
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

	Trigger_1_info = TriggerInfo(1, "ContainerTri_1", true, false, false)
	Trigger_1 = ZoneActionTrigger(Trigger_1_info, 2.99804, 5.99609, 3.99804, "Normal", "")
	Trigger_1:SetPosition(59.499, 2, 48.999)
	Trigger_1_act1 = OpenContainerAction()
	Trigger_1_act1:SetTimeToReset(300)
		Trigger_1_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_1_act1:AddItem(Trigger_1_act1ContItem0)
		Trigger_1_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_1_act1:AddItem(Trigger_1_act1ContItem1)
		Trigger_1_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_1_act1:AddItem(Trigger_1_act1ContItem2)
		Trigger_1_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_1_act1:AddItem(Trigger_1_act1ContItem3)
	Trigger_1:SetAction1(Trigger_1_act1)
	Trigger_1:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_1)

	Trigger_2_info = TriggerInfo(2, "ContainerTri_2", true, false, false)
	Trigger_2 = ZoneActionTrigger(Trigger_2_info, 1.99805, 2.99609, 0.998046, "Normal", "")
	Trigger_2:SetPosition(53.999, 2, 54.499)
	Trigger_2_act1 = OpenContainerAction()
	Trigger_2_act1:SetTimeToReset(300)
		Trigger_2_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_2_act1:AddItem(Trigger_2_act1ContItem0)
		Trigger_2_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_2_act1:AddItem(Trigger_2_act1ContItem1)
		Trigger_2_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_2_act1:AddItem(Trigger_2_act1ContItem2)
		Trigger_2_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_2_act1:AddItem(Trigger_2_act1ContItem3)
	Trigger_2:SetAction1(Trigger_2_act1)
	Trigger_2:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_2)

	Trigger_3_info = TriggerInfo(3, "ContainerTri_3", true, false, false)
	Trigger_3 = ZoneActionTrigger(Trigger_3_info, 1.99805, 2.99609, 0.998046, "Normal", "")
	Trigger_3:SetPosition(53.999, 2, 56.499)
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
	Trigger_4 = ZoneActionTrigger(Trigger_4_info, 1.99805, 2.99609, 0.998046, "Normal", "")
	Trigger_4:SetPosition(53.999, 2, 60.499)
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

	Trigger_5_info = TriggerInfo(5, "ContainerTri_5", true, false, false)
	Trigger_5 = ZoneActionTrigger(Trigger_5_info, 1.99805, 2.99609, 0.998046, "Normal", "")
	Trigger_5:SetPosition(53.999, 2, 50.499)
	Trigger_5_act1 = OpenContainerAction()
	Trigger_5_act1:SetTimeToReset(300)
		Trigger_5_act1ContItem0 = ContainerItemGroupElement(1,1,1,0.3,1)
		Trigger_5_act1:AddItem(Trigger_5_act1ContItem0)
		Trigger_5_act1ContItem1 = ContainerItemGroupElement(2,1,1,0.3,1)
		Trigger_5_act1:AddItem(Trigger_5_act1ContItem1)
		Trigger_5_act1ContItem2 = ContainerItemGroupElement(8,2,2,0.35,1)
		Trigger_5_act1:AddItem(Trigger_5_act1ContItem2)
		Trigger_5_act1ContItem3 = ContainerItemGroupElement(3,1,1,0.05,1)
		Trigger_5_act1:AddItem(Trigger_5_act1ContItem3)
	Trigger_5:SetAction1(Trigger_5_act1)
	Trigger_5:SetPlayAnimation(true)
	environment:AddTrigger(Trigger_5)

end
