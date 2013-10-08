class "PhysicsHingeConstraint"



function PhysicsHingeConstraint:__getvar(name)
	if name == "btConstraint" then
		local retVal = Physics3D.PhysicsHingeConstraint_get_btConstraint(self.__ptr)
		local __c = _G["btHingeConstraint"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function PhysicsHingeConstraint:__setvar(name,value)
	return false
end


function PhysicsHingeConstraint:PhysicsHingeConstraint(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Physics3D.PhysicsHingeConstraint(unpack(arg))
	end
end

function PhysicsHingeConstraint:setLimits(minLimit, maxLimit)
	local retVal = Physics3D.PhysicsHingeConstraint_setLimits(self.__ptr, minLimit, maxLimit)
end

function PhysicsHingeConstraint:getAngle()
	local retVal =  Physics3D.PhysicsHingeConstraint_getAngle(self.__ptr)
	return retVal
end

function PhysicsHingeConstraint:__delete()
	if self then Physics3D.delete_PhysicsHingeConstraint(self.__ptr) end
end
