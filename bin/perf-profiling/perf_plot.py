import os 
import sys 
import re
import argparse
import traceback
import glob

import matplotlib
matplotlib.use("TkAgg") 

from matplotlib import pyplot as plt
import numpy as np 

legends = ['red', 'green', 'blue', 'black', 'rose', 'orange','cyan','violet','magenta'] 
def usage():
    print('Usage: python perf_plot.py -f <file folder>') 
    print('\n') 

def main():

    file_dir = None 

    parser = argparse.ArgumentParser() 
    parser.add_argument('--files', '-f', help='folder that include profiling data files')
    args = vars(parser.parse_args())
    file_dir = args['files']
    if  file_dir is None:
        usage() 
        return 
    else: 
        if not os.path.exists(file_dir):
            print("file directory %s dosn't exist"%(file_dir)) 

    # look for README.txt for mapping pid <---> process name
    mapfile = os.path.join(file_dir, 'README.txt')
    if not os.path.exists(mapfile):
        print("No process id and name mapping file - README.txt")
        return 
    
    process_data = {}
    system_data = {}
    mem_data = {} 
    with open(mapfile, 'r') as f:
        for line in f:
            try:
                id, name = re.split(',|-|:', line)
                process_data[id.strip()] = {}
                process_data[id.strip()]['name'] = name.strip()
                mem_data[id.strip()] = {}
                mem_data[id.strip()]['name'] = name.strip()
            except:
                break
    
    # read cpu, memory usage of individual process 
    x_len = 0
    for pid in process_data.keys():
        process_data[pid]['data'] = []
        mem_data[pid]['data'] = []
        with open(os.path.join(file_dir, 'cpu-'+pid+'.txt')) as f:
            for line in f:
                process_data[pid]['data'].append(float(line.strip())) 
        with open(os.path.join(file_dir, 'mem-'+pid+'.txt')) as f:
            for line in f:
                mem_data[pid]['data'].append(float(line.strip()))
        x_len = max(x_len, len(process_data[pid]['data']))

    
    x = [i for i in range(x_len)]
    fig, (cpu_usage, sys_usage, mem_usage) = plt.subplots(1,3) 
    fig.suptitle('Processes and System CPU, Memory usage')
    count = 0
    legend_names = []
    for pid in process_data.keys():
        legend_names.append(process_data[pid]['name'])
        cpu_usage.plot(x,process_data[pid]['data'],legends[count]) 
        count += 1 
    print(legend_names)
    cpu_usage.legend(legend_names)
    cpu_usage.set_xlabel("time")
    cpu_usage.set_ylabel("Process CPU Usage") 
    cpu_usage.set_ylim([0, 70])

    count = 0
    legend_names = []
    for pid in mem_data.keys():
        legend_names.append(mem_data[pid]['name'])
        mem_usage.plot(x,mem_data[pid]['data'],legends[count]) 
        count += 1 
    print(legend_names)
    mem_usage.legend(legend_names)
    mem_usage.set_xlabel("time")
    mem_usage.set_ylabel("Process Mem Usage") 
    mem_usage.set_ylim([0, 20])
    
    # read system usage (idle, load_avg) 
    mapfile = os.path.join(file_dir, 'sys.txt')
    system_data['idle'] = [] 
    system_data['load_avg'] = [] 
    x_len = 0
    with open(mapfile, 'r') as f:
        for line in f:
            try:
                x_len += 1
                idle_u, load_avg_u = re.split(',|;|:', line)
                system_data['idle'].append(float(idle_u.strip()))
                system_data['load_avg'].append(float(load_avg_u.strip())) 
            except:
                break   

    
    x = [i for i in range(x_len)]
    sys_usage.plot(x,system_data['idle'],'-r')
    sys_usage.plot(x,system_data['load_avg'], '-g')
    sys_usage.legend(['idle','load_avg'])
    sys_usage.set_xlabel("time")
    sys_usage.set_ylabel("System CPU Usage") 
    sys_usage.set_ylim([0,100]) 

    plt.show() 

if __name__=='__main__':
    try: 
        main()
    except:
        print('Exception - %s'%(traceback.print_exc()))


