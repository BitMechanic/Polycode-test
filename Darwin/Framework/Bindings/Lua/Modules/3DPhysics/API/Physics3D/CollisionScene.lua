require "Polycode/Scene"

class "CollisionScene" (Scene)







function CollisionScene:CollisionScene(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Scene" then
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
		self.__ptr = Physics3D.CollisionScene(unpack(arg))
	end
end

function CollisionScene:initCollisionScene(size)
	local retVal = Physics3D.CollisionScene_initCollisionScene(self.__ptr, size.__ptr)
end

function CollisionScene:Update()
	local retVal =  Physics3D.CollisionScene_Update(self.__ptr)
end

function CollisionScene:removeEntity(entity)
	local retVal = Physics3D.CollisionScene_removeEntity(self.__ptr, entity.__ptr)
end

function CollisionScene:getCollisionEntityByObject(collisionObject)
	local retVal = Physics3D.CollisionScene_getCollisionEntityByObject(self.__ptr, collisionObject.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CollisionSceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionScene:getFirstEntityInRay(origin, dest)
	local retVal = Physics3D.CollisionScene_getFirstEntityInRay(self.__ptr, origin.__ptr, dest.__ptr)
	if retVal == nil then return nil end
	local __c = _G["RayTestResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionScene:enableCollision(entity, val)
	local retVal = Physics3D.CollisionScene_enableCollision(self.__ptr, entity.__ptr, val)
end

function CollisionScene:getCollisionByScreenEntity(ent)
	local retVal = Physics3D.CollisionScene_getCollisionByScreenEntity(self.__ptr, ent.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CollisionSceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionScene:testCollision(ent1, ent2)
	local retVal = Physics3D.CollisionScene_testCollision(self.__ptr, ent1.__ptr, ent2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CollisionResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionScene:testCollisionOnCollisionChild(cEnt1, cEnt2)
	local retVal = Physics3D.CollisionScene_testCollisionOnCollisionChild(self.__ptr, cEnt1.__ptr, cEnt2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CollisionResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionScene:testCollisionOnCollisionChild_Convex(cEnt1, cEnt2)
	local retVal = Physics3D.CollisionScene_testCollisionOnCollisionChild_Convex(self.__ptr, cEnt1.__ptr, cEnt2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CollisionResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionScene:addCollisionChild(newEntity, type, group)
	local retVal = Physics3D.CollisionScene_addCollisionChild(self.__ptr, newEntity.__ptr, type, group)
	if retVal == nil then return nil end
	local __c = _G["CollisionSceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionScene:trackCollision(newEntity, type, group)
	local retVal = Physics3D.CollisionScene_trackCollision(self.__ptr, newEntity.__ptr, type, group)
	if retVal == nil then return nil end
	local __c = _G["CollisionSceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionScene:removeCollision(entity)
	local retVal = Physics3D.CollisionScene_removeCollision(self.__ptr, entity.__ptr)
end

function CollisionScene:adjustForCollision(collisionEntity)
	local retVal = Physics3D.CollisionScene_adjustForCollision(self.__ptr, collisionEntity.__ptr)
end

function CollisionScene:__delete()
	if self then Physics3D.delete_CollisionScene(self.__ptr) end
end
