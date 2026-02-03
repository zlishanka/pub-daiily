# Networking in Google Cloud 

## AWS vs GCP on Regions 
- VPC in GCP is very efficient, 
- one VPC covers multiple regions
- AWS has regional VPC

## VPC networking 
- Google Cloud VPC provides a logically isolated network connectivity. 
- VPCs combine the benefits of public cloud computing with those of private cloud computing. 

## Three types of creation of VPC
- Default
- Auto mode: 42 subnets
- Custom mode: no subnet pre-defined

##  Summary of differences beween AWS VPC and GCP VPC

## Cloud DNS

## command line to create VPC
```bash
gcloud compute networks create management --project=qwiklabs-gcp-03-21158b728798 --subnet-mode=custom --mtu=1460 --bgp-routing-mode=regional --bgp-best-path-selection-mode=legacy

gcloud compute networks subnets create managementsubnet-1 --project=qwiklabs-gcp-03-21158b728798 --range=10.240.0.0/20 --stack-type=IPV4_ONLY --network=management --region=us-east5
```

## create firewall rules 
```bash
gcloud compute --project=qwiklabs-gcp-03-21158b728798 firewall-rules create managementnet-allow-icmp-ssh-rdp --direction=INGRESS --priority=1000 --network=management --action=ALLOW --rules=tcp:22,tcp:3389 --source-ranges=0.0.0.0/0
```

## GCP NAT


