#ifndef CHEF_H
#define CHEF_H

struct Coordinate;
class Kitchen;

class Chef {
public:
    Chef();
    Chef(const Kitchen& _kitchen);
    
    void changeKitchen(const Kitchen& _kitchen);

    Coordinate& getPos();
    Coordinate getPos() const;
    int& getItem();
    int getItem() const;
    int& getTarget();
    int getTarget() const;
    int required() const;

    Coordinate find(const Coordinate& partnerPos, int target) const;
    Coordinate find(const Chef& partner, int target) const;
    
    bool want(int dishes) const;
    bool has(int dishes) const;

private:
    Coordinate pos;
    int carriedItem = 0;
    int targetOrder = 0;
    
    const Kitchen* kitchen;
};

#endif /* CHEF_H */