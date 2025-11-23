#include "menu.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>

// Inclui os headers dos objetos geométricos
#include "vector2d.h"
#include "line.h"
#include "polygon.h"
#include "circumference.h"

// Usando declarações específicas para evitar poluir o namespace global
using std::cin;
using std::cout;
using std::endl;
using std::string;

Menu::~Menu() {
    // Liberta a memória de todos os objetos criados dinamicamente
    for (auto obj : geometricObjects) {
        delete obj;
    }
}

int Menu::getNumericInput() {
    int input;
    while (true) {
        if (!(cin >> input)) {
            cout << "Entrada inválida. Por favor, digite um número." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Limpa o resto da linha (caso o utilizador digite "5 abc")
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
}

void Menu::pauseForEnter() {
    cout << endl << "Pressione Enter para continuar...";
    string dummy;
    std::getline(cin, dummy);
}

void Menu::showMenu() {
    while (true) {
        cout << "\n===== Menu Principal =====" << endl;
        cout << "1 - Gerenciamento de Objetos Geométricos" << endl;
        cout << "2 - Calculadora Geométrica" << endl;
        cout << "3 - Polígono Convexo (Não implementado)" << endl;
        cout << "4 - Círculo Mínimo (Não implementado)" << endl;
        cout << "5 - Visualização (Plotter)" << endl;
        cout << "0 - Sair" << endl;

        cout << "\nEscolha uma opção: ";
        int option = getNumericInput();

        if (option == 0) {
            cout << "Saindo...\n";
            break;
        }

        processOption(option);
        pauseForEnter(); // Pausa após cada ação antes de mostrar o menu novamente
    }
}

void Menu::processOption(int option) {
    switch (option) {
        case 1:
            cout << "\n[1] Gerenciamento de Objetos" << endl;
            manageObjects();
            break;
        case 2:
            cout << "\n[2] Calculadora Geométrica" << endl;
            manageCalculator();
            break;
        case 3:
            cout << "\n[3] Cálculo do Polígono Convexo" << endl;
            manageConvexHull();
            break;
        case 4:
            cout << "\n[4] Cálculo do Círculo Mínimo" << endl;
            manageMinCircle();
            break;
        case 5:
            cout << "\n[5] Visualização" << endl;
            managePlotter();
            break;
        default:
            cout << "\nOpção inválida. Escolha um número entre 0 e 5." << endl;
            break;
    }
}

// --- Métodos de Gerenciamento (para Escalabilidade) ---

void Menu::manageObjects() {
    cout << endl << "Selecione uma subopção:" << endl;
    cout << "1 - Adicionar objeto" << endl;
    cout << "2 - Remover objeto" << endl;
    cout << "3 - Listar objetos" << endl;
    cout << "4 - Salvar objetos (Não implementado)" << endl;
    cout << "5 - Carregar objetos (Não implementado)" << endl;
    cout << "0 - Voltar ao menu principal" << endl;

    int option = getNumericInput();
    switch (option) {
        case 1:
            addObject();
            break;
        case 2:
            removeObject();
            break;
        case 3:
            listObjects();
            break;
        case 4:
            saveObjects();
            break;
        case 5:
            loadObjects();
            break;
        case 0:
            break;
        default:
            cout << endl << "Opção inválida." << endl;
            break;
    }
}

void Menu::manageCalculator() {
    cout << "A funcionalidade da Calculadora Geométrica está temporariamente desativada." << endl;
    //
    // A implementação anterior da calculadora (de menu.cpp original)
    // foi removida para refatoração.
    //
}

void Menu::manageConvexHull() {
    cout << "Funcionalidade de Polígono Convexo ainda não implementada." << endl;
}

void Menu::manageMinCircle() {
    cout << "Funcionalidade de Círculo Mínimo ainda não implementada." << endl;
}

void Menu::managePlotter() {
    cout << "1 - Gerar visualização dos objetos geométricos armazenados" << endl;
    cout << "2 - Salvar último plot gerado em arquivo" << endl;
    cout << "0 - Voltar" << endl;

    int option = getNumericInput();
    switch (option) {
        case 1:
            cout << "Gerando plot..." << endl;
            plotter.plot(geometricObjects);
            cout << "Plot gerado. (Pode ter aberto numa janela separada ou salvo em 'plot.png')." << endl;
            break;
        case 2: {
            cout << "Digite o nome do arquivo para salvar o plot (ex: 'figura.png'): ";
            string filename;
            std::getline(cin, filename); // Lê a linha inteira
            if (plotter.saveFigure(filename)) {
                cout << "Figura salva com sucesso em " << filename << endl;
            } else {
                cout << "Erro ao salvar figura. Talvez nenhum plot tenha sido gerado ainda." << endl;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Opção inválida." << endl;
            break;
    }
}

// --- Sub-métodos de 'manageObjects' ---

void Menu::addObject(geometricObject *obj) {
    // ID estático para auto-incremento
    static int objectCounter = 0 + getMaxId();

    // Se um objeto foi passado (ex: resultado de uma operação), adicione-o
    if (obj) {
        obj->setId(objectCounter++);
        geometricObjects.push_back(obj);
        return;
    }

    // Menu para adicionar novo objeto
    cout << "Selecione o tipo de objeto a adicionar:" << endl;
    cout << "1 - Vetor (ou Ponto/Vetor de Posição)" << endl;
    cout << "2 - Reta (Segmento)" << endl;
    cout << "3 - Polígono" << endl;
    cout << "4 - Circunferência" << endl;
    cout << "0 - Voltar" << endl;

    int objectType = getNumericInput();
    switch (objectType) {
        case 1: {
            cout << "Adicionar Vetor/Ponto." << endl;
            double x, y;
            cout << "Digite a coordenada x: "; cin >> x;
            cout << "Digite a coordenada y: "; cin >> y;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
            
            geometricObjects.push_back(new Vector2D(x, y));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Vetor/Ponto adicionado com sucesso." << endl;
            break;
        }
        case 2: {
            cout << "Adicionar Reta." << endl;
            double x1, y1, x2, y2;
            cout << "Ponto 1 (x y): "; cin >> x1 >> y1;
            cout << "Ponto 2 (x y): "; cin >> x2 >> y2;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
            
            // Usa Vector2D em vez de Point
            geometricObjects.push_back(new Line(Vector2D(x1, y1), Vector2D(x2, y2)));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Reta adicionada com sucesso." << endl;
            break;
        }
        case 3: {
            cout << "Adicionar Polígono." << endl;
            int numVertices;
            cout << "Digite o número de vértices: ";
            numVertices = getNumericInput();
            
            std::vector<Vector2D> vertices; // Usa Vector2D
            for (int i = 0; i < numVertices; ++i) {
                double x, y;
                cout << "Vértice " << (i + 1) << " (x y): ";
                cin >> x >> y;
                vertices.emplace_back(x, y); // Usa Vector2D
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer

            geometricObjects.push_back(new Polygon(vertices));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Polígono adicionado com sucesso." << endl;
            break;
        }
        case 4: {
            cout << "Adicionar Circunferência." << endl;
            double centerX, centerY, radius;
            cout << "Centro (x y): "; cin >> centerX >> centerY;
            cout << "Raio: "; cin >> radius;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
            
            // Usa Vector2D
            geometricObjects.push_back(new Circumference(Vector2D(centerX, centerY), radius));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Circunferência adicionada com sucesso." << endl;
            break;
        }
        case 0:
            break;
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
            delete *it; // Libertar memória
            geometricObjects.erase(it);
            cout << "Objeto com ID " << idToRemove << " removido com sucesso." << endl;
            return;
        }
    }
    cout << "Objeto com ID " << idToRemove << " não encontrado." << endl;
}

/**
 * @brief Lista objetos usando dynamic_cast e operator<<,
 * já que o método virtual print() foi removido.
 */
void Menu::listObjects() {
    if (geometricObjects.empty()) {
        cout << "Nenhum objeto geométrico armazenado." << endl;
        return;
    }

    cout << "Objetos geométricos armazenados:" << endl;
    for (const auto& obj : geometricObjects) {
        cout << "ID: " << obj->getId() << " - ";
        
        // Polimorfismo com operator<< requer RTTI (dynamic_cast)
        // Esta é a consequência de remover o virtual print()
        
        if (auto v = dynamic_cast<Vector2D*>(obj)) {
            cout << *v << endl;
        } else if (auto l = dynamic_cast<Line*>(obj)) {
            cout << *l << endl;
        } else if (auto p = dynamic_cast<Polygon*>(obj)) {
            cout << *p << endl;
        } else if (auto c = dynamic_cast<Circumference*>(obj)) {
            cout << *c << endl;
        } else {
            cout << "Objeto de tipo desconhecido." << endl;
        }
    }
}

void Menu::saveObjects() {
    cout << "Funcionalidade de Salvar Objetos ainda não implementada." << endl;
}

void Menu::loadObjects() {
    cout << "Funcionalidade de Carregar Objetos ainda não implementada." << endl;
}

// --- Métodos de Ajuda ---

void Menu::askAddResult(geometricObject* result) {
    if (!result) return;
    
    cout << "Deseja adicionar o resultado como um novo objeto? (1 - Sim, 0 - Não): ";
    int choice = getNumericInput();
    if (choice == 1) {
        addObject(result); // Adiciona o objeto pré-criado
        cout << "Resultado adicionado com sucesso." << endl;
    } else {
        delete result; // Se não for adicionado, liberta a memória
        cout << "Resultado não adicionado." << endl;
    }
}

int Menu::getMaxId() {
    // TO-DO: Implementar a lógica para carregar o ID máximo
    // da base de dados (quando 'saveObjects' for implementado)
    return 0; // Stub
}
