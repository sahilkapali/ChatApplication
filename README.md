# 💬 Chat Application in C++

A simple console-based chat application built using **C++** that allows users to register, login, add friends, send messages, and view chat history — all stored in plain text files.

---

## 📂 Features

- ✅ User registration and login system  
- 👥 Friend list management (add/remove friends)  
- 💌 Messaging between friends  
- 📥 View inbox with chat history  
- 📁 Persistent data storage using files  

---

## 🧱 How It Works

1. **User Registration/Login**
   - Stores credentials in `users.txt`
   - Validates login credentials

2. **Friend Management**
   - Friend list is maintained in a file named `<username>_friends.txt`

3. **Chat System**
   - Messages are saved in `chat_history.txt` with sender/receiver info
   - Users can store up to 50 messages per friend

4. **Inbox**
   - Displays chat history with each friend

---

## 🔧 Setup & Compilation

### Requirements:
- C++ compiler (e.g., g++, Turbo C++)
- Command-line terminal or C++ IDE

### Compile:
bash
```
g++ -o chat_app chat_app.cpp
./chat_app
```

📁 File Structure
| File                     | Description                               |
| ------------------------ | ----------------------------------------- |
| `chat_app.cpp`           | Main source code                          |
| `users.txt`              | Stores registered usernames and passwords |
| `<username>_friends.txt` | Stores the friend list of each user       |
| `chat_history.txt`       | Stores all chat messages between users    |

🔒 Note on Security

This application does not use password encryption or secure protocols. It is intended for learning purposes and should not be used in a real-world deployment without modifications.


🚀 Possible Future Enhancements

- Hashing and encryption for passwords

- Timestamps for each message

- GUI interface using Qt or SFML

- Real-time chat using sockets or networking

- Database integration (e.g., SQLite)




