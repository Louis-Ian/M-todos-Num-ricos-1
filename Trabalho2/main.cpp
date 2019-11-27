#include <iostream>
#include <vector>

using namespace std;

class Matriz
{
private:
    int linhas, colunas;                         // Linhas e colunas da matriz
    vector<vector<float>> matriz; // Vector 2D contendo os dados da matriz

public:
    Matriz(); // Inicializador da matriz
    Matriz(vector<vector<float>>);
    ~Matriz();        // Destrutor da matriz
    int getLinhas(); // Retorna o numero de linhas da matriz
    int getColunas();   // Retirna o numero de colunas da matriz
    void gauss();     // Resolver por Gauss
    vector<float> get(int);
    float get(int, int);       // Acessa elemento da matriz
    void set(int, int, float); // Altera elemento da matriz
    void print();
    void montarB(vector<float>); // Monta a matriz A com o vetor B
};

Matriz::Matriz()
{
    this->linhas = 1;
    this->colunas = 1;
    this->matriz = {{}};
}

Matriz::Matriz(vector<vector<float>> dados)
{
    this->linhas = dados.size();
    this->colunas = dados[0].size();
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
    return this->matriz[aLinha - 1];
}

float Matriz::get(int aLinha, int aColuna)
{
    return this->matriz[aLinha - 1][aColuna - 1];
}

void Matriz::set(int aLinha, int aColuna, float valor)
{
    this->matriz[aLinha - 1][aColuna - 1] = valor;
}

void Matriz::gauss()
{
    float novoValor = 0;
    for (int i = 1; i < this->getLinhas(); i++)
    {
        float pivo = this->get(i, i);
        // vector<float> multiplicador;

        for (int j = i + 1; j <= this->getLinhas(); j++)
        {
            float multiplicador = (this->get(j, i) / pivo);
            // cout << "\nget(j, i): " << this->get(j, i) << endl;
            // cout << "pivo: " << pivo << endl;
            // cout << "m: " << multiplicador << endl;
            for (int k = i; k <= this->getColunas(); k++)
            {
                novoValor = (float(this->get(j, k)) - float(multiplicador * float(this->get(i, k))));
                // cout << "(j, k): " << this->get(j, k) << "\n(i, k): " << this->get(i, k) << endl;
                // cout << "subtraindo: " << float(multiplicador * this->get(i, k)) << endl;
                // cout << i << ", " << j << ", " << k << ":" << (this->get(j, k) - float(multiplicador * this->get(i, k))) << endl << endl;
                // cout << type_info(this->get(j, k)) << endl;
                this->set(j, k, novoValor);
            }
        }
    };
}

void Matriz::print()
{
    for (int i = 0; i < this->getLinhas(); i++)
    {
        // cout << "I: " << i << endl;
        for (int j = 0; j < this->getColunas(); j++)
        {
            // cout << "J: " << j << endl;
            cout.width(12);
            cout << this->get(i + 1, j + 1) << " ";
        }
        cout << endl;
    }
}

void Matriz::montarB(vector<float> b)
{
    if(b.size() == this->linhas)
    {   
        this->colunas++;
        for(int i = 0; i < this->linhas; i++)
        {
            this->matriz[i].push_back(b[i]);
        }
    } else {
        cout << "B tem tamanho invalido\n";
    }
}

// Globais
int n;    // Número de pêndulos
float a; // Parâmetro 'a' em 'a*d' da amplitude

int main()
{
    vector<vector<float>> dadosTeste1d = {{10.0f, 1.0f, 1.0f}, {1.0f, 10.0f, 1.0f}, {1.0f, 1.0f, 10.0f}};
    // vector<vector<float>> dadosTeste1d = {{10.0, 1.0, 1.0}, {1.0, 10.0, 1.0}, {1.0, 1.0, 10.0}};
    vector<float> testeB = {12.0f, 12.0f, 12.0f};
    Matriz teste1d(dadosTeste1d);
    teste1d.montarB(testeB);

    // cout << "\n(2):\n";
    // vector<float> linha2 = teste1d.get(2);
    // for (int i = 0; i < teste1d.getLinhas(); i++)
    // {
    //     cout << linha2[i] << " ";
    // }
    // cout << endl;

    // cout << "\n(1, 1):\n";
    // cout << teste1d.get(1, 1) << endl;

    teste1d.print();
    cout << endl;
    teste1d.gauss();
    teste1d.print();

    return 0;
}