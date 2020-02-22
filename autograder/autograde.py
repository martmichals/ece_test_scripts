#!/bin/python3
import os,json,sys,subprocess

print('Python autograder started!')

class_name = open('class.txt').read().strip()
repo_name = open('repo.txt').read().strip()

print('Searching for autograde scripts (class=%s, repo=%s)...'%(class_name, repo_name))

scripts = []

for (dirpath, dirnames, filenames) in os.walk('ece_test_scripts'):
	for filename in filenames:
		if filename == 'autograde.json':
			script = json.loads(open(dirpath + '/autograde.json').read())
			if script['class'] == class_name:
				script['path'] = dirpath
				scripts += [script]

if len(scripts) == 0:
	print('No scripts found for this class! Aborting.')
	sys.exit()

exit = False

while not exit:
	selection = -1
	print('********')
	print('What do you want to grade?')
	for i in range(len(scripts)):
		print('%d) %s'%(i+1, scripts[i]['name']))
	print('********')
	while selection < 0 or selection >= len(scripts):
		try:
			selection = int(input('Selection: ')) - 1
		except:
			pass
		if selection < 0 or selection >= len(scripts):
			print('Invalid Selection!')

	script = scripts[selection]
	print('Ececuting %s...'%(script['name']))

	if 'options' in script:
		print('********')
		print('This script has multiple options.')
		for i in range(len(script['options'])):
			option = script['options'][i]
			print('%d) %s - %s'%(i+1,option['display'],option['description']))
		print('********')
		selection = -1
		while selection < 0 or selection >= len(script['options']):
			try:
				selection = int(input('Selection ')) - 1
			except (ValueError, TypeError):
				pass
			if selection < 0 or selection >= len(script['options']):
				print('Invalid Selection!')
		option = script['options'][selection]['option']
		for i in range(len(script['commands'])):
			script['commands'][i] = script['commands'][i].replace('{option}',option)


	for in_file in script['files']:
		subprocess.Popen(['cp',repo_name + '/' + in_file, script['path'] + '/']).wait()
	
	os.chdir(script['path'])

	for command in script['commands']:
		subprocess.Popen(command, shell=True).wait()

	if not 'y' in input('Would you like to run another test [y/N]?').lower():
		exit = True
