require "UI/UIElement"

class "UIImageButton" (UIElement)







function UIImageButton:UIImageButton(...)
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
		self.__ptr = UI.UIImageButton(unpack(arg))
	end
end

function UIImageButton:__delete()
	if self then UI.delete_UIImageButton(self.__ptr) end
end
