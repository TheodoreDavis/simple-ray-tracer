#include <inc/v3.h>
using namespace std;

int main() {
    v3 a = v3(1,2,3);

    // Test Accessers
    cout << a[0] << a[1] << a[2];
    cout << " -- Should be 123" << endl;

    a[0] = 5, a[1] = 5, a[2] = 5;
    cout << a[0] << a[1] << a[2];
    cout << " -- Should be 555" << endl;
    a[0] = 1, a[1] = 2, a[2] = 3;

    // Test ostream
    cout << a;
    cout << " -- Should be {1,2,3}" << endl;

    // Test unary operators
    cout << +a;
    cout << " -- Should be {1,2,3}" << endl;
    
    cout << -a;
    cout << " -- Should be {-1,-2,-3}" << endl;

    // Test assignments
    a += v3(1,1,1);
    cout << a;
    cout << " -- Should be {2,3,4}" << endl;

    a -= v3(1,2,1);
    cout << a;
    cout << " -- Should be {1,1,3}" << endl;

    a *= v3(1,2,4);
    cout << a;
    cout << " -- Should be {1,2,12}" << endl;

    a /= v3(1,1,4);
    cout << a;
    cout << " -- Should be {1,2,3}" << endl;

    a *= 5;
    cout << a;
    cout << " -- Should be {5,10,15}" << endl;

    a /= 5;
    cout << a;
    cout << " -- Should be {1,2,3}" << endl;

    // Operations
    cout << a + v3(1,1,1);
    cout << " -- Should be {2,3,4}" << endl;

    cout << a - v3(1,2,1);
    cout << " -- Should be {0,0,3}" << endl;

    cout << a * v3(1,2,4);
    cout << " -- Should be {1,4,12}" << endl;

    cout << a / v3(1,1,4);
    cout << " -- Should be {1,2,0.75}" << endl;

    cout << a * 5;
    cout << " -- Should be {5,10,15}" << endl;

    cout << a / 5;
    cout << " -- Should be {0.2,0.4,0.6}" << endl;
}