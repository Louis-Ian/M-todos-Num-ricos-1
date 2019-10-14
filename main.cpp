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

// Função para calcular a derivada de qualquer função a partir da definição de derivada:f'(x)==f(x+h)-f(x)/h', onde h é um valor proximo de zero

float derivada(float f, float h, float x1, float a1, float a2){
	float enumerador = f*(x1+h, a1, a2)-f*(x1, a1, a2);
	float denominador = h;
	return enumerador / denominador;
}

float derivadaCentral(float f, float h, float x1, float a1, float a2){
	float enumerador = f*(x1+h, a1, a2)-f*(x1-h, a1, a2);
	float denominador = 2*h;
	return enumerador / denominador;
}

// Função melhorada para calcular a derivada usando a extrapolação de Richardson

float richardsonExtrapolation(float f, float h, float x1, float a1, float a2){
	float enumerador = 4*derivadaCentral(f, 2*h, x1, a1, a2)-derivadaCentral(f, h, x1, a1, a2);
	float denominador = 3;
	return enumerador / denominador;
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
        x2 = x - (f1 / f2); // x' = x - f(x)/f'(x)

        if (abs(f1) < e1 or abs(x2-x1Att) < e2) {   // Segunda checagem de parada
            return x2;
        } else {
            x1Att = x2;
        }
    }
}

// Método de Newton-Raphson utilizando lâmbda
float newton_raphson_fl (float x1Att, float a3Att, float a2Att, float e1Att, float e2Att, float lAtt){
    e1 = e1Att;
    e2 = e2Att;
    l = lAtt;

    float f1 = pendulo(x1Att, a3Att, a2Att);           // Função f(x)

    if (abs(f1) < e1){   // Primeira checagem de parada
        return x;
    }

    float f2 = derivadaPendulo(x1Att, a3Att, a2Att);   // Função f'(x)
    float fl = f2;  // 
    float x2 = x - (f1 / f2);
    while(true){
        f1 = pendulo(x1Att, a3Att, a2Att);
        f2 = derivadaPendulo(x1Att, a3Att, a2Att);

        if (abs(f2) > l){
            fl = f2;
        } else{
            f2 = fl;
        }

        x2 = x - (f1 / f2); // x' = x - f(x)/f'(x)

        if (abs(f1) < e1 or abs(x2-x1Att) < e2) {   // Segunda checagem de parada
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

    float testeNewtonRaphson = newton_raphson(d0, a3, a3, e1, e2);  // deve dar aproximadamente 2.81697875211
    cout << "\nValor do teste de Newton-Raphson: " << testeNewtonRaphson << endl;

    float testeNewtonRaphsonFL = newton_raphson_fl(d0, a3, a3, e1, e2, l);  // deve dar aproximadamente 0.333780224702
    cout << "\nValor do teste de Newton-Raphson-lâmbda: " << testeNewtonRaphsonFL << endl;

    return 0;
}