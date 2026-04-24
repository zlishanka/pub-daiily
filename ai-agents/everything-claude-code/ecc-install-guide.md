# ECC Install / Uninstall Guide

Source repo: `/Users/qigong.zheng/third-party/everything-claude-code`

---

## Where Things Get Installed

| Module | Destination (Claude Code) |
|--------|--------------------------|
| Agents | `~/.claude/agents/<name>.md` |
| Skills | `~/.claude/skills/<name>/SKILL.md` |
| Commands | `~/.claude/commands/` |
| Rules | `~/.claude/rules/` |
| Hooks | `~/.claude/settings.json` (paths rewritten by installer) |

---

## CLI Entry Points

```bash
npx ecc <subcommand>        # via npm
bash ./install.sh           # shell wrapper (same flags)
pwsh .\install.ps1          # PowerShell wrapper
```

---

## Install

### By profile (named bundle)

```bash
npx ecc install --profile <name> --target claude
```

| Profile | Includes |
|---------|----------|
| `core` | rules, agents, commands, hooks, platform-configs, workflow |
| `developer` | core + framework-language, database, orchestration |
| `security` | core + security |
| `research` | core + research-apis, business-content, social-distribution |
| `full` | all 19 modules |

### By module ID (fine-grained)

```bash
npx ecc install --modules <id,id,...> --target claude
```

| Module ID | Type |
|-----------|------|
| `rules-core` | rules |
| `agents-core` | agents |
| `commands-core` | commands |
| `hooks-runtime` | hooks |
| `workflow-quality` | skills |
| `framework-language` | skills |
| `security` | skills |
| `agentic-patterns` | skills |
| `orchestration` | orchestration |
| `swift-apple` | skills |

Full list: `npx ecc plan --list-modules`

### Profile with additions / exclusions

```bash
npx ecc install --profile developer --with capability:security --without capability:database
```

Component IDs follow `<family>:<name>`:

| Family | Examples |
|--------|---------|
| `baseline` | `baseline:agents`, `baseline:hooks`, `baseline:commands` |
| `lang` | `lang:typescript`, `lang:python`, `lang:go`, `lang:swift` |
| `framework` | `framework:react`, `framework:django`, `framework:springboot` |
| `capability` | `capability:security`, `capability:database`, `capability:orchestration` |

### Via config file (`ecc-install.json`)

```json
{
  "version": 1,
  "target": "claude",
  "profile": "developer",
  "include": ["capability:security", "lang:python"],
  "exclude": ["capability:database"]
}
```

```bash
npx ecc install --config ./ecc-install.json
```

---

## Preview Before Installing

```bash
npx ecc plan --profile core --target claude        # dry-run a profile
npx ecc plan --list-profiles                        # list all profiles
npx ecc plan --list-modules                         # list all module IDs
npx ecc plan --list-components --family capability  # list components by family
npx ecc install --profile full --dry-run            # dry-run flag on installer
```

---

## Uninstall

Removes **all ECC-tracked files** for a target — no per-module flag.

```bash
npx ecc uninstall --target claude --dry-run   # preview
npx ecc uninstall --target claude             # remove
```

To effectively remove one module: re-install with a reduced profile/module list, or delete files manually from `~/.claude/`.

---

## Manual Copy (bypass installer)

Works for agents, skills, rules, and commands. **Hooks must go through the installer** (it rewrites paths).

```bash
# Single agent
cp third-party/everything-claude-code/agents/planner.md ~/.claude/agents/

# Single skill
cp -r third-party/everything-claude-code/skills/tdd-workflow ~/.claude/skills/

# Multiple skills
for s in django-patterns python-patterns laravel-patterns; do
  cp -r third-party/everything-claude-code/skills/$s ~/.claude/skills/
done

# Rules
cp -r third-party/everything-claude-code/rules/common ~/.claude/rules/
```

---

## Cross-Platform Support (Cursor, Gemini, etc.)

The installer supports multiple IDE targets beyond Claude Code:

```bash
npx ecc install --profile core --target cursor
npx ecc install --profile core --target gemini
```

Supported targets: `claude`, `cursor`, `antigravity`, `codex`, `gemini`, `opencode`, `codebuddy`

Files land in the corresponding config directory (`.cursor/`, `.gemini/`, etc.) instead of `~/.claude/`.

### What actually works per platform

| Module | Claude Code | Cursor | Gemini CLI |
|--------|-------------|--------|------------|
| **Rules** | `~/.claude/rules/` | `.cursor/rules/` | `.gemini/` |
| **Agents** | `~/.claude/agents/` | partial | limited |
| **Skills** | `~/.claude/skills/` | no `Skill` tool | no `Skill` tool |
| **Commands** | `~/.claude/commands/` | different system | different system |
| **Hooks** | full support | no | no |

**Bottom line:** ECC is built primarily for Claude Code. Rules are the most portable piece — they translate well across platforms. Agents, skills, commands, and hooks are Claude Code-specific; installing them to other targets places the files but the platforms won't use them the same way. If working primarily in Cursor or Gemini, only the `rules-core` module provides meaningful value.

---

## Diagnostics

```bash
npx ecc list-installed   # what ECC thinks is installed
npx ecc doctor           # detect missing or drifted files
npx ecc repair           # restore drifted files (dry-run: --dry-run)
```
