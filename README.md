# botui

Botui is a device-independent graphical interface designed initially for the Kovan controller.

The icons used throughout botui are from the [Font Awesome](https://fontawesome.com/icons?d=gallery) by © Fonticons, Inc.

# Requirements

- [libkar](https://github.com/kipr/libkar)
- [pcompiler ](https://github.com/kipr/pcompiler)
- CMake 3.10 or later
- Qt 6

# Build

# Cross-compile to the Wombat (Raspberry Pi 3b+)

Local build, tested on Debian 13.
Be aware that `:arm64` versions of packages often conflict with `x86_64` versions, so if these commands fail try the Docker build.

```bash
sudo dpkg --add-architecture arm64
sudo apt update
sudo apt install make cmake gcc-aarch64-linux-gnu g++-aarch64-linux-gnu qt6-base-dev:arm64  qt6-declarative-dev:arm64 libssl-dev:arm64 zlib1g-dev:arm64

cmake -Bbuild -DCMAKE_TOOLCHAIN_FILE=toolchain/aarch64-linux-gnu.cmake .
cmake --build build -j "$(nproc)" --target package-debian
```

Build with Docker:

```bash
docker build -t botui-builder .
docker run --rm --mount type=bind,source=.,destination=/src/ botui-builder sh -c 'cmake -B/src/build -DCMAKE_TOOLCHAIN_FILE=/src/toolchain/aarch64-linux-gnu.cmake /src && cmake --build /src/build -j "$(nproc)" --target package-debian'
```

## Old instructions

```bash
git clone https://github.com/kipr/botui
cd botui
mkdir build
cd build
cmake .. or /home/<container name>/qt-raspi/bin/qt-cmake -Ddocker_cross=ON .. (for docker cross compilation)
make -j4
sudo make install
```

# License

Botui is released under the terms of the GPLv3. For more information, see the LICENSE file.

Want to Contribute? Start Here!: 
https://github.com/kipr/KIPR-Development-Toolkit
