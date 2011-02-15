-- In this file you can define custom functions to be used on the server side.

-- Please note that the changes done on this file will
-- only be reflected on the server when you change map on the editor!


-- A function used as custom action should have the following signature:
-- function Functioname(ObjectType, ObjectId, Arguments, Environment)

-- ObjectType and Objectid will contains the type and id of the object triggering the action
-- Arguments is a virtual class containing possible extra arguments
-- Environment is a pointer used to access the server class (see documentation for further information)


function ExampleServerFct(ObjectType, ObjectId, Arguments, Environment)

Environment:DisplayTextAction(ObjectType, ObjectId, 0)

end


function FunctionCustom(ScriptId, Environment,ActorId)
	Environment:UpdateActorAnimation(ActorId,"MoveForward")
	Position = LbaVec3(37.6,7,9.5)
	Environment:ActorStraightWalkTo(ScriptId,ActorId,Position)
	Environment:ActorRotate(ScriptId,ActorId,90,0.21,true)
	Environment:UpdateActorAnimation(ActorId,"MoveForward")
	Position = LbaVec3(50,7,9.5)
	Environment:ActorStraightWalkTo(ScriptId,ActorId,Position)
	Environment:ActorRotate(ScriptId,ActorId,270,0.11,true)
	Position = LbaVec3(38,7,5.5)
	Environment:ActorGoTo(ScriptId,ActorId,Position,0.005)
	Position = LbaVec3(36.5,7,12.5)
	Environment:TeleportActorTo(ScriptId,ActorId,Position)
	Environment:SetActorRotation(ActorId,180)
	Environment:UpdateActorModel(ActorId,"Horse")
	Environment:UpdateActorOutfit(ActorId,"Empty")
	Environment:UpdateActorWeapon(ActorId,"No")
	Environment:UpdateActorMode(ActorId,"Normal")
	Environment:ActorWaitForSignal(ScriptId,ActorId,2)
end
