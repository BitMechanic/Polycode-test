class "BoneTrack"



function BoneTrack:__getvar(name)
	if name == "scaleX" then
		local retVal = Polycore.BoneTrack_get_scaleX(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "scaleY" then
		local retVal = Polycore.BoneTrack_get_scaleY(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "scaleZ" then
		local retVal = Polycore.BoneTrack_get_scaleZ(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "QuatW" then
		local retVal = Polycore.BoneTrack_get_QuatW(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "QuatX" then
		local retVal = Polycore.BoneTrack_get_QuatX(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "QuatY" then
		local retVal = Polycore.BoneTrack_get_QuatY(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "QuatZ" then
		local retVal = Polycore.BoneTrack_get_QuatZ(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "LocX" then
		local retVal = Polycore.BoneTrack_get_LocX(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "LocY" then
		local retVal = Polycore.BoneTrack_get_LocY(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "LocZ" then
		local retVal = Polycore.BoneTrack_get_LocZ(self.__ptr)
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "LocXVec" then
		local retVal = Polycore.BoneTrack_get_LocXVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "LocYVec" then
		local retVal = Polycore.BoneTrack_get_LocYVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "LocZVec" then
		local retVal = Polycore.BoneTrack_get_LocZVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "ScaleXVec" then
		local retVal = Polycore.BoneTrack_get_ScaleXVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "ScaleYVec" then
		local retVal = Polycore.BoneTrack_get_ScaleYVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "ScaleZVec" then
		local retVal = Polycore.BoneTrack_get_ScaleZVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "boneQuat" then
		local retVal = Polycore.BoneTrack_get_boneQuat(self.__ptr)
		local __c = _G["Quaternion"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "quatTween" then
		local retVal = Polycore.BoneTrack_get_quatTween(self.__ptr)
		local __c = _G["QuaternionTween"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "QuatWVec" then
		local retVal = Polycore.BoneTrack_get_QuatWVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "QuatXVec" then
		local retVal = Polycore.BoneTrack_get_QuatXVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "QuatYVec" then
		local retVal = Polycore.BoneTrack_get_QuatYVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "QuatZVec" then
		local retVal = Polycore.BoneTrack_get_QuatZVec(self.__ptr)
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function BoneTrack:__setvar(name,value)
	if name == "LocXVec" then
		Polycore.BoneTrack_set_LocXVec(self.__ptr, value.__ptr)
		return true
	elseif name == "LocYVec" then
		Polycore.BoneTrack_set_LocYVec(self.__ptr, value.__ptr)
		return true
	elseif name == "LocZVec" then
		Polycore.BoneTrack_set_LocZVec(self.__ptr, value.__ptr)
		return true
	elseif name == "ScaleXVec" then
		Polycore.BoneTrack_set_ScaleXVec(self.__ptr, value.__ptr)
		return true
	elseif name == "ScaleYVec" then
		Polycore.BoneTrack_set_ScaleYVec(self.__ptr, value.__ptr)
		return true
	elseif name == "ScaleZVec" then
		Polycore.BoneTrack_set_ScaleZVec(self.__ptr, value.__ptr)
		return true
	elseif name == "boneQuat" then
		Polycore.BoneTrack_set_boneQuat(self.__ptr, value.__ptr)
		return true
	elseif name == "QuatWVec" then
		Polycore.BoneTrack_set_QuatWVec(self.__ptr, value.__ptr)
		return true
	elseif name == "QuatXVec" then
		Polycore.BoneTrack_set_QuatXVec(self.__ptr, value.__ptr)
		return true
	elseif name == "QuatYVec" then
		Polycore.BoneTrack_set_QuatYVec(self.__ptr, value.__ptr)
		return true
	elseif name == "QuatZVec" then
		Polycore.BoneTrack_set_QuatZVec(self.__ptr, value.__ptr)
		return true
	end
	return false
end


function BoneTrack:BoneTrack(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.BoneTrack(unpack(arg))
	end
end

function BoneTrack:Play(once)
	local retVal = Polycore.BoneTrack_Play(self.__ptr, once)
end

function BoneTrack:Stop()
	local retVal =  Polycore.BoneTrack_Stop(self.__ptr)
end

function BoneTrack:Update()
	local retVal =  Polycore.BoneTrack_Update(self.__ptr)
end

function BoneTrack:setSpeed(speed)
	local retVal = Polycore.BoneTrack_setSpeed(self.__ptr, speed)
end

function BoneTrack:__delete()
	if self then Polycore.delete_BoneTrack(self.__ptr) end
end
