# app.py
from flask import Flask, request, jsonify

app = Flask(__name__)

countries = [
    {"id": 1, "name": "Thailand", "capital": "Bangkok", "area": 513120},
    {"id": 2, "name": "Australia", "capital": "Canberra", "area": 7617930},
    {"id": 3, "name": "Egypt", "capital": "Cairo", "area": 1010408},
]

def _find_next_id():
    return max(country["id"] for country in countries) + 1

@app.get("/countries")
def get_countries():
    return jsonify(countries)

@app.get('/country/<int:country_id>')
def get_country(country_id):
    #id richiesto
    for el in countries:
        if el["id"] == country_id:
            return {"country":el}, 201
    return  {"msg": "not found"}, 201

@app.post('/country')
def post_country():
    if request.is_json:
        data = request.get_json()  # Ottieni i dati JSON dalla richiesta
        data["area"] = int(data["area"])
        countries.append(data)

        return {"msg":"ok", "size":str(len(countries))}, 201
    return {"error": "Request must be JSON"}, 415

@app.delete('/country/<int:country_id>')
def delete_country(country_id):
    for el in countries:
        if el["id"] == country_id:
            countries.remove(el)
            return {"msg":"ok", "size":str(len(countries))}, 201
    return  {"msg": "not found"}, 201

@app.put('/country')
def put_country():
    if request.is_json:
        data = request.get_json()  # Ottieni i dati JSON dalla richiesta
        data["area"] = int(data["area"])
        
        i = 0;
        for country in countries:
            if country['id'] == data['id']:
                countries[i] = data                
                break
            i += 1
        
        return {"msg":"ok", "size":str(len(countries))}, 201
    return {"error": "Request must be JSON"}, 415

if __name__ == '__main__': 
    #app.run(host='192.168.1.7')
    app.run(host='0.0.0.0', port=5150) 
