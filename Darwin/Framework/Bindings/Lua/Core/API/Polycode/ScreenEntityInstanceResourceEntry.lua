require "Polycode/Resource"

class "ScreenEntityInstanceResourceEntry" (Resource)







function ScreenEntityInstanceResourceEntry:ScreenEntityInstanceResourceEntry(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
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
		self.__ptr = Polycore.ScreenEntityInstanceResourceEntry(unpack(arg))
	end
end

function ScreenEntityInstanceResourceEntry:getInstance()
	local retVal =  Polycore.ScreenEntityInstanceResourceEntry_getInstance(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenEntityInstance"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenEntityInstanceResourceEntry:reloadResource()
	local retVal =  Polycore.ScreenEntityInstanceResourceEntry_reloadResource(self.__ptr)
end

function ScreenEntityInstanceResourceEntry:__delete()
	if self then Polycore.delete_ScreenEntityInstanceResourceEntry(self.__ptr) end
end
