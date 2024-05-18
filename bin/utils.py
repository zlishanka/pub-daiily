import subprocess
import random
import time
import sys
import psutil
import json
from threading import Timer
from datetime import datetime 

def print_info(msg):
    print(str(datetime.now()) + ' [Info] ' + msg)
    sys.stdout.flush()

def print_warning(msg):
    print(str(datetime.now()) + ' [Warning] ' + msg)
    sys.stdout.flush()

def print_error(msg):
    print(str(datetime.now()) + ' [Error] ' + msg)
    sys.stdout.flush()

def exec_command_timeout(cmd, timeout=3):
    kill = lambda process: process.kill()
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, \
                   stderr=subprocess.PIPE, shell=True)
    my_timer = Timer(timeout, kill, [p])

    try:
        my_timer.start()
        text = p.stdout.read()
        retcode = p.wait()
        return retcode, text.decode("utf-8")

    except subprocess.TimeoutExpired:
        return 1, "timeout"

def exec_command(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, \
                       stderr=subprocess.PIPE, shell=True)
    text = p.stdout.read()
    retcode = p.wait()
    return retcode, text.decode("utf-8")

def get_proc_id(proc_name):
    success = False
    proc_id = None 

    cmd = 'ps aux | grep -v "grep" | grep -v "killproc" | grep  ' + proc_name 
    #print(cmd)
    ret, out = exec_command_timeout(cmd, 5)
    msg = out.splitlines()
    if len(msg) == 0:
        print_info('process %s is not running'%(proc_name))
        success = True
    elif ret == 0 and len(msg) == 1 and proc_name in msg[0]:
        m_list = msg[0].split(' ')
        while '' in m_list: 
            m_list.remove('')
        proc_id = m_list[1] 
        print_info('process %s is running with PID=%s'%(proc_name, proc_id))
        success = True
    else:
        print_error('process %s is running in multiples, errors out ...'%(proc_name))
    
    return success, proc_id
    

def verify_response(code, msg_out):
    msgs = msg_out.splitlines()
    for l in msgs:
        if "HTTP/1.1" in l:
            if int(l.split(' ')[1]) == code:
                return True
    return False

def get_resp_body(msg_out):
    msgs = msg_out.splitlines()
    return msgs[-1]
    

def send_request(url, host='http://127.0.0.1:5001', req_mode='GET', body='{}'):
    cmd = "curl -i -X " + " '" + req_mode + "' " + host + url + " " + " -d '" + body + "'"
    ret, out =  exec_command(cmd)
    return ret, out

def start_process(proc_name, proc_path='/Applications/AvailCV/bin/', msg_protocol='', kill_process=True):
    success, proc_id = get_proc_id(proc_name)
    if not success: 
        sys.exit(-1)

    if proc_id is not None:
        if not kill_process:
            print_info("process %s already started %s "%(proc_name, proc_id))
            return 
        ret, out = exec_command('kill -9 ' + proc_id)
        if ret != 0: 
            print_error("Failed to kill the existing process %s "%(proc_name))
            sys.exit(-1)
        time.sleep(1)

        success, proc_id = get_proc_id(proc_name)
        if not success or proc_id is not None:
            print_error("Failed to kill the existing process %s "%(proc_name))
            sys.exit(-1)
    
    cmd = 'nohup ' + proc_path + proc_name + '  ' + msg_protocol + ' > /dev/null 2>&1 &'
    ret, out = exec_command(cmd)
    if ret != 0: 
        print_error("Failed to start the process %s "%(proc_name))
        sys.exit(-1)

    print_info("process %s started %s "%(proc_name, ret))
    
    time.sleep(1)
    success, proc_id = get_proc_id(proc_name)
    if not success or proc_id is None:
        print_error("Failed to start the process %s "%(proc_name))
        sys.exit(-1)

    print_info("start the process %s successfully."%(proc_name))

def kill_process(proc_name):
    success, proc_id = get_proc_id(proc_name)
    if not success:
        print_info("process %s is not found or running"%(proc_name)) 
        sys.exit(-1)
    if proc_id is not None:
        ret, out = exec_command('kill -9 ' + proc_id)
        if ret != 0:
            print_error("Failed to kill the existing process %s "%(proc_name))
            sys.exit(-1)
        time.sleep(1) 
        
        success, proc_id = get_proc_id(proc_name)
        if not success or proc_id is not None:
            print_error("Failed to kill the existing process %s "%(proc_name))
            sys.exit(-1)

    print_info("kill process %s successfully."%(proc_name)) 

def cleanup_files(file_name): 
    ret, out = exec_command('rm -rf  ' + file_name) 
    if ret != 0: 
        print_error("Failed to cleanup the files  %s "%(file_name))
        sys.exit(-1)
    print_info("clean up successfully.") 

# get CPU/MEM percentage of running process 
def get_usage(proc_id):
    #p = psutil.Process(int(proc_id))
    num_core = psutil.cpu_count(logical=False) 
    cmd = "ps -p "  + proc_id + " -o %cpu,%mem" 
    ret, out = exec_command(cmd)
    msg = out.splitlines()
    success = False 
    cpu_u = 0.0 
    mem_u = 0.0 
    if ret != 0:
        print_error("Failed to kill the existing process %s "%(proc_name))
        return 0.0, 0.0
    elif ret == 0 and len(msg) == 2:
        m_list = msg[1].split(' ')
        while '' in m_list:
            m_list.remove('')
        #cpu_u = float(m_list[0])/num_core
        cpu_u = float(m_list[0])
        mem_u = float(m_list[1])
        cmd = "uptime"  
        ret, out = exec_command(cmd)
        load_avg = float(out.split(' ')[-1]) 
        success = True 

    return success, '{:4.2f}'.format(cpu_u), '{:4.2f}'.format(mem_u), '{:4.2f}'.format(load_avg) 

