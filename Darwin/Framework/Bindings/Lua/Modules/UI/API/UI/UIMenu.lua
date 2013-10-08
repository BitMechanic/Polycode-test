require "UI/UIElement"

class "UIMenu" (UIElement)







function UIMenu:UIMenu(...)
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
		self.__ptr = UI.UIMenu(unpack(arg))
	end
end

function UIMenu:addOption(label, _id, data)
	local retVal = UI.UIMenu_addOption(self.__ptr, label, _id, data.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UIMenuItem"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIMenu:addDivider()
	local retVal =  UI.UIMenu_addDivider(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UIMenuItem"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIMenu:getSelectedItem()
	local retVal =  UI.UIMenu_getSelectedItem(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UIMenuItem"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIMenu:Resize(width, height)
	local retVal = UI.UIMenu_Resize(self.__ptr, width, height)
end

function UIMenu:Update()
	local retVal =  UI.UIMenu_Update(self.__ptr)
end

function UIMenu:fitToScreenVertical()
	local retVal =  UI.UIMenu_fitToScreenVertical(self.__ptr)
end

function UIMenu:__delete()
	if self then UI.delete_UIMenu(self.__ptr) end
end
