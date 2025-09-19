# Containers in Google Cloud 

## Container fundamentals
- What is a container?  A container is an invisible box around your code and its dependencies, with limited access to its own partition of the file system and hardware.
- What makes containers flexible?  A container virtualizes the OS and dependencies to make your code ultra portable. This allows you to “code once and run anywhere”.
- How do you develop application code?  You develop on hardware, while executing your final code on VMs free from typical software dependencies.

### Container images
- An application and its dependencies are called an image.
- A container is a running instance of an image.
- Building software into container images, means you can easily package and ship an application.
- Docker is a open-source software in which you can build and run container images.

![alt text](gcp-container-cloud-build.png "GCP Container Cloud Build") 

## Google Kubernetes Engine

### Orchestrating containers with Kubernetes
- Kubernetes basics
	- Kubernetes is an open-source platform for managing containerized workloads and services.
	- It is a set of APIs for deploying containers on a set of nodes called a cluster.
	- It is declarative, allowing you to describe a set of applications and how they should interact.
- Kubernetes features 
	- Workload types 
		- Supports stateless and stateful applications 
		- Supports batch jobs
	- Autoscaling
		- Automatically scales in and out containerized applications based on resource utilization and daemon tasks
	- Resource controls 
		- Specify resource request levels and resource limits for your workloads
	- Portability
		- Supports workload portability across on-premises or multiple cloud service providers
		- Deploy anywhere and move workloads without vendor lock-in

### Kubernetes concepts: Pod
- A Pod is the smallest unit in Kubernetes that you create or deploy.
	- Represents a running process on your cluster
	- Provides a unique network IP address and set of ports for your containers and configurable options

![alt text](gcp-container-gke-pod.png, "Pod")

### Kubernetes concepts: Deployment
- A Deployment represents a group of replicas of the same Pod and keeps your Pods running even when the nodes they run on fail.

![alt text](gcp-container-gke-deploy.png, "Deploy")

### Kubernetes concepts: Service
- A Service is an abstraction that defines a logical set of Pods and a policy by which to access them.
	- Kubernetes creates a Service with a fixed IP address for your Pods.
	- A Service group is a set of Pods and provides a stable endpoint (or fixed IP address) for them.

![alt text](gcp-container-gke-service.png, "Service")

## Start a Kubernetes cluster managed by Kubernetes Engine 

### Set project

```bash 
gcloud config set project qwiklabs-gcp-04-d01c2c70cc92
Updated property [core/project].
```

### Update env MY_ZONE and create clusters 
```bash
export MY_ZONE=us-central1-a
gcloud container clusters create webfrontend --zone $MY_ZONE --num-nodes 2
```
```bash
kubeconfig entry generated for webfrontend.
NAME: webfrontend
LOCATION: us-central1-a
MASTER_VERSION: 1.33.4-gke.1036000
MASTER_IP: 34.28.52.168
MACHINE_TYPE: e2-medium
NODE_VERSION: 1.33.4-gke.1036000
NUM_NODES: 2
STATUS: RUNNING
STACK_TYPE: IPV4
```
- Start a Kubernetes cluster managed by Kubernetes Engine. 
- Name the cluster webfrontend and configure it to run 2 nodes:
- It takes several minutes to create a cluster as Kubernetes Engine provisions virtual machines for you.

### After the cluster is created, check your installed version of Kubernetes
```bash
kubectl version 
```

### Run and deploy a container
```bash
kubectl create deploy nginx --image=nginx:1.17.10
```
```bash
deployment.apps/nginx created
```
- In Kubernetes, all containers run in pods. 
- This use of the kubectl create command caused Kubernetes to create a deployment consisting of a single pod containing the nginx container. 
- A Kubernetes deployment keeps a given number of pods up and running even in the event of failures among the nodes on which they run. 
- In this command, you launched the default number of pods, which is 1.

### View the pod running the nginx container
```bash
kubectl get pods
NAME                     READY   STATUS    RESTARTS   AGE
nginx-5d7f755ff7-bmb8v   1/1     Running   0          73s
```

### Expose the nginx container to the Internet
```bash
kubectl expose deployment nginx --port 80 --type LoadBalancer
```
```bash
service/nginx exposed
```

- Kubernetes created a service and an external load balancer with a public IP address attached to it. 
- The IP address remains the same for the life of the service. 
- Any network traffic to that public IP address is routed to pods behind the service: in this case, the nginx pod.

### View the new service:
```bash
kubectl get services
```
```bash
NAME         TYPE           CLUSTER-IP      EXTERNAL-IP    PORT(S)        AGE
kubernetes   ClusterIP      34.118.224.1    <none>         443/TCP        7m59s
nginx        LoadBalancer   34.118.225.33   34.31.94.162   80:30169/TCP   79s
```
- You can use the displayed external IP address to test and contact the nginx container remotely.
- It may take a few seconds before the External-IP field is populated for your service. 
- This is normal. Just re-run the kubectl get services command every few seconds until the field is populated.

### Scale up the number of pods running on your service
```bash
kubectl scale deployment nginx --replicas 3
kubectl get pods
kubectl get services
```
- Scale up the number of pods running on your service
- Confirm that Kubernetes has updated the number of pods:
- Confirm that your external IP address has not changed:
- Return to the web browser tab in which you viewed your cluster's external IP address. 
- Refresh the page to confirm that the nginx web server is still responding.



