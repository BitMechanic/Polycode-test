require "Polycode/ScreenEntity"

class "UIWindow" (ScreenEntity)



function UIWindow:__getvar(name)
	if name == "padding" then
		return UI.UIWindow_get_padding(self.__ptr)
	elseif name == "topPadding" then
		return UI.UIWindow_get_topPadding(self.__ptr)
	elseif name == "closeOnEscape" then
		return UI.UIWindow_get_closeOnEscape(self.__ptr)
	end
	if ScreenEntity["__getvar"] ~= nil then
		return ScreenEntity.__getvar(self, name)
	end
end


function UIWindow:__setvar(name,value)
	if name == "padding" then
		UI.UIWindow_set_padding(self.__ptr, value)
		return true
	elseif name == "topPadding" then
		UI.UIWindow_set_topPadding(self.__ptr, value)
		return true
	elseif name == "closeOnEscape" then
		UI.UIWindow_set_closeOnEscape(self.__ptr, value)
		return true
	end
	if ScreenEntity["__setvar"] ~= nil then
		return ScreenEntity.__setvar(self, name, value)
	else
		return false
	end
end


function UIWindow:UIWindow(...)
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
		self.__ptr = UI.UIWindow(unpack(arg))
	end
end

function UIWindow:showWindow()
	local retVal =  UI.UIWindow_showWindow(self.__ptr)
end

function UIWindow:hideWindow()
	local retVal =  UI.UIWindow_hideWindow(self.__ptr)
end

function UIWindow:onKeyDown(key, charCode)
	local retVal = UI.UIWindow_onKeyDown(self.__ptr, key, charCode.__ptr)
end

function UIWindow:onClose()
	local retVal =  UI.UIWindow_onClose(self.__ptr)
end

function UIWindow:onLoseFocus()
	local retVal =  UI.UIWindow_onLoseFocus(self.__ptr)
end

function UIWindow:setWindowSize(w, h)
	local retVal = UI.UIWindow_setWindowSize(self.__ptr, w, h)
end

function UIWindow:setWindowCaption(caption)
	local retVal = UI.UIWindow_setWindowCaption(self.__ptr, caption)
end

function UIWindow:onMouseDown(x, y)
	local retVal = UI.UIWindow_onMouseDown(self.__ptr, x, y)
end

function UIWindow:__delete()
	if self then UI.delete_UIWindow(self.__ptr) end
end
