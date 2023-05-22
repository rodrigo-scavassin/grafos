// Aluno: Rodrigo Mattos Scavassin		TIA: 32055374
#include "TGrafo.h"
#include "TGrafo.cpp"
#include "filaCircular.h"
#include "filaCircular.cpp"

void showMenu()
{
    std::cout << "Selecione uma das opções do menu abaixo:\n";
    std::cout << "\nETAPA 1 DO PROJETO\n";
    std::cout << "(1) - Ler dados do arquivo\n";
    std::cout << "(2) - Gravar dados no arquivo\n";
    std::cout << "(3) - Inserir vértice\n";
    std::cout << "(4) - Inserir aresta\n";
    std::cout << "(5) - Remover vértice\n";
    std::cout << "(6) - Remover aresta\n";
    std::cout << "(7) - Mostrar o conteúdo do arquivo\n";
    std::cout << "(8) - Mostrar Grafo\n";
    std::cout << "(9) - Mostrar apenas arestas\n";
    std::cout << "\nETAPA 2 DO PROJETO\n";
    std::cout << "(10) - Mostrar a conexidade do grafo\n";
    std::cout << "(11) - Determinar a melhor rota\n";
    std::cout << "(12) Diretirzes da ODS\n";
    std::cout << "(0) - Encerrar a aplicação\n";
}

int main()
{
    //  Cria o grafo g com base no arquivo de texto
    TGrafo g("grafo.txt");
    int option = 1;
    std::string aeroporto1;
    std::string aeroporto2;
    int distancia;
    int tempo;
    std::cout << "\nTRÁFEGO DE ROTAS AÉREAS NACIONAIS\n";
    while (option > 0)
    {
        showMenu();
        std::cin >> option;

        switch (option)
        {
        case 1:
            g = TGrafo("grafo.txt");
            std::cout << "\nGrafo Carregado.\n";
            break;

        case 2:
            g.save();
            std::cout << "\nGrafo Salvo em arquivo.\n";
            break;

        case 3:
            std::cout << "Insira o nome do aeroporto: ";
            std::cin >> aeroporto1;
            g.insereV(aeroporto1);
            std::cout << "\nNovo vértice inserido.\n";
            break;

        case 4:
            std::cout << "Insira o nome do 1º aeroporto: ";
            std::cin >> aeroporto1;
            std::cout << "Insira o nome do 2º aeroporto: ";
            std::cin >> aeroporto2;
            std::cout << "Insira a distância entre os aeroportos: ";
            std::cin >> distancia;
            std::cout << "Insira o tempo de viagem em minutos entre os aeroportos: ";
            std::cin >> tempo;
            g.insereA(aeroporto1, aeroporto2, distancia, tempo);
            break;

        case 5:
            std::cout << "Insira o nome do aeroporto: ";
            std::cin >> aeroporto1;
            g.removeV(aeroporto1);
            break;

        case 6:
            std::cout << "Insira o nome do 1º aeroporto: ";
            std::cin >> aeroporto1;
            std::cout << "Insira o nome do 2º aeroporto: ";
            std::cin >> aeroporto2;
            g.removeA(aeroporto1, aeroporto2);

            break;

        case 7:
            g.mostrarConteudo("grafo.txt");
            break;

        case 8:
            g.mostrarGrafo();
            break;

        case 9:
            g.mostrarGrafoArestas();
            break;

        case 10:
            g.determinarConexidade();
            break;

        case 11:
            std::cout << "Insira o nome do aeroporto de origem: ";
            std::cin >> aeroporto1;
            std::cout << "Insira o nome do aeroporto de destino: ";
            std::cin >> aeroporto2;
            g.melhorRota(aeroporto1, aeroporto2);
            break;

        case 12:
            std::cout << "\nEste programa apoia os objetivos 8 e 9 da ODS.\n";
            std::cout << "8. Trabalho Descente e Crescimento Econômico.\n";
            std::cout << "9. Indústria, Inovação e Infraestrutura.\n";

            break;

        case 0:
            break;

        default:
            std::cout << "\nOpção inválida!\n";
            break;
        }

        std::cout << "\n";
    }
    std::cout << "Fim do programa.\n\n";
    return 0;
}
