# CppHead Usage Guide

CppHead is a fast, local-first, C++23 reimplementation of the Unix `head` command. It streams the first N lines of one or more files (or stdin) with minimal overhead.

## Synopsis

```
head [OPTION]... [FILE]...
```

If no `FILE` is given, or `FILE` is `-`, CppHead reads from standard input.

## Options

| Option | Description |
|---|---|
| `-n [NUM]`, `--lines=[NUM]` | Print the first `NUM` lines instead of the default 10. |
| `-NUM` | Shorthand for `-n NUM` (e.g. `-5` is equivalent to `-n 5`). |
| `-q`, `--quiet`, `--silent` | Never print file name headers. |
| `-v`, `--verbose` | Always print file name headers, even for a single file. |
| `--version` | Print version and build metadata, then exit. |
| `-h`, `--help` | Print usage information, then exit. |

## Examples

Print the first 10 lines of a file (default):

```
head notes.txt
```

Print the first 5 lines of a file:

```
head -5 notes.txt
head -n 5 notes.txt
head --lines=5 notes.txt
```

Read from standard input:

```
cat notes.txt | head -n 20
head -n 20 -
```

Print the first lines of multiple files, with headers:

```
head -n 3 a.txt b.txt c.txt
```

Output:

```
==> a.txt <==
line 1
line 2
line 3

==> b.txt <==
line 1
line 2
line 3

==> c.txt <==
line 1
line 2
line 3
```

Suppress headers even with multiple files:

```
head -q -n 3 a.txt b.txt
```

Force headers even with a single file:

```
head -v -n 3 a.txt
```

## Exit Codes

| Code | Meaning |
|---|---|
| 0 | Success |
| 1 | One or more input files could not be opened or read |
| 2 | Invalid or malformed command-line arguments |

## Performance Notes

CppHead decouples standard I/O and uses stream buffering to minimize syscall overhead. In benchmarks, it processes 1,000 lines in under 400 microseconds. For very large files, prefer piping through stdin over shell-level file globbing where possible, to avoid unnecessary intermediate buffering.

## Building From Source

```
cmake -B build -S .
cmake --build build --config Release
```

Or, on Windows, using the provided automation script:

```
.\build.ps1
```

## Running Tests

```
ctest --test-dir build --output-on-failure -C Release
```

## Version Metadata

CppHead embeds its version and build timestamp at compile time. Run:

```
head --version
```

to confirm which build you're running.
