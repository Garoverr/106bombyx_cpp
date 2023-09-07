/*
** EPITECH PROJECT, 2023
** Bombyx project
** File description:
** math project in C++
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

class Bombyx {
public:
    Bombyx(float n, float k) {
        this->n = n;
        this->k = k;
    }

    void evolution_calculator() {
        for (int i = 1; i <= 100; i++) {
            printf("%d %.2f\n", i, n);
            n = k * n * (1000 - n) / 1000;
        }
    }

    void bombyx_bounded(int i0, int i1) {
        float new_k = 1.00;
        for (; new_k <= 4; new_k += 0.01) {
            int bound = 1;
            while (bound < i0) {
                n = new_k * n * (1000 - n) / 1000;
                bound++;
            }
            while (bound <= i1) {
                printf("%.2f %.2f\n", new_k, n);
                n = new_k * n * (1000 - n) / 1000;
                bound++;
            }
        }
    }

private:
    float n;
    float k;
};

int data_calculator(int argc, char*argv[])
{
    int n = atoi(argv[1]);
    float k = atof(argv[2]);
    Bombyx bombyx(n, k);

    if (argc == 3) {
        bombyx.evolution_calculator();
    } else {
        int i0 = atoi(argv[2]);
        int i1 = atoi(argv[3]);
        bombyx.bombyx_bounded(i0, i1);
    }
    return 0;
}

int data_checker(int argc, char *argv[])
{
    if (argc == 3) {
        if ((atoi(argv[1]) <= 0) || ((atof(argv[2]) < 1.0 ) || (atof(argv[2]) > 4.0)))
            return 84;
    }
    if (argc == 4) {
        if ((atoi(argv[1]) <= 0) || (atoi(argv[3]) <= 0) || atoi(argv[2]) <= 0 || (atoi(argv[2]) > atoi(argv[3])))
            return 84;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 4)
        return 84;
    if (data_checker(argc, argv) == 84)
        return 84;
    data_calculator(argc, argv);
    return 0;
}
