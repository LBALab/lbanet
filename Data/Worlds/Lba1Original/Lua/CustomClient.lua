-- In this file you can define custom functions to be used on the client side.
-- It is typically used to define custom client script functions.

-- Please note that the changes done on this file will
-- only be reflected once you click the "Refresh client script" in the top menu of the editor!


-- A function used as custom clientscript should have the following signature:
-- Function Functioname(ScriptId)

-- ScriptId is used by many functions of the client API (see documentation for further information on the API)
-- Environment is a pointer used to access the server class (see documentation for further information)

function ExampleClientFct(ScriptId, Environment)

	LadderPos = LbaVec3(42, 7, 9)
	ActorGoUpLadder(ScriptId, -1, LadderPos, 10, 0, Environment)
	
end


function PlayStartSequence(ScriptId, Environment)

	Environment:StartDisplayExtraScreen(ScriptId)
	
	vec1 = LbaVecLong()
	vec1:Add(1041)
	Environment:DisplayScrollingText(ScriptId, "", vec1, " ")
	
	fadeinC = LbaColor(1, 1, 1, 1)
	fadeoutC = LbaColor(0, 0, 0, 1)	
	Environment:DisplayImage(ScriptId, "Worlds/Lba1Original/Video/Adelinescreen.png", 6, true, fadeinC, true, fadeoutC, "Worlds/Lba1Original/Music/Midi_mi_win31.midi")

	Environment:DisplayImage(ScriptId, "Worlds/Lba1Original/Video/lba1title.gif", 5, true, fadeoutC, true, fadeoutC, " ")
	
	Environment:DisplayImage(ScriptId, "Worlds/Lba1Original/Video/EAscreen.png", 5, true, fadeoutC, true, fadeoutC, " ")
	
	Environment:PlayClientVideo(ScriptId, "Worlds/Lba1Original/Video/DRAGON3.avi")
	
	Environment:EndDisplayExtraScreen()
end


function PlayIntro(ScriptId, Environment)

	Environment:StartDisplayExtraScreen(ScriptId)
	
	vec1 = LbaVecLong()
	vec1:Add(135)
	Environment:DisplayScrollingText(ScriptId, "Worlds/Lba1Original/Video/lba1twinsun.gif", vec1, " ")
	
	vec2 = LbaVecLong()
	vec2:Add(136)
	Environment:DisplayScrollingText(ScriptId, "Worlds/Lba1Original/Video/lba1fortress.gif", vec2, " ")
	
	vec3 = LbaVecLong()
	vec3:Add(137)		
	Environment:DisplayScrollingText(ScriptId, "Worlds/Lba1Original/Video/lba1islands.gif", vec3, " ")
	
	
	Environment:PlayClientVideo(ScriptId, "Worlds/Lba1Original/Video/INTROD.avi")
	
	Environment:EndDisplayExtraScreen()
end