cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

include(CTest)
enable_testing()

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c18 -O3" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks" )

#
# set (SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/src/shmupwarz.c )
# if (EXISTS ${CMAKE_SOURCE_DIR}/data )
#     add_subdirectory (data)
#     list ( APPEND RESOURCES ${resources_gresource_xml_C_FILE} )
# endif ()

add_subdirectory ( libs/cfw )
add_subdirectory ( libs/dna )
# add_subdirectory ( libs/artemis )

# add_executable( ${PROJECT_NAME} 
#     src/main.c 
#     src/shmupwarz.c
#     ${SOURCE} )
add_executable( ${PROJECT_NAME} 
    src/main.c 
    src/Demo.c
    src/BallObject.c 
    src/Collision.c 
    src/GameLevel.c 
    src/GameObject.c 
    src/Particle.c 
    src/ParticleGenerator.c 
    ${SOURCE} )
# add_executable( ${PROJECT_NAME} 
#     src/breakout/main.c 
#     src/breakout/BallObject.c 
#     src/breakout/Collision.c 
#     src/breakout/Game.c 
#     src/breakout/GameLevel.c 
#     src/breakout/GameObject.c 
#     src/breakout/Particle.c 
#     src/breakout/ParticleGenerator.c 
#     ${SOURCE} )


include_directories( include )
# include_directories( include/breakout )
include_directories( include/demo )
include_directories( libs/cfw/include )
include_directories( libs/dna/include )
# include_directories( libs/artemis/include )
include_directories( external/stb )
 
# add_subdirectory(tests)
target_link_libraries ( ${PROJECT_NAME} dl m BlocksRuntime corefw glfw GL )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

