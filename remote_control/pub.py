import time
import paho.mqtt.client as paho

broker = "broker.emqx.io"

client = paho.Client("client-isu-1611515")

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
print("Publishing")

for i in range(100000):
    if i%2==1:
        state ="d 7"
    else:
        state = 'u 6'
    print(f"{state}")
    client.publish("house/EGOR", state)
    time.sleep(3)
    
client.disconnect()
client.loop_stop()
