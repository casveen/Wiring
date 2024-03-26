#ifndef _WiringHPP
#define _WiringHPP


template <int wires>
class Wiring {
    private:
        const int _wires;
        bool connections[wires][wires]; //boolean array.
        int direct_connections[wires];  //points to the ROW(or wire) that a wire is connected directly to.
        int connection_count[wires];    //count how many connectios are to a particular wire. NOTE only valid for common wires

    public:
        constexpr Wiring() : _wires{wires} {
            //initialize values, ensure every wire is connected to itself
            for (int i=0; i<wires; i++) {
                for (int j=0; j<wires; j++) {
                    connections[i][j] = false;
                }
                connections[i][i] = true;
                direct_connections[i] = i;
            }
        }
        int get_common_wire(const int wire) const;
        void connect(const int wire_i, const int wire_j);
        bool is_connected(const int wire_i, const int wire_j) const;
        const bool* get_connections(const int wire) const;

        const bool is_symmetric() const;
        const bool is_transitive() const;
};

#include "wiring.inl"

#endif