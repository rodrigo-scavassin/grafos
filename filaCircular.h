/*
   Fila Circular
   Desenvolvimento com Classe
   criação: 24/08/2022.
   prof. Dr. Ivan Carlos Alcântara de Oliveira
   Arquivo: filaCircular.h
*/

#ifndef __FILA_CIRCULAR_H__
#define __FILA_CIRCULAR_H__

// definição de um novo tipo de dado
typedef int Elem;

// constante que indica o Tamanho alocado para a Fila
const int TAM_FILA = 200;

// Classe que representa a fila circular estática e sequencial
class FilaCircular
{
private:
	int inicio, fim, qtde;
	Elem e[TAM_FILA];

public:
	FilaCircular();
	~FilaCircular(){};
	bool qIsEmpty();
	bool qIsFull();
	void enqueue(Elem e);
	Elem dequeue();
	Elem front();
	Elem rear();
	int size();
};

#endif
