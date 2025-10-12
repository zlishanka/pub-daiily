## Pro plan limit
Average users can send approximately 45 messages with Claude every five hours, 
OR send approximately 10-40 prompts with Claude Code every five hours

## Claude code workflow
- Use plan mode first , shift + tab to switch to plan mode. Think through first and won't generate any codes. it will create a game plan . Review the plan thoroughly.
- Generate CLAUDE.md file , `/init` command in any directory
- Use git as checkpoint system
- Use screenshot, simply drag screenshot file to terminal as a dialog context
- Use the web link as context
- Ask to Double check its work (can you make sure it doesn't break things...)
- Select Claude model :  Opus, Sonnet, etc. If you paid over $200, use Opus

### Install claude code
```bash
npm install -g @anthropic-ai/claude-code
claude update
```


### Start claude and bypass frequent trivial permission prompts
```bash
claude --dangerously-skip-permissions
``` 
### Setup Claude github action for a repo
- Create github action for a repo
```bash
	/install-github-app
```
- review a pull request
```bash
/review
/pr-comments : Get comments from a Github PR
/code-review :
```
### Create CLAUDE.me
- Manual creation by director
```bash
cd ../sub-dir; claude --create CLAUDE.md
```
#### Batch creation with instructions
```bash
claude "Create CLAUDE.md files in each major subdirectory (src/components, src/services, src/utils, etc.) with architecture overviews for each module. Each CLAUDE.md should document the purpose, key files, dependencies, and architecture patterns specific to that directory."
```
#### Structured approach code analysis 
- Start with root-level architecture overview
```bash
claude "Analyze this repository structure and create a main CLAUDE.md with overall architecture, then create specific CLAUDE.md files in major subdirectories"
```
- Then ask for specific subdirectory documentation
```bash
claude "Create detailed CLAUDE.md files in src/components/, src/api/, and src/utils/ directories focusing on their specific responsibilities and internal structure"
```
### Other prompts
```bash
claude "Create CLAUDE.md files in each major subdirectory (src/components, src/services, src/utils, etc.) with architecture overviews for each module. Each CLAUDE.md should document the purpose, key files, dependencies, and architecture patterns specific to that directory."
claude "Analyze this repository structure and create a main CLAUDE.md with overall architecture, then create specific CLAUDE.md files in major subdirectories"
```

### Use CC as a bash CLI
```bash
claude -p "HOw many files are in this project?"
cat data.csv | claude -p "Who won the most games"
```

### CC + Images 
- Drag directly 
- shift + cmd + 4 to capture image and ctrl + v to paste it in claude
 
### Import misc knowledge with URLs
```bash
claude Write pseudo code to describe the rules of uno based on there: https://www.unorules.com
```
- Use screenshots are feedback
- Automate feedback with Puppeteer (MCP server)
	- Let's set up Puppeteer and navigate to the game.

### Use CC as an MCP client/server
```bash
# Install the filesystem MCP server
npm install -g @modelcontextprotocol/server-filesystem
# In your project directory, tell Claude Code to connect to the MCP server
claude --mcp-server stdio://npx @modelcontextprotocol/server-filesystem $(pwd)
claude "What files are in my project? Show me the directory structure."
claude "Read my main.py file and explain what it does."
claude "Find all files that contain 'TODO' comments and list them."
claude "Create a new README.md file with a project overview based on the code you can see."

# Database MCP server
claude --mcp-server stdio://npx @modelcontextprotocol/server-sqlite /path/to/database.db
# Git MCP server  
claude --mcp-server stdio://npx @modelcontextprotocol/server-git
# Web scraping MCP server
claude --mcp-server stdio://npx @modelcontextprotocol/server-brave-search
```
### shift + tab 
- swithc modes between "auto-accept edits on", "plan mode", etc.

### Get usage
```bash
npx ccusage
claude-monitor
```
### level of thinking 
- prompt to `I want to add a support page to my app. Think harder about the implementation`
- prompt to `I want to add a support page to my app. ultrathink about the implementation`

### loop
- run the build in a loop and fix all build errors as they get reported

### clear and resume
- `clear` to clear the context 
- `resume` to restart the context of last few days


### plugins
- Combine `/` slash, subagents, MCP servers and Hooks features together
- Can be packaged or pushed to github so it can be shared with others
- Plugins make it very flexible to share claude workflow with developers
- Anthropics github plugins : `anthropics/claude-code/plugins` 
- Add marketplace, install "claude code plugins"
```bash 
/plugin marketplace add anthropics/claude-code
```
- Use agent SDK to create simple agent
```bash
/agent-sdk-dev:new-sdk-app [project_name]
```
- Create new plugin
	- Plugin marketplaces
	- To host a marketplace, all you need is a git repository, GitHub repository, or URL with a properly formatted .claude-plugin/marketplace.json
	- To use plugins from a marketplace, run /plugin marketplace add user-or-org/repo-name, then browse and install plugins using the /plugin menu.
```bash
.claude-plugin/marketplace.json
/plugin marketplace add user-or-org/repo-name
```

## References
[Claude Code Beginner Guide](https://www.youtube.com/watch?v=iYiuzAsWnHU)  
[Tips to use claude code](https://www.youtube.com/watch?v=n7iT5r0Sl_Y)  
[Claude Code pro tips](https://www.youtube.com/watch?v=TiNpzxoBPz0) 
[What makes Claude Code so damn good](https://minusx.ai/blog/decoding-claude-code/)
[claude Agent SDK python](https://github.com/anthropics/claude-agent-sdk-python) 
[Customize Claude Code with plugins](https://www.anthropic.com/news/claude-code-plugins)  
