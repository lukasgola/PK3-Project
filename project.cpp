#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <memory>


using namespace std;
class Calendar{

    int day;
    int month;
    int year;
public:
    Calendar(int y): year(y){}

};

class Time{

    int hours;
    int minutes;

public:
    Time(int h, int m): hours(h), minutes(m){};

    int getHours(){
        return hours;
    }

    int getMinutes(){
        return minutes;
    }

};
// Node class to represent
// a node of the linked list.
class Node {
public:

	int id;
    int day;
    int month;
    int year;

    Time start;
    Time end;
    string title;

    static int count;

    shared_ptr <Node> next;
	//Node* next;

	// Parameterised Constructor
    Node(int d, int m, int y, Time s, Time e, string t): 
    id(count+1), day(d), month(m), year(y), start(s), end(e), title(t){
        count ++;
        this->next = nullptr;
    };

    int getId(){
        return id;
    }

    int getDay(){
        return day;
    }
    int getMonth(){
        return month;
    }
    int getYear(){
        return year;
    }

    Time getTime(){
        return start;
    }

    string getTitle(){
        return title;
    }

    void showEvent(){
        cout << "    [" << this->id << "]  ";
        cout << this->start.getHours() << ":" << this->start.getMinutes();
        cout << " - " << this->end.getHours() << ":" << this->end.getMinutes();
        cout << " " << title << endl;
    }
};

// Linked list class to
// implement a linked list.
class Linkedlist {

	Linkedlist() { head = nullptr; }
    shared_ptr <Node> head;
	//Node* head;

	static Linkedlist *s_Instance;

public:
	Linkedlist(const Linkedlist&) = delete;
	static Linkedlist *Get(){
		return s_Instance;
	}
	// Default constructor
	//Linkedlist() { head = NULL; }

	// Function to insert a
	// node at the end of the
	// linked list.
	void insertNode(int, int, int, int, int, string);

	// Function to print the
	// linked list.
	void printList(int, int, int);

	// Function to delete the
	// node at given position
	void deleteNode(int);


	shared_ptr<Node> getNode(int);

	int getLenght();

};

// Function to delete the
// node at given position
void Linkedlist::deleteNode(int id)
{
    int nodeOffset = 1;
    for(int i=1;i<this->getLenght();i++){
        cout << this->getNode(i)->getId() << this ->getNode(i)->getTitle() << endl;
        if(id == this->getNode(i)->getId()){
            nodeOffset = i+1;
        }
    }


    shared_ptr<Node> temp1 = head;
    shared_ptr<Node> temp2 = nullptr;
	//Node *temp1 = head, *temp2 = NULL;
	int ListLen = 0;

	if (head == nullptr) {
		cout << "List empty." << endl;
		return;
	}

	// Find length of the linked-list.
	while (temp1 != nullptr) {
		temp1 = temp1->next;
		ListLen++;
	}

	// Check if the position to be
	// deleted is greater than the length
	// of the linked list.
	if (ListLen < nodeOffset) {
		cout << "Index out of range"
			<< endl;
		return;
	}

	// Declare temp1
	temp1 = head;

	// Deleting the head.
	if (nodeOffset == 1) {

		// Update head
		head = head->next;
		return;
	}

	// Traverse the list to
	// find the node to be deleted.
	while (nodeOffset-- > 1) {

		// Update temp2
		temp2 = temp1;

		// Update temp1
		temp1 = temp1->next;
	}

	// Change the next pointer
	// of the previous node.
	temp2->next = temp1->next;

}


// Function to insert a new node.
void Linkedlist::insertNode(int chosen_day, int month, int year, int s_h, int s_m, string t)
{
	// Create the new Node.
	//Node* newNode = new Node(data);
    Time t1(s_h,s_m);
    Time t2(s_h+1,s_m);

	shared_ptr<Node> newNode(new Node (chosen_day, month, year, t1, t2, t));

	// Assign to head
	if (head == nullptr) {
		head = newNode;
		return;
	}

	// Traverse till end of list
	//Node* temp = head;
	shared_ptr<Node> temp = head;
	while (temp->next != nullptr) {

		// Update temp
		temp = temp->next;
	}

	// Insert at the last.
	temp->next = newNode;

}

// Function to print the
// nodes of the linked list.
void Linkedlist::printList(int d, int m, int y)
{

    for(int i=0;i<this->getLenght();i++){
        if(d == this->getNode(i)->getDay() && m == this->getNode(i)->getMonth() && y == this->getNode(i)->getYear()){
            this->getNode(i)->showEvent();
        }  
    }

	shared_ptr<Node> temp = head;
	//Node* temp = head;

	// Check for empty list.
	if (head == nullptr) {
		return;
	}
    /*
	// Traverse the list.
	while (temp != NULL) {
		temp->showEvent();
		temp = temp->next;
	}
    */
}

shared_ptr<Node> Linkedlist::getNode(int nodeOffset)
{
	shared_ptr<Node> temp = head;
	//Node* temp = head;
	int ListLen = 0;

	// Find length of the linked-list.
	while (temp != nullptr) {
		temp = temp->next;
		ListLen++;
	}

	temp = head;

	for(int i=0;i<nodeOffset;i++){
		temp = temp->next;
	}

	return temp;
}

int Linkedlist::getLenght(){
    shared_ptr<Node> temp1 = head;
	//Node *temp1 = head, *temp2 = NULL;
	int ListLen = 0;

	if (head == nullptr) {
		cout << "List empty." << endl;
		return ListLen;
	}

	// Find length of the linked-list.
	while (temp1 != nullptr) {
		temp1 = temp1->next;
		ListLen++;
	}

	return ListLen;
}




int Node::count = 0;

class Month{

    int days;
    int month;
    int year;

    int chosen_day;

    Linkedlist *events;

public:

    Month(int d, int m, int y):chosen_day(d), month(m), year(y){
        days = this->numberOfDays();
        events = Linkedlist::Get();
        getEvents();
    }

    int getDays(){
        return days;
    }

    void setDays(){
        days=this->numberOfDays();
    }

    

    int dayNumber(int day, int year)
    {

        static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
                        4, 6, 2, 4 };
        year -= month < 3;
        return ( year + year/4 - year/100 +
                year/400 + t[month-1] + day) % 7;
    }

    int numberOfDays ()
    {
        int tab[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


        if (month == 2)
        {
            if (year % 400 == 0 ||
                    (year % 4 == 0 && year % 100 != 0))
                return (29);
            else
                return (28);
        }
        else{
            return tab[month-1];
        }
    }

    string getMonthName(int monthNumber)
    {
        string months[] = {"January", "February", "March",
                        "April", "May", "June",
                        "July", "August", "September",
                        "October", "November", "December"
                        };

        return (months[monthNumber]);
    }

    void getEvents(){
        ifstream plik;
        plik.open("events.txt");


        while(!plik.eof()){
            int day, month, year, s_h, s_m;
            string title;
            plik >> day;
            plik >> month;
            plik >> year;
            plik >> s_h;
            plik >> s_m;
            plik >> title;
            events->insertNode(day, month, year, s_h, s_m, title);
        }

        plik.close();
        cout << events->getLenght();
    }

    void saveEvents(){
        ofstream plik;
        plik.open("events.txt");

        for(int i=1; i<events->getLenght();i++){
            plik << events->getNode(i)->getDay() << endl;
            plik << events->getNode(i)->getMonth() << endl;
            plik << events->getNode(i)->getYear() << endl;
            plik << events->getNode(i)->getTime().getHours() << endl;
            plik << events->getNode(i)->getTime().getMinutes() << endl;
            plik << events->getNode(i)->getTitle();
        }
        plik.close();
        
        
    }


    void printMonth(){

        setDays();

        int current = dayNumber (1,year);


        printf("\n ------------%s-------------\n",
            getMonthName (month-1).c_str());

        cout << "\n --------------" << year << "--------------\n" << endl;

  
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int k;
        for (k = 0; k < current; k++)
            printf("     ");

        for (int j = 1; j <= days; j++)
        {
            if(j == chosen_day) 
            printf("\x1b[32m    %d\x1b[0m",j);
            else
            printf("%5d", j);

            if (++k > 6)
            {
                k = 0;
                printf("\n");
            }
        }

        if (k)
            printf("\n");

        current = k;

    cout << "   [1] <- Miesiac -> [2] " << endl;
    cout << "   [a] <-  Dzien  -> [d] " << endl;
    cout << "   [w] -> Dodaj " << endl;
    cout << "   [q] -> Usun " << endl << endl;

    events->printList(chosen_day, month, year);

    char choice;
    cin >> choice;
    switch (choice) {
        case '1':
            if(month == 1){
                year--;
                month=12;
                this->printMonth();
            } 
            else {
                month--;
                this->printMonth();
            }
            break;

        case '2':
            if(month == 12){
                year++;
                month=1;
                this->printMonth();
            } 
            else{
                month++;
                this->printMonth();
            }
            break;

        case 'a':
            if(chosen_day == 1){
                if(month == 1){
                    year--;
                    month=12;
                    chosen_day=31;
                }
                else{
                    month--;
                    chosen_day=this->numberOfDays();
                }
            }
            else{
                chosen_day--;
            }
            this->printMonth();
            break;
        
        case 'd':
            if(chosen_day == this->numberOfDays()){
                if(month == 12){
                    year++;
                    month=1;
                    chosen_day=1;
                }
                else{
                    month++;
                    chosen_day=1;
                }
                
            }
            else{
                chosen_day++;
            }
            this->printMonth();
            break;

        case 's':
            for(int i=0;i<events->getLenght();i++){
                events->getNode(i)->showEvent();
            }
            this->printMonth();
        break;

        case 'q':
            int id;
            cout << "Wprowadz id: ";
            cin >> id;
            events->deleteNode(id);
            this->saveEvents();
            this->printMonth();
            

        break;  
        
        case 'w':
            int s_h, s_m;
            string t;
            cout << "Wprowadz godzine: ";
            cin >> s_h;
            cout << endl;
            cout << "Wprowadz minuty: ";
            cin >> s_m;
            cout << "Wprowadz nazwe: ";
            cin >> t;
            events->insertNode(chosen_day, month, year, s_h, s_m, t);
            this->saveEvents();
            this->printMonth();
        break;

       

        

	}
    
    }
};

Linkedlist *Linkedlist::s_Instance = new Linkedlist;

int main(){

    

    Calendar c1(2023);

    Month m1(1,2,2023);

    m1.printMonth();


    //e1.showEvent();

}