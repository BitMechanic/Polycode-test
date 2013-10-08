class "PhysicsGenericConstraint"



function PhysicsGenericConstraint:__getvar(name)
	if name == "btConstraint" then
		local retVal = Physics3D.PhysicsGenericConstraint_get_btConstraint(self.__ptr)
		local __c = _G["btGeneric6DofConstraint"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function PhysicsGenericConstraint:__setvar(name,value)
	return false
end


function PhysicsGenericConstraint:setLinearLowerLimit(limit)
	local retVal = Physics3D.PhysicsGenericConstraint_setLinearLowerLimit(self.__ptr, limit.__ptr)
end

function PhysicsGenericConstraint:setLinearUpperLimit(limit)
	local retVal = Physics3D.PhysicsGenericConstraint_setLinearUpperLimit(self.__ptr, limit.__ptr)
end

function PhysicsGenericConstraint:setAngularLowerLimit(limit)
	local retVal = Physics3D.PhysicsGenericConstraint_setAngularLowerLimit(self.__ptr, limit.__ptr)
end

function PhysicsGenericConstraint:setAngularUpperLimit(limit)
	local retVal = Physics3D.PhysicsGenericConstraint_setAngularUpperLimit(self.__ptr, limit.__ptr)
end

function PhysicsGenericConstraint:__delete()
	if self then Physics3D.delete_PhysicsGenericConstraint(self.__ptr) end
end
