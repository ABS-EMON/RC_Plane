# RC_Plane

![rc](https://github.com/user-attachments/assets/62259c55-ad51-4a63-bf5f-34b6652f4a48)
# 🚀 SkyLink AI: Smart Telemetry & Risk Prediction for SU-27 RC Jet

A real-time IoT-based telemetry and AI-powered risk prediction system for a custom-built SU-27 RC fighter jet — combining **ESP32**, **GPS**, **ThingSpeak**, **Flutter**, **Web Dashboard**, and a **FastAPI-based Machine Learning model**.

---

## 📸 Overview

SkyLink AI collects live flight data such as speed, altitude, and GPS coordinates via ESP32 and NEO-6M GPS, then sends it to the cloud. A trained ML model hosted via FastAPI predicts whether the flight is currently **safe** or at **risk**, based on flight conditions. The results are visualized in both a **Flutter mobile app** and a **web dashboard**.

---
## 📹 Video Presentation

<p align="center">
  <a href="https://youtu.be/WZZK0KcxGKY?si=8z3GlVLEiOAYxiYh">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="https://img.youtube.com/vi/WZZK0KcxGKY/maxresdefault.jpg">
      <img src="https://img.youtube.com/vi/WZZK0KcxGKY/maxresdefault.jpg" alt="SkyLink AI Demo" width="100%" style="max-width: 800px; border-radius: 4px solid #555; border-radius: 12px;">
    </picture>
  </a>
</p>
## 🎯 Key Features

### 📡 Real-Time Telemetry
- Collects GPS, speed, altitude, HDOP, satellite count
- Uploads data to ThingSpeak every 5 seconds
- Flutter and Web UI fetch and display live data

### 🧠 AI Risk Prediction
- Inputs: Speed, Altitude, Location (Lat, Lon)
- Output: `Safe` or `Risk` label
- ML Model hosted using FastAPI (locally or on a server)
- Automatically predicts and displays flight risk in real time

### 🌐 Dual Platform Visualization
- 📱 **Flutter App**: Modern UI, graphs, maps, telemetry cards
- 💻 **Web Dashboard**: Real-time charts, Google Maps, risk alerts

---
<img width="701" height="1041" alt="Web ML prediction" src="https://github.com/user-attachments/assets/dfe6390d-ef2b-401f-aa15-5043a28ddb07" />

## 📦 Hardware Components

- ✅ ESP32 WiFi Microcontroller
- ✅ NEO-6M GPS Module
- ✅ 2.2k mAh LiPo Battery
- ✅ SG90 Micro Servos (Elevator, Aileron)
- ✅ Brushless Motor (1400KV) + 30A ESC
- ✅ Flysky FS-i6 Transmitter & Receiver
- ✅ SU-27 Custom RC Jet Frame

---

## 🧰 Software Stack

| Layer          | Tools/Frameworks                             |
|----------------|-----------------------------------------------|
| Firmware       | Arduino IDE, TinyGPS++                        |
| Cloud          | ThingSpeak (HTTP GET API)                    |
| ML Prediction  | Python, FastAPI, scikit-learn / XGBoost       |
| Web App        | HTML, JS, Tailwind CSS, Chart.js, Google Maps |
| Mobile App     | Flutter SDK, Android                         |

---

## 🔁 System Flow

<img width="1536" height="1024" alt="su" src="https://github.com/user-attachments/assets/90caf70b-2d03-42c2-a532-c24c759af83b" />
![flu](https://github.com/user-attachments/assets/12af9188-8840-4079-b80c-efd88bf7e33b)
<img width="914" height="910" alt="thing" src="https://github.com/user-attachments/assets/38ba5051-bd66-4243-8234-6b28ad8ada07" />
![flo](https://github.com/user-attachments/assets/c496a0b0-2776-418f-bfe1-2787ed7e6214)
<img width="461" height="368" alt="GPS" src="https://github.com/user-attachments/assets/6651835f-8bb3-4ef6-8f19-a10357b26f74" />

<img width="1920" height="6543" alt="rc_image" src="https://github.com/user-attachments/assets/b128f32c-d6df-480d-b985-126b1be05ced" />





