## Instructions

    # What script does
 
        (1) Take snapshot from all available external devices for every 10 seconds. For gen2 console, 4 externals, for gen1.5, 2 externals
        (2) Send snapshot (png image)  to a pre-configured aws s3 bucket
        (3) Script can be interrupted by keyboard event "ctrl+c" or it would timeout automatically at about 30 minutes

    # When to use 
        
        pre-call, post-call but not during the call to avoid camera contention.  

    # Installation

        (1) Use BeyondTrust File Transfer to upload the tar ball external_capturing.tar.gz to the console
 
        (2) Remotely login into field console through BeyondTrust terminal, start a console terminal (not command line shell though)

        (3) Unzip the external_capturing.tar.gz
   
            tar -xvzf external_capturing.tar.gz 

        (4) Create virtural environment

            cd external_capturing
            python3 -m venv env
  
        (5) Install the python packages

            source env/bin/activate
            pip install -r requirements.txt
            
        (6) Finish installation, exit virtual env 

            deactivate
 
    # Usage (run script)

            (1) Remotely login into field console through BeyondTrust terminal, start a console terminal (not command line shell though)
           
            (2) Get into directory and apply virtual environment  
            
            cd external_capturing
            source env/bin/activate

            (3) Run capturing script 
 
            python capture.py 
        
                - by default, script will stop capturing automatically after 30 minutes. It can be interrupted by "ctrl+c" as well
                    To run script with different time duration, use option -d   
        
                -  The followings are example to run script with 20 and 5 minutes duration
 
                python capture.py -d 20      
                python capture.py -d 5
    
      
            (4) After it stops 30 minutes or be interrupted manually ctrl+c, leave virtual environment 

                deactivate
              
            (5) Send notice to dev team (console id, time of capture),  we will be getting captured images from S3 for analysis! 
