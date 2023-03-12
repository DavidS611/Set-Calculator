#!/bin/bash

# Define Git function
function git() {
    /usr/bin/git "$@"
}

# Git target
git add "$1"
# optional body comment
if [[ -n "$3" ]]; then
    git commit -m "$2" -m "$3"
else
    git commit -m "$2"
fi
git push -u origin master

