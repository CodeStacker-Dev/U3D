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

#pragma once

#ifdef AS_MAX_PORTABILITY
#include "../AngelScript/aswrappedcall.h"
#endif

#include "../AngelScript/Generated_Templates.h"

namespace Urho3D
{

// f - function
// c - class
// m - method
// p - parameters (in parentheses)
// r - return type
// PR - parameters + return type

// RegisterGlobalFunction(decl, AS_FUNCTION(f), AS_CALL_CDECL)
// RegisterGlobalFunction(decl, AS_FUNCTIONPR(f, p, r), AS_CALL_CDECL)
// RegisterObjectBehaviour(obj, asBEHAVE_FACTORY, decl, AS_FUNCTION(f), AS_CALL_CDECL)
// RegisterObjectBehaviour(obj, asBEHAVE_FACTORY, decl, AS_FUNCTIONPR(f, p, r), AS_CALL_CDECL)
#ifdef AS_MAX_PORTABILITY
	#define AS_FUNCTION(f) WRAP_FN(f)
	#define AS_FUNCTIONPR(f, p, r) WRAP_FN_PR(f, p, r)
	#define AS_CALL_CDECL asCALL_GENERIC
#else
	#define AS_FUNCTION(f) asFUNCTION(f)
	#define AS_FUNCTIONPR(f, p, r) asFUNCTIONPR(f, p, r)
	#define AS_CALL_CDECL asCALL_CDECL
#endif

// RegisterObjectBehaviour(obj, behaviour, decl, AS_METHOD(c, m), AS_CALL_THISCALL)
// RegisterObjectBehaviour(obj, behaviour, decl, AS_METHODPR(c, m, p, r), AS_CALL_THISCALL)
//     where behaviour is asBEHAVE_ADDREF or asBEHAVE_RELEASE
// RegisterObjectMethod(obj, decl, AS_METHOD(c, m), AS_CALL_THISCALL)
// RegisterObjectMethod(obj, decl, AS_METHODPR(c, m, p, r), AS_CALL_THISCALL)
#ifdef AS_MAX_PORTABILITY
	#define AS_METHOD(c, m) WRAP_MFN(c, m)
	#define AS_METHODPR(c, m, p, r) WRAP_MFN_PR(c, m, p, r)
	#define AS_CALL_THISCALL asCALL_GENERIC
#else
	#define AS_METHOD(c, m) asMETHOD(c, m)
	#define AS_METHODPR(c, m, p, r) asMETHODPR(c, m, p, r)
	#define AS_CALL_THISCALL asCALL_THISCALL
#endif

// RegisterObjectBehaviour(obj, behaviour, decl, AS_FUNCTION_OBJFIRST(f), AS_CALL_CDECL_OBJFIRST)
// RegisterObjectBehaviour(obj, behaviour, decl, AS_FUNCTION_OBJLAST(f), AS_CALL_CDECL_OBJLAST)
//     where behaviour is asBEHAVE_CONSTRUCT, asBEHAVE_ADDREF or asBEHAVE_RELEASE
// RegisterObjectMethod(obj, decl, AS_FUNCTION_OBJFIRST(f), AS_CALL_CDECL_OBJFIRST)
// RegisterObjectMethod(obj, decl, AS_FUNCTIONPR_OBJFIRST(f, p, r), AS_CALL_CDECL_OBJFIRST)
// RegisterObjectMethod(obj, decl, AS_FUNCTION_OBJLAST(f), AS_CALL_CDECL_OBJLAST)
// RegisterObjectMethod(obj, decl, AS_FUNCTIONPR_OBJLAST(f, p, r), AS_CALL_CDECL_OBJLAST)
#ifdef AS_MAX_PORTABILITY
	#define AS_FUNCTION_OBJFIRST(f) WRAP_OBJ_FIRST(f)
	#define AS_FUNCTION_OBJLAST(f) WRAP_OBJ_LAST(f)
	#define AS_FUNCTIONPR_OBJFIRST(f, p, r) WRAP_OBJ_FIRST_PR(f, p, r)
	#define AS_FUNCTIONPR_OBJLAST(f, p, r) WRAP_OBJ_LAST_PR(f, p, r)
	#define AS_CALL_CDECL_OBJFIRST asCALL_GENERIC
	#define AS_CALL_CDECL_OBJLAST asCALL_GENERIC
#else
	#define AS_FUNCTION_OBJFIRST(f) asFUNCTION(f)
	#define AS_FUNCTION_OBJLAST(f) asFUNCTION(f)
	#define AS_FUNCTIONPR_OBJFIRST(f, p, r) asFUNCTIONPR(f, p, r)
	#define AS_FUNCTIONPR_OBJLAST(f, p, r) asFUNCTIONPR(f, p, r)
	#define AS_CALL_CDECL_OBJFIRST asCALL_CDECL_OBJFIRST
	#define AS_CALL_CDECL_OBJLAST asCALL_CDECL_OBJLAST
#endif

// RegisterObjectBehaviour(obj, asBEHAVE_DESTRUCT, decl, AS_DESTRUCTOR(c), AS_CALL_CDECL_OBJFIRST)
// RegisterObjectBehaviour(obj, asBEHAVE_DESTRUCT, decl, AS_DESTRUCTOR(c), AS_CALL_CDECL_OBJLAST)
#ifdef AS_MAX_PORTABILITY
	#define AS_DESTRUCTOR(c) WRAP_DES(c)
#else
	template <class T>
	void ASNativeDestructor(T* ptr)
	{
		ptr->~T();
	}

	#define AS_DESTRUCTOR(c) asFUNCTION(ASNativeDestructor<c>)
#endif

} // namespace Urho3D
