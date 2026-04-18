Based on the technical breakdown provided in the post by [万有引力AI](https://www.xiaohongshu.com/explore/69d03fda0000000022001803), here is a summary of how **Claude Code** manages its memory system.

## ---

**🧠 Claude Code Memory Architecture Summary**

Claude Code utilizes a sophisticated, **5-layer architecture** to balance long-term retention with the technical limits of LLM context windows.

### **1\. The 5-Layer Hierarchy**

The system organizes information from user-defined rules to automated background learning:

* **CLAUDE.md:** User-controlled configuration for coding styles, preferences, and SOPs. It is loaded immediately and injected as raw text.  
* **Session Memory:** A structured Markdown format managed by a background Agent. It summarizes the current conversation once the context window reaches \~85% capacity.  
* **Conversation History:** Stored in JSONL format, keeping a record of all user queries and Claude's responses (capped at 100 items per project).  
* **Team Memory:** Shared memory synced via servers for collaborative environments.  
* **Auto Memory:** The "core" of the system. It learns roles, preferences, and project context across multiple sessions, stored locally as .md files with YAML frontmatter.

### ---

**2\. The Memory Lifecycle (Writing)**

The "Auto Memory" doesn't just record everything; it follows a three-stage process:

1. **Extraction:** After each round, a background Agent identifies "high-value" information.  
2. **Integration (autoDream):** Periodically, the system triggers a process to merge duplicate entries and correct outdated information.  
3. **Conflict Resolution:** Memories do not have a set expiration date; they are only modified or deleted if a direct contradiction is detected in newer interactions.

### ---

**3\. Smart Retrieval & Context Management**

To prevent "context stuffing," Claude Code is highly selective about what it remembers during a chat:

* **Strict Limits:** The memory index is restricted to **200 lines or 25KB**.  
* **Relevance Filtering:** Using the Claude 3.5 Sonnet model, the system filters all available memories and only injects the **top 5 most relevant** pieces of information into the current context.  
* **Auto-Exclusion:** To save space, any information already displayed or used in the current session is automatically excluded from the retrieval prompt.

### ---

**4\. Security & Guardrails**

The system implements a triple-layer defense to ensure memory isn't abused:

* **Path Locking:** Global locking of storage paths to prevent unauthorized file access.  
* **Permission Interception:** Model-level checks to ensure the AI doesn't perform "illegal" memory operations.  
* **Sandbox Whitelisting:** Verification via a sandbox environment to ensure memory actions stay within project boundaries.

**Key Takeaway:** Claude Code's memory isn't just a database; it's an **active management system** that uses "background agents" to summarize, filter, and clean data so the model stays sharp without hitting token limits.