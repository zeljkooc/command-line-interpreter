# C++ Command Line Interpreter (CLI Shell)

A C++ command-line interpreter that implements core shell architecture, lexical/syntax parsing, input/output stream redirection, batch script execution, and multi-stage execution pipelines (`pipes`).

---

## 📌 System Architecture & Core Concepts

The system operates as an interactive shell or a batch interpreter, mimicking standard Unix/POSIX CLI behaviors:

* **Command Prompt:** Dynamic, customizable prompt (`$` by default, modifiable via `prompt`).
* **Lexical Parser:** Processes lines up to 512 characters. Handles whitespace separation, quoted literals (`"..."`), special operators (`|`, `<`, `>`, `>>`), and positional error reporting with character offset tracking.
* **Stream Abstraction:** Unified treatment of `std::cin`/`std::cout`, in-memory string arguments, and filesystem streams via standard standard library/custom wrappers.
* **Redirection Engine:** Supports input redirection (`<`) and output redirection (overwrite `>` or append `>>`).
* **Pipelining Engine:** Unidirectional character/stream flow between sequential commands connected by the pipe operator (`|`).

---

## 🛠️ Supported Commands

| Command | Format | Options / Arguments | Description |
| :--- | :--- | :--- | :--- |
| `echo` | `echo [arg]` | — | Passes input stream directly to output stream unchanged. |
| `prompt` | `prompt "new_prompt"` | — | Updates the shell command prompt symbol. |
| `time` | `time` | — | Outputs the current system time. |
| `date` | `date` | — | Outputs the current system date. |
| `touch` | `touch filename` | — | Creates an empty file in the working directory. |
| `truncate` | `truncate filename` | — | Clears the contents of an existing file. |
| `rm` | `rm filename` | — | Deletes a file from the filesystem. |
| `wc` | `wc -opt [arg]` | `-w` (words), `-c` (chars) | Counts words or total characters in the input stream. |
| `tr` | `tr [arg] -what [with]` | — | Replaces occurrences of string `what` with `with`, or strips `what` if `with` is omitted. |
| `head` | `head -nCOUNT [arg]` | `-nCOUNT` (up to 5 digits) | Outputs the first $N$ lines of the input stream. |
| `batch` | `batch filename` | — | Executes CLI commands sequentially from a batch file. |

---

## ⚙️ Technical Requirements & Design Patterns

* **Language:** Modern C++ (C++17 / C++20)
* **Object-Oriented Design:**
  * Strict abstraction, single-responsibility principle (SRP), and clean encapsulation.
  * Polymorphic command hierarchy (`Command` base class with specific execution contexts).
  * Robust resource management (RAII, Rule of 5 for dynamic buffer handle/file stream wrappers).
  * Exception-driven error handling for syntax errors, OS filesystem exceptions, and invalid semantic pipe bounds.

---

## 🚀 Building & Running

### Prerequisites
* GCC / Clang / MSVC compiler with C++17 support.
* CMake or standard Makefile build configuration.
