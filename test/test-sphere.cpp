#include <inc/sphere.h>
#include <iostream>
using namespace std;

int main() {
    //sphere at {4,2,0} with radius 2
    sphere a = sphere(v3(4,2,0), 2);

    cout << "Testing Shape getColor()" << endl;
    cout << a.getColor();
    cout << " should be {0.392, 0.584, 0.929}" << endl << endl;

    cout << "Testing rayIntersections" << endl;
    //origin to cast rays from
    v3 o = v3(0,0,0);

    cout << a.rayIntersections(o, v3(1,0,0));
    cout << " should be 1" << endl;

    cout << a.rayIntersections(o, v3(7,2,0));
    cout << " should be 2" << endl;

    cout << a.rayIntersections(o, v3(2,4,0));
    cout << " should be 0" << endl << endl;

    cout << "Testing rayIntersectionPoint with 1 intersection" << endl;
    cout << a.rayIntersectionPoint(o, v3(1,0,0));
    cout << " should be {4,0,0}" << endl << endl;

    cout << "Testing rayIntersectionPoint with 2 intersections" << endl;
    cout << a.rayIntersectionPoint(o, v3(7,2,0));
    cout << " should be {2.474,0.707,0}" << endl << endl;

    cout << "Testing rayIntersectionPoint with 0 intersections" << endl;
    cout << a.rayIntersectionPoint(o, v3(2,4,0));
    cout << " should be {0,0,0}" << endl << endl;

}
