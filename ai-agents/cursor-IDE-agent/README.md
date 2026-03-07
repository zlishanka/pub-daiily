# Cursor IDE Agent — Documentation

Documentation for the **Cursor IDE Agent**: how it works, how to configure it (rules, commands, skills), and how it interacts with MCP servers.

---

## Contents index

| File | Summary |
|------|---------|
| [cursor.agent.md](cursor.agent.md) | Core agent overview: what it is, how to open it, and its three components (instructions, tools, user messages). |
| [cursor.rules.md](cursor.rules.md) | **Rules** — Project, User, Team rules and AGENTS.md; rule types, file structure, and precedence. |
| [cursor.commands.md](cursor.commands.md) | **Commands** — Custom `/`-prefixed workflows; project/global/team commands and how to create them. |
| [cursor.agent.skills.md](cursor.agent.skills.md) | **Skills** — Extending the agent with domain-specific packages (SKILL.md, scripts, references, assets). |
| [cursor.agent.call.flow.details.md](cursor.agent.call.flow.details.md) | **MCP call flow** — End-to-end example: Jira → GitHub → Runner → Confluence with approval gates and JSON payloads. |

---

## Quick reference

### Agent basics
- **Open agent**: `Cmd+I` (sidepane).
- **Components**: Instructions (system prompt + rules), Tools (edit, search, terminal, etc.), User messages.

### Configuration mechanisms

| Mechanism | Location | Purpose |
|-----------|----------|---------|
| **Rules** | `.cursor/rules/`, User/Team, AGENTS.md | Persistent context and behavior (always / intelligent / file-scoped / manual). |
| **Commands** | `.cursor/commands/`, `~/.cursor/commands/` | Reusable workflows triggered by `/` in chat. |
| **Skills** | `.cursor/skills/`, `~/.cursor/skills/` | Domain-specific packages (SKILL.md + optional scripts/references/assets). |

### Rule precedence
**Team Rules → Project Rules → User Rules**

### MCP integration
- Cursor is the **MCP host**: it connects to MCP servers (Jira, GitHub, Confluence, Runner, etc.).
- Composer shows **approval prompts** before running MCP tools.
- Flow: User prompt → LLM plan → tool calls (with approval) → synthesis.

---

## Reading order

1. **New to the agent**: Start with [cursor.agent.md](cursor.agent.md).
2. **Configuring behavior**: [cursor.rules.md](cursor.rules.md) and [cursor.commands.md](cursor.commands.md).
3. **Adding capabilities**: [cursor.agent.skills.md](cursor.agent.skills.md).
4. **Understanding MCP flows**: [cursor.agent.call.flow.details.md](cursor.agent.call.flow.details.md).
