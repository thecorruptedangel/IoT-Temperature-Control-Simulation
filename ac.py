from flask import Flask, jsonify

app = Flask(__name__)

ac_status = "OFF"

@app.route('/start')
def start_ac():
    global ac_status
    ac_status = "ON"
    return jsonify({"status": ac_status})

@app.route('/stop')
def stop_ac():
    global ac_status
    ac_status = "OFF"
    return jsonify({"status": ac_status})

@app.route('/status')
def get_status():
    return jsonify({"status": ac_status})

if __name__ == '__main__':
    print("----- IoT Sensor & Control simulator -----")
    print("-----        AC control module       ----- \n\n")
    app.run(port=5000)