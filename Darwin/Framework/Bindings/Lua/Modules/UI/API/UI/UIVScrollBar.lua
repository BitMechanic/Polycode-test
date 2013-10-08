require "UI/UIElement"

class "UIVScrollBar" (UIElement)



function UIVScrollBar:__getvar(name)
	if name == "minHandleSize" then
		return UI.UIVScrollBar_get_minHandleSize(self.__ptr)
	end
	if UIElement["__getvar"] ~= nil then
		return UIElement.__getvar(self, name)
	end
end


function UIVScrollBar:__setvar(name,value)
	if name == "minHandleSize" then
		UI.UIVScrollBar_set_minHandleSize(self.__ptr, value)
		return true
	end
	if UIElement["__setvar"] ~= nil then
		return UIElement.__setvar(self, name, value)
	else
		return false
	end
end


function UIVScrollBar:UIVScrollBar(...)
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
		self.__ptr = UI.UIVScrollBar(unpack(arg))
	end
end

function UIVScrollBar:Update()
	local retVal =  UI.UIVScrollBar_Update(self.__ptr)
end

function UIVScrollBar:getScrollValue()
	local retVal =  UI.UIVScrollBar_getScrollValue(self.__ptr)
	return retVal
end

function UIVScrollBar:Resize(newHeight)
	local retVal = UI.UIVScrollBar_Resize(self.__ptr, newHeight)
end

function UIVScrollBar:scrollTo(scrollValue)
	local retVal = UI.UIVScrollBar_scrollTo(self.__ptr, scrollValue)
end

function UIVScrollBar:Scroll(amount)
	local retVal = UI.UIVScrollBar_Scroll(self.__ptr, amount)
end

function UIVScrollBar:setTickSize(newTickSize)
	local retVal = UI.UIVScrollBar_setTickSize(self.__ptr, newTickSize)
end

function UIVScrollBar:onMouseWheelDown(x, y)
	local retVal = UI.UIVScrollBar_onMouseWheelDown(self.__ptr, x, y)
end

function UIVScrollBar:onMouseWheelUp(x, y)
	local retVal = UI.UIVScrollBar_onMouseWheelUp(self.__ptr, x, y)
end

function UIVScrollBar:scrollUpOneTick()
	local retVal =  UI.UIVScrollBar_scrollUpOneTick(self.__ptr)
end

function UIVScrollBar:scrollDownOneTick()
	local retVal =  UI.UIVScrollBar_scrollDownOneTick(self.__ptr)
end

function UIVScrollBar:setHandleRatio(newRatio)
	local retVal = UI.UIVScrollBar_setHandleRatio(self.__ptr, newRatio)
end

function UIVScrollBar:__delete()
	if self then UI.delete_UIVScrollBar(self.__ptr) end
end
