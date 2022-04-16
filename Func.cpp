#include "myStruct.h"
#include "Func.h"

int parseItem(const std::string &request){
    size_t start = 0;
    size_t last = start;
    std::vector<std::string> parseWords;
    while((last = request.find("-", start)) != std::string::npos){
        parseWords.push_back(request.substr(start, last - start));
        start = last + 1;
    }
    parseWords.push_back(request.substr(start));
    int ret = 0;
    for(auto &it : parseWords){
        if(it == "DISH"){
            ret |= (1 << DISH);
        }
        else if(it == "BLUEBERRIES"){
            ret |= (1 << BLUEBERRIES);
        }
        else if(it == "ICE_CREAM"){
            ret |= (1 << ICE_CREAM);
        }
        else if(it == "STRAWBERRIES"){
            ret |= (1 << STRAWBERRIES);
        }
        else if(it == "CHOPPED_STRAWBERRIES"){
            ret |= (1 << CHOPPED_STRAWBERRIES);
        }
        else if(it == "DOUGH"){
            ret |= (1 << DOUGH);
        }
        else if(it == "CHOPPED_DOUGH"){
            ret |= (1 << CHOPPED_DOUGH);
        }
        else if(it == "CROISSANT"){
            ret |= (1 << CROISSANT);
        }
        else if(it == "RAW_TART"){
            ret |= (1 << RAW_TART);
        }
        else if(it == "TART"){
            ret |= (1 << TART);
        }
    }
    return ret;
}
int parseItem(const char* str){
    return parseItem(std::string(str));
}

bool matchItem(int item, int request){
    if(item & (~request))
        return false;
    return true;
}

int hashDualCoordinate(Coordinate c1, Coordinate c2){
    return ((c1.x * 20 + c1.y) * 20 + c2.x) * 20 + c2.y;
}