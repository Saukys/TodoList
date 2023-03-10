#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

class TodoItem {
private:
    int id;
    std::string description;
    bool completed;

public:
    TodoItem(): id(0), description(""), completed(false){}

    TodoItem(int new_id, string new_description, bool new_completed)
    {
        id = new_id;
        description = new_description;
        completed = new_completed;

    }
    ~TodoItem() = default;

    bool create(std::string new_description) {
        description = new_description;

        id = rand() % 10000 + 1;
        
        return true;
    }

    int getId() { return id; }
    std::string getDescripton() { return description; }
    bool isCompleted() { return completed; }
    void setCompleted()
    { 
        if (completed) {
            completed = false;
        }
        else if (!completed)
        {
            completed = true;
        }
    }


};

int main()
{
    std::list<TodoItem> todoItems;
    std::list<TodoItem>::iterator it;

    srand(time(NULL));
    
    todoItems.clear();

    int saved_files;
    int saved_id;
    string saved_description;
    bool saved_completed;
    ifstream fin("save.txt");
    fin >> saved_files;
    for (int i = 0; i < saved_files; i++) {
        fin >> saved_id;
        fin.ignore();
        getline(fin, saved_description);
        fin >> saved_completed;
        TodoItem saved_todo(saved_id, saved_description, saved_completed);
        todoItems.push_back(saved_todo);
    }
    fin.close();


    char choice = ' ';

    while (true) {
        system("cls");
        std::cout << "Todo List Maker" << endl << endl;

        

        for (it = todoItems.begin(); it != todoItems.end(); it++) {

            std::string completed;

            if (it->isCompleted()) 
            {
                completed = "Completed";
            }
            else
            {
                completed = "Uncompleted";
            }


            std::cout << it->getId() << " | " << it->getDescripton() << " | " << completed << std::endl;
        }

        if (todoItems.empty()) {
            cout << "Add your first Todo item!" << endl;
        }


      
        cout << "[a]dd a new Todo item" << endl;
        cout << "[c]omlete/uncomplete a Todo item" << endl;
        cout << "[q]uit" << endl;
        cout << "[d]elate" << endl;
        cout << "choice:";
        cin >> choice;
       

        if (choice == 'a')
        {
            TodoItem new_todo;
            string description1, description2, description;
            cout << "Description: ";
            cin >> description1;
            getline(cin, description2);
            description = description1 + description2;
            new_todo.create(description);
            todoItems.push_back(new_todo);
            choice = ' ';
        }
        else if (choice == 'q') 
        {
            ofstream fout("save.txt");

            fout << todoItems.size()<< endl;
            for (it = todoItems.begin(); it != todoItems.end(); it++) {
                fout << it->getId() << endl << it->getDescripton() << endl << it->isCompleted() << endl;
            }

            fout.close();

            cout << "Goodbye";
            break;
        }
        else if (choice == 'c')
        {
            int id;
            cout << "Item id: ";
            cin >> id;

            for (it = todoItems.begin(); it != todoItems.end(); it++) {
                if (it->getId() == id) {
                    it->setCompleted();
                }
            }

            choice == ' ';

        }
        else if (choice == 'd')
        {
            int id;
            cout << "Item id: ";
            cin >> id;

            list<TodoItem>::iterator i;


            for (it = todoItems.begin(); it != todoItems.end(); it++) {
                if (it->getId() == id) {
                    i = it;
                }
            }
            todoItems.erase(i);

            choice == ' ';

        }

    }
    return 0;
}

