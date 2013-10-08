require "UI/UIElement"

class "UIButton" (UIElement)







function UIButton:UIButton(...)
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
		self.__ptr = UI.UIButton(unpack(arg))
	end
end

function UIButton:Resize(width, height)
	local retVal = UI.UIButton_Resize(self.__ptr, width, height)
end

function UIButton:Update()
	local retVal =  UI.UIButton_Update(self.__ptr)
end

function UIButton:__delete()
	if self then UI.delete_UIButton(self.__ptr) end
end
