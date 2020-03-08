import os

search_dir = 'txt_boards'

for filename in os.listdir(search_dir):
	if filename.endswith('.in'):
		name = filename[:-3]
		if os.path.exists(search_dir + '/' + name + '.changes') and os.path.exists(search_dir + '/' + name + '.neighbors'):
			print(name)
