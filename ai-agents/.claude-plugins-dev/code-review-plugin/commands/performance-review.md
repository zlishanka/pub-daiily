---
description: Performance bottleneck analysis
argument-hint: [code-path]
---

# Performance review analysis

Analyze the performance characteristics of $1.

## Analysis Dimensions

### 1. Algorithm Complexity
- Time Complexity Analysis
- Space Complexity Estimation
- Identifying Optimizable Loops

### 2. Database Queries
- N+1 Query Problem
- Missing Indexes
- Overquerying
- Batched Operations

### 3. Resource Usage
- Memory Allocation Patterns
- Large Object Creation
- Caching Opportunities

### 4. Concurrency and Asynchrony
- Parallelizable Operations
- Blocking Calls
- Lock Contention

## Output Format

Each performance issue provides:

- **Location**: File and Function
- **Issue**: Current Performance Characteristics
- **Impact**: Estimated Performance Impact
- **Optimization Plan**: Specific Improvement Suggestions
- **Complexity**: Comparison Before and After Optimization (e.g., O(n²) → O(n log n))
