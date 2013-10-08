require "Polycode/ScreenEntity"

class "UIElement" (ScreenEntity)







function UIElement:UIElement(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScreenEntity" then
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
		self.__ptr = UI.UIElement(unpack(arg))
	end
end

function UIElement:Resize(width, height)
	local retVal = UI.UIElement_Resize(self.__ptr, width, height)
end

function UIElement:__delete()
	if self then UI.delete_UIElement(self.__ptr) end
end
