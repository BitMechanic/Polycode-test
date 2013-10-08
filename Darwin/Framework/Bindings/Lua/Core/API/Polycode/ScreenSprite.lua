require "Polycode/ScreenShape"

class "ScreenSprite" (ScreenShape)







function ScreenSprite:ScreenSprite(...)
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
		self.__ptr = Polycore.ScreenSprite(unpack(arg))
	end
end

function ScreenSprite.ScreenSpriteFromImageFile(fileName, spriteWidth, spriteHeight)
	local retVal = Polycore.ScreenSprite_ScreenSpriteFromImageFile(fileName, spriteWidth, spriteHeight)
	if retVal == nil then return nil end
	local __c = _G["ScreenSprite"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSprite:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenSprite_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSprite:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenSprite_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function ScreenSprite:addAnimation(name, frames, speed)
	local retVal = Polycore.ScreenSprite_addAnimation(self.__ptr, name, frames, speed)
	if retVal == nil then return nil end
	local __c = _G["SpriteAnimation"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSprite:showFrame(frameIndex)
	local retVal = Polycore.ScreenSprite_showFrame(self.__ptr, frameIndex)
end

function ScreenSprite:playAnimation(name, startFrame, once)
	local retVal = Polycore.ScreenSprite_playAnimation(self.__ptr, name, startFrame, once)
end

function ScreenSprite:Update()
	local retVal =  Polycore.ScreenSprite_Update(self.__ptr)
end

function ScreenSprite:setSpriteSize(spriteWidth, spriteHeight)
	local retVal = Polycore.ScreenSprite_setSpriteSize(self.__ptr, spriteWidth, spriteHeight)
end

function ScreenSprite:getSpriteSize()
	local retVal =  Polycore.ScreenSprite_getSpriteSize(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSprite:getFileName()
	local retVal =  Polycore.ScreenSprite_getFileName(self.__ptr)
	return retVal
end

function ScreenSprite:recalculateSpriteDimensions()
	local retVal =  Polycore.ScreenSprite_recalculateSpriteDimensions(self.__ptr)
end

function ScreenSprite:loadFromFile(fileName)
	local retVal = Polycore.ScreenSprite_loadFromFile(self.__ptr, fileName)
	return retVal
end

function ScreenSprite:reloadSprite()
	local retVal =  Polycore.ScreenSprite_reloadSprite(self.__ptr)
end

function ScreenSprite:Pause(val)
	local retVal = Polycore.ScreenSprite_Pause(self.__ptr, val)
end

function ScreenSprite:getNumAnimations()
	local retVal =  Polycore.ScreenSprite_getNumAnimations(self.__ptr)
	return retVal
end

function ScreenSprite:getAnimationAtIndex(index)
	local retVal = Polycore.ScreenSprite_getAnimationAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["SpriteAnimation"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSprite:getCurrentAnimation()
	local retVal =  Polycore.ScreenSprite_getCurrentAnimation(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SpriteAnimation"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSprite:getCurrentAnimationFrame()
	local retVal =  Polycore.ScreenSprite_getCurrentAnimationFrame(self.__ptr)
	return retVal
end

function ScreenSprite:isCurrentAnimationFinished()
	local retVal =  Polycore.ScreenSprite_isCurrentAnimationFinished(self.__ptr)
	return retVal
end

function ScreenSprite:updateSprite()
	local retVal =  Polycore.ScreenSprite_updateSprite(self.__ptr)
end

function ScreenSprite:getResourceEntry()
	local retVal =  Polycore.ScreenSprite_getResourceEntry(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenSpriteResourceEntry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenSprite:__delete()
	if self then Polycore.delete_ScreenSprite(self.__ptr) end
end
