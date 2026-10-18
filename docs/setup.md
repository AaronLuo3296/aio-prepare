# Setting up C++ and the course tools (macOS and Windows)

You need four things: a **C++ compiler**, an **editor** (VS Code), **Python 3** (for the
stress-test and test tools) and **Git** (to download this repository). Allow 30–60 minutes.
If anything goes wrong, use the [USACO Guide IDE](https://ide.usaco.guide/) in the browser
for now. You can solve problems there while you fix your setup.

---

## macOS

### 1. Compiler, Git and Python

Open **Terminal** (⌘-Space, type "Terminal") and run:

```sh
xcode-select --install
```

Accept the dialog. This installs Apple's C++ compiler (`clang++`, also callable as `g++`),
Git and Python 3. Check:

```sh
g++ --version        # should say "Apple clang version ..."
git --version
python3 --version
```

### 2. Get the course repository

> **Access:** if the repository is private, ask your teacher to add your GitHub account
> as a collaborator first (or to send you a ZIP of the repository).

```sh
cd ~
git clone https://github.com/AaronLuo3296/aio-prepare.git
cd aio-prepare
make test
```

`make test` compiles and checks every reference solution. If the last line reads
`0 failing case(s)`, your setup works.

### 3. Two macOS quirks (already handled by the repo)

- **`<bits/stdc++.h>` not found.** Apple's compiler doesn't ship this header (GCC, which
  the judges use, does). Always compile through the repo's flags, which add a fallback copy:
  ```sh
  g++ $(tools/cxxflags.sh) mysol.cpp -o mysol
  ```
- **`'algorithm' file not found`** (or `'vector'`, `'iostream'`…). The Command Line Tools
  install is broken, which often happens after a macOS upgrade. `tools/cxxflags.sh` works
  around it automatically. To repair it properly:
  ```sh
  sudo rm -rf /Library/Developer/CommandLineTools
  xcode-select --install
  ```

> **Heads-up: GCC-only extensions.** Some tricks in other people's contest code work only
> with GCC (the judges' compiler), not with Apple clang. The most common one is `__lg(x)`
> (⌊log₂ x⌋), which fails with `use of undeclared identifier '__lg'`. Write
> `31 - __builtin_clz(x)` instead (`63 - __builtin_clzll(x)` for `long long`). It works with
> both compilers. Code in this repo avoids GCC-only extensions, so it compiles on both.

### 4. Optional: real GCC (identical to the judges)

Install [Homebrew](https://brew.sh/), then:

```sh
brew install gcc
ls $(brew --prefix)/bin/g++-*     # shows e.g. g++-15; use that name
export CXX=g++-15                 # add to ~/.zshrc to make it permanent
```

The repo's tools use `$CXX` when it is set.

---

## Windows

**Recommended: WSL (Windows Subsystem for Linux).** You get a real Linux with GCC, the same
compiler the judges use, and every repo tool (`make`, `bash` scripts, sanitizers) works
unchanged.

### Option A: WSL (recommended)

1. Open **PowerShell as Administrator** and run `wsl --install`, then restart
   ([Microsoft guide](https://learn.microsoft.com/en-us/windows/wsl/install)). On first
   start, Ubuntu asks you to create a Linux username and password.
2. In the **Ubuntu** terminal:
   ```sh
   sudo apt update
   sudo apt install build-essential gdb python3 git make
   g++ --version        # should say "g++ (Ubuntu ...)"
   ```
3. Clone and test, inside Ubuntu (keep your files in the Linux home folder `~`, not under
   `/mnt/c`, which is much slower):
   ```sh
   cd ~
   git clone https://github.com/AaronLuo3296/aio-prepare.git
   cd aio-prepare
   make test
   ```
4. Install VS Code **on Windows**, plus the
   [WSL extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl).
   Then from the Ubuntu terminal run `code .` inside the repo. VS Code opens connected to
   Linux ([guide](https://code.visualstudio.com/docs/cpp/config-wsl)).

### Option B: MSYS2 / MinGW (if WSL is not allowed on your computer)

1. Install [MSYS2](https://www.msys2.org/), open the **MSYS2 UCRT64** terminal and run:
   ```sh
   pacman -S mingw-w64-ucrt-x86_64-gcc make python git
   ```
2. Follow [VS Code: GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)
   to add `C:\msys64\ucrt64\bin` to your PATH.
3. Run the repo tools from the MSYS2 terminal. MinGW does **not** support sanitizers, so use:
   ```sh
   SANITIZE=0 make test
   ```
4. **Stack size:** Windows gives programs a small stack (1 MB), so deep recursion (DFS on
   10⁵ nodes) can crash locally even though it passes on the judge. Compile with a larger
   stack when testing such code:
   ```sh
   g++ $(tools/cxxflags.sh) -Wl,--stack,268435456 mysol.cpp -o mysol
   ```

---

## Both systems: VS Code

1. Install [VS Code](https://code.visualstudio.com/).
2. Extensions:
   - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
     (Microsoft): syntax highlighting, error squiggles, debugger.
   - [Competitive Programming Helper](https://marketplace.visualstudio.com/items?itemName=DivyanshuAgrawal.competitive-programming-helper):
     runs your code on the sample tests with one click.
   - Browser extension [Competitive Companion](https://github.com/jmerle/competitive-companion):
     sends a problem's samples from CSES/AtCoder/Codeforces straight into the helper above.
3. Use the integrated terminal (`` Ctrl-` ``) to compile and run.

## Daily workflow

```sh
cp templates/template.cpp work/apartments.cpp      # start a problem (work/ is yours)
g++ $(tools/cxxflags.sh) -fsanitize=address,undefined work/apartments.cpp -o work/a
./work/a < work/sample.txt                          # run on the sample
make stress SOL=work/a.cpp BRUTE=work/brute.cpp GEN=work/gen.py   # hunt bugs (Day 7)
```

Drop `-fsanitize=...` on MinGW. Remove it, too, when timing a solution: sanitizers make
code several times slower.

> **Heads-up: passing the samples is not "Accepted".** Samples and small random tests
> check that your answers are right. They do not check speed, memory or overflow at the
> real limits, which is what the judge's hidden tests do. Before you submit, time one
> max-size input (without sanitizers), and treat only the judge's verdict as final.
> The same applies to `make test` on the reference solutions in this repo.
>
> **On a Mac, timings with Apple clang can mislead.** Its `cin` can be 10× or more slower
> than GCC's, even with `sync_with_stdio(false)`. A solution that reads 2·10⁵ numbers
> may take about 1 s locally but under 0.1 s on the judge. If your timing looks slow, use
> GCC (step 4 above) or `scanf` before you decide your algorithm is too slow.

## Checklist

- [ ] `g++ --version` works.
- [ ] `make test` ends with `0 failing case(s)`.
- [ ] You compiled and ran `templates/template.cpp`.
- [ ] You have an account on [CSES](https://cses.fi/problemset/) and
      [ORAC](https://orac2.info/learn/).
