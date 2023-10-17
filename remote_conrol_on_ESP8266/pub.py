import paho.mqtt.client as paho

broker = "broker.emqx.io"

client = paho.Client("your_name") #Your name

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
print("Publishing")

state = """Chukcha bought a refrigerator.
— What do you need this fridge for? You live in Siberia.
— To warm up during winter. Imagine the joy - it`s -40 outside and +4 in the refrigerator.""" #Your message

topic = "Now_I_decide_the_name_myself/command"
client.publish(topic, state) #Your topic
client.disconnect()
client.loop_stop()
