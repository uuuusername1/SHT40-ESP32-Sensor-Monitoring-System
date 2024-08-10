from flask import Flask, request, jsonify

app = Flask(__name__)

# Store the latest sensor data
sensor_data = {"temperature": 0, "humidity": 0}

@app.route('/sensor-data', methods=['GET', 'POST'])
def handle_sensor_data():
    if request.method == 'POST':
        if request.headers.get('X-PSK') != psk:
            return 'Forbidden', 403
        
        sensor_data['temperature'] = request.form['temperature']
        sensor_data['humidity'] = request.form['humidity']
        return 'Data received', 200
    return jsonify(sensor_data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=4000)
