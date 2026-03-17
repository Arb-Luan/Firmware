
import serial
import requests
import time

API_KEY = "THINGSPEAK_API_KEY"   # Replace with your ThingSpeak Write API Key
ARDUINO_PORT = "COMX"            # Replace with your serial port (e.g., COM5 or /dev/ttyUSB0)
BAUD_RATE = 9600
INTERVAL = 30                    # Seconds between updates

arduino = serial.Serial(ARDUINO_PORT, BAUD_RATE, timeout=1)
time.sleep(2)

print(f"Connected to Arduino at {ARDUINO_PORT}")

last_value = None
last_send = 0


def parse_data(data):
    """
    Convert serial data into a numeric value.
    Customize this function depending on your device output.
    """
    if data == "APERTADO":
        return 1
    return 0


def send_to_thingspeak(value):
    url = f"https://api.thingspeak.com/update?api_key={API_KEY}&field1={value}"
    response = requests.get(url)
    return response


while True:
    try:
        data = arduino.readline().decode(errors="ignore").strip()

        if data:
            value = parse_data(data)

            if value != last_value or (time.time() - last_send) >= INTERVAL:
                response = send_to_thingspeak(value)

                if response.status_code == 200:
                    print(f"Sent value: {value} | Response: {response.text}")
                    last_value = value
                    last_send = time.time()
                else:
                    print("HTTP Error:", response.status_code)

        time.sleep(1)

    except KeyboardInterrupt:
        print("\nProgram terminated.")
        break

    except Exception as e:
        print("Error:", e)
