/*
Copyright 2010 (c) by Oliver Schoenborn. License terms in LICENSE.txt.
*/


#ifndef LUAXX_RESULT_INCLUDED
#define LUAXX_RESULT_INCLUDED


#include <cassert>
#include <string>

#include <lua.hpp>
#include "luaxx_dll.h"
#include "LuaAdapters.h"
#include "LuaStatus.h"
#include "LuaRegistryRef.h"


namespace Lua
{


class Function; 


// Represent the result of a call to a Lua function
class LUAXX_CPP_API 
LuaResult
{
public:
    LuaResult(lua_State* lua, int numRetVal = 0, int errCode = 0, const std::string& errMsg = "");
    LuaResult(const Function&);
    inline ~LuaResult() { clear(); }

    // get one more returned item from last function call
    size_t countTotal() const     { return mNumRetVal; }
    size_t countRemaining() const { return mNumRetsOnStack; }
    template <typename TT> LuaResult& operator>>(TT& obj);

    // false if error, true otherwise:
    bool ok() const {return mLua && mStatus;}
    // err msg (empty if ok() is true)
    std::string errMsg() const {return mStatus.errMsg();}
    // Get the complete status info, which contains error message from Lua, if any
    const Status& getStatus() const { return mStatus; }

    // Get specific result items via array [] operator; 
    // get TT value of item N by conversion TT(result[N]) for instance int(res[1]) to 
    // get first item of LuaResult object as an integer; can also compare an Item to a 
    // TT value directly as in "if (res[1] == 3) ..."
    class Item
    {
    public:
        Item(lua_State* lua, int index): mLua(lua), mIndex(index) { assert(lua); }

        template <typename TT>
        operator TT() const { return (mIndex < 1 ? TT(0) : XferAdapt<TT>::getObjFromStack(mLua, -mIndex) ); }

    private:
        lua_State * mLua;
        int mIndex;
    };

    // result items get indexed starting from ARRAY_OFFSET
    static const int ARRAY_OFFSET = 1;
    inline Item operator[](int index) const;

private:
    inline void init();

    LuaResult& operator=(const LuaResult&);
    //LuaResult(const LuaResult& rhs);

    friend class Function;
    inline void clear();
    inline lua_State* getItemRef() const;
    lua_State* getLuaState() { return mLua; }

private:
    lua_State * mLua;
    int mNumRetVal;
    Status mStatus;
    size_t mNumRetsOnStack;
};


inline void 
LuaResult::clear() 
{
    if (mNumRetVal)
    {
        assert(mLua);
        lua_pop(mLua, mNumRetVal);
        mNumRetVal = 0;
    }
    mNumRetsOnStack = 0;
    mStatus = Status();
}


/*inline void 
LuaResult::operator=(LuaResult& rhs)
{
    assert(mLua == rhs.mLua);

    // clear ourselves
    if (mNumRetVal)
        lua_pop(mLua, mNumRetVal);

    // copy rhs:
    mNumRetVal = rhs.mNumRetVal;
    mNumRetsOnStack = rhs.mNumRetsOnStack;
    mStatus = rhs.mStatus;

    // clear out rhs result:
    rhs.mNumRetVal = 0;
    rhs.mNumRetsOnStack = 0;
    rhs.mStatus = Status();
}*/


inline lua_State*
LuaResult::getItemRef() const
{
    assert(mLua);
    if (mNumRetsOnStack > 0)
        lua_pushvalue(mLua, -int(mNumRetsOnStack));
    else
        lua_pushnil(mLua);
    return mLua;
}


// Get a return value from the stack, after a Function was 
// called (which could happen via conversion of a Function to a LuaResult)
template <typename TT>
LuaResult& 
LuaResult::operator>>( TT& obj )
{
    assert(mLua);
    if (mNumRetsOnStack > 0)
    {
        obj = XferAdapt<TT>::getObjFromStack(mLua, -int(mNumRetsOnStack));
        mNumRetsOnStack --;
    }
    else 
        obj = TT(0);

    return *this;
}


// Get a LuaResult::Item which can then be converted to a desired type value, 
// or compared to a value of desired type
inline LuaResult::Item 
LuaResult::operator[]( int index ) 
const
{
    assert(mLua);
    return ( index >= ARRAY_OFFSET && index < ARRAY_OFFSET + mNumRetVal )
        ? Item(mLua, ARRAY_OFFSET + mNumRetVal - index)
        : Item(mLua, -1);
}


template <typename TT> inline bool operator==(const LuaResult::Item& item, const TT& rhs) { return TT(item) == rhs; }
template <typename TT> inline bool operator>=(const LuaResult::Item& item, const TT& rhs) { return TT(item) >= rhs; }
template <typename TT> inline bool operator<=(const LuaResult::Item& item, const TT& rhs) { return TT(item) <= rhs; }
template <typename TT> inline bool operator> (const LuaResult::Item& item, const TT& rhs) { return TT(item) >  rhs; }
template <typename TT> inline bool operator< (const LuaResult::Item& item, const TT& rhs) { return TT(item) <  rhs; }
template <typename TT> inline bool operator==(const TT& lhs, const LuaResult::Item& item) { return lhs == TT(item); }
template <typename TT> inline bool operator>=(const TT& lhs, const LuaResult::Item& item) { return lhs >= TT(item); }
template <typename TT> inline bool operator<=(const TT& lhs, const LuaResult::Item& item) { return lhs <= TT(item); }
template <typename TT> inline bool operator> (const TT& lhs, const LuaResult::Item& item) { return lhs >  TT(item); }
template <typename TT> inline bool operator< (const TT& lhs, const LuaResult::Item& item) { return lhs <  TT(item); }


} // namespace

#endif // LUAXX_RESULT_INCLUDED
