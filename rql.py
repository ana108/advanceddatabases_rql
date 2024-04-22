import sys
import subprocess
import re

list_of_sql_only_words = ['delete', 'drop', 'truncate', 'update', 'alter', 'create', 'insert']

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
            processes_input(user_input, username, password)
            user_input = ""


def set_credentials(username, password):
    file='credentials.txt' 
    with open(file, 'w') as filetowrite:
        filetowrite.write(username + "\n" + password + "\n")

def is_sql_terms(text_to_check):
    for keyword in list_of_sql_only_words:
        if keyword in text_to_check:
            return True
    return False

def processes_input(user_str, username, password):
    if len(user_str.strip()) == 0:
        print("Synax Error")
        return
    first_char = user_str.strip()[0]
    first_word = user_str.strip().split()[0]
    if first_char == '{':
        first_word = user_str.strip()[1:].strip().split()[0]
        if '.' in first_word: # it is TRC if its not a variable
            call_exec(user_str, 'trc', 'The sql statement is : ')
        else:
            call_exec(user_str, 'drc', 'statement:')
    else:
        if 'select' in first_word.lower() and 'from ' in user_str.lower():
            call_sqlplus(username, password, user_str)
        elif is_sql_terms(user_str.lower()):
            call_sqlplus(username, password, user_str)
        else:
            call_exec(user_str, 'alg', 'ALG> \n')

def call_sqlplus(username, password, query_input):
    file='query.txt' 
    with open(file, 'w') as filetowrite:
        filetowrite.write(query_input + "\nexit;")
    ps = subprocess.Popen(['sqlplus', '-L', '-S', username + '/' + password + "@xe", "@query.txt"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    output = ps.communicate()[0]
    if len(output.strip()) == 0:
        print("Syntax error. Try again")
        return

    print output

def call_exec(query_input, type_of_exe, str_to_truncate_from):
    print("Executing", type_of_exe)
    file='query.txt' 
    with open(file, 'w') as filetowrite:
        filetowrite.write(query_input + "\n")
    executable_to_call = './' + type_of_exe
    ps = subprocess.Popen([executable_to_call, 'query.txt'],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    output = ps.communicate()[0]
    start_idx = str(output).rfind(str_to_truncate_from)
    end_idx = str(output).rfind('processed.')
    result_to_print = output[(start_idx):end_idx]
    if len(result_to_print.strip()) == 0:
        print("Syntax error. Try again")
        return

    print result_to_print

if __name__ == '__main__':
    main()