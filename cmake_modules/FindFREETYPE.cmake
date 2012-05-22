FIND_PATH(FREETYPE_INCLUDE_DIR freetype/freetype.h
    ${FREETYPE_DIR}/include
    $ENV{FREETYPE_DIR}/include
    NO_DEFAULT_PATH
)

FIND_PATH(FREETYPE_LIB_DIR freetype244
    ${FREETYPE_DIR}/lib
    $ENV{FREETYPE_DIR}/lib
    NO_DEFAULT_PATH
)

