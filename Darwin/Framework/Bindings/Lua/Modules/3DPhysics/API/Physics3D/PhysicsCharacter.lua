require "Physics3D/PhysicsSceneEntity"

class "PhysicsCharacter" (PhysicsSceneEntity)



function PhysicsCharacter:__getvar(name)
	if name == "character" then
		local retVal = Physics3D.PhysicsCharacter_get_character(self.__ptr)
		local __c = _G["btKinematicCharacterController"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "ghostObject" then
		local retVal = Physics3D.PhysicsCharacter_get_ghostObject(self.__ptr)
		local __c = _G["btPairCachingGhostObject"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if PhysicsSceneEntity["__getvar"] ~= nil then
		return PhysicsSceneEntity.__getvar(self, name)
	end
end


function PhysicsCharacter:__setvar(name,value)
	if PhysicsSceneEntity["__setvar"] ~= nil then
		return PhysicsSceneEntity.__setvar(self, name, value)
	else
		return false
	end
end


function PhysicsCharacter:PhysicsCharacter(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "PhysicsSceneEntity" then
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
		self.__ptr = Physics3D.PhysicsCharacter(unpack(arg))
	end
end

function PhysicsCharacter:Update()
	local retVal =  Physics3D.PhysicsCharacter_Update(self.__ptr)
end

function PhysicsCharacter:setWalkDirection(direction)
	local retVal = Physics3D.PhysicsCharacter_setWalkDirection(self.__ptr, direction.__ptr)
end

function PhysicsCharacter:jump()
	local retVal =  Physics3D.PhysicsCharacter_jump(self.__ptr)
end

function PhysicsCharacter:warpCharacter(position)
	local retVal = Physics3D.PhysicsCharacter_warpCharacter(self.__ptr, position.__ptr)
end

function PhysicsCharacter:setJumpSpeed(jumpSpeed)
	local retVal = Physics3D.PhysicsCharacter_setJumpSpeed(self.__ptr, jumpSpeed)
end

function PhysicsCharacter:setFallSpeed(fallSpeed)
	local retVal = Physics3D.PhysicsCharacter_setFallSpeed(self.__ptr, fallSpeed)
end

function PhysicsCharacter:setMaxJumpHeight(maxJumpHeight)
	local retVal = Physics3D.PhysicsCharacter_setMaxJumpHeight(self.__ptr, maxJumpHeight)
end

function PhysicsCharacter:onGround()
	local retVal =  Physics3D.PhysicsCharacter_onGround(self.__ptr)
	return retVal
end

function PhysicsCharacter:__delete()
	if self then Physics3D.delete_PhysicsCharacter(self.__ptr) end
end
