"""
Write a python code to do the following:
1) I have a list of genes as input: BRI3BP, ENDOD1, ASB8, TFPI, FBXO33 
2) Use the list of genes above to send a query to the backend service through API like following: https://www.fobinf.com/?gene=BRI3BP&dataset=nl_human_data_HemaExp_v_1 
3) Collect result for each query as a rows of a CSV file, note you need to create javascript event by clicking on button and result is downloaded as csv file at ~/Downloads/BRI3BP_log2.csv  
4) Output row results into a CSV file

Get the chromedriver from 
https://googlechromelabs.github.io/chrome-for-testing/

Need to pip install following packages 
pip install selenium
 
"""

import os
import time
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
import csv

# Step 1: Define the list of genes
genes = ["BRI3BP", "ENDOD1", "ASB8", "TFPI", "FBXO33"]

# Step 2: Define the base URL and dataset parameter
base_url = "https://www.fobinf.com/"
dataset = "nl_human_data_HemaExp_v_1"

# Step 3: Configure Chrome to automatically download files
download_dir = os.path.expanduser("~/Downloads")  # Path to the Downloads directory
chrome_options = Options()
chrome_options.add_experimental_option("prefs", {
    "download.default_directory": download_dir,
    "download.prompt_for_download": False,
    "download.directory_upgrade": True,
    "safebrowsing.enabled": True
})
chrome_options.add_argument("--headless")  # Run in headless mode (no GUI)
chrome_options.add_argument("--disable-gpu")
chrome_options.add_argument("--no-sandbox")

# Path to your chromedriver executable
chromedriver_path = "/usr/local/bin/chromedriver"  # Update this path
service = Service(chromedriver_path)
driver = webdriver.Chrome(service=service, options=chrome_options)

# Step 4: Initialize the CSV file and write the header
output_file = "gene_expression_results.csv"
csv_header = [
    "Gene",
    "log2",
    "HSC_BM", "HSC_BM", "HSC_BM", "HSC_BM", "HSC_BM", "HSC_BM", "HSC_BM", "HSC_BM",
    "early HPC_BM", "early HPC_BM", "early HPC_BM", "early HPC_BM",
    "CMP", "CMP", "CMP",
    "GMP", "GMP", "GMP",
    "MEP", "MEP", "MEP",
    "PM_BM", "PM_BM", "PM_BM",
    "MY_BM", "MY_BM", "MY_BM",
    "PMN_BM", "PMN_BM", "PMN_BM",
    "PMN_PB", "PMN_PB", "PMN_PB",
    "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes", "CD14+ monocytes",
    "B cells", "B cells", "B cells", "B cells", "B cells",
    "CD4+ T cells", "CD4+ T cells", "CD4+ T cells", "CD4+ T cells", "CD4+ T cells",
    "CD8+ T cells", "CD8+ T cells", "CD8+ T cells", "CD8+ T cells", "CD8+ T cells",
    "NK cells", "NK cells", "NK cells", "NK cells", "NK cells",
    "mDC", "mDC", "mDC", "mDC", "mDC",
    "pDC", "pDC", "pDC", "pDC", "pDC"
]

# delete old files
os.system(f"rm {download_dir}/*.csv") 

with open(output_file, mode="w", newline="", encoding="utf-8") as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(csv_header)

    # Step 5: Loop through each gene and process the download
    for gene in genes:
        # Construct the full URL with query parameters
        url = f"{base_url}?gene={gene}&dataset={dataset}"
        
        try:
            # Load the webpage
            driver.get(url)
            time.sleep(3)  # Wait for JavaScript to load (adjust as needed)

            # Step 6: Locate the button using its selector
            button = WebDriverWait(driver, 10).until(
                EC.element_to_be_clickable((By.CSS_SELECTOR, "button[onclick='exportDataAsText()']"))
            )

            # Simulate a click on the button to trigger the download
            button.click()

            # Step 7: Wait for the file to be downloaded
            # Assume the file name is based on the gene name (e.g., BRI3BP.csv)
            file_name = f"{gene}_log2.csv"
            file_path = os.path.join(download_dir, file_name)

            # Wait until the file exists in the download directory
            timeout = 30  # Maximum wait time in seconds
            start_time = time.time()
            while not os.path.exists(file_path):
                time.sleep(1)
                if time.time() - start_time > timeout:
                    raise TimeoutError(f"File {file_name} was not downloaded within {timeout} seconds.")

            # Step 8: Read the downloaded CSV file and skip the first row
            with open(file_path, mode="r", encoding="utf-8") as downloaded_file:
                reader = csv.reader(downloaded_file)
                rows = list(reader)[1:]  # Skip the first row (header)

            # Step 9: Write the data to the output CSV file
            for row in rows:
                writer.writerow([gene] + row)
            print(f"Processed gene: {gene}")

        except Exception as e:
            # Handle any errors during scraping
            print(f"Error processing gene {gene}: {e}")
            writer.writerow([gene, "Error"])

# Step 10: Close the WebDriver
driver.quit()

print(f"All results have been saved to {output_file}")
