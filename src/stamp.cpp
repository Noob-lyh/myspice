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


/// \brief Constructor 
Stamp::Stamp() : _C(NULL), _G(NULL), _B(NULL), _LT(NULL) {
	_X = new vector<string*>;	// setup
	_Y = new vector<string*>;	// parse
	_U = new vector<string*>;	// stamp
};


/// \brief Destructor
///
/// It destroys the system matrix and release the allocated memory
Stamp::~Stamp(){
	DELETE_AND_SET_NULL(_C);
	DELETE_AND_SET_NULL(_G);
	DELETE_AND_SET_NULL(_B);
	DELETE_AND_SET_NULL(_LT);
	DELETE_AND_SET_NULL(_X);
	DELETE_AND_SET_NULL(_Y);
	DELETE_AND_SET_NULL(_U);
}


int Stamp::parse_line(ifstream& ifid, string& line, int& num_in, int& num_out, 
            int& node_index, int& aux_node_index, int& subckt_index, 
            map<string, int>& node_list, map<string, int>& aux_node_list, 
			map<string, int>& subckt_list, vector<Device*>& dev_list){

	string tmp;
	string delims(" \n\r()\t");

	if(line[0] == 'R'){
		// name
		tmp = tokenizer(line, delims);
		Resistor *r = new Resistor(tmp);
		// pnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setPnode(node_list[tmp]);
		// nnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setNnode(node_list[tmp]);
		// value
		tmp = tokenizer(line, delims);
		r->setValue(to_double(tmp));
		// add to device list
		dev_list.push_back(r);
		return 1;

    } else if(line[0] == 'C'){
		// name
		tmp = tokenizer(line, delims);
		Capacitor* r = new Capacitor(tmp);
		// pnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setPnode(node_list[tmp]);
		// nnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setNnode(node_list[tmp]);
		// value
		tmp = tokenizer(line, delims);
		r->setValue(to_double(tmp));
		// add to device list
		dev_list.push_back(r);
		return 2;

    } else if(line[0] == 'L'){
		// name
		tmp = tokenizer(line, delims);
		Inductor* r = new Inductor(tmp);
		// aux current
		tmp = "i:"+tmp;
		if(aux_node_list.find(tmp) == aux_node_list.end())
	    	aux_node_list[tmp] = aux_node_index++;
		r->setAux(aux_node_list[tmp]);
		// pnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setPnode(node_list[tmp]);
		// nnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setNnode(node_list[tmp]);
		// value
		tmp = tokenizer(line, delims);
		r->setValue(to_double(tmp));
		// add to device list
		dev_list.push_back(r);
		return 3;
    
	} else if(line[0] == 'I'){
		// name
		tmp = tokenizer(line, delims);
		Isrc* r = new Isrc(tmp);
		// pnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	   		node_list[tmp] = node_index++;
		r->setPnode(node_list[tmp]);
		// nnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setNnode(node_list[tmp]);
		// value
		tmp = tokenizer(line, delims);
		r->setValue(to_double(tmp));
		// add to num_in
		r->setIn(num_in++);
		// add to device list
		dev_list.push_back(r);
		return 4;
      	
	} else if(line[0] == 'V'){
		// name
		tmp = tokenizer(line, delims);
		Vsrc* r = new Vsrc(tmp);
		// aux current
		tmp = "i:"+tmp;
		if(aux_node_list.find(tmp) == aux_node_list.end())
	    	aux_node_list[tmp] = aux_node_index++;
		r->setAux(aux_node_list[tmp]);
		// pnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setPnode(node_list[tmp]);
		// nnode
		tmp = tokenizer(line, delims);
		if(node_list.find(tmp) == node_list.end())
	    	node_list[tmp] = node_index++;
		r->setNnode(node_list[tmp]);	
		// value
		tmp = tokenizer(line, delims);
		r->setValue(to_double(tmp));
		// add to num_in
		r->setIn(num_in++);
		// add to device list
		dev_list.push_back(r);
		return 5;

    } else if(line[0] == 'K'){
		// name
		tmp = tokenizer(line, delims);
		Mutual* r = new Mutual(tmp);
		// pnode & auxpos
		tmp = tokenizer(line, delims);
		r->setInd1(tmp);
		r->setAuxPos(aux_node_list[tmp]);
		// nnode & auxneg
		tmp = tokenizer(line, delims);
		r->setInd2(tmp);
		r->setAuxNeg(aux_node_list[tmp]);
		// value
		tmp = tokenizer(line, delims);
		r->setValue(to_double(tmp));
		// add to device list
		dev_list.push_back(r);
		return 6;
    
	} else if(line[0] == 'X'){	// only ports and subckt name
		// name
		tmp = tokenizer(line, delims);
		Subckt* r = new Subckt(tmp);
		// ports
		string next;
		tmp = tokenizer(line, delims);
		next = tokenizer(line, delims);
		while (!next.empty()){
			if(node_list.find(tmp) == node_list.end())
	    		node_list[tmp] = node_index++;
			r->addPort(node_list[tmp]);
			// next two tokens
			tmp = next;
			next = tokenizer(line, delims);
		}
		// subckt type (when next is empty)
		r->setSubcktName(tmp);
		// add to device list
		dev_list.push_back(r);
		return 7;
	
	} else {	// line[0] == '.' or others		
		string token = tokenizer(line, delims);

		// netlist file or subckt ends
		if (token == ".END" || token == ".ENDS") {
#ifdef PRINT_INFO				
printf("READ_END, return -1.\n");
#endif
	  		return -1;
		}

		// note or blank
		else if (token == "*" || token == ""){
			return 0;
		}
	
		// specify output node
		else if (token == ".PROBE" /*|| token == ".PRINT"*/) {
	  		token = tokenizer(line, delims);
	  		while(!token.empty()){
	    		if(token == "V"){
					token = tokenizer(line, delims);
					continue;
	      		}
				string *tmp = new string(token);
	    		(*_Y).push_back(tmp);
	    		++_num_out;	// only in main circuit
	    		token = tokenizer(line, delims);
	  		}
			return 0;
		}

		// sub circuit definition, always operate global list
		else if (token == ".SUBCKT") {

			token = tokenizer(line, delims);	// subckt name

			if (_subckt_list.find(token) != _subckt_list.end()) {
				printf("redefine sub circuit!\n");
				return -1;

			} else {

				string name = token;	
#ifdef PRINT_INFO				
printf("DEF_SUB : %s\n", name.c_str());
#endif
				_subckt_list[name] = subckt_index;	// add to map

				SubcktDef *tmp = new SubcktDef(name);				
				
				// read subckt ports
				token = tokenizer(line, delims);
				while (token.size() != 0) {	
					tmp->addPortName(token);
#ifdef PRINT_INFO
printf("ADD_PORT : %s\n", token.c_str());
#endif
					token = tokenizer(line, delims);
				}
 				
				// read dev in subckt until ".ENDS name" 
				int sub_node_index = 1;
				int sub_aux_node_index = 0;
				int idum = 0;	// unused
				map<string, int> ldum;	// unused

				while(getline(ifid, line)) {
					capitalize(line);
#ifdef PRINT_INFO
printf("READ_SUB : %s\n", line.c_str());
#endif
					if (parse_line(ifid, line, idum, idum,
							sub_node_index, sub_aux_node_index, idum, 
							tmp->_node_list, tmp->_aux_node_list, ldum, tmp->_dev_list) == -1)
						break;
    			}
		
				_subckt_def_list.push_back(tmp);	// add to subcircuit define list

				++subckt_index;	
			}
			return 8;

		// others
		} else {
			printf("Invalid netlist or unsupported device.\n");
			return -1;
		}
	}
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
	_node_list["0"] = 0;
	int node_index = 1;
	int aux_node_index = 0;
	int subckt_index = 0;

	getline(ifid, line);
	while(getline(ifid, line))
	{	
		capitalize(line);
#ifdef PRINT_INFO
printf("READ_MAIN : %s\n", line.c_str());
#endif
		if (parse_line(ifid, line, _num_in, _num_out,
			node_index, aux_node_index, subckt_index,
			_node_list, _aux_node_list, _subckt_list, _dev_list) == -1)
			break;
    }

	for (vector<SubcktDef*>::iterator it = _subckt_def_list.begin(); it != _subckt_def_list.end(); ++it){
		(*it)->getSize(_subckt_list, _subckt_def_list);
#ifdef PRINT_INFO
printf("SUBCKT : %s, size = %d\n", (*it)->_name.c_str(), (*it)->getSize(_subckt_list, _subckt_def_list));
#endif
	}

  	ifid.close();
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

	// caculate size
	int n = static_cast<int>(_node_list.size() + _aux_node_list.size()) - 1;

	// get _X
	_X->resize(n);
	for(map<string,int>::iterator it = _node_list.begin(); it != _node_list.end(); ++it){
		if (it->second != 0){
			string *tmp = new string(it->first);
			(*_X)[it->second - 1] = tmp;
		}
	}
	for(map<string,int>::iterator it = _aux_node_list.begin(); it != _aux_node_list.end(); ++it){
		string *tmp = new string(it->first);
		(*_X)[it->second + _node_list.size() - 1] = tmp;
	}

	// get _C, _G, _B and _U
	_C = new Mat<REAL>(n,n);	// diag([C L])
	_G = new Mat<REAL>(n,n);	// [G, E; -E^T, O]
	_B = new Mat<REAL>(n, _num_in);
	_U->resize(_num_in);
	for(size_t i = 0; i < _dev_list.size(); ++i){
		_dev_list[i]->stamp(*_C, *_G, *_B, *_LT, *_X, *_Y, *_U, _node_list.size());
	}
	
	// get _LT
	_LT = new Mat<REAL>(_num_out, n);
	for(size_t i = 0; i < _Y->size(); ++i){
		string *probe_name = (*_Y)[i];
		int out_index;
		for(out_index = 0; out_index < _X->size(); ++out_index)
			if (*probe_name == (*(*_X)[out_index]))
				break;
		_LT->insert(i, out_index, 1);	 //printf("%d %d\n", i, out_index);
	}

	// form all sparse matrixes
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

	if(output_setting == 0){
		// vector X
		for(int i = 0; i < (*_X).size(); ++i){
			fprintf(output, "%s ", (*_X)[i]->c_str());
		}
		fprintf(output, "\n");	
		// vector Y
		for(int i = 0; i < (*_Y).size(); ++i){
			fprintf(output, "%s ", (*_Y)[i]->c_str());
		}
		fprintf(output, "\n");
		// vector U
		for(int i = 0; i < (*_U).size(); ++i){
			fprintf(output, "%s ", (*_U)[i]->c_str());
		}
		fprintf(output, "\n");
	}

	fclose(output);
}
