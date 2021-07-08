#include "KNoise.hpp"


unsigned int KNoise::ToSeed(std::string F_Text) {
    std::string Text = F_Text;
    unsigned int Seed = 0;

    for (size_t i = 0; i < Text.length(); i++) {
        if(Text.at(i) >= '0' && Text.at(i) <= '9') {
            Seed = Seed * 10;
            Seed = Seed + (Text.at(i)-48);
        } else {
            Seed = Seed * 100;
            srand((int)Text.at(i)+i);
            Seed = Seed + rand()%99;
        }
    }

    return Seed;
}