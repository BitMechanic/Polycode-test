require "Polycode/EventDispatcher"

class "ScreenManager" (EventDispatcher)



function ScreenManager:__getvar(name)
	if name == "drawScreensFirst" then
		return Polycore.ScreenManager_get_drawScreensFirst(self.__ptr)
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function ScreenManager:__setvar(name,value)
	if name == "drawScreensFirst" then
		Polycore.ScreenManager_set_drawScreensFirst(self.__ptr, value)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function ScreenManager:ScreenManager(...)
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
		self.__ptr = Polycore.ScreenManager(unpack(arg))
	end
end

function ScreenManager:removeScreen(screen)
	local retVal = Polycore.ScreenManager_removeScreen(self.__ptr, screen.__ptr)
end

function ScreenManager:addScreen(screen)
	local retVal = Polycore.ScreenManager_addScreen(self.__ptr, screen.__ptr)
end

function ScreenManager:Update()
	local retVal =  Polycore.ScreenManager_Update(self.__ptr)
end

function ScreenManager:Render()
	local retVal =  Polycore.ScreenManager_Render(self.__ptr)
end

function ScreenManager:__delete()
	if self then Polycore.delete_ScreenManager(self.__ptr) end
end
