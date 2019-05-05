import paho.mqtt.client as mqtt
import mido
import time

def main():
	# Client(client_id=””, clean_session=True, userdata=None, protocol=MQTTv311, transport=”tcp”)
	client =mqtt.Client("kalimbot_client")
	host = "192.168.137.251"
	client.connect(host, port=1883)


	mid = mido.MidiFile('../MIDI-LiveParser/test.mid')
	for i, track in enumerate(mid.tracks):
	    print('Track {}: {}'.format(i, track.name))
	    for msg in track:
        	client.publish("/kalimbot_midi", msg.bytes()[1])
        	print(msg.bytes()[1])
	        time.sleep(msg.time/1000)



	# client.publish("/kalimbot_midi", 5)





if __name__ == '__main__':
	main()