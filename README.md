# Cartesia

**Cartesia** é uma ferramenta de geometria computacional híbrida (C++/Python).O projeto visa aplicar conhecimentos de álgebra linear, algoritmos e estruturas de dados para realizar tarefas geométricas complexas, como o cálculo de Fecho Convexo (Convex Hull) e Círculo Mínimo, além de oferecer visualização gráfica integrada.

O sistema utiliza **C++** para o gerenciamento de objetos e cálculos matemáticos, **SQL** (SQLite) para persistência de dados e **Python** (Matplotlib) para renderização gráfica.

## Funcionalidades

* **Gerenciamento de Objetos (SQL):** Persistência dinâmica de Pontos (Vetores), Segmentos (Retas), Polígonos e Circunferências.
* **Calculadora Geométrica:** Operações aritméticas entre vetores e formas geométricas.
* **Algoritmos Avançados:**
    * **Polígono Convexo:** Determina o menor polígono convexo que envolve um conjunto de pontos.
    * **Círculo Mínimo:** Encontra o círculo de menor raio que contém todos os pontos.
* **Visualização Híbrida:** Plotagem interativa e exportação de figuras via script Python embarcado.

## Pré-requisitos

Para compilar e executar o Cartesia, você precisa de um ambiente Linux com compilador C++17, Python 3.9+ e bibliotecas de desenvolvimento do SQLite.

### Arch Linux
```bash
sudo pacman -S gcc python python-matplotlib python-pyqt5 sqlite base-devel
```

### Ubuntu / Debian
```bash
sudo apt-get update
sudo apt-get install g++ python3-dev python3-matplotlib python3-pyqt5 libsqlite3-dev build-essential
```

## Instalação

O projeto utiliza um `Makefile` automatizado que gerencia tanto as dependências do Python quanto a compilação do C++.

1.  **Instalação Completa:**
    Execute o comando abaixo para instalar as dependências Python (em modo editável) e compilar o binário C++.
```bash
make install
```

2.  **Apenas Compilar (se já instalado):**
```bash
make
```

3.  **Limpar Arquivos de Build:**
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
3 - Polígono Convexo
4 - Círculo Mínimo
5 - Visualização (Plotter)
0 - Sair
```

## Estrutura do Projeto

O projeto foi refatorado para seguir padrões profissionais de C++:

```text
Cartesia/
├── bin/                  # Executável compilado (cartesia)
├── build/                # Arquivos objeto (.o) e dependências (.d)
├── include/              # Headers (.h)
│   ├── database.h        # Gerenciador do SQLite
│   └── geometricObjects/ # Definições de classes (Vector2D, Polygon, etc.)
├── src/                  # Implementação (.cpp)
│   ├── main.cpp          # Ponto de entrada
│   ├── database.cpp      # Implementação do Singleton de Banco de Dados
│   ├── menu.cpp          # Lógica de interface CLI
│   └── geometricObjects/ # Lógica das formas geométricas
├── scripts/              # Scripts Python (plotter.py)
├── Makefile              # Automação de build (C++ e Python)
├── pyproject.toml        # Configuração de dependências Python
└── README.md             # Documentação
```

## Autores

* **Luís Rafael Sena**
* **Pedro Videira Rubinstein**

Desenvolvido para a disciplina **EEL670**, Setembro de 2025.

## Licença

Este projeto é de código aberto e está licenciado sob a licença MIT.
