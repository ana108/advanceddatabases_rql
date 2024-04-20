import sys

def main():
    sys.ps1 = 'RQL'
    if hasattr(__builtins__, 'raw_input'):
      input=raw_input
    
    username = input("Please enter a valid SQLPlus username: ")
    password = input("Please enter a valid password: ")
    user_input = ""
    while True:
        user_input += input("RQL> ")
        if ";" in user_input:
            processes_input(user_input)
            user_input = ""
        if user_input == 'exit':
            break


def processes_input(user_str):
    print user_str

if __name__ == '__main__':
    main()