# Makefile

# Filament version
FILAMENT_VERSION := v1.54.4
FILAMENT_TGZ := filament-$(FILAMENT_VERSION)-linux.tgz
FILAMENT_DIR := filament

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

SRC := main.cpp
TARGET := a.out

.PHONY: all clean install deps

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

install: deps filament
	@echo "Filament installed. You can now run 'make' to build the project."

deps:
	sudo apt-get update
	sudo apt-get -y install libsdl2-dev ninja-build clang libc++-dev libc++abi-dev \
	                        libxi-dev libxcomposite-dev libxxf86vm-dev g++ build-essential wget

filament:
	@if [ ! -d "$(FILAMENT_DIR)" ]; then \
		wget https://github.com/google/filament/releases/download/$(FILAMENT_VERSION)/$(FILAMENT_TGZ); \
		tar -xf $(FILAMENT_TGZ); \
		rm $(FILAMENT_TGZ); \
	fi
