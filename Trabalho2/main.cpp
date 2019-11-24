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
    Matriz(int aLinhas, int aColunas);
    ~Matriz(); // Destrutor da matriz
};

Matriz::Matriz()
{
    this->linhas = 1;
    this->colunas = 1;
    this->matriz = {{}};
}

Matriz::Matriz(int aLinhas, int aColunas)
{
    this->linhas = aLinhas;
    this->colunas = aColunas;
    this->matriz;
}

Matriz::~Matriz()
{
    this->linhas = 0;
    this->colunas = 0;
    this->matriz.clear();
    this->matriz.shrink_to_fit();
}

// Globais
int n;      // Número de pêndulos
float a;    // Parâmetro 'a' em 'a*d' da amplitude

int main()
{

    return 0;
}