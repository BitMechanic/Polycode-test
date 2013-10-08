require "Polycode/Resource"

class "ScreenSpriteResourceEntry" (Resource)







function ScreenSpriteResourceEntry:ScreenSpriteResourceEntry(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
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
		self.__ptr = Polycore.ScreenSpriteResourceEntry(unpack(arg))
	end
end

function ScreenSpriteResourceEntry:getSprite()
	local retVal =  Polycore.ScreenSpriteResourceEntry_getSprite(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenSprite"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSpriteResourceEntry:reloadResource()
	local retVal =  Polycore.ScreenSpriteResourceEntry_reloadResource(self.__ptr)
end

function ScreenSpriteResourceEntry:__delete()
	if self then Polycore.delete_ScreenSpriteResourceEntry(self.__ptr) end
end
