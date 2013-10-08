class "ResourceManager"



function ResourceManager:__getvar(name)
	if name == "reloadResourcesOnModify" then
		return Polycore.ResourceManager_get_reloadResourcesOnModify(self.__ptr)
	end
end


function ResourceManager:__setvar(name,value)
	if name == "reloadResourcesOnModify" then
		Polycore.ResourceManager_set_reloadResourcesOnModify(self.__ptr, value)
		return true
	end
	return false
end


function ResourceManager:ResourceManager(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ResourceManager(unpack(arg))
	end
end

function ResourceManager:addResource(resource)
	local retVal = Polycore.ResourceManager_addResource(self.__ptr, resource.__ptr)
end

function ResourceManager:removeResource(resource)
	local retVal = Polycore.ResourceManager_removeResource(self.__ptr, resource.__ptr)
end

function ResourceManager:hasResource(resource)
	local retVal = Polycore.ResourceManager_hasResource(self.__ptr, resource.__ptr)
	return retVal
end

function ResourceManager:addDirResource(dirPath, recursive)
	local retVal = Polycore.ResourceManager_addDirResource(self.__ptr, dirPath, recursive)
end

function ResourceManager:addArchive(path)
	local retVal = Polycore.ResourceManager_addArchive(self.__ptr, path)
end

function ResourceManager:removeArchive(path)
	local retVal = Polycore.ResourceManager_removeArchive(self.__ptr, path)
end

function ResourceManager:readFile(fileName)
	local retVal = Polycore.ResourceManager_readFile(self.__ptr, fileName)
	return retVal
end

function ResourceManager:parseTextures(dirPath, recursive, basePath)
	local retVal = Polycore.ResourceManager_parseTextures(self.__ptr, dirPath, recursive, basePath)
end

function ResourceManager:parseMaterials(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseMaterials(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseShaders(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseShaders(self.__ptr, dirPath, recursive)
end

function ResourceManager:parsePrograms(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parsePrograms(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseCubemaps(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseCubemaps(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseOthers(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseOthers(self.__ptr, dirPath, recursive)
end

function ResourceManager:getResource(resourceType, resourceName)
	local retVal = Polycore.ResourceManager_getResource(self.__ptr, resourceType, resourceName)
	if retVal == nil then return nil end
	local __c = _G["Resource"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourceManager:getResourceByPath(resourcePath)
	local retVal = Polycore.ResourceManager_getResourceByPath(self.__ptr, resourcePath)
	if retVal == nil then return nil end
	local __c = _G["Resource"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourceManager:getResources(resourceType)
	local retVal = Polycore.ResourceManager_getResources(self.__ptr, resourceType)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Resource"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function ResourceManager:addShaderModule(module)
	local retVal = Polycore.ResourceManager_addShaderModule(self.__ptr, module.__ptr)
end

function ResourceManager:checkForChangedFiles()
	local retVal =  Polycore.ResourceManager_checkForChangedFiles(self.__ptr)
end

function ResourceManager:Update(elapsed)
	local retVal = Polycore.ResourceManager_Update(self.__ptr, elapsed)
end

function ResourceManager:__delete()
	if self then Polycore.delete_ResourceManager(self.__ptr) end
end
