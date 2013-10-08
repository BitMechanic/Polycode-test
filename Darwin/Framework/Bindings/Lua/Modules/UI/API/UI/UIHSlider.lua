require "UI/UIElement"

class "UIHSlider" (UIElement)







function UIHSlider:UIHSlider(...)
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
		self.__ptr = UI.UIHSlider(unpack(arg))
	end
end

function UIHSlider:Update()
	local retVal =  UI.UIHSlider_Update(self.__ptr)
end

function UIHSlider:Resize(width, height)
	local retVal = UI.UIHSlider_Resize(self.__ptr, width, height)
end

function UIHSlider:isContinuous()
	local retVal =  UI.UIHSlider_isContinuous(self.__ptr)
	return retVal
end

function UIHSlider:setContinuous(_continuous)
	local retVal = UI.UIHSlider_setContinuous(self.__ptr, _continuous)
end

function UIHSlider:setSliderValue(val)
	local retVal = UI.UIHSlider_setSliderValue(self.__ptr, val)
end

function UIHSlider:getSliderValue()
	local retVal =  UI.UIHSlider_getSliderValue(self.__ptr)
	return retVal
end

function UIHSlider:__delete()
	if self then UI.delete_UIHSlider(self.__ptr) end
end
