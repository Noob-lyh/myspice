///
/// @file   mat.cpp
/// @author 
/// @date   Fri Sep 12 14:06:47 2008
/// 
/// @brief  Header of the Matrix class
/// 
/// 
///

#include "myspice.h"


/// \class Mat 
///
/// \brief the matrix class
///
/// This is an empty class. You have to design you own Matrix class by
/// adding necessary data and public functions. \n
///
/// To facilliate the stamping process, the matrix class needs to satisfy 
/// the following condition:
/// - Dynamic allocation of the memory according to the size of the circuit.
/// - Expandable. Each time we stamp an element, the entries of the matrix may grow.
/// - Flexible and efficient. Most of the entries in the matrix would be zero and we don't need to store them. 
///
/// My advice is: Using orthogonal list data structure. \n
///
/// Currently, this class is designed as a C++ template. If you're not familliar with 
/// the concept of template. Just define a non-template class and do the same thing.


/// \brief Constructor
/// \param nrow #rows
/// \param ncol #columns
///
/// \todo Allocate the memory with given size of the matrix
template<class T>
Mat<T>::Mat(int nrow, int ncol) : _row(nrow), _col(ncol), _nnz(0), _row_pointer(NULL), _col_index(NULL), _csr_value(NULL) {}


/// \brief Destructor
///
/// \todo release the allocated memory
template<class T>
Mat<T>::~Mat(){
    if (_row_pointer) delete _row_pointer;
    if (_col_index) delete _col_index;
    if (_csr_value) delete _csr_value;
}

/// \brief insert nonezeros
template<class T>
void Mat<T>::insert(int _row, int _col, REAL _value){
    if( _row == 0 || _col == 0 )
        return;
    
};

template class Mat<double>;
template class Mat<float>;