class "UIMenuBarEntryItem"



function UIMenuBarEntryItem:__getvar(name)
	if name == "name" then
		return UI.UIMenuBarEntryItem_get_name(self.__ptr)
	elseif name == "code" then
		return UI.UIMenuBarEntryItem_get_code(self.__ptr)
	elseif name == "shortCut1" then
		return UI.UIMenuBarEntryItem_get_shortCut1(self.__ptr)
	elseif name == "shortCut2" then
		return UI.UIMenuBarEntryItem_get_shortCut2(self.__ptr)
	end
end


function UIMenuBarEntryItem:__setvar(name,value)
	if name == "name" then
		UI.UIMenuBarEntryItem_set_name(self.__ptr, value)
		return true
	elseif name == "code" then
		UI.UIMenuBarEntryItem_set_code(self.__ptr, value)
		return true
	elseif name == "shortCut1" then
		UI.UIMenuBarEntryItem_set_shortCut1(self.__ptr, value)
		return true
	elseif name == "shortCut2" then
		UI.UIMenuBarEntryItem_set_shortCut2(self.__ptr, value)
		return true
	end
	return false
end


function UIMenuBarEntryItem:UIMenuBarEntryItem(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = UI.UIMenuBarEntryItem(unpack(arg))
	end
end

function UIMenuBarEntryItem:checkShortCut(shortCut)
	local retVal = UI.UIMenuBarEntryItem_checkShortCut(self.__ptr, shortCut)
	return retVal
end

function UIMenuBarEntryItem:__delete()
	if self then UI.delete_UIMenuBarEntryItem(self.__ptr) end
end
