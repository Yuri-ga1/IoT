import time
import numpy as np
import paho.mqtt.client as paho

def ligth(a: int, b: int):
    client.publish(topic, 1)
    print("off")
    time.sleep(5+a)
    client.publish(topic, 0)
    print("on")
    time.sleep(5-b-a)
    client.publish(topic, 1)
    print("off")
    time.sleep(5+b)

broker = "broker.emqx.io"
client = paho.Client("your_name")
client.connect(broker)
client.loop_start()
topic = "tyt/command"

timings = np.array((0, 0))
while True:
    if timings.sum() == 11:
        timings = np.array((0, 0))

    if timings.sum()%2==0:
        ligth(timings[0], timings[1])
        timings[1]+=1
    else:
        ligth(timings[0], timings[1])
        timings[0]+=1


client.disconnect()
client.loop_stop()