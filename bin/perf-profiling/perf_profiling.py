# performance profiling util
# input - process names or process ids, use ',' to separate 
# output - a bunch of files to to record the profiling snapshot at each sampling interval

import os 
import sys 
import time
import argparse
import traceback
import subprocess
from datetime import datetime 

import psutil

profiling_duration = 3600
sampling_interval = 10

def print_info(msg):
    print(str(datetime.now()) + ' [Info] ' + msg)
    sys.stdout.flush() 

def usage():
    print('usage: python perf_profiling.py --name run_name --pids 99818,74321 --sample_interval 10 --duration 1200')
    print('or     python perf_profiling.py -n vidgear -p 99818,74321 -s 10 -d 1200')
    print('\n')

def exec_command(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, \
                       stderr=subprocess.PIPE, shell=True)
    text = p.stdout.read()
    retcode = p.wait() 
    return retcode, text.decode("utf-8") 

# get CPU/MEM percentage of running process
def get_pid_usage(proc_id):
    #psutil.Process() cannot access some process's data
    #p = psutil.Process(int(proc_id))
    num_core = psutil.cpu_count(logical=False)
    cmd = "ps -p "  + proc_id + " -o %cpu,%mem"
    ret, out = exec_command(cmd)
    msg = out.splitlines()
    
    cpu_u = 0.0 
    mem_u = 0.0
    if ret != 0:
        print("Failed to profile the existing process pid= %s "%(proc_id))
        return None, 0.0, 0.0

    elif ret == 0 and len(msg) == 2:
        m_list = msg[1].split(' ')
        while '' in m_list:
            m_list.remove('')
        #cpu_u = float(m_list[0])/psutil.cpu_count()
        cpu_u = float(m_list[0])/num_core
        mem_u = float(m_list[1])
    

    return proc_id, '{:4.2f}'.format(cpu_u), '{:4.2f}'.format(mem_u)

def get_system_usage():
    p = psutil.cpu_times_percent(percpu=False)
    ret, out = exec_command('uptime')
    print_info('uptime out - %s'%(out))
    load_avg = float(out.split(' ')[-3])
    return p.idle, load_avg

def main():

    name_run = None
    pids = None 
    sample_interval = None 
    duration = None

    parser = argparse.ArgumentParser()
    parser.add_argument('--name', '-n', help='name of the run, a name folder will be created')
    parser.add_argument('--pids', '-p', help='profiling pids, separate by comma')
    parser.add_argument('--sample_interval', '-s', help='sampling interval(sec), default=10')
    parser.add_argument('--duration', '-d', help='profiling duration(sec), default=1200')

    args = vars(parser.parse_args())

    if args['name'] is not None: 
        name_run = args['name'] + '-' + str(datetime.now().strftime("%y-%m-%d-%H:%M:%S"))
    else: 
        name_run = 'run-' + str(datetime.now().strftime("%y-%m-%d-%H:%M:%S"))
    
    if not os.path.exists(name_run):
        os.makedirs(name_run) 

    print_info("name of run - %s"%(name_run)) 

    if args['pids'] is not None:
        pids = args['pids']
    if args['sample_interval'] is not None:
        sample_interval = int(args['sample_interval'])
    else:
        sample_interval = sampling_interval 
    if args['duration'] is not None:
        duration = int(args['duration']) 
    else:
        duration = profiling_duration 
    
    if pids is None: 
        usage()
        return
    
    f_map = {} 
    for pid in pids.split(','):
        fname = 'cpu-'+pid
        f_map[fname] = open(os.path.join(name_run, fname+'.txt'), 'w')
        fname = 'mem-'+pid 
        f_map[fname] = open(os.path.join(name_run, fname+'.txt'), 'w') 
    f_map['sys'] = open(os.path.join(name_run, 'sys.txt'), 'w')

    count = 0
    loop_count = duration/sample_interval
    print_info('Total collected sampling points: %s'%(loop_count))
    while count < loop_count:
        for pid in pids.split(','):
            rpid, cpu_u, mem_u = get_pid_usage(pid) 
            if rpid is not None: 
                print_info('pid=%s, cpu=%s, mem=%s'%(rpid, cpu_u, mem_u))
                f_map['cpu-'+rpid].write('%s\n'%(cpu_u))
                f_map['mem-'+rpid].write('%s\n'%(mem_u))
            else: 
                print_info('pid=%s is not running, cpu=%s, mem=%s'%(pid, cpu_u, mem_u))
                f_map['cpu-'+pid].write('%s\n'%(cpu_u))
                f_map['mem-'+pid].write('%s\n'%(mem_u))
            
        idle_percentage, load_avg = get_system_usage()
        print_info('System idle=%s, load avg=%s'%(idle_percentage, load_avg))
        f_map['sys'].write('%s, %s\n'%(idle_percentage,load_avg))
        count += 1
        time.sleep(sample_interval) 

    for k in f_map.keys(): 
        f_map[k].close() 

if __name__ == '__main__':
    try: 
        main() 
    except:
        print("Exception - %s"%(traceback.print_exc()))
