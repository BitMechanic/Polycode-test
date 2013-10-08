require "Polycode/EventDispatcher"

class "Core" (EventDispatcher)



Core.EVENTBASE_CORE = 0x200
Core.EVENT_CORE_RESIZE = Core.EVENTBASE_CORE + 0
Core.EVENT_LOST_FOCUS = Core.EVENTBASE_CORE + 1
Core.EVENT_GAINED_FOCUS = Core.EVENTBASE_CORE + 2
Core.EVENT_UNDO = Core.EVENTBASE_CORE + 3
Core.EVENT_REDO = Core.EVENTBASE_CORE + 4
Core.EVENT_COPY = Core.EVENTBASE_CORE + 5
Core.EVENT_CUT = Core.EVENTBASE_CORE + 6
Core.EVENT_SELECT_ALL = Core.EVENTBASE_CORE + 7
Core.EVENT_PASTE = Core.EVENTBASE_CORE + 8
Core.CURSOR_ARROW = 0
Core.CURSOR_TEXT = 1
Core.CURSOR_POINTER = 2
Core.CURSOR_CROSSHAIR = 3
Core.CURSOR_RESIZE_LEFT_RIGHT = 4
Core.CURSOR_RESIZE_UP_DOWN = 5
Core.CURSOR_OPEN_HAND = 6
function Core:__getvar(name)
	if name == "eventMutex" then
		local retVal = Polycore.Core_get_eventMutex(self.__ptr)
		local __c = _G["CoreMutex"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "paused" then
		return Polycore.Core_get_paused(self.__ptr)
	elseif name == "pauseOnLoseFocus" then
		return Polycore.Core_get_pauseOnLoseFocus(self.__ptr)
	elseif name == "defaultScreenWidth" then
		return Polycore.Core_get_defaultScreenWidth(self.__ptr)
	elseif name == "defaultScreenHeight" then
		return Polycore.Core_get_defaultScreenHeight(self.__ptr)
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function Core:__setvar(name,value)
	if name == "paused" then
		Polycore.Core_set_paused(self.__ptr, value)
		return true
	elseif name == "pauseOnLoseFocus" then
		Polycore.Core_set_pauseOnLoseFocus(self.__ptr, value)
		return true
	elseif name == "defaultScreenWidth" then
		Polycore.Core_set_defaultScreenWidth(self.__ptr, value)
		return true
	elseif name == "defaultScreenHeight" then
		Polycore.Core_set_defaultScreenHeight(self.__ptr, value)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function Core:Update()
	local retVal =  Polycore.Core_Update(self.__ptr)
	return retVal
end

function Core:Render()
	local retVal =  Polycore.Core_Render(self.__ptr)
end

function Core:updateAndRender()
	local retVal =  Polycore.Core_updateAndRender(self.__ptr)
	return retVal
end

function Core:enableMouse(newval)
	local retVal = Polycore.Core_enableMouse(self.__ptr, newval)
end

function Core:captureMouse(newval)
	local retVal = Polycore.Core_captureMouse(self.__ptr, newval)
end

function Core:setCursor(cursorType)
	local retVal = Polycore.Core_setCursor(self.__ptr, cursorType)
end

function Core:warpCursor(x, y)
	local retVal = Polycore.Core_warpCursor(self.__ptr, x, y)
end

function Core:createThread(target)
	local retVal = Polycore.Core_createThread(self.__ptr, target.__ptr)
end

function Core:lockMutex(mutex)
	local retVal = Polycore.Core_lockMutex(self.__ptr, mutex.__ptr)
end

function Core:unlockMutex(mutex)
	local retVal = Polycore.Core_unlockMutex(self.__ptr, mutex.__ptr)
end

function Core:createMutex()
	local retVal =  Polycore.Core_createMutex(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreMutex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:copyStringToClipboard(str)
	local retVal = Polycore.Core_copyStringToClipboard(self.__ptr, str)
end

function Core:getClipboardString()
	local retVal =  Polycore.Core_getClipboardString(self.__ptr)
	return retVal
end

function Core:getServices()
	local retVal =  Polycore.Core_getServices(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreServices"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:getFPS()
	local retVal =  Polycore.Core_getFPS(self.__ptr)
	return retVal
end

function Core:Shutdown()
	local retVal =  Polycore.Core_Shutdown(self.__ptr)
end

function Core:isFullscreen()
	local retVal =  Polycore.Core_isFullscreen(self.__ptr)
	return retVal
end

function Core:getAALevel()
	local retVal =  Polycore.Core_getAALevel(self.__ptr)
	return retVal
end

function Core:getInput()
	local retVal =  Polycore.Core_getInput(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreInput"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:getXRes()
	local retVal =  Polycore.Core_getXRes(self.__ptr)
	return retVal
end

function Core:getYRes()
	local retVal =  Polycore.Core_getYRes(self.__ptr)
	return retVal
end

function Core.getScreenInfo(width, height, hz)
	local retVal = Polycore.Core_getScreenInfo(width.__ptr, height.__ptr, hz.__ptr)
end

function Core:createFolder(folderPath)
	local retVal = Polycore.Core_createFolder(self.__ptr, folderPath)
end

function Core:copyDiskItem(itemPath, destItemPath)
	local retVal = Polycore.Core_copyDiskItem(self.__ptr, itemPath, destItemPath)
end

function Core:moveDiskItem(itemPath, destItemPath)
	local retVal = Polycore.Core_moveDiskItem(self.__ptr, itemPath, destItemPath)
end

function Core:removeDiskItem(itemPath)
	local retVal = Polycore.Core_removeDiskItem(self.__ptr, itemPath)
end

function Core:openFolderPicker()
	local retVal =  Polycore.Core_openFolderPicker(self.__ptr)
	return retVal
end

function Core:setFramerate(frameRate)
	local retVal = Polycore.Core_setFramerate(self.__ptr, frameRate)
end

function Core:openFilePicker(extensions, allowMultiple)
	local retVal = Polycore.Core_openFilePicker(self.__ptr, extensions.__ptr, allowMultiple)
	if retVal == nil then return nil end
	local __c = _G["std::vector<String>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel)
	local retVal = Polycore.Core_setVideoMode(self.__ptr, xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel)
end

function Core:resizeTo(xRes, yRes)
	local retVal = Polycore.Core_resizeTo(self.__ptr, xRes, yRes)
end

function Core:doSleep()
	local retVal =  Polycore.Core_doSleep(self.__ptr)
end

function Core:openURL(url)
	local retVal = Polycore.Core_openURL(self.__ptr, url)
end

function Core:getElapsed()
	local retVal =  Polycore.Core_getElapsed(self.__ptr)
	return retVal
end

function Core:getTicks()
	local retVal =  Polycore.Core_getTicks(self.__ptr)
	return retVal
end

function Core:getTicksFloat()
	local retVal =  Polycore.Core_getTicksFloat(self.__ptr)
	return retVal
end

function Core:setUserPointer(ptr)
	local retVal = Polycore.Core_setUserPointer(self.__ptr, ptr.__ptr)
end

function Core:getUserPointer()
	local retVal =  Polycore.Core_getUserPointer(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:executeExternalCommand(command, args, inDirectory)
	local retVal = Polycore.Core_executeExternalCommand(self.__ptr, command, args, inDirectory)
	return retVal
end

function Core:getDefaultWorkingDirectory()
	local retVal =  Polycore.Core_getDefaultWorkingDirectory(self.__ptr)
	return retVal
end

function Core:getUserHomeDirectory()
	local retVal =  Polycore.Core_getUserHomeDirectory(self.__ptr)
	return retVal
end

function Core:makeApplicationMain()
	local retVal =  Polycore.Core_makeApplicationMain(self.__ptr)
end

function Core:getEventMutex()
	local retVal =  Polycore.Core_getEventMutex(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreMutex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:removeThread(thread)
	local retVal = Polycore.Core_removeThread(self.__ptr, thread.__ptr)
end

function Core:__delete()
	if self then Polycore.delete_Core(self.__ptr) end
end
