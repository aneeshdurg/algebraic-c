#!/usr/bin/python3
import re
from sys import argv

def output(o, string):
    o.write(string)

def escapes(string):
   string = '\"\"\"+str('.join(string.split("%{")) 
   string = ')+\"\"\"'.join(string.split("}%")) 
   return string

def process_buff(buff, o):
    for i in range(len(buff)):
        l = buff[i]
        r = re.match(r' *#define ', l)
        if r:
            buff[i] =\
                    r.string[:r.span()[1]-len("#define")-1] + \
                    "output(o, \"\"\"#define "+\
                    r.string[r.span()[1]:] + \
                    "\"\"\")\n"
            buff[i] =\
                    escapes(buff[i])
    cmd = ''.join(buff)
    exec(cmd)


def main():
    if(len(argv) == 1):
        print("No input files!")
        exit()
    filename = argv[1]
    if(filename[-2:] not in ['.c','.h']):
        print("Only .c and .h files supported!")
        exit()
    if(filename[-6:-2] != '.pyp'):
        print("Only .pyp.(c/h) files supported!")
        exit()

    f = open(filename, 'r')
    o = open(filename[:-6]+filename[-2:], 'w')
    lines = f.readlines()
    buff = []
    record = False
    for i in range(len(lines)):
        l = lines[i]
        if l == "%{\n":
            record = True
        elif l == "}%\n":
            process_buff(buff, o)
            record = False 
            buff = []
        else:
            if record:
                buff.append(l)
            else:
                o.write(l)

if __name__ == "__main__":
    main()
