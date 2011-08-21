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
	Environment:UpdateActorAnimation(ScriptId, -1, "DoAction")
	Environment:ActorAnimate(ScriptId, -1, true)	
	
	-- wait for truck
	Environment:ActorWaitForSignal(ScriptId, -1, 20)
	
	-- hide in truck and attach to truck
	Environment:ActorShowHide(ScriptId, -1, false)
	Environment:AttachActor(-1, 1, 16)
	
	
	-- wait for truck to move
	Environment:ActorWaitForSignal(ScriptId, -1, 30)
	
	--detach from truck
	Environment:DettachActor(-1, 16)
	
	--show player
	TeleportPos = LbaVec3(5.8, 8, 43.6)	
	Environment:TeleportActorTo(ScriptId, -1, TeleportPos)		
	Environment:ActorShowHide(ScriptId, -1, true)	
end


function PlayStartSequence(ScriptId, Environment)

	Environment:StartDisplayExtraScreen(ScriptId)
	
	vec1 = LbaVecLong()
	vec1:Add(1091)
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


function PlayBoat(ScriptId, Environment)

	Environment:StartDisplayExtraScreen(ScriptId)
	
	if(math.random() > 0.5) then
		Environment:PlayClientVideo(ScriptId, "Worlds/Lba1Original/Video/BATEAU.avi")
	else
		Environment:PlayClientVideo(ScriptId, "Worlds/Lba1Original/Video/BATEAU2.avi")	
	end
	
	Environment:EndDisplayExtraScreen()
end


-- Player to use trash truck close to citadel prison
function UseBoatCitadelToPrincipal(ScriptId, Environment)

	-- hide in truck and attach to truck
	Environment:ActorShowHide(ScriptId, -1, false)
	Environment:AttachActor(-1, 1, 10)
	
	
	-- get current position
	CurrentPosition = Environment:GetActorPosition(ScriptId, 10)

	
	P0 = LbaVec3(18.4,0,36.2)	
	P1 = LbaVec3(10.7,0,36.3)	
	P2 = LbaVec3(11.1,0,47.2)
	
	P3 = LbaVec3(10.6,0,40)
	P4 = LbaVec3(10,0,30)
	P5 = LbaVec3(1,0,27)	
	
	Environment:UpdateActorAnimation(ScriptId, 10, "MoveBackward")
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, CurrentPosition, CurrentPosition, CurrentPosition, P0, P1, P2)
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, CurrentPosition, CurrentPosition, P0, P1, P2, P2)
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, CurrentPosition, P0, P1, P2, P2, P2)
	
	Environment:UpdateActorAnimation(ScriptId, 10, "MoveForward")	
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, P2, P2, P2, P3, P4, P5)
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, P2, P2, P3, P4, P5, P5)
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, P2, P3, P4, P5, P5, P5)
	
	Environment:TeleportPlayerAtEndScript(ScriptId, "Map011_1", 8)
	PlayBoat(ScriptId, Environment)
end

-- Player to use trash truck close to citadel prison
function UseBoatCitadelFromPrincipal(ScriptId, Environment)

	CurrentPosition = LbaVec3(1,0,27)

	-- hide in truck and attach to truck
	Environment:ActorShowHide(ScriptId, -1, false)
	Environment:TeleportActorTo(ScriptId, -1, CurrentPosition)
	Environment:TeleportActorTo(ScriptId, 10, CurrentPosition)		
	Environment:AttachActor(-1, 1, 10)

	P0 = LbaVec3(3,0,29)	
	P1 = LbaVec3(8,0,34)	
	P2 = LbaVec3(21,0,36.4)
	

	
	Environment:UpdateActorAnimation(ScriptId, 10, "MoveForward")
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, CurrentPosition, CurrentPosition, CurrentPosition, P0, P1, P2)
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, CurrentPosition, CurrentPosition, P0, P1, P2, P2)
	Environment:ActorFollowGivenWaypoint(ScriptId, 10, CurrentPosition, P0, P1, P2, P2, P2)

	
	--detach from boat
	Environment:DettachActor(-1, 10)
	
	--show player
	TeleportPos = LbaVec3(21, 4, 40)	
	Environment:TeleportActorTo(ScriptId, -1, TeleportPos)		
	Environment:ActorShowHide(ScriptId, -1, true)	
end


-- Player to use trash truck close to citadel prison
function UseBoatPrincipalToCitadel(ScriptId, Environment)

	-- hide in truck and attach to truck
	Environment:ActorShowHide(ScriptId, -1, false)
	Environment:AttachActor(-1, 1, 25)
	
	-- get current position
	P0 = LbaVec3(31,0,33)	
	P1 = LbaVec3(31,0,64)
	
	Environment:UpdateActorAnimation(ScriptId, 25, "MoveForward")		
	Environment:ActorGoTo(ScriptId, 25, P0, 0.0012);
	Environment:ActorGoTo(ScriptId, 25, P1, 0.0025);
	
	Environment:TeleportPlayerAtEndScript(ScriptId, "Map006_1", 7)
	PlayBoat(ScriptId, Environment)
end


-- Player to use trash truck close to citadel prison
function UseBoatPrincipalFromCitadel(ScriptId, Environment)

	CurrentPosition = LbaVec3(31,0,64)

	-- hide in truck and attach to truck
	Environment:ActorShowHide(ScriptId, -1, false)
	Environment:TeleportActorTo(ScriptId, -1, CurrentPosition)
	Environment:TeleportActorTo(ScriptId, 25, CurrentPosition)		
	Environment:AttachActor(-1, 1, 25)

		
	P0 = LbaVec3(34.5,0,57)	
	P1 = LbaVec3(28,0,54)		
	P2 = LbaVec3(25,0,53)	
	
	P3 = LbaVec3(27,0,53)
	P4 = LbaVec3(29,0,43)
	P5 = LbaVec3(28,0,33)	
	
	EndPos = LbaVec3(37, 0, 33)
	
	
	Environment:UpdateActorAnimation(ScriptId, 25, "MoveForward")
	Environment:ActorFollowGivenWaypoint(ScriptId, 25, CurrentPosition, CurrentPosition, CurrentPosition, P0, P1, P2)
	Environment:ActorFollowGivenWaypoint(ScriptId, 25, CurrentPosition, CurrentPosition, P0, P1, P2, P2)
	Environment:ActorFollowGivenWaypoint(ScriptId, 25, CurrentPosition, P0, P1, P2, P2, P2)	
	
	Environment:UpdateActorAnimation(ScriptId, 25, "MoveBackward")
	Environment:ActorFollowGivenWaypoint(ScriptId, 25, P2, P2, P2, P3, P4, P5)
	Environment:ActorFollowGivenWaypoint(ScriptId, 25, P2, P2, P3, P4, P5, P5)
	Environment:ActorFollowGivenWaypoint(ScriptId, 25, P2, P3, P4, P5, P5, P5)
	
	Environment:UpdateActorAnimation(ScriptId, 25, "MoveForward")		
	Environment:ActorGoTo(ScriptId, 25, EndPos, 0.0012);
	
	
	--detach from boat
	Environment:DettachActor(-1, 25)
	
	--show player
	TeleportPos = LbaVec3(41, 4, 37)	
	Environment:TeleportActorTo(ScriptId, -1, TeleportPos)		
	Environment:ActorShowHide(ScriptId, -1, true)	
end