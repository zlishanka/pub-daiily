#!/Users/royzheng/miniconda3/bin/python

import sys 
import argparse 
import traceback 

from utils import print_info, kill_process

def usage():
    print("Usage - killproc -n <process name>")

def main(): 
    
    proc_name = None

    parser = argparse.ArgumentParser()
    parser.add_argument('--name', '-n', help='process name to kill') 
    args = vars(parser.parse_args()) 
    proc_name = args['name']
    if proc_name is None:
        usage()
        return 
    kill_process(proc_name) 

if __name__=='__main__':
    try:
        main() 
    except:
        print_info("Exception - %s"%(traceback.print_exc()))        
