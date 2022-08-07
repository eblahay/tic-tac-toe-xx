#include <tic-tac-toe++/validators.hxx>

bool validators::inputCoordValidator(std::string input){
    bool result = false;

    if(input.find(',') != std::string::npos){
        try{
            int x = std::stoi(input.substr(0, input.find(','))), y = std::stoi(input.substr(input.find(',')+1));
            result = true;
        }
        catch(std::exception e){
            result = false;
        }
    }

    return result;
}
