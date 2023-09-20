///
/// @file   stamp.cpp
/// @author Yinghai
/// @date   Fri Sep 12 13:05:24 2008
/// 
/// @brief  Implementation of the Stamp class
/// 
/// 
///

#include "myspice.h"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::getline;


/// \brief Constructor 
Stamp::Stamp() : _C(NULL), _G(NULL), _B(NULL), _LT(NULL) {};


/// \brief Destructor
///
/// It destroys the system matrix and release the allocated memory
Stamp::~Stamp(){
	if(_C) delete _C;
	if(_G) delete _G;
	if(_B) delete _B;
	if(_LT) delete _LT;
}


/// \brief Initialize the system matrix and carry out the stamping
///
/// This function is most important one because it setups up the liear system
/// \f[
/// \left\{\begin{array}{ccc}
///   C\dot{x}+Gx &=& Bu \\
///   y &=& L^T x \end{array}\right.
/// \f]
/// and fills in the elements in the system matrices. 
/// 
/// The matrix class \e Matrix needs to be designed by you.
/// Sparse matrix structure is preferred than the dense one since
/// the matrix will be very large while most of its elemets would be zero. 
/// 
/// In the skeleton program, the devices are enumerated and
/// they contributes to the system matrices by calling thier own stamping function.
/// 
/// \todo 
/// = Some devices such as mutual inductance depends on other devices. You need to 
///  take care of this situation. 
/// - We also have to enumerate the probe list to build the
/// \f$ L^T \f$ matrix. 
/// - SPICE file support multi-line command with a \e '+' at the beginning of the line.
/// Please consider how to support this. 
/// 
void Stamp::setup(){
	int n = static_cast<int>(_node_list.size()) - 1;
	_C = new Mat<REAL>(n,n);	// diag([C L])
	_G = new Mat<REAL>(n,n);	// [G, E; -E^T, O]
	_B = new Mat<REAL>(n, _num_in);
	_LT = new Mat<REAL>(_num_out, n);
	for(size_t i=0; i < _dev_list.size(); ++i){
		_dev_list[i]->stamp(*_C, *_G, *_B);
	}
	_C->csr();
	_G->csr();
	_B->csr();
	_LT->csr();
}


/// \brief Output the system matrix to disk
///
/// @param filename output file name
///
/// This function will write the system matrix to the disk. 
/// Binary file format is preferred over the ASCII one. Sparse
/// matrix structure is preferred over the dense one. 
/// 
/// \todo Please fill in this function. 
void Stamp::output(const char* filename)
{
	int output_setting = 0; // 0-text, 1-binary, 2-command, others-nothing
	
	FILE* output = NULL;

	if (output_setting == 0)
		output = fopen(filename, "w");
	else if (output_setting == 1)
		output = fopen(filename, "wb");

	_C->print_csr(output, output_setting);
	_G->print_csr(output, output_setting);
	_B->print_csr(output, output_setting);
	_LT->print_csr(output, output_setting);
	// vector X
	// vector Y
	// vector U

	fclose(output);
	
}


/// \brief Parsing the SPICE netlist
///
/// @param filename SPICE filename
///
/// This is the first step of STAMP. It reads in the SPICE file and
/// extracts device and node information from it. The devices and nodes
/// are stored in \e _dev_list and \e _node_list for later usage. 
/// The parser reads in the SPICE netlist line by line. It breaks each line into
/// string tokens according to the delimiters, and then processes each token case by case.
/// Notice the using of \e tokenizer and \e captilizer. These two functions break the
/// line and convert them to upper case. (SPICE file are not case-sensitive)
///
/// \todo Currently, only limited devices cards for SPICE are considered. You can 
/// Further develop this fucntion to  accomodate more SPICE elements or cards such as 
/// subcircuit or controlled sources. 
void Stamp::parse(char* filename)
{
	ifstream ifid(filename);
	_num_in = 0;
	_num_out = 0;
	
	string line;
	string delims(" \n\r()\t");
	int k = 0;
	_node_list["0"] = 0;

	while(getline(ifid, line))
	{
		string tmp;
		capitalize(line);

		if(line[0] == 'R'){

			// name
			tmp = tokenizer(line, delims);
			Resistor *r = new Resistor(tmp);

			// pnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setNnode(_node_list[tmp]);

			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
      	}
      
	  	else if(line[0] == 'C'){
			
			// name
			tmp = tokenizer(line, delims);
			Capacitor* r = new Capacitor(tmp);

			// pnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setNnode(_node_list[tmp]);

			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
      	}
      
		else if(line[0] == 'I'){
			
			// name
			tmp = tokenizer(line, delims);
			Isrc* r = new Isrc(tmp);

			// pnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	   			_node_list[tmp] = ++k;
	  		}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setNnode(_node_list[tmp]);

			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
			++_num_in;
      	}

      	else if(line[0] == 'V'){
			
			// name
			tmp = tokenizer(line, delims);
			Vsrc* r = new Vsrc(tmp);
			
			// aux current
			tmp = "i:"+tmp;
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setAux(_node_list[tmp]);

			// pnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setNnode(_node_list[tmp]);
			
			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
			++_num_out;
      	}
    
		else if(line[0] == 'L'){
	
			// name
			tmp = tokenizer(line, delims);
			Inductor* r = new Inductor(tmp);
			
			// aux current
			tmp = "i:"+tmp;
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setAux(_node_list[tmp]);

			// pnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if(_node_list.find(tmp) == _node_list.end())
	  		{
	    		_node_list[tmp] = ++k;
	  		}
			r->setNnode(_node_list[tmp]);
			
			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
      	}
    
		else if(line[0] == 'K'){
			
			// name
			tmp = tokenizer(line, delims);
			Mutual* r = new Mutual(tmp);
			
			// pnode
			tmp = tokenizer(line, delims);
			r->setInd1(tmp);

			// nnode
			tmp = tokenizer(line, delims);
			r->setInd2(tmp);
			
			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
      	}
      
	  	else {
			
			string token = tokenizer(line, delims);
	
			// netlist file ends
			if (token == ".END") {
	  			return;
			}
	
			// specify output node
			else if (token == ".PROBE" /*|| token == ".PRINT"*/) {
	  			token = tokenizer(line, delims);
	  			while(!token.empty()){
	    			if(token == "V")
	      			{
						token = tokenizer(line, delims);
						continue;
	      			}
	    			_probe_list.push_back(_node_list[token]);
	    			++_num_out;
	    			token = tokenizer(line, delims);
	  			}
			}
      	}

    } // end while

  	ifid.close();
}
