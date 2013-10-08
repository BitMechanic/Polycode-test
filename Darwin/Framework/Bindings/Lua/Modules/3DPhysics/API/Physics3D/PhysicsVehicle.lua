require "Physics3D/PhysicsSceneEntity"

class "PhysicsVehicle" (PhysicsSceneEntity)



function PhysicsVehicle:__getvar(name)
	if name == "tuning" then
		local retVal = Physics3D.PhysicsVehicle_get_tuning(self.__ptr)
		local __c = _G["btRaycastVehicle::btVehicleTuning"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "rayCaster" then
		local retVal = Physics3D.PhysicsVehicle_get_rayCaster(self.__ptr)
		local __c = _G["btDefaultVehicleRaycaster"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vehicle" then
		local retVal = Physics3D.PhysicsVehicle_get_vehicle(self.__ptr)
		local __c = _G["btRaycastVehicle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if PhysicsSceneEntity["__getvar"] ~= nil then
		return PhysicsSceneEntity.__getvar(self, name)
	end
end


function PhysicsVehicle:__setvar(name,value)
	if name == "tuning" then
		Physics3D.PhysicsVehicle_set_tuning(self.__ptr, value.__ptr)
		return true
	end
	if PhysicsSceneEntity["__setvar"] ~= nil then
		return PhysicsSceneEntity.__setvar(self, name, value)
	else
		return false
	end
end


function PhysicsVehicle:PhysicsVehicle(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "PhysicsSceneEntity" then
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
		self.__ptr = Physics3D.PhysicsVehicle(unpack(arg))
	end
end

function PhysicsVehicle:addWheel(entity, connection, direction, axle, suspentionRestLength, wheelRadius, isFrontWheel, suspensionStiffness, suspensionDamping, suspensionCompression, wheelFriction, rollInfluence)
	local retVal = Physics3D.PhysicsVehicle_addWheel(self.__ptr, entity.__ptr, connection.__ptr, direction.__ptr, axle.__ptr, suspentionRestLength, wheelRadius, isFrontWheel, suspensionStiffness, suspensionDamping, suspensionCompression, wheelFriction, rollInfluence)
end

function PhysicsVehicle:applyEngineForce(force, wheelIndex)
	local retVal = Physics3D.PhysicsVehicle_applyEngineForce(self.__ptr, force, wheelIndex)
end

function PhysicsVehicle:setSteeringValue(value, wheelIndex)
	local retVal = Physics3D.PhysicsVehicle_setSteeringValue(self.__ptr, value, wheelIndex)
end

function PhysicsVehicle:setBrake(value, wheelIndex)
	local retVal = Physics3D.PhysicsVehicle_setBrake(self.__ptr, value, wheelIndex)
end

function PhysicsVehicle:warpVehicle(position)
	local retVal = Physics3D.PhysicsVehicle_warpVehicle(self.__ptr, position.__ptr)
end

function PhysicsVehicle:Update()
	local retVal =  Physics3D.PhysicsVehicle_Update(self.__ptr)
end

function PhysicsVehicle:__delete()
	if self then Physics3D.delete_PhysicsVehicle(self.__ptr) end
end
