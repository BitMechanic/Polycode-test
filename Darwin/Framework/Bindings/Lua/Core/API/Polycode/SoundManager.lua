class "SoundManager"







function SoundManager:SoundManager(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SoundManager(unpack(arg))
	end
end

function SoundManager:setListenerPosition(position)
	local retVal = Polycore.SoundManager_setListenerPosition(self.__ptr, position.__ptr)
end

function SoundManager:setListenerOrientation(orientation, upVector)
	local retVal = Polycore.SoundManager_setListenerOrientation(self.__ptr, orientation.__ptr, upVector.__ptr)
end

function SoundManager:initAL()
	local retVal =  Polycore.SoundManager_initAL(self.__ptr)
end

function SoundManager:setGlobalVolume(globalVolume)
	local retVal = Polycore.SoundManager_setGlobalVolume(self.__ptr, globalVolume)
end

function SoundManager:__delete()
	if self then Polycore.delete_SoundManager(self.__ptr) end
end
