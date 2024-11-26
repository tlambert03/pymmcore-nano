pip install meson-python ninja build

mkdir -p subprojects
meson wrap install robin-map
meson wrap install nanobind


rm -rf builddir
export CXX=/opt/homebrew/opt/llvm/bin/clang++
export LDFLAGS="-L/opt/homebrew/opt/llvm/lib -Wl"
meson setup builddir
meson compile -C builddir

rm -rf builddir
export CXX=/usr/bin/c++
export CXXFLAGS="-isystem /Library/Developer/CommandLineTools/usr/include/c++/v1"
export LDFLAGS="-L/Library/Developer/CommandLineTools/usr/lib -Wl,-rpath,/Library/Developer/CommandLineTools/usr/lib"
meson setup builddir
meson compile -C builddir