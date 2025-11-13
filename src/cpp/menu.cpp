#include <iostream>
#include <limits>
#include <vector>
#include <string>

#include "menu.h"
#include "geometricObjects/polygon.h"
#include "geometricObjects/line.h"
#include "geometricObjects/circumference.h"
#include "geometricObjects/vector2d.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

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
            manageCalculator();
            break;
        case 3:
            cout << "\n[3] Cálculo do polígono convexo selecionado." << endl;
            break;
        case 4:
            cout << "\n[4] Cálculo do círculo mínimo selecionado." << endl;
            break;
        case 5:
            cout << "\n[5] Visualização selecionada." << endl;
            managePlotter();
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

void Menu::addObject(geometricObject *obj) {

    static int objectCounter = 0 + getMaxId();

    if (obj) {
        geometricObjects.push_back(obj);
        obj->setId(objectCounter++);
        return;
    }

    cout << "Selecione o tipo de objeto a adicionar:" << endl;
    cout << "1 - Ponto" << endl;
    cout << "2 - Reta" << endl;
    cout << "3 - Vetor" << endl;
    cout << "4 - Polígono" << endl;
    cout << "5 - Circunferência" << endl;

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
            cout << "Adicionar Reta selecionado." << endl;
            double x1, y1, x2, y2;
            cout << "Digite a coordenada x do primeiro ponto: "; cin >> x1;
            cout << "Digite a coordenada y do primeiro ponto: "; cin >> y1;
            cout << "Digite a coordenada x do segundo ponto: "; cin >> x2;
            cout << "Digite a coordenada y do segundo ponto: "; cin >> y2;
            geometricObjects.push_back(new Line(Point(x1, y1), Point(x2, y2)));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Reta adicionada com sucesso." << endl;
            break;
        }
        case 3: {
            cout << "Adicionar Vetor selecionado." << endl;
            double x, y;
            cout << "Digite a coordenada x do vetor: ";
            cin >> x;
            cout << "Digite a coordenada y do vetor: ";
            cin >> y;
            geometricObjects.push_back(new Vector2D(x, y));
            geometricObjects.back()->setId(objectCounter++);
            cout << "Vetor adicionado com sucesso." << endl;
            break;
        }
        case 4: {
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
        case 5: {
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
	// Finish this switch case later
	switch (obj->type()) {
		case geometricObject::Type::Point:
			cout << (Point*)obj << endl;
			break;    
		case geometricObject::Type::Line:
			cout << (Line*)obj << endl;
			break;
		default:
			cout << "Unknown object type" << endl;
			break;
	}
	cout << endl;
    }
}

void Menu::manageCalculator() {

    cout << endl << "Selecione o tipo de operação:" << endl;
    cout << "1 - Operações com pontos" << endl;
    cout << "2 - Operações com vetores" << endl;
    cout << "3 - Operações com segmentos (retas)" << endl;
    cout << "4 - Operações com polígonos" << endl;

    int option = getNumericInput();
    switch (option) {
        case 1: {
            // Point operations
            cout << endl << "Operações com pontos:" << endl;
            cout << "1 - Distância entre dois pontos" << endl;
            cout << "2 - Ponto médio entre dois pontos" << endl;
            cout << "3 - Translação de ponto por vetor" << endl;
            cout << "4 - Vetor entre dois pontos" << endl;
            
            int subopt = getNumericInput();
            if (subopt == 1) {
                cout << "Digite o ID do primeiro ponto: ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo ponto: ";
                int id2 = getNumericInput();
                
                Point* p1 = nullptr;
                Point* p2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Point) {
                        p1 = dynamic_cast<Point*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Point) {
                        p2 = dynamic_cast<Point*>(obj);
                    }
                }
                
                if (p1 && p2) {
                    double dist = Calculator::distance(*p1, *p2);
                    cout << "Distância: " << dist << endl;
                } else {
                    cout << "Um ou ambos os pontos não encontrados." << endl;
                }
            } else if (subopt == 2) {
                cout << "Digite o ID do primeiro ponto: ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo ponto: ";
                int id2 = getNumericInput();
                
                Point* p1 = nullptr;
                Point* p2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Point) {
                        p1 = dynamic_cast<Point*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Point) {
                        p2 = dynamic_cast<Point*>(obj);
                    }
                }
                
                if (p1 && p2) {
                    Point mid = Calculator::midpoint(*p1, *p2);
                    cout << "Ponto médio: (";
                    mid.print();
                    cout << ")" << endl;
                    Point* newPoint = new Point(mid);
                    askAddResult(newPoint);
                } else {
                    cout << "Um ou ambos os pontos não encontrados." << endl;
                }
            } else if (subopt == 3) {
                cout << "Digite o ID do ponto: ";
                int pid = getNumericInput();
                cout << "Digite o ID do vetor: ";
                int vid = getNumericInput();
                
                Point* p = nullptr;
                Vector2D* v = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == pid && obj->type() == geometricObject::Type::Point) {
                        p = dynamic_cast<Point*>(obj);
                    }
                    if (obj->getId() == vid && obj->type() == geometricObject::Type::Vector2D) {
                        v = dynamic_cast<Vector2D*>(obj);
                    }
                }
                
                if (p && v) {
                    Point result = Calculator::addPointVector(*p, *v);
                    cout << "Resultado da translação: (";
                    result.print();
                    cout << ")" << endl;
                    Point* newPoint = new Point(result);
                    askAddResult(newPoint);
                } else {
                    cout << "Ponto ou vetor não encontrado." << endl;
                }
            } else if (subopt == 4) {
                cout << "Digite o ID do primeiro ponto: ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo ponto: ";
                int id2 = getNumericInput();
                
                Point* p1 = nullptr;
                Point* p2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Point) {
                        p1 = dynamic_cast<Point*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Point) {
                        p2 = dynamic_cast<Point*>(obj);
                    }
                }
                
                if (p1 && p2) {
                    Vector2D vec = Calculator::subtractPoints(*p1, *p2);
                    cout << "Vetor P1-P2: (";
                    cout << vec.getX() << ", " << vec.getY();
                    cout << ")" << endl;
                    Vector2D* newVec = new Vector2D(vec);
                    askAddResult(newVec);
                } else {
                    cout << "Um ou ambos os pontos não encontrados." << endl;
                }
            } else {
                cout << "Opção inválida." << endl;
            }
            break;
        }
        case 2: {
            // Vector operations
            cout << endl << "Operações com vetores:" << endl;
            cout << "1 - Adição de vetores" << endl;
            cout << "2 - Subtração de vetores" << endl;
            cout << "3 - Multiplicação por escalar" << endl;
            cout << "4 - Divisão por escalar" << endl;
            cout << "5 - Produto escalar" << endl;
            cout << "6 - Produto vetorial" << endl;
            cout << "7 - Magnitude (norma)" << endl;
            cout << "8 - Normalizar vetor" << endl;
            
            int subopt = getNumericInput();
            if (subopt == 1) {
                cout << "Digite o ID do primeiro vetor: ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo vetor: ";
                int id2 = getNumericInput();
                
                Vector2D* v1 = nullptr;
                Vector2D* v2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Vector2D) {
                        v1 = dynamic_cast<Vector2D*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Vector2D) {
                        v2 = dynamic_cast<Vector2D*>(obj);
                    }
                }
                
                if (v1 && v2) {
                    Vector2D result = Calculator::addVectors(*v1, *v2);
                    cout << "Resultado V1 + V2: (" << result.getX() << ", " << result.getY() << ")" << endl;
                    Vector2D* newVec = new Vector2D(result);
                    askAddResult(newVec);
                } else {
                    cout << "Um ou ambos os vetores não encontrados." << endl;
                }
            } else if (subopt == 2) {
                cout << "Digite o ID do primeiro vetor: ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo vetor: ";
                int id2 = getNumericInput();
                
                Vector2D* v1 = nullptr;
                Vector2D* v2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Vector2D) {
                        v1 = dynamic_cast<Vector2D*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Vector2D) {
                        v2 = dynamic_cast<Vector2D*>(obj);
                    }
                }
                
                if (v1 && v2) {
                    Vector2D result = Calculator::subtractVectors(*v1, *v2);
                    cout << "Resultado V1 - V2: (" << result.getX() << ", " << result.getY() << ")" << endl;
                    Vector2D* newVec = new Vector2D(result);
                    askAddResult(newVec);
                } else {
                    cout << "Um ou ambos os vetores não encontrados." << endl;
                }
            } else if (subopt == 3) {
                cout << "Digite o ID do vetor: ";
                int vid = getNumericInput();
                cout << "Digite o escalar: ";
                double scalar = 0;
                cin >> scalar;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                Vector2D* v = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == vid && obj->type() == geometricObject::Type::Vector2D) {
                        v = dynamic_cast<Vector2D*>(obj);
                    }
                }
                
                if (v) {
                    Vector2D result = Calculator::scalarMultiply(*v, scalar);
                    cout << "Resultado " << scalar << " * V: (" << result.getX() << ", " << result.getY() << ")" << endl;
                    Vector2D* newVec = new Vector2D(result);
                    askAddResult(newVec);
                } else {
                    cout << "Vetor não encontrado." << endl;
                }
            } else if (subopt == 4) {
                cout << "Digite o ID do vetor: ";
                int vid = getNumericInput();
                cout << "Digite o escalar (não zero): ";
                double scalar = 0;
                cin >> scalar;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if (scalar == 0) {
                    cout << "Escalar não pode ser zero." << endl;
                } else {
                    Vector2D* v = nullptr;
                    for (auto obj : geometricObjects) {
                        if (obj->getId() == vid && obj->type() == geometricObject::Type::Vector2D) {
                            v = dynamic_cast<Vector2D*>(obj);
                        }
                    }
                    
                    if (v) {
                        Vector2D result = Calculator::scalarDivide(*v, scalar);
                        cout << "Resultado V / " << scalar << ": (" << result.getX() << ", " << result.getY() << ")" << endl;
                        Vector2D* newVec = new Vector2D(result);
                        askAddResult(newVec);
                    } else {
                        cout << "Vetor não encontrado." << endl;
                    }
                }
            } else if (subopt == 5) {
                cout << "Digite o ID do primeiro vetor: ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo vetor: ";
                int id2 = getNumericInput();
                
                Vector2D* v1 = nullptr;
                Vector2D* v2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Vector2D) {
                        v1 = dynamic_cast<Vector2D*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Vector2D) {
                        v2 = dynamic_cast<Vector2D*>(obj);
                    }
                }
                
                if (v1 && v2) {
                    double dot = Calculator::dotProduct(*v1, *v2);
                    cout << "V1 · V2 = " << dot << endl;
                } else {
                    cout << "Um ou ambos os vetores não encontrados." << endl;
                }
            } else if (subopt == 6) {
                cout << "Digite o ID do primeiro vetor: ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo vetor: ";
                int id2 = getNumericInput();
                
                Vector2D* v1 = nullptr;
                Vector2D* v2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Vector2D) {
                        v1 = dynamic_cast<Vector2D*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Vector2D) {
                        v2 = dynamic_cast<Vector2D*>(obj);
                    }
                }
                
                if (v1 && v2) {
                    double cross = Calculator::crossProduct(*v1, *v2);
                    cout << "V1 × V2 = " << cross << " (signed area)" << endl;
                } else {
                    cout << "Um ou ambos os vetores não encontrados." << endl;
                }
            } else if (subopt == 7) {
                cout << "Digite o ID do vetor: ";
                int vid = getNumericInput();
                
                Vector2D* v = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == vid && obj->type() == geometricObject::Type::Vector2D) {
                        v = dynamic_cast<Vector2D*>(obj);
                    }
                }
                
                if (v) {
                    double mag = Calculator::magnitude(*v);
                    cout << "|V| = " << mag << endl;
                } else {
                    cout << "Vetor não encontrado." << endl;
                }
            } else if (subopt == 8) {
                cout << "Digite o ID do vetor: ";
                int vid = getNumericInput();
                
                Vector2D* v = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == vid && obj->type() == geometricObject::Type::Vector2D) {
                        v = dynamic_cast<Vector2D*>(obj);
                    }
                }
                
                if (v) {
                    try {
                        Vector2D normalized = Calculator::normalize(*v);
                        cout << "Vetor normalizado: (" << normalized.getX() << ", " << normalized.getY() << ")" << endl;
                        Vector2D* newVec = new Vector2D(normalized);
                        askAddResult(newVec);
                    } catch (const std::exception& e) {
                        cout << "Erro: " << e.what() << endl;
                    }
                } else {
                    cout << "Vetor não encontrado." << endl;
                }
            } else {
                cout << "Opção inválida." << endl;
            }
            break;
        }
        case 3: {
            // Segment operations
            cout << endl << "Operações com segmentos (retas):" << endl;
            cout << "1 - Comprimento do segmento" << endl;
            cout << "2 - Ponto médio do segmento" << endl;
            cout << "3 - Verificar se dois segmentos são paralelos" << endl;
            cout << "4 - Verificar se dois segmentos são perpendiculares" << endl;
            
            int subopt = getNumericInput();
            if (subopt == 1) {
                cout << "Digite o ID do segmento (reta): ";
                int id = getNumericInput();
                
                Line* seg = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id && obj->type() == geometricObject::Type::Line) {
                        seg = dynamic_cast<Line*>(obj);
                    }
                }
                
                if (seg) {
                    double length = Calculator::segmentLength(*seg);
                    cout << "Comprimento do segmento: " << length << endl;
                } else {
                    cout << "Segmento não encontrado." << endl;
                }
            } else if (subopt == 2) {
                cout << "Digite o ID do segmento (reta): ";
                int id = getNumericInput();
                
                Line* seg = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id && obj->type() == geometricObject::Type::Line) {
                        seg = dynamic_cast<Line*>(obj);
                    }
                }
                
                if (seg) {
                    Point mid = Calculator::segmentMidpoint(*seg);
                    cout << "Ponto médio do segmento: (";
                    mid.print();
                    cout << ")" << endl;
                    Point* newPoint = new Point(mid);
                    askAddResult(newPoint);
                } else {
                    cout << "Segmento não encontrado." << endl;
                }
            } else if (subopt == 3) {
                cout << "Digite o ID do primeiro segmento (reta): ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo segmento (reta): ";
                int id2 = getNumericInput();
                
                Line* seg1 = nullptr;
                Line* seg2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Line) {
                        seg1 = dynamic_cast<Line*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Line) {
                        seg2 = dynamic_cast<Line*>(obj);
                    }
                }
                
                if (seg1 && seg2) {
                    bool parallel = Calculator::areParallel(*seg1, *seg2);
                    cout << "São paralelos? " << (parallel ? "SIM" : "NÃO") << endl;
                } else {
                    cout << "Um ou ambos os segmentos não encontrados." << endl;
                }
            } else if (subopt == 4) {
                cout << "Digite o ID do primeiro segmento (reta): ";
                int id1 = getNumericInput();
                cout << "Digite o ID do segundo segmento (reta): ";
                int id2 = getNumericInput();
                
                Line* seg1 = nullptr;
                Line* seg2 = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id1 && obj->type() == geometricObject::Type::Line) {
                        seg1 = dynamic_cast<Line*>(obj);
                    }
                    if (obj->getId() == id2 && obj->type() == geometricObject::Type::Line) {
                        seg2 = dynamic_cast<Line*>(obj);
                    }
                }
                
                if (seg1 && seg2) {
                    bool perpendicular = Calculator::arePerpendicular(*seg1, *seg2);
                    cout << "São perpendiculares? " << (perpendicular ? "SIM" : "NÃO") << endl;
                } else {
                    cout << "Um ou ambos os segmentos não encontrados." << endl;
                }
            } else {
                cout << "Opção inválida." << endl;
            }
            break;
        }
        case 4: {
            // Polygon operations
            cout << endl << "Operações com polígonos:" << endl;
            cout << "1 - Perímetro do polígono" << endl;
            cout << "2 - Área do polígono" << endl;
            cout << "3 - Centróide do polígono" << endl;
            cout << "4 - Verificar se ponto está dentro do polígono" << endl;
            
            int subopt = getNumericInput();
            if (subopt == 1) {
                cout << "Digite o ID do polígono: ";
                int id = getNumericInput();
                
                Polygon* poly = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id && obj->type() == geometricObject::Type::Polygon) {
                        poly = dynamic_cast<Polygon*>(obj);
                    }
                }
                
                if (poly) {
                    double perimeter = Calculator::polygonPerimeter(*poly);
                    cout << "Perímetro do polígono: " << perimeter << endl;
                } else {
                    cout << "Polígono não encontrado." << endl;
                }
            } else if (subopt == 2) {
                cout << "Digite o ID do polígono: ";
                int id = getNumericInput();
                
                Polygon* poly = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id && obj->type() == geometricObject::Type::Polygon) {
                        poly = dynamic_cast<Polygon*>(obj);
                    }
                }
                
                if (poly) {
                    double area = Calculator::polygonArea(*poly);
                    cout << "Área do polígono: " << area << endl;
                } else {
                    cout << "Polígono não encontrado." << endl;
                }
            } else if (subopt == 3) {
                cout << "Digite o ID do polígono: ";
                int id = getNumericInput();
                
                Polygon* poly = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == id && obj->type() == geometricObject::Type::Polygon) {
                        poly = dynamic_cast<Polygon*>(obj);
                    }
                }
                
                if (poly) {
                    Point centroid = Calculator::polygonCentroid(*poly);
                    cout << "Centróide do polígono: (";
                    centroid.print();
                    cout << ")" << endl;
                    Point* newPoint = new Point(centroid);
                    askAddResult(newPoint);
                } else {
                    cout << "Polígono não encontrado." << endl;
                }
            } else if (subopt == 4) {
                cout << "Digite o ID do ponto: ";
                int pid = getNumericInput();
                cout << "Digite o ID do polígono: ";
                int polyid = getNumericInput();
                
                Point* p = nullptr;
                Polygon* poly = nullptr;
                for (auto obj : geometricObjects) {
                    if (obj->getId() == pid && obj->type() == geometricObject::Type::Point) {
                        p = dynamic_cast<Point*>(obj);
                    }
                    if (obj->getId() == polyid && obj->type() == geometricObject::Type::Polygon) {
                        poly = dynamic_cast<Polygon*>(obj);
                    }
                }
                
                if (p && poly) {
                    bool inside = Calculator::isPointInPolygon(*p, *poly);
                    cout << "O ponto está dentro do polígono? " << (inside ? "SIM" : "NÃO") << endl;
                } else {
                    cout << "Ponto ou polígono não encontrado." << endl;
                }
            } else {
                cout << "Opção inválida." << endl;
            }
            break;
        }
        default:
            cout << "Opção inválida." << endl;
            break;
    }
}

void Menu::askAddResult(geometricObject* result) {
    cout << "Deseja adicionar o resultado como um novo objeto? (1 - Sim, 0 - Não): ";
    int choice = getNumericInput();
    if (choice == 1) {
        addObject(result);
        cout << "Resultado adicionado com sucesso." << endl;
    } else {
        cout << "Resultado não adicionado." << endl;
    }
}

void Menu::managePlotter() {
    cout << "1 - Gerar visualização dos objetos geométricos armazenados" << endl;
    cout << "2 - Salvar último plot gerado em arquivo desejado" << endl;

    int option = getNumericInput();
    switch (option) {
        case 1:
            plotter.plot(geometricObjects);
            break;
        case 2: {
            cout << "Digite o nome do arquivo para salvar o plot: ";
            string filename;
            cin >> filename;
            plotter.saveFigure(filename);
            break;
        }
        default:
            cout << "Opção inválida." << endl;
            break;
    }
}
