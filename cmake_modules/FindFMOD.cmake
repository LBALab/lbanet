FIND_PATH(FMOD_INCLUDE_DIR fmod.h
    ${FMOD_DIR}/include
    $ENV{FMOD_DIR}/include
    /usr/include
    /usr/local/include
    NO_DEFAULT_PATH
)

FIND_PATH(FMOD_LIB_DIR fmodex
    ${FMOD_DIR}/lib
    $ENV{FMOD_DIR}/lib
    /usr/lib
    /usr/local/lib
    NO_DEFAULT_PATH
)
