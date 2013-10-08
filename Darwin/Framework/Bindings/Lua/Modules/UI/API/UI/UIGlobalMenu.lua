require "Polycode/ScreenEntity"

class "UIGlobalMenu" (ScreenEntity)



function UIGlobalMenu:__getvar(name)
	if name == "defaultMenuWidth" then
		return UI.UIGlobalMenu_get_defaultMenuWidth(self.__ptr)
	end
	if ScreenEntity["__getvar"] ~= nil then
		return ScreenEntity.__getvar(self, name)
	end
end


function UIGlobalMenu:__setvar(name,value)
	if name == "defaultMenuWidth" then
		UI.UIGlobalMenu_set_defaultMenuWidth(self.__ptr, value)
		return true
	end
	if ScreenEntity["__setvar"] ~= nil then
		return ScreenEntity.__setvar(self, name, value)
	else
		return false
	end
end


function UIGlobalMenu:UIGlobalMenu(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScreenEntity" then
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
		self.__ptr = UI.UIGlobalMenu(unpack(arg))
	end
end

function UIGlobalMenu:Update()
	local retVal =  UI.UIGlobalMenu_Update(self.__ptr)
end

function UIGlobalMenu:hideMenu()
	local retVal =  UI.UIGlobalMenu_hideMenu(self.__ptr)
end

function UIGlobalMenu:showMenu(x, y, width)
	local retVal = UI.UIGlobalMenu_showMenu(self.__ptr, x, y, width)
	if retVal == nil then return nil end
	local __c = _G["UIMenu"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIGlobalMenu:showMenuAtMouse(width)
	local retVal = UI.UIGlobalMenu_showMenuAtMouse(self.__ptr, width)
	if retVal == nil then return nil end
	local __c = _G["UIMenu"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIGlobalMenu:__delete()
	if self then UI.delete_UIGlobalMenu(self.__ptr) end
end
