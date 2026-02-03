# Cursor Context

## Rules

- Rules provide system-level instructions to Agent. 
- They bundle prompts, scripts, and more together, making it easy to manage and share workflows across your team.
- Cursor supports four types of rules:
	- **Project Rules** - Stored in `.cursor/rules`
	- **User Rules** - Global to your Cursor environment. Used by Agent (Chat).
	- **Team Rules** - Team-wide rules managed from the dashboard.
	- **AGENTS.md** - Agent instructions in markdown format. Simple alternative to `.cursor/rules`. 

## How rules work

- Large language models don't retain memory between completions. Rules provide persistent, reusable context at the prompt level. 
- When applied, rule contents are included at the start of the model context. This gives the AI consistent guidance for generating code, interpreting edits, or helping with workflows.

## Project rules

- Project rules live in `.cursor/rules` as markdown files and are version-controlled. They are scoped using path patterns, invoked manually, or included based on relevance.
- Use project rules to:
	- Encode domain-specific knowledge about your codebase
	- Automate project-specific workflows or templates
	- Standardize style or architecture decisions

### Rule file structure

- Each rule is a markdown file that you can name anything you want. 
- Cursor supports .md and .mdc extensions. Use .mdc files with frontmatter to specify description and globs for more control over when rules are applied.
```bash
.cursor/rules/
  react-patterns.mdc       # Rule with frontmatter (description, globs)
  api-guidelines.md        # Simple markdown rule
  frontend/                # Organize rules in folders
    components.md
```

### Rule anatomy

- Each rule is a markdown file with frontmatter metadata and content. 
- Control how rules are applied from the type dropdown which changes properties `description`, `globs`, `alwaysApply`

| Rule Type | Description |
|-----------|-------------|
| Always Apply | Apply to every chat session |
| Apply Intelligently | When Agent decides it's relevant based on description |
| Apply to Specific Files | When file matches a specified pattern |
| Apply Manually | When @-mentioned in chat (e.g., @my-rule) |

```bash
---
globs:
alwaysApply: false
---

- Use our internal RPC pattern when defining services
- Always use snake_case for service names.

@service-template.ts
```

### Creating a rule

- Create rules using the `New Cursor Rule` command or going to `Cursor Settings > Rules, Commands`. This creates a new rule file in `.cursor/rules`. From settings you can see all rules and their status.

### Rule file format

- Each rule is a markdown file with frontmatter metadata and content. 
- The frontmatter metadata is used to control how the rule is applied. The content is the rule itself.
```bash
---
description: "This rule provides standards for frontend components and API validation"
alwaysApply: false
---

...rest of the rule content
```

## Team Rules

- Team and Enterprise plans can create and enforce rules across their entire organization from the Cursor dashboard. 
- Admins can configure whether or not each rule is required for team members.
- **Team administrators** can create and manage rules directly from the Cursor dashboard
- Once team rules are created, they automatically apply to all team members and are visible in the dashboard
	- for example, React + GraphQL , always use Apollo Hooks GraphQL queries
- Plain text: Team Rules are free‑form text. They do not use the folder structure of Project Rules and do not support metadata such as `globs, alwaysApply`, or rule types.

## Rules Precedence

- Precedence: Rules are applied in this order: **Team Rules → Project Rules → User Rules**. 

## References
[awesome-cursorrules](https://github.com/PatrickJS/awesome-cursorrules)

- 
