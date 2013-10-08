class "CollisionSceneEntity"



CollisionSceneEntity.SHAPE_BOX = 0
CollisionSceneEntity.SHAPE_TERRAIN = 1
CollisionSceneEntity.SHAPE_SPHERE = 2
CollisionSceneEntity.SHAPE_MESH = 3
CollisionSceneEntity.CHARACTER_CONTROLLER = 4
CollisionSceneEntity.SHAPE_CAPSULE = 5
CollisionSceneEntity.SHAPE_PLANE = 6
CollisionSceneEntity.SHAPE_CONE = 7
CollisionSceneEntity.SHAPE_CYLINDER = 8
function CollisionSceneEntity:__getvar(name)
	if name == "collisionObject" then
		local retVal = Physics3D.CollisionSceneEntity_get_collisionObject(self.__ptr)
		local __c = _G["btCollisionObject"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "lastPosition" then
		local retVal = Physics3D.CollisionSceneEntity_get_lastPosition(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "enabled" then
		return Physics3D.CollisionSceneEntity_get_enabled(self.__ptr)
	elseif name == "shape" then
		local retVal = Physics3D.CollisionSceneEntity_get_shape(self.__ptr)
		local __c = _G["btCollisionShape"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function CollisionSceneEntity:__setvar(name,value)
	if name == "lastPosition" then
		Physics3D.CollisionSceneEntity_set_lastPosition(self.__ptr, value.__ptr)
		return true
	elseif name == "enabled" then
		Physics3D.CollisionSceneEntity_set_enabled(self.__ptr, value)
		return true
	end
	return false
end


function CollisionSceneEntity:CollisionSceneEntity(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Physics3D.CollisionSceneEntity(unpack(arg))
	end
end

function CollisionSceneEntity:getSceneEntity()
	local retVal =  Physics3D.CollisionSceneEntity_getSceneEntity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionSceneEntity:getType()
	local retVal =  Physics3D.CollisionSceneEntity_getType(self.__ptr)
	return retVal
end

function CollisionSceneEntity:Update()
	local retVal =  Physics3D.CollisionSceneEntity_Update(self.__ptr)
end

function CollisionSceneEntity:getConvexShape()
	local retVal =  Physics3D.CollisionSceneEntity_getConvexShape(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["btConvexShape"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionSceneEntity:createCollisionShape(entity, type)
	local retVal = Physics3D.CollisionSceneEntity_createCollisionShape(self.__ptr, entity.__ptr, type)
	if retVal == nil then return nil end
	local __c = _G["btCollisionShape"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CollisionSceneEntity:__delete()
	if self then Physics3D.delete_CollisionSceneEntity(self.__ptr) end
end
