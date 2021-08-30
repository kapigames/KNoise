#include "KNoise.hpp"


unsigned int KNoise::ToSeed(std::string F_Text) {
    std::wstring TextW( F_Text.begin(), F_Text.end() );
    std::string Text( TextW.begin(), TextW.end() );

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



unsigned int KNoise::ToSeedW(std::wstring F_Text) {
    std::string Text = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(F_Text);

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