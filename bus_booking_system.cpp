#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits> 
using namespace std;

double amount = 0.0;
int x, y, bno;
string bn, bt, fileName, date;

template <typename T>
T datedisplay(T d) {
    date = d;
    return d;
}

class intro {
public:
    void getintro() {
        cout << endl << setw(50) << "Welcome" << endl;
        cout.fill('-');
        cout.width(100);
        cout << "\n";
        cout << "\nPlease select your destination\nMumbai\nPune\nBangalore\nHyderabad\nMysuru\n";
    }
    virtual void busInfo() {} // Base class virtual function
} i;

class BusInfo : virtual public intro {
public:
    string name;
    string btime;
    int number;

    void busInfo() {
        cout << "\nThe departure point(source) is set to Panaji.\n\n";
    }

    BusInfo() {}

    BusInfo(const string& busName, const string& busTime, int busNumber)
        : name(busName), btime(busTime), number(busNumber) {}

    void buspass(BusInfo businfo) {
        bn = businfo.name;
        bt = businfo.btime;
        bno = businfo.number;
        cout << endl << "Your selected bus is:" << endl << bn << endl << bt << endl << bno;
    }

    void display() {
        static int i = 1;
        cout << i << "] Bus Name: " << name << "\t\t Dept Time: " << btime << "\t\t Bus Number: " << number << endl;
        i++;
    }
};

class route : virtual public intro {
protected:
    string from;
    string to;

public:
    route() {}
    
    route(const string& a, const string& b = "panaji") {
        from = b;
        to = a;
    }

    void businfo() {
        cout << "\nYour selected route is from " << from << " to " << to << "." << endl;
        cout << endl << "Enter the travel date (DD.MM.YY): ";
        string d;
        cin >> d;
        datedisplay(d);

        cout << "\nAvailable buses are:\n";
        if (to == "Mumbai" || to == "mumbai") amount = 1200;
        else if (to == "Pune" || to == "pune") amount = 900;
        else if (to == "Bangalore" || to == "bangalore") amount = 1000;
        else if (to == "Hyderabad" || to == "hyderabad") amount = 1300;
        else if (to == "Mysuru" || to == "mysuru") amount = 1100;
    }  
};

class passinfo : public route, public BusInfo {
protected:
    char pname[20];
    string gen;
    int age;
    long long contact; 

public:
    passinfo() {}
    passinfo(const string& destination, const string& from = "Panaji") : route(destination, from) {}

    void getpassinfo() {
        static int i = 1;
        cout << endl << "Enter passenger " << i << " details\n";
        cout << "Passenger Name: ";
        cin.getline(pname, 20); 
        cout << "Gender: ";
        cin >> gen;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        cout << "Age: ";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Contact Number: ";
        cin >> contact;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        i++;
    }

    void putpassinfo() {
        static int i = 1;
        cout << "\n\nPassenger " << i << " Name: " << pname << endl;
        cout << setw(8) << left << "Gender: " << gen << "   ";
        cout << setw(5) << "Age: " << age << "   ";
        cout << setw(10) << "Contact Number: " << contact << endl;
        i++;
    }
    
    void putpassinfoinfile() {
        fstream outf(fileName, ios::out | ios::app);
        outf << "Bus Name: " << bn << "   Bus Type: " << bt << "   Bus Number: " << bno;
        outf << "   Date: " << date << endl;
        outf << "\nPassenger Name: " << pname << endl;
        outf << setw(8) << left << "Gender: " << gen << "   ";
        outf << setw(5) << "Age: " << age << "   ";
        outf << setw(10) << "Contact Number: " << contact << endl;
        outf.close();
    }
    friend class ticket;
};

class payment {
private:
    double pamount;

public:
    void setAmount(int a) {
        pamount = amount;
    }

    double setAmount(double a) {
        y = pamount * x;
        return pamount * x;
    }
};

class ticket : public passinfo, public payment {
public:
    ticket(const string& destination, const string& from = "Panaji") : passinfo(destination, from) {}

    void displayTicketdest() {
        cout << endl << "From: " << from;
        cout << setw(42) << setfill(' ') << "To: " << to << endl;
    }
    
    void busdet() {
        cout << endl << bn << setw(20) << setfill(' ') << bt << setw(20) << setfill(' ') << bno << setw(20)
             << setfill(' ') << date;
    }

    void disp() {
        cout << endl << endl << setw(50) << setfill('*') << "Ticket";
        cout << setw(50) << "\n";
    }

    void displayTicketamt() {
        cout << endl << setw(80) << setfill(' ') << right << "Total Amount: " << y << endl;
    }

    void ticketfile() {
        fileName = to + "_ticket.txt";
        ifstream inf(fileName);
        int existingPassengers;
        inf.seekg(0, ios::beg);
        inf >> existingPassengers;
        inf.close();

        existingPassengers += x;

        ofstream outf1(fileName, ios::out | ios::app);
        outf1.seekp(0, ios::beg);
        outf1 << existingPassengers << " passengers\n";
        outf1.close();
    }

    void fileloc() {
        cout << "Ticket information has been saved to " << fileName << endl;
    }
};

int main() {
    int o = 0;
    do {
        i.getintro();
        intro* ptr;
        BusInfo bu;
        ptr = &bu;
        ptr->busInfo();
        string destination;
        bool validDestination = false;

        while (!validDestination) {
            cout << "Type your destination in lowercase (e.g., 'bangalore'): ";
            cin >> destination;

            if (destination == "mumbai" || destination == "pune" || destination == "bangalore" ||
                destination == "hyderabad" || destination == "mysuru") {
                validDestination = true;
            } else {
                cout << "Invalid destination. Please try again." << endl;
            }
        }

        passinfo passengerInfo(destination);
        passinfo passengerInfo1[20];
        passengerInfo.businfo();

        const int maxBuses = 7;
        BusInfo busInfoArray[maxBuses] = {
            BusInfo("Bus 1", "08:00 PM", 5364),
            BusInfo("Bus 2", "09:30 PM", 5423),
            BusInfo("Bus 3", "11:00 PM", 5324),
            BusInfo("Bus 4", "02:30 PM", 5234),
            BusInfo("Bus 5", "04:30 PM", 5343),
            BusInfo("Bus 6", "03:00 PM", 5246),
            BusInfo("Bus 7", "06:00 PM", 5356)
        };

        for (int i = 0; i < maxBuses; ++i) {
            busInfoArray[i].display();
        }

        int choice;
        cout << "\nSelect your desired bus (1-7): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after choice

        int flag = 0;
        while (flag != 1) {
            try {
                switch (choice) {
                    case 1: passengerInfo.buspass(busInfoArray[0]); flag = 1; break;
                    case 2: passengerInfo.buspass(busInfoArray[1]); flag = 1; break;
                    case 3: passengerInfo.buspass(busInfoArray[2]); flag = 1; break;
                    case 4: passengerInfo.buspass(busInfoArray[3]); flag = 1; break;
                    case 5: passengerInfo.buspass(busInfoArray[4]); flag = 1; break;
                    case 6: passengerInfo.buspass(busInfoArray[5]); flag = 1; break;
                    case 7: passengerInfo.buspass(busInfoArray[6]); flag = 1; break;
                    default: throw "Invalid choice. Please enter 1-7: ";
                }
            } catch (const char* msg) {
                cout << msg;
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << endl << "Enter the number of passengers: ";
        cin >> x;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after x

        for (int j = 0; j < x; j++) {
            passengerInfo1[j].getpassinfo();
        }

        payment paymentInfo;
        paymentInfo.setAmount(1); // Set amount per passenger
        paymentInfo.setAmount(1.0); // Calculate total

        ticket passengerTicket(destination);
        passengerTicket.disp();
        passengerTicket.displayTicketdest();
        passengerTicket.busdet();

        for (int j = 0; j < x; j++) {
            passengerInfo1[j].putpassinfo();
        }

        cout.fill('_');
        cout.width(100);
        cout << "\n";
        passengerTicket.displayTicketamt();
        cout.fill('_');
        cout.width(100);
        cout << "\n";

        passengerTicket.ticketfile();
        for (int j = 0; j < x; j++) {
            passengerInfo1[j].putpassinfoinfile();
        }
        passengerTicket.fileloc();

        cout << endl << "Continue booking? (1=Yes, 0=No): ";
        cin >> o;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (o == 0) cout << "Thank you for booking with us!\n";
    } while (o == 1);

    return 0;
}