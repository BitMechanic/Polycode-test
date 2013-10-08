require "Polycode/ScreenMesh"

class "ScreenLine" (ScreenMesh)







function ScreenLine:ScreenLine(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScreenMesh" then
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
		self.__ptr = Polycore.ScreenLine(unpack(arg))
	end
end

function ScreenLine:setStart(point)
	local retVal = Polycore.ScreenLine_setStart(self.__ptr, point.__ptr)
end

function ScreenLine:setEnd(point)
	local retVal = Polycore.ScreenLine_setEnd(self.__ptr, point.__ptr)
end

function ScreenLine.ScreenLineBetweenEntities(target1, target2)
	local retVal = Polycore.ScreenLine_ScreenLineBetweenEntities(target1.__ptr, target2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ScreenLine"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScreenLine:Update()
	local retVal =  Polycore.ScreenLine_Update(self.__ptr)
end

function ScreenLine:Render()
	local retVal =  Polycore.ScreenLine_Render(self.__ptr)
end

function ScreenLine:setLineWidth(width)
	local retVal = Polycore.ScreenLine_setLineWidth(self.__ptr, width)
end

function ScreenLine:__delete()
	if self then Polycore.delete_ScreenLine(self.__ptr) end
end
