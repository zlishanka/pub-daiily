"""
Weather Agent - A Claude Agent SDK application for fetching weather information

This agent helps users get current weather and forecast information.
It demonstrates basic Claude Agent SDK features including:
- Async query functionality
- System prompts
- Error handling
- Streaming responses
"""

import asyncio
import os
from dotenv import load_dotenv
from claude_agent_sdk import query, ClaudeAgentOptions

# Load environment variables from .env file
load_dotenv()


async def main():
    """
    Main function to run the weather agent.

    This demonstrates a basic weather information agent that can:
    - Answer weather-related questions
    - Provide weather forecasts
    - Explain weather concepts
    """

    # Check if API key is set
    api_key = os.getenv("ANTHROPIC_API_KEY")
    if not api_key:
        print("Error: ANTHROPIC_API_KEY not found in environment variables.")
        print("Please set your API key in the .env file.")
        print("Get your API key from: https://console.anthropic.com/")
        return

    # Configure the agent with options
    options = ClaudeAgentOptions(
        # Define the agent's role and capabilities
        system_prompt=(
            "You are a helpful weather information assistant. "
            "You help users understand weather conditions, forecasts, and weather-related concepts. "
            "You provide clear, accurate information about weather patterns, temperature, precipitation, "
            "and other meteorological phenomena. "
            "Note: You don't have real-time weather data access yet, but you can explain weather concepts "
            "and help users understand how to interpret weather information."
        ),

        # Set permission mode for tool execution
        # Options: 'accept_all', 'reject_all', 'ask_user'
        permission_mode='default',

        # Specify allowed tools (if needed)
        # For a basic agent, we'll keep this simple
        allowed_tools=None,  # None means allow default tools
    )

    # Example weather-related query
    user_query = (
        "What's the difference between weather and climate? "
        "Also, explain what causes rain."
    )

    print("Weather Agent Starting...")
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
    Interactive mode for continuous conversation with the weather agent.

    Users can ask multiple questions in a row.
    Type 'quit' or 'exit' to stop.
    """

    # Check if API key is set
    api_key = os.getenv("ANTHROPIC_API_KEY")
    if not api_key:
        print("Error: ANTHROPIC_API_KEY not found in environment variables.")
        print("Please set your API key in the .env file.")
        return

    options = ClaudeAgentOptions(
        system_prompt=(
            "You are a helpful weather information assistant. "
            "You help users understand weather conditions, forecasts, and weather-related concepts. "
            "Provide clear, concise answers to weather-related questions."
        ),
        permission_mode='default',
    )

    print("Weather Agent - Interactive Mode")
    print("Type 'quit' or 'exit' to stop")
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
    # Run the main example
    # To use interactive mode instead, uncomment the line below:
    asyncio.run(interactive_mode())

    #asyncio.run(main())
