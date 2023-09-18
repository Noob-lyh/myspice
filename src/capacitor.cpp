///
/// @file   cap.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:25:35 2008
/// 
/// @brief  implementation of Capacitor
/// 
/// 
///

#include "myspice.h"

/// \brief Constructor
/// \param name name of the capacitor
Capacitor::Capacitor(const string& name):Device(name) {};

/// \brief Destructor
Capacitor::~Capacitor() {};

/// \brief stamping function of the capacitor
///
/// @param C system matrix \f$ C \f$
/// @param G system matrix \f$ G \f$
/// @param B system matrix \f$ B \f$
///
/// \todo You have to fills in each stamp function. 
/// 
void Capacitor::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B)
{
  

  cout << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}


