class "ParticleEmitter"



ParticleEmitter.CONTINUOUS_EMITTER = 0
ParticleEmitter.TRIGGERED_EMITTER = 1
function ParticleEmitter:__getvar(name)
	if name == "particleSpeedMod" then
		return Polycore.ParticleEmitter_get_particleSpeedMod(self.__ptr)
	elseif name == "brightnessDeviation" then
		return Polycore.ParticleEmitter_get_brightnessDeviation(self.__ptr)
	elseif name == "deviation" then
		local retVal = Polycore.ParticleEmitter_get_deviation(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "dirVector" then
		local retVal = Polycore.ParticleEmitter_get_dirVector(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "gravVector" then
		local retVal = Polycore.ParticleEmitter_get_gravVector(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "lifespan" then
		return Polycore.ParticleEmitter_get_lifespan(self.__ptr)
	elseif name == "rotationFollowsPath" then
		return Polycore.ParticleEmitter_get_rotationFollowsPath(self.__ptr)
	elseif name == "scaleCurve" then
		local retVal = Polycore.ParticleEmitter_get_scaleCurve(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveR" then
		local retVal = Polycore.ParticleEmitter_get_colorCurveR(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveG" then
		local retVal = Polycore.ParticleEmitter_get_colorCurveG(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveB" then
		local retVal = Polycore.ParticleEmitter_get_colorCurveB(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveA" then
		local retVal = Polycore.ParticleEmitter_get_colorCurveA(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "useColorCurves" then
		return Polycore.ParticleEmitter_get_useColorCurves(self.__ptr)
	elseif name == "useScaleCurves" then
		return Polycore.ParticleEmitter_get_useScaleCurves(self.__ptr)
	elseif name == "particleSize" then
		return Polycore.ParticleEmitter_get_particleSize(self.__ptr)
	elseif name == "emitterRadius" then
		local retVal = Polycore.ParticleEmitter_get_emitterRadius(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "perlinModSize" then
		return Polycore.ParticleEmitter_get_perlinModSize(self.__ptr)
	elseif name == "perlinEnabled" then
		return Polycore.ParticleEmitter_get_perlinEnabled(self.__ptr)
	elseif name == "rotationSpeed" then
		return Polycore.ParticleEmitter_get_rotationSpeed(self.__ptr)
	elseif name == "emitterType" then
		return Polycore.ParticleEmitter_get_emitterType(self.__ptr)
	end
end


function ParticleEmitter:__setvar(name,value)
	if name == "particleSpeedMod" then
		Polycore.ParticleEmitter_set_particleSpeedMod(self.__ptr, value)
		return true
	elseif name == "brightnessDeviation" then
		Polycore.ParticleEmitter_set_brightnessDeviation(self.__ptr, value)
		return true
	elseif name == "deviation" then
		Polycore.ParticleEmitter_set_deviation(self.__ptr, value.__ptr)
		return true
	elseif name == "dirVector" then
		Polycore.ParticleEmitter_set_dirVector(self.__ptr, value.__ptr)
		return true
	elseif name == "gravVector" then
		Polycore.ParticleEmitter_set_gravVector(self.__ptr, value.__ptr)
		return true
	elseif name == "lifespan" then
		Polycore.ParticleEmitter_set_lifespan(self.__ptr, value)
		return true
	elseif name == "rotationFollowsPath" then
		Polycore.ParticleEmitter_set_rotationFollowsPath(self.__ptr, value)
		return true
	elseif name == "scaleCurve" then
		Polycore.ParticleEmitter_set_scaleCurve(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveR" then
		Polycore.ParticleEmitter_set_colorCurveR(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveG" then
		Polycore.ParticleEmitter_set_colorCurveG(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveB" then
		Polycore.ParticleEmitter_set_colorCurveB(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveA" then
		Polycore.ParticleEmitter_set_colorCurveA(self.__ptr, value.__ptr)
		return true
	elseif name == "useColorCurves" then
		Polycore.ParticleEmitter_set_useColorCurves(self.__ptr, value)
		return true
	elseif name == "useScaleCurves" then
		Polycore.ParticleEmitter_set_useScaleCurves(self.__ptr, value)
		return true
	elseif name == "particleSize" then
		Polycore.ParticleEmitter_set_particleSize(self.__ptr, value)
		return true
	elseif name == "emitterRadius" then
		Polycore.ParticleEmitter_set_emitterRadius(self.__ptr, value.__ptr)
		return true
	elseif name == "perlinModSize" then
		Polycore.ParticleEmitter_set_perlinModSize(self.__ptr, value)
		return true
	elseif name == "perlinEnabled" then
		Polycore.ParticleEmitter_set_perlinEnabled(self.__ptr, value)
		return true
	elseif name == "rotationSpeed" then
		Polycore.ParticleEmitter_set_rotationSpeed(self.__ptr, value)
		return true
	elseif name == "emitterType" then
		Polycore.ParticleEmitter_set_emitterType(self.__ptr, value)
		return true
	end
	return false
end


function ParticleEmitter:ParticleEmitter(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ParticleEmitter(unpack(arg))
	end
end

function ParticleEmitter:dispatchTriggerCompleteEvent()
	local retVal =  Polycore.ParticleEmitter_dispatchTriggerCompleteEvent(self.__ptr)
end

function ParticleEmitter:createParticles()
	local retVal =  Polycore.ParticleEmitter_createParticles(self.__ptr)
end

function ParticleEmitter:setRotationSpeed(speed)
	local retVal = Polycore.ParticleEmitter_setRotationSpeed(self.__ptr, speed)
end

function ParticleEmitter:setParticleBlendingMode(mode)
	local retVal = Polycore.ParticleEmitter_setParticleBlendingMode(self.__ptr, mode)
end

function ParticleEmitter:getParticleBlendingMode()
	local retVal =  Polycore.ParticleEmitter_getParticleBlendingMode(self.__ptr)
	return retVal
end

function ParticleEmitter:setDepthWrite(val)
	local retVal = Polycore.ParticleEmitter_setDepthWrite(self.__ptr, val)
end

function ParticleEmitter:setDepthTest(val)
	local retVal = Polycore.ParticleEmitter_setDepthTest(self.__ptr, val)
end

function ParticleEmitter:setAlphaTest(val)
	local retVal = Polycore.ParticleEmitter_setAlphaTest(self.__ptr, val)
end

function ParticleEmitter:enablePerlin(val)
	local retVal = Polycore.ParticleEmitter_enablePerlin(self.__ptr, val)
end

function ParticleEmitter:setParticleVisibility(val)
	local retVal = Polycore.ParticleEmitter_setParticleVisibility(self.__ptr, val)
end

function ParticleEmitter:setPerlinModSize(size)
	local retVal = Polycore.ParticleEmitter_setPerlinModSize(self.__ptr, size)
end

function ParticleEmitter:setBillboardMode(mode)
	local retVal = Polycore.ParticleEmitter_setBillboardMode(self.__ptr, mode)
end

function ParticleEmitter:enableEmitter(val)
	local retVal = Polycore.ParticleEmitter_enableEmitter(self.__ptr, val)
end

function ParticleEmitter:emitterEnabled()
	local retVal =  Polycore.ParticleEmitter_emitterEnabled(self.__ptr)
	return retVal
end

function ParticleEmitter:setEmitterRadius(rad)
	local retVal = Polycore.ParticleEmitter_setEmitterRadius(self.__ptr, rad.__ptr)
end

function ParticleEmitter:setAllAtOnce(val)
	local retVal = Polycore.ParticleEmitter_setAllAtOnce(self.__ptr, val)
end

function ParticleEmitter:getNumParticles()
	local retVal =  Polycore.ParticleEmitter_getNumParticles(self.__ptr)
	return retVal
end

function ParticleEmitter:getParticleAtIndex(index)
	local retVal = Polycore.ParticleEmitter_getParticleAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Particle"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ParticleEmitter:resetAll()
	local retVal =  Polycore.ParticleEmitter_resetAll(self.__ptr)
end

function ParticleEmitter:Trigger()
	local retVal =  Polycore.ParticleEmitter_Trigger(self.__ptr)
end

function ParticleEmitter:resetParticle(particle)
	local retVal = Polycore.ParticleEmitter_resetParticle(self.__ptr, particle.__ptr)
end

function ParticleEmitter:setParticleCount(count)
	local retVal = Polycore.ParticleEmitter_setParticleCount(self.__ptr, count)
end

function ParticleEmitter:getParticleCompoundScale()
	local retVal =  Polycore.ParticleEmitter_getParticleCompoundScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ParticleEmitter:addParticleBody(particleBody)
	local retVal = Polycore.ParticleEmitter_addParticleBody(self.__ptr, particleBody.__ptr)
end

function ParticleEmitter:getBaseMatrix()
	local retVal =  Polycore.ParticleEmitter_getBaseMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ParticleEmitter:updateEmitter()
	local retVal =  Polycore.ParticleEmitter_updateEmitter(self.__ptr)
end

function ParticleEmitter:getParticleTexture()
	local retVal =  Polycore.ParticleEmitter_getParticleTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ParticleEmitter:setParticleTexture(texture)
	local retVal = Polycore.ParticleEmitter_setParticleTexture(self.__ptr, texture.__ptr)
end

function ParticleEmitter:getIgnoreParentMatrix()
	local retVal =  Polycore.ParticleEmitter_getIgnoreParentMatrix(self.__ptr)
	return retVal
end

function ParticleEmitter:setIgnoreParentMatrix(val)
	local retVal = Polycore.ParticleEmitter_setIgnoreParentMatrix(self.__ptr, val)
end

function ParticleEmitter:__delete()
	if self then Polycore.delete_ParticleEmitter(self.__ptr) end
end
