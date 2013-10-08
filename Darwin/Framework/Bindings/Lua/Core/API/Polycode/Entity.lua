require "Polycode/EventDispatcher"

class "Entity" (EventDispatcher)



function Entity:__getvar(name)
	if name == "ownsChildren" then
		return Polycore.Entity_get_ownsChildren(self.__ptr)
	elseif name == "custEntityType" then
		return Polycore.Entity_get_custEntityType(self.__ptr)
	elseif name == "billboardMode" then
		return Polycore.Entity_get_billboardMode(self.__ptr)
	elseif name == "billboardRoll" then
		return Polycore.Entity_get_billboardRoll(self.__ptr)
	elseif name == "billboardIgnoreScale" then
		return Polycore.Entity_get_billboardIgnoreScale(self.__ptr)
	elseif name == "alphaTest" then
		return Polycore.Entity_get_alphaTest(self.__ptr)
	elseif name == "backfaceCulled" then
		return Polycore.Entity_get_backfaceCulled(self.__ptr)
	elseif name == "renderWireframe" then
		return Polycore.Entity_get_renderWireframe(self.__ptr)
	elseif name == "color" then
		local retVal = Polycore.Entity_get_color(self.__ptr)
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "enabled" then
		return Polycore.Entity_get_enabled(self.__ptr)
	elseif name == "visible" then
		return Polycore.Entity_get_visible(self.__ptr)
	elseif name == "depthWrite" then
		return Polycore.Entity_get_depthWrite(self.__ptr)
	elseif name == "depthTest" then
		return Polycore.Entity_get_depthTest(self.__ptr)
	elseif name == "blendingMode" then
		return Polycore.Entity_get_blendingMode(self.__ptr)
	elseif name == "colorAffectsChildren" then
		return Polycore.Entity_get_colorAffectsChildren(self.__ptr)
	elseif name == "visibilityAffectsChildren" then
		return Polycore.Entity_get_visibilityAffectsChildren(self.__ptr)
	elseif name == "depthOnly" then
		return Polycore.Entity_get_depthOnly(self.__ptr)
	elseif name == "bBox" then
		local retVal = Polycore.Entity_get_bBox(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "ignoreParentMatrix" then
		return Polycore.Entity_get_ignoreParentMatrix(self.__ptr)
	elseif name == "enableScissor" then
		return Polycore.Entity_get_enableScissor(self.__ptr)
	elseif name == "scissorBox" then
		local retVal = Polycore.Entity_get_scissorBox(self.__ptr)
		local __c = _G["Rectangle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "position" then
		local retVal = Polycore.Entity_get_position(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "scale" then
		local retVal = Polycore.Entity_get_scale(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "rotation" then
		local retVal = Polycore.Entity_get_rotation(self.__ptr)
		local __c = _G["Rotation"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "editorOnly" then
		return Polycore.Entity_get_editorOnly(self.__ptr)
	elseif name == "id" then
		return Polycore.Entity_get_id(self.__ptr)
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function Entity:__setvar(name,value)
	if name == "ownsChildren" then
		Polycore.Entity_set_ownsChildren(self.__ptr, value)
		return true
	elseif name == "custEntityType" then
		Polycore.Entity_set_custEntityType(self.__ptr, value)
		return true
	elseif name == "billboardMode" then
		Polycore.Entity_set_billboardMode(self.__ptr, value)
		return true
	elseif name == "billboardRoll" then
		Polycore.Entity_set_billboardRoll(self.__ptr, value)
		return true
	elseif name == "billboardIgnoreScale" then
		Polycore.Entity_set_billboardIgnoreScale(self.__ptr, value)
		return true
	elseif name == "alphaTest" then
		Polycore.Entity_set_alphaTest(self.__ptr, value)
		return true
	elseif name == "backfaceCulled" then
		Polycore.Entity_set_backfaceCulled(self.__ptr, value)
		return true
	elseif name == "renderWireframe" then
		Polycore.Entity_set_renderWireframe(self.__ptr, value)
		return true
	elseif name == "color" then
		Polycore.Entity_set_color(self.__ptr, value.__ptr)
		return true
	elseif name == "enabled" then
		Polycore.Entity_set_enabled(self.__ptr, value)
		return true
	elseif name == "visible" then
		Polycore.Entity_set_visible(self.__ptr, value)
		return true
	elseif name == "depthWrite" then
		Polycore.Entity_set_depthWrite(self.__ptr, value)
		return true
	elseif name == "depthTest" then
		Polycore.Entity_set_depthTest(self.__ptr, value)
		return true
	elseif name == "blendingMode" then
		Polycore.Entity_set_blendingMode(self.__ptr, value)
		return true
	elseif name == "colorAffectsChildren" then
		Polycore.Entity_set_colorAffectsChildren(self.__ptr, value)
		return true
	elseif name == "visibilityAffectsChildren" then
		Polycore.Entity_set_visibilityAffectsChildren(self.__ptr, value)
		return true
	elseif name == "depthOnly" then
		Polycore.Entity_set_depthOnly(self.__ptr, value)
		return true
	elseif name == "bBox" then
		Polycore.Entity_set_bBox(self.__ptr, value.__ptr)
		return true
	elseif name == "ignoreParentMatrix" then
		Polycore.Entity_set_ignoreParentMatrix(self.__ptr, value)
		return true
	elseif name == "enableScissor" then
		Polycore.Entity_set_enableScissor(self.__ptr, value)
		return true
	elseif name == "scissorBox" then
		Polycore.Entity_set_scissorBox(self.__ptr, value.__ptr)
		return true
	elseif name == "position" then
		Polycore.Entity_set_position(self.__ptr, value.__ptr)
		return true
	elseif name == "scale" then
		Polycore.Entity_set_scale(self.__ptr, value.__ptr)
		return true
	elseif name == "rotation" then
		Polycore.Entity_set_rotation(self.__ptr, value.__ptr)
		return true
	elseif name == "editorOnly" then
		Polycore.Entity_set_editorOnly(self.__ptr, value)
		return true
	elseif name == "id" then
		Polycore.Entity_set_id(self.__ptr, value)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function Entity:Entity(...)
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
		self.__ptr = Polycore.Entity(unpack(arg))
	end
end

function Entity:Render()
	local retVal =  Polycore.Entity_Render(self.__ptr)
end

function Entity:Update()
	local retVal =  Polycore.Entity_Update(self.__ptr)
end

function Entity:transformAndRender()
	local retVal =  Polycore.Entity_transformAndRender(self.__ptr)
end

function Entity:renderChildren()
	local retVal =  Polycore.Entity_renderChildren(self.__ptr)
end

function Entity:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.Entity_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.Entity_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function Entity:dirtyMatrix(val)
	local retVal = Polycore.Entity_dirtyMatrix(self.__ptr, val)
end

function Entity:rebuildTransformMatrix()
	local retVal =  Polycore.Entity_rebuildTransformMatrix(self.__ptr)
end

function Entity:updateEntityMatrix()
	local retVal =  Polycore.Entity_updateEntityMatrix(self.__ptr)
end

function Entity:getTransformMatrix()
	local retVal =  Polycore.Entity_getTransformMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedMatrix()
	local retVal =  Polycore.Entity_getConcatenatedMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedMatrixRelativeTo(relativeEntity)
	local retVal = Polycore.Entity_getConcatenatedMatrixRelativeTo(self.__ptr, relativeEntity.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedRollMatrix()
	local retVal =  Polycore.Entity_getConcatenatedRollMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setTransformByMatrixPure(matrix)
	local retVal = Polycore.Entity_setTransformByMatrixPure(self.__ptr, matrix.__ptr)
end

function Entity:getLookAtMatrix(loc, upVector)
	local retVal = Polycore.Entity_getLookAtMatrix(self.__ptr, loc.__ptr, upVector.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:moveChildUp(child)
	local retVal = Polycore.Entity_moveChildUp(self.__ptr, child.__ptr)
end

function Entity:moveChildDown(child)
	local retVal = Polycore.Entity_moveChildDown(self.__ptr, child.__ptr)
end

function Entity:moveChildTop(child)
	local retVal = Polycore.Entity_moveChildTop(self.__ptr, child.__ptr)
end

function Entity:moveChildBottom(child)
	local retVal = Polycore.Entity_moveChildBottom(self.__ptr, child.__ptr)
end

function Entity:addEntity(newChild)
	local retVal = Polycore.Entity_addEntity(self.__ptr, newChild.__ptr)
end

function Entity:addChild(newChild)
	local retVal = Polycore.Entity_addChild(self.__ptr, newChild.__ptr)
end

function Entity:removeChild(entityToRemove)
	local retVal = Polycore.Entity_removeChild(self.__ptr, entityToRemove.__ptr)
end

function Entity:setParentEntity(entity)
	local retVal = Polycore.Entity_setParentEntity(self.__ptr, entity.__ptr)
end

function Entity:getParentEntity()
	local retVal =  Polycore.Entity_getParentEntity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getNumChildren()
	local retVal =  Polycore.Entity_getNumChildren(self.__ptr)
	return retVal
end

function Entity:getChildAtIndex(index)
	local retVal = Polycore.Entity_getChildAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setOwnsChildrenRecursive(val)
	local retVal = Polycore.Entity_setOwnsChildrenRecursive(self.__ptr, val)
end

function Entity:getPosition()
	local retVal =  Polycore.Entity_getPosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getCombinedPosition()
	local retVal =  Polycore.Entity_getCombinedPosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setPosition(x, y, z)
	local retVal = Polycore.Entity_setPosition(self.__ptr, x, y, z)
end

function Entity:setPositionX(x)
	local retVal = Polycore.Entity_setPositionX(self.__ptr, x)
end

function Entity:setPositionY(y)
	local retVal = Polycore.Entity_setPositionY(self.__ptr, y)
end

function Entity:Translate(x, y, z)
	local retVal = Polycore.Entity_Translate(self.__ptr, x, y, z)
end

function Entity:setPositionZ(z)
	local retVal = Polycore.Entity_setPositionZ(self.__ptr, z)
end

function Entity:setScaleX(x)
	local retVal = Polycore.Entity_setScaleX(self.__ptr, x)
end

function Entity:setScaleY(y)
	local retVal = Polycore.Entity_setScaleY(self.__ptr, y)
end

function Entity:setScaleZ(z)
	local retVal = Polycore.Entity_setScaleZ(self.__ptr, z)
end

function Entity:Scale(x, y, z)
	local retVal = Polycore.Entity_Scale(self.__ptr, x, y, z)
end

function Entity:setScale(x, y, z)
	local retVal = Polycore.Entity_setScale(self.__ptr, x, y, z)
end

function Entity:getCompoundScale()
	local retVal =  Polycore.Entity_getCompoundScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getScale()
	local retVal =  Polycore.Entity_getScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getCombinedPitch()
	local retVal =  Polycore.Entity_getCombinedPitch(self.__ptr)
	return retVal
end

function Entity:getCombinedYaw()
	local retVal =  Polycore.Entity_getCombinedYaw(self.__ptr)
	return retVal
end

function Entity:getCombinedRoll()
	local retVal =  Polycore.Entity_getCombinedRoll(self.__ptr)
	return retVal
end

function Entity:rebuildRotation()
	local retVal =  Polycore.Entity_rebuildRotation(self.__ptr)
end

function Entity:setPitch(pitch)
	local retVal = Polycore.Entity_setPitch(self.__ptr, pitch)
end

function Entity:setYaw(yaw)
	local retVal = Polycore.Entity_setYaw(self.__ptr, yaw)
end

function Entity:setRoll(roll)
	local retVal = Polycore.Entity_setRoll(self.__ptr, roll)
end

function Entity:Roll(roll)
	local retVal = Polycore.Entity_Roll(self.__ptr, roll)
end

function Entity:Yaw(yaw)
	local retVal = Polycore.Entity_Yaw(self.__ptr, yaw)
end

function Entity:Pitch(pitch)
	local retVal = Polycore.Entity_Pitch(self.__ptr, pitch)
end

function Entity:getPitch()
	local retVal =  Polycore.Entity_getPitch(self.__ptr)
	return retVal
end

function Entity:getYaw()
	local retVal =  Polycore.Entity_getYaw(self.__ptr)
	return retVal
end

function Entity:getRoll()
	local retVal =  Polycore.Entity_getRoll(self.__ptr)
	return retVal
end

function Entity:setRotationQuat(w, x, y, z)
	local retVal = Polycore.Entity_setRotationQuat(self.__ptr, w, x, y, z)
end

function Entity:getRotationQuat()
	local retVal =  Polycore.Entity_getRotationQuat(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:lookAt(loc, upVector)
	local retVal = Polycore.Entity_lookAt(self.__ptr, loc.__ptr, upVector.__ptr)
end

function Entity:lookAtEntity(entity, upVector)
	local retVal = Polycore.Entity_lookAtEntity(self.__ptr, entity.__ptr, upVector.__ptr)
end

function Entity:getCombinedColor()
	local retVal =  Polycore.Entity_getCombinedColor(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setColor(r, g, b, a)
	local retVal = Polycore.Entity_setColor(self.__ptr, r, g, b, a)
end

function Entity:setColorInt(r, g, b, a)
	local retVal = Polycore.Entity_setColorInt(self.__ptr, r, g, b, a)
end

function Entity:recalculateBBox()
	local retVal =  Polycore.Entity_recalculateBBox(self.__ptr)
end

function Entity:getBBoxRadius()
	local retVal =  Polycore.Entity_getBBoxRadius(self.__ptr)
	return retVal
end

function Entity:getCompoundBBoxRadius()
	local retVal =  Polycore.Entity_getCompoundBBoxRadius(self.__ptr)
	return retVal
end

function Entity:setBBoxRadius(rad)
	local retVal = Polycore.Entity_setBBoxRadius(self.__ptr, rad)
end

function Entity:setUserData(userData)
	local retVal = Polycore.Entity_setUserData(self.__ptr, userData.__ptr)
end

function Entity:getUserData()
	local retVal =  Polycore.Entity_getUserData(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setBlendingMode(newBl_endingMode)
	local retVal = Polycore.Entity_setBlendingMode(self.__ptr, newBl_endingMode)
end

function Entity:getEntityById(id, recursive)
	local retVal = Polycore.Entity_getEntityById(self.__ptr, id, recursive)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getEntitiesByTag(tag, recursive)
	local retVal = Polycore.Entity_getEntitiesByTag(self.__ptr, tag, recursive)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Entity"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function Entity:getChildCenter()
	local retVal =  Polycore.Entity_getChildCenter(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getEntityProp(propName)
	local retVal = Polycore.Entity_getEntityProp(self.__ptr, propName)
	return retVal
end

function Entity:setEntityProp(propName, propValue)
	local retVal = Polycore.Entity_setEntityProp(self.__ptr, propName, propValue)
end

function Entity:doUpdates()
	local retVal =  Polycore.Entity_doUpdates(self.__ptr)
end

function Entity:buildPositionMatrix()
	local retVal =  Polycore.Entity_buildPositionMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:adjustMatrixForChildren()
	local retVal =  Polycore.Entity_adjustMatrixForChildren(self.__ptr)
end

function Entity:setRenderer(r_enderer)
	local retVal = Polycore.Entity_setRenderer(self.__ptr, r_enderer.__ptr)
end

function Entity:getNumTags()
	local retVal =  Polycore.Entity_getNumTags(self.__ptr)
	return retVal
end

function Entity:getTagAtIndex(index)
	local retVal = Polycore.Entity_getTagAtIndex(self.__ptr, index)
	return retVal
end

function Entity:hasTag(tag)
	local retVal = Polycore.Entity_hasTag(self.__ptr, tag)
	return retVal
end

function Entity:clearTags()
	local retVal =  Polycore.Entity_clearTags(self.__ptr)
end

function Entity:addTag(tag)
	local retVal = Polycore.Entity_addTag(self.__ptr, tag)
end

function Entity:__delete()
	if self then Polycore.delete_Entity(self.__ptr) end
end
