import time
import paho.mqtt.client as paho

broker="broker.emqx.io"

def on_message(client, userdata, message):
    time.sleep(1)
    data = str(message.payload.decode("utf-8"))
    print('Message is:',data)

client= paho.Client("your_name1") #your name, it must not match the name in pub.py
client.on_message=on_message

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()

print("Subscribing")
client.subscribe("Now_I_decide_the_name_myself/state")
print("Succses")
time.sleep(1800)
client.disconnect()
client.loop_stop()