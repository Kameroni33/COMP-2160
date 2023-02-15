@echo off

:loop
    rem Fetch and pull any repository changes
    git fetch origin
    git pull

    rem Wait 5 seconds and then do it again
    timeout /t 5

goto loop
