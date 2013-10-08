class "Font"



function Font:__getvar(name)
	if name == "loaded" then
		return Polycore.Font_get_loaded(self.__ptr)
	end
end


function Font:__setvar(name,value)
	if name == "loaded" then
		Polycore.Font_set_loaded(self.__ptr, value)
		return true
	end
	return false
end


function Font:Font(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Font(unpack(arg))
	end
end

function Font:getFace()
	local retVal =  Polycore.Font_getFace(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["FT_Face"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Font:isValid()
	local retVal =  Polycore.Font_isValid(self.__ptr)
	return retVal
end

function Font:setFontName(fontName)
	local retVal = Polycore.Font_setFontName(self.__ptr, fontName)
end

function Font:getFontName()
	local retVal =  Polycore.Font_getFontName(self.__ptr)
	return retVal
end

function Font:getFontPath()
	local retVal =  Polycore.Font_getFontPath(self.__ptr)
	return retVal
end

function Font:__delete()
	if self then Polycore.delete_Font(self.__ptr) end
end
