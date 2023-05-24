# Project Title

### 0x16. C - Simple Shell
##### Weight: 10 

## Names of Participant
+ Joseph Johnson Aniekan
+ Olabanji Enioluwayan Emmanuel (collaborator)

## Resources
1. Unix shell
2. Thompson shell
3. Ken Thompson

## Allowed Editors
+ Vi|Vim
+ Emacs

## Compilation

*** gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh ***

## Concept


## Output

*** Interactive mode ***
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

*** Non-Interactive mode ***
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```


