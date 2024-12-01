// 312.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

class Toy {
public:
    Toy(const std::string& name) : name_(name) {}

    std::string getName() const {
        return name_;
    }

    ~Toy() {
        std::cout << "Toy " << name_ << " was dropped." << std::endl;
    }

private:
    std::string name_;
};

class shared_ptr_toy {
public:
  
    shared_ptr_toy() : ptr_(nullptr), count_(new int(0)) {}

   
    explicit shared_ptr_toy(const std::string& toyName)
        : ptr_(new Toy(toyName)), count_(new int(1)) {}

    
    shared_ptr_toy(const shared_ptr_toy& other)
        : ptr_(other.ptr_), count_(other.count_) {
        ++(*count_);
    }

   
    shared_ptr_toy& operator=(const shared_ptr_toy& other) {
        if (this != &other) {
            
            reset();
           
            ptr_ = other.ptr_;
            count_ = other.count_;
            ++(*count_);
        }
        return *this;
    }

   
    ~shared_ptr_toy() {
        reset();
    }

   
    void reset() {
        if (count_ && --(*count_) == 0) {
            delete ptr_;
            delete count_;
        }
        ptr_ = nullptr;
        count_ = new int(0);
    }

  
    Toy* get() const {
        return ptr_;
    }

    
    std::string getToyName() const {
        if (ptr_) {
            return ptr_->getName();
        }
        return "Nothing";
    }

   
    int use_count() const {
        return *count_;
    }

private:
    Toy* ptr_;    
    int* count_;  
};


shared_ptr_toy make_shared_toy(const std::string& name) {
    return shared_ptr_toy(name);  
}

int main() {
    shared_ptr_toy toy_01 = make_shared_toy("ball");
    shared_ptr_toy toy_02(toy_01);
    shared_ptr_toy toy_03("duck");

    std::cout << "=================================================" << std::endl;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

    toy_02 = toy_03;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

    toy_01.reset();
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

    toy_02.reset();
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

    return 0;
}