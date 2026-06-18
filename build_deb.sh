#!/bin/bash
set -e

# Define directories using the script's location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
WORKSPACE_DIR="$SCRIPT_DIR"
GUI_DIR="$WORKSPACE_DIR/gui"
PACKAGING_DIR="$WORKSPACE_DIR/packaging"
ICON_PATH="$WORKSPACE_DIR/gui/studentgrademanager.png"

echo "=== 1. Creating Packaging Directories ==="
mkdir -p "$PACKAGING_DIR/usr/bin"
mkdir -p "$PACKAGING_DIR/usr/share/applications"
mkdir -p "$PACKAGING_DIR/usr/share/pixmaps"
mkdir -p "$PACKAGING_DIR/DEBIAN"

echo "=== 2. Rebuilding GUI Application ==="
cd "$GUI_DIR"
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)

echo "=== 3. Copying Binary and Resources ==="
cp "$GUI_DIR/build/StudentGradeManager" "$PACKAGING_DIR/usr/bin/studentgrademanager"

if [ -f "$ICON_PATH" ]; then
    echo "Found custom icon in GUI folder. Copying..."
    cp "$ICON_PATH" "$PACKAGING_DIR/usr/share/pixmaps/studentgrademanager.png"
else
    echo "Custom icon not found, using generic icon placeholder."
    # Fail-safe just in case the file doesn't exist
    touch "$PACKAGING_DIR/usr/share/pixmaps/studentgrademanager.png"
fi

echo "=== 4. Setting Correct Permissions ==="
chmod -R 755 "$PACKAGING_DIR/usr/bin/studentgrademanager"
chmod -R 755 "$PACKAGING_DIR/DEBIAN"
chmod 644 "$PACKAGING_DIR/DEBIAN/control"
chmod 644 "$PACKAGING_DIR/usr/share/applications/studentgrademanager.desktop"
if [ -f "$PACKAGING_DIR/usr/share/pixmaps/studentgrademanager.png" ]; then
    chmod 644 "$PACKAGING_DIR/usr/share/pixmaps/studentgrademanager.png"
fi

echo "=== 5. Building Debian Package ==="
cd "$WORKSPACE_DIR"
dpkg-deb --build packaging studentgrademanager_1.0.1_amd64.deb

echo "=== SUCCESS! debian package created at: studentgrademanager_1.0.1_amd64.deb ==="
