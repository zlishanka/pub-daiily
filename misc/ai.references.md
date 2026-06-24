## Skills

[Lenny Skills Database](https://refoundai.com/lenny-skills/)  
- **PM-domain skills, not dev workflows**: 86 product management skills (prioritization, user research, growth loops) distilled from 100+ Lenny's Podcast episodes with top PMs
- **Expertise-as-skills**: each skill encodes a specific leader's frameworks (Shreyas Doshi, Marty Cagan, Elena Verna) so Claude applies their mental models, not generic advice
[superpowers](https://github.com/obra/superpowers)  
- **Full dev methodology, not just prompts**: enforces spec → plan → TDD → subagent execution loop before touching code
- **Subagent-driven development**: spins up sub-agents per task, inspects their work, and chains autonomously for hours without drift
- **Auto-activating skills**: skills trigger on their own — no slash commands needed, just install and the agent gains the behaviors
[planning-with-files](https://github.com/othmanadi/planning-with-files)  
- **3-file markdown persistence**: stores plan, findings, and progress in files so agent memory survives context resets and `/clear`
- **Hook-driven workflow**: pre/post-tool hooks auto-reload the plan before decisions and prompt status updates after each action
- **14x benchmark improvement**: formal evals show 96.7% task completion vs 6.7% baseline — measurable, not just structural  
[llm-wiki-skill](https://github.com/sdyckjq-lab/llm-wiki-skill)
- **Knowledge Base Augmentation**: Enables LLMs to build and maintain a persistent wiki-style knowledge base, allowing agents to capture learnings and reference them across sessions
- **Context-Aware Retrieval**: Uses semantic search over accumulated knowledge to ground agent responses in documented patterns and prior solutions

[Addy Osmani's agent-skills](https://github.com/addyosmani/agent-skills)
- **Developer-Centric Agent Design**: Curated collection of skills optimized for engineering workflows, focusing on real developer productivity patterns from a performance-focused perspective
- **Composable Capability Modules**: Modular skills that can be mixed and matched to create specialized agent behaviors tailored to frontend, backend, or full-stack development tasks

[GStack:Garry Tan's exact Claude Code setup: 23 opinionated tools ](https://github.com/garrytan/gstack)  
- **Opinionated Multi-Role Framework:** It transforms Claude Code into a 23-specialist engineering team (CEO, Eng Manager, Designer, QA) using structured "Skills" that enforce professional startup workflows.
- **Comprehensive "Think-to-Ship" Lifecycle:** It manages the entire development process—from stress-testing product ideas in `/office-hours` to automated browser-based testing with `/qa` and one-command deployment via `/ship`.
- **AI-Enhanced Tooling Integration:** It features a custom "GStack Browser" with anti-bot stealth and a multi-agent coordinator (`/pair-agent`) that allows different AI models (Claude, Gemini, Codex) to collaborate in a shared browser session.

[andrej-karpathy-skills](https://github.com/forrestchang/andrej-karpathy-skills)
- **CLAUDE.md guideline for AI coding**: Framework based on Karpathy's observations about LLM pitfalls (unfounded assumptions, overcomplexity) to improve Claude Code behavior
- **Four core principles**: Think Before Coding, Simplicity First, Surgical Changes, Goal-Driven Execution—each targeting specific weaknesses in AI-assisted development

[mattpocock-real-engineer-skills](https://github.com/mattpocock/skills) 
- **Skills targeting AI-coding failure modes**: Matt Pocock's collection of small, composable Claude skills built around four problems — misalignment, verbosity, code quality, and architecture decay
- **Discipline-enforcing workflows**: `/grill-me` and `/grill-with-docs` force the agent to confirm requirements before coding, while `/tdd` and `/diagnosing-bugs` drive red-green-refactor and systematic debugging
- **Classical engineering principles**: emphasizes small deliberate steps with rapid feedback, plus a shared `CONTEXT.md` domain language to cut token waste

[Open Design: The open-source Claude Design alternative](https://github.com/nexu-io/open-design)
- **Agent-native design app**: local-first desktop tool that generates prototypes, dashboards, decks, images, and videos by driving 22+ coding agents already on your machine (Claude Code, Cursor, Copilot) — swap models with one click
- **Brand-driven outputs**: every artifact reads from a structured `DESIGN.md` spec, shipping 150 pre-built design systems modeled on Linear, Stripe, Apple, and Figma
- **Local-first & extensible**: runs entirely on your machine with zero telemetry, extended via 261 plugins and 100+ skills, Apache-2.0 licensed

[**High-performance CLI proxy that reduces LLM token consumption**](https://github.com/rtk-ai/rtk)
- **Token-killing output proxy**: single zero-dependency Rust binary that intercepts command output and compresses it before it hits the LLM context, cutting 60-90% of tokens via filtering, grouping, truncation, and dedup
- **Measured savings**: a typical 30-min Claude Code session drops from ~118K to ~24K tokens (80% less) across `git status`, test runs, and file ops
- **Transparent integration**: auto-rewrite hooks, plugin interception, or CLAUDE.md injection across 14 coding tools and 100+ commands — one `rtk init -g` to set up

[HTML Anything](https://github.com/nexu-io/html-anything)
- **Markdown/CSV/JSON/SQL → ship-ready HTML**: local-first desktop app that turns structured inputs into polished HTML through your existing coding-agent CLI — no API key needed, reuses your authenticated Claude Code/Cursor/Gemini session
- **75 composable templates**: across nine surfaces — magazine articles, keynote decks, résumés, posters, social cards, web prototypes, data reports, and video scripts
- **Design discipline built in**: live streaming render (interruptible), sandboxed iframe preview against XSS, and enforced CJK-first fonts, 8px grids, and WCAG contrast to avoid AI visual mediocrity


## Agents

[agency-agents](https://github.com/msitarzewski/agency-agents)  
- **Personality-Driven Domain Experts**: 144+ meticulously crafted AI personas (from Frontend Wizards to Reality Checkers)
- **Production-Ready Workflows**: Each agent is built with a "Mission-First" structure that includes specific technical deliverables

[hermes-agent](https://github.com/NousResearch/hermes-agent) 
- **Self-Improving Learning Loop:** Unlike static agents, it features a built-in cycle where it autonomously creates new skills from experience, searches its own past conversation history using FTS5, and builds a persistent model of the user to improve across sessions.
- **Universal Multi-Platform Gateway:** It is uniquely designed to live where the user does, offering a unified gateway that connects a single agent process to Telegram, Discord, Slack, WhatsApp, Signal, and a full-featured Terminal UI (TUI) simultaneously.
- **Serverless Persistence & Portability:** It supports advanced terminal backends like [Daytona](https://github.com/daytonaio/daytona) and [Modal](https://www.modal.com/), allowing the agent’s entire environment to hibernate when idle and wake on demand, providing cloud-scale persistence with near-zero idle costs.

[Stanford lecture on LLM agentic systems](https://www.youtube.com/watch?v=k1njvbBmfsw&t=5640s)
- **Optimizing LLMs through Prompt Engineering:** Rather than relying on resource-intensive fine-tuning, developers can significantly enhance base models using advanced prompting techniques. The lecture highlights strategies like **few-shot prompting** to align the model with specific expectations, **chain-of-thought** to break down reasoning step-by-step, and **chaining complex prompts** to separate tasks for easier debugging and control.
- **Solving Hallucinations and Knowledge Gaps with RAG:** To address base LLM limitations such as outdated knowledge, context window restrictions, and a lack of verifiable sources, the lecture details **Retrieval-Augmented Generation (RAG)**. RAG grounds the LLM by embedding external documents into a vector database, retrieving relevant context based on user queries, and feeding it to the model to generate accurate, sourced answers.
- **Building Autonomous Agentic Workflows:** The lecture explains how to transition from single-prompt applications to multi-step **agentic AI workflows**, where models act autonomously to solve complex tasks. These systems equip LLMs with **memory management** (working and archival) and **external tools** (like APIs or Model Context Protocols) to retrieve data and execute actions, sometimes even utilizing **multi-agent systems** running specialized tasks in parallel

[AutoGPT: Build, Deploy, and Run AI Agents](https://github.com/significant-gravitas/autogpt)
- **Low-code visual agent builder**: construct continuous AI agents by wiring together single-action blocks in an intuitive interface, making sophisticated automation accessible to non-technical users
- **Continuous, autonomous operation**: agents run continuously and can be triggered by external sources, rather than one-off tasks
- **Marketplace & dev ecosystem**: deploy or customize pre-built agents from an integrated marketplace, backed by Forge (custom-agent toolkit) and agbenchmark (performance testing)

[Omnigent: open-source **AI agent framework**](https://github.com/omnigent-ai/omnigent)
- **Meta-harness for multiple agents**: orchestration layer that unifies Claude Code, Codex, Cursor, Pi, and custom agents, letting you swap runtimes without rewriting code
- **Multi-agent coordination & sync**: supervisors delegate tasks across vendors (one agent reviews another's work), with sessions persisting in real time across terminals, browsers, and mobile
- **Production governance**: approval gates, spending caps, and tool-access policies at server/agent/session levels, plus disposable cloud sandboxes via Modal, Daytona, or Islo

[Openhands](https://github.com/OpenHands/openhands) 
- **Self-hosted control center for coding agents**: run OpenHands' native agent alongside Claude Code, Codex, and Gemini, switching between local, remote, and cloud backends without interrupting workflows
- **Flexible deployment**: hosts on a laptop, a dedicated Mac Mini, cloud VMs, or enterprise infra — addressing security and performance per use case
- **Always-on automations**: scheduled and event-driven workflows integrate with Slack, GitHub, Linear, and Notion; model-agnostic with bring-your-own-LLM and custom agent profiles

## Tools

[markitdown](https://github.com/microsoft/markitdown) 
- **Anything-to-Markdown for LLMs**: Microsoft's Python utility converts PDFs, Office docs, images (OCR), audio (transcription), HTML, and even YouTube URLs into Markdown — the format LLMs natively speak, keeping output semantically clear and token-efficient
- **Structure-preserving conversion**: retains headings, lists, tables, and links so downstream LLM processing keeps document semantics, with a plugin system for third-party converters
- **Enterprise extraction path**: optional Azure Document Intelligence integration for higher-quality cloud extraction beyond local processing

[headroom](https://github.com/chopratejas/headroom)
- **60-95% token reduction for agents**: compresses tool outputs, logs, RAG chunks, and conversation history before they hit the LLM, cutting cost and latency while maintaining answer quality
- **Reversible, content-aware compression**: originals are cached locally and retrievable on demand (lossless in practice), with strategies picked per content type — JSON, code (AST-aware), and free text each get their own compressor
- **Drops into any stack**: works as an inline library, transparent proxy, CLI wrapper, or MCP server with Claude/Codex/Cursor — no code changes required, all processing stays local

[MoneyPrinterTurbo](https://github.com/harry0703/MoneyPrinterTurbo)
- **Topic-to-video pipeline**: give it a keyword and it auto-generates the script, sources footage, adds subtitles and music, and renders polished HD shorts in 9:16 or 16:9 — zero manual editing
- **Model-agnostic**: works with OpenAI, Claude, Gemini, DeepSeek, and 700+ models, so you can optimize for cost or quality
- **Built for content-at-scale**: batch generation for TikTok/Reels/Shorts, deployable via one-click Windows package, Docker, or Colab

[Use Gemini Code Assist on GitHub]( https://developers.google.com/gemini-code-assist/docs/overview)
- **Free AI PR reviews on GitHub**: a GitHub app that automatically reviews pull requests with Gemini 2.5, with setup and customization of review behavior per repo
- **Full-SDLC assistant beyond GitHub**: same product covers code completion, generation, and agentic multi-step chat in VS Code, JetBrains, and Android Studio
- **Enterprise codebase awareness**: Standard/Enterprise tiers customize suggestions from private codebases and integrate with Google Cloud services (Firebase, BigQuery, Apigee)

[# Harness — The Team-Architecture Factory for Claude Code](https://github.com/revfactory/harness)
- **Factory for agent teams, not an agent itself**: say "build a harness for this project" and it generates a coordinated multi-agent architecture plus specialized skills tailored to your domain — a meta-layer that produces harnesses rather than being one
- **Six pre-built team patterns**: Pipeline, Fan-out/Fan-in, Expert Pool, Producer-Reviewer, Supervisor, and Hierarchical Delegation, so team designs don't start from scratch
- **Measured quality gains**: author-run evals across 15 software engineering tasks show average quality score up 60% (49.5 → 79.3) with structured pre-configuration

[Hoppscotch: **Open Source API Development Ecosystem**](https://github.com/hoppscotch/hoppscotch) 
- **Lightweight Postman alternative**: fast, browser-based API client for building and testing requests across REST, GraphQL, WebSocket, SSE, Socket.IO, and MQTT — no heavy desktop install required
- **Team-ready workspaces**: collections, environments, and request history with real-time collaboration, plus authentication helpers and pre-request scripting
- **Self-hostable & extensible**: open-source under MIT, deployable via Docker for full data control, with a CLI for running collections in CI pipelines

[Puppeteer: JavaScript library which provides a high-level API to control Chrome or Firefox](https://github.com/puppeteer/puppeteer) 
- **Headless browser automation**: Node.js library driving Chrome/Firefox over the DevTools Protocol to script navigation, clicks, form fills, and page interactions programmatically
- **Capture & extract**: generate screenshots and PDFs of pages, scrape rendered content, and crawl SPAs where the DOM is built client-side
- **Testing & CI staple**: automate end-to-end UI tests and reproduce user flows in a real browser, with headless mode for fast, reliable runs in pipelines

## Research
[Karparthy Autoresearch](https://github.com/karpathy/autoresearch)  
- **Overnight autonomous ML research**: an agent modifies training code, runs experiments, evaluates validation metrics, and iterates ~100 times per night — you wake up to a log of optimized models
- **Fixed 5-minute time budget**: every experiment trains exactly 5 minutes regardless of hardware, making runs directly comparable and optimizing for your actual platform rather than abstract benchmarks
- **Program the researcher, not the code**: humans steer by editing a `program.md` "research org code" file instead of Python, while the agent only touches a single `train.py` — keeping modifications reviewable and the system minimal

## Tutorials
[spelled-out intro to neural networks and backpropagation: building micrograd](https://www.youtube.com/watch?v=VMj-3S1tku0)
- **From-scratch neural nets**: Build a tiny autograd engine to understand backpropagation and gradient computation at the core level

[Deep Dive into LLMs like chatGPT](https://www.youtube.com/watch?v=7xTGNNLPyMI)
- **LLM internals demystified**: Understand transformer architecture, tokenization, and inference mechanics that power large language models

## Books
[Build a Large Language Model (From Scratch)](https://www.amazon.com/gp/product/1633437167)


## Github repo knowledge
[Lenny's Product Skills for Claude Code](https://github.com/RefoundAI/lenny-skills)  
[Darwin skillsu - Autoresearch-inspired autonomous skill optimization](https://github.com/alchaincyf/darwin-skill)   


## Github repos for learning 

[LLMs-from-scratch](https://github.com/rasbt/LLMs-from-scratch)  
[LLM Course](https://github.com/mlabonne/llm-course)  
[cracking-the-data-science-interview](https://github.com/khanhnamle1994/cracking-the-data-science-interview/tree/master)  
[Designing Machine Learning Systems](https://github.com/chiphuyen/dmls-book)    
[ML Questions](https://github.com/andrewekhalel/MLQuestions)   
[ML concepts](https://github.com/jayinai/ml-interview?tab=readme-ov-file#machine-learning)    
[MLE-Flashcards](https://github.com/b7leung/MLE-Flashcards/tree/main)    
[Quick Notes for ML, DS, MLOps, LLMOps](https://github.com/ashishtele/Quick-Notes-for-ML-DS?tab=readme-ov-file)  
[Advanced RAG Techniques: Elevating Your Retrieval-Augmented Generation Systems](https://github.com/NirDiamant/RAG_Techniques)  
[Introduction to Machine Learning Interviews Book](https://github.com/chiphuyen/ml-interviews-book)  
[Claudian plugin for obsidian](https://github.com/YishenTu/claudian)



