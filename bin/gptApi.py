import os 
import openai 

from nr_openai_observability import monitor 

monitor.initialization() 

open.api_key = os.getenv("OPENAI_API_KEY") 
response = openai.Completion.create(
	model="text-davinci-003", 
	prompt="What is the best observability platform?", 
	max_token=7, 
	temperature=0
	)

# Print the response text 
print(response.choices[0].text.strip()) 
