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

## Agents

[agency-agents](https://github.com/msitarzewski/agency-agents)  
- **Personality-Driven Domain Experts**: 144+ meticulously crafted AI personas (from Frontend Wizards to Reality Checkers)
- **Production-Ready Workflows**: Each agent is built with a "Mission-First" structure that includes specific technical deliverables

[hermes-agent](https://github.com/NousResearch/hermes-agent) 
- **Self-Improving Learning Loop:** Unlike static agents, it features a built-in cycle where it autonomously creates new skills from experience, searches its own past conversation history using FTS5, and builds a persistent model of the user to improve across sessions.
- **Universal Multi-Platform Gateway:** It is uniquely designed to live where the user does, offering a unified gateway that connects a single agent process to Telegram, Discord, Slack, WhatsApp, Signal, and a full-featured Terminal UI (TUI) simultaneously.
- **Serverless Persistence & Portability:** It supports advanced terminal backends like [Daytona](https://github.com/daytonaio/daytona) and [Modal](https://www.modal.com/), allowing the agent’s entire environment to hibernate when idle and wake on demand, providing cloud-scale persistence with near-zero idle costs.
- 
[Stanford lecture on LLM agentic systems](https://www.youtube.com/watch?v=k1njvbBmfsw&t=5640s)
- **Optimizing LLMs through Prompt Engineering:** Rather than relying on resource-intensive fine-tuning, developers can significantly enhance base models using advanced prompting techniques. The lecture highlights strategies like **few-shot prompting** to align the model with specific expectations, **chain-of-thought** to break down reasoning step-by-step, and **chaining complex prompts** to separate tasks for easier debugging and control.
- **Solving Hallucinations and Knowledge Gaps with RAG:** To address base LLM limitations such as outdated knowledge, context window restrictions, and a lack of verifiable sources, the lecture details **Retrieval-Augmented Generation (RAG)**. RAG grounds the LLM by embedding external documents into a vector database, retrieving relevant context based on user queries, and feeding it to the model to generate accurate, sourced answers.
- **Building Autonomous Agentic Workflows:** The lecture explains how to transition from single-prompt applications to multi-step **agentic AI workflows**, where models act autonomously to solve complex tasks. These systems equip LLMs with **memory management** (working and archival) and **external tools** (like APIs or Model Context Protocols) to retrieve data and execute actions, sometimes even utilizing **multi-agent systems** running specialized tasks in parallel
## Research
[Karparthy Autoresearch](https://github.com/karpathy/autoresearch)  

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



