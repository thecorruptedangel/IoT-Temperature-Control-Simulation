import requests
import time
import socket
import sys

def get_temperature():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(('localhost', 12345))
            s.sendall(b'GET_TEMP')
            return int(s.recv(1024).decode())
    except ConnectionRefusedError:
        print("Error: Unable to connect to the temperature sensor. Make sure it's running.")
        return None

def main():
    print("----- IoT Sensor & Control simulator -----")
    print("-----       thermostat module        ----- \n\n")
    threshold = int(input("Enter temperature threshold (between 20-25 Celsius): "))
    while threshold < 20 or threshold > 25:
        threshold = int(input("Invalid input. Enter temperature threshold (between 20-25 Celsius): "))

    ac_url = "http://localhost:5000"
    
    while True:
        temp = get_temperature()
        if temp is None:
            print("Retrying in 5 seconds...")
            time.sleep(5)
            continue
        
        print(f"Current temperature: {temp}°C")
        
        try:
            if temp > threshold:
                print("Temperature above threshold. Turning ON AC.")
                requests.get(f"{ac_url}/start")
            elif temp < threshold:
                print("Temperature below threshold. Turning OFF AC.")
                requests.get(f"{ac_url}/stop")
            
            status = requests.get(f"{ac_url}/status").json()
            print(f"AC status: {status['status']}")
        except requests.RequestException as e:
            print(f"Error communicating with AC control. Make sure AC control module is running..")
        
        time.sleep(5)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nProgram terminated by user.")
        sys.exit(0)