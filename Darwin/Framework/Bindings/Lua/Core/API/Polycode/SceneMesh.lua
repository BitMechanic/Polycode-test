require "Polycode/SceneEntity"

class "SceneMesh" (SceneEntity)



function SceneMesh:__getvar(name)
	if name == "lightmapIndex" then
		return Polycore.SceneMesh_get_lightmapIndex(self.__ptr)
	elseif name == "showVertexNormals" then
		return Polycore.SceneMesh_get_showVertexNormals(self.__ptr)
	elseif name == "lineWidth" then
		return Polycore.SceneMesh_get_lineWidth(self.__ptr)
	elseif name == "lineSmooth" then
		return Polycore.SceneMesh_get_lineSmooth(self.__ptr)
	elseif name == "ownsMesh" then
		return Polycore.SceneMesh_get_ownsMesh(self.__ptr)
	elseif name == "ownsSkeleton" then
		return Polycore.SceneMesh_get_ownsSkeleton(self.__ptr)
	end
	if SceneEntity["__getvar"] ~= nil then
		return SceneEntity.__getvar(self, name)
	end
end


function SceneMesh:__setvar(name,value)
	if name == "lightmapIndex" then
		Polycore.SceneMesh_set_lightmapIndex(self.__ptr, value)
		return true
	elseif name == "showVertexNormals" then
		Polycore.SceneMesh_set_showVertexNormals(self.__ptr, value)
		return true
	elseif name == "lineWidth" then
		Polycore.SceneMesh_set_lineWidth(self.__ptr, value)
		return true
	elseif name == "lineSmooth" then
		Polycore.SceneMesh_set_lineSmooth(self.__ptr, value)
		return true
	elseif name == "ownsMesh" then
		Polycore.SceneMesh_set_ownsMesh(self.__ptr, value)
		return true
	elseif name == "ownsSkeleton" then
		Polycore.SceneMesh_set_ownsSkeleton(self.__ptr, value)
		return true
	end
	if SceneEntity["__setvar"] ~= nil then
		return SceneEntity.__setvar(self, name, value)
	else
		return false
	end
end


function SceneMesh:SceneMesh(...)
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
		self.__ptr = Polycore.SceneMesh(unpack(arg))
	end
end

function SceneMesh.SceneMeshFromMesh(mesh)
	local retVal = Polycore.SceneMesh_SceneMeshFromMesh(mesh.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneMesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh.SceneMeshWithType(meshType)
	local retVal = Polycore.SceneMesh_SceneMeshWithType(meshType)
	if retVal == nil then return nil end
	local __c = _G["SceneMesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:Render()
	local retVal =  Polycore.SceneMesh_Render(self.__ptr)
end

function SceneMesh:getLocalShaderOptions()
	local retVal =  Polycore.SceneMesh_getLocalShaderOptions(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ShaderBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:getMesh()
	local retVal =  Polycore.SceneMesh_getMesh(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:getTexture()
	local retVal =  Polycore.SceneMesh_getTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:getMaterial()
	local retVal =  Polycore.SceneMesh_getMaterial(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:loadTexture(fileName)
	local retVal = Polycore.SceneMesh_loadTexture(self.__ptr, fileName)
end

function SceneMesh:loadSkeleton(fileName)
	local retVal = Polycore.SceneMesh_loadSkeleton(self.__ptr, fileName)
end

function SceneMesh:setTexture(texture)
	local retVal = Polycore.SceneMesh_setTexture(self.__ptr, texture.__ptr)
end

function SceneMesh:clearMaterial()
	local retVal =  Polycore.SceneMesh_clearMaterial(self.__ptr)
end

function SceneMesh:setMaterial(material)
	local retVal = Polycore.SceneMesh_setMaterial(self.__ptr, material.__ptr)
end

function SceneMesh:setMaterialByName(materialName)
	local retVal = Polycore.SceneMesh_setMaterialByName(self.__ptr, materialName)
end

function SceneMesh:setMesh(mesh)
	local retVal = Polycore.SceneMesh_setMesh(self.__ptr, mesh.__ptr)
end

function SceneMesh:setSkeleton(skeleton)
	local retVal = Polycore.SceneMesh_setSkeleton(self.__ptr, skeleton.__ptr)
end

function SceneMesh:getSkeleton()
	local retVal =  Polycore.SceneMesh_getSkeleton(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Skeleton"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:renderMeshLocally()
	local retVal =  Polycore.SceneMesh_renderMeshLocally(self.__ptr)
end

function SceneMesh:cacheToVertexBuffer(cache)
	local retVal = Polycore.SceneMesh_cacheToVertexBuffer(self.__ptr, cache)
end

function SceneMesh:__delete()
	if self then Polycore.delete_SceneMesh(self.__ptr) end
end
