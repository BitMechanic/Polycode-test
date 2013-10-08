require "Polycode/Vector3"

class "Vertex" (Vector3)



function Vertex:__getvar(name)
	if name == "restNormal" then
		local retVal = Polycore.Vertex_get_restNormal(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "restPosition" then
		local retVal = Polycore.Vertex_get_restPosition(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "normal" then
		local retVal = Polycore.Vertex_get_normal(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "tangent" then
		local retVal = Polycore.Vertex_get_tangent(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexColor" then
		local retVal = Polycore.Vertex_get_vertexColor(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "texCoord" then
		local retVal = Polycore.Vertex_get_texCoord(self.__ptr)
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "useVertexColor" then
		return Polycore.Vertex_get_useVertexColor(self.__ptr)
	end
	if Vector3["__getvar"] ~= nil then
		return Vector3.__getvar(self, name)
	end
end


function Vertex:__setvar(name,value)
	if name == "restNormal" then
		Polycore.Vertex_set_restNormal(self.__ptr, value.__ptr)
		return true
	elseif name == "restPosition" then
		Polycore.Vertex_set_restPosition(self.__ptr, value.__ptr)
		return true
	elseif name == "normal" then
		Polycore.Vertex_set_normal(self.__ptr, value.__ptr)
		return true
	elseif name == "tangent" then
		Polycore.Vertex_set_tangent(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexColor" then
		Polycore.Vertex_set_vertexColor(self.__ptr, value.__ptr)
		return true
	elseif name == "texCoord" then
		Polycore.Vertex_set_texCoord(self.__ptr, value.__ptr)
		return true
	elseif name == "useVertexColor" then
		Polycore.Vertex_set_useVertexColor(self.__ptr, value)
		return true
	end
	if Vector3["__setvar"] ~= nil then
		return Vector3.__setvar(self, name, value)
	else
		return false
	end
end


function Vertex:Vertex(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Vector3" then
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
		self.__ptr = Polycore.Vertex(unpack(arg))
	end
end

function Vertex:addBoneAssignment(boneID, boneWeight)
	local retVal = Polycore.Vertex_addBoneAssignment(self.__ptr, boneID, boneWeight)
end

function Vertex:getNumBoneAssignments()
	local retVal =  Polycore.Vertex_getNumBoneAssignments(self.__ptr)
	return retVal
end

function Vertex:getBoneAssignment(index)
	local retVal = Polycore.Vertex_getBoneAssignment(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["BoneAssignment"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Vertex:normalizeWeights()
	local retVal =  Polycore.Vertex_normalizeWeights(self.__ptr)
end

function Vertex:getTexCoord()
	local retVal =  Polycore.Vertex_getTexCoord(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Vertex:setTexCoord(u, v)
	local retVal = Polycore.Vertex_setTexCoord(self.__ptr, u, v)
end

function Vertex:setNormal(x, y, z)
	local retVal = Polycore.Vertex_setNormal(self.__ptr, x, y, z)
end

function Vertex:__delete()
	if self then Polycore.delete_Vertex(self.__ptr) end
end
