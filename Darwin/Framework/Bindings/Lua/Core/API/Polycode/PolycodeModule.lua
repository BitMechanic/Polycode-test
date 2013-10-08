class "PolycodeModule"



PolycodeModule.TYPE_GENERIC = 0
PolycodeModule.TYPE_SHADER = 1




function PolycodeModule:PolycodeModule(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.PolycodeModule(unpack(arg))
	end
end

function PolycodeModule:getType()
	local retVal =  Polycore.PolycodeModule_getType(self.__ptr)
	return retVal
end

function PolycodeModule:Update(elapsed)
	local retVal = Polycore.PolycodeModule_Update(self.__ptr, elapsed)
end

function PolycodeModule:requiresUpdate()
	local retVal =  Polycore.PolycodeModule_requiresUpdate(self.__ptr)
	return retVal
end

function PolycodeModule:__delete()
	if self then Polycore.delete_PolycodeModule(self.__ptr) end
end
