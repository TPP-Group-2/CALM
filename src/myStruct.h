#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <vector>
#include <string>

struct Coordinate{
    int x, y;
    Coordinate operator+ (const Coordinate &rhs) const {
        return {x + rhs.x, y + rhs.y};
    }
    Coordinate operator* (const int &rhs) const {
        return {x * rhs, y * rhs};
    }
    bool operator== (const Coordinate &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!= (const Coordinate &rhs) const {
        return !((*this) == rhs);
    }
    bool operator< (const Coordinate &rhs) const {
        return x * x + y * y < rhs.x * rhs.x + rhs.y * rhs.y;
    }
};

template <typename T>
class Matrix {
public:
    Matrix() {};
    Matrix(size_t _h, size_t _w, T _data):
        h(_h), w(_w), data(_h, std::vector<T> (_w, _data)) {};

    std::vector<T>& operator[] (int row) { return data[row]; };
    std::vector<T> operator[] (int row) const { return data[row]; };
    T& operator[] (const Coordinate &rhs) { return data[rhs.x][rhs.y]; };
    T operator[] (const Coordinate &rhs) const { return data[rhs.x][rhs.y]; };

    size_t size() { return data.size(); };

private:
    int h = 0, w = 0;
    std::vector<std::vector<T>> data;
};

constexpr Coordinate dir[8] = {
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1}
};

// equipments
enum Equipment {
    DISH_WASHER,
    WINDOW,
    BLUEBERRIES_CRATE,
    ICE_CREAM_CRATE,
    STRAWBERRIES_CRATE,
    CHOPPING_BOARD,
    DOUGH_CRATE,
    OVEN,
    SIZE_OF_EQUIPMENT
};

// materials
enum class Material: int {
    DISH = 0,
    BLUEBERRIES = 1,
    ICE_CREAM = 2,
    STRAWBERRIES = 3,
    CHOPPED_STRAWBERRIES = 4,
    DOUGH = 5,
    CHOPPED_DOUGH = 6,
    CROISSANT = 7,
    RAW_TART = 8,
    TART = 9
};


#endif /* MYSTRUCT_H */
