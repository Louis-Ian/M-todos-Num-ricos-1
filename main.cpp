#include <iostream>
#include <math.h>

using namespace std;

// Variáveis da função dada
double a1 = 1.0;
double a2 = 1.0;
double h = 0.1e-5;
double d0 = -1.275;
double l = 0.05;
double e1 = 0.05;
double e2 = 0.05;
double x;

// 
double pendulo (double xAtt, double a1Att, double a2Att) {
    x = xAtt;       // X atributo da função
    a1 = a1Att;     // A1 atributo da função
    a2 = a2Att;     // A2 atributo da função

    return ((3.0 * a1 * x * x) - (9 * a2));
};


int main () {

    double teste = pendulo(1.0, a1, a2);    // deve dar -6

    cout << "\nValor do teste: " << teste << endl;

    return 0;
}