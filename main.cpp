#include <iostream>
#include "AVLTree.h"
#include "SortById.h"
#include "Player.h"
#include <memory>
#include "Node.h"
#include "twoWayList.h"
#include "worldcup23a1.h"
#include "wet1util.h"

void checkAddPlayer(){
    world_cup_t world;
    world.add_team(1, 0);
    world.add_team(2, 0);
    world.add_player(10, 1, 0, 0, 0, true);
    world.add_player(11, 1, 1, 2, 0, false);
    world.add_player(12, 2, 1, 2, 1, false);
}

int main() {
    checkAddPlayer();
    return 0;
}


//std::cout << "enter values" << std::endl;
//for(int i=0; i<7; i++){
//std::cin >> val;
//tree.insert(val);
//tree.printD(tree.getRoot(), 0);
//tree.printH(tree.getRoot(), 0);
//std::cout << "---------------";
//}
//
//
//std::cout << "enter values to delete" << std::endl;
//for(int i=0; i<7; i++){
//std::cin >> val;
//tree.remove(val);
//tree.printD(tree.getRoot(), 0);
//tree.printH(tree.getRoot(), 0);
//std::cout << "---------------";
//}