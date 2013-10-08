require "Polycode/ScreenShape"

class "ScreenLabel" (ScreenShape)



function ScreenLabel:__getvar(name)
	if name == "positionAtBaseline" then
		return Polycore.ScreenLabel_get_positionAtBaseline(self.__ptr)
	end
	if ScreenShape["__getvar"] ~= nil then
		return ScreenShape.__getvar(self, name)
	end
end


function ScreenLabel:__setvar(name,value)
	if name == "positionAtBaseline" then
		Polycore.ScreenLabel_set_positionAtBaseline(self.__ptr, value)
		return true
	end
	if ScreenShape["__setvar"] ~= nil then
		return ScreenShape.__setvar(self, name, value)
	else
		return false
	end
end


function ScreenLabel:ScreenLabel(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScreenShape" then
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
		self.__ptr = Polycore.ScreenLabel(unpack(arg))
	end
end

function ScreenLabel:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenLabel_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenLabel:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenLabel_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function ScreenLabel:setText(newText)
	local retVal = Polycore.ScreenLabel_setText(self.__ptr, newText)
end

function ScreenLabel:getText()
	local retVal =  Polycore.ScreenLabel_getText(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["String"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenLabel:getLabel()
	local retVal =  Polycore.ScreenLabel_getLabel(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Label"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenLabel:Render()
	local retVal =  Polycore.ScreenLabel_Render(self.__ptr)
end

function ScreenLabel:__delete()
	if self then Polycore.delete_ScreenLabel(self.__ptr) end
end
