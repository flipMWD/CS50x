from sys import argv, exit      # command line interaction requires sys lib

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)                     # system signal, read by $?

for i in range(len(argv)):
    print(argv[i])              # python interpreter is ignored

for arg in argv:
    print(arg)
