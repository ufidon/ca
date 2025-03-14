# Setup Development Tools

## **Objective**  
This lab will guide you through setting up and using development tools for C/C++ programming and debugging, including Visual Studio 2022, x64dbg, HxD, Ubuntu 22.04 LTS or any recent Linux distribution, and CPU-Z. By the end of the lab, you will have practical experience compiling, running, debugging, and analyzing a C/C++ program and examining your computer's specifications.

---

## **Tools and Requirements**  
1. **Visual Studio 2022 (Community Edition)**  
2. **x64dbg**  
3. **HxD**  
4. **Ubuntu 22.04 LTS on VirtualBox**  
5. **CPU-Z**  

---

## **Instructions**  

### **Step 1: Install and Use Visual Studio 2022 for C/C++ Programming**
1. **Install Visual Studio 2022 (Community Edition):**  
   - Download and install from the official [Visual Studio website](https://visualstudio.microsoft.com/).  
   - During installation, select the [Desktop development with C/C++](https://www.youtube.com/watch?v=7dXfMowQIfE) workload.

2. **Create a C/C++ Program:**  
   - Open Visual Studio 2022.  
   - Create a new project by selecting **File > New > Project > Console App (C/C++).**  
   - You may use one of the code files demonstrated during the class:
     - [fun.c](../../mod0/code/fun.c), or [perf.c](../../mod0/code/perf.c)
     - Remember to add the following line to the end of the code
       ```c++
       getchar();  // Keeps the program running for debugging.
       ```

3. **Compile and Run the Program:**  
   - Build the solution by clicking **Build > Build Solution** or pressing `Ctrl + Shift + B`.  
   - Run the program by clicking **Debug > Start Without Debugging** or pressing `Ctrl + F5`.  

4. 💻**Take a Screenshot** of the console output.  

---

### **Step 2: Debug the C/C++ Program Using x64dbg**
1. **Install x64dbg:**  
   - Download and install x64dbg from [x64dbg’s official website](https://x64dbg.com/).  

2. **Load the Compiled Program:**  
   - Open x64dbg and load the compiled `.exe` file from Visual Studio.  

3. **Debug the Program:**  
   - Set a breakpoint at the program's `main` function.  
   - Step through the code using x64dbg's debugging interface.  

4. 💻**Take a Screenshot** of the debugger showing the program execution.  

---

### **Step 3: Analyze the Program Using HxD**
1. **Install HxD:**  
   - Download and install HxD from [HxD’s official website](https://mh-nexus.de/en/hxd/).  

2. **Open the Compiled Program File:**  
   - Open the `.exe` file generated by Visual Studio in HxD.  

3. **Inspect the Program in Memory:**  
   - Use HxD to analyze the program's process in memory.  

4. 💻**Take a Screenshot** showing the file and memory content in HxD.  

---

### **Step 4: Compile and Run the Program on Ubuntu 22.04 LTS in VirtualBox**

**⚠️ You may use any recent Linux distribution.**

1. **Set Up Ubuntu 22.04 LTS:**  
   - Install [Ubuntu 22.04](https://youtu.be/rJ9ysibH768) LTS on [VirtualBox](https://youtu.be/VSar76Y7wPs).  
   - Allocate at least 2GB of RAM and 20GB of disk space for the virtual machine.  

2. **Install C/C++ Development Tools:**  
   - Run the following commands in the terminal:
     ```bash
     sudo apt update
     sudo apt install build-essential g++
     ```
   - Install [VSCodium](https://vscodium.com/)

3. **Create and Compile the C/C++ Program:**  
   - Open the C program [ov.c](../../mod0/code/ov.c) from using Codium.  
   - Compile the program using:  
     ```bash
     g++ -o ov ov.c
     ```

4. **Run the Program:**  
   - Execute the program following lecture demo:  
     ```bash
     ./ov
     ```

5. 💻**Take a Screenshot** of the terminal showing the compilation and execution.  

---

### **Step 5: Analyze System Specifications Using CPU-Z**
1. **Install CPU-Z:**  
   - Download and install CPU-Z from [CPU-Z’s official website](https://www.cpuid.com/softwares/cpu-z.html).  

2. **Open CPU-Z:**  
   - View the CPU, memory, and other hardware details.  

3. 💻**Take Screenshots** of the following tabs:  
   - **CPU Tab**  
   - **Memory Tab**  

---

### **Lab Report Submission**  
1. **Include the Following in Your Report:**  
   - Title Page with your name, date, and lab title.  
   - Screenshots for each step (Visual Studio, x64dbg, HxD, Ubuntu terminal, CPU-Z).  
   - Brief descriptions for each tool and what the screenshot demonstrates.  

2. **Save the Report as a PDF:**  
   - Use tools like Microsoft Word, Google Docs, or LaTeX to compile the report.  
   - Export or save the document as a PDF.  

3. **Submit the Report:**  
   - Submit on Canvas. 

--- 

### **Expected Output**  
Your report should demonstrate the successful setup and usage of all tools, with screenshots clearly showing the program execution, debugging, memory analysis, and system specifications.