# Program 3 — Image Filter Pipeline

**Course:** 2143 - Object Oriented Programming  
**ID:** 10-P03  
**Points:** 100  
**Date Assigned:** 2026-04-06 12:00  
**Date Due:** 2026-04-24 11:00  

---

This program extends your **Args parser (P02)** into a full image processing pipeline.

The key design pattern is **Strategy**:

- Each image operation is implemented as a class derived from a common `Filter` interface.
- A `Pipeline` object stores and executes filters in sequence.
- Adding new behavior requires only a new filter class — no changes to `main.cpp` or `Pipeline`.

> Program 4 will extend this system with convolution kernels and advanced color operations.

---


```cpp
class Filter {
public:
    virtual void apply(Grid& pixels) = 0;
    virtual std::string name() const = 0;
    virtual ~Filter() = default;
};
