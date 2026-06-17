# Presentation Script (Roman Urdu)
## Student Grade Management & Analytics System

Yeh script 10-minute ki presentation ke liye word-by-word taiyar ki gayi hai. Isko bolte waqt confidence aur natural tone ka khayal rakhein.

---

### 🎤 Phase 1: Introduction & Slide 1-2 (Time: 0:00 - 2:00)
#### **Presenter 1 (Ali Ahmed - Roll No: F24-101)**

**Script:**
"Assalam-o-Alaikum Sir/Ma'am aur mere class fellows. Mera naam **Ali Ahmed** hai aur aaj humari group presentation ka topic hai **Student Grade Management and Analytics System**. Humne yeh project Programming Fundamentals ke core concepts ko use karte hue banaya hai.

Is project ka main objective yeh hai ke schools aur colleges ke teachers jo manually grades aur averages calculate karte hain, unka time bache aur data hamesha safe rahe. Humari application ke do versions hain:
1. **CLI (Terminal Edition):** Jo bilkul lightweight hai aur code ke core components ko display karta hai.
2. **GUI (Graphical Desktop App):** Jo advanced analytics aur interlinked charts ke sath visual performance summaries details show karta hai.

Hum dono versions ke backend par aik hi file database use kar rahe hain taake agar aap terminal par koi student add karein, toh wo direct GUI me update ho jaye, aur GUI me add karein toh wo terminal me update ho jaye.

Ab mai hand over karunga **Hamza** ko jo aapko backend logic aur terminal implementation ke baare me batayenge. Thank you."

---

### 🎤 Phase 2: CLI & Code Logic (Time: 2:00 - 4:30)
#### **Presenter 2 (Hamza Khan - Roll No: F24-102)**

**Script:**
"Thank you Ali. Assalam-o-Alaikum class. Mera naam **Hamza Khan** hai. Mai aapko humare system ke C++ core architecture aur CLI module ke baare me bataunga.

Humne database design karne ke liye kisi external SQL library ko use nahi kiya balki pure C++ standard file handling (`std::ifstream` aur `std::ofstream`) ko use kiya hai. Humara database `students_db.txt` hai jahan records pipe-delimited format me store hote hain.

Humare code me key Programming Fundamentals concepts implement hue hain:
1. **Structures (`struct Student`):** Ek single entity me Roll Number, Name, 5 subjects ke marks array, Total Marks, Average aur Letter Grade ko bundle karne ke liye use kiya hai.
2. **Arrays (`float marks[5]`):** Har student ke individual subjects ke numbers track karne ke liye.
3. **Loops aur Conditionals:** Grade nikalne ke liye humne nested `if-else` use kiya hai jahan scale 85% se A, 75% se B, 60% se C aur 50% se D set kiya hai.

Jab hum system run karte hain, CLI version me hume visual text menu milta hai. Yahan se hum students add kar sakte hain, roll number se search kar sakte hain, database clean kar sakte hain, aur dynamic list generate kar sakte hain.

Ab mai **Sara** ko request karunga ke wo GUI aur active dashboard ka live demo show karein. Thank you."

---

### 🎤 Phase 3: GUI & Live Analytics Demo (Time: 4:30 - 7:30)
#### **Presenter 3 (Sara Noor - Roll No: F24-103)**

**Script:**
"Thank you Hamza. Assalam-o-Alaikum Sir. Mera naam **Sara Noor** hai aur mai aapko GUI Application ka live demo dikhaungi.

Jaise hi hum application launch karte hain, main screen par hume ek premium dashboard dikhta hai. Iske right side par **Student Registry** tab hai jisme real-time table show ho raha hai. Is table me column selection stretching automatic responsive hai taake columns screen size ke sath expand aur contract ho sakein.

Niche humne **Class Performance Summary KPIs** design kiye hain. Yahan class ke metrics auto-calculate hote hain:
1. **Evaluated Students:** Total kitne entries hain.
2. **Class Average Mark:** Puri class ka average percentage kya chal raha hai.
3. **Class Topper:** Sabse highest score karne wala student aur uske total marks.
4. **Lowest Performer:** Kis student ko assistance ki zaroorat hai.

Ab mai dynamic add form perform karungi. Jab mai **Add Student** par click karti hoon toh dialog box open hota hai. Yahan safety input checks hain, yaani agar marks `0` se kam ya `100` se zyada likhe jayein toh inputs automate clamp ho jate hain. 

Jaise hi hum numeric values enter karte hain, text labels par live status update hota hai ke dynamic total, average aur expected grade kya banega. Add karne par table instantly update hota hai aur charts automatically change ho jate hain.

Analytics tab me humne **Qt Charts** integrate kiya hai. Yahan do main graphs hain:
1. **Bar Chart:** Jo subject-wise performance benchmarks show karta hai.
2. **Pie Chart:** Jo grade A, B, C, D aur F ki class percentage distribution visually partition karta hai.

Ab mai request karungi Ali ko ke wo dynamic themes aur Linux package installation ko wind up karein. Thank you."

---

### 🎤 Phase 4: Theme Switching & Linux Mint Packaging (Time: 7:30 - 9:30)
#### **Presenter 1 (Ali Ahmed - Roll No: F24-101)**

**Script:**
"Thank you Sara. Ji, toh ab mai aapko do important features dikhaunga: **Dynamic Theme Toggle** aur **Linux Mint Packaging**.

Humne application ko dynamic look dene ke liye customized stylesheet files lagayi hain. Jab hum top right button click karte hain:
- System instant switch karta hai **Dark Cosmic Gradient** (jis me deep spaces gradients aur neon borders hain) se **Celestial Light Gradient** (jis me soft sky gradients aur clear text borders hain) par.
- Is switch ke dauran GUI components aur table header cells ke sath dynamic graphs aur plot labels bhi auto-adjust hote hain taake readibility kharab na ho.

Second, Linux Mint humara target platform tha. Application ko build, compile aur package karne ke liye humne script build ki hai. `build_deb.sh` system ke absolute paths ko construct karti hai, execute permission define karti hai, aur final **`.deb` package installer** ready karti hai.

Aap Mint user interface me is `.deb` file par double click karke normal software package ki tarah install kar sakte hain. Iska launcher menu shortcut applications section me create ho jata hai aur system me application cap aur charts wala unique brand icon set ho jata hai.

Humne source control ke liye clean git environment setup kiya hai, aur presentation ready material hum usb me sath le kar aaye hain. Hard copy and source files compile ki ja chuki hain."

---

### 🎤 Phase 5: Q&A & Closing (Time: 9:30 - 10:00)
#### **All Presenters**

**Script (Presenter 1):**
"Humara code files complete compile hain aur structural data validation successfully clear hai. Ab agar examiner ya class fellows ka koi question ho, toh hum use answer karne ke liye ready hain. Thank you very much!"
