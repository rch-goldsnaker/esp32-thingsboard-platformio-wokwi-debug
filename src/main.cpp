#include <WiFi.h>
#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>
#include <ArduinoJson.h>
#include <Client_Side_RPC.h>
#include <RPC_Request_Callback.h>

// WiFi Configuration
constexpr char WIFI_SSID[] = "Wokwi-GUEST";
constexpr char WIFI_PASSWORD[] = "";

// ThingsBoard Configuration
constexpr char TOKEN[] = "j9jWuXgh0KLHFq4mYbrN";
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud";
constexpr uint16_t THINGSBOARD_PORT = 1883U;

// Hardware Pins
#define BUTTON1_PIN 0  // Telemetry button
#define BUTTON2_PIN 4  // Client attributes button
#define BUTTON3_PIN 5  // RPC client button

// Global Objects
WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
Client_Side_RPC<5U> client_rpc;

const std::array<IAPI_Implementation *, 1U> apis = {
    &client_rpc
};

ThingsBoard tb(mqttClient, 1024U, Default_Max_Stack_Size, apis);

// RPC Callback Functions
void rpcResponseCallback(const JsonDocument &data) {
  Serial.println("=== CLIENT-SIDE RPC RESPONSE RECEIVED ===");
  
  Serial.print("Server response: ");
  String output;
  serializeJson(data, output);
  Serial.println(output);
  
  Serial.println("=========================================");
}

void rpcTimeoutCallback() {
  Serial.println("RPC timeout - no response from server");
}

void InitWiFi() 
{
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

const bool reconnect() 
{
  const wl_status_t status = WiFi.status();
  
  if (status == WL_CONNECTED) {
    return true;
  }
  
  InitWiFi();
  return true;
}

// Send telemetry data (random temperature)
void sendTelemetryData()
{
  if (tb.connected()) {
    float temperature = random(200, 350) / 10.0; // Random temp between 20.0 and 35.0°C
    
    Serial.print("Sending telemetry - Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
    
    tb.sendTelemetryData("temperature", temperature);
  } else {
    Serial.println("Not connected to ThingsBoard - Cannot send telemetry");
  }
}

// Send client attributes (Battery Level)
void sendClientAttributes()
{
  if (tb.connected()) {
    int batteryLevel = random(10, 101); // Random battery level between 10% and 100%
    
    Serial.print("Sending client attributes - Battery Level: ");
    Serial.print(batteryLevel);
    Serial.println("%");
    
    tb.sendAttributeData("batteryLevel", batteryLevel);
  } else {
    Serial.println("Not connected to ThingsBoard - Cannot send attributes");
  }
}

// Send RPC client request
void sendRpcClientRequest()
{
  if (!tb.connected()) {
    Serial.println("Not connected to ThingsBoard - Cannot send RPC request");
    return;
  }
  
  Serial.println("Making client-side RPC call: getCurrentTime");
  
  // Create RPC callback with 10 seconds timeout
  RPC_Request_Callback callback("getCurrentTime", rpcResponseCallback, nullptr, 10000U * 1000U, rpcTimeoutCallback);
  
  // Make the RPC call
  if (client_rpc.RPC_Request(callback)) {
    Serial.println("RPC call sent successfully - waiting for response...");
  } else {
    Serial.println("Failed to send RPC call");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON1_PIN, INPUT_PULLUP); // Telemetry button
  pinMode(BUTTON2_PIN, INPUT_PULLUP); // Attributes button
  pinMode(BUTTON3_PIN, INPUT_PULLUP); // RPC button
  
  // Initialize random seed
  randomSeed(analogRead(0));
  
  Serial.println("\n=== ESP32 ThingsBoard Multi-Button Demo ===");
  Serial.println("Button 1 (GPIO 0): Send Telemetry Data");
  Serial.println("Button 2 (GPIO 4): Send Client Attributes");
  Serial.println("Button 3 (GPIO 5): Send RPC Client Request");
  Serial.println("==========================================\n");
  
  InitWiFi();
}

void loop()
{
  // Check WiFi connection
  if (!reconnect())
  {
    delay(1000);
    return;
  }

  // Connect to ThingsBoard if not connected
  if (!tb.connected())
  {
    Serial.print("Connecting to ThingsBoard: ");
    Serial.println(THINGSBOARD_SERVER);
    
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT))
    {
      Serial.println("Failed to connect to ThingsBoard!");
      delay(5000);
      return;
    }
    
    Serial.println("Connected to ThingsBoard successfully!");
  }
  
  // Process ThingsBoard messages
  tb.loop();

  // Handle button inputs
  static bool lastButton1State = HIGH;
  static bool lastButton2State = HIGH;
  static bool lastButton3State = HIGH;
  
  bool currentButton1State = digitalRead(BUTTON1_PIN);
  bool currentButton2State = digitalRead(BUTTON2_PIN);
  bool currentButton3State = digitalRead(BUTTON3_PIN);
  
  // Button 1 - Telemetry Data
  if (lastButton1State == HIGH && currentButton1State == LOW) {
    Serial.println("\n--- Button 1 Pressed: Sending Telemetry ---");
    sendTelemetryData();
  }
  
  // Button 2 - Client Attributes
  if (lastButton2State == HIGH && currentButton2State == LOW) {
    Serial.println("\n--- Button 2 Pressed: Sending Client Attributes ---");
    sendClientAttributes();
  }
  
  // Button 3 - RPC Client Request
  if (lastButton3State == HIGH && currentButton3State == LOW) {
    Serial.println("\n--- Button 3 Pressed: Sending RPC Client Request ---");
    sendRpcClientRequest();
  }
  
  lastButton1State = currentButton1State;
  lastButton2State = currentButton2State;
  lastButton3State = currentButton3State;
  
  delay(50);
}
