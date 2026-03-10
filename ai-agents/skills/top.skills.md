## Top Skills

- Anthropic made **Agent Skills** an open standard (Dec 18, 2025).
- The same Skills folder can be used in Claude Code, Codex CLI, Gemini, Cursor, etc.
- Below: top-ranked skills with core features, use cases, and public repo links.

---

### document-skills

**Core features**

- Office document support: **DOCX**, **XLSX**, **PPTX**, **PDF** creation, editing, and analysis.
- Structured, source-available reference implementations from Anthropic.
- Progressive disclosure: agents load only relevant skill content to save context.
- Self-contained skills: `SKILL.md` + optional scripts/resources per format.

**Common use cases**

- Generating and editing Word, Excel, PowerPoint, and PDF from natural language.
- Automating report and spreadsheet generation.
- Extracting and summarizing content from PDFs.
- Building document-heavy workflows (contracts, presentations, data exports).

**Public repo**

- [anthropics/skills](https://github.com/anthropics/skills) — Official Anthropic skills repo; document skills live under `skills/document-skills/` and format-specific folders (e.g. `docx`, `xlsx`, `pdf`, `pptx`).

---

### Superpowers

**Core features**

- Composable skills for **test-driven development (TDD)**, debugging, brainstorming, code review, and subagent-driven development.
- Slash commands (e.g. `/brainstorming`, `/execute-plan`) to invoke skills.
- Enforces disciplined workflows: red–green–refactor, systematic debugging, plan-vs-implementation review.
- Built-in code reviewer agent; 20+ battle-tested skills in the ecosystem.
- Strong adoption (e.g. 143k+ installs on Claude Code); Cursor install via clone + bootstrap rule.

**Common use cases**

- Running TDD cycles and structured debugging with an AI agent.
- Brainstorming and planning features before implementation.
- Automated code review against plans and standards.
- Orchestrating multi-step dev workflows (planner → executor, subagents).

**Public repos**

- [obra/superpowers](https://github.com/obra/superpowers) — Main framework.
- [obra/superpowers-skills](https://github.com/obra/superpowers-skills) — Community-editable skills (install/clone for Cursor: e.g. `~/.cursor/skills/superpowers`).

---

### planning-with-files

**Core features**

- **File-based planning**: persistent markdown files as “working memory on disk” (e.g. `task_plan.md`, `findings.md`, `progress.md`).
- Session recovery: scripts like `session-catchup.py` to catch up after context clears.
- Multi-tool support: Claude Code, Cursor, Antigravity, OpenCode.
- High benchmark pass rate (e.g. 96.7% with security audits); “2-Action Rule” to save findings regularly.

**Common use cases**

- Complex, multi-step tasks (5+ tool calls) that need state across sessions.
- Research and discovery workflows with persistent findings and progress.
- Recovering and continuing work after context or session resets.
- Keeping phases, decisions, and test results in version-controlled files.

**Public repo**

- [OthmanAdi/planning-with-files](https://github.com/OthmanAdi/planning-with-files)

---

### ui-ux-pro-max-skill

**Core features**

- **57 UI styles** (e.g. Glassmorphism, Neumorphism, Minimalism, Brutalism, Aurora UI).
- **95 color palettes**, **56 font pairings** (Google Fonts), **98 UX guidelines**, **24 chart types**, **29 landing page patterns**.
- **AI-powered Design System Generator**: analyzes requirements and outputs a tailored design system (layouts, styles, colors, typography, UX rules).
- Support for 11 tech stacks; install via `uipro init --ai cursor` (or claude/windsurf).

**Common use cases**

- Generating and refining design systems from project requirements.
- Keeping UI/UX consistent (styles, palettes, typography) across features.
- Landing pages and dashboards with predefined patterns and chart types.
- Onboarding agents to design standards without hand-writing long style guides.

**Public repo**

- [nextlevelbuilder/ui-ux-pro-max-skill](https://github.com/nextlevelbuilder/ui-ux-pro-max-skill)

---

### frontend-design

**Core features**

- **10 aesthetic archetypes**: Editorial, Swiss, Brutalist, Minimalist, Maximalist, Retro-Futuristic, Organic, Industrial, Art Deco, Lo-Fi.
- **Design token system**: CSS custom properties for colors, spacing, typography, shadows.
- Structured workflow: Context → Archetype → Differentiator → Token System → Implementation.
- Motion and interaction guidance; 5-point quality checklist before delivery.
- Aims to avoid generic “AI slop” and default purple gradients.

**Common use cases**

- Production-grade frontends with a clear, chosen aesthetic (not generic).
- Theming and design systems via tokens and archetypes.
- Consistent, intentional layout and motion across components and pages.
- Teaching agents design discipline (archetype + tokens + checklist).

**Public repo**

- [Ilm-Alan/frontend-design](https://github.com/Ilm-Alan/frontend-design) — Skill source; install via `claude plugin add anthropic/frontend-design` or copy `SKILL.md` into your skills directory.

---

### claude-scientific-skills

**Core features**

- **170+ scientific skills** across biology, chemistry, medicine, genomics, drug discovery, medical imaging, proteomics, clinical research, ML, materials science.
- **250+ integrated databases**; semantic and natural-language search (no raw API syntax required).
- Publication-ready outputs; regular updates with current methodologies.
- Works with Claude Code, Cursor, Codex, and other Agent Skills–compatible tools.

**Common use cases**

- Literature and data search across PubMed, arXiv, ChEMBL, DrugBank, bioRxiv, medRxiv, clinical trials, etc.
- Drug discovery, molecular property prediction, virtual screening, docking.
- Genomics, single-cell RNA-seq, gene networks; medical imaging and digital pathology.
- Scientific writing and methodology guidance with citation-ready structure.

**Public repos**

- [K-Dense-AI/claude-scientific-skills](https://github.com/K-Dense-AI/claude-scientific-skills) — Large, actively maintained collection (MIT).
- [yorkeccak/scientific-skills](https://github.com/yorkeccak/scientific-skills) — Natural-language scientific literature search (e.g. PubMed, arXiv) with semantic search; install via skills.sh / NPX.

---

### skill-creator

**Core features**

- **Guides for creating production-grade, reusable agent skills** (SKILL.md + optional scripts/references/assets).
- Principles: concise context (only what the agent doesn’t already know), modular structure, progressive disclosure (e.g. SKILL.md under ~500 lines, details in separate files).
- Five-step process: Understand with examples → Plan reusable contents → Initialize → Implement → Iterate.
- Works with Claude Code, Cursor, Copilot, and other AI coding assistants.

**Common use cases**

- Designing and documenting new skills for your team or product.
- Turning internal playbooks and workflows into installable skills.
- Ensuring skills are discoverable, maintainable, and context-efficient.
- Learning the Agent Skills standard by following a structured creation flow.

**Public repo**

- [skillcreatorai/Ai-Agent-Skills](https://github.com/skillcreatorai/Ai-Agent-Skills) — Universal skills installer and curated set; includes skill-creator and 40+ other skills. Install via `skills install @skillcreatorai/skill-creator` (or equivalent from SkillCreator.ai).

---

### notebooklm-skill

**Core features**

- **Query Google NotebookLM notebooks from Claude** (and compatible agents); source-grounded, citation-backed answers via Gemini.
- Browser automation and persistent authentication; library management for notebooks.
- Reduces hallucinations by constraining answers to uploaded documents.
- Typically requires local Claude Code (or similar) with network access for browser automation; not for web-only UI.

**Common use cases**

- RAG-style Q&A over your own documents (papers, notes, manuals) via NotebookLM.
- Research and summarization with citations to specific notebook sources.
- Keeping agent answers aligned with a curated knowledge base in NotebookLM.
- Multi-document reasoning without building a custom RAG pipeline.

**Public repo**

- [PleasePrompto/notebooklm-skill](https://github.com/PleasePrompto/notebooklm-skill) — Popular implementation; Python, uses a `run.py` wrapper for env and dependencies.

---

### obsidian-skills

**Core features**

- **obsidian-markdown**: Create and edit Obsidian Flavored Markdown (wikilinks, embeds, callouts).
- **obsidian-bases**: Work with Obsidian Bases (views, filters, formulas).
- **json-canvas**: Create and edit JSON Canvas files for visual note organization.
- **obsidian-cli**: Interact with vaults from the command line.
- **defuddle**: Extract clean markdown from web pages.
- Official-style skills from Obsidian (kepano); portable, Agent Skills–spec compliant; MIT licensed.

**Common use cases**

- Automating note creation, linking, and templating in Obsidian vaults.
- Building and maintaining Bases, dashboards, and JSON Canvas maps from an agent.
- Ingesting and structuring web content into vault-ready markdown.
- Scripting and bulk updates across a vault (rename, backlinks, tags).

**Public repo**

- [kepano/obsidian-skills](https://github.com/kepano/obsidian-skills) — Install via Obsidian plugin marketplace, `npx skills`, or manual copy into Claude Code / Codex / Cursor skills directories.

---

### ralph-wiggum

**Core features**

- **Autonomous iteration loop**: feed the same (or evolving) prompt to the agent until the task is done; treats context as finite “memory” and uses **state files** instead of relying only on context.
- **State files** in `.ralph/`: e.g. `state.md`, `guardrails.md`, `context-log.md`, `progress.md`; **guardrails** accumulate lessons from mistakes to avoid repetition.
- **Gutter detection**: detects when the agent is stuck and triggers a **fresh context** (new conversation) while preserving progress via **git checkpoints**.
- Context and token tracking; rate-limit handling and recovery.

**Common use cases**

- Long-running, iterative tasks (refactors, migrations, multi-file features) that outlive a single context window.
- Greenfield or well-defined projects where the agent can run with minimal human intervention.
- Avoiding “context rot” and repeated mistakes by persisting state and guardrails on disk.
- Continuous autonomous development with safe resets and rollbacks via git.

**Public repos**

- [agrimsingh/ralph-wiggum-cursor](https://github.com/agrimsingh/ralph-wiggum-cursor) — Cursor-oriented implementation.
- [harrymunro/ralph-wiggum](https://github.com/harrymunro/ralph-wiggum) — Claude Code–focused implementation of the Ralph Wiggum loop.
