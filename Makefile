# Makefile for offscreen Filament PBR example

FILAMENT_DIR := filament
SRC := main.cpp
TARGET := offscreen_pbr

CXX := clang++
CXXFLAGS := -std=c++17 -stdlib=libc++ -I$(PWD)/$(FILAMENT_DIR)/include \
            -Wno-unknown-warning-option -Wno-deprecated-declarations
LDFLAGS := -L$(PWD)/$(FILAMENT_DIR)/lib/x86_64 \
           -lfilament -lfilaflat -lfilabridge -lfilamat -lfilameshio \
           -lgltfio -lgltfio_core -lgeometry -ldracodec -lktxreader -lzstd \
           -lmeshoptimizer -lstb -limage -lsmol-v \
           -lfilament-iblprefilter -lbackend -lbluegl -lbluevk -lutils \
           -lvulkan -ldl -pthread -lm

.PHONY: all clean deps filament

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

deps:
	sudo apt-get update
	sudo apt-get install -y clang libc++-dev libc++abi-dev g++ build-essential wget ninja-build libvulkan-dev
