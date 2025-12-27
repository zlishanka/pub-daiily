# Cursor tips, workflow

## Useful tips 

### Command + k
- Highlight the code and use `command + k` to get pop-up
- Then to `ask questions` or tell it to make certain changes

### Agent mode
- `Cursor` -->  `Settings` --> `Cursor Settings` 
- Chooose `Models` , most of them are auto-enabled by admin, say `gemini 3` just comes out

## commands and rules
- `.cursor` directory in a project holds AI configuration, primarily for the Cursor IDE or cli
- subfolders like `commands/` for custom `/slash` commands (e.g., review-code.md) 
- and `rules/` for project-specific `.mdc` files that define AI behavior

```bash
my-project/
├── .cursor/
│   ├── rules/
│   │   ├── typescript-style.mdc
│   │   └── api-design.mdc
│   └── commands/
│       ├── review-code.md
│       └── write-tests.md
├── .cursorrules (Legacy or root rule file)
└── ... rest of your project
```

### Cursor rules
- Contains Markdown files defining custom AI action
- in current working direcotry `.cursor` --> `rules` --> system-design-guidance.mdc
- like `.cursor/rules/system-design-guidance.mdc` 
- may `Apply to Specific Files` like `*.tsx, *.ts, *.js, *.jsx` 
- Not model itself. Just guidance for the group users, etc.

### Cursor commands
- `.cursor/commands` : Contains Markdown files defining custom AI actions.
    - `create-pr.md` : Describes steps for creating a Pull Request.
    - `security-audit.md` : Contains prompts for running security checks.

- like `.cursor/commands/create-implementation-checklist.md` 
    - GOAL: write doc per the below. Don not write code. Do not start implementation. Write step only.
    - TASK: see the feature request below. Create a concise implementation checklist. 
- in `command-action.md` file, specify concrete `GOAL` and `TASK`

### Cli
- install cursor cli (command line interface)
```bash
curl https://cursor.com/install -fsS | bash

Next Steps
1. Add ~/.local/bin to your PATH:
   For zsh:
   echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc
   source ~/.zshrc
```
- Run interactive session
```bash
cursor-agent
```

### Agent vs Ask vs Plan vs Debug modes
- Agent : `Read and Write` 
- Ask : `Read` only, won't change your files
- Plan : Create plans for the specific tasks
    - Once it's created, you can start `Building` 
    - Planning, Building can be executed in parallel
- Can open multiple tabs to create multiple agents, each conducting different task.
- Debug mode
    - Agent adds logs to the codebase
    - Agent asks to run in debug mode and check run-time logs to identify the known bug

### Connect to MCP server
- `Cursor` -->  `Settings` --> `Cursor Settings` 
- Choose `Tools & MCP` 
- Install & connect various MCP servers
- like following MCP servers. In Chat, we can ask to pull Jira tickets through MCP server
```json
{
  "mcpServers": {
    "Linear": {
      "url": "https://mcp.linear.app/mcp",
      "headers": {}
    },
    "Atlassian": {
      "command": "npx mcp-remote https://mcp.atlassian.com/v1/sse",
      "env": {},
      "args": []
    }
  }
}
```

### Plan
- Create a plan

## References
[1] Cursor documentation : https://cursor.com/docs  

