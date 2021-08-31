#include "KNoise.hpp"



unsigned int KNoise::ToSeed(std::string F_Text) { 
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert32;
    std::u32string utf32 = convert32.from_bytes(F_Text);

    return ToSeed(utf32);
}


unsigned int KNoise::ToSeed(std::wstring F_Text) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>,wchar_t> convert; 
    std::string utf8 = convert.to_bytes(F_Text);

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert32;
    std::u32string utf32 = convert32.from_bytes(utf8);

    return ToSeed(utf32);
}


unsigned int KNoise::ToSeed(std::u16string F_Text) { 
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert; 
    std::string utf8 = convert.to_bytes(F_Text);

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert32;
    std::u32string utf32 = convert32.from_bytes(utf8);

    return ToSeed(utf32);
}


unsigned int KNoise::ToSeed(std::u32string F_Text) {
    unsigned int Seed = 0;

    for (size_t i = 0; i < F_Text.length(); i++) {
        if(F_Text.at(i) >= '0' && F_Text.at(i) <= '9') {
            Seed = Seed * 10;
            Seed = Seed + (F_Text.at(i)-48);
        } else {
            Seed = Seed * 100;
            srand((int)F_Text.at(i)+i);
            Seed = Seed + rand()%99;
        }
    }

    return Seed;
}