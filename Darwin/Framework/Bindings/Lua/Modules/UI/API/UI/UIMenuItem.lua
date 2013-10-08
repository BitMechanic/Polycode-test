require "UI/UIElement"

class "UIMenuItem" (UIElement)



function UIMenuItem:__getvar(name)
	if name == "data" then
		local retVal = UI.UIMenuItem_get_data(self.__ptr)
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "label" then
		return UI.UIMenuItem_get_label(self.__ptr)
	elseif name == "_id" then
		return UI.UIMenuItem_get__id(self.__ptr)
	end
	if UIElement["__getvar"] ~= nil then
		return UIElement.__getvar(self, name)
	end
end


function UIMenuItem:__setvar(name,value)
	if name == "label" then
		UI.UIMenuItem_set_label(self.__ptr, value)
		return true
	elseif name == "_id" then
		UI.UIMenuItem_set__id(self.__ptr, value)
		return true
	end
	if UIElement["__setvar"] ~= nil then
		return UIElement.__setvar(self, name, value)
	else
		return false
	end
end


function UIMenuItem:UIMenuItem(...)
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
		self.__ptr = UI.UIMenuItem(unpack(arg))
	end
end

function UIMenuItem:isSelectable()
	local retVal =  UI.UIMenuItem_isSelectable(self.__ptr)
	return retVal
end

function UIMenuItem:__delete()
	if self then UI.delete_UIMenuItem(self.__ptr) end
end
