# Resource and Access Management of Google Cloud

## Review of AWS resource hierarchy: Levels
- AWS 
	- Organization Root
	- Organization Unit
	- Member Account )(Managerment and Member)  
	- Resource

## Comparison of resource hierarchy in AWS and GCP
- GCP
	- Organization (top of the hierarchy) 
	- Folder (represent a department of team) 
	- Project (container of resources) 
	- Resources

### Policy inheritance
- Policy like VM size cannot be larger than 4 CPUs
- Define policies at multiple levels
- GCP offers a hierarchy of ownership 

## Organizations: Organization roles

### Folders 
- Organization admin define folders
- Like Deapartment X, Department Y

### Projects
- Projects are separate entities under the organization node 
- Project has 3 attributes
	- ID	(immutable, unique)
	- name 	(changeable)
	- number (immuntable, unique)


## GCP Resource Manager tool: Roles

### Roles and hierarchy
- predefined roles
- admin, editor, viewer
	- cloudsql, storage, kubernetes, etc.
- `create role` : customize role
- [IAM Role Permission](https://cloud.google.com/iam/docs/permissions-change-log)
- [GCP tags and labels](https://storage.googleapis.com/jellyfish-training-demo-7/%20GCP%20Tags%20and%20labels.pdf) 


## Service Accounts
- Google Cloud IAM roles
- Service accounts are assigned to GCP instances
- Google-managed key pairs

## Labs
- AWS SDKs



