import sys
import subprocess

def main():
    sys.ps1 = 'RQL'
    if hasattr(__builtins__, 'raw_input'):
      input=raw_input
    
    username = input("Please enter a valid SQLPlus username: ")
    password = input("Please enter a valid password: ")
    set_credentials(username, password)
    user_input = ""
    while True:
        user_input += " " + input("RQL> ")
        if ";" in user_input:
            # processes_input(user_input)
            call_drc(user_input)
            user_input = ""
        if user_input.strip() == 'exit':
            break


def set_credentials(username, password):
    file='credentials.txt' 
    with open(file, 'w') as filetowrite:
        filetowrite.write(username + "\n" + password + "\n")

def processes_input(user_str):
    # TODO this function will parse input and decide which function to call
    call_drc(user_str)
    call_alg(user_str)

def call_drc(query_input):
    file='query.txt' 
    with open(file, 'w') as filetowrite:
        filetowrite.write(query_input + "\n")
    ps = subprocess.Popen(['./drc', 'query.txt'],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    output = ps.communicate()[0]
    start_idx = str(output).find('ALG> \n')
    result_to_print = output[(start_idx+6):]
    print result_to_print

def call_alg(query_input):
    file='query.txt' 
    with open(file, 'w') as filetowrite:
        filetowrite.write(query_input + "\n")
    ps = subprocess.Popen(['./alg', 'query.txt'],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    output = ps.communicate()[0]
    start_idx = str(output).find('ALG> \n')
    result_to_print = output[(start_idx+6):]
    print result_to_print

if __name__ == '__main__':
    main()