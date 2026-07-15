*This project was developed by **gcerrete** as part of the 42 curriculum.*

# Codexion
This project addresses the challenges of managing parallel processes in a multi-threaded environment. I implemented a circular doubly-linked list where each node represents a "coder." Each coder requires access to two dongles to perform tasks; these resources are shared with adjacent coders, creating a resource-dependency structure where the left dongle of one coder is the right dongle of the previous one, and the right dongle corresponds to the left of the next.

## Description
The project is structured into three main phases:

### Validation and Initialization
The application first validates the input arguments to ensure all parameters are integers and fall within logical ranges. Edge cases, such as inputting 0 or 1 coder, are handled explicitly to prevent runtime and leak errors.

### Execution Flow
Coders cycle through three core operations "compile, debug, and refactor" until the required number of compilations is reached:

Compile: This phase requires acquiring two dongles. Resource contention is managed using mutexes, and access is governed by the chosen scheduling algorithm. Additionally, a specific function controls the dongle cooldown mechanism.

FIFO (First-In, First-Out): This criterion follows the coder ID sequence, which is reset each cycle using the modulo operation.

EDF (Earliest Deadline First): This algorithm prioritizes tasks based on their proximity to the "burnout" threshold. Coders whose last_compile timestamp is the furthest in the past are prioritized to ensure no process exceeds the burnout limit.

Task Cycles: Coders perform these actions sequentially, ensuring that resource acquisition and release are handled safely to avoid deadlocks.

### Monitoring (Med Coders)
I implemented a specialized med_coders monitor thread that oversees the system state. Its primary responsibility is to track the last compilation time of each coder. If any coder exceeds the time_to_burnout threshold, the monitor triggers a burnout state, which safely halts all active processes and terminates the execution.

## Instructions

Use the following `make` commands in your terminal to set up, run, and manage the project:

* **`make cc`**: Compile the program.
* **`make run`**: Executes the main program.
* **`make debug`**: Starts Debugger (`pdb`).
* **`make clean`**: Removes the installation files.
* **`make fclean`**: Removes the installation and executable files.
* **`make val`**: Runs valgrind.
* **`make hel`**: Runs valgrind with helgrind option.

## Resources

* Gemini AI was utilized as a theoretical learning aid. To ensure a solid understanding of the underlying logic, the AI was strictly instructed to provide conceptual guidance and explanations rather than outputting ready-to-use code, unless explicitly requested.