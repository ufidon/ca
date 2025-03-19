# Computer Architecture

- [Module 0: Overview](./mod0/README.md)
- [Module 1: Program Structure and Construction](./mod1/README.md)
- [Module 2: Building the System to Run Programs](./mod2/README.md)
- [Module 3: Interaction and Communication between Programs](./mod3/README.md)

## References

### Textbooks
- [Computer Systems: A Programmer's Perspective, 3/E (CS:APP3e)](https://csapp.cs.cmu.edu/)
  - [UCLID5: an integrated modeling, verification and synthesis tool](https://github.com/uclid-org/uclid)
  - [中文版](https://fengmuzi2003.gitbook.io/csapp3e)
- [Computer Architecture: A Quantitative Approach, 6e](https://www.elsevier.com/books-and-journals/book-companion/9780128119051)
- [Modern Processor Design: Fundamentals of Superscalar Processors](https://www.waveland.com/browse.php?t=624)
- [x86-64 Assembly Language Programming with Ubuntu](https://open.umn.edu/opentextbooks/textbooks/733)

### Classes
- CMU
  - [18-447 Introduction to Computer Architecture](https://users.ece.cmu.edu/~jhoe/doku/doku.php?id=18-447_introduction_to_computer_architecture)
- Harvard
  - [CS 61: Systems Programming and Machine Organization](https://cs61.seas.harvard.edu)
- Stanford
  - [CS107: Computer Organization & Systems](https://web.stanford.edu/class/archive/cs/cs107/cs107.1252/)
  - [EE282: Computer Systems Architecture](https://web.stanford.edu/class/ee282/)
- MIT
  - [6.5900[6.823] Computer System Architecture](https://csg.csail.mit.edu/6.5900/info.html)
- Cornell
  - [ECE 4750 / CS 4420 / ECE 5740: Computer Architecture](https://www.csl.cornell.edu/courses/ece4750/index.shtml)

# Online resources
- *assembler*
  - [flat assembler](https://flatassembler.net/)
  - [NASM](https://github.com/netwide-assembler/nasm)
  - [yasm](https://github.com/yasm/yasm)
  - [JWasm](https://jwasm.github.io/)
  - [Keystone: The Ultimate Assembler](https://www.keystone-engine.org/)
  - [Capstone: The Ultimate Disassembler](http://www.capstone-engine.org/)
- *reversing tools*
  - [radare 2](https://rada.re/)
  - [Ghidra](https://ghidra-sre.org/)
- *Binary tools*
  - [The LLVM Compiler Infrastructure](https://llvm.org/)
    - [LLVM MinGW](https://github.com/mstorsjo/llvm-mingw)
  - [GNU Binutils](https://www.gnu.org/software/binutils/)
  - [x64dbg](https://x64dbg.com/)
- *BIOS*
  - [CoreBoot](https://www.coreboot.org/)
  - [Libreboot](https://libreboot.org/)
  - [SeaBIOS](https://www.seabios.org/)
  - [TianoCore](https://www.tianocore.org/)
    - [code](https://github.com/tianocore/edk2)
  - [U-Boot](https://github.com/u-boot/u-boot)
  - [open-source firmware](https://opensourcefirmware.foundation/)
    - [Open Platform Firmware](https://www.opencompute.org/projects/open-system-firmware)
      - [Open Computer Project](https://www.opencompute.org/)
- *Bootloader*
  - [GRUB: GRand Unified Bootloader](https://www.gnu.org/software/grub/)
  - [SysLinux](https://www.syslinux.org/)
  - [The rEFInd Boot Manager](https://www.rodsbooks.com/refind/)
- *OS*
  - [osdev](https://wiki.osdev.org/)
  - [BareMetal OS](https://github.com/ReturnInfinity/BareMetal-OS)
    - [PiscisOS](https://tishion.github.io/PiscisOS/)
  - [Minix 3](https://www.minix3.org/)
  - [HelenOS](https://www.helenos.org/)
  - [SerenityOS](https://github.com/SerenityOS/serenity)
  - [Redox](https://www.redox-os.org/)
  - [Haihu-OS](https://www.haiku-os.org/)
  - [ToaruOS](https://www.toaruos.org/)
  - [KolibriOS](https://kolibrios.org/)
    - [menuetos](https://menuetos.net/)
  - [RIOT](https://www.riot-os.org/)
  - [FreeRTOS](https://www.freertos.org/)
  - [Contiki-NG](https://github.com/contiki-ng/contiki-ng)
  - [Operating Systems (OS) Collection](https://github.com/exajobs/os-collection)
    - [WinWorld](https://winworldpc.com/)

- *emulators*
  - [Unicorn: The Ultimate CPU emulator](https://www.unicorn-engine.org/)
    - [Qiling: Cross platform and multi arch ultra lightweight emulator](https://qiling.io)
    - [ROPgadget](https://github.com/JonathanSalwan/ROPgadget)
  - [Renode](https://renode.io/)
  - [Qemu](https://www.qemu.org/)
    - [How to add a new architecture to QEMU](https://fgoehler.com/blog/adding-a-new-architecture-to-qemu-01/)
  - [Bochs](https://bochs.sourceforge.io/)
    - [source](https://github.com/bochs-emu/Bochs/)
  - [gem5: an open-source system-level and processor simulator](https://www.gem5.org/)
  - [Verilator Open-Source SystemVerilog simulator](https://github.com/verilator/verilator)
- *Y86-64*
  - [js-y86-64](https://github.com/boginw/js-y86-64)
    - [node implementation](https://github.com/vaguilar/js-y86)
      - [one more](https://github.com/xsznix/js-y86)
    - [pipeline style](https://dnc1994.github.io/Y86-Simulator/)
    - [Y86 Emulator](https://y86.js.org/)
- *RISC-V specific*
  - [Spike RISC-V ISA Simulator](https://github.com/riscv-software-src/riscv-isa-sim)
  - [FireSim](https://fires.im/)
- *archaic*
  - [MAME: Multiple Arcade Machine Emulator](https://www.mamedev.org/)
  - [OpenSimH](https://opensimh.org/)
    - [code](https://github.com/open-simh/simh)
  - [JPC: The fast x86 PC emulator in pure Java](https://github.com/ianopolous/JPC)
  - [PCem](https://pcem-emulator.co.uk/)
  - [DOSBox](https://www.dosbox.com/)
    - [FreeDOS](https://www.freedos.org/)
  - [OpenEmu](https://openemu.org/)

- *simulators*
  - [visual debugger](https://pythontutor.com/)

- *Creators for bootable USB drives*
  - [Rufus](https://github.com/pbatard/rufus)
  - [Etcher](https://github.com/balena-io/etcher)
  - [ventoy](https://github.com/ventoy/Ventoy)
  - [WoeUSB](https://github.com/WoeUSB)
  - [UNetbootin](https://github.com/unetbootin/unetbootin)
  - [YUMI](https://yumiusb.com/)
  - [MultiBootUSB](https://github.com/mbusb/multibootusb)

---
## C/C++ references
- [C reference](https://en.cppreference.com/w/c)
  - [c++ reference](https://en.cppreference.com)
- [The GNU C Reference Manual](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html)
  - [The GNU C Programming Tutorial](http://www.crasseux.com/books/ctutorial/)
- [Clang: a C language family frontend for LLVM](https://clang.llvm.org/)
  - [Clang Compiler User’s Manual](https://clang.llvm.org/docs/UsersManual.html)
  - [Clang's documentation!](https://clang.llvm.org/docs/index.html)
- [MSDN: C language documentation](https://learn.microsoft.com/en-us/cpp/c-language)
  - [MSDN: C++, C, and Assembler documentation](https://learn.microsoft.com/en-us/cpp)
- *GUI programming*
  - [Programming Windows, 5th Edition](https://www.charlespetzold.com/pw5/index.html)
  - [raygui](https://github.com/raysan5/raygui)
  - [Nuklear](https://github.com/Immediate-Mode-UI/Nuklear)
  - [microui](https://github.com/rxi/microui)
  - [luigi](https://github.com/nakst/luigi)
  - [LCUI](https://github.com/lc-soft/LCUI)
  - [horus_ui](https://github.com/7thFACTOR/horus_ui)
  - [GuiLite](https://github.com/idea4good/GuiLite)
  - [SFGUI — Simple and Fast Graphical User Interface](https://github.com/TankOs/SFGUI)

- ---
- *package managers*
  - [xrepo](https://github.com/xmake-io/xrepo)
  - [conan](https://conan.io/)
  - [vcpkg](https://github.com/microsoft/vcpkg)
  - [cpm](https://github.com/cpm-cmake/CPM.cmake)
- *auto builder*
  - [SCons](https://scons.org/)
  - [Meson](https://mesonbuild.com/)
  - [CMake](https://cmake.org/)

# Lists
- [Awesome C](https://github.com/oz123/awesome-c)
  - [uncategorized](https://github.com/uhub/awesome-c)
- [Awesome C++](https://github.com/fffaraz/awesome-cpp)
  - [doc](https://awesome-cpp.readthedocs.io/en/latest/README.html)
  - [30dayMakeOS](https://github.com/yourtion/30dayMakeOS)
- [C++ UI Libraries](https://philippegroarke.com/posts/2018/c++_ui_solutions/)

# Tips
- [解决clangd找不到iostream的错误](https://blog.csdn.net/weixin_61184943/article/details/131820087)