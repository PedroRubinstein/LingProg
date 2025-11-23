# Cartesia

**Cartesia** is a hybrid C++/Python geometric modeling engine. It leverages the raw performance of C++ for geometric object management and calculations, while embedding a Python interpreter to utilize **Matplotlib** for high-quality visualization.

## Features

* **Hybrid Architecture:** Seamless integration between C++ (backend) and Python (frontend/plotting).
* **Geometric Primitives:** Support for creating and managing:
    * Vectors (2D)
    * Lines (Segments)
    * Polygons (Arbitrary vertices)
    * Circumferences (Center + Radius)
* **Visualization:** Plot geometric objects instantly using Matplotlib.
* **Command Line Interface:** Interactive menu for object management.

## Prerequisites

To build and run Cartesia, you need a Linux environment with a C++17 compiler and Python 3.9+ installed with development headers.

### Arch Linux
```bash
sudo pacman -S gcc python python-matplotlib python-pyqt5 base-devel
```

### Ubuntu / Debian
```bash
sudo apt-get update
sudo apt-get install g++ python3-dev python3-matplotlib python3-pyqt5 build-essential
```

## Installation

Cartesia uses a combination of `pip` (for Python environment) and `make` (for C++ compilation).

1.  **Install Python Dependencies:**
    This installs the required Python libraries and links the `scripts/` folder in editable mode so the C++ binary can find them.
```bash
pip install -e .
```

2.  **Compile the C++ Engine:**
    Use the `Makefile` to compile the source code and link it against the Python library.
```bash
make
```

## Usage

Once compiled, the executable is placed in the `bin/` directory.

1.  **Run the Application:**
```bash
./bin/cartesia
```

2.  **Interactive Menu:**
    * **Option 1:** Add, remove, or list geometric objects.
    * **Option 5:** Generate a plot of all current objects.

    *Example Workflow:*
```text
> 1 (Manage Objects)
> 1 (Add Object)
> 3 (Polygon)
> Enter vertices...
> 0 (Back)
> 5 (Visualization) -> Opens a window with the shape
```

## Project Structure

The project follows a standard C++ directory layout:

```text
Cartesia/
├── bin/                  # Compiled executable (cartesia)
├── build/                # Intermediate object files (.o, .d)
├── include/              # Header files (.h)
│   └── geometricObjects/ # Geometry class definitions
├── src/                  # Source files (.cpp)
│   └── geometricObjects/ # Geometry class implementations
├── scripts/              # Python plotting scripts
├── Makefile              # Build configuration
├── pyproject.toml        # Python project configuration
└── README.md             # Documentation
```

## Authors

* **Developer**: [Luís Rafael Sena](https://github.com/ifuaslaerl)

## License

This project is licensed under the MIT License - see the LICENSE file for details.
