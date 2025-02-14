cmake_minimum_required(VERSION 3.0.0)
set ( VERSION 0.0.1 )
set ( RELEASE_NAME demo )
set ( PROJECT_NAME demo )
set ( APP_NAME "Demo" )
set ( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include(CTest)
enable_testing()

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c18 -O3" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks" )


add_subdirectory ( libs/corefw )
add_subdirectory ( libs/cfw )
add_subdirectory ( libs/dna )
# add_subdirectory ( libs/artemis )

add_executable( ${APP_NAME} 
    src/main.c 
    src/Demo.c
    src/BallObject.c 
    src/Collision.c 
    src/GameLevel.c 
    src/GameObject.c 
    src/Particle.c 
    src/ParticleGenerator.c 
    ${SOURCE} )


include_directories( include )
include_directories( libs/corefw/include )
include_directories( libs/cfw/include )
include_directories( libs/dna/include )
# include_directories( libs/artemis/include )
include_directories( external/stb )
 
# add_subdirectory(tests)
target_link_libraries ( ${APP_NAME} dl m BlocksRuntime glfw GL )

add_custom_command ( TARGET ${APP_NAME} PRE_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/data/Resources/ $<TARGET_FILE_DIR:${APP_NAME}>/Resources )