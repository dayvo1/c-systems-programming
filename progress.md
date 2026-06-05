# C Learning Progress

## Exercise 1 — Variables & Basic Output
**Concepts:** `#include`, `main()`, variable declaration, `printf`, format specifiers
**Format specifiers:** `%d` int, `%f` float, `%c` char, `%p` pointer address
**Notes:**
- `\n` ends output with a newline
- `%.2f` limits float to 2 decimal places
- `main` should return `int`, always end with `return 0;`
- `%f` defaults to 6 decimal places

---

## Exercise 2 — Pointers
**Concepts:** memory addresses, pointer declaration, `&` (address-of), `*` (dereference)
**Notes:**
- `&x` gives the address of variable `x`
- `int *p` declares a pointer to an int
- `*p` reads the value at the address `p` holds
- `*p = value` writes through the pointer, changing the original variable

---

## Exercise 3 — Arrays & Memory
**Concepts:** arrays, `for` loops, array indexing, pointer arithmetic
**Notes:**
- An array name is a pointer to its first element — `arr == &arr[0]`
- Array elements are stored in consecutive memory
- Each `int` takes 4 bytes — addresses increment by 4
- `arr[i]` and `*(arr + i)` are identical — indexing is just pointer arithmetic
- Writing past the end of an array is a buffer overflow — corrupts adjacent memory

---

## Exercise 4 — Functions & the Stack
**Concepts:** functions, stack frames, pass-by-value vs pass-by-pointer
**Notes:**
- Every function call creates a stack frame holding local variables and the return address
- When a function returns, its stack frame is destroyed — locals don't persist
- Pass-by-value copies the data — the function can't modify the caller's variable
- Pass-by-pointer gives the function the address — it can modify the original

---

## Exercise 5 — Heap Memory (malloc & free)
**Concepts:** heap vs stack, `malloc`, `free`, memory leaks, use-after-free
**Notes:**
- Stack memory is automatic — allocated/freed with function calls
- Heap memory is manual — you control exactly how long it lives
- `malloc(n)` allocates n bytes, returns a `void *` — cast to your type
- Always use `sizeof` instead of hardcoding byte sizes
- Always `free` what you `malloc` — forgetting causes memory leaks
- After `free`, set the pointer to `NULL` — prevents use-after-free bugs
- Use-after-free: accessing freed memory corrupts silently — a major exploit class

---

## Exercise 6 — Strings
**Concepts:** `char[]`, null terminator, `string.h`, buffer overflow via strings
**Notes:**
- A string is a `char` array ending with `'\0'` — C uses it to find the end
- String literals `"hi"` automatically include `'\0'`
- `%s` prints a string, `%c` prints a single char
- `strlen` returns length excluding `'\0'`
- `strcat(dst, src)` appends in place — `dst` must be large enough or it's a buffer overflow
- `strcmp` returns `0` if equal, nonzero otherwise
- Store `strlen` result before a loop — don't recalculate every iteration

---

## Exercise 7 — Structs
**Concepts:** struct definition, dot vs arrow notation, passing structs by pointer
**Notes:**
- `struct` keyword is part of the type name in C — `struct Person p`, not `Person p`
- Define structs at file scope so all functions can use them
- Access fields with `.` on a value, `->` on a pointer (`ptr->x` == `(*ptr).x`)
- Pass structs by pointer to avoid copying — especially important for large structs
- Heap structs: `malloc(sizeof(struct Person))`, use `->`, then `free`
- Stack person needs `&p` to pass as pointer; heap pointer passed directly

---

## Exercise 8 — Linked List
**Concepts:** linked lists, struct self-reference, pointer traversal, node-based data structures
**Notes:**
- A linked list node holds data and a `next` pointer — last node's `next` is `NULL`
- `struct Node* next` inside the struct is a self-referential pointer — valid in C
- Always initialize `next` to `NULL` in `create_node`
- Traverse with `while (head != NULL) { head = head->next; }`
- When freeing a list, save `next` before freeing each node — or you lose the pointer
- Nodes don't need to be contiguous in memory — pointers connect them

---

## Exercise 9 — File I/O
**Concepts:** `FILE*`, `fopen`, `fprintf`, `fgets`, `fclose`, file modes
**Notes:**
- `fopen` returns `NULL` on failure — always check it
- Modes: `"r"` read, `"w"` write (creates/truncates), `"a"` append
- `fgets(buf, size, fp)` reads one line, returns `NULL` at end of file
- `fgets` keeps the `\n` from the file — don't add one in printf
- Use `sizeof(buf)` instead of hardcoding the size in fgets
- Always `fclose` what you `fopen` — same discipline as malloc/free
- In Unix, files, sockets, pipes, and stdin/stdout all use the same descriptor model

---

## Exercise 10 — Bit Manipulation
**Concepts:** bitwise operators, masks, shifting
**Notes:**
- `|` sets a bit, `&` checks/clears a bit, `^` toggles a bit, `~` flips all bits
- Build a mask with `1 << n` to target bit n
- Clear bit n: `val & ~(1 << n)`
- Check bit n: `(val & (1 << n)) != 0` — returns 1 or 0 directly
- Left shift by n multiplies by 2^n, right shift divides by 2^n
- Use `uint16_t` from `<stdint.h>` (not `u_int16_t` — that's a macOS BSD extension)

---

## Exercise 11 — TCP Server
**Concepts:** sockets, TCP lifecycle, `bind`, `listen`, `accept`, `send`, `close`
**Notes:**
- A socket is just a file descriptor — `socket()` returns an int
- Server lifecycle: `socket → bind → listen → accept → send/recv → close`
- `sockaddr_in` fields: `sin_family = AF_INET`, `sin_port = htons(port)`, `sin_addr.s_addr = INADDR_ANY`
- Always cast `&sa` to `(struct sockaddr *)` when passing to socket functions
- `bind` needs `sizeof(sa)` as a value; `accept` needs `&size` as a pointer (writes back to it)
- `accept` blocks until a client connects, returns a new fd for that client
- Send on `client_fd` not `s` — `s` is the listening socket, `client_fd` is the connection
- `ssize_t` is signed size — can return `-1` for errors
- `127.0.0.1` is loopback — always means this machine, never leaves the computer
- `INADDR_ANY` listens on all interfaces (loopback, WiFi, ethernet)
- Wrap `accept` in a `while(1)` loop to handle multiple connections

---

## Exercise 12 — TCP Client
**Concepts:** client socket lifecycle, `connect`, `recv`, `inet_pton`
**Notes:**
- Client lifecycle: `socket → connect → recv/send → close` (no bind/listen/accept)
- Fill `sockaddr_in` with the SERVER's address, not your own
- `inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)` converts IP string to binary
- `sizeof(struct)` not `sizeof(&struct)` — & gives pointer size (always 8 bytes on 64-bit)
- `recv` returns number of bytes received, `0` means connection closed, `-1` means error
- `%zd` is the correct format specifier for `ssize_t`
- For unknown message sizes: recv in a loop until return value is 0

---

## Exercise 13 — Persistent Server (accept loop + echo)
**Concepts:** server loop, echo, `snprintf`, recv return value
**Notes:**
- Wrap `accept` in `while(1)` to handle multiple connections
- Use `while((bytes = recv(...)) > 0)` — `> 0` handles both disconnect (0) and error (-1)
- `recv` may return data in chunks — always loop until 0
- `snprintf(buf, size, fmt, ...)` writes formatted string into a buffer safely
- Send `strlen(response)` not `sizeof(response)` — sizeof includes unused buffer bytes
- Send on `client_fd` not `server_socket`
- `close(client_fd)` after inner loop, before looping back to `accept`

---

## Exercise 14 — HTTP Server (basics)
**Concepts:** HTTP protocol, headers, Content-Length, HTML over TCP
**Notes:**
- HTTP is just formatted text over TCP — no magic
- Request format: `METHOD /path HTTP/1.1\r\nHeader: value\r\n\r\n`
- Response format: `HTTP/1.1 200 OK\r\nHeader: value\r\n\r\nbody`
- `\r\n` separates headers; blank line `\r\n\r\n` separates headers from body
- `Content-Length` must match the body length exactly — browser waits otherwise
- Use `strlen(body)` to get the correct Content-Length value
- Browsers use keep-alive — don't loop on recv waiting for disconnect, just recv once
- `snprintf` to build the response string, `strlen(response)` for send length
- `strnlen` needs two args; just use `strlen` for null-terminated strings

---

## Exercise 15 — HTTP Routing
**Concepts:** HTTP routing, `strstr`, if/else dispatch, 404 responses
**Notes:**
- First line of HTTP request contains method and path: `GET /about HTTP/1.1`
- `strstr(buf, "GET / ")` — note the space after `/` to avoid matching `/about`
- Always use if/else — never send multiple responses to one request
- 404 response uses `HTTP/1.1 404 Not Found` as status line
- Every web framework (Express, Flask, Django) does this same routing logic underneath

---

## Exercise 16 — Serve a File over HTTP
**Concepts:** static file serving, `fseek`/`ftell`, `fread`, dynamic buffer sizing
**Notes:**
- `fseek(fp, 0, SEEK_END)` + `ftell(fp)` gets file size; `fseek(fp, 0, SEEK_SET)` rewinds
- `fread(buf, 1, size, fp)` reads `size` bytes into `buf`
- `malloc(size + 1)` — always +1 for null terminator
- Use a separate response buffer for headers + body — never use file buf as snprintf destination
- Path is relative to where binary is run from — always run from project root
- `free(buf)`, `fclose(fp)`, `close(client_fd)` — clean up everything per request
- HTML is not compiled — browser interprets raw text bytes, guided by Content-Type header

---

## Exercise 17 — Fork: Handling Multiple Clients Simultaneously
**Concepts:** `fork()`, parent/child processes, zombie processes, `SIGCHLD`
**Notes:**
- `fork()` creates an exact copy of the process — parent gets child's PID, child gets 0
- Child handles the client; parent loops back to `accept()` immediately
- Child must `close(server_socket)` — it doesn't need to accept connections
- Parent must `close(client_fd)` — child owns it, parent should let go
- Child must call `exit(0)` — without it, child loops back to `accept()` as a second parent
- Without `signal(SIGCHLD, SIG_IGN)`, dead children become zombies and pile up
- Zombie processes fill the OS process table — can crash the whole system (learned the hard way)
- `signal(SIGCHLD, SIG_IGN)` tells OS to auto-clean dead children
- Always `#include <signal.h>` when using signals

---

## Exercise 18 — System Calls
**Concepts:** `open`, `read`, `write`, `close`, `lseek`, file descriptors, stdin/stdout/stderr
**Notes:**
- `write(1, buf, n)` writes to stdout; `read(0, buf, n)` reads from stdin
- fd 0 = stdin, fd 1 = stdout, fd 2 = stderr — always open in every process
- `open()` flags: `O_RDONLY`, `O_WRONLY`, `O_CREAT`, `O_TRUNC` — combine with `|`
- Mode `0644` sets file permissions — only matters when `O_CREAT` is used
- `lseek(fd, 0, SEEK_END)` + `lseek(fd, 0, SEEK_SET)` to get file size for malloc
- Use `bytes` return value from `read` in `write` — not `sizeof(buf)`
- `malloc(size + 1)` when using buffer as a string — room for null terminator
- `#include <fcntl.h>` for open flags

---

## Exercise 19 — Processes & exec()
**Concepts:** `execl`, `execlp`, `execv`, `waitpid`, fork+exec pattern
**Notes:**
- `exec` replaces the current process with a new program — never returns on success
- Always add `exit(1)` after `exec` in case it fails — child must not fall through
- `arg0` is always the program name by convention, actual args start at `arg1`
- `execlp` searches `$PATH` — no need for full path like `/bin/ls`
- `waitpid(pid, &status, 0)` — parent blocks until that specific child exits
- `status` is written by the OS — non-zero means child failed
- fork+exec is how every shell runs programs — fork a child, child execs the program
- Parent reaches code after the if/else; child never does (it exec'd and exited)

---

## Exercise 20 — Pipes
**Concepts:** `pipe()`, inter-process communication, read/write ends, fd assignment
**Notes:**
- `pipe(fds)` fills `fds[0]` (read end) and `fds[1]` (write end)
- Always declare `int fds[2]` — pipe needs exactly 2 slots
- After `fork()` both processes have both ends — close the one you don't use
- If write end stays open in reader, `read()` blocks forever waiting for more data
- OS assigns lowest available fd numbers — typically 3 and 4 on a fresh process
- `|` in shell is just `pipe()` + `fork()` + `exec()` in a loop over commands
- Data flows one way: write end → pipe buffer → read end

---

## Exercise 21 — dup2 & I/O Redirection
**Concepts:** `dup2`, `STDOUT_FILENO`, I/O redirection, intercepting program output
**Notes:**
- `dup2(oldfd, newfd)` makes `newfd` point to the same thing as `oldfd`
- `dup2(fds[1], STDOUT_FILENO)` redirects stdout into the pipe write end
- After `dup2`, close the original fds — stdout already points to the pipe
- Programs don't know their stdout was redirected — they just write normally
- Use `write(1, buf, bytes)` for raw pipe output — not `printf` (not null-terminated)
- Pipes aren't seekable — can't use `lseek` to get size upfront, use a large buffer
- This is how `ls | grep` works — `ls` stdout → pipe → `grep` stdin

---

## Exercise 22 — Mini Shell
**Concepts:** shell loop, `fgets`, `strtok`, `execvp`, `strcspn`, fork+exec in a loop
**Notes:**
- A shell is just `while(1) { prompt → read → parse → fork → exec → wait }`
- `fgets(buf, size, stdin)` reads a line including the `\n` — strip it with `buf[strcspn(buf, "\n")] = '\0'`
- `strtok` is destructive — replaces delimiters with `'\0'` one at a time, one per call
- First call: `strtok(str, " ")`, subsequent calls: `strtok(NULL, " ")` — it remembers position internally
- Build a fixed `char* argv[64]` — no need to count tokens first
- `argv` must be NULL-terminated — strtok returns NULL at end, store it as the last element
- `execvp(argv[0], argv)` — searches PATH, takes the full argv array
- Always `exit(1)` after `execvp` in the child — execvp only returns on failure
- Fork so the child gets replaced by the command, parent survives and loops back to prompt
- Child inherits parent's stdout (the PTY) — command output goes to your terminal automatically
- `strcmp(argv[0], "exit") == 0` to detect the exit command and break the loop

---

## Exercise 23 — Shell with Pipes
**Concepts:** pipe in a shell, splitting argv, two children, dup2 on both ends
**Notes:**
- Scan argv for `"|"` using `strcmp(argv[j], "|") == 0` — save the index as `pipe_idx`
- Null-check before strcmp — `argv[j] != NULL && strcmp(...)` — scan loop must be `j < i` not `j < i+1`
- Split argv into `left[]` (0 to pipe_idx-1, then NULL) and `right[]` (pipe_idx+1 onward)
- Right array index: `right[l - (pipe_idx + 1)] = argv[l]` — right starts at 0, not pipe_idx+1
- Fork child_1 first: `dup2(fds[1], STDOUT_FILENO)` → close both fds → execvp left command
- Fork child_2 second: `dup2(fds[0], STDIN_FILENO)` → close both fds → execvp right command
- Parent closes both fds, then waitpid for both children
- Parent must close fds or right child blocks forever waiting for EOF on the pipe
- `cd` can't be forked — it only works as a built-in calling `chdir()` directly in the shell process
- If no pipe found, run command normally (same as ex22)
