import json,sys,pexpect,random,time,subprocess

start = time.time()
print('Starting MP5 Autograder')
print('These tests take a few minutes to run')
characters = ['Vader','Padme','R2-D2','C-3PO','Jabba','Dooku','Lando','Snoke']
print('Loading solutions...')
sols = json.loads(open('sols.json').read())
len_sols = len(sols.keys())


def guess_str(guess, perfect, misplaced):
	return 'With guess %d, you got %d perfect matches and %d misplaced matches.'%(guess, perfect, misplaced)

def check_output(instance, expected_out, error_msg=''):
	try:
		instance.expect(expected_out) #, async_=True)
	except (pexpect.TIMEOUT, pexpect.EOF):
		print(error_msg)
		print('\nTEST FAILED\n')
		print('Expected output:')
		print('********')
		print(expected_out)
		print('********')
		print('Your output:')
		print('********')
		print(instance.before.decode('UTF-8'))
		print('********')
		sys.exit(0)

def create_instance(seed):
	instance = pexpect.spawn('./mp5')
	instance.timeout = 0.1
	check_output(instance, 'Please enter a seed: ')
	instance.sendline(str(seed))
	return instance

def check_malformed_inputs():
	checks = 200
	for check in range(1,checks+1):
		if check%10 == 0:
			print('Testing malformed inputs (%d/%d)...'%(check,checks))
		test_input = [random.choice(characters) for i in range(4)]
		choice = random.randint(0,2)
		if choice == 0 or choice ==2:
			i = random.randint(0,3)
			tmp = list(test_input[i])
			tmp[random.randint(0,4)]='*'
			test_input[i] = ''.join(tmp)
		if choice == 1 or choice == 2:
			test_input += ['*']
		err = '\nTesting malformed input'
		err += 'Input: "' + ' '.join(test_input) + '"'
		instance = create_instance('1')
		instance.sendline(' '.join(test_input))
		check_output(instance, 'make_guess: invalid guess', err)
		

def check_sol_generation():
	count = 0
	for seed in sols.keys():
		count += 1
		if count%10 == 0:
			print('Testing random seeds (%d/%d)...'%(count, len_sols))
		instance = create_instance(seed)
		err = '\nTesting random seed (seed=%s)\n'%(seed)
		err += 'Input: "' + ' '.join(sols[seed]) + '"\n'
		err += 'Solution: "' + ' '.join(sols[seed]) + '"'
		check_output(instance, 'Enter your guess: ')
		instance.sendline(' '.join(sols[seed]))
		check_output(instance, guess_str(1, 4, 0), err)

# implement logic directly from wiki
def calc_match(guess, test, sol):
	#print(test)
	#print(sol)
	misplaced,perfect = (0,0)
	for i in range(4):
		if test[i]==sol[i]:
			perfect += 1
			sol[i] = None
			test[i] = None
	for i in range(4):
		for j in range(4):
			if test[i] != None and sol[j] != None and test[i] == sol[j]:
				misplaced += 1
				sol[j] = None
				test[i] = None
	return guess_str(guess, perfect, misplaced), True if perfect==4 else False

def check_random_inputs():
	count = 0
	for seed in sols.keys():
		count += 1
		if count%10 == 0:
			print('Testing random inputs (%d/%d)...'%(count, len_sols))
		instance = create_instance(seed)
		guess = 1
		perfect = False
		while not perfect and guess <= 10:
			#print(guess)
			test_input = [random.choice(characters) for i in range(4)]
			err = '\nTesting random input...\n'
			err += 'Input: "' + ' '.join(test_input) + '"\n'
			err += 'Solution: "' + ' '.join(sols[seed])
			check_output(instance, 'Enter your guess: ')
			instance.sendline(' '.join(test_input))
			output, perfect = calc_match(guess, test_input, sols[seed].copy())
			check_output(instance, output, err)
			guess += 1

def check_pregenerated_outputs():
	proc = subprocess.Popen('./michalski_script/test_script.sh', shell=True, stdout=subprocess.PIPE)
	output, err = proc.communicate()
	print(output.decode('utf-8'))
	if 'CONGRATULATIONS, YOU PASSED ALL THE TEST CASES' in output.decode('utf-8'):
		return
	else:
		print('Pregenerated test cases failed!')
		print(output.decode('utf-8'))
		sys.exit(0)
	

option = 'all'
if len(sys.argv) > 1:
	option = sys.argv[1]
if option == 'all':
	print('Testing malformed inputs...')
	check_malformed_inputs()
	print('Testing solution generation...')
	check_sol_generation()
	print('Testing random inputs...')
	check_random_inputs()
	print('Testing against pregenerated output (this will take awhile)...')
	check_pregenerated_outputs()

elif option == 'malformed_input':
	print('Testing malformed inputs...')
	check_malformed_inputs()
elif option == 'solution_generation':
	print('Testing solution generation...')
	check_sol_generation()
elif option == 'random_inputs':
	print('Testing random inputs...')
	check_random_inputs()
elif option == 'pregenerated_output':
	print('Testing against pregenerated output (this will take awhile)...')
	check_pregenerated_outputs()
else:
	print('Invalid option: ' + option)
	print('Valid options are all, malformed_input,solution_generation, random_inputs, and pregenerated_output.')
	sys.exit(0)

timetaken = time.time() - start
print('Test cases passed! Took %d minutes and %d seconds'%(timetaken//60, timetaken%60))

