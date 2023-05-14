#!/bin/bash

# Set the path to the file that contains the access token
TOKEN_FILE=/home/david/Documents/Degree/Projects/token.txt

# Read the access token from the file
GITHUB_TOKEN=$(cat "$TOKEN_FILE")

# Add and commit changes
git add .
git commit -m "Daily commit"

# Push changes with authentication using the access token
git push https://$GITHUB_TOKEN@github.com/<DavidS611/Set-Calculator.git

