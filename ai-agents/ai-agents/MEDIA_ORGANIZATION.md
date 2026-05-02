---
title: Media Organization Summary
description: Documentation of the ai-agents media structure reorganization
date: 2026-04-26
type: meta
---

# Media Organization Complete ✅

## What Was Done

### 1. Created Centralized Media Structure
```
ai-agents/
└── _media/                          # New central media directory
    ├── agentic-engineers/           # 2 images
    ├── ai-agent/                    # 16 images
    ├── claude-code/                 # 2 images
    ├── claude-skills/               # 2 images
    ├── cursor-IDE-agent/            # 2 images
    ├── mcp-server/                  # 3 images
    └── skills/                      # 1 image
```

### 2. Migrated All Images
- **Total images moved**: 26
- **Categories**: 7
- **All images**: Organized by topic/domain

### 3. Updated Markdown References
- **Files updated**: 10
- **Reference format**: Changed from relative paths to `../_media/category/image`
- **Example**: 
  - Before: `![alt](workflows-rule-based.jpg)`
  - After: `![alt](../_media/ai-agent/workflows-rule-based.jpg)`

---

## Benefits

✅ **Centralized Management** — All media in one searchable location  
✅ **Clear Organization** — Images organized by topic/category  
✅ **Easy Maintenance** — Simple to find and manage media files  
✅ **Scalable** — Can easily add new categories as vault grows  
✅ **Clean Markdown** — No more mixed media in each folder  
✅ **Better Discovery** — Quick access to all visual assets  

---

## Files Updated

| File | Images Updated |
|------|---|
| `agentic-engineers/agentic-engineer-techniques.md` | 2 |
| `ai-agent/ai.agent.llm.workflows.md` | 4 |
| `ai-agent/ai.agent.llm.in.the.loop.md` | 2 |
| `ai-agent/ai.agent.improve.llm.with.tools.md` | 4 |
| `ai-agent/ai.agent.intro.md` | 1 |
| `claude-skills/claude.skills.vs.mcp.md` | 2 |
| `cursor-IDE-agent/cursor.agent.call.flow.details.md` | 1 |
| `mcp-server/mcp-example.md` | 2 |
| `mcp-server/mcp-basics.md` | 1 |
| `skills/skills.vs.mcp.md` | 1 |

---

## Image Inventory

### agentic-engineers/ (2 images)
- PIVLoopDiagram.png
- top-techniques-agentic-engineers.png

### ai-agent/ (16 images)
- LLM-not-enough-solve-problem.jpg
- agent-llm-in-loop.jpg
- agent-llm-workflow-common-patterns.jpg
- agent-workflow-example.jpg
- llm-tool-call-api.jpg
- llm-tool-call-example.jpg
- llm-tool-call-prompting.jpg
- pros-cons-3-softwares.jpg
- reward-hacking-positive-feedback.jpg
- reward-hacking-twitter-agent.jpg
- traditional-software-vs-ai-agent.jpg
- workflows-llm-based.jpg
- workflows-of-ava.jpg
- workflows-rule-based.jpg

### claude-code/ (2 images)
- anatomy-dot-claude-folder.jpg
- claude-code-workflow-cheatsheet.jpg

### claude-skills/ (2 images)
- claude.agent+skills+computer.jpeg
- claude.agent+skills+contextWindow.jpg

### cursor-IDE-agent/ (2 images)
- cursor-architecture-diagram.png
- cursor-mcp-flow-diagram.png

### mcp-server/ (3 images)
- mcp-ai-apps.jpg
- mcp-diagram.jpg
- mcp-server-task-overview.jpg

### skills/ (1 image)
- agent.skills.progressive.disclosure.png

---

## How to Use Going Forward

1. **Add new images** → Place in `_media/[category]/`
2. **Reference in markdown** → Use: `![alt](../_media/category/image.png)`
3. **Organize by topic** → Create new subdirectories as needed in `_media/`

---

## Obsidian Viewer Note

All images now display correctly in Obsidian vault with proper relative paths. The `../_media/` path works from any markdown file in the vault hierarchy.

---

**Migration completed**: 2026-04-26
