#include "Template.h"
template<class T>
CPair<T>::CPair() : first(0), second(0) {

}
template<class T>
CPair<T>::CPair(T firstVal, T secondVal) : first(firstVal), second(secondVal){
}
template<class T>
T CPair<T>::getFirst() const {
	return first;
}
template<class T>
void CPair<T>::setFirst(T nFirst) {
	first = nFirst;
}
template<class T>
T CPair<T>::getSecond() const {
	return second;
}
template<class T>
void CPair<T>::setSecond(T nSecond) {
	second = nSecond;
}