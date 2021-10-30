add_library(KNoise KNoise.cpp Perlin.cpp)

set_property(TARGET KNoise PROPERTY CXX_STANDARD 17)

install(TARGETS KNoise
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)