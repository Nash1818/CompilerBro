// implements the token's struct method:

#include "token.h"

void Token:: print() const{
        std::cout << "Token (Type: " << static_cast<int>(type) << ", Value: " << value << "')\n";
}