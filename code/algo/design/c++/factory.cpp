#include <iostream>

class Book {
public:
  virtual void displayFormat() const = 0;
  virtual ~Book() {}
};

class PDFBook : public Book {
public:
  void displayFormat() const override {
    std::cout << "This is a PDF book." << std::endl;
  }
};

class EPUBBook : public Book {
public:
  void displayFormat() const override {
    std::cout << "This is an EPUB book." << std::endl;
  }
};

class BookFactory {
public:
  static Book *createBook(const std::string &format) {
    if (format == "pdf") {
      return new PDFBook();
    } else if (format == "epub") {
      return new EPUBBook();
    } else {
      return nullptr;
    }
  }
};

// 使用方式
int main() {
  Book *myBook = BookFactory::createBook("pdf");
  if (myBook) {
    myBook->displayFormat();
    delete myBook;
  }
  return 0;
}
