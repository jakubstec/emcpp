#include "../utils.h"
#include <initializer_list>

class Vector {
    int len;
    double *data;
public:
    Vector() : data(nullptr), len(0) {
        log("Default ctr");
    }

    Vector(std::initializer_list<double> l) : len(l.size()), data(new double[l.size()]) {
        log("Init list ctr");
        int i = 0;
        for(auto x: l) {
            data[i] = x;
            ++i;
        }
    }
    
    Vector(const Vector &v) : len(v.len), data(new double[v.len]) {
        log("Copy ctr");
        for(int i = 0; i < len; ++i) {
            data[i] = v.data[i];
        }
    }

    Vector(Vector &&v) : len(v.len), data(v.data) {
        log("Move ctr");
        v.data = nullptr;
        v.len = 0;
    }

    Vector& operator=(const Vector &v) {
        log("Copy assignment op");
        if(this != &v) {
            auto new_data = new double[v.len];
            for(int i = 0; i < v.len; ++i) {
                new_data[i] = v.data[i];
            }
            delete[] this->data;
            this->len = v.len;
            this->data = new_data;
        }
        return *this;
    }

    #ifdef MOVE
    Vector& operator=(Vector &&v) {
        if(&v != this) {
            log("Move assignment op");
            delete[] this->data;
            this->data = v.data;
            this->len = v.len;
            v.data = nullptr;
            v.len = 0;
        }
        return *this;
    }
    #endif

    ~Vector() {
        log("Dtr");
        if(data) delete[] data;
    }

    void zero() {
        for(int i = 0; i < len; ++i) data[i] = 0;
    }

    Vector copy() {
        return Vector(*this);
    }

    friend std::ostream& operator<<(std::ostream &o, const Vector &v) {
        for(int i = 0; i < v.len; ++i) {
            o << v.data[i] << " ";
        }
        return o;
    }
};

int main() {
    Vector v({1, 2, 3, 4, 5, 6, 7, 8, 9});
    print("v", ' '); print(v);
    //Vector w = Vector({5, 6, 7}); // copy ellision
    {
    auto m = Measure("Does move make things faster?");
    for(int i = 0; i < 10000000; ++i) {
        v = v.copy();
    }
    }
    print("v", ' '); print(v);
}
