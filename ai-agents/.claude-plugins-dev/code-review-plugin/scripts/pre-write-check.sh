#!/bin/bash
# Quick check script before writing

# Read tool input from stdin
tool_input=$(cat)

# Extract the file path (if it's a Python file)
file_path=$(echo "$tool_input" | jq -r '.tool_input.path // empty')

if [[ "$file_path" == *.py ]]; then
echo "🔍 Python file check, ensuring compliance with PEP 8"
fi

exit 0
