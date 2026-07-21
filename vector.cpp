#include <iostream>
#include <stdexcept>

template <typename T>
class myVector{
private:
    size_t size_;
    size_t capacity_;
    T* arr;
public:
    // default constructor no arguments
    myVector(){
        size_ = 0;
        capacity_ = 0;
        arr = nullptr;
    }
    // constructor with arguments
    myVector(size_t n){
        size_ = n;
        capacity_ = n;
        // initialize with default value of datatype
        arr = new T[capacity_]();
    }
    // destructor
    ~myVector(){
        // call destructors for elements
        // not necessary, delete[] calls destructor for all elements anyways
        // for(size_t i = 0; i < size; i++){
        //     arr[i].~T();
        // }
        delete[] arr;
    }
    // copy constructor
    myVector(const myVector& other){
        if(other.arr == nullptr){
            size_ = 0;
            capacity_ = 0;
            arr = nullptr;
            return;
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        arr = new T[capacity_];
        for(size_t i = 0; i < size_; i++){
            arr[i] = other.arr[i];
        }
    }
    
    // move constructor
    myVector(myVector&& other) noexcept {
        size_ = other.size_;
        capacity_ = other.capacity_;
        arr = other.arr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.arr = nullptr;
    }

    // copy assignment operator
    myVector& operator=(const myVector& other){
        if(this == &other){
            return *this;
        }
        delete[] arr;
        size_ = other.size_;
        capacity_ = other.capacity_;
        arr = new T[capacity_];
        for(size_t i = 0; i < size_; i++){
            arr[i] = other.arr[i];
        }
        return *this;
    }

    // move assignment operator
    myVector& operator=(myVector&& other) noexcept {
        if(this == &other){
            return *this;
        }
        delete[] arr;
        size_ = other.size_;
        capacity_ = other.capacity_;
        arr = other.arr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.arr = nullptr;
        return *this;
    }

    // operator overload []
    T& operator[](const size_t index) {
        // no bounds checking here
        return arr[index];
    }
    // const operator overload [], allowed to use on const vectors
    const T& operator[](const size_t index) const {
        // no bounds checking here
        return arr[index];
    }

    // .at() operator
    // performs bounds checking
    T& at(const size_t index) {
        if(index >= size_){
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }
    // const .at() operator, allowed to use on const vectors
    const T& at(const size_t index) const {
        if(index >= size_){
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    // .front() function
    T& front() {
        if(size_ == 0){
            throw std::out_of_range("Vector is empty");
        }
        return arr[0];
    }
    // const .front() function, allowed to use on const vectors
    const T& front() const {
        if(size_ == 0){
            throw std::out_of_range("Vector is empty");
        }
        return arr[0];
    }

    // .back() function
    T& back() {
        if(size_ == 0){
            throw std::out_of_range("Vector is empty");
        }
        return arr[size_ - 1];
    }
    // const .back() function, allowed to use on const vectors
    const T& back() const {
        if(size_ == 0){
            throw std::out_of_range("Vector is empty");
        }
        return arr[size_ - 1];
    }

    // .size() function
    size_t size() const{
        return size_;
    }

    // .capacity() function
    size_t capacity() const{
        return capacity_;
    }

    // .empty() function
    bool empty() const{
        return size_ == 0;
    }

    // .clear() function
    void clear(){
        // call destructors for elements
        // for(size_t i = 0; i < size; i++){
        //     arr[i].~T();
        // }
        size_ = 0;
    }

    // .reserve() function
    void reserve(size_t capacity){
        // if capacity is smaller or equal to current capacity, return
        if(capacity <= this->capacity_){
            return;
        }
        // create new array with new capacity
        T* newArr = new T[capacity];
        // copy elements from old array to new array
        for(size_t i = 0; i < size_; i++){
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        this->capacity_ = capacity;
    }

    // .resize() function
    void resize(size_t size){
        // if size is smaller or equal to current size, shrink size
        if(size <= this->size_){
            this->size_ = size;
            return;
        }
        // if size is greater than current size, reserve space
        reserve(size);
        // update size
        this->size_ = size;
    }

    // .push_back() function
    void push_back(const T& value){
        // if size equals capacity, reserve space
        if(size_ == capacity_){
            // if capacity is 0, reserve 1
            if(capacity_ == 0){
                reserve(1);
            }else{
                // otherwise, double the capacity
                reserve(capacity_ * 2);
            }
        }
        // insert value at the end
        arr[size_] = value;
        size_++;
    }

    // .pop_back() function
    void pop_back(){
        if(size_ == 0){
            throw std::out_of_range("Vector is empty");
        }
        size_--;
    }

    // .insert() function
    void insert(const size_t index, const T& value){
        // check bounds
        if(index > size_){
            throw std::out_of_range("Index out of range");
        }
        // check if capacity is full
        if(size_ == capacity_){
            // if capacity is 0, reserve 1
            if(capacity_ == 0){
                reserve(1);
            }else{
                // otherwise, double the capacity
                reserve(capacity_ * 2);
            }
        }
        // shift elements to the right
        for(size_t i = size_; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        // insert value at the index
        arr[index] = value;
        // update size
        size_++;
    }

    // .erase() function
    void erase(const size_t index){
        // check bounds
        if(index >= size_){
            throw std::out_of_range("Index out of range");
        }
        // shift elements to the left
        for(size_t i = index; i < size_ - 1; i++){
            arr[i] = arr[i + 1];
        }
        // update size
        size_--;
    }
};

void intTest(){
    // -----------------------Int Tests-----------------------
    // create int vector
    myVector<int> intVec;
    // reserve 10 elements
    intVec.reserve(10);
    // add 10 elements to vector
    for(size_t i = 0; i < 10; i++){
        intVec.push_back(i);
    }
    // remove last element
    intVec.pop_back();
    // insert 10 at index 0
    intVec.insert(0, 10);
    // remove element at index 2
    intVec.erase(2);
    // add 11 and 12 to back
    intVec.push_back(11);
    // this should trigger a resize, doubling capacity to 20
    intVec.push_back(12);
    std::cout << "------Int Test------" << std::endl;
    std::cout << "vector size: " << intVec.size() << std::endl;
    std::cout << "vector capacity: " << intVec.capacity() << std::endl;
    for(size_t i = 0; i < intVec.size(); i++){
        std::cout << intVec[i] << " ";
    }
    // expected output: 
    // vector size: 11
    // vector capacity: 20
    // 10 0 2 3 4 5 6 7 8 11 12
    std::cout << std::endl;
}

void structTest(){
        // -----------------------Struct Tests-----------------------
    struct Person{
        std::string name;
        int age;
    };
    myVector<Person> personVec;
    personVec.reserve(3);
    personVec.push_back({"John", 20});
    personVec.push_back({"Jane", 25});
    personVec.push_back({"Bob", 30});
    personVec.pop_back();
    personVec.insert(0, {"Alice", 35});
    personVec.erase(2);
    personVec.push_back({"Steve", 40});
    // this should trigger a resize, doubling capacity to 6
    personVec.push_back({"Bill", 45});
    std::cout << "------Struct Test------" << std::endl;
    std::cout << "vector size: " << personVec.size() << std::endl;
    std::cout << "vector capacity: " << personVec.capacity() << std::endl;
    for(size_t i = 0; i < personVec.size(); i++){
        std::cout << personVec[i].name << " " << personVec[i].age << std::endl;
    }
    // expected output: 
    // vector size: 4
    // vector capacity: 6
    // Alice 35 John 20 Steve 40 Bill 45
    std::cout << std::endl;
}

void copyTest(){
    // -----------------------Copy Tests-----------------------
    myVector<int> copyVec;
    copyVec.reserve(10);
    for(size_t i = 0; i < 10; i++){
        copyVec.push_back(i);
    }
    // copy vector
    myVector<int> copiedVec = copyVec;
    // remove last element
    copiedVec.pop_back();
    // insert 10 at index 0
    copiedVec.insert(0, 10);
    // remove element at index 2
    copiedVec.erase(2);
    // add 11 and 12 to back
    copiedVec.push_back(11);
    // this should trigger a resize, doubling capacity to 20
    copiedVec.push_back(12);
    std::cout << "------Copy Test------" << std::endl;
    std::cout << "vector size: " << copyVec.size() << std::endl;
    std::cout << "vector capacity: " << copyVec.capacity() << std::endl;
    for(size_t i = 0; i < copyVec.size(); i++){
        std::cout << copyVec[i] << " ";
    }
    // expected output: 
    // vector size: 10
    // vector capacity: 10
    // 0 1 2 3 4 5 6 7 8 9
    std::cout << std::endl;
    std::cout << "copied vector size: " << copiedVec.size() << std::endl;
    std::cout << "copied vector capacity: " << copiedVec.capacity() << std::endl;
    for(size_t i = 0; i < copiedVec.size(); i++){
        std::cout << copiedVec[i] << " ";
    }
    // expected output: 
    // copied vector size: 11
    // copied vector capacity: 20
    // 10 0 2 3 4 5 6 7 8 11 12
    std::cout << std::endl;
}

int main(){
    intTest();
    structTest();
    // copyTest();
    return 0;
}