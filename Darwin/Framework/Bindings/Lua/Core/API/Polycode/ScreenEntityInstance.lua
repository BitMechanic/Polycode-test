require "Polycode/ScreenEntity"

class "ScreenEntityInstance" (ScreenEntity)



function ScreenEntityInstance:__getvar(name)
	if name == "cloneUsingReload" then
		return Polycore.ScreenEntityInstance_get_cloneUsingReload(self.__ptr)
	elseif name == "fileName" then
		return Polycore.ScreenEntityInstance_get_fileName(self.__ptr)
	end
	if ScreenEntity["__getvar"] ~= nil then
		return ScreenEntity.__getvar(self, name)
	end
end


function ScreenEntityInstance:__setvar(name,value)
	if name == "cloneUsingReload" then
		Polycore.ScreenEntityInstance_set_cloneUsingReload(self.__ptr, value)
		return true
	elseif name == "fileName" then
		Polycore.ScreenEntityInstance_set_fileName(self.__ptr, value)
		return true
	end
	if ScreenEntity["__setvar"] ~= nil then
		return ScreenEntity.__setvar(self, name, value)
	else
		return false
	end
end


function ScreenEntityInstance:ScreenEntityInstance(...)
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
		self.__ptr = Polycore.ScreenEntityInstance(unpack(arg))
	end
end

function ScreenEntityInstance.BlankScreenEntityInstance()
	local retVal =  Polycore.ScreenEntityInstance_BlankScreenEntityInstance()
	if retVal == nil then return nil end
	local __c = _G["ScreenEntityInstance"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenEntityInstance:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenEntityInstance_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenEntityInstance:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenEntityInstance_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function ScreenEntityInstance:reloadEntityInstance()
	local retVal =  Polycore.ScreenEntityInstance_reloadEntityInstance(self.__ptr)
end

function ScreenEntityInstance:clearInstance()
	local retVal =  Polycore.ScreenEntityInstance_clearInstance(self.__ptr)
end

function ScreenEntityInstance:parseObjectIntoCurve(entry, curve)
	local retVal = Polycore.ScreenEntityInstance_parseObjectIntoCurve(self.__ptr, entry.__ptr, curve.__ptr)
end

function ScreenEntityInstance:applyScreenShape(entry, shape)
	local retVal = Polycore.ScreenEntityInstance_applyScreenShape(self.__ptr, entry.__ptr, shape.__ptr)
end

function ScreenEntityInstance:loadObjectEntryIntoEntity(entry, targetEntity)
	local retVal = Polycore.ScreenEntityInstance_loadObjectEntryIntoEntity(self.__ptr, entry.__ptr, targetEntity.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenEntity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenEntityInstance:loadFromFile(fileName)
	local retVal = Polycore.ScreenEntityInstance_loadFromFile(self.__ptr, fileName)
	return retVal
end

function ScreenEntityInstance:getResourceEntry()
	local retVal =  Polycore.ScreenEntityInstance_getResourceEntry(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenEntityInstanceResourceEntry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenEntityInstance:getFileName()
	local retVal =  Polycore.ScreenEntityInstance_getFileName(self.__ptr)
	return retVal
end

function ScreenEntityInstance:__delete()
	if self then Polycore.delete_ScreenEntityInstance(self.__ptr) end
end
