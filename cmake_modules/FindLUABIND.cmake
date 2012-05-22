FIND_PATH(LUABIND_INCLUDE_DIR luabind/version.hpp
    ${LUABIND_DIR}/include
    $ENV{LUABIND_DIR}/include
    NO_DEFAULT_PATH
)

FIND_PATH(LUABIND_LIB_DIR luabind
    ${LUABIND_DIR}/lib
    $ENV{LUABIND_DIR}/lib
    NO_DEFAULT_PATH
)