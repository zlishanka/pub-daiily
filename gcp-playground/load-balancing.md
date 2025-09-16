## Configuring an HTTP Load Balancer with Autoscaling 
- Google Cloud HTTP(S) load balancing is implemented at the edge of Google's network in Google's points of presence (POP) around the world. 
	- User traffic directed to an HTTP(S) load balancer enters the POP closest to the user 
	- and is then load-balanced over Google's global network to the closest backend that has sufficient available capacity.

![alt text](gcp-http-load-balancing.png "GCP http load balancing")

### Tasks 
- Create a health check firewall rule
- Create a NAT configuration using Cloud Router
- Create a custom image for a web server
- Create an instance template based on the custom image
- Create two managed instance groups
- Configure an HTTP load balancer with IPv4 and IPv6
- Stress test an HTTP load balancer

https://www.cloudskillsboost.google/classrooms/31136/labs/255337/materials
