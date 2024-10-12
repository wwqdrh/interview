#include <iostream>
#include <string>


class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;  // C++11之后的线程安全单例实现
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "Log: " << message << std::endl;
    }

private:
    Logger() {}  // 构造函数私有化
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;
};

// 使用方式
int main() {
    Logger::getInstance().log("Service started");
    return 0;
}