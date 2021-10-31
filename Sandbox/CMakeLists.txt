add_executable(Sandbox main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/KNoise)
target_link_libraries(Sandbox KNoise)

install(TARGETS Sandbox RUNTIME DESTINATION build)