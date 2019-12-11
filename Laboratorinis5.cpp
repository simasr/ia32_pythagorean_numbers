#include "pch.h"
#include <iostream>
#include <stdio.h> 
#include <string.h> 
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
	int dalis;
	cout << "Pirma dalis / Antra dalis? ";
	cin >> dalis;
	if (dalis == 1) {
		int rez;
		string temp = argv[1];
		char text[10];
		for (int i = 0; i < temp.length(); i++) {
			text[i] = temp[i];
		}
		int text_length = temp.length();

		_asm {
			push eax
			push ebx
			push ecx
			push edx

			mov ebx, 0
			mov ecx, 0

			while_loop:
			cmp ecx, text_length
				je exit_loop
				mov al, text[ecx]
				sub eax, '0'
				imul ebx, 10
				add ebx, eax
				inc ecx
				jmp while_loop

				exit_loop :
			mov rez, ebx

				pop edx
				pop ecx
				pop ebx
				pop eax
		}

		cout << rez;

	}
	if (dalis == 2) {
		ofstream output;
		output.open("output.csv");
		output << "x,y,z,\n";
		float masyvas1[4], masyvas2[4], masyvas3[4];
		float z;
		for (int i = 1; i < 998; i += 4) {
			masyvas1[0] = i;
			masyvas1[1] = i + 1;
			masyvas1[2] = i + 2;
			masyvas1[3] = i + 3;
			for (int j = i + 1; j < 998; j += 4) {
				masyvas2[0] = j;
				masyvas2[1] = j + 1;
				masyvas2[2] = j + 2;
				masyvas2[3] = j + 3;
				_asm {
					movups xmm0, masyvas1
					movups xmm1, masyvas2
					movups xmm2, masyvas1
					mulps xmm2, xmm2
					movups xmm3, masyvas2
					mulps xmm3, xmm3
					movups xmm4, xmm2
					addps xmm4, xmm3
					sqrtps xmm5, xmm4
					roundps xmm5, xmm5, 1
					mulps xmm5, xmm5
					subps xmm5, xmm4
					movups masyvas3, xmm5
				}
				for (int i = 0; i < 4; i++) {
					if (masyvas3[i] == 0) {
						z = masyvas1[i] * masyvas1[i] + masyvas2[i] * masyvas2[i];
						z = sqrt(z);
						output << masyvas1[i] << "," << masyvas2[i] << "," << z << ",\n";
					}
				}
			}
		}
		output.close();
		system("output.csv");
	}
}