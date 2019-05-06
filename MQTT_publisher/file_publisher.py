import paho.mqtt.client as mqtt
import mido
import time

def main():
	# Client(client_id=””, clean_session=True, userdata=None, protocol=MQTTv311, transport=”tcp”)
	client =mqtt.Client("kalimbot_client")
	host = "192.168.137.251"
	client.connect(host, port=1883)

	# mid = mido.MidiFile('../test.mid')
	mid = mido.MidiFile('../Ice_Cream_Truck_Song.mid')
	for i, track in enumerate(mid.tracks):
		print('Track {}: {}'.format(i, track.name))
		for msg in track:
			send_msg = (msg.bytes()[1]%11) + 60
			if send_msg == 61:
				send_msg = 60
			elif send_msg == 64:
				send_msg = 62
			elif send_msg == 65:
				send_msg = 62
			elif send_msg == 66:
				send_msg = 67
			elif send_msg == 68:
				send_msg = 70
			elif send_msg == 69:
				send_msg = 70
			client.publish("/kalimbot_midi", chr(send_msg))
			print(send_msg)
			time.sleep(msg.time/1000)


if __name__ == '__main__':
	main()
