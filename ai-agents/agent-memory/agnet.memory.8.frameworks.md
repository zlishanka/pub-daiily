# Eight agent memory frameworks (summary)

Source: [Best AI Agent Memory Systems in 2026: 8 Frameworks Compared](https://vectorize.io/articles/best-ai-agent-memory-systems) (Vectorize, March 2026).

## Why memory matters

Most agents are **stateless** unless you add a memory layer. Without it, sessions reset; users repeat preferences; **institutional knowledge** (rules learned from corrections, vendor quirks, evolving facts) never compounds. Context windows alone do not persist or structure knowledge.

The article separates two needs:

- **Personalization** — session continuity, user prefs, chat history.
- **Institutional knowledge** — extracted facts, entities, relationships, lessons across runs (harder; separates “demo” from production workflows).

You likely need a memory system if the agent runs **repeatedly** in one domain, humans **correct** it and those fixes should stick, **rules change over time**, or you pay heavily re-sending the same context every call.

## How memory systems work (four moves)

1. **Ingestion** — extract facts, resolve entities, timestamps, embeddings (not raw chat dumps).
2. **Storage** — vectors, graphs, keyword indexes, temporal metadata (mix varies by product).
3. **Retrieval** — similarity search, BM25, graph walks, time filters; often **multi-strategy + rerank**.
4. **Synthesis** — optional LLM step to **reason across** retrieved facts (adds latency).

Good designs usually **pay on write** (extraction, indexing) so **reads stay fast**.

## Quick comparison (8 frameworks)

| Framework | Memory focus | Architecture (high level) | OSS | Notes |
| --- | --- | --- | --- | --- |
| **Mem0** | Personalization + some institutional | Vector + graph (graph often Pro) | Apache 2.0 | Large ecosystem; managed tiers; graph gated on higher tier |
| **Hindsight** | Both; institutional-first | Multi-strategy hybrid + synthesis (`reflect`) | MIT | Semantic + BM25 + graph + temporal; Vectorize |
| **Letta** (ex-MemGPT) | Both | Tiered “OS-like” context (core / recall / archival) | Apache 2.0 | Full **runtime**; agents self-edit memory blocks |
| **Zep / Graphiti** | Both; strong **temporal** KG | Temporal knowledge graph | Graphiti open | Zep Cloud for full product; validity windows for facts |
| **Cognee** | Institutional | KG + vector; rich ingestion | Open core | Multimodal; local-friendly defaults |
| **SuperMemory** | Personalization + some institutional | Memory + RAG + profiles | Closed | Single API; generous free tier cited |
| **LangMem** | Personalization | Flat KV + vector (LangGraph store) | MIT | **LangGraph-centric** |
| **LlamaIndex Memory** | Personalization | Composable buffers / vectors | MIT | **LlamaIndex-centric**; not a standalone service |

## Choosing (compressed)

- Need **institutional** learning and robust retrieval → prioritize **Hindsight, Letta, Zep, Cognee** (Mem0/SuperMemory more personalization-leaning; graph/extraction tiers vary).
- Need **temporal** “who was X when?” → **Zep / Graphiti**.
- Want **agent-managed** context tiers → **Letta**.
- Want **biggest community / integrations** → **Mem0**.
- Already on **LangGraph** / **LlamaIndex** → **LangMem** / **LlamaIndex Memory** (expect **ecosystem lock-in**).

**Caveats from the article:** benchmark leaders (**LoCoMo**, **LongMemEval**) stress **conversational** recall—not yet whether memory improves **task outcomes** over many runs. Treat scores as a shortlist signal; evaluate on **your** workflows. **“Memory”** products differ wildly (buffer vs vector vs graph vs multi-strategy).

## Related

- Full write-up, code snippets, pricing notes, and pitfalls: [vectorize.io article](https://vectorize.io/articles/best-ai-agent-memory-systems).
