@echo off
echo ========================================
echo Movie Advisor - GitHub Setup
echo ========================================
echo.

echo Step 1: Initializing Git repository...
git init
if %errorlevel% neq 0 (
    echo Error: Git is not installed or not in PATH
    echo Please install Git from https://git-scm.com/
    pause
    exit /b 1
)

echo.
echo Step 2: Adding all files...
git add .

echo.
echo Step 3: Creating initial commit...
git commit -m "Initial commit: Movie Advisor - Full stack movie recommendation system"

echo.
echo ========================================
echo Git repository initialized successfully!
echo ========================================
echo.
echo Next steps:
echo 1. Go to https://github.com and create a new repository
echo 2. Name it: Movie-Advisor
echo 3. Don't initialize with README, .gitignore, or license
echo 4. Copy the repository URL
echo 5. Run these commands (replace YOUR_USERNAME):
echo.
echo    git remote add origin https://github.com/YOUR_USERNAME/Movie-Advisor.git
echo    git branch -M main
echo    git push -u origin main
echo.
pause

