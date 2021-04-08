# NAME
**simple_shell** - command interpreter (shell)

# SYNOPSIS
**simple_shell** [command_file]

# DESCRIPTION
**simple_shell** is a custom command interpreter for the system.

* **Overwiew**

  The simple_shell is a command that reads lines from either a file or the terminal, intereprets them, and generally executes other commands. It is the program a user could run on logging into the system (it can be set as default shell with the chsh(1) command). The simple_shell implements a lamguage that has flow control constructs, a macro facility that provides a variety of features in addition to data storage, along with built in history and line editing capabilities. It incorporates many features to aid interactive use and has the advantage that the interpretative language is common to both interactive and non-interactive use (shell scripts). That is, commands can be typed directly to the running shell or can be put into a file and the file can be executed directly by the shell.

* **Invocation**

  If no args are present and if the standard input of the shell is connected to a terminal, the shell is considered an interactive shell. An interactive shell generally prompts before each command and handles programming and command errors differently (as described below).

  If command line argument `command_file` has been specified, then the shell treats it as the name of a file from which to read commands (a shell script). Otherwise, the shell reads commands from its standard input.
  
* **Lexical Structure**

  The simple_shell reads input in terms of lines from a file and breaks it up into words at whitespace (blanks and tabs), and at certain sequences of characters that are special to the shell called `operators`. Following is a list of operators (their meaning is discussed later) :
  * Control operators:
    `&&` `;` `||`

* **Aliases**

  An alias is a name and corresponding value set using the alias builtin command. The shell checks the word to see if it matches an alias, If it does, it replaces it in the input stream with its value. For example, if there is an alias called `lf` with the value `ls -F`, then the input:
  
  ```Shell
  lf foobar
  ```
    would become
  ```Shell
  ls -F foobar
  ```
  Aliases provide a convenient way for naive users to create shorthands for commands without having to learn how to create functions with arguments. They can also be used to create lexically obscure code. This use is discouraged.
  
* **Commands**

  The shell interprets the words it reads according to a language. Essentially though, a line is read and the first word of the line is recognized as a simple command.  Otherwise, a complex command or some other special construct may have been recognized.
  
* **Simple Commands**

  If a simple command has been recognized, the words are expanded as described in the section called “Expansions”, and the first remaining word is considered the command name and the command is located. The remaining words are considered the arguments of the command.
  
* **Search and Execution**

  There are two types of commands: builtin commands, and normal programs -- and the command is searched for (by name) in that order. They each are executed in a different way.

  Shell builtins are executed internally to the shell, without spawning a new process.

  Otherwise, the command is searched for as a normal program in the file system (as described in the next section). The shell will interpret the program in a subshell.
  
* **Path Search**

  When locating a command, the shell first looks for a builtin command by that name. If a builtin command is not found, one of two things happen:
  1) Command names containing a slash are simply executed without performing any searches.
  2) The shell searches each entry in PATH in turn for the command. The value of the PATH variable should be a series of entries separated by colons. Each entry consists of a directory name. The current directory may be indicated implicitly by an empty directory name, or explicitly by a single period.
  
* **Command Exit Status**
  
  Each command has an exit status that can influence the behaviour of other shell commands. The paradigm is that a command exits with zero for normal or success, and non-zero for failure, error, or a false indication. The man page for each command should indicate the various exit codes and what they mean. Additionally, the builtin commands return exit codes, as does an executed shell function.
  
* **Short-Circuit List Operators**

  `&&` and `||` are AND-OR list operators. `&&` executes the first command, and then executes the second command if the exit status of the first command is zero. `||` is similar, but executes the second command if the exit status of the first command is nonzero.  `&&` and `||` both have the same priority.

* **Special Parameters**

  **?** - Expands to the exit status of the most recent pipeline.
  
  **$** - Expands to the process ID of the invoked shell.  A subshell retains the same value of `$` as its parent.
  
* **Parameter Expansion**

  The format for parameter expansion is as follows:
  
  ``$expression``
  
* **White Space Splitting (Field Splitting)**

  The shell treats each whitespace or tab to split the results of parameter expansion into fields.
  
* **Builtins**

  This section lists the builtin commands which are builtin because they need to perform some operation that can't be performed by a separate process.
  
  * **alias [name[='value'] ...]**
  
    If name=value is specified, the shell defines an alias for each name whose value is given. If name is already an alias, replaces its value with value.
    
    If just names are specified, prints the aliases 1 per line, in the form name='value'.
    
    With no arguments, prints a list of all aliases, one per line, in the form name='value'.
    
  * **cd -**
  
  * **cd [DIRECTORY]**
    
    Changes the current directory of the process.
    
    If no argument is given to `cd` the command is interpreted as `cd $HOME`.
    
    Updates the environment variable `PWD` when changing directory.
    
  * **env**
  
    Prints the current environment.
    
  * **exit [STATUS]**
  
    Terminate the shell process.
    If `STATUS` is given it is used as the exit status of the shell, otherwise the exit status of the preceding command is used.
    
  * **help [BUILTIN]**
  
    Displays `BUILTIN` help section.
    
  * **history**
  
    Displays the history list, one command by line, preceded with line numbers (starting at `0`).
    On `exit`, write the entire history, without line numbers, to a file named `.simple_shell_history` in the directory `$HOME`.
    When the shell starts, read the file `.simple_shell_history` in the directory `$HOME` if it exists, and set the first line number to the total number of lines in the file modulo `4096`.
    
  * **setenv VARIABLE VALUE**
  
    Initialize a new environment variable, or modify an existing one.
    
  * **unsetenv VARIABLE**
  
    Remove an environment variable
    
# EXIT STATUS
Errors that are detected by the shell, such as a syntax error, will cause the shell to exit with a non-zero exit status. If the shell is not an interactive shell, the execution of the shell file will be aborted. Otherwise the shell will return the exit status of the last command executed, or if the exit builtin is used with a numeric argument, it will return the argument.

# FILES
$HOME/.simple_shell_history

# AUTHORS
[Tanguy Sauraneri](https://github.com/TS-N)

[Pierre Forcioli](https://github.com/pforciol)
