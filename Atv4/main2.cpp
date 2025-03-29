#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <cmath>

// Representação de uma cor em RGB
struct RGB{
    float r;
    float g;
    float b;
};
// Representação de uma cor em HSV
struct HSV{
    float h;
    float s;
    float v;
};

using namespace std;

// Calcula o Hue
float hue(RGB in, float delta, float maior) {

    if (delta == 0) return 0;
    
    else if (maior == in.r)
        return 60.0 * (in.g - in.b)/delta;

    else if (maior == in.g)
        return 60.0 * (2.0 + (in.b - in.r)/delta);

    else return 60.0 * (4.0 + (in.r - in.g)/delta);
}

// Calcula a Saturação
float saturation(RGB in, float delta, float maior){
    if (maior == 0) return  0;
    else return delta/maior;
}

// Calcula o Valor
float value(float maior){
    return  maior/255.0;
}

// Converte o RGB em HSV
HSV convert (RGB in){
    HSV result;

    float maior = max({in.r, in.g, in.b});
    float menor = min({in.r, in.g, in.b});
    float delta = maior - menor;

    result.h = hue(in, delta, maior);
    result.s = saturation(in, delta, maior);
    result.v = value(maior);

    return result;
}

int main(){
    RGB in;
    HSV out;

    // Pega os dados do RGB
    cout << "R: "; cin >> in.r;
    cout << "G: "; cin >> in.g;
    cout << "B: "; cin >> in.b;

    // Converte para HSV
    out = convert(in);

    // Imprime em HSV
    cout << fixed << setprecision(1)
         << "H: " << out.h << "°" << endl
         << "S: " << out.s * 100 << "%" << endl
         << "V: " << out.v * 100 << "%" << endl;

    return 0;
}