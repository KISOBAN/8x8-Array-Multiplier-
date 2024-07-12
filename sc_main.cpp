#include <systemc.h>
#include <cstdlib>
#include "CPA.h"
void make_CPA(){

	sc_trace_file *tf;                  // Create VCD file for tracing
	sc_signal<sc_uint<8> > csaA;     //Declare signals
	sc_signal<sc_uint<8> > csaB;
	sc_signal<sc_uint<8> > csaCin;
	sc_signal<sc_uint<8> > csaCout;
	sc_signal<sc_uint<8> > csaSout;
	sc_signal<sc_uint<8> > csaS;
	sc_signal<sc_uint<8> > dataResult1; // first half of the final result
	sc_signal<sc_uint<8> > dataResult2; // second half of the final result
	sc_signal<sc_uint<16> > totalresult;

	sc_clock clk("clk",10,SC_NS,0.5);   //Create a clock signal

	CPA DUT("CSA_TEST");		// instantiate an object 'DUT' (Device Under Test) of type CPA 
	DUT.clk(clk);
	DUT.csaA(csaA);
	DUT.csaB(csaB);
	DUT.csaS(csaS);
	DUT.csaCin(csaCin);
	DUT.csaCout(csaCout);
	DUT.csaSout(csaSout);
	DUT.dataResult1(dataResult1);
	DUT.dataResult2(dataResult2);
	DUT.dataresult(totalresult);
	
	tf = sc_create_vcd_trace_file("trace_file");
    tf->set_time_unit(1, SC_NS);
	sc_trace(tf, clk, "clk");
	sc_trace(tf, csaA, "A");
	sc_trace(tf, csaB, "B");
	sc_trace(tf, csaS, "S");
	sc_trace(tf, csaCin, "Cin");
	sc_trace(tf, csaCout, "Cout");
	sc_trace(tf, csaSout, "Sout");
	sc_trace(tf,dataResult1, "Result");
	sc_trace(tf,dataResult2, "Result2");
	sc_trace(tf,totalresult, "TOTALRESULT");

// TEST CASE 1: binary numbers that don't result in carryout in CSAs
	csaA.write(4);
	csaB.write(2);
	csaCin.write(0);
	csaCout.write(0);
	sc_start(10, SC_NS);

// TEST CASE 2: binary numbers that have a carryout in CSAs
	csaA.write(7);
	csaB.write(7);
	csaCin.write(0);
	csaCout.write(0);
	sc_start(10, SC_NS);

// TEST CASE 3: Largest possible binary inputs
	csaA.write(255);
	csaB.write(255);
	csaCin.write(0);
	csaCout.write(0);
	sc_start(10, SC_NS);

// TEST CASE 4: Random number case
	csaA.write(90);
	csaB.write(77);
	csaCin.write(0);
	csaCout.write(0);
	sc_start(10, SC_NS);


   	sc_close_vcd_trace_file(tf);
	
}
int sc_main(int argc, char* argv[]){

	make_CPA(); //example of function call in main cpu

	return 0;                         
}
	


