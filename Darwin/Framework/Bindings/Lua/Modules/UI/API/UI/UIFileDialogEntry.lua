require "UI/UIElement"

class "UIFileDialogEntry" (UIElement)



function UIFileDialogEntry:__getvar(name)
	if name == "canSelect" then
		return UI.UIFileDialogEntry_get_canSelect(self.__ptr)
	elseif name == "bg" then
		local retVal = UI.UIFileDialogEntry_get_bg(self.__ptr)
		local __c = _G["ScreenShape"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "label" then
		local retVal = UI.UIFileDialogEntry_get_label(self.__ptr)
		local __c = _G["ScreenLabel"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "fileEntry" then
		local retVal = UI.UIFileDialogEntry_get_fileEntry(self.__ptr)
		local __c = _G["OSFileEntry"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "icon" then
		local retVal = UI.UIFileDialogEntry_get_icon(self.__ptr)
		local __c = _G["ScreenImage"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if UIElement["__getvar"] ~= nil then
		return UIElement.__getvar(self, name)
	end
end


function UIFileDialogEntry:__setvar(name,value)
	if name == "canSelect" then
		UI.UIFileDialogEntry_set_canSelect(self.__ptr, value)
		return true
	elseif name == "fileEntry" then
		UI.UIFileDialogEntry_set_fileEntry(self.__ptr, value.__ptr)
		return true
	end
	if UIElement["__setvar"] ~= nil then
		return UIElement.__setvar(self, name, value)
	else
		return false
	end
end


function UIFileDialogEntry:UIFileDialogEntry(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "UIElement" then
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
		self.__ptr = UI.UIFileDialogEntry(unpack(arg))
	end
end

function UIFileDialogEntry:Select()
	local retVal =  UI.UIFileDialogEntry_Select(self.__ptr)
end

function UIFileDialogEntry:Deselect()
	local retVal =  UI.UIFileDialogEntry_Deselect(self.__ptr)
end

function UIFileDialogEntry:__delete()
	if self then UI.delete_UIFileDialogEntry(self.__ptr) end
end
