class "PhysicsScreenEntity"



PhysicsScreenEntity.ENTITY_RECT = 1
PhysicsScreenEntity.ENTITY_CIRCLE = 2
PhysicsScreenEntity.ENTITY_MESH = 3
PhysicsScreenEntity.ENTITY_EDGE = 4
PhysicsScreenEntity.ENTITY_CAPSULE = 5
PhysicsScreenEntity.ENTITY_TRIPLE_CIRCLE = 6
function PhysicsScreenEntity:__getvar(name)
	if name == "body" then
		local retVal = Physics2D.PhysicsScreenEntity_get_body(self.__ptr)
		local __c = _G["b2Body"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "fixture" then
		local retVal = Physics2D.PhysicsScreenEntity_get_fixture(self.__ptr)
		local __c = _G["b2Fixture"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "collisionOnly" then
		return Physics2D.PhysicsScreenEntity_get_collisionOnly(self.__ptr)
	end
end


function PhysicsScreenEntity:__setvar(name,value)
	if name == "collisionOnly" then
		Physics2D.PhysicsScreenEntity_set_collisionOnly(self.__ptr, value)
		return true
	end
	return false
end


function PhysicsScreenEntity:PhysicsScreenEntity(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Physics2D.PhysicsScreenEntity(unpack(arg))
	end
end

function PhysicsScreenEntity:Update()
	local retVal =  Physics2D.PhysicsScreenEntity_Update(self.__ptr)
end

function PhysicsScreenEntity:getScreenEntity()
	local retVal =  Physics2D.PhysicsScreenEntity_getScreenEntity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScreenEntity:applyTorque(torque)
	local retVal = Physics2D.PhysicsScreenEntity_applyTorque(self.__ptr, torque)
end

function PhysicsScreenEntity:applyForce(force)
	local retVal = Physics2D.PhysicsScreenEntity_applyForce(self.__ptr, force.__ptr)
end

function PhysicsScreenEntity:applyImpulse(fx, fy)
	local retVal = Physics2D.PhysicsScreenEntity_applyImpulse(self.__ptr, fx, fy)
end

function PhysicsScreenEntity:setTransform(pos, angle)
	local retVal = Physics2D.PhysicsScreenEntity_setTransform(self.__ptr, pos.__ptr, angle)
end

function PhysicsScreenEntity:setVelocity(fx, fy)
	local retVal = Physics2D.PhysicsScreenEntity_setVelocity(self.__ptr, fx, fy)
end

function PhysicsScreenEntity:setVelocityX(fx)
	local retVal = Physics2D.PhysicsScreenEntity_setVelocityX(self.__ptr, fx)
end

function PhysicsScreenEntity:setVelocityY(fy)
	local retVal = Physics2D.PhysicsScreenEntity_setVelocityY(self.__ptr, fy)
end

function PhysicsScreenEntity:setLinearDamping(damping)
	local retVal = Physics2D.PhysicsScreenEntity_setLinearDamping(self.__ptr, damping)
end

function PhysicsScreenEntity:setAngularDamping(damping)
	local retVal = Physics2D.PhysicsScreenEntity_setAngularDamping(self.__ptr, damping)
end

function PhysicsScreenEntity:setFriction(friction)
	local retVal = Physics2D.PhysicsScreenEntity_setFriction(self.__ptr, friction)
end

function PhysicsScreenEntity:getLinearDamping()
	local retVal =  Physics2D.PhysicsScreenEntity_getLinearDamping(self.__ptr)
	return retVal
end

function PhysicsScreenEntity:getAngularDamping()
	local retVal =  Physics2D.PhysicsScreenEntity_getAngularDamping(self.__ptr)
	return retVal
end

function PhysicsScreenEntity:getFriction()
	local retVal =  Physics2D.PhysicsScreenEntity_getFriction(self.__ptr)
	return retVal
end

function PhysicsScreenEntity:setDensity(density)
	local retVal = Physics2D.PhysicsScreenEntity_setDensity(self.__ptr, density)
end

function PhysicsScreenEntity:getDensity()
	local retVal =  Physics2D.PhysicsScreenEntity_getDensity(self.__ptr)
	return retVal
end

function PhysicsScreenEntity:setCollisionCategory(categoryBits)
	local retVal = Physics2D.PhysicsScreenEntity_setCollisionCategory(self.__ptr, categoryBits)
end

function PhysicsScreenEntity:setCollisionMask(maskBits)
	local retVal = Physics2D.PhysicsScreenEntity_setCollisionMask(self.__ptr, maskBits)
end

function PhysicsScreenEntity:setCollisionGroupIndex(group)
	local retVal = Physics2D.PhysicsScreenEntity_setCollisionGroupIndex(self.__ptr, group)
end

function PhysicsScreenEntity:getFixture(index)
	local retVal = Physics2D.PhysicsScreenEntity_getFixture(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["b2Fixture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysicsScreenEntity:__delete()
	if self then Physics2D.delete_PhysicsScreenEntity(self.__ptr) end
end
