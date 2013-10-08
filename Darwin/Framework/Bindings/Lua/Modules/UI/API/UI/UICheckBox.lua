require "UI/UIElement"

class "UICheckBox" (UIElement)







function UICheckBox:UICheckBox(...)
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
		self.__ptr = UI.UICheckBox(unpack(arg))
	end
end

function UICheckBox:setChecked(val)
	local retVal = UI.UICheckBox_setChecked(self.__ptr, val)
end

function UICheckBox:changeCheck()
	local retVal =  UI.UICheckBox_changeCheck(self.__ptr)
end

function UICheckBox:isChecked()
	local retVal =  UI.UICheckBox_isChecked(self.__ptr)
	return retVal
end

function UICheckBox:getCaptionLabel()
	local retVal =  UI.UICheckBox_getCaptionLabel(self.__ptr)
	return retVal
end

function UICheckBox:__delete()
	if self then UI.delete_UICheckBox(self.__ptr) end
end
