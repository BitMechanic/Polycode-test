#pragma once

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
} // extern "C" 

#include "Polycode3DPhysics.h"
#include "PolyCollisionScene.h"
#include "PolyCollisionSceneEntity.h"
#include "PolyPhysicsScene.h"
#include "PolyPhysicsSceneEntity.h"

using namespace std;


namespace Polycode {

static int Physics3D_CollisionScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 size = *(Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	bool virtualScene;
	if(lua_isboolean(L, 2)) {
		virtualScene = lua_toboolean(L, 2) != 0;
	} else {
		virtualScene = false;
	}
	bool deferInitCollision;
	if(lua_isboolean(L, 3)) {
		deferInitCollision = lua_toboolean(L, 3) != 0;
	} else {
		deferInitCollision = false;
	}
	CollisionScene *inst = new CollisionScene(size, virtualScene, deferInitCollision);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics3D.CollisionScene");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics3D_CollisionScene_initCollisionScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 size = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->initCollisionScene(size);
	return 0;
}

static int Physics3D_CollisionScene_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Physics3D_CollisionScene_removeEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeEntity(entity);
	return 0;
}

static int Physics3D_CollisionScene_getCollisionEntityByObject(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	btCollisionObject* collisionObject = (btCollisionObject*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getCollisionEntityByObject(collisionObject);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_CollisionScene_getFirstEntityInRay(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 origin = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 dest = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	RayTestResult *retInst = new RayTestResult();
	*retInst = inst->getFirstEntityInRay(origin, dest);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Physics3D.RayTestResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Physics3D_CollisionScene_enableCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 3) != 0;
	inst->enableCollision(entity, val);
	return 0;
}

static int Physics3D_CollisionScene_getCollisionByScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* ent = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getCollisionByScreenEntity(ent);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_CollisionScene_testCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* ent1 = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	SceneEntity* ent2 = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 3));
	CollisionResult *retInst = new CollisionResult();
	*retInst = inst->testCollision(ent1, ent2);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Physics3D.CollisionResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Physics3D_CollisionScene_testCollisionOnCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	CollisionSceneEntity* cEnt1 = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	CollisionSceneEntity* cEnt2 = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 3));
	CollisionResult *retInst = new CollisionResult();
	*retInst = inst->testCollisionOnCollisionChild(cEnt1, cEnt2);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Physics3D.CollisionResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Physics3D_CollisionScene_testCollisionOnCollisionChild_Convex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	CollisionSceneEntity* cEnt1 = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	CollisionSceneEntity* cEnt2 = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 3));
	CollisionResult *retInst = new CollisionResult();
	*retInst = inst->testCollisionOnCollisionChild_Convex(cEnt1, cEnt2);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Physics3D.CollisionResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Physics3D_CollisionScene_addCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* newEntity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	int type;
	if(lua_isnumber(L, 3)) {
		type = lua_tointeger(L, 3);
	} else {
		type = 0;
	}
	int group;
	if(lua_isnumber(L, 4)) {
		group = lua_tointeger(L, 4);
	} else {
		group = 1;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->addCollisionChild(newEntity, type, group);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_CollisionScene_trackCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* newEntity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	int type;
	if(lua_isnumber(L, 3)) {
		type = lua_tointeger(L, 3);
	} else {
		type = 0;
	}
	int group;
	if(lua_isnumber(L, 4)) {
		group = lua_tointeger(L, 4);
	} else {
		group = 1;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->trackCollision(newEntity, type, group);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_CollisionScene_removeCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeCollision(entity);
	return 0;
}

static int Physics3D_CollisionScene_adjustForCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionScene *inst = (CollisionScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	CollisionSceneEntity* collisionEntity = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->adjustForCollision(collisionEntity);
	return 0;
}

static int Physics3D_delete_CollisionScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((CollisionScene*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics3D_CollisionSceneEntity_get_collisionObject(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->collisionObject;
	return 1;
}

static int Physics3D_CollisionSceneEntity_get_lastPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->lastPosition;
	return 1;
}

static int Physics3D_CollisionSceneEntity_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Physics3D_CollisionSceneEntity_get_shape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->shape;
	return 1;
}

static int Physics3D_CollisionSceneEntity_set_lastPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->lastPosition = *argInst;
	return 0;
}

static int Physics3D_CollisionSceneEntity_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

static int Physics3D_CollisionSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int type = lua_tointeger(L, 2);
	bool compoundChildren;
	if(lua_isboolean(L, 3)) {
		compoundChildren = lua_toboolean(L, 3) != 0;
	} else {
		compoundChildren = false;
	}
	CollisionSceneEntity *inst = new CollisionSceneEntity(entity, type, compoundChildren);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics3D.CollisionSceneEntity");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics3D_CollisionSceneEntity_getSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSceneEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_CollisionSceneEntity_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Physics3D_CollisionSceneEntity_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Physics3D_CollisionSceneEntity_getConvexShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getConvexShape();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_CollisionSceneEntity_createCollisionShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int type = lua_tointeger(L, 3);
	PolyBase *ptrRetVal = (PolyBase*)inst->createCollisionShape(entity, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_delete_CollisionSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((CollisionSceneEntity*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics3D_PhysicsScene_get_pausePhysics(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->pausePhysics);
	return 1;
}

static int Physics3D_PhysicsScene_set_pausePhysics(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->pausePhysics = param;
	return 0;
}

static int Physics3D_PhysicsScene(lua_State *L) {
	int maxSubSteps;
	if(lua_isnumber(L, 1)) {
		maxSubSteps = lua_tointeger(L, 1);
	} else {
		maxSubSteps = 0;
	}
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 size = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	bool virtualScene;
	if(lua_isboolean(L, 3)) {
		virtualScene = lua_toboolean(L, 3) != 0;
	} else {
		virtualScene = false;
	}
	PhysicsScene *inst = new PhysicsScene(maxSubSteps, size, virtualScene);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics3D.PhysicsScene");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics3D_PhysicsScene_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Physics3D_PhysicsScene_removeEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeEntity(entity);
	return 0;
}

static int Physics3D_PhysicsScene_processWorldCollisions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	inst->processWorldCollisions();
	return 0;
}

static int Physics3D_PhysicsScene_getPhysicsEntityByCollisionObject(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	btCollisionObject* object = (btCollisionObject*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getPhysicsEntityByCollisionObject(object);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_removePhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removePhysicsChild(entity);
	return 0;
}

static int Physics3D_PhysicsScene_getPhysicsEntityBySceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getPhysicsEntityBySceneEntity(entity);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_addPhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* newEntity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	int type;
	if(lua_isnumber(L, 3)) {
		type = lua_tointeger(L, 3);
	} else {
		type = 0;
	}
	Number mass;
	if(lua_isnumber(L, 4)) {
		mass = lua_tonumber(L, 4);
	} else {
		mass = 0.0f;
	}
	Number friction;
	if(lua_isnumber(L, 5)) {
		friction = lua_tonumber(L, 5);
	} else {
		friction = 1;
	}
	Number restitution;
	if(lua_isnumber(L, 6)) {
		restitution = lua_tonumber(L, 6);
	} else {
		restitution = 0;
	}
	int group;
	if(lua_isnumber(L, 7)) {
		group = lua_tointeger(L, 7);
	} else {
		group = 1;
	}
	bool compoundChildren;
	if(lua_isboolean(L, 8)) {
		compoundChildren = lua_toboolean(L, 8) != 0;
	} else {
		compoundChildren = false;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->addPhysicsChild(newEntity, type, mass, friction, restitution, group, compoundChildren);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_trackPhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* newEntity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	int type;
	if(lua_isnumber(L, 3)) {
		type = lua_tointeger(L, 3);
	} else {
		type = 0;
	}
	Number mass;
	if(lua_isnumber(L, 4)) {
		mass = lua_tonumber(L, 4);
	} else {
		mass = 0.0f;
	}
	Number friction;
	if(lua_isnumber(L, 5)) {
		friction = lua_tonumber(L, 5);
	} else {
		friction = 1;
	}
	Number restitution;
	if(lua_isnumber(L, 6)) {
		restitution = lua_tonumber(L, 6);
	} else {
		restitution = 0;
	}
	int group;
	if(lua_isnumber(L, 7)) {
		group = lua_tointeger(L, 7);
	} else {
		group = 1;
	}
	bool compoundChildren;
	if(lua_isboolean(L, 8)) {
		compoundChildren = lua_toboolean(L, 8) != 0;
	} else {
		compoundChildren = false;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->trackPhysicsChild(newEntity, type, mass, friction, restitution, group, compoundChildren);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_addCharacterChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* newEntity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number stepSize = lua_tonumber(L, 5);
	int group;
	if(lua_isnumber(L, 6)) {
		group = lua_tointeger(L, 6);
	} else {
		group = 1;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->addCharacterChild(newEntity, mass, friction, stepSize, group);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_removeCharacterChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	PhysicsCharacter* character = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeCharacterChild(character);
	return 0;
}

static int Physics3D_PhysicsScene_createHingeConstraint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 pivot = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Vector3 axis = *(Vector3*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number minLimit = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number maxLimit = lua_tonumber(L, 6);
	PolyBase *ptrRetVal = (PolyBase*)inst->createHingeConstraint(entity, pivot, axis, minLimit, maxLimit);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_createHingeJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity1 = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	SceneEntity* entity2 = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Vector3 pivot1 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Vector3 axis1 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 5));
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Vector3 pivot2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 6));
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Vector3 axis2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 7));
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number minLimit = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TNUMBER);
	Number maxLimit = lua_tonumber(L, 9);
	PolyBase *ptrRetVal = (PolyBase*)inst->createHingeJoint(entity1, entity2, pivot1, axis1, pivot2, axis2, minLimit, maxLimit);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_createGenericConstraint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->createGenericConstraint(entity);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_setVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 velocity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->setVelocity(entity, velocity);
	return 0;
}

static int Physics3D_PhysicsScene_setSpin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 spin = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->setSpin(entity, spin);
	return 0;
}

static int Physics3D_PhysicsScene_warpEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	bool resetRotation;
	if(lua_isboolean(L, 4)) {
		resetRotation = lua_toboolean(L, 4) != 0;
	} else {
		resetRotation = false;
	}
	inst->warpEntity(entity, position, resetRotation);
	return 0;
}

static int Physics3D_PhysicsScene_removeConstraint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	PhysicsHingeConstraint* constraint = (PhysicsHingeConstraint*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeConstraint(constraint);
	return 0;
}

static int Physics3D_PhysicsScene_applyImpulse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 force = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Vector3 point = *(Vector3*) *((PolyBase**)lua_touserdata(L, 4));
	inst->applyImpulse(entity, force, point);
	return 0;
}

static int Physics3D_PhysicsScene_addVehicleChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* newEntity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 4);
	int group;
	if(lua_isnumber(L, 5)) {
		group = lua_tointeger(L, 5);
	} else {
		group = 1;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->addVehicleChild(newEntity, mass, friction, group);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsScene_setGravity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 gravity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setGravity(gravity);
	return 0;
}

static int Physics3D_PhysicsScene_wakeUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsScene *inst = (PhysicsScene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->wakeUp(entity);
	return 0;
}

static int Physics3D_delete_PhysicsScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsScene*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics3D_PhysicsHingeConstraint_get_btConstraint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsHingeConstraint *inst = (PhysicsHingeConstraint*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->btConstraint;
	return 1;
}

static int Physics3D_PhysicsHingeConstraint(lua_State *L) {
	PhysicsHingeConstraint *inst = new PhysicsHingeConstraint();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics3D.PhysicsHingeConstraint");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics3D_PhysicsHingeConstraint_setLimits(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsHingeConstraint *inst = (PhysicsHingeConstraint*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number minLimit = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number maxLimit = lua_tonumber(L, 3);
	inst->setLimits(minLimit, maxLimit);
	return 0;
}

static int Physics3D_PhysicsHingeConstraint_getAngle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsHingeConstraint *inst = (PhysicsHingeConstraint*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getAngle());
	return 1;
}

static int Physics3D_delete_PhysicsHingeConstraint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsHingeConstraint*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics3D_PhysicsSceneEvent_get_entityA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->entityA;
	return 1;
}

static int Physics3D_PhysicsSceneEvent_get_entityB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->entityB;
	return 1;
}

static int Physics3D_PhysicsSceneEvent_get_appliedImpulse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->appliedImpulse);
	return 1;
}

static int Physics3D_PhysicsSceneEvent_get_positionOnA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->positionOnA;
	return 1;
}

static int Physics3D_PhysicsSceneEvent_get_positionOnB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->positionOnB;
	return 1;
}

static int Physics3D_PhysicsSceneEvent_get_worldNormalOnB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->worldNormalOnB;
	return 1;
}

static int Physics3D_PhysicsSceneEvent_set_appliedImpulse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->appliedImpulse = param;
	return 0;
}

static int Physics3D_PhysicsSceneEvent_set_positionOnA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->positionOnA = *argInst;
	return 0;
}

static int Physics3D_PhysicsSceneEvent_set_positionOnB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->positionOnB = *argInst;
	return 0;
}

static int Physics3D_PhysicsSceneEvent_set_worldNormalOnB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEvent *inst = (PhysicsSceneEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->worldNormalOnB = *argInst;
	return 0;
}

static int Physics3D_PhysicsSceneEvent(lua_State *L) {
	PhysicsSceneEvent *inst = new PhysicsSceneEvent();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics3D.PhysicsSceneEvent");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics3D_delete_PhysicsSceneEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsSceneEvent*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics3D_PhysicsGenericConstraint_get_btConstraint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsGenericConstraint *inst = (PhysicsGenericConstraint*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->btConstraint;
	return 1;
}

static int Physics3D_PhysicsGenericConstraint_setLinearLowerLimit(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsGenericConstraint *inst = (PhysicsGenericConstraint*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 limit = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setLinearLowerLimit(limit);
	return 0;
}

static int Physics3D_PhysicsGenericConstraint_setLinearUpperLimit(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsGenericConstraint *inst = (PhysicsGenericConstraint*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 limit = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setLinearUpperLimit(limit);
	return 0;
}

static int Physics3D_PhysicsGenericConstraint_setAngularLowerLimit(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsGenericConstraint *inst = (PhysicsGenericConstraint*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 limit = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setAngularLowerLimit(limit);
	return 0;
}

static int Physics3D_PhysicsGenericConstraint_setAngularUpperLimit(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsGenericConstraint *inst = (PhysicsGenericConstraint*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 limit = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setAngularUpperLimit(limit);
	return 0;
}

static int Physics3D_delete_PhysicsGenericConstraint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsGenericConstraint*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics3D_PhysicsSceneEntity_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Physics3D_PhysicsSceneEntity_get_rigidBody(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->rigidBody;
	return 1;
}

static int Physics3D_PhysicsSceneEntity_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

static int Physics3D_PhysicsSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int type = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number restitution = lua_tonumber(L, 5);
	bool compoundChildren;
	if(lua_isboolean(L, 6)) {
		compoundChildren = lua_toboolean(L, 6) != 0;
	} else {
		compoundChildren = false;
	}
	PhysicsSceneEntity *inst = new PhysicsSceneEntity(entity, type, mass, friction, restitution, compoundChildren);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics3D.PhysicsSceneEntity");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics3D_PhysicsSceneEntity_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Physics3D_PhysicsSceneEntity_getSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSceneEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Physics3D_PhysicsSceneEntity_setFriction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 2);
	inst->setFriction(friction);
	return 0;
}

static int Physics3D_PhysicsSceneEntity_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Physics3D_PhysicsSceneEntity_setSpin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 spin = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setSpin(spin);
	return 0;
}

static int Physics3D_PhysicsSceneEntity_setMass(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 2);
	inst->setMass(mass);
	return 0;
}

static int Physics3D_PhysicsSceneEntity_getVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getVelocity();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Physics3D.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Physics3D_PhysicsSceneEntity_getSpin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getSpin();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Physics3D.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Physics3D_PhysicsSceneEntity_setRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion quat = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setRotation(quat);
	return 0;
}

static int Physics3D_PhysicsSceneEntity_setVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 velocity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setVelocity(velocity);
	return 0;
}

static int Physics3D_PhysicsSceneEntity_warpTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool resetRotation = lua_toboolean(L, 3) != 0;
	inst->warpTo(position, resetRotation);
	return 0;
}

static int Physics3D_PhysicsSceneEntity_applyImpulse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 point = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->applyImpulse(direction, point);
	return 0;
}

static int Physics3D_delete_PhysicsSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsSceneEntity*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics3D_PhysicsCharacter_get_character(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->character;
	return 1;
}

static int Physics3D_PhysicsCharacter_get_ghostObject(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->ghostObject;
	return 1;
}

static int Physics3D_PhysicsCharacter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number stepSize = lua_tonumber(L, 4);
	PhysicsCharacter *inst = new PhysicsCharacter(entity, mass, friction, stepSize);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics3D.PhysicsCharacter");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics3D_PhysicsCharacter_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Physics3D_PhysicsCharacter_setWalkDirection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setWalkDirection(direction);
	return 0;
}

static int Physics3D_PhysicsCharacter_jump(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->jump();
	return 0;
}

static int Physics3D_PhysicsCharacter_warpCharacter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->warpCharacter(position);
	return 0;
}

static int Physics3D_PhysicsCharacter_setJumpSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number jumpSpeed = lua_tonumber(L, 2);
	inst->setJumpSpeed(jumpSpeed);
	return 0;
}

static int Physics3D_PhysicsCharacter_setFallSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fallSpeed = lua_tonumber(L, 2);
	inst->setFallSpeed(fallSpeed);
	return 0;
}

static int Physics3D_PhysicsCharacter_setMaxJumpHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number maxJumpHeight = lua_tonumber(L, 2);
	inst->setMaxJumpHeight(maxJumpHeight);
	return 0;
}

static int Physics3D_PhysicsCharacter_onGround(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->onGround());
	return 1;
}

static int Physics3D_delete_PhysicsCharacter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsCharacter*) *inst);
	*inst = NULL;
	return 0;
}

static int Physics3D_PhysicsVehicle_get_tuning(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->tuning;
	return 1;
}

static int Physics3D_PhysicsVehicle_get_rayCaster(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->rayCaster;
	return 1;
}

static int Physics3D_PhysicsVehicle_get_vehicle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->vehicle;
	return 1;
}

static int Physics3D_PhysicsVehicle_set_tuning(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	btRaycastVehicle::btVehicleTuning *argInst = (btRaycastVehicle::btVehicleTuning*) *((PolyBase**)lua_touserdata(L, 2));
	inst->tuning = *argInst;
	return 0;
}

static int Physics3D_PhysicsVehicle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TUSERDATA);
	btDefaultVehicleRaycaster* rayCaster = (btDefaultVehicleRaycaster*) *((PolyBase**)lua_touserdata(L, 4));
	PhysicsVehicle *inst = new PhysicsVehicle(entity, mass, friction, rayCaster);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Physics3D.PhysicsVehicle");
	lua_setmetatable(L, -2);
	return 1;
}

static int Physics3D_PhysicsVehicle_addWheel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 connection = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Vector3 axle = *(Vector3*) *((PolyBase**)lua_touserdata(L, 5));
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number suspentionRestLength = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number wheelRadius = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TBOOLEAN);
	bool isFrontWheel = lua_toboolean(L, 8) != 0;
	Number suspensionStiffness;
	if(lua_isnumber(L, 9)) {
		suspensionStiffness = lua_tonumber(L, 9);
	} else {
		suspensionStiffness = 20.0f;
	}
	Number suspensionDamping;
	if(lua_isnumber(L, 10)) {
		suspensionDamping = lua_tonumber(L, 10);
	} else {
		suspensionDamping = 1.0f;
	}
	Number suspensionCompression;
	if(lua_isnumber(L, 11)) {
		suspensionCompression = lua_tonumber(L, 11);
	} else {
		suspensionCompression = 4.0f;
	}
	Number wheelFriction;
	if(lua_isnumber(L, 12)) {
		wheelFriction = lua_tonumber(L, 12);
	} else {
		wheelFriction = 10000.0f;
	}
	Number rollInfluence;
	if(lua_isnumber(L, 13)) {
		rollInfluence = lua_tonumber(L, 13);
	} else {
		rollInfluence = 0.5f;
	}
	inst->addWheel(entity, connection, direction, axle, suspentionRestLength, wheelRadius, isFrontWheel, suspensionStiffness, suspensionDamping, suspensionCompression, wheelFriction, rollInfluence);
	return 0;
}

static int Physics3D_PhysicsVehicle_applyEngineForce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number force = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int wheelIndex = lua_tointeger(L, 3);
	inst->applyEngineForce(force, wheelIndex);
	return 0;
}

static int Physics3D_PhysicsVehicle_setSteeringValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number value = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int wheelIndex = lua_tointeger(L, 3);
	inst->setSteeringValue(value, wheelIndex);
	return 0;
}

static int Physics3D_PhysicsVehicle_setBrake(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number value = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int wheelIndex = lua_tointeger(L, 3);
	inst->setBrake(value, wheelIndex);
	return 0;
}

static int Physics3D_PhysicsVehicle_warpVehicle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->warpVehicle(position);
	return 0;
}

static int Physics3D_PhysicsVehicle_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Physics3D_delete_PhysicsVehicle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PhysicsVehicle*) *inst);
	*inst = NULL;
	return 0;
}

} // namespace Polycode
