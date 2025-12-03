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

// Helper local para forçar o tipo 'Point' (que será plotado em Azul)
class PointWrapper : public Vector2D {
public:
    using Vector2D::Vector2D;
    geometricObject::Type type() const override { return geometricObject::Type::Point; }
};

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
        "Localização de Ponto (Esq/Dir/Colinear)",
        [this]() {
            cout << ">> Defina o Segmento de referência:" << endl;
            geometricObject* l = getObjectFromUser(2);
            if (!l) return;

            cout << ">> Defina o Ponto de teste:" << endl;
            geometricObject* p = getObjectFromUser(1);
            if (!p) { if(l->getId()==-1) delete l; return; }

            // ANTES: Calculator::pointLocationTest(...)
            // DEPOIS: Chamada direta no objeto Line
            Line* lineObj = dynamic_cast<Line*>(l);
            Vector2D* pointObj = dynamic_cast<Vector2D*>(p);
            
            cout << "\n>> Resultado: " << lineObj->pointLocation(*pointObj) << endl;

            if(l->getId() == -1) delete l;
            if(p->getId() == -1) delete p;
        }
    });

    calculatorOperations.push_back({
        "Interseção de Segmentos",
        [this]() {
            // ... (código de obter s1 e s2 igual) ...
            geometricObject* s1 = getObjectFromUser(2);
            if(!s1) return;
            geometricObject* s2 = getObjectFromUser(2);
            if(!s2) { if(s1->getId()==-1) delete s1; return; }

            // ANTES: Calculator::checkIntersection(...)
            // DEPOIS: Chamada direta
            bool res = dynamic_cast<Line*>(s1)->intersects(*dynamic_cast<Line*>(s2));
            
            cout << "\n>> Resultado: " << (res ? "INTERCEPTAM" : "NÃO INTERCEPTAM") << endl;
            
            if(s1->getId() == -1) delete s1;
            if(s2->getId() == -1) delete s2;
        }
    });

    calculatorOperations.push_back({
        "Área de Polígono",
        [this]() {
            // ...
            geometricObject* poly = getObjectFromUser(3);
            if(!poly) return;

            // ANTES: Calculator::polygonArea(...)
            // DEPOIS: Chamada direta
            double area = dynamic_cast<Polygon*>(poly)->getArea();
            
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

geometricObject* Menu::readObjectFromConsole(int type) {
    geometricObject* created = nullptr;

    if (type == 1) { // Vector2D
        Vector2D* vec = new Vector2D();
        cout << "  Digite as coordenadas (X Y): "; 
        cin >> *vec;
        created = vec;
    } 
    else if (type == 2) { // Line [MODIFICADO]
        Line* line = new Line();
        Vector2D p1, p2;

        cout << "  Definindo Segmento de Reta:" << endl;
        
        cout << "  -> Ponto Inicial (X Y): ";
        cin >> p1; // Usa Vector2D::operator>>
        
        cout << "  -> Ponto Final (X Y): ";
        cin >> p2; // Usa Vector2D::operator>>

        line->setP1(p1);
        line->setP2(p2);
        created = line;
    } 
    else if (type == 3) { // Polygon (Já modificado anteriormente)
        Polygon* poly = new Polygon();
        int n = 0;
        
        while (true) {
            cout << "  Quantos vértices terá o polígono? (Min: 3): ";
            if (cin >> n && n >= 3) break;
            cout << "  [!] Entrada inválida. Mínimo 3 vértices." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        for (int i = 0; i < n; ++i) {
            Vector2D v;
            cout << "  -> Vértice " << (i + 1) << " (X Y): ";
            cin >> v;
            poly->addVertex(v);
        }
        created = poly;
    } 
    else if (type == 4) { // Circumference [MODIFICADO]
        Circumference* circ = new Circumference();
        Vector2D center;
        ld radius;

        cout << "  Definindo Circunferência:" << endl;

        cout << "  -> Centro (X Y): ";
        cin >> center; // Usa Vector2D::operator>>

        cout << "  -> Raio: ";
        cin >> radius;

        circ->setCenter(center);
        circ->setRadius(radius);
        created = circ;
    }

    // Limpar buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return created;
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
    cout << "1 - Vetor/Ponto\n2 - Segmento\n3 - Polígono\n4 - Circunferência\n0 - Cancelar" << endl;
    int type = getNumericInput();
    if (type == 0) return;
    
    geometricObject* created = readObjectFromConsole(type);

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
        return readObjectFromConsole(type);
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
    const vector<Vector2D>& originalPoints = inputPoly->getVertices();

    if (originalPoints.size() < 3) {
        cout << "Erro: Necessário pelo menos 3 pontos." << endl;
        if(inputObj->getId() == -1) delete inputObj;
        return;
    }

    // [NOVO] Opção de Visualização
    cout << "Deseja visualizar passo-a-passo? (1-Sim / 0-Não): ";
    int visualize = getNumericInput();

    ConvexHull::StepCallback stepAction = nullptr;

    if (visualize == 1) {
        cout << ">> [INFO] Feche a janela do gráfico para avançar o passo." << endl;
        cout << ">> [LEGENDA] Azul: Pontos originais | Laranja: Fecho parcial | Vermelho: Ponto atual" << endl;

        stepAction = [this, originalPoints](const vector<Vector2D>& currHull, const Vector2D& currP) {
            vector<geometricObject*> frameObjects;

            // 1. Desenha todos os pontos originais como "fundo" (Azul)
            for (const auto& p : originalPoints) {
                frameObjects.push_back(new PointWrapper(p.getX(), p.getY()));
            }

            // 2. Desenha o fecho parcial (Polígono Laranja)
            if (!currHull.empty()) {
                frameObjects.push_back(new Polygon(currHull));
            }

            // 3. Destaca o ponto sendo processado (Vermelho)
            // Usamos Vector2D padrão que o plotter renderiza como 'ro' (red dot)
            frameObjects.push_back(new Vector2D(currP.getX(), currP.getY()));

            // Plota
            plotter.plot(frameObjects);

            // Limpeza
            for (auto* obj : frameObjects) delete obj;
        };
    }

    // Executa o algoritmo com o callback (se houver)
    Polygon resultHull = ConvexHull::monotoneChain(originalPoints, stepAction);

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
    
    geometricObject* inputObj = getObjectFromUser(3);
    if (!inputObj) return;

    Polygon* poly = dynamic_cast<Polygon*>(inputObj);
    const auto& points = poly->getVertices();

    if (points.empty()) {
        cout << "Erro: Sem pontos." << endl;
        if(inputObj->getId() == -1) delete inputObj;
        return;
    }

    cout << "Deseja visualizar passo-a-passo? (1-Sim / 0-Não): ";
    int visualize = getNumericInput();

    MinCircle::StepCallback stepAction = nullptr;

    if (visualize == 1) {
        cout << ">> [INFO] Feche a janela do gráfico para avançar o passo." << endl;
        
        stepAction = [this](const Circumference& c, const vector<Vector2D>& all_pts, const vector<Vector2D>& active_pts) {
            vector<geometricObject*> frameObjects;
            
            // 1. Output no Terminal (Pedido Solicitado)
            cout << c << endl;

            // 2. Lógica de Destaque
            for (const auto& p : all_pts) {
                bool isActive = false;
                // Verifica se 'p' é um dos pontos ativos (usando distSq para evitar erro de float)
                for(const auto& a : active_pts) {
                    if (Vector2D::distSq(p, a) < 1e-9) { 
                        isActive = true; break; 
                    }
                }

                if (isActive) {
                    // Envia como Vector2D -> Plotter recebe 'vector' -> Vermelho
                    frameObjects.push_back(new Vector2D(p.getX(), p.getY())); 
                } else {
                    // Envia como PointWrapper -> Plotter recebe 'point' -> Azul
                    frameObjects.push_back(new PointWrapper(p.getX(), p.getY()));
                }
            }
            
            frameObjects.push_back(new Circumference(c.getCenter(), c.getRadius()));
            plotter.plot(frameObjects);
            
            for (auto* obj : frameObjects) delete obj;
        };
    }

    Circumference res = MinCircle::find(points, stepAction);

    cout << "\n>> Resultado Final: " << res << endl;
    
    cout << "\nDeseja salvar? (1-Sim / 0-Não): ";
    if (getNumericInput() == 1) {
        addObject(new Circumference(res.getCenter(), res.getRadius()));
    }

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
        cout << "1 - Vetor/Ponto\n2 - Segmento\n3 - Polígono\n4 - Circunferência" << endl;
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
