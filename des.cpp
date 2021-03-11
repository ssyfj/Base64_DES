#include "table.h"
#include "des.h"
#include <string>
#include <qDebug>

using namespace std;

void Des::Initial_Permutation(BIT pt[64])
{
    BIT tmp[64];
    for (int i = 0; i < 64; i++)
        tmp[i] = pt[IP[i] - 1];
    memcpy(pt, tmp, sizeof(tmp));
    return;
}

void Des::Final_Permutation(BIT pt[64])
{
    BIT tmp[64];
    for (int i = 0; i < 64; i++)
        tmp[i] = pt[FP[i] - 1];
    memcpy(pt, tmp, sizeof(tmp));
    return;
}

void Des::P_Box_Permutation(BIT x[32])
{
    BIT tmp[32];
    for (int i = 0; i < 32; i++)
        tmp[i] = x[PP[i] - 1];
    memcpy(x, tmp, sizeof(tmp));
    return;
}

void Des::Generate_K(BIT SK[64])
{
    BIT L[60], R[60];
    int i, j, st;

    memset(K, 0, sizeof(K));

    for (i = 0; i < 28; i++)
        L[i + 28] = L[i] = SK[KP[i] - 1],
        R[i + 28] = R[i] = SK[KP[i + 28] - 1];
    st = 0;
    for (i = 0; i < 16; i++) {
        st += KM[i];
        for (j = 0; j < 48; j++)
            K[i][j] = (CP[j] < 28) ? L[CP[j] + st - 1] : R[CP[j] - 29 + st];
    }
    return;
}

void Des::Work(BIT L[32], BIT R[32], BIT KEY[48], int cnt)
{
    BIT X[48], RES[32];
    memset(RES, 0, sizeof(RES));
    memset(X, 0, sizeof(X));
    int i, j, a, b, st, st2, tmp;

    for (i = 0; i < 48; i++)
        X[i] = R[EP[i] - 1] ^ KEY[i];

    for (i = 0; i < 8; i++) {

        st = i * 6;
        a = (X[st] << 1) + X[st + 5];
        b = (X[st + 1] << 3) + (X[st + 2] << 2) + (X[st + 3] << 1) + X[st + 4];
        tmp = S_box[i][a][b];
        st2 = i * 4;
        for (j = 0; j < 4; j++)
            RES[st2 + (3 - j)] |= (tmp >> j) & 1;
    }

    P_Box_Permutation(RES);

    for (i = 0; i < 32; i++)
        L[i] ^= RES[i];

    if (cnt == 15) return;

    BIT temp[32];

    memcpy(temp, L, sizeof(temp));
    memcpy(L, R, sizeof(temp));
    memcpy(R, temp, sizeof(temp));

    return;
}

void Des::DES_enc(char txt[10], char enc[10])
{
    int i, j;
    BIT L[32], R[32];
    BIT pt[64];

    for (i = 0; i < 8; i++)
        for (j = 7; j >= 0; j--)
            pt[i * 8 + (7 - j)] = (txt[i] >> j) & 1;

    Initial_Permutation(pt);

    for (i = 0; i < 32; i++)
        L[i] = pt[i], R[i] = pt[i + 32];

    for (i = 0; i < 16; i++)
        Work(L, R, K[i], i);

    for (i = 0; i < 32; i++)
        pt[i] = L[i], pt[i + 32] = R[i];


    Final_Permutation(pt);

    for (i = 0; i < 8; i++)
        for (j = 7; j >= 0; j--)
            enc[i] |= pt[i * 8 + (7 - j)] << j;

    return;
}

void Des::DES_dec(char txt[10], char dec[10])
{
    int i, j;
    BIT L[32], R[32];
    BIT pt[64];

    for (i = 0; i < 8; i++)
        for (j = 7; j >= 0; j--)
            pt[i * 8 + (7 - j)] = (txt[i] >> j) & 1;

    Initial_Permutation(pt);

    for (i = 0; i < 32; i++)
        L[i] = pt[i], R[i] = pt[i + 32];

    for (i = 0; i < 16; i++)
        Work(L, R, K[15 - i], i);

    for (i = 0; i < 32; i++)
        pt[i] = L[i], pt[i + 32] = R[i];

    Final_Permutation(pt);

    for (i = 0; i < 8; i++)
        for (j = 7; j >= 0; j--)
            dec[i] |= pt[i * 8 + (7 - j)] << j;

    return;
}

void Des::DES_E(const char txt[], const char key_c[])
{
    int i, j,len;
    BIT sk[64];
    char key[10], res[10],temp[10];

	strcpy(key, key_c);

    memset(this->encode_data, 0, sizeof(this->encode_data));

    for (i = 0; i < 8; i++)
        for (j = 7; j >= 0; j--)
            sk[i * 8 + (7 - j)] = (key[i] >> j) & 1;

    Generate_K(sk);

    for (i = 0; i < strlen(txt); i += 8)
    {
        strncpy(temp, (const char*)(&txt[i]), 8);
        for (j = strlen(temp); j < 8; j++) temp[j] = 0;
        memset(res, 0, sizeof(res));
        DES_enc(temp, res);
        strcat(this->encode_data, res);
    }

    this->base->base64_encode((unsigned char*)this->encode_data);
}


void Des::DES_D(const char txt[],const char key_c[])
{
    int tmp, i, j;
    BIT sk[64];
    char key[10], res[10],temp[10];

    strcpy(key,key_c);

    memset(this->decode_data, 0, sizeof(this->decode_data));

    for (i = 0; i < 8; i++)
        for (j = 7; j >= 0; j--)
            sk[i * 8 + (7 - j)] = (key[i] >> j) & 1;

    Generate_K(sk);

    this->base->bae64_decode((unsigned char*)txt);

    for (i = 0; i < strlen((const char*)this->base->src); i += 8)
    {
        strncpy(temp, (const char*)(&(this->base->src[i])), 8);
        for (j = strlen(temp); j < 8; j++) temp[j] = 0;
        memset(res, 0, sizeof(res));
        DES_dec(temp, res);
        strcat(this->decode_data, res);
    }
}
