#include <iostream>
#include <string>
#include <sstream>

template<typename T>
class Vector {
public:
    Vector()
    {
        Resize(2);
    }

    void push(const T& element)
    {
        if (size_ >= capacity_)
            Resize(capacity_ * 2);

        elements_[size_++] = element;
    }

    T pop()
    {
        if (size_ > 0)
        {
            T temp = elements_[--size_];
            elements_[size_] = NULL;
            capacity_ = size_;
            Resize(capacity_);
            if (capacity_ == 0)
            {
                Resize(2);
            }
            return temp;
        }
        else
        {
            throw "error";
        }
    }

    T at_i (size_t i)
    {
        T temp = elements_[i];
        return temp;
    }

    size_t size() const {return size_;}

    size_t capacity() const {return capacity_;}

    void Clear()
    {
        if (size_ != 0)
        {
            for (size_t i=0; i<= size_; i++)
            {
                elements_[i] = NULL;
            }
        }
        size_ = 0;
        Resize(1);
    }

    void Exit()
    {
        std:: cout << "bye"<<std::endl;
        std::exit(0);
    }

    void Resize(size_t new_capacity)
    {
        T* new_memory = new T[new_capacity];
        for (size_t i = 0; i <size_; i++)
            new_memory[i] = elements_[i];
        delete[] elements_;
        elements_ = new_memory;
        capacity_ = new_capacity;
        if (capacity_ < size_)
        {
            size_ = capacity_;
        }

    }
    ~Vector()
    {
        delete[] elements_;
    }

private:
    int n_;
    T* elements_ = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;

};


int main()
{
    Vector<int> my_vector;
    std::string input, input1[2], word;

    while (1 == 1)
    {
        std::getline(std::cin, input);
        std::stringstream X(input);
        int i = 0;
        while (std::getline(X, word,' '))
            input1[i++] = word;

       if(input1[0] == "exit")
        {
            std::cout<< "bye"<<std::endl;
            break;
        }
        else if(input1[0] == "push")
        {
            int n = 0;
            for (int i = 0; i< input.size(); i++)
                if (input[i] >= '0' && input[i]<= '9')
                {
                    n *= 10;
                    n += int(input[i]) - 48;
                }
            my_vector.push(n);
            std::cout << "ok"<<std::endl;
        }
        else if(input1[0] == "pop")
        {
            try{
                std::cout << my_vector.pop() <<std::endl;
            } catch(char const*){
                std::cout << "error" << std::endl;
            }
            continue;
        }
        else if(input1[0] == "at")
        {
            int n = 0;
            for (int i = 0; i< input.size(); i++)
                if (input[i] >= '0' && input[i]<= '9')
                {
                    n *= 10;
                    n += int(input[i]) - 48;
                }
            if (n < my_vector.size())
                std::cout<< my_vector.at_i(n) << std::endl;
            else
                std::cout<< "error"<<std::endl;
        }
        else if(input1[0] == "capacity")
            std::cout<< my_vector.capacity()<<std::endl;
        else if(input1[0] == "clear")
        {
            my_vector.Clear();
            std:: cout << "ok"<<std::endl;
        }
        else if(input1[0] == "size")
            std::cout<< my_vector.size()<<std::endl;
        else if(input1[0] == "resize")
        {
            int n = 0;
            for (int i = 0; i< input.size(); i++)
                if (input[i] >= '0' && input[i]<= '9')
                {
                    n *= 10;
                    n += int(input[i]) - 48;
                }
            my_vector.Resize(n);
            std::cout<< "ok"<<std::endl;
        }
        else
            break;
    }
    return 0;
}
