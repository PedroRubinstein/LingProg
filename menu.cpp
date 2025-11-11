#include <iostream>
#include <limits>
#include "menu.h"
#include "polygon.h"
#include "circumference.h"
#include <vector>

using std::cin;
using std::cout;
using std::endl;

void Menu::showMenu() {
    while (true) {
        cout << "\n===== Menu do usuário =====" << endl;
        cout << "1 - Gerenciamento de dados geométricos" << endl;
        cout << "   inserir, remover, salvar e carregar dados." << endl;
        cout << "2 - Calculadora geométrica" << endl;
        cout << "   Responsável por realizar operações aritméticas simples entre vetores, pontos, segmentos e polígonos." << endl;
        cout << "3 - Polígono convexo composto pelos pontos de um conjunto" << endl;
        cout << "   Encontra o subconjunto de pontos que forma o menor polígono convexo que envolve todos os pontos do conjunto." << endl;
        cout << "4 - Círculo mínimo que contém todos os pontos de um conjunto" << endl;
        cout << "   Obtem o círculo com o menor raio possível que contém todos os pontos." << endl;
        cout << "5 - Visualização" << endl;
        cout << "   Gera representações gráficas dos objetos geométricos armazenados ou criados durante a execução." << endl;
        cout << "0 - Sair" << endl;

        cout << "\nEscolha uma opção: ";
        int option;
        if (!(cin >> option)) {
            cout << "Entrada inválida. Digite um número entre 0 e 5." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // clear the rest of the line
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option == 0) {
            cout << "Saindo...\n";
            break;
        }

            processOption(option);
    }
}

void Menu::processOption(int option) {
    switch (option) {
        case 1: {
            cout << "\n[1] Gerenciamento de dados geométricos selecionado." << endl;
            cout << "Criando alguns objetos de teste..." << endl;

            // Ponto simples
            geometricObjects.push_back(new Point(0.0, 0.0));

            // Quadrado
            Polygon *square = new Polygon();
            square->addVertex(Point(0.0, 0.0));
            square->addVertex(Point(1.0, 0.0));
            square->addVertex(Point(1.0, 1.0));
            square->addVertex(Point(0.0, 1.0));
            geometricObjects.push_back(square);

            // Circunferência com centro no meio do quadrado
            geometricObjects.push_back(new Circumference(Point(0.5, 0.5), 0.5));

            cout << "\nObjetos criados:\n";
            for (const auto &o : geometricObjects) {
                cout << "- ";
                o->print();
                cout << endl;
                cout << "  Tipo: ";
                switch (o->type()) {
                    case geometricObject::Type::Point: cout << "Ponto" << endl; break;
                    case geometricObject::Type::Polygon: cout << "Polígono" << endl; break;
                    case geometricObject::Type::Circumference: cout << "Circunferência" << endl; break;
                    default: cout << "Desconhecido" << endl; break;
                }
            }

            break; }
        case 2:
            cout << "\n[2] Calculadora geométrica simples selecionada." << endl;
            break;
        case 3:
            cout << "\n[3] Cálculo do polígono convexo selecionado." << endl;
            break;
        case 4:
            cout << "\n[4] Cálculo do círculo mínimo selecionado." << endl;
            break;
        case 5:
            cout << "\n[5] Visualização selecionada." << endl;
            Plotter::plot(geometricObjects);
            break;
        default:
            cout << "\nOpção inválida. Escolha um número entre 0 e 5." << endl;
            break;
    }

    // Just a prompt to pause before returning to menu
    cout << endl;
    cout << "Pressione Enter para continuar...";
    // Wait for Enter: read a line
    std::string dummy;
    std::getline(cin, dummy);
}

