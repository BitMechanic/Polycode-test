require "Polycode/EventDispatcher"

class "Screen" (EventDispatcher)



function Screen:__getvar(name)
	if name == "enabled" then
		return Polycore.Screen_get_enabled(self.__ptr)
	elseif name == "processTouchEventsAsMouse" then
		return Polycore.Screen_get_processTouchEventsAsMouse(self.__ptr)
	elseif name == "ownsChildren" then
		return Polycore.Screen_get_ownsChildren(self.__ptr)
	elseif name == "rootEntity" then
		local retVal = Polycore.Screen_get_rootEntity(self.__ptr)
		local __c = _G["ScreenEntity"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function Screen:__setvar(name,value)
	if name == "enabled" then
		Polycore.Screen_set_enabled(self.__ptr, value)
		return true
	elseif name == "processTouchEventsAsMouse" then
		Polycore.Screen_set_processTouchEventsAsMouse(self.__ptr, value)
		return true
	elseif name == "ownsChildren" then
		Polycore.Screen_set_ownsChildren(self.__ptr, value)
		return true
	elseif name == "rootEntity" then
		Polycore.Screen_set_rootEntity(self.__ptr, value.__ptr)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function Screen:Screen(...)
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
		self.__ptr = Polycore.Screen(unpack(arg))
	end
end

function Screen:addChild(newEntity)
	local retVal = Polycore.Screen_addChild(self.__ptr, newEntity.__ptr)
end

function Screen:addEntity(newEntity)
	local retVal = Polycore.Screen_addEntity(self.__ptr, newEntity.__ptr)
end

function Screen:removeChild(entityToRemove)
	local retVal = Polycore.Screen_removeChild(self.__ptr, entityToRemove.__ptr)
end

function Screen:setScreenOffset(x, y)
	local retVal = Polycore.Screen_setScreenOffset(self.__ptr, x, y)
end

function Screen:Shutdown()
	local retVal =  Polycore.Screen_Shutdown(self.__ptr)
end

function Screen:Update()
	local retVal =  Polycore.Screen_Update(self.__ptr)
end

function Screen:Render()
	local retVal =  Polycore.Screen_Render(self.__ptr)
end

function Screen:setRenderer(r_enderer)
	local retVal = Polycore.Screen_setRenderer(self.__ptr, r_enderer.__ptr)
end

function Screen:setNormalizedCoordinates(newVal, yCoordinateSize)
	local retVal = Polycore.Screen_setNormalizedCoordinates(self.__ptr, newVal, yCoordinateSize)
end

function Screen:setScreenShader(shaderName)
	local retVal = Polycore.Screen_setScreenShader(self.__ptr, shaderName)
end

function Screen:clearScreenShader()
	local retVal =  Polycore.Screen_clearScreenShader(self.__ptr)
end

function Screen:handleInputEvent(inputEvent)
	local retVal = Polycore.Screen_handleInputEvent(self.__ptr, inputEvent.__ptr)
end

function Screen:hasFilterShader()
	local retVal =  Polycore.Screen_hasFilterShader(self.__ptr)
	return retVal
end

function Screen:drawFilter()
	local retVal =  Polycore.Screen_drawFilter(self.__ptr)
end

function Screen:usesNormalizedCoordinates()
	local retVal =  Polycore.Screen_usesNormalizedCoordinates(self.__ptr)
	return retVal
end

function Screen:getYCoordinateSize()
	local retVal =  Polycore.Screen_getYCoordinateSize(self.__ptr)
	return retVal
end

function Screen:getLocalShaderOptions()
	local retVal =  Polycore.Screen_getLocalShaderOptions(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["std::vector<ShaderBinding>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Screen:getScreenShaderMaterial()
	local retVal =  Polycore.Screen_getScreenShaderMaterial(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Screen:__delete()
	if self then Polycore.delete_Screen(self.__ptr) end
end
