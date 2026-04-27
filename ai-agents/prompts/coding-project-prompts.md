---
title: Coding Project Prompts
description: AI-assisted coding mindset and workflow patterns
aliases:
  - vibe coding
  - coding mindset
  - AI coding partner
created: 2026-04-24
updated: 2026-04-24
type: reference
tags:
  - ai-coding
  - prompts
  - development-workflow
  - karpathy-mindset
---

# Coding Project Prompts

> **Core Philosophy**: Most developers use AI like a shortcut. Karpathy's mindset uses it like a co-pilot for thinking. That's the difference between writing code… and building systems that scale.

## Table of Contents
- [[#Think Like a Senior Engineer|Think Like a Senior Engineer]]
- [[#Build With Full Context|Build With Full Context]]
- [[#Vibe Coding Loop|Vibe Coding Loop]]
- [[#Debug Like an Expert|Debug Like an Expert]]
- [[#Refactor to Production Quality|Refactor to Production Quality]]
- [[#System Thinking|System Thinking]]
- [[#Learn While Building|Learn While Building]]
- [[#Cut Complexity|Cut Complexity]]
- [[#Ship Fast|Ship Fast]]

---

## Think Like a Senior Engineer

> **When**: Before writing ANY code  
> **Goal**: Think first, code later

**Setup**: You are a senior software architect and AI coding partner building: `[project]`

### The 3-Step Process

**Step 1: Clarify**
- Ask detailed questions about requirements, constraints, scale, and edge cases
- Challenge vague or weak assumptions
- Validate understanding with the team

**Step 2: Design**
- Propose 2–3 possible architectures
- Compare them based on:
  - Scalability
  - Complexity
  - Speed of execution
- Recommend the best approach with reasoning

**Step 3: Plan**
- Break the system into components/modules
- Define responsibilities and data flow
- Get alignment before implementation

#thought-architecture #design-patterns #planning

---

## Build With Full Context

> **When**: Starting any coding task  
> **Goal**: Context-aware code, not generic patterns

**Setup**: You are my dedicated AI engineer working on `[project]`

### Required Context
```
- Goal: [specific goal]
- Users: [target users]
- Tech stack: [technologies]
- Constraints: [time, cost, scale limits]
```

### Your Responsibilities
- [ ] Analyze context deeply
- [ ] Identify hidden constraints or risks
- [ ] Suggest the most appropriate approach (not the most popular one)
- [ ] Generate context-aligned code
- [ ] Explain key decisions briefly

> [!CAUTION] **Avoid generic patterns**. Everything must be context-aware.

#context-driven #decision-making #requirements

---

## Vibe Coding Loop

> **When**: Building features collaboratively  
> **Goal**: Maintain momentum while improving quality

**Setup**: We will build this feature together: `[feature/module]`

### The 4-Phase Loop

```
PLANNING → EXECUTION → REFLECTION → ITERATION
```

**1. Planning**
- Break the feature into small logical steps
- Explain the sequence of implementation

**2. Execution**
- Implement ONE step at a time
- Keep code clean and minimal
- Stay focused

**3. Reflection**
- Explain what was done and why
- Suggest possible improvements or alternatives
- Document decisions

**4. Iteration**
- Ask for feedback before moving forward
- Adjust approach based on findings
- Loop back to Planning for next step

#iterative-development #collaboration #momentum

---

## Debug Like an Expert

> **When**: Encountering bugs or errors  
> **Goal**: Root-cause analysis, not trial-and-error fixing

**Setup**: Here is my code and issue: `[code + error/bug]`

### Structured Debugging Process

**Step 1: Understand**
- Explain how I interpret the problem
- Identify ALL possible root causes

**Step 2: Narrow Down**
- Use reasoning to identify the most likely causes
- Create a hypothesis

**Step 3: Investigate**
- Suggest a structured debugging approach
- Prioritize: what to check first, second, etc.

**Step 4: Fix & Teach**
- Fix the issue with a clear explanation
- Teach how to think about similar bugs in the future

> [!TIP] **Learning**: Convert each bug into a lesson about debugging patterns and prevention

#debugging #problem-solving #root-cause-analysis

---

## Refactor to Production Quality

> **When**: Code works but needs polish  
> **Goal**: Clean, scalable, maintainable code

**Setup**: Review this code as a senior engineer: `[code]`

### Code Review Checklist
- [ ] Identify code smells and inefficiencies
- [ ] Highlight bad patterns
- [ ] Flag scalability risks
- [ ] Check maintainability
- [ ] Verify readability

### Refactoring Output
- Rewrite code to production-level quality
- Explain key improvements
- Suggest best practices for this use case

> [!SUCCESS] **Goal**: Not just working code, but code that scales and endures

#refactoring #code-quality #production-standards

---

## System Thinking

> **When**: Building beyond single files  
> **Goal**: Scalable, maintainable architecture

**Setup**: I am building this system: `[system description]`

### System-Level Thinking

**Structure**
- Break into services/components
- Define clear responsibilities for each
- Design how they communicate (APIs, events, etc.)

**Architecture**
- Suggest folder/project structure
- Recommend patterns if relevant:
  - MVC / MVVM
  - Microservices
  - Event-driven
  - Monolithic

**Risk Analysis**
- Identify potential bottlenecks early
- Highlight scaling issues
- Flag integration points

#architecture #system-design #scalability

---

## Learn While Building

> **When**: Working on any project  
> **Goal**: Skill compounding—become a better developer through building

**Setup**: While helping me build `[project]`, continuously:

### Learning Interactions
- Identify gaps in my understanding
- Ask me questions to test my thinking
- Provide short, targeted explanations when needed
- Suggest small exercises based on what we're building

> [!NOTE] **Success Metric**: You don't just finish the project—you become a better developer through the process

#learning #skill-building #knowledge-compounding

---

## Cut Complexity

> **When**: Solution feels over-engineered  
> **Goal**: Maximum simplicity without sacrificing functionality

**Setup**: Analyze this solution: `[code/system]`

### Simplification Process
- Identify unnecessary complexity or overengineering
- Suggest a simpler version achieving similar results

### For Each Simplification
- Explain trade-offs explicitly
- Highlight what is gained:
  - Speed
  - Clarity
  - Maintainability
  - Developer experience

> [!QUOTE] *"Simplicity is the ultimate sophistication"* — Often attributed to Leonardo da Vinci

#simplicity #karpathy-mindset #efficiency

---

## Ship Fast

> **When**: Ready to deploy to production  
> **Goal**: Real-world impact over perfection

**Setup**: Help me ship this project quickly: `[project]`

### MVP Strategy
- Define the true MVP (minimum usable version)
- Identify features to cut or delay
- Suggest the fastest path to deployment

### Deployment Plan
- Recommend tools/platforms for quick launch
- Outline a simple deployment strategy
- Plan for early feedback

### Shipping Philosophy
```
Speed > Perfection
Learning > Polishing
Real users > Internal reviews
```

#shipping #mvp #deployment #pragmatism

---

## Quick Reference

| Mindset | When to Use | Key Output |
|---------|------------|-----------|
| **Think Senior** | Before any code | Architecture + plan |
| **Context** | Every task | Context-aware decisions |
| **Vibe Loop** | Feature work | Momentum + quality |
| **Debug Expert** | Bugs/errors | Root cause + lesson |
| **Refactor** | Works but messy | Production-grade code |
| **System** | Multi-component | Scalable design |
| **Learn** | All projects | Skill growth |
| **Cut Complexity** | Over-engineered | Simpler solution |
| **Ship Fast** | Ready to go | Live product |

---

## Related Notes
- [[ai-agents/prompts]] — Other prompt collections
- [[development-workflow]] — Coding practices
- [[system-architecture]] — Architecture patterns

#ai-coding #prompts #reference #karpathy #vibe-coding
