require "UI/UIElement"

class "UITextInput" (UIElement)



function UITextInput:__getvar(name)
	if name == "useStrongHinting" then
		return UI.UITextInput_get_useStrongHinting(self.__ptr)
	end
	if UIElement["__getvar"] ~= nil then
		return UIElement.__getvar(self, name)
	end
end


function UITextInput:__setvar(name,value)
	if name == "useStrongHinting" then
		UI.UITextInput_set_useStrongHinting(self.__ptr, value)
		return true
	end
	if UIElement["__setvar"] ~= nil then
		return UIElement.__setvar(self, name, value)
	else
		return false
	end
end


function UITextInput:UITextInput(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "UIElement" then
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
		self.__ptr = UI.UITextInput(unpack(arg))
	end
end

function UITextInput:Update()
	local retVal =  UI.UITextInput_Update(self.__ptr)
end

function UITextInput:setText(text, s_endChangeEvent)
	local retVal = UI.UITextInput_setText(self.__ptr, text, s_endChangeEvent)
end

function UITextInput:getText()
	local retVal =  UI.UITextInput_getText(self.__ptr)
	return retVal
end

function UITextInput:onLoseFocus()
	local retVal =  UI.UITextInput_onLoseFocus(self.__ptr)
end

function UITextInput:insertLine(lineText)
	local retVal = UI.UITextInput_insertLine(self.__ptr, lineText)
	return retVal
end

function UITextInput:onKeyDown(key, charCode)
	local retVal = UI.UITextInput_onKeyDown(self.__ptr, key, charCode.__ptr)
end

function UITextInput:clearSelection()
	local retVal =  UI.UITextInput_clearSelection(self.__ptr)
end

function UITextInput:setSelection(lineStart, lineEnd, colStart, colEnd)
	local retVal = UI.UITextInput_setSelection(self.__ptr, lineStart, lineEnd, colStart, colEnd)
end

function UITextInput:deleteSelection()
	local retVal =  UI.UITextInput_deleteSelection(self.__ptr)
end

function UITextInput:selectAll()
	local retVal =  UI.UITextInput_selectAll(self.__ptr)
end

function UITextInput:Undo()
	local retVal =  UI.UITextInput_Undo(self.__ptr)
end

function UITextInput:Redo()
	local retVal =  UI.UITextInput_Redo(self.__ptr)
end

function UITextInput:Cut()
	local retVal =  UI.UITextInput_Cut(self.__ptr)
end

function UITextInput:Copy()
	local retVal =  UI.UITextInput_Copy(self.__ptr)
end

function UITextInput:Paste()
	local retVal =  UI.UITextInput_Paste(self.__ptr)
end

function UITextInput:enableLineNumbers(val)
	local retVal = UI.UITextInput_enableLineNumbers(self.__ptr, val)
end

function UITextInput:setBackgroundColor(color)
	local retVal = UI.UITextInput_setBackgroundColor(self.__ptr, color.__ptr)
end

function UITextInput:setSelectionColor(color)
	local retVal = UI.UITextInput_setSelectionColor(self.__ptr, color.__ptr)
end

function UITextInput:setCursorColor(color)
	local retVal = UI.UITextInput_setCursorColor(self.__ptr, color.__ptr)
end

function UITextInput:setTextColor(color)
	local retVal = UI.UITextInput_setTextColor(self.__ptr, color.__ptr)
end

function UITextInput:setLineNumberColor(color)
	local retVal = UI.UITextInput_setLineNumberColor(self.__ptr, color.__ptr)
end

function UITextInput:checkBufferLines()
	local retVal =  UI.UITextInput_checkBufferLines(self.__ptr)
end

function UITextInput:replaceAll(what, withWhat)
	local retVal = UI.UITextInput_replaceAll(self.__ptr, what, withWhat)
end

function UITextInput:findString(stringToFind, replace, replaceString)
	local retVal = UI.UITextInput_findString(self.__ptr, stringToFind, replace, replaceString)
end

function UITextInput:getFindMatches(stringToFind)
	local retVal = UI.UITextInput_getFindMatches(self.__ptr, stringToFind)
	if retVal == nil then return nil end
	local __c = _G["std::vector<FindMatch>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITextInput:findNext()
	local retVal =  UI.UITextInput_findNext(self.__ptr)
end

function UITextInput:findPrevious()
	local retVal =  UI.UITextInput_findPrevious(self.__ptr)
end

function UITextInput:findCurrent()
	local retVal =  UI.UITextInput_findCurrent(self.__ptr)
end

function UITextInput:showLine(lineNumber, top)
	local retVal = UI.UITextInput_showLine(self.__ptr, lineNumber, top)
end

function UITextInput:setSyntaxHighlighter(syntaxHighlighter)
	local retVal = UI.UITextInput_setSyntaxHighlighter(self.__ptr, syntaxHighlighter.__ptr)
end

function UITextInput:Resize(width, height)
	local retVal = UI.UITextInput_Resize(self.__ptr, width, height)
end

function UITextInput:setNumberOnly(val)
	local retVal = UI.UITextInput_setNumberOnly(self.__ptr, val)
end

function UITextInput:getLineText(index)
	local retVal = UI.UITextInput_getLineText(self.__ptr, index)
	return retVal
end

function UITextInput:getSelectionText()
	local retVal =  UI.UITextInput_getSelectionText(self.__ptr)
	return retVal
end

function UITextInput:insertText(text, updateWordWrap)
	local retVal = UI.UITextInput_insertText(self.__ptr, text, updateWordWrap)
end

function UITextInput:setCaretPosition(position)
	local retVal = UI.UITextInput_setCaretPosition(self.__ptr, position)
end

function UITextInput:getScrollContainer()
	local retVal =  UI.UITextInput_getScrollContainer(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["UIScrollContainer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function UITextInput:shiftText(left)
	local retVal = UI.UITextInput_shiftText(self.__ptr, left)
end

function UITextInput:convertIndentToTabs()
	local retVal =  UI.UITextInput_convertIndentToTabs(self.__ptr)
end

function UITextInput:convertIndentToSpaces()
	local retVal =  UI.UITextInput_convertIndentToSpaces(self.__ptr)
end

function UITextInput:doMultilineResize()
	local retVal =  UI.UITextInput_doMultilineResize(self.__ptr)
end

function UITextInput.setMenuSingleton(_globalMenu)
	local retVal = UI.UITextInput_setMenuSingleton(_globalMenu.__ptr)
end

function UITextInput:__delete()
	if self then UI.delete_UITextInput(self.__ptr) end
end
