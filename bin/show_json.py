#!/Users/royzheng/miniconda3/bin/python

import argparse
import json
import traceback

def main():
    
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--file_name', required=True, type=str, help='json file name')

    args = parser.parse_args()
    file_name = args.file_name
    try:
        fp = open(file_name)
        a = json.load(fp)
        print(a) 
    except:
        print(f"Exception - {traceback.print_exc()}")

if __name__=='__main__':
    main()
