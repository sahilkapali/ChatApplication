#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Constants for limits
#define MAX_FRIENDS 100
#define MAX_MESSAGES 50
#define MAX_USERS 100

// Function declarations
void page1();
void page2(string);

// Global arrays to store user credentials
string usernames[MAX_USERS];
string passwords[MAX_USERS];
int userCount = 0;  // Track the number of registered users

// Load user data from file
void loadUsersFromFile()
{
    ifstream userFile("users.txt");
    if (userFile.is_open())
    {
        while (userFile >> usernames[userCount] >> passwords[userCount])
        {
            userCount++;
        }
        userFile.close();
    }
}

// Save user data to file
void saveUsersToFile()
{
    ofstream userFile("users.txt");
    if (userFile.is_open())
    {
        for (int i = 0; i < userCount; i++)
        {
            userFile << usernames[i] << " " << passwords[i] << endl;
        }
        userFile.close();
    }
}

// Class representing a friend with functionalities for managing friends and chats
class frnd
{
    string flist[MAX_FRIENDS];  // Array to store friends
    int flistCount = 0;  // Counter for the number of friends

    struct chat
    {
        int message_id;              // Unique ID for each message
        string sender, receiver;     // Sender and receiver of the message
        char mess[MAX_MESSAGES][100];// Array to store up to 50 messages of 100 characters each
        int num_of_message = 0;      // Counter for the number of messages
    };

public:
    chat sms[MAX_FRIENDS];  // Array to store chats, one for each friend

    void addfrnd(string);   // Function to add a friend
    void unfrnd(string);    // Function to remove a friend
    void dispfrnd(string);  // Function to display the friend list
    void chat_on(string, string, char*);  // Function to send a message
    void inbox(string);     // Function to display the inbox
    void saveChatToFile(string, string, char*);  // Function to save chat to a file
    void loadChatFromFile(string, string);       // Function to load chat from a file
    void saveFriendsToFile(string); // Save friend list to a file
    void loadFriendsFromFile(string); // Load friend list from a file
};

// Save friend list to file
void frnd::saveFriendsToFile(string uname)
{
    ofstream friendFile(uname + "_friends.txt");
    if (friendFile.is_open())
    {
        for (int i = 0; i < flistCount; i++)
        {
            friendFile << flist[i] << endl;
        }
        friendFile.close();
    }
    else
    {
        cout << "\nUnable to open file for saving friends.\n";
    }
}

// Load friend list from file
void frnd::loadFriendsFromFile(string uname)
{
    ifstream friendFile(uname + "_friends.txt");
    if (friendFile.is_open())
    {
        while (getline(friendFile, flist[flistCount]))
        {
            sms[flistCount].message_id = flistCount + 1; // Assign message ID
            flistCount++;
        }
        friendFile.close();
    }
    else
    {
        cout << "\nUnable to open file for loading friends.\n";
    }
}

// Function to save chat to a file
void frnd::saveChatToFile(string sender, string reciever, char *message)
{
    ofstream outFile("chat_history.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << sender << " -> " << reciever << ": " << message << endl;
        outFile.close();
    }
    else
    {
        cout << "\nUnable to open file for writing.\n";
    }
}

// Function to load chat from file
void frnd::loadChatFromFile(string user1, string user2)
{
    ifstream inFile("chat_history.txt");
    string line;
    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            if (line.find(user1 + " -> " + user2) != string::npos ||
                line.find(user2 + " -> " + user1) != string::npos)
            {
                cout << line << endl;
            }
        }
        inFile.close();
    }
    else
    {
        cout << "\nUnable to open file for reading.\n";
    }
}

// Function to handle the chat and save the message to the file
void frnd::chat_on(string uname, string reciepient, char *message)
{
    int flag = 0;
    int friendIndex = -1;

    // Find the friend index
    for (int i = 0; i < flistCount; i++)
    {
        if (flist[i] == reciepient)
        {
            friendIndex = i;
            flag = 1;
            break;
        }
    }

    if (friendIndex == -1)
    {
        cout << "\nSorry!! No user found\a\a\n";
        page2(uname);
        return;
    }

    // Check if there is space for a new message
    if (sms[friendIndex].num_of_message < MAX_MESSAGES)
    {
        sms[friendIndex].sender = uname;
        sms[friendIndex].receiver = reciepient;
        strcpy(sms[friendIndex].mess[sms[friendIndex].num_of_message], message);
    //sms[friendIndex].mess[sms[friendIndex].num_of_message] points to the location in the array where the new message will be stored.
     // This is based on the current count of messages (num_of_message).
        sms[friendIndex].num_of_message++;
        saveChatToFile(uname, reciepient, message);  // Save the message to file
    }
    else
    {
        cout << "\nMessage limit reached!!\n";
    }
}

// Function to display the inbox by loading chat history from file
void frnd::inbox(string uname)
{
    for (int i = 0; i < flistCount; i++)
    {
        loadChatFromFile(uname, flist[i]);  // Load chat history from file
    }
}

// Function to add a friend to the user's friend list
void frnd::addfrnd(string uname)
{
    if (flistCount < MAX_FRIENDS)
    {
        cout << "\nEnter friend's name: ";
        cin >> flist[flistCount];
        sms[flistCount].message_id = flistCount + 1;  // Assign a message ID based on the list index
        flistCount++;
        saveFriendsToFile(uname); // Save the updated friend list
        cout << "\nFriend added!\n";
    }
    else
    {
        cout << "\nFriend list is full!\n";
    }
}

// Function to remove a friend from the user's friend list
void frnd::unfrnd(string uname)
{
    string fname;
    cout << "\nEnter friend's name to remove: ";
    cin >> fname;
    for (int i = 0; i < flistCount; i++)
    {
        if (flist[i] == fname)
        {
            // Shift friends down in the array to fill the gap
            for (int j = i; j < flistCount - 1; j++)
            {
                flist[j] = flist[j + 1];
                sms[j] = sms[j + 1];
            }
            flistCount--;
            saveFriendsToFile(uname); // Save the updated friend list
            cout << "\nFriend removed!\n";
            return;
        }
    }
    cout << "\nFriend not found!\n";
}

// Function to display the user's friend list
void frnd::dispfrnd(string uname)
{
    cout << "\nFriend list:\n";
    for (int i = 0; i < flistCount; i++)
    {
        cout << flist[i] << endl;  // Display each friend's name
    }
}

// Function to display the first page (login, register, exit)
void page1()
{
    cout << "\nWelcome to the Chat Application!\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
}

// Function to display the user's options after logging in
void page2(string uname)
{
    frnd f;
    f.loadFriendsFromFile(uname);  // Load the user's friend list from the file

    int choice;
    do
    {
        cout << "\nWelcome " << uname << "!\n";
        cout << "1. Add Friend\n";
        cout << "2. Remove Friend\n";
        cout << "3. Display Friends\n";
        cout << "4. Chat\n";
        cout << "5. View Inbox\n";
        cout << "6. Logout\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: f.addfrnd(uname); break;   // Add a friend
            case 2: f.unfrnd(uname); break;    // Remove a friend
            case 3: f.dispfrnd(uname); break;  // Display friend list
            case 4:
            {
                string reciepient;
                char message[100];
                cout << "\nEnter friend's name: ";
                cin >> reciepient;
                cout << "\nEnter your message: ";
                cin.ignore();
                cin.getline(message, 100);
                f.chat_on(uname, reciepient, message);  // Send a message
                break;
            }
            case 5: f.inbox(uname); break;  // View inbox
            case 6: cout << "\nLogging out...\n"; break;  // Logout
            default: cout << "\nInvalid choice!\n";
        }
    } while(choice != 6);
}

// Function to register a new user
void registerUser(string uname, string pass)
{
    if (userCount < MAX_USERS)
    {
        usernames[userCount] = uname;
        passwords[userCount] = pass;
        userCount++;
        saveUsersToFile();  // Save the updated user list to the file
        cout << "\nUser registered successfully!\n";
    }
    else
    {
        cout << "\nUser registration limit reached!\n";
    }
}

// Function to check if a user exists and password matches
bool loginUser(string uname, string pass)
{
    for (int i = 0; i < userCount; i++)
    {
        if (usernames[i] == uname && passwords[i] == pass)
        {
            return true;
        }
    }
    return false;
}

// Main function to handle user registration, login, and exit
int main()
{
    loadUsersFromFile();  // Load users from the file at the start

    string uname, pass;
    int choice;

    do
    {
        page1();
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                cout << "\nEnter username: ";
                cin >> uname;
                cout << "\nEnter password: ";
                cin >> pass;

                if (loginUser(uname, pass))
                {
                    page2(uname);  // Go to user options page
                }
                else
                {
                    cout << "\nInvalid credentials!\n";
                }
                break;
            }
            case 2:
            {
                cout << "\nEnter username: ";
                cin >> uname;
                cout << "\nEnter password: ";
                cin >> pass;

                registerUser(uname, pass);  // Register a new user
                break;
            }
            case 3: cout << "\nExiting...\n"; break;  // Exit the application
            default: cout << "\nInvalid choice!\n";
        }
    } while(choice != 3);

    return 0;
}

