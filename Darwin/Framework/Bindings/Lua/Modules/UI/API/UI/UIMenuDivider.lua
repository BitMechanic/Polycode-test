require "UI/UIMenuItem"

class "UIMenuDivider" (UIMenuItem)







function UIMenuDivider:UIMenuDivider(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "UIMenuItem" then
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
		self.__ptr = UI.UIMenuDivider(unpack(arg))
	end
end

function UIMenuDivider:isSelectable()
	local retVal =  UI.UIMenuDivider_isSelectable(self.__ptr)
	return retVal
end

function UIMenuDivider:__delete()
	if self then UI.delete_UIMenuDivider(self.__ptr) end
end
