# Instruction 

    https://www.youtube.com/watch?v=wbsbXfkv47A&t=1s
    https://www.youtube.com/watch?v=2VtuNOEw8S4&t=24s 

    # Requirements 
        Docker, AWS cli, AWS CDK
        npm install -g aws-cdk
        brew install node
        brew install docker --cask

    # Create a CDK project 
        mkdir docker-lambda-aws
        cdk init app --language typescript

    # Create docker image

        # main lambda handler function
            cd docker-lambda-aws; mkdir image/src
            image/src/main.py 

        # python packages
            image/requirements.txt       
   
        # Create docker file
            image/Dockerfile 

    # Build/test docker image

        docker build -t docker-image:test .
        docker run -p 9000:8080 docker-image:test
        curl "http://localhost:9000/2015-03-31/functions/function/invocations" -d '{}'

    # Create aws infrastructure code (type script)
    
        lib/docker-lambda-aws-stack.ts 
   
    # bootstrap 
        
        cdk bootstrap --region us-west-2

    # deploy
        cdk deploy
      
# Welcome to your CDK TypeScript project

    This is a blank project for CDK development with TypeScript.

    The `cdk.json` file tells the CDK Toolkit how to execute your app.

## Useful commands

    * `npm run build`   compile typescript to js
    * `npm run watch`   watch for changes and compile
    * `npm run test`    perform the jest unit tests
    * `cdk deploy`      deploy this stack to your default AWS account/region
    * `cdk diff`        compare deployed stack with current state
    * `cdk synth`       emits the synthesized CloudFormation template
