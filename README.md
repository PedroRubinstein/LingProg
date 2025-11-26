# Cartesia

**Cartesia** é uma ferramenta de geometria computacional híbrida (C++/Python). O projeto visa aplicar conhecimentos de álgebra linear, algoritmos e estruturas de dados para realizar tarefas geométricas complexas, como o cálculo de Fecho Convexo (Convex Hull) e Círculo Mínimo, além de oferecer visualização gráfica integrada.

O sistema utiliza **C++** para o gerenciamento de objetos e cálculos matemáticos, **SQL** (SQLite) para persistência de dados e **Python** (Matplotlib) para renderização gráfica.

## Funcionalidades

* **Gerenciamento de Objetos (SQL):** Persistência dinâmica de Pontos (Vetores), Segmentos (Retas), Polígonos e Circunferências. Inclui funcionalidade de **Reset Completo** do banco de dados.
* **Calculadora Geométrica:** Operações aritméticas entre vetores, interseção de retas e cálculo de área (com alertas de consistência).
* **Algoritmos Avançados:**
    * **Polígono Convexo:** Determina o menor polígono convexo que envolve um conjunto de pontos utilizando os algoritmos **Graham Scan** ou **Monotone Chain**.
    * **Círculo Mínimo:** (Em desenvolvimento) Encontra o círculo de menor raio que contém todos os pontos.
* **Visualização Híbrida:** Plotagem interativa com opções de **filtragem por ID ou Tipo**, além de exportação de figuras.

## Pré-requisitos

Para compilar e executar o Cartesia, você precisa de um ambiente Linux com compilador C++17, Python 3.9+, bibliotecas de desenvolvimento do SQLite e a **biblioteca JSON for Modern C++**.

### Arch Linux
```bash
sudo pacman -S gcc python sqlite base-devel nlohmann-json
```

### Ubuntu / Debian
```bash
sudo apt-get update
sudo apt-get install g++ python3-dev libsqlite3-dev nlohmann-json3-dev build-essential
```

## Instalação

O projeto utiliza `pyproject.toml` para gerenciamento de dependências Python e um `Makefile` para a compilação do C++.

1.  **Instalar Dependências Python:**
    Execute o comando abaixo na raiz do projeto para instalar as bibliotecas necessárias (Matplotlib, PyQt5, etc):
```bash
pip install .
```

2.  **Compilar o Projeto C++:**
```bash
make
```

3.  **Limpar Arquivos de Build (Opcional):**
```bash
make clean
```

## Como Usar

Após a compilação, o executável é gerado no diretório `bin/`.

1.  **Executar a Aplicação:**
```bash
./bin/cartesia
```

2.  **Menu Interativo:**
    O programa apresenta um menu no terminal com as seguintes opções:

```text
===== Menu Principal =====
1 - Gerenciamento de Objetos Geométricos (SQL)
2 - Calculadora Geométrica
3 - Fecho Convexo (Convex Hull)
4 - Círculo Mínimo (Não implementado)
5 - Visualização (Plotter)
0 - Sair
```

## Estrutura do Projeto

O projeto foi refatorado para seguir padrões profissionais de C++ e empacotamento Python:

```text
Cartesia/
├── bin/                  # Executável compilado (cartesia)
├── build/                # Arquivos objeto (.o) e dependências (.d)
├── include/              # Headers (.h)
│   ├── algorithms/       # Algoritmos (convexhull.h)
│   ├── database.h        # Gerenciador do SQLite
│   └── geometricObjects/ # Definições de classes (Vector2D, Polygon, etc.)
├── src/                  # Implementação (.cpp)
│   ├── main.cpp          # Ponto de entrada
│   ├── database.cpp      # Implementação do Singleton de Banco de Dados
│   ├── menu.cpp          # Lógica de interface CLI
│   ├── algorithms/       # Implementação de Algoritmos (convexhull.cpp)
│   └── geometricObjects/ # Lógica das formas geométricas
├── scripts/              # Scripts Python (plotter.py)
├── Makefile              # Automação de build (C++)
├── pyproject.toml        # Configuração de dependências Python
├── MANIFEST.in           # Regras de inclusão de arquivos para distribuição
└── README.md             # Documentação
```

## Autores

* **Luís Rafael Sena**
* **Pedro Videira Rubinstein**

Desenvolvido para a disciplina **EEL670**, Setembro de 2025.

## Licença

Este projeto é de código aberto e está licenciado sob a licença MIT.
