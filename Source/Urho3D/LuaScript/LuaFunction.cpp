//
// Copyright (c) 2008-2025 the U3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Precompiled.h"

#include "../IO/Log.h"
#include "../IO/VectorBuffer.h"
#include "../LuaScript/LuaFunction.h"
#include "../LuaScript/LuaScript.h"
#include "../LuaScript/LuaScriptInstance.h"

#include <toluapp/tolua++.h>
#include "../LuaScript/ToluaUtils.h"

#include "../DebugNew.h"

namespace Urho3D
{

LuaFunction::LuaFunction(lua_State* L, int index) :
    luaState_(L),
    numArguments_(-1)
{
    assert(L);
    lua_pushvalue(L, index);
    functionRef_ = luaL_ref(L, LUA_REGISTRYINDEX);
}

LuaFunction::LuaFunction(lua_State* L, lua_CFunction func) :
    luaState_(L),
    numArguments_(-1)
{
    assert(L);
    lua_pushcfunction(L, func);
    functionRef_ = luaL_ref(L, LUA_REGISTRYINDEX);
}

LuaFunction::~LuaFunction()
{
    luaL_unref(luaState_, LUA_REGISTRYINDEX, functionRef_);
    functionRef_ = LUA_NOREF;
}

bool LuaFunction::IsValid() const
{
    return functionRef_ != LUA_REFNIL && functionRef_ != LUA_NOREF;
}

bool LuaFunction::BeginCall(const LuaScriptInstance* instance)
{
    if (!IsValid())
        return false;

    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef_);
    if (instance)
    {
        lua_rawgeti(luaState_, LUA_REGISTRYINDEX, instance->GetScriptObjectRef());      // Will get a nil when reference is invalid
        numArguments_ = 1;
    }
    else
        numArguments_ = 0;

    return true;
}

bool LuaFunction::EndCall(int numReturns)
{
    assert(numArguments_ >= 0);
    int numArguments = numArguments_;
    numArguments_ = -1;

    if (lua_pcall(luaState_, numArguments, numReturns, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        URHO3D_LOGERROR("Execute Lua function failed: {}", message);
        lua_pop(luaState_, 1);
        return false;
    }

    return true;
}

void LuaFunction::PushInt(int value)
{
    assert(numArguments_ >= 0);
    ++numArguments_;
    lua_pushinteger(luaState_, value);
}

void LuaFunction::PushBool(bool value)
{
    assert(numArguments_ >= 0);
    ++numArguments_;
    lua_pushboolean(luaState_, value);
}

void LuaFunction::PushFloat(float value)
{
    assert(numArguments_ >= 0);
    ++numArguments_;
    lua_pushnumber(luaState_, value);
}

void LuaFunction::PushDouble(double value)
{
    assert(numArguments_ >= 0);
    ++numArguments_;
    lua_pushnumber(luaState_, value);
}

void LuaFunction::PushString(const String& string)
{
    assert(numArguments_ >= 0);
    ++numArguments_;
    tolua_pushurho3dstring(luaState_, string);
}

void LuaFunction::PushUserType(void* userType, const char* typeName)
{
    assert(numArguments_ >= 0);
    ++numArguments_;
    tolua_pushusertype(luaState_, userType, typeName);
}

void LuaFunction::PushVariant(const Variant& variant, const char* asType)
{
    assert(numArguments_ >= 0);
    ++numArguments_;
    ToluaPushVariant(luaState_, &variant, asType);
}

void LuaFunction::PushLuaTable(const char* tableName)
{
    assert(numArguments_ >= 0);
    ++numArguments_;

    // Performance impact wasn't confirmed here. However, I'd like to avoid unneeded allocations.
    if (!strchr(tableName, '.'))
    {
        lua_getglobal(luaState_, tableName);
    }
    else
    {
        Vector<String> splitNames = String::Split(tableName, '.');

        String currentName = splitNames.Front();
        lua_getglobal(luaState_, currentName.CString());

        if (splitNames.Size() > 1)
        {
            for (unsigned i = 0; i < splitNames.Size() - 1; ++i)
            {
                if (i)
                {
                    currentName = currentName + "." + splitNames[i];
                    lua_getfield(luaState_, -1, splitNames[i].CString());
                    lua_replace(luaState_, -2);
                }
                if (!lua_istable(luaState_, -1))
                {
                    lua_pop(luaState_, 1);
                    lua_pushnil(luaState_);
                    URHO3D_LOGERROR("Could not find lua table '{}'", currentName.CString());
                    return;
                }
            }

            currentName = currentName + "." + splitNames.Back();
            lua_getfield(luaState_, -1, splitNames.Back().CString());
            lua_replace(luaState_, -2);
        }
    }

    if (!lua_istable(luaState_, -1))
        URHO3D_LOGERROR("Could not find lua table '{}'", tableName);      // nil is pushed instead
}

}
