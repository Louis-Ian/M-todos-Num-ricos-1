#include <iostream>
#include <vector>

using namespace std;

class Matriz
{
private:
    int linhas, colunas;          // Linhas e colunas da matriz
    vector<vector<float>> matriz; // Vector 2D contendo os dados da matriz

public:
    Matriz(); // Inicializador da matriz
    Matriz(int, int, vector<vector<float>>);
    ~Matriz();      // Destrutor da matriz
    int getLinhas();
    int getColunas();
    Matriz Gauss(); // Resolver por Gauss
    vector<float> get(int);
    float get(int, int);
};

Matriz::Matriz()
{
    this->linhas = 1;
    this->colunas = 1;
    this->matriz = {{}};
}

Matriz::Matriz(int aLinhas, int aColunas, vector<vector<float>> dados) // TODO estabelecer como os dados da matriz são inseridos
{
    this->linhas = aLinhas;
    this->colunas = aColunas;
    this->matriz = dados;
}

Matriz::~Matriz()
{
    this->linhas = 0;
    this->colunas = 0;
    this->matriz.clear();
    this->matriz.shrink_to_fit();
}

int Matriz::getLinhas()
{
    return this->linhas;
}

int Matriz::getColunas()
{
    return this->colunas;
}

vector<float> Matriz::get(int aLinha)
{
    return this->matriz[aLinha-1];    
}

float Matriz::get(int aLinha, int aColuna)
{
    return this->matriz[aLinha-1][aColuna-1];
}

Matriz Matriz::Gauss()
{
    for (int i = 0; i < this->linhas; i++)
    {
        float pivo = this->get(i, i);
    };
}

// Globais
int n;   // Número de pêndulos
float a; // Parâmetro 'a' em 'a*d' da amplitude

int main()
{
    vector<vector<float>> dadosTeste1d = {{10, 1, 1}, {1, 10, 1}, {1, 1, 10}};
    Matriz teste1d(1, 4, dadosTeste1d);

    cout << "\n(2):\n";
    vector<float> linha2 = teste1d.get(2);
    for(int i = 0; i < teste1d.getLinhas; i++)
    {
        cout << linha2[i] << endl;
    }

    cout << "\n(1, 1):\n";
    cout << teste1d.get(1, 1) << endl;

    return 0;
}