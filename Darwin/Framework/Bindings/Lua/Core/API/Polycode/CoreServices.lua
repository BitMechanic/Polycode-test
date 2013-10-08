require "Polycode/EventDispatcher"

class "CoreServices" (EventDispatcher)



function CoreServices:__getvar(name)
	if name == "focusedChild" then
		local retVal = Polycore.CoreServices_get_focusedChild(self.__ptr)
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function CoreServices:__setvar(name,value)
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function CoreServices.getInstance()
	local retVal =  Polycore.CoreServices_getInstance()
	if retVal == nil then return nil end
	local __c = _G["CoreServices"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices.setInstance(_instance)
	local retVal = Polycore.CoreServices_setInstance(_instance.__ptr)
end

function CoreServices.getRenderMutex()
	local retVal =  Polycore.CoreServices_getRenderMutex()
	if retVal == nil then return nil end
	local __c = _G["CoreMutex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:setRenderer(r_enderer)
	local retVal = Polycore.CoreServices_setRenderer(self.__ptr, r_enderer.__ptr)
end

function CoreServices:getRenderer()
	local retVal =  Polycore.CoreServices_getRenderer(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Renderer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:Update(elapsed)
	local retVal = Polycore.CoreServices_Update(self.__ptr, elapsed)
end

function CoreServices:Render()
	local retVal =  Polycore.CoreServices_Render(self.__ptr)
end

function CoreServices:setCore(core)
	local retVal = Polycore.CoreServices_setCore(self.__ptr, core.__ptr)
end

function CoreServices:setupBasicListeners()
	local retVal =  Polycore.CoreServices_setupBasicListeners(self.__ptr)
end

function CoreServices:getCore()
	local retVal =  Polycore.CoreServices_getCore(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Core"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:installModule(module)
	local retVal = Polycore.CoreServices_installModule(self.__ptr, module.__ptr)
end

function CoreServices:getMaterialManager()
	local retVal =  Polycore.CoreServices_getMaterialManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["MaterialManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getScreenManager()
	local retVal =  Polycore.CoreServices_getScreenManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getSceneManager()
	local retVal =  Polycore.CoreServices_getSceneManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getTimerManager()
	local retVal =  Polycore.CoreServices_getTimerManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["TimerManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getTweenManager()
	local retVal =  Polycore.CoreServices_getTweenManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["TweenManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getResourceManager()
	local retVal =  Polycore.CoreServices_getResourceManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ResourceManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getSoundManager()
	local retVal =  Polycore.CoreServices_getSoundManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SoundManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getFontManager()
	local retVal =  Polycore.CoreServices_getFontManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["FontManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getLogger()
	local retVal =  Polycore.CoreServices_getLogger(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Logger"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getConfig()
	local retVal =  Polycore.CoreServices_getConfig(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Config"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:__delete()
	if self then Polycore.delete_CoreServices(self.__ptr) end
end
