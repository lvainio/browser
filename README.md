# Seal Browser 🦭

## Build instructions

### Ubuntu

#### Prerequisites

- CMake version 4.0 or higher
- A C++23-compatible compiler (e.g., GCC 13+ or Clang 16+)
- libcurl development package

Install libcurl development files:

```bash
sudo apt install libcurl4-openssl-dev
```

Create a new build directory from the root directory:  
```bash
mkdir build
cd build
```

Run CMake:  
```bash
cmake ..
```

Build the project:  
```bash
make
```

Run the executable:  
```bash
./browser
```

## Clang Format

### Ubuntu

#### Prerequisites

- Clang-format 20 or later.

Automatically format the file:
```bash
clang-format -i file
```

Check if formatting is needed:
```bash
clang-format --dry-run --Werror file
```

## Clang Tidy

### Ubuntu

#### Prerequisites

- Clang-tidy 20 or later.

clang-tidy src/url.h -p build