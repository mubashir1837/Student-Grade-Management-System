#!/bin/bash
set -e

# Define directories
WORKSPACE_DIR="/home/ali/LAB-PF-FINAL"
GUI_DIR="$WORKSPACE_DIR/gui"
PACKAGING_DIR="$WORKSPACE_DIR/packaging"
IMAGE_PATH="/home/ali/.gemini/antigravity/brain/713ae9b4-a0bc-44db-b844-e63a3688d906/studentgrademanager_1781727451528.png"

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

if [ -f "$IMAGE_PATH" ]; then
    echo "Found custom generated icon. Copying..."
    cp "$IMAGE_PATH" "$PACKAGING_DIR/usr/share/pixmaps/studentgrademanager.png"
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
dpkg-deb --build packaging studentgrademanager_1.0.0_amd64.deb

echo "=== SUCCESS! debian package created at: studentgrademanager_1.0.0_amd64.deb ==="
