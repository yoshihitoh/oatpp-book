premake5 gmake2
premake5 xcode4
cd build-gmake && make -j$(sysctl -n hw.ncpu)
