class "EventHandler"



function EventHandler:__getvar(name)
	if name == "secondaryHandlerData" then
		local retVal = Polycore.EventHandler_get_secondaryHandlerData(self.__ptr)
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function EventHandler:__setvar(name,value)
	return false
end


function EventHandler:EventHandler(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.EventHandler(self)
	end
end

function EventHandler:__delete()
	if self then Polycore.delete_EventHandler(self.__ptr) end
end
