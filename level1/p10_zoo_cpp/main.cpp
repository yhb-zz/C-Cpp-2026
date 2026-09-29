#include <iostream>

struct Record {
    char name[20];
    char calling[20];
};

class Zoo {
private:
    struct Record *animals;
    int number;
public:
    Zoo () {
        number = 0;
        animals = new struct Record[number];
    }

    void new_animal(char *name, char *calling) {
        number++;
        struct Record *p = new struct Record[number];
        for (int _ = 0; _ < number - 1; _++) {
            for (int i = 0; i < 20; i++) {
                p[_].name[i] = animals[_].name[i];
            }
            for (int i = 0; i < 20; i++) {
                p[_].calling[i] = animals[_].calling[i];
            }
        }

        for (int i = 0; i < 20; i++) {
            p[number - 1].name[i] = name[i];
        }
        for (int i = 0; i < 20; i++) {
            p[number - 1].calling[i] = calling[i];
        }

        delete animals;
        animals = p;
        p = NULL;
    }
    void symphony () {
        for (int i = 0; i < number; i ++) {
            std::cout << animals[i].calling << std::endl;
        }
    }
};

int main() {
    Zoo zoo;
    zoo.new_animal("猫猫", "喵呜~");
    zoo.new_animal("狗狗", "汪汪~");
    zoo.new_animal("绵羊", "咩~");
    zoo.symphony();
    zoo.new_animal("布谷鸟", "布谷~布谷~");
    zoo.new_animal("狼狗", "嗷呜~嗷呜~");
    zoo.symphony();
    return 0;
}
