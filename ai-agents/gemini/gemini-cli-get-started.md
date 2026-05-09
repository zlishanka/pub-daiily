[source link](https://geminicli.com/docs/)
## Installation

Install Gemini CLI globally using `npm`. If you need to install `npm` first, use Homebrew:

```bash
# Optional: Install npm if you don't have it
brew install npm

# Install Gemini CLI
npm install -g @google/gemini-cli
```

## Authenticate

Run the `gemini` command to start the interactive setup:

```bash
gemini
```

Follow the prompt to authenticate:
- Select **1. Sign in with Google** when asked "How would you like to authenticate for this project?".

## CLI commands

|Command|Description|Example|
|---|---|---|
|`gemini`|Start interactive REPL|`gemini`|
|`gemini -p "query"`|Query non-interactively|`gemini -p "summarize README.md"`|
|gemini “query”|Query and continue interactively|gemini “explain this project”|
|`cat file \| gemini`|Process piped content|`cat logs.txt \| gemini`  <br>`Get-Content logs.txt \| gemini`|
|`gemini -i "query"`|Execute and continue interactively|`gemini -i "What is the purpose of this project?"`|
|`gemini -r "latest"`|Continue most recent session|`gemini -r "latest"`|
|`gemini -r "latest" "query"`|Continue session with a new prompt|`gemini -r "latest" "Check for type errors"`|
|`gemini -r "<session-id>" "query"`|Resume session by ID|`gemini -r "abc123" "Finish this PR"`|
|`gemini update`|Update to latest version|`gemini update`|
|`gemini extensions`|Manage extensions|See [Extensions Management](https://geminicli.com/docs/cli/cli-reference/#extensions-management)|
|`gemini mcp`|Configure MCP servers|See [MCP Server Management](https://geminicli.com/docs/cli/cli-reference/#mcp-server-management)|
## Interactive commands

|Command|Description|
|---|---|
|`/skills reload`|Reload discovered skills from disk|
|`/agents reload`|Reload the agent registry|
|`/commands list`|List available custom slash commands|
|`/commands reload`|Reload custom slash commands|
|`/memory reload`|Reload context files (for example, `GEMINI.md`)|
|`/mcp reload`|Restart and reload MCP servers|
|`/extensions reload`|Reload all active extensions|
|`/help`|Show help for all commands|
|`/quit`|Exit the interactive session|

## Model selection

These are convenient shortcuts that map to specific models:

| Alias        | Resolves To                                | Description                                                                                                               |
| ------------ | ------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------- |
| `auto`       | `gemini-2.5-pro` or `gemini-3-pro-preview` | **Default.** Resolves to the preview model if preview features are enabled, otherwise resolves to the standard pro model. |
| `pro`        | `gemini-2.5-pro` or `gemini-3-pro-preview` | For complex reasoning tasks. Uses preview model if enabled.                                                               |
| `flash`      | `gemini-2.5-flash`                         | Fast, balanced model for most tasks.                                                                                      |
| `flash-lite` | `gemini-2.5-flash-lite`                    | Fastest model for simple tasks.                                                                                           |