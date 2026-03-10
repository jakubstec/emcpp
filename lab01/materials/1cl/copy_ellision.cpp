#define LOG
#include "../utils.h"

struct Foo {
    Foo() {log("def");}
    Foo(const Foo &f) {log("copy");}
    Foo(Foo &&f) {log("move");}
    ~Foo() {log("dtr");}
};

Foo no_rvo(int x) {
    if(x == 1) {
        Foo f;
        return f;
    }
    else {
        Foo f;
        return f;
    }
}

Foo rvo(int x) {
    if(x == 1) {
        return Foo();
    }
    else {
        return Foo();
    }
}

Foo rvo2(int x) {
    Foo f;
    if(x == 1) {
        return f;
    }
    else {
        return f;
    }
}

int main() {
    Foo f1 = no_rvo(1); // move constructs, if there is no move ctr the copy constructs
    Foo f2 = rvo(1); // rvo copy ellision
    Foo f3 = rvo2(1); // rvo copy ellision

}

