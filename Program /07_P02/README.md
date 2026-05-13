# Program 2 — Args Parser

## Course Info
- **Course:** 2143 - Object Oriented Programming
- **Program:** 07-P02
- **Title:** Command-Line Args Parser

---


This program builds the argument parser for `imgtool`.

The parser:
- Reads command-line arguments
- Validates input
- Stores options inside an `Args` object
- Prints parsed results

No image processing is done in this assignment.

---



```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/main.cpp src/Args.cpp -o imgtool
```

---



```bash
./imgtool in.png out.png --grayscale --brighten 20
```

```bash
./imgtool photo.jpg result.png --rotate=90 --flipH
```
## Invalid
```bash
./imgtool in.png out.png --graycale
```

Output:

```text
Error: unknown option '--graycale'
Usage: ./imgtool <input_image> <output_image> [options]
```

---

| Long | Short | Description |
|---|---|---|
| `--grayscale` | `-g` | Grayscale |
| `--blur` | `-l` | Blur |
| `--flipH` | `-h` | Flip horizontal |
| `--flipV` | `-v` | Flip vertical |

## Options With Values

| Long | Short | Constraint |
|---|---|---|
| `--brighten N` | `-b N` | `[-255,255]` |
| `--rotate N` | `-r N` | `{0,90,180,270}` |

Accepted formats:

```bash
--brighten 20
--brighten=20
```

---



```text
INPUT  : in.png
OUTPUT : out.png
FLAGS  : grayscale blur
PARAMS : brighten=20 rotate=90
```

---



- `src/Args.h`
- `src/Args.cpp`
- `src/main.cpp`
- `README.md`

---



- No external CLI libraries allowed
- `main.cpp` should not be modified
- Program must compile with no warnings

---


GABRIEL OFORI
