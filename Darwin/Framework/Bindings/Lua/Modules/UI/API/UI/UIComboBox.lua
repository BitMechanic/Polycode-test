require "UI/UIElement"

class "UIComboBox" (UIElement)







function UIComboBox:UIComboBox(...)
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
		self.__ptr = UI.UIComboBox(unpack(arg))
	end
end

function UIComboBox:toggleDropDown()
	local retVal =  UI.UIComboBox_toggleDropDown(self.__ptr)
end

function UIComboBox:clearItems()
	local retVal =  UI.UIComboBox_clearItems(self.__ptr)
end

function UIComboBox:addComboItem(itemName)
	local retVal = UI.UIComboBox_addComboItem(self.__ptr, itemName)
	return retVal
end

function UIComboBox:getSelectedIndex()
	local retVal =  UI.UIComboBox_getSelectedIndex(self.__ptr)
	return retVal
end

function UIComboBox:getSelectedItem()
	local retVal =  UI.UIComboBox_getSelectedItem(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UIComboBoxItem"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIComboBox:setSelectedIndex(newIndex)
	local retVal = UI.UIComboBox_setSelectedIndex(self.__ptr, newIndex)
end

function UIComboBox:Resize(width, height)
	local retVal = UI.UIComboBox_Resize(self.__ptr, width, height)
end

function UIComboBox:getNumItems()
	local retVal =  UI.UIComboBox_getNumItems(self.__ptr)
	return retVal
end

function UIComboBox:getItemAtIndex(index)
	local retVal = UI.UIComboBox_getItemAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["UIComboBoxItem"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIComboBox:__delete()
	if self then UI.delete_UIComboBox(self.__ptr) end
end
