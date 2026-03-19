---
title: ChatGPT & LLM Prompt Guide
created: 2025-03-14
tags:
  - prompts
  - chatgpt
  - llm
  - prompt-engineering
  - obsidian
aliases:
  - GPT Prompt Cheatsheet
  - LLM Prompt Reference
---

# ChatGPT & LLM Prompt Guide

Quick reference for effective prompts, techniques, and use cases. Optimized for retrieval in [[Obsidian]] and similar note apps.

---

## Quick Index (MOC)

| Category | Use when you need… |
|----------|--------------------|
| [[#Role & Persona]] | GPT to act as a specific role or tool |
| [[#Learning & Explanation]] | Explain at different levels, learn concepts |
| [[#Prompt Engineering]] | Temperature, chaining, training GPT |
| [[#Business & Creativity]] | Ideas, marketing, hiring, landing pages |
| [[#Structured Output]] | Tables, JSON, CSV, charts, scorecards |
| [[#Developer & Code]] | Debug, refactor, test, document, Git |
| [[#Coding Productivity]] | Explain, extend, simplify, optimize code |
| [[#Search & Research]] | Google operators, research memos |
| [[#Decision Making]] | Pros/cons, frameworks, pre-mortem |
| [[#Writing & Communication]] | Emails, proofreading, style, summaries |
| [[#Problem-Solving Frameworks]] | KT, RCA, Six Hats |
| [[#Utility & Formats]] | Checklists, regex, translation, contracts |

---

## Role & Persona

#role #persona #priming

Have the model adopt a specific identity or tool:

- **Act as a Linux Terminal**
- **Act as "[Position] interviewer"** (e.g. "Act as a Product Manager interviewer")
- **Act as an Excel Sheet**
- **Act as an English Teacher**

**Example — expert persona for content:**

> As a Harvard Marketing graduate and skilled content creator, guide me in crafting social media content that resonates with AI enthusiasts. Emphasize uncommon and expert questions to ask.

---

## Learning & Explanation

#learning #explanation #eli5

Ask for explanations at different levels:

- Explain **like I'm 5**, with examples
- Explain for **5th graders** / **high schoolers**
- Explain **like Elon Musk**, detailed with examples

**3-step way to learn a new concept:**

1. Copy a lesson and paste it into ChatGPT.
2. Ask it to formulate questions about the lesson (e.g. *"Ask me 3 questions about this summary"*).
3. Answer the questions and ask ChatGPT to evaluate your answers.

**Learn to use ChatGPT better:**

> Create a beginner's guide to using ChatGPT. Topics should include prompts, priming, and personas. Include examples. The guide should be no longer than 500 words.

---

## Prompt Engineering

#temperature #chained-prompts #meta

### Temperature

- **Higher (e.g. 10.0):** more creative/varied.
- **Lower (e.g. 0.1):** more focused and deterministic.

> Give me a short paragraph on why AI will continue to gain popularity. Use a temperature of 10.0  
> Give me a short paragraph on why AI will continue to gain popularity. Use a temperature of 0.1

### Train GPT to write prompts for you

> What's the best prompt for ChatGPT to learn my writing style and respond to my emails for me?

### Chained prompts

Break a task into steps; use each output as input for the next.

**Example — article about ChatGPT:**

1. *"Write an article about ChatGPT. First give me the outline: headline, teaser, and several subheadings."*
2. *"Now write 5 different subheadings."*
3. *"Add 5 keywords for each subheading."*

---

## Business & Creativity

#business #ideas #marketing #hiring

### Generate ideas and angles

> Generate unique angles or strategies for the topic "How to increase your creative output."

### List of ideas

> I am building a [insert thing]. Give me a list of 10 ideas for [insert thing].  
> I am building a landing page for a fintech app. Give me a list of 10 persuasive and catchy headlines for the page.

### Marketer prompts

> I am a marketer and I am new to using GPT. Can you give me a list of essential GPT prompts that will help marketers get more done and save time?

### Interview questions for hiring

> I am hiring a [insert job title]. I have no experience hiring for this position. Give me a list of questions for how I should evaluate them, along with scoring criteria.

---

## Structured Output

#tables #json #csv #charts #formats

### Table

> Create a table for top AI tools. Include the following columns: Name, Category, and Oneliner. Here are the tools that I want to summarize: [list tools]

### Scorecard

> Can you generate output in a scorecard format on how Apple stocks performed against Tesla in the past 5 years?

### JSON

> Can you provide details of the last 2 FIFA World Cup winners in JSON format?  
> I want the following to include: date, opponent name, winner name, score, and stadium name.

### Chart (from text)

> Johnny made $50k in Jan, $40k in Feb, $30k in March. Shaun made $60k in Jan, $20k in Feb, $75k in March. Can you put this data in a bar chart?

### Other formats

- **CSV** — request CSV output
- **XML / YAML** — specify format
- **SVG** — for diagrams or graphics
- **Diagrams** — flowcharts, process diagrams
- **Checklist** — e.g. *"Create a checklist for preparing for a job interview."*

---

## Developer & Code

#developer #code #debugging #architecture

### Architecture and implementation

> Develop an architecture and code for a [description] website with JavaScript.

### Find mistakes

> Help me find mistakes in the following code: [paste code below]

### Sticky header example

> I want to implement a sticky header on my website. Can you provide an example using CSS and JavaScript?

### Continue writing code

> Please continue writing code for JavaScript. [Paste code below]

### Code review (debugging & optimization)

> Review the following [programming language] code for [specific functionality]: [paste code]. Identify bugs, inefficiencies, and security vulnerabilities. Propose optimized code with inline comments explaining fixes and adherence to [framework/library] best practices.

### Document summarization

> Summarize the attached [document/report] into a 10-point executive briefing. Extract key decisions, metrics, and recommendations. Highlight sections requiring urgent attention and cross-reference with [related policy/regulation].

### Financial forecasting

> Analyze the attached financial statements for [company]. Perform a variance analysis vs. budget, identify liquidity risks, and forecast [e.g. EBITDA, cash flow] for the next 6 quarters. Visualize trends and recommend cost-optimization strategies.

### Smart contract review

> This is a Solidity contract. Can you help me review it and let me know if there are security vulnerabilities?

### Cursor-style codebase overview

> The current GitHub repo is for [main functionality of codebase and environment] (e.g. written in Python FastAPI). It uses [framework, etc.]. Please analyze the codebase holistically and give me a comprehensive overview of the major functionality and use cases.

---

## Coding Productivity (10+1)

#coding #productivity #refactor #tests

Source: [10 ways to improve coding productivity with ChatGPT](https://www.youtube.com/watch?v=uZUcZEDdseY)

1. **Explain** — Paste code and ask it to explain each function.
2. **Extend** — Ask to add exception handling, new features, etc.
3. **Refactor** — Rewrite following a style (e.g. *"Rewrite the code below following the Google style guidelines for JavaScript"*).
4. **Simplify** — Simplify complex code (use ` ``` ... ``` ` as delimiter for code).
5. **Test cases** — *"Write test cases for the main edge cases for the below code. First outline the test cases, then write them in JavaScript using the Jest framework."*
6. **Optimize** — Ask for an alternative, more efficient version of the function.
7. **Translate language** — e.g. JavaScript to Python: *"Translate this code from JavaScript to Python [enter code]"*
8. **Document** — *"Regenerate the code snippet below with comments on each line. [enter code]"*
9. **Debug** — Ask it to track down the bug.
10. **Upload to S3** — (joke in original notes.)
11. **Translate** — Repeat of (7); use for any language pair.

---

## Git & Regex

#git #regex

### Git command generator

> I want you to act like a Git command generator. I'll explain what I need to do and you will provide me with the right Git command. My first requirement is [describe what you need].

### Regex

Ask GPT to **generate regexes** for your pattern (describe the pattern in plain language).

---

## Search & Research

#search #google #research

### Google Search operators (tutorial)

Ref: [Google like a pro — advanced search operators](https://www.youtube.com/watch?v=BRiNw490Eq0)

- **Phrase / limit keyword:** `"AGI threat"`
- **intitle:** `intitle:iphone15 sale`
- **intitle + phrase:** `intitle:"iphone 15 deal"`
- **allintitle:** `allintitle:word1 word2 word3`
- **intext:** `intitle:"Elon MUSK" intext:"SpaceX Starship"` or `intitle:"Qigong Zheng" intext:"UMD"`
- **inurl:** `Elon MUSK inurl:youtube intext:youtube`
- **site:** `Elon Musk site:youtube.com` or `little cat site:pexels.com`
- **imagesize:** `elon musk imagesize:2560x1440`
- **filetype:** `large language model filetype:pdf` or `arrow filetype:png`

**Tips:** Start with a simple, precise query; avoid redundant terms; break into smaller questions; word choice and order matter.

### GPT as research analyst

Ref: [X / GodofPrompt](https://x.com/godofprompt/status/1923644667633205555)

> I want you to act as an elite research analyst with deep experience in synthesizing complex information into clear, concise insights.  
> Your task is to [condense / analyze] [insert your topic here].  
> Proceed as follows:  
> 1. Brief plain-English overview of the topic.  
> 2. Break the topic into 3–5 major sub-topics or components.  
> 3. For each sub-topic: short definition, key facts/trends/recent developments, major debates or differing perspectives.  
> 4. Include notable data, statistics, or real-world examples.  
> 5. Recommend 3–5 high-quality resources for further reading.  
> 6. End with a "Smart Summary" — 5 bullet points for an executive-style briefing.  
> Guidelines: clear, structured, skimmable (headings, bullets). Act like you're preparing a research memo for a CEO or investor — no fluff, just value.

---

## Decision Making

#decision-making #pros-cons #frameworks

### Pros and cons

> I am trying to decide if I should [insert decision]. Give me a list of pros and cons that will help me decide why I should or shouldn't make this decision.

### Industry expert

> Imagine you could consult [industry expert] on [specific decision]. What questions would you ask them, and what insights do you think they would share?

### Reverse engineer success

> Study a successful individual or company in [industry/field] and identify the key factors and decisions that contributed to their success. How can these insights be applied to [your situation]?

### Six Thinking Hats

> Apply the Six Thinking Hats technique to [decision/problem] and provide a summary of the insights gathered from each hat.

### Alternative perspectives

> Provide three different perspectives on [decision/problem] and evaluate the pros and cons of each approach.

### Long-term consequences

> Consider the long-term implications of [decision] for [individual/company]. What possible outcomes could arise, and how might they impact future success?

### Timeframes (10 min / 10 months / 10 years)

> Evaluate the possible consequences of [decision] in the short term (10 minutes), medium term (10 months), and long term (10 years). How should these timeframes affect my perspective on the decision?

### Diverse feedback

> Identify three individuals with different backgrounds or perspectives who could provide valuable input on [decision/problem]. What questions should I ask them, and how could their insights inform my decision-making?

### Pre-mortem

> Imagine that [decision/project] has failed in the future. Conduct a pre-mortem analysis to identify potential causes of failure and develop strategies to address them before they become issues.

---

## Writing & Communication

#writing #email #proofreading #style

### Summarize complex texts

> I need to read a complicated article related to (topic). Can you help me summarise the key points and takeaways from the text?

### Connect with communities

> Connect me with a community of learners and experts in (topic). How can I join a forum, social media group, or other online community to share my knowledge and learn from others?

### Customer service email

> As a customer service representative, you are tasked with handling a case involving [PROBLEM]. Write an email responding to that problem, no more than [NUMBER] words, offering the customer [SOLUTION].

### Proofreading and clarity

> [Paste your writing]  
> Proofread my writing above. Fix grammar and spelling mistakes and make suggestions that will improve the clarity of my writing.

### Match writing style

> Analyze the writing style of the text provided below: [TEXT]. Now write an essay of [NUMBER] words on [SPECIFIC TOPIC]. You do not have to mention anything from the previous text; it is only provided to elicit a response that imitates the tone, structure, and vocabulary. Answer only with the requested essay.

### Simplify with analogies

> Break down (topic) into smaller, easier-to-understand parts. Use analogies and real-life examples to simplify the concept and make it more relatable.

### Personal intern / report

> I am creating a report about [topic]. Research and create an in-depth report with a step-by-step guide that will help readers understand how to [insert outcome].

### 30-day learning plan

> I want to learn [insert skill]. Generate a 30-day plan that will help a beginner like me learn the skill from scratch.

### Book summary

> Summarize the book [insert book] by [insert author] and give me a list of the most important learnings and insights.

### Problem-solving steps

> Your role is that of a problem solver. Give me a step-by-step guide to solving [insert your problem].

### 80/20 learning

> I want to learn about [insert topic]. Identify and share the most important 20% of learnings from this topic that will help me understand 80% of it.

### First principles

> I have difficulty learning AI. Help me understand it better using First Principle Thinking.

---

## Problem-Solving Frameworks

#kt #rca #structured-thinking

### Kepner-Tregoe (KT)

> You are an expert [niche] coach. I am [describe the problem with background context]. Help me analyze the problem using the Kepner-Tregoe framework. The issue involves [describe the problem]. Start by helping me appraise the situation to identify main concerns and prioritize them. Then guide me through defining the problem clearly, analyzing potential causes, and evaluating alternative solutions. Finally, discuss how we can anticipate and mitigate potential future problems. I want you to [mention how you want the output in detail with examples].

### Root Cause Analysis (RCA)

> You are an expert [niche]. Assist me with a Root Cause Analysis for a recurring problem. The problem is [describe the issue]. Begin by helping me clearly define the problem and gather all necessary data related to its occurrence. Then brainstorm possible causes and use techniques like the 5 Whys or Fishbone Diagram to pinpoint the root cause. Finally, suggest practical solutions to address this root cause and prevent the issue from recurring. I want you to [mention how you want the output in detail with examples].

---

## Utility & Formats

#utility #translation #contracts #ml #presentations

### Lease / contracts

> Write a 12-month lease agreement.  
> Write a motivating email with a quote from Nelson Mandela explaining that all employees in the company will get a 20% pay cut so that top executives can get a larger Christmas bonus. Make it inspiring and positive.

### Translation

> Translate to [target language]. (e.g. English to Chinese, Chinese to English.)

### Word meaning and examples

> Synonym for sagacious.  
> Now use it in 10 sentences.

### Instructional guide

> How to format a word in MLA?

### Cooking from ingredients

> How to make dinner from [available ingredients]?

### Extract as variable

> [Describe the information.] Now output that as a Python variable.

### ML / PyTorch example

> Build a model using PyTorch that does multi-label classification over 10 classes. It takes as input: (1) an RGB image of size 320×320, and (2) a vector of length 128.

### Presentations (Gamma)

- Tool: [Gamma.app](http://gamma.app) — e.g. generate a presentation on "Top 10 Cell Phones of 2025".

### Deep learning papers

> What are the milestone papers in deep learning that have had great impact?

---

## Related

- [[Obsidian]] — linking and MOC
- Original raw notes: `gptPrompt` (same folder)
