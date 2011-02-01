-- In this file you can define custom functions to be used on the client side.
-- It is typically used to define custom client script functions.

-- Please note that the changes done on this file will
-- only be reflected once you click the "Refresh client script" in the top menu of the editor!


-- A function used as custom clientscript should have the following signature:
-- Function Functioname(ScriptId)

-- ScriptId is used by many functions of the client API (see documentation for further information on the API)


function ExampleClientFct(ScriptId)

	LadderPos = LbaVec3(42, 7, 9)
	ActorGoUpLadder(ScriptId, -1, LadderPos, 10, 0)
	
end