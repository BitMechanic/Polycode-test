require "Polycode/ScreenEntity"

require "Polycode/ParticleEmitter"

class "ScreenParticleEmitter" (ScreenEntity)



ScreenParticleEmitter.CONTINUOUS_EMITTER = 0
ScreenParticleEmitter.TRIGGERED_EMITTER = 1




function ScreenParticleEmitter:ScreenParticleEmitter(...)
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
		self.__ptr = Polycore.ScreenParticleEmitter(unpack(arg))
	end
end

function ScreenParticleEmitter:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenParticleEmitter_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenParticleEmitter:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.ScreenParticleEmitter_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function ScreenParticleEmitter:getEmitter()
	local retVal =  Polycore.ScreenParticleEmitter_getEmitter(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ParticleEmitter"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenParticleEmitter:dispatchTriggerCompleteEvent()
	local retVal =  Polycore.ScreenParticleEmitter_dispatchTriggerCompleteEvent(self.__ptr)
end

function ScreenParticleEmitter:addParticleBody(particleBody)
	local retVal = Polycore.ScreenParticleEmitter_addParticleBody(self.__ptr, particleBody.__ptr)
end

function ScreenParticleEmitter:getBaseMatrix()
	local retVal =  Polycore.ScreenParticleEmitter_getBaseMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenParticleEmitter:Update()
	local retVal =  Polycore.ScreenParticleEmitter_Update(self.__ptr)
end

function ScreenParticleEmitter:getParticleCompoundScale()
	local retVal =  Polycore.ScreenParticleEmitter_getParticleCompoundScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenParticleEmitter:__delete()
	if self then Polycore.delete_ScreenParticleEmitter(self.__ptr) end
end
