from flask import Flask, jsonify
import random

app = Flask(__name__)

stored_codes = [] 

def generate_code():
    return str(random.randint(100000, 999999)) 

@app.route('/get-code', methods=['GET'])
def get_code():
    new_code = generate_code()
    stored_codes.append(new_code)
    return jsonify({"code": new_code})

@app.route('/codes', methods=['GET'])
def get_all_codes():
    return jsonify({"codes": stored_codes}) 

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
