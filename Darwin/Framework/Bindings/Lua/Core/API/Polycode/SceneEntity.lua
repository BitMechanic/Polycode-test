require "Polycode/Entity"

class "SceneEntity" (Entity)



function SceneEntity:__getvar(name)
	if name == "castShadows" then
		return Polycore.SceneEntity_get_castShadows(self.__ptr)
	elseif name == "collisionShapeType" then
		return Polycore.SceneEntity_get_collisionShapeType(self.__ptr)
	end
	if Entity["__getvar"] ~= nil then
		return Entity.__getvar(self, name)
	end
end


function SceneEntity:__setvar(name,value)
	if name == "castShadows" then
		Polycore.SceneEntity_set_castShadows(self.__ptr, value)
		return true
	elseif name == "collisionShapeType" then
		Polycore.SceneEntity_set_collisionShapeType(self.__ptr, value)
		return true
	end
	if Entity["__setvar"] ~= nil then
		return Entity.__setvar(self, name, value)
	else
		return false
	end
end


function SceneEntity:SceneEntity(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Entity" then
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
		self.__ptr = Polycore.SceneEntity(unpack(arg))
	end
end

function SceneEntity:testMouseCollision(x, y)
	local retVal = Polycore.SceneEntity_testMouseCollision(self.__ptr, x, y)
	return retVal
end

function SceneEntity:__delete()
	if self then Polycore.delete_SceneEntity(self.__ptr) end
end
