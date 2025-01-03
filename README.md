# 2D Physics Engine

This project is a 2D physics engine built in C++ that uses **SFML** for rendering and **Premake** for project configuration. It is designed to simulate basic physics and showcase the engine's capabilities through a simple example application.

The project is modular, consisting of two parts:
1. **PhysicsEngine** - The core physics module, which implements collision detection and physics simulation for AABBs and circles.
2. **ShowCase** - An application demonstrating the engine's features, such as spawning AABBs and circles by holding the left or right mouse button.

## Features
- **Physics Simulation**: Supports Axis-Aligned Bounding Boxes (AABBs) and circles.
- **Collision Detection**: Handles collisions between AABBs and circles.
- **Integration with SFML**: Uses SFML for rendering and input handling.
- **Premake Build System**: Easily generate project files for various platforms.

## Getting Started

### Prerequisites
1. **C++ Compiler**:
   - Windows: Visual Studio 2022 or later.
   - Linux: GCC or Clang.
2. **SFML**: Download and extract SFML ([official site](https://www.sfml-dev.org/).
3. **Premake**: The project includes Premake binaries (v5.0-beta2) for Windows, macOS, and Linux.

### Steps to Run the Project
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/trier111/2DPhysicsEngine.git
   cd 2DPhysicsEngine
   ### Set Up SFML:
- Update the `SFML_DIR` variable in the `ShowCase/Build-App.lua` file to point to your SFML installation path.

### Generate Project Files:
- Run the appropriate script from the `Scripts/` directory:
  - On Windows:
    ```bash
    Scripts/Setup-Windows.bat
    ```
  - On Linux:
    ```bash
    ./Scripts/Setup-Linux.sh
    ```

### Build the Project:
- Open the generated solution/project file (e.g., Visual Studio on Windows or Makefiles on Linux) and build the desired configuration (`Debug`, `Release`, or `Dist`).

### Run the ShowCase Application:
- After building, navigate to the `Binaries/<configuration>/ShowCase` directory and run the executable.

### Example Usage
- Hold **Left Mouse Button (LMB)** to spawn circles.
- Hold **Right Mouse Button (RMB)** to spawn AABBs.
- Observe collision detection and response in real-time.

### Project Structure
- `PhysicsEngine/`: Core physics engine module (static library).
- `ShowCase/`: Application module showcasing the engine.
- `Scripts/`: Build scripts for setting up the project.

### Video Demonstration
A video showcasing the project will be available soon. Stay tuned!

### License
- The project is licensed under the **UNLICENSE** (see `UNLICENSE.txt` for details).
- Premake is licensed under the **BSD 3-Clause License** (see `Vendor/LICENSE.txt`).