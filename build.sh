clang++ -std=c++17 -stdlib=libc++ \
-I$(pwd)/filament/include -I/usr/include/SDL2 main.cpp \
-L$(pwd)/filament/lib/x86_64 \
-lfilament -lfilabridge -lfilaflat -lfilamat -lfilameshio \
-lgltfio -lgltfio_core -lgeometry -ldracodec -lktxreader -lzstd \
-lmeshoptimizer -lstb -limage -lsmol-v \
-lfilament-iblprefilter -libl \
-lbackend -lbluegl -lbluevk -lutils \
-lSDL2 -lvulkan -ldl -lpthread -lm
