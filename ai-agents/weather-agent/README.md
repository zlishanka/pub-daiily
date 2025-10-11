# Weather Agent

A Claude Agent SDK application for fetching and understanding weather information.

## Features

- Interactive weather information assistant
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

## Usage

### Basic Example

Run the default example:
```bash
python main.py
```

### Interactive Mode

To use the interactive mode, edit `main.py` and uncomment this line at the bottom:
```python
asyncio.run(interactive_mode())
```

Then run:
```bash
python main.py
```

Type your weather-related questions and the agent will respond. Type `quit` or `exit` to stop.

## Project Structure

```
weather-agent/
├── main.py              # Main application file
├── requirements.txt     # Python dependencies
├── .env.example        # Example environment variables
├── .env                # Your actual API key (not tracked in git)
├── .gitignore          # Git ignore rules
└── README.md           # This file
```

## Configuration

The agent can be configured through `ClaudeAgentOptions` in `main.py`:

- `system_prompt`: Defines the agent's role and capabilities
- `permission_mode`: Controls tool execution ('ask_user', 'accept_all', 'reject_all')
- `allowed_tools`: List of tools the agent can use (None = default tools)

## Next Steps

1. **Add MCP Weather Tools**: Integrate with a weather API using MCP servers
2. **Customize System Prompt**: Modify the agent's behavior and personality
3. **Add Custom Tools**: Create Python functions decorated with `@tool`
4. **Enable Persistent Memory**: Add CLAUDE.md for context across sessions
5. **Create Subagents**: Build specialized agents for different weather tasks

## Resources

- [Claude Agent SDK Python Documentation](https://docs.claude.com/en/api/agent-sdk/python)
- [Agent SDK Overview](https://docs.claude.com/en/api/agent-sdk/overview)
- [Anthropic API Console](https://console.anthropic.com/)

## License

MIT
