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



