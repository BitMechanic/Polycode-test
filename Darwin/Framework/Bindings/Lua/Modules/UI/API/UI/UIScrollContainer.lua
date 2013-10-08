require "UI/UIElement"

class "UIScrollContainer" (UIElement)







function UIScrollContainer:UIScrollContainer(...)
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
		self.__ptr = UI.UIScrollContainer(unpack(arg))
	end
end

function UIScrollContainer:setContentSize(newContentWidth, newContentHeight)
	local retVal = UI.UIScrollContainer_setContentSize(self.__ptr, newContentWidth, newContentHeight)
end

function UIScrollContainer:Resize(width, height)
	local retVal = UI.UIScrollContainer_Resize(self.__ptr, width, height)
end

function UIScrollContainer:setScrollValue(xScroll, yScroll)
	local retVal = UI.UIScrollContainer_setScrollValue(self.__ptr, xScroll, yScroll)
end

function UIScrollContainer:scrollVertical(amount)
	local retVal = UI.UIScrollContainer_scrollVertical(self.__ptr, amount)
end

function UIScrollContainer:scrollHorizontal(amount)
	local retVal = UI.UIScrollContainer_scrollHorizontal(self.__ptr, amount)
end

function UIScrollContainer:Update()
	local retVal =  UI.UIScrollContainer_Update(self.__ptr)
end

function UIScrollContainer:getContentSize()
	local retVal =  UI.UIScrollContainer_getContentSize(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIScrollContainer:onMouseWheelDown(x, y)
	local retVal = UI.UIScrollContainer_onMouseWheelDown(self.__ptr, x, y)
end

function UIScrollContainer:onMouseWheelUp(x, y)
	local retVal = UI.UIScrollContainer_onMouseWheelUp(self.__ptr, x, y)
end

function UIScrollContainer:getVScrollWidth()
	local retVal =  UI.UIScrollContainer_getVScrollWidth(self.__ptr)
	return retVal
end

function UIScrollContainer:getVScrollBar()
	local retVal =  UI.UIScrollContainer_getVScrollBar(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UIVScrollBar"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIScrollContainer:getHScrollBar()
	local retVal =  UI.UIScrollContainer_getHScrollBar(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UIHScrollBar"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UIScrollContainer:__delete()
	if self then UI.delete_UIScrollContainer(self.__ptr) end
end
