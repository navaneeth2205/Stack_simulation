#include<bits/stdc++.h>

// --- ADDED THIS SECTION ---
#ifdef _WIN32
#include <windows.h>
#endif
// --------------------------

using namespace std;

struct WebPage {
    string url;
    string title;
    WebPage(string u, string t) : url(u), title(t) {}
    string toString() const { return title + " (" + url + ")"; }
};

class BrowserHistory {
private:
    stack<WebPage> backStack;
    stack<WebPage> forwardStack;

public:
    BrowserHistory(string homepage) {
        backStack.push(WebPage(homepage, "Google Search"));
        clearScreen();
        showWelcome(homepage);
    }

    void visit() {
        string url, title;
        getPageInfo(url, title);
        if (!url.empty()) {
            string pageTitle = title.empty() ? getTitle(url) : title;
            showOperation("🌐 VISIT NEW PAGE", pageTitle, url, "➕ PUSH(backStack.push())");
            backStack.push(WebPage(url, pageTitle));
            if (!forwardStack.empty()) {
                showOperation("🧹 CLEAR HISTORY", "Forward Stack", "", "🔄 POP(forwardStack) x ALL");
                while (!forwardStack.empty()) forwardStack.pop();
            }
            showResult("✅ SUCCESS", backStack.top().toString());
        } else {
            showResult("❌ ERROR", "URL cannot be empty!");
        }
    }

    string goBack() {
        if (backStack.size() <= 1) {
            showResult("⛔ LIMIT", "Cannot go back further!");
            return backStack.top().url;
        }
        WebPage current = backStack.top();
        showOperation("⬅️ GO BACK", current.toString(), "", "⬅️ POP(backStack) + PUSH(forwardStack)");
        backStack.pop();
        forwardStack.push(current);
        showResult("✅ BACK", backStack.top().toString());
        return backStack.top().url;
    }

    string goForward() {
        if (forwardStack.empty()) {
            showResult("⛔ LIMIT", "Cannot go forward!");
            return backStack.top().url;
        }
        WebPage nextPage = forwardStack.top();
        showOperation("➡️ GO FORWARD", nextPage.toString(), "", "➡️ POP(forwardStack) + PUSH(backStack)");
        forwardStack.pop();
        backStack.push(nextPage);
        showResult("✅ FORWARD", backStack.top().toString());
        return backStack.top().url;
    }

    void showCurrent() {
        showResult("📍 CURRENT", backStack.top().toString());
    }

    void showHistory() {
        clearScreen();
        drawBeautifulStacks();
        cout << "\n" << repeatChar('=', 60) << "\n\n";
        showMenu();
    }

    void handleInvalid() {
        showResult("❓ INVALID", "Type 1-6 or 'visit/back/forward/current/history/quit'");
    }

    void quit() {
        clearScreen();
        cout << "\n" << repeatChar('=', 50) << "\n";
        cout << "           👋 Thanks for using Stack Browser!           \n";
        cout << "           " << repeatChar('=', 26) << "            \n\n";
    }

private:
    string repeatChar(char c, int count) {
        return string(count, c);
    }

    void getPageInfo(string& url, string& title) {
        clearScreen();
        cout << repeatChar('=', 50) << "\n";
        cout << "            🌐 NEW PAGE VISIT            \n";
        cout << repeatChar('=', 50) << "\n\n";
        cout << " 🔗 URL: ";
        getline(cin, url);
        cout << " 📄 Title: ";
        getline(cin, title);
        cout << "\n" << repeatChar('=', 50) << "\n";
    }

    void showOperation(string title, string name, string url, string stackOp) {
        clearScreen();
        cout << repeatChar('=', 55) << "\n";
        cout << "        " << title << "        \n";
        cout << repeatChar('=', 55) << "\n\n";
        cout << "\n 🔧 LIVE STACK OPERATION:\n";
        cout << "    " << stackOp << "\n\n";
        animateStackOperation(stackOp);
        cout << "\n ✅ STACK OPERATION COMPLETED!\n\n";
        this_thread::sleep_for(chrono::milliseconds(1500));
    }

    void animateStackOperation(string operation) {
        bool hasPop = operation.find("POP") != string::npos;
        bool hasPush = operation.find("PUSH") != string::npos;

        if (hasPop) {
            cout << "   📤 POPPING ";
            for (int i = 0; i < 4; i++) {
                cout << "⬆️ ";
                cout.flush();
                this_thread::sleep_for(chrono::milliseconds(300));
            }
            cout << "\n";
        }

        if (hasPush) {
            cout << "   📥 PUSHING ";
            for (int i = 0; i < 4; i++) {
                cout << "⬇️ ";
                cout.flush();
                this_thread::sleep_for(chrono::milliseconds(300));
            }
            cout << "\n";
        }
    }

    void showResult(string icon, string message) {
        clearScreen();
        showStatusWithResult(icon, message);
    }

    void showStatusWithResult(string icon, string message) {
        cout << repeatChar('-', 55) << "\n";
        cout << " " << icon << " " << message << "\n";
        cout << repeatChar('-', 55) << "\n\n";
        cout << " 📊 STATUS: Back Stack(" << backStack.size()
             << ") | Forward Stack(" << forwardStack.size() << ") 📊\n\n";
        showMenu();
    }

    void drawBeautifulStacks() {
        vector<WebPage> back, forward;
        extractStacks(back, forward);

        cout << repeatChar('=', 70) << "\n";
        cout << "      🔵 BACK STACK 🔵       |       🔴 FORWARD STACK 🔴       \n";
        cout << repeatChar('=', 70) << "\n";

        int maxH = max(back.size(), forward.size());
        // Print from TOP (index 0) to BOTTOM
        for (int i = 0; i < maxH; i++) {
            if (i < back.size()) {
                string t = truncate(back[i].title, 20);
                // 🟢 marks TOP element at index 0 (i==0)
                cout << (i==0 ? "🟢 " : "  ") << left << setw(22) << t;
            } else {
                cout << left << setw(24) << "";
            }
            cout << "|";
            if (i < forward.size()) {
                string t = truncate(forward[i].title, 20);
                // 🟢 marks TOP element at index 0 (i==0)
                cout << (i==0 ? "🟢 " : "  ") << left << setw(22) << t;
            } else {
                cout << left << setw(24) << "";
            }
            cout << "\n";
        }

        cout << repeatChar('-', 24) << "|" << repeatChar('-', 24) << "\n\n";
        cout << "🟢 TOP=Recent | Back:" << back.size() << " | Forward:" << forward.size() << "\n";
    }

    void extractStacks(vector<WebPage>& back, vector<WebPage>& fwd) {
        // Extract back stack - top first
        stack<WebPage> tempBack = backStack;
        while (!tempBack.empty()) {
            back.push_back(tempBack.top());  // back[0] = TOP (bvafhmh)
            tempBack.pop();
        }

        // Extract forward stack - top first
        stack<WebPage> tempForward = forwardStack;
        while (!tempForward.empty()) {
            fwd.push_back(tempForward.top());
            tempForward.pop();
        }
    }

    string truncate(string s, int maxLen) {
        if ((int)s.length() > maxLen) s = s.substr(0, maxLen-3) + "...";
        return s;
    }

    string getTitle(string url) {
        if (url.find("google") != string::npos) return "Google Search Engine";
        if (url.find("leetcode") != string::npos) return "LeetCode Practice";
        if (url.find("github") != string::npos) return "GitHub Repository";
        if (url.find("stackoverflow") != string::npos) return "Stack Overflow Q&A";
        return "Web Page";
    }

    void showStatus() {
        clearScreen();
        showStatusWithResult("", "Ready");
    }

    void showMenu() {
        cout << repeatChar('=', 60) << "\n";
        cout << "         STACK BROWSER - LIVE OPERATIONS         \n";
        cout << repeatChar('=', 60) << "\n\n";
        cout << " 1️⃣ VISIT           -> PUSH(backStack)                     \n";
        cout << " 2️⃣ BACK            <- POP(backStack) -> PUSH(forward)      \n";
        cout << " 3️⃣ FORWARD         -> POP(forward) -> PUSH(backStack)      \n";
        cout << " 4️⃣ CURRENT         -> backStack.top()                    \n";
        cout << " 5️⃣ HISTORY         -> Visualize Stack States            \n";
        cout << " 6️⃣ QUIT            -> Exit Program                       \n\n";
        cout << repeatChar('=', 60) << "\n> ";
    }

    void showWelcome(string homepage) {
        clearScreen();
        cout << repeatChar('=', 55) << "\n";
        cout << "            🕷️ STACK BASED BROWSER 🕷️            \n";
        cout << repeatChar('=', 55) << "\n";
        cout << " 🚀 Started at: " << getTitle(homepage) << "\n";
        showMenu();
    }

    void clearScreen() {
        system("cls || clear");
    }
};

int main() {
    // --- ADDED THIS SECTION ---
    // Forces the console to use UTF-8 encoding so emojis display correctly on Windows
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    // --------------------------

    BrowserHistory browser("https://google.com");
    string cmd;
    while (getline(cin, cmd)) {
        if (cmd == "quit" || cmd == "6") {
            browser.quit();
            break;
        }
        if (cmd == "visit" || cmd == "1") browser.visit();
        else if (cmd == "back" || cmd == "2") browser.goBack();
        else if (cmd == "forward" || cmd == "3") browser.goForward();
        else if (cmd == "current" || cmd == "4") browser.showCurrent();
        else if (cmd == "history" || cmd == "5") browser.showHistory();
        else browser.handleInvalid();
    }
    return 0;
}
