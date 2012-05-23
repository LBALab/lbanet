FIND_PATH(LUA_INCLUDE_DIR lua.h
    ${LUA_DIR}/include
    $ENV{LUA_DIR}/include
    /usr/include
    /usr/local/include
    NO_DEFAULT_PATH
)

FIND_PATH(LUA_LIB_DIR lua
    ${LUA_DIR}/lib
    $ENV{LUA_DIR}/lib
    /usr/lib
    /usr/local/lib
    NO_DEFAULT_PATH
)

