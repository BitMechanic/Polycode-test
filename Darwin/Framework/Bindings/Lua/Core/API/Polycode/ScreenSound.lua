require "Polycode/ScreenEntity"

class "ScreenSound" (ScreenEntity)







function ScreenSound:ScreenSound(...)
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
		self.__ptr = Polycore.ScreenSound(unpack(arg))
	end
end

function ScreenSound:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenSound_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSound:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenSound_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function ScreenSound:Update()
	local retVal =  Polycore.ScreenSound_Update(self.__ptr)
end

function ScreenSound:getSound()
	local retVal =  Polycore.ScreenSound_getSound(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Sound"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSound:__delete()
	if self then Polycore.delete_ScreenSound(self.__ptr) end
end
