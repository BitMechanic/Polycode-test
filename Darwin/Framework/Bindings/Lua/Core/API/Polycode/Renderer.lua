class "Renderer"



Renderer.RENDER_MODE_NORMAL = 0
Renderer.RENDER_MODE_WIREFRAME = 1
Renderer.BLEND_MODE_NORMAL = 0
Renderer.BLEND_MODE_LIGHTEN = 1
Renderer.BLEND_MODE_COLOR = 2
Renderer.BLEND_MODE_PREMULTIPLIED = 3
Renderer.BLEND_MODE_MULTIPLY = 4
Renderer.FOG_LINEAR = 0
Renderer.FOG_EXP = 1
Renderer.FOG_EXP2 = 2
Renderer.DEPTH_FUNCTION_GREATER = 0
Renderer.DEPTH_FUNCTION_LEQUAL = 1
Renderer.TEX_FILTERING_NEAREST = 0
Renderer.TEX_FILTERING_LINEAR = 1
function Renderer:__getvar(name)
	if name == "ambientColor" then
		local retVal = Polycore.Renderer_get_ambientColor(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "clearColor" then
		local retVal = Polycore.Renderer_get_clearColor(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "exposureLevel" then
		return Polycore.Renderer_get_exposureLevel(self.__ptr)
	elseif name == "cameraPosition" then
		local retVal = Polycore.Renderer_get_cameraPosition(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "doClearBuffer" then
		return Polycore.Renderer_get_doClearBuffer(self.__ptr)
	elseif name == "blendNormalAsPremultiplied" then
		return Polycore.Renderer_get_blendNormalAsPremultiplied(self.__ptr)
	end
end


function Renderer:__setvar(name,value)
	if name == "ambientColor" then
		Polycore.Renderer_set_ambientColor(self.__ptr, value.__ptr)
		return true
	elseif name == "clearColor" then
		Polycore.Renderer_set_clearColor(self.__ptr, value.__ptr)
		return true
	elseif name == "exposureLevel" then
		Polycore.Renderer_set_exposureLevel(self.__ptr, value)
		return true
	elseif name == "cameraPosition" then
		Polycore.Renderer_set_cameraPosition(self.__ptr, value.__ptr)
		return true
	elseif name == "doClearBuffer" then
		Polycore.Renderer_set_doClearBuffer(self.__ptr, value)
		return true
	elseif name == "blendNormalAsPremultiplied" then
		Polycore.Renderer_set_blendNormalAsPremultiplied(self.__ptr, value)
		return true
	end
	return false
end


function Renderer:Init()
	local retVal =  Polycore.Renderer_Init(self.__ptr)
	return retVal
end

function Renderer:Resize(xRes, yRes)
	local retVal = Polycore.Renderer_Resize(self.__ptr, xRes, yRes)
end

function Renderer:BeginRender()
	local retVal =  Polycore.Renderer_BeginRender(self.__ptr)
end

function Renderer:EndRender()
	local retVal =  Polycore.Renderer_EndRender(self.__ptr)
end

function Renderer:createCubemap(t0, t1, t2, t3, t4, t5)
	local retVal = Polycore.Renderer_createCubemap(self.__ptr, t0.__ptr, t1.__ptr, t2.__ptr, t3.__ptr, t4.__ptr, t5.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Cubemap"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createTexture(width, height, textureData, clamp, createMipmaps, type)
	local retVal = Polycore.Renderer_createTexture(self.__ptr, width, height, textureData.__ptr, clamp, createMipmaps, type)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:destroyTexture(texture)
	local retVal = Polycore.Renderer_destroyTexture(self.__ptr, texture.__ptr)
end

function Renderer:createRenderTextures(colorBuffer, depthBuffer, width, height, floatingPointBuffer)
	local retVal = Polycore.Renderer_createRenderTextures(self.__ptr, colorBuffer.__ptr, depthBuffer.__ptr, width, height, floatingPointBuffer)
end

function Renderer:createFramebufferTexture(width, height)
	local retVal = Polycore.Renderer_createFramebufferTexture(self.__ptr, width, height)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:bindFrameBufferTexture(texture)
	local retVal = Polycore.Renderer_bindFrameBufferTexture(self.__ptr, texture.__ptr)
end

function Renderer:bindFrameBufferTextureDepth(texture)
	local retVal = Polycore.Renderer_bindFrameBufferTextureDepth(self.__ptr, texture.__ptr)
end

function Renderer:unbindFramebuffers()
	local retVal =  Polycore.Renderer_unbindFramebuffers(self.__ptr)
end

function Renderer:renderScreenToImage()
	local retVal =  Polycore.Renderer_renderScreenToImage(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Image"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:setFOV(fov)
	local retVal = Polycore.Renderer_setFOV(self.__ptr, fov)
end

function Renderer:setViewportSize(w, h)
	local retVal = Polycore.Renderer_setViewportSize(self.__ptr, w, h)
end

function Renderer:setViewportSizeAndFOV(w, h, fov)
	local retVal = Polycore.Renderer_setViewportSizeAndFOV(self.__ptr, w, h, fov)
end

function Renderer:resetViewport()
	local retVal =  Polycore.Renderer_resetViewport(self.__ptr)
end

function Renderer:loadIdentity()
	local retVal =  Polycore.Renderer_loadIdentity(self.__ptr)
end

function Renderer:setOrthoMode(xSize, ySize, centered)
	local retVal = Polycore.Renderer_setOrthoMode(self.__ptr, xSize, ySize, centered)
end

function Renderer:_setOrthoMode(orthoSizeX, orthoSizeY)
	local retVal = Polycore.Renderer__setOrthoMode(self.__ptr, orthoSizeX, orthoSizeY)
end

function Renderer:setPerspectiveMode()
	local retVal =  Polycore.Renderer_setPerspectiveMode(self.__ptr)
end

function Renderer:setTexture(texture)
	local retVal = Polycore.Renderer_setTexture(self.__ptr, texture.__ptr)
end

function Renderer:enableBackfaceCulling(val)
	local retVal = Polycore.Renderer_enableBackfaceCulling(self.__ptr, val)
end

function Renderer:setClearColor(r, g, b, a)
	local retVal = Polycore.Renderer_setClearColor(self.__ptr, r, g, b, a)
end

function Renderer:setAmbientColor(r, g, b)
	local retVal = Polycore.Renderer_setAmbientColor(self.__ptr, r, g, b)
end

function Renderer:clearScreen()
	local retVal =  Polycore.Renderer_clearScreen(self.__ptr)
end

function Renderer:translate2D(x, y)
	local retVal = Polycore.Renderer_translate2D(self.__ptr, x, y)
end

function Renderer:rotate2D(angle)
	local retVal = Polycore.Renderer_rotate2D(self.__ptr, angle)
end

function Renderer:scale2D(scale)
	local retVal = Polycore.Renderer_scale2D(self.__ptr, scale.__ptr)
end

function Renderer:setVertexColor(r, g, b, a)
	local retVal = Polycore.Renderer_setVertexColor(self.__ptr, r, g, b, a)
end

function Renderer:pushDataArrayForMesh(mesh, arrayType)
	local retVal = Polycore.Renderer_pushDataArrayForMesh(self.__ptr, mesh.__ptr, arrayType)
end

function Renderer:pushRenderDataArray(array)
	local retVal = Polycore.Renderer_pushRenderDataArray(self.__ptr, array.__ptr)
end

function Renderer:createRenderDataArrayForMesh(mesh, arrayType)
	local retVal = Polycore.Renderer_createRenderDataArrayForMesh(self.__ptr, mesh.__ptr, arrayType)
	if retVal == nil then return nil end
	local __c = _G["RenderDataArray"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createRenderDataArray(arrayType)
	local retVal = Polycore.Renderer_createRenderDataArray(self.__ptr, arrayType)
	if retVal == nil then return nil end
	local __c = _G["RenderDataArray"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:setRenderArrayData(array, arrayData)
	local retVal = Polycore.Renderer_setRenderArrayData(self.__ptr, array.__ptr, arrayData.__ptr)
end

function Renderer:drawArrays(drawType)
	local retVal = Polycore.Renderer_drawArrays(self.__ptr, drawType)
end

function Renderer:translate3D(position)
	local retVal = Polycore.Renderer_translate3D(self.__ptr, position.__ptr)
end

function Renderer:scale3D(scale)
	local retVal = Polycore.Renderer_scale3D(self.__ptr, scale.__ptr)
end

function Renderer:pushMatrix()
	local retVal =  Polycore.Renderer_pushMatrix(self.__ptr)
end

function Renderer:popMatrix()
	local retVal =  Polycore.Renderer_popMatrix(self.__ptr)
end

function Renderer:setLineSmooth(val)
	local retVal = Polycore.Renderer_setLineSmooth(self.__ptr, val)
end

function Renderer:setLineSize(lineSize)
	local retVal = Polycore.Renderer_setLineSize(self.__ptr, lineSize)
end

function Renderer:enableLighting(enable)
	local retVal = Polycore.Renderer_enableLighting(self.__ptr, enable)
end

function Renderer:enableFog(enable)
	local retVal = Polycore.Renderer_enableFog(self.__ptr, enable)
end

function Renderer:setFogProperties(fogMode, color, density, startDepth, _endDepth)
	local retVal = Polycore.Renderer_setFogProperties(self.__ptr, fogMode, color.__ptr, density, startDepth, _endDepth)
end

function Renderer:multModelviewMatrix(m)
	local retVal = Polycore.Renderer_multModelviewMatrix(self.__ptr, m.__ptr)
end

function Renderer:setModelviewMatrix(m)
	local retVal = Polycore.Renderer_setModelviewMatrix(self.__ptr, m.__ptr)
end

function Renderer:setCurrentModelMatrix(m)
	local retVal = Polycore.Renderer_setCurrentModelMatrix(self.__ptr, m.__ptr)
end

function Renderer:getCurrentModelMatrix()
	local retVal =  Polycore.Renderer_getCurrentModelMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:setBlendingMode(bl_endingMode)
	local retVal = Polycore.Renderer_setBlendingMode(self.__ptr, bl_endingMode)
end

function Renderer:applyMaterial(material, localOptions, shaderIndex)
	local retVal = Polycore.Renderer_applyMaterial(self.__ptr, material.__ptr, localOptions.__ptr, shaderIndex)
end

function Renderer:clearShader()
	local retVal =  Polycore.Renderer_clearShader(self.__ptr)
end

function Renderer:setDepthFunction(depthFunction)
	local retVal = Polycore.Renderer_setDepthFunction(self.__ptr, depthFunction)
end

function Renderer:createVertexBufferForMesh(mesh)
	local retVal = Polycore.Renderer_createVertexBufferForMesh(self.__ptr, mesh.__ptr)
end

function Renderer:drawVertexBuffer(buffer, enableColorBuffer)
	local retVal = Polycore.Renderer_drawVertexBuffer(self.__ptr, buffer.__ptr, enableColorBuffer)
end

function Renderer:setRenderMode(newR_enderMode)
	local retVal = Polycore.Renderer_setRenderMode(self.__ptr, newR_enderMode)
end

function Renderer:getRenderMode()
	local retVal =  Polycore.Renderer_getRenderMode(self.__ptr)
	return retVal
end

function Renderer:enableDepthTest(val)
	local retVal = Polycore.Renderer_enableDepthTest(self.__ptr, val)
end

function Renderer:enableDepthWrite(val)
	local retVal = Polycore.Renderer_enableDepthWrite(self.__ptr, val)
end

function Renderer:billboardMatrix()
	local retVal =  Polycore.Renderer_billboardMatrix(self.__ptr)
end

function Renderer:billboardMatrixWithScale(scale)
	local retVal = Polycore.Renderer_billboardMatrixWithScale(self.__ptr, scale.__ptr)
end

function Renderer:setTextureFilteringMode(mode)
	local retVal = Polycore.Renderer_setTextureFilteringMode(self.__ptr, mode)
end

function Renderer:setClippingPlanes(nearPlane, farPlane)
	local retVal = Polycore.Renderer_setClippingPlanes(self.__ptr, nearPlane, farPlane)
end

function Renderer:enableAlphaTest(val)
	local retVal = Polycore.Renderer_enableAlphaTest(self.__ptr, val)
end

function Renderer:clearBuffer(colorBuffer, depthBuffer)
	local retVal = Polycore.Renderer_clearBuffer(self.__ptr, colorBuffer, depthBuffer)
end

function Renderer:drawToColorBuffer(val)
	local retVal = Polycore.Renderer_drawToColorBuffer(self.__ptr, val)
end

function Renderer:getCameraMatrix()
	local retVal =  Polycore.Renderer_getCameraMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:setCameraMatrix(matrix)
	local retVal = Polycore.Renderer_setCameraMatrix(self.__ptr, matrix.__ptr)
end

function Renderer:setCameraPosition(pos)
	local retVal = Polycore.Renderer_setCameraPosition(self.__ptr, pos.__ptr)
end

function Renderer:drawScreenQuad(qx, qy)
	local retVal = Polycore.Renderer_drawScreenQuad(self.__ptr, qx, qy)
end

function Renderer:getXRes()
	local retVal =  Polycore.Renderer_getXRes(self.__ptr)
	return retVal
end

function Renderer:getYRes()
	local retVal =  Polycore.Renderer_getYRes(self.__ptr)
	return retVal
end

function Renderer:isScissorEnabled()
	local retVal =  Polycore.Renderer_isScissorEnabled(self.__ptr)
	return retVal
end

function Renderer:enableScissor(val)
	local retVal = Polycore.Renderer_enableScissor(self.__ptr, val)
end

function Renderer:setScissorBox(box)
	local retVal = Polycore.Renderer_setScissorBox(self.__ptr, box.__ptr)
end

function Renderer:getScissorBox()
	local retVal =  Polycore.Renderer_getScissorBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Polycode::Rectangle"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:setAnisotropyAmount(amount)
	local retVal = Polycore.Renderer_setAnisotropyAmount(self.__ptr, amount)
end

function Renderer:getAnisotropyAmount()
	local retVal =  Polycore.Renderer_getAnisotropyAmount(self.__ptr)
	return retVal
end

function Renderer:cullFrontFaces(val)
	local retVal = Polycore.Renderer_cullFrontFaces(self.__ptr, val)
end

function Renderer:clearLights()
	local retVal =  Polycore.Renderer_clearLights(self.__ptr)
end

function Renderer:addLight(lightImportance, position, direction, type, color, specularColor, constantAttenuation, linearAttenuation, quadraticAttenuation, intensity, spotlightCutoff, spotlightExponent, shadowsEnabled, textureMatrix, shadowMapTexture)
	local retVal = Polycore.Renderer_addLight(self.__ptr, lightImportance, position.__ptr, direction.__ptr, type, color.__ptr, specularColor.__ptr, constantAttenuation, linearAttenuation, quadraticAttenuation, intensity, spotlightCutoff, spotlightExponent, shadowsEnabled, textureMatrix.__ptr, shadowMapTexture.__ptr)
end

function Renderer:setExposureLevel(level)
	local retVal = Polycore.Renderer_setExposureLevel(self.__ptr, level)
end

function Renderer:rayTriangleIntersect(ray_origin, ray_direction, vert0, vert1, vert2, hitPoint)
	local retVal = Polycore.Renderer_rayTriangleIntersect(self.__ptr, ray_origin.__ptr, ray_direction.__ptr, vert0.__ptr, vert1.__ptr, vert2.__ptr, hitPoint.__ptr)
	return retVal
end

function Renderer:projectRayFrom2DCoordinate(x, y, cameraMatrix, projectionMatrix)
	local retVal = Polycore.Renderer_projectRayFrom2DCoordinate(self.__ptr, x, y, cameraMatrix.__ptr, projectionMatrix.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:enableShaders(flag)
	local retVal = Polycore.Renderer_enableShaders(self.__ptr, flag)
end

function Renderer:getViewportWidth()
	local retVal =  Polycore.Renderer_getViewportWidth(self.__ptr)
	return retVal
end

function Renderer:getViewportHeight()
	local retVal =  Polycore.Renderer_getViewportHeight(self.__ptr)
	return retVal
end

function Renderer:setViewportShift(shiftX, shiftY)
	local retVal = Polycore.Renderer_setViewportShift(self.__ptr, shiftX, shiftY)
end

function Renderer:getDataPointerForName(name)
	local retVal = Polycore.Renderer_getDataPointerForName(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:setRendererShaderParams(shader, binding)
	local retVal = Polycore.Renderer_setRendererShaderParams(self.__ptr, shader.__ptr, binding.__ptr)
end

function Renderer:addShaderModule(module)
	local retVal = Polycore.Renderer_addShaderModule(self.__ptr, module.__ptr)
end

function Renderer:test2DCoordinateInPolygon(x, y, cameraMatrix, projectionMatrix, poly, matrix, ortho, testBackfacing, billboardMode, reverseDirection, adjustMatrix)
	local retVal = Polycore.Renderer_test2DCoordinateInPolygon(self.__ptr, x, y, cameraMatrix.__ptr, projectionMatrix.__ptr, poly.__ptr, matrix.__ptr, ortho, testBackfacing, billboardMode, reverseDirection, adjustMatrix.__ptr)
	return retVal
end

function Renderer:getProjectionMatrix()
	local retVal =  Polycore.Renderer_getProjectionMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:getModelviewMatrix()
	local retVal =  Polycore.Renderer_getModelviewMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:Unproject(x, y)
	local retVal = Polycore.Renderer_Unproject(self.__ptr, x, y)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:sortLights()
	local retVal =  Polycore.Renderer_sortLights(self.__ptr)
end

function Renderer:getNumAreaLights()
	local retVal =  Polycore.Renderer_getNumAreaLights(self.__ptr)
	return retVal
end

function Renderer:getNumSpotLights()
	local retVal =  Polycore.Renderer_getNumSpotLights(self.__ptr)
	return retVal
end

function Renderer:getNumLights()
	local retVal =  Polycore.Renderer_getNumLights(self.__ptr)
	return retVal
end

function Renderer:getAreaLights()
	local retVal =  Polycore.Renderer_getAreaLights(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["std::vector<LightInfo>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:getSpotLights()
	local retVal =  Polycore.Renderer_getSpotLights(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["std::vector<LightInfo>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:__delete()
	if self then Polycore.delete_Renderer(self.__ptr) end
end
