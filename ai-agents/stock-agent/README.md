# Stock Agent

A Claude Agent SDK application for checking real-time stock price information from a customizable watchlist.

## Features

- Interactive stock market information assistant
- Customizable stock watchlist via JSON configuration
- Basic error handling
- Streaming responses
- Configurable system prompts
- Support for both single-query and interactive modes

## Prerequisites

- Python 3.10 or higher
- pip package manager
- Anthropic API key

## Installation

1. Install dependencies:
```bash
pip install -r requirements.txt
```

2. Set up your API key:
```bash
cp .env.example .env
```

3. Edit `.env` and add your Anthropic API key:
```
ANTHROPIC_API_KEY=your_actual_api_key_here
```

Get your API key from: https://console.anthropic.com/

4. Customize your stock watchlist by editing `stock_list.json`:
```json
{
  "stocks": [
    {
      "symbol": "AAPL",
      "name": "Apple Inc."
    },
    {
      "symbol": "GOOGL",
      "name": "Alphabet Inc."
    }
  ]
}
```

## Usage

### Interactive Mode (Default)

Run the interactive mode:
```bash
python main.py
```

The agent will display your tracked stocks and allow you to ask questions about them. Type `quit` or `exit` to stop.

### Basic Example

To run the basic example instead, edit `main.py` and change the last line to:
```python
asyncio.run(main())
```

Then run:
```bash
python main.py
```

## Project Structure

```
stock-agent/
├── main.py              # Main application file
├── stock_list.json      # Stock watchlist configuration
├── requirements.txt     # Python dependencies
├── .env.example        # Example environment variables
├── .env                # Your actual API key (not tracked in git)
├── .gitignore          # Git ignore rules
└── README.md           # This file
```

## Configuration

### Agent Configuration

The agent can be configured through `ClaudeAgentOptions` in `main.py`:

- `system_prompt`: Defines the agent's role and capabilities
- `permission_mode`: Controls tool execution ('ask_user', 'accept_all', 'reject_all')
- `allowed_tools`: List of tools the agent can use (None = default tools)

### Stock Watchlist

Edit `stock_list.json` to customize which stocks to track:

```json
{
  "stocks": [
    {
      "symbol": "TICKER",
      "name": "Company Name"
    }
  ]
}
```

The agent will automatically load and reference these stocks in conversations.

## Example Conversations

```
You: What should I know about AAPL?
Agent: Apple Inc. (AAPL) is one of the world's largest technology companies...

You: How do I interpret stock price movements?
Agent: Stock price movements can be influenced by several factors...

You: What's the difference between market cap and stock price?
Agent: Market capitalization and stock price are related but different concepts...
```

## Next Steps

1. **Add MCP Stock Price Tools**: Integrate with a stock market API (e.g., Alpha Vantage, Yahoo Finance) using MCP servers
2. **Customize System Prompt**: Modify the agent's behavior and investment style
3. **Add Custom Tools**: Create Python functions decorated with `@tool` for technical analysis
4. **Enable Persistent Memory**: Add CLAUDE.md for context across sessions
5. **Create Subagents**: Build specialized agents for different tasks (e.g., technical analysis, fundamental analysis)
6. **Add Portfolio Tracking**: Extend functionality to track positions and performance

## Resources

- [Claude Agent SDK Python Documentation](https://docs.claude.com/en/api/agent-sdk/python)
- [Agent SDK Overview](https://docs.claude.com/en/api/agent-sdk/overview)
- [Anthropic API Console](https://console.anthropic.com/)

## License

MIT
