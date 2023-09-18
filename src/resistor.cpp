///
/// @file   resistor.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:21:15 2008
/// 
/// @brief  implementation of Resistor
/// 
/// 
///

#include "myspice.h"


/// \brief Constructor
/// \param name name of the resistor
Resistor::Resistor(const string &name) : Device(name) {};


/// \brief Destructor
Resistor::~Resistor() {};


/// \brief stamping function of the resistor
///
/// @param C system matrix \f$ C \f$
/// @param G system matrix \f$ G \f$
/// @param B system matrix \f$ B \f$
///
/// \todo You have to fills in each stamp function. 
/// 
void Resistor::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B)
{
  

  cout << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}
