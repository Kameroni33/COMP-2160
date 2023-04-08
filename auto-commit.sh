#!/bin/bash

git pull
while true; do
    CHANGES=$(git status -s)
    if [[ -n "$CHANGES" ]]; then
        # Commit the changes
        git add -A
        git commit -m "[auto-commit] COMP 2160"
        git push
    fi
    sleep 5
done
