/*
Copyright 2010 (c) by Oliver Schoenborn. License terms in LICENSE.txt.
*/


#ifndef LUAXX_FUNCTION_INCLUDED
#define LUAXX_FUNCTION_INCLUDED


#include <cassert>
#include <lua.hpp>
#include "luaxx_dll.h"
#include "LuaAdapters.h"
#include "LuaResult.h"
#include "LuaRegistryRef.h"


namespace Lua
{


// use this as second arg to LuaResult or Function to get 
// all return values from a function call
static const int ALL = LUA_MULTRET;


// Represent a Lua function; called by () or when converted to LuaResult 
class LUAXX_CPP_API 
Function
{
public:
    // Last arg could be LuaALL to get all values returned; 
    // otherwise will get only numRets values
    Function(const std::string& id, int numRets=LuaALL): mLua(NULL), mID(id), mNumRets(numRets) {}
    Function(lua_State* lua, const std::string& globalName, int numRets=LuaALL);
    Function(LuaResult& result, int numRets=LuaALL);
    Function(LuaResult& result, const std::string& name, int numRets=LuaALL);
    ~Function() { if (mLua) mStack.reset(mLua); }

    Function& rebindChunk(const std::string& statement);
    Function& rebindRef(LuaResult& result);
    Function& operator=(LuaResult& result) { return rebindRef(result); }

    bool isNil() const { return mRegKey.isNil(); }
    const std::string& getID() const { return mID; }
    const Status& getRefStatus() const { return mStatus; }

    template <typename TT> Function& operator<<(TT obj);
    LuaResult operator() () const { prepStack(); return LuaResult(*this); }

public:
    // TODO: bug in compiler prevents this from being private; must never be used; 
    // currently only way to verify is to put a breakpoint on copy constructor and 
    // running test should complete without hitting breakpoint
    Function(const Function&): mLua(NULL), mNumRets(0) { assert(false); }

private:
    friend class LuaResult;
    int compute( lua_State* & lua, int& numRetVal ) const;

    inline void prepStack() const;

private:
    lua_State * mLua;
    const int mNumRets;
    const std::string mID;
    LuaRegRef mRegKey;
    Status mStatus;

    struct Stack
    {
        bool mFuncOnStack;
        size_t mArgsOnStack;
        int mStackTop;

        Stack(): mFuncOnStack(false), mArgsOnStack(0), mStackTop(0) {}
        void reset(lua_State*);
        inline void pushFunction(const LuaRegRef& regRef, lua_State*);
    };

    #pragma warning(push)
    #pragma warning(disable:4251)

    mutable Stack mStack;

    #pragma warning(pop)
};


// If function object not already on Lua stack, put it there
inline void 
Function::Stack::pushFunction(const LuaRegRef& regRef, lua_State* lua) 
{
    if (! mFuncOnStack) // then put on stack
    {
        // must track stack depth so know how many values returned by function call
        mStackTop = lua_gettop(lua);
        // put function on stack (before first arg);
        // NOTE: If function doesnt' exist, Lua will put nil
        // on stack and the error will come up at call time
        regRef.pushObj(); 
        mFuncOnStack = true;
    }
}


inline void 
Function::prepStack() 
const
{
    if ( mLua )
        mStack.pushFunction(mRegKey, mLua);
}


// Push values onto the Lua stack, in pushFunction for function call
template <typename TT>
Function& 
Function::operator<<( TT obj )
{
    if ( mLua ) 
    {
        prepStack();

        // put obj on stack
        XferAdapt<TT>::put(mLua, obj);
        mStack.mArgsOnStack ++;
    }

    return *this;
}


}; // namespace

#endif // LUAXX_FUNCTION_INCLUDED

