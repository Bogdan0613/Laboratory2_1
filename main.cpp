#include<iostream>
include<fstream>

using namespace std;

enum enter_menu { sign_in = 1, registration = 2, end_session = 3};
enum user_menu { show_list = 1, soonest_transport = 2, Exit = 3};
enum admin_menu { add_bus = 1,station_buses = 2, route_buses = 3,  station_arrival = 4, station_left = 5};

struct Node_clients{
    string login;
    string password;
    bool role;
    Node_clients* next;
    Node_clients* prev;
};
Node_clients* head1 = nullptr;
Node_clients* tail1 = nullptr;

Node_clients* add_first(char login, char password, bool role);
void add_client(Node_clients** tail, char login, char password, bool role);

Node_clients* add_first(char login, char password, bool role){
    Node_clients* Node = new Node_clients();
    Node->login = login;
    Node->password = password;
    Node->role = role;
    return Node;
}

void add_client(Node_clients** tail, char login, char password, bool role){
    Node_clients* Node = new Node_clients();
    Node->login = login;
    Node->password = password;
    Node->role = role;
    Node->next = nullptr;
    Node->prev = *tail;
    (*tail)->next = Node;
    *tail = Node;
}


struct Node_bus {
    int bus_number;
    int frequency;
    int route_number;
    bool location;
    Node_bus* next;
    Node_bus* prev;
};

Node_bus* head2 = nullptr;
Node_bus* tail2 = nullptr;

Node_bus* add(int bus_number, char driver_initials[50], int route_number, bool location);
void bus_arrived(Node_bus** tail, int bus_number, char driver_initials[50], int route_number, bool location);
void print_station(Node_bus* const head);
void print_route(Node_bus* const head);
void bus_left(Node_bus** head, Node_bus** tail, int key);
Node_bus* find(Node_bus* const head, int key);

Node_bus* add(int bus_number, int frequency, int route_number, bool location){
    Node_bus* node = new Node_bus();
    node->bus_number = bus_number;
    node->frequency = frequency;
    node->route_number = route_number;
    node->location = location;
    return node;
}

Node_bus* find(Node_bus* const head, int key){
    Node_bus* node = head;
    while(node != nullptr){
        if(node->bus_number==key) break;
        node = node->next;
    }
    return node;
}

void bus_left(Node_bus** head, Node_bus** tail, int key){
    if(Node_bus* node = find(*head,key)){
        if(node == *head){
            *head = (*head)->next;
            (*head)->prev = nullptr;
        }else if(node == *tail){
            *tail = (*tail)->prev;
            (*tail)->next = nullptr;
        }else{
            (node->prev)->next = node->next;
            (node->next)->prev = node->prev;
        }
    }
}

void bus_arrived(Node_bus** tail, int bus_number, int frequency, int route_number, bool location){
    if(tail==nullptr){
        Node_bus* node = new Node_bus();
        node->bus_number = bus_number;
        node->frequency = frequency;
        node->route_number = route_number;
        node->location = location;
    }
    Node_bus* node = new Node_bus();
    node->bus_number = bus_number;
    node->frequency = frequency;
    node->route_number = route_number;
    node->location = location;
    node->next = nullptr;
    node->prev = *tail;
    (*tail)->next = node;
    *tail = node;
}

void print_station(Node_bus* const head){
    Node_bus* node = head;
    cout << "----------------" << endl << "\t" << "STATION" << endl << "----------------"<<endl;
    while(node != nullptr){
        if(node->location==1) {
            cout << "Bus number:" << node->bus_number << endl << "Frequency:" << node->frequency << endl
                 << "Route number:" << node->route_number << endl;
        }
        node = node->next;
    }
}

void print_route(Node_bus* const head){
    Node_bus* node = head;
    cout << "----------------" << endl << "\t" << " ROUTE" << endl << "----------------"<<endl;
    while(node != nullptr){
        if(node->location==0) {
            cout << "Bus number:" << node->bus_number << endl << "Frequency:" << node->frequency << endl
                 << "Route number:" << node->route_number << endl;
        }
        node = node->next;
    }
}



FILE* f_clients;
FILE* f_transport;

void admin_menu();
void user_menu();
int main(){
    //    time_t seconds = time(NULL);
    //    tm* timeinfo = localtime(&seconds);
    //    cout<<"Current Datetime:"<<asctime(timeinfo)<<endl;

    while(true){
        int choice;
        cout << "Enter the action:\n1)Sign in\n2)Register\n3)End session\n";
        cin >> choice;

        switch (choice) {
            case sign_in:

                char login[20];
                char password[20];
                cout << "Enter your login:";
                cin >> login;
                cout << "Enter your password:";
                cin >> password;

//                char client_data[sizeof(login) + sizeof(password)];
//                strcpy(&client_data[0], login);
//                strcpy(&client_data[sizeof(login)-1], password);
                string login_s, password_s;
                login_s = string(login);
                password_s = string(password);
                string client_data = login_s + password_s;
                char s2[20];
                f_clients = fopen("clients_list.txt", "rb");
                if(f_clients != NULL){
                    fread(s2, sizeof(char), 20, f_clients);
                }
                fclose(f_clients);
                if(client_data == string(s2)){
            user_menu();
        }
                break;
//
//            case registration:
//
//                break;
//            case end_session:
//
//                break;

        }
    }
}
void user_menu(){
    int choice;
    while(true){
        cout << "Hello, you are in user menu\n Choose the action:\n1)Show the list of the transport\n2)The soonest transport\n3)Exit\n";
        cin >> choice;
        switch (choice) {
            case show_list:
                print_route(head2);
                break;
            case soonest_transport:
                print_route(head2);
                cout << "Enter the ";
                break;
            case Exit:

                break;

        }
    }
}

void admin_menu(){
    int choice;
    while(true){
        cout << "Hello, you are in admin menu\n Choose the action:\n1)Add the bus\n2)Show the busses on the station\n3)Show the busses on the route\n4)Bus arrives to the station\n5)Bus leaves the station\n";
    }
}
