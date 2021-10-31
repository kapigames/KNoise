add_executable(Sandbox main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/KNoise)
target_link_libraries(Sandbox KNoise)

set_property(TARGET Sandbox PROPERTY CXX_STANDARD 17)

install(TARGETS Sandbox RUNTIME DESTINATION build)