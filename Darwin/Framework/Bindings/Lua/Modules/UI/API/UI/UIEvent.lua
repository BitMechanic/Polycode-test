require "Polycode/Event"

class "UIEvent" (Event)



UIEvent.EVENTBASE_UIEVENT = 0xA00
UIEvent.CLICK_EVENT = UIEvent.EVENTBASE_UIEVENT + 0
UIEvent.CLOSE_EVENT = UIEvent.EVENTBASE_UIEVENT + 1
UIEvent.OK_EVENT = UIEvent.EVENTBASE_UIEVENT + 2
UIEvent.CANCEL_EVENT = UIEvent.EVENTBASE_UIEVENT + 3
UIEvent.CHANGE_EVENT = UIEvent.EVENTBASE_UIEVENT + 4
UIEvent.YES_EVENT = UIEvent.EVENTBASE_UIEVENT + 5
UIEvent.NO_EVENT = UIEvent.EVENTBASE_UIEVENT + 6




function UIEvent:UIEvent(...)
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
		self.__ptr = UI.UIEvent(unpack(arg))
	end
end

function UIEvent:__delete()
	if self then UI.delete_UIEvent(self.__ptr) end
end
