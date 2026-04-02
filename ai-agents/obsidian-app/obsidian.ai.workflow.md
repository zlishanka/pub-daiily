# Obsidian AI Workflow Guide

The central philosophy when integrating AI into Obsidian: balance the power of automation with protecting your personal idea verse so your own voice isn't drowned out.

---

## The IDI Framework

A safe, structured way to interact with AI inside your vault:

| Step | Action |
|------|--------|
| **Imagine** | Use AI to spark new possibilities and generate ideas |
| **Discern** | Review AI output — separate what is accurate and useful from what is not |
| **Integrate** | Manually connect valuable insights to your current projects and goals |

---

## The Barbell Approach

### Playing Defense
Protect your vault from AI overgeneration:
- Create a dedicated **"AI zone"** folder or a fully separate vault for AI-generated content
- This wall of "good friction" forces you to manually copy over only the insights you truly value into your main, sacred thinking space

### Playing Offense
Use AI for targeted, high-value tasks:
- Reflect on themes from your past 45 days of daily notes
- Track how often you use specific concepts across the vault
- Automatically search the web to grab images and populate metadata for notes on specific people
- Deep research pipelines to synthesize external sources into your vault

---

## Document Synthesis Pipeline

For messy folders of PDFs, annual reports, or JSON files:

1. Claude Code organizes files by type
2. Passes thick documents to an API with a large context window (e.g. Gemini) for extraction
3. Synthesizes key points into clean markdown cheat sheets
4. Imports them safely into Obsidian

---

## Conversational & Daily Logging

Set up slash commands to integrate AI into your daily routines:

| Command | Purpose |
|---------|---------|
| `/standup` | Daily brief across your active projects |
| `/tlddr` | Summarize a long session and log next steps + decisions into Obsidian |
