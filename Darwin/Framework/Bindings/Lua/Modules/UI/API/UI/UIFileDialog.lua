require "UI/UIWindow"

class "UIFileDialog" (UIWindow)



function UIFileDialog:__getvar(name)
	if name == "action" then
		return UI.UIFileDialog_get_action(self.__ptr)
	end
	if UIWindow["__getvar"] ~= nil then
		return UIWindow.__getvar(self, name)
	end
end


function UIFileDialog:__setvar(name,value)
	if name == "action" then
		UI.UIFileDialog_set_action(self.__ptr, value)
		return true
	end
	if UIWindow["__setvar"] ~= nil then
		return UIWindow.__setvar(self, name, value)
	else
		return false
	end
end


function UIFileDialog:UIFileDialog(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "UIWindow" then
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
		self.__ptr = UI.UIFileDialog(unpack(arg))
	end
end

function UIFileDialog:onClose()
	local retVal =  UI.UIFileDialog_onClose(self.__ptr)
end

function UIFileDialog:clearEntries()
	local retVal =  UI.UIFileDialog_clearEntries(self.__ptr)
end

function UIFileDialog:showFolder(folderPath)
	local retVal = UI.UIFileDialog_showFolder(self.__ptr, folderPath)
end

function UIFileDialog:canOpen(extension)
	local retVal = UI.UIFileDialog_canOpen(self.__ptr, extension)
	return retVal
end

function UIFileDialog:addToSidebar(path, name)
	local retVal = UI.UIFileDialog_addToSidebar(self.__ptr, path, name)
end

function UIFileDialog:Update()
	local retVal =  UI.UIFileDialog_Update(self.__ptr)
end

function UIFileDialog:getSelection()
	local retVal =  UI.UIFileDialog_getSelection(self.__ptr)
	return retVal
end

function UIFileDialog:__delete()
	if self then UI.delete_UIFileDialog(self.__ptr) end
end
