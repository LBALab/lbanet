function ActorRotateAndMoveForwardTo(ScriptId, ActorId, ArrivalPosition, RotationSpeed, Environment)
	
	-- get current position
	CurrentPosition = Environment:GetActorPosition(ActorId)	
	
	-- calculate rotation angle
	TDistance = LbaVec3(ArrivalPosition)
	TDistance.x = TDistance.x - CurrentPosition.x
	TDistance.z = TDistance.z - CurrentPosition.z
	angle = LbaQuaternion.GetAngleFromVector(TDistance)

	
	-- add first rotation	
	Environment:ActorRotate(ScriptId, ActorId, angle, RotationSpeed, true)
	
	
	-- add translation
	Environment:UpdateActorAnimation(ActorId, "MoveForward")	
	Environment:ActorStraightWalkTo(ScriptId, ActorId, ArrivalPosition)
end



function ActorGoUpLadder(ScriptId, ActorId, LadderPosition, LadderHeight, LadderDirection, Environment)
	
	-- fix fall down when arrive
	LadderHeight = LadderHeight + 1
	
	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)

	-- change actor mode to normal
	Environment:UpdateActorMode(ActorId, "Normal")

	-- get current position
	CurrentPosition = Environment:GetActorPosition(ActorId)
	
	-- calculate offsets depending of ladder direction
	remX=0
	remZ=0
	dX=0
	dZ=0
	
	if (LadderDirection >= 45) then	
		if (LadderDirection >= 135) then
			if (LadderDirection >= 225) then
				if (LadderDirection >= 315) then
					remZ = -0.8
					dZ = 1
				else
					remX = 0.8
					dX = -1
				end			
			else
				remZ = 0.8
				dZ = -1
			end
		else
			remX = -0.8
			dX = 1
		end
	else
		remZ = -0.8
		dZ = 1
	end
	

	-- calculate position and rotation actor need to proceed to
	TranslationPosition = LbaVec3(LadderPosition)
	TranslationPosition.x = TranslationPosition.x + remX
	TranslationPosition.z = TranslationPosition.z + remZ
	
	
	-- go to ladder
	ActorRotateAndMoveForwardTo(ScriptId, ActorId, TranslationPosition, 0.15, Environment)	
	
	
	
	-- add rotation before climbing
	Environment:ActorRotate(ScriptId, ActorId, LadderDirection, 0.15, true)
	
	
	-- add translation up the ladder
	if(LadderHeight > 4.7) then
		Environment:UpdateActorAnimation(ActorId, "GoUpLadder")
		TranslationPosition = LbaVec3(LadderPosition)
		TranslationPosition.x = TranslationPosition.x +remX
		TranslationPosition.y = TranslationPosition.y +LadderHeight - 4.7
		TranslationPosition.z = TranslationPosition.z +remZ
		Environment:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)
	end


	-- add action up the ladder
	Environment:UpdateActorAnimation(ActorId, "ArriveLadder")
	Environment:ActorAnimate(ScriptId, ActorId, true)


	-- add translation to exit the ladder
	Environment:UpdateActorAnimation(ActorId, "MoveForward")
	TranslationPosition = LbaVec3(LadderPosition)
	TranslationPosition.x = TranslationPosition.x +remX + dX
	TranslationPosition.y = TranslationPosition.y +LadderHeight + 0.1	
	TranslationPosition.z = TranslationPosition.z +remZ + dZ	
	Environment:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)	

end


function TakeExitUp(ScriptId, ActorId, ExitPosition, ExitDirection, Environment)

	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)
	
	-- change actor mode to normal
	Environment:UpdateActorMode(ActorId, "Normal")

	-- get current position
	CurrentPosition = Environment:GetActorPosition(ActorId)
	
	-- calculate offsets depending of ladder direction
	remX=0
	remZ=0
	dX=0
	dZ=0
	
	if (ExitDirection >= 45) then	
		if (ExitDirection >= 135) then
			if (ExitDirection >= 225) then
				if (ExitDirection >= 315) then
					remZ = -0.8
					dZ = 0.5
				else
					remX = 0.8
					dX = -0.5
				end			
			else
				remZ = 0.8
				dZ = -0.5
			end
		else
			remX = -0.8
			dX = 0.5
		end
	else
		remZ = -0.8
		dZ = 0.5
	end
	

	-- calculate position and rotation actor need to proceed to
	TranslationPosition = LbaVec3(ExitPosition)
	TranslationPosition.x = TranslationPosition.x + remX
	TranslationPosition.z = TranslationPosition.z + remZ
	
	
	-- go to exit
	ActorRotateAndMoveForwardTo(ScriptId, ActorId, TranslationPosition, 0.15, Environment)	
	
	
	-- add rotation before climbing
	Environment:ActorRotate(ScriptId, ActorId, ExitDirection, 0.15, true)
	

	-- add exit animation
	Environment:UpdateActorAnimation(ActorId, "Climb")
	Environment:ActorAnimate(ScriptId, ActorId, true)
	
	-- go up to activate trigger
	NewPosition = Environment:GetActorPosition(ActorId)
	NewPosition.x = NewPosition.x - remX
	NewPosition.y = NewPosition.y + 2.5
	NewPosition.z = NewPosition.z - remZ
	Environment:TeleportActorTo(ScriptId, ActorId, NewPosition)


end



function TakeExitDown(ScriptId, ActorId, ExitPosition, ExitDirection, Environment)

	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)
	
	-- change actor mode to normal
	Environment:UpdateActorMode(ActorId, "Normal")

	-- get current position
	CurrentPosition = Environment:GetActorPosition(ActorId)
	
	-- calculate offsets depending of ladder direction
	remX=0
	remZ=0
	dX=0
	dZ=0
	
	if (ExitDirection >= 45) then	
		if (ExitDirection >= 135) then
			if (ExitDirection >= 225) then
				if (ExitDirection >= 315) then
					remZ = -0.8
					dZ = 1
				else
					remX = 0.8
					dX = -1
				end			
			else
				remZ = 0.8
				dZ = -1
			end
		else
			remX = -0.8
			dX = 1
		end
	else
		remZ = -0.8
		dZ = 1
	end
	

	-- calculate position and rotation actor need to proceed to
	TranslationPosition = LbaVec3(ExitPosition)
	TranslationPosition.x = TranslationPosition.x + remX
	TranslationPosition.z = TranslationPosition.z + remZ
	
	
	-- go to exit
	ActorRotateAndMoveForwardTo(ScriptId, ActorId, TranslationPosition, 0.15, Environment)		
	
	
	-- add rotation before climbing
	Environment:ActorRotate(ScriptId, ActorId, ExitDirection, 0.15, true)
	

	-- add exit animation
	Environment:UpdateActorAnimation(ActorId, "Crawl")
	Environment:ActorAnimate(ScriptId, ActorId, true)
	Environment:ActorAnimate(ScriptId, ActorId, true)
	Environment:ActorAnimate(ScriptId, ActorId, true)
	Environment:ActorAnimate(ScriptId, ActorId, true)	
	Environment:ActorAnimate(ScriptId, ActorId, true)	
end