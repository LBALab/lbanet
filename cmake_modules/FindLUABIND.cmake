FIND_PATH(LUABIND_INCLUDE_DIR luabind/version.hpp
    ${LUABIND_DIR}/include
    $ENV{LUABIND_DIR}/include
    /usr/include
    /usr/local/include
    NO_DEFAULT_PATH
)

FIND_PATH(LUABIND_LIB_DIR luabind
    ${LUABIND_DIR}/lib
    $ENV{LUABIND_DIR}/lib
    /usr/lib
    /usr/local/lib
    NO_DEFAULT_PATH
)