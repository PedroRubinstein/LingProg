#ifndef PLOTTER_H
#define PLOTTER_H

#include <vector>
#include <string>
#include "geometricObjects/geometricobject.h"

/**
 * @brief Gerencia a integração com Python (Matplotlib) para visualização.
 */
class Plotter {
public:
    Plotter();
    ~Plotter();

    /**
     * @brief Plota uma lista de objetos geométricos numa janela gráfica.
     * * Converte os objetos C++ para dicionários Python e invoca o script de plotagem.
     * * @param objects Vetor de ponteiros para os objetos a desenhar.
     */
    void plot(const std::vector<geometricObject*> &objects);

    /**
     * @brief Salva a última figura gerada em um arquivo de imagem.
     * * @param filename Nome do arquivo de destino (ex: "plot.png").
     * @return true Se salvo com sucesso.
     */
    bool saveFigure(const std::string &filename);
};

#endif // PLOTTER_H
