import paho.mqtt.client as mqtt
import mido
import time
from custom_liveparser import LiveParser
import numpy as np

def main():
	bpm = 120
	midi = LiveParser(bpm=bpm, ppq=24, bars=100, end_seq_note=127)
	midi.open_inport(midi.mqtt_publish)
	midi.open_outport()
	midi.reset_clock()
	while True:
	    status_played_notes = midi.clock()

if __name__ == '__main__':
	main()