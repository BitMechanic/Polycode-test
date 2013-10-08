require "UI/UIElement"

class "UIVSizer" (UIElement)







function UIVSizer:UIVSizer(...)
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
		self.__ptr = UI.UIVSizer(unpack(arg))
	end
end

function UIVSizer:setMainHeight(height)
	local retVal = UI.UIVSizer_setMainHeight(self.__ptr, height)
end

function UIVSizer:getMainHeight()
	local retVal =  UI.UIVSizer_getMainHeight(self.__ptr)
	return retVal
end

function UIVSizer:addTopChild(element)
	local retVal = UI.UIVSizer_addTopChild(self.__ptr, element.__ptr)
end

function UIVSizer:addBottomChild(element)
	local retVal = UI.UIVSizer_addBottomChild(self.__ptr, element.__ptr)
end

function UIVSizer:Resize(width, height)
	local retVal = UI.UIVSizer_Resize(self.__ptr, width, height)
end

function UIVSizer:updateSizer()
	local retVal =  UI.UIVSizer_updateSizer(self.__ptr)
end

function UIVSizer:__delete()
	if self then UI.delete_UIVSizer(self.__ptr) end
end
