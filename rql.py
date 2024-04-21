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
        if user_input.strip() == 'exit' or user_input.strip() == 'exit;':
            break
        if ";" in user_input:
            processes_input(user_input)
            user_input = ""


def set_credentials(username, password):
    file='credentials.txt' 
    with open(file, 'w') as filetowrite:
        filetowrite.write(username + "\n" + password + "\n")

def processes_input(user_str):
    first_char = user_str.strip()[0]
    if first_char == '{':
        first_word = user_str.strip()[1:].strip().split()[0]
        if '.' in first_word: # it is TRC if its not a variable
            call_exec(user_str, 'trc', 'The sql statement is : ')
        else:
            call_exec(user_str, 'drc', 'statement:')
    else:
        call_exec(user_str, 'alg', 'ALG> \n')
        # it is either alg or sql

def call_exec(query_input, type_of_exe, str_to_truncate_from):
    file='query.txt' 
    with open(file, 'w') as filetowrite:
        filetowrite.write(query_input + "\n")
    executable_to_call = './' + type_of_exe
    ps = subprocess.Popen([executable_to_call, 'query.txt'],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    output = ps.communicate()[0]
    start_idx = str(output).rfind(str_to_truncate_from)
    end_idx = str(output).rfind('processed.')
    result_to_print = output[(start_idx):end_idx]
    print result_to_print

if __name__ == '__main__':
    main()