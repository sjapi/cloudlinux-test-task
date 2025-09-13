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

## Task 3: Command Pipeline Executor

Executes: `prog1 && prog2 | prog3 > file`

* Runs `prog1` first; stops if it fails
* Pipes `prog2` output to `prog3` only if `prog1` succeeds
* Redirects `prog3` output to file

**Usage:** `./run_cmds prog1 prog2 prog3 outfile ` 

```bash
$ cd task3
$ make
$ ./run_cmds /bin/true /bin/echo /usr/bin/wc output.txt
$ cat output.txt 
      1       0       1
```

System calls used: `fork()`, `pipe()`, `dup2()`, `execl()`, `waitpid()`

---

Task 1 and task 2 use `make` with standard targets: `all`, `clean`, `fclean`, `re`
