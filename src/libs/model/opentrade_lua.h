/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

#ifndef OPENTRADE_LUA_H
#define OPENTRADE_LUA_H

#ifdef __cplusplug
extern "C" {
#endif

#include <lua.h>

/* OpenTrade Lua API
 * Strategy API & Indicator API
 */

// Strategy API

// Base
/* 对于Instrument,系统存在一个InstrumentManager管理整个的Instrument列表,
 * 如果用户定义的Instrument存在于系统中,系统返回一个已经定义好的Instrument
 * 如果没有,系统加入这个Instrument,同时向底层取得该Instrument一些信息
 */
int Instrument(lua_State *L);
int getInstrument(lua_State *L);

// market

// execution
int Order(lua_State *L);

#ifdef __cplusplug
}
#endif

#endif // OPENTRADE_LUA_H
