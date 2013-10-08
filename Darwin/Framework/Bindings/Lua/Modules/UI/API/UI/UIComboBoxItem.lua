class "UIComboBoxItem"



function UIComboBoxItem:__getvar(name)
	if name == "data" then
		local retVal = UI.UIComboBoxItem_get_data(self.__ptr)
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "label" then
		return UI.UIComboBoxItem_get_label(self.__ptr)
	end
end


function UIComboBoxItem:__setvar(name,value)
	if name == "label" then
		UI.UIComboBoxItem_set_label(self.__ptr, value)
		return true
	end
	return false
end


function UIComboBoxItem:UIComboBoxItem(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = UI.UIComboBoxItem(unpack(arg))
	end
end

function UIComboBoxItem:__delete()
	if self then UI.delete_UIComboBoxItem(self.__ptr) end
end
