#include <iostream>
#include <vector>
#include <string>

// 观察者接口
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

// 被观察者类
class Subject {
private:
    std::vector<Observer*> observers;
    std::string message;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void setMessage(const std::string& msg) {
        message = msg;
        notify();
    }

    void notify() {
        for (auto observer : observers) {
            observer->update(message);
        }
    }
};

// 具体观察者
class ConcreteObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Observer received message: " << message << std::endl;
    }
};

// 使用方式
int main() {
    Subject subject;
    ConcreteObserver observer1, observer2;
    subject.attach(&observer1);
    subject.attach(&observer2);

    subject.setMessage("Task completed");
    return 0;
}
