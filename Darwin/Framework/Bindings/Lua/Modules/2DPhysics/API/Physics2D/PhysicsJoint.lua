class "PhysicsJoint"



function PhysicsJoint:__getvar(name)
	if name == "box2DJoint" then
		local retVal = Physics2D.PhysicsJoint_get_box2DJoint(self.__ptr)
		local __c = _G["b2Joint"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function PhysicsJoint:__setvar(name,value)
	return false
end


function PhysicsJoint:PhysicsJoint(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Physics2D.PhysicsJoint(unpack(arg))
	end
end

function PhysicsJoint:__delete()
	if self then Physics2D.delete_PhysicsJoint(self.__ptr) end
end
