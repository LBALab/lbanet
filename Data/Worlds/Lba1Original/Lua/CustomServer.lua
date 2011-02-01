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