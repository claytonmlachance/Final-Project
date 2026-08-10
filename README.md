# Final Project
Repository for Final Project Display

## Spell Checker

`SpellCheck.cpp` reads words from a file and prints any that are not in the dictionary (`words`).

### Run locally

```bash
g++ -std=c++17 SpellCheck.cpp -o spellcheck
echo test.txt | ./spellcheck
```

### Run on GitHub

The workflow in [`.github/workflows/spellcheck.yml`](.github/workflows/spellcheck.yml) compiles and runs the program automatically on every push or pull request to `main`/`master`. You can also run it manually from the **Actions** tab (**Spell Check** → **Run workflow**).
