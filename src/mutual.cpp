///
/// @file   mutual.cpp
/// @author Yinghai
/// @date   Fri Sep 12 15:06:23 2008
/// 
/// @brief  implementation of mutual inductance
/// 
/// 
///

#include "myspice.h"


/// \brief Constructor
/// \param name name of the mutual inductance
Mutual::Mutual(const string &name) : Device(name) {};


/// \brief Destructor
Mutual::~Mutual() {};


/// \brief return the auxiliary current node  of L1
/// @return auxiliary current node of L1
int Mutual::auxPosNode() const {return _aux_node_pos;}


/// \brief set the auxiliary current node  of L1
/// @param s auxiliary current node of L1
void Mutual::setAuxPos(int s) {_aux_node_pos = s;}


/// \brief return the auxiliary current node  of L2
/// @return auxiliary current node of L2
int Mutual::auxNegNode() const {return _aux_node_neg;}


/// \brief set the auxiliary current node  of L2
/// @param s auxiliary current node of L2
void Mutual::setAuxNeg(int s) {_aux_node_neg = s;}


/// \brief return the name of L1
/// @return name of inductor L1
string Mutual::ind1() const {return _ind1;}


/// \brief set the name of L1
/// @param l  name of inductor L1
void Mutual::setInd1(const string& l) {_ind1=l;}


/// \brief return the name of L2
/// @return name of inductor L2
string Mutual::ind2() const {return _ind2;}


/// \brief set the name of L2
/// @param l  name of inductor L2
void Mutual::setInd2(const string& l) {_ind2=l;}


/// \brief stamping function of the mutual inductance
///
/// @param C system matrix \f$ C \f$
/// @param G system matrix \f$ G \f$
/// @param B system matrix \f$ B \f$
///
/// \todo You have to fills in each stamp function. 
/// 
void Mutual::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B)
{
  

  cout << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}