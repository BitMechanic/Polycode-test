require "Polycode/ScreenMesh"

class "ScreenShape" (ScreenMesh)



ScreenShape.SHAPE_RECT = 1
ScreenShape.SHAPE_CIRCLE = 2
ScreenShape.SHAPE_CUSTOM = 4
function ScreenShape:__getvar(name)
	if name == "strokeEnabled" then
		return Polycore.ScreenShape_get_strokeEnabled(self.__ptr)
	elseif name == "strokeColor" then
		local retVal = Polycore.ScreenShape_get_strokeColor(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "strokeWidth" then
		return Polycore.ScreenShape_get_strokeWidth(self.__ptr)
	end
	if ScreenMesh["__getvar"] ~= nil then
		return ScreenMesh.__getvar(self, name)
	end
end


function ScreenShape:__setvar(name,value)
	if name == "strokeEnabled" then
		Polycore.ScreenShape_set_strokeEnabled(self.__ptr, value)
		return true
	elseif name == "strokeColor" then
		Polycore.ScreenShape_set_strokeColor(self.__ptr, value.__ptr)
		return true
	elseif name == "strokeWidth" then
		Polycore.ScreenShape_set_strokeWidth(self.__ptr, value)
		return true
	end
	if ScreenMesh["__setvar"] ~= nil then
		return ScreenMesh.__setvar(self, name, value)
	else
		return false
	end
end


function ScreenShape:ScreenShape(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScreenMesh" then
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
		self.__ptr = Polycore.ScreenShape(unpack(arg))
	end
end

function ScreenShape:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenShape_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenShape:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenShape_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function ScreenShape:Render()
	local retVal =  Polycore.ScreenShape_Render(self.__ptr)
end

function ScreenShape:setStrokeColor(r, g, b, a)
	local retVal = Polycore.ScreenShape_setStrokeColor(self.__ptr, r, g, b, a)
end

function ScreenShape:setStrokeWidth(width)
	local retVal = Polycore.ScreenShape_setStrokeWidth(self.__ptr, width)
end

function ScreenShape:setGradient(r1, g1, b1, a1, r2, g2, b2, a2)
	local retVal = Polycore.ScreenShape_setGradient(self.__ptr, r1, g1, b1, a1, r2, g2, b2, a2)
end

function ScreenShape:clearGradient()
	local retVal =  Polycore.ScreenShape_clearGradient(self.__ptr)
end

function ScreenShape:getShapeType()
	local retVal =  Polycore.ScreenShape_getShapeType(self.__ptr)
	return retVal
end

function ScreenShape:setShapeType(type)
	local retVal = Polycore.ScreenShape_setShapeType(self.__ptr, type)
end

function ScreenShape:setShapeSize(newWidth, newHeight)
	local retVal = Polycore.ScreenShape_setShapeSize(self.__ptr, newWidth, newHeight)
end

function ScreenShape:buildShapeMesh()
	local retVal =  Polycore.ScreenShape_buildShapeMesh(self.__ptr)
end

function ScreenShape:__delete()
	if self then Polycore.delete_ScreenShape(self.__ptr) end
end
