#ifndef __MYSPICE_H__
#define __MYSPICE_H__

#include<iostream>
#include<vector>
#include<map>
#include<string>

using std::vector;
using std::map;
using std::string;

using std::cout;
using std::endl;


// ===================================== defines =====================================

#define REAL double // default precision

#define MYSPICE_SUCCESS             (0)
#define MYSPICE_ARGUMENT_ERROR      (-1)
#define MYSPICE_FILE_CANNOT_OPEN    (-2)
#define MYSPICE_FILE_FORMAT_ERROR   (-3)



// ===================================== class def =====================================

template<class T>
class Mat{
public:
  Mat(int, int);
  ~Mat();
  int row() const;
  int column() const;
private:
  int _row;
  int _col;
};


class Device {
public:
  Device(const string&);
  virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&) = 0;
  virtual ~Device();
  void setPnode(int);
  int pnode() const;
  void setNnode(int);
  int nnode() const;
  void setValue(double);
  double value() const;
  void setName(const string&);
  string name() const;
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
  virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&);
};


class Capacitor: public Device{
public:
  Capacitor(const string&);
  virtual ~Capacitor();
  virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&);
};


class Inductor: public Device{
public:
  Inductor(const string&);
  virtual ~Inductor();
  virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&);
  int auxNode() const;
  void setAux(int);
private:
  int _aux_node;
};


class Isrc: public Device{
public:
  Isrc(const string&);
  virtual ~Isrc();
  virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&);
};

class Vsrc: public Device{
public:
  Vsrc(const string&);
  virtual ~Vsrc();
  virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&);
  int auxNode() const;
  void setAux(int);
private:
  int _aux_node;
};

class Mutual: public Device{
public:
  Mutual(const string&);
  virtual ~Mutual();
  virtual void stamp(Mat<REAL>&, Mat<REAL>&, Mat<REAL>&);
  int auxPosNode() const;
  void setAuxPos(int);
  int auxNegNode() const;
  void setAuxNeg(int);
  string ind1() const;
  void setInd1(const string&);
  string ind2() const;
  void setInd2(const string&);
private:
  int _aux_node_pos;
  int _aux_node_neg;
  string _ind1;
  string _ind2;
};

class Stamp{
public:
  typedef vector<Device*> devList;
  typedef map<std::string, int> nodeList;
  Stamp();
  ~Stamp();
  void parse(char*);
  void output(char*);
  void setup();
private:
  devList _dev_list;
  nodeList _node_list;
  vector<int> _probe_list;
  Mat<REAL>* _C;
  Mat<REAL>* _G;
  Mat<REAL>* _B;
  Mat<REAL>* _LT;
  int _num_in;
  int _num_out;
};


// ===================================== funtions def =====================================

// argparse.cpp
void help_message();
int argparse(int, char**, int*, double*, char*);

// utils.cpp
string tokenizer(string&, const string&);
void capitalize(string &);
double to_double(string &); 

#endif