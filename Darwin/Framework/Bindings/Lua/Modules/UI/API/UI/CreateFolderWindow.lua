require "UI/UIWindow"

class "CreateFolderWindow" (UIWindow)



function CreateFolderWindow:__getvar(name)
	if name == "okButton" then
		local retVal = UI.CreateFolderWindow_get_okButton(self.__ptr)
		local __c = _G["UIButton"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "cancelButton" then
		local retVal = UI.CreateFolderWindow_get_cancelButton(self.__ptr)
		local __c = _G["UIButton"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "nameInput" then
		local retVal = UI.CreateFolderWindow_get_nameInput(self.__ptr)
		local __c = _G["UITextInput"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if UIWindow["__getvar"] ~= nil then
		return UIWindow.__getvar(self, name)
	end
end


function CreateFolderWindow:__setvar(name,value)
	if UIWindow["__setvar"] ~= nil then
		return UIWindow.__setvar(self, name, value)
	else
		return false
	end
end


function CreateFolderWindow:CreateFolderWindow(...)
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
		self.__ptr = UI.CreateFolderWindow(unpack(arg))
	end
end

function CreateFolderWindow:__delete()
	if self then UI.delete_CreateFolderWindow(self.__ptr) end
end
