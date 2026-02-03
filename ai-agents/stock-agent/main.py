"""
Stock Agent - A Claude Agent SDK application for checking real-time stock prices

This agent helps users get current stock price information for symbols in a watchlist.
It demonstrates basic Claude Agent SDK features including:
- Async query functionality
- System prompts
- Error handling
- Streaming responses
- JSON file parsing
"""

import asyncio
import json
import os
from pathlib import Path
from dotenv import load_dotenv
from claude_agent_sdk import query, ClaudeAgentOptions

# Load environment variables from .env file
load_dotenv()


def load_stock_list():
    """
    Load stock symbols from stock_list.json

    Returns:
        list: List of stock dictionaries with symbol and name
    """
    stock_file = Path(__file__).parent / "stock_list.json"

    try:
        with open(stock_file, 'r') as f:
            data = json.load(f)
            return data.get('stocks', [])
    except FileNotFoundError:
        print(f"Error: {stock_file} not found.")
        return []
    except json.JSONDecodeError:
        print(f"Error: Invalid JSON in {stock_file}")
        return []


async def main():
    """
    Main function to run the stock agent.

    This demonstrates a basic stock information agent that can:
    - Check stock prices from a watchlist
    - Provide stock information
    - Answer stock-related questions
    """

    # Check if API key is set
    api_key = os.getenv("ANTHROPIC_API_KEY")
    if not api_key:
        print("Error: ANTHROPIC_API_KEY not found in environment variables.")
        print("Please set your API key in the .env file.")
        print("Get your API key from: https://console.anthropic.com/")
        return

    # Load stock list
    stocks = load_stock_list()
    if not stocks:
        print("Warning: No stocks loaded from stock_list.json")
        return

    # Create a formatted list of stocks for the prompt
    stock_symbols = ", ".join([f"{s['symbol']} ({s['name']})" for s in stocks])

    # Configure the agent with options
    options = ClaudeAgentOptions(
        # Define the agent's role and capabilities
        system_prompt=(
            "You are a helpful stock market information assistant. "
            "You help users understand stock prices, market trends, and stock-related concepts. "
            "You provide clear, accurate information about stock market data, trading, "
            "and financial concepts. "
            f"The user is tracking these stocks: {stock_symbols}. "
            "Note: You don't have real-time stock price data access yet, but you can explain "
            "stock concepts and help users understand how to interpret stock information. "
            "You can provide general guidance about the tracked stocks and financial markets."
        ),

        # Set permission mode for tool execution
        # Options: 'accept_all', 'reject_all', 'ask_user'
        permission_mode='default',

        # Specify allowed tools (if needed)
        # For a basic agent, we'll keep this simple
        allowed_tools=None,  # None means allow default tools
    )

    # Example stock-related query
    user_query = (
        f"I'm tracking these stocks: {stock_symbols}. "
        "Can you explain what factors typically affect stock prices and "
        "what I should pay attention to when monitoring these stocks?"
    )

    print("Stock Agent Starting...")
    print(f"\nTracking {len(stocks)} stocks from stock_list.json")
    print(f"\nUser Query: {user_query}\n")
    print("Agent Response:")
    print("-" * 80)

    try:
        # Query the agent with streaming response
        # The agent will respond in real-time as it generates the response
        async for message in query(
            prompt=user_query,
            options=options
        ):
            # Print each message chunk as it arrives
            print(message, end='', flush=True)

        print("\n" + "-" * 80)
        print("\nAgent finished successfully!")

    except Exception as e:
        print(f"\nError occurred: {e}")
        print("Please check your API key and internet connection.")


async def interactive_mode():
    """
    Interactive mode for continuous conversation with the stock agent.

    Users can ask multiple questions about stocks in their watchlist.
    Type 'quit' or 'exit' to stop.
    """

    # Check if API key is set
    api_key = os.getenv("ANTHROPIC_API_KEY")
    if not api_key:
        print("Error: ANTHROPIC_API_KEY not found in environment variables.")
        print("Please set your API key in the .env file.")
        return

    # Load stock list
    stocks = load_stock_list()
    if not stocks:
        print("Warning: No stocks loaded from stock_list.json")
        print("Please add stocks to stock_list.json before running.")
        return

    # Create a formatted list of stocks for the prompt
    stock_symbols = ", ".join([f"{s['symbol']} ({s['name']})" for s in stocks])

    options = ClaudeAgentOptions(
        system_prompt=(
            "You are a helpful stock market information assistant. "
            "You help users understand stock prices, market trends, and stock-related concepts. "
            f"The user is tracking these stocks: {stock_symbols}. "
            "Provide clear, concise answers to stock-related questions. "
            "Note: You don't have real-time stock price data access yet, but you can provide "
            "valuable insights about stock concepts, market analysis, and financial information."
        ),
        permission_mode='default',
    )

    print("Stock Agent - Interactive Mode")
    print(f"Tracking {len(stocks)} stocks:")
    for stock in stocks:
        print(f"  - {stock['symbol']}: {stock['name']}")
    print("\nType 'quit' or 'exit' to stop")
    print("-" * 80)

    while True:
        # Get user input
        user_input = input("\nYou: ").strip()

        # Check for exit commands
        if user_input.lower() in ['quit', 'exit', 'q']:
            print("Goodbye!")
            break

        if not user_input:
            continue

        print("\nAgent: ", end='', flush=True)

        try:
            # Query the agent
            async for message in query(
                prompt=user_input,
                options=options
            ):
                print(message, end='', flush=True)

            print()  # New line after response

        except Exception as e:
            print(f"\nError: {e}")
            print("Please try again or type 'quit' to exit.")


if __name__ == "__main__":
    # Run the interactive mode by default
    asyncio.run(interactive_mode())

    # To run the basic example instead, uncomment the line below:
    # asyncio.run(main())
