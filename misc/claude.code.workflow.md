## Claude code workflow
- Use plan mode first , shift + tab to switch to plan mode. Think through first and won't generate any codes. it will create a game plan . Review the plan thoroughly.
- Generate CLAUDE.md file , /init command in any directory
- Use git as checkpoint system
- Use screenshot, simply drag screenshot file to terminal as a dialog context
- Use the web link as context
- Ask to Double check its work (can you make sure it doesn't break things...)
- Select Claude model :  Opus, Sonnet, etc. If you paid $200/month, use Opus

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
- Batch creation with instructions
```bash
claude "Create CLAUDE.md files in each major subdirectory (src/components, src/services, src/utils, etc.) with architecture overviews for each module. Each CLAUDE.md should document the purpose, key files, dependencies, and architecture patterns specific to that directory."
```
- Structured approach code analysis 
	- Start with root-level architecture overview
```bash
claude "Analyze this repository structure and create a main CLAUDE.md with overall architecture, then create specific CLAUDE.md files in major subdirectories"
```
	- Then ask for specific subdirectory documentation
```bash
claude "Create detailed CLAUDE.md files in src/components/, src/api/, and src/utils/ directories focusing on their specific responsibilities and internal structure"
```
- Other prompts
```bash
claude "Create CLAUDE.md files in each major subdirectory (src/components, src/services, src/utils, etc.) with architecture overviews for each module. Each CLAUDE.md should document the purpose, key files, dependencies, and architecture patterns specific to that directory."
claude "Analyze this repository structure and create a main CLAUDE.md with overall architecture, then create specific CLAUDE.md files in major subdirectories"
```

## References
[Claude Code Beginner Guide](https://www.youtube.com/watch?v=iYiuzAsWnHU)
[Tips to use claude code](https://www.youtube.com/watch?v=n7iT5r0Sl_Y)

