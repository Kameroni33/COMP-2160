#!/bin/bash

while true; do
    CHANGES=$(git status -s)

    if [[ -n "$CHANGES" ]]; then
        # Commit the changes
        git add -A
        git commit -m "[auto-commit] COMP 2160"
        git push
    fi

  # Sleep for 5 seconds before checking again
  sleep 5
done
