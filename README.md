# ESP32 ThingsBoard Multi-Function Client

This project demonstrates multiple **ThingsBoard** functionalities with ESP32 using **3 different buttons** for various data transmission types. Each button triggers a different type of communication with ThingsBoard IoT platform, simulated in **Wokwi**.

## 🎯 Features

- **3-Button Interface**: Different buttons for different functionalities
- **Telemetry Data**: Send sensor data (temperature, humidity) 
- **Client Attributes**: Send device/network information
- **RPC Requests**: Request server information with response handling
- **Serial Feedback**: Detailed logging of all operations
- **Wokwi Simulation**: Complete hardware simulation with 3 labeled buttons

## 📚 Dependencies and Libraries

### PlatformIO Libraries
```ini
lib_deps = 
    thingsboard/ThingsBoard@0.14.0                    # ThingsBoard MQTT Client
    arduino-libraries/ArduinoHttpClient@^0.6.1        # HTTP Client
    arduino-libraries/ArduinoMqttClient@^0.1.8        # MQTT Client
    knolleary/PubSubClient@^2.8                       # MQTT Pub/Sub
```

### System Libraries
- `WiFi.h` - WiFi connectivity (ESP32)
- `Arduino_MQTT_Client.h` - MQTT client for ThingsBoard
- `Attribute_Request.h` - Client attributes management

## ⚙️ Configuration

### 1. WiFi Credentials
```cpp
constexpr char WIFI_SSID[] = "Wokwi-GUEST";      // WiFi Network
constexpr char WIFI_PASSWORD[] = "";             // Password (empty for Wokwi)
```

### 2. ThingsBoard Configuration
```cpp
constexpr char TOKEN[] = "xxxxxxxxxxxxxxxxxxxx";           // Device token (from ThingsBoard)
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud"; // ThingsBoard server
constexpr uint16_t THINGSBOARD_PORT = 1883U;               // MQTT port
constexpr const char LED_STATE_ATTR[] = "ledState";        // Client attribute name
```

### 3. Hardware Configuration
```cpp
#define BUTTON1_PIN 0    // Telemetry button - GPIO 0
#define BUTTON2_PIN 4    // Client attributes button - GPIO 4  
#define BUTTON3_PIN 5    // RPC client button - GPIO 5
```

## 🚀 Installation and Usage

### 1. Prerequisites
- [PlatformIO IDE](https://platformio.org/platformio-ide) or [PlatformIO Core](https://platformio.org/install/cli)
- Account on [ThingsBoard Cloud](https://thingsboard.cloud/) or local server
- Access to [Wokwi](https://wokwi.com/) for simulation

### 2. Project Setup
```bash
# Clone the repository
git clone <repository-url>
cd esp32-thingsboard-platformio-wokwi-telemetry
```

### 3. ThingsBoard Configuration
1. Create a new device in ThingsBoard
2. Copy the device **Access Token**
3. Replace the `TOKEN` in `main.cpp`
4. The device will automatically create the `ledState` client attribute

### 4. Wokwi Simulation
1. Open the project in Wokwi
2. The `diagram.json` contains:
   - ESP32 DevKit C V4
   - Blue button (Telemetry) on GPIO 0
   - Green button (Attributes) on GPIO 4
   - Orange button (RPC) on GPIO 5
3. Run the simulation
4. Monitor serial port for connection status and button actions

## 🔧 How It Works

### Button Functions

#### Button 1 (GPIO 0) - Telemetry Data 🌡️
- **Function**: Sends telemetry data to ThingsBoard
- **Data**: Random temperature (20-35°C) and humidity (40-80%)
- **Feedback**: Serial monitor logging
- **Use Case**: Sensor data reporting

#### Button 2 (GPIO 4) - Client Attributes 📡
- **Function**: Sends device/network attributes
- **Data**: WiFi SSID, signal strength (RSSI), IP address, device status
- **Feedback**: Serial monitor logging
- **Use Case**: Device information and diagnostics

#### Button 3 (GPIO 5) - RPC Client Request 🔄
- **Function**: Sends RPC request to server
- **Data**: Device ID, request type, timestamp, memory info, uptime
- **Feedback**: Serial monitor logging with response details
- **Use Case**: Server communication and command requests

### Hardware Components
- **3 Buttons**: Each with different colored labels and functions
- **Serial Monitor**: Detailed logging of all operations and responses

## 📊 ThingsBoard Integration

### Telemetry Data
- **temperature** (float): Random sensor temperature readings
- **humidity** (float): Random sensor humidity readings

### Client Attributes  
- **wifiSSID** (string): Connected WiFi network name
- **wifiRSSI** (int): WiFi signal strength in dBm
- **ipAddress** (string): Device IP address
- **deviceStatus** (string): Current device status

### RPC Requests
- **Method**: "getServerInfo" - Request server information
- **Parameters**: Device ID, request type, timestamp, memory info, uptime
- **Response**: Handled by callback function with LED feedback

### Device Behavior
- **Connection**: ESP32 connects to WiFi and ThingsBoard automatically
- **Multi-Function**: Three different communication types in one device
- **Serial Feedback**: Comprehensive logging for monitoring all operations
- **Subsequent Connections**: Restores last saved state
- **Button Press**: Toggles LED and saves new state
- **State Persistence**: Survives device restarts and reconnections

## 🎮 Usage

1. **Power On**: Device connects and restores last LED state
2. **Press Button**: Toggle LED between ON/OFF
3. **Check ThingsBoard**: View `ledState` client attribute updates
4. **Restart Device**: LED returns to last saved state

## 📄 License

This project is an open source educational template. Free to use and modify.


## 📞 Support

For questions or issues:
- Create an issue in the repository
- Review [ThingsBoard documentation](https://thingsboard.io/docs/devices-library/esp32-dev-kit-v1/)
- Check [Wokwi documentation](https://docs.wokwi.com/)

## 🔍 Troubleshooting

### Common Issues
- **"Failed to connect to ThingsBoard"**: Check device token and internet connection
- **"LED value not found on server"**: Normal for first-time connections
- **"Timeout: No response from ThingsBoard"**: Network or server issues

### Serial Monitor Messages
- `LED restored: ON/OFF` - State successfully recovered from ThingsBoard
- `LED value not found on server` - Using default state (first connection)
- `LED: ON/OFF` - Button pressed, new state sent to ThingsBoard

---
**Author**: Mirutec - Roger Chung  
**Version**: 1.0 - Client Attributes  
**Date**: November 2025
