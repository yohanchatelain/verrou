
#include<iostream> 
#include<math.h> 

int main(int argc, char** argv){

  double a(0.1);
  float af(0.1);
  
  std::cout << "diff cos: " <<  cos(a) -cos(a) << std::endl;
  std::cout << "diff cosf: " <<  cosf(af) -cosf(af) << std::endl;
  
  
  
};
