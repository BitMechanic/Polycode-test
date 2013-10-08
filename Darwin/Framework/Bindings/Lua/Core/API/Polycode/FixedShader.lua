require "Polycode/Shader"

class "FixedShader" (Shader)







function FixedShader:FixedShader(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Shader" then
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
		self.__ptr = Polycore.FixedShader(unpack(arg))
	end
end

function FixedShader:createBinding()
	local retVal =  Polycore.FixedShader_createBinding(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ShaderBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function FixedShader:__delete()
	if self then Polycore.delete_FixedShader(self.__ptr) end
end
