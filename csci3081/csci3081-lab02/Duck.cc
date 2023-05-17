#include <iostream>
#include "Duck.h"

Duck::Duck() {
  this->name = "Unknown";
  this->type = "Unknown";
  this->color = "Unknown";
  this->mother = NULL;
}
Duck::Duck(string name, string type, string color) {
  this->name = name;
  this->type = type;
  this->color = color;
  this->mother = NULL;
}
Duck::Duck(string name, string type, string color, Duck *mother) {
  this->name = name;
  this->type = type;
  this->color = color;
  this->mother = mother;
}

Duck *Duck::give_birth(string name) {
  return new Duck(name, type, color, this);
}

string Duck::get_name() {return name;}
string Duck::get_type() {return type;}
string Duck::get_color() {return color;}
Duck* Duck::get_mother() {return mother;}

void Duck::print_all() {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Type: " << type << std::endl;
  std::cout << "Color: " << color << std::endl;
  if(mother){
    std::cout << "Mother's Name: " << mother->get_name() << std::endl;
    std::cout << "Mother's Type: " << mother->get_type() << std::endl;
    std::cout << "Mother's Color: " << mother->get_color() << std::endl;
  } else {
    std::cout << "Mother: Unknown" << std::endl;
  }
  std::cout << "-------------------------" << std::endl;
}
