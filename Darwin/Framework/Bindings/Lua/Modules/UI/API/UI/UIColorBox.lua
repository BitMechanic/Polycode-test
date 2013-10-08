require "UI/UIElement"

class "UIColorBox" (UIElement)







function UIColorBox:UIColorBox(...)
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
		self.__ptr = UI.UIColorBox(unpack(arg))
	end
end

function UIColorBox:getSelectedColor()
	local retVal =  UI.UIColorBox_getSelectedColor(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIColorBox:setBoxColor(newColor)
	local retVal = UI.UIColorBox_setBoxColor(self.__ptr, newColor.__ptr)
end

function UIColorBox:showColorPicker()
	local retVal =  UI.UIColorBox_showColorPicker(self.__ptr)
end

function UIColorBox:__delete()
	if self then UI.delete_UIColorBox(self.__ptr) end
end
