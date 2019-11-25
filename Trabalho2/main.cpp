#include <iostream>
#include <vector>

using namespace std;

class Matriz
{
private:
    int n;                        // Linhas e colunas da matriz
    vector<vector<float>> matriz; // Vector 2D contendo os dados da matriz

public:
    Matriz(); // Inicializador da matriz
    Matriz(vector<vector<float>>);
    ~Matriz();        // Destrutor da matriz
    int getTamanho(); // Retorna tamanho n da matriz NxN
    Matriz Gauss();   // Resolver por Gauss
    vector<float> get(int);
    float get(int, int);
};

Matriz::Matriz()
{
    this->n = 1;
    this->matriz = {{}};
}

Matriz::Matriz(vector<vector<float>> dados)
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

vector<float> Matriz::get(int aLinha)
{
    return this->matriz[aLinha - 1];
}

float Matriz::get(int aLinha, int aColuna)
{
    return this->matriz[aLinha - 1][aColuna - 1];
}

Matriz Matriz::Gauss()
{
    for (int i = 0; i < this->n; i++)
    {
        float pivo = this->get(i, i);
    };
}

// Globais
int n;   // Número de pêndulos
float a; // Parâmetro 'a' em 'a*d' da amplitude

int main()
{
    vector<vector<float>> dadosTeste1d = {{1, 9, 8}, {7, 6, 5}, {4, 3, 2}};
    Matriz teste1d(dadosTeste1d);

    cout << "\n(2):\n";
    vector<float> linha2 = teste1d.get(2);
    for (int i = 0; i < teste1d.getTamanho(); i++)
    {
        cout << linha2[i] << " ";
    }
    cout << endl;

    cout << "\n(1, 1):\n";
    cout << teste1d.get(1, 1) << endl;

    return 0;
}