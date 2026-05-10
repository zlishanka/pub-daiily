---
title: Workflow Orchestration Framework
description: Core operational principles for AI-assisted development with Claude
aliases:
  - workflow orchestration
  - development workflow
  - orchestration principles
created: 2026-05-07
updated: 2026-05-07
type: framework
tags:
  - workflow
  - orchestration
  - claude-code
  - planning
  - execution
  - best-practices
  - development-workflow
---

# Workflow Orchestration Framework

> A disciplined approach to AI-assisted development: plan thoroughly, delegate intelligently, verify relentlessly, and improve continuously. Shard by Boris Cherny (creator of Claude Code at Anthropic).

---

## Table of Contents

- [[#Core Operational Principles|Core Operational Principles]]
- [[#Task Management|Task Management]]
- [[#Core Principles|Core Principles]]
- [[#Execution Checklist|Execution Checklist]]

---

## Core Operational Principles

### 1. Plan Node Default

> **When**: ANY non-trivial task (3+ steps or architectural decisions)

**Key Actions:**
- Enter plan mode before writing code
- If something goes sideways, **STOP and re-plan immediately** — don't keep pushing
- Use plan mode for verification steps, not just building
- Write detailed specs upfront to reduce ambiguity

> [!NOTE] Plan mode is your safety net. It prevents wasted effort on the wrong approach.

#planning #plan-mode #architecture

---

### 2. Subagent Strategy

> **When**: Context needs to stay clean; work is parallel or isolated

**Key Actions:**
- Use subagents **liberally** to keep main context window clean
- Offload research, exploration, and parallel analysis to subagents
- For complex problems, throw more compute at it via subagents
- One task per subagent for focused execution

> [!TIP] Subagents are context isolation tools. Each returns only final answers, keeping your main session's reasoning intact.

#subagents #context-management #parallel-work

---

### 3. Self-Improvement Loop

> **When**: After ANY correction from the user

**Key Actions:**
- Update `tasks/lessons.md` with the pattern that failed
- Write rules for yourself that prevent the same mistake
- Ruthlessly iterate on these lessons until mistake rate drops
- Review lessons at session start for relevant project

> [!SUCCESS] This is how you stop repeating the same mistakes. Each correction becomes a permanent rule.

#learning #improvement #mistakes #lessons

---

### 4. Verification Before Done

> **When**: Before marking ANY task as complete

**Key Actions:**
- Never mark a task complete without proving it works
- Diff behavior between main and your changes when relevant
- Ask yourself: **"Would a staff engineer approve this?"**
- Run tests, check logs, demonstrate correctness

> [!CAUTION] Verification separates "done" from "shipped." Don't skip this step.

#verification #testing #quality-assurance #correctness

---

### 5. Demand Elegance (Balanced)

> **When**: Implementing non-trivial changes

**Key Actions:**
- For non-trivial changes: pause and ask **"Is there a more elegant way?"**
- If a fix feels hacky: **"Knowing everything I know now, implement the elegant solution"**
- Skip this for simple, obvious fixes — don't over-engineer
- Challenge your own work before presenting it

> [!NOTE] Elegance ≠ complexity. A simpler, clearer solution is always more elegant than a hacky one.

#elegance #code-quality #design #refinement

---

### 6. Autonomous Bug Fixing

> **When**: Given a bug report

**Key Actions:**
- Just fix it. Don't ask for hand-holding
- Point at logs, errors, failing tests — then resolve them
- Zero context switching required from the user
- Go fix failing CI tests without being told how

> [!SUCCESS] Autonomous execution means you take ownership. Find the problem, understand it, fix it.

#bugs #autonomy #debugging #problem-solving

---

## Task Management

### Workflow Sequence

| Phase | Action | Artifact |
|-------|--------|----------|
| **1. Planning** | Write plan with checkable items | `tasks/todo.md` |
| **2. Verification** | Check in before starting implementation | Review with user |
| **3. Execution** | Mark items complete as you go | Progressive updates |
| **4. Documentation** | High-level summary at each step | Commit messages |
| **5. Results** | Add review section with outcomes | `tasks/todo.md` |
| **6. Learning** | Update lessons from corrections | `tasks/lessons.md` |

### Task Management Checklist

- [ ] **Plan First**: Write plan to `tasks/todo.md` with checkable items
- [ ] **Verify Plan**: Check in before starting implementation
- [ ] **Track Progress**: Mark items complete as you go
- [ ] **Explain Changes**: High-level summary at each step
- [ ] **Document Results**: Add review section to `tasks/todo.md`
- [ ] **Capture Lessons**: Update `tasks/lessons.md` after corrections

#task-management #planning #documentation

---

## Core Principles

### Principle 1: Simplicity First

**Statement**: Make every change as simple as possible. Impact minimal code.

**In Practice:**
- Don't add features you don't need
- Don't create abstraction layers prematurely
- If something can be done in 10 lines, don't make it 30
- Simple solutions compound over time

#simplicity #minimalism #code-quality

---

### Principle 2: No Laziness

**Statement**: Find root causes. No temporary fixes. Senior developer standards.

**In Practice:**
- Don't apply band-aids
- Understand *why* the bug happened
- Fix the underlying issue, not the symptom
- If you're tempted to say "this will do for now," that's a red flag

> [!CAUTION] Temporary fixes are permanent. They multiply. Stop the cycle.

#root-cause #rigor #standards

---

### Principle 3: Minimal Impact

**Statement**: Changes should only touch what's necessary. Avoid introducing bugs.

**In Practice:**
- Surgical changes, not wholesale rewrites
- Modify only the code that needs changing
- Test that you didn't break adjacent functionality
- Smaller changes = easier to review, easier to revert

#surgical #minimal-diff #risk-management

---

## Execution Checklist

Use this before starting any significant task:

- [ ] **Is this a plan-mode task?** (3+ steps, architectural decision?)
  - If yes: Enter `/plan` mode first
- [ ] **Does context matter?** (complex, exploratory, isolated?)
  - If yes: Consider spinning up a subagent
- [ ] **Have I reviewed lessons?** (relevant mistakes to avoid?)
  - If yes: Read `tasks/lessons.md` for this project
- [ ] **How will I verify this works?** (tests, logs, diff?)
  - Define verification step upfront
- [ ] **Is there a simpler way?** (before you code)
  - Pause and sketch alternatives
- [ ] **Am I fixing the root cause?** (or just the symptom?)
  - Trace the problem to its source

---

## Related Notes

- [[ai-agents/claude-code/claude.code.hidden.commands.md]] — Claude Code commands reference
- [[ai-agents/prompts]] — Prompt collections for various tasks
- [[ai-agents/skills]] — Available skills and how to use them

---

## Quick Reference

| Principle | When | Action |
|-----------|------|--------|
| **Plan Default** | 3+ steps | Enter `/plan` mode |
| **Subagent Strategy** | Parallel work | Offload to focused agents |
| **Self-Improvement** | After corrections | Update `lessons.md` |
| **Verification** | Before marking done | Run tests, check logs |
| **Elegant Code** | Non-trivial changes | Pause and improve |
| **Autonomous** | Bug reports | Fix without hand-holding |
| **Simplicity** | Always | Minimal, focused changes |
| **No Laziness** | Always | Root cause only |
| **Minimal Impact** | Always | Surgical, precise edits |

---

#workflow #orchestration #principles #framework #development-workflow
