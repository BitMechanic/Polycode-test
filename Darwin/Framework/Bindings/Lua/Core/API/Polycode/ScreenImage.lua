require "Polycode/ScreenShape"

class "ScreenImage" (ScreenShape)







function ScreenImage:ScreenImage(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScreenShape" then
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
		self.__ptr = Polycore.ScreenImage(unpack(arg))
	end
end

function ScreenImage.ScreenImageWithImage(image)
	local retVal = Polycore.ScreenImage_ScreenImageWithImage(image.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenImage"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenImage.ScreenImageWithTexture(texture)
	local retVal = Polycore.ScreenImage_ScreenImageWithTexture(texture.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenImage"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenImage:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenImage_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenImage:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenImage_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function ScreenImage:setImageCoordinates(x, y, width, height)
	local retVal = Polycore.ScreenImage_setImageCoordinates(self.__ptr, x, y, width, height)
end

function ScreenImage:getImageWidth()
	local retVal =  Polycore.ScreenImage_getImageWidth(self.__ptr)
	return retVal
end

function ScreenImage:getImageHeight()
	local retVal =  Polycore.ScreenImage_getImageHeight(self.__ptr)
	return retVal
end

function ScreenImage:__delete()
	if self then Polycore.delete_ScreenImage(self.__ptr) end
end
