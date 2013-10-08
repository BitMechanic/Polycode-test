#pragma once

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
} // extern "C" 

#include "PolyBezierCurve.h"
#include "PolyBone.h"
#include "PolyCamera.h"
#include "Polycode.h"
#include "PolyColor.h"
#include "PolyConfig.h"
#include "PolyCore.h"
#include "PolyCoreInput.h"
#include "PolyCoreServices.h"
#include "PolyCubemap.h"
#include "PolyData.h"
#include "PolyEntity.h"
#include "PolyEvent.h"
#include "PolyEventDispatcher.h"
#include "PolyEventHandler.h"
#include "PolyFixedShader.h"
#include "PolyFont.h"
#include "PolyFontManager.h"
#include "PolyGLCubemap.h"
#include "PolyGlobals.h"
#include "PolyImage.h"
#include "PolyInputEvent.h"
#include "PolyInputKeys.h"
#include "PolyLabel.h"
#include "PolyMaterial.h"
#include "PolyMaterialManager.h"
#include "PolyMatrix4.h"
#include "PolyMesh.h"
#include "PolyModule.h"
#include "PolyObject.h"
#include "PolyParticle.h"
#include "PolyParticleEmitter.h"
#include "PolyPerlin.h"
#include "PolyPolygon.h"
#include "PolyQuaternion.h"
#include "PolyQuaternionCurve.h"
#include "PolyRectangle.h"
#include "PolyRenderer.h"
#include "PolyResource.h"
#include "PolyResourceManager.h"
#include "PolyScene.h"
#include "PolySceneEntity.h"
#include "PolySceneLabel.h"
#include "PolySceneLight.h"
#include "PolySceneLine.h"
#include "PolySceneManager.h"
#include "PolySceneMesh.h"
#include "PolyScenePrimitive.h"
#include "PolySceneRenderTexture.h"
#include "PolySceneSound.h"
#include "PolyScreen.h"
#include "PolyScreenEntity.h"
#include "PolyScreenEntityInstance.h"
#include "PolyScreenEvent.h"
#include "PolyScreenImage.h"
#include "PolyScreenLabel.h"
#include "PolyScreenLine.h"
#include "PolyScreenManager.h"
#include "PolyScreenMesh.h"
#include "PolyScreenShape.h"
#include "PolyScreenSound.h"
#include "PolyScreenSprite.h"
#include "PolyShader.h"
#include "PolySkeleton.h"
#include "PolySound.h"
#include "PolySoundManager.h"
#include "PolyString.h"
#include "PolyTexture.h"
#include "PolyTimer.h"
#include "PolyTimerManager.h"
#include "PolyVector2.h"
#include "PolyVector3.h"
#include "PolyVertex.h"

using namespace std;


namespace Polycode {

class LuaEventHandler : public EventHandler {
public:
	LuaEventHandler() : EventHandler() {}
	void handleEvent(Event *e) {
		lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
		int errH = lua_gettop(L);
		lua_getfield(L, LUA_GLOBALSINDEX, "__handleEvent");
		lua_rawgeti( L, LUA_REGISTRYINDEX, wrapperIndex );
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)e;
		lua_pcall(L, 2, 0, errH);
		lua_settop(L, 0);
	}
	int wrapperIndex;
	lua_State *L;
};

static int Polycore_BezierCurve_get_insertPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->insertPoint;
	return 1;
}

static int Polycore_BezierCurve(lua_State *L) {
	BezierCurve *inst = new BezierCurve();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.BezierCurve");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_BezierCurve_getControlPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getControlPoint(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_BezierCurve_getNumControlPoints(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumControlPoints());
	return 1;
}

static int Polycore_BezierCurve_addControlPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number p1x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number p1y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number p1z = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number p2x = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number p2y = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number p2z = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number p3x = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TNUMBER);
	Number p3y = lua_tonumber(L, 9);
	luaL_checktype(L, 10, LUA_TNUMBER);
	Number p3z = lua_tonumber(L, 10);
	inst->addControlPoint(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);
	return 0;
}

static int Polycore_BezierCurve_addControlPoint3dWithHandles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number p1x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number p1y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number p1z = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number p2x = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number p2y = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number p2z = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number p3x = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TNUMBER);
	Number p3y = lua_tonumber(L, 9);
	luaL_checktype(L, 10, LUA_TNUMBER);
	Number p3z = lua_tonumber(L, 10);
	inst->addControlPoint3dWithHandles(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);
	return 0;
}

static int Polycore_BezierCurve_addControlPoint3d(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->addControlPoint3d(x, y, z);
	return 0;
}

static int Polycore_BezierCurve_addControlPoint2dWithHandles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number p1x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number p1y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number p2x = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number p2y = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number p3x = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number p3y = lua_tonumber(L, 7);
	inst->addControlPoint2dWithHandles(p1x, p1y, p2x, p2y, p3x, p3y);
	return 0;
}

static int Polycore_BezierCurve_addControlPoint2d(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->addControlPoint2d(x, y);
	return 0;
}

static int Polycore_BezierCurve_getHeightAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number a = lua_tonumber(L, 2);
	lua_pushnumber(L, inst->getHeightAt(a));
	return 1;
}

static int Polycore_BezierCurve_getPointAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number a = lua_tonumber(L, 2);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getPointAt(a);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_BezierCurve_getPointBetween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number a = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	BezierPoint* bp1 = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	BezierPoint* bp2 = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 4));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getPointBetween(a, bp1, bp2);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_BezierCurve_clearControlPoints(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearControlPoints();
	return 0;
}

static int Polycore_BezierCurve_rebuildBuffers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	inst->rebuildBuffers();
	return 0;
}

static int Polycore_BezierCurve_removePoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierPoint* point = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removePoint(point);
	return 0;
}

static int Polycore_BezierCurve_recalculateDistances(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	inst->recalculateDistances();
	return 0;
}

static int Polycore_delete_BezierCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((BezierCurve*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Bone_get_parentBoneId(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->parentBoneId);
	return 1;
}

static int Polycore_Bone_get_boneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->boneMatrix;
	return 1;
}

static int Polycore_Bone_get_restMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->restMatrix;
	return 1;
}

static int Polycore_Bone_get_baseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->baseMatrix;
	return 1;
}

static int Polycore_Bone_set_parentBoneId(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->parentBoneId = param;
	return 0;
}

static int Polycore_Bone_set_boneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->boneMatrix = *argInst;
	return 0;
}

static int Polycore_Bone_set_restMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->restMatrix = *argInst;
	return 0;
}

static int Polycore_Bone_set_baseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->baseMatrix = *argInst;
	return 0;
}

static int Polycore_Bone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String boneName = String(lua_tostring(L, 1));
	Bone *inst = new Bone(boneName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Bone");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Bone_enableBoneLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String labelFont = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number size = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number scale = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Color labelColor = *(Color*) *((PolyBase**)lua_touserdata(L, 5));
	inst->enableBoneLabel(labelFont, size, scale, labelColor);
	return 0;
}

static int Polycore_Bone_getName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getName();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Bone_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_Bone_setParentBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setParentBone(bone);
	return 0;
}

static int Polycore_Bone_addChildBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addChildBone(bone);
	return 0;
}

static int Polycore_Bone_getParentBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getParentBone();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Bone_getNumChildBones(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumChildBones());
	return 1;
}

static int Polycore_Bone_getChildBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getChildBone(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Bone_getBoneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getBoneMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Bone_setBoneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setBoneMatrix(matrix);
	return 0;
}

static int Polycore_Bone_getRestMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getRestMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Bone_getFullRestMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getFullRestMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Bone_getParentRestMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getParentRestMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Bone_getFinalMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getFinalMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Bone_setRestMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setRestMatrix(matrix);
	return 0;
}

static int Polycore_Bone_setBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setBaseMatrix(matrix);
	return 0;
}

static int Polycore_Bone_getBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	 Matrix4  *retInst = new  Matrix4 ();
	*retInst = inst->getBaseMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Matrix4 ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Bone_getFullBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getFullBaseMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_delete_Bone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Bone*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Camera_get_frustumCulling(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->frustumCulling);
	return 1;
}

static int Polycore_Camera_get_cameraShift(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->cameraShift;
	return 1;
}

static int Polycore_Camera_set_frustumCulling(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->frustumCulling = param;
	return 0;
}

static int Polycore_Camera_set_cameraShift(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->cameraShift = *argInst;
	return 0;
}

static int Polycore_Camera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene* parentScene = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	Camera *inst = new Camera(parentScene);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Camera");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Camera_buildFrustumPlanes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	inst->buildFrustumPlanes();
	return 0;
}

static int Polycore_Camera_isSphereInFrustum(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 pos = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fRadius = lua_tonumber(L, 3);
	lua_pushboolean(L, inst->isSphereInFrustum(pos, fRadius));
	return 1;
}

static int Polycore_Camera_canSee(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushboolean(L, inst->canSee(entity));
	return 1;
}

static int Polycore_Camera_setOrthoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool mode = lua_toboolean(L, 2) != 0;
	Number orthoSizeX;
	if(lua_isnumber(L, 3)) {
		orthoSizeX = lua_tonumber(L, 3);
	} else {
		orthoSizeX = 1.0;
	}
	Number orthoSizeY;
	if(lua_isnumber(L, 4)) {
		orthoSizeY = lua_tonumber(L, 4);
	} else {
		orthoSizeY = 1.0;
	}
	inst->setOrthoMode(mode, orthoSizeX, orthoSizeY);
	return 0;
}

static int Polycore_Camera_getOrthoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->getOrthoMode());
	return 1;
}

static int Polycore_Camera_getOrthoSizeX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getOrthoSizeX());
	return 1;
}

static int Polycore_Camera_getOrthoSizeY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getOrthoSizeY());
	return 1;
}

static int Polycore_Camera_setFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fov = lua_tonumber(L, 2);
	inst->setFOV(fov);
	return 0;
}

static int Polycore_Camera_getFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getFOV());
	return 1;
}

static int Polycore_Camera_setParentScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Scene* parentScene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setParentScene(parentScene);
	return 0;
}

static int Polycore_Camera_doCameraTransform(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	inst->doCameraTransform();
	return 0;
}

static int Polycore_Camera_setLightDepthTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setLightDepthTexture(texture);
	return 0;
}

static int Polycore_Camera_hasFilterShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->hasFilterShader());
	return 1;
}

static int Polycore_Camera_drawFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	Texture* targetTexture;
	if(lua_isuserdata(L, 2)) {
		targetTexture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	} else {
		targetTexture = NULL;
	}
	Number targetTextureWidth;
	if(lua_isnumber(L, 3)) {
		targetTextureWidth = lua_tonumber(L, 3);
	} else {
		targetTextureWidth = 0.0;
	}
	Number targetTextureHeight;
	if(lua_isnumber(L, 4)) {
		targetTextureHeight = lua_tonumber(L, 4);
	} else {
		targetTextureHeight = 0.0;
	}
	Texture* targetColorTexture;
	if(lua_isuserdata(L, 5)) {
		targetColorTexture = (Texture*) *((PolyBase**)lua_touserdata(L, 5));
	} else {
		targetColorTexture = NULL;
	}
	Texture* targetZTexture;
	if(lua_isuserdata(L, 6)) {
		targetZTexture = (Texture*) *((PolyBase**)lua_touserdata(L, 6));
	} else {
		targetZTexture = NULL;
	}
	inst->drawFilter(targetTexture, targetTextureWidth, targetTextureHeight, targetColorTexture, targetZTexture);
	return 0;
}

static int Polycore_Camera_getProjectionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getProjectionMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Camera_setExposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number level = lua_tonumber(L, 2);
	inst->setExposureLevel(level);
	return 0;
}

static int Polycore_Camera_getExposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getExposureLevel());
	return 1;
}

static int Polycore_Camera_setPostFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Material* shaderMaterial = (Material*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setPostFilter(shaderMaterial);
	return 0;
}

static int Polycore_Camera_setPostFilterByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String shaderName = String(lua_tostring(L, 2));
	inst->setPostFilterByName(shaderName);
	return 0;
}

static int Polycore_Camera_removePostFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	inst->removePostFilter();
	return 0;
}

static int Polycore_Camera_getLocalShaderOptions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	std::vector<ShaderBinding*> retVector = inst->getLocalShaderOptions();
	lua_newtable(L);
	for(int i=0; i < retVector.size(); i++) {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)retVector[i];
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static int Polycore_Camera_getScreenShaderMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getScreenShaderMaterial();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_Camera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Camera*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Color_get_r(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->r);
	return 1;
}

static int Polycore_Color_get_g(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->g);
	return 1;
}

static int Polycore_Color_get_b(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->b);
	return 1;
}

static int Polycore_Color_get_a(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->a);
	return 1;
}

static int Polycore_Color_set_r(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->r = param;
	return 0;
}

static int Polycore_Color_set_g(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->g = param;
	return 0;
}

static int Polycore_Color_set_b(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->b = param;
	return 0;
}

static int Polycore_Color_set_a(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->a = param;
	return 0;
}

static int Polycore_Color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number r = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number g = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number b = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number a = lua_tonumber(L, 4);
	Color *inst = new Color(r, g, b, a);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Color");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Color_ColorWithInts(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int r = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int g = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int b = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int a = lua_tointeger(L, 4);
	 Color *retInst = new  Color();
	*retInst = Color::ColorWithInts(r, g, b, a);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Color_ColorWithHex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int hex = lua_tointeger(L, 1);
	 Color *retInst = new  Color();
	*retInst = Color::ColorWithHex(hex);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Color_setColorHex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int hex = lua_tointeger(L, 2);
	inst->setColorHex(hex);
	return 0;
}

static int Polycore_Color_setColorHexRGB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int hex = lua_tointeger(L, 2);
	inst->setColorHexRGB(hex);
	return 0;
}

static int Polycore_Color_setColorHexFromString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String hex = String(lua_tostring(L, 2));
	inst->setColorHexFromString(hex);
	return 0;
}

static int Polycore_Color_setColorHexRGBFromString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String hex = String(lua_tostring(L, 2));
	inst->setColorHexRGBFromString(hex);
	return 0;
}

static int Polycore_Color_setColorHSV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number h = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number s = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number v = lua_tonumber(L, 4);
	inst->setColorHSV(h, s, v);
	return 0;
}

static int Polycore_Color_setColorRGBA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int r = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int g = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int b = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int a = lua_tointeger(L, 5);
	inst->setColorRGBA(r, g, b, a);
	return 0;
}

static int Polycore_Color_setColorRGB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int r = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int g = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int b = lua_tointeger(L, 4);
	inst->setColorRGB(r, g, b);
	return 0;
}

static int Polycore_Color_setColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a = lua_tonumber(L, 5);
	inst->setColor(r, g, b, a);
	return 0;
}

static int Polycore_Color_blendColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color c2 = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int mode = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number amount = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Color c3 = *(Color*) *((PolyBase**)lua_touserdata(L, 5));
	Color *retInst = new Color();
	*retInst = inst->blendColor(c2, mode, amount, c3);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Color_Random(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Random();
	return 0;
}

static int Polycore_Color_getBrightness(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getBrightness());
	return 1;
}

static int Polycore_Color_RGBtoHSV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number r = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number g = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number b = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number h = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number s = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number v = lua_tonumber(L, 6);
	Color::RGBtoHSV(r, g, b, h, s, v);
	return 0;
}

static int Polycore_Color_getHue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getHue());
	return 1;
}

static int Polycore_Color_getSaturation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getSaturation());
	return 1;
}

static int Polycore_Color_getValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getValue());
	return 1;
}

static int Polycore_Color_getUint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getUint());
	return 1;
}

static int Polycore_delete_Color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Color*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Config(lua_State *L) {
	Config *inst = new Config();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Config");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Config_loadConfig(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 3));
	inst->loadConfig(configNamespace, fileName);
	return 0;
}

static int Polycore_Config_saveConfig(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 3));
	inst->saveConfig(configNamespace, fileName);
	return 0;
}

static int Polycore_Config_getEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	PolyBase *ptrRetVal = (PolyBase*)inst->getEntry(configNamespace, key);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Config_setStringValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TSTRING);
	String value = String(lua_tostring(L, 4));
	inst->setStringValue(configNamespace, key, value);
	return 0;
}

static int Polycore_Config_setNumericValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number value = lua_tonumber(L, 4);
	inst->setNumericValue(configNamespace, key, value);
	return 0;
}

static int Polycore_Config_getNumericValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	lua_pushnumber(L, inst->getNumericValue(configNamespace, key));
	return 1;
}

static int Polycore_Config_getStringValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	 String  *retInst = new  String ();
	*retInst = inst->getStringValue(configNamespace, key);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_delete_Config(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Config*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_PolycodeViewBase_get_windowData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolycodeViewBase *inst = (PolycodeViewBase*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->windowData;
	return 1;
}

static int Polycore_PolycodeViewBase(lua_State *L) {
	PolycodeViewBase *inst = new PolycodeViewBase();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.PolycodeViewBase");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_delete_PolycodeViewBase(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PolycodeViewBase*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Core_get_eventMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->eventMutex;
	return 1;
}

static int Polycore_Core_get_paused(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->paused);
	return 1;
}

static int Polycore_Core_get_pauseOnLoseFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->pauseOnLoseFocus);
	return 1;
}

static int Polycore_Core_get_defaultScreenWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->defaultScreenWidth);
	return 1;
}

static int Polycore_Core_get_defaultScreenHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->defaultScreenHeight);
	return 1;
}

static int Polycore_Core_set_paused(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->paused = param;
	return 0;
}

static int Polycore_Core_set_pauseOnLoseFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->pauseOnLoseFocus = param;
	return 0;
}

static int Polycore_Core_set_defaultScreenWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->defaultScreenWidth = param;
	return 0;
}

static int Polycore_Core_set_defaultScreenHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->defaultScreenHeight = param;
	return 0;
}

static int Polycore_Core_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->Update());
	return 1;
}

static int Polycore_Core_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_Core_updateAndRender(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->updateAndRender());
	return 1;
}

static int Polycore_Core_enableMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool newval = lua_toboolean(L, 2) != 0;
	inst->enableMouse(newval);
	return 0;
}

static int Polycore_Core_captureMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool newval = lua_toboolean(L, 2) != 0;
	inst->captureMouse(newval);
	return 0;
}

static int Polycore_Core_setCursor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int cursorType = lua_tointeger(L, 2);
	inst->setCursor(cursorType);
	return 0;
}

static int Polycore_Core_warpCursor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	inst->warpCursor(x, y);
	return 0;
}

static int Polycore_Core_createThread(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Threaded* target = (Threaded*) *((PolyBase**)lua_touserdata(L, 2));
	inst->createThread(target);
	return 0;
}

static int Polycore_Core_lockMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	CoreMutex* mutex = (CoreMutex*) *((PolyBase**)lua_touserdata(L, 2));
	inst->lockMutex(mutex);
	return 0;
}

static int Polycore_Core_unlockMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	CoreMutex* mutex = (CoreMutex*) *((PolyBase**)lua_touserdata(L, 2));
	inst->unlockMutex(mutex);
	return 0;
}

static int Polycore_Core_createMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->createMutex();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Core_copyStringToClipboard(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	inst->copyStringToClipboard(str);
	return 0;
}

static int Polycore_Core_getClipboardString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getClipboardString().c_str());
	return 1;
}

static int Polycore_Core_getServices(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getServices();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Core_getFPS(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getFPS());
	return 1;
}

static int Polycore_Core_Shutdown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Shutdown();
	return 0;
}

static int Polycore_Core_isFullscreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isFullscreen());
	return 1;
}

static int Polycore_Core_getAALevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getAALevel());
	return 1;
}

static int Polycore_Core_getInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getInput();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Core_getXRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getXRes());
	return 1;
}

static int Polycore_Core_getYRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getYRes());
	return 1;
}

static int Polycore_Core_getScreenInfo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	int* width = (int*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	int* height = (int*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	int* hz = (int*) *((PolyBase**)lua_touserdata(L, 3));
	Core::getScreenInfo(width, height, hz);
	return 0;
}

static int Polycore_Core_createFolder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String folderPath = String(lua_tostring(L, 2));
	inst->createFolder(folderPath);
	return 0;
}

static int Polycore_Core_copyDiskItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String itemPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String destItemPath = String(lua_tostring(L, 3));
	inst->copyDiskItem(itemPath, destItemPath);
	return 0;
}

static int Polycore_Core_moveDiskItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String itemPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String destItemPath = String(lua_tostring(L, 3));
	inst->moveDiskItem(itemPath, destItemPath);
	return 0;
}

static int Polycore_Core_removeDiskItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String itemPath = String(lua_tostring(L, 2));
	inst->removeDiskItem(itemPath);
	return 0;
}

static int Polycore_Core_openFolderPicker(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->openFolderPicker().c_str());
	return 1;
}

static int Polycore_Core_setFramerate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int frameRate = lua_tointeger(L, 2);
	inst->setFramerate(frameRate);
	return 0;
}

static int Polycore_Core_openFilePicker(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool allowMultiple = lua_toboolean(L, 3) != 0;
	return 0;
}

static int Polycore_Core_setVideoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int xRes = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int yRes = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool fullScreen = lua_toboolean(L, 4) != 0;
	luaL_checktype(L, 5, LUA_TBOOLEAN);
	bool vSync = lua_toboolean(L, 5) != 0;
	luaL_checktype(L, 6, LUA_TNUMBER);
	int aaLevel = lua_tointeger(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	int anisotropyLevel = lua_tointeger(L, 7);
	inst->setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel);
	return 0;
}

static int Polycore_Core_resizeTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int xRes = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int yRes = lua_tointeger(L, 3);
	inst->resizeTo(xRes, yRes);
	return 0;
}

static int Polycore_Core_doSleep(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	inst->doSleep();
	return 0;
}

static int Polycore_Core_openURL(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String url = String(lua_tostring(L, 2));
	inst->openURL(url);
	return 0;
}

static int Polycore_Core_getElapsed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getElapsed());
	return 1;
}

static int Polycore_Core_getTicks(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getTicks());
	return 1;
}

static int Polycore_Core_getTicksFloat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getTicksFloat());
	return 1;
}

static int Polycore_Core_setUserPointer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* ptr = (void*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setUserPointer(ptr);
	return 0;
}

static int Polycore_Core_getUserPointer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getUserPointer();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Core_executeExternalCommand(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String command = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String args = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TSTRING);
	String inDirectory = String(lua_tostring(L, 4));
	lua_pushstring(L, inst->executeExternalCommand(command, args, inDirectory).c_str());
	return 1;
}

static int Polycore_Core_getDefaultWorkingDirectory(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getDefaultWorkingDirectory().c_str());
	return 1;
}

static int Polycore_Core_getUserHomeDirectory(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getUserHomeDirectory().c_str());
	return 1;
}

static int Polycore_Core_makeApplicationMain(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	inst->makeApplicationMain();
	return 0;
}

static int Polycore_Core_getEventMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getEventMutex();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Core_removeThread(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Threaded* thread = (Threaded*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeThread(thread);
	return 0;
}

static int Polycore_delete_Core(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Core*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_CoreInput_get_simulateTouchWithMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->simulateTouchWithMouse);
	return 1;
}

static int Polycore_CoreInput_get_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->mousePosition;
	return 1;
}

static int Polycore_CoreInput_get_deltaMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->deltaMousePosition;
	return 1;
}

static int Polycore_CoreInput_set_simulateTouchWithMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->simulateTouchWithMouse = param;
	return 0;
}

static int Polycore_CoreInput_set_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->mousePosition = *argInst;
	return 0;
}

static int Polycore_CoreInput_set_deltaMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->deltaMousePosition = *argInst;
	return 0;
}

static int Polycore_CoreInput(lua_State *L) {
	CoreInput *inst = new CoreInput();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.CoreInput");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_CoreInput_getMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getMousePosition();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_CoreInput_getKeyState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY keyCode = (PolyKEY)lua_tointeger(L, 2);
	lua_pushboolean(L, inst->getKeyState(keyCode));
	return 1;
}

static int Polycore_CoreInput_getJoystickButtonState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int joystickIndex = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int button = lua_tointeger(L, 3);
	lua_pushboolean(L, inst->getJoystickButtonState(joystickIndex, button));
	return 1;
}

static int Polycore_CoreInput_getJoystickAxisValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int joystickIndex = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int axis = lua_tointeger(L, 3);
	lua_pushnumber(L, inst->getJoystickAxisValue(joystickIndex, axis));
	return 1;
}

static int Polycore_CoreInput_getMouseDelta(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getMouseDelta();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_CoreInput_getMouseButtonState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 2);
	lua_pushboolean(L, inst->getMouseButtonState(mouseButton));
	return 1;
}

static int Polycore_CoreInput_getNumJoysticks(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumJoysticks());
	return 1;
}

static int Polycore_CoreInput_getJoystickInfoByIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getJoystickInfoByIndex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreInput_getJoystickInfoByID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int deviceID = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getJoystickInfoByID(deviceID);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreInput_addJoystick(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int deviceID = lua_tointeger(L, 2);
	inst->addJoystick(deviceID);
	return 0;
}

static int Polycore_CoreInput_removeJoystick(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int deviceID = lua_tointeger(L, 2);
	inst->removeJoystick(deviceID);
	return 0;
}

static int Polycore_CoreInput_joystickAxisMoved(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int axisID = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number value = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int deviceID = lua_tointeger(L, 4);
	inst->joystickAxisMoved(axisID, value, deviceID);
	return 0;
}

static int Polycore_CoreInput_joystickButtonDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int buttonID = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int deviceID = lua_tointeger(L, 3);
	inst->joystickButtonDown(buttonID, deviceID);
	return 0;
}

static int Polycore_CoreInput_joystickButtonUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int buttonID = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int deviceID = lua_tointeger(L, 3);
	inst->joystickButtonUp(buttonID, deviceID);
	return 0;
}

static int Polycore_CoreInput_mouseWheelUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 2);
	inst->mouseWheelUp(ticks);
	return 0;
}

static int Polycore_CoreInput_mouseWheelDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 2);
	inst->mouseWheelDown(ticks);
	return 0;
}

static int Polycore_CoreInput_setMouseButtonState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool state = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 4);
	inst->setMouseButtonState(mouseButton, state, ticks);
	return 0;
}

static int Polycore_CoreInput_setMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 4);
	inst->setMousePosition(x, y, ticks);
	return 0;
}

static int Polycore_CoreInput_setKeyState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY keyCode = (PolyKEY)lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	wchar_t code = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool newState = lua_toboolean(L, 4) != 0;
	luaL_checktype(L, 5, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 5);
	inst->setKeyState(keyCode, code, newState, ticks);
	return 0;
}

static int Polycore_CoreInput_setDeltaPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	inst->setDeltaPosition(x, y);
	return 0;
}

static int Polycore_CoreInput_touchesBegan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TouchInfo touch = *(TouchInfo*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	vector<TouchInfo> touches = *(vector<TouchInfo>*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 4);
	inst->touchesBegan(touch, touches, ticks);
	return 0;
}

static int Polycore_CoreInput_touchesMoved(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TouchInfo touch = *(TouchInfo*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	vector<TouchInfo> touches = *(vector<TouchInfo>*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 4);
	inst->touchesMoved(touch, touches, ticks);
	return 0;
}

static int Polycore_CoreInput_touchesEnded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TouchInfo touch = *(TouchInfo*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	vector<TouchInfo> touches = *(vector<TouchInfo>*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 4);
	inst->touchesEnded(touch, touches, ticks);
	return 0;
}

static int Polycore_CoreInput_createEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event* event = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)CoreInput::createEvent(event);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreInput_clearInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearInput();
	return 0;
}

static int Polycore_delete_CoreInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((CoreInput*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_CoreServices_get_focusedChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->focusedChild;
	return 1;
}

static int Polycore_CoreServices_getInstance(lua_State *L) {
	PolyBase *ptrRetVal = (PolyBase*)CoreServices::getInstance();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_setInstance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices* _instance = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	CoreServices::setInstance(_instance);
	return 0;
}

static int Polycore_CoreServices_getRenderMutex(lua_State *L) {
	PolyBase *ptrRetVal = (PolyBase*)CoreServices::getRenderMutex();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_setRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Renderer* r_enderer = (Renderer*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setRenderer(r_enderer);
	return 0;
}

static int Polycore_CoreServices_getRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getRenderer();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int elapsed = lua_tointeger(L, 2);
	inst->Update(elapsed);
	return 0;
}

static int Polycore_CoreServices_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_CoreServices_setCore(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Core* core = (Core*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setCore(core);
	return 0;
}

static int Polycore_CoreServices_setupBasicListeners(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	inst->setupBasicListeners();
	return 0;
}

static int Polycore_CoreServices_getCore(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getCore();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_installModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	PolycodeModule* module = (PolycodeModule*) *((PolyBase**)lua_touserdata(L, 2));
	inst->installModule(module);
	return 0;
}

static int Polycore_CoreServices_getMaterialManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getMaterialManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getScreenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getScreenManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getSceneManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSceneManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getTimerManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTimerManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getTweenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTweenManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getResourceManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getResourceManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getSoundManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSoundManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getFontManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getFontManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getLogger(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getLogger();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_CoreServices_getConfig(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getConfig();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_CoreServices(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((CoreServices*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Cubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture* t0 = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* t1 = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Texture* t2 = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Texture* t3 = (Texture*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Texture* t4 = (Texture*) *((PolyBase**)lua_touserdata(L, 5));
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Texture* t5 = (Texture*) *((PolyBase**)lua_touserdata(L, 6));
	Cubemap *inst = new Cubemap(t0, t1, t2, t3, t4, t5);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Cubemap");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Cubemap_getTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Cubemap *inst = (Cubemap*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getTexture(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Cubemap_setTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Cubemap *inst = (Cubemap*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int index = lua_tointeger(L, 3);
	inst->setTexture(texture, index);
	return 0;
}

static int Polycore_Cubemap_recreateFromTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Cubemap *inst = (Cubemap*) *((PolyBase**)lua_touserdata(L, 1));
	inst->recreateFromTextures();
	return 0;
}

static int Polycore_delete_Cubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Cubemap*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Data(lua_State *L) {
	Data *inst = new Data();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Data");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Data_loadFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->loadFromFile(fileName));
	return 1;
}

static int Polycore_Data_getAsString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	lua_pushstring(L, inst->getAsString(encoding).c_str());
	return 1;
}

static int Polycore_Data_setFromString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 3);
	inst->setFromString(str, encoding);
	return 0;
}

static int Polycore_Data_saveToFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->saveToFile(fileName));
	return 1;
}

static int Polycore_Data_getData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getData();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_Data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Data*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Rotation_get_pitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->pitch);
	return 1;
}

static int Polycore_Rotation_get_yaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->yaw);
	return 1;
}

static int Polycore_Rotation_get_roll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->roll);
	return 1;
}

static int Polycore_Rotation_set_pitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->pitch = param;
	return 0;
}

static int Polycore_Rotation_set_yaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->yaw = param;
	return 0;
}

static int Polycore_Rotation_set_roll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->roll = param;
	return 0;
}

static int Polycore_Rotation(lua_State *L) {
	Rotation *inst = new Rotation();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Rotation");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_delete_Rotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Rotation*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Entity_get_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsChildren);
	return 1;
}

static int Polycore_Entity_get_custEntityType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->custEntityType.c_str());
	return 1;
}

static int Polycore_Entity_get_billboardMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->billboardMode);
	return 1;
}

static int Polycore_Entity_get_billboardRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->billboardRoll);
	return 1;
}

static int Polycore_Entity_get_billboardIgnoreScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->billboardIgnoreScale);
	return 1;
}

static int Polycore_Entity_get_alphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->alphaTest);
	return 1;
}

static int Polycore_Entity_get_backfaceCulled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->backfaceCulled);
	return 1;
}

static int Polycore_Entity_get_renderWireframe(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->renderWireframe);
	return 1;
}

static int Polycore_Entity_get_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->color;
	return 1;
}

static int Polycore_Entity_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycore_Entity_get_visible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->visible);
	return 1;
}

static int Polycore_Entity_get_depthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthWrite);
	return 1;
}

static int Polycore_Entity_get_depthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthTest);
	return 1;
}

static int Polycore_Entity_get_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->blendingMode);
	return 1;
}

static int Polycore_Entity_get_colorAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->colorAffectsChildren);
	return 1;
}

static int Polycore_Entity_get_visibilityAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->visibilityAffectsChildren);
	return 1;
}

static int Polycore_Entity_get_depthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthOnly);
	return 1;
}

static int Polycore_Entity_get_bBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->bBox;
	return 1;
}

static int Polycore_Entity_get_ignoreParentMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ignoreParentMatrix);
	return 1;
}

static int Polycore_Entity_get_enableScissor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enableScissor);
	return 1;
}

static int Polycore_Entity_get_scissorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->scissorBox;
	return 1;
}

static int Polycore_Entity_get_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->position;
	return 1;
}

static int Polycore_Entity_get_scale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->scale;
	return 1;
}

static int Polycore_Entity_get_rotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->rotation;
	return 1;
}

static int Polycore_Entity_get_editorOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->editorOnly);
	return 1;
}

static int Polycore_Entity_get_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->id.c_str());
	return 1;
}

static int Polycore_Entity_set_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsChildren = param;
	return 0;
}

static int Polycore_Entity_set_custEntityType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->custEntityType = param;
	return 0;
}

static int Polycore_Entity_set_billboardMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->billboardMode = param;
	return 0;
}

static int Polycore_Entity_set_billboardRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->billboardRoll = param;
	return 0;
}

static int Polycore_Entity_set_billboardIgnoreScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->billboardIgnoreScale = param;
	return 0;
}

static int Polycore_Entity_set_alphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->alphaTest = param;
	return 0;
}

static int Polycore_Entity_set_backfaceCulled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->backfaceCulled = param;
	return 0;
}

static int Polycore_Entity_set_renderWireframe(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->renderWireframe = param;
	return 0;
}

static int Polycore_Entity_set_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->color = *argInst;
	return 0;
}

static int Polycore_Entity_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

static int Polycore_Entity_set_visible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->visible = param;
	return 0;
}

static int Polycore_Entity_set_depthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthWrite = param;
	return 0;
}

static int Polycore_Entity_set_depthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthTest = param;
	return 0;
}

static int Polycore_Entity_set_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->blendingMode = param;
	return 0;
}

static int Polycore_Entity_set_colorAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->colorAffectsChildren = param;
	return 0;
}

static int Polycore_Entity_set_visibilityAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->visibilityAffectsChildren = param;
	return 0;
}

static int Polycore_Entity_set_depthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthOnly = param;
	return 0;
}

static int Polycore_Entity_set_bBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->bBox = *argInst;
	return 0;
}

static int Polycore_Entity_set_ignoreParentMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ignoreParentMatrix = param;
	return 0;
}

static int Polycore_Entity_set_enableScissor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enableScissor = param;
	return 0;
}

static int Polycore_Entity_set_scissorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Rectangle *argInst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scissorBox = *argInst;
	return 0;
}

static int Polycore_Entity_set_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->position = *argInst;
	return 0;
}

static int Polycore_Entity_set_scale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scale = *argInst;
	return 0;
}

static int Polycore_Entity_set_rotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Rotation *argInst = (Rotation*) *((PolyBase**)lua_touserdata(L, 2));
	inst->rotation = *argInst;
	return 0;
}

static int Polycore_Entity_set_editorOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->editorOnly = param;
	return 0;
}

static int Polycore_Entity_set_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->id = param;
	return 0;
}

static int Polycore_Entity(lua_State *L) {
	Entity *inst = new Entity();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Entity");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Entity_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_Entity_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_Entity_transformAndRender(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->transformAndRender();
	return 0;
}

static int Polycore_Entity_renderChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->renderChildren();
	return 0;
}

static int Polycore_Entity_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Entity_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_Entity_dirtyMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->dirtyMatrix(val);
	return 0;
}

static int Polycore_Entity_rebuildTransformMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->rebuildTransformMatrix();
	return 0;
}

static int Polycore_Entity_updateEntityMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->updateEntityMatrix();
	return 0;
}

static int Polycore_Entity_getTransformMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	 Matrix4  *retInst = new  Matrix4 ();
	*retInst = inst->getTransformMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Matrix4 ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_getConcatenatedMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getConcatenatedMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_getConcatenatedMatrixRelativeTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* relativeEntity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getConcatenatedMatrixRelativeTo(relativeEntity);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_getConcatenatedRollMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getConcatenatedRollMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_setTransformByMatrixPure(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setTransformByMatrixPure(matrix);
	return 0;
}

static int Polycore_Entity_getLookAtMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 loc = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getLookAtMatrix(loc, upVector);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_moveChildUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* child = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->moveChildUp(child);
	return 0;
}

static int Polycore_Entity_moveChildDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* child = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->moveChildDown(child);
	return 0;
}

static int Polycore_Entity_moveChildTop(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* child = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->moveChildTop(child);
	return 0;
}

static int Polycore_Entity_moveChildBottom(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* child = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->moveChildBottom(child);
	return 0;
}

static int Polycore_Entity_addEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* newChild = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addEntity(newChild);
	return 0;
}

static int Polycore_Entity_addChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* newChild = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addChild(newChild);
	return 0;
}

static int Polycore_Entity_removeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* entityToRemove = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeChild(entityToRemove);
	return 0;
}

static int Polycore_Entity_setParentEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* entity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setParentEntity(entity);
	return 0;
}

static int Polycore_Entity_getParentEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getParentEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Entity_getNumChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumChildren());
	return 1;
}

static int Polycore_Entity_getChildAtIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getChildAtIndex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Entity_setOwnsChildrenRecursive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setOwnsChildrenRecursive(val);
	return 0;
}

static int Polycore_Entity_getPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getPosition();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_getCombinedPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getCombinedPosition();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_setPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->setPosition(x, y, z);
	return 0;
}

static int Polycore_Entity_setPositionX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	inst->setPositionX(x);
	return 0;
}

static int Polycore_Entity_setPositionY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number y = lua_tonumber(L, 2);
	inst->setPositionY(y);
	return 0;
}

static int Polycore_Entity_Translate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->Translate(x, y, z);
	return 0;
}

static int Polycore_Entity_setPositionZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number z = lua_tonumber(L, 2);
	inst->setPositionZ(z);
	return 0;
}

static int Polycore_Entity_setScaleX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	inst->setScaleX(x);
	return 0;
}

static int Polycore_Entity_setScaleY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number y = lua_tonumber(L, 2);
	inst->setScaleY(y);
	return 0;
}

static int Polycore_Entity_setScaleZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number z = lua_tonumber(L, 2);
	inst->setScaleZ(z);
	return 0;
}

static int Polycore_Entity_Scale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->Scale(x, y, z);
	return 0;
}

static int Polycore_Entity_setScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->setScale(x, y, z);
	return 0;
}

static int Polycore_Entity_getCompoundScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getCompoundScale();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_getScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getScale();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_getCombinedPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getCombinedPitch());
	return 1;
}

static int Polycore_Entity_getCombinedYaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getCombinedYaw());
	return 1;
}

static int Polycore_Entity_getCombinedRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getCombinedRoll());
	return 1;
}

static int Polycore_Entity_rebuildRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->rebuildRotation();
	return 0;
}

static int Polycore_Entity_setPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number pitch = lua_tonumber(L, 2);
	inst->setPitch(pitch);
	return 0;
}

static int Polycore_Entity_setYaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number yaw = lua_tonumber(L, 2);
	inst->setYaw(yaw);
	return 0;
}

static int Polycore_Entity_setRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number roll = lua_tonumber(L, 2);
	inst->setRoll(roll);
	return 0;
}

static int Polycore_Entity_Roll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number roll = lua_tonumber(L, 2);
	inst->Roll(roll);
	return 0;
}

static int Polycore_Entity_Yaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number yaw = lua_tonumber(L, 2);
	inst->Yaw(yaw);
	return 0;
}

static int Polycore_Entity_Pitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number pitch = lua_tonumber(L, 2);
	inst->Pitch(pitch);
	return 0;
}

static int Polycore_Entity_getPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getPitch());
	return 1;
}

static int Polycore_Entity_getYaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getYaw());
	return 1;
}

static int Polycore_Entity_getRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getRoll());
	return 1;
}

static int Polycore_Entity_setRotationQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number x = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number y = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number z = lua_tonumber(L, 5);
	inst->setRotationQuat(w, x, y, z);
	return 0;
}

static int Polycore_Entity_getRotationQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Quaternion *retInst = new Quaternion();
	*retInst = inst->getRotationQuat();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Quaternion");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_lookAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 loc = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->lookAt(loc, upVector);
	return 0;
}

static int Polycore_Entity_lookAtEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* entity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->lookAtEntity(entity, upVector);
	return 0;
}

static int Polycore_Entity_getCombinedColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Color *retInst = new Color();
	*retInst = inst->getCombinedColor();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_setColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a = lua_tonumber(L, 5);
	inst->setColor(r, g, b, a);
	return 0;
}

static int Polycore_Entity_setColorInt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int r = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int g = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int b = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int a = lua_tointeger(L, 5);
	inst->setColorInt(r, g, b, a);
	return 0;
}

static int Polycore_Entity_recalculateBBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->recalculateBBox();
	return 0;
}

static int Polycore_Entity_getBBoxRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getBBoxRadius());
	return 1;
}

static int Polycore_Entity_getCompoundBBoxRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getCompoundBBoxRadius());
	return 1;
}

static int Polycore_Entity_setBBoxRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number rad = lua_tonumber(L, 2);
	inst->setBBoxRadius(rad);
	return 0;
}

static int Polycore_Entity_setUserData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* userData = (void*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setUserData(userData);
	return 0;
}

static int Polycore_Entity_getUserData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getUserData();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Entity_setBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newBl_endingMode = lua_tointeger(L, 2);
	inst->setBlendingMode(newBl_endingMode);
	return 0;
}

static int Polycore_Entity_getEntityById(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String id = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->getEntityById(id, recursive);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Entity_getEntitiesByTag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String tag = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	std::vector<Entity*> retVector = inst->getEntitiesByTag(tag, recursive);
	lua_newtable(L);
	for(int i=0; i < retVector.size(); i++) {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)retVector[i];
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static int Polycore_Entity_getChildCenter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getChildCenter();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_getEntityProp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String propName = String(lua_tostring(L, 2));
	lua_pushstring(L, inst->getEntityProp(propName).c_str());
	return 1;
}

static int Polycore_Entity_setEntityProp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String propName = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String propValue = String(lua_tostring(L, 3));
	inst->setEntityProp(propName, propValue);
	return 0;
}

static int Polycore_Entity_doUpdates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->doUpdates();
	return 0;
}

static int Polycore_Entity_buildPositionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->buildPositionMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Entity_adjustMatrixForChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->adjustMatrixForChildren();
	return 0;
}

static int Polycore_Entity_setRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Renderer* r_enderer = (Renderer*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setRenderer(r_enderer);
	return 0;
}

static int Polycore_Entity_getNumTags(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumTags());
	return 1;
}

static int Polycore_Entity_getTagAtIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	lua_pushstring(L, inst->getTagAtIndex(index).c_str());
	return 1;
}

static int Polycore_Entity_hasTag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String tag = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->hasTag(tag));
	return 1;
}

static int Polycore_Entity_clearTags(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearTags();
	return 0;
}

static int Polycore_Entity_addTag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String tag = String(lua_tostring(L, 2));
	inst->addTag(tag);
	return 0;
}

static int Polycore_delete_Entity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Entity*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Event_get_deleteOnDispatch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->deleteOnDispatch);
	return 1;
}

static int Polycore_Event_set_deleteOnDispatch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->deleteOnDispatch = param;
	return 0;
}

static int Polycore_Event(lua_State *L) {
	Event *inst = new Event();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Event");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Event_getEventCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getEventCode());
	return 1;
}

static int Polycore_Event_getDispatcher(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getDispatcher();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Event_setEventCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 2);
	inst->setEventCode(eventCode);
	return 0;
}

static int Polycore_Event_setDispatcher(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	EventDispatcher* dispatcher = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setDispatcher(dispatcher);
	return 0;
}

static int Polycore_Event_getEventType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getEventType();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_delete_Event(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Event*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_EventDispatcher(lua_State *L) {
	EventDispatcher *inst = new EventDispatcher();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.EventDispatcher");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_EventDispatcher_removeAllHandlers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
	inst->removeAllHandlers();
	return 0;
}

static int Polycore_EventDispatcher_removeAllHandlersForListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	EventHandler* handler = (EventHandler*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeAllHandlersForListener(handler);
	return 0;
}

static int Polycore_EventDispatcher_addEventListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	EventHandler* handler = (EventHandler*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->addEventListener(handler, eventCode);
	return 0;
}

static int Polycore_EventDispatcher_removeEventListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	EventHandler* handler = (EventHandler*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->removeEventListener(handler, eventCode);
	return 0;
}

static int Polycore_EventDispatcher___dispatchEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Event* event = (Event*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->__dispatchEvent(event, eventCode);
	return 0;
}

static int Polycore_EventDispatcher_dispatchEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Event* event = (Event*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->dispatchEvent(event, eventCode);
	return 0;
}

static int Polycore_EventDispatcher_dispatchEventNoDelete(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Event* event = (Event*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->dispatchEventNoDelete(event, eventCode);
	return 0;
}

static int Polycore_delete_EventDispatcher(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((EventDispatcher*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_EventHandler_get_secondaryHandlerData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EventHandler *inst = (EventHandler*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->secondaryHandlerData;
	return 1;
}

static int Polycore_EventHandler(lua_State *L) {
	LuaEventHandler *inst = new LuaEventHandler();
	inst->wrapperIndex = luaL_ref(L, LUA_REGISTRYINDEX );
	inst->L = L;
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.EventHandler");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_delete_EventHandler(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((EventHandler*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_FixedShader(lua_State *L) {
	FixedShader *inst = new FixedShader();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.FixedShader");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_FixedShader_createBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FixedShader *inst = (FixedShader*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->createBinding();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_FixedShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((FixedShader*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_FixedShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FixedShader* shader = (FixedShader*) *((PolyBase**)lua_touserdata(L, 1));
	FixedShaderBinding *inst = new FixedShaderBinding(shader);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.FixedShaderBinding");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_FixedShaderBinding_addTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
	inst->addTexture(name, texture);
	return 0;
}

static int Polycore_FixedShaderBinding_addCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Cubemap* cubemap = (Cubemap*) *((PolyBase**)lua_touserdata(L, 3));
	inst->addCubemap(name, cubemap);
	return 0;
}

static int Polycore_FixedShaderBinding_getDiffuseTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getDiffuseTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_FixedShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((FixedShaderBinding*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Font_get_loaded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->loaded);
	return 1;
}

static int Polycore_Font_set_loaded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->loaded = param;
	return 0;
}

static int Polycore_Font(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	Font *inst = new Font(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Font");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Font_getFace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	FT_Face *retInst = new FT_Face();
	*retInst = inst->getFace();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.FT_Face");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Font_isValid(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isValid());
	return 1;
}

static int Polycore_Font_setFontName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fontName = String(lua_tostring(L, 2));
	inst->setFontName(fontName);
	return 0;
}

static int Polycore_Font_getFontName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getFontName().c_str());
	return 1;
}

static int Polycore_Font_getFontPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getFontPath().c_str());
	return 1;
}

static int Polycore_delete_Font(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Font*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_FontManager(lua_State *L) {
	FontManager *inst = new FontManager();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.FontManager");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_FontManager_registerFont(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FontManager *inst = (FontManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fontName = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String fontPath = String(lua_tostring(L, 3));
	inst->registerFont(fontName, fontPath);
	return 0;
}

static int Polycore_FontManager_getFontByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FontManager *inst = (FontManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fontName = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getFontByName(fontName);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_FontManager_getNumFonts(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FontManager *inst = (FontManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumFonts());
	return 1;
}

static int Polycore_FontManager_getFontEntryByIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FontManager *inst = (FontManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getFontEntryByIndex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_FontManager_getFontEntryByFontPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FontManager *inst = (FontManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fontPath = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getFontEntryByFontPath(fontPath);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_FontManager_removeFontEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	FontManager *inst = (FontManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	FontEntry* entry = (FontEntry*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deleteFont = lua_toboolean(L, 3) != 0;
	inst->removeFontEntry(entry, deleteFont);
	return 0;
}

static int Polycore_delete_FontManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((FontManager*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Image(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	Image *inst = new Image(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Image");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Image_BlankImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int width = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int height = lua_tointeger(L, 2);
	int type;
	if(lua_isnumber(L, 3)) {
		type = lua_tointeger(L, 3);
	} else {
		type = Image :: IMAGE_RGBA;
	}
	PolyBase *ptrRetVal = (PolyBase*)Image::BlankImage(width, height, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Image_loadImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->loadImage(fileName));
	return 1;
}

static int Polycore_Image_loadPNG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->loadPNG(fileName));
	return 1;
}

static int Polycore_Image_saveImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->saveImage(fileName));
	return 1;
}

static int Polycore_Image_savePNG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->savePNG(fileName));
	return 1;
}

static int Polycore_Image_pasteImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Image* image = (Image*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int x = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int y = lua_tointeger(L, 4);
	int bl_endingMode;
	if(lua_isnumber(L, 5)) {
		bl_endingMode = lua_tointeger(L, 5);
	} else {
		bl_endingMode = 0;
	}
	Number bl_endAmount;
	if(lua_isnumber(L, 6)) {
		bl_endAmount = lua_tonumber(L, 6);
	} else {
		bl_endAmount = 1.0;
	}
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Color bl_endColor = *(Color*) *((PolyBase**)lua_touserdata(L, 7));
	inst->pasteImage(image, x, y, bl_endingMode, bl_endAmount, bl_endColor);
	return 0;
}

static int Polycore_Image_createEmpty(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	inst->createEmpty(width, height);
	return 0;
}

static int Polycore_Image_fill(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->fill(color);
	return 0;
}

static int Polycore_Image_setPixel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number r = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number g = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number b = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number a = lua_tonumber(L, 7);
	inst->setPixel(x, y, r, g, b, a);
	return 0;
}

static int Polycore_Image_getPixel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	Color *retInst = new Color();
	*retInst = inst->getPixel(x, y);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Image_swap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	int* v1 = (int*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	int* v2 = (int*) *((PolyBase**)lua_touserdata(L, 3));
	inst->swap(v1, v2);
	return 0;
}

static int Polycore_Image_drawLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x0 = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y0 = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int x1 = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int y1 = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Color col = *(Color*) *((PolyBase**)lua_touserdata(L, 6));
	inst->drawLine(x0, y0, x1, y1, col);
	return 0;
}

static int Polycore_Image_moveBrushTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	inst->moveBrushTo(x, y);
	return 0;
}

static int Polycore_Image_moveBrush(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	inst->moveBrush(x, y);
	return 0;
}

static int Polycore_Image_drawLineTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Color col = *(Color*) *((PolyBase**)lua_touserdata(L, 4));
	inst->drawLineTo(x, y, col);
	return 0;
}

static int Polycore_Image_fillRect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int w = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int h = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Color col = *(Color*) *((PolyBase**)lua_touserdata(L, 6));
	inst->fillRect(x, y, w, h, col);
	return 0;
}

static int Polycore_Image_perlinNoise(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int seed = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool alpha = lua_toboolean(L, 3) != 0;
	inst->perlinNoise(seed, alpha);
	return 0;
}

static int Polycore_Image_fastBlur(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int blurSize = lua_tointeger(L, 2);
	inst->fastBlur(blurSize);
	return 0;
}

static int Polycore_Image_fastBlurVert(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int blurSize = lua_tointeger(L, 2);
	inst->fastBlurVert(blurSize);
	return 0;
}

static int Polycore_Image_fastBlurHor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int blurSize = lua_tointeger(L, 2);
	inst->fastBlurHor(blurSize);
	return 0;
}

static int Polycore_Image_gaussianBlur(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number deviation = lua_tonumber(L, 3);
	inst->gaussianBlur(radius, deviation);
	return 0;
}

static int Polycore_Image_createKernel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number deviation = lua_tonumber(L, 3);
	PolyBase *ptrRetVal = (PolyBase*)inst->createKernel(radius, deviation);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Image_darken(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amt = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool color = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool alpha = lua_toboolean(L, 4) != 0;
	inst->darken(amt, color, alpha);
	return 0;
}

static int Polycore_Image_lighten(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amt = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool color = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool alpha = lua_toboolean(L, 4) != 0;
	inst->lighten(amt, color, alpha);
	return 0;
}

static int Polycore_Image_multiply(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amt = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool color = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool alpha = lua_toboolean(L, 4) != 0;
	inst->multiply(amt, color, alpha);
	return 0;
}

static int Polycore_Image_getPixelsInRect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int width = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int height = lua_tointeger(L, 5);
	PolyBase *ptrRetVal = (PolyBase*)inst->getPixelsInRect(x, y, width, height);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Image_getImagePart(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Polycode::Rectangle subRect = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getImagePart(subRect);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Image_getBrushX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getBrushX());
	return 1;
}

static int Polycore_Image_getBrushY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getBrushY());
	return 1;
}

static int Polycore_Image_isLoaded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isLoaded());
	return 1;
}

static int Polycore_Image_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Polycore_Image_writeBMP(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->writeBMP(fileName);
	return 0;
}

static int Polycore_Image_getWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getWidth());
	return 1;
}

static int Polycore_Image_getHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getHeight());
	return 1;
}

static int Polycore_Image_getPixels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getPixels();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Image_premultiplyAlpha(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	inst->premultiplyAlpha();
	return 0;
}

static int Polycore_delete_Image(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Image*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_InputEvent_get_mouseButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->mouseButton);
	return 1;
}

static int Polycore_InputEvent_get_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->mousePosition;
	return 1;
}

static int Polycore_InputEvent_get_key(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->key);
	return 1;
}

static int Polycore_InputEvent_get_charCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->charCode;
	return 1;
}

static int Polycore_InputEvent_get_timestamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->timestamp);
	return 1;
}

static int Polycore_InputEvent_get_touch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->touch;
	return 1;
}

static int Polycore_InputEvent_get_joystickDeviceID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->joystickDeviceID);
	return 1;
}

static int Polycore_InputEvent_get_joystickAxisValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->joystickAxisValue);
	return 1;
}

static int Polycore_InputEvent_get_joystickButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->joystickButton);
	return 1;
}

static int Polycore_InputEvent_get_joystickAxis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->joystickAxis);
	return 1;
}

static int Polycore_InputEvent_get_joystickIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->joystickIndex);
	return 1;
}

static int Polycore_InputEvent_set_mouseButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->mouseButton = param;
	return 0;
}

static int Polycore_InputEvent_set_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->mousePosition = *argInst;
	return 0;
}

static int Polycore_InputEvent_set_key(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyKEY param = (PolyKEY)lua_tointeger(L, 2);
	inst->key = param;
	return 0;
}

static int Polycore_InputEvent_set_charCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	wchar_t *argInst = (wchar_t*) *((PolyBase**)lua_touserdata(L, 2));
	inst->charCode = *argInst;
	return 0;
}

static int Polycore_InputEvent_set_timestamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->timestamp = param;
	return 0;
}

static int Polycore_InputEvent_set_touch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TouchInfo *argInst = (TouchInfo*) *((PolyBase**)lua_touserdata(L, 2));
	inst->touch = *argInst;
	return 0;
}

static int Polycore_InputEvent_set_joystickDeviceID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->joystickDeviceID = param;
	return 0;
}

static int Polycore_InputEvent_set_joystickAxisValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->joystickAxisValue = param;
	return 0;
}

static int Polycore_InputEvent_set_joystickButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->joystickButton = param;
	return 0;
}

static int Polycore_InputEvent_set_joystickAxis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->joystickAxis = param;
	return 0;
}

static int Polycore_InputEvent_set_joystickIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->joystickIndex = param;
	return 0;
}

static int Polycore_InputEvent(lua_State *L) {
	InputEvent *inst = new InputEvent();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.InputEvent");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_InputEvent_getMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getMousePosition();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_InputEvent_getKey(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getKey());
	return 1;
}

static int Polycore_InputEvent_getMouseButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getMouseButton());
	return 1;
}

static int Polycore_InputEvent_keyCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->keyCode());
	return 1;
}

static int Polycore_delete_InputEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((InputEvent*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_GlyphData_get_glyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->glyphs;
	return 1;
}

static int Polycore_GlyphData_get_positions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->positions;
	return 1;
}

static int Polycore_GlyphData_get_num_glyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->num_glyphs;
	return 1;
}

static int Polycore_GlyphData_get_trailingAdvance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->trailingAdvance);
	return 1;
}

static int Polycore_GlyphData_set_num_glyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	FT_UInt *argInst = (FT_UInt*) *((PolyBase**)lua_touserdata(L, 2));
	inst->num_glyphs = *argInst;
	return 0;
}

static int Polycore_GlyphData_set_trailingAdvance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->trailingAdvance = param;
	return 0;
}

static int Polycore_GlyphData(lua_State *L) {
	GlyphData *inst = new GlyphData();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.GlyphData");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_GlyphData_clearData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearData();
	return 0;
}

static int Polycore_delete_GlyphData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((GlyphData*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font* font = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int size = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int antiAliasMode = lua_tointeger(L, 4);
	bool premultiplyAlpha;
	if(lua_isboolean(L, 5)) {
		premultiplyAlpha = lua_toboolean(L, 5) != 0;
	} else {
		premultiplyAlpha = false;
	}
	Label *inst = new Label(font, text, size, antiAliasMode, premultiplyAlpha);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Label");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Label_setText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	inst->setText(text);
	return 0;
}

static int Polycore_Label_getText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getText();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Label_getTextWidthForString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	lua_pushinteger(L, inst->getTextWidthForString(text));
	return 1;
}

static int Polycore_Label_getTextHeightForString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	lua_pushinteger(L, inst->getTextHeightForString(text));
	return 1;
}

static int Polycore_Label_computeStringBbox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	GlyphData* glyphData = (GlyphData*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	FT_BBox* abbox = (FT_BBox*) *((PolyBase**)lua_touserdata(L, 3));
	inst->computeStringBbox(glyphData, abbox);
	return 0;
}

static int Polycore_Label_precacheGlyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	GlyphData* glyphData = (GlyphData*) *((PolyBase**)lua_touserdata(L, 3));
	inst->precacheGlyphs(text, glyphData);
	return 0;
}

static int Polycore_Label_renderGlyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	GlyphData* glyphData = (GlyphData*) *((PolyBase**)lua_touserdata(L, 2));
	inst->renderGlyphs(glyphData);
	return 0;
}

static int Polycore_Label_drawGlyphBitmap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	FT_Bitmap* bitmap = (FT_Bitmap*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int x = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int y = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Color glyphColor = *(Color*) *((PolyBase**)lua_touserdata(L, 5));
	inst->drawGlyphBitmap(bitmap, x, y, glyphColor);
	return 0;
}

static int Polycore_Label_getTextWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getTextWidth());
	return 1;
}

static int Polycore_Label_getTextHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getTextHeight());
	return 1;
}

static int Polycore_Label_clearColors(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearColors();
	return 0;
}

static int Polycore_Label_setColorForRange(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int rangeStart = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int rangeEnd = lua_tointeger(L, 4);
	inst->setColorForRange(color, rangeStart, rangeEnd);
	return 0;
}

static int Polycore_Label_getColorForIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	Color *retInst = new Color();
	*retInst = inst->getColorForIndex(index);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Label_setFont(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Font* newFont = (Font*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setFont(newFont);
	return 0;
}

static int Polycore_Label_getFont(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getFont();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Label_setSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newSize = lua_tointeger(L, 2);
	inst->setSize(newSize);
	return 0;
}

static int Polycore_Label_getSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getSize());
	return 1;
}

static int Polycore_Label_getAntialiasMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getAntialiasMode());
	return 1;
}

static int Polycore_Label_setAntialiasMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newMode = lua_tointeger(L, 2);
	inst->setAntialiasMode(newMode);
	return 0;
}

static int Polycore_Label_optionsChanged(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->optionsChanged());
	return 1;
}

static int Polycore_Label_getBaselineAdjust(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getBaselineAdjust());
	return 1;
}

static int Polycore_delete_Label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Label*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Material_get_fp16RenderTargets(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->fp16RenderTargets);
	return 1;
}

static int Polycore_Material_get_shaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->shaderModule;
	return 1;
}

static int Polycore_Material_get_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->blendingMode);
	return 1;
}

static int Polycore_Material_get_screenMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->screenMaterial);
	return 1;
}

static int Polycore_Material_set_fp16RenderTargets(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->fp16RenderTargets = param;
	return 0;
}

static int Polycore_Material_set_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->blendingMode = param;
	return 0;
}

static int Polycore_Material_set_screenMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->screenMaterial = param;
	return 0;
}

static int Polycore_Material(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String name = String(lua_tostring(L, 1));
	Material *inst = new Material(name);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Material");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Material_addShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ShaderBinding* shaderBinding = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 3));
	inst->addShader(shader, shaderBinding);
	return 0;
}

static int Polycore_Material_addShaderAtIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ShaderBinding* shaderBinding = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	int shaderIndex = lua_tointeger(L, 4);
	inst->addShaderAtIndex(shader, shaderBinding, shaderIndex);
	return 0;
}

static int Polycore_Material_getNumShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumShaders());
	return 1;
}

static int Polycore_Material_removeShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int shaderIndex = lua_tointeger(L, 2);
	inst->removeShader(shaderIndex);
	return 0;
}

static int Polycore_Material_addShaderRenderTarget(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ShaderRenderTarget* newTarget = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addShaderRenderTarget(newTarget);
	return 0;
}

static int Polycore_Material_getNumShaderRenderTargets(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumShaderRenderTargets());
	return 1;
}

static int Polycore_Material_getShaderRenderTarget(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getShaderRenderTarget(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Material_removeShaderRenderTarget(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	inst->removeShaderRenderTarget(index);
	return 0;
}

static int Polycore_Material_recreateRenderTarget(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ShaderRenderTarget* r_enderTarget = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 2));
	inst->recreateRenderTarget(r_enderTarget);
	return 0;
}

static int Polycore_Material_recreateRenderTargets(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	inst->recreateRenderTargets();
	return 0;
}

static int Polycore_Material_getName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getName();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Material_getShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getShader(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Material_getShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getShaderBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Material_loadMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadMaterial(fileName);
	return 0;
}

static int Polycore_Material_setName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	inst->setName(name);
	return 0;
}

static int Polycore_Material_clearShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearShaders();
	return 0;
}

static int Polycore_delete_Material(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Material*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_MaterialManager_get_premultiplyAlphaOnLoad(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->premultiplyAlphaOnLoad);
	return 1;
}

static int Polycore_MaterialManager_get_clampDefault(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->clampDefault);
	return 1;
}

static int Polycore_MaterialManager_get_mipmapsDefault(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->mipmapsDefault);
	return 1;
}

static int Polycore_MaterialManager_set_premultiplyAlphaOnLoad(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->premultiplyAlphaOnLoad = param;
	return 0;
}

static int Polycore_MaterialManager_set_clampDefault(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->clampDefault = param;
	return 0;
}

static int Polycore_MaterialManager_set_mipmapsDefault(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->mipmapsDefault = param;
	return 0;
}

static int Polycore_MaterialManager(lua_State *L) {
	MaterialManager *inst = new MaterialManager();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.MaterialManager");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_MaterialManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int elapsed = lua_tointeger(L, 2);
	inst->Update(elapsed);
	return 0;
}

static int Polycore_MaterialManager_createFramebufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int type = lua_tointeger(L, 4);
	PolyBase *ptrRetVal = (PolyBase*)inst->createFramebufferTexture(width, height, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_createTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TUSERDATA);
	char* imageData = (char*) *((PolyBase**)lua_touserdata(L, 4));
	bool clamp;
	if(lua_isboolean(L, 5)) {
		clamp = lua_toboolean(L, 5) != 0;
	} else {
		clamp = false;
	}
	bool createMipmaps;
	if(lua_isboolean(L, 6)) {
		createMipmaps = lua_toboolean(L, 6) != 0;
	} else {
		createMipmaps = true;
	}
	int type;
	if(lua_isnumber(L, 7)) {
		type = lua_tointeger(L, 7);
	} else {
		type = Image :: IMAGE_RGBA;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->createTexture(width, height, imageData, clamp, createMipmaps, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_createNewTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	bool clamp;
	if(lua_isboolean(L, 4)) {
		clamp = lua_toboolean(L, 4) != 0;
	} else {
		clamp = false;
	}
	bool createMipmaps;
	if(lua_isboolean(L, 5)) {
		createMipmaps = lua_toboolean(L, 5) != 0;
	} else {
		createMipmaps = true;
	}
	int type;
	if(lua_isnumber(L, 6)) {
		type = lua_tointeger(L, 6);
	} else {
		type = Image :: IMAGE_RGBA;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->createNewTexture(width, height, clamp, createMipmaps, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_createTextureFromImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Image* image = (Image*) *((PolyBase**)lua_touserdata(L, 2));
	bool clamp;
	if(lua_isboolean(L, 3)) {
		clamp = lua_toboolean(L, 3) != 0;
	} else {
		clamp = false;
	}
	bool createMipmaps;
	if(lua_isboolean(L, 4)) {
		createMipmaps = lua_toboolean(L, 4) != 0;
	} else {
		createMipmaps = true;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->createTextureFromImage(image, clamp, createMipmaps);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_createTextureFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	bool clamp;
	if(lua_isboolean(L, 3)) {
		clamp = lua_toboolean(L, 3) != 0;
	} else {
		clamp = false;
	}
	bool createMipmaps;
	if(lua_isboolean(L, 4)) {
		createMipmaps = lua_toboolean(L, 4) != 0;
	} else {
		createMipmaps = true;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->createTextureFromFile(fileName, clamp, createMipmaps);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_deleteTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->deleteTexture(texture);
	return 0;
}

static int Polycore_MaterialManager_reloadTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadTextures();
	return 0;
}

static int Polycore_MaterialManager_reloadProgramsAndTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadProgramsAndTextures();
	return 0;
}

static int Polycore_MaterialManager_reloadPrograms(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadPrograms();
	return 0;
}

static int Polycore_MaterialManager_addShaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	PolycodeShaderModule* module = (PolycodeShaderModule*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addShaderModule(module);
	return 0;
}

static int Polycore_MaterialManager_getTextureByResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String resourcePath = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTextureByResourcePath(resourcePath);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_createProgramFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String programPath = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->createProgramFromFile(programPath);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_cubemapFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TiXmlNode* node = (TiXmlNode*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->cubemapFromXMLNode(node);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_materialFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TiXmlNode* node = (TiXmlNode*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->materialFromXMLNode(node);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_createMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String materialName = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String shaderName = String(lua_tostring(L, 3));
	PolyBase *ptrRetVal = (PolyBase*)inst->createMaterial(materialName, shaderName);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_setShaderFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TiXmlNode* node = (TiXmlNode*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->setShaderFromXMLNode(node);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_createShaderFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TiXmlNode* node = (TiXmlNode*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->createShaderFromXMLNode(node);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_createShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String shaderType = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String name = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TSTRING);
	String vpName = String(lua_tostring(L, 4));
	luaL_checktype(L, 5, LUA_TSTRING);
	String fpName = String(lua_tostring(L, 5));
	luaL_checktype(L, 6, LUA_TBOOLEAN);
	bool screenShader = lua_toboolean(L, 6) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->createShader(shaderType, name, vpName, fpName, screenShader);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_MaterialManager_loadMaterialsFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	std::vector<Material*> retVector = inst->loadMaterialsFromFile(fileName);
	lua_newtable(L);
	for(int i=0; i < retVector.size(); i++) {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)retVector[i];
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static int Polycore_MaterialManager_loadShadersFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	std::vector<Shader*> retVector = inst->loadShadersFromFile(fileName);
	lua_newtable(L);
	for(int i=0; i < retVector.size(); i++) {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)retVector[i];
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static int Polycore_MaterialManager_loadCubemapsFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	std::vector<Cubemap*> retVector = inst->loadCubemapsFromFile(fileName);
	lua_newtable(L);
	for(int i=0; i < retVector.size(); i++) {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)retVector[i];
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static int Polycore_MaterialManager_addMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addMaterial(material);
	return 0;
}

static int Polycore_MaterialManager_addShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addShader(shader);
	return 0;
}

static int Polycore_MaterialManager_getNumShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumShaders());
	return 1;
}

static int Polycore_MaterialManager_getShaderByIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getShaderByIndex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_MaterialManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((MaterialManager*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Matrix4(lua_State *L) {
	Matrix4 *inst = new Matrix4();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Matrix4_identity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	inst->identity();
	return 0;
}

static int Polycore_Matrix4_rotateVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 v2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->rotateVector(v2);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Matrix4_getPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->getPosition();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Matrix4_setPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->setPosition(x, y, z);
	return 0;
}

static int Polycore_Matrix4_setScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 scale = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setScale(scale);
	return 0;
}

static int Polycore_Matrix4_getEulerAngles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Number* ax = (Number*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Number* ay = (Number*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Number* az = (Number*) *((PolyBase**)lua_touserdata(L, 4));
	inst->getEulerAngles(ax, ay, az);
	return 0;
}

static int Polycore_Matrix4_transpose(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	 Matrix4 *retInst = new  Matrix4();
	*retInst = inst->transpose();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Matrix4_Inverse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->Inverse();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Matrix4_inverseAffine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->inverseAffine();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Matrix4_determinant(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->determinant());
	return 1;
}

static int Polycore_Matrix4_generalDeterminant(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Number** a = (Number**) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int n = lua_tointeger(L, 2);
	 Number *retInst = new  Number();
	*retInst = Matrix4::generalDeterminant(a, n);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Number");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_delete_Matrix4(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Matrix4*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Mesh_get_useVertexColors(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useVertexColors);
	return 1;
}

static int Polycore_Mesh_set_useVertexColors(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useVertexColors = param;
	return 0;
}

static int Polycore_Mesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int meshType = lua_tointeger(L, 1);
	Mesh *inst = new Mesh(meshType);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Mesh");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Mesh_MeshFromFileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)Mesh::MeshFromFileName(fileName);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Mesh_addPolygon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Polycode::Polygon* newPolygon = (Polycode::Polygon*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addPolygon(newPolygon);
	return 0;
}

static int Polycore_Mesh_loadMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadMesh(fileName);
	return 0;
}

static int Polycore_Mesh_clearMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearMesh();
	return 0;
}

static int Polycore_Mesh_saveToFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->saveToFile(fileName);
	return 0;
}

static int Polycore_Mesh_loadFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	OSFILE* inFile = (OSFILE*) *((PolyBase**)lua_touserdata(L, 2));
	inst->loadFromFile(inFile);
	return 0;
}

static int Polycore_Mesh_getPolygonCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getPolygonCount());
	return 1;
}

static int Polycore_Mesh_getVertexCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getVertexCount());
	return 1;
}

static int Polycore_Mesh_getPolygon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getPolygon(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Mesh_createPlane(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number h = lua_tonumber(L, 3);
	inst->createPlane(w, h);
	return 0;
}

static int Polycore_Mesh_createVPlane(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number h = lua_tonumber(L, 3);
	inst->createVPlane(w, h);
	return 0;
}

static int Polycore_Mesh_createTorus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number tubeRadius = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int rSegments = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int tSegments = lua_tointeger(L, 5);
	inst->createTorus(radius, tubeRadius, rSegments, tSegments);
	return 0;
}

static int Polycore_Mesh_createBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number d = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number h = lua_tonumber(L, 4);
	inst->createBox(w, d, h);
	return 0;
}

static int Polycore_Mesh_createSphere(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int numRings = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int numSegments = lua_tointeger(L, 4);
	inst->createSphere(radius, numRings, numSegments);
	return 0;
}

static int Polycore_Mesh_createCylinder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int numSegments = lua_tointeger(L, 4);
	bool capped;
	if(lua_isboolean(L, 5)) {
		capped = lua_toboolean(L, 5) != 0;
	} else {
		capped = true;
	}
	inst->createCylinder(height, radius, numSegments, capped);
	return 0;
}

static int Polycore_Mesh_createCone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int numSegments = lua_tointeger(L, 4);
	inst->createCone(height, radius, numSegments);
	return 0;
}

static int Polycore_Mesh_recenterMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->recenterMesh();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Mesh_useVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->useVertexNormals(val);
	return 0;
}

static int Polycore_Mesh_setVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexBuffer* buffer = (VertexBuffer*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setVertexBuffer(buffer);
	return 0;
}

static int Polycore_Mesh_getVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getVertexBuffer();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Mesh_getRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getRadius());
	return 1;
}

static int Polycore_Mesh_calculateNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool smooth;
	if(lua_isboolean(L, 2)) {
		smooth = lua_toboolean(L, 2) != 0;
	} else {
		smooth = true;
	}
	Number smoothAngle;
	if(lua_isnumber(L, 3)) {
		smoothAngle = lua_tonumber(L, 3);
	} else {
		smoothAngle = 90.0;
	}
	inst->calculateNormals(smooth, smoothAngle);
	return 0;
}

static int Polycore_Mesh_calculateTangents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->calculateTangents();
	return 0;
}

static int Polycore_Mesh_getConnectedFaces(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vertex* v = (Vertex*) *((PolyBase**)lua_touserdata(L, 2));
	std::vector<Polygon*> retVector = inst->getConnectedFaces(v);
	lua_newtable(L);
	for(int i=0; i < retVector.size(); i++) {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)retVector[i];
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static int Polycore_Mesh_getMeshType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getMeshType());
	return 1;
}

static int Polycore_Mesh_setMeshType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newType = lua_tointeger(L, 2);
	inst->setMeshType(newType);
	return 0;
}

static int Polycore_Mesh_dirtyArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int arrayIndex = lua_tointeger(L, 2);
	inst->dirtyArray(arrayIndex);
	return 0;
}

static int Polycore_Mesh_dirtyArrays(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->dirtyArrays();
	return 0;
}

static int Polycore_Mesh_calculateBBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->calculateBBox();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Mesh_hasVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->hasVertexBuffer());
	return 1;
}

static int Polycore_delete_Mesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Mesh*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_VertexBuffer_get_verticesPerFace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VertexBuffer *inst = (VertexBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->verticesPerFace);
	return 1;
}

static int Polycore_VertexBuffer_get_meshType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VertexBuffer *inst = (VertexBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->meshType);
	return 1;
}

static int Polycore_VertexBuffer_set_verticesPerFace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VertexBuffer *inst = (VertexBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->verticesPerFace = param;
	return 0;
}

static int Polycore_VertexBuffer_set_meshType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VertexBuffer *inst = (VertexBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->meshType = param;
	return 0;
}

static int Polycore_VertexBuffer(lua_State *L) {
	VertexBuffer *inst = new VertexBuffer();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.VertexBuffer");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_VertexBuffer_getVertexCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VertexBuffer *inst = (VertexBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getVertexCount());
	return 1;
}

static int Polycore_delete_VertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((VertexBuffer*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_PolycodeModule(lua_State *L) {
	PolycodeModule *inst = new PolycodeModule();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.PolycodeModule");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_PolycodeModule_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolycodeModule *inst = (PolycodeModule*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Polycore_PolycodeModule_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolycodeModule *inst = (PolycodeModule*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number elapsed = lua_tonumber(L, 2);
	inst->Update(elapsed);
	return 0;
}

static int Polycore_PolycodeModule_requiresUpdate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolycodeModule *inst = (PolycodeModule*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->requiresUpdate());
	return 1;
}

static int Polycore_delete_PolycodeModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((PolycodeModule*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ObjectEntry_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycore_ObjectEntry_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycore_ObjectEntry_get_NumberVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->NumberVal);
	return 1;
}

static int Polycore_ObjectEntry_get_intVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->intVal);
	return 1;
}

static int Polycore_ObjectEntry_get_stringVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->stringVal.c_str());
	return 1;
}

static int Polycore_ObjectEntry_get_boolVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->boolVal);
	return 1;
}

static int Polycore_ObjectEntry_get_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->length);
	return 1;
}

static int Polycore_ObjectEntry_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycore_ObjectEntry_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycore_ObjectEntry_set_NumberVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->NumberVal = param;
	return 0;
}

static int Polycore_ObjectEntry_set_intVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->intVal = param;
	return 0;
}

static int Polycore_ObjectEntry_set_stringVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->stringVal = param;
	return 0;
}

static int Polycore_ObjectEntry_set_boolVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->boolVal = param;
	return 0;
}

static int Polycore_ObjectEntry_set_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->length = param;
	return 0;
}

static int Polycore_ObjectEntry(lua_State *L) {
	ObjectEntry *inst = new ObjectEntry();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ObjectEntry");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ObjectEntry_readNumber(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String key = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Number* out = (Number*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushboolean(L, inst->readNumber(key, out));
	return 1;
}

static int Polycore_ObjectEntry_readString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String key = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	String* out = (String*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushboolean(L, inst->readString(key, out));
	return 1;
}

static int Polycore_ObjectEntry_readBool(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String key = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	bool* out = (bool*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushboolean(L, inst->readBool(key, out));
	return 1;
}

static int Polycore_ObjectEntry_addChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->addChild(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ObjectEntry_getTypedName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getTypedName().c_str());
	return 1;
}

static int Polycore_ObjectEntry_setTypedName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	inst->setTypedName(str);
	return 0;
}

static int Polycore_ObjectEntry_Clear(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Clear();
	return 0;
}

static int Polycore_delete_ObjectEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ObjectEntry*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_BinaryObjectReader_get_success(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectReader *inst = (BinaryObjectReader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->success);
	return 1;
}

static int Polycore_BinaryObjectReader_set_success(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectReader *inst = (BinaryObjectReader*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->success = param;
	return 0;
}

static int Polycore_BinaryObjectReader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Object* object = (Object*) *((PolyBase**)lua_touserdata(L, 2));
	BinaryObjectReader *inst = new BinaryObjectReader(fileName, object);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.BinaryObjectReader");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_delete_BinaryObjectReader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((BinaryObjectReader*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_BinaryObjectWriter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Object* object = (Object*) *((PolyBase**)lua_touserdata(L, 1));
	BinaryObjectWriter *inst = new BinaryObjectWriter(object);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.BinaryObjectWriter");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_BinaryObjectWriter_parseKeysFromObjectEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
	inst->parseKeysFromObjectEntry(entry);
	return 0;
}

static int Polycore_BinaryObjectWriter_writeEntryToFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
	inst->writeEntryToFile(entry);
	return 0;
}

static int Polycore_BinaryObjectWriter_addKey(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String key = String(lua_tostring(L, 2));
	lua_pushinteger(L, inst->addKey(key));
	return 1;
}

static int Polycore_BinaryObjectWriter_getKeyIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String key = String(lua_tostring(L, 2));
	lua_pushinteger(L, inst->getKeyIndex(key));
	return 1;
}

static int Polycore_BinaryObjectWriter_writeToFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->writeToFile(fileName));
	return 1;
}

static int Polycore_delete_BinaryObjectWriter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((BinaryObjectWriter*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Particle_get_particleBody(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->particleBody;
	return 1;
}

static int Polycore_Particle_get_velVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->velVector;
	return 1;
}

static int Polycore_Particle_get_dirVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->dirVector;
	return 1;
}

static int Polycore_Particle_get_deviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->deviation;
	return 1;
}

static int Polycore_Particle_get_life(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->life);
	return 1;
}

static int Polycore_Particle_get_lifespan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->lifespan);
	return 1;
}

static int Polycore_Particle_get_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->brightnessDeviation);
	return 1;
}

static int Polycore_Particle_get_perlinPosX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->perlinPosX);
	return 1;
}

static int Polycore_Particle_get_perlinPosY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->perlinPosY);
	return 1;
}

static int Polycore_Particle_get_perlinPosZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->perlinPosZ);
	return 1;
}

static int Polycore_Particle_set_velVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->velVector = *argInst;
	return 0;
}

static int Polycore_Particle_set_dirVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->dirVector = *argInst;
	return 0;
}

static int Polycore_Particle_set_deviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->deviation = *argInst;
	return 0;
}

static int Polycore_Particle_set_life(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->life = param;
	return 0;
}

static int Polycore_Particle_set_lifespan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->lifespan = param;
	return 0;
}

static int Polycore_Particle_set_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->brightnessDeviation = param;
	return 0;
}

static int Polycore_Particle_set_perlinPosX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->perlinPosX = param;
	return 0;
}

static int Polycore_Particle_set_perlinPosY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->perlinPosY = param;
	return 0;
}

static int Polycore_Particle_set_perlinPosZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->perlinPosZ = param;
	return 0;
}

static int Polycore_Particle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool isScreenParticle = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Mesh* particleMesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 5));
	Particle *inst = new Particle(particleType, isScreenParticle, material, texture, particleMesh);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Particle");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Particle_Reset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool continuious = lua_toboolean(L, 2) != 0;
	inst->Reset(continuious);
	return 0;
}

static int Polycore_Particle_createSceneParticle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Mesh* particleMesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 4));
	inst->createSceneParticle(particleType, material, particleMesh);
	return 0;
}

static int Polycore_Particle_createScreenParticle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Particle *inst = (Particle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Mesh* particleMesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 4));
	inst->createScreenParticle(particleType, texture, particleMesh);
	return 0;
}

static int Polycore_delete_Particle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Particle*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String imageFile = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int emitterType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number lifespan = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int numParticles = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 6));
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Vector3 gravity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 7));
	luaL_checktype(L, 8, LUA_TUSERDATA);
	Vector3 deviation = *(Vector3*) *((PolyBase**)lua_touserdata(L, 8));
	luaL_checktype(L, 9, LUA_TUSERDATA);
	Vector3 emitterRadius = *(Vector3*) *((PolyBase**)lua_touserdata(L, 9));
	Mesh* particleMesh;
	if(lua_isuserdata(L, 10)) {
		particleMesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 10));
	} else {
		particleMesh = NULL;
	}
	ScreenMesh* emitter;
	if(lua_isuserdata(L, 11)) {
		emitter = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 11));
	} else {
		emitter = NULL;
	}
	ScreenParticleEmitter *inst = new ScreenParticleEmitter(imageFile, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation, emitterRadius, particleMesh, emitter);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenParticleEmitter");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenParticleEmitter_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenParticleEmitter_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_ScreenParticleEmitter_getEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getEmitter();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenParticleEmitter_dispatchTriggerCompleteEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->dispatchTriggerCompleteEvent();
	return 0;
}

static int Polycore_ScreenParticleEmitter_addParticleBody(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* particleBody = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addParticleBody(particleBody);
	return 0;
}

static int Polycore_ScreenParticleEmitter_getBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getBaseMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenParticleEmitter_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_ScreenParticleEmitter_getParticleCompoundScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getParticleCompoundScale();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_delete_ScreenParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenParticleEmitter*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String materialName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int emitterType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number lifespan = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int numParticles = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 6));
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Vector3 gravity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 7));
	luaL_checktype(L, 8, LUA_TUSERDATA);
	Vector3 deviation = *(Vector3*) *((PolyBase**)lua_touserdata(L, 8));
	luaL_checktype(L, 9, LUA_TUSERDATA);
	Vector3 emitterRadius = *(Vector3*) *((PolyBase**)lua_touserdata(L, 9));
	Mesh* particleMesh;
	if(lua_isuserdata(L, 10)) {
		particleMesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 10));
	} else {
		particleMesh = NULL;
	}
	SceneMesh* emitter;
	if(lua_isuserdata(L, 11)) {
		emitter = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 11));
	} else {
		emitter = NULL;
	}
	SceneParticleEmitter *inst = new SceneParticleEmitter(materialName, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation, emitterRadius, particleMesh, emitter);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneParticleEmitter");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneParticleEmitter_getEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getEmitter();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneParticleEmitter_respawnSceneParticles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->respawnSceneParticles();
	return 0;
}

static int Polycore_SceneParticleEmitter_addParticleBody(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* particleBody = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addParticleBody(particleBody);
	return 0;
}

static int Polycore_SceneParticleEmitter_getBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getBaseMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_SceneParticleEmitter_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_SceneParticleEmitter_getParticleCompoundScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getParticleCompoundScale();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_SceneParticleEmitter_dispatchTriggerCompleteEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->dispatchTriggerCompleteEvent();
	return 0;
}

static int Polycore_delete_SceneParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneParticleEmitter*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ParticleEmitter_get_particleSpeedMod(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->particleSpeedMod);
	return 1;
}

static int Polycore_ParticleEmitter_get_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->brightnessDeviation);
	return 1;
}

static int Polycore_ParticleEmitter_get_deviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->deviation;
	return 1;
}

static int Polycore_ParticleEmitter_get_dirVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->dirVector;
	return 1;
}

static int Polycore_ParticleEmitter_get_gravVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->gravVector;
	return 1;
}

static int Polycore_ParticleEmitter_get_lifespan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->lifespan);
	return 1;
}

static int Polycore_ParticleEmitter_get_rotationFollowsPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->rotationFollowsPath);
	return 1;
}

static int Polycore_ParticleEmitter_get_scaleCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->scaleCurve;
	return 1;
}

static int Polycore_ParticleEmitter_get_colorCurveR(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorCurveR;
	return 1;
}

static int Polycore_ParticleEmitter_get_colorCurveG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorCurveG;
	return 1;
}

static int Polycore_ParticleEmitter_get_colorCurveB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorCurveB;
	return 1;
}

static int Polycore_ParticleEmitter_get_colorCurveA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorCurveA;
	return 1;
}

static int Polycore_ParticleEmitter_get_useColorCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useColorCurves);
	return 1;
}

static int Polycore_ParticleEmitter_get_useScaleCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useScaleCurves);
	return 1;
}

static int Polycore_ParticleEmitter_get_particleSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->particleSize);
	return 1;
}

static int Polycore_ParticleEmitter_get_emitterRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->emitterRadius;
	return 1;
}

static int Polycore_ParticleEmitter_get_perlinModSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->perlinModSize);
	return 1;
}

static int Polycore_ParticleEmitter_get_perlinEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->perlinEnabled);
	return 1;
}

static int Polycore_ParticleEmitter_get_rotationSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->rotationSpeed);
	return 1;
}

static int Polycore_ParticleEmitter_get_emitterType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->emitterType);
	return 1;
}

static int Polycore_ParticleEmitter_set_particleSpeedMod(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->particleSpeedMod = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->brightnessDeviation = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_deviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->deviation = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_dirVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->dirVector = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_gravVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->gravVector = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_lifespan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->lifespan = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_rotationFollowsPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->rotationFollowsPath = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_scaleCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scaleCurve = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_colorCurveR(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorCurveR = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_colorCurveG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorCurveG = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_colorCurveB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorCurveB = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_colorCurveA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorCurveA = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_useColorCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useColorCurves = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_useScaleCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useScaleCurves = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_particleSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->particleSize = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_emitterRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->emitterRadius = *argInst;
	return 0;
}

static int Polycore_ParticleEmitter_set_perlinModSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->perlinModSize = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_perlinEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->perlinEnabled = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_rotationSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->rotationSpeed = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_emitterType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->emitterType = param;
	return 0;
}

static int Polycore_ParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String imageFile = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Mesh* particleMesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int emitterType = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number lifespan = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	int numParticles = lua_tointeger(L, 6);
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 7));
	luaL_checktype(L, 8, LUA_TUSERDATA);
	Vector3 gravity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 8));
	luaL_checktype(L, 9, LUA_TUSERDATA);
	Vector3 deviation = *(Vector3*) *((PolyBase**)lua_touserdata(L, 9));
	luaL_checktype(L, 10, LUA_TUSERDATA);
	Vector3 emitterRadius = *(Vector3*) *((PolyBase**)lua_touserdata(L, 10));
	ParticleEmitter *inst = new ParticleEmitter(imageFile, particleMesh, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation, emitterRadius);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ParticleEmitter");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ParticleEmitter_dispatchTriggerCompleteEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->dispatchTriggerCompleteEvent();
	return 0;
}

static int Polycore_ParticleEmitter_createParticles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->createParticles();
	return 0;
}

static int Polycore_ParticleEmitter_setRotationSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 2);
	inst->setRotationSpeed(speed);
	return 0;
}

static int Polycore_ParticleEmitter_setParticleBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mode = lua_tointeger(L, 2);
	inst->setParticleBlendingMode(mode);
	return 0;
}

static int Polycore_ParticleEmitter_getParticleBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getParticleBlendingMode());
	return 1;
}

static int Polycore_ParticleEmitter_setDepthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setDepthWrite(val);
	return 0;
}

static int Polycore_ParticleEmitter_setDepthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setDepthTest(val);
	return 0;
}

static int Polycore_ParticleEmitter_setAlphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setAlphaTest(val);
	return 0;
}

static int Polycore_ParticleEmitter_enablePerlin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enablePerlin(val);
	return 0;
}

static int Polycore_ParticleEmitter_setParticleVisibility(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setParticleVisibility(val);
	return 0;
}

static int Polycore_ParticleEmitter_setPerlinModSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number size = lua_tonumber(L, 2);
	inst->setPerlinModSize(size);
	return 0;
}

static int Polycore_ParticleEmitter_setBillboardMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool mode = lua_toboolean(L, 2) != 0;
	inst->setBillboardMode(mode);
	return 0;
}

static int Polycore_ParticleEmitter_enableEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enableEmitter(val);
	return 0;
}

static int Polycore_ParticleEmitter_emitterEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->emitterEnabled());
	return 1;
}

static int Polycore_ParticleEmitter_setEmitterRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 rad = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setEmitterRadius(rad);
	return 0;
}

static int Polycore_ParticleEmitter_setAllAtOnce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setAllAtOnce(val);
	return 0;
}

static int Polycore_ParticleEmitter_getNumParticles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumParticles());
	return 1;
}

static int Polycore_ParticleEmitter_getParticleAtIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getParticleAtIndex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ParticleEmitter_resetAll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->resetAll();
	return 0;
}

static int Polycore_ParticleEmitter_Trigger(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Trigger();
	return 0;
}

static int Polycore_ParticleEmitter_resetParticle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Particle* particle = (Particle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->resetParticle(particle);
	return 0;
}

static int Polycore_ParticleEmitter_setParticleCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int count = lua_tointeger(L, 2);
	inst->setParticleCount(count);
	return 0;
}

static int Polycore_ParticleEmitter_getParticleCompoundScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getParticleCompoundScale();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ParticleEmitter_addParticleBody(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* particleBody = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addParticleBody(particleBody);
	return 0;
}

static int Polycore_ParticleEmitter_getBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getBaseMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ParticleEmitter_updateEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	inst->updateEmitter();
	return 0;
}

static int Polycore_ParticleEmitter_getParticleTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getParticleTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ParticleEmitter_setParticleTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setParticleTexture(texture);
	return 0;
}

static int Polycore_ParticleEmitter_getIgnoreParentMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->getIgnoreParentMatrix());
	return 1;
}

static int Polycore_ParticleEmitter_setIgnoreParentMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setIgnoreParentMatrix(val);
	return 0;
}

static int Polycore_delete_ParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ParticleEmitter*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Perlin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int octaves = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number freq = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number amp = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int seed = lua_tointeger(L, 4);
	Perlin *inst = new Perlin(octaves, freq, amp, seed);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Perlin");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Perlin_Get2DTiledX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Perlin *inst = (Perlin*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number t = lua_tonumber(L, 4);
	lua_pushnumber(L, inst->Get2DTiledX(x, y, t));
	return 1;
}

static int Polycore_Perlin_Get(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Perlin *inst = (Perlin*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushnumber(L, inst->Get(x, y));
	return 1;
}

static int Polycore_Perlin_Get2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Perlin *inst = (Perlin*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushnumber(L, inst->Get2D(x, y));
	return 1;
}

static int Polycore_Perlin_Get3D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Perlin *inst = (Perlin*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	lua_pushnumber(L, inst->Get3D(x, y, z));
	return 1;
}

static int Polycore_delete_Perlin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Perlin*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Polygon_get_useVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useVertexNormals);
	return 1;
}

static int Polycore_Polygon_set_useVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useVertexNormals = param;
	return 0;
}

static int Polycore_Polygon(lua_State *L) {
	Polygon *inst = new Polygon();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Polygon");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Polygon_getVertexCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getVertexCount());
	return 1;
}

static int Polycore_Polygon_getVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getVertex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Polygon_addVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number u = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number v = lua_tonumber(L, 6);
	PolyBase *ptrRetVal = (PolyBase*)inst->addVertex(x, y, z, u, v);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Polygon_removeVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	inst->removeVertex(index);
	return 0;
}

static int Polycore_Polygon_calculateNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	inst->calculateNormal();
	return 0;
}

static int Polycore_Polygon_calculateTangent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	inst->calculateTangent();
	return 0;
}

static int Polycore_Polygon_getFaceNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getFaceNormal();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Polygon_getFaceTangent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getFaceTangent();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Polygon_getBounds2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	Polycode::Rectangle *retInst = new Polycode::Rectangle();
	*retInst = inst->getBounds2D();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Polycode::Rectangle");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Polygon_setNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 normal = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setNormal(normal);
	return 0;
}

static int Polycore_Polygon_flipUVY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Polygon *inst = (Polygon*) *((PolyBase**)lua_touserdata(L, 1));
	inst->flipUVY();
	return 0;
}

static int Polycore_delete_Polygon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Polygon*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Quaternion_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycore_Quaternion_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycore_Quaternion_get_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->z);
	return 1;
}

static int Polycore_Quaternion_get_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->w);
	return 1;
}

static int Polycore_Quaternion_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycore_Quaternion_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycore_Quaternion_set_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->z = param;
	return 0;
}

static int Polycore_Quaternion_set_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->w = param;
	return 0;
}

static int Polycore_Quaternion(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number w = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	Quaternion *inst = new Quaternion(w, x, y, z);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Quaternion");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Quaternion_setFromMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 _mat = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setFromMatrix(_mat);
	return 0;
}

static int Polycore_Quaternion_Slerp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number fT = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion rkP = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Quaternion rkQ = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 3));
	bool shortestPath;
	if(lua_isboolean(L, 4)) {
		shortestPath = lua_toboolean(L, 4) != 0;
	} else {
		shortestPath = false;
	}
	 Quaternion *retInst = new  Quaternion();
	*retInst = Quaternion::Slerp(fT, rkP, rkQ, shortestPath);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Quaternion");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Quaternion_Dot(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion rkQ = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushnumber(L, inst->Dot(rkQ));
	return 1;
}

static int Polycore_Quaternion_Log(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Quaternion *retInst = new Quaternion();
	*retInst = inst->Log();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Quaternion");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Quaternion_Exp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Quaternion *retInst = new Quaternion();
	*retInst = inst->Exp();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Quaternion");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Quaternion_Norm(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->Norm());
	return 1;
}

static int Polycore_Quaternion_Normalize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->Normalize());
	return 1;
}

static int Polycore_Quaternion_lookAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 D = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->lookAt(D, upVector);
	return 0;
}

static int Polycore_Quaternion_createFromMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->createFromMatrix(matrix);
	return 0;
}

static int Polycore_Quaternion_Squad(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number fT = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion rkP = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Quaternion rkA = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Quaternion rkB = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Quaternion rkQ = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 5));
	luaL_checktype(L, 6, LUA_TBOOLEAN);
	bool shortestPath = lua_toboolean(L, 6) != 0;
	 Quaternion *retInst = new  Quaternion();
	*retInst = Quaternion::Squad(fT, rkP, rkA, rkB, rkQ, shortestPath);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Quaternion");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Quaternion_Inverse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Quaternion *retInst = new Quaternion();
	*retInst = inst->Inverse();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Quaternion");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Quaternion_set(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number x = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number y = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number z = lua_tonumber(L, 5);
	inst->set(w, x, y, z);
	return 0;
}

static int Polycore_Quaternion_InvSqrt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	lua_pushnumber(L, inst->InvSqrt(x));
	return 1;
}

static int Polycore_Quaternion_fromAxes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number az = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number ay = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number ax = lua_tonumber(L, 4);
	inst->fromAxes(az, ay, ax);
	return 0;
}

static int Polycore_Quaternion_fromAngleAxis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number rfAngle = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 rkAxis = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->fromAngleAxis(rfAngle, rkAxis);
	return 0;
}

static int Polycore_Quaternion_toEulerAngles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 eulerAngles = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->toEulerAngles(eulerAngles);
	return 0;
}

static int Polycore_Quaternion_toAngleAxis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number rfAngle = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 rkAxis = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->toAngleAxis(rfAngle, rkAxis);
	return 0;
}

static int Polycore_Quaternion_createFromAxisAngle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number degrees = lua_tonumber(L, 5);
	inst->createFromAxisAngle(x, y, z, degrees);
	return 0;
}

static int Polycore_Quaternion_createMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->createMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Quaternion_applyTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 v = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	Vector3 *retInst = new Vector3();
	*retInst = inst->applyTo(v);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_delete_Quaternion(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Quaternion*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_QuaternionCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve* wCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* xCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	BezierCurve* yCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	BezierCurve* zCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 4));
	QuaternionCurve *inst = new QuaternionCurve(wCurve, xCurve, yCurve, zCurve);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.QuaternionCurve");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_QuaternionCurve_interpolate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuaternionCurve *inst = (QuaternionCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number t = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool useShortestPath = lua_toboolean(L, 3) != 0;
	Quaternion *retInst = new Quaternion();
	*retInst = inst->interpolate(t, useShortestPath);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Quaternion");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_QuaternionCurve_generatePointsFromCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuaternionCurve *inst = (QuaternionCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* wCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	BezierCurve* xCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	BezierCurve* yCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	BezierCurve* zCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 5));
	inst->generatePointsFromCurves(wCurve, xCurve, yCurve, zCurve);
	return 0;
}

static int Polycore_QuaternionCurve_recalcTangents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuaternionCurve *inst = (QuaternionCurve*) *((PolyBase**)lua_touserdata(L, 1));
	inst->recalcTangents();
	return 0;
}

static int Polycore_delete_QuaternionCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((QuaternionCurve*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Rectangle_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycore_Rectangle_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycore_Rectangle_get_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->w);
	return 1;
}

static int Polycore_Rectangle_get_h(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->h);
	return 1;
}

static int Polycore_Rectangle_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycore_Rectangle_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycore_Rectangle_set_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->w = param;
	return 0;
}

static int Polycore_Rectangle_set_h(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->h = param;
	return 0;
}

static int Polycore_Rectangle(lua_State *L) {
	Rectangle *inst = new Rectangle();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Rectangle");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Rectangle_setRect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number w = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number h = lua_tonumber(L, 5);
	inst->setRect(x, y, w, h);
	return 0;
}

static int Polycore_Rectangle_Clipped(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Polycode::Rectangle rect = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	Polycode::Rectangle *retInst = new Polycode::Rectangle();
	*retInst = inst->Clipped(rect);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Polycode::Rectangle");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Rectangle_minX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->minX());
	return 1;
}

static int Polycore_Rectangle_maxX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->maxX());
	return 1;
}

static int Polycore_Rectangle_minY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->minY());
	return 1;
}

static int Polycore_Rectangle_maxY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->maxY());
	return 1;
}

static int Polycore_delete_Rectangle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Rectangle*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Renderer_get_ambientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->ambientColor;
	return 1;
}

static int Polycore_Renderer_get_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->clearColor;
	return 1;
}

static int Polycore_Renderer_get_exposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->exposureLevel);
	return 1;
}

static int Polycore_Renderer_get_cameraPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->cameraPosition;
	return 1;
}

static int Polycore_Renderer_get_doClearBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->doClearBuffer);
	return 1;
}

static int Polycore_Renderer_get_blendNormalAsPremultiplied(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->blendNormalAsPremultiplied);
	return 1;
}

static int Polycore_Renderer_set_ambientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->ambientColor = *argInst;
	return 0;
}

static int Polycore_Renderer_set_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->clearColor = *argInst;
	return 0;
}

static int Polycore_Renderer_set_exposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->exposureLevel = param;
	return 0;
}

static int Polycore_Renderer_set_cameraPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->cameraPosition = *argInst;
	return 0;
}

static int Polycore_Renderer_set_doClearBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->doClearBuffer = param;
	return 0;
}

static int Polycore_Renderer_set_blendNormalAsPremultiplied(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->blendNormalAsPremultiplied = param;
	return 0;
}

static int Polycore_Renderer_Init(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->Init());
	return 1;
}

static int Polycore_Renderer_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int xRes = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int yRes = lua_tointeger(L, 3);
	inst->Resize(xRes, yRes);
	return 0;
}

static int Polycore_Renderer_BeginRender(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->BeginRender();
	return 0;
}

static int Polycore_Renderer_EndRender(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->EndRender();
	return 0;
}

static int Polycore_Renderer_createCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* t0 = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Texture* t1 = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Texture* t2 = (Texture*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Texture* t3 = (Texture*) *((PolyBase**)lua_touserdata(L, 5));
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Texture* t4 = (Texture*) *((PolyBase**)lua_touserdata(L, 6));
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Texture* t5 = (Texture*) *((PolyBase**)lua_touserdata(L, 7));
	PolyBase *ptrRetVal = (PolyBase*)inst->createCubemap(t0, t1, t2, t3, t4, t5);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Renderer_createTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TUSERDATA);
	char* textureData = (char*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TBOOLEAN);
	bool clamp = lua_toboolean(L, 5) != 0;
	luaL_checktype(L, 6, LUA_TBOOLEAN);
	bool createMipmaps = lua_toboolean(L, 6) != 0;
	int type;
	if(lua_isnumber(L, 7)) {
		type = lua_tointeger(L, 7);
	} else {
		type = Image :: IMAGE_RGBA;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->createTexture(width, height, textureData, clamp, createMipmaps, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Renderer_destroyTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->destroyTexture(texture);
	return 0;
}

static int Polycore_Renderer_createRenderTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture** colorBuffer = (Texture**) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Texture** depthBuffer = (Texture**) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	int width = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int height = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TBOOLEAN);
	bool floatingPointBuffer = lua_toboolean(L, 6) != 0;
	inst->createRenderTextures(colorBuffer, depthBuffer, width, height, floatingPointBuffer);
	return 0;
}

static int Polycore_Renderer_createFramebufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	PolyBase *ptrRetVal = (PolyBase*)inst->createFramebufferTexture(width, height);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Renderer_bindFrameBufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->bindFrameBufferTexture(texture);
	return 0;
}

static int Polycore_Renderer_bindFrameBufferTextureDepth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->bindFrameBufferTextureDepth(texture);
	return 0;
}

static int Polycore_Renderer_unbindFramebuffers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->unbindFramebuffers();
	return 0;
}

static int Polycore_Renderer_renderScreenToImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->renderScreenToImage();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Renderer_setFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fov = lua_tonumber(L, 2);
	inst->setFOV(fov);
	return 0;
}

static int Polycore_Renderer_setViewportSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int w = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int h = lua_tointeger(L, 3);
	inst->setViewportSize(w, h);
	return 0;
}

static int Polycore_Renderer_setViewportSizeAndFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int w = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int h = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number fov = lua_tonumber(L, 4);
	inst->setViewportSizeAndFOV(w, h, fov);
	return 0;
}

static int Polycore_Renderer_resetViewport(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->resetViewport();
	return 0;
}

static int Polycore_Renderer_loadIdentity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->loadIdentity();
	return 0;
}

static int Polycore_Renderer_setOrthoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	Number xSize;
	if(lua_isnumber(L, 2)) {
		xSize = lua_tonumber(L, 2);
	} else {
		xSize = 0.0f;
	}
	Number ySize;
	if(lua_isnumber(L, 3)) {
		ySize = lua_tonumber(L, 3);
	} else {
		ySize = 0.0f;
	}
	bool centered;
	if(lua_isboolean(L, 4)) {
		centered = lua_toboolean(L, 4) != 0;
	} else {
		centered = false;
	}
	inst->setOrthoMode(xSize, ySize, centered);
	return 0;
}

static int Polycore_Renderer__setOrthoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number orthoSizeX = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number orthoSizeY = lua_tonumber(L, 3);
	inst->_setOrthoMode(orthoSizeX, orthoSizeY);
	return 0;
}

static int Polycore_Renderer_setPerspectiveMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->setPerspectiveMode();
	return 0;
}

static int Polycore_Renderer_setTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setTexture(texture);
	return 0;
}

static int Polycore_Renderer_enableBackfaceCulling(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enableBackfaceCulling(val);
	return 0;
}

static int Polycore_Renderer_setClearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	Number a;
	if(lua_isnumber(L, 5)) {
		a = lua_tonumber(L, 5);
	} else {
		a = 1.0;
	}
	inst->setClearColor(r, g, b, a);
	return 0;
}

static int Polycore_Renderer_setAmbientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	inst->setAmbientColor(r, g, b);
	return 0;
}

static int Polycore_Renderer_clearScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearScreen();
	return 0;
}

static int Polycore_Renderer_translate2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->translate2D(x, y);
	return 0;
}

static int Polycore_Renderer_rotate2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number angle = lua_tonumber(L, 2);
	inst->rotate2D(angle);
	return 0;
}

static int Polycore_Renderer_scale2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2* scale = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scale2D(scale);
	return 0;
}

static int Polycore_Renderer_setVertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a = lua_tonumber(L, 5);
	inst->setVertexColor(r, g, b, a);
	return 0;
}

static int Polycore_Renderer_pushDataArrayForMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int arrayType = lua_tointeger(L, 3);
	inst->pushDataArrayForMesh(mesh, arrayType);
	return 0;
}

static int Polycore_Renderer_pushRenderDataArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	RenderDataArray* array = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->pushRenderDataArray(array);
	return 0;
}

static int Polycore_Renderer_createRenderDataArrayForMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int arrayType = lua_tointeger(L, 3);
	PolyBase *ptrRetVal = (PolyBase*)inst->createRenderDataArrayForMesh(mesh, arrayType);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Renderer_createRenderDataArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int arrayType = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->createRenderDataArray(arrayType);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Renderer_setRenderArrayData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	RenderDataArray* array = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Number* arrayData = (Number*) *((PolyBase**)lua_touserdata(L, 3));
	inst->setRenderArrayData(array, arrayData);
	return 0;
}

static int Polycore_Renderer_drawArrays(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int drawType = lua_tointeger(L, 2);
	inst->drawArrays(drawType);
	return 0;
}

static int Polycore_Renderer_translate3D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3* position = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->translate3D(position);
	return 0;
}

static int Polycore_Renderer_scale3D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3* scale = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scale3D(scale);
	return 0;
}

static int Polycore_Renderer_pushMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->pushMatrix();
	return 0;
}

static int Polycore_Renderer_popMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->popMatrix();
	return 0;
}

static int Polycore_Renderer_setLineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setLineSmooth(val);
	return 0;
}

static int Polycore_Renderer_setLineSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number lineSize = lua_tonumber(L, 2);
	inst->setLineSize(lineSize);
	return 0;
}

static int Polycore_Renderer_enableLighting(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enable = lua_toboolean(L, 2) != 0;
	inst->enableLighting(enable);
	return 0;
}

static int Polycore_Renderer_enableFog(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enable = lua_toboolean(L, 2) != 0;
	inst->enableFog(enable);
	return 0;
}

static int Polycore_Renderer_setFogProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int fogMode = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number density = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number startDepth = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number _endDepth = lua_tonumber(L, 6);
	inst->setFogProperties(fogMode, color, density, startDepth, _endDepth);
	return 0;
}

static int Polycore_Renderer_multModelviewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 m = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->multModelviewMatrix(m);
	return 0;
}

static int Polycore_Renderer_setModelviewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 m = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setModelviewMatrix(m);
	return 0;
}

static int Polycore_Renderer_setCurrentModelMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 m = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setCurrentModelMatrix(m);
	return 0;
}

static int Polycore_Renderer_getCurrentModelMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getCurrentModelMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Renderer_setBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int bl_endingMode = lua_tointeger(L, 2);
	inst->setBlendingMode(bl_endingMode);
	return 0;
}

static int Polycore_Renderer_applyMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ShaderBinding* localOptions = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	int shaderIndex = lua_tointeger(L, 4);
	inst->applyMaterial(material, localOptions, shaderIndex);
	return 0;
}

static int Polycore_Renderer_clearShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearShader();
	return 0;
}

static int Polycore_Renderer_setDepthFunction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int depthFunction = lua_tointeger(L, 2);
	inst->setDepthFunction(depthFunction);
	return 0;
}

static int Polycore_Renderer_createVertexBufferForMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
	inst->createVertexBufferForMesh(mesh);
	return 0;
}

static int Polycore_Renderer_drawVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexBuffer* buffer = (VertexBuffer*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool enableColorBuffer = lua_toboolean(L, 3) != 0;
	inst->drawVertexBuffer(buffer, enableColorBuffer);
	return 0;
}

static int Polycore_Renderer_setRenderMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newR_enderMode = lua_tointeger(L, 2);
	inst->setRenderMode(newR_enderMode);
	return 0;
}

static int Polycore_Renderer_getRenderMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getRenderMode());
	return 1;
}

static int Polycore_Renderer_enableDepthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enableDepthTest(val);
	return 0;
}

static int Polycore_Renderer_enableDepthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enableDepthWrite(val);
	return 0;
}

static int Polycore_Renderer_billboardMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->billboardMatrix();
	return 0;
}

static int Polycore_Renderer_billboardMatrixWithScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 scale = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->billboardMatrixWithScale(scale);
	return 0;
}

static int Polycore_Renderer_setTextureFilteringMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mode = lua_tointeger(L, 2);
	inst->setTextureFilteringMode(mode);
	return 0;
}

static int Polycore_Renderer_setClippingPlanes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number nearPlane = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number farPlane = lua_tonumber(L, 3);
	inst->setClippingPlanes(nearPlane, farPlane);
	return 0;
}

static int Polycore_Renderer_enableAlphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enableAlphaTest(val);
	return 0;
}

static int Polycore_Renderer_clearBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool colorBuffer = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool depthBuffer = lua_toboolean(L, 3) != 0;
	inst->clearBuffer(colorBuffer, depthBuffer);
	return 0;
}

static int Polycore_Renderer_drawToColorBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->drawToColorBuffer(val);
	return 0;
}

static int Polycore_Renderer_getCameraMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	 Matrix4  *retInst = new  Matrix4 ();
	*retInst = inst->getCameraMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Matrix4 ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Renderer_setCameraMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setCameraMatrix(matrix);
	return 0;
}

static int Polycore_Renderer_setCameraPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 pos = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setCameraPosition(pos);
	return 0;
}

static int Polycore_Renderer_drawScreenQuad(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number qx = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number qy = lua_tonumber(L, 3);
	inst->drawScreenQuad(qx, qy);
	return 0;
}

static int Polycore_Renderer_getXRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getXRes());
	return 1;
}

static int Polycore_Renderer_getYRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getYRes());
	return 1;
}

static int Polycore_Renderer_isScissorEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isScissorEnabled());
	return 1;
}

static int Polycore_Renderer_enableScissor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enableScissor(val);
	return 0;
}

static int Polycore_Renderer_setScissorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Polycode::Rectangle box = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setScissorBox(box);
	return 0;
}

static int Polycore_Renderer_getScissorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	Polycode::Rectangle *retInst = new Polycode::Rectangle();
	*retInst = inst->getScissorBox();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Polycode::Rectangle");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Renderer_setAnisotropyAmount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amount = lua_tonumber(L, 2);
	inst->setAnisotropyAmount(amount);
	return 0;
}

static int Polycore_Renderer_getAnisotropyAmount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getAnisotropyAmount());
	return 1;
}

static int Polycore_Renderer_cullFrontFaces(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->cullFrontFaces(val);
	return 0;
}

static int Polycore_Renderer_clearLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearLights();
	return 0;
}

static int Polycore_Renderer_addLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int lightImportance = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TNUMBER);
	int type = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 6));
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Color specularColor = *(Color*) *((PolyBase**)lua_touserdata(L, 7));
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number constantAttenuation = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TNUMBER);
	Number linearAttenuation = lua_tonumber(L, 9);
	luaL_checktype(L, 10, LUA_TNUMBER);
	Number quadraticAttenuation = lua_tonumber(L, 10);
	luaL_checktype(L, 11, LUA_TNUMBER);
	Number intensity = lua_tonumber(L, 11);
	luaL_checktype(L, 12, LUA_TNUMBER);
	Number spotlightCutoff = lua_tonumber(L, 12);
	luaL_checktype(L, 13, LUA_TNUMBER);
	Number spotlightExponent = lua_tonumber(L, 13);
	luaL_checktype(L, 14, LUA_TBOOLEAN);
	bool shadowsEnabled = lua_toboolean(L, 14) != 0;
	luaL_checktype(L, 15, LUA_TUSERDATA);
	Matrix4* textureMatrix = (Matrix4*) *((PolyBase**)lua_touserdata(L, 15));
	luaL_checktype(L, 16, LUA_TUSERDATA);
	Texture* shadowMapTexture = (Texture*) *((PolyBase**)lua_touserdata(L, 16));
	inst->addLight(lightImportance, position, direction, type, color, specularColor, constantAttenuation, linearAttenuation, quadraticAttenuation, intensity, spotlightCutoff, spotlightExponent, shadowsEnabled, textureMatrix, shadowMapTexture);
	return 0;
}

static int Polycore_Renderer_setExposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number level = lua_tonumber(L, 2);
	inst->setExposureLevel(level);
	return 0;
}

static int Polycore_Renderer_rayTriangleIntersect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 ray_origin = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 ray_direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Vector3 vert0 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Vector3 vert1 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 5));
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Vector3 vert2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 6));
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Vector3* hitPoint = (Vector3*) *((PolyBase**)lua_touserdata(L, 7));
	lua_pushboolean(L, inst->rayTriangleIntersect(ray_origin, ray_direction, vert0, vert1, vert2, hitPoint));
	return 1;
}

static int Polycore_Renderer_projectRayFrom2DCoordinate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Matrix4 cameraMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Matrix4 projectionMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 5));
	Vector3 *retInst = new Vector3();
	*retInst = inst->projectRayFrom2DCoordinate(x, y, cameraMatrix, projectionMatrix);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Renderer_enableShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool flag = lua_toboolean(L, 2) != 0;
	inst->enableShaders(flag);
	return 0;
}

static int Polycore_Renderer_getViewportWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getViewportWidth());
	return 1;
}

static int Polycore_Renderer_getViewportHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getViewportHeight());
	return 1;
}

static int Polycore_Renderer_setViewportShift(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number shiftX = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number shiftY = lua_tonumber(L, 3);
	inst->setViewportShift(shiftX, shiftY);
	return 0;
}

static int Polycore_Renderer_getDataPointerForName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getDataPointerForName(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Renderer_setRendererShaderParams(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ShaderBinding* binding = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 3));
	inst->setRendererShaderParams(shader, binding);
	return 0;
}

static int Polycore_Renderer_addShaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	PolycodeShaderModule* module = (PolycodeShaderModule*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addShaderModule(module);
	return 0;
}

static int Polycore_Renderer_test2DCoordinateInPolygon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TUSERDATA);
	Matrix4 cameraMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 4));
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Matrix4 projectionMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 5));
	luaL_checktype(L, 6, LUA_TUSERDATA);
	Polycode::Polygon* poly = (Polycode::Polygon*) *((PolyBase**)lua_touserdata(L, 6));
	luaL_checktype(L, 7, LUA_TUSERDATA);
	Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 7));
	luaL_checktype(L, 8, LUA_TBOOLEAN);
	bool ortho = lua_toboolean(L, 8) != 0;
	luaL_checktype(L, 9, LUA_TBOOLEAN);
	bool testBackfacing = lua_toboolean(L, 9) != 0;
	luaL_checktype(L, 10, LUA_TBOOLEAN);
	bool billboardMode = lua_toboolean(L, 10) != 0;
	bool reverseDirection;
	if(lua_isboolean(L, 11)) {
		reverseDirection = lua_toboolean(L, 11) != 0;
	} else {
		reverseDirection = false;
	}
	Matrix4* adjustMatrix;
	if(lua_isuserdata(L, 12)) {
		adjustMatrix = (Matrix4*) *((PolyBase**)lua_touserdata(L, 12));
	} else {
		adjustMatrix = NULL;
	}
	lua_pushboolean(L, inst->test2DCoordinateInPolygon(x, y, cameraMatrix, projectionMatrix, poly, matrix, ortho, testBackfacing, billboardMode, reverseDirection, adjustMatrix));
	return 1;
}

static int Polycore_Renderer_getProjectionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getProjectionMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Renderer_getModelviewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getModelviewMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Renderer_Unproject(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	Vector3 *retInst = new Vector3();
	*retInst = inst->Unproject(x, y);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Renderer_sortLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->sortLights();
	return 0;
}

static int Polycore_Renderer_getNumAreaLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumAreaLights());
	return 1;
}

static int Polycore_Renderer_getNumSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumSpotLights());
	return 1;
}

static int Polycore_Renderer_getNumLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumLights());
	return 1;
}

static int Polycore_Renderer_getAreaLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	return 0;
}

static int Polycore_Renderer_getSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
	return 0;
}

static int Polycore_delete_Renderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Renderer*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Resource_get_reloadOnFileModify(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->reloadOnFileModify);
	return 1;
}

static int Polycore_Resource_get_resourceFileTime(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->resourceFileTime;
	return 1;
}

static int Polycore_Resource_set_reloadOnFileModify(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->reloadOnFileModify = param;
	return 0;
}

static int Polycore_Resource_set_resourceFileTime(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	time_t *argInst = (time_t*) *((PolyBase**)lua_touserdata(L, 2));
	inst->resourceFileTime = *argInst;
	return 0;
}

static int Polycore_Resource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int type = lua_tointeger(L, 1);
	Resource *inst = new Resource(type);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Resource");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Resource_reloadResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadResource();
	return 0;
}

static int Polycore_Resource_getResourceName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getResourceName();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Resource_getResourceType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getResourceType());
	return 1;
}

static int Polycore_Resource_setResourceName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String newName = String(lua_tostring(L, 2));
	inst->setResourceName(newName);
	return 0;
}

static int Polycore_Resource_setResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String path = String(lua_tostring(L, 2));
	inst->setResourcePath(path);
	return 0;
}

static int Polycore_Resource_getResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getResourcePath();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_delete_Resource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Resource*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ResourceManager_get_reloadResourcesOnModify(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->reloadResourcesOnModify);
	return 1;
}

static int Polycore_ResourceManager_set_reloadResourcesOnModify(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->reloadResourcesOnModify = param;
	return 0;
}

static int Polycore_ResourceManager(lua_State *L) {
	ResourceManager *inst = new ResourceManager();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ResourceManager");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ResourceManager_addResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Resource* resource = (Resource*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addResource(resource);
	return 0;
}

static int Polycore_ResourceManager_removeResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Resource* resource = (Resource*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeResource(resource);
	return 0;
}

static int Polycore_ResourceManager_hasResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Resource* resource = (Resource*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushboolean(L, inst->hasResource(resource));
	return 1;
}

static int Polycore_ResourceManager_addDirResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	bool recursive;
	if(lua_isboolean(L, 3)) {
		recursive = lua_toboolean(L, 3) != 0;
	} else {
		recursive = true;
	}
	inst->addDirResource(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_addArchive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String path = String(lua_tostring(L, 2));
	inst->addArchive(path);
	return 0;
}

static int Polycore_ResourceManager_removeArchive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String path = String(lua_tostring(L, 2));
	inst->removeArchive(path);
	return 0;
}

static int Polycore_ResourceManager_readFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->readFile(fileName));
	return 1;
}

static int Polycore_ResourceManager_parseTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TSTRING);
	String basePath = String(lua_tostring(L, 4));
	inst->parseTextures(dirPath, recursive, basePath);
	return 0;
}

static int Polycore_ResourceManager_parseMaterials(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	inst->parseMaterials(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	inst->parseShaders(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parsePrograms(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	inst->parsePrograms(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseCubemaps(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	inst->parseCubemaps(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseOthers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	inst->parseOthers(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_getResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int resourceType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String resourceName = String(lua_tostring(L, 3));
	PolyBase *ptrRetVal = (PolyBase*)inst->getResource(resourceType, resourceName);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ResourceManager_getResourceByPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String resourcePath = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getResourceByPath(resourcePath);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ResourceManager_getResources(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int resourceType = lua_tointeger(L, 2);
	std::vector<Resource*> retVector = inst->getResources(resourceType);
	lua_newtable(L);
	for(int i=0; i < retVector.size(); i++) {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)retVector[i];
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static int Polycore_ResourceManager_addShaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	PolycodeShaderModule* module = (PolycodeShaderModule*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addShaderModule(module);
	return 0;
}

static int Polycore_ResourceManager_checkForChangedFiles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->checkForChangedFiles();
	return 0;
}

static int Polycore_ResourceManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int elapsed = lua_tointeger(L, 2);
	inst->Update(elapsed);
	return 0;
}

static int Polycore_delete_ResourceManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ResourceManager*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Scene_get_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->clearColor;
	return 1;
}

static int Polycore_Scene_get_useClearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useClearColor);
	return 1;
}

static int Polycore_Scene_get_ambientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->ambientColor;
	return 1;
}

static int Polycore_Scene_get_fogColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->fogColor;
	return 1;
}

static int Polycore_Scene_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycore_Scene_get_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsChildren);
	return 1;
}

static int Polycore_Scene_set_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->clearColor = *argInst;
	return 0;
}

static int Polycore_Scene_set_useClearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useClearColor = param;
	return 0;
}

static int Polycore_Scene_set_ambientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->ambientColor = *argInst;
	return 0;
}

static int Polycore_Scene_set_fogColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->fogColor = *argInst;
	return 0;
}

static int Polycore_Scene_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

static int Polycore_Scene_set_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsChildren = param;
	return 0;
}

static int Polycore_Scene(lua_State *L) {
	Scene *inst = new Scene();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Scene");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Scene_addEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addEntity(entity);
	return 0;
}

static int Polycore_Scene_addChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addChild(entity);
	return 0;
}

static int Polycore_Scene_removeEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* entity = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeEntity(entity);
	return 0;
}

static int Polycore_Scene_getDefaultCamera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getDefaultCamera();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Scene_getActiveCamera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getActiveCamera();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Scene_setActiveCamera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Camera* camera = (Camera*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setActiveCamera(camera);
	return 0;
}

static int Polycore_Scene_enableLighting(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enable = lua_toboolean(L, 2) != 0;
	inst->enableLighting(enable);
	return 0;
}

static int Polycore_Scene_enableFog(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enable = lua_toboolean(L, 2) != 0;
	inst->enableFog(enable);
	return 0;
}

static int Polycore_Scene_setFogProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int fogMode = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number density = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number startDepth = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number _endDepth = lua_tonumber(L, 6);
	inst->setFogProperties(fogMode, color, density, startDepth, _endDepth);
	return 0;
}

static int Polycore_Scene_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_Scene_setVirtual(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->setVirtual(val);
	return 0;
}

static int Polycore_Scene_isVirtual(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isVirtual());
	return 1;
}

static int Polycore_Scene_isEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isEnabled());
	return 1;
}

static int Polycore_Scene_setEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enabled = lua_toboolean(L, 2) != 0;
	inst->setEnabled(enabled);
	return 0;
}

static int Polycore_Scene_getNumEntities(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumEntities());
	return 1;
}

static int Polycore_Scene_getEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getEntity(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Scene_getEntityAtScreenPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	PolyBase *ptrRetVal = (PolyBase*)inst->getEntityAtScreenPosition(x, y);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Scene_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	Camera* targetCamera;
	if(lua_isuserdata(L, 2)) {
		targetCamera = (Camera*) *((PolyBase**)lua_touserdata(L, 2));
	} else {
		targetCamera = NULL;
	}
	inst->Render(targetCamera);
	return 0;
}

static int Polycore_Scene_RenderDepthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Camera* targetCamera = (Camera*) *((PolyBase**)lua_touserdata(L, 2));
	inst->RenderDepthOnly(targetCamera);
	return 0;
}

static int Polycore_Scene_addLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneLight* light = (SceneLight*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addLight(light);
	return 0;
}

static int Polycore_Scene_removeLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneLight* light = (SceneLight*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeLight(light);
	return 0;
}

static int Polycore_Scene_getNearestLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 pos = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getNearestLight(pos);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Scene_getNumLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumLights());
	return 1;
}

static int Polycore_Scene_getLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getLight(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_Scene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Scene*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneEntity_get_castShadows(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity *inst = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->castShadows);
	return 1;
}

static int Polycore_SceneEntity_get_collisionShapeType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity *inst = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->collisionShapeType);
	return 1;
}

static int Polycore_SceneEntity_set_castShadows(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity *inst = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->castShadows = param;
	return 0;
}

static int Polycore_SceneEntity_set_collisionShapeType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity *inst = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->collisionShapeType = param;
	return 0;
}

static int Polycore_SceneEntity(lua_State *L) {
	SceneEntity *inst = new SceneEntity();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneEntity");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneEntity_testMouseCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity *inst = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushboolean(L, inst->testMouseCollision(x, y));
	return 1;
}

static int Polycore_delete_SceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneEntity*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fontName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int size = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number scale = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int amode = lua_tointeger(L, 5);
	bool premultiplyAlpha;
	if(lua_isboolean(L, 6)) {
		premultiplyAlpha = lua_toboolean(L, 6) != 0;
	} else {
		premultiplyAlpha = false;
	}
	SceneLabel *inst = new SceneLabel(fontName, text, size, scale, amode, premultiplyAlpha);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneLabel");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneLabel_setText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String newText = String(lua_tostring(L, 2));
	inst->setText(newText);
	return 0;
}

static int Polycore_SceneLabel_getLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getLabel();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_SceneLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneLabel*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneLight_get_specularLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->specularLightColor;
	return 1;
}

static int Polycore_SceneLight_get_lightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->lightColor;
	return 1;
}

static int Polycore_SceneLight_get_lightShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->lightShape;
	return 1;
}

static int Polycore_SceneLight_set_specularLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->specularLightColor = *argInst;
	return 0;
}

static int Polycore_SceneLight_set_lightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->lightColor = *argInst;
	return 0;
}

static int Polycore_SceneLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int type = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Scene* parentScene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number intensity = lua_tonumber(L, 3);
	Number constantAttenuation;
	if(lua_isnumber(L, 4)) {
		constantAttenuation = lua_tonumber(L, 4);
	} else {
		constantAttenuation = 1;
	}
	Number linearAttenuation;
	if(lua_isnumber(L, 5)) {
		linearAttenuation = lua_tonumber(L, 5);
	} else {
		linearAttenuation = 1;
	}
	Number quadraticAttenuation;
	if(lua_isnumber(L, 6)) {
		quadraticAttenuation = lua_tonumber(L, 6);
	} else {
		quadraticAttenuation = 1;
	}
	SceneLight *inst = new SceneLight(type, parentScene, intensity, constantAttenuation, linearAttenuation, quadraticAttenuation);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneLight");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneLight_getIntensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getIntensity());
	return 1;
}

static int Polycore_SceneLight_setIntensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newIntensity = lua_tonumber(L, 2);
	inst->setIntensity(newIntensity);
	return 0;
}

static int Polycore_SceneLight_setAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number constantAttenuation = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number linearAttenuation = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number quadraticAttenuation = lua_tonumber(L, 4);
	inst->setAttenuation(constantAttenuation, linearAttenuation, quadraticAttenuation);
	return 0;
}

static int Polycore_SceneLight_getConstantAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getConstantAttenuation());
	return 1;
}

static int Polycore_SceneLight_getLinearAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getLinearAttenuation());
	return 1;
}

static int Polycore_SceneLight_getQuadraticAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getQuadraticAttenuation());
	return 1;
}

static int Polycore_SceneLight_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Polycore_SceneLight_renderDepthMap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Scene* scene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
	inst->renderDepthMap(scene);
	return 0;
}

static int Polycore_SceneLight_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_SceneLight_getLightViewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	 Matrix4  *retInst = new  Matrix4 ();
	*retInst = inst->getLightViewMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Matrix4 ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_SceneLight_getZBufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getZBufferTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneLight_setSpecularLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a = lua_tonumber(L, 5);
	inst->setSpecularLightColor(r, g, b, a);
	return 0;
}

static int Polycore_SceneLight_setDiffuseLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	inst->setDiffuseLightColor(r, g, b);
	return 0;
}

static int Polycore_SceneLight_setLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	Number a;
	if(lua_isnumber(L, 5)) {
		a = lua_tonumber(L, 5);
	} else {
		a = 1.0;
	}
	inst->setLightColor(r, g, b, a);
	return 0;
}

static int Polycore_SceneLight_setSpotlightProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number spotlightCutoff = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number spotlightExponent = lua_tonumber(L, 3);
	inst->setSpotlightProperties(spotlightCutoff, spotlightExponent);
	return 0;
}

static int Polycore_SceneLight_getSpotlightCutoff(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getSpotlightCutoff());
	return 1;
}

static int Polycore_SceneLight_getSpotlightExponent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getSpotlightExponent());
	return 1;
}

static int Polycore_SceneLight_enableShadows(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	Number resolution;
	if(lua_isnumber(L, 3)) {
		resolution = lua_tonumber(L, 3);
	} else {
		resolution = 256;
	}
	inst->enableShadows(val, resolution);
	return 0;
}

static int Polycore_SceneLight_setShadowMapFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fov = lua_tonumber(L, 2);
	inst->setShadowMapFOV(fov);
	return 0;
}

static int Polycore_SceneLight_areShadowsEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->areShadowsEnabled());
	return 1;
}

static int Polycore_SceneLight_getLightType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getLightType());
	return 1;
}

static int Polycore_SceneLight_enableDebugDraw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->enableDebugDraw(val);
	return 0;
}

static int Polycore_SceneLight_setLightImportance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newImportance = lua_tointeger(L, 2);
	inst->setLightImportance(newImportance);
	return 0;
}

static int Polycore_SceneLight_getLightImportance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getLightImportance());
	return 1;
}

static int Polycore_delete_SceneLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneLight*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntity* ent1 = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntity* ent2 = (SceneEntity*) *((PolyBase**)lua_touserdata(L, 2));
	SceneLine *inst = new SceneLine(ent1, ent2);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneLine");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneLine_SceneLineWithPositions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 start = *(Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 _end = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)SceneLine::SceneLineWithPositions(start, _end);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneLine_setStart(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLine *inst = (SceneLine*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 start = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setStart(start);
	return 0;
}

static int Polycore_SceneLine_setEnd(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLine *inst = (SceneLine*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 _end = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setEnd(_end);
	return 0;
}

static int Polycore_SceneLine_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLine *inst = (SceneLine*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_delete_SceneLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneLine*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneManager(lua_State *L) {
	SceneManager *inst = new SceneManager();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneManager");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneManager_addScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Scene* newScene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addScene(newScene);
	return 0;
}

static int Polycore_SceneManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_SceneManager_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_SceneManager_renderVirtual(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->renderVirtual();
	return 0;
}

static int Polycore_SceneManager_removeScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Scene* scene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeScene(scene);
	return 0;
}

static int Polycore_SceneManager_registerRenderTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneRenderTexture* r_enderTexture = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->registerRenderTexture(r_enderTexture);
	return 0;
}

static int Polycore_SceneManager_unregisterRenderTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneRenderTexture* r_enderTexture = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->unregisterRenderTexture(r_enderTexture);
	return 0;
}

static int Polycore_delete_SceneManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneManager*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneMesh_get_lightmapIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->lightmapIndex);
	return 1;
}

static int Polycore_SceneMesh_get_showVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->showVertexNormals);
	return 1;
}

static int Polycore_SceneMesh_get_lineWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->lineWidth);
	return 1;
}

static int Polycore_SceneMesh_get_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->lineSmooth);
	return 1;
}

static int Polycore_SceneMesh_get_ownsMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsMesh);
	return 1;
}

static int Polycore_SceneMesh_get_ownsSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsSkeleton);
	return 1;
}

static int Polycore_SceneMesh_set_lightmapIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->lightmapIndex = param;
	return 0;
}

static int Polycore_SceneMesh_set_showVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->showVertexNormals = param;
	return 0;
}

static int Polycore_SceneMesh_set_lineWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->lineWidth = param;
	return 0;
}

static int Polycore_SceneMesh_set_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->lineSmooth = param;
	return 0;
}

static int Polycore_SceneMesh_set_ownsMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsMesh = param;
	return 0;
}

static int Polycore_SceneMesh_set_ownsSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsSkeleton = param;
	return 0;
}

static int Polycore_SceneMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	SceneMesh *inst = new SceneMesh(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneMesh");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneMesh_SceneMeshFromMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)SceneMesh::SceneMeshFromMesh(mesh);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneMesh_SceneMeshWithType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int meshType = lua_tointeger(L, 1);
	PolyBase *ptrRetVal = (PolyBase*)SceneMesh::SceneMeshWithType(meshType);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneMesh_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_SceneMesh_getLocalShaderOptions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getLocalShaderOptions();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneMesh_getMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getMesh();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneMesh_getTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneMesh_getMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getMaterial();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneMesh_loadTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadTexture(fileName);
	return 0;
}

static int Polycore_SceneMesh_loadSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadSkeleton(fileName);
	return 0;
}

static int Polycore_SceneMesh_setTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setTexture(texture);
	return 0;
}

static int Polycore_SceneMesh_clearMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearMaterial();
	return 0;
}

static int Polycore_SceneMesh_setMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setMaterial(material);
	return 0;
}

static int Polycore_SceneMesh_setMaterialByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String materialName = String(lua_tostring(L, 2));
	inst->setMaterialByName(materialName);
	return 0;
}

static int Polycore_SceneMesh_setMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setMesh(mesh);
	return 0;
}

static int Polycore_SceneMesh_setSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Skeleton* skeleton = (Skeleton*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setSkeleton(skeleton);
	return 0;
}

static int Polycore_SceneMesh_getSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSkeleton();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneMesh_renderMeshLocally(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->renderMeshLocally();
	return 0;
}

static int Polycore_SceneMesh_cacheToVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool cache = lua_toboolean(L, 2) != 0;
	inst->cacheToVertexBuffer(cache);
	return 0;
}

static int Polycore_delete_SceneMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneMesh*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScenePrimitive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int type = lua_tointeger(L, 1);
	Number v1;
	if(lua_isnumber(L, 2)) {
		v1 = lua_tonumber(L, 2);
	} else {
		v1 = 1.0f;
	}
	Number v2;
	if(lua_isnumber(L, 3)) {
		v2 = lua_tonumber(L, 3);
	} else {
		v2 = 1.0f;
	}
	Number v3;
	if(lua_isnumber(L, 4)) {
		v3 = lua_tonumber(L, 4);
	} else {
		v3 = 1.0f;
	}
	Number v4;
	if(lua_isnumber(L, 5)) {
		v4 = lua_tonumber(L, 5);
	} else {
		v4 = 0.0f;
	}
	Number v5;
	if(lua_isnumber(L, 6)) {
		v5 = lua_tonumber(L, 6);
	} else {
		v5 = 0.0f;
	}
	ScenePrimitive *inst = new ScenePrimitive(type, v1, v2, v3, v4, v5);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScenePrimitive");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_delete_ScenePrimitive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScenePrimitive*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneRenderTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene* targetScene = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Camera* targetCamera = (Camera*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int r_enderWidth = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int r_enderHeight = lua_tointeger(L, 4);
	bool floatingPoint;
	if(lua_isboolean(L, 5)) {
		floatingPoint = lua_toboolean(L, 5) != 0;
	} else {
		floatingPoint = false;
	}
	SceneRenderTexture *inst = new SceneRenderTexture(targetScene, targetCamera, r_enderWidth, r_enderHeight, floatingPoint);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneRenderTexture");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneRenderTexture_getTargetTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTargetTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneRenderTexture_getFilterColorBufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getFilterColorBufferTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneRenderTexture_getFilterZBufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getFilterZBufferTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneRenderTexture_resizeRenderTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newWidth = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int newHeight = lua_tointeger(L, 3);
	inst->resizeRenderTexture(newWidth, newHeight);
	return 0;
}

static int Polycore_SceneRenderTexture_getTargetScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTargetScene();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_SceneRenderTexture_getTargetCamera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTargetCamera();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_SceneRenderTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneRenderTexture*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number referenceDistance = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number maxDistance = lua_tonumber(L, 3);
	bool directionalSound;
	if(lua_isboolean(L, 4)) {
		directionalSound = lua_toboolean(L, 4) != 0;
	} else {
		directionalSound = false;
	}
	SceneSound *inst = new SceneSound(fileName, referenceDistance, maxDistance, directionalSound);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneSound");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneSound_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_SceneSound_getSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSound();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_SceneSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneSound*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SceneSoundListener(lua_State *L) {
	SceneSoundListener *inst = new SceneSoundListener();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SceneSoundListener");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SceneSoundListener_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneSoundListener *inst = (SceneSoundListener*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_delete_SceneSoundListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SceneSoundListener*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Screen_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycore_Screen_get_processTouchEventsAsMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->processTouchEventsAsMouse);
	return 1;
}

static int Polycore_Screen_get_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsChildren);
	return 1;
}

static int Polycore_Screen_get_rootEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->rootEntity;
	return 1;
}

static int Polycore_Screen_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

static int Polycore_Screen_set_processTouchEventsAsMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->processTouchEventsAsMouse = param;
	return 0;
}

static int Polycore_Screen_set_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsChildren = param;
	return 0;
}

static int Polycore_Screen_set_rootEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity *argInst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->rootEntity = *argInst;
	return 0;
}

static int Polycore_Screen(lua_State *L) {
	Screen *inst = new Screen();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Screen");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Screen_addChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* newEntity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addChild(newEntity);
	return 0;
}

static int Polycore_Screen_addEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* newEntity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addEntity(newEntity);
	return 0;
}

static int Polycore_Screen_removeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* entityToRemove = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeChild(entityToRemove);
	return 0;
}

static int Polycore_Screen_setScreenOffset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->setScreenOffset(x, y);
	return 0;
}

static int Polycore_Screen_Shutdown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Shutdown();
	return 0;
}

static int Polycore_Screen_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_Screen_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_Screen_setRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Renderer* r_enderer = (Renderer*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setRenderer(r_enderer);
	return 0;
}

static int Polycore_Screen_setNormalizedCoordinates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool newVal = lua_toboolean(L, 2) != 0;
	Number yCoordinateSize;
	if(lua_isnumber(L, 3)) {
		yCoordinateSize = lua_tonumber(L, 3);
	} else {
		yCoordinateSize = 1.0f;
	}
	inst->setNormalizedCoordinates(newVal, yCoordinateSize);
	return 0;
}

static int Polycore_Screen_setScreenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String shaderName = String(lua_tostring(L, 2));
	inst->setScreenShader(shaderName);
	return 0;
}

static int Polycore_Screen_clearScreenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearScreenShader();
	return 0;
}

static int Polycore_Screen_handleInputEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	InputEvent* inputEvent = (InputEvent*) *((PolyBase**)lua_touserdata(L, 2));
	inst->handleInputEvent(inputEvent);
	return 0;
}

static int Polycore_Screen_hasFilterShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->hasFilterShader());
	return 1;
}

static int Polycore_Screen_drawFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	inst->drawFilter();
	return 0;
}

static int Polycore_Screen_usesNormalizedCoordinates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->usesNormalizedCoordinates());
	return 1;
}

static int Polycore_Screen_getYCoordinateSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getYCoordinateSize());
	return 1;
}

static int Polycore_Screen_getLocalShaderOptions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	return 0;
}

static int Polycore_Screen_getScreenShaderMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Screen *inst = (Screen*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getScreenShaderMaterial();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_Screen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Screen*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenEntity_get_hasFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->hasFocus);
	return 1;
}

static int Polycore_ScreenEntity_get_blockMouseInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->blockMouseInput);
	return 1;
}

static int Polycore_ScreenEntity_get_snapToPixels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->snapToPixels);
	return 1;
}

static int Polycore_ScreenEntity_get_processInputEvents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->processInputEvents);
	return 1;
}

static int Polycore_ScreenEntity_get_width(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->width);
	return 1;
}

static int Polycore_ScreenEntity_get_height(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->height);
	return 1;
}

static int Polycore_ScreenEntity_set_hasFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->hasFocus = param;
	return 0;
}

static int Polycore_ScreenEntity_set_blockMouseInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->blockMouseInput = param;
	return 0;
}

static int Polycore_ScreenEntity_set_snapToPixels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->snapToPixels = param;
	return 0;
}

static int Polycore_ScreenEntity_set_processInputEvents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->processInputEvents = param;
	return 0;
}

static int Polycore_ScreenEntity_set_width(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->width = param;
	return 0;
}

static int Polycore_ScreenEntity_set_height(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->height = param;
	return 0;
}

static int Polycore_ScreenEntity(lua_State *L) {
	ScreenEntity *inst = new ScreenEntity();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenEntity");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenEntity_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenEntity_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_ScreenEntity_addEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* newChild = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addEntity(newChild);
	return 0;
}

static int Polycore_ScreenEntity_setPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->setPosition(x, y);
	return 0;
}

static int Polycore_ScreenEntity_setScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->setScale(x, y);
	return 0;
}

static int Polycore_ScreenEntity_setRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number rotation = lua_tonumber(L, 2);
	inst->setRotation(rotation);
	return 0;
}

static int Polycore_ScreenEntity_getRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getRotation());
	return 1;
}

static int Polycore_ScreenEntity__onMouseDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 5);
	MouseEventResult *retInst = new MouseEventResult();
	*retInst = inst->_onMouseDown(x, y, mouseButton, timestamp);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.MouseEventResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity__onMouseUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 5);
	MouseEventResult *retInst = new MouseEventResult();
	*retInst = inst->_onMouseUp(x, y, mouseButton, timestamp);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.MouseEventResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity__onMouseMove(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 4);
	MouseEventResult *retInst = new MouseEventResult();
	*retInst = inst->_onMouseMove(x, y, timestamp);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.MouseEventResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity__onMouseWheelUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 4);
	MouseEventResult *retInst = new MouseEventResult();
	*retInst = inst->_onMouseWheelUp(x, y, timestamp);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.MouseEventResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity__onMouseWheelDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 4);
	MouseEventResult *retInst = new MouseEventResult();
	*retInst = inst->_onMouseWheelDown(x, y, timestamp);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.MouseEventResult");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity_onMouseDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseDown(x, y);
	return 0;
}

static int Polycore_ScreenEntity_onMouseUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseUp(x, y);
	return 0;
}

static int Polycore_ScreenEntity_onMouseMove(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseMove(x, y);
	return 0;
}

static int Polycore_ScreenEntity_onMouseWheelUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseWheelUp(x, y);
	return 0;
}

static int Polycore_ScreenEntity_onMouseWheelDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseWheelDown(x, y);
	return 0;
}

static int Polycore_ScreenEntity__onKeyDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY key = (PolyKEY)lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	wchar_t charCode = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
	inst->_onKeyDown(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity__onKeyUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY key = (PolyKEY)lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	wchar_t charCode = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
	inst->_onKeyUp(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity_getScreenConcatenatedMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getScreenConcatenatedMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity_onKeyDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY key = (PolyKEY)lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	wchar_t charCode = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
	inst->onKeyDown(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity_onKeyUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	PolyKEY key = (PolyKEY)lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TUSERDATA);
	wchar_t charCode = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
	inst->onKeyUp(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity_hitTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushboolean(L, inst->hitTest(x, y));
	return 1;
}

static int Polycore_ScreenEntity_buildPositionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->buildPositionMatrix();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Matrix4");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity_adjustMatrixForChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->adjustMatrixForChildren();
	return 0;
}

static int Polycore_ScreenEntity_getWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getWidth());
	return 1;
}

static int Polycore_ScreenEntity_getHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getHeight());
	return 1;
}

static int Polycore_ScreenEntity_setWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	inst->setWidth(w);
	return 0;
}

static int Polycore_ScreenEntity_setHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number h = lua_tonumber(L, 2);
	inst->setHeight(h);
	return 0;
}

static int Polycore_ScreenEntity_onGainFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->onGainFocus();
	return 0;
}

static int Polycore_ScreenEntity_onLoseFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->onLoseFocus();
	return 0;
}

static int Polycore_ScreenEntity_startDrag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number xOffset = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number yOffset = lua_tonumber(L, 3);
	inst->startDrag(xOffset, yOffset);
	return 0;
}

static int Polycore_ScreenEntity_stopDrag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->stopDrag();
	return 0;
}

static int Polycore_ScreenEntity_setBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newBl_endingMode = lua_tointeger(L, 2);
	inst->setBlendingMode(newBl_endingMode);
	return 0;
}

static int Polycore_ScreenEntity_setPositionMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newPositionMode = lua_tointeger(L, 2);
	inst->setPositionMode(newPositionMode);
	return 0;
}

static int Polycore_ScreenEntity_getPositionMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getPositionMode());
	return 1;
}

static int Polycore_ScreenEntity_setDragLimits(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Polycode::Rectangle rect = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setDragLimits(rect);
	return 0;
}

static int Polycore_ScreenEntity_clearDragLimits(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearDragLimits();
	return 0;
}

static int Polycore_ScreenEntity_setDefaultScreenOptions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool snapToPixels = lua_toboolean(L, 2) != 0;
	inst->setDefaultScreenOptions(snapToPixels);
	return 0;
}

static int Polycore_ScreenEntity_focusChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* child = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->focusChild(child);
	return 0;
}

static int Polycore_ScreenEntity_focusNextChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	inst->focusNextChild();
	return 0;
}

static int Polycore_ScreenEntity_getPosition2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getPosition2D();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity_getScreenPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getScreenPosition();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity_getScale2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getScale2D();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity_isFocusable(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isFocusable());
	return 1;
}

static int Polycore_ScreenEntity_getScreenEntityById(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String id = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->getScreenEntityById(id, recursive);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenEntity_getScreenEntitiesByTag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String tag = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3) != 0;
	std::vector<ScreenEntity*> retVector = inst->getScreenEntitiesByTag(tag, recursive);
	lua_newtable(L);
	for(int i=0; i < retVector.size(); i++) {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)retVector[i];
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static int Polycore_ScreenEntity_getHitbox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	Polycode::Rectangle *retInst = new Polycode::Rectangle();
	*retInst = inst->getHitbox();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Polycode::Rectangle");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenEntity_setHitbox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number height = lua_tonumber(L, 3);
	inst->setHitbox(width, height);
	return 0;
}

static int Polycore_ScreenEntity_isDragged(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity *inst = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isDragged());
	return 1;
}

static int Polycore_delete_ScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenEntity*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenEntityInstance_get_cloneUsingReload(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->cloneUsingReload);
	return 1;
}

static int Polycore_ScreenEntityInstance_get_fileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->fileName.c_str());
	return 1;
}

static int Polycore_ScreenEntityInstance_set_cloneUsingReload(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->cloneUsingReload = param;
	return 0;
}

static int Polycore_ScreenEntityInstance_set_fileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->fileName = param;
	return 0;
}

static int Polycore_ScreenEntityInstance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	ScreenEntityInstance *inst = new ScreenEntityInstance(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenEntityInstance");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenEntityInstance_BlankScreenEntityInstance(lua_State *L) {
	PolyBase *ptrRetVal = (PolyBase*)ScreenEntityInstance::BlankScreenEntityInstance();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenEntityInstance_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenEntityInstance_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_ScreenEntityInstance_reloadEntityInstance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadEntityInstance();
	return 0;
}

static int Polycore_ScreenEntityInstance_clearInstance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearInstance();
	return 0;
}

static int Polycore_ScreenEntityInstance_parseObjectIntoCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	BezierCurve* curve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 3));
	inst->parseObjectIntoCurve(entry, curve);
	return 0;
}

static int Polycore_ScreenEntityInstance_applyScreenShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	ScreenShape* shape = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 3));
	inst->applyScreenShape(entry, shape);
	return 0;
}

static int Polycore_ScreenEntityInstance_loadObjectEntryIntoEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
	ScreenEntity* targetEntity;
	if(lua_isuserdata(L, 3)) {
		targetEntity = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 3));
	} else {
		targetEntity = NULL;
	}
	PolyBase *ptrRetVal = (PolyBase*)inst->loadObjectEntryIntoEntity(entry, targetEntity);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenEntityInstance_loadFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->loadFromFile(fileName));
	return 1;
}

static int Polycore_ScreenEntityInstance_getResourceEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getResourceEntry();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenEntityInstance_getFileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance *inst = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getFileName().c_str());
	return 1;
}

static int Polycore_delete_ScreenEntityInstance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenEntityInstance*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenEntityInstanceResourceEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstance* instance = (ScreenEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	ScreenEntityInstanceResourceEntry *inst = new ScreenEntityInstanceResourceEntry(instance);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenEntityInstanceResourceEntry");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenEntityInstanceResourceEntry_getInstance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstanceResourceEntry *inst = (ScreenEntityInstanceResourceEntry*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getInstance();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenEntityInstanceResourceEntry_reloadResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntityInstanceResourceEntry *inst = (ScreenEntityInstanceResourceEntry*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadResource();
	return 0;
}

static int Polycore_delete_ScreenEntityInstanceResourceEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenEntityInstanceResourceEntry*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenEvent(lua_State *L) {
	ScreenEvent *inst = new ScreenEvent();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenEvent");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_delete_ScreenEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenEvent*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	ScreenImage *inst = new ScreenImage(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenImage");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenImage_ScreenImageWithImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Image* image = (Image*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)ScreenImage::ScreenImageWithImage(image);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenImage_ScreenImageWithTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)ScreenImage::ScreenImageWithTexture(texture);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenImage_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenImage *inst = (ScreenImage*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenImage_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenImage *inst = (ScreenImage*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_ScreenImage_setImageCoordinates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenImage *inst = (ScreenImage*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number width = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number height = lua_tonumber(L, 5);
	inst->setImageCoordinates(x, y, width, height);
	return 0;
}

static int Polycore_ScreenImage_getImageWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenImage *inst = (ScreenImage*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getImageWidth());
	return 1;
}

static int Polycore_ScreenImage_getImageHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenImage *inst = (ScreenImage*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getImageHeight());
	return 1;
}

static int Polycore_delete_ScreenImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenImage*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenLabel_get_positionAtBaseline(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLabel *inst = (ScreenLabel*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->positionAtBaseline);
	return 1;
}

static int Polycore_ScreenLabel_set_positionAtBaseline(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLabel *inst = (ScreenLabel*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->positionAtBaseline = param;
	return 0;
}

static int Polycore_ScreenLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String text = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int size = lua_tointeger(L, 2);
	String fontName;
	if(lua_isstring(L, 3)) {
		fontName = lua_tostring(L, 3);
	} else {
		fontName = "sans";
	}
	int amode;
	if(lua_isnumber(L, 4)) {
		amode = lua_tointeger(L, 4);
	} else {
		amode = 0;
	}
	bool premultiplyAlpha;
	if(lua_isboolean(L, 5)) {
		premultiplyAlpha = lua_toboolean(L, 5) != 0;
	} else {
		premultiplyAlpha = false;
	}
	ScreenLabel *inst = new ScreenLabel(text, size, fontName, amode, premultiplyAlpha);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenLabel");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenLabel_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLabel *inst = (ScreenLabel*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenLabel_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLabel *inst = (ScreenLabel*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_ScreenLabel_setText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLabel *inst = (ScreenLabel*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String newText = String(lua_tostring(L, 2));
	inst->setText(newText);
	return 0;
}

static int Polycore_ScreenLabel_getText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLabel *inst = (ScreenLabel*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getText();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenLabel_getLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLabel *inst = (ScreenLabel*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getLabel();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenLabel_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLabel *inst = (ScreenLabel*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_delete_ScreenLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenLabel*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 start = *(Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 _end = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	ScreenLine *inst = new ScreenLine(start, _end);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenLine");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenLine_setStart(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLine *inst = (ScreenLine*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 point = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setStart(point);
	return 0;
}

static int Polycore_ScreenLine_setEnd(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLine *inst = (ScreenLine*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 point = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setEnd(point);
	return 0;
}

static int Polycore_ScreenLine_ScreenLineBetweenEntities(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenEntity* target1 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ScreenEntity* target2 = (ScreenEntity*) *((PolyBase**)lua_touserdata(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)ScreenLine::ScreenLineBetweenEntities(target1, target2);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenLine_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLine *inst = (ScreenLine*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_ScreenLine_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLine *inst = (ScreenLine*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_ScreenLine_setLineWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenLine *inst = (ScreenLine*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	inst->setLineWidth(width);
	return 0;
}

static int Polycore_delete_ScreenLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenLine*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenManager_get_drawScreensFirst(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenManager *inst = (ScreenManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->drawScreensFirst);
	return 1;
}

static int Polycore_ScreenManager_set_drawScreensFirst(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenManager *inst = (ScreenManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->drawScreensFirst = param;
	return 0;
}

static int Polycore_ScreenManager(lua_State *L) {
	ScreenManager *inst = new ScreenManager();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenManager");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenManager_removeScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenManager *inst = (ScreenManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Screen* screen = (Screen*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeScreen(screen);
	return 0;
}

static int Polycore_ScreenManager_addScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenManager *inst = (ScreenManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Screen* screen = (Screen*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addScreen(screen);
	return 0;
}

static int Polycore_ScreenManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenManager *inst = (ScreenManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_ScreenManager_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenManager *inst = (ScreenManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_delete_ScreenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenManager*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenMesh_get_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->lineSmooth);
	return 1;
}

static int Polycore_ScreenMesh_get_lineWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->lineWidth);
	return 1;
}

static int Polycore_ScreenMesh_get_ownsMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsMesh);
	return 1;
}

static int Polycore_ScreenMesh_set_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->lineSmooth = param;
	return 0;
}

static int Polycore_ScreenMesh_set_lineWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->lineWidth = param;
	return 0;
}

static int Polycore_ScreenMesh_set_ownsMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsMesh = param;
	return 0;
}

static int Polycore_ScreenMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	ScreenMesh *inst = new ScreenMesh(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenMesh");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenMesh_ScreenMeshWithType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int meshType = lua_tointeger(L, 1);
	PolyBase *ptrRetVal = (PolyBase*)ScreenMesh::ScreenMeshWithType(meshType);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenMesh_ScreenMeshWithMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)ScreenMesh::ScreenMeshWithMesh(mesh);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenMesh_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_ScreenMesh_getMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getMesh();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenMesh_getTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenMesh_loadTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadTexture(fileName);
	return 0;
}

static int Polycore_ScreenMesh_setTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setTexture(texture);
	return 0;
}

static int Polycore_ScreenMesh_setMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setMaterial(material);
	return 0;
}

static int Polycore_ScreenMesh_setMaterialByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String materialName = String(lua_tostring(L, 2));
	inst->setMaterialByName(materialName);
	return 0;
}

static int Polycore_ScreenMesh_clearMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearMaterial();
	return 0;
}

static int Polycore_ScreenMesh_getMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getMaterial();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenMesh_getLocalShaderOptions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getLocalShaderOptions();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenMesh_updateHitBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenMesh *inst = (ScreenMesh*) *((PolyBase**)lua_touserdata(L, 1));
	inst->updateHitBox();
	return 0;
}

static int Polycore_delete_ScreenMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenMesh*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenShape_get_strokeEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->strokeEnabled);
	return 1;
}

static int Polycore_ScreenShape_get_strokeColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->strokeColor;
	return 1;
}

static int Polycore_ScreenShape_get_strokeWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->strokeWidth);
	return 1;
}

static int Polycore_ScreenShape_set_strokeEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->strokeEnabled = param;
	return 0;
}

static int Polycore_ScreenShape_set_strokeColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->strokeColor = *argInst;
	return 0;
}

static int Polycore_ScreenShape_set_strokeWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->strokeWidth = param;
	return 0;
}

static int Polycore_ScreenShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int shapeType = lua_tointeger(L, 1);
	Number option1;
	if(lua_isnumber(L, 2)) {
		option1 = lua_tonumber(L, 2);
	} else {
		option1 = 0;
	}
	Number option2;
	if(lua_isnumber(L, 3)) {
		option2 = lua_tonumber(L, 3);
	} else {
		option2 = 0;
	}
	Number option3;
	if(lua_isnumber(L, 4)) {
		option3 = lua_tonumber(L, 4);
	} else {
		option3 = 0;
	}
	Number option4;
	if(lua_isnumber(L, 5)) {
		option4 = lua_tonumber(L, 5);
	} else {
		option4 = 0;
	}
	ScreenShape *inst = new ScreenShape(shapeType, option1, option2, option3, option4);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenShape");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenShape_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenShape_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_ScreenShape_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Render();
	return 0;
}

static int Polycore_ScreenShape_setStrokeColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a = lua_tonumber(L, 5);
	inst->setStrokeColor(r, g, b, a);
	return 0;
}

static int Polycore_ScreenShape_setStrokeWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	inst->setStrokeWidth(width);
	return 0;
}

static int Polycore_ScreenShape_setGradient(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r1 = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g1 = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b1 = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a1 = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number r2 = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number g2 = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number b2 = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TNUMBER);
	Number a2 = lua_tonumber(L, 9);
	inst->setGradient(r1, g1, b1, a1, r2, g2, b2, a2);
	return 0;
}

static int Polycore_ScreenShape_clearGradient(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	inst->clearGradient();
	return 0;
}

static int Polycore_ScreenShape_getShapeType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getShapeType());
	return 1;
}

static int Polycore_ScreenShape_setShapeType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int type = lua_tointeger(L, 2);
	inst->setShapeType(type);
	return 0;
}

static int Polycore_ScreenShape_setShapeSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newWidth = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number newHeight = lua_tonumber(L, 3);
	inst->setShapeSize(newWidth, newHeight);
	return 0;
}

static int Polycore_ScreenShape_buildShapeMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenShape *inst = (ScreenShape*) *((PolyBase**)lua_touserdata(L, 1));
	inst->buildShapeMesh();
	return 0;
}

static int Polycore_delete_ScreenShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenShape*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenSoundListener(lua_State *L) {
	ScreenSoundListener *inst = new ScreenSoundListener();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenSoundListener");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenSoundListener_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSoundListener *inst = (ScreenSoundListener*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_delete_ScreenSoundListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenSoundListener*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number referenceDistance = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number maxDistance = lua_tonumber(L, 3);
	ScreenSound *inst = new ScreenSound(fileName, referenceDistance, maxDistance);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenSound");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenSound_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSound *inst = (ScreenSound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenSound_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSound *inst = (ScreenSound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_ScreenSound_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSound *inst = (ScreenSound*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_ScreenSound_getSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSound *inst = (ScreenSound*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSound();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_ScreenSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenSound*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenSpriteResourceEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite* sprite = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	ScreenSpriteResourceEntry *inst = new ScreenSpriteResourceEntry(sprite);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenSpriteResourceEntry");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenSpriteResourceEntry_getSprite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSpriteResourceEntry *inst = (ScreenSpriteResourceEntry*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getSprite();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenSpriteResourceEntry_reloadResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSpriteResourceEntry *inst = (ScreenSpriteResourceEntry*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadResource();
	return 0;
}

static int Polycore_delete_ScreenSpriteResourceEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenSpriteResourceEntry*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ScreenSprite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	ScreenSprite *inst = new ScreenSprite(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ScreenSprite");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ScreenSprite_ScreenSpriteFromImageFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number spriteWidth = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number spriteHeight = lua_tonumber(L, 3);
	PolyBase *ptrRetVal = (PolyBase*)ScreenSprite::ScreenSpriteFromImageFile(fileName, spriteWidth, spriteHeight);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenSprite_Clone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
	PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenSprite_applyClone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool deepClone = lua_toboolean(L, 3) != 0;
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
	inst->applyClone(clone, deepClone, ignoreEditorOnly);
	return 0;
}

static int Polycore_ScreenSprite_addAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String frames = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 4);
	PolyBase *ptrRetVal = (PolyBase*)inst->addAnimation(name, frames, speed);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenSprite_showFrame(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int frameIndex = lua_tointeger(L, 2);
	inst->showFrame(frameIndex);
	return 0;
}

static int Polycore_ScreenSprite_playAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int startFrame = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool once = lua_toboolean(L, 4) != 0;
	inst->playAnimation(name, startFrame, once);
	return 0;
}

static int Polycore_ScreenSprite_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_ScreenSprite_setSpriteSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number spriteWidth = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number spriteHeight = lua_tonumber(L, 3);
	inst->setSpriteSize(spriteWidth, spriteHeight);
	return 0;
}

static int Polycore_ScreenSprite_getSpriteSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getSpriteSize();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_ScreenSprite_getFileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getFileName().c_str());
	return 1;
}

static int Polycore_ScreenSprite_recalculateSpriteDimensions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	inst->recalculateSpriteDimensions();
	return 0;
}

static int Polycore_ScreenSprite_loadFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->loadFromFile(fileName));
	return 1;
}

static int Polycore_ScreenSprite_reloadSprite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadSprite();
	return 0;
}

static int Polycore_ScreenSprite_Pause(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->Pause(val);
	return 0;
}

static int Polycore_ScreenSprite_getNumAnimations(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumAnimations());
	return 1;
}

static int Polycore_ScreenSprite_getAnimationAtIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getAnimationAtIndex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenSprite_getCurrentAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getCurrentAnimation();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ScreenSprite_getCurrentAnimationFrame(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getCurrentAnimationFrame());
	return 1;
}

static int Polycore_ScreenSprite_isCurrentAnimationFinished(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isCurrentAnimationFinished());
	return 1;
}

static int Polycore_ScreenSprite_updateSprite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	inst->updateSprite();
	return 0;
}

static int Polycore_ScreenSprite_getResourceEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScreenSprite *inst = (ScreenSprite*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getResourceEntry();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_ScreenSprite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ScreenSprite*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Shader_get_numSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->numSpotLights);
	return 1;
}

static int Polycore_Shader_get_numAreaLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->numAreaLights);
	return 1;
}

static int Polycore_Shader_get_screenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->screenShader);
	return 1;
}

static int Polycore_Shader_get_vp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->vp;
	return 1;
}

static int Polycore_Shader_get_fp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->fp;
	return 1;
}

static int Polycore_Shader_set_numSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->numSpotLights = param;
	return 0;
}

static int Polycore_Shader_set_numAreaLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->numAreaLights = param;
	return 0;
}

static int Polycore_Shader_set_screenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->screenShader = param;
	return 0;
}

static int Polycore_Shader_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Polycore_Shader_setName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	inst->setName(name);
	return 0;
}

static int Polycore_Shader_getName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getName();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Shader_createBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->createBinding();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Shader_reload(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reload();
	return 0;
}

static int Polycore_Shader_getExpectedParamType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	lua_pushinteger(L, inst->getExpectedParamType(name));
	return 1;
}

static int Polycore_Shader_setVertexProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ShaderProgram* vp = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setVertexProgram(vp);
	return 0;
}

static int Polycore_Shader_setFragmentProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ShaderProgram* fp = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setFragmentProgram(fp);
	return 0;
}

static int Polycore_delete_Shader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Shader*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_LocalShaderParam_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycore_LocalShaderParam_get_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->data;
	return 1;
}

static int Polycore_LocalShaderParam_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycore_LocalShaderParam_getNumber(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getNumber());
	return 1;
}

static int Polycore_LocalShaderParam_getVector2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getVector2();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_LocalShaderParam_getVector3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	Vector3 *retInst = new Vector3();
	*retInst = inst->getVector3();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_LocalShaderParam_getColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	Color *retInst = new Color();
	*retInst = inst->getColor();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Color");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_LocalShaderParam_setNumber(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	inst->setNumber(x);
	return 0;
}

static int Polycore_LocalShaderParam_setVector2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 x = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setVector2(x);
	return 0;
}

static int Polycore_LocalShaderParam_setVector3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 x = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setVector3(x);
	return 0;
}

static int Polycore_LocalShaderParam_setColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color x = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setColor(x);
	return 0;
}

static int Polycore_delete_LocalShaderParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((LocalShaderParam*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ShaderProgram_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderProgram *inst = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycore_ShaderProgram_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderProgram *inst = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycore_ShaderProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int type = lua_tointeger(L, 1);
	ShaderProgram *inst = new ShaderProgram(type);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ShaderProgram");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ShaderProgram_reloadProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderProgram *inst = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadProgram();
	return 0;
}

static int Polycore_ShaderProgram_reloadResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderProgram *inst = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadResource();
	return 0;
}

static int Polycore_delete_ShaderProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ShaderProgram*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_ShaderBinding_get_shader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->shader;
	return 1;
}

static int Polycore_ShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	ShaderBinding *inst = new ShaderBinding(shader);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.ShaderBinding");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_ShaderBinding_getTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTexture(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_getCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getCubemap(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_clearTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	inst->clearTexture(name);
	return 0;
}

static int Polycore_ShaderBinding_clearCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	inst->clearCubemap(name);
	return 0;
}

static int Polycore_ShaderBinding_addTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
	inst->addTexture(name, texture);
	return 0;
}

static int Polycore_ShaderBinding_addParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int type = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String name = String(lua_tostring(L, 3));
	PolyBase *ptrRetVal = (PolyBase*)inst->addParam(type, name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_addCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Cubemap* cubemap = (Cubemap*) *((PolyBase**)lua_touserdata(L, 3));
	inst->addCubemap(name, cubemap);
	return 0;
}

static int Polycore_ShaderBinding_getNumLocalParams(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumLocalParams());
	return 1;
}

static int Polycore_ShaderBinding_getLocalParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getLocalParam(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_getLocalParamByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getLocalParamByName(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_addRenderTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	RenderTargetBinding* binding = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addRenderTargetBinding(binding);
	return 0;
}

static int Polycore_ShaderBinding_removeRenderTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	RenderTargetBinding* binding = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeRenderTargetBinding(binding);
	return 0;
}

static int Polycore_ShaderBinding_getNumRenderTargetBindings(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumRenderTargetBindings());
	return 1;
}

static int Polycore_ShaderBinding_getRenderTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getRenderTargetBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_getNumInTargetBindings(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumInTargetBindings());
	return 1;
}

static int Polycore_ShaderBinding_getInTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getInTargetBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_getNumColorTargetBindings(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumColorTargetBindings());
	return 1;
}

static int Polycore_ShaderBinding_getColorTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getColorTargetBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_getNumDepthTargetBindings(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumDepthTargetBindings());
	return 1;
}

static int Polycore_ShaderBinding_getDepthTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getDepthTargetBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_getNumOutTargetBindings(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumOutTargetBindings());
	return 1;
}

static int Polycore_ShaderBinding_getOutTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getOutTargetBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_ShaderBinding_addLocalParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	void* ptr = (void*) *((PolyBase**)lua_touserdata(L, 3));
	PolyBase *ptrRetVal = (PolyBase*)inst->addLocalParam(name, ptr);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_ShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((ShaderBinding*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SkeletonAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String name = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number duration = lua_tonumber(L, 2);
	SkeletonAnimation *inst = new SkeletonAnimation(name, duration);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SkeletonAnimation");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SkeletonAnimation_addBoneTrack(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BoneTrack* boneTrack = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addBoneTrack(boneTrack);
	return 0;
}

static int Polycore_SkeletonAnimation_getName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
	 String  *retInst = new  String ();
	*retInst = inst->getName();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. String ");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_SkeletonAnimation_Play(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool once = lua_toboolean(L, 2) != 0;
	inst->Play(once);
	return 0;
}

static int Polycore_SkeletonAnimation_Stop(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Stop();
	return 0;
}

static int Polycore_SkeletonAnimation_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_SkeletonAnimation_setSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 2);
	inst->setSpeed(speed);
	return 0;
}

static int Polycore_delete_SkeletonAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SkeletonAnimation*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Skeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	Skeleton *inst = new Skeleton(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Skeleton");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Skeleton_BlankSkeleton(lua_State *L) {
	PolyBase *ptrRetVal = (PolyBase*)Skeleton::BlankSkeleton();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Skeleton_loadSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadSkeleton(fileName);
	return 0;
}

static int Polycore_Skeleton_playAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String animName = String(lua_tostring(L, 2));
	bool once;
	if(lua_isboolean(L, 3)) {
		once = lua_toboolean(L, 3) != 0;
	} else {
		once = false;
	}
	inst->playAnimation(animName, once);
	return 0;
}

static int Polycore_Skeleton_playAnimationByIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	bool once;
	if(lua_isboolean(L, 3)) {
		once = lua_toboolean(L, 3) != 0;
	} else {
		once = false;
	}
	inst->playAnimationByIndex(index, once);
	return 0;
}

static int Polycore_Skeleton_addAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 3));
	inst->addAnimation(name, fileName);
	return 0;
}

static int Polycore_Skeleton_getAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getAnimation(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Skeleton_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_Skeleton_getBoneByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	PolyBase *ptrRetVal = (PolyBase*)inst->getBoneByName(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Skeleton_bonesVisible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2) != 0;
	inst->bonesVisible(val);
	return 0;
}

static int Polycore_Skeleton_enableBoneLabels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String labelFont = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number size = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number scale = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TUSERDATA);
	Color labelColor = *(Color*) *((PolyBase**)lua_touserdata(L, 5));
	inst->enableBoneLabels(labelFont, size, scale, labelColor);
	return 0;
}

static int Polycore_Skeleton_getNumBones(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumBones());
	return 1;
}

static int Polycore_Skeleton_getBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getBone(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Skeleton_getCurrentAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getCurrentAnimation();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_delete_Skeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Skeleton*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_BoneTrack_get_scaleX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->scaleX;
	return 1;
}

static int Polycore_BoneTrack_get_scaleY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->scaleY;
	return 1;
}

static int Polycore_BoneTrack_get_scaleZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->scaleZ;
	return 1;
}

static int Polycore_BoneTrack_get_QuatW(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->QuatW;
	return 1;
}

static int Polycore_BoneTrack_get_QuatX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->QuatX;
	return 1;
}

static int Polycore_BoneTrack_get_QuatY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->QuatY;
	return 1;
}

static int Polycore_BoneTrack_get_QuatZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->QuatZ;
	return 1;
}

static int Polycore_BoneTrack_get_LocX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->LocX;
	return 1;
}

static int Polycore_BoneTrack_get_LocY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->LocY;
	return 1;
}

static int Polycore_BoneTrack_get_LocZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->LocZ;
	return 1;
}

static int Polycore_BoneTrack_get_LocXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->LocXVec;
	return 1;
}

static int Polycore_BoneTrack_get_LocYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->LocYVec;
	return 1;
}

static int Polycore_BoneTrack_get_LocZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->LocZVec;
	return 1;
}

static int Polycore_BoneTrack_get_ScaleXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->ScaleXVec;
	return 1;
}

static int Polycore_BoneTrack_get_ScaleYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->ScaleYVec;
	return 1;
}

static int Polycore_BoneTrack_get_ScaleZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->ScaleZVec;
	return 1;
}

static int Polycore_BoneTrack_get_boneQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->boneQuat;
	return 1;
}

static int Polycore_BoneTrack_get_quatTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->quatTween;
	return 1;
}

static int Polycore_BoneTrack_get_QuatWVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->QuatWVec;
	return 1;
}

static int Polycore_BoneTrack_get_QuatXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->QuatXVec;
	return 1;
}

static int Polycore_BoneTrack_get_QuatYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->QuatYVec;
	return 1;
}

static int Polycore_BoneTrack_get_QuatZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->QuatZVec;
	return 1;
}

static int Polycore_BoneTrack_set_LocXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->LocXVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_LocYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->LocYVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_LocZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->LocZVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_ScaleXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->ScaleXVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_ScaleYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->ScaleYVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_ScaleZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->ScaleZVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_boneQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion *argInst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	inst->boneQuat = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_QuatWVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->QuatWVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_QuatXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->QuatXVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_QuatYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->QuatYVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack_set_QuatZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->QuatZVec = *argInst;
	return 0;
}

static int Polycore_BoneTrack(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number length = lua_tonumber(L, 2);
	BoneTrack *inst = new BoneTrack(bone, length);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.BoneTrack");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_BoneTrack_Play(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	bool once;
	if(lua_isboolean(L, 2)) {
		once = lua_toboolean(L, 2) != 0;
	} else {
		once = false;
	}
	inst->Play(once);
	return 0;
}

static int Polycore_BoneTrack_Stop(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Stop();
	return 0;
}

static int Polycore_BoneTrack_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_BoneTrack_setSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 2);
	inst->setSpeed(speed);
	return 0;
}

static int Polycore_delete_BoneTrack(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((BoneTrack*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Sound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	Sound *inst = new Sound(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Sound");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Sound_loadFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadFile(fileName);
	return 0;
}

static int Polycore_Sound_reloadProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadProperties();
	return 0;
}

static int Polycore_Sound_Play(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	bool loop;
	if(lua_isboolean(L, 2)) {
		loop = lua_toboolean(L, 2) != 0;
	} else {
		loop = false;
	}
	inst->Play(loop);
	return 0;
}

static int Polycore_Sound_Stop(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Stop();
	return 0;
}

static int Polycore_Sound_setVolume(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newVolume = lua_tonumber(L, 2);
	inst->setVolume(newVolume);
	return 0;
}

static int Polycore_Sound_getVolume(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getVolume());
	return 1;
}

static int Polycore_Sound_setPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newPitch = lua_tonumber(L, 2);
	inst->setPitch(newPitch);
	return 0;
}

static int Polycore_Sound_getPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getPitch());
	return 1;
}

static int Polycore_Sound_isPlaying(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isPlaying());
	return 1;
}

static int Polycore_Sound_setIsPositional(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool isPositional = lua_toboolean(L, 2) != 0;
	inst->setIsPositional(isPositional);
	return 0;
}

static int Polycore_Sound_setSoundPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setSoundPosition(position);
	return 0;
}

static int Polycore_Sound_setSoundVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 velocity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setSoundVelocity(velocity);
	return 0;
}

static int Polycore_Sound_setSoundDirection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setSoundDirection(direction);
	return 0;
}

static int Polycore_Sound_setOffset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int off = lua_tointeger(L, 2);
	inst->setOffset(off);
	return 0;
}

static int Polycore_Sound_getFileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->getFileName().c_str());
	return 1;
}

static int Polycore_Sound_getPlaybackDuration(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getPlaybackDuration());
	return 1;
}

static int Polycore_Sound_getPlaybackTime(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getPlaybackTime());
	return 1;
}

static int Polycore_Sound_seekTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number time = lua_tonumber(L, 2);
	inst->seekTo(time);
	return 0;
}

static int Polycore_Sound_getOffset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getOffset());
	return 1;
}

static int Polycore_Sound_getSampleLength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getSampleLength());
	return 1;
}

static int Polycore_Sound_setPositionalProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number referenceDistance = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number maxDistance = lua_tonumber(L, 3);
	inst->setPositionalProperties(referenceDistance, maxDistance);
	return 0;
}

static int Polycore_Sound_setReferenceDistance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number referenceDistance = lua_tonumber(L, 2);
	inst->setReferenceDistance(referenceDistance);
	return 0;
}

static int Polycore_Sound_setMaxDistance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number maxDistance = lua_tonumber(L, 2);
	inst->setMaxDistance(maxDistance);
	return 0;
}

static int Polycore_Sound_getReferenceDistance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getReferenceDistance());
	return 1;
}

static int Polycore_Sound_getMaxDistance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getMaxDistance());
	return 1;
}

static int Polycore_Sound_loadBytes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char* data = (char*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int size = lua_tointeger(L, 3);
	int channels;
	if(lua_isnumber(L, 4)) {
		channels = lua_tointeger(L, 4);
	} else {
		channels = 1;
	}
	luaL_checktype(L, 5, LUA_TUSERDATA);
	ALsizei freq = *(ALsizei*) *((PolyBase**)lua_touserdata(L, 5));
	int bps;
	if(lua_isnumber(L, 6)) {
		bps = lua_tointeger(L, 6);
	} else {
		bps = 16;
	}
	ALuint *retInst = new ALuint();
	*retInst = inst->loadBytes(data, size, channels, freq, bps);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.ALuint");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Sound_loadWAV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	ALuint *retInst = new ALuint();
	*retInst = inst->loadWAV(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.ALuint");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Sound_loadOGG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	ALuint *retInst = new ALuint();
	*retInst = inst->loadOGG(fileName);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.ALuint");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Sound_GenSource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ALuint buffer = *(ALuint*) *((PolyBase**)lua_touserdata(L, 2));
	ALuint *retInst = new ALuint();
	*retInst = inst->GenSource(buffer);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.ALuint");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Sound_checkALError(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String operation = String(lua_tostring(L, 2));
	ALenum *retInst = new ALenum();
	*retInst = inst->checkALError(operation);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.ALenum");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Sound_soundError(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String err = String(lua_tostring(L, 2));
	inst->soundError(err);
	return 0;
}

static int Polycore_Sound_soundCheck(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool result = lua_toboolean(L, 2) != 0;
	luaL_checktype(L, 3, LUA_TSTRING);
	String err = String(lua_tostring(L, 3));
	inst->soundCheck(result, err);
	return 0;
}

static int Polycore_delete_Sound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Sound*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_SoundManager(lua_State *L) {
	SoundManager *inst = new SoundManager();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.SoundManager");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_SoundManager_setListenerPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setListenerPosition(position);
	return 0;
}

static int Polycore_SoundManager_setListenerOrientation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 orientation = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
	inst->setListenerOrientation(orientation, upVector);
	return 0;
}

static int Polycore_SoundManager_initAL(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->initAL();
	return 0;
}

static int Polycore_SoundManager_setGlobalVolume(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number globalVolume = lua_tonumber(L, 2);
	inst->setGlobalVolume(globalVolume);
	return 0;
}

static int Polycore_delete_SoundManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((SoundManager*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_String_get_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->contents;
	return 1;
}

static int Polycore_String_get_w_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->w_contents;
	return 1;
}

static int Polycore_String_set_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	string *argInst = (string*) *((PolyBase**)lua_touserdata(L, 2));
	inst->contents = *argInst;
	return 0;
}

static int Polycore_String_set_w_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	wstring *argInst = (wstring*) *((PolyBase**)lua_touserdata(L, 2));
	inst->w_contents = *argInst;
	return 0;
}

static int Polycore_String(lua_State *L) {
	String *inst = new String();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.String");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_String_size(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->size());
	return 1;
}

static int Polycore_String_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->length());
	return 1;
}

static int Polycore_String_substr(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	size_t n = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushstring(L, inst->substr(pos, n).c_str());
	return 1;
}

static int Polycore_String_rfind(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushinteger(L, inst->rfind(str, pos));
	return 1;
}

static int Polycore_String_find(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushinteger(L, inst->find(str, pos));
	return 1;
}

static int Polycore_String_find_last_of(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushinteger(L, inst->find_last_of(str, pos));
	return 1;
}

static int Polycore_String_find_first_of(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TUSERDATA);
	size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
	lua_pushinteger(L, inst->find_first_of(str, pos));
	return 1;
}

static int Polycore_String_toLowerCase(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->toLowerCase().c_str());
	return 1;
}

static int Polycore_String_toUpperCase(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->toUpperCase().c_str());
	return 1;
}

static int Polycore_String_split(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String delim = String(lua_tostring(L, 2));
	return 0;
}

static int Polycore_String_replace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String what = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String withWhat = String(lua_tostring(L, 3));
	lua_pushstring(L, inst->replace(what, withWhat).c_str());
	return 1;
}

static int Polycore_String_NumberToString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number value = lua_tonumber(L, 1);
	int precision;
	if(lua_isnumber(L, 2)) {
		precision = lua_tointeger(L, 2);
	} else {
		precision = 2;
	}
	lua_pushstring(L, String::NumberToString(value, precision).c_str());
	return 1;
}

static int Polycore_String_IntToString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int value = lua_tointeger(L, 1);
	lua_pushstring(L, String::IntToString(value).c_str());
	return 1;
}

static int Polycore_String_c_str(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->c_str();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_String_getDataWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getDataWithEncoding(encoding);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_String_getWDataWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getWDataWithEncoding(encoding);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_String_append(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char c = *(char*) *((PolyBase**)lua_touserdata(L, 2));
	inst->append(c);
	return 0;
}

static int Polycore_String_getDataSizeWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	lua_pushinteger(L, inst->getDataSizeWithEncoding(encoding));
	return 1;
}

static int Polycore_String_setDataWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char* data = (char*) *((PolyBase**)lua_touserdata(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 3);
	inst->setDataWithEncoding(data, encoding);
	return 0;
}

static int Polycore_String_isNumber(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isNumber());
	return 1;
}

static int Polycore_delete_String(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((String*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Texture_get_scrollSpeedX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->scrollSpeedX);
	return 1;
}

static int Polycore_Texture_get_scrollSpeedY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->scrollSpeedY);
	return 1;
}

static int Polycore_Texture_get_clamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->clamp);
	return 1;
}

static int Polycore_Texture_get_textureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst->textureData;
	return 1;
}

static int Polycore_Texture_set_scrollSpeedX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->scrollSpeedX = param;
	return 0;
}

static int Polycore_Texture_set_scrollSpeedY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->scrollSpeedY = param;
	return 0;
}

static int Polycore_Texture_set_clamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->clamp = param;
	return 0;
}

static int Polycore_Texture_reloadResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	inst->reloadResource();
	return 0;
}

static int Polycore_Texture_setTextureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char* data = (char*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setTextureData(data);
	return 0;
}

static int Polycore_Texture_recreateFromImageData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	inst->recreateFromImageData();
	return 0;
}

static int Polycore_Texture_getScrollOffsetX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getScrollOffsetX());
	return 1;
}

static int Polycore_Texture_getScrollOffsetY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getScrollOffsetY());
	return 1;
}

static int Polycore_Texture_setImageData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Image* data = (Image*) *((PolyBase**)lua_touserdata(L, 2));
	inst->setImageData(data);
	return 0;
}

static int Polycore_Texture_updateScroll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int elapsed = lua_tointeger(L, 2);
	inst->updateScroll(elapsed);
	return 0;
}

static int Polycore_Texture_getTextureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase *ptrRetVal = (PolyBase*)inst->getTextureData();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Texture_getWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getWidth());
	return 1;
}

static int Polycore_Texture_getHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getHeight());
	return 1;
}

static int Polycore_delete_Texture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Texture*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Timer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TBOOLEAN);
	bool triggerMode = lua_toboolean(L, 1) != 0;
	luaL_checktype(L, 2, LUA_TNUMBER);
	int msecs = lua_tointeger(L, 2);
	Timer *inst = new Timer(triggerMode, msecs);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Timer");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Timer_Pause(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool paused = lua_toboolean(L, 2) != 0;
	inst->Pause(paused);
	return 0;
}

static int Polycore_Timer_isPaused(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isPaused());
	return 1;
}

static int Polycore_Timer_getTicks(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getTicks());
	return 1;
}

static int Polycore_Timer_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 2);
	inst->Update(ticks);
	return 0;
}

static int Polycore_Timer_Reset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Reset();
	return 0;
}

static int Polycore_Timer_hasElapsed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->hasElapsed());
	return 1;
}

static int Polycore_Timer_getElapsedf(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->getElapsedf());
	return 1;
}

static int Polycore_Timer_setTimerInterval(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int msecs = lua_tointeger(L, 2);
	inst->setTimerInterval(msecs);
	return 0;
}

static int Polycore_delete_Timer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Timer*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_TimerManager(lua_State *L) {
	TimerManager *inst = new TimerManager();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.TimerManager");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_TimerManager_removeTimer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimerManager *inst = (TimerManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Timer* timer = (Timer*) *((PolyBase**)lua_touserdata(L, 2));
	inst->removeTimer(timer);
	return 0;
}

static int Polycore_TimerManager_addTimer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimerManager *inst = (TimerManager*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Timer* timer = (Timer*) *((PolyBase**)lua_touserdata(L, 2));
	inst->addTimer(timer);
	return 0;
}

static int Polycore_TimerManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimerManager *inst = (TimerManager*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Update();
	return 0;
}

static int Polycore_delete_TimerManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((TimerManager*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Vector2_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycore_Vector2_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycore_Vector2_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycore_Vector2_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycore_Vector2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number x = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number y = lua_tonumber(L, 2);
	Vector2 *inst = new Vector2(x, y);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Vector2_set(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->set(x, y);
	return 0;
}

static int Polycore_Vector2_distance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 vec2 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushnumber(L, inst->distance(vec2));
	return 1;
}

static int Polycore_Vector2_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->length());
	return 1;
}

static int Polycore_Vector2_dot(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 u = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushnumber(L, inst->dot(u));
	return 1;
}

static int Polycore_Vector2_crossProduct(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 vec2 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushnumber(L, inst->crossProduct(vec2));
	return 1;
}

static int Polycore_Vector2_angle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 vec2 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushnumber(L, inst->angle(vec2));
	return 1;
}

static int Polycore_Vector2_Normalize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Normalize();
	return 0;
}

static int Polycore_delete_Vector2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Vector2*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Vector3_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycore_Vector3_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycore_Vector3_get_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->z);
	return 1;
}

static int Polycore_Vector3_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycore_Vector3_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycore_Vector3_set_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->z = param;
	return 0;
}

static int Polycore_Vector3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number x = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number y = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number z = lua_tonumber(L, 3);
	Vector3 *inst = new Vector3(x, y, z);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Vector3");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Vector3_set(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->set(x, y, z);
	return 0;
}

static int Polycore_Vector3_distance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 vec2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushnumber(L, inst->distance(vec2));
	return 1;
}

static int Polycore_Vector3_angleBetween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 dest = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushnumber(L, inst->angleBetween(dest));
	return 1;
}

static int Polycore_Vector3_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->length());
	return 1;
}

static int Polycore_Vector3_dot(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 u = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	lua_pushnumber(L, inst->dot(u));
	return 1;
}

static int Polycore_Vector3_crossProduct(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 vec2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->crossProduct(vec2);
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore. Vector3");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Vector3_Normalize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	inst->Normalize();
	return 0;
}

static int Polycore_delete_Vector3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Vector3*) *inst);
	*inst = NULL;
	return 0;
}

static int Polycore_Vertex_get_restNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->restNormal;
	return 1;
}

static int Polycore_Vertex_get_restPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->restPosition;
	return 1;
}

static int Polycore_Vertex_get_normal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->normal;
	return 1;
}

static int Polycore_Vertex_get_tangent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->tangent;
	return 1;
}

static int Polycore_Vertex_get_vertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexColor;
	return 1;
}

static int Polycore_Vertex_get_texCoord(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->texCoord;
	return 1;
}

static int Polycore_Vertex_get_useVertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useVertexColor);
	return 1;
}

static int Polycore_Vertex_set_restNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->restNormal = *argInst;
	return 0;
}

static int Polycore_Vertex_set_restPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->restPosition = *argInst;
	return 0;
}

static int Polycore_Vertex_set_normal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->normal = *argInst;
	return 0;
}

static int Polycore_Vertex_set_tangent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->tangent = *argInst;
	return 0;
}

static int Polycore_Vertex_set_vertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexColor = *argInst;
	return 0;
}

static int Polycore_Vertex_set_texCoord(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->texCoord = *argInst;
	return 0;
}

static int Polycore_Vertex_set_useVertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useVertexColor = param;
	return 0;
}

static int Polycore_Vertex(lua_State *L) {
	Vertex *inst = new Vertex();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)inst;
	luaL_getmetatable(L, "Polycore.Vertex");
	lua_setmetatable(L, -2);
	return 1;
}

static int Polycore_Vertex_addBoneAssignment(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int boneID = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number boneWeight = lua_tonumber(L, 3);
	inst->addBoneAssignment(boneID, boneWeight);
	return 0;
}

static int Polycore_Vertex_getNumBoneAssignments(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->getNumBoneAssignments());
	return 1;
}

static int Polycore_Vertex_getBoneAssignment(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	PolyBase *ptrRetVal = (PolyBase*)inst->getBoneAssignment(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = ptrRetVal;
	}
	return 1;
}

static int Polycore_Vertex_normalizeWeights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	inst->normalizeWeights();
	return 0;
}

static int Polycore_Vertex_getTexCoord(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	Vector2 *retInst = new Vector2();
	*retInst = inst->getTexCoord();
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	luaL_getmetatable(L, "Polycore.Vector2");
	lua_setmetatable(L, -2);
	*userdataPtr = (PolyBase*)retInst;
	return 1;
}

static int Polycore_Vertex_setTexCoord(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number u = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number v = lua_tonumber(L, 3);
	inst->setTexCoord(u, v);
	return 0;
}

static int Polycore_Vertex_setNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vertex *inst = (Vertex*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->setNormal(x, y, z);
	return 0;
}

static int Polycore_delete_Vertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
	delete ((Vertex*) *inst);
	*inst = NULL;
	return 0;
}

} // namespace Polycode
