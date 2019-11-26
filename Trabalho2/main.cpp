#include <iostream>
#include <vector>

using namespace std;

class Matriz
{
private:
    int n;                        // Linhas e colunas da matriz
    vector<vector<double>> matriz; // Vector 2D contendo os dados da matriz

public:
    Matriz(); // Inicializador da matriz
    Matriz(vector<vector<double>>);
    ~Matriz();        // Destrutor da matriz
    int getTamanho(); // Retorna tamanho n da matriz NxN
    void gauss();   // Resolver por Gauss
    vector<double> get(int);
    double get(int, int);       // Acessa elemento da matriz
    void set(int, int, double); // Altera elemento da matriz
    void print();
};

Matriz::Matriz()
{
    this->n = 1;
    this->matriz = {{}};
}

Matriz::Matriz(vector<vector<double>> dados)
{
    this->n = dados.size();
    this->matriz = dados;
}

Matriz::~Matriz()
{
    this->n = 0;
    this->matriz.clear();
    this->matriz.shrink_to_fit();
}

int Matriz::getTamanho()
{
    return this->n;
}

vector<double> Matriz::get(int aLinha)
{
    return this->matriz[aLinha - 1];
}

double Matriz::get(int aLinha, int aColuna)
{
    return this->matriz[aLinha - 1][aColuna - 1];
}

void Matriz::set(int aLinha, int aColuna, double valor)
{
    this->matriz[aLinha - 1][aColuna - 1] = valor;
}

void Matriz::gauss()
{
    double novoValor = 0;
    for (int i = 1; i < this->getTamanho(); i++)
    {
        double pivo = this->get(i, i);
        // vector<double> multiplicador;

        for (int j = i + 1; j <= this->getTamanho(); j++)
        {
            double multiplicador = (this->get(j, i) / pivo);
            // cout << "\nget(j, i): " << this->get(j, i) << endl;
            // cout << "pivo: " << pivo << endl;
            // cout << "m: " << multiplicador << endl;
            for (int k = i; k <= this->getTamanho(); k++)
            {
                novoValor = (double(this->get(j, k)) - double(multiplicador * double(this->get(i, k))));
                // cout << "(j, k): " << this->get(j, k) << "\n(i, k): " << this->get(i, k) << endl;
                // cout << "subtraindo: " << float(multiplicador * this->get(i, k)) << endl;
                // cout << i << ", " << j << ", " << k << ":" << (this->get(j, k) - double(multiplicador * this->get(i, k))) << endl << endl;
                // cout << type_info(this->get(j, k)) << endl;
                this->set(j, k, novoValor);
            }
        }
    };
}

void Matriz::print()
{
    for (int i = 0; i < this->getTamanho(); i++)
    {
        for (int j = 0; j < this->getTamanho(); j++)
        {
            cout.width(8);
            cout << this->get(i + 1, j + 1) << " ";
        }
        cout << endl;
    }
}

// Globais
int n;   // Número de pêndulos
double a; // Parâmetro 'a' em 'a*d' da amplitude

int main()
{
    // vector<vector<double>> dadosTeste1d = {{1, 10, 100}, {10, 1, 100}, {100, 1000, 1}};
    // vector<vector<double>> dadosTeste1d = {{10.0f, 1.0f, 1.0f}, {1.0f, 10.0f, 1.0f}, {1.0f, 1.0f, 10.0f}};
    vector<vector<double>> dadosTeste1d = {{10.0, 1.0, 1.0}, {1.0, 10.0, 1.0}, {1.0, 1.0, 10.0}};
    Matriz teste1d(dadosTeste1d);

    // cout << "\n(2):\n";
    // vector<double> linha2 = teste1d.get(2);
    // for (int i = 0; i < teste1d.getTamanho(); i++)
    // {
    //     cout << linha2[i] << " ";
    // }
    // cout << endl;

    // cout << "\n(1, 1):\n";
    // cout << teste1d.get(1, 1) << endl;

    // teste1d.print();

    // cout << 1.0f - 1.0f/10.0f * 10.0f << endl;
    
    teste1d.gauss();
    teste1d.print();

    // vector<vector<double>> testeZero = {{10.0f, 1.0f, 1.0f}, {1.0f, 10.0f, 1.0f}, {1.0f, 1.0f, 10.0f}};
    // testeZero[1][1] = 99.0f;
    // cout << testeZero[1][1] << endl;

    return 0;
}