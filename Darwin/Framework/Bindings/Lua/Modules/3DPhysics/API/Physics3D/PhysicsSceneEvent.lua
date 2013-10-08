require "Polycode/Event"

class "PhysicsSceneEvent" (Event)



PhysicsSceneEvent.EVENTBASE_PHYSICSSCENEEVENT = 0x900
PhysicsSceneEvent.COLLISION_EVENT = PhysicsSceneEvent.EVENTBASE_PHYSICSSCENEEVENT + 0
function PhysicsSceneEvent:__getvar(name)
	if name == "entityA" then
		local retVal = Physics3D.PhysicsSceneEvent_get_entityA(self.__ptr)
		local __c = _G["PhysicsSceneEntity"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "entityB" then
		local retVal = Physics3D.PhysicsSceneEvent_get_entityB(self.__ptr)
		local __c = _G["PhysicsSceneEntity"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "appliedImpulse" then
		return Physics3D.PhysicsSceneEvent_get_appliedImpulse(self.__ptr)
	elseif name == "positionOnA" then
		local retVal = Physics3D.PhysicsSceneEvent_get_positionOnA(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "positionOnB" then
		local retVal = Physics3D.PhysicsSceneEvent_get_positionOnB(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "worldNormalOnB" then
		local retVal = Physics3D.PhysicsSceneEvent_get_worldNormalOnB(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if Event["__getvar"] ~= nil then
		return Event.__getvar(self, name)
	end
end


function PhysicsSceneEvent:__setvar(name,value)
	if name == "appliedImpulse" then
		Physics3D.PhysicsSceneEvent_set_appliedImpulse(self.__ptr, value)
		return true
	elseif name == "positionOnA" then
		Physics3D.PhysicsSceneEvent_set_positionOnA(self.__ptr, value.__ptr)
		return true
	elseif name == "positionOnB" then
		Physics3D.PhysicsSceneEvent_set_positionOnB(self.__ptr, value.__ptr)
		return true
	elseif name == "worldNormalOnB" then
		Physics3D.PhysicsSceneEvent_set_worldNormalOnB(self.__ptr, value.__ptr)
		return true
	end
	if Event["__setvar"] ~= nil then
		return Event.__setvar(self, name, value)
	else
		return false
	end
end


function PhysicsSceneEvent:PhysicsSceneEvent(...)
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
		self.__ptr = Physics3D.PhysicsSceneEvent(unpack(arg))
	end
end

function PhysicsSceneEvent:__delete()
	if self then Physics3D.delete_PhysicsSceneEvent(self.__ptr) end
end
