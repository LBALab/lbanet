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

	Action_90 = TeleportAction(90, "tp_from_outmain_to_control", "Map032_2", 1)
	environment:AddAction(Action_90)

	Action_91 = TeleportAction(91, "tp_from_control_to_outmain", "EMERAUDE", 3)
	environment:AddAction(Action_91)

	Action_92 = TeleportAction(92, "tp_from_outmain_to_square", "Map113_2", 1)
	environment:AddAction(Action_92)

	Action_93 = TeleportAction(93, "tp_from_square_to_outmain", "EMERAUDE", 4)
	environment:AddAction(Action_93)

	Action_94 = TeleportAction(94, "tp_from_square_to_tech", "Map024_2", 2)
	environment:AddAction(Action_94)

	Action_95 = TeleportAction(95, "tp_from_tech_to_square", "Map113_2", 2)
	environment:AddAction(Action_95)

	Action_96 = TeleportAction(96, "tp_from_tech_to_inmain", "Map014_2", 2)
	environment:AddAction(Action_96)

	Action_97 = TeleportAction(97, "tp_from_inmain_to_tech", "Map024_2", 3)
	environment:AddAction(Action_97)

	Action_98 = TeleportAction(98, "tp_from_tech_to_cross", "Map045_2", 1)
	environment:AddAction(Action_98)

	Action_99 = TeleportAction(99, "tp_from_cross_to_tech", "Map024_2", 4)
	environment:AddAction(Action_99)

	Action_100 = TeleportAction(100, "tp_from_cross_to_outmain", "EMERAUDE", 5)
	environment:AddAction(Action_100)

	Action_101 = TeleportAction(101, "tp_from_outmain_to_cross", "Map045_2", 2)
	environment:AddAction(Action_101)

	Action_102 = TeleportAction(102, "tp_from_inmain_to_baldinocell", "Map046_2", 1)
	environment:AddAction(Action_102)

	Action_103 = TeleportAction(103, "tp_from_baldinocell_to_inmain", "Map014_2", 1)
	environment:AddAction(Action_103)

	Action_104 = TeleportAction(104, "tp_from_outmain_to_circle", "Map044_2", 1)
	environment:AddAction(Action_104)

	Action_105 = TeleportAction(105, "tp_form_circle_to_outmain", "EMERAUDE", 6)
	environment:AddAction(Action_105)

	Action_106 = TeleportAction(106, "tp_from_circle_to_inmain", "Map014_2", 3)
	environment:AddAction(Action_106)

	Action_107 = TeleportAction(107, "tp_from_inmain_to_circle", "Map044_2", 2)
	environment:AddAction(Action_107)

	Action_108 = TeleportAction(108, "tp_from_inmain_to_triangle", "Map112_2", 1)
	environment:AddAction(Action_108)

	Action_109 = TeleportAction(109, "tp_from_triangle_to_inmain", "Map014_2", 4)
	environment:AddAction(Action_109)

	Action_110 = TeleportAction(110, "tp_from_triangle_to_outmain", "EMERAUDE", 7)
	environment:AddAction(Action_110)

	Action_111 = TeleportAction(111, "tp_from_outmain_to_triangle", "Map112_2", 2)
	environment:AddAction(Action_111)

	Action_112 = TeleportAction(112, "tp_from_otringal_to_control", "Map054_2", 1)
	environment:AddAction(Action_112)

	Action_113 = TeleportAction(113, "tp_from_control_to_otringal", "OTRINGAL", 2)
	environment:AddAction(Action_113)

	Action_114 = TeleportAction(114, "tp_from_control_to_controltop", "Map054_2", 3)
	environment:AddAction(Action_114)

	Action_115 = TeleportAction(115, "tp_from_controltop_to_control", "Map054_2", 2)
	environment:AddAction(Action_115)

	Action_116 = TeleportAction(116, "tp_from_otringal_to_way1", "Map055_2", 1)
	environment:AddAction(Action_116)

	Action_117 = TeleportAction(117, "tp_from_otringal_to_terminal", "Map047_2", 1)
	environment:AddAction(Action_117)

	Action_118 = TeleportAction(118, "tp_from_way1_to_otringal1", "OTRINGAL", 3)
	environment:AddAction(Action_118)

	Action_119 = TeleportAction(119, "tp_from_way2_to_otringal2", "OTRINGAL", 4)
	environment:AddAction(Action_119)

	Action_120 = TeleportAction(120, "tp_from_otringal_to_way2", "Map055_2", 2)
	environment:AddAction(Action_120)

	Action_121 = TeleportAction(121, "tp_from_way1_to_terminal1", "Map047_2", 3)
	environment:AddAction(Action_121)

	Action_122 = TeleportAction(122, "tp_from_way2_to_terminal2", "Map047_2", 2)
	environment:AddAction(Action_122)

	Action_123 = TeleportAction(123, "tp_from_terminal_to_otringal", "OTRINGAL", 5)
	environment:AddAction(Action_123)

	Action_124 = TeleportAction(124, "tp_from_terminal2_to_way2", "Map055_2", 4)
	environment:AddAction(Action_124)

	Action_125 = TeleportAction(125, "tp_form_terminal1_to_way1", "Map055_2", 3)
	environment:AddAction(Action_125)

	Action_126 = TeleportAction(126, "tp_from_otringal_to_copback", "Map053_2", 2)
	environment:AddAction(Action_126)

	Action_131 = TeleportAction(131, "tp_from_copbox_to_otringalcop1", "OTRINGAL", 7)
	environment:AddAction(Action_131)

	Action_132 = TeleportAction(132, "tp_from_copbox_to_otringalcop2", "OTRINGAL", 8)
	environment:AddAction(Action_132)

	Action_133 = TeleportAction(133, "tp_from_otringalcop1_to_copbox", "Map052_2", 2)
	environment:AddAction(Action_133)

	Action_134 = TeleportAction(134, "tp_from_otringalcop2_to_copbox2", "Map052_2", 3)
	environment:AddAction(Action_134)

	Action_135 = TeleportAction(135, "tp_from_jail_to_copbox", "Map052_2", 1)
	environment:AddAction(Action_135)

	Action_136 = TeleportAction(136, "tp_from_copbox_to_jail", "Map053_2", 1)
	environment:AddAction(Action_136)

	Action_137 = TeleportAction(137, "tp_from_copback_to_otringal", "OTRINGAL", 9)
	environment:AddAction(Action_137)

	Action_138 = TeleportAction(138, "tp_from_otringal_to_lowelelow", "Map051_2", 1)
	environment:AddAction(Action_138)

	Action_139 = TeleportAction(139, "tp_from_lowelelow_to_otringal", "OTRINGAL", 6)
	environment:AddAction(Action_139)

	Action_140 = TeleportAction(140, "tp_from_loweleup_to_lowelelow", "Map051_2", 2)
	environment:AddAction(Action_140)

	Action_141 = TeleportAction(141, "tp_from_lowelelow_to_loweleup", "Map084_2", 1)
	environment:AddAction(Action_141)

	Action_142 = TeleportAction(142, "tp_from_loweleup_to_otringal", "OTRINGAL", 10)
	environment:AddAction(Action_142)

	Action_143 = TeleportAction(143, "tp_from_otringal_to_loweleright", "Map084_2", 3)
	environment:AddAction(Action_143)

	Action_144 = TeleportAction(144, "tp_from_loweleup_to_otr2", "OTRINGAL", 11)
	environment:AddAction(Action_144)

	Action_145 = TeleportAction(145, "tp_from_otringal_to_loweleleft", "Map084_2", 2)
	environment:AddAction(Action_145)

	Action_146 = TeleportAction(146, "tp_from_souvenir_to_otringal", "OTRINGAL", 12)
	environment:AddAction(Action_146)

	Action_147 = TeleportAction(147, "tp_from_otringal_to_souvenir", "Map092_2", 1)
	environment:AddAction(Action_147)

	Action_148 = TeleportAction(148, "tp_from_dissidents_to_souvenir", "Map092_2", 2)
	environment:AddAction(Action_148)

	Action_149 = TeleportAction(149, "tp_from_souvenir_to_dissidents", "Map093_2", 1)
	environment:AddAction(Action_149)

	Action_150 = TeleportAction(150, "tp_from_hotelstraight_to_otringalstraight", "OTRINGAL", 19)
	environment:AddAction(Action_150)

	Action_151 = TeleportAction(151, "tp_from_otringalstraight_to_hotelstraight", "Map050_2", 1)
	environment:AddAction(Action_151)

	Action_152 = TeleportAction(152, "tp_from_hotelcurve_to_ortingalcurve", "OTRINGAL", 20)
	environment:AddAction(Action_152)

	Action_153 = TeleportAction(153, "tp_from_otringalcurve_to_hotelcurve", "Map050_2", 2)
	environment:AddAction(Action_153)

	Action_154 = TeleportAction(154, "drop", "Map081_2", 1)
	environment:AddAction(Action_154)

	Action_156 = TeleportAction(156, "up", "Map081_2", 3)
	environment:AddAction(Action_156)

	Action_157 = TeleportAction(157, "tp_from_otringal_to_casino", "Map081_2", 2)
	environment:AddAction(Action_157)

	Action_158 = TeleportAction(158, "tp_from_casino_to_otringal", "OTRINGAL", 13)
	environment:AddAction(Action_158)

	Action_159 = TeleportAction(159, "tp_from_casino_to_casinocrock", "Map079_2", 1)
	environment:AddAction(Action_159)

	Action_160 = TeleportAction(160, "tp_from_casinocrock_to_casino", "Map081_2", 4)
	environment:AddAction(Action_160)

	Action_161 = TeleportAction(161, "tp_from_casinocrock_to_otringal", "OTRINGAL", 16)
	environment:AddAction(Action_161)

	Action_162 = TeleportAction(162, "tp_from_otringal_to_casinocrock", "Map079_2", 2)
	environment:AddAction(Action_162)

	Action_163 = TeleportAction(163, "tp_from_club_to_otringal", "OTRINGAL", 15)
	environment:AddAction(Action_163)

	Action_164 = TeleportAction(164, "tp_from_otringal_to_club", "Map082_2", 1)
	environment:AddAction(Action_164)

	Action_165 = TeleportAction(165, "tp_from_backstage_to_club", "Map082_2", 3)
	environment:AddAction(Action_165)

	Action_166 = TeleportAction(166, "tp_from_club_to_backstage", "Map080_2", 1)
	environment:AddAction(Action_166)

	Action_167 = TeleportAction(167, "tp_from_rick_to_club", "Map082_2", 2)
	environment:AddAction(Action_167)

	Action_168 = TeleportAction(168, "tp_from_club_to_rick", "Map083_2", 1)
	environment:AddAction(Action_168)

	Action_169 = TeleportAction(169, "tp_from_highele_to_otringal", "OTRINGAL", 14)
	environment:AddAction(Action_169)

	Action_170 = TeleportAction(170, "tp_from_otringal_to_highele", "Map095_2", 1)
	environment:AddAction(Action_170)

	Action_171 = TeleportAction(171, "leftup", "Map095_2", 2)
	environment:AddAction(Action_171)

	Action_172 = TeleportAction(172, "right", "Map095_2", 4)
	environment:AddAction(Action_172)

	Action_173 = TeleportAction(173, "tp_from_highele_to_otrright", "OTRINGAL", 18)
	environment:AddAction(Action_173)

	Action_174 = TeleportAction(174, "tp_from_otringal_to_higheleright", "Map095_2", 6)
	environment:AddAction(Action_174)

	Action_175 = TeleportAction(175, "tp_from_highele_to_otrleft", "OTRINGAL", 17)
	environment:AddAction(Action_175)

	Action_176 = TeleportAction(176, "tp_from_otringal_to_higheleleft", "Map095_2", 5)
	environment:AddAction(Action_176)

	Action_177 = TeleportAction(177, "tp_from_royalshuttle_to_otringal", "OTRINGAL", 21)
	environment:AddAction(Action_177)

	Action_178 = TeleportAction(178, "tp_from_otringal_to_royalshuttle", "Map127_2", 1)
	environment:AddAction(Action_178)

	Action_179 = TeleportAction(179, "tp_from_gate_to_otr", "OTRINGAL", 22)
	environment:AddAction(Action_179)

	Action_180 = TeleportAction(180, "tp_from_otr_to_gate", "OTRINGAL", 23)
	environment:AddAction(Action_180)

	Action_181 = TeleportAction(181, "expandexit", "OTRINGAL", 24)
	environment:AddAction(Action_181)

	Action_182 = TeleportAction(182, "expandentrance", "OTRINGAL", 25)
	environment:AddAction(Action_182)

	Action_183 = TeleportAction(183, "tp_from_insanity_to_otringal", "OTRINGAL", 26)
	environment:AddAction(Action_183)

	Action_184 = TeleportAction(184, "tp_from_otringal_to_insanity", "Map099_2", 1)
	environment:AddAction(Action_184)

	Action_185 = TeleportAction(185, "tp_from_4_to_3", "Map098_2", 3)
	environment:AddAction(Action_185)

	Action_186 = TeleportAction(186, "tp_from_4_to_8", "Map103_2", 2)
	environment:AddAction(Action_186)

	Action_187 = TeleportAction(187, "tp_from_3_to_2", "Map097_2", 3)
	environment:AddAction(Action_187)

	Action_188 = TeleportAction(188, "tp_from_3_to_7", "Map102_2", 3)
	environment:AddAction(Action_188)

	Action_189 = TeleportAction(189, "tp_from_3_to_4", "Map099_2", 2)
	environment:AddAction(Action_189)

	Action_190 = TeleportAction(190, "tp_from_2_to_3", "Map098_2", 1)
	environment:AddAction(Action_190)

	Action_191 = TeleportAction(191, "tp_from_2_to_1", "Map096_2", 1)
	environment:AddAction(Action_191)

	Action_192 = TeleportAction(192, "tp_from_2_to_6", "Map101_2", 4)
	environment:AddAction(Action_192)

	Action_193 = TeleportAction(193, "tp_from_1_to_2", "Map097_2", 1)
	environment:AddAction(Action_193)

	Action_194 = TeleportAction(194, "tp_from_1_to_5", "Map100_2", 2)
	environment:AddAction(Action_194)

	Action_195 = TeleportAction(195, "tp_from_8_to_4", "Map099_2", 3)
	environment:AddAction(Action_195)

	Action_196 = TeleportAction(196, "tp_from_8_to_7", "Map102_2", 4)
	environment:AddAction(Action_196)

	Action_197 = TeleportAction(197, "tp_from_7_to_8", "Map103_2", 1)
	environment:AddAction(Action_197)

	Action_198 = TeleportAction(198, "tp_from_7_to_3", "Map098_2", 2)
	environment:AddAction(Action_198)

	Action_199 = TeleportAction(199, "tp_from_7_to_6", "Map101_2", 3)
	environment:AddAction(Action_199)

	Action_200 = TeleportAction(200, "tp_from_6_to_7", "Map102_2", 1)
	environment:AddAction(Action_200)

	Action_201 = TeleportAction(201, "tp_from_6_to_2", "Map097_2", 2)
	environment:AddAction(Action_201)

	Action_202 = TeleportAction(202, "tp_from_6_to_5", "Map100_2", 1)
	environment:AddAction(Action_202)

	Action_203 = TeleportAction(203, "tp_from_5_to_6", "Map101_2", 1)
	environment:AddAction(Action_203)

	Action_204 = TeleportAction(204, "tp_from_5_to_1", "Map096_2", 2)
	environment:AddAction(Action_204)

	Action_205 = TeleportAction(205, "tp_from_8_to_12", "Map107_2", 3)
	environment:AddAction(Action_205)

	Action_206 = TeleportAction(206, "tp_from_7_to_11", "Map106_2", 4)
	environment:AddAction(Action_206)

	Action_207 = TeleportAction(207, "tp_from_6_to_10", "Map105_2", 4)
	environment:AddAction(Action_207)

	Action_208 = TeleportAction(208, "tp_from_5_to_9", "Map104_2", 1)
	environment:AddAction(Action_208)

	Action_209 = TeleportAction(209, "tp_from_9_to_5", "Map100_2", 3)
	environment:AddAction(Action_209)

	Action_210 = TeleportAction(210, "tp_from_9_to_10", "Map105_2", 1)
	environment:AddAction(Action_210)

	Action_211 = TeleportAction(211, "tp_from_10_to_9", "Map104_2", 2)
	environment:AddAction(Action_211)

	Action_212 = TeleportAction(212, "tp_from_10_to_6", "Map101_2", 2)
	environment:AddAction(Action_212)

	Action_213 = TeleportAction(213, "tp_from_10_to_11", "Map106_2", 1)
	environment:AddAction(Action_213)

	Action_214 = TeleportAction(214, "tp_from_11_to_10", "Map105_2", 3)
	environment:AddAction(Action_214)

	Action_215 = TeleportAction(215, "tp_from_11_to_7", "Map102_2", 2)
	environment:AddAction(Action_215)

	Action_216 = TeleportAction(216, "tp_from_11_to_12", "Map107_2", 1)
	environment:AddAction(Action_216)

	Action_217 = TeleportAction(217, "tp_from_12_to_8", "Map103_2", 3)
	environment:AddAction(Action_217)

	Action_218 = TeleportAction(218, "tp_from_12_to_11", "Map106_2", 3)
	environment:AddAction(Action_218)

	Action_219 = TeleportAction(219, "tp_from_12_to_16", "Map111_2", 2)
	environment:AddAction(Action_219)

	Action_220 = TeleportAction(220, "tp_from_16_to_12", "Map107_2", 2)
	environment:AddAction(Action_220)

	Action_221 = TeleportAction(221, "tp_from_16_to_15", "Map110_2", 3)
	environment:AddAction(Action_221)

	Action_222 = TeleportAction(222, "tp_from_11_to_15", "Map110_2", 2)
	environment:AddAction(Action_222)

	Action_223 = TeleportAction(223, "tp_from_15_to_11", "Map106_2", 2)
	environment:AddAction(Action_223)

	Action_224 = TeleportAction(224, "tp_from_15_to_16", "Map111_2", 1)
	environment:AddAction(Action_224)

	Action_225 = TeleportAction(225, "tp_from_15_to_14", "Map109_2", 3)
	environment:AddAction(Action_225)

	Action_226 = TeleportAction(226, "tp_from_10_to_14", "Map109_2", 2)
	environment:AddAction(Action_226)

	Action_227 = TeleportAction(227, "tp_from_14_to_10", "Map105_2", 2)
	environment:AddAction(Action_227)

	Action_228 = TeleportAction(228, "tp_from_14_to_15", "Map110_2", 1)
	environment:AddAction(Action_228)

	Action_229 = TeleportAction(229, "tp_from_14_to_13", "Map108_2", 3)
	environment:AddAction(Action_229)

	Action_230 = TeleportAction(230, "tp_from_9_to_13", "Map108_2", 1)
	environment:AddAction(Action_230)

	Action_231 = TeleportAction(231, "tp_from_13_to_9", "Map104_2", 3)
	environment:AddAction(Action_231)

	Action_232 = TeleportAction(232, "tp_from_13_to_14", "Map109_2", 1)
	environment:AddAction(Action_232)

	Action_233 = TeleportAction(233, "tp_from_biggie_to_13", "Map108_2", 2)
	environment:AddAction(Action_233)

	Action_234 = TeleportAction(234, "tp_from_13_to_biggie", "Map049_2", 1)
	environment:AddAction(Action_234)

	Action_235 = TeleportAction(235, "tp_from_hotel3_to_hotel", "Map050_2", 5)
	environment:AddAction(Action_235)

	Action_236 = TeleportAction(236, "tp_from_hotel_to_hotel3", "Map048_2", 1)
	environment:AddAction(Action_236)

	Action_237 = TeleportAction(237, "to_from_hotel1_to_hotel", "Map050_2", 3)
	environment:AddAction(Action_237)

	Action_238 = TeleportAction(238, "tp_from_hotel_to_hotel1", "Map114_2", 1)
	environment:AddAction(Action_238)

	Action_239 = TeleportAction(239, "tp_from_hotel2_to_hotel", "Map050_2", 4)
	environment:AddAction(Action_239)

	Action_240 = TeleportAction(240, "tp_from_hotel_to_hotel2", "Map115_2", 1)
	environment:AddAction(Action_240)

	Action_241 = TeleportAction(241, "tp_from_citadel_to_museum_window", "Map016_2", 1)
	environment:AddAction(Action_241)

	Action_242 = ClientScriptAction(242, "climb_museum_window_outside", 1)
	environment:AddAction(Action_242)

	Action_243 = TeleportAction(243, "tp_from_museum_to_cita_window", "CITABAU", 16)
	environment:AddAction(Action_243)

	Action_244 = ClientScriptAction(244, "sc_exitup_window_from_museum", 2)
	environment:AddAction(Action_244)

end
