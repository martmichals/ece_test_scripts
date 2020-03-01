import string, sys
from os import listdir
from os.path import isfile, join
from subprocess import Popen, PIPE

mypath = 'testing_images/' 
onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]

fullpath = []
for i,f in enumerate(onlyfiles):
    f = "{}{}".format(mypath, f)
    fullpath.append(f)

seed_number = 0
case_num = 1
for g,filename in enumerate(fullpath):
    tester_file = open(filename)
    seed_passed = True

    cur_line = True
    while cur_line:
        input_list = ['./c_runner', onlyfiles[g]]
        seed_number = int(onlyfiles[g])
        guess_sequence = []

        while cur_line:
            cur_line = tester_file.readline().rstrip()

            if(cur_line == '--'):
                cur_line = tester_file.readline()
                break
            else:
                input_list.append(cur_line)
                guess_sequence.append(cur_line)

        proper_output = ''
        while cur_line:
            if(cur_line[0] == '*'):
                break

            proper_output = '{}{}'.format(proper_output, cur_line)
            cur_line = tester_file.readline()

        if len(proper_output) < 1:
            break

        process = Popen(input_list, stdout=PIPE)
        (output, err) = process.communicate()
        ex_code = process.wait()

        if not (output == proper_output):
            seed_passed = False
            parsed_output = output.split('\n')
            parsed_proper = proper_output.split('\n')
            for linenum,text in enumerate(parsed_output):
                if text != parsed_proper[linenum]:
                    print('***************************************************')

                    if len(parsed_proper[linenum]) > 6:
                        print('Here is the expected output: ')
                        print('{}'.format(parsed_proper[linenum]))
                        print('Your output: ') 
                        print('{}'.format(text))
                    else:
                        if len(parsed_proper[linenum - 1]) > 4: 
                            print('Here is the proper return value: ')
                            print('{}'.format(parsed_proper[linenum]))
                            print('Your return value: ') 
                            print('{}'.format(text))
                        else:
                            print('Here is the proper max_score value: ')
                            print('{}'.format(parsed_proper[linenum]))
                            print('Your max_score value: ') 
                            print('{}'.format(text))
                            

                    print('\n')
                    print('Conditions that caused this failure:')
                    print('Seed Number: {}'.format(seed_number))
                    print('Guess Sequence: {}'.format(guess_sequence))
                    print('***************************************************')

            print('\n\n')
            print('HALTING TESTS')
            print('Program passed {} test cases'.format(case_num))
            sys.exit()

            
    if seed_passed:
        print('Seed number {}, passed'.format(seed_number))
        case_num+=1

    tester_file.close()

print('\n\n')
print('CONGRATULATIONS, YOU PASSED ALL THE TEST CASES')

