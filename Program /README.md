# Program 1 — Image Tool

## Course Information
** Gabriel Ofori
- **Course:** 2143 - Object Oriented Programming
- **Program ID:** 06-P01
- **Assigned:** March 2, 2026 @ 12:00
- **Due:** March 9, 2026 @ 11:00
- **Points:** 100

---



This program loads an image, converts it to grayscale using the luminance formula, and saves the result as a PNG image.

Additional features added:
- Colored terminal output using the `termcolor` library
- Automatically opens the output image in the system's default image viewer

---



```text
06-P01/
├── README.md
├── src/
│   └── main.cpp
├── include/
│   ├── stb_image.h
│   ├── stb_image_write.h
│   └── termcolor.hpp
├── images/
│   ├── Hulda.png
│   ├── Hulda.jpg
│   └── HuldaBW.png
└── docs/
    └── compile_cmd.md
```

---


Compile from the project root:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude src/main.cpp -o imgtool
```

Run the program:

```bash
./imgtool images/Hulda.png output.png
```

---



The program uses the `termcolor` library to display:
- Usage errors in color
- Load failures in color
- Success messages in color

Example:

```cpp
std::cout << green  << "Saved output to: "
          << yellow << outputPath
          << reset  << "\n";
```

---



After saving the grayscale image, the program automatically attempts to open it using the operating system's default image viewer.

Supported platforms:
- Windows
- macOS
- Linux

Example function:

```cpp
bool open_file_default_app(const std::string& path) {
#if defined(_WIN32)
    std::string cmd = "start \"\" \"" + path + "\"";
#elif defined(__APPLE__)
    std::string cmd = "open \"" + path + "\"";
#else
    std::string cmd = "xdg-open \"" + path + "\"";
#endif

    return std::system(cmd.c_str()) == 0;
}
```

---

- Submit only `src/main.cpp`
- Program must compile with:
  - `-Wall`
  - `-Wextra`
  - `-pedantic`
- No extra features should be added
- Viewer launch may fail in remote environments without a GUI

---



```bash
./imgtool images/Hulda.png HuldaBW.png
```

Expected behavior:
1. Image loads successfully
2. Grayscale conversion occurs
3. Output image saves successfully
4. Output image opens automatically

---


| Category | Points |
|---|---:|
| Compiles clean | 20 |
| Usage message colored | 15 |
| Error message colored | 10 |
| Success message colored | 15 |
| Function defined | 20 |
| Function called | 10 |
| Code quality | 10 |
| Total | 100 |

---



Name: YOUR NAME HERE  
Course: 2143 Object Oriented Programming
