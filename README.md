# Final Project

Repository containing two small C++ programs used for the final project: a Spell Checker and a Cipher/crypt utility. Each program includes source and project files in their respective folders.

## Spell Checker

What it does
- Reads words from an input file (or stdin) and reports words not found in the dictionary file (named `words` in the project).

How it works (high level)
- Loads the dictionary into memory.
- Reads words from the provided input file (or stdin).
- Prints any words that are not present in the dictionary.

Run locally
- If the spell-check source is at the repository root:
  ```bash
  g++ -std=c++17 SpellCheck.cpp -o spellcheck
  echo test.txt | ./spellcheck
  ```
- If the source is inside the SpellCheck folder:
  ```bash
  g++ -std=c++17 SpellCheck/SpellCheck.cpp -o spellcheck
  echo test.txt | ./spellcheck
  ```

Run on GitHub
- A GitHub Actions workflow (.github/workflows/spellcheck.yml) is configured to compile and run the program automatically on pushes and pull requests to main/master.

Notes
- Ensure the dictionary file (`words`) is available in the expected path when running the program.
- See the SpellCheck folder for pseudocode and the Visual Studio project files.

## Cipher (crypt)

What it does
- Builds a substitution cipher keyed by a user-supplied keyword.
- The program constructs a cipher alphabet by taking the keyword (preserving the first occurrence of each letter) and then filling the remaining letters with a reversed alphabet sequence.

How it works (high level)
- `buildCipher(keyword, cipher[])` creates a 26-character mapping:
  - Adds each unique letter from the keyword in order.
  - Fills the rest of the mapping with the remaining letters of the alphabet in reverse order.
- The current implementation reads the keyword from stdin and constructs the `cipher` array.

Run locally
- Compile:
  ```bash
  g++ -std=c++17 Cipher/crypt/crypt.cpp -o crypt
  ```
- Run (example):
  ```bash
  echo mykeyword | ./crypt
  ```
- For Visual Studio users, the project files are under `Cipher/crypt` (crypt.vcxproj, solution files).

Notes
- The current `main()` builds the cipher but does not print it by default (there are commented `cout` lines). Uncomment or add output logic to display or use the cipher mapping.
- The implementation uses lowercase alphabetic characters; normalize input to lowercase if needed.

## Files of interest
- `README.md` (this file)
- `SpellCheck/` (pseudocode, project files)
- `Cipher/crypt/crypt.cpp` (cipher implementation and Visual Studio project files)
- `.github/workflows/spellcheck.yml` (CI workflow for the spell checker)

If you’d like, I can:
- Commit further examples or sample inputs/outputs to the repo, or
- Add a short script to demonstrate each program's output.

— GitHub Copilot Chat Assistant
