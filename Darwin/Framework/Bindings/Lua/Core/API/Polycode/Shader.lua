require "Polycode/Resource"

class "Shader" (Resource)



Shader.FIXED_SHADER = 0
Shader.MODULE_SHADER = 1
function Shader:__getvar(name)
	if name == "numSpotLights" then
		return Polycore.Shader_get_numSpotLights(self.__ptr)
	elseif name == "numAreaLights" then
		return Polycore.Shader_get_numAreaLights(self.__ptr)
	elseif name == "screenShader" then
		return Polycore.Shader_get_screenShader(self.__ptr)
	elseif name == "vp" then
		local retVal = Polycore.Shader_get_vp(self.__ptr)
		local __c = _G["ShaderProgram"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "fp" then
		local retVal = Polycore.Shader_get_fp(self.__ptr)
		local __c = _G["ShaderProgram"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end


function Shader:__setvar(name,value)
	if name == "numSpotLights" then
		Polycore.Shader_set_numSpotLights(self.__ptr, value)
		return true
	elseif name == "numAreaLights" then
		Polycore.Shader_set_numAreaLights(self.__ptr, value)
		return true
	elseif name == "screenShader" then
		Polycore.Shader_set_screenShader(self.__ptr, value)
		return true
	end
	if Resource["__setvar"] ~= nil then
		return Resource.__setvar(self, name, value)
	else
		return false
	end
end


function Shader:getType()
	local retVal =  Polycore.Shader_getType(self.__ptr)
	return retVal
end

function Shader:setName(name)
	local retVal = Polycore.Shader_setName(self.__ptr, name)
end

function Shader:getName()
	local retVal =  Polycore.Shader_getName(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["String"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Shader:createBinding()
	local retVal =  Polycore.Shader_createBinding(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ShaderBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Shader:reload()
	local retVal =  Polycore.Shader_reload(self.__ptr)
end

function Shader:getExpectedParamType(name)
	local retVal = Polycore.Shader_getExpectedParamType(self.__ptr, name)
	return retVal
end

function Shader:setVertexProgram(vp)
	local retVal = Polycore.Shader_setVertexProgram(self.__ptr, vp.__ptr)
end

function Shader:setFragmentProgram(fp)
	local retVal = Polycore.Shader_setFragmentProgram(self.__ptr, fp.__ptr)
end

function Shader:__delete()
	if self then Polycore.delete_Shader(self.__ptr) end
end
