# SHT40 & ESP32 Tempteraure and humidity to python server

## Overview

Very easy, beginner friendly project. 
This project demonstrates how to set up a real-time sensor monitoring system using an ESP32 microcontroller and the SHT40 temperature and humidity sensor. The system sends sensor data to a Python backend running on a server. The server then serves this data through an Nginx web server with basic authentication using a Pre-Shared Key (PSK). The data is displayed in real-time on a web page.

## Components

- **ESP32**: Microcontroller used to read data from the SHT40 sensor and send it to the server.
- **SHT40**: Sensor that measures temperature and humidity.
- **Python Backend**: Handles data reception and provides an endpoint for data retrieval.
- **Nginx**: Web server that serves the HTML page and provides basic authentication with a PSK.

## Hardware Connections

Connect the SHT40 sensor to the ESP32 as follows:

| SHT40 Pin | ESP32 Pin                |
|-----------|---------------------------|
| VCC       | 3.3V                      |
| GND       | GND                       |
| SDA       | GPIO 21 (or any available SDA pin) |
| SCL       | GPIO 22 (or any available SCL pin) |


nginx conf
```

server {
    listen 80;
    server_name example.com;  # Replace with your FQDN

    # Serve the HTML file
    location / {
        root /var/www/html;
        index index.html;
    }

    # Handle sensor data submissions
    location /sensor-data {
        proxy_pass http://localhost:4000;  # Forward to the Python script
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection 'upgrade';
        proxy_set_header Host $host;
        proxy_cache_bypass $http_upgrade;
    }
}
```

To open your server to internet use this guide by network chuck:
https://www.youtube.com/watch?v=ey4u7OUAF3c
