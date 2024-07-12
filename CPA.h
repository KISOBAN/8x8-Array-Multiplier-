#include <systemc.h>
void make_CPA();	// this is for the testbench of the CPA


SC_MODULE(CPA){

	// CPA VARIABLES
	sc_in<bool> clk;
	// CSA VARIABLES
	sc_inout<sc_uint<8> > csaA;
	sc_inout<sc_uint<8> > csaB;
	sc_inout<sc_uint<8> > csaCin;
	sc_inout<sc_uint<8> > csaCout;
	sc_inout<sc_uint<8> > csaS;
	sc_inout<sc_uint<8> > csaSout;


// Both of the result variables below will be concatenated together
	sc_inout<sc_uint<8> > dataResult1; // first half of the final result
	sc_inout<sc_uint<8> > dataResult2; // second half of the final result
	sc_inout<sc_uint<16> > dataresult;
	void CPA_method();
	SC_CTOR(CPA){
		SC_METHOD(CPA_method);
	dont_initialize();
		sensitive << clk.pos();
}
};


