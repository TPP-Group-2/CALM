#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <cstring>
#include <unordered_map>
#include "CalmClam.h"

int main(){
    int allCustomers;
    std::cin >> allCustomers; std::cin.ignore();
    for(int i = 0; i < allCustomers; i++){
        std::string item;
        int award;
        std::cin>>item>>award; std::cin.ignore();
        // using parseItem to change item string to item data
        // we won't use pre-order data in this example code
        int itemData = parseItem(item);
    }

    std::vector<std::string> v;
    for (int i = 0; i < 7; ++i) {
        std::string kitchen_line;
        std::getline(std::cin, kitchen_line);
        v.push_back(kitchen_line);
    }

    Kitchen kitchen(v);
    std::vector<Chef> player(2, Chef(kitchen));

    // alternative way without using std::vector

    // std::string str[7];
    // for(int i = 0; i < 7; ++i){
    //     std::getline(std::cin, str[i]);
    // }

    // Kitchen kitchen(str);
    // Chef player[2] = {Chef(kitchen), Chef(kitchen)};

    enum Phase {
        THINKING,
        MAKING_STRAWBERRIES,
        GATHERING,
        SEND_DISH
    } phase = THINKING;

    // set player target as nothing
    player[0].getTarget() = 0;

    // game loop
    while(1){
        int remainTurns;
        std::cin >>remainTurns; std::cin.ignore();
        for(int i = 0; i < 2; i++){
            Coordinate pos;
            std::string item;
            std::cin>>pos.y>>pos.x>>item; std::cin.ignore();
            
            // set player information in current turn
            player[i].getPos() = pos;
            player[i].getItem() = parseItem(item);
        }
        int tableItems; // the number of tables in the kitchen that currently hold an item
        std::cin>>tableItems; std::cin.ignore();

        // reset current table items
        kitchen.clearTable();
        for(int i = 0; i < tableItems; i++){
            int table_x;
            int table_y;
            std::string item;
            std::cin >> table_y >> table_x >> item; std::cin.ignore();
            kitchen.setTable(parseItem(item), {table_x, table_y});
        }

        // set source materials location
        kitchen.setTable(1 << DISH, kitchen.locate(DISH_WASHER));
        kitchen.setTable(1 << BLUEBERRIES, kitchen.locate(BLUEBERRIES_CRATE));
        kitchen.setTable(1 << ICE_CREAM, kitchen.locate(ICE_CREAM_CRATE));
        kitchen.setTable(1 << STRAWBERRIES, kitchen.locate(STRAWBERRIES_CRATE));
        kitchen.setTable(1 << DOUGH, kitchen.locate(DOUGH_CRATE));

        std::string ovenContent; // ignore until wood 1 league
        int ovenTimer;
        std::cin>>ovenContent>>ovenTimer; std::cin.ignore();

        // if oven content can be took
        if(ovenContent != "NONE" && ovenContent != "DOUGH" && ovenContent != "RAW_TART")
            kitchen.setTable(parseItem(ovenContent), kitchen.locate(OVEN));

        int num_customers; // the number of customers currently waiting for food
        std::cin>>num_customers; std::cin.ignore();

        std::unordered_map<int, int> order;
        for(int i = 0; i < num_customers; i++){
            std::string request;
            int award;
            std::cin>>request>>award; std::cin.ignore();
            int item = parseItem(request);
            order.insert({item, award});
        }
        
        // get players' information
        Chef &chef = player[0];
        Chef &partner = player[1];
        Coordinate &pos = chef.getPos(); // won't use in this example code
        int &targetOrder = chef.getTarget();
        int &carriedItem  = chef.getItem();

        // if target order is not in order board anymore
        if(order.find(targetOrder) == order.end()){
            // set another target
            targetOrder = order.begin()->first;
            for(auto &it : order){
                if(it.first > targetOrder && matchItem(it.first, targetOrder))
                    targetOrder = it.first;
            }
        }

        do {
            switch (phase) {
            case MAKING_STRAWBERRIES:
                if(chef.has(CHOPPED_STRAWBERRIES))
                    phase = THINKING;
                break;
            case GATHERING:
                phase = THINKING;
                break;
            case SEND_DISH:
                phase = THINKING;
                break;

            default:
                // want && don't have && can't find on table
                if(chef.want(CHOPPED_STRAWBERRIES)
                    && (!chef.has(CHOPPED_STRAWBERRIES))
                    && chef.find(partner, 1 << CHOPPED_STRAWBERRIES).x == -1){
                    phase = MAKING_STRAWBERRIES;
                }
                if(phase == THINKING){
                    if(!matchItem(carriedItem, targetOrder) || carriedItem == targetOrder){
                        phase = SEND_DISH;
                    }
                    else{
                        phase = GATHERING;
                    }
                }
                break;
            }
        } while(phase == THINKING);

        switch (phase) {
        Coordinate dest;
        case MAKING_STRAWBERRIES:
            // if carring something not strawberries
            if(carriedItem != 0 && carriedItem != (1 << STRAWBERRIES)){
                // find nearest empty table
                dest = chef.find(partner, 0);
                std::cout<<"USE "<<dest.y<<" "<<dest.x<<"; place dish"<<std::endl;
                break;
            }
            // if not holding anything
            else if(carriedItem == 0){
                // find nearest strawberries
                dest = chef.find(partner, 1 << STRAWBERRIES);
                std::cout<<"USE "<<dest.y<<" "<<dest.x<<"; get strawberries"<<std::endl;
                break;
            }
            // if holding strawberries
            else{
                // find chopping board
                dest = kitchen.locate(CHOPPING_BOARD);
                std::cout<<"USE "<<dest.y<<" "<<dest.x<<"; chop strawberries"<<std::endl;
                break;
            }
            break;
        case GATHERING:{
            bool isGathering = false;
            // find a table item which can combine with your carried item
            int lack = chef.required();
            for(int i = lack; i >= 1; i = lack & (i - 2)){
                dest = chef.find(partner, i);
                if(dest.x != -1){
                    isGathering = true;
                    std::cout<<"USE "<<dest.y<<" "<<dest.x<<"; gathering"<<std::endl;
                    break;
                }
                if(i == 1){
                    break;
                }
            }
            if(!isGathering){
                std::cout<<"WAIT; nothing to do"<<std::endl;
            }
            break;
        }
        case SEND_DISH:
            // find serving window
            dest = kitchen.locate(WINDOW);
            std::cout<<"USE "<<dest.y<<" "<<dest.x<<"; serve dish"<<std::endl;
            break;

        default:
            std::cout<<"WAIT; nothing to do"<<std::endl;
            break;
        }
    }
}
