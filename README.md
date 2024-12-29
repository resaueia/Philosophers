# Philosophers
The dining philosophers problem - 42 Project

This project implements the classic **"Dining Philosophers Problem"** using the C programming language. The program is designed to respect synchronization and threading constraints, using mutexes to prevent race conditions.

---

### Execution
After compilation, the program can be executed as follows:
```bash
./philosophers <number of philosophers> <time to die> <time to eat> <time to sleep>
```

- `<number of philosophers>`: Number of philosophers (and forks) at the table.
- `<time to die>`: Time in milliseconds a philosopher can go without eating before dying.
- `<time to eat>`: Time in milliseconds a philosopher spends eating.
- `<time to sleep>`: Time in milliseconds a philosopher spends sleeping.

**Example:**
```bash
./philosophers 5 800 200 200
```

---

## 🛠️ Project Structure

The project is organized into the following files:
1. **`main.c`**: Contains the main function and initializes the simulation.
2. **`philosophers.c`**: Implements the philosophers' routines (thinking, eating, sleeping).
3. **`utils.c`**: Provides helper functions like time tracking and message printing.
4. **`philosophers.h`**: Header file with all project definitions and declarations.
5. **`Makefile`**: Automates the compilation process.
6. **`README.md`**: This document explaining the project.

---

## 🔄 Execution Flow

### `main` Function
1. Reads and validates the input arguments.
2. Initializes the simulation structure (`t_simulation`) with the necessary configurations and resources:
   - Creates mutexes for the forks.
   - Initializes the philosophers and their respective threads.
3. Starts the simulation by calling `start_simulation()`.
4. Cleans up allocated resources at the end by calling `cleanup_simulation()`.

### `start_simulation` Function
- Creates a thread for each philosopher, each running the `philosopher_routine`.
- Monitors the philosophers' state to check if any have died.

### `philosopher_routine` Function
Each philosopher executes a continuous cycle of actions:
1. **Thinking**: The philosopher reflects before attempting to eat.
2. **Eating**: The philosopher tries to pick up two forks (mutexes) and eats for a certain time.
3. **Sleeping**: After eating, the philosopher rests for a certain time.

### Auxiliary Functions
- **`print_message`**: Prints synchronized messages to the console, such as "philosopher picked up a fork" or "philosopher is eating."
- **`get_timestamp`**: Gets the current timestamp in milliseconds for time tracking.

---

## 🧠 Key Concepts

### Threads
The program uses **threads** to simulate the parallel behavior of each philosopher. Each thread represents a philosopher, executing its routine independently.

### Mutex (Mutual Exclusion)
Forks are represented by **mutexes**. Only one philosopher can "pick up" a fork at a time, ensuring no two philosophers attempt to use the same fork simultaneously, preventing race conditions.

### Synchronization
Message printing and resource allocation are synchronized using mutexes to avoid inconsistencies in output and program state.

---

## 📚 Understanding the Dining Philosophers Problem

In the **Dining Philosophers Problem**, a circular table has:
- **N philosophers** alternating between thinking, eating, and sleeping.
- **N forks**, where each philosopher needs two forks to eat.

Rules:
1. Only one philosopher can use a fork at a time.
2. A philosopher can pick up the fork to their left and the fork to their right to eat.
3. A philosopher who cannot pick up two forks must wait.

Challenges:
- Avoiding **deadlocks**: Situations where all philosophers are waiting indefinitely for forks.
- Ensuring **mutual exclusion**: Only one philosopher can use each fork at a time.

---

## 🔎 Example Output

```plaintext
0 1 is thinking
10 2 is thinking
20 1 picked up the left fork
30 1 picked up the right fork
30 1 is eating
50 2 picked up the left fork
60 2 picked up the right fork
60 2 is eating
90 1 is sleeping
100 2 is sleeping
```

---

## 🧹 Cleaning Up

To remove compiled files, run:
```bash
make clean
```

To remove all binaries and object files, run:
```bash
make fclean
```

---

## 💡 Notes
This project was developed following best coding practices, with a focus on simplicity, readability, and modularity. The problem was implemented within the scope of the mandatory requirements, without additional bonus features.

If you have any questions or need further assistance, feel free to ask!
