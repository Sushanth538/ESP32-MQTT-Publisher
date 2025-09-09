ESP32 MQTT Publisher using WIFI.

This repository contains a beginner-friendly ESP32-C3 project demonstrating how to connect the device to a Wi-Fi network and publish messages using MQTT. The project is intended for learning and experimentation with IoT concepts.

How to use this example

We encourage users to use this project as a template for creating their own ESP32-C3 MQTT projects.
A recommended way is to follow the ESP-IDF docs
 for building and flashing ESP32 projects.

Project Folder Contents

The project ESP32C3-MQTT-Hello contains the following files and folders:

├── CMakeLists.txt             # Main CMake file for project build
├── main
│   ├── CMakeLists.txt         # CMake for main folder
│   └── app_main.c             # Main application code (Wi-Fi + MQTT)
├── README.md                  # This file
└── .vscode/                   # VS Code settings for the project (optional)

Features :

Connects ESP32-C3 to a Wi-Fi network.

Connects to a public MQTT broker (HiveMQ used here).

Publishes "hi" message to a specific MQTT topic.

Can be subscribed to via MQTT client apps (e.g., MQTT Terminal) to receive messages.

Fully explained code for learning purposes.

Prerequisites :

ESP32-C3 board

ESP-IDF v5.x installed

Wi-Fi network credentials

Optional: MQTT client app to subscribe to messages

Usage Instructions :

Clone or download this repository.

Open the project in VS Code.

Update your Wi-Fi SSID and password in main/app_main.c.

Set the MQTT broker and topic if needed (broker.hivemq.com and esp32/test/sushanth).

Build and flash the project:

idf.py build
idf.py flash
idf.py monitor


Subscribe to the topic in an MQTT client to see the "hi" message.

Learning Outcomes

Understanding Wi-Fi initialization on ESP32-C3.

Learning MQTT client setup and message publishing.

Understanding event-driven programming with FreeRTOS and ESP-IDF.

Understanding folder structure and CMake build system for ESP-IDF projects.
