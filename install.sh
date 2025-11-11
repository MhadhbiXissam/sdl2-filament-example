sudo apt-get update
sudo apt-get -y install libsdl2-dev 
#####################################################""
apt update 
apt install -y ninja-build
sudo apt install -y clang libc++-dev libc++abi-dev
apt install -y libxi-dev libxcomposite-dev libxxf86vm-dev
wget https://github.com/google/filament/releases/download/v1.54.4/filament-v1.54.4-linux.tgz
tar -xf filament-v1.54.4-linux.tgz 
rm filament-v1.54.4-linux.tgz
#clang++ -std=c++17 -stdlib=libc++ main.cpp -I$(pwd)/filament/include -L$(pwd)/filament/lib/x86_64  -lbluevk -lvkshaders -lmatdbg -lbluegl -lfilament-iblprefilter -lktxreader -lzstd -limage -lfilament -lfilamat -lfilabridge -libl -lgltfio -lgltfio_core -lgeometry -ldracodec -lmikktspace -libl-lite -lshaders -lmeshoptimizer -lstb -lviewer -lcivetweb -lfilaflat -lcamutils -lfilameshio -lsmol-v -lbasis_transcoder -lutils -lbackend -luberzlib -luberarchive
 