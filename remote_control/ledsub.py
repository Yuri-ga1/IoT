import serial
import time
import paho.mqtt.client as paho

broker="broker.emqx.io"

port = "COM6" #COM{i} for windows

connection = serial.Serial(port, timeout=1)

def on_message(client, userdata, message):
    data = str(message.payload.decode("utf-8"))
    data = data.split()
    print(send_command(data[0], int(data[1])))

def send_command(cmd: str, response_len: int) -> str:
    connection.write(cmd.encode())
    str_resp = None
    if response_len != 0:
        # connection.in_waiting <-> available from arduino
        resp = connection.read(response_len)
        str_resp = resp.decode()
    return str_resp


client= paho.Client("client-isu-161515")
client.on_message=on_message

#print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()

#print("Subscribing")
client.subscribe("house/EGOR")
time.sleep(1800)
client.disconnect()
client.loop_stop()