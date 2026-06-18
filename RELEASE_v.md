# v

Release date: 2026-06-18

## Summary

This release packages the Student Grade Management System (version 1.0.1) for amd64 Linux as a .deb installer and includes build instructions and cleaned up project metadata.

## Highlights

- Portable build script (`build_deb.sh`) — no hard-coded local paths.
- Maintainer metadata updated to `Mubashir Ali & Group <mubashirali1837@gmail.com>`.
- Removed lab/semester labels from the terminal edition UI for a neutral presentation.
- Added `build.md` with portable build and packaging steps.
- Cleaned `.gitignore` to avoid committing runtime artifacts.

## Changelog

- Update maintainer email and name.
- Replace local-only artifact paths with repository-relative paths.
- Remove educational lab header from terminal menu.
- Add release documentation and build instructions.

## Assets

-- Debian package: `studentgrademanager_1.0.1_amd64.deb` (at repository root)

## Checksum

SHA256(studentgrademanager_1.0.1_amd64.deb) = `97c51ec98973685ab3b388791b6835d4abc19c63fa567cbec2d121651a1ac7fc`

## Installation

Install the provided Debian package:

```bash
sudo dpkg -i studentgrademanager_1.0.1_amd64.deb
sudo apt-get install -f
```

Or build from source (see `build.md`):

```bash
# Build GUI
cd gui
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)

# Build terminal edition
cd ../../terminal
g++ -std=c++17 main.cpp -o student_manager
```

## Notes

- For exact build steps and dependency installation, see [build.md](build.md).
- To report issues, open an issue at the repository: https://github.com/mubashir1837/Student-Grade-Management-System/issues

## Credits

Maintainer: Mubashir Ali & Group <mubashirali1837@gmail.com>

---

Thank you for using Student Grade Management System.
