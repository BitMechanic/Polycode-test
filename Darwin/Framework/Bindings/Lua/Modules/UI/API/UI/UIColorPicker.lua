require "UI/UIWindow"

class "UIColorPicker" (UIWindow)







function UIColorPicker:UIColorPicker(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "UIWindow" then
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
		self.__ptr = UI.UIColorPicker(unpack(arg))
	end
end

function UIColorPicker:updateSelectedColor(updateTextFields, updateHue, updateSV)
	local retVal = UI.UIColorPicker_updateSelectedColor(self.__ptr, updateTextFields, updateHue, updateSV)
end

function UIColorPicker:setHue(hueNum)
	local retVal = UI.UIColorPicker_setHue(self.__ptr, hueNum)
end

function UIColorPicker:setSaturationAndValue(S, V)
	local retVal = UI.UIColorPicker_setSaturationAndValue(self.__ptr, S, V)
end

function UIColorPicker:updateColorFromMainSelector()
	local retVal =  UI.UIColorPicker_updateColorFromMainSelector(self.__ptr)
end

function UIColorPicker:updateColorFromHueSelector()
	local retVal =  UI.UIColorPicker_updateColorFromHueSelector(self.__ptr)
end

function UIColorPicker:rebuildFromTextInputs()
	local retVal =  UI.UIColorPicker_rebuildFromTextInputs(self.__ptr)
end

function UIColorPicker:cancelColorListeners()
	local retVal =  UI.UIColorPicker_cancelColorListeners(self.__ptr)
end

function UIColorPicker:Update()
	local retVal =  UI.UIColorPicker_Update(self.__ptr)
end

function UIColorPicker:onClose()
	local retVal =  UI.UIColorPicker_onClose(self.__ptr)
end

function UIColorPicker:isContinuous()
	local retVal =  UI.UIColorPicker_isContinuous(self.__ptr)
	return retVal
end

function UIColorPicker:setContinuous(_continuous)
	local retVal = UI.UIColorPicker_setContinuous(self.__ptr, _continuous)
end

function UIColorPicker:setPickerColor(newColor)
	local retVal = UI.UIColorPicker_setPickerColor(self.__ptr, newColor.__ptr)
end

function UIColorPicker:getSelectedColor()
	local retVal =  UI.UIColorPicker_getSelectedColor(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIColorPicker:__delete()
	if self then UI.delete_UIColorPicker(self.__ptr) end
end
