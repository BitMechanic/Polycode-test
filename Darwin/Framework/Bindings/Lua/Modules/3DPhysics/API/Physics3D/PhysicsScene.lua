require "Physics3D/CollisionScene"

class "PhysicsScene" (CollisionScene)



function PhysicsScene:__getvar(name)
	if name == "pausePhysics" then
		return Physics3D.PhysicsScene_get_pausePhysics(self.__ptr)
	end
	if CollisionScene["__getvar"] ~= nil then
		return CollisionScene.__getvar(self, name)
	end
end


function PhysicsScene:__setvar(name,value)
	if name == "pausePhysics" then
		Physics3D.PhysicsScene_set_pausePhysics(self.__ptr, value)
		return true
	end
	if CollisionScene["__setvar"] ~= nil then
		return CollisionScene.__setvar(self, name, value)
	else
		return false
	end
end


function PhysicsScene:PhysicsScene(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "CollisionScene" then
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
		self.__ptr = Physics3D.PhysicsScene(unpack(arg))
	end
end

function PhysicsScene:Update()
	local retVal =  Physics3D.PhysicsScene_Update(self.__ptr)
end

function PhysicsScene:removeEntity(entity)
	local retVal = Physics3D.PhysicsScene_removeEntity(self.__ptr, entity.__ptr)
end

function PhysicsScene:processWorldCollisions()
	local retVal =  Physics3D.PhysicsScene_processWorldCollisions(self.__ptr)
end

function PhysicsScene:getPhysicsEntityByCollisionObject(object)
	local retVal = Physics3D.PhysicsScene_getPhysicsEntityByCollisionObject(self.__ptr, object.__ptr)
	if retVal == nil then return nil end
	local __c = _G["PhysicsSceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:removePhysicsChild(entity)
	local retVal = Physics3D.PhysicsScene_removePhysicsChild(self.__ptr, entity.__ptr)
end

function PhysicsScene:getPhysicsEntityBySceneEntity(entity)
	local retVal = Physics3D.PhysicsScene_getPhysicsEntityBySceneEntity(self.__ptr, entity.__ptr)
	if retVal == nil then return nil end
	local __c = _G["PhysicsSceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:addPhysicsChild(newEntity, type, mass, friction, restitution, group, compoundChildren)
	local retVal = Physics3D.PhysicsScene_addPhysicsChild(self.__ptr, newEntity.__ptr, type, mass, friction, restitution, group, compoundChildren)
	if retVal == nil then return nil end
	local __c = _G["PhysicsSceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:trackPhysicsChild(newEntity, type, mass, friction, restitution, group, compoundChildren)
	local retVal = Physics3D.PhysicsScene_trackPhysicsChild(self.__ptr, newEntity.__ptr, type, mass, friction, restitution, group, compoundChildren)
	if retVal == nil then return nil end
	local __c = _G["PhysicsSceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:addCharacterChild(newEntity, mass, friction, stepSize, group)
	local retVal = Physics3D.PhysicsScene_addCharacterChild(self.__ptr, newEntity.__ptr, mass, friction, stepSize, group)
	if retVal == nil then return nil end
	local __c = _G["PhysicsCharacter"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:removeCharacterChild(character)
	local retVal = Physics3D.PhysicsScene_removeCharacterChild(self.__ptr, character.__ptr)
end

function PhysicsScene:createHingeConstraint(entity, pivot, axis, minLimit, maxLimit)
	local retVal = Physics3D.PhysicsScene_createHingeConstraint(self.__ptr, entity.__ptr, pivot.__ptr, axis.__ptr, minLimit, maxLimit)
	if retVal == nil then return nil end
	local __c = _G["PhysicsHingeConstraint"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:createHingeJoint(entity1, entity2, pivot1, axis1, pivot2, axis2, minLimit, maxLimit)
	local retVal = Physics3D.PhysicsScene_createHingeJoint(self.__ptr, entity1.__ptr, entity2.__ptr, pivot1.__ptr, axis1.__ptr, pivot2.__ptr, axis2.__ptr, minLimit, maxLimit)
	if retVal == nil then return nil end
	local __c = _G["PhysicsHingeConstraint"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:createGenericConstraint(entity)
	local retVal = Physics3D.PhysicsScene_createGenericConstraint(self.__ptr, entity.__ptr)
	if retVal == nil then return nil end
	local __c = _G["PhysicsGenericConstraint"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:setVelocity(entity, velocity)
	local retVal = Physics3D.PhysicsScene_setVelocity(self.__ptr, entity.__ptr, velocity.__ptr)
end

function PhysicsScene:setSpin(entity, spin)
	local retVal = Physics3D.PhysicsScene_setSpin(self.__ptr, entity.__ptr, spin.__ptr)
end

function PhysicsScene:warpEntity(entity, position, resetRotation)
	local retVal = Physics3D.PhysicsScene_warpEntity(self.__ptr, entity.__ptr, position.__ptr, resetRotation)
end

function PhysicsScene:removeConstraint(constraint)
	local retVal = Physics3D.PhysicsScene_removeConstraint(self.__ptr, constraint.__ptr)
end

function PhysicsScene:applyImpulse(entity, force, point)
	local retVal = Physics3D.PhysicsScene_applyImpulse(self.__ptr, entity.__ptr, force.__ptr, point.__ptr)
end

function PhysicsScene:addVehicleChild(newEntity, mass, friction, group)
	local retVal = Physics3D.PhysicsScene_addVehicleChild(self.__ptr, newEntity.__ptr, mass, friction, group)
	if retVal == nil then return nil end
	local __c = _G["PhysicsVehicle"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScene:setGravity(gravity)
	local retVal = Physics3D.PhysicsScene_setGravity(self.__ptr, gravity.__ptr)
end

function PhysicsScene:wakeUp(entity)
	local retVal = Physics3D.PhysicsScene_wakeUp(self.__ptr, entity.__ptr)
end

function PhysicsScene:__delete()
	if self then Physics3D.delete_PhysicsScene(self.__ptr) end
end
