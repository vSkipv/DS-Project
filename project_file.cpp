#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int x;
/// Client structure
struct Client
{
    int id;
    string name;
    string currency;
    string password;
    double balance;
    double amount;
    Client* next;
    Client* previous;

    Client(int id, string name, string currency, string password, double balance) : id(id),
        name(name),
        currency(currency),
        password(password),
        balance(balance),
        next(nullptr),
        previous(nullptr)
    {
    }
};

/// Priority queue node
struct PQNode
{
    string name;
    int rating;
    PQNode* next;

    PQNode(string name, int rating) : name(name),
        rating(rating),
        next(nullptr)
    {
    }
};

/// Binary search tree node
struct BSTNode
{
    Client* client;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Client* client) : client(client),
        left(nullptr),
        right(nullptr)
    {
    }
};

struct STACK
{

    int data;
    struct STACK* next;
};
struct STACK* top = NULL;

/// Bank class
class Bank
{
private:
    Client* clients_head;
    int num_clients;
    PQNode* ratings_head;
    BSTNode* root;

public:
    Bank()
    {
        clients_head = nullptr;
        ratings_head = nullptr;
        root = nullptr;
        num_clients = 0;
    }
    /// Admin Login
    void
        admin_login()
    {
        int id, ch;
        string password;
        do
        {
            system("cls");
            cout << "\n-------------------------" << endl;
            cout << "   Administration Page" << endl;
            cout << "-------------------------" << endl;
            cout << "\t\t\t                                                          \n\n\n";
            cout << "\t|Press 1 to go to Admin Page                                                |" << endl;
            cout << "\t|Press 2 to Return to the main menu                                         |" << endl;
            cout << "Enter your choice: ";
            cin >> ch;
            system("COLOR F0");
            system("cls");
            switch (ch)
            {
            case 1:
                cout << "\nEnter Admin ID: ";
                cin >> id;
                cout << "Enter password: ";
                cin >> password;

                if (id == 1 && password == "1")
                {
                    admin_menu();
                }
                else
                {
                    cout << "Invalid login.\n"
                        << endl;
                }
            }
        } while (ch == 1);
    }
    void transactions_push(int val)
    {
        struct STACK* newtransactions = new struct STACK;
        newtransactions->data = val;
        newtransactions->next = top;
        top = newtransactions;
    }
    void transactions_pop()
    {
        if (top == NULL)
            cout << "Underflow" << endl;
        else
        {
            cout << "The popped element is " << top->data << endl;
            top = top->next;
        }
    }
    void transactions_display()
    {

        struct STACK* ptr;
        if (top == NULL)
            cout << "stack is empty";
        else
        {
            ptr = top;
            cout << "Stack elements are: ";
            while (ptr != NULL)
            {
                cout << ptr->data << " "
                    << "\n";
                ptr = ptr->next;
            }
        }
    }

    void admin_menu()
    {
        system("cls");
        bool isLoggedIn = true;

        while (isLoggedIn)
        {
            cout << "\n-------------------------" << endl;
            cout << "   Administration Page" << endl;
            cout << "-------------------------" << endl;
            cout << "\n\t1. Add Client" << endl;
            cout << "\t2. Search Client" << endl;
            cout << "\t3. List Clients" << endl;
            cout << "\t4. Edit Client Information" << endl;
            cout << "\t5. Remove Client" << endl;
            cout << "\t6. Display Ratings" << endl;
            cout << "\t7. Logout" << endl;
            cout << "\n\t\tEnter choice: ";
            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                add_client();
                break;
            case 2:
                search_client();
                break;
            case 3:
                list_clients();
                break;
            case 4:
                edit_client_info();
                break;
            case 5:
                remove_client_info();
                break;
            case 6:
                display_ratings();
                break;
            case 7:
                cout << "Logged out." << endl;
                isLoggedIn = false;
                break;
            default: cout
                << "Invalid choice."
                << endl;
                break;
            }
        }
    }

    void add_client()
    {

        int id;
        string name, password, currency;
        double balance;

        cout << " Enter client ID: ";
        cin >> id;
        // Check if client ID already exists
        if (find_client(id) != nullptr)
        {
            cout << "Client with ID " << id << " already exists." << endl;
            return;
        }
        cout << "Enter the client's name: ";
        cin >> name;
        cout << "Enter client's password: ";
        cin >> password;
        cout << "Enter initial client balance: ";
        cin >> balance;
        if (balance > 50000)
        {
            cout << "This Client has VIP account" << endl;
            balance += balance * 10 / 100;
        }
        cout << "Enter currency type(USD/EGP): ";
        cin >> currency;

        bool validCurrency = false;
        for (const string& validCurrencyType : { "USD", "EGP" })
        {
            if (currency == validCurrencyType)
            {
                validCurrency = true;
                break;
            }
        }

        if (!validCurrency)
        {
            cout << "Invalid currency, try again\n";
            return add_client();
        }

        Client* client = new Client(id, name, currency, password, balance);

        // linled list
        // Add the new client to the client list
        if (clients_head == nullptr)
        {
            clients_head = client;
        }
        else
        {
            Client* temp = clients_head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            // Set the next node of the last node to the new client
            temp->next = client;
            client->previous = temp;
        }
        num_clients++;
        system("cls");
        cout << "Client added successfully!\n"
            << endl;

        insertClientBST(client); /// ???????????????
    }

    // tree

    void insertClientBST(Client* client)
    { /// ???
        BSTNode* newNode = new BSTNode(client);
        if (root == nullptr)
        {
            root = newNode;
        }
        else
        {
            BSTNode* current = root;
            while (true)
            {
                if (client->id < current->client->id)
                {
                    if (current->left == nullptr)
                    {
                        current->left = newNode;
                        break;
                    }
                    else
                    {
                        current = current->left;
                    }
                }
                else
                {
                    if (current->right == nullptr)
                    {
                        current->right = newNode;
                        break;
                    }
                    else
                    {
                        current = current->right;
                    }
                }
            }
        }
    }

    void search_client()
    {
        int id;
        cout << "Enter client ID: ";
        cin >> id;

        Client* client = find_client(id);
        if (client == nullptr)
        {
            cout << "Client not found.\n"
                << endl;
        }
        else
        {
            cout << "\n*Client found*" << endl;
            cout << "ID: " << client->id << endl;
            cout << "Name: " << client->name << endl;
            cout << "Balance: " << client->balance << " " << client->currency << endl;
        }
    }

    void list_clients()
    {
        if (num_clients == 0)
        {
            cout << "No clients found.\n"
                << endl;
        }
        else
        {
            cout << "List of clients:" << endl;
            Client* current = clients_head;
            while (current != nullptr)
            {
                cout << "-------------------------" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Balance: " << current->balance << " " << current->currency << endl;
                cout << "-------------------------" << endl;
                current = current->next;
            }
        }
    }

    void edit_client_info()
    {
        int id;
        cout << "Enter client ID: ";
        cin >> id;

        Client* client = find_client(id);
        if (client == nullptr)
        {
            cout << "Client not found." << endl;
        }
        else
        {
            cout << "Enter new client name: ";
            cin >> client->name;
            cout << "Enter new client password: ";
            cin >> client->password;
            cout << "Client information updated!\n"
                << endl;
        }
    }

    void remove_client_info()
    {
        int id;
        cout << "Enter client ID: ";
        cin >> id;

        Client* client = find_client(id);
        if (client == nullptr)
        {
            cout << "Client not found." << endl;
        }
        else
        {
            remove_client_rating(client->name); ///

            // linked list
            //  If the client to be removed is the head of the list
            if (client == clients_head)
            {
                clients_head = client->next;
                if (clients_head != nullptr)
                {
                    clients_head->previous = nullptr;
                }
            }
            else
            {
                // If the client is not the head, update the next and previous pointers of the adjacent nodes
                if (client->previous != nullptr)
                {
                    client->previous->next = client->next;
                }
                if (client->next != nullptr)
                {
                    client->next->previous = client->previous;
                }
            }
            delete client;
            num_clients--;
            cout << "Client removed successfully!\n"
                << endl;
        }
    }

    void remove_client_rating(const string& name)
    {
        // Traverse the ratings list to find the client
        PQNode* current = ratings_head;
        PQNode* previous = nullptr;

        // Search for the client in the ratings list
        while (current != nullptr)
        {
            if (current->name == name)
            {
                // If the node to be removed is the head of the list
                if (current == ratings_head)
                {
                    ratings_head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                delete current;
                break;
            }

            previous = current;
            current = current->next;
        }

        // If the client is not found in the ratings list, display an error message
        if (current == nullptr)
        {
            cout << "Client '" << name << "' does not have a rating." << endl;
        }
    }

    // linked list
    Client* find_client(int id)
    {
        Client* current = clients_head;
        while (current != nullptr)
        {
            if (current->id == id)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Client Login
    void client_login()
    {
        int id;
        string password;
        cout << "Enter client ID: ";
        cin >> id;
        cout << "Enter password: ";
        cin >> password;

        Client* client = find_client(id);
        if (client != nullptr && client->password == password)
        {
            client_menu(client);
        }
        else
        {
            cout << "Invalid client ID or password." << endl;
        }
    }

    void client_menu(Client* client)
    {
        bool isLoggedIn = true;
        while (isLoggedIn)
        {
            cout << "\n-------------------------" << endl;
            cout << "   Clint Page              " << endl;
            cout << "-------------------------" << endl;
            cout << endl;
            cout << "1. Deposit" << endl;
            cout << "2. Withdraw" << endl;
            cout << "3. Loan" << endl;
            cout << "4. Check balance" << endl;
            cout << "5. Transfer money" << endl;
            cout << "6. transection display" << endl;
            cout << "7. Write Feedback" << endl;
            cout << "8. Logout" << endl;
            cout << "Enter choice: ";
            int choice;
            cin >> choice;
system("cls");
            switch (choice)
            {
            case 1:
                deposit(client);
                break;
            case 2:
                withdraw(client);
                break;
            case 3:
                loan(client);
                break;
            case 4:
                check_balance(client);
                break;
            case 5:
                transfer_money(client);
                break;
            case 6:
                transection_display(client);
                break;
            case 7:
                take_feedback(client);
                break;
            case 8:
                cout << "Logged out." << endl;
                isLoggedIn = false;
                system("cls");
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }
        }
    }

    void deposit(Client* client)
    {
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        client->balance += amount;
        if (client->balance > 50000)
        {
            cout << "This Client Have The VIP Card" << endl;
            client->balance += amount * 10 / 100;
            cout << "The 10% Has Been Add successfully!" << endl;
        }

        cout << "Deposit successful. New balance: " << client->balance << endl;
    }

    void withdraw(Client* client)
    {
        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if (amount > client->balance)
        {
            cout << "Insufficient balance." << endl;
        }
        else
        {
            client->balance -= amount;
            cout << "Withdrawal successful. New balance: " << client->balance << endl;
        }
    }
    void loan(Client* client)
    {
        int phone, NationalID, salary;
        string name, Email;
        char loa;
        double amount;
        cout << "Dear client, do you want to get a personal loan? (y/n)" << endl;
        cin >> loa;
        if (loa == 'y')
        {
            if (client->balance >= 50000)
            {
                cout << "Please Submit your application for a personal loan:\n";
                cout << "Name: ";
                cin >> name;
                cout << endl;
                cout << "Mobile Phone Number: ";
                cin >> phone;
                cout << endl;
                cout << "E-mail: ";
                cin >> Email;
                cout << endl;
                cout << "National ID: ";
                cin >> NationalID;
                cout << endl;
                cout << "Please indicate the loan amount you want: ";
                cin >> amount;
                client->amount = amount;
                client->balance += amount;
                cout << "The loan process was completed successfully" << endl;

            }
            else
            {
                cout << "Insufficient balance, Please Try Again..." << endl;
            }
        }
        else
        {
            cout << "Thank you for visiting our site... " << endl;
        }
    }
    void check_balance(Client* client)
    {
        char charYN;
        int choise, eur, kwd, omr, gbp, jpy;
        cout << "YOUR BALANCE IS:" << client->balance << " " << client->currency << endl;
        cout << "\nDo you want to view your balance by other currencies? (y/n)";
        cin >> charYN;
        string user_currency = client->currency;
        if (charYN == 'y')
        {
            cout << "Choose the currency \n";
            cout << "1.EURO (EUR)\n";
            cout << "2.Kuwaiti dinar (KWD) \n";
            cout << "3.Omani rial (OMR)\n";
            cout << "4.Pound Sterling (GBP) \n";
            cout << "5.Japanese Yen (JPY) \n";
            cout << "6.All available currencies \n";

            cin >> choise;
            switch (choise)
            {
            case 1:
                if (user_currency == "USD")
                {
                    eur = client->balance * 0.93;
                    cout << "Your balance by EURO is: " << eur;
                    break;
                }
                else
                {
                    eur = client->balance * 33.27;
                    cout << "Your balance by EURO is " << eur;
                    break;
                }

            case 2:
                if (user_currency == "USD")
                {
                    kwd = client->balance * 0.31;
                    cout << "Your balance in Kuwaiti dinar is: " << kwd;
                    break;
                }
                else
                {
                    kwd = client->balance * 100.60;
                    cout << "Your balance in Kuwaiti dinar is " << kwd;
                    break;
                }

            case 3:
                if (user_currency == "USD")
                {
                    omr = client->balance * 0.39;
                    cout << "Your balance in Omani rial is: " << omr;
                    break;
                }
                else
                {
                    omr = client->balance * 80.25;
                    cout << "Your balance by Omani rial is " << omr;
                    break;
                }

            case 4:
                if (user_currency == "USD")
                {
                    gbp = client->balance * 0.81;
                    cout << "Your balance in Pound Sterling is: " << gbp;
                    break;
                }
                else
                {
                    gbp = client->balance * 0.026;
                    cout << "Your balance by Pound Sterling is " << gbp;
                    break;
                }

            case 5:
                if (user_currency == "USD")
                {
                    jpy = client->balance * 140.62;
                    cout << "Your balance in Japanese Yen is: " << jpy;
                    break;
                }
                else
                {
                    jpy = client->balance * 4.54;
                    cout << "Your balance by Japanese Yen is " << jpy;
                    break;
                }

            case 6:
                if (user_currency == "USD")
                {
                    eur = client->balance * 0.93;
                    cout << "Your balance by EURO is: " << eur << "\n";
                    kwd = client->balance * 0.31;
                    cout << "Your balance in Kuwaiti dinar is: " << kwd << "\n";
                    omr = client->balance * 0.39;
                    cout << "Your balance in Omani rial is: " << omr << "\n";
                    gbp = client->balance * 0.81;
                    cout << "Your balance in Pound Sterling is: " << gbp << "\n";
                    jpy = client->balance * 140.62;
                    cout << "Your balance in Japanese Yen is: " << jpy << "\n";
                    break;
                }
                else
                {
                    eur = client->balance * 33.27;
                    cout << "Your balance by EURO is: " << eur << "/n";
                    kwd = client->balance * 100, 60;
                    cout << "Your balance in Kuwaiti dinar is: " << kwd << "/n";
                    omr = client->balance * 80.25;
                    cout << "Your balance in Omani rial is: " << omr << "/n";
                    gbp = client->balance * 0.026;
                    cout << "Your balance in Pound Sterling is: " << gbp << "/n";
                    jpy = client->balance * 4.54;
                    cout << "Your balance by Japanese Yen is " << jpy << "/n";
                    break;
                }

            default:
                cout << "Wrong choose please try again";
            }
        }

        else if (charYN == 'n')
        {
            cout << "Glad to help you";
        }
        else
        {
            cout << "Wrong choice try again";
        }
    }

    void transection_display(Client* client)
    {
        int id;
        cout << "Enter client ID: ";
        cin >> id;

        Client* Client = find_client(id);
        if (client == nullptr)
        {
            cout << "Client not found.\n"
                << endl;
        }
        else
        {
            cout << "-------------------------" << endl;
            cout << "YOUR BALANCE IS:" << client->balance << " " << client->currency << endl;
            if (client->amount > 0)
            {
                cout << "YOUR LOAN AMOUNT IS:" << client->amount << endl;

            }
            else
            {
                cout << "you haven't request a loan" << endl;

            }
            cout << "-------------------------" << endl;
        }



    }


    void transfer_money(Client* client)
    {
        int receive_id;
        double namount, bamount;

        cout << "Enter recipient ID: ";
        cin >> receive_id;
        Client* recipient = find_client(receive_id);
        if (recipient == nullptr)
        {
            cout << "Invalid recipient ID." << endl;
            return;
        }

        cout << "Enter amount to transfer: ";
        cin >> bamount;
        if (bamount > client->balance)
        {
            cout << "Not enough balance" << endl;
            return;
        }

        string user_currency = client->currency;
        string recipient_currency = recipient->currency;

        if (user_currency != recipient_currency)
        {
            double conversion_rate = 1;
            if (user_currency == "USD")
            {
                conversion_rate = 31.90;
            }
            else if (recipient_currency == "USD")
            {
                conversion_rate = 1 / 31.90;
            }

            namount = bamount * conversion_rate;
            client->balance -= bamount;
            recipient->balance += namount;
        }

        else
        {
            client->balance -= bamount;
            recipient->balance += bamount;
        }
        cout << "Transfer successful!\nCurrent balance: " << client->balance << " " << client->currency << endl;
    }

    // Function to take client feedback and rating
    void take_feedback(Client* client)
    {
        string feedback;
        int rating;

        cout << "Enter your feedback: ";
        cin.ignore(); //?????????????????????????????????????
        getline(cin, feedback);

        cout << "Rate your experience (out of 10): ";
        cin >> rating;

        // Store the feedback and rating in a file
        ofstream file("feedback.txt", ios::app);
        file << "Client ID: " << client->id << endl;
        file << "Name: " << client->name << endl;
        file << "Feedback: " << feedback << endl;
        file << "Rating: " << rating << endl;
        file << "--------------------------" << endl;
        file.close();

        if (rating < 10)
        {
            insert_rating(client->name, rating);
        }
    }

    // Priority queue
    void insert_rating(string name, int rating)
    {
        PQNode* newRating = new PQNode(name, rating);
        if (ratings_head == nullptr || rating < ratings_head->rating)
        {
            newRating->next = ratings_head;
            ratings_head = newRating;
        }
        else
        {
            PQNode* current = ratings_head;
            while (current->next != nullptr && current->next->rating <= rating)
            {
                current = current->next;
            }
            newRating->next = current->next;
            current->next = newRating;
        }
    }

    // Function to display ratings with ascending order from the queue
    // bigger to smaller
    void display_ratings()
    {
        if (ratings_head == nullptr)
        {
            cout << "No ratings available." << endl;
        }
        else
        {
            cout << "Ratings with ascending order:" << endl;
            PQNode* current = ratings_head;
            while (current != nullptr)
            {
                cout << "-------------------------" << endl;
                cout << "Name: " << current->name << endl;
                cout << "Rating: " << current->rating << endl;
                cout << "-------------------------" << endl;
                current = current->next;
            }
        }
    }
};

int main()
{
    Bank bank;
    int ch;
    cout << "\t\t\t\t\t\t_____________________________________________________________\n\n\n";
    cout << "\t\t\t\t\t\t               Welcome to the Banking Management System         \n\n\n";
    system("COLOR F0");
    do
    {
        cout << "\t\t\t\t\t\t______________________     MAIN MENU    _____________________\n\n\n";
        cout << "\t\t\t\t\t\t\t                                                  \n\n\n";
        cout << "\t\t\t\t\t\t|   1 to LOGIN ADMIN MODE                                       |" << endl;
        cout << "\t\t\t\t\t\t|   2 to Client Login MODE                                      |" << endl;
        cout << "\t\t\t\t\t\t|   3 to EXIT                                                   |" << endl;
        cout << "\n\t\t\t\t\t\t\t\t Please enter your choice : ";
        cin >> ch;
        system("cls");
        cout << endl;
        system("COLOR F0");
        switch (ch)
        {
        case 1:
            bank.admin_login();
            break;
        case 2:
            bank.client_login();
            break;
        default:
            exit(0);
        }
    } while (ch < 3);

    return 0;
}
