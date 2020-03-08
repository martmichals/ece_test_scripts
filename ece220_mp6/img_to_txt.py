from PIL import Image
import os

img_dir = 'img_boards'
txt_dir = 'txt_boards'

def convert_img(image_to_convert, txt_name):
	image = Image.open(image_to_convert)
	image = image.convert('RGBA')
	width, height = image.size
	pixel_map = image.load()

	txt = open(txt_name, 'w')
	txt.write('{} {}\n'.format(height, width)) # Writes rows, columns into the first line of the text file, delimited with a space

	# Writes the initial board into the text file
	for y in range(height):
	    write_str=''
	    for x in range(width):
	        pixel_val = pixel_map[x, y]
	
	        if(pixel_val[0] == 0):
	            write_str = '{}1 '.format(write_str)
	        else:
	            write_str = '{}0 '.format(write_str)
	    txt.write('{}\n'.format(write_str))
	
	txt.close()

for img_file in os.listdir(img_dir):
	if not os.path.isfile(txt_dir + '/' + img_file.replace('.gif','.in')):
		print('Converting ' + img_file)
		convert_img(img_dir + '/' + img_file, txt_dir + '/' + img_file.replace('.gif', '.in'))
