require "Polycode/EventDispatcher"

class "CoreInput" (EventDispatcher)



CoreInput.MOUSE_BUTTON1 = 0
CoreInput.MOUSE_BUTTON2 = 1
CoreInput.MOUSE_BUTTON3 = 2
function CoreInput:__getvar(name)
	if name == "simulateTouchWithMouse" then
		return Polycore.CoreInput_get_simulateTouchWithMouse(self.__ptr)
	elseif name == "mousePosition" then
		local retVal = Polycore.CoreInput_get_mousePosition(self.__ptr)
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "deltaMousePosition" then
		local retVal = Polycore.CoreInput_get_deltaMousePosition(self.__ptr)
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function CoreInput:__setvar(name,value)
	if name == "simulateTouchWithMouse" then
		Polycore.CoreInput_set_simulateTouchWithMouse(self.__ptr, value)
		return true
	elseif name == "mousePosition" then
		Polycore.CoreInput_set_mousePosition(self.__ptr, value.__ptr)
		return true
	elseif name == "deltaMousePosition" then
		Polycore.CoreInput_set_deltaMousePosition(self.__ptr, value.__ptr)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function CoreInput:CoreInput(...)
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
		self.__ptr = Polycore.CoreInput(unpack(arg))
	end
end

function CoreInput:getMousePosition()
	local retVal =  Polycore.CoreInput_getMousePosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreInput:getKeyState(keyCode)
	local retVal = Polycore.CoreInput_getKeyState(self.__ptr, keyCode)
	return retVal
end

function CoreInput:getJoystickButtonState(joystickIndex, button)
	local retVal = Polycore.CoreInput_getJoystickButtonState(self.__ptr, joystickIndex, button)
	return retVal
end

function CoreInput:getJoystickAxisValue(joystickIndex, axis)
	local retVal = Polycore.CoreInput_getJoystickAxisValue(self.__ptr, joystickIndex, axis)
	return retVal
end

function CoreInput:getMouseDelta()
	local retVal =  Polycore.CoreInput_getMouseDelta(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreInput:getMouseButtonState(mouseButton)
	local retVal = Polycore.CoreInput_getMouseButtonState(self.__ptr, mouseButton)
	return retVal
end

function CoreInput:getNumJoysticks()
	local retVal =  Polycore.CoreInput_getNumJoysticks(self.__ptr)
	return retVal
end

function CoreInput:getJoystickInfoByIndex(index)
	local retVal = Polycore.CoreInput_getJoystickInfoByIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["JoystickInfo"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreInput:getJoystickInfoByID(deviceID)
	local retVal = Polycore.CoreInput_getJoystickInfoByID(self.__ptr, deviceID)
	if retVal == nil then return nil end
	local __c = _G["JoystickInfo"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreInput:addJoystick(deviceID)
	local retVal = Polycore.CoreInput_addJoystick(self.__ptr, deviceID)
end

function CoreInput:removeJoystick(deviceID)
	local retVal = Polycore.CoreInput_removeJoystick(self.__ptr, deviceID)
end

function CoreInput:joystickAxisMoved(axisID, value, deviceID)
	local retVal = Polycore.CoreInput_joystickAxisMoved(self.__ptr, axisID, value, deviceID)
end

function CoreInput:joystickButtonDown(buttonID, deviceID)
	local retVal = Polycore.CoreInput_joystickButtonDown(self.__ptr, buttonID, deviceID)
end

function CoreInput:joystickButtonUp(buttonID, deviceID)
	local retVal = Polycore.CoreInput_joystickButtonUp(self.__ptr, buttonID, deviceID)
end

function CoreInput:mouseWheelUp(ticks)
	local retVal = Polycore.CoreInput_mouseWheelUp(self.__ptr, ticks)
end

function CoreInput:mouseWheelDown(ticks)
	local retVal = Polycore.CoreInput_mouseWheelDown(self.__ptr, ticks)
end

function CoreInput:setMouseButtonState(mouseButton, state, ticks)
	local retVal = Polycore.CoreInput_setMouseButtonState(self.__ptr, mouseButton, state, ticks)
end

function CoreInput:setMousePosition(x, y, ticks)
	local retVal = Polycore.CoreInput_setMousePosition(self.__ptr, x, y, ticks)
end

function CoreInput:setKeyState(keyCode, code, newState, ticks)
	local retVal = Polycore.CoreInput_setKeyState(self.__ptr, keyCode, code.__ptr, newState, ticks)
end

function CoreInput:setDeltaPosition(x, y)
	local retVal = Polycore.CoreInput_setDeltaPosition(self.__ptr, x, y)
end

function CoreInput:touchesBegan(touch, touches, ticks)
	local retVal = Polycore.CoreInput_touchesBegan(self.__ptr, touch.__ptr, touches.__ptr, ticks)
end

function CoreInput:touchesMoved(touch, touches, ticks)
	local retVal = Polycore.CoreInput_touchesMoved(self.__ptr, touch.__ptr, touches.__ptr, ticks)
end

function CoreInput:touchesEnded(touch, touches, ticks)
	local retVal = Polycore.CoreInput_touchesEnded(self.__ptr, touch.__ptr, touches.__ptr, ticks)
end

function CoreInput.createEvent(event)
	local retVal = Polycore.CoreInput_createEvent(event.__ptr)
	if retVal == nil then return nil end
	local __c = _G["InputEvent"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreInput:clearInput()
	local retVal =  Polycore.CoreInput_clearInput(self.__ptr)
end

function CoreInput:__delete()
	if self then Polycore.delete_CoreInput(self.__ptr) end
end
