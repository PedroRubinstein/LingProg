#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <functional> 
#include "geometricObjects/geometricobject.h" 
#include "plotter.h"         

/**
 * @brief Classe principal de interface (CLI) da aplicação.
 * * Gerencia o loop principal, leitura de entrada do usuário e orquestração
 * entre Banco de Dados, Calculadora e Plotter.
 */
class Menu {
public:
    /**
     * @brief Construtor. Inicializa o menu e carrega objetos do banco.
     */
    Menu(); 
    ~Menu();

    /**
     * @brief Inicia o loop principal de interação com o usuário.
     * Bloqueia a execução até que o usuário escolha sair.
     */
    void showMenu();

private:
    /**
     * @brief Processa a escolha numérica do menu principal.
     * @param option O número da opção escolhida.
     */
    void processOption(int option);
    
    /**
     * @brief Lê um inteiro da entrada padrão com tratamento de erros.
     * @return int O valor lido.
     */
    int getNumericInput();
    
    /**
     * @brief Pausa a execução aguardando um ENTER do usuário.
     */
    void pauseForEnter();

    // Sub-menus de gerenciamento
    void manageObjects();
    void manageCalculator();
    void manageConvexHull();
    void manageMinCircle();
    void managePlotter();

    struct CalculatorOp {
        std::string name;
        std::function<void()> action;
    };
    std::vector<CalculatorOp> calculatorOperations;
    void registerCalculatorOperations();

    // Auxiliares de CRUD
    void addObject(geometricObject* obj = nullptr);
    void removeObject();
    void listObjects();
    void loadObjects(); // Sincroniza memória com DB

    void askAddResult(geometricObject* obj);
    int getMaxId();

    /**
     * @brief Solicita ao usuário que selecione um objeto existente ou crie um novo.
     * @param type O tipo de objeto esperado (1=Vector, 2=Line, 3=Poly).
     * @return geometricObject* Ponteiro para o objeto (novo ou existente).
     */
    geometricObject* getObjectFromUser(int type);

    /**
     * @brief Lê os dados de um objeto geométrico a partir do console.
     * @param type O tipo de objeto a ser lido (1=Vector, 2=Line, 3=Poly, 4=Circumference).
     * @return geometricObject* Ponteiro para o novo objeto criado.
     */
    geometricObject* readObjectFromConsole(int type);

    std::vector<geometricObject*> geometricObjects;
    Plotter plotter;
};

#endif
