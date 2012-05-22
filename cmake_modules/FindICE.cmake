FIND_PATH(ICE_INCLUDE_DIR Ice/Ice.h
    ${ICE_DIR}/include
    $ENV{ICE_HOME}/include
    NO_DEFAULT_PATH
)

FIND_PATH(ICE_LIB_DIR slice
    ${ICE_DIR}/lib
    $ENV{ICE_HOME}/lib
    NO_DEFAULT_PATH
)

