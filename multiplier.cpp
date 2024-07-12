#include <systemc.h>
#include <cstdlib>
#include "CPA.h"

void CPA::CPA_method(){ // this is essentially a one bit FULL adder
	sc_uint<8> A;
	sc_uint<8> B;
	sc_uint<8> AB; // A AND B
	sc_uint<8> Cin;
	sc_uint<8> Cout;
	sc_uint<8> S;
	sc_uint<8> Sout;
	sc_uint<8> result1; // first half of final result
	sc_uint<8> result2; // second half of final result, it will be concatenated with the variable 'result1'
	sc_uint<16> result;

// FIRST START WITH THE CSA MATRIX SO ONLY USE VARIABLES FROM THE CSA.h FILE
	A = csaA.read();
	B = csaB.read();
	// in the first row of the matrix both Cin and S are set to 0
	S = csaS.read();
	Cin = csaCin.read();
// dummy variable B
	sc_uint<9> dumB; // this is a dummy array used for copying the one bit B[j] into 8 bits
	S = 0;

for (int j = 0; j<8;j++){
	// Since the same B[j] value is ANDED with each A value it is necessary to create another array all with the same
	// B[j] values

	if (B[j] == 1)
		dumB = "255";
	else
		dumB = "0";
	AB = A & dumB; // This is the anded result of B[j] with every result of A 

	for (int i = 0; i < 8;i++){
			Sout[i] = AB[i]^S[i]^Cin[i];
			Cout[i] = (AB[i] & S[i]) | (Cin[i] & (AB[i]^S[i]));
	 } 
	  result1[j] = Sout[0];
	  Cin = Cout;
	  S = Sout>>1;
	  S[7] = 0; // the last bit of 'S' is always 0

	  // WRITING ALL THE VALUES INTO THE SIGNALS FROM THE .h FILE
	  csaA.write(A);
	  csaB.write(B);
	  csaCin.write(Cin);
	  csaCout.write(Cout);
	  csaS.write(Sout);
// END OF OUTER FOR LOOP
}
	dataResult1.write(result1);

// NOW DO THE LAST CPA ROW

//CPA Variables

	sc_uint<8> cpaA;
	sc_uint<8> cpaB;
	sc_uint<8> cpaCin;
	sc_uint<8> cpaCout;
	sc_uint<8> cpaSout;

cpaB = Cout;
cpaA = Sout >> 1;
Cin[0] = 0;


	for (int k = 0; k < 8;k++){
		cpaSout[k] = cpaA[k]^cpaB[k]^cpaCin[k];
		cpaCout[k] = (cpaA[k] & cpaB[k]) | (cpaCin[k] & (cpaA[k]^cpaB[k]));
		if (k < 7)
			cpaCin[k+1] = cpaCout[k];
		else{
			cpaCout[k] = 0;
			cpaA[k] = 0; // This is the 'Cin' value shown on the diagram that is shown in the diagram
	}
result2[k] = cpaSout[k];
}
// WRITING THE FINAL RESULT TO THE OVERALL RESULT VARIABLE AFTER CONCATENATING THEM TOGETHER
dataResult2.write(result2);
result = concat(result2,result1);
dataresult.write(result);

}


