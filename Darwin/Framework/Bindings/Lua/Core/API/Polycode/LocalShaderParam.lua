class "LocalShaderParam"



function LocalShaderParam:__getvar(name)
	if name == "name" then
		return Polycore.LocalShaderParam_get_name(self.__ptr)
	elseif name == "data" then
		local retVal = Polycore.LocalShaderParam_get_data(self.__ptr)
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function LocalShaderParam:__setvar(name,value)
	if name == "name" then
		Polycore.LocalShaderParam_set_name(self.__ptr, value)
		return true
	end
	return false
end


function LocalShaderParam:getNumber()
	local retVal =  Polycore.LocalShaderParam_getNumber(self.__ptr)
	return retVal
end

function LocalShaderParam:getVector2()
	local retVal =  Polycore.LocalShaderParam_getVector2(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:getVector3()
	local retVal =  Polycore.LocalShaderParam_getVector3(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:getColor()
	local retVal =  Polycore.LocalShaderParam_getColor(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:setNumber(x)
	local retVal = Polycore.LocalShaderParam_setNumber(self.__ptr, x)
end

function LocalShaderParam:setVector2(x)
	local retVal = Polycore.LocalShaderParam_setVector2(self.__ptr, x.__ptr)
end

function LocalShaderParam:setVector3(x)
	local retVal = Polycore.LocalShaderParam_setVector3(self.__ptr, x.__ptr)
end

function LocalShaderParam:setColor(x)
	local retVal = Polycore.LocalShaderParam_setColor(self.__ptr, x.__ptr)
end

function LocalShaderParam:__delete()
	if self then Polycore.delete_LocalShaderParam(self.__ptr) end
end
