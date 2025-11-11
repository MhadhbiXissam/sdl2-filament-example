# Filament + SDL2 Minimal Example

This project demonstrates a minimal example of using [Filament](https://google.github.io/filament/) with SDL2 in C++.

## Prerequisites

- Linux system (tested on Ubuntu 22.04)
- `sudo` privileges
- Internet connection (for downloading Filament)

## Build Instructions

1. **Clone the repository**

   ```bash
   git clone <your-repo-url>
   cd <your-repo-folder>
   ```
2. **Install dependencies and Filament** 

This will install required packages and download Filament automatically:

```bash
make install
```

3. **Build the project** 
```bash
make
```
This will produce the executable a.out.

4. **Run the example** 

```bash
./a.out
```


## Clean Build

To remove the compiled binary:
```bash
make clean
```

### Notes

Filament is downloaded and extracted automatically into the filament/ folder.

The Makefile uses clang++ with libc++ for compilation.

The example uses SDL2 to create an OpenGL context for Filament rendering.

