require "Polycode/SceneEntity"

class "Skeleton" (SceneEntity)







function Skeleton:Skeleton(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "SceneEntity" then
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
		self.__ptr = Polycore.Skeleton(unpack(arg))
	end
end

function Skeleton.BlankSkeleton()
	local retVal =  Polycore.Skeleton_BlankSkeleton()
	if retVal == nil then return nil end
	local __c = _G["Skeleton"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Skeleton:loadSkeleton(fileName)
	local retVal = Polycore.Skeleton_loadSkeleton(self.__ptr, fileName)
end

function Skeleton:playAnimation(animName, once)
	local retVal = Polycore.Skeleton_playAnimation(self.__ptr, animName, once)
end

function Skeleton:playAnimationByIndex(index, once)
	local retVal = Polycore.Skeleton_playAnimationByIndex(self.__ptr, index, once)
end

function Skeleton:addAnimation(name, fileName)
	local retVal = Polycore.Skeleton_addAnimation(self.__ptr, name, fileName)
end

function Skeleton:getAnimation(name)
	local retVal = Polycore.Skeleton_getAnimation(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["SkeletonAnimation"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Skeleton:Update()
	local retVal =  Polycore.Skeleton_Update(self.__ptr)
end

function Skeleton:getBoneByName(name)
	local retVal = Polycore.Skeleton_getBoneByName(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["Bone"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Skeleton:bonesVisible(val)
	local retVal = Polycore.Skeleton_bonesVisible(self.__ptr, val)
end

function Skeleton:enableBoneLabels(labelFont, size, scale, labelColor)
	local retVal = Polycore.Skeleton_enableBoneLabels(self.__ptr, labelFont, size, scale, labelColor.__ptr)
end

function Skeleton:getNumBones()
	local retVal =  Polycore.Skeleton_getNumBones(self.__ptr)
	return retVal
end

function Skeleton:getBone(index)
	local retVal = Polycore.Skeleton_getBone(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Bone"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Skeleton:getCurrentAnimation()
	local retVal =  Polycore.Skeleton_getCurrentAnimation(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SkeletonAnimation"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Skeleton:__delete()
	if self then Polycore.delete_Skeleton(self.__ptr) end
end
