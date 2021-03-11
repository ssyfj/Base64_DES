#ifndef		_DES_H_
#define	_DES_H_

#include "common.h"
#include "base64.h"

#define BIT bool

class Des
{
private:
    BIT K[16][48];
    char encode_data[1000];
public:
    Base64* base;
    char decode_data[1000];
protected:
    void Initial_Permutation(BIT pt[64]);
    void Final_Permutation(BIT pt[64]);
    void P_Box_Permutation(BIT x[32]);
    void Generate_K(BIT SK[64]);
    void Work(BIT L[32], BIT R[32], BIT KEY[48], int cnt);
    void DES_enc(char txt[10], char enc[10]);
    void DES_dec(char txt[10], char dec[10]);
public:
    Des()
    {
        base = new Base64();
    }

	void DES_E(const char* str, const char key_c[]);
	void DES_D(const char* str, const char key_c[]);
};

#endif
