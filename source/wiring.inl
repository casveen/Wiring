#ifndef _WiringINL
#define _WiringINL

#include "wiring.hpp"

template <int wires>
int Wiring<wires>::get_common_wire(const int wire) const {
    //simply get the direct connection (sinc ethis is not a tree structure)
    return direct_connections[wire];
}

template <int wires>
void Wiring<wires>::connect(const int wire_i, const int wire_j) {
    //find common wire of both
    int wire_i_common = get_common_wire(wire_i);
    int wire_j_common = get_common_wire(wire_j);
    int i_wires = connection_count[wire_i_common];
    int j_wires = connection_count[wire_j_common];

    if (i_wires>j_wires) {
        //get all wires for wire j, and connect them to i
        for (int wire =0; wire<_wires; wire++) {
            connections[wire_i_common][wire] = connections[wire_i_common][wire] || connections[wire_j_common][wire];
            if (connections[wire_j_common][wire]) {
                direct_connections[wire] = wire_i_common;
            }
        }
    } else {
        //get all wires for wire j, and connect them to i
        for (int wire =0; wire<_wires; wire++) {
            connections[wire_j_common][wire] = connections[wire_i_common][wire] || connections[wire_j_common][wire];
            if (connections[wire_i_common][wire]) {
                direct_connections[wire] = wire_j_common;
            }
        }
    }
}

template <int wires>
bool Wiring<wires>::is_connected(const int wire_i, const int wire_j) const {
    int wire_i_common = get_common_wire(wire_i);
    return connections[wire_i_common][wire_j];
}

template <int wires>
const bool* Wiring<wires>::get_connections(const int wire) const {
    return connections[get_common_wire(wire)];
}






template <int wires>
const bool Wiring<wires>::is_symmetric() const {
        for (int i = 0;     i < wires; i++) {
            for (int j = 0; j < wires; j++) {
                if (is_connected(i,j) != is_connected(j,i)) {
                    return false;
                }
            }
        }
        return true;
    }

template <int wires>
const bool Wiring<wires>::is_transitive() const {
        for (int i = 0;         i < wires; i++) {
            for (int j = 0;     j < wires; j++) {
                for (int k = 0; k < wires; k++) {
                    //check that if M[i,j]>0, M[j,k]>0, then M[i,k]>0 (but what should the exact values be?)
                    if (is_connected(i,j) && is_connected(j,k) && !is_connected(i,k)) {
                        /*std::cout<<i<<"<->"  <<j<<" and "
                                 <<j<<"<->"  <<k<<" but "
                                 <<i<<"<-/->"<<k<<"\n";*/
                        return false;
                    }
                }
            }
        }
        return true;
    }

#endif