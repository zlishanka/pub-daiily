# MCP Server — Documentation

Documentation for the **Model Context Protocol (MCP)**: what it is, how it works, how to build a server (with a Python example), and notes on specific MCP servers (Fastly, Yahoo Fantasy).

---

## Contents index

| File | Summary |
|------|---------|
| [mcp-basics.md](mcp-basics.md) | **MCP overview** — What MCP is (open standard for AI↔data/APIs); key features (dynamic context, memory, LLM-optimized, multi-agent); core concepts: servers, clients, tools/resources/prompts. |
| [mcp-example.md](mcp-example.md) | **Building an MCP server** — Client–server model; three services (Prompt, Resource, Tool); transports (stdio, HTTP+SSE); Python example with FastMCP (prompts, resources, tools), testing, and Claude Desktop integration. |
| [fastly.mcp.server.md](fastly.mcp.server.md) | **Fastly MCP server** — MCP server for Fastly: manage services, monitor performance, deploy changes, analyze issues, control security; security-first design, transports, pagination, privacy options. |
| [yahoo.fantasy.mcp.server.md](yahoo.fantasy.mcp.server.md) | **Yahoo Fantasy MCP server** — Public server URL, adding to ChatGPT/Claude/Cursor; lineup optimization, draft assistance, league management; references to Pipedream and GitHub. |

---

## Quick reference

### What is MCP?
- **Model Context Protocol** — Open standard (Anthropic) for connecting AI agents to data sources, APIs, and external systems.
- “USB-C of AI apps”: a standard way to plug **tools and context** into LLM-based clients (Claude Desktop, Cursor, etc.).

### Core concepts

| Concept | Description |
|--------|-------------|
| **Server** | Exposes **resources** or **tools** to the model (e.g. `get_forecast`, `/policies/leave-policy.md`). |
| **Client** | LLM-based app (Claude, Cursor) that discovers and invokes MCP servers; turns user prompts into tool/resource calls. |
| **Tools** | Functions the model can call (with approval): e.g. `createNewTicket`, `write_email_draft`. |
| **Resources** | File-like data the model can read: company wiki, datasets, etc. |
| **Prompts** | Templated text for specialized tasks. |

### Server services and transports
- **3 services**: Prompts (templates), Resources (data/files/DB), Tools (functions/APIs).
- **Transports**: **stdio** (local), **HTTP + SSE** (remote).

### Key MCP features
- Dynamic context switching; memory management; optimized for LLMs (relevant context only); multi-agent coordination; fine-tuned context retrieval.

---

## Reading order

1. **Concepts first**: [mcp-basics.md](mcp-basics.md).
2. **Hands-on**: [mcp-example.md](mcp-example.md) (Python/FastMCP, prompts, resources, tools).
3. **Example servers**: [fastly.mcp.server.md](fastly.mcp.server.md), [yahoo.fantasy.mcp.server.md](yahoo.fantasy.mcp.server.md).
