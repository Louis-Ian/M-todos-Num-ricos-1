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
    void montarB(vector<float>, float); // Monta a matriz A com o vetor B e o parâmetro a
    float determinante();        // Calcula determinante da matriz
    void gauss();                // Eliminação de Gauss
    void gauss_jordan();         // Eliminação de Gaus-Jordan
    void resolveGauss();         // Resolve por Gauss. presume existencia de coluna b de 'Ax=b'
    void printDeslocamentos();   // Imprime os valores d
    void printAmplitudes();       // Imprime os valores a*d
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
    this->deslocamentos = vector<float>(dados.size(), 0.0f); // Inicializa o vetor dos deslocamentos para ter o tamanho correto,
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
    // Imprime a matriz
    for (int i = 0; i < this->getLinhas(); i++)
    {
        for (int j = 0; j < this->getColunas(); j++)
        {
            cout.width(12);
            cout << this->get(i + 1, j + 1) << " ";
        }
        cout << endl;
    }

    // Imprime os deslocamentos
    for (int i = 0; i < this->deslocamentos.size(); i++)
    {
        cout.width(12);
        cout << this->deslocamentos[i]  << " ";
    }
    cout << endl << endl;
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

void Matriz::montarB(vector<float> b, float a)
{
    if (b.size() == this->linhas)
    {
        this->colunas++;
        for (int i = 0; i < this->linhas; i++)
        {
            this->matriz[i].push_back(b[i]);
        }
        this->deslocamentos.push_back(a);
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

void Matriz::gauss_jordan()
{
    float novoValor = 0.0f;
    float pivo = 0.0f;
    float multiplicador = 0.0f;
    for (int i = 1; i <= this->getLinhas(); i++)
    {
        pivo = this->get(i, i);
        for (int j = 1; j <= this->getLinhas(); j++)
        {
            if (j != i)
            {
                multiplicador = this->get(j, i) / pivo;
                for (int k = i; k <= this->getColunas(); k++)
                {
                    novoValor = this->get(j, k) - multiplicador * this->get(i, k);
                    this->set(j, k, novoValor);
                }
            }
        }
    };
}

void Matriz::resolveGauss()
{
    this->gauss();
    int ultimaColuna = this->colunas - 1;
    for (int i = this->linhas - 1; i >= 0; i--)
    {
        this->deslocamentos[i] = this->matriz[i][ultimaColuna];
        for (int j = this->linhas - 1; j > i; j--)
        {
            this->deslocamentos[i] -= this->deslocamentos[j] * this->matriz[i][j];
        }
        this->deslocamentos[i] /= this->matriz[i][i];
    }
}

void Matriz::printDeslocamentos()
{
    cout << endl;
    cout << "Deslocamentos: ";
    for(int i = 0; i < colunas - 1; i++)
    {
        cout << this->deslocamentos[i] << " ";
    }
    cout << endl;
}

void Matriz::printAmplitudes()
{
    float a = deslocamentos[colunas-1];

    cout << endl;
    cout << "Amplitudes de deslocamento: ";
    for(int i = 0; i < colunas - 1; i++)
    {
        cout << a*deslocamentos[i] << "  ";
    }
    cout << endl;
}

// Globais
int n;   // Número de pêndulos
float a; // Parâmetro 'a' em 'a*d' da amplitude
Matriz matriz;

void boot()
{
    cout.width(6);
    cout << "\nMENU:\n";
    cout << "Insira:\n";
    cout << "0 para parar o programa.\n";
    cout << "1 para resolver uma matriz por Gauss.\n";
    cout << "2 para resolver uma matriz por Gauss-Jordan.\n";
    cout << "3 para resumir soluções de uma matriz.\n";
    cout << "9 para calibrar o sistema.\n";
}

void shutdown()
{
    cout << "FIM DO PROGRAMA.\n";
}

Matriz input()
{
    int n = 0;
    cout << "Insira o tamanho da matriz: ";
    cin >> n;

    float a = 0.0f;
    cout << "\nInsira o valor do parametro a: ";
    cin >> a;

    vector<float> init1(n, 0.0f);
    vector<vector<float>> entrada(n, init1);
    cout << endl << "Insira os termos da matriz.";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << endl << i + 1 << "," << j + 1<< ":";
            cin >> entrada[i][j];
        }
    }

    cout << endl << "Insira os termos do vetor.";
    vector<float> init2(n, 0.0f);
    for(int i = 0; i < n; i++)
    {
        cout << endl << i + 1 << ":";
        cin >> init2[i];
    }

    Matriz r(entrada);
    r.montarB(init2, a);

    return r;
}

int inputMenu()
{
    int menu;
    Matriz matrizCalibragem({{10.0f, 1.0f, 1.0f}, {1.0f, 10.0f, 1.0f}, {1.0f, 1.0f, 10.0f}}); // Matriz C da questão;
    vector<float> vetorV = {12.0f, 12.0f, 12.0f}; // Vetor V da questão
    Matriz mGauss;
    Matriz mGaussJordan;


    cin >> menu;

    switch (menu)
    {
    case 0:
        return 0;
    case 1:
        matriz = input();
        matriz.print();
        matriz.gauss();
        matriz.resolveGauss();
        return 99;
    case 2:
        matriz = input();
        matriz.print();
        matriz.gauss_jordan();
        matriz.resolveGauss();
        return 99;
    case 3:
        matriz = input();
        
        mGauss = matriz;
        cout << "\nGAUSS:\n";
        mGauss.gauss();
        mGauss.resolveGauss();
        mGauss.print();
        mGauss.printDeslocamentos();
        mGauss.printAmplitudes();

        cout << "\nGAUSS-JORDAN:\n";
        mGaussJordan = matriz;
        mGaussJordan.gauss_jordan();
        mGaussJordan.resolveGauss();
        mGaussJordan.print();
        mGaussJordan.printDeslocamentos();
        mGaussJordan.printAmplitudes();

        return 1;
    case 9:
        matriz = matrizCalibragem;
        matriz.montarB(vetorV, 1.0f);
        cout << "\nMATRIZ:\n";
        matriz.print();

        cout << "\nGAUSS:\n";
        mGauss = matriz;
        mGauss.gauss();
        mGauss.resolveGauss();
        mGauss.print();
        mGauss.printDeslocamentos();
        mGauss.printAmplitudes();

        cout << "\nGAUSS-JORDAN:\n";
        mGaussJordan = matriz;
        mGaussJordan.gauss_jordan();
        mGaussJordan.resolveGauss();
        mGaussJordan.print();
        mGaussJordan.printDeslocamentos();
        mGaussJordan.printAmplitudes();
        
        return 1;
    default:
        cout << "Entrada invalida. Tente novamente.\n\n";
        boot();
        return 1;
        break;
    }

    return 0;
}

int main()
{
    int menu = 1;
    while (menu != 0)
    {
        boot();
        menu = inputMenu();
        if(menu == 99)
        {
            matriz.print();
            matriz.printDeslocamentos();
            matriz.printAmplitudes();
        }
    }
    shutdown();

    return 0;
}
