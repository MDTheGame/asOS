# asOS - Absolute Solver OS
-------------------------------------------------------------------------------

1. Information
-------------------------------------------------------------------------------
The **sub-system** for Windows, **based on C.** Inspired by the `Absolute Solver` from `Murder Drones`.

asOS is a lightweight command-line interface (CLI) designed to provide a simple and efficient way to interact with your system. It offers a set of commands for file management, directory navigation, user management, and running external programs.

-------------------------------------------------------------------------------
2. Creators
-------------------------------------------------------------------------------
- **NTheCuteDrone**
- **DeepSeek**

-------------------------------------------------------------------------------
Commands
-------------------------------------------------------------------------------

1. Help
-------------------------------------------------------------------------------
**Displays the entire list of available commands.**

Example:
```
SYS:/C:\Users\{user}> help
Available commands:
  -> help - Show this help message
  -> create <filename> <content> - Create a file
  -> read <filename> - Read a file
  -> rm/del <filename> - Delete a file
  -> ls / dir - List files in current directory
  -> cd <path> - Change directory
  -> mkdir <path> - Create a directory
  -> run <program> - Run an external program
  -> about - Show information about asOS
  -> register - Register a new user
  -> login - Login as a user
  -> logout - Logout current user
  -> setlang <language> - Set language (English/Russian) (BETA)
  -> users - List all users
  -> deleteuser <username> - Delete a user
  -> restrict <username> - Restrict a user
  -> grant <username> - Grant permissions to a user
  -> disableperm <username> <permission> - Disable a permission for a user
  -> enableperm <username> <permission> - Enable a permission for a user
  -> np <filename> - asOS Notepad
  -> pk - Process Killer (Task Manager)
  -> pac [install/update/uninstall/ --version] - PAC System (Package for asOS based on C)
  -> exit - Shutdown asOS
```

-------------------------------------------------------------------------------
2. Create
-------------------------------------------------------------------------------
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

-------------------------------------------------------------------------------
3. Read
-------------------------------------------------------------------------------
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

-------------------------------------------------------------------------------
4. Delete (rm/del)
-------------------------------------------------------------------------------
**Deletes a file.**

Usage:
```
rm <filename>
```
or
```
del <filename>
```

Example:
```
SYS:/C:\Users\{user}> rm example.txt
File 'example.txt' deleted.
```

-------------------------------------------------------------------------------
5. List Files (ls/dir)
-------------------------------------------------------------------------------
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

-------------------------------------------------------------------------------
6. Change Directory (cd)
-------------------------------------------------------------------------------
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

-------------------------------------------------------------------------------
7. Make Directory (mkdir)
-------------------------------------------------------------------------------
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

-------------------------------------------------------------------------------
8. Run
-------------------------------------------------------------------------------
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

-------------------------------------------------------------------------------
9. About
-------------------------------------------------------------------------------
**Displays information about asOS.**

Usage:
```
about
```

Example:
```
SYS:/C:\Users\{user}> about
---asOS---
Version: alpha-0.2
Creators: NTheCuteDrone, DeepSeek

The sub-system based on C & motives = Absolute Solver from Murder Drones

Thanks for using asOS!
```

-------------------------------------------------------------------------------
10. Register
-------------------------------------------------------------------------------
**Registers a new user.**

Usage:
```
register
```

Example:
```
SYS:/C:\Users\{user}> register
Enter username: testuser
Enter password: testpass
Enter shortname: test
User 'testuser' registered.
```

-------------------------------------------------------------------------------
11. Login
-------------------------------------------------------------------------------
**Logs in as a user.**

Usage:
```
login
```

Example:
```
SYS:/C:\Users\{user}> login
Enter username: testuser
Enter password: testpass
User 'testuser' logged in.
```

-------------------------------------------------------------------------------
12. Logout
-------------------------------------------------------------------------------
**Logs out the current user.**

Usage:
```
logout
```

Example:
```
SYS:/C:\Users\{user}> logout
User 'testuser' logged out.
```

-------------------------------------------------------------------------------
13. Set Language (setlang)
-------------------------------------------------------------------------------
**Sets the language of the system (English/Russian).**

Usage:
```
setlang <language>
```

Example:
```
SYS:/C:\Users\{user}> setlang Russian
Language set to Russian.
```

-------------------------------------------------------------------------------
14. Users
-------------------------------------------------------------------------------
**Lists all registered users.**

Usage:
```
users
```

Example:
```
SYS:/C:\Users\{user}> users
Users:
  testuser (test) - Permissions: CREATE DELETE READ MKDIR CD RUN
```

-------------------------------------------------------------------------------
15. Delete User (deleteuser)
-------------------------------------------------------------------------------
**Deletes a user.**

Usage:
```
deleteuser <username>
```

Example:
```
SYS:/C:\Users\{user}> deleteuser testuser
User 'testuser' deleted.
```

-------------------------------------------------------------------------------
16. Restrict User (restrict)
-------------------------------------------------------------------------------
**Restricts a user's permissions.**

Usage:
```
restrict <username>
```

Example:
```
SYS:/C:\Users\{user}> restrict testuser
User 'testuser' restricted.
```

-------------------------------------------------------------------------------
17. Grant Permissions (grant)
-------------------------------------------------------------------------------
**Grants permissions to a user.**

Usage:
```
grant <username>
```

Example:
```
SYS:/C:\Users\{user}> grant testuser
User 'testuser' granted permissions.
```

-------------------------------------------------------------------------------
18. Disable Permission (disableperm)
-------------------------------------------------------------------------------
**Disables a specific permission for a user.**

Usage:
```
disableperm <username> <permission>
```

Example:
```
SYS:/C:\Users\{user}> disableperm testuser CREATE
Permission 'CREATE' disabled for user 'testuser'.
```

-------------------------------------------------------------------------------
19. Enable Permission (enableperm)
-------------------------------------------------------------------------------
**Enables a specific permission for a user.**

Usage:
```
enableperm <username> <permission>
```

Example:
```
SYS:/C:\Users\{user}> enableperm testuser CREATE
Permission 'CREATE' enabled for user 'testuser'.
```

-------------------------------------------------------------------------------
20. Notepad (np)
-------------------------------------------------------------------------------
**Opens asOS Notepad to edit a file.**

Usage:
```
np <filename>
```

Example:
```
SYS:/C:\Users\{user}> np example.txt
(Opens asOS Notepad to edit example.txt)
```

-------------------------------------------------------------------------------
21. Process Killer (pk)
-------------------------------------------------------------------------------
**Opens the Process Killer (Task Manager).**

Usage:
```
pk
```

Example:
```
SYS:/C:\Users\{user}> pk
(Opens Process Killer)
```

-------------------------------------------------------------------------------
22. PAC System (pac)
-------------------------------------------------------------------------------
**Manages packages in asOS.**

Usage:
```
pac <install|update|uninstall|--version>
```

Example:
```
SYS:/C:\Users\{user}> pac install package.spac
Package installed from 'package.spac'
```

-------------------------------------------------------------------------------
23. Exit
-------------------------------------------------------------------------------
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

-------------------------------------------------------------------------------
Installation
-------------------------------------------------------------------------------
1. Download the latest release from the [releases page](https://github.com/MDTheGame/asOS/releases/).
2. Extract the files and run `asOS.exe`.

-------------------------------------------------------------------------------
Contributing
-------------------------------------------------------------------------------
Contributions are welcome! If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.

-------------------------------------------------------------------------------
Acknowledgments
-------------------------------------------------------------------------------
- Inspired by the **Absolute Solver** from **Murder Drones**.
- Thanks to **DeepSeek** for assistance in development.
