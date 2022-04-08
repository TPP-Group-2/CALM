#ifndef KITCHEN_H
#define KITCHEN_H

#include <vector>
#include <map>
#include <unordered_map>
#include "myStruct.h"

class Chef;

class Kitchen {
public:
    Kitchen();
    Kitchen(const std::vector<std::string> &v);
    Kitchen(const std::string str[]);
    
    Coordinate locate(Equipment en) const;
    std::vector<Coordinate> search(Material item) const;
    Coordinate nearestItem(const Coordinate &pos, const Coordinate &partnerPos, int item) const;
    Coordinate nearestTable(const Coordinate &pos, const Coordinate &partnerPos) const;
    int distance(const Coordinate &src, const Coordinate &dest, const Coordinate &block) const;

    bool isWalkable(const Coordinate &pos) const;

    void clearTable();
    void setTable(int item, const Coordinate &pos);

private:
    Matrix<char> room = Matrix<char> (7, 11, '#');

    std::vector<Coordinate> eq = std::vector <Coordinate> (SIZE_OF_EQUIPMENT);
    Matrix<int> table = Matrix<int> (7, 11, 0);
    std::unordered_map<int, std::vector<Coordinate>> mt;
    static std::map <int, Matrix<int>> dis;
};

#endif /* KITCHEN_H */