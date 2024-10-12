#include <iostream>
#include <vector>

// 命令接口
class Command {
public:
  virtual void execute() = 0;
  virtual ~Command() = default;
};

// 具体命令：打开文件
class OpenFileCommand : public Command {
public:
  void execute() override { std::cout << "Opening file..." << std::endl; }
};

// 具体命令：关闭文件
class CloseFileCommand : public Command {
public:
  void execute() override { std::cout << "Closing file..." << std::endl; }
};

// 命令调用者
class FileInvoker {
  std::vector<Command *> commands;

public:
  void addCommand(Command *command) { commands.push_back(command); }

  void executeCommands() {
    for (Command *command : commands) {
      command->execute();
    }
    commands.clear();
  }

  ~FileInvoker() {
    for (Command *command : commands) {
      delete command;
    }
  }
};

int main() {
  Command *openCommand = new OpenFileCommand();
  Command *closeCommand = new CloseFileCommand();

  FileInvoker invoker;
  invoker.addCommand(openCommand);
  invoker.addCommand(closeCommand);

  invoker.executeCommands(); // 打开文件，关闭文件

  return 0;
}
