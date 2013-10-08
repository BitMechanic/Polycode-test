require "UI/UIElement"

class "UITreeContainer" (UIElement)



function UITreeContainer:__getvar(name)
	if name == "scrollChild" then
		local retVal = UI.UITreeContainer_get_scrollChild(self.__ptr)
		local __c = _G["ScreenEntity"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if UIElement["__getvar"] ~= nil then
		return UIElement.__getvar(self, name)
	end
end


function UITreeContainer:__setvar(name,value)
	if UIElement["__setvar"] ~= nil then
		return UIElement.__setvar(self, name, value)
	else
		return false
	end
end


function UITreeContainer:UITreeContainer(...)
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
		self.__ptr = UI.UITreeContainer(unpack(arg))
	end
end

function UITreeContainer:Resize(width, height)
	local retVal = UI.UITreeContainer_Resize(self.__ptr, width, height)
end

function UITreeContainer:getRootNode()
	local retVal =  UI.UITreeContainer_getRootNode(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UITree"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITreeContainer:onKeyDown(key, charCode)
	local retVal = UI.UITreeContainer_onKeyDown(self.__ptr, key, charCode.__ptr)
end

function UITreeContainer:onGainFocus()
	local retVal =  UI.UITreeContainer_onGainFocus(self.__ptr)
end

function UITreeContainer:scrollToNode(node, showAtTop)
	local retVal = UI.UITreeContainer_scrollToNode(self.__ptr, node.__ptr, showAtTop)
end

function UITreeContainer:__delete()
	if self then UI.delete_UITreeContainer(self.__ptr) end
end
