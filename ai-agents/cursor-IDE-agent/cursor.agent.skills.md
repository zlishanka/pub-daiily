# Agent Skills

- Agent Skills is an open standard for extending AI agents with specialized capabilities.
- Skills package domain-specific knowledge and workflows that agents can use to perform specific tasks.

## What are skills?

- A skill is a portable, **version-controlled** package that teaches agents how to perform domain-specific tasks.
- Skills can include both **instructions** and **executable scripts or code** that agents can run.

## How it works

- When Cursor starts, it automatically discovers skills from skill directories and makes them available to Agent. 
- The agent is presented with available skills and decides when they are relevant based on context.
- Skills can also be manually invoked by typing `/` in Agent chat and searching for the skill name.

## Skill directories

| Location | Scope |
|----------|-------|
| `.cursor/skills/` | Project-level |
| `.claude/skills/` | Project-level (Claude compatibility) |
| `.codex/skills/` | Project-level (Codex compatibility) |
| `~/.cursor/skills/` | User-level (global) |
| `~/.claude/skills/` | User-level (global, Claude compatibility) |
| `~/.codex/skills/` | User-level (global, Codex compatibility) |

- Each skill should be a folder containing a `SKILL.md` file
```bash
.cursor/
└── skills/
    └── my-skill/
        └── SKILL.md
```
- Skills can also include optional directories for `scripts, references, and assets`
```bash
.cursor/
└── skills/
    └── deploy-app/
        ├── SKILL.md
        ├── scripts/
        │   ├── deploy.sh
        │   └── validate.py
        ├── references/
        │   └── REFERENCE.md
        └── assets/
            └── config-template.json
```

## SKILL.md file format

- Each skill is defined in a SKILL.md file with YAML frontmatter:
```bash
---
name: my-skill
description: Short description of what this skill does and when to use it.
---

# My Skill

Detailed instructions for the agent.

## When to Use

- Use this skill when...
- This skill is helpful for...

## Instructions

- Step-by-step guidance for the agent
- Domain-specific conventions
- Best practices and patterns
- Use the ask questions tool if you need to clarify requirements with the user

```
## Optional directories

- Skills support these optional directories

| Directory | Purpose |
|-----------|---------|
| `scripts/` | Executable code that agents can run |
| `references/` | Additional documentation loaded on demand |
| `assets/` | Static resources like templates, images, or data files |

## References
[Cursor: How skills work](https://cursor.com/docs/context/skills#how-skills-work)  
[Install skills from Github](https://cursor.com/docs/context/skills#installing-skills-from-github)  
[antigravity-awesome-skills](https://github.com/sickn33/antigravity-awesome-skills)  

