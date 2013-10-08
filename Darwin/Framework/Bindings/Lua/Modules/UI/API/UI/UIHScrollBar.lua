require "UI/UIElement"

class "UIHScrollBar" (UIElement)



function UIHScrollBar:__getvar(name)
	if name == "minHandleSize" then
		return UI.UIHScrollBar_get_minHandleSize(self.__ptr)
	end
	if UIElement["__getvar"] ~= nil then
		return UIElement.__getvar(self, name)
	end
end


function UIHScrollBar:__setvar(name,value)
	if name == "minHandleSize" then
		UI.UIHScrollBar_set_minHandleSize(self.__ptr, value)
		return true
	end
	if UIElement["__setvar"] ~= nil then
		return UIElement.__setvar(self, name, value)
	else
		return false
	end
end


function UIHScrollBar:UIHScrollBar(...)
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
		self.__ptr = UI.UIHScrollBar(unpack(arg))
	end
end

function UIHScrollBar:Update()
	local retVal =  UI.UIHScrollBar_Update(self.__ptr)
end

function UIHScrollBar:getScrollValue()
	local retVal =  UI.UIHScrollBar_getScrollValue(self.__ptr)
	return retVal
end

function UIHScrollBar:scrollTo(scrollValue)
	local retVal = UI.UIHScrollBar_scrollTo(self.__ptr, scrollValue)
end

function UIHScrollBar:Scroll(amount)
	local retVal = UI.UIHScrollBar_Scroll(self.__ptr, amount)
end

function UIHScrollBar:setHandleRatio(newRatio)
	local retVal = UI.UIHScrollBar_setHandleRatio(self.__ptr, newRatio)
end

function UIHScrollBar:__delete()
	if self then UI.delete_UIHScrollBar(self.__ptr) end
end
