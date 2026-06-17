# Build Instructions

This project includes two build flows:
1. Terminal Edition (CLI)
2. GUI Edition (Qt6) with Debian package creation

---

## 1. Terminal Edition (CLI)

```bash
cd terminal
g++ -std=c++17 main.cpp -o student_manager
./student_manager
```

---

## 2. GUI Edition (Qt6)

### Install dependencies

```bash
sudo apt update
sudo apt install cmake g++ qt6-base-dev qt6-charts-dev
```

### Configure and build

```bash
cd gui
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

### Run GUI app

```bash
./gui/build/StudentGradeManager
```

---

## 3. Debian Package Build

This project includes a packaging folder and `build_deb.sh` script to create a `.deb` package.

### Build package using script

```bash
./build_deb.sh
```

### Manual packaging steps

```bash
mkdir -p packaging/usr/bin
mkdir -p packaging/usr/share/applications
mkdir -p packaging/usr/share/pixmaps
mkdir -p packaging/DEBIAN

cd gui
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)

cp gui/build/StudentGradeManager packaging/usr/bin/studentgrademanager
cp packaging/usr/share/applications/studentgrademanager.desktop packaging/usr/share/applications/studentgrademanager.desktop
cp packaging/usr/share/pixmaps/studentgrademanager.png packaging/usr/share/pixmaps/studentgrademanager.png

chmod 755 packaging/usr/bin/studentgrademanager
chmod 755 packaging/DEBIAN
chmod 644 packaging/DEBIAN/control
chmod 644 packaging/usr/share/applications/studentgrademanager.desktop
chmod 644 packaging/usr/share/pixmaps/studentgrademanager.png

dpkg-deb --build packaging studentgrademanager_1.0.0_amd64.deb
```

### Install the generated package

```bash
sudo dpkg -i studentgrademanager_1.0.0_amd64.deb
sudo apt-get install -f
```

---

## Notes

- `build_deb.sh` already automates the rebuild and packaging flow.
- If you change source files, rerun `cmake` and `make` in `gui/build` before packaging.
- The project uses Qt6 and requires `qt6-base-dev` and `qt6-charts-dev` for GUI compilation.
