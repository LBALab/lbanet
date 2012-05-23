FIND_PATH(ICE_INCLUDE_DIR Ice/Ice.h
    ${ICE_DIR}/include
    $ENV{ICE_HOME}/include
    /usr/include
    /usr/local/include
    NO_DEFAULT_PATH
)

FIND_PATH(ICE_LIB_DIR slice
    ${ICE_DIR}/lib
    $ENV{ICE_HOME}/lib
    /usr/lib
    /usr/local/lib
    NO_DEFAULT_PATH
)

