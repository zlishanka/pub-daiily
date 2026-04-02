# Claude Code MCP Server Guide

## Overview

MCP (Model Context Protocol) servers extend Claude Code with external tools and data sources.
Configured servers are **automatically loaded on every startup** — no rules or skills needed.

---

## Transport Types

| Transport | Use Case |
|-----------|----------|
| `http`    | Remote/cloud services (recommended) |
| `sse`     | Legacy real-time servers (deprecated, prefer http) |
| `stdio`   | Local tools, scripts, CLI-based servers |

---

## Adding Servers

### HTTP (remote service)
```bash
claude mcp add --transport http <name> <url>

# Examples
claude mcp add --transport http sentry https://mcp.sentry.dev/mcp
claude mcp add --transport http github https://api.githubcopilot.com/mcp/
claude mcp add --transport http notion https://mcp.notion.com/mcp

# With auth header
claude mcp add --transport http stripe https://mcp.stripe.com \
  --header "Authorization: Bearer sk-..."
```

### Stdio (local process)
```bash
claude mcp add --transport stdio <name> -- <command> [args...]

# PostgreSQL
claude mcp add --transport stdio db -- npx -y @bytebase/dbhub \
  --dsn "postgresql://user:pass@localhost:5432/mydb"

# Filesystem
claude mcp add --transport stdio filesystem -- \
  npx -y @modelcontextprotocol/server-filesystem /path/to/dir

# Playwright (browser automation)
claude mcp add --transport stdio playwright -- npx -y @playwright/mcp@latest

# With environment variables
claude mcp add --transport stdio myserver \
  --env API_KEY=secret \
  --env DEBUG=true \
  -- ./my-server
```

> **Flag ordering:** all options (`--transport`, `--env`, `--scope`, `--header`) must come
> **before** the server name. The `--` separator precedes the command and its arguments.

### Add from JSON
```bash
claude mcp add-json <name> '<json>'

# HTTP example
claude mcp add-json weather '{"type":"http","url":"https://api.weather.com/mcp","headers":{"Authorization":"Bearer token"}}'

# Stdio example
claude mcp add-json localdb '{"type":"stdio","command":"npx","args":["-y","@bytebase/dbhub"],"env":{"DSN":"${DATABASE_URL}"}}'
```

### Import from Claude Desktop
```bash
claude mcp add-from-claude-desktop
```

---

## Scopes

| Scope | Flag | Stored in | Loads when |
|-------|------|-----------|------------|
| Local (default) | `--scope local` | `~/.claude.json` (keyed by project path) | `claude` started in that project |
| Project | `--scope project` | `.mcp.json` at project root | Anyone starts `claude` in that project |
| User | `--scope user` | `~/.claude.json` | `claude` started anywhere |

**Precedence:** Local > Project > User (when server names conflict)

```bash
# Available only in current project (private)
claude mcp add --scope local --transport http sentry https://mcp.sentry.dev/mcp

# Shared with team via git
claude mcp add --scope project --transport http sentry https://mcp.sentry.dev/mcp

# Available across all your projects
claude mcp add --scope user --transport stdio db -- npx -y @bytebase/dbhub --dsn "..."
```

---

## Managing Servers

```bash
claude mcp list           # list all configured servers
claude mcp get <name>     # details for a specific server
claude mcp remove <name>  # remove a server
/mcp                      # check server status inside a session
```

---

## Auth & Secrets

### Option 1: `--header` flag (HTTP servers)
```bash
claude mcp add --transport http myapi https://api.example.com/mcp \
  --header "Authorization: Bearer $MY_TOKEN"
```

### Option 2: `--env` flag (stdio servers)
```bash
claude mcp add --transport stdio myserver \
  --env API_KEY=abc123 \
  -- ./server-binary
```

### Option 3: Environment variable expansion in `.mcp.json`
Use `${VAR}` or `${VAR:-default}` syntax — variables are read from your shell environment at startup.

```json
{
  "mcpServers": {
    "mydb": {
      "command": "npx",
      "args": ["-y", "@bytebase/dbhub"],
      "env": {
        "DSN": "${DATABASE_URL}",
        "PORT": "${MCP_PORT:-8080}"
      }
    }
  }
}
```

Export secrets from your shell profile (`.zshrc` / `.bashrc`), not hardcoded in `.mcp.json`.

### Option 4: OAuth (browser-based)
For services like Notion, Sentry, GitHub:
```bash
claude mcp add --transport http notion https://mcp.notion.com/mcp
# Then inside Claude Code:
/mcp   # triggers the OAuth flow
```

---

## Environment Variables (Global)

```bash
MCP_TIMEOUT=10000 claude           # server startup timeout (ms, default varies)
MAX_MCP_OUTPUT_TOKENS=50000 claude # increase tool output limit (default: 10,000)
```

---

## Project `.mcp.json` Structure

Committed to git, shared with the team:

```json
{
  "mcpServers": {
    "sentry": {
      "type": "http",
      "url": "https://mcp.sentry.dev/mcp"
    },
    "localdb": {
      "type": "stdio",
      "command": "npx",
      "args": ["-y", "@bytebase/dbhub", "--dsn", "${DATABASE_URL}"]
    }
  }
}
```

---

## Common MCP Servers

| Server | Command |
|--------|---------|
| Sentry | `claude mcp add --transport http sentry https://mcp.sentry.dev/mcp` |
| GitHub | `claude mcp add --transport http github https://api.githubcopilot.com/mcp/` |
| Notion | `claude mcp add --transport http notion https://mcp.notion.com/mcp` |
| PostgreSQL | `claude mcp add --transport stdio db -- npx -y @bytebase/dbhub --dsn "postgres://..."` |
| Filesystem | `claude mcp add --transport stdio fs -- npx -y @modelcontextprotocol/server-filesystem /path` |
| Playwright | `claude mcp add --transport stdio playwright -- npx -y @playwright/mcp@latest` |

---

## Quick Reference

```
# Add
claude mcp add [--transport http|sse|stdio] [--scope local|project|user] [--env K=V] <name> [url | -- cmd args]

# Manage
claude mcp list
claude mcp get <name>
claude mcp remove <name>
/mcp   (inside session)
```
