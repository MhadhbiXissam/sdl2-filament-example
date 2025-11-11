# Makefile

# Filament version
FILAMENT_VERSION := v1.54.4
FILAMENT_TGZ := filament-$(FILAMENT_VERSION)-linux.tgz
FILAMENT_DIR := filament

# Source and target
SRC := main.cpp
TARGET := a.out
MAT_FILE := default.mat
FILAMAT_FILE := default.filamat

# Compiler and flags
CXX := clang++
CXXFLAGS := -std=c++17 -stdlib=libc++ -I$(PWD)/$(FILAMENT_DIR)/include -I/usr/include/SDL2
LDFLAGS := -L$(PWD)/$(FILAMENT_DIR)/lib/x86_64 \
           -lfilament -lfilaflat -lfilabridge -lfilamat -lfilameshio \
           -lgltfio -lgltfio_core -lgeometry -ldracodec -lktxreader -lzstd \
           -lmeshoptimizer -lstb -limage -lsmol-v \
           -lfilament-iblprefilter -libl \
           -lbackend -lbluegl -lbluevk -lutils \
           -lSDL2 -lvulkan -ldl -lpthread -lm

.PHONY: all clean install deps filament material

# Default target
all: material $(TARGET)

# Build the C++ executable
$(TARGET): $(SRC) $(FILAMAT_FILE)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Compile .mat to .filamat
$(FILAMAT_FILE): $(MAT_FILE)
	@echo "Building material..."
	@$(FILAMENT_DIR)/bin/matc -p desktop  -o $(FILAMAT_FILE) $(MAT_FILE)

# Clean build artifacts
clean:
	rm -f $(TARGET) $(FILAMAT_FILE)

# Install dependencies and Filament
install: deps filament
	@echo "Filament installed. You can now run 'make' to build the project."

# Install system dependencies
deps:
	sudo apt-get update
	sudo apt-get -y install libsdl2-dev ninja-build clang libc++-dev libc++abi-dev \
	                        libxi-dev libxcomposite-dev libxxf86vm-dev g++ build-essential wget

# Download Filament if not present
filament:
	@if [ ! -d "$(FILAMENT_DIR)" ]; then \
		wget https://github.com/google/filament/releases/download/$(FILAMENT_VERSION)/$(FILAMENT_TGZ); \
		tar -xf $(FILAMENT_TGZ); \
		rm $(FILAMENT_TGZ); \
	fi
