# ITMS for ABC Solutions Sdn. Bhd

---

## Project Description

This project develops a Blockchain-Integrated Inventory and Transportation Management System (ITMS) for ABC Solutions Sdn. Bhd.,
a hypothetical supplier company in Malaysia, using C++. By incorporating blockchain's decentralized ledger, immutable records,
and smart contract capabilities, the system aims to enhance operational efficiency, ensure transactional security and transparency,
and foster stakeholder trust. Designed to tackle the complexities of post-pandemic supply chains,
this innovative C++-based ITMS positions ABC Solutions for sustainable growth and a competitive edge,
demonstrating a forward-thinking approach to overcoming traditional logistical challenges.

## Report Documentation

The report documentation for this project can be found in `report-documentation.pdf` in the root directory. The report provides a detailed overview 
and implementation of the ITMS project.

## File Placements

1. You can find the `.exe` within the `cmake-build-debug` folder.
2. You can find the `.obj` within the `cmake-build-debug/CMakeFiles` folder.

## CLion Project Setup and Execution Guide

This guide provides detailed instructions on how to setup and run the provided C++ project using CLion IDE.

### Prerequisites

- Ensure that you have at least CLion Version 2023.2.2 installed on your machine.
- Ensure you have a C++ compiler installed and configured in CLion.

### Opening the Project in CLion

1. Launch CLion.
2. From the welcome screen, select 'Open'.
3. Navigate to the root directory of the project where you see the LICENSE.txt file.
4. Select the root directory and click 'Open'. CLion will automatically detect the CMake project file and configure your project accordingly.

### Configuring Project Settings

1. Wait for CLion to finish indexing the project.
2. If there are any dependencies required by the project, ensure they are installed on your system and properly referenced in the CMakeLists.txt file.
3. Go to 'File' > 'Settings' (on Windows) or 'CLion' > 'Preferences' (on macOS) > 'Build, Execution, Deployment' to customize build options if needed.

### Building the Project

1. Click on 'Build' in the main menu, then select 'Build Project'.
   Alternatively, you can press Ctrl+F9 on Windows/Linux or Cmd+F9 on macOS.
2. The 'cmake-build-debug' folder will be populated with build artifacts.

### Running the Project

1. To run the project, navigate to 'src' directory in the Project panel.
2. Right-click on the `main.cpp` file.
3. Select 'Run 'main' from the context menu to compile and execute the program.
   Alternatively, you can click on the green play button in the top-right corner of the IDE.

### Viewing and Interacting with the Application

- After running the program, the console at the bottom of the CLion window will display the output.
- If the program requires input, you can interact with it through the same console.

### Debugging

1. Set breakpoints by clicking in the gutter next to the line numbers in the editor.
2. Right-click on the main.cpp file and select 'Debug 'main'' to start debugging.
3. Use the debugging tools provided by CLion to step through the code, inspect variables, and evaluate expressions.

### License Information

- Make sure to read the `LICENSE.txt` file in the root project directory to understand the licensing terms of the project.
