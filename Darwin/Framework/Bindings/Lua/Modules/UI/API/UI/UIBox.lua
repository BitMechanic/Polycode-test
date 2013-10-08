require "UI/UIElement"

class "UIBox" (UIElement)







function UIBox:UIBox(...)
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
		self.__ptr = UI.UIBox(unpack(arg))
	end
end

function UIBox:resizeBox(newWidth, newHeight)
	local retVal = UI.UIBox_resizeBox(self.__ptr, newWidth, newHeight)
end

function UIBox:__delete()
	if self then UI.delete_UIBox(self.__ptr) end
end
