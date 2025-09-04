# Git introduction
This document intends to show some of the commonly used git commands, as well as explain how it can help you when writing code.

# Most common commands and what they do
1. `git config` – Set username and email for commits.
2. `git init` – Initialize a local repository.
3. `git status` – Show current repository state.
4. `git clone <url>` – Copy a remote repository locally.
5. `git pull` – Update local copy with remote changes.
6. `git add . / git add <file>` – Stage changes.
7. `git commit -m "msg"` – Save staged changes with a message.
8. `git push` – Upload local commits to remote.
9. `git checkout <branch>` – Switch or create a branch.
10. `git merge <branch>` – Merge a branch into the current one.
11. `git log` – View commit history

# Common workflows
## Starting a new project
1. Create a new repo on github.
2. Either upload files manually or run git init locally and connect it with GitHub using the provided commands.
3. Clone the repo with `git clone <url>` to work locally. Use the SSH url.
4. Share the GitHub repo so collaborators can clone, push, and pull changes.

## Working on a project
1. Make changes locally (new or modified files).
2. Stage changes with `git add .` for all changes in the current directory or `git add <file>` for specific file(s).
3. Commit with `git commit -m "message"`.
4. Push changes to remote with `git push`.
5. Others should run `git pull` to fetch the new changes from the remote branch.


## Using branches
1. Keep the main branch stable
2. Create a new branch with `git checkout -b <branch>` or switch to an existing one using `git checkout <branch>`.
3. After finalizing new changes in your new branch, add the files `git add`, commit them `git commit -m "changes in xyz"`.
4. Once the commit is done use `git checkout main` to go back to the main branch, then `git merge <branch>` to merge the changes from the other branch.
5. Now you can push the changes to the remote main branch if you'd like with `git push`
