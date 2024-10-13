#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Task {
  int id;
  std::string description;
  bool completed;

  Task(int id, const std::string &desc, bool comp)
      : id(id), description(desc), completed(comp) {}

  std::string status() const { return completed ? "Completed" : "Pending"; }
};

class TodoList {
private:
  std::vector<Task> tasks;
  int next_id;

public:
  TodoList() : next_id(1) {}

  void add_task(const std::string &description) {
    tasks.emplace_back(next_id++, description, false);
  }

  void remove_task(int id) {
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                               [id](const Task &t) { return t.id == id; }),
                tasks.end());
  }

  void mark_complete(int id) {
    for (auto &task : tasks) {
      if (task.id == id) {
        task.completed = true;
        break;
      }
    }
  }

  void display_tasks() const {
    std::cout << std::setw(5) << "ID" << std::setw(20) << "Description"
              << std::setw(15) << "Status"
              << "\n";
    std::cout << "------------------------\n";
    for (const auto &task : tasks) {
      std::cout << std::setw(5) << task.id << std::setw(20) << task.description
                << std::setw(15) << task.status() << "\n";
    }
    std::cout << "=======================\n";
  }

  void save_to_file(const std::string &filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
      for (const auto &task : tasks) {
        file << task.id << "|" << task.description << "|" << task.completed
             << "\n";
      }
    }
    file.close();
  }

  void load_from_file(const std::string &filename) {
    std::ifstream file(filename);
    tasks.clear();
    std::string line;
    if (file.is_open()) {
      while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_str, desc, comp_str;
        getline(ss, id_str, '|');
        getline(ss, desc, '|');
        getline(ss, comp_str, '|');
        tasks.emplace_back(std::stoi(id_str), desc, std::stoi(comp_str));
        next_id = std::stoi(id_str) + 1;
      }
    }
    file.close();
  }
};

void display_menu() {
  std::cout << "Todo List Manager\n";
  std::cout << "1. Add Task\n";
  std::cout << "2. Remove Task\n";
  std::cout << "3. Mark Task as Completed\n";
  std::cout << "4. View All Tasks\n";
  std::cout << "5. Save Tasks to File\n";
  std::cout << "6. Load Tasks from File\n";
  std::cout << "7. Exit\n";
}

int main() {
  TodoList todo_list;
  int choice;

  while (true) {
    display_menu();
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
      std::cin.ignore();
      std::string description;
      std::cout << "Enter task description: ";
      getline(std::cin, description);
      todo_list.add_task(description);
    } else if (choice == 2) {
      int id;
      std::cout << "Enter task ID to remove: ";
      std::cin >> id;
      todo_list.remove_task(id);
    } else if (choice == 3) {
      int id;
      std::cout << "Enter task ID to mark as completed: ";
      std::cin >> id;
      todo_list.mark_complete(id);
    } else if (choice == 4) {
      todo_list.display_tasks();
    } else if (choice == 5) {
      std::cin.ignore();
      std::string filename;
      std::cout << "Enter filename to save tasks: ";
      getline(std::cin, filename);
      todo_list.save_to_file(filename);
    } else if (choice == 6) {
      std::cin.ignore();
      std::string filename;
      std::cout << "Enter filename to load tasks: ";
      getline(std::cin, filename);
      todo_list.load_from_file(filename);
    } else if (choice == 7) {
      break;
    } else {
      std::cout << "Invalid choice, please try again.\n";
    }
  }
}