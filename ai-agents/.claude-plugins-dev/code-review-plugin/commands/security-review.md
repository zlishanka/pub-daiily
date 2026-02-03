---
description: Deep security vulnerability scan
argument-hint: [target-path]
---

# Security Audit Expert Mode

Perform a comprehensive security vulnerability analysis on $1.

## Security Checklist

### 1. Injection Attack Prevention
- SQL Injection, NoSQL Injection
- Command Injection, Code Injection
- Path Traversal, LDAP Injection

### 2. Authentication and Authorization
- Password Strength Policy
- Session Management (Solidification, Hijacking)
- Missing or Improper Permission Checks
- JWT Security Issues

### 3. Data Protection
- Sensitive Data Encryption (Transmission and Storage)
- Key and Credential Management
- Personal Information (PII) Handling

### 4. Input Validation
- Missing User Input Validation
- Insecure Deserialization
- XSS (Stored, Reflected, DOM)
- CSRF Protection

### 5. Configuration and Dependencies
- Secure Configuration Issues
- Dependent Packages with Known Vulnerabilities
- Debugging Information Leaks

## Output Requirements

Report only confirmed security issues. Each issue should include:

- Severity Level: Critical / High / Medium / Low
- **CWE Number**: For example, CWE-89 (SQL Injection)
- **Attack Scenario**: How it could be exploited
- **Impact Scope**: Potential damage
- **Remediation**: Specific code examples
- **References**: Links to OWASP, CVE, etc.
