#pragma once

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
} // extern "C" 

#include "PolycodeUI.h"
#include "PolyUIBox.h"
#include "PolyUIButton.h"
#include "PolyUICheckBox.h"
#include "PolyUIColorBox.h"
#include "PolyUIComboBox.h"
#include "PolyUIElement.h"
#include "PolyUIEvent.h"
#include "PolyUIFileDialog.h"
#include "PolyUIHScrollBar.h"
#include "PolyUIHSizer.h"
#include "PolyUIHSlider.h"
#include "PolyUIImageButton.h"
#include "PolyUIMenu.h"
#include "PolyUIMenuBar.h"
#include "PolyUIScrollContainer.h"
#include "PolyUITextInput.h"
#include "PolyUITree.h"
#include "PolyUITreeContainer.h"
#include "PolyUITreeEvent.h"
#include "PolyUIVScrollBar.h"
#include "PolyUIVSizer.h"
#include "PolyUIWindow.h"

using namespace std;


namespace Polycode {

static int UI_UIBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String imageFile = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number t = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number r = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number l = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number boxWidth = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number boxHeight = lua_tonumber(L, 7);
	UIBox *inst = new UIBox(imageFile, t, r, b, l, boxWidth, boxHeight);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIBox");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIBox_resizeBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIBox *inst = (UIBox*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newWidth = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number newHeight = lua_tonumber(L, 3);
	inst->resizeBox(newWidth, newHeight);
	return 0;
}

static int UI_delete_UIBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIBox*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String text = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	Number height;
	if(lua_isnumber(L, 3)) {
		height = lua_tonumber(L, 3);
	} else {
		height = 23;
	}
	UIButton *inst = new UIButton(text, width, height);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIButton");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIButton_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIButton *inst = (UIButton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UIButton_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIButton *inst = (UIButton*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_delete_UIButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIButton*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UICheckBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String caption = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool checked = lua_toboolean(L, 2) != 0;
	UICheckBox *inst = new UICheckBox(caption, checked);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UICheckBox");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UICheckBox_setChecked(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UICheckBox *inst = (UICheckBox*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setChecked(val);
	return 0;
}

static int UI_UICheckBox_changeCheck(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UICheckBox *inst = (UICheckBox*) *((PolyBase**)lua_touserdata(L, 1));
	inst->changeCheck();
	return 0;
}

static int UI_UICheckBox_isChecked(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UICheckBox *inst = (UICheckBox*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isChecked());
	return 1;
}

static int UI_UICheckBox_getCaptionLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UICheckBox *inst = (UICheckBox*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getCaptionLabel().c_str());
	return 1;
}

static int UI_delete_UICheckBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UICheckBox*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIColorPicker(lua_State *L) {
	UIColorPicker *inst = new UIColorPicker();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIColorPicker");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIColorPicker_updateSelectedColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	bool updateTextFields;
	if(lua_isboolean(L, 2)) {
		updateTextFields = lua_toboolean(L, 2) != 0;
	} else {
		updateTextFields = true;
	}
	bool updateHue;
	if(lua_isboolean(L, 3)) {
		updateHue = lua_toboolean(L, 3) != 0;
	} else {
		updateHue = true;
	}
	bool updateSV;
	if(lua_isboolean(L, 4)) {
		updateSV = lua_toboolean(L, 4) != 0;
	} else {
		updateSV = true;
	}
	inst->updateSelectedColor(updateTextFields, updateHue, updateSV);
	return 0;
}

static int UI_UIColorPicker_setHue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number hueNum = lua_tonumber(L, 2);
	inst->setHue(hueNum);
	return 0;
}

static int UI_UIColorPicker_setSaturationAndValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number S = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number V = lua_tonumber(L, 3);
	inst->setSaturationAndValue(S, V);
	return 0;
}

static int UI_UIColorPicker_updateColorFromMainSelector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	inst->updateColorFromMainSelector();
	return 0;
}

static int UI_UIColorPicker_updateColorFromHueSelector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	inst->updateColorFromHueSelector();
	return 0;
}

static int UI_UIColorPicker_rebuildFromTextInputs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	inst->rebuildFromTextInputs();
	return 0;
}

static int UI_UIColorPicker_cancelColorListeners(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	inst->cancelColorListeners();
	return 0;
}

static int UI_UIColorPicker_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UIColorPicker_onClose(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	inst->onClose();
	return 0;
}

static int UI_UIColorPicker_isContinuous(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isContinuous());
	return 1;
}

static int UI_UIColorPicker_setContinuous(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool _continuous = lua_toboolean(L, 2) != 0;
	inst->setContinuous(_continuous);
	return 0;
}

static int UI_UIColorPicker_setPickerColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color newColor = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setPickerColor(newColor);
	return 0;
}

static int UI_UIColorPicker_getSelectedColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker *inst = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	Color *retInst = new Color();
	*retInst = inst->getSelectedColor();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "UI.Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int UI_delete_UIColorPicker(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIColorPicker*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIColorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorPicker* colorPicker = (UIColorPicker*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color initialColor = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number width = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number height = lua_tonumber(L, 4);
	UIColorBox *inst = new UIColorBox(colorPicker, initialColor, width, height);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIColorBox");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIColorBox_getSelectedColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorBox *inst = (UIColorBox*) *((PolyBase**)lua_touserdata(L, 1));
	Color *retInst = new Color();
	*retInst = inst->getSelectedColor();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "UI.Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int UI_UIColorBox_setBoxColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorBox *inst = (UIColorBox*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color newColor = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setBoxColor(newColor);
	return 0;
}

static int UI_UIColorBox_showColorPicker(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIColorBox *inst = (UIColorBox*) *((PolyBase**)lua_touserdata(L, 1));
	inst->showColorPicker();
	return 0;
}

static int UI_delete_UIColorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIColorBox*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIComboBoxItem_get_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBoxItem *inst = (UIComboBoxItem*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->data;
	return 1;
}

static int UI_UIComboBoxItem_get_label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBoxItem *inst = (UIComboBoxItem*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->label.c_str());
	return 1;
}

static int UI_UIComboBoxItem_set_label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBoxItem *inst = (UIComboBoxItem*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->label = param;
	return 0;
}

static int UI_UIComboBoxItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String label = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* data = (void*) *((PolyBase**)lua_touserdata(L, 2));
	UIComboBoxItem *inst = new UIComboBoxItem(label, data);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIComboBoxItem");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_delete_UIComboBoxItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIComboBoxItem*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIComboBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIGlobalMenu* globalMenu = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number comboWidth = lua_tonumber(L, 2);
	UIComboBox *inst = new UIComboBox(globalMenu, comboWidth);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIComboBox");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIComboBox_toggleDropDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	inst->toggleDropDown();
	return 0;
}

static int UI_UIComboBox_clearItems(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearItems();
	return 0;
}

static int UI_UIComboBox_addComboItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String itemName = String(lua_tostring(L, 2));
	lua_pushinteger(L, inst->addComboItem(itemName));
	return 1;
}

static int UI_UIComboBox_getSelectedIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getSelectedIndex());
	return 1;
}

static int UI_UIComboBox_getSelectedItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSelectedItem();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UIComboBox_setSelectedIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newIndex = lua_tointeger(L, 2);
	inst->setSelectedIndex(newIndex);
	return 0;
}

static int UI_UIComboBox_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UIComboBox_getNumItems(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumItems());
	return 1;
}

static int UI_UIComboBox_getItemAtIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIComboBox *inst = (UIComboBox*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getItemAtIndex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_delete_UIComboBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIComboBox*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIElement(lua_State *L) {
	UIElement *inst = new UIElement();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIElement");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIElement_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIElement *inst = (UIElement*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_delete_UIElement(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIElement*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIEvent(lua_State *L) {
	UIEvent *inst = new UIEvent();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIEvent");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_delete_UIEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIEvent*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIFileDialog_get_action(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->action.c_str());
	return 1;
}

static int UI_UIFileDialog_set_action(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->action = param;
	return 0;
}

static int UI_UIFileDialog(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String baseDir = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool foldersOnly = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TUSERDATA);
	vector<String> extensions = *(vector<String>*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool allowMultiple = lua_toboolean(L, 4) != 0;
	UIFileDialog *inst = new UIFileDialog(baseDir, foldersOnly, extensions, allowMultiple);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIFileDialog");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIFileDialog_onClose(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	inst->onClose();
	return 0;
}

static int UI_UIFileDialog_clearEntries(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearEntries();
	return 0;
}

static int UI_UIFileDialog_showFolder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String folderPath = String(lua_tostring(L, 2));
	inst->showFolder(folderPath);
	return 0;
}

static int UI_UIFileDialog_canOpen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String extension = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->canOpen(extension));
	return 1;
}

static int UI_UIFileDialog_addToSidebar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String path = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String name = String(lua_tostring(L, 3));
	inst->addToSidebar(path, name);
	return 0;
}

static int UI_UIFileDialog_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UIFileDialog_getSelection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialog *inst = (UIFileDialog*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getSelection().c_str());
	return 1;
}

static int UI_delete_UIFileDialog(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIFileDialog*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIFileDialogEntry_get_canSelect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->canSelect);
	return 1;
}

static int UI_UIFileDialogEntry_get_bg(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->bg;
	return 1;
}

static int UI_UIFileDialogEntry_get_label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->label;
	return 1;
}

static int UI_UIFileDialogEntry_get_fileEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->fileEntry;
	return 1;
}

static int UI_UIFileDialogEntry_get_icon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->icon;
	return 1;
}

static int UI_UIFileDialogEntry_set_canSelect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->canSelect = param;
	return 0;
}

static int UI_UIFileDialogEntry_set_fileEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	OSFileEntry *argInst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 2));
	inst->fileEntry = *argInst;
	return 0;
}

static int UI_UIFileDialogEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry entry = *(OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool canSelect = lua_toboolean(L, 2) != 0;
	int width;
	if(lua_isnumber(L, 3)) {
		width = lua_tointeger(L, 3);
	} else {
		width = 340;
	}
	bool isPlace;
	if(lua_isboolean(L, 4)) {
		isPlace = lua_toboolean(L, 4) != 0;
	} else {
		isPlace = false;
	}
	UIFileDialogEntry *inst = new UIFileDialogEntry(entry, canSelect, width, isPlace);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIFileDialogEntry");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIFileDialogEntry_Select(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Select();
	return 0;
}

static int UI_UIFileDialogEntry_Deselect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIFileDialogEntry *inst = (UIFileDialogEntry*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Deselect();
	return 0;
}

static int UI_delete_UIFileDialogEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIFileDialogEntry*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_CreateFolderWindow_get_okButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CreateFolderWindow *inst = (CreateFolderWindow*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->okButton;
	return 1;
}

static int UI_CreateFolderWindow_get_cancelButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CreateFolderWindow *inst = (CreateFolderWindow*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->cancelButton;
	return 1;
}

static int UI_CreateFolderWindow_get_nameInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CreateFolderWindow *inst = (CreateFolderWindow*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->nameInput;
	return 1;
}

static int UI_CreateFolderWindow(lua_State *L) {
	CreateFolderWindow *inst = new CreateFolderWindow();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.CreateFolderWindow");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_delete_CreateFolderWindow(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((CreateFolderWindow*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIHScrollBar_get_minHandleSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHScrollBar *inst = (UIHScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->minHandleSize);
	return 1;
}

static int UI_UIHScrollBar_set_minHandleSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHScrollBar *inst = (UIHScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->minHandleSize = param;
	return 0;
}

static int UI_UIHScrollBar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number width = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number initialRatio = lua_tonumber(L, 3);
	UIHScrollBar *inst = new UIHScrollBar(width, height, initialRatio);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIHScrollBar");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIHScrollBar_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHScrollBar *inst = (UIHScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UIHScrollBar_getScrollValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHScrollBar *inst = (UIHScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getScrollValue());
	return 1;
}

static int UI_UIHScrollBar_scrollTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHScrollBar *inst = (UIHScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number scrollValue = lua_tonumber(L, 2);
	inst->scrollTo(scrollValue);
	return 0;
}

static int UI_UIHScrollBar_Scroll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHScrollBar *inst = (UIHScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amount = lua_tonumber(L, 2);
	inst->Scroll(amount);
	return 0;
}

static int UI_UIHScrollBar_setHandleRatio(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHScrollBar *inst = (UIHScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newRatio = lua_tonumber(L, 2);
	inst->setHandleRatio(newRatio);
	return 0;
}

static int UI_delete_UIHScrollBar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIHScrollBar*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIHSizer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number width = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number mainWidth = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool leftSizer = lua_toboolean(L, 4) != 0;
	UIHSizer *inst = new UIHSizer(width, height, mainWidth, leftSizer);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIHSizer");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIHSizer_setMainWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSizer *inst = (UIHSizer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	inst->setMainWidth(width);
	return 0;
}

static int UI_UIHSizer_getMainWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSizer *inst = (UIHSizer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getMainWidth());
	return 1;
}

static int UI_UIHSizer_addLeftChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSizer *inst = (UIHSizer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UIElement* element = (UIElement*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addLeftChild(element);
	return 0;
}

static int UI_UIHSizer_addRightChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSizer *inst = (UIHSizer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UIElement* element = (UIElement*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addRightChild(element);
	return 0;
}

static int UI_UIHSizer_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSizer *inst = (UIHSizer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UIHSizer_updateSizer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSizer *inst = (UIHSizer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->updateSizer();
	return 0;
}

static int UI_delete_UIHSizer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIHSizer*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIHSlider(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number start = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number _end = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number width = lua_tonumber(L, 3);
	UIHSlider *inst = new UIHSlider(start, _end, width);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIHSlider");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIHSlider_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSlider *inst = (UIHSlider*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UIHSlider_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSlider *inst = (UIHSlider*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UIHSlider_isContinuous(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSlider *inst = (UIHSlider*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isContinuous());
	return 1;
}

static int UI_UIHSlider_setContinuous(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSlider *inst = (UIHSlider*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool _continuous = lua_toboolean(L, 2) != 0;
	inst->setContinuous(_continuous);
	return 0;
}

static int UI_UIHSlider_setSliderValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSlider *inst = (UIHSlider*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number val = lua_tonumber(L, 2);
	inst->setSliderValue(val);
	return 0;
}

static int UI_UIHSlider_getSliderValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIHSlider *inst = (UIHSlider*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getSliderValue());
	return 1;
}

static int UI_delete_UIHSlider(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIHSlider*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIImageButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String imageName = String(lua_tostring(L, 1));
	UIImageButton *inst = new UIImageButton(imageName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIImageButton");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_delete_UIImageButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIImageButton*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIMenuItem_get_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuItem *inst = (UIMenuItem*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->data;
	return 1;
}

static int UI_UIMenuItem_get_label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuItem *inst = (UIMenuItem*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->label.c_str());
	return 1;
}

static int UI_UIMenuItem_get__id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuItem *inst = (UIMenuItem*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->_id.c_str());
	return 1;
}

static int UI_UIMenuItem_set_label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuItem *inst = (UIMenuItem*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->label = param;
	return 0;
}

static int UI_UIMenuItem_set__id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuItem *inst = (UIMenuItem*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->_id = param;
	return 0;
}

static int UI_UIMenuItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String label = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String _id = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	void* data = (void*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number comboWidth = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number comboHeight = lua_tonumber(L, 5);
	UIMenuItem *inst = new UIMenuItem(label, _id, data, comboWidth, comboHeight);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIMenuItem");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIMenuItem_isSelectable(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuItem *inst = (UIMenuItem*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isSelectable());
	return 1;
}

static int UI_delete_UIMenuItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIMenuItem*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIMenu(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number menuWidth = lua_tonumber(L, 1);
	UIMenu *inst = new UIMenu(menuWidth);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIMenu");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIMenu_addOption(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenu *inst = (UIMenu*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String label = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String _id = String(lua_tostring(L, 3));
	void* data;
	if(lua_isuserdata(L, 4)) {
		data = (void*) *((PolyBase**)lua_touserdata(L, 4));
	} else {
		data = NULL;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->addOption(label, _id, data);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UIMenu_addDivider(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenu *inst = (UIMenu*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->addDivider();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UIMenu_getSelectedItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenu *inst = (UIMenu*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSelectedItem();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UIMenu_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenu *inst = (UIMenu*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UIMenu_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenu *inst = (UIMenu*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UIMenu_fitToScreenVertical(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenu *inst = (UIMenu*) *((PolyBase**)lua_touserdata(L, 1));
	inst->fitToScreenVertical();
	return 0;
}

static int UI_delete_UIMenu(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIMenu*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIGlobalMenu_get_defaultMenuWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIGlobalMenu *inst = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->defaultMenuWidth);
	return 1;
}

static int UI_UIGlobalMenu_set_defaultMenuWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIGlobalMenu *inst = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->defaultMenuWidth = param;
	return 0;
}

static int UI_UIGlobalMenu(lua_State *L) {
	UIGlobalMenu *inst = new UIGlobalMenu();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIGlobalMenu");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIGlobalMenu_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIGlobalMenu *inst = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UIGlobalMenu_hideMenu(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIGlobalMenu *inst = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 1));
	inst->hideMenu();
	return 0;
}

static int UI_UIGlobalMenu_showMenu(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIGlobalMenu *inst = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number width = lua_tonumber(L, 4);
	PolyBase *ptrRetVal = (PolyBase*)inst->showMenu(x, y, width);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UIGlobalMenu_showMenuAtMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIGlobalMenu *inst = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->showMenuAtMouse(width);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_delete_UIGlobalMenu(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIGlobalMenu*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIMenuDivider(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number comboWidth = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number comboHeight = lua_tonumber(L, 2);
	UIMenuDivider *inst = new UIMenuDivider(comboWidth, comboHeight);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIMenuDivider");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIMenuDivider_isSelectable(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuDivider *inst = (UIMenuDivider*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isSelectable());
	return 1;
}

static int UI_delete_UIMenuDivider(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIMenuDivider*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIMenuBarEntry_get_bg(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntry *inst = (UIMenuBarEntry*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->bg;
	return 1;
}

static int UI_UIMenuBarEntry_get_label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntry *inst = (UIMenuBarEntry*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->label;
	return 1;
}

static int UI_UIMenuBarEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String name = String(lua_tostring(L, 1));
	UIMenuBarEntry *inst = new UIMenuBarEntry(name);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIMenuBarEntry");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIMenuBarEntry_addItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntry *inst = (UIMenuBarEntry*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String code = String(lua_tostring(L, 3));
	PolyKEY shortCut1;
	if(lua_isnumber(L, 4)) {
		shortCut1 = (PolyKEY)lua_tointeger(L, 4);
	} else {
		shortCut1 = KEY_UNKNOWN;
	}
	PolyKEY shortCut2;
	if(lua_isnumber(L, 5)) {
		shortCut2 = (PolyKEY)lua_tointeger(L, 5);
	} else {
		shortCut2 = KEY_UNKNOWN;
	}
	inst->addItem(name, code, shortCut1, shortCut2);
	return 0;
}

static int UI_UIMenuBarEntry_Select(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntry *inst = (UIMenuBarEntry*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Select();
	return 0;
}

static int UI_UIMenuBarEntry_Deselect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntry *inst = (UIMenuBarEntry*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Deselect();
	return 0;
}

static int UI_delete_UIMenuBarEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIMenuBarEntry*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIMenuBarEntryItem_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int UI_UIMenuBarEntryItem_get_code(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->code.c_str());
	return 1;
}

static int UI_UIMenuBarEntryItem_get_shortCut1(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->shortCut1);
	return 1;
}

static int UI_UIMenuBarEntryItem_get_shortCut2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->shortCut2);
	return 1;
}

static int UI_UIMenuBarEntryItem_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int UI_UIMenuBarEntryItem_set_code(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->code = param;
	return 0;
}

static int UI_UIMenuBarEntryItem_set_shortCut1(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	PolyKEY param = (PolyKEY)lua_tointeger(L, 2);
	inst->shortCut1 = param;
	return 0;
}

static int UI_UIMenuBarEntryItem_set_shortCut2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	PolyKEY param = (PolyKEY)lua_tointeger(L, 2);
	inst->shortCut2 = param;
	return 0;
}

static int UI_UIMenuBarEntryItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String name = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String code = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	PolyKEY shortCut1 = (PolyKEY)lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	PolyKEY shortCut2 = (PolyKEY)lua_tointeger(L, 4);
	UIMenuBarEntryItem *inst = new UIMenuBarEntryItem(name, code, shortCut1, shortCut2);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIMenuBarEntryItem");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIMenuBarEntryItem_checkShortCut(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBarEntryItem *inst = (UIMenuBarEntryItem*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY shortCut = (PolyKEY)lua_tointeger(L, 2);
	lua_pushboolean(L, inst->checkShortCut(shortCut));
	return 1;
}

static int UI_delete_UIMenuBarEntryItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIMenuBarEntryItem*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIMenuBar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int width = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UIGlobalMenu* globalMenu = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 2));
	UIMenuBar *inst = new UIMenuBar(width, globalMenu);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIMenuBar");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIMenuBar_showMenuForEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBar *inst = (UIMenuBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UIMenuBarEntry* entry = (UIMenuBarEntry*) *((PolyBase**)lua_touserdata(L, 2));
	inst->showMenuForEntry(entry);
	return 0;
}

static int UI_UIMenuBar_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBar *inst = (UIMenuBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UIMenuBar_addMenuBarEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBar *inst = (UIMenuBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->addMenuBarEntry(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UIMenuBar_getSelectedItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIMenuBar *inst = (UIMenuBar*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getSelectedItem().c_str());
	return 1;
}

static int UI_delete_UIMenuBar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIMenuBar*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIScrollContainer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity* scrolledEntity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool hScroll = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool vScroll = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number width = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number height = lua_tonumber(L, 5);
	UIScrollContainer *inst = new UIScrollContainer(scrolledEntity, hScroll, vScroll, width, height);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIScrollContainer");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIScrollContainer_setContentSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newContentWidth = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number newContentHeight = lua_tonumber(L, 3);
	inst->setContentSize(newContentWidth, newContentHeight);
	return 0;
}

static int UI_UIScrollContainer_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UIScrollContainer_setScrollValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number xScroll = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number yScroll = lua_tonumber(L, 3);
	inst->setScrollValue(xScroll, yScroll);
	return 0;
}

static int UI_UIScrollContainer_scrollVertical(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amount = lua_tonumber(L, 2);
	inst->scrollVertical(amount);
	return 0;
}

static int UI_UIScrollContainer_scrollHorizontal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amount = lua_tonumber(L, 2);
	inst->scrollHorizontal(amount);
	return 0;
}

static int UI_UIScrollContainer_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UIScrollContainer_getContentSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getContentSize();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "UI.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int UI_UIScrollContainer_onMouseWheelDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseWheelDown(x, y);
	return 0;
}

static int UI_UIScrollContainer_onMouseWheelUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseWheelUp(x, y);
	return 0;
}

static int UI_UIScrollContainer_getVScrollWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getVScrollWidth());
	return 1;
}

static int UI_UIScrollContainer_getVScrollBar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getVScrollBar();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UIScrollContainer_getHScrollBar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIScrollContainer *inst = (UIScrollContainer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getHScrollBar();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_delete_UIScrollContainer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIScrollContainer*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_SyntaxHighlightToken_get_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SyntaxHighlightToken *inst = (SyntaxHighlightToken*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->color;
	return 1;
}

static int UI_SyntaxHighlightToken_get_text(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SyntaxHighlightToken *inst = (SyntaxHighlightToken*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->text.c_str());
	return 1;
}

static int UI_SyntaxHighlightToken_get_overrideType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SyntaxHighlightToken *inst = (SyntaxHighlightToken*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->overrideType);
	return 1;
}

static int UI_SyntaxHighlightToken_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SyntaxHighlightToken *inst = (SyntaxHighlightToken*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int UI_SyntaxHighlightToken_set_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SyntaxHighlightToken *inst = (SyntaxHighlightToken*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->color = *argInst;
	return 0;
}

static int UI_SyntaxHighlightToken_set_text(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SyntaxHighlightToken *inst = (SyntaxHighlightToken*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->text = param;
	return 0;
}

static int UI_SyntaxHighlightToken_set_overrideType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SyntaxHighlightToken *inst = (SyntaxHighlightToken*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->overrideType = param;
	return 0;
}

static int UI_SyntaxHighlightToken_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SyntaxHighlightToken *inst = (SyntaxHighlightToken*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int UI_SyntaxHighlightToken(lua_State *L) {
	SyntaxHighlightToken *inst = new SyntaxHighlightToken();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.SyntaxHighlightToken");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_delete_SyntaxHighlightToken(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SyntaxHighlightToken*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_LineColorData_get_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LineColorData *inst = (LineColorData*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->color;
	return 1;
}

static int UI_LineColorData_get_rangeStart(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LineColorData *inst = (LineColorData*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->rangeStart);
	return 1;
}

static int UI_LineColorData_get_rangeEnd(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LineColorData *inst = (LineColorData*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->rangeEnd);
	return 1;
}

static int UI_LineColorData_set_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LineColorData *inst = (LineColorData*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->color = *argInst;
	return 0;
}

static int UI_LineColorData_set_rangeStart(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LineColorData *inst = (LineColorData*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->rangeStart = param;
	return 0;
}

static int UI_LineColorData_set_rangeEnd(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LineColorData *inst = (LineColorData*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->rangeEnd = param;
	return 0;
}

static int UI_LineColorData(lua_State *L) {
	LineColorData *inst = new LineColorData();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.LineColorData");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_delete_LineColorData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((LineColorData*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UITextInput_get_useStrongHinting(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useStrongHinting);
	return 1;
}

static int UI_UITextInput_set_useStrongHinting(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useStrongHinting = param;
	return 0;
}

static int UI_UITextInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TBOOLEAN);
	bool multiLine = lua_toboolean(L, 1) != 0;
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	UITextInput *inst = new UITextInput(multiLine, width, height);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UITextInput");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UITextInput_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UITextInput_setText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	bool s_endChangeEvent;
	if(lua_isboolean(L, 3)) {
		s_endChangeEvent = lua_toboolean(L, 3) != 0;
	} else {
		s_endChangeEvent = true;
	}
	inst->setText(text, s_endChangeEvent);
	return 0;
}

static int UI_UITextInput_getText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getText().c_str());
	return 1;
}

static int UI_UITextInput_onLoseFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->onLoseFocus();
	return 0;
}

static int UI_UITextInput_insertLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	String lineText;
	if(lua_isstring(L, 2)) {
		lineText = lua_tostring(L, 2);
	} else {
		lineText = "";
	}
	lua_pushinteger(L, inst->insertLine(lineText));
	return 1;
}

static int UI_UITextInput_onKeyDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY key = (PolyKEY)lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	wchar_t charCode = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
	inst->onKeyDown(key, charCode);
	return 0;
}

static int UI_UITextInput_clearSelection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearSelection();
	return 0;
}

static int UI_UITextInput_setSelection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int lineStart = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int lineEnd = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int colStart = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int colEnd = lua_tointeger(L, 5);
	inst->setSelection(lineStart, lineEnd, colStart, colEnd);
	return 0;
}

static int UI_UITextInput_deleteSelection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->deleteSelection();
	return 0;
}

static int UI_UITextInput_selectAll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->selectAll();
	return 0;
}

static int UI_UITextInput_Undo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Undo();
	return 0;
}

static int UI_UITextInput_Redo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Redo();
	return 0;
}

static int UI_UITextInput_Cut(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Cut();
	return 0;
}

static int UI_UITextInput_Copy(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Copy();
	return 0;
}

static int UI_UITextInput_Paste(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Paste();
	return 0;
}

static int UI_UITextInput_enableLineNumbers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enableLineNumbers(val);
	return 0;
}

static int UI_UITextInput_setBackgroundColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setBackgroundColor(color);
	return 0;
}

static int UI_UITextInput_setSelectionColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setSelectionColor(color);
	return 0;
}

static int UI_UITextInput_setCursorColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setCursorColor(color);
	return 0;
}

static int UI_UITextInput_setTextColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setTextColor(color);
	return 0;
}

static int UI_UITextInput_setLineNumberColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setLineNumberColor(color);
	return 0;
}

static int UI_UITextInput_checkBufferLines(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->checkBufferLines();
	return 0;
}

static int UI_UITextInput_replaceAll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String what = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String withWhat = String(lua_tostring(L, 3));
	inst->replaceAll(what, withWhat);
	return 0;
}

static int UI_UITextInput_findString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String stringToFind = String(lua_tostring(L, 2));
	bool replace;
	if(lua_isboolean(L, 3)) {
		replace = lua_toboolean(L, 3) != 0;
	} else {
		replace = false;
	}
	String replaceString;
	if(lua_isstring(L, 4)) {
		replaceString = lua_tostring(L, 4);
	} else {
		replaceString = "";
	}
	inst->findString(stringToFind, replace, replaceString);
	return 0;
}

static int UI_UITextInput_getFindMatches(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String stringToFind = String(lua_tostring(L, 2));
	return 0;
}

static int UI_UITextInput_findNext(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->findNext();
	return 0;
}

static int UI_UITextInput_findPrevious(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->findPrevious();
	return 0;
}

static int UI_UITextInput_findCurrent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->findCurrent();
	return 0;
}

static int UI_UITextInput_showLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int lineNumber = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool top = lua_toboolean(L, 3) != 0;
	inst->showLine(lineNumber, top);
	return 0;
}

static int UI_UITextInput_setSyntaxHighlighter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UITextInputSyntaxHighlighter* syntaxHighlighter = (UITextInputSyntaxHighlighter*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setSyntaxHighlighter(syntaxHighlighter);
	return 0;
}

static int UI_UITextInput_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UITextInput_setNumberOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setNumberOnly(val);
	return 0;
}

static int UI_UITextInput_getLineText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	lua_pushstring(L, inst->getLineText(index).c_str());
	return 1;
}

static int UI_UITextInput_getSelectionText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getSelectionText().c_str());
	return 1;
}

static int UI_UITextInput_insertText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	bool updateWordWrap;
	if(lua_isboolean(L, 3)) {
		updateWordWrap = lua_toboolean(L, 3) != 0;
	} else {
		updateWordWrap = true;
	}
	inst->insertText(text, updateWordWrap);
	return 0;
}

static int UI_UITextInput_setCaretPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int position = lua_tointeger(L, 2);
	inst->setCaretPosition(position);
	return 0;
}

static int UI_UITextInput_getScrollContainer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getScrollContainer();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITextInput_shiftText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	bool left;
	if(lua_isboolean(L, 2)) {
		left = lua_toboolean(L, 2) != 0;
	} else {
		left = false;
	}
	inst->shiftText(left);
	return 0;
}

static int UI_UITextInput_convertIndentToTabs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->convertIndentToTabs();
	return 0;
}

static int UI_UITextInput_convertIndentToSpaces(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->convertIndentToSpaces();
	return 0;
}

static int UI_UITextInput_doMultilineResize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITextInput *inst = (UITextInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->doMultilineResize();
	return 0;
}

static int UI_UITextInput_setMenuSingleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIGlobalMenu* _globalMenu = (UIGlobalMenu*) *((PolyBase**)lua_touserdata(L, 1));
	UITextInput::setMenuSingleton(_globalMenu);
	return 0;
}

static int UI_delete_UITextInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UITextInput*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UITree_get_handleRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->handleRotation);
	return 1;
}

static int UI_UITree_set_handleRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->handleRotation = param;
	return 0;
}

static int UI_UITree(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String icon = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number treeWidth = lua_tonumber(L, 3);
	Number treeOffset;
	if(lua_isnumber(L, 4)) {
		treeOffset = lua_tonumber(L, 4);
	} else {
		treeOffset = 0;
	}
	UITree *inst = new UITree(icon, text, treeWidth, treeOffset);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UITree");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UITree_toggleCollapsed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	inst->toggleCollapsed();
	return 0;
}

static int UI_UITree_addTreeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String icon = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String text = String(lua_tostring(L, 3));
	void* userData;
	if(lua_isuserdata(L, 4)) {
		userData = (void*) *((PolyBase**)lua_touserdata(L, 4));
	} else {
		userData = NULL;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->addTreeChild(icon, text, userData);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITree_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UITree_refreshTree(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	inst->refreshTree();
	return 0;
}

static int UI_UITree_getTreeHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getTreeHeight());
	return 1;
}

static int UI_UITree_setParent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UITree* parent = (UITree*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setParent(parent);
	return 0;
}

static int UI_UITree_clearSelection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UITree* selectedNode = (UITree*) *((PolyBase**)lua_touserdata(L, 2));
	inst->clearSelection(selectedNode);
	return 0;
}

static int UI_UITree_isCollapsed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isCollapsed());
	return 1;
}

static int UI_UITree_getUserData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getUserData();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITree_setUserData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* data = (void*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setUserData(data);
	return 0;
}

static int UI_UITree_getSelectedNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSelectedNode();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITree_setIcon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String iconFile = String(lua_tostring(L, 2));
	inst->setIcon(iconFile);
	return 0;
}

static int UI_UITree_setSelected(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	bool byKey;
	if(lua_isboolean(L, 2)) {
		byKey = lua_toboolean(L, 2) != 0;
	} else {
		byKey = false;
	}
	inst->setSelected(byKey);
	return 0;
}

static int UI_UITree_setLabelText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	inst->setLabelText(text);
	return 0;
}

static int UI_UITree_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	inst->Resize(width);
	return 0;
}

static int UI_UITree_getNumTreeChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumTreeChildren());
	return 1;
}

static int UI_UITree_getTreeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getTreeChild(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITree_removeTreeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UITree* child = (UITree*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeTreeChild(child);
	return 0;
}

static int UI_UITree_clearTree(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearTree();
	return 0;
}

static int UI_UITree_getLabelText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getLabelText().c_str());
	return 1;
}

static int UI_UITree_getParent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getParent();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITree_hasTreeChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->hasTreeChildren());
	return 1;
}

static int UI_UITree_getPrevSibling(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getPrevSibling();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITree_getNextSibling(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getNextSibling();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITree_getCellHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getCellHeight());
	return 1;
}

static int UI_UITree_isSelectedByKey(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree *inst = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isSelectedByKey());
	return 1;
}

static int UI_delete_UITree(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UITree*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UITreeContainer_get_scrollChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITreeContainer *inst = (UITreeContainer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->scrollChild;
	return 1;
}

static int UI_UITreeContainer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String icon = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number treeWidth = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number treeHeight = lua_tonumber(L, 4);
	UITreeContainer *inst = new UITreeContainer(icon, text, treeWidth, treeHeight);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UITreeContainer");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UITreeContainer_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITreeContainer *inst = (UITreeContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UITreeContainer_getRootNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITreeContainer *inst = (UITreeContainer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getRootNode();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int UI_UITreeContainer_onKeyDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITreeContainer *inst = (UITreeContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY key = (PolyKEY)lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	wchar_t charCode = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
	inst->onKeyDown(key, charCode);
	return 0;
}

static int UI_UITreeContainer_onGainFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITreeContainer *inst = (UITreeContainer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->onGainFocus();
	return 0;
}

static int UI_UITreeContainer_scrollToNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITreeContainer *inst = (UITreeContainer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UITree* node = (UITree*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool showAtTop = lua_toboolean(L, 3) != 0;
	inst->scrollToNode(node, showAtTop);
	return 0;
}

static int UI_delete_UITreeContainer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UITreeContainer*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UITreeEvent_get_selection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITreeEvent *inst = (UITreeEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->selection;
	return 1;
}

static int UI_UITreeEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UITree* selection = (UITree*) *((PolyBase**)lua_touserdata(L, 1));
	UITreeEvent *inst = new UITreeEvent(selection);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UITreeEvent");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_delete_UITreeEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UITreeEvent*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIVScrollBar_get_minHandleSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->minHandleSize);
	return 1;
}

static int UI_UIVScrollBar_set_minHandleSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->minHandleSize = param;
	return 0;
}

static int UI_UIVScrollBar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number width = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number initialRatio = lua_tonumber(L, 3);
	UIVScrollBar *inst = new UIVScrollBar(width, height, initialRatio);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIVScrollBar");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIVScrollBar_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int UI_UIVScrollBar_getScrollValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getScrollValue());
	return 1;
}

static int UI_UIVScrollBar_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newHeight = lua_tointeger(L, 2);
	inst->Resize(newHeight);
	return 0;
}

static int UI_UIVScrollBar_scrollTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number scrollValue = lua_tonumber(L, 2);
	inst->scrollTo(scrollValue);
	return 0;
}

static int UI_UIVScrollBar_Scroll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amount = lua_tonumber(L, 2);
	inst->Scroll(amount);
	return 0;
}

static int UI_UIVScrollBar_setTickSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newTickSize = lua_tonumber(L, 2);
	inst->setTickSize(newTickSize);
	return 0;
}

static int UI_UIVScrollBar_onMouseWheelDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseWheelDown(x, y);
	return 0;
}

static int UI_UIVScrollBar_onMouseWheelUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseWheelUp(x, y);
	return 0;
}

static int UI_UIVScrollBar_scrollUpOneTick(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	inst->scrollUpOneTick();
	return 0;
}

static int UI_UIVScrollBar_scrollDownOneTick(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	inst->scrollDownOneTick();
	return 0;
}

static int UI_UIVScrollBar_setHandleRatio(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVScrollBar *inst = (UIVScrollBar*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newRatio = lua_tonumber(L, 2);
	inst->setHandleRatio(newRatio);
	return 0;
}

static int UI_delete_UIVScrollBar(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIVScrollBar*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIVSizer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number width = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number mainHeight = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool topSizer = lua_toboolean(L, 4) != 0;
	UIVSizer *inst = new UIVSizer(width, height, mainHeight, topSizer);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIVSizer");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIVSizer_setMainHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVSizer *inst = (UIVSizer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	inst->setMainHeight(height);
	return 0;
}

static int UI_UIVSizer_getMainHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVSizer *inst = (UIVSizer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getMainHeight());
	return 1;
}

static int UI_UIVSizer_addTopChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVSizer *inst = (UIVSizer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UIElement* element = (UIElement*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addTopChild(element);
	return 0;
}

static int UI_UIVSizer_addBottomChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVSizer *inst = (UIVSizer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	UIElement* element = (UIElement*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addBottomChild(element);
	return 0;
}

static int UI_UIVSizer_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVSizer *inst = (UIVSizer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->Resize(width, height);
	return 0;
}

static int UI_UIVSizer_updateSizer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIVSizer *inst = (UIVSizer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->updateSizer();
	return 0;
}

static int UI_delete_UIVSizer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIVSizer*) *inst);
	*inst = NULL;
	return 0;
}

static int UI_UIWindow_get_padding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->padding);
	return 1;
}

static int UI_UIWindow_get_topPadding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->topPadding);
	return 1;
}

static int UI_UIWindow_get_closeOnEscape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->closeOnEscape);
	return 1;
}

static int UI_UIWindow_set_padding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->padding = param;
	return 0;
}

static int UI_UIWindow_set_topPadding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->topPadding = param;
	return 0;
}

static int UI_UIWindow_set_closeOnEscape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->closeOnEscape = param;
	return 0;
}

static int UI_UIWindow(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String windowName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	UIWindow *inst = new UIWindow(windowName, width, height);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "UI.UIWindow");
	lua_setmetatable(L, -2);
	return 1;
}

static int UI_UIWindow_showWindow(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	inst->showWindow();
	return 0;
}

static int UI_UIWindow_hideWindow(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	inst->hideWindow();
	return 0;
}

static int UI_UIWindow_onKeyDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY key = (PolyKEY)lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	wchar_t charCode = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
	inst->onKeyDown(key, charCode);
	return 0;
}

static int UI_UIWindow_onClose(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	inst->onClose();
	return 0;
}

static int UI_UIWindow_onLoseFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	inst->onLoseFocus();
	return 0;
}

static int UI_UIWindow_setWindowSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number h = lua_tonumber(L, 3);
	inst->setWindowSize(w, h);
	return 0;
}

static int UI_UIWindow_setWindowCaption(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String caption = String(lua_tostring(L, 2));
	inst->setWindowCaption(caption);
	return 0;
}

static int UI_UIWindow_onMouseDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	UIWindow *inst = (UIWindow*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseDown(x, y);
	return 0;
}

static int UI_delete_UIWindow(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((UIWindow*) *inst);
	*inst = NULL;
	return 0;
}

} // namespace Polycode
