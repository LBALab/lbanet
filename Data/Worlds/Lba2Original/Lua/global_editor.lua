function InitEditor(environment)
	Script_1 = TakeExitUpScript(1, "exitup_window_to_museum", 488.8, 10, 536.6, 0)
	environment:EditorAddClientScript(Script_1)

	Script_2 = TakeExitUpScript(2, "exitup_window_frommuseum", 25, 9, 25, 180)
	environment:EditorAddClientScript(Script_2)

end
