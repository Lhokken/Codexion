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

### Blocking cases handled
A primary strategy to mitigate potential deadlocks is the implementation of an asymmetrical resource acquisition order. By ensuring that adjacent coders follow a different request sequence—specifically, having one coder request their left dongle before their right, while the adjacent coder requests the right dongle before the left—we effectively break the Circular Wait condition. This prevents the formation of circular dependencies among concurrent threads, thereby natively avoiding classic deadlock scenarios.

### Thread synchronization mechanisms
To ensure safe concurrent access, we utilize mutexes to manage resource contention:  

Global Coordination: A dedicated mutex (med_lock) is utilized by the med_coders monitor to manage global system state transitions and ensure synchronized access to shared data.  

Resource Protection: Individual mutexes are assigned to each dongle to govern exclusive access.  

Shared Infrastructure: Given that the right dongle of one coder serves as the left dongle for the adjacent coder, their corresponding locks are also shared between the two entities.  

Turn-based Access: Coders must execute the wait_my_turn function before attempting to acquire any hardware resources, ensuring they adhere to the assigned scheduling policy before requesting dongle access.  

### Monitoring (Med Coders)
The system employs a specialized monitor thread, med_coders, which serves as a central observer of the system state. This monitor provides several key functions:  

State Tracking: It continuously tracks the last_compile timestamp for every coder in the system.  

Burnout Prevention: By comparing the elapsed time since the last compilation against the time_to_burnout threshold, the monitor can identify potential failures before they compromise system integrity.  

Graceful Termination: Should any coder exceed the burnout threshold, the monitor triggers a global coder_burnout state. This flag is checked by all active threads, ensuring a coordinated halt of all processes and a safe termination of the execution.  

Centralized Information Access: This architecture creates a single source of truth, allowing all coder threads to safely query the global system status through the protected med_lock interface.

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