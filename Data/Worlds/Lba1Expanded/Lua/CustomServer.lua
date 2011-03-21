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



function CrateInPlaceCondition(Environment, ObjectType, ObjectId)

	-- first get player id
	clientid = -1;

	if ObjectType == 2 then
		clientid = ObjectId;
	end

	-- on object moved by player
	if ObjectType == 3 then
		clientid = Environment:GetGhostOwnerPlayer(ObjectId);
	end

	-- check if client found - else return
	if clientid < 0 then
		return false;
	end
	
	-- get crates positions
	crate1pos = Environment:GetGhostPosition(clientid, 5)
	crate2pos = Environment:GetGhostPosition(clientid, 6)	
	crate3pos = Environment:GetGhostPosition(clientid, 7)
	crate4pos = Environment:GetGhostPosition(clientid, 8)
	
	-- check positions
	if crate1pos.y < 0 then
		return false;
	end	
	if crate2pos.y < 0 then
		return false;
	end	
	if crate3pos.y < 0 then
		return false;
	end	
	if crate4pos.y < 0 then
		return false;
	end
	
	if crate1pos.x > 46.1 then
		return false;
	end	
	if crate2pos.x > 46.1 then
		return false;
	end	
	if crate3pos.x > 46.1 then
		return false;
	end	
	if crate4pos.x > 46.1 then
		return false;
	end
	
	if crate1pos.z > 36.1 then
		return false;
	end	
	if crate2pos.z > 36.1 then
		return false;
	end	
	if crate3pos.z > 36.1 then		
		return false;
	end	
	if crate4pos.z > 36.1 then	
		return false;
	end	
	
	
	
	return true
end