import paho.mqtt.client as mqtt
import json
import sqlite3

def on_message(client, userdata, msg):
    print(f"msg: {msg.topic} {msg.payload}")
    data = json.loads( msg.payload.decode('utf-8') )
    
    device = data["device"]
    tipo = data["tipo"]
    valore = data["valore"]
    
    print(f"Device: {device}")
    print(f"Tipo: {tipo}")
    print(f"Valore: {valore}")
    
    conn = sqlite3.connect("Sensori.db")
    try:
        cursor = conn.cursor()
        sql = f"insert into misure (mid, tipo, valore, device, datamisura) values ((SELECT max(mid)+1 from misure), '{tipo}', {valore}, '{device}' ,CURRENT_TIMESTAMP)"
        print(sql)
        cursor.execute(sql)
        conn.commit()
        
    except sqlite3.Error as error:
        print(f'Errore durante la modifica del record: {error}')
    finally:
        conn.close()

def on_connect(client, userdata, flags, rc):
    print("connesso")
    client.subscribe("esp32/misure")

def main():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect("broker.hivemq.com", 1883, 60);
    
    client.loop_forever()

if __name__ == "__main__":
    main()