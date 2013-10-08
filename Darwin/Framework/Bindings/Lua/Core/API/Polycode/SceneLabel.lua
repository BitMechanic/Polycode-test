require "Polycode/ScenePrimitive"

class "SceneLabel" (ScenePrimitive)







function SceneLabel:SceneLabel(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScenePrimitive" then
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
		self.__ptr = Polycore.SceneLabel(unpack(arg))
	end
end

function SceneLabel:setText(newText)
	local retVal = Polycore.SceneLabel_setText(self.__ptr, newText)
end

function SceneLabel:getLabel()
	local retVal =  Polycore.SceneLabel_getLabel(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Label"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLabel:__delete()
	if self then Polycore.delete_SceneLabel(self.__ptr) end
end
