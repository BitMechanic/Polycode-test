#pragma once
#include <PolycodeUI.h>
extern "C" {
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
int _PolyExport luaopen_UI(lua_State *L);
}
