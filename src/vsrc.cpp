///
/// @file   vsrc.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:53:40 2008
/// 
/// @brief  implementation of voltage source
/// 
/// 
///

#include "myspice.h"


/// \brief Constructor
/// \param name name of the voltage source
Vsrc::Vsrc(const string &name) : Device(name) {};


/// \brief Destructor
Vsrc::~Vsrc() {};

  
/// \brief Get auxiliary node
///
/// @return auxiliary node (current through the inductor)
int Vsrc::auxNode() const {return _aux_node;}


/// \brief set auxiliary node number
///
/// @param s auxiliary node number
///
void Vsrc::setAux(int s) {_aux_node = s;}


/// \brief stamping function of the voltage source
///
/// @param C system matrix \f$ C \f$
/// @param G system matrix \f$ G \f$
/// @param B system matrix \f$ B \f$
///
/// \todo You have to fills in each stamp function. 
///
void Vsrc::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B)
{
  

  cout << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}