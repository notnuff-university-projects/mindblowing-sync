/**
* ПЗВПКС
* Лабораторна робота ЛР2.1
* Бібліотека PThread
* Семафори, мютекси, події, критичні секції, атомік-змінні, бар'єри
* Моя функція: A = min(Z)*(B*MV) + e*X*(MM*MC)
* Ярошенко Олександр Сергійович
* Група ІМ-21
* Дата 14.04.2025
*/

#include <iostream>
#include <chrono>
#include "data.h"
#include "t1.h"
#include "t2.h"
#include "t3.h"
#include "t4.h"

int main() {
    Data data;

    auto start = std::chrono::high_resolution_clock::now();
    
    T1 t1(data);
    T2 t2(data);
    T3 t3(data);
    T4 t4(data);
    
    t1.start();
    t2.start();
    t3.start();
    t4.start();
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Час виконання: " << duration.count() << " мс" << std::endl;
    
    return 0;
}