// Aluno: Rodrigo Mattos Scavassin		TIA: 32055374
#include "TGrafo.h"
#include "filaCircular.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <stdlib.h>

const int MAX = 80;
const std::string delimiter = " ";

// método criado para calcular o percurso em profundidade e em largura.
int noAdjacente(int n_, int nosMarcados[], int n, int *adj[], int nroNosMarcados)
{
    bool estaMarcado = false;
    for (int i = 0; i < n; i++)
    {
        if (adj[n_][i] != 0)
        {
            for (int j = 0; j < nroNosMarcados; j++)
            {
                if (nosMarcados[j] == i)
                    estaMarcado = true;
            }
            if (!estaMarcado)
                return i;
            else
                estaMarcado = false;
        }
    }
    return -1;
}

// Método que identifica se o vértice encontra-se no percurso
bool verticeNoPercurso(int v, int percurso[], int n)
{
    for (int i = 0; i < n; i++)
        if (v == percurso[i])
            return true;
    return false;
}

// Algorítmo de Floyd para cálculo do caminho mínimo
void floyd(int v, int *adj[], int *distancia[], int *rota[], int n)
{
    // Inicia a matriz de distancias/tempo
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j)
                distancia[i][j] = 0;
            else if (adj[i][j] == std::numeric_limits<int>::infinity())
                distancia[i][j] = 999999999; // Por algum motivo, não consegui usar o infinito para comparações, então substituí por um número alto
            else
                distancia[i][j] = adj[i][j];

    // Incia a matriz de rotas
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adj[i][j] != std::numeric_limits<int>::infinity())
                rota[i][j] = j;
            else
                rota[i][j] = 0;
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j && distancia[i][k] + distancia[k][j] < distancia[i][j])
                {
                    distancia[i][j] = distancia[i][k] + distancia[k][j];
                    rota[i][j] = rota[i][k];
                }
            }
        }
    }
}

// Método que imprime o melhor caminho e o total da distancia/tempo percorridos com base no algorítmo de Floyd
void caminhoMinimo(int v, int w, int *distancia[], int *rota[], std::string rotulo[], int n)
{
    int inicio = v;
    int caminho[n];
    for (int i = 0; i < n; i++)
        caminho[i] = -1;
    caminho[0] = v;
    int i = 1;

    while (v != w && i < n)
    {
        v = rota[v][w];
        caminho[i] = v;
        i++;
    }

    if (distancia[inicio][w] != 999999999)
        for (int i = 0; i < n; i++)
            if (caminho[i] != -1 && caminho[i + 1] == -1)
                std::cout << rotulo[caminho[i]];
            else if (caminho[i] != -1)
                std::cout << rotulo[caminho[i]] << " -> ";
            else
                break;
    else
        std::cout << "Rota não encontrada. Grafo desconexo.";
    std::cout << "\nTOTAL= " << distancia[inicio][w];
}

// Construtor do TGrafo, responsável por
// Criar a matriz de adjacência v x v do Grafo
TGrafo::TGrafo(int n)
{
    this->n = n;
    this->m = 0;
    this->tipoGrafo = 0;
    this->rotulo = new std::string[n];

    // aloca da matriz de distância do TGrafo
    int **adjacDistancia = new int *[n];
    for (int i = 0; i < n; i++)
        adjacDistancia[i] = new int[n];
    adjDistancia = adjacDistancia;
    // Inicia a matriz com valores infinitos
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjDistancia[i][j] = std::numeric_limits<int>::infinity();

    // aloca da matriz de Tempo do TGrafo
    int **adjacTempo = new int *[n];
    for (int i = 0; i < n; i++)
        adjacTempo[i] = new int[n];
    adjTempo = adjacTempo;
    // Inicia a matriz com valores infinitos
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjTempo[i][j] = std::numeric_limits<int>::infinity();
}

TGrafo::TGrafo(std::string fileName)
{
    // Declaração de variáveis
    std::string line;
    std::string aeroporto1;
    std::string aeroporto2;
    int v;
    int w;
    int distancia;
    int tempo;

    // Leitura do arquivo
    int delimiterPosition;
    char buffer[MAX];
    std::ifstream fin(fileName);

    fin.getline(buffer, MAX); // Primeira linha do arquivo refere-se ao tipo de grafo
    this->tipoGrafo = std::stoi(buffer);
    fin.getline(buffer, MAX); // Segunda linha do arquivo corresponde ao número de vértices
    this->n = std::stoi(buffer);

    // aloca da vetor de Rótulo do TGrafo
    this->rotulo = new std::string[n];

    // aloca da matriz de Distancia do TGrafo
    int **adjacDistancia = new int *[n];
    for (int i = 0; i < n; i++)
        adjacDistancia[i] = new int[n];
    adjDistancia = adjacDistancia;
    // Inicia a matriz com valores infinitos
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjDistancia[i][j] = std::numeric_limits<int>::infinity();

    // aloca da matriz de Tempo do TGrafo
    int **adjacTempo = new int *[n];
    for (int i = 0; i < n; i++)
        adjacTempo[i] = new int[n];
    adjTempo = adjacTempo;
    // Inicia a matriz com valores infinitos
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjTempo[i][j] = std::numeric_limits<int>::infinity();

    // Leitura do rótulo dos vértices
    for (int i = 0; i < n; i++)
    {
        fin.getline(buffer, MAX);
        rotulo[i] = buffer;
    }

    // Leitura das arestas

    fin.getline(buffer, MAX); // Esta linha do arquivo corresponde ao número de arestas
    this->m = std::stoi(buffer);

    // Faz a leitura das arestas no arquivo
    while (!fin.eof())
    {
        fin.getline(buffer, MAX);
        line = buffer; // Lê a linha contendo aeroporto1, aeroporto2, distancia e tempo
        delimiterPosition = line.find(delimiter);
        aeroporto1 = line.substr(0, delimiterPosition); // Obtem o aeroporto1
        for (int i = 0; i < n; ++i)
        {
            if (rotulo[i] == aeroporto1) // Obtem a posição do aeroporto1 no vetor de rótulos
                v = i;
        }
        line = line.substr(delimiterPosition + 1);
        delimiterPosition = line.find(delimiter);
        aeroporto2 = line.substr(0, delimiterPosition); // Obtem o aeroporto2
        for (int i = 0; i < n; ++i)
        {
            if (rotulo[i] == aeroporto2) // Obtem a posição do aeroporto2 no vetor de rótulos
                w = i;
        }
        line = line.substr(delimiterPosition + 1);
        delimiterPosition = line.find(delimiter);
        distancia = std::stoi(line.substr(0, delimiterPosition)); // Obtem a distância
        tempo = std::stoi(line.substr(delimiterPosition + 1));
        adjDistancia[v][w] = distancia;
        adjTempo[v][w] = tempo;
    }
}

// Destructor, responsável por
// liberar a memória alocada para a matriz
TGrafo::~TGrafo()
{
    n = 0;
    m = 0;
    delete[] *adjDistancia;
    delete[] *adjTempo;
    std::cout << "espaço liberado.\n";
}

void TGrafo::save()
{
    // Inicializar o arquivo para escrita
    std::ofstream fout("Grafo.txt");

    // Salvar o tipo de grafo
    fout << this->tipoGrafo;

    // Salvar o número de vértices
    fout << "\n"
         << this->n;

    // Salvar os vértices
    for (int i = 0; i < n; i++)
    {
        fout << "\n"
             << rotulo[i];
    }

    // Salvar o número de arestas
    fout << "\n"
         << this->m;

    // Salvar as arestas
    for (int i = 0; i < n; i++)
    {
        for (int w = 0; w < n; w++)
            if (adjDistancia[i][w] != std::numeric_limits<int>::infinity())
                fout << "\n"
                     << rotulo[i] << " " << rotulo[w] << " " << adjDistancia[i][w] << " " << adjTempo[i][w];
    }
}

void TGrafo::insereV(std::string aeroporto)
{
    std::string *newRotulo = new std::string[n + 1];
    for (int i = 0; i < n; i++)
    {
        newRotulo[i] = rotulo[i];
    }
    newRotulo[n] = aeroporto;
    rotulo = newRotulo;

    // Adequa a matriz de Distância
    int **newAdjacDistancia = new int *[n + 1];
    for (int i = 0; i < n + 1; i++)
        newAdjacDistancia[i] = new int[n + 1];
    for (int i = 0; i < n; i++)
    {
        for (int w = 0; w < n; w++)
            newAdjacDistancia[i][w] = adjDistancia[i][w];
    }
    for (int i = 0; i < n + 1; i++)
    {
        newAdjacDistancia[i][n] = std::numeric_limits<int>::infinity();
        newAdjacDistancia[n][i] = std::numeric_limits<int>::infinity();
    }
    adjDistancia = newAdjacDistancia;

    // Adequa a matriz de Tempo
    int **newAdjacTempo = new int *[n + 1];
    for (int i = 0; i < n + 1; i++)
        newAdjacTempo[i] = new int[n + 1];
    for (int i = 0; i < n; i++)
    {
        for (int w = 0; w < n; w++)
            newAdjacTempo[i][w] = adjTempo[i][w];
    }
    for (int i = 0; i < n + 1; i++)
    {
        newAdjacTempo[i][n] = std::numeric_limits<int>::infinity();
        newAdjacTempo[n][i] = std::numeric_limits<int>::infinity();
    }
    adjTempo = newAdjacTempo;

    n++;
}

// Insere uma aresta no Grafo tal que
// v é adjacente a w
void TGrafo::insereA(std::string aeroporto1, std::string aeroporto2, int distancia, int tempo)
{
    int v, w;
    for (int i = 0; i < n; ++i)
    {
        if (rotulo[i] == aeroporto1) // Obtem a posição do aeroporto1 no vetor de rótulos
            v = i;
    }

    for (int i = 0; i < n; ++i)
    {
        if (rotulo[i] == aeroporto2) // Obtem a posição do aeroporto2 no vetor de rótulos
            w = i;
    }

    // testa se não temos a aresta
    if (adjDistancia[v][w] == std::numeric_limits<int>::infinity())
    {
        adjDistancia[v][w] = distancia;
        adjTempo[v][w] = tempo;
        m++; // atualiza qtd arestas
        std::cout << "\nNova aresta inserida.\n";
    }
    else
        std::cout << "\nAresta já existente. Nada foi alterado.\n";
}

void TGrafo::removeV(std::string aeroporto)
{
    int v;
    for (int i = 0; i < n; ++i)
    {
        if (rotulo[i] == aeroporto) // Obtem a posição do aeroporto no vetor de rótulos
            v = i;
    }
    // Verificar se o vértice está no grafo.
    if (v > n)
    {
        std::cout << "\nNão existe o vértice.";
        return;
    }
    else
    {
        int i;

        // recalculando o número de arestas
        for (i = 0; i < n; ++i)
        {
            if (adjDistancia[i][v] != std::numeric_limits<int>::infinity())
                m--;
            if (adjDistancia[v][i] != std::numeric_limits<int>::infinity())
                m--;
        }
        if (adjDistancia[v][v] != std::numeric_limits<int>::infinity())
            m++;

        // remover o vértice
        while (v < n - 1)
        {
            // movendo a coluna para a esquerda
            for (i = 0; i < n; ++i)
            {
                adjDistancia[i][v] = adjDistancia[i][v + 1];
                adjTempo[i][v] = adjTempo[i][v + 1];
            }

            // movendo a linha para cima
            for (i = 0; i < n; ++i)
            {
                adjDistancia[v][i] = adjDistancia[v + 1][i];
                adjTempo[v][i] = adjTempo[v + 1][i];
                rotulo[v] = rotulo[v + 1];
            }
            v++;
        }

        // diminuir número de vértices
        n--;
        std::cout << "\nVértice removido.\n";
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(std::string aeroporto1, std::string aeroporto2)
{
    int v, w;
    for (int i = 0; i < n; ++i)
    {
        if (rotulo[i] == aeroporto1) // Obtem a posição do aeroporto1 no vetor de rótulos
            v = i;
    }
    for (int i = 0; i < n; ++i)
    {
        if (rotulo[i] == aeroporto2) // Obtem a posição do aeroporto2 no vetor de rótulos
            w = i;
    }

    // testa se temos a aresta
    if (adjDistancia[v][w] != std::numeric_limits<int>::infinity())
    {
        adjDistancia[v][w] = std::numeric_limits<int>::infinity();
        adjTempo[v][w] = std::numeric_limits<int>::infinity();
        m--; // atualiza qtd arestas
        std::cout << "\nAresta removida.\n";
        return;
    }
    std::cout << "\nAresta não existente.\n";
}

void TGrafo::mostrarConteudo(std::string fileName)
{
    int delimiterPosition;
    char buffer[MAX];
    std::ifstream fin(fileName);

    // Mostrar o tipo de grafo
    fin.getline(buffer, MAX); // Primeira linha do arquivo refere-se ao tipo de grafo.
    int tipoGrafo = std::stoi(buffer);
    switch (tipoGrafo)
    {
    case 0:
        std::cout << "\nGrafo não orientado, sem peso.\n\n";
        break;
    case 1:
        std::cout << "\nGrafo não orientado, com peso no vértice.\n\n";
        break;
    case 2:
        std::cout << "\nGrafo não orientado, com peso na aresta.\n\n";
        break;
    case 3:
        std::cout << "\nGrafo não orientado, com peso no vértice e na aresta.\n\n";
        break;
    case 4:
        std::cout << "\nGrafo orientado, sem peso.\n\n";
        break;
    case 5:
        std::cout << "\nGrafo orientado, com peso no vértice.\n\n";
        break;
    case 6:
        std::cout << "\nGrafo orientado, com peso na aresta.\n\n";
        break;
    case 7:
        std::cout << "\nGrafo orientado, com peso no vértice e na aresta.\n\n";
        break;
    default:
        std::cout << "\nTipo de grafo inválido.\n\n";
        break;
    }

    // Mostrar o número de vértices
    fin.getline(buffer, MAX); // Segunda linha do arquivo corresponde ao número de vértices
    int numeroVertices = std::stoi(buffer);
    std::cout << "Número de vértices do grafo: " << numeroVertices << std::endl;

    // Mostrar todos os vértices
    for (int i = 0; i < n; i++)
    {
        fin.getline(buffer, MAX);
        std::cout << "Vértice " << i << ": " << buffer << std::endl;
    }

    // Mostrar o número de arestas
    fin.getline(buffer, MAX); // Esta linha do arquivo corresponde ao número de arestas
    int numeroArestas = std::stoi(buffer);
    std::cout << "Número de arestas do grafo: " << numeroArestas << std::endl;

    // Mostra todas as arestas
    while (!fin.eof())
    {
        fin.getline(buffer, MAX);
        std::string line = buffer; // Lê a linha contendo aeroporto1, aeroporto2, distancia e tempo
        delimiterPosition = line.find(delimiter);
        std::string aeroporto1 = line.substr(0, delimiterPosition); // Obtem o aeroporto1
        std::cout << "Aeroporto 1: " << aeroporto1;
        for (int i = 0; i < 33 - aeroporto1.length(); i++) // coloca o espaçamento necessário para alinhar os valores
            std::cout << " ";
        line = line.substr(delimiterPosition + 1);
        delimiterPosition = line.find(delimiter);
        std::string aeroporto2 = line.substr(0, delimiterPosition); // Obtem o aeroporto2
        std::cout << "| Aeroporto 2: " << aeroporto2;
        for (int i = 0; i < 33 - aeroporto2.length(); i++) // coloca o espaçamento necessário para alinhar os valores
            std::cout << " ";
        line = line.substr(delimiterPosition + 1);
        delimiterPosition = line.find(delimiter);
        int distancia = std::stoi(line.substr(0, delimiterPosition)); // Obtem a distância
        std::cout << "| Distância entre aeroportos: " << distancia << " ";
        if (distancia < 100) // coloca o espaçamento necessário para alinhar os valores
            std::cout << "  ";
        else if (distancia < 1000)
            std::cout << " ";

        int tempo = std::stoi(line.substr(delimiterPosition + 1)); // Obtem o tempo
        std::cout << "| Tempo de viagem entre aeroportos: " << tempo << "\n";
    }
}

// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência obtida
void TGrafo::mostrarGrafo()
{
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    std::cout << "DISTÂNCIAS" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (adjDistancia[i][w] != std::numeric_limits<int>::infinity())
                std::cout << "Adj[" << i << "," << w << "]= " << adjDistancia[i][w] << " ";
            else
                std::cout << "Adj[" << i << "," << w << "]= i"
                          << " ";
    }
    std::cout << "\n\n";
    std::cout << "TEMPO DECORRIDO" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (adjTempo[i][w] != std::numeric_limits<int>::infinity())
                std::cout << "Adj[" << i << "," << w << "]= " << adjTempo[i][w] << " ";
            else
                std::cout << "Adj[" << i << "," << w << "]= i"
                          << " ";
    }
    std::cout << "\nfim da impressao do grafo." << std::endl;
}

// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência obtida
void TGrafo::mostrarGrafoArestas()
{
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    std::cout << "DISTÂNCIAS" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (adjDistancia[i][w] != std::numeric_limits<int>::infinity())
                std::cout << "Adj[" << i << "," << w << "]= " << adjDistancia[i][w] << "\n";
    }
    std::cout << "\n\n";
    std::cout << "TEMPO DECORRIDO" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (adjTempo[i][w] != std::numeric_limits<int>::infinity())
                std::cout << "Adj[" << i << "," << w << "]= " << adjTempo[i][w] << "\n";
    }
    std::cout << "\nfim da impressao do grafo." << std::endl;
}

// Métodos desenvolvidos para a segunda etapa do projeto

void TGrafo::percursoLargura(int v, int nosVisitados[], int *adj[])
{
    int nroNosMarcados = 0, nroNosVisitados = 0, n_, m_, nosMarcados[n];
    FilaCircular f;
    // Preenche vetor com -1
    for (int i = 0; i < n; i++)
        nosVisitados[i] = -1;

    nosVisitados[nroNosVisitados] = v; // visita o nó
    nroNosVisitados++;
    nosMarcados[nroNosMarcados] = v; // marca o nó
    nroNosMarcados++;
    f.enqueue(v);
    while (!f.qIsEmpty())
    {
        n_ = f.dequeue();
        // Existe nó adjacente a n ainda não marcado

        while ((m_ = noAdjacente(n_, nosMarcados, n, adj, nroNosMarcados)) != -1)
        {
            nosVisitados[nroNosVisitados] = m_; // visita o nó
            nroNosVisitados++;
            f.enqueue(m_);
            nosMarcados[nroNosMarcados] = m_; // marca o nó
            nroNosMarcados++;
        }
    }
};

bool TGrafo::fconexo()
{
    int percurso[n];
    for (int i = 0; i < n; i++)
    {
        this->percursoLargura(i, percurso, adjDistancia);
        for (int j = 0; j < n; j++)
            if (percurso[j] == -1) //-1 significa que não houve percurso até o vértice
                return false;
    }

    return true;
};

bool TGrafo::sfconexo()
{
    int percurso1[n];
    int percurso2[n];
    for (int i = 0; i < n; i++)
    {
        this->percursoLargura(i, percurso1, adjDistancia);
        for (int j = 0; j < n; j++)
            if (!verticeNoPercurso(j, percurso1, n))
            {
                this->percursoLargura(j, percurso2, adjDistancia);
                if (!verticeNoPercurso(i, percurso2, n))
                    return false;
            }
    }

    return true;
};

bool TGrafo::desconexo()
{
    // aloca da matriz de Tempo do TGrafo
    int **matrizSimetrica = new int *[n];
    for (int i = 0; i < n; i++)
        matrizSimetrica[i] = new int[n];
    // Inicia a matriz com valores infinitos
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrizSimetrica[i][j] = 0;

    // Coloca valor 1 onde houver aresta (dois sentidos)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (adjDistancia[i][j] != std::numeric_limits<int>::infinity())
            {
                matrizSimetrica[i][j] = 1;
                matrizSimetrica[j][i] = 1;
            }
        }

    int percurso[n];
    for (int i = 0; i < n; i++)
    {
        this->percursoLargura(i, percurso, matrizSimetrica);
        for (int j = 0; j < n; j++)
            if (percurso[j] == -1) //-1 significa que não houve percurso até o vértice
                return true;
    }

    return false;
};

void TGrafo::determinarConexidade()
{
    std::string categoria;
    if (this->fconexo())
        categoria = "C3 - Fortemente conexo.";
    else if (this->sfconexo())
        categoria = "C2 - Semifortemente conexo e não Fortemente conexo.";
    else if (this->desconexo())
        categoria = "C0 - Desconexo.";
    else
        categoria = "C1 - Simplesmente conexo e não Semifortemente conexo.";
    std::cout << "\nCategoria de conexidade: " << categoria << std::endl;
};

void TGrafo::melhorRota(std::string aeroporto1, std::string aeroporto2)
{
    int v, w;
    for (int i = 0; i < n; ++i)
    {
        if (rotulo[i] == aeroporto1) // Obtem a posição do aeroporto1 no vetor de rótulos
            v = i;
    }
    for (int i = 0; i < n; ++i)
    {
        if (rotulo[i] == aeroporto2) // Obtem a posição do aeroporto2 no vetor de rótulos
            w = i;
    }
    // aloca da matriz de distancia do TGrafo
    int **distancia = new int *[n];
    for (int i = 0; i < n; i++)
        distancia[i] = new int[n];

    // aloca da matriz de rota de distancia do TGrafo
    int **rotaDistancia = new int *[n];
    for (int i = 0; i < n; i++)
        rotaDistancia[i] = new int[n];

    // aloca da matriz de tempo do TGrafo
    int **tempo = new int *[n];
    for (int i = 0; i < n; i++)
        tempo[i] = new int[n];

    // aloca da matriz de rota de tempo do TGrafo
    int **rotaTempo = new int *[n];
    for (int i = 0; i < n; i++)
        rotaTempo[i] = new int[n];

    // Executa o algorítimo de floyd para a matriz de distancias e para a matriz de tempo
    floyd(v, adjDistancia, distancia, rotaDistancia, n);
    floyd(v, adjTempo, tempo, rotaTempo, n);

    // Caminho mínimo considerando distancia
    std::cout << "\nMELHOR ROTA CONSIDERANDO DISTANCIA:" << std::endl;
    caminhoMinimo(v, w, distancia, rotaDistancia, rotulo, n);
    std::cout << " km\n";

    // Caminho mínimo considerando tempo
    std::cout << "\nMELHOR ROTA CONSIDERANDO TEMPO:" << std::endl;
    caminhoMinimo(v, w, tempo, rotaTempo, rotulo, n);
    std::cout << " minutos\n";
};
