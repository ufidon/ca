# Install and update MSYS2

## **1. Install MSYS2**
If you haven't installed **MSYS2**, download and install it from:  
🔗 [https://www.msys2.org/](https://www.msys2.org/)

After installation, **launch the MSYS2 shell**: `MSYS2 MinGW 64-bit`

- Note: a `MSYS2 MSYS` may be created by installing Git.

---

## **2. Update MSYS2 and Package Database**
Before installing anything, update the package manager:
```bash
pacman -Syu
```
If prompted to close the terminal, do so and restart it. Then, run:
```bash
pacman -Su
```

---

# Install the Clang Toolchain for 64-bit MinGW-w64

```bash
pacman -S --needed mingw-w64-x86_64-clang mingw-w64-x86_64-lld mingw-w64-x86_64-libc++ mingw-w64-x86_64-make mingw-w64-x86_64-gdb
```

This installs:
- **Clang** (`clang`, `clang++`)
- **LLD** (LLVM linker)
- **libc++** (Standard C++ library)
- **Make** (Build system)
- **GDB** (Debugger)

---

## **2. Verify Installation**
Check if Clang is installed correctly:
```bash
clang --version
clang++ --version
lld --version
gdb --version
```

Compile a test program:
```bash
echo '#include <iostream>\nint main() { std::cout << "Hello, Clang!\\n"; return 0; }' > test.cpp
clang++ -o test.exe test.cpp
./test.exe
```

---

## **3. (Optional) Install Additional LLVM Tools**
If you need more LLVM utilities, install:
```bash
pacman -S --needed mingw-w64-x86_64-llvm mingw-w64-x86_64-clang-tools-extra
```

This adds:
- `llvm-ar`, `llvm-nm`, `llvm-objdump` (LLVM binutils)
- `clang-format`, `clang-tidy` (Code formatting & linting)

---

## **4. Set Up Environment Variables (Optional)**
To use Clang globally in **Windows**, add the MinGW paths to `PATH`:

1. Open **System Properties** (`Win + R`, type `sysdm.cpl`, press **Enter**).
2. Go to **Advanced > Environment Variables**.
3. Under **System variables**, find `Path` and click **Edit**.
4. Add:
   ```
   C:\msys64\mingw64\bin
   ```
5. Click **OK**, then restart the terminal.

---


# Install gcc toolchain

---

## **3. Install GCC Toolchain for 64-bit MinGW-w64**

```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```
This installs:
- `gcc`, `g++` (C and C++ compilers)
- `binutils` (linker, assembler)
- `make` (build system)
- `gdb` (debugger)
- `libgcc`, `libstdc++`, `libgfortran`

---

## **4. Verify Installation**
After installation, check if GCC and GDB are working:

```bash
gcc --version
g++ --version
gdb --version
```

To compile and debug a simple program:
```bash
echo '#include <stdio.h>\nint main() { printf("Hello, MSYS2!\\n"); return 0; }' > test.c
gcc test.c -o test.exe
./test.exe
```

To run it in GDB:
```bash
gdb test.exe
```

---

## **5. Set Up Environment Variables**
To make sure `gcc` and `gdb` are available globally, add MinGW paths to the Windows `PATH`:

1. Open **System Properties** (`Win + R`, type `sysdm.cpl`, and press **Enter**).
2. Go to **Advanced > Environment Variables**.
3. Under **System variables**, find `Path` and click **Edit**.
4. Add the following (adjust if installed elsewhere):
   ```
   C:\msys64\mingw64\bin
   ```
5. Click **OK** and restart your terminal.

---

## **6. Install Additional Tools (Optional)**
For **CMake**:
```bash
pacman -S mingw-w64-x86_64-cmake
```
For **Ninja (faster builds)**:
```bash
pacman -S mingw-w64-x86_64-ninja
```