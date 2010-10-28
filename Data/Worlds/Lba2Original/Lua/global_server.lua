function InitGlobal(environment)
	Action_1 = TeleportAction(1, "tp_from_main_to_secondary", "Map002_2", 0)
	environment:AddAction(Action_1)

	Action_2 = TeleportAction(2, "tp_from_main_to_citadel", "CITABAU", 2)
	environment:AddAction(Action_2)

	Action_3 = TeleportAction(3, "tp_from_citadel_to_main", "Map001_2", 2)
	environment:AddAction(Action_3)

	Action_4 = TeleportAction(4, "tp_from_secondary_to_main", "Map001_2", 3)
	environment:AddAction(Action_4)

	Action_5 = TeleportAction(5, "tp_from_architect_to_citadel", "CITABAU", 3)
	environment:AddAction(Action_5)

	Action_6 = TeleportAction(6, "tp_from_citadel_to_architect", "Map010_2", 0)
	environment:AddAction(Action_6)

	Action_7 = TeleportAction(7, "tp_from_ticket_to_citadel", "CITABAU", 4)
	environment:AddAction(Action_7)

	Action_8 = TeleportAction(8, "tp_from_citadel_to_ticket", "Map009_2", 0)
	environment:AddAction(Action_8)

	Action_9 = TeleportAction(9, "tp_from_mrpaul_to_citadel", "CITABAU", 5)
	environment:AddAction(Action_9)

	Action_10 = TeleportAction(10, "tp_from_citadel_to_mrpaul", "Map008_2", 0)
	environment:AddAction(Action_10)

	Action_11 = TeleportAction(11, "tp_from_citadel_to_shop", "Map015_2", 0)
	environment:AddAction(Action_11)

	Action_12 = TeleportAction(12, "tp_from_shop_to_citadel", "CITABAU", 6)
	environment:AddAction(Action_12)

	Action_13 = TeleportAction(13, "tp_from_citadel_to_tavern", "Map004_2", 0)
	environment:AddAction(Action_13)

	Action_14 = TeleportAction(14, "from_tavern_to_citadel", "CITABAU", 7)
	environment:AddAction(Action_14)

	Action_15 = TeleportAction(15, "tp_from_citadel_to_museum", "Map016_2", 0)
	environment:AddAction(Action_15)

	Action_16 = TeleportAction(16, "tp_from_museum_to_citadel", "CITABAU", 8)
	environment:AddAction(Action_16)

	Action_17 = TeleportAction(17, "tp_from_tavern_to_taverncellar", "Map005_2", 0)
	environment:AddAction(Action_17)

	Action_18 = TeleportAction(18, "tp_from_taverncellar_to_tavern", "Map004_2", 1)
	environment:AddAction(Action_18)

	Action_19 = TeleportAction(19, "tp_sendell", "Map035_2", 1)
	environment:AddAction(Action_19)

	Action_20 = TeleportAction(20, "tp_from_taverncellar_to_sewer", "Map018_2", 0)
	environment:AddAction(Action_20)

	Action_21 = TeleportAction(21, "tp_from_sewer_to_sewersecret", "Map019_2", 1)
	environment:AddAction(Action_21)

	Action_22 = TeleportAction(22, "tp_from_sewersecret_to_sewer", "Map018_2", 3)
	environment:AddAction(Action_22)

	Action_23 = TeleportAction(23, "tp_from_citadel_to_pharmacy", "Map023_2", 1)
	environment:AddAction(Action_23)

	Action_24 = TeleportAction(24, "tp_from_pharmacy_to_citadel", "CITABAU", 9)
	environment:AddAction(Action_24)

	Action_25 = TeleportAction(25, "tp_from_citadel_to_baggage", "Map006_2", 1)
	environment:AddAction(Action_25)

	Action_26 = TeleportAction(26, "tp_from_baggage_to_citadel", "CITABAU", 10)
	environment:AddAction(Action_26)

	Action_27 = TeleportAction(27, "tp_from_baggagebag_to_baggagesecondbag", "Map007_2", 1)
	environment:AddAction(Action_27)

	Action_28 = TeleportAction(28, "tp_from_baggagesecondbag_to_baggagebag", "Map006_2", 2)
	environment:AddAction(Action_28)

	Action_29 = TeleportAction(29, "tp_from_baggagesecond_to_baggage", "Map006_2", 3)
	environment:AddAction(Action_29)

	Action_30 = TeleportAction(30, "tp_from_baggage_to_baggagesecond", "Map007_2", 2)
	environment:AddAction(Action_30)

	Action_31 = TeleportAction(31, "tp_from_baggagesecond_to_baggagesecret", "Map017_2", 1)
	environment:AddAction(Action_31)

	Action_32 = TeleportAction(32, "tp_from_baggagesecret_to_baggagesecond", "Map007_2", 3)
	environment:AddAction(Action_32)

	Action_33 = TeleportAction(33, "tp_from_citadel_to_school", "Map038_2", 1)
	environment:AddAction(Action_33)

	Action_34 = TeleportAction(34, "tp_from_school_to_citadel", "CITABAU", 11)
	environment:AddAction(Action_34)

	Action_35 = TeleportAction(35, "tp_from_citadel_to_magician", "Map022_2", 1)
	environment:AddAction(Action_35)

	Action_36 = TeleportAction(36, "tp_from_magician_to_citadel", "CITABAU", 12)
	environment:AddAction(Action_36)

	Action_37 = TeleportAction(37, "tp_from_spidercavefirst_to_citadelfirst", "CITABAU", 13)
	environment:AddAction(Action_37)

	Action_38 = TeleportAction(38, "tp_from_citadel_to_spidercavefirst", "Map043_2", 1)
	environment:AddAction(Action_38)

	Action_39 = TeleportAction(39, "tp_from_spidersecond_to_citadelsecond", "CITABAU", 14)
	environment:AddAction(Action_39)

	Action_40 = TeleportAction(40, "tp_from_citadelsecond_to_spidersecond", "Map043_2", 2)
	environment:AddAction(Action_40)

	Action_41 = TeleportAction(41, "tp_from_citadel_to_tralumain", "Map003_2", 1)
	environment:AddAction(Action_41)

	Action_42 = TeleportAction(42, "tp_from_tralumain_to_citadel", "CITABAU", 15)
	environment:AddAction(Action_42)

	Action_43 = TeleportAction(43, "tp_from_tralumain_to_tralusecond", "Map021_2", 1)
	environment:AddAction(Action_43)

	Action_44 = TeleportAction(44, "tp_from_tralusecond_to_tralumain", "Map003_2", 2)
	environment:AddAction(Action_44)

	Action_45 = TeleportAction(45, "tp_from_tralusecond_to_traluthird", "Map020_2", 1)
	environment:AddAction(Action_45)

	Action_46 = TeleportAction(46, "tp_from_traluthird_to_tralusecond", "Map021_2", 2)
	environment:AddAction(Action_46)

	Action_47 = TeleportAction(47, "tp_from_traluthird_to_tralumain", "Map003_2", 3)
	environment:AddAction(Action_47)

	Action_48 = TeleportAction(48, "tp_from_tralumain_to_traluthird", "Map020_2", 2)
	environment:AddAction(Action_48)

	Action_49 = TeleportAction(49, "tp_from_desert_to_ticketshop", "Map041_2", 0)
	environment:AddAction(Action_49)

	Action_50 = TeleportAction(50, "tp_from_ticketshop_to_desert", "DESERT", 2)
	environment:AddAction(Action_50)

	Action_51 = TeleportAction(51, "tp_from_shop_to_desert", "DESERT", 3)
	environment:AddAction(Action_51)

	Action_52 = TeleportAction(52, "tp_from_desert_to_shop", "Map037_2", 1)
	environment:AddAction(Action_52)

	Action_53 = TeleportAction(53, "tp_from_keroc_to_desert", "DESERT", 4)
	environment:AddAction(Action_53)

	Action_54 = TeleportAction(54, "tp_from_desert_to_keroc", "Map036_2", 1)
	environment:AddAction(Action_54)

	Action_55 = TeleportAction(55, "tp_from_desert_to_baldino", "Map039_2", 1)
	environment:AddAction(Action_55)

	Action_56 = TeleportAction(56, "tp_from_baldino_to_desert", "DESERT", 5)
	environment:AddAction(Action_56)

	Action_57 = TeleportAction(57, "tp_from_desert_to_bar", "Map040_2", 1)
	environment:AddAction(Action_57)

	Action_58 = TeleportAction(58, "tp_from_bar_to_desert", "DESERT", 6)
	environment:AddAction(Action_58)

	Action_59 = TeleportAction(59, "tp_from_desert_to_magic", "Map029_2", 1)
	environment:AddAction(Action_59)

	Action_60 = TeleportAction(60, "tp_from_magic_to_desert", "DESERT", 7)
	environment:AddAction(Action_60)

	Action_61 = TeleportAction(61, "tp_from_magic_to_magicsecond", "Map028_2", 1)
	environment:AddAction(Action_61)

	Action_62 = TeleportAction(62, "tp_from_magicsecond_to_magic", "Map029_2", 2)
	environment:AddAction(Action_62)

	Action_63 = TeleportAction(63, "tp_from_magicsecond_to_blowtron", "Map034_2", 1)
	environment:AddAction(Action_63)

	Action_64 = TeleportAction(64, "tp_from_blowtron_to_magicsecond", "Map028_2", 2)
	environment:AddAction(Action_64)

	Action_65 = TeleportAction(65, "tp_from_haciendaent1_to_desertent1", "DESERT", 8)
	environment:AddAction(Action_65)

	Action_66 = TeleportAction(66, "tp_from_haciendaent2_to_desertent2", "DESERT", 9)
	environment:AddAction(Action_66)

	Action_67 = TeleportAction(67, "tp_from_desertent1_to_haciendaent1", "Map025_2", 1)
	environment:AddAction(Action_67)

	Action_68 = TeleportAction(68, "tp_from_desertent2_to_haciendaent2", "Map025_2", 2)
	environment:AddAction(Action_68)

	Action_69 = TeleportAction(69, "tp_from_hacienda_to_hacienda2", "Map030_2", 1)
	environment:AddAction(Action_69)

	Action_70 = TeleportAction(70, "tp_from_hacienda2_to_hacienda", "Map025_2", 3)
	environment:AddAction(Action_70)

	Action_71 = TeleportAction(71, "tp_from_hacienda2_to_bathwomen", "Map026_2", 1)
	environment:AddAction(Action_71)

	Action_72 = TeleportAction(72, "tp_from_hacienda2_to_bathmen", "Map031_2", 1)
	environment:AddAction(Action_72)

	Action_73 = TeleportAction(73, "tp_from_bathmen_to_hacienda2", "Map030_2", 3)
	environment:AddAction(Action_73)

	Action_74 = TeleportAction(74, "tp_from_bathwomen_to_hacienda2", "Map030_2", 2)
	environment:AddAction(Action_74)

	Action_76 = TeleportAction(76, "tp_form_desert_to_mushroom", "Map076_2", 0)
	environment:AddAction(Action_76)

	Action_77 = TeleportAction(77, "tp_from_mushroom_to_bumain", "Map011_2", 2)
	environment:AddAction(Action_77)

	Action_78 = TeleportAction(78, "tp_from_desert_to_bumain", "Map011_2", 1)
	environment:AddAction(Action_78)

	Action_79 = TeleportAction(79, "tp_from_bumain_to_desert", "DESERT", 10)
	environment:AddAction(Action_79)

	Action_80 = TeleportAction(80, "tp_from_bumain_to_buunder", "Map012_2", 1)
	environment:AddAction(Action_80)

	Action_81 = TeleportAction(81, "tp_form_buunder_to_bumain", "Map011_2", 3)
	environment:AddAction(Action_81)

	Action_82 = TeleportAction(82, "tp_from_buunder_to_buesmer", "Map013_2", 1)
	environment:AddAction(Action_82)

	Action_83 = TeleportAction(83, "tp_from_bathmen_to_passage", "Map033_2", 1)
	environment:AddAction(Action_83)

	Action_84 = TeleportAction(84, "tp_from_passage_to_bathmen", "Map031_2", 2)
	environment:AddAction(Action_84)

	Action_85 = TeleportAction(85, "tp_from_passage_to_buesmer", "Map013_2", 2)
	environment:AddAction(Action_85)

	Action_86 = TeleportAction(86, "tp_from_buesmer_to_buunder", "Map012_2", 2)
	environment:AddAction(Action_86)

	Action_87 = TeleportAction(87, "tp_from_buesmer_to_passage", "Map033_2", 2)
	environment:AddAction(Action_87)

	Action_88 = TeleportAction(88, "tp_from_buesmer_to_bushuttle", "Map042_2", 1)
	environment:AddAction(Action_88)

	Action_89 = TeleportAction(89, "tp_from_bushuttle_to_buesmer", "Map013_2", 3)
	environment:AddAction(Action_89)

end
