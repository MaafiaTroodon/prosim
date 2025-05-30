# ProSim

**ProSim** is a lightweight C-based program simulator that interprets a custom process execution language. It simulates CPU and I/O operations based on a sequence of primitives and tracks execution time in clock ticks.

## 🧠 What It Does

The simulator reads a simple program description from standard input, consisting of commands such as:
- `DOOP <ticks>` – Simulates CPU activity for a specified number of ticks.
- `BLOCK <ticks>` – Simulates waiting (I/O or event blocking).
- `LOOP <n>` ... `END` – Repeats the enclosed instructions `n` times. Loops can be nested.
- `HALT` – Ends the program simulation.

It outputs when each operation occurs, and at the end, it summarizes how much time was spent on DOOPs and BLOCKs.

### 🛠 How It Works

- The program parses all instructions into memory.
- A loop stack is used to manage control flow for nested loops.
- The simulation keeps a global clock and prints execution logs like:
00000: DOOP
00003: BLOCK
00008: HALT

markdown
Copy
Edit
- After execution ends, it prints total counts and durations for `DOOP` and `BLOCK` operations.

## 🔧 Build

```bash
gcc -Wall -g -o prosim prosim.c

## Run
bash
Copy
Edit
./prosim < input.txt
Where input.txt contains a valid instruction sequence. Example:

scss
Copy
Edit
MyProgram 3
DOOP 2
BLOCK 4
HALT

## 📊 Sample Output
yaml
Copy
Edit
00000: DOOP
00002: BLOCK
00006: HALT

DOOP count : 1
DOOP time  : 2
BLOCK count: 1
BLOCK time : 4
