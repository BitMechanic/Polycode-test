require "Polycode/EventDispatcher"

class "Resource" (EventDispatcher)



Resource.RESOURCE_TEXTURE = 0
Resource.RESOURCE_MATERIAL = 1
Resource.RESOURCE_SHADER = 2
Resource.RESOURCE_PROGRAM = 3
Resource.RESOURCE_MESH = 5
Resource.RESOURCE_CUBEMAP = 6
Resource.RESOURCE_SCREEN_SPRITE = 7
Resource.RESOURCE_SCREEN_ENTITY_INSTANCE = 8
function Resource:__getvar(name)
	if name == "reloadOnFileModify" then
		return Polycore.Resource_get_reloadOnFileModify(self.__ptr)
	elseif name == "resourceFileTime" then
		local retVal = Polycore.Resource_get_resourceFileTime(self.__ptr)
		local __c = _G["time_t"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function Resource:__setvar(name,value)
	if name == "reloadOnFileModify" then
		Polycore.Resource_set_reloadOnFileModify(self.__ptr, value)
		return true
	elseif name == "resourceFileTime" then
		Polycore.Resource_set_resourceFileTime(self.__ptr, value.__ptr)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function Resource:Resource(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "EventDispatcher" then
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
		self.__ptr = Polycore.Resource(unpack(arg))
	end
end

function Resource:reloadResource()
	local retVal =  Polycore.Resource_reloadResource(self.__ptr)
end

function Resource:getResourceName()
	local retVal =  Polycore.Resource_getResourceName(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["String"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Resource:getResourceType()
	local retVal =  Polycore.Resource_getResourceType(self.__ptr)
	return retVal
end

function Resource:setResourceName(newName)
	local retVal = Polycore.Resource_setResourceName(self.__ptr, newName)
end

function Resource:setResourcePath(path)
	local retVal = Polycore.Resource_setResourcePath(self.__ptr, path)
end

function Resource:getResourcePath()
	local retVal =  Polycore.Resource_getResourcePath(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["String"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Resource:__delete()
	if self then Polycore.delete_Resource(self.__ptr) end
end
