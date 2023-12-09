#include "myspice.h"

Device::Device(const string &name): _name(name),_pnode(0),_nnode(0),_value(0) {};
Device::~Device() {};
void Device::setPnode(int p) {_pnode = p;}
int Device::pnode() const {return _pnode;}
void Device::setNnode(int p) {_nnode = p;}
int Device::nnode() const {return _nnode;}  
void Device::setValue(double d) {_value = d;}
double Device::value() const {return _value;}
void Device::setName(const string& n) {_name = n;}
string Device::name() const {return _name;}


Resistor::Resistor(const string &name) : Device(name) {};
Resistor::~Resistor() {};
void Resistor::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B, Mat<REAL>& LT, vector<string*>& X, vector<string*>& Y, vector<string*>& U, int aux_offset)
{
    int i = _pnode - 1;     // _pnode is 0-based, but 0 is not in matrix, so put index 1 in row/col 0
    int j = _nnode - 1;
    G.insert(i, i, 1/_value);
    G.insert(i, j, -1/_value);
    G.insert(j, i, -1/_value);
    G.insert(j, j, 1/_value);
    cout << '\t' << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}


Capacitor::Capacitor(const string& name):Device(name) {};
Capacitor::~Capacitor() {};
void Capacitor::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B, Mat<REAL>& LT, vector<string*>& X, vector<string*>& Y, vector<string*>& U, int aux_offset)
{
    int i = _pnode - 1;
    int j = _nnode - 1;
	C.insert(i, i, _value);
    C.insert(i, j, -_value);
    C.insert(j, i, -_value);
    C.insert(j, j, _value);
	cout << '\t' << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}


Inductor::Inductor(const string &name) : Device(name) {};
Inductor::~Inductor() {};
int Inductor::auxNode() const {return _aux_node;}
void Inductor::setAux(int s) {_aux_node = s;}
void Inductor::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B, Mat<REAL>& LT, vector<string*>& X, vector<string*>& Y, vector<string*>& U, int aux_offset)
{
    int i = _pnode - 1;
    int j = _nnode - 1;
    int k = _aux_node + aux_offset - 1;
	C.insert(k, k, _value);
    G.insert(i, k, 1);
    G.insert(j, k, -1);
    G.insert(k, i, -1);
    G.insert(k, j, 1);
	cout << '\t' << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}


Mutual::Mutual(const string &name) : Device(name) {};
Mutual::~Mutual() {};
int Mutual::auxPosNode() const {return _aux_node_pos;}
void Mutual::setAuxPos(int s) {_aux_node_pos = s;}
int Mutual::auxNegNode() const {return _aux_node_neg;}
void Mutual::setAuxNeg(int s) {_aux_node_neg = s;}
string Mutual::ind1() const {return _ind1;}
void Mutual::setInd1(const string& l) {_ind1=l;}
string Mutual::ind2() const {return _ind2;}
void Mutual::setInd2(const string& l) {_ind2=l;}
void Mutual::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B, Mat<REAL>& LT, vector<string*>& X, vector<string*>& Y, vector<string*>& U, int aux_offset)
{
    int i = _aux_node_pos + aux_offset - 1;
    int j = _aux_node_neg + aux_offset - 1;
    C.insert(i, j, -_value);
    C.insert(j, i, -_value);
    cout << '\t' << _name << ' ' << _ind1 << ' ' << _ind2 << ' ' << _value << endl;
}


Isrc::Isrc(const string &name) : Device(name) {};
Isrc::~Isrc() {};
int Isrc::inIdx() const {return _in_index;}
void Isrc::setIn(int in) {_in_index = in;}
void Isrc::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B, Mat<REAL>& LT, vector<string*>& X, vector<string*>& Y, vector<string*>& U, int aux_offset)
{
    string *tmp = new string(_name);
    U[_in_index] = tmp;

    int i = _pnode - 1;
    int j = _nnode - 1;
    B.insert(i, _in_index, _value);     // _in_index is 0-based
    B.insert(j, _in_index, -_value);
    
    cout << '\t' << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}


Vsrc::Vsrc(const string &name) : Device(name) {};
Vsrc::~Vsrc() {};
int Vsrc::auxNode() const {return _aux_node;}
void Vsrc::setAux(int s) {_aux_node = s;}
int Vsrc::inIdx() const {return _in_index;}
void Vsrc::setIn(int in) {_in_index = in;}
void Vsrc::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B, Mat<REAL>& LT, vector<string*>& X, vector<string*>& Y, vector<string*>& U, int aux_offset)
{
    string *tmp = new string(_name);
    U[_in_index] = tmp;   

    int i = _pnode - 1;
    int j = _nnode - 1;
    int k = _aux_node + aux_offset - 1;
    G.insert(i, k, 1);
    G.insert(j, k, -1);
    G.insert(k, i, -1);
    G.insert(k, j, 1);
    B.insert(k, _in_index, 1);
 
    cout << '\t' << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}

Subckt::Subckt(const string &name) : Device(name) {};
Subckt::~Subckt() {};
void Subckt::addPort(int p) {_port_list.push_back(p);}
int Subckt::getPort(int index) const {
    if (index >= _port_list.size()){
        printf("invalid port index.\n");
        return -1;
    } else {
        return _port_list[index];
    }
}
void Subckt::setSubcktName(const string& subckt_name) {_subckt_name = subckt_name;}
string Subckt::getSubcktName() const {return _subckt_name;}
void Subckt::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B, Mat<REAL>& LT, vector<string*>& X, vector<string*>& Y, vector<string*>& U, int aux_offset)
{

    

    cout << '\t' << _name << ' ';
    for(int i = 0; i < _port_list.size(); ++i)
        cout << _port_list[i] << ' ';
    cout << _subckt_name.c_str() << '\n';
}


SubcktDef::SubcktDef(const string& name) : _size(-1) {_name = name;};
SubcktDef::~SubcktDef() {};
void SubcktDef::addPortName(const string& portname) {
    _port_list.push_back(new string(portname));
};
string SubcktDef::getPortName(int index) const {
    if (index >= _port_list.size()){
        printf("invalid port index.\n");
        return string();
    } else {
        return *(_port_list[index]);
    }
};
int SubcktDef::getSize(map<string, int>& _subckt_list, vector<SubcktDef*>& _subckt_def_list) {  // call it after all subckt are read
    if (_size == -1) {
        int tmp = 0;
        for (int i = 0; i < _dev_list.size(); ++i){
            Subckt *dev = dynamic_cast<Subckt*>(_dev_list[i]);
            if (dev != nullptr){
                string name = dev->getSubcktName();
                tmp += _subckt_def_list[_subckt_list[name]]->getSize(_subckt_list, _subckt_def_list);
            } else {
                ++tmp;
            };
        }
        _size = tmp;
    }
    return _size;
};
