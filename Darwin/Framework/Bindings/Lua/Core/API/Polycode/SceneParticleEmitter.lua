require "Polycode/SceneEntity"

require "Polycode/ParticleEmitter"

class "SceneParticleEmitter" (SceneEntity)



SceneParticleEmitter.CONTINUOUS_EMITTER = 0
SceneParticleEmitter.TRIGGERED_EMITTER = 1




function SceneParticleEmitter:SceneParticleEmitter(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "SceneEntity" then
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
		self.__ptr = Polycore.SceneParticleEmitter(unpack(arg))
	end
end

function SceneParticleEmitter:getEmitter()
	local retVal =  Polycore.SceneParticleEmitter_getEmitter(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ParticleEmitter"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:respawnSceneParticles()
	local retVal =  Polycore.SceneParticleEmitter_respawnSceneParticles(self.__ptr)
end

function SceneParticleEmitter:addParticleBody(particleBody)
	local retVal = Polycore.SceneParticleEmitter_addParticleBody(self.__ptr, particleBody.__ptr)
end

function SceneParticleEmitter:getBaseMatrix()
	local retVal =  Polycore.SceneParticleEmitter_getBaseMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:Update()
	local retVal =  Polycore.SceneParticleEmitter_Update(self.__ptr)
end

function SceneParticleEmitter:getParticleCompoundScale()
	local retVal =  Polycore.SceneParticleEmitter_getParticleCompoundScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:dispatchTriggerCompleteEvent()
	local retVal =  Polycore.SceneParticleEmitter_dispatchTriggerCompleteEvent(self.__ptr)
end

function SceneParticleEmitter:__delete()
	if self then Polycore.delete_SceneParticleEmitter(self.__ptr) end
end
