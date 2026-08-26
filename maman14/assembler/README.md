# 🚀 Custom C Assembler (Maman 14)

This project is a custom two-pass assembler written in standard C90 (ANSI C). It was developed as the final project (Maman 14) for the **Systems Programming Laboratory (20465)** course at the Open University of Israel.

The assembler translates a custom 32-bit assembly language into machine code, featuring a fully functional macro pre-processor, a dual-pass translation engine, and strict error validation. It is designed with a heavy emphasis on dynamic memory safety, modular architecture, and strict compiler compliance.

**Author:** עידו שפי  
**Environment:** Ubuntu 24.04 / GCC

---

## ✨ Key Features
* **Strict C90 Compliance:** Compiled with `-Wall -ansi -pedantic` with zero warnings.
* **100% Memory Safe:** Verified by Valgrind. Features a custom architectural fail-safe (`memory_allocation_fail`) that prevents memory leaks even during fatal OS-level out-of-memory errors.
* **Continuous Integration:** Fully automated GitHub Actions CI pipeline testing positive/negative compilation and strict memory leak checks.
* **Robust Error Handling:** An advanced error engine that catches syntax mistakes, illegal operands, buffer overflows, and undefined references without crashing.

---

## ⚙️ The Compilation Pipeline

The assembler processes each `.as` source file through four distinct, isolated stages:

1. **Pre-Processor (`.as` -> `.am`)**
   Scans the raw source file to identify and store macro definitions (`mcro` / `mcroend`). It strips all comments and expands the stored macros whenever they are called, generating a clean `.am` file.
2. **First Pass**
   Reads the expanded `.am` file to build the **Symbol Table**. It calculates the Instruction Counter (IC) and Data Counter (DC), verifies label validity, and partially encodes recognized instructions, leaving placeholders for forward-branching labels.
3. **Second Pass**
   Resolves all missing label addresses. It finalizes the 32-bit machine code for branch distances (I-Type) and absolute jump locations (J-Type), while tracking external symbol calls.
4. **File Generation**
   Translates the internal memory arrays into formatted output files:
    * `.ob` (Object File): Hexadecimal representation of the machine code.
    * `.ent` (Entries File): Memory addresses of externally accessible labels.
    * `.ext` (Externals File): Memory locations where external scripts are required.

---

## 📂 Project Structure

```text
maman14
└── assembler
    ├── Header files
    │   ├── errors.h
    │   ├── extern_usage.h
    │   ├── file_writer.h
    │   ├── first_pass.h
    │   ├── globals.h
    │   ├── macro_table.h
    │   ├── parser.h
    │   ├── preproc.h
    │   ├── second_pass.h
    │   ├── symbol_table.h
    │   └── utils.h
    ├── Inputs
    │   ├── booklet_example.as
    │   ├── booklet_example_2.as
    │   ├── invalid_input_1.as
    │   ├── invalid_input_2.as
    │   ├── invalid_input_3.as
    │   ├── invalid_input_4.as
    │   ├── invalid_input_5.as
    │   ├── invalid_input_6.as
    │   ├── valid_input_1.as
    │   ├── valid_input_2.as
    │   ├── valid_input_3.as
    │   └── valid_input_4.as
    ├── Outputs
    │   ├── Screenshots
    │   │   ├── Invalid_input_1.png
    │   │   ├── Invalid_input_2.png
    │   │   ├── invalid_input_3.png
    │   │   ├── invalid_input_4.png
    │   │   ├── invalid_input_5.png
    │   │   ├── invalid_input_6.png
    │   │   └── valid_input_1-4.png
    │   ├── booklet_example.am
    │   ├── booklet_example.ent
    │   ├── booklet_example.ext
    │   ├── booklet_example.ob
    │   ├── booklet_example_2.am
    │   ├── booklet_example_2.ent
    │   ├── booklet_example_2.ext
    │   ├── booklet_example_2.ob
    │   ├── invalid_input_2.am
    │   ├── invalid_input_4.am
    │   ├── invalid_input_5.am
    │   ├── invalid_input_6.am
    │   ├── valid_input_1.am
    │   ├── valid_input_1.ent
    │   ├── valid_input_1.ext
    │   ├── valid_input_1.ob
    │   ├── valid_input_2.am
    │   ├── valid_input_2.ent
    │   ├── valid_input_2.ext
    │   ├── valid_input_2.ob
    │   ├── valid_input_3.am
    │   ├── valid_input_3.ent
    │   ├── valid_input_3.ext
    │   ├── valid_input_3.ob
    │   ├── valid_input_4.am
    │   ├── valid_input_4.ent
    │   ├── valid_input_4.ext
    │   └── valid_input_4.ob
    ├── Source files
    │   ├── assembler.c
    │   ├── errors.c
    │   ├── extern_usage.c
    │   ├── file_writer.c
    │   ├── first_pass.c
    │   ├── macro_table.c
    │   ├── parser.c
    │   ├── preproc.c
    │   ├── second_pass.c
    │   ├── symbol_table.c
    │   └── utils.c
    ├── assembler
    ├── assembler.o
    ├── errors.o
    ├── extern_usage.o
    ├── file_writer.o
    ├── first_pass.o
    ├── macro_table.o
    ├── Makefile
    ├── parser.o
    ├── preproc.o
    ├── README.md
    ├── second_pass.o
    ├── symbol_table.o
    └── utils.o
```

---

## 🛠️ Installation & Usage

### Prerequisites
* GCC Compiler
* Make
* Linux Environment (Ubuntu 24.04 recommended)

### Compilation
Clone the repository and compile the project using the provided Makefile:
```bash
make clean
make
```
This will generate the `assembler` executable.

### Execution
Run the assembler by passing one or more assembly files as arguments.
**Note:** The files must physically exist on your disk with the `.as` extension (e.g., `valid_input_1.as`), but you can choose to omit the `.as` extension when typing the execution command; the program will append it automatically.
```bash
./assembler valid_input_1 valid_input_2
```
If the compilation is successful, the program will generate `.ob`, `.ent`, and `.ext` files alongside the `.am` files in the working directory as mapped in the structure above.

---

## 📖 Documentation

Every component of this project is thoroughly documented to ensure readability and maintainability for future developers and graders:
* **Source Files (`.c`):** Each implementation file contains a brief 2-3 line high-level summary at the top outlining its core responsibility within the assembler's architecture.
* **Header Files (`.h`):** Every function declaration includes standard API documentation block comments detailing its purpose, expected parameters, and return values.

---

## 🧪 Testing & CI/CD

This project is bundled with a comprehensive test suite (located in the `Inputs/` directory) and runs on an automated **GitHub Actions CI Pipeline**.

* **Positive Control Tests:** `valid_input_X.as` files are tested to ensure successful compilation, accurate mathematical offset calculations, and exact file generation.
* **Negative Control Tests:** `invalid_input_X.as` files are purposefully injected with syntax errors, illegal operands, and macro placement violations. The CI ensures the assembler catches the errors, prints the correct `err_code`, prevents the creation of `.ob` files, and exits gracefully.
* **Valgrind Validation:** Every single test file is executed through Valgrind to ensure absolute zero memory leaks.

---

## 🧠 Core Assumptions & Design Decisions

* **Maximum Memory Limit:** The assembler assumes a strict overall memory constraint. The combined size of the Instruction Image and Data Image cannot exceed 4096 words. Exceeding this combined limit will trigger a memory overflow error and halt compilation for that file.
* **Line Length Constraint:** Assumes a maximum line length of 80 characters. Lines exceeding this limit trigger a buffer flush and an error flag.
* **Label Constraints:** Labels are limited to a maximum of 31 characters.
* **Global Memory Safe-State:** Because deep function calls in C can make memory cleanup difficult during a fatal `malloc` failure, this project utilizes a global `memory_allocation_fail` flag. If RAM is exhausted, the system safely unwinds to the main loop, closes open file pointers, frees partial data structures, and exits without leaking OS resources.
* **Independent File Processing:** If `fileA.as` fails due to syntax errors, the assembler safely discards its data and successfully continues compiling `fileB.as`.