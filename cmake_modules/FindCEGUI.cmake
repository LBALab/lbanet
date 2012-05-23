FIND_PATH(CEGUI_INCLUDE_DIR CEGUI.h
    ${CEGUI_DIR}/include
    $ENV{CEGUI_DIR}/include
    /usr/include
    /usr/local/include
    NO_DEFAULT_PATH
)

FIND_PATH(CEGUI_LIB_DIR CEGUIBase
    ${CEGUI_DIR}/lib
    $ENV{CEGUI_DIR}/lib
    /usr/lib
    /usr/local/lib
    NO_DEFAULT_PATH
)

