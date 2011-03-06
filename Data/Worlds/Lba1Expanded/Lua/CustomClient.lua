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



-- Player to use trash truck close to citadel prison
function UseTrashTruck(ScriptId, Environment)

	ArrivalPos = LbaVec3(53.5, 8, 13.5)
	ActorRotateAndMoveForwardTo(ScriptId, -1, ArrivalPos, 0.15, Environment)
	
	
	-- add rotation
	Environment:ActorRotate(ScriptId, -1, 0, 0.15, true)
	
	-- change animation
	Environment:UpdateActorAnimation(-1, "DoAction")
	Environment:ActorAnimate(ScriptId, -1, true)	
	
	-- wait for truck
	Environment:ActorWaitForSignal(ScriptId, -1, 20)
	
	-- hide in truck and attach to truck
	Environment:ActorShowHide(-1, false)
	Environment:AttachActor(-1, 1, 16)
	
	
	-- wait for truck to move
	Environment:ActorWaitForSignal(ScriptId, -1, 30)
	
	--detach from truck
	Environment:DettachActor(-1, 16)
	
	--show player
	TeleportPos = LbaVec3(5.8, 8, 43.6)	
	Environment:TeleportActorTo(ScriptId, -1, TeleportPos)		
	Environment:ActorShowHide(-1, true)	
end