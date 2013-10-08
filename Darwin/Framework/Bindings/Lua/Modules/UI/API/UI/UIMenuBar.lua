require "UI/UIElement"

class "UIMenuBar" (UIElement)







function UIMenuBar:UIMenuBar(...)
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
		self.__ptr = UI.UIMenuBar(unpack(arg))
	end
end

function UIMenuBar:showMenuForEntry(entry)
	local retVal = UI.UIMenuBar_showMenuForEntry(self.__ptr, entry.__ptr)
end

function UIMenuBar:Resize(width, height)
	local retVal = UI.UIMenuBar_Resize(self.__ptr, width, height)
end

function UIMenuBar:addMenuBarEntry(name)
	local retVal = UI.UIMenuBar_addMenuBarEntry(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["UIMenuBarEntry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIMenuBar:getSelectedItem()
	local retVal =  UI.UIMenuBar_getSelectedItem(self.__ptr)
	return retVal
end

function UIMenuBar:__delete()
	if self then UI.delete_UIMenuBar(self.__ptr) end
end
