# Student Grade Management System
A premium C++ Student Grade Management System. This project features two fully-functional versions of the application:
1. **Terminal Edition (CLI):** Focused on core programming concepts (arrays, files, structs, loops, conditions) with a stylized colorful console.
2. **Analytics Dashboard (GUI):** Built on Qt6 Widgets and Qt Charts, featuring a gorgeous dark mode, live previews, and interactive visual data reporting.

---

## Project Structure
```text
Student-Grade-Management-System/
├── terminal/
│   ├── main.cpp         <-- Complete CLI implementation (ideal for printing hard copies)
│   └── student_manager  <-- Compiled CLI executable
├── gui/
│   ├── main.cpp         <-- Qt6 Application entry point
│   ├── mainwindow.h     <-- GUI Main Window declarations
│   ├── mainwindow.cpp   <-- GUI Main Window implementation (KPIs, table, events)
│   ├── addstudentdialog.h
│   ├── addstudentdialog.cpp <-- Live average/grade calculator form
│   ├── chartsview.h
│   ├── chartsview.cpp   <-- Qt Charts implementation (Bar & Pie Charts)
│   ├── student.h        <-- Shared structure and grade calculations
│   ├── style.qss        <-- Glassmorphism dark-mode stylesheet
│   └── resources.qrc    <-- Qt resources config (compiles QSS into binary)
├── packaging/           <-- Build folder structure for Debian packaging
│   ├── DEBIAN/control   <-- Package metadata (dependencies, version)
│   └── usr/             <-- Installation paths (executables, desktop file, icon)
├── build_deb.sh         <-- Automation script to compile GUI and build .deb package
├── studentgrademanager_1.0.0_amd64.deb <-- Finished installer for Linux Mint
└── README.md            <-- Project documentation & Presentation Guide
```

---

## ⚡ How to Build and Run

### 1. Terminal Edition (CLI)
Navigate to the `terminal` directory:
```bash
cd terminal
```
**Compile:**
```bash
g++ -std=c++17 main.cpp -o student_manager
```
**Run:**
```bash
./student_manager
```

### 2. GUI Edition (Qt6)
The GUI application is packageable and ready for direct installation on **Linux Mint**. 

**To Install the `.deb` Package:**
Double-click `studentgrademanager_1.0.0_amd64.deb` to open it in GDebi Package Installer, or run:
```bash
sudo dpkg -i studentgrademanager_1.0.0_amd64.deb
sudo apt-get install -f  # Fixes any missing dependencies
```
Once installed, the application will appear in your Mint application menu under **Education** / **Science** or can be launched by searching for "Student Grade Manager".

**To Compile manually from Source:**
1. Install dependencies:
   ```bash
   sudo apt update
   sudo apt install cmake g++ qt6-base-dev qt6-charts-dev
   ```
2. Navigate to `gui` and build:
   ```bash
   cd gui
   mkdir -p build && cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   make -j$(nproc)
   ```
3. Run:
   ```bash
   ./StudentGradeManager
   ```

---

## C++ Concepts Implemented
To satisfy the criteria of **Programming Fundamentals**, both editions implement:
- **Structs (`struct Student`):** Grouping related student variables (name, roll, subject marks, average, grade).
- **Arrays & Vectors (`float marks[5]`, `vector<Student>`):** Storing scores in 5 specific semester subjects and dynamically tracking multiple student entries.
- **File I/O (`ifstream` / `ofstream`):** Persisting data to `students_db.txt`. Both CLI and GUI editions read/write from the same database, demonstrating cross-application data sharing.
- **Loops & Conditions:** Using `for` loops to iterate through subject lists/student entries, and `switch` / `if-else` blocks for menu systems and grade assignments (A, B, C, D, F).
- **Functions:** Modular code layout with separate functions for adding, deleting, updating, and computing performance metrics.
