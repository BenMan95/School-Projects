#include <iostream>
using namespace std;

class Duck {
  private:
    string name;
    string type;
    string color;
    Duck *mother;
  public:
    Duck();
    Duck(string name, string type, string color);
    Duck(string name, string type, string color, Duck *mother);

    Duck *give_birth(string name);
    string get_name();
    string get_type();
    string get_color();
    Duck *get_mother();
    void print_all();
};
