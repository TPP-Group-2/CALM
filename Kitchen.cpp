#include <queue>
#include "Kitchen.h"
#include "Func.h"

std::map<int, Matrix<int>> Kitchen::dis;

Kitchen::Kitchen(const std::vector<std::string> &v){
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 11; ++j){
            if(v[i][j] != '0' && v[i][j] != '1')
                room[i][j] = v[i][j];
            switch(v[i][j]){
            case '0':
                room[i][j] = '.';
                break;
            case '1':
                room[i][j] = '.';
                break;
            case 'D':
                eq[DISH_WASHER] = {i, j};
                break;
            case 'W':
                eq[WINDOW] = {i, j};
                break;
            case 'B':
                eq[BLUEBERRIES_CRATE] = {i, j};
                break;
            case 'I':
                eq[ICE_CREAM_CRATE] = {i, j};
                break;
            case 'S':
                eq[STRAWBERRIES_CRATE] = {i, j};
                break;
            case 'C':
                eq[CHOPPING_BOARD] = {i, j};
                break;
            case 'H':
                eq[DOUGH_CRATE] = {i, j};
                break;
            case 'O':
                eq[OVEN] = {i, j};
                break;
            
            default:
                break;
            }
        }
    }

    if(!Kitchen::dis.empty()){
        return;
    }

    // calculate all pair shortest path 
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 11; ++j){
            for(int k = 0; k < 7; ++k){
                for(int l = 0; l < 11; ++l){
                    Coordinate p1 = {i, j}, p2 = {k, l};
                    if(!isWalkable(p1) || !isWalkable(p2)){
                        continue;
                    }
                    
                    int key = hashDualCoordinate(p1, p2);

                    Kitchen::dis[key] = Matrix<int> (7, 11, 2e9);
                    std::priority_queue <std::pair<int, Coordinate>,
                                        std::vector<std::pair<int, Coordinate>>,
                                        std::greater<std::pair<int, Coordinate>>>  pq;
                    pq.push({0, p1});
                    
                    Kitchen::dis[key][p1] = 0;
                    std::vector<std::vector<bool>> vis(7, std::vector<bool> (11, false));
                    while(!pq.empty()){
                        if(!pq.empty() && vis[pq.top().second.x][pq.top().second.y]){
                            pq.pop();
                        }
                        if(pq.empty()){
                            break;
                        }
                        int d = pq.top().first;
                        Coordinate now = pq.top().second;
                        vis[now.x][now.y] = true;
                        for(int p = 0; p < 8; ++p){
                            Coordinate next = now + dir[p];
                            if(isWalkable(next)){
                                if(next != p2
                                    && !vis[next.x][next.y]
                                    && d + 1 < Kitchen::dis[key][next]
                                    && p % 2 == 0){
                                    Kitchen::dis[key][next] = d + 1;
                                    pq.push({d + 1, next});
                                }
                            }
                            else{
                                if(d + 4 < Kitchen::dis[key][next]){
                                    Kitchen::dis[key][next] = d + 4;
                                }
                            }
                        }
                    }
                    // change path length to turn consumed
                    for(int p = 0; p < 7; ++p){
                        for(auto &it : Kitchen::dis[key][p]){
                            it = (it + 3) / 4;
                        }
                    }
                }
            }
        }
    }
}
Kitchen::Kitchen(const std::string str[]){
    Kitchen tmp(std::vector<std::string> (str, str + 7));
    (*this) = tmp;
}

std::vector<Coordinate> Kitchen::search(Material item) const {
    if(mt.find(item) != mt.end()){
        return mt.at(item);
    }
    return std::vector<Coordinate> ();
}
Coordinate Kitchen::locate(Equipment en) const {
    return eq[en];
}

Coordinate Kitchen::nearestItem(const Coordinate &pos, const Coordinate &partnerPos, int item) const {
    if(mt.find(item) != mt.end()){
        int minimum = 2e9;
        Coordinate ret;
        for(auto &it : mt.at(item)){
            if(distance(pos, it, partnerPos) < minimum){
                ret = it;
                minimum = distance(pos, it, partnerPos);
            }
        }
        return ret;
    }
    return {-1, -1};
}

Coordinate Kitchen::nearestTable(const Coordinate &pos, const Coordinate &partnerPos) const {
    std::queue <Coordinate> q;
    q.push(pos);
    std::vector <std::vector<bool>> vis(7, std::vector<bool> (11, false));
    while(!q.empty()){
        while(!q.empty() && vis[q.front().x][q.front().y]){
            q.pop();
        }
        if(q.empty())
            break;
        Coordinate now = q.front();
        vis[now.x][now.y] = true;
        for(auto &d : dir){
            Coordinate next = now + d;
            if(next.x < 0 || next.x >= 7 || next.y < 0 || next.y >= 11){
                continue;
            }
            if(vis[next.x][next.y])
                continue;
            if(table[pos + d] == 0 && room[pos + d] == '#')
                return next;
            q.push(next);
        }
    }
    return {-1, -1};
}

bool Kitchen::isWalkable(const Coordinate &pos) const {
    return room[pos] == '.';
}

void Kitchen::clearTable(){
    for(auto &it : mt){
        for(auto &c : it.second){
            table[c] = 0;
        }
        it.second.clear();
    }
    if(!mt.empty())
        mt.clear();
    return;
}
void Kitchen::setTable(int item, const Coordinate &pos){
    table[pos] = item;
    if(mt.find(item) == mt.end()){
        mt[item] = std::vector<Coordinate> ();
    }
    mt[item].push_back(pos);
    return;
}

int Kitchen::distance(const Coordinate &src, const Coordinate &dest, const Coordinate &partnerPos) const {
    int key;
    if(partnerPos.x == -1){
        key = hashDualCoordinate(src, src);
    }
    else{
        key = hashDualCoordinate(src, partnerPos);
    }
    return Kitchen::dis[key][dest];
}

