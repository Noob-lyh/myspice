///
/// @file   isrc.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:45:16 2008
/// 
/// @brief  implementation of current source
/// 
/// 
///

#include "myspice.h"


/// \brief Constructor
/// \param name name of the current source
Isrc::Isrc(const string &name) : Device(name) {};


/// \brief Destructor
Isrc::~Isrc() {};


/// \brief stamping function of the current source
///
/// @param C system matrix \f$ C \f$
/// @param G system matrix \f$ G \f$
/// @param B system matrix \f$ B \f$
///
/// \todo You have to fills in each stamp function. 
///
void Isrc::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B)
{
  

  cout << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}
