#ifndef __MYSPICE_H__
#define __MYSPICE_H__

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<string.h>

using std::vector;
using std::map;
using std::string;

using std::cout;
using std::endl;


// ===================================== defines =====================================

#define REAL double // default precision

#define MYSPICE_SUCCESS					(0)
#define MYSPICE_ARGUMENT_ERROR			(-1)
#define MYSPICE_FILE_CANNOT_OPEN		(-2)
#define MYSPICE_FILE_FORMAT_ERROR		(-3)
#define MYSPICE_NO_INPUT_FILE			(-4)



// ===================================== class def =====================================

// matrix.cpp
template<class T>
class Mat{
public:
	Mat(int, int);
	~Mat();
	void insert(int, int, REAL);
	void csr();
    void print_csr(FILE*, int);
private:
	// basic
	int _row, _col;
	// CSR
	int _nnz;
	int *_row_pointer;
	vector<int> _col_index;
	vector<REAL> _csr_value;
	// tmp
	int **_tmp_index;
	T **_tmp_value;
	int *_tmp_len, *_tmp_size;
};


// devices.cpp
class Device {
public:
    Device(const string&);
    virtual ~Device();
    void setPnode(int);
    int pnode() const;
    void setNnode(int);
    int nnode() const;
    void setValue(double);
    double value() const;
    void setName(const string&);
    string name() const;
    virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, vector<string*>&, vector<string*>&, vector<string*>&, int) = 0;
protected:
    string _name;
    int _pnode;
    int _nnode;
    double _value;
};

class Resistor: public Device{
public:
    Resistor(const string&);
    virtual ~Resistor();
    virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, vector<string*>&, vector<string*>&, vector<string*>&, int);
};

class Capacitor: public Device{
public:
    Capacitor(const string&);
    virtual ~Capacitor();
    virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, vector<string*>&, vector<string*>&, vector<string*>&, int);
};

class Inductor: public Device{
public:
    Inductor(const string&);
    virtual ~Inductor();
    int auxNode() const;
    void setAux(int);
    virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, vector<string*>&, vector<string*>&, vector<string*>&, int);
private:
    int _aux_node;
};

class Isrc: public Device{
public:
    Isrc(const string&);
    virtual ~Isrc();
    int inIdx() const;
    void setIn(int);
    virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, Mat<REAL>&,vector<string*>&, vector<string*>&, vector<string*>&, int);
private:
    int _in_index;
};

class Vsrc: public Device{
public:
    Vsrc(const string&);
    virtual ~Vsrc();
    int auxNode() const;
    void setAux(int);
    int inIdx() const;
    void setIn(int);
    virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, vector<string*>&, vector<string*>&, vector<string*>&, int);
    int _aux_node;
    int _in_index;
};

class Mutual: public Device{
public:
    Mutual(const string&);
    virtual ~Mutual();
    int auxPosNode() const;
    void setAuxPos(int);
    int auxNegNode() const;
    void setAuxNeg(int);
    string ind1() const;
    void setInd1(const string&);
    string ind2() const;
    void setInd2(const string&);
    virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, vector<string*>&, vector<string*>&, vector<string*>&, int);
private:
    int _aux_node_pos;
    int _aux_node_neg;
    string _ind1;
    string _ind2;
};

class Subckt: public Device{
public:
    Subckt(const string&);
    virtual ~Subckt();
    void addPort(int);
    int getPort(int) const;
    void setSubcktName(const string&);
    string getSubcktName() const;
    virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, Mat<REAL>&, vector<string*>&, vector<string*>&, vector<string*>&, int);
private:
    string _subckt_name;
    vector<int> _port_list;
};


// stamp.cpp
class Stamp{
public:
    Stamp();
    ~Stamp();
    void parse(char*);
    void output(const char*);
    void setup();
private:
    // for parse
    int _num_in;
    int _num_out;
    map<string, int> _node_list, _aux_node_list, _subckt_list;    // -> vector X
    vector<Device*> _dev_list;
    vector< vector <Device*> > _subckt_dev_list;
    vector<string*> *_Y;    // = _probe_list
    // for stamp
    Mat<REAL> *_C, *_G, *_B, *_LT;
    vector<string*> *_X, *_U;
};


// ===================================== funtions def =====================================

// argparse.cpp
void help_message();
int argparse(int, char**, int*, double*, char**);

// utils.cpp
string tokenizer(string&, const string&);
void capitalize(string &);
double to_double(string &); 

#endif