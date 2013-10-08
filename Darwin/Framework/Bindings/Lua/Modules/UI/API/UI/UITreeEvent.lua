require "Polycode/Event"

class "UITreeEvent" (Event)



UITreeEvent.EVENTBASE_UITREEEVENT = 0xB00
UITreeEvent.NEED_REFRESH_EVENT = UITreeEvent.EVENTBASE_UITREEEVENT + 0
UITreeEvent.SELECTED_EVENT = UITreeEvent.EVENTBASE_UITREEEVENT + 1
UITreeEvent.EXECUTED_EVENT = UITreeEvent.EVENTBASE_UITREEEVENT + 2
UITreeEvent.DRAG_START_EVENT = UITreeEvent.EVENTBASE_UITREEEVENT + 3
function UITreeEvent:__getvar(name)
	if name == "selection" then
		local retVal = UI.UITreeEvent_get_selection(self.__ptr)
		local __c = _G["UITree"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if Event["__getvar"] ~= nil then
		return Event.__getvar(self, name)
	end
end


function UITreeEvent:__setvar(name,value)
	if Event["__setvar"] ~= nil then
		return Event.__setvar(self, name, value)
	else
		return false
	end
end


function UITreeEvent:UITreeEvent(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Event" then
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
		self.__ptr = UI.UITreeEvent(unpack(arg))
	end
end

function UITreeEvent:__delete()
	if self then UI.delete_UITreeEvent(self.__ptr) end
end
