# Everything Claude Code (ECC) — Repository Overview

> Version 1.10.0 — A production-ready Claude Code plugin providing agents, skills, commands, rules, hooks, and scripts for AI-assisted software development.

---

## Mental Model

ECC is a complete **agent harness system** layered on top of Claude Code. It provides:
- Specialized **agents** for delegation
- Reusable **skills** for domain knowledge
- User-facing **commands** (slash commands) to trigger workflows
- Always-follow **rules** by language
- Event-driven **hooks** for automated quality gates
- Cross-platform **scripts** powering the runtime engine

**Core philosophy:** Agent-first delegation → plan before code → test-driven (80%+ coverage) → security-first → hooks enforce quality automatically.

---

## IDE Support

First-class integrations for: Claude Code (`.claude/`), Cursor (`.cursor/`), CodeX (`.codex/`), OpenCode (`.opencode/`), Gemini (`.gemini/`), Trae (`.trae/`), Kiro (`.kiro/`), CodeBuddy (`.codebuddy/`).

---

## Module Breakdown

### 1. Agents (48 agents)

Specialized subagents that handle domain-specific tasks via delegation. Each is a markdown file with YAML frontmatter (name, description, tools, model).

| Category | Agents |
|----------|--------|
| **Core workflow** | planner, code-reviewer, tdd-guide, architect, doc-updater |
| **Security** | security-reviewer |
| **Build** | build-error-resolver, cpp-build-resolver, go-build-resolver, kotlin-build-resolver, java-build-resolver, rust-build-resolver, pytorch-build-resolver |
| **Language reviewers** | typescript-reviewer, python-reviewer, go-reviewer, rust-reviewer, java-reviewer, kotlin-reviewer, cpp-reviewer, csharp-reviewer |
| **Testing** | e2e-runner |
| **Database** | database-reviewer |
| **Autonomous ops** | loop-operator, harness-optimizer |
| **Code quality** | code-explorer, code-simplifier, comment-analyzer, refactor-cleaner, silent-failure-hunter |
| **Specialized** | seo-specialist |

---

### 2. Skills (183 skills)

Reusable domain knowledge and workflow patterns. Each lives in `skills/<name>/SKILL.md` with YAML frontmatter.

| Category | Examples |
|----------|---------|
| **Dev workflows** | tdd-workflow, verification-loop, e2e-testing, ai-regression-testing, continuous-agent-loop |
| **TypeScript/JS** | nestjs-patterns, frontend-patterns, backend-patterns, apollo-client-patterns |
| **Python** | python-patterns, django-patterns, django-security, django-tdd |
| **Go** | golang-patterns, golang-testing |
| **Rust** | rust-patterns, rust-testing |
| **Java** | java-coding-standards, jpa-patterns, springboot-patterns, springboot-security, springboot-tdd |
| **Kotlin** | kotlin-patterns, kotlin-ktor-patterns, kotlin-coroutines-flows, kotlin-exposed-patterns |
| **PHP** | laravel-patterns, laravel-security, laravel-tdd |
| **Swift** | swift-actor-persistence, swiftui-patterns, swift-concurrency-6-2 |
| **Architecture** | api-design, api-connector-builder, architecture-decision-records, blueprint, mcp-server-patterns |
| **Agentic/AI-first** | agentic-engineering, ai-first-engineering, autonomous-loops, claude-api, continuous-learning-v2, council |
| **Domain: Healthcare** | healthcare-phi-compliance, hipaa-compliance |
| **Domain: Finance** | finance-billing-ops, customer-billing-ops |
| **Domain: Operations** | google-workspace-ops, project-flow-ops, automated-audit-ops, terminal-ops, knowledge-ops |
| **Content/Publishing** | article-writing, content-engine, market-research, brand-voice, social-graph-ranker, manim-video, remotion-video-creation |
| **Integrations** | github-ops, jira-integration, exa-search, fal-ai-media, videodb |

---

### 3. Commands (79 slash commands)

User-facing `/command` shortcuts that orchestrate agents and skills into workflows.

| Category | Commands |
|----------|---------|
| **Core workflow** | `/plan`, `/tdd`, `/code-review`, `/build-fix`, `/verify`, `/quality-gate` |
| **Testing** | `/e2e`, `/test-coverage`, `/go-test`, `/kotlin-test`, `/rust-test`, `/cpp-test` |
| **Language review** | `/python-review`, `/go-review`, `/typescript-review`, `/rust-review`, `/java-review`, `/kotlin-review`, `/cpp-review` |
| **Language build** | `/cpp-build`, `/go-build`, `/kotlin-build`, `/java-build`, `/rust-build`, `/flutter-build` |
| **Advanced** | `/harness-audit`, `/loop-start`, `/loop-status`, `/evolve`, `/gan-build` |
| **Utility** | `/checkpoint`, `/devfleet`, `/docs`, `/eval`, `/feature-dev`, `/aside`, `/agent-sort` |

---

### 4. Rules (89 files)

Always-follow guidelines organized by language. Common rules apply universally; language-specific rules extend them.

**`rules/common/`** (universal):
- `security.md` — No hardcoded secrets, input validation, SQL injection / XSS / CSRF prevention
- `testing.md` — 80% minimum coverage, unit + integration + E2E required, TDD mandatory
- `coding-style.md` — Immutability (critical), files <800 lines, functions <50 lines, no deep nesting
- `git-workflow.md` — Conventional commits, small focused PRs
- `development-workflow.md` — Plan before code, delegate to agents, validate at boundaries
- `agents.md`, `hooks.md`, `patterns.md`, `performance.md`, `code-review.md`

**Language-specific rule sets:**
`typescript`, `python`, `golang`, `java`, `kotlin`, `rust`, `cpp`, `csharp`, `dart`, `swift`, `php`, `perl`, `web`, `zh` (Chinese)

---

### 5. Hooks (~20 active hooks)

Event-driven automations that fire before/after tool executions. Enforces quality gates without user intervention.

| Phase | Hook | Purpose |
|-------|------|---------|
| **PreToolUse** | dev-server blocker | Prevents `npm run dev` outside tmux |
| **PreToolUse** | pre-commit quality check | Lints staged files, validates commit messages |
| **PreToolUse** | secret detection | Blocks accidental secret commits |
| **PreToolUse** | config protection | Blocks modifications to linter/formatter configs |
| **PreToolUse** | governance capture | Tracks policy violations |
| **PreToolUse** | MCP health check | Validates MCP server connectivity |
| **PreToolUse** | pre-bash dispatcher | Consolidated quality/tmux/push/GateGuard checks |
| **PostToolUse** | prettier format | Auto-formats JS/TS files after edits |
| **PostToolUse** | TypeScript check | Runs `tsc --noEmit` after edits |
| **PostToolUse** | build analysis | Background build error analysis |
| **PostToolUse** | PR logger | Logs PR creation and review command |
| **PostToolUse** | console.log warning | Warns about debug statements left in code |
| **PostToolUse** | design quality check | Warns about generic/template UI drift |
| **Lifecycle** | SessionStart / SessionEnd | Session boundary tracking |
| **Lifecycle** | Stop | End-of-response processing |
| **Lifecycle** | PreCompact | Before context compaction |

---

### 6. Scripts (136+ files)

Cross-platform Node.js utilities powering installation, orchestration, validation, and hook runtime.

| Category | Key Scripts |
|----------|------------|
| **Install/Setup** | `install.sh`, `install.ps1`, `install-plan.js`, `install-apply.js`, `setup-package-manager.js` |
| **Validation** | `catalog.js`, `harness-audit.js`, `doctor.js`, `repair.js`, `uninstall.js` |
| **Orchestration** | `orchestrate-worktrees.js`, `sessions-cli.js`, `tmux-worktree-orchestrator.js`, `orchestration-status.js` |
| **Hook runtime** | `pre-bash-dispatcher.js`, `doc-file-warning.js`, `governance-capture.js`, `mcp-health-check.js` |
| **CI validators** | `validate-agents.js`, `validate-commands.js`, `validate-rules.js`, `validate-skills.js`, `validate-hooks.js` |
| **Shared libs** | `lib/utils.js`, `lib/package-manager.js`, `lib/project-detect.js`, `lib/session-manager.js` |
| **CLI entry** | `ecc.js`, `status.js`, `list-installed.js`, `skills-health.js` |

---

### 7. Tests (127 test files)

Multi-language test suite (Node.js + Python) using Node's native `assert` module with a custom `test(name, fn)` runner.

| Directory | Count | What's Tested |
|-----------|-------|---------------|
| `tests/lib/` | 27 | Agent compression, install workflows, session management, package manager, orchestration, skill operations |
| `tests/hooks/` | 25 | Hook behavior: bash dispatcher, config protection, quality gate, session tracking, dev server blocking, governance capture |
| `tests/scripts/` | 30 | install-plan/apply, repair, doctor, uninstall, skill-create-output, harness-audit, catalog, session-inspect |
| `tests/ci/` | 3 | CI validators, GitHub Actions security (workflow_run event), agent YAML schema |
| `tests/integration/` | 1 | End-to-end hook integration |
| `tests/docs/` | 2 | continuous-learning-v2 docs schema, install identifiers |
| **Root Python tests** | 4 | LLM message construction, tool execution (ToolRegistry/ToolExecutor), resolution logic, type definitions |

**Testing patterns:** subprocess validation via `spawnSync`/`execFileSync`, temp directory isolation, JSON schema validation, path traversal prevention, exit code verification.

---

### 8. Contexts (3 files)

Mode-specific behavioral guides that shape Claude's operating mode:

| File | Mode | Focus |
|------|------|-------|
| `contexts/dev.md` | Active Development | Code first, explain after; run tests after changes; atomic commits |
| `contexts/research.md` | Exploration | Read wide → clarify → hypothesize → verify → summarize; no code until understood |
| `contexts/review.md` | Code Review | Severity-first (critical → high → medium → low); logic, security, performance, coverage |

---

### 9. Assets (37 files)

Visual and media resources for documentation and marketing.

| Directory | Contents |
|-----------|---------|
| `assets/images/shortform/` | 14 files — social/short-form content: feature demos (command chaining, PostToolUse hooks, tmux `.mp4`), IDE integrations (Zed, VS Code), hackathon announcement |
| `assets/images/longform/` | 10 files — long-form doc graphics: session storage, model selection, pricing table, mgrep benchmark, parallel execution, 25k stars milestone |
| `assets/images/security/` | 10 files — security guide visuals: attack vectors/chain, sandboxing concepts, sanitization flows, observability architecture |
| `assets/images/guides/` | 2 files — quick reference cards: shorthand guide, longform guide |
| Root | `hero.png` (main banner), `ecc-logo.png` |

---

## Key Configuration Files

| File | Purpose |
|------|---------|
| `CLAUDE.md` | Claude Code project guidance |
| `AGENTS.md` | Agent instructions and orchestration guide |
| `package.json` | NPM package metadata (v1.10.0, ecc-universal) |
| `.mcp.json` | MCP server configurations |
| `eslint.config.js` | ESLint flat config |
| `.prettierrc` | Prettier formatter config |
| `commitlint.config.js` | Conventional commit validation |
| `schemas/` | JSON schema definitions |
| `manifests/` | Installation manifests per IDE target |
| `mcp-configs/` | MCP server configuration templates |

---

## Key Documentation

| File | Description |
|------|-------------|
| `README.md` (68 KB) | Main docs with language translations |
| `the-shortform-guide.md` | Quick setup and philosophy |
| `the-longform-guide.md` | Token optimization, memory, evals |
| `the-security-guide.md` | Attack vectors and sandboxing |
| `COMMANDS-QUICK-REF.md` | Command reference |
| `CONTRIBUTING.md` | Contribution guidelines |
| `TROUBLESHOOTING.md` | Common issues and fixes |
| `CHANGELOG.md` | Version history |
