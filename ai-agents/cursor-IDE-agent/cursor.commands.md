# Cursor Commands

- Custom commands allow you to create reusable workflows that can be triggered with a simple `/` prefix in the chat input box.
- These commands help standardize processes across your team and make common tasks more efficient.

## How commands work
- **Project commands** : `.cursor/commands` directory of project
- **Global commands** : `~/.cursor/commands` 
- **Team commands** :  created by team admins

## Creating commands

- Create `.cursor/commands` directory in project root
- Add `.md` files with descriptive names (e.g., `review-code.md`, `write-tests.md`)
- Write plain Markdown content describing what the command should do
- Commands will automatically appear in the chat when you type `/`

```bash
.cursor/
└── commands/
    ├── address-github-pr-comments.md
    ├── code-review-checklist.md
    ├── create-pr.md
    ├── light-review-existing-diffs.md
    ├── onboard-new-developer.md
    ├── run-all-tests-and-fix.md
    ├── security-audit.md
    └── setup-new-feature.md
```



## References
- [How commands work](https://cursor.com/docs/context/commands#how-commands-work)  
- [Examples of commands](https://cursor.com/docs/context/commands#examples)  
