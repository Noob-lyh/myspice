///
/// @file   device.h
/// @author Yinghai
/// @date   Fri Sep 12 13:37:14 2008
/// 
/// @brief  The header of Device class
/// 
/// 
///

#include "myspice.h"

/// \brief Constructor
Device::Device(const string &name): _name(name),_pnode(0),_nnode(0),_value(0) {};

/// \brief destructor
Device::~Device() {};

/// \brief Set the positive node number
///
/// @param p node number
///
void Device::setPnode(int p) {_pnode = p;}

/// \brief Get the positive node number
///
///
/// @return positive node number of this device
///
int Device::pnode() const {return _pnode;}

/// \brief Set the negative node number
///
/// @param p node number
///
void Device::setNnode(int p) {_nnode = p;}

/// \brief Get the negative node number
///
///
/// @return negative node number of this device
///
int Device::nnode() const {return _nnode;}  

/// \brief Set the value of this device
///
/// @param d value
///
/// The value could be capacitance, conductance or mutual inductance coefficient 
/// and etc. Store what you want. 
void Device::setValue(double d) {_value = d;}

/// \brief Get the value of this device
///
///
/// @return value
///
double Device::value() const {return _value;}

/// \brief Set the name of this device
///
/// @param n device name
///
void Device::setName(const string& n) {_name = n;}

/// \brief Get the name of this device
///
///
/// @return name of this device
///
string Device::name() const {return _name;}