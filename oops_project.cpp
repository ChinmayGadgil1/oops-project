#include <bits/stdc++.h>
using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

map<int, string> cities = {
    {1, "Valpoi"}, {2, "Panaji"}, {3, "Mhapsa"}, {4, "Margao"}, {5, "Bicholim"}, {6, "Ponda"}, {7, "Pernem"}, {8, "Vasco"}, {9, "Canacona"}, {10, "Sanguem"}, {11, "Dharbandoda"}, {12, "Quepem"}};

map<pair<int, int>, int> distances = {

    {{1, 2}, 37}, {{1, 3}, 30}, {{1, 4}, 63}, {{1, 5}, 23}, {{1, 6}, 38}, {{1, 7}, 38}, {{1, 8}, 50}, {{1, 9}, 90}, {{1, 10}, 78}, {{1, 11}, 50}, {{1, 12}, 65},

    {{2, 3}, 13},
    {{2, 4}, 33},
    {{2, 5}, 25},
    {{2, 6}, 28},
    {{2, 7}, 27},
    {{2, 8}, 30},
    {{2, 9}, 70},
    {{2, 10}, 65},
    {{2, 11}, 45},
    {{2, 12}, 60},

    {{3, 4}, 45},
    {{3, 5}, 20},
    {{3, 6}, 35},
    {{3, 7}, 21},
    {{3, 8}, 45},
    {{3, 9}, 75},
    {{3, 10}, 60},
    {{3, 11}, 55},
    {{3, 12}, 70},

    {{4, 5}, 50},
    {{4, 6}, 20},
    {{4, 7}, 60},
    {{4, 8}, 28},
    {{4, 9}, 35},
    {{4, 10}, 45},
    {{4, 11}, 38},
    {{4, 12}, 18},

    {{5, 6}, 30},
    {{5, 7}, 25},
    {{5, 8}, 45},
    {{5, 9}, 85},
    {{5, 10}, 65},
    {{5, 11}, 43},
    {{5, 12}, 58},

    {{6, 7}, 45},
    {{6, 8}, 35},
    {{6, 9}, 60},
    {{6, 10}, 50},
    {{6, 11}, 40},
    {{6, 12}, 35},

    {{7, 8}, 50},
    {{7, 9}, 85},
    {{7, 10}, 75},
    {{7, 11}, 65},
    {{7, 12}, 80},

    {{8, 9}, 55},
    {{8, 10}, 45},
    {{8, 11}, 40},
    {{8, 12}, 50},

    {{9, 10}, 35},
    {{9, 11}, 45},
    {{9, 12}, 30},

    {{10, 11}, 25},
    {{10, 12}, 20},

    {{11, 12}, 40}};

void printCities()
{
    for (auto i : cities)
    {
        cout << MAGENTA << i.first << ". " << i.second << "\n";
    }
    cout << RESET;
}

void showSpinner(int duration)
{
    const char spinner[] = {'|', '/', '-', '\\'};
    int spinnerIndex = 0;
    auto start = chrono::high_resolution_clock::now();
    while (chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start).count() < duration)
    {
        cout << "\r" << spinner[spinnerIndex++] << flush;
        spinnerIndex %= 4;
    }
    cout << "\r" << " " << "\r";
}

int getLastTicketNumber()
{
    ifstream inFile("lastTicketNumber.dat", ios::binary);
    int lastTicketNumber = 0;

    if (inFile.is_open())
    {
        inFile.read(reinterpret_cast<char *>(&lastTicketNumber), sizeof(lastTicketNumber));
        inFile.close();
    }

    return lastTicketNumber;
}

void updateLastTicketNumber(int newTicketNumber)
{
    ofstream outFile("lastTicketNumber.dat", ios::binary);
    if (outFile.is_open())
    {
        outFile.write(reinterpret_cast<const char *>(&newTicketNumber), sizeof(newTicketNumber));
        outFile.close();
    }
}

class Ticket
{
private:
    string cname;
    int tno;
    int start;
    int destination;
    string filename;
    int distance;

public:
    Ticket() : tno(0) {}

    void createTicket()
    {
        cin.ignore();
        cout << YELLOW << "Enter customer name: " << RESET;
        getline(cin, cname);

        int lastTicketNumber = getLastTicketNumber();
        tno = lastTicketNumber + 1;
        updateLastTicketNumber(tno);

        cout << YELLOW << "Generated Ticket Number: " << tno << RESET << endl;

        cout << YELLOW << "Enter start location:\n"
             << RESET;
        printCities();
        cout << YELLOW << "Your choice=> " << RESET;
        cin >> start;

        cout << YELLOW << "Enter destination location:\n"
             << RESET;
        printCities();
        cout << YELLOW << "Your choice=> " << RESET;
        cin >> destination;

        distance = distances[{start, destination}];

        showSpinner(1);

        filename = to_string(tno) + ".txt";

        ifstream existingFile(filename);
        if (existingFile.is_open())
        {
            cout << RED << "\nTicket with this number already exists." << RESET << endl;
            existingFile.close();
            return;
        }

        ofstream ticketFile(filename);
        if (ticketFile.is_open())
        {
            ticketFile << "------------------------------------------\n";
            ticketFile << "|                 TICKET                 |\n";
            ticketFile << "------------------------------------------\n";
            time_t now = time(0);
            tm *ltm = localtime(&now);
            char date[11];
            char time[9];

            strftime(date, sizeof(date), "%d/%m/%Y", ltm);
            strftime(time, sizeof(time), "%H:%M:%S", ltm);

            ticketFile << "| Date: " << date;
            ticketFile << "        Time: " << time << " |\n";
            ticketFile << "| Customer Name: " << cname;
            for (int i = cname.length(); i < 24; i++)
            {
                ticketFile << " ";
            }
            ticketFile << "|\n";

            ticketFile << "| Ticket Number: " << tno;
            for (int i = to_string(tno).length(); i < 24; i++)
            {
                ticketFile << " ";
            }
            ticketFile << "|\n";
            ticketFile << "| Start: " << cities[start];
            for (int i = cities[start].length(); i < 32; i++)
            {
                ticketFile << " ";
            }
            ticketFile << "|\n";
            ticketFile << "| Destination: " << cities[destination];
            for (int i = cities[destination].length(); i < 26; i++)
            {
                ticketFile << " ";
            }
            ticketFile << "|\n";
            ticketFile << "| Distance: " << distance << "km";
            for (int i = to_string(distance).length(); i < 27; i++)
            {
                ticketFile << " ";
            }
            ticketFile << "|\n";
            ticketFile << "| Price: " << setw(3) << distance * 2 << "Rs";
            for (int i = to_string(distance).length(); i < 29; i++)
            {
                ticketFile << " ";
            }
            ticketFile << "|\n";
            ticketFile << "------------------------------------------\n";
            ticketFile.close();
            cout << GREEN << "\nTicket created successfully!" << RESET << endl;
        }
        else
        {
            cout << RED << "\nUnable to open file" << RESET << endl;
        }
    }

    void editTicket()
    {
        int newTno;
        cout << YELLOW << "Enter the new ticket number: " << RESET;
        cin >> newTno;
        showSpinner(2);
        string newFilename = to_string(newTno) + ".txt";

        ifstream ticketFileIn(filename);
        string content;

        if (ticketFileIn.is_open())
        {
            string line;
            int count = 1;
            while (getline(ticketFileIn, line))
            {
                if (count == 6)
                {
                    content += "| Ticket Number: " + to_string(newTno);
                    for (int i = to_string(newTno).length(); i < 24; i++)
                    {
                        content += " ";
                    }
                    content += "|\n";
                    count++;
                    continue;
                }
                content += line + "\n";
                count++;
            }
            ticketFileIn.close();
        }
        else
        {
            cout << RED << "Unable to open file" << RESET << endl;
            return;
        }

        if (rename(filename.c_str(), newFilename.c_str()) == 0)
        {
            ofstream ticketFileOut(newFilename);
            if (ticketFileOut.is_open())
            {
                ticketFileOut << content;
                ticketFileOut.close();
                tno = newTno;
                filename = newFilename;
                cout << GREEN << "Ticket number updated successfully!" << RESET << endl;
            }
            else
            {
                cout << RED << "Unable to open new file" << RESET << endl;
            }
        }
        else
        {
            cout << RED << "Error updating ticket number" << RESET << endl;
        }
    }

    int getTicketNumber()
    {
        return tno;
    }

    void setTicketNumber(int ticketNumber)
    {
        tno = ticketNumber;
        filename = to_string(tno) + ".txt";
    }
};

int main()
{
    int choice;

    while (true)
    {
        showSpinner(1);
        cout << RED << "\nMenu:" << endl;
        cout << BLUE << "1. Enter ticket details" << endl;
        cout << "2. Edit ticket number" << endl;
        cout << "3. Display ticket" << endl;
        cout << "4. Exit" << endl;
        cout << MAGENTA << "Your choice=> " << RESET;
        cin >> choice;

        if (choice == 1)
        {
            Ticket ticket;
            ticket.createTicket();
        }
        else if (choice == 2)
        {
            cout << YELLOW << "Enter the ticket number you want to edit: " << RESET;
            int ticketNumber;
            cin >> ticketNumber;
            string filename = to_string(ticketNumber) + ".txt";
            ifstream ticketFile(filename);
            if (ticketFile.is_open())
            {
                ticketFile.close();
                Ticket ticket;
                ticket.setTicketNumber(ticketNumber);
                ticket.editTicket();
            }
            else
            {
                cout << RED << "Ticket not found" << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            cout << YELLOW << "Enter the ticket number you want to display: " << RESET;
            int ticketNumber;
            cin >> ticketNumber;
            string filename = to_string(ticketNumber) + ".txt";
            ifstream ticketFile(filename);
            if (ticketFile.is_open())
            {
                string line;
                vector<string> colors = {RED, GREEN, BLUE, MAGENTA, CYAN};
                srand(time(0));
                string color = colors[rand() % colors.size()];
                while (getline(ticketFile, line))
                {
                    cout << color << line << endl;
                }
                cout << RESET;
                ticketFile.close();
            }
            else
            {
                cout << RED << "Ticket not found" << RESET << endl;
            }
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << RED << "Invalid choice. Please try again ." << RESET << endl;
        }
    }
    cout << RESET;

    return 0;
}
