# Final Project — Spell Checker & Cipher (Visual Studio solutions)

This repository contains two small C++ programs used for the final project: a Spell Checker (Windows/Visual Studio project) and a Cipher (Windows/Visual Studio solution). Both projects are provided as Visual Studio projects; the code and project files are under the `SpellCheck/` and `Cipher/` directories.

## Stack
- Language(s): C++ (primary), small amount of shell/project files
- Platform: Windows / Visual Studio (projects use MSVC-specific headers)
- Notable files: Visual Studio solution/project files (.slnx, .vcxproj) for each program

## What's included (top-level)
- Cipher/
  - Cipher PseudoCode.docx — design notes
  - Cipher/Cipher/ — Visual Studio solution and project for the final cipher program
    - Cipher.slnx, Cipher.vcxproj, Cipher.cpp, project filters/user files, x64 folder
- SpellCheck/
  - SpellCheck.slnx — Visual Studio solution for the spell checker
  - SpellCheck/ — Visual Studio project and sources
    - Source.cpp — spell checker implementation (reads dictionary, opens files)
    - words — dictionary file used by the spell checker
- setup/ — repository setup files (LICENSE, .gitattributes, .gitignore)
- .vs/ — Visual Studio workspace metadata (ignored for builds)

## Spell Checker (SpellCheck/SpellCheck)
What it does
- Loads a dictionary file named `words` (plain text, one word per token).
- Prompts the user to either:
  - enter a full file path manually, or
  - open a file picker (Windows file dialog) to select a plain-text file.
- Reads words from the selected input file, normalizes them (removes punctuation, lowercases), and prints any words not found in the dictionary.

How it works (based on SpellCheck/SpellCheck/Source.cpp)
- The program normalizes tokens by stripping non-alphanumeric characters and converting to lowercase.
- The dictionary is loaded into memory from the file named `words` (expected to be in the program working directory).
- For each token read from the input text, the program checks membership in the dictionary and prints tokens that are not present.

How to run
- Recommended (Visual Studio):
  1. Open `SpellCheck/SpellCheck.slnx` in Visual Studio.
  2. Build the project (Debug or Release).
  3. Ensure the `words` dictionary file is in the working directory used when running the program (either place `words` next to the built executable or set the project working directory to `SpellCheck/SpellCheck/`).
  4. Run the program. It will show an interactive console prompt where you choose manual path (1) or file explorer (2), then it prints misspelled words.

- Command-line (MSVC) alternative:
  - From a Visual Studio x64/x86 Developer Command Prompt:
    cl /EHsc SpellCheck\SpellCheck\Source.cpp /Fe:spellcheck.exe
  - Run `spellcheck.exe` from the folder containing the `words` file (or copy `words` next to the exe).

Notes
- The project uses Windows APIs (`windows.h`, `commdlg.h`) for the Open File Dialog — the program is Windows-specific. Compiling with g++ on non-Windows systems will fail without changes.
- The dictionary file in this repository is at `SpellCheck/SpellCheck/words`. Keep that file available to the executable.

## Cipher (Cipher/Cipher)
What it is now
- The final cipher program is provided as a Visual Studio solution/project under `Cipher/Cipher/`. The folder contains `Cipher.slnx`, `Cipher.vcxproj`, and the implementation `Cipher.cpp`.

What it does (summary)
- The Visual Studio project implements a substitution-cipher utility (see `Cipher/Cipher/Cipher.cpp` for the implementation).
- The program constructs a cipher alphabet based on a keyword (preserving the first occurrence of each letter from the keyword) and fills the remaining letters of the alphabet (implementation detail: see the source for the exact order used).
- The Visual Studio solution contains the final implementation — open the solution and inspect `Cipher.cpp` for exact runtime behavior and any input/output examples.

How to run
- Recommended (Visual Studio):
  1. Open `Cipher/Cipher.slnx` in Visual Studio.
  2. Build the project (Debug/Release).
  3. Run the program from Visual Studio or from the built executable (ensure any expected input is provided as the program expects — see `Cipher.cpp` for details).

- Command-line (MSVC) alternative:
  - From a Visual Studio Developer Command Prompt you can compile the single source file if needed:
    cl /EHsc Cipher\Cipher\Cipher.cpp /Fe:cipher.exe
  - Run `cipher.exe` and follow the program's input prompts (see `Cipher.cpp`).

Notes
- The repository includes a design document `Cipher/Cipher PseudoCode.docx` that describes the intended algorithm and pseudocode.
- The Cipher project is also set up as a Windows/Visual Studio project; it may rely on Visual Studio project settings for some build options.

## Files of interest
- README.md (this file)
- SpellCheck/SpellCheck/Source.cpp — spell checker implementation
- SpellCheck/SpellCheck/words — dictionary used by the spell checker
- SpellCheck/SpellCheck.slnx — Visual Studio solution for spell checker
- Cipher/Cipher/Cipher.cpp — cipher implementation (final Visual Studio project)
- Cipher/Cipher/Cipher.slnx — Visual Studio solution for cipher
- Cipher/Cipher.vcxproj — project file for the cipher

## Notes and suggestions
- Both projects target Windows / Visual Studio. If you need cross-platform builds, the code will need edits (the Spell Checker uses Windows file-dialog APIs).
- If you want sample inputs or example runs added to the repo (small example text files and example outputs), I can prepare a short demo script or sample text files and a short instruction snippet to include in the repository.

