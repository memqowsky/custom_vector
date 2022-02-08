#include <iostream>
#include <array>

class buffer_overflow : public std::exception {

public:

    buffer_overflow() = default;
    const char * what() const noexcept override{
        return "buffer_overflow";
    }
};

template<class T,std::size_t SIZE>
class customVector{

private:

    std::size_t size_ = 0;
    std::array<T, SIZE> data_ = {};

public:

    customVector() = default;
    ~customVector() = default;
    customVector(const customVector& other) = default;
    customVector& operator=(const customVector& other) = default;
    customVector(customVector&& other) = default;
    customVector& operator=(customVector&& other) = default;

    const T& operator[](size_t i) const{

        return data_[i];
    }

    T& operator[](size_t i){

        return data_[i];
    }

    void push_back(const T& t){

        if(size_ >= SIZE){

            throw buffer_overflow{};
        }

        data_[size_++] = t;

    }

    bool empty() const {

        return size_ == 0;
    }

    std::size_t size() const {

        return size_;

    }

    std::size_t max_size(){

        return SIZE;
        
    }

    void show(){

        for(int i=0; i<size_; ++i){

            std::cout<<data_[i]<<" ";

        }

        std::cout<<std::endl;

    }

    void resize(size_t newSize){

        if(newSize < size_){

            size_ = newSize;
        }

        else if(newSize > size_){

            size_ = newSize;

            for(int i=0; i< newSize-size_ ; ++i){

                push_back(T(0));

            }
        }
    }
};

int main(){

    //Creating a custom vector
    customVector<int,5> vec;

    //Checking emptiness
    std::cout<< std::boolalpha << vec.empty() << std::endl;

    //Pushing some values
    for(int i = 0 ; i <4; ++i){

        vec.push_back(i*i);
    }

    //Pushing another value
    vec.push_back(12);    

    //Checking show function
    vec.show();    

    //Checking resize function
    vec.resize(10);
    vec.show();
    
    //Checking size and maxsize functions
    std::cout<< "size: " << vec.size() << std::endl;
    std::cout<< "max size: " << vec.max_size() << std::endl;

    //Checking [] operator
    std::cout<< vec[2] << std::endl;

    return 0;
}
