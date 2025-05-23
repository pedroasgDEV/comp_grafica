#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <cmath>

using namespace std;

// Representação de uma cor em RGB
struct RGB{
    float r;
    float g;
    float b;
};

// Representação de uma cor em CMYK
struct CMYK{
    float c;
    float m;
    float y;
    float k;
};

// Converte de RGB para CMYK
CMYK convert (RGB in){
    CMYK result;

    // Trasforma em base 1
    in = {
        in.r / 255.0f,
        in.g / 255.0f,
        in.b / 255.0f
    };

    result.k = 1.0f - max({in.r, in.g, in.b});
    result.c = (1.0f - result.k) == 0 ? 0 : (1.0f - in.r - result.k) / (1.0f - result.k);
    result.m = (1.0f - result.k) == 0 ? 0 : (1.0f - in.g - result.k) / (1.0f - result.k);
    result.y = (1.0f - result.k) == 0 ? 0 : (1.0f - in.b - result.k) / (1.0f - result.k);

    return result;
}

int main(){
    RGB in;
    CMYK out;

    // Pega os dados do RGB
    in = {
        255.0,
        128.0,
        64.0
    };

    // Converte para CMYK
    out = convert(in);

    // Imprime em CMYK
    cout << fixed << setprecision(1)
         << "C: " << out.c * 100 << "%" << endl
         << "M: " << out.m * 100 << "%" << endl
         << "Y: " << out.y * 100 << "%" << endl
         << "K: " << out.k * 100 << "%" << endl;

    return 0;
}