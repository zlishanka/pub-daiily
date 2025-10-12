---
description: Comprehensive code quality review
argument-hint: [file-or-directory] [focus-area]
---

# Code Review Guidelines

Please perform a code review of $1, focusing on $2.

## Review Priority

### 🔴 Critical Issues (Must Fix)

- **Security Vulnerabilities**: SQL Injection, XSS, CSRF, Hard-coded Credentials
- **Logic Errors**: May Lead to Runtime Errors or Data Corruption
- **Resource Leaks**: Unclosed Connections, Memory Leaks, File Handles

### 🟡 Important Issues (Highly Recommended)

- **Performance Bottlenecks**: Inefficient Algorithms (O(n²) or Worse), N+1 Queries
- **Maintainability**: Overcomplexity, Missing Key Comments, Duplicated Code
- **Error Handling**: Missing or Inappropriate Exception Handling

### 🟢 Improvement Suggestions (Optional)

- **Naming Clarity**: Misleading or Ambiguous Variable/Function Names
- **Coding Style**: Inconsistent Formatting, Outdated Comments
- **Best Practices**: More Elegant or Idiomatic Implementations

## Output Format

For each issue, provide:

1. **Location**: `filename:line number`
2. **Level**: 🔴 / 🟡 / 🟢
3. **Issue**: A concise description
4. **Reason**: Why this is a problem
5. **Fix**: A concrete and feasible solution
6. **Example**: A comparison of the code before and after the fix (if applicable)

## Key Principles

- Report only valuable findings and avoid noise
- Prioritize reporting code that may cause real problems
- Keep feedback concise and actionable
- Provide specific suggestions for improvement, not generalities
