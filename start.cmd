@echo off

echo Once everything has loaded type and enter "main.py" to start GreenLog.
echo.

pip install -r requirements.txt > nul

pipenv install > nul
pipenv shell
