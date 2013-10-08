require "UI/UIElement"

class "UIMenuBarEntry" (UIElement)



function UIMenuBarEntry:__getvar(name)
	if name == "bg" then
		local retVal = UI.UIMenuBarEntry_get_bg(self.__ptr)
		local __c = _G["ScreenShape"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "label" then
		local retVal = UI.UIMenuBarEntry_get_label(self.__ptr)
		local __c = _G["ScreenLabel"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if UIElement["__getvar"] ~= nil then
		return UIElement.__getvar(self, name)
	end
end


function UIMenuBarEntry:__setvar(name,value)
	if UIElement["__setvar"] ~= nil then
		return UIElement.__setvar(self, name, value)
	else
		return false
	end
end


function UIMenuBarEntry:UIMenuBarEntry(...)
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
		self.__ptr = UI.UIMenuBarEntry(unpack(arg))
	end
end

function UIMenuBarEntry:addItem(name, code, shortCut1, shortCut2)
	local retVal = UI.UIMenuBarEntry_addItem(self.__ptr, name, code, shortCut1, shortCut2)
end

function UIMenuBarEntry:Select()
	local retVal =  UI.UIMenuBarEntry_Select(self.__ptr)
end

function UIMenuBarEntry:Deselect()
	local retVal =  UI.UIMenuBarEntry_Deselect(self.__ptr)
end

function UIMenuBarEntry:__delete()
	if self then UI.delete_UIMenuBarEntry(self.__ptr) end
end
