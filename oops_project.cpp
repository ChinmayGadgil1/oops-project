// The MIT License (MIT)

// Copyright (c) 2024 Chinmay Girish Gadgil

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

//  This is a simple ticket booking system that allows the user to create, edit, append price to, and display tickets.

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
    {1, "Valpoi"}, {2, "Panaji"}, {3, "Mhapsa"}, {4, "Margao"}, {5, "Bicholim"},
    {6, "Ponda"}, {7, "Pernem"}, {8, "Vasco"}, {9, "Canacona"}, {10, "Sanguem"},
    {11, "Dharbandoda"}, {12, "Quepem"}
};

map<pair<int, int>, int> distances = {
    // Distances from Valpoi (1)
    {{1, 2}, 37}, {{1, 3}, 30}, {{1, 4}, 63}, {{1, 5}, 23}, {{1, 6}, 38},
    {{1, 7}, 38}, {{1, 8}, 50}, {{1, 9}, 90}, {{1, 10}, 78}, {{1, 11}, 50}, {{1, 12}, 65},

    // Distances from Panaji (2)
    {{2, 3}, 13}, {{2, 4}, 33}, {{2, 5}, 25}, {{2, 6}, 28}, {{2, 7}, 27},
    {{2, 8}, 30}, {{2, 9}, 70}, {{2, 10}, 65}, {{2, 11}, 45}, {{2, 12}, 60},

    // Distances from Mhapsa (3)
    {{3, 4}, 45}, {{3, 5}, 20}, {{3, 6}, 35}, {{3, 7}, 21}, {{3, 8}, 45},
    {{3, 9}, 75}, {{3, 10}, 60}, {{3, 11}, 55}, {{3, 12}, 70},

    // Distances from Margao (4)
    {{4, 5}, 50}, {{4, 6}, 20}, {{4, 7}, 60}, {{4, 8}, 28}, {{4, 9}, 35},
    {{4, 10}, 45}, {{4, 11}, 38}, {{4, 12}, 18},

    // Distances from Bicholim (5)
    {{5, 6}, 30}, {{5, 7}, 25}, {{5, 8}, 45}, {{5, 9}, 85}, {{5, 10}, 65},
    {{5, 11}, 43}, {{5, 12}, 58},

    // Distances from Ponda (6)
    {{6, 7}, 45}, {{6, 8}, 35}, {{6, 9}, 60}, {{6, 10}, 50}, {{6, 11}, 40}, {{6, 12}, 35},

    // Distances from Pernem (7)
    {{7, 8}, 50}, {{7, 9}, 85}, {{7, 10}, 75}, {{7, 11}, 65}, {{7, 12}, 80},

    // Distances from Vasco (8)
    {{8, 9}, 55}, {{8, 10}, 45}, {{8, 11}, 40}, {{8, 12}, 50},

    // Distances from Canacona (9)
    {{9, 10}, 35}, {{9, 11}, 45}, {{9, 12}, 30},

    // Distances from Sanguem (10)
    {{10, 11}, 25}, {{10, 12}, 20},

    // Distances from Dharbandoda (11)
    {{11, 12}, 40}
};

void printCities(){
    for (auto i: cities)
    {
        cout<<MAGENTA<<i.first<<". "<<i.second<<"\n";
    }
    cout<<RESET;
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
    cout << "\r" << " " << "\r"; // Clear the spinner
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
        cout << "Enter customer name: ";
        getline(cin, cname);

        cout << "Enter ticket number: ";
        cin >> tno;

        cout<<"Enter start location:\n";
        printCities();
        cin>>start;

        cout<<"Enter destination location:\n";
        printCities();
        cin>>destination;

        distance = distances[{start, destination}];
        
        showSpinner(2);

        filename = to_string(tno) + ".txt";

        ifstream existingFile(filename);
        if (existingFile.is_open())
        {
            cout << "\nTicket with this number already exists." << endl;
            existingFile.close();
            return;
        }

        ofstream ticketFile(filename);
        if (ticketFile.is_open())
        {
            ticketFile << "------------------------------------------\n";
            ticketFile << "|                  TICKET                |\n";
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
            ticketFile << "| Distance: " << distance<<"km";
            for (int i = to_string(distance).length(); i < 27; i++)
            {
                ticketFile << " ";
            }
            ticketFile<<"|\n";
            ticketFile<< "| Price: "<<"₹"<<setw(3)<<distance*2;
            for (int i = to_string(distance).length(); i < 30; i++)
            {
                ticketFile<<" ";
            }
            ticketFile << "|\n";
            ticketFile << "------------------------------------------\n";
            ticketFile.close();
            cout << "\nTicket created successfully!" << endl;
        }
        else
        {
            cout << "\nUnable to open file" << endl;
        }
    }

    void editTicket()
    {
        int newTno;
        cout << "Enter the new ticket number: ";
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
                        content+=" ";
                    }
                    content+="|\n";
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
            cout << "Unable to open file" << endl;
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
                cout << "Ticket number updated successfully!" << endl;
            }
            else
            {
                cout << "Unable to open new file" << endl;
            }
        }
        else
        {
            cout << "Error updating ticket number" << endl;
        }
    }

    void displayTicket() const
    {
        ifstream ticketFile(filename);
        string line;

        if (ticketFile.is_open())
        {
            while (getline(ticketFile, line))
            {
                cout << CYAN << line << endl;
            }
            ticketFile.close();
        }
        else
        {
            cout << "Unable to open file" << endl;
        }
    }

    int getTicketNumber() const
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
    vector<Ticket> tickets;

    while (true)
    {
        showSpinner(1);
        cout << "\nMenu:" << endl;
        cout << "1. Enter ticket details" << endl;
        cout << "2. Edit ticket number" << endl;
        cout << "3. Display ticket" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Ticket ticket;
            ticket.createTicket();
            tickets.push_back(ticket);
        }
        else if (choice == 2)
        {
            cout << "Enter the ticket number you want to edit: ";
            int ticketNumber;
            bool found = false;
            cin >> ticketNumber;
            for (auto &i : tickets)
            {
                if (i.getTicketNumber() == ticketNumber)
                {
                    i.editTicket();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Ticket not found" << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Enter the ticket number you want to display: ";
            int ticketNumber;
            cin >> ticketNumber;
            string filename = to_string(ticketNumber) + ".txt";
            ifstream ticketFile(filename);
            if (ticketFile.is_open())
            {
                string line;
                vector<string> colors = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};
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
                cout << "Ticket not found" << endl;
            }
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again ." << endl;
        }
    }

    return 0;
}
