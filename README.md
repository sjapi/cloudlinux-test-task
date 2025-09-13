# CloudLinux Test Task 

## Task 1: C File Backup Utility

`backup_c_files.sh` - Creates backup copies of all `*.c` files with `.orig` extension

`remove_backup_c_files.sh` - Removes all `.orig` backups (bonus)

```bash
$ cd task3
$ bash ../task1/backup_c_files.sh
$ ./../task2/list_dir 
/home/Desktop/cloudlinux-test-task/task3
    output.txt
    include
        utils.h
    Makefile
    src
        utils.c.orig        # <- backup created
        main.c
        utils.c
        main.c.orig         # <- backup created
        validator.c
        execute.c.orig      # <- backup created
        execute.c
        validator.c.orig    # <- backup created
```

## Task 2: Simple Directory Lister

C implementation of basic `ls` functionality using `opendir()`, `readdir()`, `closedir()`

```bash
$ cd task2
$ make
$ cd .. && ./task2/list_dir
/home/Desktop/cloudlinux-test-task
    task3
        include
            utils.h
        Makefile
        src
            main.c
            utils.c
            validator.c
            execute.c
    task2
        main.c
        Makefile
        list_dir
    task1
        remove_backup_c_files.sh
        backup_c_files.sh
    README.md
```

#### Bonus

Added ability to specify path for listing directory

```bash
$ cd task2
$ make
$ ./list_dir ../tests/  # <- Specified path
../tests/
	test_task3.sh
	test_task1.sh
	test_task2.sh
```

## Task 3: Command Pipeline Executor

Executes: `prog1 && prog2 | prog3 > file`

* Runs `prog1` first; stops if it fails
* Pipes `prog2` output to `prog3` only if `prog1` succeeds
* Redirects `prog3` output to file

**Usage:** `./run_cmds prog1 prog2 prog3 outfile ` 

```bash
$ cd task3
$ make
$ ./run_cmds /bin/true /bin/echo /bin/wc output.txt
$ cat output.txt 
      1       0       1
```

System calls used: `fork()`, `pipe()`, `dup2()`, `execl()`, `waitpid()`

---

### Build

Task 2 and task 3 use `Makefile` with standard targets: `all`, `clean`, `fclean`, `re`

## Tests

This folder contains **bonus** shell scripts to automatically test the programs from the tasks

Each `.sh` file sets up a temporary sandbox, runs the corresponding program, and checks the results

- `test_task1.sh` – tests the backup and cleanup scripts for C files  
- `test_task2.sh` – tests the simple directory lister program  
- `test_task3.sh` – tests the shell-like command runner program 

```bash
$ cd tests
$ bash test_task1.sh 
[INFO] Running backup_c_files.sh...
[PASS] Found backup: src/main.c.orig
[PASS] Found backup: src/util.c.orig
[PASS] Not-C file not backed up
[INFO] Running remove_backup_c_files.sh...
[PASS] Backup deleted: src/main.c.orig
[PASS] Backup deleted: src/util.c.orig
✅ Taks 1 passed all tests
$ bash test_task2.sh
...
✅ Task 2 passed all tests
$ bash test_task3.sh
...
✅ Task 3 passed all tests
```

