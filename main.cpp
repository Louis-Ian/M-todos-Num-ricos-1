#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

// ASCII usado na tabela
// ━  ┃  
// ┏  ┳  ┓ 
// ┣  ╋  ┫ 
// ┗  ┻  ┛ 
//
// ═  ║ 
// ╔  ╦  ╗ 
// ╠  ╬  ╣ 
// ╚  ╩  ╝ 

// Variáveis globais
// f(X) = A3*X^3 – 9*A2*X + 3
u_int k = 0;
u_int k_max = 100;
u_int precisao = 6;
double h = 0.1e-5;
vector<double> a3 = {1.0};
vector<double> a2 = {1.0};
vector<double> x0 = {-1.275};
vector<double> l = {0.05}; // lambda λ
double e1 = 0.05; // ε1
double e2 = 0.05; // ε2
double x;
vector<vector<string>> tabela = {};

// Função do pêndulo, dada pelo trabalho
// f(X) = A3*X^3 – 9*A2*X + 3
double pendulo(u_int n, double xAtt, double a3Att, double a2Att)
{
    x = xAtt;   // Parâmetro X da função
    a3[n] = a3Att; // Parâmetro A3 da função
    a2[n] = a2Att; // Parâmetro A2 da função

    return (a3[n] * pow(x, 3) - 9 * a2[n] * x + 3);
};

// Derivada da função do pêndulo
// f'(X) = A3*3*X^2 - 9*A2
double derivadaPendulo(u_int n, double xAtt, double a3Att, double a2Att)
{
    x = xAtt;   // Parâmetro X da função
    a3[n] = a3Att; // Parâmetro A3 da função
    a2[n] = a2Att; // Parâmetro A2 da função

    return ((3.0 * a3[n] * x * x) - (9 * a2[n]));
}

// Método de Newton-Raphson original
double newton_raphson(u_int n, u_int k_maxAtt, double x1Att, double a3Att, double a2Att, double e1Att, double e2Att)
{
    k = 0;
    k_max = k_maxAtt;
    e1 = e1Att;
    e2 = e2Att;

    double f1 = pendulo(n, x1Att, a3Att, a2Att); // Função f(x)

    if (abs(f1) < e1)
    { // Primeira checagem de parada
        return x;
    }

    double f2 = derivadaPendulo(n, x1Att, a3Att, a2Att); // Função f'(x)
    double x2 = x - (f1 / f2);
    while (k < k_max)
    {
        k++;
        f1 = pendulo(n, x1Att, a3Att, a2Att);
        f2 = derivadaPendulo(n, x1Att, a3Att, a2Att);
        x2 = x - (f1 / f2); // x' = x - f(x)/f'(x)

        if (abs(f1) < e1 or abs(x2 - x1Att) < e2)
        { // Segunda checagem de parada
            return x2;
        }
        else
        {
            x1Att = x2;
        }
    }

    cout << "\nlimite do número de iterações atingido." << endl;
    return x2;
}

// Método de Newton-Raphson utilizando lâmbda
double newton_raphson_fl(u_int n, uint k_maxAtt, double x1Att, double a3Att, double a2Att, double e1Att, double e2Att, double lAtt)
{
    k = 0;
    k_max = k_maxAtt;
    e1 = e1Att;
    e2 = e2Att;
    l[n] = lAtt;

    double f1 = pendulo(n, x1Att, a3Att, a2Att); // Função f(x)

    if (abs(f1) < e1)
    { // Primeira checagem de parada
        return x;
    }

    double f2 = derivadaPendulo(n, x1Att, a3Att, a2Att); // Função f'(x)
    double fl = f2;                                   // ultimo f'(x) que era maior que lâmbda
    double x2 = x - (f1 / f2);
    while (k < k_max)
    {
        k++;
        f1 = pendulo(n, x1Att, a3Att, a2Att);
        f2 = derivadaPendulo(n, x1Att, a3Att, a2Att);

        if (abs(f2) > l[n])
        {
            fl = f2;
        }
        else
        {
            f2 = fl;
        }

        x2 = x - (f1 / f2); // x' = x - f(x)/f'(x)

        if (abs(f1) < e1 or abs(x2 - x1Att) < e2)
        { // Segunda checagem de parada
            return x2;
        }
        else
        {
            x1Att = x2;
        }
    }

    cout << "\nlimite do número de iterações atingido." << endl;
    return x2;
}

// Função para calcular a derivada de qualquer função a partir da definição de derivada:f'(x)==f(x+h)-f(x)/h', onde h é um valor proximo de zero
double derivada_numerica(double f(u_int, double, double, double), u_int n, double h, double x1, double a1, double a2)
{
    double numerador = f(n, x1 + h, a1, a2) - f(n, x1, a1, a2);
    double denominador = h;
    return numerador / denominador;
}

double derivadaCentral(double f(u_int, double, double, double), u_int n, double h, double x1, double a1, double a2)
{
    double numerador = f(n, x1 + h, a1, a2) - f(n, x1 - h, a1, a2);
    double denominador = 2 * h;
    return numerador / denominador;
}

// Função melhorada para calcular a derivada usando a extrapolação de Richardson
double richardsonExtrapolation(double (*f)(u_int, double, double, double), u_int n, double h, double x1, double a1, double a2)
{
    double numerador = 4 * derivadaCentral(f, n, 2 * h, x1, a1, a2) - derivadaCentral(f, n, h, x1, a1, a2);
    double denominador = 3;
    return numerador / denominador;
}

// Método de Newton-Raphson utilizando derivada calculada numericamente
double newton_raphson_derivada_numerica(u_int n, u_int k_maxAtt, double x1Att, double a3Att, double a2Att, double e1Att, double e2Att, double hAtt)
{
    k = 0;
    k_max = k_maxAtt;
    e1 = e1Att;
    e2 = e2Att;
    h = hAtt;

    double f1 = pendulo(n, x1Att, a3Att, a2Att); // Função f(x)

    if (abs(f1) < e1)
    { // Primeira checagem de parada
        return x;
    }

    double f2 = derivada_numerica(pendulo, n, h, x1Att, a3Att, a2Att); // Função f'(x)
    double x2 = x - (f1 / f2);
    while (k < k_max)
    {
        k++;
        f1 = pendulo(n, x1Att, a3Att, a2Att);
        f2 = derivada_numerica(pendulo, n, h, x1Att, a3Att, a2Att);
        x2 = x - (f1 / f2); // x' = x - f(x)/f'(x)

        if (abs(f1) < e1 or abs(x2 - x1Att) < e2)
        { // Segunda checagem de parada
            return x2;
        }
        else
        {
            x1Att = x2;
        }
    }

    cout << "\nlimite do número de iterações atingido." << endl;
    return x2;
}

void insercao_u_int(u_int &entrada, string nome) // TODO consertar entrada negativa
{
    cout << "\nInsira  " << nome;
    cin >> entrada;

    while(!cin)
    {
        cout << "Entrada inválida, tente novamente.\n";
        cin.clear();
        cin.ignore();
        cin >> entrada;
    }
}

void insercao_double(double &entrada, string nome)
{
    cout << "\nInsira " << nome;
    cin >> entrada;

    while(!cin)
    {
        cout << "Entrada inválida, tente novamente.\n";
        cin.clear();
        cin.ignore();
        cin >> entrada;
    }
}

void insercao_vector_double(vector<double> &entrada, u_int n, string nome)
{
    cout << "\nInsira " << nome;
    cin >> entrada[n];

    while(!cin)
    {
        cout << "Entrada inválida, tente novamente.\n";
        cin.clear();
        cin.ignore();
        cin >> entrada[n];
    }
}

int main()
{
    u_int n;
    insercao_u_int(n, "o número de lambdas (0 para rodar o caso padrão):");
    if(n > 0)
    {
        vector<double> a3(n);
        vector<double> a2(n);
        vector<double> x0(n);
        vector<double> l(n);

        insercao_u_int(k_max, "o limite de iterações: ");
        insercao_u_int(precisao, "o número de casa decimais depois da vírgula: ");

        insercao_double(e1, "a precisão de ε1: ");
        insercao_double(e2, "a precisão de ε2: ");
        
        for (u_int i = 0; i < n; i++)
        {
            string iesimo = "o valor do ";
            iesimo += to_string(i+1);
            iesimo += "º ";
            
            insercao_vector_double(l, i, iesimo.append("lambda: "));
            iesimo.clear();
            insercao_vector_double(x0, i, iesimo.append("x0: "));
            iesimo.clear();
            insercao_vector_double(a3, i, iesimo.append("a3: "));
            iesimo.clear();
            insercao_vector_double(a2, i, iesimo.append("a2: "));
            iesimo.clear();
        }
    }

    cout << fixed << setprecision(precisao);

    double testePendulo = pendulo(0, 1.0, 1.0, 1.0); // deve dar -5
    cout << "\nValor do teste de f(x): " << testePendulo << endl;

    double testeDerivadaPendulo = derivadaPendulo(0, 1.0, 1.0, 1.0); // deve dar -6
    cout << "\nValor do teste de f'(x): " << testeDerivadaPendulo << endl;

    double testeNewtonRaphson = newton_raphson(0, k_max, x0[0], a3[0], a2[0], e1, e2); // deve dar aproximadamente 2.81697875211
    cout << "\nValor do teste de Newton-Raphson: " << testeNewtonRaphson << endl;

    double testeNewtonRaphsonFL = newton_raphson_fl(0, k_max, x0[0], a3[0], a2[0], e1, e2, l[0]); // deve dar aproximadamente 0.333780224702
    cout << "\nValor do teste de Newton-Raphson-lâmbda: " << testeNewtonRaphsonFL << endl;

    double testeNewtonRaphsonDerivadaNumerica = newton_raphson_derivada_numerica(0, k_max, x0[0], a3[0], a2[0], e1, e2, h); // deve dar aproximadamente 2.81697875231
    cout << "\nValor do teste de Newton-Raphson-lâmbda: " << testeNewtonRaphsonDerivadaNumerica << endl;

    return 0;
}