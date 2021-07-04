#include "KNoise.hpp"


unsigned int KNoise::ToSeed(std::string F_Text) {
    std::string Text = F_Text;
    unsigned int Seed = 0;

    for (size_t i = 0; i < Text.length(); i++) {
        switch (Text.at(i))
        {
        case '0':
            Seed = Seed * 10;
            break;

        case '1':
            Seed = Seed * 10;
            Seed = Seed + 1;
            break;

        case '2':
            Seed = Seed * 10;
            Seed = Seed + 2;
            break;

        case '3':
            Seed = Seed * 10;
            Seed = Seed + 3;
            break;

        case '4':
            Seed = Seed * 10;
            Seed = Seed + 4;
            break;

        case '5':
            Seed = Seed * 10;
            Seed = Seed + 5;
            break;

        case '6':
            Seed = Seed * 10;
            Seed = Seed + 6;
            break;

        case '7':
            Seed = Seed * 10;
            Seed = Seed + 7;
            break;

        case '8':
            Seed = Seed * 10;
            Seed = Seed + 8;
            break;

        case '9':
            Seed = Seed * 10;
            Seed = Seed + 9;
            break;

        default:
            Seed = Seed * 100;
            srand((int)Text.at(i)+i);
            Seed = Seed + rand()%99;
            break;
        }
    }

    return Seed;
}