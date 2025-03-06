# Binary Sequence Automata UML Generator

This project is a small C++ utility that generates a **PlantUML state diagram** representing a finite automaton that matches a given binary sequence.

You provide a binary string (e.g., `"1011"`), and the program outputs PlantUML code that visualizes the automaton's states and transitions.

---

## Features

* **Binary sequence parsing** – Takes a string of `0`s and `1`s as input.
* **Finite state machine construction** – Builds an automaton that detects the sequence.
* **PlantUML output** – Generates a `@startuml` / `@enduml` diagram for visualization.
* **Customizable** – Code is structured for easy modification of output format or transition rules.

---

## Example

**Input:**

```
1011
```

**Rendered Diagram:**

You can copy this output into a [PlantUML renderer](https://plantuml.com/) to visualize the automaton.

---

## Build & Run

**Build:**

```bash
g++ -std=c++17 -O2 -o automata main.cpp
```

**Run:**

```bash
echo "1011" | ./automata
```

To render the diagram:

```bash
echo "1011" | ./automata > diagram.puml
plantuml diagram.puml
```

---

## Dependencies

* C++17 compatible compiler
* [PlantUML](https://plantuml.com/) for rendering the generated `.puml` file
