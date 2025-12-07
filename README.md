**🕷️ Stack-Based Browser Simulator**
A C++ console application simulating basic browser operations using two stacks (Back and Forward stacks). This project demonstrates stack-based navigation similar to how real browsers handle Back and Forward histories.

**🌐 Overview**
The program lets the user:

Visit new web pages

Navigate backward and forward

View current page

Display a visualized stack history

Quit gracefully

All stack operations are animated and displayed beautifully in the terminal.

**⚙️ Features**
Visit New Page → Pushes a new WebPage object onto the back stack and clears forward stack.

Go Back → Pops current page from back stack and pushes it onto forward stack.

Go Forward → Pops a page from forward stack and pushes it onto back stack.

View History → Displays both stacks side by side (top-to-bottom order).

Multi-platform console clearing using system("cls || clear").

Interactive UI with colored emoji-based feedback and animations.

**🧩 Data Structures**
The application uses the Stack (LIFO) data structure:

stack<WebPage> backStack — stores the browsing history.

stack<WebPage> forwardStack — stores pages for forward navigation.

WebPage Structure
cpp
struct WebPage {
    string url;
    string title;
    WebPage(string u, string t);
    string toString() const;
};
BrowserHistory Class
Key public methods include:

visit() — Opens a new page.

goBack() — Navigates backward.

goForward() — Navigates forward.

showCurrent() — Displays the active web page.

showHistory() — Prints a visual representation of both stacks.

quit() — Exits the program.

**🚀 How It Works**
The program starts with a homepage (Google) and presents a simple menu for operations.

Example menu:
text
1️⃣ VISIT          -> PUSH(backStack)
2️⃣ BACK           <- POP(backStack) -> PUSH(forward)
3️⃣ FORWARD        -> POP(forward) -> PUSH(backStack)
4️⃣ CURRENT        -> backStack.top()
5️⃣ HISTORY        -> Visualize Stack States
6️⃣ QUIT           -> Exit Program
Each operation triggers live animations:

📤 POPPING ⬆️⬆️⬆️

📥 PUSHING ⬇️⬇️⬇️

and real-time stack visualization.

**🧠 Concept Demonstration**
Operation	Stack Behavior	Description
Visit()	backStack.push(newPage), forwardStack.clear()	Opens a new webpage
Back()	forwardStack.push(backStack.top()), backStack.pop()	Goes one step backward
Forward()	backStack.push(forwardStack.top()), forwardStack.pop()	Goes one step forward
This clearly demonstrates the LIFO (Last-In-First-Out) nature of stacks.

**🖥️ How to Run**
1. Compile
Use g++ (MinGW-w64 on Windows):

bash
g++ -std=c++11 stack_browser.cpp -o stack_browser
2. Run
bash
./stack_browser
3. Commands
You can use either number or keyword:

text
visit  or 1
back   or 2
forward or 3
current or 4
history or 5
quit    or 6
🧰 Example Session
text
> visit
🔗 URL: https://leetcode.com
📄 Title: LeetCode Practice
✅ SUCCESS - LeetCode Practice (https://leetcode.com)

> back
✅ BACK - Google Search Engine (https://google.com)

> forward
✅ FORWARD - LeetCode Practice (https://leetcode.com)

> history
🔵 BACK STACK | 🔴 FORWARD STACK
🟢 LeetCode Practice | (empty)


**🧱 Core Concepts Used**
Stack operations (push, pop, top, empty)

Object-Oriented Programming (structs/classes)

Console UI design

String manipulation & formatting

Sleep and animation effects using <thread> and <chrono>

**💡 Learning Outcome**
This project visually explains:

How browser navigation is implemented internally using stacks.

Proper management of state transitions between backStack and forwardStack.

Interactive console-based approaches to demonstrate data structure behavior.

**🧾 License**
This project is open for educational and personal use.
Developed for demonstrating stack operations and OOP concepts in C++.

