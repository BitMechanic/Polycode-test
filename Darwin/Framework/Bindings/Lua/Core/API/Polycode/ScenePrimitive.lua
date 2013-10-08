require "Polycode/SceneMesh"

class "ScenePrimitive" (SceneMesh)



ScenePrimitive.TYPE_BOX = 0
ScenePrimitive.TYPE_PLANE = 1
ScenePrimitive.TYPE_SPHERE = 2
ScenePrimitive.TYPE_CYLINDER = 3
ScenePrimitive.TYPE_CONE = 4
ScenePrimitive.TYPE_VPLANE = 5
ScenePrimitive.TYPE_TORUS = 6
ScenePrimitive.TYPE_UNCAPPED_CYLINDER = 7




function ScenePrimitive:ScenePrimitive(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "SceneMesh" then
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
		self.__ptr = Polycore.ScenePrimitive(unpack(arg))
	end
end

function ScenePrimitive:__delete()
	if self then Polycore.delete_ScenePrimitive(self.__ptr) end
end
