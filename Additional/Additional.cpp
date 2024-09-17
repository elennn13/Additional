#include <iostream>
#include <string>


class MyException : public std::exception { // производный класс от исключений

private:
    int code;

public:
    MyException() : code(0) {}
    MyException(const char* what, int code) : std::exception(what) {
        this->code = code;
    }
    int getCode() const { return code; }


};




class Person {

private:
    std::string name;
    unsigned age;
    const unsigned max_age = 110;

public:
    Person() : age(0) {}
    explicit Person (std::string name) : name(name), age(0) { }// explicit (запретит не явное преобразование)конструктор который не молжет вызываться компелятором


    void setName(std::string name) { this->name = name; }
    const std::string& getName() const { return name; } 

    void setAge(unsigned age) { 
        if (age > max_age)
            throw std::out_of_range("max age exceeded"); // ошибка! привышен максимальный возраст 
        this->age = age; 
    }
    unsigned getAge() const { return age; }


  operator bool() const {
      return name != "" || age != 0; // если имя не пустое и возраст не равен нулю
    }

  explicit operator std::string() {
      std::string result = name;
      name += ", "; name += age; name += "y.o";
      return result;
  }


};

std::ostream& operator<<(std::ostream& out, const Person& p) { // оператор битового сдвига влево
    out << p.getName() << ", " << p.getAge() << " y.o. ";
    return out;
}

std::istream& operator>>(std::istream& in, Person& p) { // оператор битового сдвига вправо// ввод в консоли
    std::string name;
    std::getline(in, name);

    unsigned age;
    in >> age; 

    p.setName(name);
    p.setAge(age);

    return in;
}

class Base {

private: 
    // данные базового класса

public:
    // конструктор и деструктор 
    Base() { std::cout << "Base() " << std::endl;}
   virtual ~Base() { std::cout << "~Base() " << std::endl;}// виртуальный диструктор

    
};

class Addit : public Base {
private:
    // делаем выделение динамической памяти вручную
    int* pointer;
    size_t size;

public:
    Addit() { std::cout << "Addit()" << std::endl;
    size = 5;
    pointer = new int[size];
}
    ~Addit() { 
        std::cout << "~Addit()" << std::endl; 
        delete[] pointer;
    }

};

int main() {
    setlocale(LC_ALL, "ru");

    // Ввод вывод объектов, преобразование типов и эксплисит
    /*
    Person p1("John");
    p1.setAge(18);
    if (p1)
       std::cout << "Employee №1: " << p1 << std::endl;

   
    Person p2;
    std::cout << "Enter name -> " << std::endl;
    std::cin >> p2;
    std::cout << "Employee №2: " << p2 << std::endl;


    Person p3;
    if (p3)
        std::cout << "Employee №3 : " << p3 << std::endl;

   // Person p4 = std::string("Bob");
    bool f = p3;

    std::string str = std::string(p1);
    std::cout << str << std::endl;
    */

    // Addit add;
    Base *pointer = new Addit;
    delete pointer;


    try {
        std::cout << "Doing something...\n";
        if (2 * 2 != 5)
            throw MyException("important question error", 7);
        std::cout << "Coffee time!\n";
    }
    catch (const MyException& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        std::cout << "Code: " << ex.getCode() << std::endl;
    }


    return 0;
}

