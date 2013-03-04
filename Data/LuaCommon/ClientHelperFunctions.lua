function ActorRotateAndMoveForwardTo(ScriptId, ActorId, ArrivalPosition, RotationSpeed, Environment)
		
	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)
	
	-- get current position
	local CurrentPosition = Environment:GetActorPosition(ScriptId, ActorId)	
	
	-- calculate rotation angle
	local TDistance = LbaVec3(ArrivalPosition)
	TDistance.x = TDistance.x - CurrentPosition.x
	TDistance.z = TDistance.z - CurrentPosition.z
	local angle = LbaQuaternion.GetAngleFromVector(TDistance)

	
	-- add first rotation	
	Environment:ActorRotate(ScriptId, ActorId, angle, RotationSpeed, true)
	
	
	-- add translation
	Environment:UpdateActorAnimation(ScriptId, ActorId, "MoveForward")	
	Environment:ActorStraightWalkTo(ScriptId, ActorId, ArrivalPosition)
end



function ActorGoUpLadder(ScriptId, ActorId, LadderPosition, LadderHeight, LadderDirection, Environment)
	
	-- fix fall down when arrive
	local LadderHeight = LadderHeight + 0.1
	
	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)

	-- change actor mode to normal
	Environment:UpdateActorMode(ScriptId, ActorId, "Normal")

	-- get current position
	local CurrentPosition = Environment:GetActorPosition(ScriptId, ActorId)
	
	-- calculate offsets depending of ladder direction
	local remX=0
	local remZ=0
	local dX=0
	local dZ=0
	
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
	local TranslationPosition = LbaVec3(LadderPosition)
	TranslationPosition.x = TranslationPosition.x + remX
	TranslationPosition.z = TranslationPosition.z + remZ
	
	
	-- go to ladder
	ActorRotateAndMoveForwardTo(ScriptId, ActorId, TranslationPosition, 0.15, Environment)	
	
	
	
	-- add rotation before climbing
	Environment:ActorRotate(ScriptId, ActorId, LadderDirection, 0.15, true)
	
	
	-- add translation up the ladder
	if(LadderHeight > 4.7) then
		Environment:UpdateActorAnimation(ScriptId, ActorId, "GoUpLadder")
		local TranslationPosition = LbaVec3(LadderPosition)
		TranslationPosition.x = TranslationPosition.x +remX
		TranslationPosition.y = TranslationPosition.y +LadderHeight - 4.7
		TranslationPosition.z = TranslationPosition.z +remZ
		Environment:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)
	end


	-- add action up the ladder
	Environment:UpdateActorAnimation(ScriptId, ActorId, "ArriveLadder")
	Environment:ActorAnimate(ScriptId, ActorId, true, 1)


	-- add translation to exit the ladder
	Environment:UpdateActorAnimation(ScriptId, ActorId, "MoveForward")
	local TranslationPosition = LbaVec3(LadderPosition)
	TranslationPosition.x = TranslationPosition.x +remX + dX
	TranslationPosition.y = TranslationPosition.y +LadderHeight	
	TranslationPosition.z = TranslationPosition.z +remZ + dZ	
	Environment:ActorStraightWalkTo(ScriptId, ActorId, TranslationPosition)	

end


function TakeExitUp(ScriptId, ActorId, ExitPosition, ExitDirection, Environment)

	-- reserve the actor for the script
	Environment:ReserveActor(ScriptId, ActorId)
	
	-- change actor mode to normal
	Environment:UpdateActorMode(ScriptId, ActorId, "Normal")

	-- get current position
	local CurrentPosition = Environment:GetActorPosition(ScriptId, ActorId)
	
	-- calculate offsets depending of ladder direction
	local remX=0
	local remZ=0
	local dX=0
	local dZ=0
	
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
	local TranslationPosition = LbaVec3(ExitPosition)
	TranslationPosition.x = TranslationPosition.x + remX
	TranslationPosition.z = TranslationPosition.z + remZ
	
	
	-- go to exit
	ActorRotateAndMoveForwardTo(ScriptId, ActorId, TranslationPosition, 0.15, Environment)	
	
	
	-- add rotation before climbing
	Environment:ActorRotate(ScriptId, ActorId, ExitDirection, 0.15, true)
	

	-- add exit animation
	Environment:UpdateActorAnimation(ScriptId, ActorId, "Climb")
	Environment:ActorAnimate(ScriptId, ActorId, true, 1)
	
	-- go up to activate trigger
	local NewPosition = Environment:GetActorPosition(ScriptId, ActorId)
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
	local CurrentPosition = Environment:GetActorPosition(ScriptId, ActorId)
	
	-- calculate offsets depending of ladder direction
	local remX=0
	local remZ=0
	local dX=0
	local dZ=0
	
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
	local TranslationPosition = LbaVec3(ExitPosition)
	TranslationPosition.x = TranslationPosition.x + remX
	TranslationPosition.z = TranslationPosition.z + remZ
	
	
	-- go to exit
	ActorRotateAndMoveForwardTo(ScriptId, ActorId, TranslationPosition, 0.15, Environment)		
	
	
	-- add rotation before climbing
	Environment:ActorRotate(ScriptId, ActorId, ExitDirection, 0.15, true)
	

	-- add exit animation
	Environment:UpdateActorAnimation(ScriptId, ActorId, "Crawl")
	Environment:ActorAnimate(ScriptId, ActorId, true, 5)	
end


-- go to player and attack him with contact weapon
function ActorAttackContactPlayer(ScriptId, ActorId, Environment)

	local TargetedPlayer = Environment:GetTargettedAttackPlayer(ActorId)
	if TargetedPlayer > -1 then
		local weaponrange = Environment:GetNpcWeaponReachDistance(ActorId, 1)
	
		local tinrange = Environment:IsTargetInRange(weaponrange, ActorId)
		if tinrange == false then
			-- follow player until we reach him
			Environment:FollowTargettedPlayer(ScriptId, ActorId, weaponrange)
		else
			local rotationdiff = Environment:GetTargetRotationDiff(ActorId)
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
	--	Environment:ActorAnimate(ScriptId, ActorId, true, 1)
	-- end
	
	local TargetedPlayer = Environment:GetTargettedAttackPlayer(ActorId)
	if TargetedPlayer > -1 then
		local weaponrange = Environment:GetNpcWeaponReachDistance(ActorId, 2)
	
		local tinrange = Environment:IsTargetInRange(weaponrange, ActorId)
		if tinrange == false then
			-- follow player until we reach him
			Environment:FollowTargettedPlayer(ScriptId, ActorId, weaponrange)
		else
			local rotationdiff = Environment:GetTargetRotationDiff(ActorId)
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
	--	Environment:ActorAnimate(ScriptId, ActorId, true, 1)
	-- end

	local TargetedPlayer = Environment:GetTargettedAttackPlayer(ActorId)
	if TargetedPlayer > -1 then

		local rotationdiff = Environment:GetTargetRotationDiff(ActorId)
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
	--	Environment:ActorAnimate(ScriptId, ActorId, true, 1)
	-- end

	local TargetedPlayer = Environment:GetTargettedAttackPlayer(ActorId)
	if TargetedPlayer > -1 then
		local weaponrange1 = Environment:GetNpcWeaponReachDistance(ActorId, 1)

		local rotationdiff = Environment:GetTargetRotationDiff(ActorId)
		if math.abs(rotationdiff) > 2 then
			-- rotate to face player
			Environment:RotateToTargettedPlayer(ScriptId, ActorId, 1.9, 0.2)	
		else
		
			local tinrange = Environment:IsTargetInRange(weaponrange1, ActorId)
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


function SpawnMecaPinguin(ObjectType, ObjectId, Arguments, Environment)

	-- retrieve player position and calculate pinguin starting position
	local pos = Environment:GetPlayerPosition(ObjectId)
	local PlayerPos = LbaVec3(pos.X, pos.Y, pos.Z)
	local Up = LbaVec3(0, 1, 0)	
	local angleQuat = LbaQuaternion(pos.Rotation, Up)
	local Move = LbaVec3(0, 0, 1)	
	local RotatedMove = angleQuat:GetDirection(Move)
	
	-- create pinguin actor
	local Actor = ActorObjectInfo(Environment:GenerateDynamicActorId())
	Actor:SetRenderType(3)
	Actor.HitPowerOnTouch = 0
	Actor.ExcludeFromNavMesh = false
	Actor.DisplayDesc.ModelId = 0
	Actor.DisplayDesc.ModelName = "Object"
	Actor.DisplayDesc.Outfit = "MekaPingouin"
	Actor.DisplayDesc.Weapon = "No"
	Actor.DisplayDesc.Mode = "Normal"
	Actor.DisplayDesc.UseLight = true
	Actor.DisplayDesc.CastShadow = true
	Actor.DisplayDesc.ColorR = 1
	Actor.DisplayDesc.ColorG = 1
	Actor.DisplayDesc.ColorB = 1
	Actor.DisplayDesc.ColorA = 1
	Actor.DisplayDesc.TransX = 0
	Actor.DisplayDesc.TransY = 0
	Actor.DisplayDesc.TransZ = 0
	Actor.DisplayDesc.ScaleX = 1
	Actor.DisplayDesc.ScaleY = 1
	Actor.DisplayDesc.ScaleZ = 1
	Actor.DisplayDesc.RotX = 0
	Actor.DisplayDesc.RotY = 0
	Actor.DisplayDesc.RotZ = 0
	Actor:SetModelState(1)
	Actor.DisplayDesc.UseBillboard = false
	Actor.DisplayDesc.ColorMaterialType = 4
	Actor.DisplayDesc.MatAmbientColorR = -0.2
	Actor.DisplayDesc.MatAmbientColorG = -0.2
	Actor.DisplayDesc.MatAmbientColorB = -0.2
	Actor.DisplayDesc.MatAmbientColorA = 1
	Actor.DisplayDesc.MatDiffuseColorR = 0.4
	Actor.DisplayDesc.MatDiffuseColorG = 0.4
	Actor.DisplayDesc.MatDiffuseColorB = 0.4
	Actor.DisplayDesc.MatDiffuseColorA = 1
	Actor.DisplayDesc.MatSpecularColorR = 0
	Actor.DisplayDesc.MatSpecularColorG = 0
	Actor.DisplayDesc.MatSpecularColorB = 0
	Actor.DisplayDesc.MatSpecularColorA = 1
	Actor.DisplayDesc.MatEmissionColorR = 0
	Actor.DisplayDesc.MatEmissionColorG = 0
	Actor.DisplayDesc.MatEmissionColorB = 0
	Actor.DisplayDesc.MatEmissionColorA = 1
	Actor.DisplayDesc.MatShininess = 0
	Actor.PhysicDesc.Pos.X = PlayerPos.x + RotatedMove.x
	Actor.PhysicDesc.Pos.Y = PlayerPos.y + 0.2
	Actor.PhysicDesc.Pos.Z = PlayerPos.z + RotatedMove.z
	Actor.PhysicDesc.Pos.Rotation = pos.Rotation
	Actor.PhysicDesc.Density = 1
	Actor.PhysicDesc.Collidable = true
	Actor.PhysicDesc.SizeX = 0.5
	Actor.PhysicDesc.SizeY = 1.5
	Actor.PhysicDesc.SizeZ = 0.5
	Actor.PhysicDesc.AllowFreeMove = true
	Actor.PhysicDesc.Filename = ""
	Actor:SetPhysicalActorType(2)
	Actor:SetPhysicalShape(2)
	Actor.ExtraInfo.Name = ""
	Actor.ExtraInfo.NameColorR = 0
	Actor.ExtraInfo.NameColorG = 0
	Actor.ExtraInfo.NameColorB = 0
	Actor.ExtraInfo.Display = false
	Actor.LifeInfo.Display = false
	local ghostId = Environment:AddManagedGhost(ObjectId, Actor, true, true)
	
	Environment:ExecuteDelayedAction("KillMecaPinguin", 6000, 0, ghostId, Arguments)
end

function KillMecaPinguin(ObjectType, ObjectId, Arguments, Environment)

	-- get pinguin position
	local pos = Environment:GetGhostPPosition(ObjectId)
	
	-- delete pinguin actor
	Environment:RemoveManagedGhost(ObjectId)
	
	-- add explosion actor
	local actorID = Environment:GenerateDynamicActorId()
	local Actor = ActorObjectInfo(actorID)
	Actor:SetRenderType(9)
	Actor.HitPowerOnTouch = -1
	Actor.ExcludeFromNavMesh = false
	Actor.DisplayDesc.ModelId = 0
	Actor.DisplayDesc.ModelName = ""
	Actor.DisplayDesc.Outfit = ""
	Actor.DisplayDesc.Weapon = ""
	Actor.DisplayDesc.Mode = ""
	Actor.DisplayDesc.UseLight = true
	Actor.DisplayDesc.CastShadow = true
	Actor.DisplayDesc.ColorR = 1
	Actor.DisplayDesc.ColorG = 1
	Actor.DisplayDesc.ColorB = 1
	Actor.DisplayDesc.ColorA = 1
	Actor.DisplayDesc.TransX = 0
	Actor.DisplayDesc.TransY = 0
	Actor.DisplayDesc.TransZ = 0
	Actor.DisplayDesc.ScaleX = 1
	Actor.DisplayDesc.ScaleY = 1
	Actor.DisplayDesc.ScaleZ = 1
	Actor.DisplayDesc.RotX = 0
	Actor.DisplayDesc.RotY = 0
	Actor.DisplayDesc.RotZ = 0
	Actor:SetModelState(2)
	Actor.DisplayDesc.UseBillboard = false
	ActorExtraInfo = ModelExtraInfoParticle()
	ActorExtraInfo.Type = ModelExtraInfoParticle.ParticleExplosion
	ActorParticleExtraInfo = PredefinedParticleInfo()
	ActorParticleExtraInfo.WindX = 0
	ActorParticleExtraInfo.WindY = 0
	ActorParticleExtraInfo.WindZ = 0
	ActorParticleExtraInfo.Scale = 0.8
	ActorParticleExtraInfo.Intensity = 5
	ActorParticleExtraInfo.EmitterDuration = 0.6
	ActorParticleExtraInfo.ParticleDuration = 0.5
	ActorParticleExtraInfo.CustomTexture = ""
	ActorExtraInfo.Info = ActorParticleExtraInfo
	Actor.DisplayDesc.ExtraInfo = ActorExtraInfo
	Actor.PhysicDesc.Pos.X = pos.X
	Actor.PhysicDesc.Pos.Y = pos.Y
	Actor.PhysicDesc.Pos.Z = pos.Z
	Actor.PhysicDesc.Pos.Rotation = 0
	Actor.PhysicDesc.Density = 1
	Actor.PhysicDesc.Collidable = true
	Actor.PhysicDesc.SizeX = 1
	Actor.PhysicDesc.SizeY = 1
	Actor.PhysicDesc.SizeZ = 1
	Actor.PhysicDesc.AllowFreeMove = true
	Actor.PhysicDesc.Filename = ""
	Actor:SetPhysicalActorType(1)
	Actor:SetPhysicalShape(1)
	Actor.ExtraInfo.Name = ""
	Actor.ExtraInfo.NameColorR = 1
	Actor.ExtraInfo.NameColorG = 1
	Actor.ExtraInfo.NameColorB = 1
	Actor.ExtraInfo.Display = false
	Actor.LifeInfo.Display = false
	Actor.AttachToActorId = -1
	local ActorH = ActorHandler(Actor)
	Environment:AddActorObject(ActorH)
	
	-- play explosion sound
	Environment:PlaySound("Worlds/Lba1Original/Sound/SAMPLES038.wav", true, pos.X, pos.Y, pos.Z)
	
	-- perform explosion action
	local zone = LbaSphere(pos.X, pos.Y, pos.Z, 2)
	local action = HurtAction()
	action:SetHurtValue(20)
	action:HurtLifeOrMana(true)
	action:SetPlayedAnimation(2)
	Environment:ExecuteActionOnZone(action, zone, Arguments)
	
	-- remove explosion actor
	Environment:ExecuteDelayedAction("RemoveActor", 5000, 0, actorID, Arguments)	
end


function RemoveActor(ObjectType, ObjectId, Arguments, Environment)

	-- remove actor
	Environment:RemoveActor(ObjectId)
end