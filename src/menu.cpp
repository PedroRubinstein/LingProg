#include "algorithms/mincircle.h"
#include "menu.h"
#include "database.h"
#include "algorithms/convexhull.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <sstream>

#include "geometricObjects/vector2d.h"
#include "geometricObjects/line.h"
#include "geometricObjects/polygon.h"
#include "geometricObjects/circumference.h"

using namespace std;

Menu::Menu() {
    registerCalculatorOperations();
    loadObjects();
}

Menu::~Menu() {
    for (auto obj : geometricObjects) {
        delete obj;
    }
    geometricObjects.clear();
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
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
}

void Menu::registerCalculatorOperations() {
    calculatorOperations.push_back({
        "Localização de Ponto (Esq/Dir/Toque)",
        [this]() {
            cout << ">> Defina a Reta de referência:" << endl;
            geometricObject* l = getObjectFromUser(2);
            if (!l) return;

            cout << ">> Defina o Ponto de teste:" << endl;
            geometricObject* p = getObjectFromUser(1);
            if (!p) { if(l->getId()==-1) delete l; return; }

            string res = Calculator::pointLocationTest(*dynamic_cast<Line*>(l), *dynamic_cast<Vector2D*>(p));
            cout << "\n>> Resultado: " << res << endl;

            if(l->getId() == -1) delete l;
            if(p->getId() == -1) delete p;
        }
    });

    calculatorOperations.push_back({
        "Interseção de Segmentos",
        [this]() {
            cout << ">> Defina o Segmento 1:" << endl;
            geometricObject* s1 = getObjectFromUser(2);
            if(!s1) return;

            cout << ">> Defina o Segmento 2:" << endl;
            geometricObject* s2 = getObjectFromUser(2);
            if(!s2) { if(s1->getId()==-1) delete s1; return; }

            bool res = Calculator::checkIntersection(*dynamic_cast<Line*>(s1), *dynamic_cast<Line*>(s2));
            cout << "\n>> Resultado: " << (res ? "INTERCEPTAM" : "NÃO INTERCEPTAM") << endl;

            if(s1->getId() == -1) delete s1;
            if(s2->getId() == -1) delete s2;
        }
    });

    calculatorOperations.push_back({
        "Área de Polígono",
        [this]() {
            cout << "\n[!] Aviso: O polígono não deve se auto-intersectar para o cálculo correto." << endl;
            cout << ">> Defina o Polígono:" << endl;
            geometricObject* poly = getObjectFromUser(3);
            if(!poly) return;

            double area = Calculator::polygonArea(*dynamic_cast<Polygon*>(poly));
            cout << "\n>> Área: " << area << endl;

            if(poly->getId() == -1) delete poly;
        }
    });
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
        cout << "3 - Fecho Convexo" << endl;
        cout << "4 - Círculo Mínimo" << endl;
        cout << "5 - Visualização" << endl;
        cout << "0 - Sair" << endl;

        cout << "\nEscolha uma opção: ";
        int option = getNumericInput();

        if (option == 0) {
            cout << "Saindo...\n";
            break;
        }

        processOption(option);
        pauseForEnter();
    }
}

void Menu::processOption(int option) {
    switch (option) {
        case 1: manageObjects(); break;
        case 2: manageCalculator(); break;
        case 3: manageConvexHull(); break;
        case 4: manageMinCircle(); break;
        case 5: managePlotter(); break;
        default: cout << "\nOpção inválida." << endl; break;
    }
}

void Menu::manageObjects() {
    cout << "\n=== Gerenciamento de Objetos (SQL) ===" << endl;
    cout << "1 - Adicionar objeto" << endl;
    cout << "2 - Remover objeto" << endl;
    cout << "3 - Listar objetos (Memória)" << endl;
    cout << "4 - Recarregar do Banco de Dados (Revert Changes)" << endl;
    cout << "5 - Limpar Banco de Dados (RESET)" << endl;
    cout << "0 - Voltar ao menu principal" << endl;

    int option = getNumericInput();
    switch (option) {
        case 1: addObject(); break;
        case 2: removeObject(); break;
        case 3: listObjects(); break;
        case 4: loadObjects(); break;
        case 5: {
            cout << "Tem certeza que deseja apagar TUDO? (1-Sim / 0-Não): ";
            int confirm = getNumericInput();
            if (confirm == 1) {
                if (DatabaseManager::getInstance().clear_database()) {
                    for (auto obj : geometricObjects) delete obj;
                    geometricObjects.clear();
                    cout << ">> Banco de dados e memória resetados com sucesso." << endl;
                }
            }
            break;
        }
        case 0: break;
        default: cout << endl << "Opção inválida." << endl; break;
    }
}

void Menu::addObject(geometricObject *obj) {
    if (obj) {
        int id = DatabaseManager::getInstance().insert_object(obj);
        if (id != -1) {
            geometricObjects.push_back(obj);
            cout << "Resultado salvo no banco com ID: " << id << endl;
        } else {
            cout << "Erro ao salvar no banco." << endl;
            delete obj;
        }
        return;
    }

    cout << "Selecione o tipo:" << endl;
    cout << "1 - Vetor/Ponto\n2 - Reta\n3 - Polígono\n4 - Circunferência\n0 - Cancelar" << endl;
    int type = getNumericInput();
    if (type == 0) return;
    
    geometricObject* created = nullptr;
    if (type == 1) {
        double x, y; cout << "X Y: "; cin >> x >> y;
        created = new Vector2D(x, y);
    } else if (type == 2) {
        double x1, y1, x2, y2;
        cout << "P1(x y): "; cin >> x1 >> y1;
        cout << "P2(x y): "; cin >> x2 >> y2;
        created = new Line(Vector2D(x1, y1), Vector2D(x2, y2));
    } else if (type == 3) {
        int n; cout << "Num vértices: "; cin >> n;
        vector<Vector2D> verts;
        for(int i=0; i<n; i++) {
            double x, y; cout << "V" << i+1 << ": "; cin >> x >> y;
            verts.emplace_back(x, y);
        }
        created = new Polygon(verts);
    } else if (type == 4) {
        double x, y, r; 
        cout << "Centro(x y): "; cin >> x >> y;
        cout << "Raio: "; cin >> r;
        created = new Circumference(Vector2D(x, y), r);
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (created) {
        int id = DatabaseManager::getInstance().insert_object(created);
        if (id != -1) {
            geometricObjects.push_back(created);
            cout << ">> Sucesso! Objeto salvo no DB com ID " << id << endl;
        } else {
            cout << ">> Erro ao salvar no DB." << endl;
            delete created;
        }
    }
}

void Menu::removeObject() {
    cout << "\n--- Objetos Disponíveis ---" << endl;
    listObjects();
    cout << "---------------------------" << endl;

    cout << "ID a remover: ";
    int id = getNumericInput();
    if (DatabaseManager::getInstance().delete_object(id)) {
        for (auto it = geometricObjects.begin(); it != geometricObjects.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;
                geometricObjects.erase(it);
                break;
            }
        }
    } else {
        cout << "Erro ao remover (ID não existe?)." << endl;
    }
}

void Menu::listObjects() {
    if (geometricObjects.empty()) {
        cout << "Nenhum objeto em memória." << endl;
        return;
    }
    for (const auto& obj : geometricObjects) {
        cout << "ID " << obj->getId() << ": " << obj->serialize() << endl;
    }
}

void Menu::loadObjects() {
    for (auto obj : geometricObjects) delete obj;
    geometricObjects.clear();
    
    auto& db = DatabaseManager::getInstance();
    vector<int> ids = db.get_all_ids();
    for(int id : ids) {
        geometricObject* obj = db.get_object_by_id(id);
        if(obj) geometricObjects.push_back(obj);
    }
    cout << ">> [Auto-Load] " << ids.size() << " objetos carregados do banco de dados." << endl;
}

geometricObject* Menu::getObjectFromUser(int type) {
    cout << "  1. Selecionar existente (ID)" << endl;
    cout << "  2. Criar novo temporário" << endl;
    cout << "  Opção: ";
    int opt = getNumericInput();

    if (opt == 1) {
        if (geometricObjects.empty()) {
            cout << "Nenhum objeto disponível." << endl;
            return nullptr;
        }

        cout << "\n  [Objetos disponíveis do tipo solicitado]:" << endl;
        bool foundAny = false;
        for (auto* obj : geometricObjects) {
            bool isTypeMatch = false;
            if (type == 1 && dynamic_cast<Vector2D*>(obj)) isTypeMatch = true;
            else if (type == 2 && dynamic_cast<Line*>(obj)) isTypeMatch = true;
            else if (type == 3 && dynamic_cast<Polygon*>(obj)) isTypeMatch = true;

            if (isTypeMatch) {
                cout << "   -> ID " << obj->getId() << ": " << obj->serialize() << endl;
                foundAny = true;
            }
        }

        if (!foundAny) {
            cout << "  [!] Nenhum objeto desse tipo encontrado na memória." << endl;
            return nullptr;
        }

        cout << "Digite o ID: ";
        int id = getNumericInput();
        for (auto* obj : geometricObjects) {
            if (obj->getId() == id) {
                bool ok = false;
                if (type == 1 && dynamic_cast<Vector2D*>(obj)) ok = true;
                if (type == 2 && dynamic_cast<Line*>(obj)) ok = true;
                if (type == 3 && dynamic_cast<Polygon*>(obj)) ok = true;
                
                if (ok) return obj;
                else {
                    cout << "Tipo incorreto selecionado." << endl;
                    return nullptr;
                }
            }
        }
        cout << "ID não encontrado." << endl;
        return nullptr;
    } else if (opt == 2) {
        if (type == 1) {
            double x, y; cout << "  X Y: "; cin >> x >> y;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return new Vector2D(x, y);
        } else if (type == 2) {
            double x1, y1, x2, y2;
            cout << "  P1(x y): "; cin >> x1 >> y1;
            cout << "  P2(x y): "; cin >> x2 >> y2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return new Line(Vector2D(x1, y1), Vector2D(x2, y2));
        } else if (type == 3) {
            int n; cout << "  Num vértices: "; cin >> n;
            vector<Vector2D> verts;
            for(int i=0; i<n; i++) {
                double x, y; cout << "  V" << i+1 << ": "; cin >> x >> y;
                verts.emplace_back(x, y);
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return new Polygon(verts);
        }
    }
    return nullptr;
}

void Menu::manageCalculator() {
    cout << "\n=== Calculadora Geométrica ===" << endl;
    for (size_t i = 0; i < calculatorOperations.size(); ++i) {
        cout << (i + 1) << " - " << calculatorOperations[i].name << endl;
    }
    cout << "0 - Voltar" << endl;
    
    int opt = getNumericInput();
    if (opt == 0) return;

    if (opt > 0 && opt <= static_cast<int>(calculatorOperations.size())) {
        calculatorOperations[opt - 1].action();
    } else {
        cout << "Opção inválida." << endl;
    }
}

void Menu::manageConvexHull() {
    cout << "\n=== Fecho Convexo (Convex Hull) ===" << endl;
    cout << "O algoritmo utiliza um conjunto de pontos para gerar o polígono envolvente." << endl;
    
    cout << ">> Selecione o Polígono (ou Nuvem de Pontos) de entrada:" << endl;
    geometricObject* inputObj = getObjectFromUser(3); 
    if (!inputObj) return;

    Polygon* inputPoly = dynamic_cast<Polygon*>(inputObj);
    const vector<Vector2D>& points = inputPoly->getVertices();

    if (points.size() < 3) {
        cout << "Erro: Necessário pelo menos 3 pontos." << endl;
        if(inputObj->getId() == -1) delete inputObj;
        return;
    }

    cout << "\nEscolha o Algoritmo:" << endl;
    cout << "1 - Graham Scan" << endl;
    cout << "2 - Monotone Chain (Andrew's)" << endl;
    int algo = getNumericInput();

    Polygon resultHull;
    if (algo == 1) {
        resultHull = ConvexHull::grahamScan(points);
    } else if (algo == 2) {
        resultHull = ConvexHull::monotoneChain(points);
    } else {
        cout << "Opção inválida." << endl;
        if(inputObj->getId() == -1) delete inputObj;
        return;
    }

    cout << "\n>> Resultado: Polígono com " << resultHull.getVertices().size() << " vértices." << endl;
    cout << resultHull << endl;

    cout << "\nDeseja salvar o resultado no banco? (1-Sim / 0-Não): ";
    if (getNumericInput() == 1) {
        Polygon* toSave = new Polygon(resultHull.getVertices());
        addObject(toSave);
    }

    if(inputObj->getId() == -1) delete inputObj;
}

void Menu::manageMinCircle() {
    cout << "\n=== Círculo Mínimo (Welzl Iterativo) ===" << endl;
    cout << ">> Selecione o Polígono (pontos):" << endl;
    
    geometricObject* inputObj = getObjectFromUser(3); // Tipo 3 = Polígono
    if (!inputObj) return;

    Polygon* poly = dynamic_cast<Polygon*>(inputObj);
    const auto& points = poly->getVertices();

    if (points.empty()) {
        cout << "Erro: O objeto selecionado não contém pontos." << endl;
        if(inputObj->getId() == -1) delete inputObj;
        return;
    }

    // Execução do algoritmo
    Circumference res = MinCircle::find(points);

    cout << "\n>> Resultado: " << res << endl;
    
    cout << "\nDeseja salvar o resultado no banco? (1-Sim / 0-Não): ";
    if (getNumericInput() == 1) {
        // Cria uma nova instância para salvar no DatabaseManager
        Circumference* toSave = new Circumference(res.getCenter(), res.getRadius());
        addObject(toSave);
    }

    // Limpeza de memória se o objeto de entrada foi criado temporariamente
    if(inputObj->getId() == -1) delete inputObj;
}

void Menu::managePlotter() {
    cout << "\n=== Visualização (Plotter) ===" << endl;
    cout << "1 - Plotar TUDO" << endl;
    cout << "2 - Plotar Subconjunto por IDs" << endl;
    cout << "3 - Plotar Subconjunto por Tipo" << endl;
    cout << "4 - Salvar último plot" << endl;
    cout << "0 - Voltar" << endl;

    cout << "Opção: ";
    int opt = getNumericInput();

    if (opt == 1) {
        if (geometricObjects.empty()) {
            cout << "Nenhum objeto para plotar." << endl;
        } else {
            plotter.plot(geometricObjects);
        }
    } 
    else if (opt == 2) {
        // --- ADDED: List objects before asking for IDs ---
        cout << "\n--- Objetos Disponíveis ---" << endl;
        listObjects();
        cout << "---------------------------" << endl;

        cout << "Digite os IDs separados por espaço (ex: 1 2 5): ";
        string line;
        std::getline(cin, line);
        
        stringstream ss(line);
        int id;
        vector<int> targetIds;
        while(ss >> id) {
            targetIds.push_back(id);
        }

        vector<geometricObject*> subset;
        for (auto* obj : geometricObjects) {
            for (int t : targetIds) {
                if (obj->getId() == t) {
                    subset.push_back(obj);
                    break; 
                }
            }
        }

        if (subset.empty()) {
            cout << "Nenhum objeto com os IDs fornecidos foi encontrado." << endl;
        } else {
            cout << "Plotando " << subset.size() << " objetos..." << endl;
            plotter.plot(subset);
        }
    } 
    else if (opt == 3) {
        cout << "Escolha o tipo: " << endl;
        cout << "1 - Vetor/Ponto\n2 - Reta\n3 - Polígono\n4 - Circunferência" << endl;
        int type = getNumericInput();

        vector<geometricObject*> subset;
        for (auto* obj : geometricObjects) {
            bool match = false;
            if (type == 1 && dynamic_cast<Vector2D*>(obj)) match = true;
            else if (type == 2 && dynamic_cast<Line*>(obj)) match = true;
            else if (type == 3 && dynamic_cast<Polygon*>(obj)) match = true;
            else if (type == 4 && dynamic_cast<Circumference*>(obj)) match = true;

            if (match) subset.push_back(obj);
        }

        if (subset.empty()) {
            cout << "Nenhum objeto desse tipo encontrado." << endl;
        } else {
            cout << "Plotando " << subset.size() << " objetos..." << endl;
            plotter.plot(subset);
        }
    } 
    else if (opt == 4) {
        string f; 
        cout << "Nome do arquivo (ex: plot.png): "; 
        std::getline(cin, f);
        if (f.empty()) f = "plot.png";
        plotter.saveFigure(f);
    }
}

void Menu::askAddResult(geometricObject*) { }

int Menu::getMaxId() { return 0; }
