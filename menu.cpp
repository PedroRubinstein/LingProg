#include <iostream>
#include <limits>
#include "menu.h"
#include "polygon.h"
#include "circumference.h"
#include <vector>

using std::cin;
using std::cout;
using std::endl;

Menu::~Menu() {
    for (auto obj : geometricObjects) {
        delete obj;
    }
}

int Menu::getNumericInput() {
    int input;
    while (true) {
        if (!(cin >> input)) {
            cout << "Entrada inválida. Digite um número entre 0 e 5." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // clear the rest of the line
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
}

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
        int option = getNumericInput();

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
            manageObjects();
            break;
        }
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

void Menu::manageObjects() {
    cout << endl << "Selecione uma subopção:" << endl;
    cout << "1 - Adicionar objeto" << endl;
    cout << "2 - Remover objeto" << endl;
    cout << "3 - Listar objetos" << endl;
    cout << "4 - Salvar objetos em base de dados" << endl;
    cout << "5 - Carregar objetos de base de dados" << endl;

    int option = getNumericInput();
    switch (option) {
        case 1:
            cout << endl << "Adicionar objeto selecionado." << endl;
            addObject();
            break;
        case 2:
            cout << endl <<"Remover objeto selecionado." << endl;
            removeObject();
            break;
        case 3:
            cout << endl << "Listar objetos selecionado." << endl;
            listObjects();
            break;
        case 4:
            cout << endl << "Salvar objetos selecionado." << endl;
            //saveObjects();
            break;
        case 5:
            cout << endl << "Carregar objetos selecionado." << endl;
            //loadObjects();
            break;
        default:
            cout << endl << "Opção inválida." << endl;
            break;
    }
}

void Menu::addObject() {

    static int objectCounter = 0 + getMaxId();

    cout << "Selecione o tipo de objeto a adicionar:" << endl;
    cout << "1 - Ponto" << endl;
    cout << "2 - Polígono" << endl;
    cout << "3 - Circunferência" << endl;

    int objectType = getNumericInput();
    switch (objectType) {
        case 1: {
            cout << "Adicionar Ponto selecionado." << endl;
            double x, y;
            cout << "Digite a coordenada x: ";
            cin >> x;
            cout << "Digite a coordenada y: ";
            cin >> y;
            geometricObjects.push_back(new Point(x, y));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Ponto adicionado com sucesso." << endl;
            break;
        }
        case 2: {
            cout << "Adicionar Polígono selecionado." << endl;
            int numVertices;
            cout << "Digite o número de vértices: ";
            cin >> numVertices;
            std::vector<Point> vertices;
            for (int i = 0; i < numVertices; ++i) {
                double x, y;
                cout << "Vértice " << (i + 1) << " - Digite a coordenada x: ";
                cin >> x;
                cout << "Vértice " << (i + 1) << " - Digite a coordenada y: ";
                cin >> y;
                vertices.emplace_back(x, y);
            }
            geometricObjects.push_back(new Polygon(vertices));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Polígono adicionado com sucesso." << endl;
            break;
        }
        case 3: {
            cout << "Adicionar Circunferência selecionado." << endl;
            double centerX, centerY, radius;
            cout << "Digite a coordenada x do centro: ";
            cin >> centerX;
            cout << "Digite a coordenada y do centro: ";
            cin >> centerY;
            cout << "Digite o raio: ";
            cin >> radius;
            geometricObjects.push_back(new Circumference(Point(centerX, centerY), radius));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Circunferência adicionada com sucesso." << endl;
            break;
        }
        default:
            cout << "Tipo de objeto inválido." << endl;
            break;
    }
}

void Menu::removeObject() {
    cout << "Digite o ID do objeto a ser removido: ";
    int idToRemove = getNumericInput();
    for (auto it = geometricObjects.begin(); it != geometricObjects.end(); ++it)
    {
        if ((*it)->getId() == idToRemove) {
            delete *it; // Free memory
            geometricObjects.erase(it);
            cout << "Objeto com ID " << idToRemove << " removido com sucesso." << endl;
            return;
        }
    }
    cout << "Objeto com ID " << idToRemove << " não encontrado." << endl;
}

void Menu::listObjects() {
    if (geometricObjects.empty()) {
        cout << "Nenhum objeto geométrico armazenado." << endl;
        return;
    }

    cout << "Objetos geométricos armazenados:" << endl;
    for (const auto& obj : geometricObjects) {
        cout << "ID: " << obj->getId() << " - ";
        obj->print();
        cout << endl;
    }
}