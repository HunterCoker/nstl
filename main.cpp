#include <iostream>

#include <nstl/timer.h>
#include <nstl/linked_list.h>
#include <nstl/graph.h>

int main() {
    double id, elapsed;
//
//    nstl::directed_graph<int> graph;
//
//
//    // depth first search
//    graph.dfs([](int value) {
//        std::cout << value << std::endl;
//    });
//
//    // breadth first search
//    graph.bst([](int value) {
//       std::cout << value << std::endl;
//    });


    nstl::singly_linked_list<int> linkedList;
    for (int i = 0; i < 10; ++i) {
        linkedList.append(i);
    }
    linkedList.remove(2);


    linkedList.traverse([](int value) {
       std::cout << value << std::endl;
    });

    return 0;
}
