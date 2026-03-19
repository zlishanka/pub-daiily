---
title: Claude Code Workflow Cheatsheet — 2026 Edition
created: 2025-03-14
tags:
  - claude
  - claude-code
  - workflow
  - cheatsheet
  - skills
  - hooks
  - memory
  - CLAUDE.md
aliases:
  - Claude Code Cheatsheet
  - Claude Workflow
---

# Claude Code Workflow Cheatsheet — 2026 Edition

Getting Started • Project Setup • File Structure • Skills • Hooks • Memory • Workflows

---

## Quick Index (MOC)

| Section | Content |
|--------|---------|
| [[#1. Getting Started]] | Install, init, first commands |
| [[#2. Understanding CLAUDE.md]] | WHAT / WHY / HOW, examples |
| [[#3. Memory File Hierarchy]] | Global → project → subfolder |
| [[#4. CLAUDE Best Practices]] | How to write and maintain memory |
| [[#5. Project File Structure]] | Where CLAUDE.md, .claude/, skills live |
| [[#6. Adding Skills]] | Project vs personal, SKILL.md, auto-invocation |
| [[#7. Skill Ideas for AI Engineers]] | code-review, testing, deploy, etc. |
| [[#8. Setting Up Hooks]] | PreToolUse, PostToolUse, Notification |
| [[#9. Permissions & Safety]] | allow / deny patterns |
| [[#10. The 4-Layer Architecture]] | CLAUDE → Skills → Hooks → Agents |
| [[#11. Daily Workflow Pattern]] | Plan mode, compact, rewind, commit |
| [[#12. Quick Reference]] | /init, /compact, shortcuts |

---

## 1. Getting Started

#getting-started #install #init

**Requires:** Node 18+

**Install Claude Code:**

```bash
curl -fsSL https://claude.ai/install.sh | bash
```

**First run:**

```bash
cd your-project
claude /init
```

`/init` scans your codebase and creates a starter memory file (CLAUDE.md).

---

## 2. Understanding CLAUDE.md

#CLAUDE.md #memory #context

**What it is:** Claude's persistent memory about your project. Loaded automatically at the start of every session.

**Structure (WHAT, WHY, HOW):**

| Category | Include |
|----------|---------|
| **WHAT** | Tech stack, directory map, architecture |
| **WHY** | Purpose of each part, module roles, design decisions |
| **HOW** | Build/test/lint commands, workflows, gotchas |

**Example — project header:**

```markdown
# Project: MyApp
FastAPI REST API + React SPA + Postgres
```

**Example — commands:**

```markdown
## Commands
npm run dev
npm run test
npm run lint
```

**Example — architecture:**

```markdown
## Architecture
/app   -> Next.js App Router pages
/lib   -> shared utilities
/prisma -> DB schema & migrations
```

---

## 3. Memory File Hierarchy

#memory #hierarchy #scope

Claude loads memory by scope (broadest first, then more specific):

| Location | Scope |
|----------|--------|
| `~/.claude/CLAUDE.md` | Global — all projects |
| `~/CLAUDE.md` | Parent monorepo root |
| `./CLAUDE.md` | Project (often shared via git) |
| `./frontend/CLAUDE.md` | Subfolder — scoped context |

**Best practices:**

- Keep each file **&lt; 200 lines**
- Subfolder files **append** context; they don't replace parent context
- **Never overwrite** parent context in a child file

---

## 4. CLAUDE Best Practices

#best-practices #memory

- Run **`/init` first**, then refine the generated output
- **Be specific** in instructions and descriptions
- **Add gotchas** Claude can't infer (quirks, env, conventions)
- **Reference docs** with `@filename` when relevant
- **Add workflow rules** (e.g. when to run tests, lint)
- **Keep memory concise** — only what's needed for the session
- **Commit CLAUDE.md to Git** so the team shares the same context

---

## 5. Project File Structure

#file-structure #project-setup

Typical layout with Claude Code:

```
your-project/
├── CLAUDE.md
├── .claude/
│   ├── settings.json
│   ├── settings.local.json
│   ├── skills/
│   │   ├── code-review/
│   │   │   └── SKILL.md
│   │   ├── testing/
│   │   │   └── SKILL.md
│   │   └── helpers.py
│   ├── commands/
│   │   └── deploy.md
│   └── agents/
│       └── security-reviewer.md
├── arc/
├── .gitignore
└── ...
```

---

## 6. Adding Skills (The Superpower)

#skills #SKILL.md #auto-invoke

**What skills are:** Markdown guides Claude auto-invokes based on natural language (description + user intent).

**Locations:**

| Type | Path |
|------|------|
| **Project skill** | `.claude/skills/<name>/SKILL.md` |
| **Personal skill** | `~/.claude/skills/<name>/SKILL.md` |

**Important:** The **description** field is critical for auto-activation — it tells Claude when to use the skill.

**Example skill — `name: testing patterns`:**

- `description:` Jest testing patterns
- `allowed tools:` Read, Grep, Glob

**Testing patterns content:**

- Use `describe` + `it` + AAA pattern
- Use factory mocks

---

## 7. Skill Ideas for AI Engineers

#skills #ideas

- **code-review**
- **testing patterns**
- **commit messages**
- **docker-deploy**
- **codebase-visualizer**
- **api-design**

---

## 8. Setting Up Hooks

#hooks #PreToolUse #PostToolUse #safety

**What hooks are:** Deterministic callbacks that run at defined points.

**Hook types:** PreToolUse • PostToolUse • Notification

**Example — PreToolUse (e.g. security check before Bash):**

```json
"hooks": {
  "PreToolUse": [
    {
      "matcher": "Bash",
      "hooks": [
        {
          "type": "command",
          "command": "scripts/sec.sh",
          "timeout": 5
        }
      ]
    }
  ]
}
```

**Exit codes:**

- `0` → allow
- `2` → block

---

## 9. Permissions & Safety

#permissions #allow #deny

**Example permissions:**

```json
{
  "permissions": {
    "allow": [
      "Read:*:*",
      "Bash:git:*",
      "Write:*:*.md"
    ],
    "deny": [
      "Read:AI & ML DATA SCIENTIST",
      "Bash:sudo:*"
    ]
  }
}
```

Use **allow** for what Claude can do; use **deny** to block sensitive paths or commands (e.g. `sudo`, specific dirs).

---

## 10. The 4-Layer Architecture

#architecture #layers

| Layer | Role |
|-------|------|
| **L1 — CLAUDE.md** | Persistent context and rules |
| **L2 — Skills** | Auto-invoked knowledge packs |
| **L3 — Hooks** | Safety gates and automation |
| **L4 — Agents** | Subagents with their own context |

---

## 11. Daily Workflow Pattern

#workflow #daily

1. `cd project && claude`
2. **Shift + Tab + Tab** → Plan Mode
3. Describe feature intent
4. **Shift + Tab** → Auto Accept
5. **`/compact`** → compress context when needed
6. **Esc Esc** → rewind
7. Commit frequently
8. Start a new session per feature

---

## 12. Quick Reference

#shortcuts #commands

| Action | How |
|--------|-----|
| Generate CLAUDE.md | `/init` |
| Check installation | `/doccat` |
| Compress context | `/compact` |
| Change modes | **Shift + Tab** |
| Toggle extended thinking | **Tab** |
| Rewind | **Esc Esc** |

---

## Related

- [[ChatGPT-Prompt-Guide]] — general LLM prompt patterns
- [[Unlock-God-Mode-Prompts]] — deep / unconventional prompts
