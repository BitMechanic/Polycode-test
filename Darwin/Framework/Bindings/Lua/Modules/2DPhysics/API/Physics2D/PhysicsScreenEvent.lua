require "Polycode/Event"

class "PhysicsScreenEvent" (Event)



PhysicsScreenEvent.EVENTBASE_PHYSICSSCREENEVENT = 0x800
PhysicsScreenEvent.EVENT_NEW_SHAPE_COLLISION = PhysicsScreenEvent.EVENTBASE_PHYSICSSCREENEVENT + 0
PhysicsScreenEvent.EVENT_END_SHAPE_COLLISION = PhysicsScreenEvent.EVENTBASE_PHYSICSSCREENEVENT + 1
PhysicsScreenEvent.EVENT_SOLVE_SHAPE_COLLISION = PhysicsScreenEvent.EVENTBASE_PHYSICSSCREENEVENT + 3
function PhysicsScreenEvent:__getvar(name)
	if name == "entity1" then
		local retVal = Physics2D.PhysicsScreenEvent_get_entity1(self.__ptr)
		local __c = _G["ScreenEntity"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "entity2" then
		local retVal = Physics2D.PhysicsScreenEvent_get_entity2(self.__ptr)
		local __c = _G["ScreenEntity"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "localCollisionNormal" then
		local retVal = Physics2D.PhysicsScreenEvent_get_localCollisionNormal(self.__ptr)
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "worldCollisionNormal" then
		local retVal = Physics2D.PhysicsScreenEvent_get_worldCollisionNormal(self.__ptr)
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "localCollisionPoint" then
		local retVal = Physics2D.PhysicsScreenEvent_get_localCollisionPoint(self.__ptr)
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "worldCollisionPoint" then
		local retVal = Physics2D.PhysicsScreenEvent_get_worldCollisionPoint(self.__ptr)
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "impactStrength" then
		return Physics2D.PhysicsScreenEvent_get_impactStrength(self.__ptr)
	elseif name == "frictionStrength" then
		return Physics2D.PhysicsScreenEvent_get_frictionStrength(self.__ptr)
	end
	if Event["__getvar"] ~= nil then
		return Event.__getvar(self, name)
	end
end


function PhysicsScreenEvent:__setvar(name,value)
	if name == "localCollisionNormal" then
		Physics2D.PhysicsScreenEvent_set_localCollisionNormal(self.__ptr, value.__ptr)
		return true
	elseif name == "worldCollisionNormal" then
		Physics2D.PhysicsScreenEvent_set_worldCollisionNormal(self.__ptr, value.__ptr)
		return true
	elseif name == "localCollisionPoint" then
		Physics2D.PhysicsScreenEvent_set_localCollisionPoint(self.__ptr, value.__ptr)
		return true
	elseif name == "worldCollisionPoint" then
		Physics2D.PhysicsScreenEvent_set_worldCollisionPoint(self.__ptr, value.__ptr)
		return true
	elseif name == "impactStrength" then
		Physics2D.PhysicsScreenEvent_set_impactStrength(self.__ptr, value)
		return true
	elseif name == "frictionStrength" then
		Physics2D.PhysicsScreenEvent_set_frictionStrength(self.__ptr, value)
		return true
	end
	if Event["__setvar"] ~= nil then
		return Event.__setvar(self, name, value)
	else
		return false
	end
end


function PhysicsScreenEvent:PhysicsScreenEvent(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Event" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Physics2D.PhysicsScreenEvent(unpack(arg))
	end
end

function PhysicsScreenEvent:getFirstEntity()
	local retVal =  Physics2D.PhysicsScreenEvent_getFirstEntity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScreenEvent:getSecondEntity()
	local retVal =  Physics2D.PhysicsScreenEvent_getSecondEntity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScreenEvent:__delete()
	if self then Physics2D.delete_PhysicsScreenEvent(self.__ptr) end
end
