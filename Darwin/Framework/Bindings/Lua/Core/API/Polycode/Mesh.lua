class "Mesh"



Mesh.QUAD_MESH = 0
Mesh.TRI_MESH = 1
Mesh.TRIFAN_MESH = 2
Mesh.LINE_MESH = 4
Mesh.POINT_MESH = 5
Mesh.LINE_STRIP_MESH = 6
Mesh.LINE_LOOP_MESH = 7
function Mesh:__getvar(name)
	if name == "useVertexColors" then
		return Polycore.Mesh_get_useVertexColors(self.__ptr)
	end
end


function Mesh:__setvar(name,value)
	if name == "useVertexColors" then
		Polycore.Mesh_set_useVertexColors(self.__ptr, value)
		return true
	end
	return false
end


function Mesh:Mesh(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Mesh(unpack(arg))
	end
end

function Mesh.MeshFromFileName(fileName)
	local retVal = Polycore.Mesh_MeshFromFileName(fileName)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:addPolygon(newPolygon)
	local retVal = Polycore.Mesh_addPolygon(self.__ptr, newPolygon.__ptr)
end

function Mesh:loadMesh(fileName)
	local retVal = Polycore.Mesh_loadMesh(self.__ptr, fileName)
end

function Mesh:clearMesh()
	local retVal =  Polycore.Mesh_clearMesh(self.__ptr)
end

function Mesh:saveToFile(fileName)
	local retVal = Polycore.Mesh_saveToFile(self.__ptr, fileName)
end

function Mesh:loadFromFile(inFile)
	local retVal = Polycore.Mesh_loadFromFile(self.__ptr, inFile.__ptr)
end

function Mesh:getPolygonCount()
	local retVal =  Polycore.Mesh_getPolygonCount(self.__ptr)
	return retVal
end

function Mesh:getVertexCount()
	local retVal =  Polycore.Mesh_getVertexCount(self.__ptr)
	return retVal
end

function Mesh:getPolygon(index)
	local retVal = Polycore.Mesh_getPolygon(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Polygon"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:createPlane(w, h)
	local retVal = Polycore.Mesh_createPlane(self.__ptr, w, h)
end

function Mesh:createVPlane(w, h)
	local retVal = Polycore.Mesh_createVPlane(self.__ptr, w, h)
end

function Mesh:createTorus(radius, tubeRadius, rSegments, tSegments)
	local retVal = Polycore.Mesh_createTorus(self.__ptr, radius, tubeRadius, rSegments, tSegments)
end

function Mesh:createBox(w, d, h)
	local retVal = Polycore.Mesh_createBox(self.__ptr, w, d, h)
end

function Mesh:createSphere(radius, numRings, numSegments)
	local retVal = Polycore.Mesh_createSphere(self.__ptr, radius, numRings, numSegments)
end

function Mesh:createCylinder(height, radius, numSegments, capped)
	local retVal = Polycore.Mesh_createCylinder(self.__ptr, height, radius, numSegments, capped)
end

function Mesh:createCone(height, radius, numSegments)
	local retVal = Polycore.Mesh_createCone(self.__ptr, height, radius, numSegments)
end

function Mesh:recenterMesh()
	local retVal =  Polycore.Mesh_recenterMesh(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:useVertexNormals(val)
	local retVal = Polycore.Mesh_useVertexNormals(self.__ptr, val)
end

function Mesh:setVertexBuffer(buffer)
	local retVal = Polycore.Mesh_setVertexBuffer(self.__ptr, buffer.__ptr)
end

function Mesh:getVertexBuffer()
	local retVal =  Polycore.Mesh_getVertexBuffer(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["VertexBuffer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getRadius()
	local retVal =  Polycore.Mesh_getRadius(self.__ptr)
	return retVal
end

function Mesh:calculateNormals(smooth, smoothAngle)
	local retVal = Polycore.Mesh_calculateNormals(self.__ptr, smooth, smoothAngle)
end

function Mesh:calculateTangents()
	local retVal =  Polycore.Mesh_calculateTangents(self.__ptr)
end

function Mesh:getConnectedFaces(v)
	local retVal = Polycore.Mesh_getConnectedFaces(self.__ptr, v.__ptr)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Polygon"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function Mesh:getMeshType()
	local retVal =  Polycore.Mesh_getMeshType(self.__ptr)
	return retVal
end

function Mesh:setMeshType(newType)
	local retVal = Polycore.Mesh_setMeshType(self.__ptr, newType)
end

function Mesh:dirtyArray(arrayIndex)
	local retVal = Polycore.Mesh_dirtyArray(self.__ptr, arrayIndex)
end

function Mesh:dirtyArrays()
	local retVal =  Polycore.Mesh_dirtyArrays(self.__ptr)
end

function Mesh:calculateBBox()
	local retVal =  Polycore.Mesh_calculateBBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:hasVertexBuffer()
	local retVal =  Polycore.Mesh_hasVertexBuffer(self.__ptr)
	return retVal
end

function Mesh:__delete()
	if self then Polycore.delete_Mesh(self.__ptr) end
end
