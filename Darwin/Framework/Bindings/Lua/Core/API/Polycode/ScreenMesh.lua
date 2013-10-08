require "Polycode/ScreenEntity"

class "ScreenMesh" (ScreenEntity)



function ScreenMesh:__getvar(name)
	if name == "lineSmooth" then
		return Polycore.ScreenMesh_get_lineSmooth(self.__ptr)
	elseif name == "lineWidth" then
		return Polycore.ScreenMesh_get_lineWidth(self.__ptr)
	elseif name == "ownsMesh" then
		return Polycore.ScreenMesh_get_ownsMesh(self.__ptr)
	end
	if ScreenEntity["__getvar"] ~= nil then
		return ScreenEntity.__getvar(self, name)
	end
end


function ScreenMesh:__setvar(name,value)
	if name == "lineSmooth" then
		Polycore.ScreenMesh_set_lineSmooth(self.__ptr, value)
		return true
	elseif name == "lineWidth" then
		Polycore.ScreenMesh_set_lineWidth(self.__ptr, value)
		return true
	elseif name == "ownsMesh" then
		Polycore.ScreenMesh_set_ownsMesh(self.__ptr, value)
		return true
	end
	if ScreenEntity["__setvar"] ~= nil then
		return ScreenEntity.__setvar(self, name, value)
	else
		return false
	end
end


function ScreenMesh:ScreenMesh(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScreenEntity" then
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
		self.__ptr = Polycore.ScreenMesh(unpack(arg))
	end
end

function ScreenMesh.ScreenMeshWithType(meshType)
	local retVal = Polycore.ScreenMesh_ScreenMeshWithType(meshType)
	if retVal == nil then return nil end
	local __c = _G["ScreenMesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenMesh.ScreenMeshWithMesh(mesh)
	local retVal = Polycore.ScreenMesh_ScreenMeshWithMesh(mesh.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenMesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenMesh:Render()
	local retVal =  Polycore.ScreenMesh_Render(self.__ptr)
end

function ScreenMesh:getMesh()
	local retVal =  Polycore.ScreenMesh_getMesh(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenMesh:getTexture()
	local retVal =  Polycore.ScreenMesh_getTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenMesh:loadTexture(fileName)
	local retVal = Polycore.ScreenMesh_loadTexture(self.__ptr, fileName)
end

function ScreenMesh:setTexture(texture)
	local retVal = Polycore.ScreenMesh_setTexture(self.__ptr, texture.__ptr)
end

function ScreenMesh:setMaterial(material)
	local retVal = Polycore.ScreenMesh_setMaterial(self.__ptr, material.__ptr)
end

function ScreenMesh:setMaterialByName(materialName)
	local retVal = Polycore.ScreenMesh_setMaterialByName(self.__ptr, materialName)
end

function ScreenMesh:clearMaterial()
	local retVal =  Polycore.ScreenMesh_clearMaterial(self.__ptr)
end

function ScreenMesh:getMaterial()
	local retVal =  Polycore.ScreenMesh_getMaterial(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenMesh:getLocalShaderOptions()
	local retVal =  Polycore.ScreenMesh_getLocalShaderOptions(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ShaderBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenMesh:updateHitBox()
	local retVal =  Polycore.ScreenMesh_updateHitBox(self.__ptr)
end

function ScreenMesh:__delete()
	if self then Polycore.delete_ScreenMesh(self.__ptr) end
end
