require "Polycode/EventDispatcher"

class "Scene" (EventDispatcher)



Scene.ENTITY_MESH = 0
Scene.ENTITY_LIGHT = 1
Scene.ENTITY_CAMERA = 2
Scene.ENTITY_ENTITY = 3
Scene.ENTITY_COLLMESH = 4
function Scene:__getvar(name)
	if name == "clearColor" then
		local retVal = Polycore.Scene_get_clearColor(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "useClearColor" then
		return Polycore.Scene_get_useClearColor(self.__ptr)
	elseif name == "ambientColor" then
		local retVal = Polycore.Scene_get_ambientColor(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "fogColor" then
		local retVal = Polycore.Scene_get_fogColor(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "enabled" then
		return Polycore.Scene_get_enabled(self.__ptr)
	elseif name == "ownsChildren" then
		return Polycore.Scene_get_ownsChildren(self.__ptr)
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function Scene:__setvar(name,value)
	if name == "clearColor" then
		Polycore.Scene_set_clearColor(self.__ptr, value.__ptr)
		return true
	elseif name == "useClearColor" then
		Polycore.Scene_set_useClearColor(self.__ptr, value)
		return true
	elseif name == "ambientColor" then
		Polycore.Scene_set_ambientColor(self.__ptr, value.__ptr)
		return true
	elseif name == "fogColor" then
		Polycore.Scene_set_fogColor(self.__ptr, value.__ptr)
		return true
	elseif name == "enabled" then
		Polycore.Scene_set_enabled(self.__ptr, value)
		return true
	elseif name == "ownsChildren" then
		Polycore.Scene_set_ownsChildren(self.__ptr, value)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function Scene:Scene(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "EventDispatcher" then
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
		self.__ptr = Polycore.Scene(unpack(arg))
	end
end

function Scene:addEntity(entity)
	local retVal = Polycore.Scene_addEntity(self.__ptr, entity.__ptr)
end

function Scene:addChild(entity)
	local retVal = Polycore.Scene_addChild(self.__ptr, entity.__ptr)
end

function Scene:removeEntity(entity)
	local retVal = Polycore.Scene_removeEntity(self.__ptr, entity.__ptr)
end

function Scene:getDefaultCamera()
	local retVal =  Polycore.Scene_getDefaultCamera(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Camera"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Scene:getActiveCamera()
	local retVal =  Polycore.Scene_getActiveCamera(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Camera"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Scene:setActiveCamera(camera)
	local retVal = Polycore.Scene_setActiveCamera(self.__ptr, camera.__ptr)
end

function Scene:enableLighting(enable)
	local retVal = Polycore.Scene_enableLighting(self.__ptr, enable)
end

function Scene:enableFog(enable)
	local retVal = Polycore.Scene_enableFog(self.__ptr, enable)
end

function Scene:setFogProperties(fogMode, color, density, startDepth, _endDepth)
	local retVal = Polycore.Scene_setFogProperties(self.__ptr, fogMode, color.__ptr, density, startDepth, _endDepth)
end

function Scene:Update()
	local retVal =  Polycore.Scene_Update(self.__ptr)
end

function Scene:setVirtual(val)
	local retVal = Polycore.Scene_setVirtual(self.__ptr, val)
end

function Scene:isVirtual()
	local retVal =  Polycore.Scene_isVirtual(self.__ptr)
	return retVal
end

function Scene:isEnabled()
	local retVal =  Polycore.Scene_isEnabled(self.__ptr)
	return retVal
end

function Scene:setEnabled(enabled)
	local retVal = Polycore.Scene_setEnabled(self.__ptr, enabled)
end

function Scene:getNumEntities()
	local retVal =  Polycore.Scene_getNumEntities(self.__ptr)
	return retVal
end

function Scene:getEntity(index)
	local retVal = Polycore.Scene_getEntity(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["SceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Scene:getEntityAtScreenPosition(x, y)
	local retVal = Polycore.Scene_getEntityAtScreenPosition(self.__ptr, x, y)
	if retVal == nil then return nil end
	local __c = _G["SceneEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Scene:Render(targetCamera)
	local retVal = Polycore.Scene_Render(self.__ptr, targetCamera.__ptr)
end

function Scene:RenderDepthOnly(targetCamera)
	local retVal = Polycore.Scene_RenderDepthOnly(self.__ptr, targetCamera.__ptr)
end

function Scene:addLight(light)
	local retVal = Polycore.Scene_addLight(self.__ptr, light.__ptr)
end

function Scene:removeLight(light)
	local retVal = Polycore.Scene_removeLight(self.__ptr, light.__ptr)
end

function Scene:getNearestLight(pos)
	local retVal = Polycore.Scene_getNearestLight(self.__ptr, pos.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneLight"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Scene:getNumLights()
	local retVal =  Polycore.Scene_getNumLights(self.__ptr)
	return retVal
end

function Scene:getLight(index)
	local retVal = Polycore.Scene_getLight(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["SceneLight"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Scene:__delete()
	if self then Polycore.delete_Scene(self.__ptr) end
end
