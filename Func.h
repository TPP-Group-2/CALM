#ifndef FUNC_H
#define FUNC_H

#include <string>

struct Coordinate;

int parseItem(const std::string &request);
int parseItem(const char* str);

bool matchItem(int item, int request);

int hashDualCoordinate(Coordinate c1, Coordinate c2);

#endif /* FUNC_H */