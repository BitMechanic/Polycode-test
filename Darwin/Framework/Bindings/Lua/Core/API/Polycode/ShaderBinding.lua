class "ShaderBinding"



function ShaderBinding:__getvar(name)
	if name == "shader" then
		local retVal = Polycore.ShaderBinding_get_shader(self.__ptr)
		local __c = _G["Shader"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function ShaderBinding:__setvar(name,value)
	return false
end


function ShaderBinding:ShaderBinding(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ShaderBinding(unpack(arg))
	end
end

function ShaderBinding:getTexture(name)
	local retVal = Polycore.ShaderBinding_getTexture(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getCubemap(name)
	local retVal = Polycore.ShaderBinding_getCubemap(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["Cubemap"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:clearTexture(name)
	local retVal = Polycore.ShaderBinding_clearTexture(self.__ptr, name)
end

function ShaderBinding:clearCubemap(name)
	local retVal = Polycore.ShaderBinding_clearCubemap(self.__ptr, name)
end

function ShaderBinding:addTexture(name, texture)
	local retVal = Polycore.ShaderBinding_addTexture(self.__ptr, name, texture.__ptr)
end

function ShaderBinding:addParam(type, name)
	local retVal = Polycore.ShaderBinding_addParam(self.__ptr, type, name)
	if retVal == nil then return nil end
	local __c = _G["LocalShaderParam"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:addCubemap(name, cubemap)
	local retVal = Polycore.ShaderBinding_addCubemap(self.__ptr, name, cubemap.__ptr)
end

function ShaderBinding:getNumLocalParams()
	local retVal =  Polycore.ShaderBinding_getNumLocalParams(self.__ptr)
	return retVal
end

function ShaderBinding:getLocalParam(index)
	local retVal = Polycore.ShaderBinding_getLocalParam(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["LocalShaderParam"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getLocalParamByName(name)
	local retVal = Polycore.ShaderBinding_getLocalParamByName(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["LocalShaderParam"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:addRenderTargetBinding(binding)
	local retVal = Polycore.ShaderBinding_addRenderTargetBinding(self.__ptr, binding.__ptr)
end

function ShaderBinding:removeRenderTargetBinding(binding)
	local retVal = Polycore.ShaderBinding_removeRenderTargetBinding(self.__ptr, binding.__ptr)
end

function ShaderBinding:getNumRenderTargetBindings()
	local retVal =  Polycore.ShaderBinding_getNumRenderTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getRenderTargetBinding(index)
	local retVal = Polycore.ShaderBinding_getRenderTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumInTargetBindings()
	local retVal =  Polycore.ShaderBinding_getNumInTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getInTargetBinding(index)
	local retVal = Polycore.ShaderBinding_getInTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumColorTargetBindings()
	local retVal =  Polycore.ShaderBinding_getNumColorTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getColorTargetBinding(index)
	local retVal = Polycore.ShaderBinding_getColorTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumDepthTargetBindings()
	local retVal =  Polycore.ShaderBinding_getNumDepthTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getDepthTargetBinding(index)
	local retVal = Polycore.ShaderBinding_getDepthTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumOutTargetBindings()
	local retVal =  Polycore.ShaderBinding_getNumOutTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getOutTargetBinding(index)
	local retVal = Polycore.ShaderBinding_getOutTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:addLocalParam(name, ptr)
	local retVal = Polycore.ShaderBinding_addLocalParam(self.__ptr, name, ptr.__ptr)
	if retVal == nil then return nil end
	local __c = _G["LocalShaderParam"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:__delete()
	if self then Polycore.delete_ShaderBinding(self.__ptr) end
end
