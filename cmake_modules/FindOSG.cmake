FIND_PATH(OSG_INCLUDE_DIR osg/Node
    ${OSG_DIR}/include
    $ENV{OSG_DIR}/include
    $ENV{OSGDIR}/include
    $ENV{OSG_ROOT}/include
    NO_DEFAULT_PATH
)

FIND_PATH(OSG_LIB_DIR osgPlugins-3.1.0
    ${OSG_DIR}/lib
    $ENV{OSG_DIR}/lib
    $ENV{OSGDIR}/lib
    $ENV{OSG_ROOT}/lib
    NO_DEFAULT_PATH
)

