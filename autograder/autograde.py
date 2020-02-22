#!/bin/python3
import os,json,pexpect

class_name = open('class.txt').read()
repo_name = open('repo.txt').read()

for (dirpath, dirnames, filenames) in os.walk('ece_test_scripts'):
	for filename in filenames:
		if filename == 'autograde.json':
			
	
print(class_name)
print(repo_name)
