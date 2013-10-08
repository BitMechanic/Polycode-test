class "Event"



Event.EVENTBASE_EVENT = 0x100
Event.COMPLETE_EVENT = Event.EVENTBASE_EVENT + 0
Event.CHANGE_EVENT = Event.EVENTBASE_EVENT + 1
Event.CANCEL_EVENT = Event.EVENTBASE_EVENT + 2
Event.NOTIFY_EVENT = Event.EVENTBASE_EVENT + 3
Event.FIRE_EVENT = Event.EVENTBASE_EVENT + 4
Event.RESOURCE_RELOAD_EVENT = Event.EVENTBASE_EVENT + 5
Event.SELECT_EVENT = Event.EVENTBASE_EVENT + 6
Event.REMOVE_EVENT = Event.EVENTBASE_EVENT + 7
Event.EVENTBASE_NONPOLYCODE = 0x10000
function Event:__getvar(name)
	if name == "deleteOnDispatch" then
		return Polycore.Event_get_deleteOnDispatch(self.__ptr)
	end
end


function Event:__setvar(name,value)
	if name == "deleteOnDispatch" then
		Polycore.Event_set_deleteOnDispatch(self.__ptr, value)
		return true
	end
	return false
end


function Event:Event(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Event(unpack(arg))
	end
end

function Event:getEventCode()
	local retVal =  Polycore.Event_getEventCode(self.__ptr)
	return retVal
end

function Event:getDispatcher()
	local retVal =  Polycore.Event_getDispatcher(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["EventDispatcher"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Event:setEventCode(eventCode)
	local retVal = Polycore.Event_setEventCode(self.__ptr, eventCode)
end

function Event:setDispatcher(dispatcher)
	local retVal = Polycore.Event_setDispatcher(self.__ptr, dispatcher.__ptr)
end

function Event:getEventType()
	local retVal =  Polycore.Event_getEventType(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["String"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Event:__delete()
	if self then Polycore.delete_Event(self.__ptr) end
end
