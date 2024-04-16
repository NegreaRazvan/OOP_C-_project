#include <string>
using std::string;

class Exception : public std::exception{
public:
    explicit Exception(string msg): message(msg){}
    [[nodiscard]] const char* what() const throw(){
        return message.c_str();
    }
private:
    string message;

};

