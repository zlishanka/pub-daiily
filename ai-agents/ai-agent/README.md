# AI Agent — Documentation

Conceptual and practical documentation for **AI agents**: definitions, levels (LLM+Tools, workflows, in-the-loop), tool use, workflow design patterns, and automated feedback with evals.

---

## Contents index

| File | Summary |
|------|---------|
| [ai.agent.intro.md](ai.agent.intro.md) | **Introduction** — What an AI agent is (OpenAI, Hugging Face, Anthropic); three key features (LLM, tools, autonomy); why agents matter; three levels (LLM+Tools, LLM Workflow, LLM in a loop); perceive → decide → act; use cases. |
| [ai.agent.improve.llm.with.tools.md](ai.agent.improve.llm.with.tools.md) | **Tool use** — How tool-use works (monitor output, execute, feed back); prompting vs API/fine-tuning; OpenAI Agents SDK example (YouTube transcript agent with `@function_tool`). |
| [ai.agent.llm.workflows.md](ai.agent.llm.workflows.md) | **LLM workflows** — Workflows vs rule-based code; agentic workflows; design patterns (chaining, routing, parallelization, orchestrator-workers, evaluator-optimizer); AVA example with Planner + Executor and Runner. |
| [ai.agent.llm.in.the.loop.md](ai.agent.llm.in.the.loop.md) | **LLM in a loop** — Refining outputs with feedback; automating feedback with evals; three eval types (rule-based, LLM-based, real-world); Upwork profile refinement example; limitations (reward hacking). |

---

## Quick reference

### What is an AI agent?
- A program that **acts on its own** to reach a goal, with an **LLM** at the center, **tools** to interact with the world, and **autonomy** (plan, reason, reflect).

### Three levels of agents

| Level | Description |
|-------|-------------|
| **LLM + Tools** | Single LLM with tools: search, code interpreter, APIs, computer use, RAG, memory. |
| **LLM Workflow** | Predefined steps with one or more LLMs: chaining, routing, parallelization, orchestrator-worker, evaluator-optimizer. |
| **LLM in a loop** | LLM gets **real-world or automated feedback** on outputs and iterates until satisfactory (evals, RL). |

### Tool-use mechanics
- **Loop**: Monitor LLM output for tool calls → Pause → Execute tool (code) → Pass result back to model.
- **How the model knows**: Prompting (describe tools in text) or API/fine-tuning (structured tool schema, stop inference for tool call).

### Eval types (for “LLM in a loop”)

| Type | Examples |
|------|----------|
| **Rule-based** | Binary: error raised, format, contains; Continuous: length, faithfulness, ROUGE/BLEU, readability. |
| **LLM-based** | Judge LLMs for flexible assessment and improvement guidance. |
| **Real-world** | CTR, conversions, user satisfaction (needs data integration). |

### Workflow design patterns
Chaining → Routing → Parallelization → Orchestrator-workers → Evaluator-optimizer.

---

## Reading order

1. **Concepts first**: [ai.agent.intro.md](ai.agent.intro.md).
2. **Tool use in practice**: [ai.agent.improve.llm.with.tools.md](ai.agent.improve.llm.with.tools.md).
3. **Multi-step workflows**: [ai.agent.llm.workflows.md](ai.agent.llm.workflows.md).
4. **Feedback and evals**: [ai.agent.llm.in.the.loop.md](ai.agent.llm.in.the.loop.md).
