/*
   Fila Circular
   Desenvolvimento com Classe
   criação: 24/08/2022.
   prof. Dr. Ivan Carlos Alcântara de Oliveira
   Arquivo: filaCircular.cpp
*/

#include <iostream>
#include "filaCircular.h"
// Construtor que Inicia a fila vazia
FilaCircular::FilaCircular()
{
  inicio = fim = qtde = 0;
}

// verifica se a fila está vazia
bool FilaCircular::qIsEmpty()
{
  if (qtde == 0)
    return true;
  else
    return false;
}
// Verifica se a fila está cheia
bool FilaCircular::qIsFull()
{
  if (qtde == TAM_FILA)
    return true;
  else
    return false;
}
// insere um elemento no final da fila
void FilaCircular::enqueue(Elem e)
{
  if (!qIsFull())
  {
    this->e[this->fim++] = e;
    this->fim = this->fim % TAM_FILA;
    this->qtde++;
  }
  else
    std::cout << "oveflow - Estouro de Fila";
}
// remove um elemento do final da fila
Elem FilaCircular::dequeue()
{
  Elem aux;
  if (!qIsEmpty())
  {
    aux = this->e[this->inicio];
    this->inicio = ++this->inicio % TAM_FILA;
    this->qtde--;
    return aux;
  }
  else
  {
    std::cout << "underflow - Esvaziamento de Fila";
    return -1;
  }
}
// retorna quem está no início da fila
// caso a fila não esteja vazia
Elem FilaCircular::front()
{
  if (!qIsEmpty())
    return e[inicio];
  else
  {
    std::cout << "underflow - Esvaziamento de Fila";
    return -1;
  }
}
// retorna quem está no final da fila caso ela não esteja vazia
Elem FilaCircular::rear()
{
  if (!qIsEmpty())
  {
    int final;
    if (this->fim != 0)
      final = this->fim - 1;
    else
      final = TAM_FILA - 1;
    return this->e[final];
  }
  else
  {
    std::cout << "underflow - Esvaziamento de Fila";
    return -1;
  }
}

// Retorna o total de elementos da fila
int FilaCircular::size()
{
  return qtde;
}
