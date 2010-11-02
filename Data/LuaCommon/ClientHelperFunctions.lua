function ActorGoUpLadder(ScriptId, ActorId, LadderPosition, LadderHeight, LadderDirection)

	-- change actor mode to normal
	Model:UpdateActorMode(ActorId, "Normal")

	-- get current position
	CurrentPosition = Model:GetActorPosition(ActorId)
	
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
	
	TDistance = LbaVec3(TranslationPosition)
	TDistance.x = TDistance.x - CurrentPosition.x
	TDistance.z = TDistance.z - CurrentPosition.z
	angle = LbaQuaternion.GetAngleFromVector(TDistance)

	
	-- add first rotation toward ladder position		
	Model:ActorRotate(ScriptId, ActorId, angle, 0.15, true)
	
	
	-- add translation to ladder
	Model:UpdateActorAnimation(ActorId, "MoveForward")	
	Model:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)
	
	
	-- add rotation before climbing
	Model:ActorRotate(ScriptId, ActorId, LadderDirection, 0.15, true)
	
	
	-- add translation up the ladder
	if(LadderHeight > 4.7) then
		Model:UpdateActorAnimation(ActorId, "GoUpLadder")
		TranslationPosition = LbaVec3(LadderPosition)
		TranslationPosition.x = TranslationPosition.x +remX
		TranslationPosition.y = TranslationPosition.y +LadderHeight - 4.7
		TranslationPosition.z = TranslationPosition.z +remZ
		Model:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)
	end


	-- add action up the ladder
	Model:UpdateActorAnimation(ActorId, "ArriveLadder")
	Model:ActorAnimate(ScriptId, ActorId, true)


	-- add translation to exit the ladder
	Model:UpdateActorAnimation(ActorId, "MoveForward")
	TranslationPosition = LbaVec3(LadderPosition)
	TranslationPosition.x = TranslationPosition.x +remX + dX
	TranslationPosition.y = TranslationPosition.y +LadderHeight + 0.1	
	TranslationPosition.z = TranslationPosition.z +remZ + dZ	
	Model:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)	

end


function TakeExitUp(ScriptId, ActorId, ExitPosition, ExitDirection)

	-- change actor mode to normal
	Model:UpdateActorMode(ActorId, "Normal")

	-- get current position
	CurrentPosition = Model:GetActorPosition(ActorId)
	
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
	
	TDistance = LbaVec3(TranslationPosition)
	TDistance.x = TDistance.x - CurrentPosition.x
	TDistance.z = TDistance.z - CurrentPosition.z
	angle = LbaQuaternion.GetAngleFromVector(TDistance)

	
	-- add first rotation toward exit position		
	Model:ActorRotate(ScriptId, ActorId, angle, 0.15, true)
	
	
	-- add translation to exit
	Model:UpdateActorAnimation(ActorId, "MoveForward")	
	Model:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)
	
	
	-- add rotation before climbing
	Model:ActorRotate(ScriptId, ActorId, ExitDirection, 0.15, true)
	

	-- add exit animation
	Model:UpdateActorAnimation(ActorId, "Climb")
	Model:ActorAnimate(ScriptId, ActorId, true)


end



function TakeExitDown(ScriptId, ActorId, ExitPosition, ExitDirection)

	-- change actor mode to normal
	Model:UpdateActorMode(ActorId, "Normal")

	-- get current position
	CurrentPosition = Model:GetActorPosition(ActorId)
	
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
	
	TDistance = LbaVec3(TranslationPosition)
	TDistance.x = TDistance.x - CurrentPosition.x
	TDistance.z = TDistance.z - CurrentPosition.z
	angle = LbaQuaternion.GetAngleFromVector(TDistance)

	
	-- add first rotation toward exit position		
	Model:ActorRotate(ScriptId, ActorId, angle, 0.15, true)
	
	
	-- add translation to exit
	Model:UpdateActorAnimation(ActorId, "MoveForward")	
	Model:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)
	
	
	-- add rotation before climbing
	Model:ActorRotate(ScriptId, ActorId, ExitDirection, 0.15, true)
	

	-- add exit animation
	Model:UpdateActorAnimation(ActorId, "Crawl")
	Model:ActorAnimate(ScriptId, ActorId, true)
	Model:ActorAnimate(ScriptId, ActorId, true)
	Model:ActorAnimate(ScriptId, ActorId, true)
	Model:ActorAnimate(ScriptId, ActorId, true)	
	Model:ActorAnimate(ScriptId, ActorId, true)	
end