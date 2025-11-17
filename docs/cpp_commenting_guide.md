# C++ Commenting & Documentation Guide

This document defines the conventions and best practices for writing comments and documentation in all C++ source files of this project. The goal is to maintain clarity, consistency, and professional-quality documentation that can also be processed by **Doxygen**.

---

## 1. General Principles

* All comments must be written in **English**.
* Prefer explaining **why**, not **what**, the code is doing.
* Use comments sparingly and purposefully.
* Keep comments **up to date** with the code.
* Avoid restating obvious details.

---

## 2. Types of Comments

### 2.1 Inline Comments

Use inline comments to clarify a specific line:

```cpp
x = computeThreshold();  // Avoid negative values
```

### 2.2 Block Comments

For longer explanations or contextual notes:

```cpp
/*
 * This block handles epsilon-transitions using DFS.
 * It assumes the graph contains no cycles through non-epsilon edges.
 */
```

---

## 3. Doxygen Documentation Style (Recommended)

All classes, public methods, and important structures must be documented using Doxygen comment blocks.

Preferred style:

```cpp
/**
 * ...
 */
```

Either multi-line (`/** */`) or single-line (`///`) is acceptable. This project uses **multi-line style**.

---

## 4. Documenting a Class

Place the documentation block **directly above the class definition**.

```cpp
/**
 * @class NFA
 * @brief Represents a Non-Deterministic Finite Automaton (NFA).
 *
 * Provides methods to build, combine, and analyze NFAs using
 * Thompson's construction. Supports union, concatenation, closures,
 * and epsilon transitions.
 */
class NFA {
```

---

## 5. Documenting Member Variables

Document public or protected attributes:

```cpp
/** @brief List of all states in this automaton. */
std::vector<Estado> states;
```

Private attributes may be documented only when necessary to clarify behavior.

---

## 6. Documenting Methods

Each method should include:

* **@brief** – short description
* **@param** – each input parameter
* **@return** – explanation of the returned value
* **@note**, **@warning**, **@details** – optional tags for extra context

Example:

```cpp
/**
 * @brief Creates a basic NFA that recognizes a single character.
 *
 * @param symbol The character to be recognized.
 * @param counter Initial state counter.
 * @return A new NFA representing the constructed automaton.
 */
NFA NFA_Basic(char symbol, int counter);
```

---

## 7. Documenting Overloaded Methods

Document each overload independently:

```cpp
/** @brief Computes epsilon-closure of a single state. */
std::vector<Estado> EpsilonClosure(const Estado& s);

/** @brief Computes epsilon-closure for a set of states. */
std::vector<Estado> EpsilonClosure(const std::vector<Estado>& states);
```

---

## 8. Documenting Constructors and Destructors

```cpp
/** @brief Default constructor. Initializes an empty NFA. */
NFA();

/** @brief Destructor. */
virtual ~NFA();
```

---

## 9. Documenting Private Methods (Optional)

Document private methods only when:

* Logic is complex
* Name is ambiguous
* Additional context is beneficial for future maintainers

Avoid unnecessary clutter.

---

## 10. What NOT To Do

* ❌ Do **not** write obvious comments:

  ```cpp
  i++; // increment i
  ```

* ❌ Do **not** duplicate code behavior:

  ```cpp
  // Calls the union method
  return NFA_Union(a, b);
  ```

* ❌ Do **not** leave outdated comments.

---

## 11. File Header (Optional but Recommended)

Each header/source file may begin with:

```cpp
/**
 * @file NFA.h
 * @brief Declaration of the NFA class used to build NFAs.
 * @author Marco
 * @date 2025
 */
```

---

## 12. Example File Structure

```cpp
/**
 * @file NFA.h
 * @brief Declaration of the NFA class used to build NFAs.
 */

#ifndef NFA_H
#define NFA_H

#include <vector>
#include "Estado.h"

/**
 * @class NFA
 * @brief Non-Deterministic Finite Automaton implementation.
 */
class NFA {
public:
    /** @brief Identifier of the automaton. */
    int id;

    /** @brief All states belonging to the NFA. */
    std::vector<Estado> states;

    /** @brief Constructs an empty NFA. */
    NFA();

    /**
     * @brief Creates a basic NFA for a symbol.
     * @param symbol Character recognized by the automaton.
     * @return The generated NFA.
     */
    NFA Basic(char symbol);

    /** @brief Destructor. */
    ~NFA();
};

#endif
```

---

## 13. Conclusion

Following this guide ensures:

* Clean and maintainable documentation
* Consistent commenting style across the project
* Doxygen-compatible markup for automatic document generation

This guide should be applied to all new C++ code written for the project.
