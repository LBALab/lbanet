function Init(environment)
	Teleport_1 = TeleportDef(1)
	Teleport_1:SetName("Brundle Island")
	Teleport_1:SetMapName("Map097_1")
	Teleport_1:SetSpawn(1)
	environment:AddTeleport(Teleport_1)

	Teleport_2 = TeleportDef(2)
	Teleport_2:SetName("Citadel Island")
	Teleport_2:SetMapName("Map006_1")
	Teleport_2:SetSpawn(1)
	environment:AddTeleport(Teleport_2)

	Teleport_3 = TeleportDef(3)
	Teleport_3:SetName("Fortress Island")
	Teleport_3:SetMapName("Map100_1")
	Teleport_3:SetSpawn(1)
	environment:AddTeleport(Teleport_3)

	Teleport_4 = TeleportDef(4)
	Teleport_4:SetName("Hamalayi Mountains")
	Teleport_4:SetMapName("Map009_1")
	Teleport_4:SetSpawn(1)
	environment:AddTeleport(Teleport_4)

	Teleport_5 = TeleportDef(5)
	Teleport_5:SetName("Polar Island")
	Teleport_5:SetMapName("Map115_1")
	Teleport_5:SetSpawn(1)
	environment:AddTeleport(Teleport_5)

	Teleport_6 = TeleportDef(6)
	Teleport_6:SetName("Principal Island")
	Teleport_6:SetMapName("Map011_1")
	Teleport_6:SetSpawn(1)
	environment:AddTeleport(Teleport_6)

	Teleport_7 = TeleportDef(7)
	Teleport_7:SetName("Proxima Island")
	Teleport_7:SetMapName("Map042_1")
	Teleport_7:SetSpawn(1)
	environment:AddTeleport(Teleport_7)

	Teleport_8 = TeleportDef(8)
	Teleport_8:SetName("Rebellion Island")
	Teleport_8:SetMapName("Map059_1")
	Teleport_8:SetSpawn(1)
	environment:AddTeleport(Teleport_8)

	Teleport_9 = TeleportDef(9)
	Teleport_9:SetName("Temple of Bu")
	Teleport_9:SetMapName("Map008_1")
	Teleport_9:SetSpawn(1)
	environment:AddTeleport(Teleport_9)

	Teleport_10 = TeleportDef(10)
	Teleport_10:SetName("Tippett Island")
	Teleport_10:SetMapName("Map074_1")
	Teleport_10:SetSpawn(1)
	environment:AddTeleport(Teleport_10)

	Teleport_11 = TeleportDef(11)
	Teleport_11:SetName("White Leaf Desert")
	Teleport_11:SetMapName("Map039_1")
	Teleport_11:SetSpawn(1)
	environment:AddTeleport(Teleport_11)

	Teleport_12 = TeleportDef(12)
	Teleport_12:SetName("Party place")
	Teleport_12:SetMapName("Map116_1")
	Teleport_12:SetSpawn(1)
	environment:AddTeleport(Teleport_12)

	Quest_1 = Quest(1)
	Quest_1:SetChapter(1)
	Quest_1:SetTitleTextId(0)
	Quest_1:SetDescriptionTextId(1)
	Quest_1:SetLocationTextId(2)
	Quest_1:SetVisible(true)
	Quest_1_cond0 = ItemInInventoryCondition()
	Quest_1_cond0:SetTextid(-1)
	Quest_1_cond0:SetItemId(3)
	Quest_1_cond0:SetItemNumber(1)
	Quest_1:AddCondition(Quest_1_cond0)
	environment:AddQuest(Quest_1)

	Quest_2 = Quest(2)
	Quest_2:SetChapter(1)
	Quest_2:SetTitleTextId(3)
	Quest_2:SetDescriptionTextId(4)
	Quest_2:SetLocationTextId(5)
	Quest_2:SetVisible(true)
	Quest_2_cond0 = QuestFinishedCondition()
	Quest_2_cond0:SetTextid(0)
	Quest_2_cond0:SetQuestId(1)
	Quest_2:AddCondition(Quest_2_cond0)
	environment:AddQuest(Quest_2)

	Quest_3 = Quest(3)
	Quest_3:SetChapter(1)
	Quest_3:SetTitleTextId(7)
	Quest_3:SetDescriptionTextId(8)
	Quest_3:SetLocationTextId(6)
	Quest_3:SetVisible(true)
	environment:AddQuest(Quest_3)

	Item_1 = InventoryItemDef(1)
	Item_1:SetName("Life potion")
	Item_1:SetIconName("GUI/imagesets/Inventory/health.png")
	Item_1:SetNameTextId(0)
	Item_1:SetDescriptionId(39)
	Item_1:SetLongDescriptionId(-1)
	Item_1:SetMax(10)
	Item_1:SetBuyPrice(2)
	Item_1:SetSellPrice(1)
	Item_1:SetDescriptionTextExtra("")
	Item_1:SetType(1)
	Item_1:SetEffect(30)
	Item_1:SetFlag(1)
	Item_1:SetEphemere(false)
	Item_1:SetStringFlag("")
	Item_1:SetColor1(-1)
	Item_1:SetColor2(-1)
	Item_1:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_1)

	Item_2 = InventoryItemDef(2)
	Item_2:SetName("Magic potion")
	Item_2:SetIconName("GUI/imagesets/Inventory/magic.png")
	Item_2:SetNameTextId(1)
	Item_2:SetDescriptionId(31)
	Item_2:SetLongDescriptionId(-1)
	Item_2:SetMax(10)
	Item_2:SetBuyPrice(1)
	Item_2:SetSellPrice(1)
	Item_2:SetDescriptionTextExtra("")
	Item_2:SetType(1)
	Item_2:SetEffect(30)
	Item_2:SetFlag(5)
	Item_2:SetEphemere(false)
	Item_2:SetStringFlag("")
	Item_2:SetColor1(-1)
	Item_2:SetColor2(-1)
	Item_2:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_2)

	Item_3 = InventoryItemDef(3)
	Item_3:SetName("Clover")
	Item_3:SetIconName("GUI/imagesets/Inventory/clover.png")
	Item_3:SetNameTextId(2)
	Item_3:SetDescriptionId(32)
	Item_3:SetLongDescriptionId(-1)
	Item_3:SetMax(3)
	Item_3:SetBuyPrice(1)
	Item_3:SetSellPrice(1)
	Item_3:SetDescriptionTextExtra("")
	Item_3:SetType(1)
	Item_3:SetEffect(100)
	Item_3:SetFlag(3)
	Item_3:SetEphemere(false)
	Item_3:SetStringFlag("")
	Item_3:SetColor1(-1)
	Item_3:SetColor2(-1)
	Item_3:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_3)

	Item_4 = InventoryItemDef(4)
	Item_4:SetName("Small key")
	Item_4:SetIconName("GUI/imagesets/Inventory/key.png")
	Item_4:SetNameTextId(3)
	Item_4:SetDescriptionId(33)
	Item_4:SetLongDescriptionId(-1)
	Item_4:SetMax(10)
	Item_4:SetBuyPrice(1)
	Item_4:SetSellPrice(1)
	Item_4:SetDescriptionTextExtra("")
	Item_4:SetType(2)
	Item_4:SetEffect(1)
	Item_4:SetFlag(0)
	Item_4:SetEphemere(true)
	Item_4:SetStringFlag("")
	Item_4:SetColor1(-1)
	Item_4:SetColor2(-1)
	Item_4:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_4)

	Item_5 = InventoryItemDef(5)
	Item_5:SetName("Horse")
	Item_5:SetIconName("GUI/imagesets/Inventory/Horse.png")
	Item_5:SetNameTextId(4)
	Item_5:SetDescriptionId(34)
	Item_5:SetLongDescriptionId(-1)
	Item_5:SetMax(1)
	Item_5:SetBuyPrice(1)
	Item_5:SetSellPrice(1)
	Item_5:SetDescriptionTextExtra("")
	Item_5:SetType(3)
	Item_5:SetEffect(1)
	Item_5:SetFlag(2)
	Item_5:SetEphemere(false)
	Item_5:SetStringFlag("")
	Item_5:SetColor1(-1)
	Item_5:SetColor2(-1)
	Item_5:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_5)

	Item_6 = InventoryItemDef(6)
	Item_6:SetName("Dinofly")
	Item_6:SetIconName("GUI/imagesets/Inventory/Dino.png")
	Item_6:SetNameTextId(5)
	Item_6:SetDescriptionId(35)
	Item_6:SetLongDescriptionId(-1)
	Item_6:SetMax(1)
	Item_6:SetBuyPrice(1)
	Item_6:SetSellPrice(1)
	Item_6:SetDescriptionTextExtra("")
	Item_6:SetType(3)
	Item_6:SetEffect(1)
	Item_6:SetFlag(3)
	Item_6:SetEphemere(false)
	Item_6:SetStringFlag("")
	Item_6:SetColor1(-1)
	Item_6:SetColor2(-1)
	Item_6:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_6)

	Item_7 = InventoryItemDef(7)
	Item_7:SetName("Protopack")
	Item_7:SetIconName("GUI/imagesets/Inventory/protopack.png")
	Item_7:SetNameTextId(6)
	Item_7:SetDescriptionId(36)
	Item_7:SetLongDescriptionId(-1)
	Item_7:SetMax(1)
	Item_7:SetBuyPrice(1)
	Item_7:SetSellPrice(1)
	Item_7:SetDescriptionTextExtra("")
	Item_7:SetType(3)
	Item_7:SetEffect(1)
	Item_7:SetFlag(1)
	Item_7:SetEphemere(false)
	Item_7:SetStringFlag("")
	Item_7:SetColor1(-1)
	Item_7:SetColor2(-1)
	Item_7:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_7)

	Item_8 = InventoryItemDef(8)
	Item_8:SetName("Kash")
	Item_8:SetIconName("GUI/imagesets/Inventory/kash.png")
	Item_8:SetNameTextId(7)
	Item_8:SetDescriptionId(37)
	Item_8:SetLongDescriptionId(-1)
	Item_8:SetMax(9999)
	Item_8:SetBuyPrice(1)
	Item_8:SetSellPrice(1)
	Item_8:SetDescriptionTextExtra("")
	Item_8:SetType(6)
	Item_8:SetEffect(1)
	Item_8:SetFlag(0)
	Item_8:SetEphemere(false)
	Item_8:SetStringFlag("")
	Item_8:SetColor1(-1)
	Item_8:SetColor2(-1)
	Item_8:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_8)

	Item_9 = InventoryItemDef(9)
	Item_9:SetName("Feather")
	Item_9:SetIconName("GUI/imagesets/Inventory/Feather.png")
	Item_9:SetNameTextId(8)
	Item_9:SetDescriptionId(38)
	Item_9:SetLongDescriptionId(-1)
	Item_9:SetMax(1)
	Item_9:SetBuyPrice(1)
	Item_9:SetSellPrice(1)
	Item_9:SetDescriptionTextExtra("")
	Item_9:SetType(7)
	Item_9:SetEffect(1)
	Item_9:SetFlag(1)
	Item_9:SetEphemere(false)
	Item_9:SetStringFlag("")
	Item_9:SetColor1(-1)
	Item_9:SetColor2(-1)
	Item_9:SetReplacedItem(-1)
	Item_9_act = OpenLetterWritterAction()
	Item_9:SetAction(Item_9_act)
	environment:AddInventoryItem(Item_9)

	Item_10 = InventoryItemDef(10)
	Item_10:SetName("Letter")
	Item_10:SetIconName("GUI/imagesets/Inventory/letter.png")
	Item_10:SetNameTextId(11)
	Item_10:SetDescriptionId(41)
	Item_10:SetLongDescriptionId(-1)
	Item_10:SetMax(1)
	Item_10:SetBuyPrice(1)
	Item_10:SetSellPrice(1)
	Item_10:SetDescriptionTextExtra("")
	Item_10:SetType(8)
	Item_10:SetEffect(1)
	Item_10:SetFlag(0)
	Item_10:SetEphemere(false)
	Item_10:SetStringFlag("")
	Item_10:SetColor1(-1)
	Item_10:SetColor2(-1)
	Item_10:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_10)

	Item_11 = InventoryItemDef(11)
	Item_11:SetName("Gas")
	Item_11:SetIconName("GUI/imagesets/Inventory/Gas.png")
	Item_11:SetNameTextId(12)
	Item_11:SetDescriptionId(42)
	Item_11:SetLongDescriptionId(-1)
	Item_11:SetMax(10)
	Item_11:SetBuyPrice(1)
	Item_11:SetSellPrice(1)
	Item_11:SetDescriptionTextExtra("")
	Item_11:SetType(6)
	Item_11:SetEffect(1)
	Item_11:SetFlag(0)
	Item_11:SetEphemere(false)
	Item_11:SetStringFlag("")
	Item_11:SetColor1(-1)
	Item_11:SetColor2(-1)
	Item_11:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_11)

	Item_12 = InventoryItemDef(12)
	Item_12:SetName("Ticket")
	Item_12:SetIconName("GUI/imagesets/Inventory/Ticket.png")
	Item_12:SetNameTextId(13)
	Item_12:SetDescriptionId(43)
	Item_12:SetLongDescriptionId(-1)
	Item_12:SetMax(1)
	Item_12:SetBuyPrice(1)
	Item_12:SetSellPrice(1)
	Item_12:SetDescriptionTextExtra("")
	Item_12:SetType(6)
	Item_12:SetEffect(1)
	Item_12:SetFlag(0)
	Item_12:SetEphemere(false)
	Item_12:SetStringFlag("")
	Item_12:SetColor1(-1)
	Item_12:SetColor2(-1)
	Item_12:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_12)

	Item_13 = InventoryItemDef(13)
	Item_13:SetName("Champagne")
	Item_13:SetIconName("GUI/imagesets/Inventory/glass.png")
	Item_13:SetNameTextId(14)
	Item_13:SetDescriptionId(44)
	Item_13:SetLongDescriptionId(-1)
	Item_13:SetMax(10)
	Item_13:SetBuyPrice(1)
	Item_13:SetSellPrice(1)
	Item_13:SetDescriptionTextExtra("")
	Item_13:SetType(1)
	Item_13:SetEffect(80)
	Item_13:SetFlag(3)
	Item_13:SetEphemere(false)
	Item_13:SetStringFlag("")
	Item_13:SetColor1(-1)
	Item_13:SetColor2(-1)
	Item_13:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_13)

	Item_14 = InventoryItemDef(14)
	Item_14:SetName("Gluehwein")
	Item_14:SetIconName("GUI/imagesets/Inventory/gluehwein.png")
	Item_14:SetNameTextId(15)
	Item_14:SetDescriptionId(45)
	Item_14:SetLongDescriptionId(-1)
	Item_14:SetMax(10)
	Item_14:SetBuyPrice(1)
	Item_14:SetSellPrice(1)
	Item_14:SetDescriptionTextExtra("")
	Item_14:SetType(1)
	Item_14:SetEffect(80)
	Item_14:SetFlag(2)
	Item_14:SetEphemere(false)
	Item_14:SetStringFlag("")
	Item_14:SetColor1(-1)
	Item_14:SetColor2(-1)
	Item_14:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_14)

	Item_15 = InventoryItemDef(15)
	Item_15:SetName("Lebkuchen")
	Item_15:SetIconName("GUI/imagesets/Inventory/Lebkuchen.png")
	Item_15:SetNameTextId(16)
	Item_15:SetDescriptionId(46)
	Item_15:SetLongDescriptionId(-1)
	Item_15:SetMax(10)
	Item_15:SetBuyPrice(1)
	Item_15:SetSellPrice(1)
	Item_15:SetDescriptionTextExtra("")
	Item_15:SetType(1)
	Item_15:SetEffect(80)
	Item_15:SetFlag(1)
	Item_15:SetEphemere(false)
	Item_15:SetStringFlag("")
	Item_15:SetColor1(-1)
	Item_15:SetColor2(-1)
	Item_15:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_15)

	Item_16 = InventoryItemDef(16)
	Item_16:SetName("Candy")
	Item_16:SetIconName("GUI/imagesets/Inventory/candy.png")
	Item_16:SetNameTextId(17)
	Item_16:SetDescriptionId(47)
	Item_16:SetLongDescriptionId(-1)
	Item_16:SetMax(10)
	Item_16:SetBuyPrice(1)
	Item_16:SetSellPrice(1)
	Item_16:SetDescriptionTextExtra("")
	Item_16:SetType(1)
	Item_16:SetEffect(80)
	Item_16:SetFlag(1)
	Item_16:SetEphemere(false)
	Item_16:SetStringFlag("")
	Item_16:SetColor1(-1)
	Item_16:SetColor2(-1)
	Item_16:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_16)

	Item_17 = InventoryItemDef(17)
	Item_17:SetName("Giftbox 2009")
	Item_17:SetIconName("GUI/imagesets/Inventory/giftbox.png")
	Item_17:SetNameTextId(18)
	Item_17:SetDescriptionId(48)
	Item_17:SetLongDescriptionId(-1)
	Item_17:SetMax(1)
	Item_17:SetBuyPrice(1)
	Item_17:SetSellPrice(1)
	Item_17:SetDescriptionTextExtra("")
	Item_17:SetType(10)
	Item_17:SetEffect(1)
	Item_17:SetFlag(0)
	Item_17:SetEphemere(false)
	Item_17:SetStringFlag("")
	Item_17:SetColor1(-1)
	Item_17:SetColor2(-1)
	Item_17:SetReplacedItem(-1)
	Item_17:AddContainedItem(8, 100, 200, 1, -1)
	Item_17:AddContainedItem(28, 1, 1, 1, -1)
	environment:AddInventoryItem(Item_17)

	Item_18 = InventoryItemDef(18)
	Item_18:SetName("Hair dryer")
	Item_18:SetIconName("GUI/imagesets/Inventory/hairdryer.png")
	Item_18:SetNameTextId(19)
	Item_18:SetDescriptionId(49)
	Item_18:SetLongDescriptionId(-1)
	Item_18:SetMax(1)
	Item_18:SetBuyPrice(1)
	Item_18:SetSellPrice(1)
	Item_18:SetDescriptionTextExtra("")
	Item_18:SetType(5)
	Item_18:SetEffect(1)
	Item_18:SetFlag(0)
	Item_18:SetEphemere(false)
	Item_18:SetStringFlag("")
	Item_18:SetColor1(-1)
	Item_18:SetColor2(-1)
	Item_18:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_18)

	Item_19 = InventoryItemDef(19)
	Item_19:SetName("Grain")
	Item_19:SetIconName("GUI/imagesets/Inventory/grain.png")
	Item_19:SetNameTextId(20)
	Item_19:SetDescriptionId(50)
	Item_19:SetLongDescriptionId(-1)
	Item_19:SetMax(1)
	Item_19:SetBuyPrice(1)
	Item_19:SetSellPrice(1)
	Item_19:SetDescriptionTextExtra("")
	Item_19:SetType(5)
	Item_19:SetEffect(1)
	Item_19:SetFlag(0)
	Item_19:SetEphemere(false)
	Item_19:SetStringFlag("")
	Item_19:SetColor1(-1)
	Item_19:SetColor2(-1)
	Item_19:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_19)

	Item_20 = InventoryItemDef(20)
	Item_20:SetName("Birthday cake")
	Item_20:SetIconName("GUI/imagesets/Inventory/bcake1.png")
	Item_20:SetNameTextId(21)
	Item_20:SetDescriptionId(51)
	Item_20:SetLongDescriptionId(-1)
	Item_20:SetMax(5)
	Item_20:SetBuyPrice(1)
	Item_20:SetSellPrice(1)
	Item_20:SetDescriptionTextExtra("")
	Item_20:SetType(1)
	Item_20:SetEffect(100)
	Item_20:SetFlag(3)
	Item_20:SetEphemere(false)
	Item_20:SetStringFlag("")
	Item_20:SetColor1(-1)
	Item_20:SetColor2(-1)
	Item_20:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_20)

	Item_21 = InventoryItemDef(21)
	Item_21:SetName("Giftbox 2010")
	Item_21:SetIconName("GUI/imagesets/Inventory/giftbox.png")
	Item_21:SetNameTextId(28)
	Item_21:SetDescriptionId(58)
	Item_21:SetLongDescriptionId(-1)
	Item_21:SetMax(1)
	Item_21:SetBuyPrice(1)
	Item_21:SetSellPrice(1)
	Item_21:SetDescriptionTextExtra("")
	Item_21:SetType(10)
	Item_21:SetEffect(1)
	Item_21:SetFlag(0)
	Item_21:SetEphemere(false)
	Item_21:SetStringFlag("")
	Item_21:SetColor1(-1)
	Item_21:SetColor2(-1)
	Item_21:SetReplacedItem(-1)
	Item_21:AddContainedItem(8, 100, 200, 1, -1)
	Item_21:AddContainedItem(29, 1, 1, 1, -1)
	environment:AddInventoryItem(Item_21)

	Item_22 = InventoryItemDef(22)
	Item_22:SetName("Yellow Magic ball")
	Item_22:SetIconName("GUI/imagesets/Inventory/yellowball.png")
	Item_22:SetNameTextId(22)
	Item_22:SetDescriptionId(52)
	Item_22:SetLongDescriptionId(-1)
	Item_22:SetMax(1)
	Item_22:SetBuyPrice(1)
	Item_22:SetSellPrice(1)
	Item_22:SetDescriptionTextExtra("")
	Item_22:SetType(4)
	Item_22:SetEffect(10)
	Item_22:SetFlag(1)
	Item_22:SetEphemere(false)
	Item_22:SetStringFlag("MagicBall")
	Item_22:SetColor1(1)
	Item_22:SetColor2(-1)
	Item_22:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_22)

	Item_23 = InventoryItemDef(23)
	Item_23:SetName("Saber")
	Item_23:SetIconName("GUI/imagesets/Inventory/saber.png")
	Item_23:SetNameTextId(23)
	Item_23:SetDescriptionId(53)
	Item_23:SetLongDescriptionId(-1)
	Item_23:SetMax(1)
	Item_23:SetBuyPrice(1)
	Item_23:SetSellPrice(1)
	Item_23:SetDescriptionTextExtra("")
	Item_23:SetType(4)
	Item_23:SetEffect(30)
	Item_23:SetFlag(1)
	Item_23:SetEphemere(false)
	Item_23:SetStringFlag("Saber")
	Item_23:SetColor1(-1)
	Item_23:SetColor2(-1)
	Item_23:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_23)

	Item_24 = InventoryItemDef(24)
	Item_24:SetName("Prisoner outfit")
	Item_24:SetIconName("GUI/imagesets/Inventory/prison.png")
	Item_24:SetNameTextId(24)
	Item_24:SetDescriptionId(54)
	Item_24:SetLongDescriptionId(-1)
	Item_24:SetMax(1)
	Item_24:SetBuyPrice(1)
	Item_24:SetSellPrice(1)
	Item_24:SetDescriptionTextExtra("")
	Item_24:SetType(9)
	Item_24:SetEffect(0)
	Item_24:SetFlag(1)
	Item_24:SetEphemere(false)
	Item_24:SetStringFlag("Prisoner")
	Item_24:SetColor1(-1)
	Item_24:SetColor2(-1)
	Item_24:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_24)

	Item_25 = InventoryItemDef(25)
	Item_25:SetName("Nurse outfit")
	Item_25:SetIconName("GUI/imagesets/Inventory/nurse.png")
	Item_25:SetNameTextId(25)
	Item_25:SetDescriptionId(55)
	Item_25:SetLongDescriptionId(-1)
	Item_25:SetMax(1)
	Item_25:SetBuyPrice(1)
	Item_25:SetSellPrice(1)
	Item_25:SetDescriptionTextExtra("")
	Item_25:SetType(9)
	Item_25:SetEffect(0)
	Item_25:SetFlag(1)
	Item_25:SetEphemere(false)
	Item_25:SetStringFlag("Nurse")
	Item_25:SetColor1(-1)
	Item_25:SetColor2(-1)
	Item_25:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_25)

	Item_26 = InventoryItemDef(26)
	Item_26:SetName("Tunic outfit")
	Item_26:SetIconName("GUI/imagesets/Inventory/tunic.png")
	Item_26:SetNameTextId(26)
	Item_26:SetDescriptionId(56)
	Item_26:SetLongDescriptionId(-1)
	Item_26:SetMax(1)
	Item_26:SetBuyPrice(1)
	Item_26:SetSellPrice(1)
	Item_26:SetDescriptionTextExtra("")
	Item_26:SetType(9)
	Item_26:SetEffect(10)
	Item_26:SetFlag(1)
	Item_26:SetEphemere(false)
	Item_26:SetStringFlag("Tunic")
	Item_26:SetColor1(-1)
	Item_26:SetColor2(-1)
	Item_26:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_26)

	Item_27 = InventoryItemDef(27)
	Item_27:SetName("Fulltunic outfit")
	Item_27:SetIconName("GUI/imagesets/Inventory/tunic-medailon.png")
	Item_27:SetNameTextId(27)
	Item_27:SetDescriptionId(57)
	Item_27:SetLongDescriptionId(-1)
	Item_27:SetMax(1)
	Item_27:SetBuyPrice(1)
	Item_27:SetSellPrice(1)
	Item_27:SetDescriptionTextExtra("")
	Item_27:SetType(9)
	Item_27:SetEffect(20)
	Item_27:SetFlag(1)
	Item_27:SetEphemere(false)
	Item_27:SetStringFlag("Fulltunic")
	Item_27:SetColor1(-1)
	Item_27:SetColor2(-1)
	Item_27:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_27)

	Item_28 = InventoryItemDef(28)
	Item_28:SetName("Red horse")
	Item_28:SetIconName("GUI/imagesets/Inventory/Horse.png")
	Item_28:SetNameTextId(29)
	Item_28:SetDescriptionId(34)
	Item_28:SetLongDescriptionId(-1)
	Item_28:SetMax(1)
	Item_28:SetBuyPrice(1)
	Item_28:SetSellPrice(1)
	Item_28:SetDescriptionTextExtra("")
	Item_28:SetType(3)
	Item_28:SetEffect(0)
	Item_28:SetFlag(2)
	Item_28:SetEphemere(false)
	Item_28:SetStringFlag("")
	Item_28:SetColor1(2)
	Item_28:SetColor2(-1)
	Item_28:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_28)

	Item_29 = InventoryItemDef(29)
	Item_29:SetName("Red dinofly")
	Item_29:SetIconName("GUI/imagesets/Inventory/Dino.png")
	Item_29:SetNameTextId(30)
	Item_29:SetDescriptionId(35)
	Item_29:SetLongDescriptionId(-1)
	Item_29:SetMax(1)
	Item_29:SetBuyPrice(1)
	Item_29:SetSellPrice(1)
	Item_29:SetDescriptionTextExtra("")
	Item_29:SetType(3)
	Item_29:SetEffect(0)
	Item_29:SetFlag(3)
	Item_29:SetEphemere(false)
	Item_29:SetStringFlag("")
	Item_29:SetColor1(2)
	Item_29:SetColor2(-1)
	Item_29:SetReplacedItem(-1)
	environment:AddInventoryItem(Item_29)

	Item_30 = InventoryItemDef(30)
	Item_30:SetName("Red Magic ball")
	Item_30:SetIconName("GUI/imagesets/Inventory/redball.png")
	Item_30:SetNameTextId(59)
	Item_30:SetDescriptionId(52)
	Item_30:SetLongDescriptionId(-1)
	Item_30:SetMax(1)
	Item_30:SetBuyPrice(1)
	Item_30:SetSellPrice(1)
	Item_30:SetDescriptionTextExtra("")
	Item_30:SetType(4)
	Item_30:SetEffect(20)
	Item_30:SetFlag(1)
	Item_30:SetEphemere(false)
	Item_30:SetStringFlag("MagicBall")
	Item_30:SetColor1(2)
	Item_30:SetColor2(-1)
	Item_30:SetReplacedItem(22)
	environment:AddInventoryItem(Item_30)

end