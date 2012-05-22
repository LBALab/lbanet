FIND_PATH(VLC_INCLUDE_DIR vlc/vlc.h
    ${VLC_DIR}/include
    $ENV{VLC_DIR}/include
    NO_DEFAULT_PATH
)

FIND_PATH(VLC_LIB_DIR vlc
    ${VLC_DIR}/lib
    $ENV{VLC_DIR}/lib
    NO_DEFAULT_PATH
)