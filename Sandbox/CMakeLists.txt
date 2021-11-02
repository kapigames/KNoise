add_executable(Sandbox main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/KNoise)
target_link_libraries(Sandbox KNoise)

if(DEFINED UNIX)
    target_link_libraries(Sandbox pthread)
endif()

install(TARGETS Sandbox RUNTIME DESTINATION build)