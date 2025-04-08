### ✅ **Basic Forking and Output Interleaving**
- **`fork0`**: Simple fork with separate messages from child and parent.
- **`fork1`**: Shows how variables are copied during fork (memory separation).
- **`fork2`, `fork3`**: Demonstrate exponential growth of processes.
- **`fork4`, `fork5`**: Conditional forks, affecting the process tree shape.

---

### ✅ **Cleanup and Exit Behavior**
- **`fork6`**: Demonstrates `atexit()` and exit handlers — only the calling process cleans up.
- **`fork7`, `fork8`**: Parent or child exits while the other loops — terminal state exploration.

---

### ✅ **Waiting and Status Checking**
- **`fork9`**: Basic `wait()` usage and process synchronization.
- **`fork10`**: Forks multiple children and waits in arbitrary order.
- **`fork11`**: Waits for children in reverse creation order using `waitpid()`.

---

### ✅ **Signal Handling and Termination**
- **`fork12`**: Kills child processes via `SIGINT`.
- **`fork13`**: Adds a `SIGINT` handler so children can react before exiting.
- **`fork14`**: Uses a `SIGCHLD` handler to reap terminated children one-by-one.
- **`fork15`**: Improves `SIGCHLD` handler to reap all terminated children at once.

---

### ✅ **Process Grouping and Hierarchy**
- **`fork16`**: Demonstrates child-child relationship and `getpgrp()`.
- **`fork17`**: Observes parent-child process group behavior.