#!/Users/royzheng/miniconda3/bin/python
import numpy as np
import matplotlib.pyplot as plt
import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-i', '--image_file', type=str)

args = parser.parse_args()

if args.image_file is None:
    print("show_img.py -i <image_file>")
    sys.exit(0)

image = plt.imread(args.image_file)

plt.figure(figsize=(10,10))
plt.imshow(image)
plt.axis('on')
plt.show()

