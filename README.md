# IoT Temperature Control Simulation

This project simulates a simple IoT temperature control system with three main components:

1. Temperature Sensor (C) temp_sensor.c
2. Thermostat (Python) thermostat.py
3. AC Control (Python) ac.py

## Requirements:

- Windows 10 or later
- Visual Studio 2019 or later (for C compilation)
- Python 3.7 or later
- pip (Python package manager)

## Installation:

1. Ensure you have Visual Studio and Python installed on your system.

2. Clone the repository:
   git clone https://github.com/thecorruptedangel/IoT-Temperature-Control-Simulation.git

3. Navigate to project directory:
   cd IoT-Temperature-Control-Simulation

4. Install required Python packages:
   pip install -r requirements.txt

5. Open Visual Studio and load the temp_sensor.c file.
   - Create a new C++ Console Application project.
   - Replace the contents of the main .cpp file with the code from temp_sensor.c.
   - Rename the file to temp_sensor.c.
   - In project properties, under C/C++ > Advanced, set "Compile As" to "Compile as C Code (/TC)".
   - In project properties, under Linker > Input, add "Ws2_32.lib" to Additional Dependencies.
   - Build the project in Release mode.

The project solution file created on Visual Studio 2022 is also included for reference as 'temp_sensor.zip'

- Open the `temp_sensor.sln` file in Visual Studio.
- Build the solution in Release mode.

## Execution:

1. Temperature Sensor:

   - Open a command prompt in the Visual Studio project's Release directory.
   - Run the compiled executable:
     temp_sensor.exe

2. AC Control:

   - Open a new command prompt in the project directory.
   - Run the AC control script:
     python ac.py

3. Thermostat:
   - Open another command prompt in the project directory.
   - Run the thermostat script:
     python thermostat.py
   - Follow the prompts to set the temperature threshold (between 20-25°C).

## Notes:

- Ensure all three components are running simultaneously for proper operation.
- The Temperature Sensor must be started before the Thermostat.
- The AC Control script uses Flask and runs on http://localhost:5000
- Check the console outputs of each component for status updates and temperature changes.
- To stop the simulation, close all command prompt windows or press Ctrl+C in each.

## Troubleshooting:

- If you encounter connection errors, ensure no other applications are using the required ports (12345 for Temperature Sensor, 5000 for AC Control).
- Verify that your firewall is not blocking the applications.
- If Python scripts fail to run, ensure you've installed all required packages and are using the correct Python version.
