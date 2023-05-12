// Aluno: Rodrigo Mattos Scavassin		TIA: 32055374
#include <iostream>
/*
Implementação de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjacência
e métodos para utilização de um grafo dirigido.
*/
#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___

// definição de uma estrutura para armezanar um grafo
// Também seria possível criar um arquivo grafo.h
// e fazer a inclusão "#include <grafo.h>"
class TGrafo
{
private:
	int n;				 // quantidade de vértices
	int m;				 // quantidade de arestas
	int tipoGrafo;		 // tipo do grafo
	int **adjDistancia;	 // matriz de adjacência de distância
	int **adjTempo;		 // matriz de adjacência de tempo
	std::string *rotulo; // vetor de Rótulo dos vértices

public:
	TGrafo(int n);
	TGrafo(std::string fileName);
	~TGrafo();
	void save();
	void insereV(std::string aeroporto);
	void insereA(std::string aeroporto1, std::string aeroporto2, int distancia = 1, int tempo = 1);
	void removeV(std::string aeroporto);
	void removeA(std::string aeroporto1, std::string aeroporto2);
	void mostrarConteudo(std::string fileName);
	void mostrarGrafo();
	void mostrarGrafoArestas();
	// Métodos desenvolvidos para o projeto 02
	void percursoLargura(int vInicio, int nosVisitados[], int *adj[]);
	bool fconexo();
	bool sfconexo();
	bool desconexo();
	void determinarConexidade();
	void melhorRota(std::string aeroporto1, std::string aeroporto2);
};

#endif