add_library(KNoise KNoise.cpp Perlin.cpp)

target_precompile_headers(KNoise PUBLIC PCH.hpp)

install(TARGETS KNoise
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)