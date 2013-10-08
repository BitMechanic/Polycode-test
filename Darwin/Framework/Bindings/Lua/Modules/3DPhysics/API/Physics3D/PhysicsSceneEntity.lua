require "Physics3D/CollisionSceneEntity"

class "PhysicsSceneEntity" (CollisionSceneEntity)



PhysicsSceneEntity.SHAPE_BOX = 0
PhysicsSceneEntity.SHAPE_TERRAIN = 1
PhysicsSceneEntity.SHAPE_SPHERE = 2
PhysicsSceneEntity.SHAPE_MESH = 3
PhysicsSceneEntity.CHARACTER_CONTROLLER = 4
PhysicsSceneEntity.SHAPE_CAPSULE = 5
PhysicsSceneEntity.SHAPE_PLANE = 6
PhysicsSceneEntity.SHAPE_CONE = 7
PhysicsSceneEntity.SHAPE_CYLINDER = 8
function PhysicsSceneEntity:__getvar(name)
	if name == "enabled" then
		return Physics3D.PhysicsSceneEntity_get_enabled(self.__ptr)
	elseif name == "rigidBody" then
		local retVal = Physics3D.PhysicsSceneEntity_get_rigidBody(self.__ptr)
		local __c = _G["btRigidBody"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if CollisionSceneEntity["__getvar"] ~= nil then
		return CollisionSceneEntity.__getvar(self, name)
	end
end


function PhysicsSceneEntity:__setvar(name,value)
	if name == "enabled" then
		Physics3D.PhysicsSceneEntity_set_enabled(self.__ptr, value)
		return true
	end
	if CollisionSceneEntity["__setvar"] ~= nil then
		return CollisionSceneEntity.__setvar(self, name, value)
	else
		return false
	end
end


function PhysicsSceneEntity:PhysicsSceneEntity(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "CollisionSceneEntity" then
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
		self.__ptr = Physics3D.PhysicsSceneEntity(unpack(arg))
	end
end

function PhysicsSceneEntity:Update()
	local retVal =  Physics3D.PhysicsSceneEntity_Update(self.__ptr)
end

function PhysicsSceneEntity:getSceneEntity()
	local retVal =  Physics3D.PhysicsSceneEntity_getSceneEntity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsSceneEntity:setFriction(friction)
	local retVal = Physics3D.PhysicsSceneEntity_setFriction(self.__ptr, friction)
end

function PhysicsSceneEntity:getType()
	local retVal =  Physics3D.PhysicsSceneEntity_getType(self.__ptr)
	return retVal
end

function PhysicsSceneEntity:setSpin(spin)
	local retVal = Physics3D.PhysicsSceneEntity_setSpin(self.__ptr, spin.__ptr)
end

function PhysicsSceneEntity:setMass(mass)
	local retVal = Physics3D.PhysicsSceneEntity_setMass(self.__ptr, mass)
end

function PhysicsSceneEntity:getVelocity()
	local retVal =  Physics3D.PhysicsSceneEntity_getVelocity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsSceneEntity:getSpin()
	local retVal =  Physics3D.PhysicsSceneEntity_getSpin(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsSceneEntity:setRotation(quat)
	local retVal = Physics3D.PhysicsSceneEntity_setRotation(self.__ptr, quat.__ptr)
end

function PhysicsSceneEntity:setVelocity(velocity)
	local retVal = Physics3D.PhysicsSceneEntity_setVelocity(self.__ptr, velocity.__ptr)
end

function PhysicsSceneEntity:warpTo(position, resetRotation)
	local retVal = Physics3D.PhysicsSceneEntity_warpTo(self.__ptr, position.__ptr, resetRotation)
end

function PhysicsSceneEntity:applyImpulse(direction, point)
	local retVal = Physics3D.PhysicsSceneEntity_applyImpulse(self.__ptr, direction.__ptr, point.__ptr)
end

function PhysicsSceneEntity:__delete()
	if self then Physics3D.delete_PhysicsSceneEntity(self.__ptr) end
end
