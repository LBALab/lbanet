FIND_PATH(LUA_INCLUDE_DIR lua.h
    ${LUA_DIR}/include
    $ENV{LUA_DIR}/include
    NO_DEFAULT_PATH
)

FIND_PATH(LUA_LIB_DIR lua
    ${LUA_DIR}/lib
    $ENV{LUA_DIR}/lib
    NO_DEFAULT_PATH
)

