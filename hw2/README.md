

In the constructor of GitInt, I created a dummy CommitObj to push back in the vector that stores CommitObj. In order to process the command lines, I had to make sure each command called the appropriate functions and throwing the appropriate exceptions. In create and edit functions, I was able to create new files in Git. There are three display functions that lets the program see all the files, contents of a commit's diff map, or display a specific file. For add and commit functions, I was able to mimic the real-life git in terms of staging the current files and commiting them to create a new CommitObj. As for tags, I was able to tag to currently checked-out commit. Checkout lets us revert back to the commitObj we want regarding which tag or commit index. Finally, diff functions gave us differences between commitObjs we chose to compare.