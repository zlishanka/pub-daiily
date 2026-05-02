## Claude Code Hidden Commands

---

### `/btw`
**What it is:** Ask a quick side question without adding it to conversation history.

**Use cases:**
- Quick clarifications while Claude is working on something else
- Fast lookups about context already loaded in the session

**Example:**
```
/btw what was that config file name we used earlier?
/btw should I use async/await or promises here?
```

---

### `/rewind`
**What it is:** Rewind conversation and file changes back to a previous checkpoint. Keyboard shortcut: `Esc` + `Esc`.

**Use cases:**
- Undo changes that broke something
- Try an alternative approach while preserving prior work
- Free up context by summarizing portions of history

**Example:**
```
/rewind   # Opens interactive menu: restore code, restore conversation, or summarize from here
```

> **Tip:** "Summarize from here" compresses messages forward — it doesn't undo. Checkpoints persist for 30 days.

---

### `/insights`
**What it is:** Generate a report analyzing your Claude Code session patterns, usage statistics, and friction points.

**Use cases:**
- Understand where you spend most time across projects
- Track daily usage, streaks, and model preferences
- Identify interaction patterns to improve workflow

**Example:**
```
/insights   # Displays session history, daily visualization, and usage analytics
```

---

### `/model opusplan`
**What it is:** A hybrid model mode — uses **Opus** for planning/reasoning, then auto-switches to **Sonnet** for execution. Best reasoning + efficient code generation.

**Use cases:**
- Complex architectural decisions requiring deep reasoning
- Large multi-step implementation tasks
- Cost-effective way to get Opus-level planning without paying Opus rates for all tokens

**Example:**
```
/model opusplan   # Enters plan mode with Opus; switches to Sonnet for code generation

# Other model aliases:
/model sonnet
/model opus
/model haiku
```

> Available on Max, Team, and Enterprise plans.

---

### `/simplify`
**What it is:** A bundled skill that reviews recently changed files for code reuse, quality, and efficiency — then auto-fixes issues. Spawns 3 review agents in parallel.

**Use cases:**
- Post-implementation cleanup before a PR
- Catching duplicated logic or inefficient patterns
- Code quality pass after a big feature

**Example:**
```
/simplify
/simplify focus on memory efficiency
/simplify look for duplicate functions
```

---

### `/branch`
**What it is:** Fork the current conversation at this point into a new parallel session. Also aliased as `/fork`.

**Use cases:**
- Explore alternative implementations without losing current work
- Try a different approach and compare results
- Preserve the original session while experimenting

**Example:**
```
/branch                      # Auto-generates branch name
/branch auth-alt-approach    # Named branch
```

> **vs `/rewind`:** `/branch` creates a new parallel session; `/rewind` goes back in the same session.

---

### `/loop`
**What it is:** A bundled skill that runs a prompt (or slash command) on a recurring interval while your session stays open.

**Use cases:**
- Poll deployment or CI status periodically
- Monitor long-running builds without babysitting
- Re-run a review workflow on a schedule

**Example:**
```
/loop 5m check if the deployment finished
/loop 30m /review-pr 1234
remind me in 45 minutes to push the release branch
```

> Default interval is 10 minutes. Sessions support up to 50 scheduled tasks. Tasks auto-expire after 3 days.

---

### `/remote-control`
**What it is:** Enable control of your local Claude Code session from another device via browser or the Claude mobile app. Short form: `/rc`.

**Use cases:**
- Start work on desktop, continue on mobile
- Monitor long-running tasks remotely
- Use your full local environment (MCP servers, tools, config) from any device

**Example:**
```
/remote-control                  # Generates a URL + QR code to connect
/rc My Project Name              # Named session, findable in claude.ai/code

# Or from CLI:
claude --remote-control
claude --rc
```

> Requires Claude Code v2.1.51+, Pro/Max/Team/Enterprise plan, and claude.ai authentication.

---

### `/export`
**What it is:** Export the current conversation as plain text to a file or clipboard.

**Use cases:**
- Save conversations for documentation or compliance records
- Share a session log with teammates
- Archive important architecture discussions

**Example:**
```
/export                      # Opens dialog: copy to clipboard or save to file
/export my-session.txt       # Writes directly to file
```

---

## Other Popular Commands Worth Knowing

### `/compact`
**What it is:** Compress the entire conversation into a summary to free up context space.

```
/compact
/compact with focus on the database schema changes
```

> Use when context is getting full during long exploratory sessions.

---

### `/diff`
**What it is:** Open an interactive diff viewer showing uncommitted changes and per-turn diffs.

```
/diff   # Browse what Claude changed, turn by turn
```

> Useful for reviewing changes before committing. Navigate with arrow keys.

---

### `/resume`
**What it is:** Resume a previous conversation by name, ID, or interactive picker.

```
/resume                      # Interactive picker with search
/resume my-feature-session   # Resume by name
claude --resume my-feature   # From CLI before starting
```

> Sessions are grouped by git branch in the picker. Press `B` to filter to current branch.

---

### `/cost`
**What it is:** Display token usage and estimated cost for the current session.

```
/cost   # Shows input/output tokens and model-specific cost breakdown
```

> Handy for monitoring spend on long sessions or comparing model costs.

---

### `/doctor`
**What it is:** Run a health check on your Claude Code installation — verifies config, auth, and environment.

```
/doctor   # Diagnoses common setup issues
```

> First thing to run when something isn't working right.

---

### `/plan`
**What it is:** Switch into **Plan mode** — Claude outlines and reasons through the approach before making edits. Use when you want a structured plan, architecture sketch, or step list first.

**Use cases:**
- Large or ambiguous tasks where you want alignment before code changes
- Reviewing tradeoffs and sequencing before implementation
- Pair with `/code` when you’re ready to execute

**Example:**
```
/plan   # Enter plan mode (keyboard: Shift+Tab repeatedly to cycle modes, depending on version)
```

> **Tip:** Plan mode reduces surprise edits; switch to `/code` when you want normal implementation flow.

---

### `/code`
**What it is:** Switch into **Code mode** (standard implementation) — Claude applies changes and runs tools as usual. Exits plan-only / “think first” style behavior.

**Use cases:**
- After `/plan`, when the plan is agreed and you want execution
- Returning to normal agent behavior if you were stuck in a planning-only flow

**Example:**
```
/code   # Enter standard code / execution mode
```

> **Tip:** Same mode toggles are often available via **Shift+Tab** in the UI; slash commands are explicit and scriptable.

---

### `/context`
**What it is:** Display current context window usage — shows how many tokens are loaded and what's consuming them.

**Use cases:**
- Checking how much headroom you have before hitting limits
- Diagnosing why responses feel slow or degraded (context bloat)
- Deciding whether to `/clear` or `/compact` before starting a big task

**Example:**
```
/context   # Show token usage breakdown for the current session
```

> **Tip:** Run this before long tasks to baseline your context. If you're already at 60–70%, consider clearing first.

---

### `/clear`
**What it is:** Wipe the entire conversation history and start a fresh session.

**Use cases:**
- Starting a new, unrelated task — old context only hurts you
- Recovering from a confused or degraded session
- Freeing up tokens when you're near the limit

**Example:**
```
/clear   # Nuke conversation history; Claude starts fresh
```

> **Tip:** Use `/clear` for simple reboots and use `/compact` if you want a summary preserved instead of a full wipe. Every time you start something new, clear the chat.

---

### `/agents`
**What it is:** Manage subagent configurations — view, create, or configure specialized Claude instances that handle scoped sub-tasks.

**Use cases:**
- Viewing what agents are defined in `.claude/agents/`
- Setting up agents for parallel workstreams (e.g., a test-runner agent, a research agent)
- Keeping your main session's context clean by delegating isolated work

**Example:**
```
/agents   # Open agent management interface
```

> **Tip:** Subagents are powerful for context isolation — farm out work to specialized agents that return only final answers, keeping your main context clean. Don't overuse them; if you make a PythonTests subagent, you've hidden all testing context from your main agent, which can no longer reason holistically about a change.

---

### `/chrome`
**What it is:** Configure and launch the Chrome browser integration — opens an isolated Claude instance with Chrome DevTools MCP attached.

**Use cases:**
- Debugging UI bugs, checking console errors, or inspecting network requests
- Running browser-based tests without polluting your main session's context
- Any task requiring real browser interaction (screenshots, performance traces, auth flows)

**Example:**
```
/chrome check the homepage for errors
/chrome test the dashboard and verify widgets load
```

> **Tip:** Chrome DevTools MCP adds ~20k tokens of tool definitions to context. Isolating it in `/chrome` keeps that overhead out of your main session — each invocation launches, completes its task, and closes.

---

### `/permission`
**What it is:** Cycle through permission modes mid-session to control how aggressively Claude asks for approval before running tools. Keyboard shortcut: `Shift+Tab`.

**Use cases:**
- Switching to acceptEdits to auto-approve file edits while still being prompted for shell commands
- Dropping into plan mode to make Claude propose actions without executing them
- Tightening back up after a burst of autonomous work

**Permission Modes:**
- default — prompts on first use of each tool type
- acceptEdits — auto-approves all file modifications but still prompts for shell commands
- plan — propose actions without executing
- auto — appears when account meets requirements (not in default cycle)
- bypassPermissions — appears only after starting with appropriate flag (not in default cycle)

**Example:**
```
Shift+Tab   # Cycle modes; current mode shown in status bar
/permission   # Open permission mode selector
```

> **Tip:** Your current permission mode is always visible in the status bar. Use Shift+Tab to quickly cycle through available modes or `/permission` to open the interactive selector.

---

## Built-in vs Bundled Skills

| Type | Examples | Notes |
|------|----------|-------|
| **Built-in commands** | `/rewind`, `/branch`, `/export`, `/remote-control`, `/cost`, `/resume`, `/diff`, `/compact`, `/plan`, `/code` | Fixed logic, always available |
| **Bundled skills** | `/simplify`, `/loop`, `/claude-api` | Prompt-based; Claude orchestrates using its tools |
| **Custom skills** | User-created in `.claude/skills/` | Same invocation as bundled |
