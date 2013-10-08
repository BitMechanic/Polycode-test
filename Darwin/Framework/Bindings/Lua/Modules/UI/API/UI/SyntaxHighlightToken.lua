class "SyntaxHighlightToken"



SyntaxHighlightToken.TOKEN_TYPE_NO_OVERRIDE = 0
SyntaxHighlightToken.TOKEN_TYPE_OVERRIDE_START = 1
SyntaxHighlightToken.TOKEN_TYPE_OVERRIDE_END = 2
SyntaxHighlightToken.TOKEN_TYPE_OVERRIDE_LINE = 3
function SyntaxHighlightToken:__getvar(name)
	if name == "color" then
		local retVal = UI.SyntaxHighlightToken_get_color(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "text" then
		return UI.SyntaxHighlightToken_get_text(self.__ptr)
	elseif name == "overrideType" then
		return UI.SyntaxHighlightToken_get_overrideType(self.__ptr)
	elseif name == "type" then
		return UI.SyntaxHighlightToken_get_type(self.__ptr)
	end
end


function SyntaxHighlightToken:__setvar(name,value)
	if name == "color" then
		UI.SyntaxHighlightToken_set_color(self.__ptr, value.__ptr)
		return true
	elseif name == "text" then
		UI.SyntaxHighlightToken_set_text(self.__ptr, value)
		return true
	elseif name == "overrideType" then
		UI.SyntaxHighlightToken_set_overrideType(self.__ptr, value)
		return true
	elseif name == "type" then
		UI.SyntaxHighlightToken_set_type(self.__ptr, value)
		return true
	end
	return false
end


function SyntaxHighlightToken:SyntaxHighlightToken(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = UI.SyntaxHighlightToken(unpack(arg))
	end
end

function SyntaxHighlightToken:__delete()
	if self then UI.delete_SyntaxHighlightToken(self.__ptr) end
end
