#include "myStruct.h"
#include "Kitchen.h"
#include "Chef.h"

Chef::Chef(const Kitchen& _kitchen) : kitchen(&_kitchen) {

}

void Chef::changeKitchen(const Kitchen& _kitchen){
    kitchen = &_kitchen;
}

Coordinate& Chef::getPos(){
    return pos;
}
Coordinate Chef::getPos() const {
    return pos;
}
int& Chef::getItem(){
    return carriedItem;
}
int Chef::getItem() const {
    return carriedItem;
}
int& Chef::getTarget(){
    return targetOrder;
}
int Chef::getTarget() const {
    return targetOrder;
}

Coordinate Chef::find(const Coordinate& partnerPos, int target) const {
    if(target != 0)
        return kitchen->nearestItem(pos, partnerPos, target);
    
    return kitchen->nearestTable(pos, partnerPos);
}
Coordinate Chef::find(const Chef& partner, int target) const {
    return find(partner.getPos(), target);
}

int Chef::required() const {
    return (carriedItem & targetOrder) ^ targetOrder;
}
bool Chef::want(int dishes) const {
    return targetOrder & (1 << dishes);
}
bool Chef::has(int dishes) const {
    return carriedItem & (1 << dishes);
}