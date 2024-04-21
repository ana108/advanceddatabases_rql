Relational Algebra Converter
  Compilation Instructions:
  Ensure you have both BISON and flex-devel installed.
  If you have any error during the build, then they are
  most likely the result of either of the binaries missing
  from the system.

  //BISON
  To install BISON, use the following command:
    sudo yum install bison
  
  When prompted, accept the download and installation.

  //Flex-devel
  To install flex-devel, use the following command:
    sudo yum install flex-devel

  When prompted, accept the download and installation.

  //Compilation
  Please use the following command while within the alg 
  directory to allow your user account to run the build 
  file:
    sudo chmod 777 build
  
  Now, attempt to create the alg executable with the
  following command:
    ./build

Program Use:
  The program can be started with the following command 
  while within the alg directory:
    ./alg
  
  When the program begins, it will ask you for the SQLPlus
  username for your account, and then the password for that
  account. Please provide the SQLPlus credentials you usually
  use to access the ORACLE database on your system (usually
  accessed by use the sqlplus command). Please note that if
  your password has expired, an error for connecting to the
  database might be thrown. If you do not remember if you 
  ever changed your ORACLE user account password, then you
  may need to have your password reset. Please follow the
  instructions found in the Virtual Machine guide to 
  resolve this issue.

  Once you are logged in, the program will display a prompt.
  You may begin to input Relational Algebra (ALG) statements.

  If at any point you may need some help with syntax and 
  available program operations, use the following command
  on the ALG prompt:
    HELP;
  
  If at any point you would like to exit, please use the
  following command on the ALG prompt:
    EXIT;

Program Implementation details:
  The program was implemented using flex as a means of 
  creating a lexical analyser to break the statement 
  provided by the user into tokens that can then be
  interpreted by the parser created by BISON. This
  parser can then indicate which operations should be
  completed by the program to create the SQL statement
  for the query based on which grammar rule for statements
  was followed by the user in their input.

  Additional information can be found in the documentation
  in the source files.

End of README.txt