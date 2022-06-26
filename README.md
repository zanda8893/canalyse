# canalyse
```
░█████╗░░█████╗░███╗░░██╗░█████╗░██╗░░░░░██╗░░░██╗░██████╗███████╗
██╔══██╗██╔══██╗████╗░██║██╔══██╗██║░░░░░╚██╗░██╔╝██╔════╝██╔════╝
██║░░╚═╝███████║██╔██╗██║███████║██║░░░░░░╚████╔╝░╚█████╗░█████╗░░
██║░░██╗██╔══██║██║╚████║██╔══██║██║░░░░░░░╚██╔╝░░░╚═══██╗██╔══╝░░
╚█████╔╝██║░░██║██║░╚███║██║░░██║███████╗░░░██║░░░██████╔╝███████╗
░╚════╝░╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚══════╝░░░╚═╝░░░╚═════╝░╚══════╝
```
                 
<h2>Canalyse is a commandline c source files analysis tool</h2>

  
```
Options: [--countlines] count all lines including comments and whitespace
         [--countcharacters] count all characters
         [--countcodelines] count all lines of code
         [--removecomments] remove all comments and out a .o file with the same name
         [--balancebrackets] check that all brackets are balanced
         [--functioncount] count the number of functions
         [--all] run all checks
         [--help] display help message
```
#
<h3>Compiling the program</h3>

 - Open a terminal  
 - Run `$ make` same directory as the files
 - `$ make` should complete without error and generate a `canalyse` binary
 - Run canalyse with `$ ./canalyse` or proceed to install
#

<h3>Installing the program(Linux only)</h3>

  - Run `$ sudo make install` or `# make install`

You have now sucessfully install Canalyse and can use it in commandline from any directory
