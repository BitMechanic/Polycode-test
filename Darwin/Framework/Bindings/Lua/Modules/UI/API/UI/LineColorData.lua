class "LineColorData"



function LineColorData:__getvar(name)
	if name == "color" then
		local retVal = UI.LineColorData_get_color(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "rangeStart" then
		return UI.LineColorData_get_rangeStart(self.__ptr)
	elseif name == "rangeEnd" then
		return UI.LineColorData_get_rangeEnd(self.__ptr)
	end
end


function LineColorData:__setvar(name,value)
	if name == "color" then
		UI.LineColorData_set_color(self.__ptr, value.__ptr)
		return true
	elseif name == "rangeStart" then
		UI.LineColorData_set_rangeStart(self.__ptr, value)
		return true
	elseif name == "rangeEnd" then
		UI.LineColorData_set_rangeEnd(self.__ptr, value)
		return true
	end
	return false
end


function LineColorData:LineColorData(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = UI.LineColorData(unpack(arg))
	end
end

function LineColorData:__delete()
	if self then UI.delete_LineColorData(self.__ptr) end
end
