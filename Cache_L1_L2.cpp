#include <stdio.h>
#include <map>

using namespace std;

//--------------------------------
// ������� ������������ ��� L2 L1
// ���������� ����� �� ������: ���� �� ����� � ����?

bool L1(unsigned int key);
bool L2(unsigned int key);

//--------------------------------
// ���� ������
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
// ������������� ������ ���� � ���� ������ map

unsigned int way_l1 = 4;
unsigned int way_l2 = 8;

unsigned int size_bit_l1 = 262144;
unsigned int size_bit_l2 = 1048576 * 8;

unsigned int size_cache_line_bit = 512;

// ��� ���, ������ ����� �����
unsigned int l1[4][128];  // 4 ����� �� 128 �����
// 128 == (size_bit_l1/size_cache_line_bit)/way_l1
unsigned int l2[8][2048];  // 8 ������ �� 2048 �����
// 2048 == (size_bit_l2/size_cache_line_bit)/way_l2

// ������ ��������� ����� ������� � ��� �����
unsigned long long l1t[4][128];
unsigned long long l2t[8][2048];


//--------------------------------

int main()
{
    // �������������� ��� (������ ������)
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

    // �������� ��������� � ��������� � L1 L2
    unsigned long long hitl1=0, hitl2=0, appl1=0, appl2=0;
    // ���� ������� � ������������ ��������� ��������� �� L1 � L2
    double w;
    float res; //������������ ��� ������ �� ����� %

    // ����� ������� ����� ������� ������ (3)
    // ��������� ����������� ���������� �� ���������� ���������

    for (unsigned int i=0; i<size; ++i) {
        x[i] = xx[i] * w + x[i];
        // �������� ���� �� ����� � ���� � ������� ���� �������������
        // ����� ������� �� 8 ����� ���� double �� 8 ����
        // ��������� ���������� � 1024
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
        if(L1(size*6+1024)) {   // w ��������� �������� ����� ��������
            hitl1++;
        } else {
            appl2++;
            if(L2(size*6+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(i/8+1024)) {   // x[] ������ ������ � ������
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
        if(L1(size*6+1024)) {   // w ��������� �������� ����� ��������
            hitl1++;
        } else {
            appl2++;
            if(L2(size*6+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(size*1+i/8+1024)) {   // y[] ������ ������ � ������
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
        if(L1(size*6+1024)) {   // w ��������� �������� ����� ��������
            hitl1++;
        } else {
            appl2++;
            if(L2(size*6+1024)) {
                hitl2++;
            }
        }

        appl1++;
        if(L1(size*2+i/8+1024)) {   // z[] ������ ������ � ������
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
    unsigned int k = 0; // ���������� ��������� �����
    unsigned int resi; // ����� ���������� ����� �� ��������� �������
    unsigned int n = key%128;  // (size_bit_l1/size_cache_line_bit)/way_l1

    // ���� �������� ��� ���� � ���� ������ true
    for(int i=0; i<4; i++) {
        if(l1[i][n] == key) {
            l1t[i][n] = time1;
            return true;
        } else if (l1[i][n] == 0) {
            k++;
            resi = i;
        }
    }

    // ���� ��� ��� �����, �� �������� ����� ������ �������
    if (k == 0) {
        unsigned long long imin = 0;

        for(int i=1; i<4; i++) {    // ��������� ���� �� �����
                                    // ��� ������� ���������
            if (l1t[imin][n] > l1t[i][n])
                imin = i;
        }
        // �������� �������� � ��� L2
        L2(l1t[imin][n]);
        // ������� �������� � ��� � ������� �������
        l1[imin][n] = key;
        l1t[imin][n] = time1;
    } else {
        // ������� �������� � ��� � ������� �������
        l1[resi][n] = key;
        l1t[resi][n] = time1;
    }
    return false;
}

bool L2(unsigned int key) {
    time2++;
    unsigned int k = 0; // ���������� ��������� �����
    unsigned int resi; // ����� ���������� ����� �� ��������� �������
    unsigned int n = key%2048;  // (size_bit_l2/size_cache_line_bit)/way_l2

    // ���� �������� ��� ���� � ���� ������ true
    for(int i=0; i<8; i++) {
        if(l2[i][n] == key) {
            l2t[i][n] = time1;
            return true;
        } else if (l2[i][n] == 0) {
            k++;
            resi = i;
        }
    }

    // ���� ��� ��� �����, �� �������� ����� ������ �������
    if (k == 0) {
        unsigned long long imin = 0;

        for(int i=1; i<8; i++) {    // ��������� ���� �� �����
                                    // ��� ������� ���������
            if (l2t[imin][n] > l2t[i][n])
                imin = i;
        }

        // ������� �������� � ��� � ������� �������
        l2[imin][n] = key;
        l2t[imin][n] = time1;
    } else {
        // ������� �������� � ��� � ������� �������
        l2[resi][n] = key;
        l2t[resi][n] = time1;
    }

    return false;
}
