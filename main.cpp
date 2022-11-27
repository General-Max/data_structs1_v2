#include <iostream>
#include "AVLTree.h"
#include "sortingTreeMethods.h"
#include "Player.h"
#include <memory>
#include "Node.h"
#include "twoWayList.h"

int main3(){
    auto p1 = new Player(12, 1, 0, 0, 7, true);
    Node<Player*> n1 = Node<Player*>(p1);
    Node<Player*> n2 = Node<Player*>(p1);
    std::cout << **n1.getData() << std::endl;
    std::cout << **n2.getData() << std::endl;

    p1->updateGoals(5);
    std::cout << **n1.getData() << std::endl;
    std::cout << **n2.getData() << std::endl;
    std::cout << *p1 << std::endl;

    return 0;
}

int main2(){
    AVLTree<Player*, SortById> tree;
   // auto p1 = std::make_shared<Player>(12, 1, 0, 0, 7, true);
    auto p1 = new Player(12, 1, 0, 0, 7, true);
    tree.insert(p1);
    tree.printD(tree.getRoot(), 0);
    //tree.printH(tree.getRoot(), 0);

   // std::cout << tree.find(12);
    //std::cout << tree.find(12)->getData();
    auto *p2 = new Player(15, 1, 2, 0, 6, true);
    tree.insert(p2);
    tree.printD(tree.getRoot(), 0);
   // tree.printH(tree.getRoot(), 0);

    //tree.remove(p1);
    tree.remove(15);
    std::cout << "remove :\n";
    tree.printD(tree.getRoot(), 0);

//    std::cout << tree.find(15) << std::endl;
//    Player* t = *tree.find(15)->getData();
//    std::cout << tree.find(15)->getData()<<std::endl;
//    std::cout << **tree.find(15)->getData()<<std::endl;
    return 0;
}

int checkList(){
    twoWayList<Player*> list;
    auto p1 = new Player(12, 1, 0, 0, 7, true);
    auto p2 = new Player(10, 1, 0, 3, 7, true);
    auto p3 = new Player(15, 1, 0, 6, 7, true);
    auto* n1 = new ListNode<Player*>(p1);
    auto* n2 = new ListNode<Player*>(p2);
    auto* n3 = new ListNode<Player*>(p3);
    auto* n4 = new ListNode<Player*>(p3);
    list.insertAfter(n1);
    list.printList();
    list.insertAfter(n2, n1);
    list.printList();
    list.insertAfter(n3, n1);
    list.printList();
    list.deleteNode(n1);
    list.printList();


    return 0;
}

int main() {
    main2();
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