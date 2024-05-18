#!/Users/royzheng/miniconda3/bin/python 

from genericpath import isfile
import os 
import sys
import argparse
import traceback 
import uuid
import cv2  



def usage():
    print('Usage: resize_img.py -i <original image folder> -o <destination image folder> -w <output image width> -n <output name prefix> ')  

def main():

    input_dir = None 
    output_dir = None 
    output_width = None 
    output_name_prefix = None  

    parser = argparse.ArgumentParser() 
     
    parser.add_argument('--input_dir', '-i', help='input image folder')    
    parser.add_argument('--output_dir', '-o', help='output image folder') 
    parser.add_argument('--output_width', '-w', help='output image width, default: 720')
    parser.add_argument('--output_name_prefix', '-n', help='output image prefix,  default: same as input')

    args = vars(parser.parse_args()) 

    if args['input_dir'] is not None: 
        input_dir = args['input_dir'] 
    if args['output_dir'] is not None: 
        output_dir = args['output_dir'] 
    if args['output_width'] is not None:
        output_width = int(args['output_width'])
    else:
        output_width = 720 
    if args['output_name_prefix'] is not None:
        output_name_prefix = args['output_name_prefix']

    if input_dir is None or output_dir is None:
        usage() 
        return 


    # traverse image files from input directory 
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for filename in os.listdir(input_dir):
        f = os.path.join(input_dir, filename)
        print("input image -f %s"%(f))
        if os.path.isfile(f):
            img = cv2.imread(f, cv2.IMREAD_UNCHANGED)
            if img is None:
                continue # non image
            output_height = int(float(output_width)/img.shape[1] * img.shape[0])
            # resize image
            resized = cv2.resize(img, (output_width, output_height), interpolation = cv2.INTER_AREA)
            output_filename = filename 
            if output_name_prefix is not None:
                output_filename = os.path.join(output_dir, output_name_prefix + '-' + str(uuid.uuid4()) + '.jpg')
            else:
                output_filename = os.path.join(output_dir, filename)

            cv2.imwrite(output_filename, resized)

if __name__ == '__main__':
    try:
        main()
    except: 
        print('Got exception - %s'%(traceback.print_exc()))  

