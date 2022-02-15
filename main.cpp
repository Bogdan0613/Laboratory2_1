#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

enum enter_menu { sign_in = 1, registration = 2};
enum user_menu { show_list = 1, soonest_transport = 2, Exit = 3};
enum admin_menu { add_transport = 1,show_buses = 2, delete_bus = 3, end_session = 4};

struct Node_clients{
    string login;
    string password;
    bool role;
    Node_clients* next;
    Node_clients* prev;
};
Node_clients* head1 = nullptr;
Node_clients* tail1 = nullptr;

void add_client(Node_clients* tail1, char login, char password, bool role);

void add_client(Node_clients* tail1, char login[20], char password[20], bool role){
    if(tail1 == nullptr){
        Node_clients* Node = new Node_clients();
        Node->login = login;
        Node->password = password;
        Node->role = role;
        head1 = Node;
        tail1 = head1;
    }else{
        Node_clients* Node = new Node_clients();
        Node->login = login;
        Node->password = password;
        Node->role = role;
        Node->next = nullptr;
        Node->prev = tail1;
        tail1->next = Node;
        tail1 = Node;
    }
}


struct Node_transport {
    int bus_number;
    int frequency;
    int route_number;
    bool location;
    Node_transport* next;
    Node_transport* prev;
};
Node_transport* head2 = nullptr;
Node_transport* tail2 = nullptr;

void bus_arrived(Node_transport* tail2, int bus_number, char driver_initials[50], int route_number, bool location);
void print_station(Node_transport* const head);
void print_buses(Node_transport* const head);
void bus_left(Node_transport** head, Node_transport** tail, int key);
Node_transport* find(Node_transport* const head, int key);

Node_transport* find(Node_transport* const head, int key){
    Node_transport* node = head2;
    while(node != nullptr){
        if(node->route_number==key) break;
        node = node->next;
    }
    return node;
}

void bus_left(Node_transport* head2, Node_transport* tail2, int key){
    if(Node_transport* node = find(head2,key)){
        if(node == head2){
            head2 = (head2)->next;
            (head2)->prev = nullptr;
        }else if(node == tail2){
            tail2 = (tail2)->prev;
            (tail2)->next = nullptr;
        }else{
            (node->prev)->next = node->next;
            (node->next)->prev = node->prev;
        }
    }
}

void add_bus(Node_transport* tail2, int bus_number, int frequency, int route_number, bool location){
    if(tail2 == nullptr){
        Node_transport* node = new Node_transport();
        node->bus_number = bus_number;
        node->frequency = frequency;
        node->route_number = route_number;
        node->location = location;
        head2 = node;
        tail2 = head2;
    }else{
        Node_transport* node = new Node_transport();
        node->bus_number = bus_number;
        node->frequency = frequency;
        node->route_number = route_number;
        node->location = location;
        node->next = nullptr;
        node->prev = tail2;
        tail2->next = node;
        tail2 = node;
    }
}

void print_buses(Node_transport* const head){
    Node_transport* node = head;
    cout << "----------------" << endl << "\t" << " ROUTE" << endl << "----------------"<<endl;
    while(node != nullptr){
        cout << "Bus number:" << node->bus_number << endl << "Frequency:" << node->frequency << endl
        << "Route number:" << node->route_number << endl;
    }
    node = node->next;
}




FILE* f_clients;
FILE* f_admin;
FILE* f_buses;
FILE* f_trams;
FILE* f_trolleybuses;

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
        
        int check = 0;
        switch (choice) {
            case sign_in: {
                
                char login[20];
                char password[20];
                cout << "Enter your login:";
                cin >> login;
                cout << "Enter your password:";
                cin >> password;
                
                string login_s, password_s;
                login_s = string(login);
                password_s = string(password);
                string client_data = login_s + password_s;
                char s2[20];
                char s3[20];
                f_clients = fopen("clients_list.txt", "rb");
                if(f_clients != NULL){
                    fread(s2, sizeof(char), 20, f_clients);
                }
                f_admin = fopen("admin.txt", "rb");
                
                if(f_admin != NULL){
                    fread(s3, sizeof(char), 20, f_admin);
                }
                fclose(f_admin);
                
                cout<<"!!!"<<client_data<<endl<<"!!!"<<s2<<endl;
                
                if(client_data == string(s3)){
                    add_client(tail1, login, password, 1);
                    admin_menu();
                }else if(client_data == string(s2)){
                    add_client(tail1, login, password, 0);
                    user_menu();
                }else{
                    cout << "You are not registered!"<<endl;
                }
            }
            case registration:{
                char login[20];
                char password[20];
                cout << "Create your login:";
                cin >> login;
                cout << "Create your password:";
                cin >> password;
                string client_data = string(login)+string(password);
                add_client(tail1, login, password, 0);
                
                f_clients = fopen("clients_list.txt","ab");
                fwrite(login, sizeof(login), sizeof(login), f_clients);
                fwrite(password, sizeof(password), sizeof(password), f_clients);
                fclose(f_clients);
                admin_menu();
                break;
            }
                
                
        }
    }
}
void user_menu(){
    int choice = 1;
    while(choice != 0){
        cout << "Hello, you are in user menu\n Choose the action:\n1)Show the list of the transport\n2)The soonest transport\n3)Exit\n";
        cin >> choice;
        switch (choice) {
            case show_list:
                print_buses(head2);
                break;
            case soonest_transport:
                print_buses(head2);
                cout << "Enter the transport number:";
                break;
            case Exit:
                cout << "Goodbye!"<<endl;
                choice = 0;
                break;
                
        }
    }
}

void admin_menu(){
    int choice = 1;
    while(choice!=0){
        cout << "Hello, you are in admin menu\n Choose the action:\n1)Add the transport\n2)Show the busses\n3)Delete bus\n4)End session\n";
        cin >> choice;
        switch (choice) {
            case add_transport:{
                int choose;
                cout << "Enter the type of the transport you want to choose(1-bus, 2-tram, 3-trolley):";
                cin >> choose;
                if(choose == 1){
                    int num1;
                    bool exists = 0;
                    int num[5];
                    cout << "Enter the bus number:";
                    cin >> num1;
                    f_buses = fopen("ListOfBusses.txt","rb");
                    fread(num, sizeof(int), sizeof(num)/sizeof(int), f_buses);
                    fclose(f_buses);
                    for(int i = 0; i<5; i++){
                        if(num1==num[i]){
                            cout << "The bus succesfully added"<<endl;
                            add_bus(tail2, 5, num[i], 10, 1);
                            exists = 1;
                        }
                    }
                    if(exists == 0){
                        cout << "Do you want to add a bus?(1-Yes 2-No)";
                        cin >> choose;
                        if(choose == 1){
                            add_bus(tail2, 5, num1, 10, 1);
                            cout << "Bus succesfully added"<<endl;
                            f_buses = fopen("ListOfBusses.txt","rb");
                            fwrite(&num1, sizeof(int), 1, f_buses);
                            fclose(f_buses);
                        }else{
                            break;
                        }
                    }
                }else if(choose == 2){
                    int num1;
                    bool exists = 0;
                    int num[5];
                    cout << "Enter the tram number:";
                    cin >> num1;
                    f_trams = fopen("ListOfTrams.txt","rb");
                    fread(num, sizeof(int), sizeof(num)/sizeof(int), f_trams);
                    fclose(f_trams);
                    for(int i = 0; i<5; i++){
                        if(num1==num[i]){
                            cout << "The tram succesfully added"<<endl;
                            add_bus(tail2, 5, num[i], 15, 1);
                            exists = 1;
                        }
                    }
                    if(exists == 0){
                        cout << "Do you want to add a bus?(1-Yes 2-No)";
                        cin >> choose;
                        if(choose == 1){
                            add_bus(tail2, 5, num1, 15, 1);
                            cout << "The tram succesfully added"<<endl;
                            f_buses = fopen("ListOfTrams.txt","rb");
                            fwrite(&num1, sizeof(int), 1, f_trams);
                            fclose(f_trams);
                        }else{
                            break;
                        }
                    }
                }else if(choose == 3){
                    int num1;
                    bool exists = 0;
                    int num[5];
                    cout << "Enter the trolley number:";
                    cin >> num1;
                    f_trams = fopen("ListOfTrolleys.txt","rb");
                    fread(num, sizeof(int), sizeof(num)/sizeof(int), f_trolleybuses);
                    fclose(f_trolleybuses);
                    for(int i = 0; i<5; i++){
                        if(num1==num[i]){
                            cout << "The trolleybus succesfully added"<<endl;
                            add_bus(tail2, 5, num[i], 15, 1);
                            exists = 1;
                        }
                    }
                    if(exists == 0){
                        cout << "Do you want to add a trolleybus?(1-Yes 2-No)";
                        cin >> choose;
                        if(choose == 1){
                            add_bus(tail2, 5, num1, 15, 1);
                            cout << "The trolleysbus succesfully added"<<endl;
                            f_buses = fopen("ListOfTrolleys.txt","rb");
                            fwrite(&num1, sizeof(int), 1, f_trolleybuses);
                            fclose(f_trolleybuses);
                        }else{
                            break;
                        }
                    }
                }
                break;
            }
                
            case show_buses:
                print_buses(head2);
                break;
                
            case delete_bus:
                cout << "Enter the route number to delete:";
                break;
                
            case end_session:
                choice = 0;
                cout << "Goodbye"<<endl;
                break;
        }
    }
}
