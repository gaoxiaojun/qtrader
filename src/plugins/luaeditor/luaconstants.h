#ifndef LUACONSTANTS_H
#define LUACONSTANTS_H

#include <QtGlobal>

#include <app/app_config.h>


#include <coreplugin/idocument.h>

namespace LuaEditor {
namespace Constants {

// contexts
const char C_LUAEDITOR[]      = "Lua Editor";

// menus
const char M_CONTEXT[]        = "LuaEditor.ContextMenu";

// actions
const char SEPARATOR[]        = "LuaEditor.Separator";
const char JUMP_TO_FILE[]     = "LuaEditor.JumpToFile";

const char LUA_EDITOR_ID[]    = "Premake.LuaEditor";
const char LUA_EDITOR_DISPLAY_NAME[] = QT_TRANSLATE_NOOP("OpenWith::Editors", "Lua Editor");

const char LUA_MIMETYPE[]     = "text/x-lua";

// ICONS
const char ICON_LUA_FILE[]    = ":/LuaEditor/images/lua_small.png";

}
}

#endif // LUACONSTANTS_H
