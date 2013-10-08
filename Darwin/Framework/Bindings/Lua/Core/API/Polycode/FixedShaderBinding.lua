require "Polycode/ShaderBinding"

class "FixedShaderBinding" (ShaderBinding)







function FixedShaderBinding:FixedShaderBinding(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ShaderBinding" then
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
		self.__ptr = Polycore.FixedShaderBinding(unpack(arg))
	end
end

function FixedShaderBinding:addTexture(name, texture)
	local retVal = Polycore.FixedShaderBinding_addTexture(self.__ptr, name, texture.__ptr)
end

function FixedShaderBinding:addCubemap(name, cubemap)
	local retVal = Polycore.FixedShaderBinding_addCubemap(self.__ptr, name, cubemap.__ptr)
end

function FixedShaderBinding:getDiffuseTexture()
	local retVal =  Polycore.FixedShaderBinding_getDiffuseTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function FixedShaderBinding:__delete()
	if self then Polycore.delete_FixedShaderBinding(self.__ptr) end
end
