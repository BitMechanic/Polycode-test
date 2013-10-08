class "FontManager"







function FontManager:FontManager(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.FontManager(unpack(arg))
	end
end

function FontManager:registerFont(fontName, fontPath)
	local retVal = Polycore.FontManager_registerFont(self.__ptr, fontName, fontPath)
end

function FontManager:getFontByName(fontName)
	local retVal = Polycore.FontManager_getFontByName(self.__ptr, fontName)
	if retVal == nil then return nil end
	local __c = _G["Font"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function FontManager:getNumFonts()
	local retVal =  Polycore.FontManager_getNumFonts(self.__ptr)
	return retVal
end

function FontManager:getFontEntryByIndex(index)
	local retVal = Polycore.FontManager_getFontEntryByIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["FontEntry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function FontManager:getFontEntryByFontPath(fontPath)
	local retVal = Polycore.FontManager_getFontEntryByFontPath(self.__ptr, fontPath)
	if retVal == nil then return nil end
	local __c = _G["FontEntry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function FontManager:removeFontEntry(entry, deleteFont)
	local retVal = Polycore.FontManager_removeFontEntry(self.__ptr, entry.__ptr, deleteFont)
end

function FontManager:__delete()
	if self then Polycore.delete_FontManager(self.__ptr) end
end
