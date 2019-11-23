#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

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
double e1 = 0.05;          // ε1
double e2 = 0.05;          // ε2
double x;
vector<vector<string>> tabela_newton = {};          // tabela de todos os registros de newton original
vector<vector<string>> tabela_newton_lambda = {};   // tabela de todos os registros de newton utilizando lambda
vector<vector<string>> tabela_newton_numerico = {}; // tabela de todos os registros de newton com derivada numérica

// Função do pêndulo, dada pelo trabalho
// f(X) = A3*X^3 – 9*A2*X + 3
double pendulo(double xAtt, double a3Att, double a2Att)
{
    x = xAtt;            // Parâmetro X da função
    a3.push_back(a3Att); // Parâmetro A3 da função
    a2.push_back(a2Att); // Parâmetro A2 da função

    return (a3Att * pow(x, 3) - 9 * a2Att * x + 3);
};

// Derivada da função do pêndulo
// f'(X) = A3*3*X^2 - 9*A2
double derivadaPendulo(double xAtt, double a3Att, double a2Att)
{
    x = xAtt;            // Parâmetro X da função
    a3.push_back(a3Att); // Parâmetro A3 da função
    a2.push_back(a2Att); // Parâmetro A2 da função

    return ((3.0 * a3Att * x * x) - (9 * a2Att));
}

// Método de Newton-Raphson original
double newton_raphson(u_int k_maxAtt, double x1Att, double a3Att, double a2Att, double e1Att, double e2Att, vector<vector<string>> &tabela)
{
    k = 0;
    k_max = k_maxAtt;
    e1 = e1Att;
    e2 = e2Att;

    double f1 = pendulo(x1Att, a3Att, a2Att); // Função f(x)
    double f2 = derivadaPendulo(x1Att, a3Att, a2Att);
    double x2 = x - (f1 / f2);

    if (abs(f1) < e1)
    { // Primeira checagem de parada
        tabela.push_back({to_string(k), to_string(x1Att), to_string(f1), to_string(f2), to_string(abs(x2 - x1Att))});
        return x;
    }

    while (k < k_max)
    {
        k++;
        f1 = pendulo(x1Att, a3Att, a2Att);         // Função f(x)
        f2 = derivadaPendulo(x1Att, a3Att, a2Att); // Função f'(x)
        x2 = x - (f1 / f2);                        // x' = x - f(x)/f'(x)

        tabela.push_back({to_string(k), to_string(x1Att), to_string(f1), to_string(f2), to_string(abs(x2 - x1Att))});
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
double newton_raphson_fl(uint k_maxAtt, double x1Att, double a3Att, double a2Att, double e1Att, double e2Att, double lAtt, vector<vector<string>> &tabela)
{
    k = 0;
    k_max = k_maxAtt;
    e1 = e1Att;
    e2 = e2Att;
    l.push_back(lAtt);

    double f1 = pendulo(x1Att, a3Att, a2Att);         // Função f(x)
    double f2 = derivadaPendulo(x1Att, a3Att, a2Att); // Função f'(x)
    double fl = f2;                                   // ultimo f'(x) que era maior que lâmbda
    double x2 = x - (f1 / f2);

    if (abs(f1) < e1)
    { // Primeira checagem de parada
        tabela.push_back({to_string(k), to_string(x1Att), to_string(f1), to_string(f2), to_string(abs(x2 - x1Att))});
        return x;
    }

    while (k < k_max)
    {
        k++;
        f1 = pendulo(x1Att, a3Att, a2Att);
        f2 = derivadaPendulo(x1Att, a3Att, a2Att);

        if (abs(f2) > lAtt)
        {
            fl = f2;
        }
        else
        {
            f2 = fl;
        }

        x2 = x - (f1 / f2); // x' = x - f(x)/f'(x)

        tabela.push_back({to_string(k), to_string(x1Att), to_string(f1), to_string(f2), to_string(abs(x2 - x1Att))});

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
double derivada_numerica(double f(double, double, double), double h, double x1, double a1, double a2)
{
    double numerador = f(x1 + h, a1, a2) - f(x1, a1, a2);
    double denominador = h;
    return numerador / denominador;
}

double derivadaCentral(double f(double, double, double), double h, double x1, double a1, double a2)
{
    double numerador = f(x1 + h, a1, a2) - f(x1 - h, a1, a2);
    double denominador = 2 * h;
    return numerador / denominador;
}

// Função melhorada para calcular a derivada usando a extrapolação de Richardson
double richardsonExtrapolation(double (*f)(double, double, double), double h, double x1, double a1, double a2)
{
    double numerador = 4 * derivadaCentral(f, 2 * h, x1, a1, a2) - derivadaCentral(f, h, x1, a1, a2);
    double denominador = 3;
    return numerador / denominador;
}

// Método de Newton-Raphson utilizando derivada calculada numericamente
double newton_raphson_derivada_numerica(u_int k_maxAtt, double x1Att, double a3Att, double a2Att, double e1Att, double e2Att, double hAtt, vector<vector<string>> &tabela)
{
    k = 0;
    k_max = k_maxAtt;
    e1 = e1Att;
    e2 = e2Att;
    h = hAtt;

    double f1 = pendulo(x1Att, a3Att, a2Att);                       // Função f(x)
    double f2 = derivada_numerica(pendulo, h, x1Att, a3Att, a2Att); // Função f'(x)
    double x2 = x - (f1 / f2);

    if (abs(f1) < e1)
    { // Primeira checagem de parada
        tabela.push_back({to_string(k), to_string(x1Att), to_string(f1), to_string(f2), to_string(abs(x2 - x1Att))});
        return x;
    }

    while (k < k_max)
    {
        k++;
        f1 = pendulo(x1Att, a3Att, a2Att);
        f2 = derivada_numerica(pendulo, h, x1Att, a3Att, a2Att);
        x2 = x - (f1 / f2); // x' = x - f(x)/f'(x)

        tabela.push_back({to_string(k), to_string(x1Att), to_string(f1), to_string(f2), to_string(abs(x2 - x1Att))});

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

    while (!cin)
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

    while (!cin)
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

    while (!cin)
    {
        cout << "Entrada inválida, tente novamente.\n";
        cin.clear();
        cin.ignore();
        cin >> entrada[n];
    }
}

void loop_print_vazio(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << " ";
    }
}

void print_tabela(vector<vector<string>> &tabela, string metodo)
{
    vector<int> max_char_coluna(tabela[0].size());
    int aux = 0;
    for (int i = 0; i < tabela.size(); i++)
    {
        aux = 0;
        for (int j = 0; j < tabela[0].size(); j++)
        {
            if (tabela[i][j].length() > aux)
            {
                aux = tabela[i][j].length();
            }
        }
        max_char_coluna[i] = aux + 2;
    }

    if (max_char_coluna[4] < 16)
    {
        max_char_coluna[4] = 20;
    }

    cout << metodo;
    cout << "\nK";
    loop_print_vazio(max_char_coluna[0] - 1);
    cout << "X";
    loop_print_vazio(max_char_coluna[1] - 1);
    cout << "f(x)";
    loop_print_vazio(max_char_coluna[2] - 4);
    cout << "f'(x)";
    loop_print_vazio(max_char_coluna[3] - 5);
    cout << "| X[k] - X[k-1]|";
    loop_print_vazio(max_char_coluna[4] - 16);
    cout << "\n";
    for (int i = 0; i < tabela.size(); i++)
    {
        for (int j = 0; j < tabela[0].size(); j++)
        {
            cout << tabela[i][j] << " ";
            loop_print_vazio(max_char_coluna[j] - tabela[i][j].length());
        }
        cout << endl;
    }
    cout << endl;
}

void print_resultado(vector<vector<vector<string>>> &tabela, string metodo)
{
    for (int i = 0; i < tabela.size(); i++)
    {
        cout << "\nDados lambda: " << l[i] << " - A3: " << a3[i] << " - A2: " << a2[i] << endl;
        cout << metodo << "  ";
        cout << "\nK ";
        loop_print_vazio(tabela[i][tabela[i].size() - 1][0].size() - 1);
        cout << "X";
        loop_print_vazio(tabela[i][tabela[i].size() - 1][1].size() - 1);
        cout << "f(x)";
        loop_print_vazio(tabela[i][tabela[i].size() - 1][2].size() - 3);
        cout << "f'(x)";
        loop_print_vazio(tabela[i][tabela[i].size() - 1][3].size() - 4);
        cout << "| X[k] - X[k-1]|";
        loop_print_vazio(tabela[i][tabela[i].size() - 1][4].size() - 14);
        cout << "\n";

        cout << "";
        for (int j = 0; j < tabela[i][0].size(); j++)
        {
            cout << tabela[i][tabela[i].size() - 1][j] << " ";
            cout << abs((int)tabela[i][tabela[i].size() - 1][j].length() - (int)tabela[i][tabela[i].size() - 2][j].length());
            loop_print_vazio(abs((int)tabela[i][tabela[i].size() - 1][j].length() - (int)tabela[i][tabela[i].size() - 2][j].length()));
        }
        cout << "\n";
    }
}

void print_tabela_comparativo(vector<vector<vector<string>>> tabela_newton, vector<vector<vector<string>>> tabela_newton_lambda, vector<vector<vector<string>>> tabela_newton_numerico)
{

    for (int i = 0; i < tabela_newton.size(); i++)
    {
        cout << "\nDados lambda: " << l[i] << " - A3: " << a3[i] << " - A2: " << a2[i] << endl;
        print_tabela(tabela_newton[i], "Método de newton");
    }
    for (int i = 0; i < tabela_newton.size(); i++)
    {
        cout << "\nDados lambda: " << l[i] << " - A3: " << a3[i] << " - A2: " << a2[i] << endl;
        print_tabela(tabela_newton_lambda[i], "Método de newton com uso de lâmbda");
    }
    for (int i = 0; i < tabela_newton.size(); i++)
    {
        cout << "\nDados lambda: " << l[i] << " - A3: " << a3[i] << " - A2: " << a2[i] << endl;
        print_tabela(tabela_newton_numerico[i], "Método de newton com uso de derivada numérica");
    }
}

int main()
{
    u_int n;
    insercao_u_int(n, "o número de lambdas (0 para rodar o caso padrão):");
    bool calibragem = false;
    if (n > 0)
    {
        vector<double> a3(n);
        vector<double> a2(n);
        vector<double> x0(n);
        vector<double> l(n);

        insercao_u_int(k_max, "o limite de iterações: ");
        insercao_u_int(precisao, "o número de casa decimais depois da vírgula(máximo 15): ");

        insercao_double(e1, "a precisão de ε1: ");
        insercao_double(e2, "a precisão de ε2: ");

        for (u_int i = 0; i < n; i++)
        {
            string iesimo = "o valor do ";
            iesimo += to_string(i + 1);
            iesimo += "º ";

            insercao_vector_double(l, i, iesimo + "lambda: ");
            insercao_vector_double(x0, i, iesimo + "x0: ");
            insercao_vector_double(a3, i, iesimo + "a3: ");
            insercao_vector_double(a2, i, iesimo + "a2: ");
        }
    }
    else
    {
        calibragem = true;
    }

    vector<vector<string>> tabela_newton(1, vector<string>(5));
    vector<vector<string>> tabela_newton_lambda(1, vector<string>(5));
    vector<vector<string>> tabela_newton_numerico(1, vector<string>(5));

    vector<vector<vector<string>>> tabelas_newton = {};
    vector<vector<vector<string>>> tabelas_newton_lambda = {};
    vector<vector<vector<string>>> tabelas_newton_numerico = {};

    cout << fixed << setprecision(precisao);

    // ASCII usado na tabela
    // ━  ┃
    // ┏┳┓
    // ┣╋┫
    // ┗┻┛
    //
    // ═  ║
    // ╔  ╦  ╗
    // ╠  ╬  ╣
    // ╚  ╩  ╝

    // Tabela resumida
    // ┏━━━━━━━━┳━━━┳━━━━━━┓
    // ┃ método ┃ k ┃ raíz ┃
    // ┣━━━━━━━━╋━━━╋━━━━━━┫

    for (int i = 0; i < n; i++)
    {
        newton_raphson(k_max, x0[i], a3[i], a2[i], e1, e2, tabela_newton);
        newton_raphson_fl(k_max, x0[i], a3[i], a2[i], e1, e2, l[i], tabela_newton_lambda);
        newton_raphson_derivada_numerica(k_max, x0[i], a3[i], a2[i], e1, e2, h, tabela_newton_numerico);
        tabelas_newton.push_back(tabela_newton);
        tabelas_newton_lambda.push_back(tabela_newton_lambda);
        tabelas_newton_numerico.push_back(tabela_newton_numerico);
        vector<vector<string>> tabela_newton(1, vector<string>(5, 0));
        vector<vector<string>> tabela_newton_lambda(1, vector<string>(5, 0));
        vector<vector<string>> tabela_newton_numerico(1, vector<string>(5, 0));
    }

    if (calibragem)
    {
        // double testePendulo = pendulo(1.0, 1.0, 1.0); // deve dar -5
        // cout << "\nValor do teste de f(x): " << testePendulo << endl;

        // double testeDerivadaPendulo = derivadaPendulo(1.0, 1.0, 1.0); // deve dar -6
        // cout << "\nValor do teste de f'(x): " << testeDerivadaPendulo << endl;

        newton_raphson(k_max, x0[0], a3[0], a2[0], e1, e2, tabela_newton);
        newton_raphson_fl(k_max, x0[0], a3[0], a2[0], e1, e2, l[0], tabela_newton_lambda);
        newton_raphson_derivada_numerica(k_max, x0[0], a3[0], a2[0], e1, e2, h, tabela_newton_numerico);
        tabelas_newton.push_back(tabela_newton);
        tabelas_newton_lambda.push_back(tabela_newton_lambda);
        tabelas_newton_numerico.push_back(tabela_newton_numerico);
    }

    int escolha;
    cout << "\nValores calculados!\nInsira\n1 para exibir um comparativo de todos os métodos,\n2 para exibir o resultado do método de newton,\n3 parar exibir o resultado do método de newton utilizando lâmbda\n4 para exibir resultado do método de newton utilizando derivada numérica:";
    cin >> escolha;
    cout << endl;

    switch (escolha)
    {
    case 1:
        print_tabela_comparativo(tabelas_newton, tabelas_newton_lambda, tabelas_newton_numerico);
        break;

    case 2:
        print_resultado(tabelas_newton, "método de newton");
        break;

    case 3:
        print_resultado(tabelas_newton_lambda, "método de newtom-lâmbda");
        break;

    case 4:
        print_resultado(tabelas_newton_numerico, "método de newton-derivada numérica");
        break;

    default:
        break;
    }

    return 0;
}