///
/// @file   inductor.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:32:59 2008
/// 
/// @brief  implementation of inductor
/// 
/// 
///

#include "myspice.h"


/// \brief Constructor
/// \param name name of the inductor
Inductor::Inductor(const string &name) : Device(name) {};


/// \brief Destructor
Inductor::~Inductor() {};


/// \brief Get auxiliary node
///
///
/// @return auxiliary node (current through the inductor)
///
int Inductor::auxNode() const {return _aux_node;}


/// \brief set auxiliary node number
///
/// @param s auxiliary node number
///
void Inductor::setAux(int s) {_aux_node = s;}


/// \brief stamping function of the inductor
///
/// @param C system matrix \f$ C \f$
/// @param G system matrix \f$ G \f$
/// @param B system matrix \f$ B \f$
///
/// \todo You have to fills in each stamp function. 
/// 
void Inductor::stamp(Mat<REAL>& C, Mat<REAL>& G, Mat<REAL>& B)
{
	C.insert(_aux_node, _aux_node, _value);
    G.insert(_nnode, _aux_node, 1);
    G.insert(_pnode, _aux_node, -1);
    G.insert(_aux_node, _nnode, -1);
    G.insert(_aux_node, _pnode, 1);
	cout << _name << ' ' << _pnode << ' ' << _nnode << ' ' << _value << endl;
}
