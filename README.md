```
# 🚢 OOP-V2 – Cargo & Freight Matching Simulator

> A console-based C++ project that showcases clean object-oriented programming by solving a practical logistics problem: **matching cargo items to suitable freight options and generating a shipping schedule**.

![C++](https://img.shields.io/badge/language-C++17-blue.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey)

---

## ✨ Key Features

- 🧱 **Encapsulated Domain Classes**  
  Modular design with clear abstractions for `Cargo`, `Freight`, and `Transport`.

- 📦 **Storage Singletons**  
  Dedicated storage containers (`CargoStorage`, `FreightStorage`, `MatchedStorage`) to manage lifecycle and access.

- 🤝 **Two-Phase Matching Engine**  
  The `Matcher` class handles compatibility checks and pairing logic; `MatchedStorage` saves results.

- 🗃️ **Flat File Persistence**  
  Input/output through simple text files (`Cargo.txt`, `Freight.txt`, `schedule.txt`) — no database needed.

- 🧪 **Clean Layered Architecture**  
  Easy to extend, test, and adapt to GUI/API use cases thanks to separation of model, service, and UI logic.

---

## 📂 File Structure

```
.
├── Cargo.h / .cpp         # Cargo item class and utilities
├── Freight.h / .cpp       # Freight offer class and utilities
├── Transport.h / .cpp     # Transport route/vehicle class
├── CargoStorage.\*         # Singleton for cargo records
├── FreightStorage.\*       # Singleton for freight records
├── MatchedStorage.\*       # Stores matched cargo-freight pairs
├── Matcher.\*              # Matching logic engine
├── Cargo.txt              # Sample cargo input
├── Freight.txt            # Sample freight input
├── schedule.txt           # Output shipping schedule
└── main.cpp               # Program entry point

````
## 🚀 Getting Started

### ✅ Prerequisites

- A C++17-compatible compiler (e.g., GCC 9+, Clang 10+, MSVC 2019+)
- Optional: CMake 3.15+ for easier builds

### 🔧 Build & Run

Using a terminal:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o oop_v2 src/*.cpp
./oop_v2
````

> Ensure your source files are located under a `src/` directory or adjust the path accordingly.
```
## 👥 Contributors

* **jullion14**
* **JunXuanSIT**
* **Kktanker**
* **GhosterRoller**
* **Leepq**

## 📜 License

This project is for educational use only. Feel free to fork, explore, or improve!

```
