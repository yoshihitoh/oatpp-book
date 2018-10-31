set AR="/usr/bin/ar"
set RANLIB="/usr/bin/ranlib"

premake5 gmake2
premake5 xcode4
cd build-gmake && make -j$(sysctl -n hw.ncpu)
