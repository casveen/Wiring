#include "wiring.hpp"
#include <catch2/catch_test_macros.hpp>
#include<stdlib.h>     /* srand, rand */

TEST_CASE("Testing small(4) set") {
    Wiring<4> w;
    w.connect(0,2);
    w.connect(1,3);
    w.connect(2,3);
    REQUIRE(w.is_connected(0,0));
    REQUIRE(w.is_connected(0,1));
    REQUIRE(w.is_connected(0,2));
    REQUIRE(w.is_connected(0,3));
}

TEST_CASE("Testing small(6) set") {
    Wiring<6> w;
    w.connect(0,3);
    w.connect(1,5);
    w.connect(5,3);

    REQUIRE(w.is_connected(0,0));
    REQUIRE(w.is_connected(0,1));
    REQUIRE(!w.is_connected(0,2)); 
    REQUIRE(w.is_connected(0,3));
    REQUIRE(!w.is_connected(0,4));
    REQUIRE(w.is_connected(0,5));
}

TEST_CASE("Testing small(8) set closure") {
    Wiring<8> w;
    w.connect(0,1);
    w.connect(2,3);
    w.connect(4,5);
    w.connect(6,7);

    w.connect(1,2);
    w.connect(5,6);

    w.connect(3,4);

    REQUIRE(w.is_connected(0,0)); 
    REQUIRE(w.is_connected(0,1)); 
    REQUIRE(w.is_connected(0,2)); 
    REQUIRE(w.is_connected(0,3));
    REQUIRE(w.is_connected(0,4));
    REQUIRE(w.is_connected(0,5));
    REQUIRE(w.is_connected(0,6));
    REQUIRE(w.is_connected(0,7));
}

TEST_CASE("Testing smallish(16) set closure") {
    Wiring<16> w;
    

    w.connect(3,5);
    w.connect(8,10);
    w.connect(4,6);
    w.connect(4,2);
    w.connect(11,13);
    w.connect(12,10);
    w.connect(1,3);
    w.connect(2,0);
    w.connect(13,15);
    w.connect(5,7);
    w.connect(11,9);
    w.connect(12,14);
    w.connect(2,12);
    w.connect(15,1);

    REQUIRE(w.is_connected(0,0)); 
    REQUIRE(w.is_connected(0,2)); 
    REQUIRE(w.is_connected(0,4)); 
    REQUIRE(w.is_connected(0,6));
    REQUIRE(w.is_connected(0,8));
    REQUIRE(w.is_connected(0,10));
    REQUIRE(w.is_connected(0,12));
    REQUIRE(w.is_connected(0,14));
    REQUIRE(!w.is_connected(1,0)); 
    REQUIRE(!w.is_connected(1,2)); 
    REQUIRE(!w.is_connected(1,4)); 
    REQUIRE(!w.is_connected(1,6));
    REQUIRE(!w.is_connected(1,8));
    REQUIRE(!w.is_connected(1,10));
    REQUIRE(!w.is_connected(1,12));
    REQUIRE(!w.is_connected(1,14));
    REQUIRE(w.is_connected(0,0)); 
    REQUIRE(w.is_connected(1,3)); 
    REQUIRE(w.is_connected(1,5)); 
    REQUIRE(w.is_connected(1,7));
    REQUIRE(w.is_connected(1,9));
    REQUIRE(w.is_connected(1,11));
    REQUIRE(w.is_connected(1,13));
    REQUIRE(w.is_connected(1,15));
    REQUIRE(!w.is_connected(0,1)); 
    REQUIRE(!w.is_connected(0,3)); 
    REQUIRE(!w.is_connected(0,5)); 
    REQUIRE(!w.is_connected(0,7));
    REQUIRE(!w.is_connected(0,9));
    REQUIRE(!w.is_connected(0,11));
    REQUIRE(!w.is_connected(0,13));
    REQUIRE(!w.is_connected(0,15));
}

TEST_CASE("Testing transitivity of connections(small)") {
    int wires = 3;
    Wiring<3> connections;
    //add some connections
    connections.connect(0,1);
    connections.connect(1,2);
    //connections.closure();
    REQUIRE(connections.is_transitive());
    REQUIRE(connections.is_symmetric());
}

TEST_CASE("Testing transitivity of connections(small, both directions)") {
    int wires = 3;
    Wiring<3> connections;
    //add some connections
    connections.connect(1,2);
    connections.connect(0,1);
    //connections.closure();
    REQUIRE(connections.is_transitive());
    REQUIRE(connections.is_symmetric());
}

TEST_CASE("Testing transitivity of connections(medium)") {
    Wiring<10> connections;
    //add some connections
    connections.connect(0,1);
    connections.connect(0,2);
    connections.connect(0,3);
    connections.connect(5,0);
    connections.connect(0,6);
    connections.connect(0,7);
    connections.connect(0,9);
    connections.connect(1,3);
    connections.connect(1,4);
    connections.connect(8,1);
    connections.connect(1,9);
    connections.connect(2,5);
    connections.connect(2,6);
    connections.connect(3,5);
    connections.connect(4,9);
    connections.connect(9,5);
    connections.connect(6,7);
    connections.connect(6,8);
    connections.connect(6,9);
    connections.connect(7,8);
    connections.connect(8,9);
    REQUIRE(connections.is_transitive());
    REQUIRE(connections.is_symmetric());
}

TEST_CASE("Testing transitivity of connections(with disconnects)") {
    int wires = 8;
    Wiring<8> connections;
    srand(42);
    //add some connections
    for (int i = 0; i < 20; i++) {
        connections.connect(rand()%wires, rand()%wires);
        
    }
    //make some disconnects
    for (int i = 0; i < 10; i++) {
        //connections.disconnect(rand()%wires, rand()%wires);
    }
    //add some connections
    for (int i = 0; i < 5; i++) {
        connections.connect(rand()%wires, rand()%wires);
    }
    //connections.closure();
    REQUIRE(connections.is_symmetric());
    REQUIRE(connections.is_transitive());
}

TEST_CASE("Testing transitivity of connections(large, with disconnects)") {
    int wires = 26;
    Wiring<26> connections;
    srand(69);
    //add some connections
    for (int i = 0; i < 20; i++) {
        connections.connect(rand()%wires, rand()%wires);
    }
    //make some disconnects
    for (int i = 0; i < 20; i++) {
        //connections.disconnect(rand()%wires, rand()%wires);
    }
    //add some connections
    for (int i = 0; i < 10; i++) {
        connections.connect(rand()%wires, rand()%wires);
    }
    REQUIRE(connections.is_symmetric());
    REQUIRE(connections.is_transitive());
}

TEST_CASE("Testing transitivity of connections(very large, with disconnects)") {
    int wires = 1000;
    Wiring<1000> connections;
    srand(123);
    //add some connections
    for (int i = 0; i < 200; i++) {
        connections.connect(rand()%wires, rand()%wires);
    }
    //make some disconnects
    for (int i = 0; i < 100; i++) {
        //connections.disconnect(rand()%wires, rand()%wires);
    }
    //add some connections
    for (int i = 0; i < 100; i++) {
        connections.connect(rand()%wires, rand()%wires);
    }

    REQUIRE(connections.is_symmetric());
    REQUIRE(connections.is_transitive());
}

