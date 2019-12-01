#include <iostream>
#include <vector>

using namespace std;

class Matriz
{
private:
    int linhas, colunas;          // Linhas e colunas da matriz
    vector<vector<float>> matriz; // Vector 2D contendo os dados da matriz
    vector<float> deslocamentos;  // Vector com os valores dos deeslocamentos solução

public:
    Matriz(); // Inicializador da matriz
    Matriz(vector<vector<float>>);
    ~Matriz();                   // Destrutor da matriz
    int getLinhas();             // Retorna o numero de linhas da matriz
    int getColunas();            // Retirna o numero de colunas da matriz
    void print();                // Imprime a matriz
    vector<float> get(int);      // Retorna linha da matriz
    float get(int, int);         // Retorna elemento da matriz
    void set(int, int, float);   // Altera elemento da matriz
    void montarB(vector<float>); // Monta a matriz A com o vetor B
    float determinante();        // Calcula determinante da matriz
    void gauss();                // Eliminação de Gauss
    void resolveGauss();         // Resolve por Gauss. presume existencia de coluna b de 'Ax=b'
    void gaussJordan();          // Calcula a matriz por meio do Método de Gauss-Jordan
};

Matriz::Matriz()
{
    this->linhas = 1;
    this->colunas = 1;
    this->matriz = {{}};
    this->deslocamentos = {};
}

Matriz::Matriz(vector<vector<float>> dados)
{
    this->linhas = dados.size();
    this->colunas = dados[0].size();
    this->matriz = dados;
    this->deslocamentos = vector<float>(dados.size(), 0); // Inicializa o vetor dos deslocamentos para ter o tamanho correto,
                                                          // e todos os elementos são 0
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

void Matriz::print()
{
    for (int i = 0; i < this->getLinhas(); i++)
    {
        for (int j = 0; j < this->getColunas(); j++)
        {
            cout.width(12);
            cout << this->get(i + 1, j + 1) << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < this->deslocamentos.size(); i++)
    {
        cout.width(12);
        cout << this->deslocamentos[i];
    }
    cout << endl;
}

float Matriz::determinante() // TODO finalizar determinante
{
    vector<float> auxiliares(this->linhas);
    for (int i = 0; i < auxiliares.size(); i++)
    {
        auxiliares[i] = 0;
    }

    for (int i = 0; i < this->linhas; i++)
    {
        // auxiliares
    }
}

void Matriz::montarB(vector<float> b)
{
    if (b.size() == this->linhas)
    {
        this->colunas++;
        for (int i = 0; i < this->linhas; i++)
        {
            this->matriz[i].push_back(b[i]);
        }
    }
    else
    {
        cout << "B tem tamanho invalido\n";
    }
}

void Matriz::gauss()
{
    float novoValor = 0.0f;
    float pivo = 0.0f;
    for (int i = 1; i < this->getLinhas(); i++)
    {
        pivo = this->get(i, i);
        for (int j = i + 1; j <= this->getLinhas(); j++)
        {
            float multiplicador = this->get(j, i) / pivo;
            for (int k = i; k <= this->getColunas(); k++)
            {
                novoValor = this->get(j, k) - multiplicador * this->get(i, k);
                this->set(j, k, novoValor);
            }
        }
    };
}

void Matriz::resolveGauss()
{
    this->gauss();
    int ultimaColuna = this->colunas - 1;
    for(int i = this->linhas - 1; i >= 0; i--)
    {
        this->deslocamentos[i] = this->matriz[i][ultimaColuna];
        for(int j = this->linhas - 1; j > i; j--)
        {
            this->deslocamentos[i] -= this->deslocamentos[j]*this->matriz[i][j];
        }
        this->deslocamentos[i] /= this->matriz[i][i];
    }
}

void Matriz::gaussJordan(){
    float pivo = 0.0f;
    float novoValor = 0.0f;
    // Encontra o pivô por linha da matriz.
    for (int i = 1; i < this->getLinhas(); i++){
        pivo = this->get(i, i);     // Localiza o elemento aij da matriz, i = j, para ser o pivô.
        for (int j = 1; j <= this->getColunas(); j++){
            novoValor = this->get(j, i) / pivo;     // Aqui, cada elemento da linha é dividido pelo pivô, incluindo ele mesmo.
        }
        // A partir daqui, os valores das linhas que sobram são calculados: 
        for (int k = i; k <= this->getLinhas(); k++){
            if (k != i){
                float multiplicador = this->get(k, i);  // No Gauss-Jordan, não precisa dividir o aij, i != j, pelo pivô.
                // Aqui, calculamos os novos aij:
                for (int l = i; l <= getColunas(); l++){
                    novoValor = this->get(k, l) - multiplicador * this->get(i, l);
                    this->set(k, l, novoValor);
                }
            }
        }
    }
}

// Globais
int n;   // Número de pêndulos
float a; // Parâmetro 'a' em 'a*d' da amplitude

Matriz input() // TODO Função que permite input de dados de uma matriz
{
}

int main()
{
    vector<vector<float>> dadosTeste1d = {{10.0f, 1.0f, 1.0f}, {1.0f, 10.0f, 1.0f}, {1.0f, 1.0f, 10.0f}}; // Matriz C da questão
    // vector<vector<float>> dadosTeste1d = {{10.0, 1.0, 1.0}, {1.0, 10.0, 1.0}, {1.0, 1.0, 10.0}};
    vector<float> testeB = {12.0f, 12.0f, 12.0f}; // Vetor V da questão
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
    teste1d.resolveGauss();
    teste1d.print();

    return 0;
}
