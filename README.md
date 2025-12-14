# ESP32 ThingsBoard Multi-Button Demo

This project demonstrates multiple **ThingsBoard** functionalities with ESP32 using **3 different buttons** for various data transmission types. Each button triggers a different type of communication with ThingsBoard IoT platform, simulated in **Wokwi**.

## 🎯 Features

- **3-Button Interface**: Different buttons for different functionalities
- **Telemetry Data**: Send random temperature readings (20.0-35.0°C)
- **Client Attributes**: Send battery level information (10-100%)
- **RPC Client Requests**: Make client-side RPC calls with response handling
- **Serial Feedback**: Detailed logging of all operations
- **Wokwi Simulation**: Complete hardware simulation with 3 buttons

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
- `ThingsBoard.h` - Main ThingsBoard client library
- `ArduinoJson.h` - JSON parsing and serialization
- `Client_Side_RPC.h` - Client-side RPC functionality
- `RPC_Request_Callback.h` - RPC callback management

## ⚙️ Configuration

### 1. WiFi Credentials
```cpp
constexpr char WIFI_SSID[] = "Wokwi-GUEST";      // WiFi Network
constexpr char WIFI_PASSWORD[] = "";             // Password (empty for Wokwi)
```

### 2. ThingsBoard Configuration
```cpp
constexpr char TOKEN[] = "xxxxxxxxxxxxxxxxxx";           // Device token (from ThingsBoard)
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud"; // ThingsBoard server
constexpr uint16_t THINGSBOARD_PORT = 1883U;               // MQTT port
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
4. The device will automatically create telemetry and attribute data when buttons are pressed

### 4. Wokwi Simulation
1. Open the project in Wokwi
2. The `diagram.json` contains:
   - ESP32 DevKit C V4
   - Button 1 (Telemetry) on GPIO 0
   - Button 2 (Attributes) on GPIO 4
   - Button 3 (RPC) on GPIO 5
3. Run the simulation
4. Monitor serial port for connection status and button actions

## 🔧 How It Works

### Button Functions

#### Button 1 (GPIO 0) - Telemetry Data 🌡️
- **Function**: Sends telemetry data to ThingsBoard
- **Data**: Random temperature readings between 20.0°C and 35.0°C
- **Feedback**: Serial monitor logging with temperature value
- **Use Case**: Sensor data reporting

#### Button 2 (GPIO 4) - Client Attributes 🔋
- **Function**: Sends client attributes to ThingsBoard
- **Data**: Random battery level between 10% and 100%
- **Feedback**: Serial monitor logging with battery percentage
- **Use Case**: Device status information

#### Button 3 (GPIO 5) - RPC Client Request 🔄
- **Function**: Makes client-side RPC call to server
- **Method**: `getCurrentTime` - Request current time from server
- **Timeout**: 10 seconds with timeout callback
- **Feedback**: Serial monitor logging with server response or timeout message
- **Use Case**: Client-side RPC communication and server interaction

### Hardware Components
- **3 Push Buttons**: GPIO 0, 4, and 5 with INPUT_PULLUP configuration
- **Serial Monitor**: Detailed logging of all operations and responses
- **ESP32 DevKit**: Main microcontroller with WiFi connectivity

## 📊 ThingsBoard Integration

### Telemetry Data
- **temperature** (float): Random temperature readings between 20.0°C and 35.0°C

### Client Attributes  
- **batteryLevel** (int): Random battery level percentage between 10% and 100%

### RPC Client Requests
- **Method**: "getCurrentTime" - Request current server time
- **Timeout**: 10 seconds with callback handling
- **Response**: JSON response with server data or timeout notification

### Device Behavior
- **Connection**: ESP32 connects to WiFi and ThingsBoard automatically
- **Multi-Function**: Three different communication types in one device
- **Serial Feedback**: Comprehensive logging for monitoring all operations
- **Button Handling**: Debounced button press detection with falling edge triggers
- **Random Data**: Generates random sensor values for demonstration
- **RPC Handling**: Client-side RPC with response callbacks and timeout management

## 🎮 Usage

1. **Power On**: Device connects to WiFi and ThingsBoard automatically
2. **Button 1**: Press to send random temperature telemetry data
3. **Button 2**: Press to send random battery level as client attribute
4. **Button 3**: Press to make RPC call requesting current server time
5. **Monitor**: View all operations and responses in serial monitor
6. **ThingsBoard**: Check telemetry, attributes, and RPC activity in ThingsBoard dashboard

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
- **"Not connected to ThingsBoard"**: Device attempting to reconnect
- **"RPC timeout"**: No response received from server within 10 seconds
- **"Failed to send RPC call"**: RPC client communication error

### Serial Monitor Messages
- `Sending telemetry - Temperature: XX.X°C` - Temperature data sent
- `Sending client attributes - Battery Level: XX%` - Battery level sent
- `Making client-side RPC call: getCurrentTime` - RPC request initiated
- `SERVER RESPONSE RECEIVED` - RPC response received successfully
- `RPC timeout - no response from server` - RPC call timed out

---
**Author**: Mirutec - Roger Chung  
**Version**: 2.0 - Multi-Button Demo with RPC  
**Date**: December 2025
