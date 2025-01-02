a simple MQTT sub-scriber example running on the ESP32 'CYD'

built in Arduino 2.x IDE
MQTT uses "PubSubClient" from https://github.com/knolleary/pubsubclient

--- commit notes ---
01/02/2025 MAR
It builds clean.
Can't test at the moment due to COM port issues between Arduino 2.3.1 IDE and system:
    esptool.py v4.6
    Serial port COM4
    Connecting....

    A serial exception error occurred: Cannot configure port, something went wrong. Original message: PermissionError(13, 'Access is denied.', None, 5)
    Note: This error originates from pySerial. It is likely not a problem with esptool, but with the hardware connection or drivers.
    For troubleshooting steps visit: https://docs.espressif.com/projects/esptool/en/latest/troubleshooting.html
