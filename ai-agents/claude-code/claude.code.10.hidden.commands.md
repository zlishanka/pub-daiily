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

## Built-in vs Bundled Skills

| Type | Examples | Notes |
|------|----------|-------|
| **Built-in commands** | `/rewind`, `/branch`, `/export`, `/remote-control`, `/cost`, `/resume`, `/diff`, `/compact` | Fixed logic, always available |
| **Bundled skills** | `/simplify`, `/loop`, `/claude-api` | Prompt-based; Claude orchestrates using its tools |
| **Custom skills** | User-created in `.claude/skills/` | Same invocation as bundled |
