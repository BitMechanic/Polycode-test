#pragma once

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
} // extern "C" 

#include "Polycode2DPhysics.h"
#include "PolyPhysicsScreen.h"
#include "PolyPhysicsScreenEntity.h"

using namespace std;


namespace Polycode {

static int Physics2D_PhysicsScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number worldScale = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number freq = lua_tonumber(L, 2);
	int velIterations;
	if(lua_isnumber(L, 3)) {
		velIterations = lua_tointeger(L, 3);
	} else {
		velIterations = 10;
	}
	int posIterations;
	if(lua_isnumber(L, 4)) {
		posIterations = lua_tointeger(L, 4);
	} else {
		posIterations = 10;
	}
	PhysicsScreen *inst = new PhysicsScreen(worldScale, freq, velIterations, posIterations);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics2D.PhysicsScreen");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics2D_PhysicsScreen_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Physics2D_PhysicsScreen_addPhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* newEntity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int entType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool isStatic = lua_toboolean(L, 4) != 0;
	Number friction;
	if(lua_isnumber(L, 5)) {
		friction = lua_tonumber(L, 5);
	} else {
		friction = 0.1;
	}
	Number density;
	if(lua_isnumber(L, 6)) {
		density = lua_tonumber(L, 6);
	} else {
		density = 1;
	}
	Number restitution;
	if(lua_isnumber(L, 7)) {
		restitution = lua_tonumber(L, 7);
	} else {
		restitution = 0;
	}
	bool isSensor;
	if(lua_isboolean(L, 8)) {
		isSensor = lua_toboolean(L, 8) != 0;
	} else {
		isSensor = false;
	}
	bool fixedRotation;
	if(lua_isboolean(L, 9)) {
		fixedRotation = lua_toboolean(L, 9) != 0;
	} else {
		fixedRotation = false;
	}
	int groupIndex;
	if(lua_isnumber(L, 10)) {
		groupIndex = lua_tointeger(L, 10);
	} else {
		groupIndex = 0;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->addPhysicsChild(newEntity, entType, isStatic, friction, density, restitution, isSensor, fixedRotation, groupIndex);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_trackPhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* newEntity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int entType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool isStatic = lua_toboolean(L, 4) != 0;
	Number friction;
	if(lua_isnumber(L, 5)) {
		friction = lua_tonumber(L, 5);
	} else {
		friction = 0.1;
	}
	Number density;
	if(lua_isnumber(L, 6)) {
		density = lua_tonumber(L, 6);
	} else {
		density = 1;
	}
	Number restitution;
	if(lua_isnumber(L, 7)) {
		restitution = lua_tonumber(L, 7);
	} else {
		restitution = 0;
	}
	bool isSensor;
	if(lua_isboolean(L, 8)) {
		isSensor = lua_toboolean(L, 8) != 0;
	} else {
		isSensor = false;
	}
	bool fixedRotation;
	if(lua_isboolean(L, 9)) {
		fixedRotation = lua_toboolean(L, 9) != 0;
	} else {
		fixedRotation = false;
	}
	int groupIndex;
	if(lua_isnumber(L, 10)) {
		groupIndex = lua_tointeger(L, 10);
	} else {
		groupIndex = 0;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->trackPhysicsChild(newEntity, entType, isStatic, friction, density, restitution, isSensor, fixedRotation, groupIndex);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_stopTrackingChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* entity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->stopTrackingChild(entity);
	return 0;
}

static int Physics2D_PhysicsScreen_removePhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* entityToRemove = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removePhysicsChild(entityToRemove);
	return 0;
}

static int Physics2D_PhysicsScreen_removeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* entityToRemove = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeChild(entityToRemove);
	return 0;
}

static int Physics2D_PhysicsScreen_addCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* newEntity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int entType = lua_tointeger(L, 3);
	int groupIndex;
	if(lua_isnumber(L, 4)) {
		groupIndex = lua_tointeger(L, 4);
	} else {
		groupIndex = 0;
	}
	bool sensorOnly;
	if(lua_isboolean(L, 5)) {
		sensorOnly = lua_toboolean(L, 5) != 0;
	} else {
		sensorOnly = true;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->addCollisionChild(newEntity, entType, groupIndex, sensorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_trackCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* newEntity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int entType = lua_tointeger(L, 3);
	int groupIndex;
	if(lua_isnumber(L, 4)) {
		groupIndex = lua_tointeger(L, 4);
	} else {
		groupIndex = 0;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->trackCollisionChild(newEntity, entType, groupIndex);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_destroyJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	PhysicsJoint* joint = (PhysicsJoint*) *((PolyBase**)lua_touserdata(L, 2));
	inst->destroyJoint(joint);
	return 0;
}

static int Physics2D_PhysicsScreen_createDistanceJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent1 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ScreenEntity* ent2 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool collideConnected = lua_toboolean(L, 4) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->createDistanceJoint(ent1, ent2, collideConnected);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_createPrismaticJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent1 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ScreenEntity* ent2 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Vector2 worldAxis = *(Vector2*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number ax = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number ay = lua_tonumber(L, 6);
	bool collideConnected;
	if(lua_isboolean(L, 7)) {
		collideConnected = lua_toboolean(L, 7) != 0;
	} else {
		collideConnected = false;
	}
	Number lowerTranslation;
	if(lua_isnumber(L, 8)) {
		lowerTranslation = lua_tonumber(L, 8);
	} else {
		lowerTranslation = 0;
	}
	Number upperTranslation;
	if(lua_isnumber(L, 9)) {
		upperTranslation = lua_tonumber(L, 9);
	} else {
		upperTranslation = 0;
	}
	bool enableLimit;
	if(lua_isboolean(L, 10)) {
		enableLimit = lua_toboolean(L, 10) != 0;
	} else {
		enableLimit = false;
	}
	Number motorSpeed;
	if(lua_isnumber(L, 11)) {
		motorSpeed = lua_tonumber(L, 11);
	} else {
		motorSpeed = 0;
	}
	Number motorForce;
	if(lua_isnumber(L, 12)) {
		motorForce = lua_tonumber(L, 12);
	} else {
		motorForce = 0;
	}
	bool motorEnabled;
	if(lua_isboolean(L, 13)) {
		motorEnabled = lua_toboolean(L, 13) != 0;
	} else {
		motorEnabled = false;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->createPrismaticJoint(ent1, ent2, worldAxis, ax, ay, collideConnected, lowerTranslation, upperTranslation, enableLimit, motorSpeed, motorForce, motorEnabled);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_createRevoluteJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent1 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ScreenEntity* ent2 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number ax = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number ay = lua_tonumber(L, 5);
	bool collideConnected;
	if(lua_isboolean(L, 6)) {
		collideConnected = lua_toboolean(L, 6) != 0;
	} else {
		collideConnected = false;
	}
	bool enableLimit;
	if(lua_isboolean(L, 7)) {
		enableLimit = lua_toboolean(L, 7) != 0;
	} else {
		enableLimit = false;
	}
	Number lowerLimit;
	if(lua_isnumber(L, 8)) {
		lowerLimit = lua_tonumber(L, 8);
	} else {
		lowerLimit = 0;
	}
	Number upperLimit;
	if(lua_isnumber(L, 9)) {
		upperLimit = lua_tonumber(L, 9);
	} else {
		upperLimit = 0;
	}
	bool motorEnabled;
	if(lua_isboolean(L, 10)) {
		motorEnabled = lua_toboolean(L, 10) != 0;
	} else {
		motorEnabled = false;
	}
	Number motorSpeed;
	if(lua_isnumber(L, 11)) {
		motorSpeed = lua_tonumber(L, 11);
	} else {
		motorSpeed = 0;
	}
	Number maxTorque;
	if(lua_isnumber(L, 12)) {
		maxTorque = lua_tonumber(L, 12);
	} else {
		maxTorque = 0;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->createRevoluteJoint(ent1, ent2, ax, ay, collideConnected, enableLimit, lowerLimit, upperLimit, motorEnabled, motorSpeed, maxTorque);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_applyForce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 4);
	inst->applyForce(ent, fx, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_applyImpulse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 4);
	inst->applyImpulse(ent, fx, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_setGravity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 newGravity = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setGravity(newGravity);
	return 0;
}

static int Physics2D_PhysicsScreen_setTransform(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector2 pos = *(Vector2*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number angle = lua_tonumber(L, 4);
	inst->setTransform(ent, pos, angle);
	return 0;
}

static int Physics2D_PhysicsScreen_getPhysicsEntityByShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	b2Shape* shape = (b2Shape*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getPhysicsEntityByShape(shape);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_getPhysicsEntityByFixture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	b2Fixture* fixture = (b2Fixture*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getPhysicsEntityByFixture(fixture);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_setVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 4);
	inst->setVelocity(ent, fx, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_setVelocityX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	inst->setVelocityX(ent, fx);
	return 0;
}

static int Physics2D_PhysicsScreen_setVelocityY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 3);
	inst->setVelocityY(ent, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_setAngularVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number spin = lua_tonumber(L, 3);
	inst->setAngularVelocity(ent, spin);
	return 0;
}

static int Physics2D_PhysicsScreen_getVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getVelocity(ent);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Physics2D.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Physics2D_PhysicsScreen_BeginContact(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	b2Contact* contact = (b2Contact*) *((PolyBase**)lua_touserdata(L, 2));
	inst->BeginContact(contact);
	return 0;
}

static int Physics2D_PhysicsScreen_EndContact(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	b2Contact* contact = (b2Contact*) *((PolyBase**)lua_touserdata(L, 2));
	inst->EndContact(contact);
	return 0;
}

static int Physics2D_PhysicsScreen_PreSolve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	b2Contact* contact = (b2Contact*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	b2Manifold* oldManifold = (b2Manifold*) *((PolyBase**)lua_touserdata(L, 3));
	inst->PreSolve(contact, oldManifold);
	return 0;
}

static int Physics2D_PhysicsScreen_PostSolve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	b2Contact* contact = (b2Contact*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	b2ContactImpulse* impulse = (b2ContactImpulse*) *((PolyBase**)lua_touserdata(L, 3));
	inst->PostSolve(contact, impulse);
	return 0;
}

static int Physics2D_PhysicsScreen_wakeUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->wakeUp(ent);
	return 0;
}

static int Physics2D_PhysicsScreen_getEntityAtPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	PolyBase *ptrRetVal = (PolyBase*)inst->getEntityAtPosition(x, y);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_testEntityAtPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number x = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number y = lua_tonumber(L, 4);
	lua_pushboolean(L, inst->testEntityAtPosition(ent, x, y));
	return 1;
}

static int Physics2D_PhysicsScreen_testEntityCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent1 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ScreenEntity* ent2 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushboolean(L, inst->testEntityCollision(ent1, ent2));
	return 1;
}

static int Physics2D_PhysicsScreen_isEntityColliding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent1 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushboolean(L, inst->isEntityColliding(ent1));
	return 1;
}

static int Physics2D_PhysicsScreen_Shutdown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Shutdown();
	return 0;
}

static int Physics2D_PhysicsScreen_getPhysicsByScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* ent = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getPhysicsByScreenEntity(ent);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreen_destroyMouseJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	b2MouseJoint* mJoint = (b2MouseJoint*) *((PolyBase**)lua_touserdata(L, 2));
	inst->destroyMouseJoint(mJoint);
	return 0;
}

static int Physics2D_delete_PhysicsScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsScreen*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics2D_PhysicsJoint_get_box2DJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsJoint *inst = (PhysicsJoint*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->box2DJoint;
	return 1;
}

static int Physics2D_PhysicsJoint(lua_State *L) {
	PhysicsJoint *inst = new PhysicsJoint();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics2D.PhysicsJoint");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics2D_delete_PhysicsJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsJoint*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics2D_PhysicsScreenEvent_get_entity1(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->entity1;
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_entity2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->entity2;
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_localCollisionNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->localCollisionNormal;
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_worldCollisionNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->worldCollisionNormal;
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_localCollisionPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->localCollisionPoint;
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_worldCollisionPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->worldCollisionPoint;
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_impactStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->impactStrength);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_frictionStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->frictionStrength);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_set_localCollisionNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->localCollisionNormal = *argInst;
	return 0;
}

static int Physics2D_PhysicsScreenEvent_set_worldCollisionNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->worldCollisionNormal = *argInst;
	return 0;
}

static int Physics2D_PhysicsScreenEvent_set_localCollisionPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->localCollisionPoint = *argInst;
	return 0;
}

static int Physics2D_PhysicsScreenEvent_set_worldCollisionPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->worldCollisionPoint = *argInst;
	return 0;
}

static int Physics2D_PhysicsScreenEvent_set_impactStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->impactStrength = param;
	return 0;
}

static int Physics2D_PhysicsScreenEvent_set_frictionStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->frictionStrength = param;
	return 0;
}

static int Physics2D_PhysicsScreenEvent(lua_State *L) {
	PhysicsScreenEvent *inst = new PhysicsScreenEvent();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics2D.PhysicsScreenEvent");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_getFirstEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getFirstEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreenEvent_getSecondEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSecondEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_delete_PhysicsScreenEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsScreenEvent*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics2D_PhysicsScreenEntity_get_body(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->body;
	return 1;
}

static int Physics2D_PhysicsScreenEntity_get_fixture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->fixture;
	return 1;
}

static int Physics2D_PhysicsScreenEntity_get_collisionOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->collisionOnly);
	return 1;
}

static int Physics2D_PhysicsScreenEntity_set_collisionOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->collisionOnly = param;
	return 0;
}

static int Physics2D_PhysicsScreenEntity(lua_State *L) {
	PhysicsScreenEntity *inst = new PhysicsScreenEntity();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics2D.PhysicsScreenEntity");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics2D_PhysicsScreenEntity_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Physics2D_PhysicsScreenEntity_getScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getScreenEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_PhysicsScreenEntity_applyTorque(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number torque = lua_tonumber(L, 2);
	inst->applyTorque(torque);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_applyForce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 force = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->applyForce(force);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_applyImpulse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 3);
	inst->applyImpulse(fx, fy);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setTransform(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 pos = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number angle = lua_tonumber(L, 3);
	inst->setTransform(pos, angle);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 3);
	inst->setVelocity(fx, fy);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setVelocityX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 2);
	inst->setVelocityX(fx);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setVelocityY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 2);
	inst->setVelocityY(fy);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setLinearDamping(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number damping = lua_tonumber(L, 2);
	inst->setLinearDamping(damping);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setAngularDamping(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number damping = lua_tonumber(L, 2);
	inst->setAngularDamping(damping);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setFriction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 2);
	inst->setFriction(friction);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_getLinearDamping(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getLinearDamping());
	return 1;
}

static int Physics2D_PhysicsScreenEntity_getAngularDamping(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getAngularDamping());
	return 1;
}

static int Physics2D_PhysicsScreenEntity_getFriction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getFriction());
	return 1;
}

static int Physics2D_PhysicsScreenEntity_setDensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number density = lua_tonumber(L, 2);
	inst->setDensity(density);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_getDensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getDensity());
	return 1;
}

static int Physics2D_PhysicsScreenEntity_setCollisionCategory(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int categoryBits = lua_tointeger(L, 2);
	inst->setCollisionCategory(categoryBits);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setCollisionMask(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int maskBits = lua_tointeger(L, 2);
	inst->setCollisionMask(maskBits);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setCollisionGroupIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int group = lua_tointeger(L, 2);
	inst->setCollisionGroupIndex(group);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_getFixture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getFixture(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics2D_delete_PhysicsScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsScreenEntity*) *inst);
	*inst = NULL;
	return 0;
}

} // namespace Polycode
