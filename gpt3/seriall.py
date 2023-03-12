import serial

serialName = '/dev/ttyUSB0'

with serial.Serial(serialName, 112500, timeout=10) as ser:
	ser.write(b'hello')     # write a string
	ser.write(b'\r')        # write a string

with serial.Serial(serialName, 112500, timeout=10) as ser:
	while True:
		line = ser.readline()   # read a '\n' terminated line
		#print(line)
		# Check if the line contains "not pressed" or "pressed"
		if b'released' in line:
			print('Button is not pressed')
		elif b'pressed' in line:
			print('Button is pressed')