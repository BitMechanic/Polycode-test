require "Polycode/SceneEntity"

class "Camera" (SceneEntity)



function Camera:__getvar(name)
	if name == "frustumCulling" then
		return Polycore.Camera_get_frustumCulling(self.__ptr)
	elseif name == "cameraShift" then
		local retVal = Polycore.Camera_get_cameraShift(self.__ptr)
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if SceneEntity["__getvar"] ~= nil then
		return SceneEntity.__getvar(self, name)
	end
end


function Camera:__setvar(name,value)
	if name == "frustumCulling" then
		Polycore.Camera_set_frustumCulling(self.__ptr, value)
		return true
	elseif name == "cameraShift" then
		Polycore.Camera_set_cameraShift(self.__ptr, value.__ptr)
		return true
	end
	if SceneEntity["__setvar"] ~= nil then
		return SceneEntity.__setvar(self, name, value)
	else
		return false
	end
end


function Camera:Camera(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "SceneEntity" then
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
		self.__ptr = Polycore.Camera(unpack(arg))
	end
end

function Camera:buildFrustumPlanes()
	local retVal =  Polycore.Camera_buildFrustumPlanes(self.__ptr)
end

function Camera:isSphereInFrustum(pos, fRadius)
	local retVal = Polycore.Camera_isSphereInFrustum(self.__ptr, pos.__ptr, fRadius)
	return retVal
end

function Camera:canSee(entity)
	local retVal = Polycore.Camera_canSee(self.__ptr, entity.__ptr)
	return retVal
end

function Camera:setOrthoMode(mode, orthoSizeX, orthoSizeY)
	local retVal = Polycore.Camera_setOrthoMode(self.__ptr, mode, orthoSizeX, orthoSizeY)
end

function Camera:getOrthoMode()
	local retVal =  Polycore.Camera_getOrthoMode(self.__ptr)
	return retVal
end

function Camera:getOrthoSizeX()
	local retVal =  Polycore.Camera_getOrthoSizeX(self.__ptr)
	return retVal
end

function Camera:getOrthoSizeY()
	local retVal =  Polycore.Camera_getOrthoSizeY(self.__ptr)
	return retVal
end

function Camera:setFOV(fov)
	local retVal = Polycore.Camera_setFOV(self.__ptr, fov)
end

function Camera:getFOV()
	local retVal =  Polycore.Camera_getFOV(self.__ptr)
	return retVal
end

function Camera:setParentScene(parentScene)
	local retVal = Polycore.Camera_setParentScene(self.__ptr, parentScene.__ptr)
end

function Camera:doCameraTransform()
	local retVal =  Polycore.Camera_doCameraTransform(self.__ptr)
end

function Camera:setLightDepthTexture(texture)
	local retVal = Polycore.Camera_setLightDepthTexture(self.__ptr, texture.__ptr)
end

function Camera:hasFilterShader()
	local retVal =  Polycore.Camera_hasFilterShader(self.__ptr)
	return retVal
end

function Camera:drawFilter(targetTexture, targetTextureWidth, targetTextureHeight, targetColorTexture, targetZTexture)
	local retVal = Polycore.Camera_drawFilter(self.__ptr, targetTexture.__ptr, targetTextureWidth, targetTextureHeight, targetColorTexture.__ptr, targetZTexture.__ptr)
end

function Camera:getProjectionMatrix()
	local retVal =  Polycore.Camera_getProjectionMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:setExposureLevel(level)
	local retVal = Polycore.Camera_setExposureLevel(self.__ptr, level)
end

function Camera:getExposureLevel()
	local retVal =  Polycore.Camera_getExposureLevel(self.__ptr)
	return retVal
end

function Camera:setPostFilter(shaderMaterial)
	local retVal = Polycore.Camera_setPostFilter(self.__ptr, shaderMaterial.__ptr)
end

function Camera:setPostFilterByName(shaderName)
	local retVal = Polycore.Camera_setPostFilterByName(self.__ptr, shaderName)
end

function Camera:removePostFilter()
	local retVal =  Polycore.Camera_removePostFilter(self.__ptr)
end

function Camera:getLocalShaderOptions()
	local retVal =  Polycore.Camera_getLocalShaderOptions(self.__ptr)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["ShaderBinding"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function Camera:getScreenShaderMaterial()
	local retVal =  Polycore.Camera_getScreenShaderMaterial(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:__delete()
	if self then Polycore.delete_Camera(self.__ptr) end
end
