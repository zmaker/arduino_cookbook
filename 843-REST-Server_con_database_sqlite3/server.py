from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

@app.get('/sensor/<int:sensor_id>')
def get_sensor(sensor_id):
    result = {"msg":"not found"}
    conn = sqlite3.connect('sensors.db')
    try:
        cur = conn.cursor()
        sql = f"select sid, valore, misura, data_misura from sensors where sid = {sensor_id}"
        cur.execute(sql)
        row = cur.fetchone()
        if row:
            result = {"sid":row[0], "valore":row[1], "misura":row[2], "data_misura":row[3]}
    except sqlite3.Error as error:
        print(f'Errore durante la modifica del record: {error}')
        result = {"err":"err db"}
    finally:
        conn.close()
    return result, 201

@app.post('/sensor')
def post_sensor():
    if request.is_json:
        # {"misura":"temp", "valore":"45.6"}
        data = request.get_json()
        js_val = data["valore"]
        js_mis = data["misura"]
    
        result = {"msg":"inserted"}
        conn = sqlite3.connect('sensors.db')
        try:
            cur = conn.cursor()
            newsid = "(SELECT max(sid)+1 from sensors)"
            sql = f"insert into sensors (sid, valore, misura, data_misura) values ({newsid},'{js_val}','{js_mis}', CURRENT_TIMESTAMP)"
            print(sql)
            cur.execute(sql)
            conn.commit()
            
        except sqlite3.Error as error:
            print(f'Errore durante la modifica del record: {error}')
            result = {"err":"err db"}
        finally:
            conn.close()
        return result, 201
    else:
        return {"error":"Non è json"}, 201

@app.get('/sensors')
def get_sensors():
    result = {"msg":"not found"}
    conn = sqlite3.connect('sensors.db')
    try:
        cur = conn.cursor()
        
        start_from = request.args.get('from')
        if start_from is None:
            start_from = 0
            
        page_size = request.args.get('page')
        if page_size is None:
            page_size = 5
        
        sql = f"select sid, valore, misura, data_misura from sensors LIMIT {page_size} OFFSET {start_from}"
        cur.execute(sql)
        
        rows = cur.fetchall()
        result = jsonify(rows)
    except sqlite3.Error as error:
        print(f'Errore durante la modifica del record: {error}')
        result = {"err":"err db"}
    finally:
        conn.close()
    return result, 201

@app.delete('/sensor/<int:sensor_id>')
def delete_sensor(sensor_id):
    result = {"msg":"not found"}
    conn = sqlite3.connect('sensors.db')
    try:
        cur = conn.cursor()
        sql = f"delete from sensors where sid = {sensor_id}"
        cur.execute(sql)
        conn.commit()
        
        result = {"msg":"deleted"}
        
    except sqlite3.Error as error:
        print(f'Errore durante la modifica del record: {error}')
        result = {"err":"err db"}
    finally:
        conn.close()
    return result, 201

@app.put('/sensor')
def put_sensor():
    if request.is_json:
        # {"sid":2, "misura":"temp", "valore":"45.6"}
        data = request.get_json()
        js_sid = data["sid"]
        js_val = data["valore"]
        js_mis = data["misura"]
    
        result = {"msg":"updated"}
        conn = sqlite3.connect('sensors.db')
        try:
            cur = conn.cursor()
            
            sql = f"UPDATE sensors SET valore='{js_val}', misura='{js_mis}', data_misura=CURRENT_TIMESTAMP WHERE sid = {js_sid}"
            print(sql)
            cur.execute(sql)
            conn.commit()
            
        except sqlite3.Error as error:
            print(f'Errore durante la modifica del record: {error}')
            result = {"err":"err db"}
        finally:
            conn.close()
        return result, 201
    else:
        return {"error":"Non è json"}, 201


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5150)