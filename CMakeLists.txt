
project(python-classads)
cmake_minimum_required(VERSION 2.6)
set( CMAKE_MODULE_PATH
 ${PROJECT_SOURCE_DIR}/cmake )

if( CMAKE_COMPILER_IS_GNUCXX )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror" )
endif()

# Uncomment the below line to help find boost.
#set(Boost_DEBUG             ON)
# On RHEL6, you'll need boost-python and boost-devel
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS
                thread
                python
             REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#  On RHEL6, you'll need python-devel
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})

# Requires condor-classad-devel
find_package( Classad REQUIRED )
include_directories(${CLASSAD_INCLUDES})

# Requires condor source code and condor-devel
find_package( Condor REQUIRED )
include_directories(${CONDOR_INCLUDES} ${CONDOR_UTILS_INCLUDES}
${CONDOR_SAFEFILE_INCLUDES} ${CONDOR_DAEMON_INCLUDES})

# Requires python-classad
find_package( PythonClassad REQUIRED )
include_directories(${PYTHON_CLASSAD_INCLUDES})

add_library(condor SHARED
        src/condor.cpp
        src/daemon_and_ad_types.cpp
        src/collector.cpp
        src/schedd.cpp
        src/config.cpp
        src/dc_tool.cpp
        src/secman.cpp
    )
# Note we change the library prefix to produce "testboost" instead of
# "libtestboost", following python convention.
set_target_properties(condor PROPERTIES PREFIX "")
target_link_libraries(condor ${Boost_LIBRARIES} ${PYTHON_LIBRARIES}
${CLASSAD_LIB} ${PYTHON_CLASSAD_LIB} ${CONDOR_LIB})

