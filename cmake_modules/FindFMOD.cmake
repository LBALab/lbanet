FIND_PATH(FMOD_INCLUDE_DIR fmod.h
    ${FMOD_DIR}/include
    $ENV{FMOD_DIR}/include
    NO_DEFAULT_PATH
)

FIND_PATH(FMOD_LIB_DIR fmodex
    ${FMOD_DIR}/lib
    $ENV{FMOD_DIR}/lib
    NO_DEFAULT_PATH
)
