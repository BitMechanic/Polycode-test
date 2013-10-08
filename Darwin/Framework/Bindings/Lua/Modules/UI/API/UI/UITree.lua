require "UI/UIElement"

class "UITree" (UIElement)



function UITree:__getvar(name)
	if name == "handleRotation" then
		return UI.UITree_get_handleRotation(self.__ptr)
	end
	if UIElement["__getvar"] ~= nil then
		return UIElement.__getvar(self, name)
	end
end


function UITree:__setvar(name,value)
	if name == "handleRotation" then
		UI.UITree_set_handleRotation(self.__ptr, value)
		return true
	end
	if UIElement["__setvar"] ~= nil then
		return UIElement.__setvar(self, name, value)
	else
		return false
	end
end


function UITree:UITree(...)
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
		self.__ptr = UI.UITree(unpack(arg))
	end
end

function UITree:toggleCollapsed()
	local retVal =  UI.UITree_toggleCollapsed(self.__ptr)
end

function UITree:addTreeChild(icon, text, userData)
	local retVal = UI.UITree_addTreeChild(self.__ptr, icon, text, userData.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UITree"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITree:Update()
	local retVal =  UI.UITree_Update(self.__ptr)
end

function UITree:refreshTree()
	local retVal =  UI.UITree_refreshTree(self.__ptr)
end

function UITree:getTreeHeight()
	local retVal =  UI.UITree_getTreeHeight(self.__ptr)
	return retVal
end

function UITree:setParent(parent)
	local retVal = UI.UITree_setParent(self.__ptr, parent.__ptr)
end

function UITree:clearSelection(selectedNode)
	local retVal = UI.UITree_clearSelection(self.__ptr, selectedNode.__ptr)
end

function UITree:isCollapsed()
	local retVal =  UI.UITree_isCollapsed(self.__ptr)
	return retVal
end

function UITree:getUserData()
	local retVal =  UI.UITree_getUserData(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITree:setUserData(data)
	local retVal = UI.UITree_setUserData(self.__ptr, data.__ptr)
end

function UITree:getSelectedNode()
	local retVal =  UI.UITree_getSelectedNode(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UITree"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITree:setIcon(iconFile)
	local retVal = UI.UITree_setIcon(self.__ptr, iconFile)
end

function UITree:setSelected(byKey)
	local retVal = UI.UITree_setSelected(self.__ptr, byKey)
end

function UITree:setLabelText(text)
	local retVal = UI.UITree_setLabelText(self.__ptr, text)
end

function UITree:Resize(width)
	local retVal = UI.UITree_Resize(self.__ptr, width)
end

function UITree:getNumTreeChildren()
	local retVal =  UI.UITree_getNumTreeChildren(self.__ptr)
	return retVal
end

function UITree:getTreeChild(index)
	local retVal = UI.UITree_getTreeChild(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["UITree"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITree:removeTreeChild(child)
	local retVal = UI.UITree_removeTreeChild(self.__ptr, child.__ptr)
end

function UITree:clearTree()
	local retVal =  UI.UITree_clearTree(self.__ptr)
end

function UITree:getLabelText()
	local retVal =  UI.UITree_getLabelText(self.__ptr)
	return retVal
end

function UITree:getParent()
	local retVal =  UI.UITree_getParent(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UITree"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITree:hasTreeChildren()
	local retVal =  UI.UITree_hasTreeChildren(self.__ptr)
	return retVal
end

function UITree:getPrevSibling()
	local retVal =  UI.UITree_getPrevSibling(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UITree"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITree:getNextSibling()
	local retVal =  UI.UITree_getNextSibling(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UITree"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITree:getCellHeight()
	local retVal =  UI.UITree_getCellHeight(self.__ptr)
	return retVal
end

function UITree:isSelectedByKey()
	local retVal =  UI.UITree_isSelectedByKey(self.__ptr)
	return retVal
end

function UITree:__delete()
	if self then UI.delete_UITree(self.__ptr) end
end
