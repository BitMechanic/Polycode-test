require "UI/UIElement"

class "UIHSizer" (UIElement)







function UIHSizer:UIHSizer(...)
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
		self.__ptr = UI.UIHSizer(unpack(arg))
	end
end

function UIHSizer:setMainWidth(width)
	local retVal = UI.UIHSizer_setMainWidth(self.__ptr, width)
end

function UIHSizer:getMainWidth()
	local retVal =  UI.UIHSizer_getMainWidth(self.__ptr)
	return retVal
end

function UIHSizer:addLeftChild(element)
	local retVal = UI.UIHSizer_addLeftChild(self.__ptr, element.__ptr)
end

function UIHSizer:addRightChild(element)
	local retVal = UI.UIHSizer_addRightChild(self.__ptr, element.__ptr)
end

function UIHSizer:Resize(width, height)
	local retVal = UI.UIHSizer_Resize(self.__ptr, width, height)
end

function UIHSizer:updateSizer()
	local retVal =  UI.UIHSizer_updateSizer(self.__ptr)
end

function UIHSizer:__delete()
	if self then UI.delete_UIHSizer(self.__ptr) end
end
