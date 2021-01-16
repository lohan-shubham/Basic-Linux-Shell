# Basic Linux Shell 

>`Purpose:` Course Project at [IIITD](https://www.iiitd.ac.in/)
>
>[`Instructions:`](/instructions.pdf) (Credits- [Operating System](http://techtree.iiitd.edu.in/viewDescription/filename?=CSE231))

## Syscall Used:
> |Syscall | Work|
>| ------ | ------ |
> | fork() | to create a child process to aid the parent process in completing task |
>| waitpid() | to wait for the child process to finish, so that parent can start working |
>|execv() |to pass arguments to executable binaries|

## Commands:
>|Command| Work
>| ------ | ------ |
>| cd | change the current working directory of shell|
>| pwd |  get the current working directory of shell |
>| history|  to check the entered commands |
>| echo|  to show user input back |
>| exit|  to exit the shell |
>| cat |  to print files |
>| ls | to show content of current directory |
>| date|  to show the current time |
>| rm | to remove a file |
>| mkdir|   to make directory |


# Run:
 ```sh
$ make 
```
# Note :
This repository is open to contribute 
## Known bug:
- Symbolic Linkage in pwd and cd
- space between name interpretate as a two different things