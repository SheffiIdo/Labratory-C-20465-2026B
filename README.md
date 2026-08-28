# Systems Programming in C & Two-Pass Assembler

A collection of systems-level C projects and utilities developed by **Ido Sheffi**, featuring an automated compilation toolchain, strict ANSI C compliance, and a full-featured **Two-Pass Assembler**.

---

## 🌟 Featured Project: [Two-Pass Assembler (`/maman14`)](./maman14)

The centerpiece of this repository is a complete **Two-Pass Assembler** developed in ANSI C that translates assembly code into machine binary/hex code for a custom CPU architecture.

* **Two-Pass Pipeline:** Handles pre-processor macro expansion, dynamic symbol lookup tables, memory offset calculations, and binary translation files (`.ob`, `.ent`, `.ext`).
* **Memory Safety:** Strict dynamic memory management with zero memory leaks, validated using **Valgrind**.
* **Modern CI/CD:** Integrated **GitHub Actions** CI pipeline executing automated test suites on **Ubuntu 24.04**.

👉 **[View Full Assembler Documentation, Architecture & Source Code ➔](./maman14)**

---

## 📂 Repository Structure

| Directory | Module / Project | Key Concepts |
| :--- | :--- | :--- |
| **[`/maman14`](./maman14)** | **Two-Pass Assembler (Final Project)** | Pre-assembler macro expansion, two-pass compilation pipeline, symbol tables, binary/hex machine code emission, memory safety (`Valgrind`) |
| **[`/maman23`](./maman23)** | **File Offset Traversal CLI (`seek`)** | Command-line arguments (`argc`, `argv`), low-level stream positioning (`fseek`), batch file processing, error handling |
| **[`/maman22`](./maman22)** | **Complex Number Interpreter (`mycomp`)** | Modular multi-file design (`.h`/`.c`), `struct` & `typedef` data abstraction, interactive CLI parsing, syntax validation |
| **[`/maman12`](./maman12)** | **Dynamic Array & Preprocessor Macros (`difference_and_sum`)** | Pointer pass-by-reference, dynamic memory reallocation (`realloc`), preprocessor calculation macros vs. functions, I/O redirection |
| **[`/maman11`](./maman11)** | **String Parsing & Bitwise Operations** | In-place string parsing without auxiliary buffers (`remove_blanks`), bitwise operators & masking (`turn_on`), portability |

---

## 📖 Module Descriptions

### [Maman 14: Two-Pass Assembler](./maman14)
* **Pre-Assembler Stage:** Performs macro scanning, extraction, and in-place expansion to generate clean `.am` files.
* **First Pass:** Builds the dynamic symbol table, validates syntax, calculates data counter (DC) and instruction counter (IC) offsets, and constructs intermediate machine code structures.
* **Second Pass:** Resolves label memory references, calculates relative jump offsets for branch instructions, and outputs `.ob` (machine code), `.ent` (entry symbols), and `.ext` (external symbols) files.

### [Maman 23: File Offset Traversal (`seek`)](./maman23)
* Implements a CLI tool that accepts a target byte index and multiple file paths via `argc`/`argv`.
* Utilizes `fseek` to jump directly to specific byte offsets without linear scanning and outputs the corresponding ASCII code.
* Validates parameter inputs, verifies file access, and handles bounds-checking for files shorter than the specified offset.

### [Maman 22: Interactive Complex Number Interpreter (`mycomp`)](./maman22)
* Built with a modular multi-file architecture (`mycomp.c`, `complex.c`, `complex.h`).
* Implements abstract data structures for complex numbers using `typedef struct` and supports arithmetic operations (addition, subtraction, real/imaginary multiplications, absolute values).
* Includes a robust CLI parser with strict validation for extraneous tokens, missing parameters, consecutive commas, and syntax errors.

### [Maman 12: Dynamic Memory & Macros (`difference_and_sum`)](./maman12)
* Evaluates differences between preprocessor macro expansions and C functions performing calculations with address pointers.
* Manages dynamic arrays that automatically expand to accommodate user input streams using `realloc`.

### [Maman 11: String Manipulation & Bit Manipulation](./maman11)
* **`remove_blanks`:** Removes whitespace characters (`space`, `\t`, `\n`) in-place in a single pass without auxiliary memory buffers.
* **`turn_on`:** Activates the 17th bit from the right using bitwise shifts and masks, printing the binary output without arrays or recursion.

---

## 🛠️ Engineering Standards & Toolchain

* **IDE:** CLion
* **Compilers:** GCC / Clang
* **Language Standard:** ANSI C (C90) compiled with `-Wall -ansi -pedantic`
* **Build System:** Dedicated modular `Makefile` for every assignment
* **Testing & Environment:** Containerized via **Docker** (Ubuntu) and tested locally on macOS
* **Memory Verification:** Dynamic memory profiling and leak detection via **Valgrind**
* **CI/CD:** Automated build and regression test suites via **GitHub Actions**

---

## 👤 Author

* **Ido Sheffi** – [GitHub](https://github.com/SheffiIdo) • [LinkedIn]([https://www.linkedin.com](https://www.linkedin.com/in/ido-sheffi-840273366?utm_source=share_via&utm_content=profile&utm_medium=member_ios))