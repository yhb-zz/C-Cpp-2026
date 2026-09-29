#include <iostream>
#include <stdexcept>

template <typename T>
class SafeArray {
private:
    int length;
    T *values;

public:
    SafeArray(int len) {
        length = len;
        values = new T[len];
        for (int _ = 0; _ < len; _++) {
            values[_] = (T)0;
        }
    }
    T & operator[](int i) {
        if (i >= 0 && i < length) {
            return values[i];
        } else {
            throw std::out_of_range("下标越界");
        }
    }
    ~SafeArray() {
        delete[] values;
    }
};

int main() {
    SafeArray<double> a(10);
    a[0] = 0.8;
    a[1] = 2.9;

    std::cout << a[0] << " " << a[1] << " " << a[9] << std::endl;

    // 测试越界报错
    a[10] = 2.2;

    return 0;
}
