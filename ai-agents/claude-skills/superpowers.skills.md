# Superpowers (plugin) 10x Claude Code

- **Superpowers plugin** for _Claude Code_ (created by _Jesse Vincent_) significantly enhances the capabilities of AI-driven software development.
- The plugin introduces an agentic framework that moves beyond simple coding tasks, enforcing a disciplined development methodology.
## What are the main project development phases?

1. **Clarify:** The agent ensures it fully understands the requirements before taking any action.
2. **Design:** This phase involves brainstorming, where the agent may provide a visual companion or interactive dashboards to align on the project's direction (1:56).
3. **Plan:** The agent creates hyper-detailed implementation plans, including specific file paths and task breakdowns (2:46).
4. **Code:** The actual implementation happens here, utilizing specialized skills such as sub-agent-driven development and parallel agent dispatching to execute tasks efficiently (2:59).
5. **Verify:** Before completion, the agent performs quality gates, including test-driven development (TDD) and systematic debugging, to ensure the output is reliable and meets the project specs (3:33).

## The 7-Phase Workflow

- **Brainstorming**: Ideation and scope definition.
- **Spec Writing**: Formalizing the plan into a technical document.
- **Spec Review**: A feedback loop to ensure the plan is sound.
- **Mockup (Visual Companion)**: Creating browser-based mockups if applicable.
- **Implementation**: Coding based on the finalized spec.
- **TDD (Test Driven Development)**: Following the "Iron Law" of testing to verify functionality.
- **Final Review**: Polishing the implementation before completion.

## The 3-Core commands

- **`brainstorm`**: Used to explore ideas and requirements before any building begins.
- **`write-plan`**: Used to design a detailed roadmap and technical specification for the task.
- **`execute-plan`**: Used to initiate the actual implementation and building phase using AI agents.
## The 14 skills

The _Superpowers_ plugin for _Claude Code_ utilizes 14 specialized skills that are triggered by a master orchestrator to manage the software development lifecycle.

**1. Orchestration**

- **Using Superpowers (1:27):** The master skill that acts as a dispatcher, analyzing your request and automatically invoking the relevant skills from the set.

**2. Design & Discovery**

- **Brainstorming (1:58, 4:18):** Helps clarify requirements by engaging in discovery and presenting options, often using a **visual companion** or dashboard to align on the project scope before coding begins.

**3. Planning**

- **Hyper-detailed Planning (2:46):** Generates granular implementation plans, identifying exact file paths and breaking tasks into 2-5 minute segments with built-in testing blocks.

**4. Execution**

- **Executing Plans (3:08):** Walks through tasks sequentially, incorporating safety stops to handle blockers effectively.
- **Sub-agent-driven Development (3:16):** Dispatches fresh sub-agents for specific tasks, each with its own review cycle.
- **Dispatching Parallel Agents (3:23):** Identifies independent problems and spins up parallel agents to work on them simultaneously.

**5. Quality & Verification**

- **Test-driven Development (TDD) (3:36):** Mandates writing tests first, watching them fail, and implementing only the necessary code to pass.
- **Systematic Debugging (3:44):** A rigorous four-phase approach involving root cause investigation, analysis, hypothesis formation, and implementation of the fix.
- **Verification (3:51):** Final validation checks before completing any task.

**6. Extensibility**

- **Writing Skills (4:00):** A meta-skill that teaches _Claude_ how to create new _Superpowers_ skills using TDD principles, allowing for system customization.


## References
[# This One Plugin Just 10x’d Claude Code](https://www.youtube.com/watch?v=4XqVR6xI6Kw)   
[The claude code plugins Every Developer Must learn](https://www.youtube.com/watch?v=yEzzBxhkUw4)   
