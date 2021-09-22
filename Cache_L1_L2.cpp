#include <stdio.h>
#include <map>

using namespace std;

//--------------------------------
// функции иммитирующие кэш L2 L1
// возвращают ответ на вопрос: была ли линия в кэше?

bool L1(unsigned int key);
bool L2(unsigned int key);

//--------------------------------
// наши данные
unsigned int size = 1024 * 1024;

double x[1024 * 1024];
double y[1024 * 1024];
double z[1024 * 1024];
double xx[1024 * 1024];
double yy[1024 * 1024];
double zz[1024 * 1024];

unsigned long long time1 = 0;
unsigned long long time2 = 0;

//--------------------------------
// представление памяти кэша в типе данных map

unsigned int way_l1 = 4;
unsigned int way_l2 = 8;

unsigned int size_bit_l1 = 262144;
unsigned int size_bit_l2 = 1048576 * 8;

unsigned int size_cache_line_bit = 512;

// сам кэш, хранит номер линии
unsigned int l1[4][128];  // 4 блока по 128 линий
// 128 == (size_bit_l1/size_cache_line_bit)/way_l1
unsigned int l2[8][2048];  // 8 блоков по 2048 линий
// 2048 == (size_bit_l2/size_cache_line_bit)/way_l2

// хранит последнее время запроса к кеш линии
unsigned long long l1t[4][128];
unsigned long long l2t[8][2048];


//--------------------------------

int main()
{
    // инициализируем кэш (забьем нулями)
    for(int i=0; i<4; i++) {
        for(int j=0; j<128; j++) {
            l1[i][j]=0;
        }
    }

    for(int i=0; i<8; i++) {
        for(int j=0; j<2048; j++) {
            l2[i][j]=0;
        }
    }
    //--------------------------------

    // счетчики попаданий и обращений к L1 L2
    unsigned long long hitl1=0, hitl2=0, appl1=0, appl2=0;
    // наша функция с прикрученным счетчиком попаданий по L1 и L2
    double w;
    float res; //используется для вывода на экран %

    // после каждого цикла обсчета данных (3)
    // выводится обновленная информация по количеству попаданий

    for (unsigned int i=0; i<size; ++i) {
        x[i] = xx[i] * w + x[i];
        // проверим были ли линии в кэше и добавим если отсутствовали
        // линия состоит из 8 чисел типа double по 8 байт
        // адресация начинается с 1024
        appl1++;
        if(L1(size*3+i/8+1024)) {   // xx[] 1024*1024*3
            hitl1++;
        } else {
            appl2++;
            if(L2(size*3+i/8+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(size*6+1024)) {   // w последнее значение после массивов
            hitl1++;
        } else {
            appl2++;
            if(L2(size*6+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(i/8+1024)) {   // x[] первый массив в памяти
            hitl1++;
        } else {
            appl2++;
            if(L2(i/8+1024)) {
                hitl2++;
            }
        }
        if(i%(1024*128)==0)
            printf("i = %u   time counters L1/L2 = %llu/%llu\n", i, time1, time2);
    }

    res = hitl1*100;
    printf("\n\n%llu %llu %f%%\n", hitl1, appl1, res/appl1);
    res = hitl2*100;
    printf("%llu %llu %f%%\n\n\n", hitl2, appl2, res/appl2);

    for (unsigned int i=0; i<size; ++i) {
        y[i] = yy[i] * w + y[i];

        appl1++;
        if(L1(size*4+i/8+1024)) {   // yy[] 1024*1024*4
            hitl1++;
        } else {
            appl2++;
            if(L2(size*4+i/8+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(size*6+1024)) {   // w последнее значение после массивов
            hitl1++;
        } else {
            appl2++;
            if(L2(size*6+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(size*1+i/8+1024)) {   // y[] второй массив в памяти
            hitl1++;
        } else {
            appl2++;
            if(L2(size*1+i/8+1024)) {
                hitl2++;
            }
        }
        if(i%(1024*128)==0)
            printf("i = %u   time counters L1/L2 = %llu/%llu\n", i, time1, time2);
    }

    res = hitl1*100;
    printf("\n\n%llu %llu %f%%\n", hitl1, appl1, res/appl1);
    res = hitl2*100;
    printf("%llu %llu %f%%\n\n\n", hitl2, appl2, res/appl2);

    for (unsigned int i=0; i<size; ++i) {
        z[i] = zz[i] * w + z[i];

        appl1++;
        if(L1(size*5+i/8+1024)) {   // zz[] 1024*1024*5
            hitl1++;
        } else {
            appl2++;
            if(L2(size*5+i/8+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(size*6+1024)) {   // w последнее значение после массивов
            hitl1++;
        } else {
            appl2++;
            if(L2(size*6+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(size*2+i/8+1024)) {   // z[] третий массив в памяти
            hitl1++;
        } else {
            appl2++;
            if(L2(size*2+i/8+1024)) {
                hitl2++;
            }
        }
        if(i%(1024*128)==0)
            printf("i = %u   time counters L1/L2 = %llu/%llu\n", i, time1, time2);
    }

    res = hitl1*100;
    printf("\n\n%llu %llu %f%%\n", hitl1, appl1, res/appl1);
    res = hitl2*100;
    printf("%llu %llu %f%%\n\n\n", hitl2, appl2, res/appl2);
    return 0;
}


bool L1(unsigned int key) {
    time1++;
    unsigned int k = 0; // количество свободных ячеек
    unsigned int resi; // номер последнего блока со свободной ячейкой
    unsigned int n = key%128;  // (size_bit_l1/size_cache_line_bit)/way_l1

    // Если значение уже было в кэше вернем true
    for(int i=0; i<4; i++) {
        if(l1[i][n] == key) {
            l1t[i][n] = time1;
            return true;
        } else if (l1[i][n] == 0) {
            k++;
            resi = i;
        }
    }

    // Если кэш уже забит, то вытесним самый старый элемент
    if (k == 0) {
        unsigned long long imin = 0;

        for(int i=1; i<4; i++) {    // запускаем цикл на поиск
                                    // мин времени обращения
            if (l1t[imin][n] > l1t[i][n])
                imin = i;
        }
        // отправим значение в кэш L2
        L2(l1t[imin][n]);
        // занесем значения в кеш и таблицу времени
        l1[imin][n] = key;
        l1t[imin][n] = time1;
    } else {
        // занесем значения в кеш и таблицу времени
        l1[resi][n] = key;
        l1t[resi][n] = time1;
    }
    return false;
}

bool L2(unsigned int key) {
    time2++;
    unsigned int k = 0; // количество свободных ячеек
    unsigned int resi; // номер последнего блока со свободной ячейкой
    unsigned int n = key%2048;  // (size_bit_l2/size_cache_line_bit)/way_l2

    // Если значение уже было в кэше вернем true
    for(int i=0; i<8; i++) {
        if(l2[i][n] == key) {
            l2t[i][n] = time1;
            return true;
        } else if (l2[i][n] == 0) {
            k++;
            resi = i;
        }
    }

    // Если кэш уже забит, то вытесним самый старый элемент
    if (k == 0) {
        unsigned long long imin = 0;

        for(int i=1; i<8; i++) {    // запускаем цикл на поиск
                                    // мин времени обращения
            if (l2t[imin][n] > l2t[i][n])
                imin = i;
        }

        // занесем значения в кеш и таблицу времени
        l2[imin][n] = key;
        l2t[imin][n] = time1;
    } else {
        // занесем значения в кеш и таблицу времени
        l2[resi][n] = key;
        l2t[resi][n] = time1;
    }

    return false;
}
