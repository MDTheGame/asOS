# asOS - Absolute Solver OS
------

## 1. Information
The **sub-system** for Windows, **based on C.** Inspired by the `Absolute Solver` from `Murder Drones`.

asOS is a lightweight command-line interface (CLI) designed to provide a simple and efficient way to interact with your system. It offers a set of commands for file management, directory navigation, and running external programs.

------

## 2. Creators
- **NTheCuteDrone**
- **DeepSeek**

------

# Commands
------

## 1. Help
**Displays the entire list of available commands.**

Example:
```
SYS:/C:\Users\{user}> help
Available commands:
  help - Show this help message
  create <filename> <content> - Create a file
  read <filename> - Read a file
  ls / dir - List files in current directory
  cd <path> - Change directory
  mkdir <path> - Create a directory
  run <program> - Run an external program
  about - Show information about asOS
  exit - Shutdown asOS
```

------

## 2. Create
**Creates a new file with the specified content.**

Usage:
```
create <filename> <content>
```

Example:
```
SYS:/C:\Users\{user}> create example.txt Hello, World!
File 'example.txt' created.
```

------

## 3. Read
**Reads and displays the content of a file.**

Usage:
```
read <filename>
```

Example:
```
SYS:/C:\Users\{user}> read example.txt
Content of 'example.txt':
Hello, World!
```

------

## 4. List Files (ls/dir)
**Lists all files and directories in the current directory.**

Usage:
```
ls
```
or
```
dir
```

Example:
```
SYS:/C:\Users\{user}> ls
Files in current directory:
 Volume in drive C is OS
 Volume Serial Number is XXXX-XXXX

 Directory of C:\Users\{user}

01/01/2023  12:00 PM    <DIR>          .
01/01/2023  12:00 PM    <DIR>          ..
01/01/2023  12:00 PM                12 example.txt
               1 File(s)             12 bytes
               2 Dir(s)   XXX,XXX,XXX,XXX bytes free
```

------

## 5. Change Directory (cd)
**Changes the current directory to the specified path.**

Usage:
```
cd <path>
```

Example:
```
SYS:/C:\Users\{user}> cd C:\Users
Changed directory to: C:\Users
```

------

## 6. Make Directory (mkdir)
**Creates a new directory at the specified path.**

Usage:
```
mkdir <path>
```

Example:
```
SYS:/C:\Users\{user}> mkdir new_folder
Directory 'new_folder' created.
```

------

## 7. Run
**Runs an external program.**

Usage:
```
run <program>
```

Example:
```
SYS:/C:\Users\{user}> run notepad.exe
(Opens Notepad)
```

------

## 8. About
**Displays information about asOS.**

Usage:
```
about
```

Example:
```
SYS:/C:\Users\{user}> about
---asOS---
Version: alpha-0.1
Creators: NTheCuteDrone, DeepSeek

The sub-system based on C & motives = Absolute Solver from Murder Drones

Thanks for using asOS!
```

------

## 9. Exit
**Shuts down asOS.**

Usage:
```
exit
```

Example:
```
SYS:/C:\Users\{user}> exit
Shutting down asOS...
```

------

# Installation (Option 1)
1. Clone the repository or download the source code.
2. Compile the code using a C compiler (e.g., GCC):
   ```
   gcc asOS-x86_64.c -o asOS.exe
   ```
3. Run the compiled executable:
   ```
   ./asOS.exe
   ```

## or

# Installation (Option 2, not 100% work)
1. Download a [release](https://github.com/MDTheGame/asOS/releases/)
2. Run a `asOS.exe`

------

# Contributing
Contributions are welcome! If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.---

------

# Acknowledgments
- Inspired by the **Absolute Solver** from **Murder Drones**.
- Thanks to **DeepSeek** for assistance in development.
```
