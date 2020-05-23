# core utils

Implemetations of Unix core utils in C.

### Why?
For get new skills in development and reverse engineering. 🙃

# Available
+ echo
+ head
+ cat
+ true
+ false

more in future...

# Decisions
### echo
Input text must be in quotation marks, e.g.:
```bash
echo -n "sample text"
```
**Why?**
In GNU echo isn't possible to run `--version` or `--help` option via a
command from PATH because echo returns all arguments to stdout.
You must specify full path for it (/bin/echo) to do that.

This implementation allows to run correctly:
```bash
echo --help
```

### true & false
These tools don't have any useless additional options. Simply returns
only 0 (true) or 1 (false).

### cat
Available only `-n` additional flag for numerate lines.
In my opinion other options are useless.
