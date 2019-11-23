#include <iostream>
#include <math.h>

using namespace std;

// Variáveis globais
// f(X) = A3*X^3 – 9*A2*X + 3
u_int k = 1;
float a3 = 1.0;
float a2 = 1.0;
float h = 0.1e-5;
float d0 = -1.275;
float l = 0.05;     // lambda λ
float e1 = 0.05;
float e2 = 0.05;
float x;

// Função do pêndulo, dada pelo trabalho
// f(X) = A3*X^3 – 9*A2*X + 3
float pendulo (float xAtt, float a3Att, float a2Att) {
    x = xAtt;       // Parâmetro X da função
    a3 = a3Att;     // Parâmetro A3 da função
    a2 = a2Att;     // Parâmetro A2 da função

    return (a3 * pow(x, 3) - 9 * a2 * x + 3);
};

// Derivada da função do pêndulo
// f'(X) = A3*3*X^2 - 9*A2
float derivadaPendulo (float xAtt, float a3Att, float a2Att) {
    x = xAtt;       // Parâmetro X da função
    a3 = a3Att;     // Parâmetro A3 da função
    a2 = a2Att;     // Parâmetro A2 da função

    return ((3.0 * a3 * x * x) - (9 * a2));
}

// Método de Newton-Raphson original
float newton_raphson (float x1Att, float a3Att, float a2Att, float e1Att, float e2Att){
    e1 = e1Att;
    e2 = e2Att;

    float f1 = pendulo(x1Att, a3Att, a2Att);           // Função f(x)

    if (abs(f1) < e1){   // Primeira checagem de parada
        return x;
    }

    float f2 = derivadaPendulo(x1Att, a3Att, a2Att);   // Função f'(x)
    float x2 = x - (f1 / f2);
    while(true){
        f1 = pendulo(x1Att, a3Att, a2Att);
        f2 = derivadaPendulo(x1Att, a3Att, a2Att);
        x2 = x - (f1 / f2);

        if (abs(f1) < e1 or abs(x2-x1Att) < e2) {
            return x2;
        } else {
            x1Att = x2;
        }
    }
}


int main () {

    float testePendulo = pendulo(1.0 , 1.0, 1.0);    // deve dar -5
    cout << "\nValor do teste de f(x): " << testePendulo << endl;

    float testeDerivadaPendulo = derivadaPendulo(1.0, 1.0, 1.0);  // deve dar -6
    cout << "\nValor do teste de f'(x): " << testeDerivadaPendulo << endl;

    float testeNewtonRaphson = newton_raphson(d0, a3, a3, e1, e2);  // deve dar ~2.816978
    cout << "\nValor do teste de Newton-Raphson: " << testeNewtonRaphson << endl;

    return 0;
}