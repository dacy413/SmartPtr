#include <memory>
#include <iostream>

class Test
{
private:
    int age;
    std::string name;

public:
    Test()
    {
        std::cout << "Call construct" << std::endl;
    }
    ~Test()
    {
        std::cout << "Call deconstruct" << std::endl;
    }
    Test(const Test& t)
    {
        name = t.name;
        age = t.age;
        std::cout << "Call copy construct" << std::endl;
    }
    Test& operator =(const Test& t)
    {
        name = t.name;
        age = t.age;
        std::cout << "Call = operator" << std::endl;
        return (*this);
    }
    void showYourself()
    {
        std::cout <<"My name is "<< name.c_str() << ",I'm " << age << " years." << std::endl;
    }
    bool setAge(int t_age)
    {
        age = t_age;
        return 1;
    }
    bool setName(std::string t_name)
    {
        name = t_name;
        return 1;
    }
};

std::unique_ptr<Test> test(Test t)
{
    std::unique_ptr<Test> p_t( new Test(t)) ;
    t.showYourself();
    p_t->setAge(25);
    return p_t;
}

int main()
{
    Test t;
    t.setName("Daisy");
    t.setAge(24);
    std::unique_ptr<Test> tp1(std::move(test(t)));
    {
        Test t2;
        t2 = *tp1.get();
        t2.showYourself();
    }
    tp1.release();
    t.~Test();
    std::unique_ptr<Test> tp3(new Test());
    //下面两种形式就是不可以
    //std::unique_ptr<Test> tp4(tp3);
    //std::unique_ptr<Test> tp5 = tp3;
    std::cout << "END..." << std::endl;
    return 1;
}
