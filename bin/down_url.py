#!/Users/royzheng/.pyenv/shims/python

import sys 
import argparse
import urllib.request
import traceback 

def usage():
    print("Usage: down_url.py -u <url> -f <filename> -c <start count> -e <extension>") 


def plus_one(num):
    nums = list(num)
    for i in reversed(range(len(nums))):
        a = int(nums[i])
        if a < 9: 
            nums[i] = str(a+1)     
            break 
        else:
            nums[i] = '0'
    if (i == 0): 
        nums.insert(0, '1')
    return ''.join(nums)      

def main():
    #urllib.request.urlretrieve("http://www.example.com/songs/mp3.mp3", "mp3.mp3") 

    download_url = None 
    filename = None 
    start_count = None
    extension = None 

    parser = argparse.ArgumentParser()
    parser = argparse.ArgumentParser()
    parser.add_argument('--url', '-u', help='file url')
    parser.add_argument('--filename', '-f', help='filename prefix')
    parser.add_argument('--counter', '-c', help='start counter, i.e. 000001')
    parser.add_argument('--extension', '-e', help='file extension, i.e. jpg')
    args = vars(parser.parse_args())

    if args['url'] is not None:
        download_url  = args['url']
    if args['filename'] is not None: 
        filename = args['filename'] 
    if args['counter'] is not None:
        start_count = args['counter'] 
    if args['extension'] is not None:
        extension = args['extension'] 

    if download_url is None or filename is None: 
        usage() 
        sys.exit(-1) 

    print('download_url', download_url) 
    print('filename', filename) 

    count = start_count
    remote_file = None  
    while True: 
        try:
            local_file = filename 
            if count is not None:  
               local_file = local_file + count 
            if extension is not None: 
               local_file = local_file + '.' + extension
            remote_file = download_url+'/'+ local_file  
            print("Downloading ", remote_file) 
            urllib.request.urlretrieve(remote_file, local_file)
            count = plus_one(count)  
        except:
            #traceback.print_exc()  
            print("Cannot file %s, bye"%(remote_file)) 
            break 
    
    print("bye") 
 
if __name__ == '__main__': 
    main() 
