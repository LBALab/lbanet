FIND_PATH(PHYSX_DIR Foundation/include/NxFoundation.h
    "$ENV{PROGRAMFILES}/NVIDIA Corporation/NVIDIA PhysX SDK"
    $ENV{PHYSX_HOME}
    /usr/include/PhysX/v2.8.3/SDKs
    /usr/local/include/PhysX/v2.8.3/SDKs
    NO_DEFAULT_PATH
)

FIND_PATH(PHYSX_LIB_DIR *PhysXCore*
    "$ENV{PROGRAMFILES}/NVIDIA Corporation/NVIDIA PhysX SDK/v2.8.4/SDKs/lib/Win32"
    "$ENV{PROGRAMFILES}/NVIDIA Corporation/NVIDIA PhysX SDK/v2.8.4_win/SDKs/lib/Win32"
    $ENV{PHYSX_HOME}/lib/Win32
    /usr/lib/PhysX/v2.8.3
    /usr/local/lib/PhysX/v2.8.3
    NO_DEFAULT_PATH
)

