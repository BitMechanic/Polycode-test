class "Polygon"



function Polygon:__getvar(name)
	if name == "useVertexNormals" then
		return Polycore.Polygon_get_useVertexNormals(self.__ptr)
	end
end


function Polygon:__setvar(name,value)
	if name == "useVertexNormals" then
		Polycore.Polygon_set_useVertexNormals(self.__ptr, value)
		return true
	end
	return false
end


function Polygon:Polygon(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Polygon(unpack(arg))
	end
end

function Polygon:getVertexCount()
	local retVal =  Polycore.Polygon_getVertexCount(self.__ptr)
	return retVal
end

function Polygon:getVertex(index)
	local retVal = Polycore.Polygon_getVertex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Vertex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Polygon:addVertex(x, y, z, u, v)
	local retVal = Polycore.Polygon_addVertex(self.__ptr, x, y, z, u, v)
	if retVal == nil then return nil end
	local __c = _G["Vertex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Polygon:removeVertex(index)
	local retVal = Polycore.Polygon_removeVertex(self.__ptr, index)
end

function Polygon:calculateNormal()
	local retVal =  Polycore.Polygon_calculateNormal(self.__ptr)
end

function Polygon:calculateTangent()
	local retVal =  Polycore.Polygon_calculateTangent(self.__ptr)
end

function Polygon:getFaceNormal()
	local retVal =  Polycore.Polygon_getFaceNormal(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Polygon:getFaceTangent()
	local retVal =  Polycore.Polygon_getFaceTangent(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Polygon:getBounds2D()
	local retVal =  Polycore.Polygon_getBounds2D(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Rectangle"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Polygon:setNormal(normal)
	local retVal = Polycore.Polygon_setNormal(self.__ptr, normal.__ptr)
end

function Polygon:flipUVY()
	local retVal =  Polycore.Polygon_flipUVY(self.__ptr)
end

function Polygon:__delete()
	if self then Polycore.delete_Polygon(self.__ptr) end
end
