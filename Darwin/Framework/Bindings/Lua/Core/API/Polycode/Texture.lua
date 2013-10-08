require "Polycode/Resource"

class "Texture" (Resource)



function Texture:__getvar(name)
	if name == "scrollSpeedX" then
		return Polycore.Texture_get_scrollSpeedX(self.__ptr)
	elseif name == "scrollSpeedY" then
		return Polycore.Texture_get_scrollSpeedY(self.__ptr)
	elseif name == "clamp" then
		return Polycore.Texture_get_clamp(self.__ptr)
	elseif name == "textureData" then
		local retVal = Polycore.Texture_get_textureData(self.__ptr)
		local __c = _G["char"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end


function Texture:__setvar(name,value)
	if name == "scrollSpeedX" then
		Polycore.Texture_set_scrollSpeedX(self.__ptr, value)
		return true
	elseif name == "scrollSpeedY" then
		Polycore.Texture_set_scrollSpeedY(self.__ptr, value)
		return true
	elseif name == "clamp" then
		Polycore.Texture_set_clamp(self.__ptr, value)
		return true
	end
	if Resource["__setvar"] ~= nil then
		return Resource.__setvar(self, name, value)
	else
		return false
	end
end


function Texture:reloadResource()
	local retVal =  Polycore.Texture_reloadResource(self.__ptr)
end

function Texture:setTextureData(data)
	local retVal = Polycore.Texture_setTextureData(self.__ptr, data.__ptr)
end

function Texture:recreateFromImageData()
	local retVal =  Polycore.Texture_recreateFromImageData(self.__ptr)
end

function Texture:getScrollOffsetX()
	local retVal =  Polycore.Texture_getScrollOffsetX(self.__ptr)
	return retVal
end

function Texture:getScrollOffsetY()
	local retVal =  Polycore.Texture_getScrollOffsetY(self.__ptr)
	return retVal
end

function Texture:setImageData(data)
	local retVal = Polycore.Texture_setImageData(self.__ptr, data.__ptr)
end

function Texture:updateScroll(elapsed)
	local retVal = Polycore.Texture_updateScroll(self.__ptr, elapsed)
end

function Texture:getTextureData()
	local retVal =  Polycore.Texture_getTextureData(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["char"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Texture:getWidth()
	local retVal =  Polycore.Texture_getWidth(self.__ptr)
	return retVal
end

function Texture:getHeight()
	local retVal =  Polycore.Texture_getHeight(self.__ptr)
	return retVal
end

function Texture:__delete()
	if self then Polycore.delete_Texture(self.__ptr) end
end
