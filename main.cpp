/*
 * Задание:
 * 2.11. Бильярд 1 (10)
 * Бильярдный стол расчерчен на квадратные клетки и имеет размеры M×N клеток. В углах стола находятся четыре лузы для шаров. В центрах некоторых клеток находятся шары. По определенному шару, называемому битком, наносится удар, в результате которого шар может катиться в одном из четырех направлений вдоль диагоналей клетки. Если этот шар достигает края стола, то отражается и продолжает движение, а если попадает в угол стола, то сваливается в лузу и игра заканчивается. Если биток не встречает на своем пути других шаров и не сваливается в лузу, то он проходит ровно K клеток, не считая начальной, но включая конечную клетку либо лузу. Если же биток достигает клетки с другим шаром, то встреченный шар удаляется, а биток занимает его место и используется для последующих ударов. По заданному расположению шаров найти наименьшее количество ударов, необходимое для снятия всех шаров, включая биток.
 * Ввод из файла INPUT.TXT. Первая  строка  содержит целые числа  M, N  и K  (1 ≤  M, N ≤ 15;  1 ≤ K ≤ 10) через пробел. Каждая  i-я  строка  из  следующих M  строк  содержит  N  символов Cij  (1 ≤ j ≤ N). Свободные клетки стола помечаются символами ‘.’, клетки с неподвижными шарами символами ‘#’, а клетка с битком - символом ‘&’. Общее количество шаров, включая биток, может быть от 1 до 15.
 * Вывод в файл OUTPUT.TXT. В единственной строке выводится минимальное количество ударов, необходимое для снятия всех шаров. Если это невозможно, вывести No.
 *
 * ФИО: Веселов Максим Геннадьевич
 * Группа: ПС-21
 * Версия c++: 17
 */


#include <iostream>
#include <fstream>
#include <string>

#define ErrCountCMDArgs "count args error"
#define ErrOpenFile "open file error"

void run(std::ifstream *in, std::ostream *out) {
    std::cout<<"Hello world";
}

int main(int argc, char **argv) {
    if (argc < 2) // no arguments were passed
    {
        std::cout << ErrCountCMDArgs << std::endl;
        return -1;
    }

    std::string inFileName = argv[1];
    std::string outFileName = argv[2];

    std::ifstream in(inFileName);
    std::ofstream out(outFileName);

    if (!in.is_open() || !out.is_open())
    {
        std::cout << ErrOpenFile << std::endl;
        return -1;
    }

    run(&in, &out);
    return 0;
}
