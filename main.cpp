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
    world.add_player(21, 1, 0, 1, 20, true);
    world.add_player(25, 1, 1, 1, 20, false);
    world.add_player(3, 1, 1, 1, 5, false);
    world.add_player(4, 2, 1, 1, 1, false);
    world.add_player(5, 2, 1, 2, 5, false);
    world.add_player(6, 2, 2, 2, 4, true);
    world.add_player(24, 1, 1, 2, 3, true);
    world.add_player(7, 1, 1, 2, 2, true);
    world.add_player(8, 1, 1, 2, 1, true);
    world.add_player(9, 1, 1, 5, 30, true);
    world.add_player(10, 1, 1, 5, 29, true);
    world.add_player(11, 1, 1, 5, 28, true);
    world.add_player(12, 1, 1, 5, 27, true);
    world.add_player(51, 1, 1, 6, 40, true);
    world.add_player(52, 1, 1, 6, 40, true);
    world.add_player(53, 1, 1, 6, 40, true);
    world.add_player(54, 1, 1, 6, 10, true);
    world.add_player(60, 1, 1, 6, 5, true);
    world.add_player(70, 1, 1, 6, 4, true);
    world.add_player(100, 1, 1, 8, 6, true);
    world.add_player(80, 1, 1, 10, 7, true);
    world.add_player(90, 1, 1, 10, 7, true);
    world.play_match(1,2);
    world.update_player_stats(10, 0, 5, 29);
    world.remove_player(11);
    world.get_top_scorer(1);
}

void check(){
    auto *p = new Player(21, 1, 0, 1, 20, true);
    Player *p2 = p;
    BinNode<Player*>* b1 = new BinNode<Player*>(p);
    BinNode<Player*>* b2 = new BinNode<Player*>(p);
    delete b1;
    std::cout << p << std::endl;
    delete p;
    bool exist = p==nullptr;
    std::cout << exist;
    std::cout << p;
    int n=5;
    //int arr[]= new int(n);
    int* ptr = (int*) malloc(n*sizeof(int));

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