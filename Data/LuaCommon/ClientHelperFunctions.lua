function ActorRotateAndMoveForwardTo(ScriptId, ActorId, ArrivalPosition, RotationSpeed, Environment)
		
	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)
	
	-- get current position
	CurrentPosition = Environment:GetActorPosition(ScriptId, ActorId)	
	
	-- calculate rotation angle
	TDistance = LbaVec3(ArrivalPosition)
	TDistance.x = TDistance.x - CurrentPosition.x
	TDistance.z = TDistance.z - CurrentPosition.z
	angle = LbaQuaternion.GetAngleFromVector(TDistance)

	
	-- add first rotation	
	Environment:ActorRotate(ScriptId, ActorId, angle, RotationSpeed, true)
	
	
	-- add translation
	Environment:UpdateActorAnimation(ScriptId, ActorId, "MoveForward")	
	Environment:ActorStraightWalkTo(ScriptId, ActorId, ArrivalPosition)
end



function ActorGoUpLadder(ScriptId, ActorId, LadderPosition, LadderHeight, LadderDirection, Environment)
	
	-- fix fall down when arrive
	LadderHeight = LadderHeight + 1
	
	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)

	-- change actor mode to normal
	Environment:UpdateActorMode(ScriptId, ActorId, "Normal")

	-- get current position
	CurrentPosition = Environment:GetActorPosition(ScriptId, ActorId)
	
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
		Environment:UpdateActorAnimation(ScriptId, ActorId, "GoUpLadder")
		TranslationPosition = LbaVec3(LadderPosition)
		TranslationPosition.x = TranslationPosition.x +remX
		TranslationPosition.y = TranslationPosition.y +LadderHeight - 4.7
		TranslationPosition.z = TranslationPosition.z +remZ
		Environment:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)
	end


	-- add action up the ladder
	Environment:UpdateActorAnimation(ScriptId, ActorId, "ArriveLadder")
	Environment:ActorAnimate(ScriptId, ActorId, true)


	-- add translation to exit the ladder
	Environment:UpdateActorAnimation(ScriptId, ActorId, "MoveForward")
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
	Environment:UpdateActorMode(ScriptId, ActorId, "Normal")

	-- get current position
	CurrentPosition = Environment:GetActorPosition(ScriptId, ActorId)
	
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
	Environment:UpdateActorAnimation(ScriptId, ActorId, "Climb")
	Environment:ActorAnimate(ScriptId, ActorId, true)
	
	-- go up to activate trigger
	NewPosition = Environment:GetActorPosition(ScriptId, ActorId)
	NewPosition.x = NewPosition.x - remX
	NewPosition.y = NewPosition.y + 2.5
	NewPosition.z = NewPosition.z - remZ
	Environment:TeleportActorTo(ScriptId, ActorId, NewPosition)


end



function TakeExitDown(ScriptId, ActorId, ExitPosition, ExitDirection, Environment)

	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)
	
	-- change actor mode to normal
	Environment:UpdateActorMode(ScriptId, ActorId, "Normal")

	-- get current position
	CurrentPosition = Environment:GetActorPosition(ScriptId, ActorId)
	
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
	Environment:UpdateActorAnimation(ScriptId, ActorId, "Crawl")
	Environment:ActorAnimate(ScriptId, ActorId, true)
	Environment:ActorAnimate(ScriptId, ActorId, true)
	Environment:ActorAnimate(ScriptId, ActorId, true)
	Environment:ActorAnimate(ScriptId, ActorId, true)	
	Environment:ActorAnimate(ScriptId, ActorId, true)	
end


-- go to player and attack him with contact weapon
function ActorAttackContactPlayer(ScriptId, ActorId, Environment)

	TargetedPlayer = Environment:GetTargettedAttackPlayer(ActorId)
	if TargetedPlayer > -1 then
		weaponrange = Environment:GetNpcWeaponReachDistance(ActorId, 1)
	
		tinrange = Environment:IsTargetInRange(weaponrange, ActorId)
		if tinrange == false then
			-- follow player until we reach him
			Environment:FollowTargettedPlayer(ScriptId, ActorId, weaponrange)
		else
			rotationdiff = Environment:GetTargetRotationDiff(ActorId)
			if math.abs(rotationdiff) > 5 then
				-- rotate to face player
				Environment:RotateToTargettedPlayer(ScriptId, ActorId, 4.9, 0.2)	
			else
				-- attack player
				Environment:UseWeapon(ScriptId, ActorId, 1)
			end
		end
	end
end


-- go to player and attack him with contact weapon
function ActorFollowAttackDistancePlayer(ScriptId, ActorId, Environment)

	-- if Environment:CanPlayAnimation(1, ActorId, "PrepareWeapon") then
	--	Environment:UpdateActorAnimation(ActorId, "PrepareWeapon")
	--	Environment:ActorAnimate(ScriptId, ActorId, true)
	-- end
	
	TargetedPlayer = Environment:GetTargettedAttackPlayer(ActorId)
	if TargetedPlayer > -1 then
		weaponrange = Environment:GetNpcWeaponReachDistance(ActorId, 2)
	
		tinrange = Environment:IsTargetInRange(weaponrange, ActorId)
		if tinrange == false then
			-- follow player until we reach him
			Environment:FollowTargettedPlayer(ScriptId, ActorId, weaponrange)
		else
			rotationdiff = Environment:GetTargetRotationDiff(ActorId)
			if math.abs(rotationdiff) > 3 then
				-- rotate to face player
				Environment:RotateToTargettedPlayer(ScriptId, ActorId, 2.9, 0.2)	
			else
				-- attack player
				Environment:StartUseWeapon(ScriptId, ActorId, 2)
			end
		end
	end
end

-- go to player and attack him with contact weapon
function ActorRotateAttackDistancePlayer(ScriptId, ActorId, Environment)

	-- if Environment:CanPlayAnimation(1, ActorId, "PrepareWeapon") then
	--	Environment:UpdateActorAnimation(ScriptId, ActorId, "PrepareWeapon")
	--	Environment:ActorAnimate(ScriptId, ActorId, true)
	-- end

	TargetedPlayer = Environment:GetTargettedAttackPlayer(ActorId)
	if TargetedPlayer > -1 then

		rotationdiff = Environment:GetTargetRotationDiff(ActorId)
		if math.abs(rotationdiff) > 2 then
			-- rotate to face player
			Environment:RotateToTargettedPlayer(ScriptId, ActorId, 1.9, 0.2)	
		else		
			-- attack player contact
			Environment:StartUseWeapon(ScriptId, ActorId, 2)

		end
	end
end

-- go to player and attack him with contact weapon
function ActorRotateAttackDistanceAndContactPlayer(ScriptId, ActorId, Environment)

	-- if Environment:CanPlayAnimation(1, ActorId, "PrepareWeapon") then
	--	Environment:UpdateActorAnimation(ScriptId, ActorId, "PrepareWeapon")
	--	Environment:ActorAnimate(ScriptId, ActorId, true)
	-- end

	TargetedPlayer = Environment:GetTargettedAttackPlayer(ActorId)
	if TargetedPlayer > -1 then
		weaponrange1 = Environment:GetNpcWeaponReachDistance(ActorId, 1)

		rotationdiff = Environment:GetTargetRotationDiff(ActorId)
		if math.abs(rotationdiff) > 2 then
			-- rotate to face player
			Environment:RotateToTargettedPlayer(ScriptId, ActorId, 1.9, 0.2)	
		else
		
			tinrange = Environment:IsTargetInRange(weaponrange1, ActorId)
			if tinrange == true then		
				-- attack player contact
				Environment:StartUseWeapon(ScriptId, ActorId, 1)
			else
				-- attack player distance
				Environment:StartUseWeapon(ScriptId, ActorId, 2)	
			end
		end
	end
end