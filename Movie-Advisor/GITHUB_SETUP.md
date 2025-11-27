# GitHub Setup Guide

Follow these steps to push your Movie Advisor project to GitHub.

## Step 1: Initialize Git Repository

Open PowerShell or Command Prompt in the project directory and run:

```bash
git init
```

## Step 2: Add All Files

```bash
git add .
```

## Step 3: Create Initial Commit

```bash
git commit -m "Initial commit: Movie Advisor - Full stack movie recommendation system"
```

## Step 4: Create GitHub Repository

1. Go to [GitHub](https://github.com) and sign in
2. Click the **+** icon in the top right
3. Select **New repository**
4. Name it: `Movie-Advisor` (or any name you prefer)
5. **Don't** initialize with README, .gitignore, or license (we already have these)
6. Click **Create repository**

## Step 5: Connect Local Repository to GitHub

After creating the repository, GitHub will show you commands. Use these:

```bash
# Add remote repository (replace YOUR_USERNAME with your GitHub username)
git remote add origin https://github.com/YOUR_USERNAME/Movie-Advisor.git

# Rename branch to main (if needed)
git branch -M main

# Push to GitHub
git push -u origin main
```

## Step 6: Verify

Go to your GitHub repository page and verify all files are uploaded.

## Future Updates

When you make changes:

```bash
# Check status
git status

# Add changed files
git add .

# Commit changes
git commit -m "Description of your changes"

# Push to GitHub
git push
```

## Optional: Add GitHub Topics

On your GitHub repository page, click the gear icon next to "About" and add topics:
- `c-programming`
- `movie-recommendation`
- `web-development`
- `full-stack`
- `javascript`
- `html-css`

## Optional: Add Repository Description

Add a description like:
"Full-stack movie recommendation system with C backend and modern web frontend"

---

**Note**: Make sure `.gitignore` is working correctly - it should exclude `.exe` files and the `database/` folder.

