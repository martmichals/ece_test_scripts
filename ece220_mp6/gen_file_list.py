import os

for filename in os.listdir('txt_boards'):
	if filename.endswith('.in'):
		print(filename[:-3])
