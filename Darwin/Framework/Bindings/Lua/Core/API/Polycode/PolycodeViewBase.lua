class "PolycodeViewBase"



function PolycodeViewBase:__getvar(name)
	if name == "windowData" then
		local retVal = Polycore.PolycodeViewBase_get_windowData(self.__ptr)
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function PolycodeViewBase:__setvar(name,value)
	return false
end


function PolycodeViewBase:PolycodeViewBase(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.PolycodeViewBase(unpack(arg))
	end
end

function PolycodeViewBase:__delete()
	if self then Polycore.delete_PolycodeViewBase(self.__ptr) end
end
