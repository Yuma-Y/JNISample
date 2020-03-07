/*
 * main.cpp
 *
 *  Created on: 2018/09/15
 *      Author: Yuma Y
 */

#include <iostream>
#include "JNISampleWrapper.h"

int main(void){
	JNISampleWrapper wrapper;
	wrapper.print();
	wrapper.printValues();

	wrapper.setBool(true);
	wrapper.setIvalue(100);
	wrapper.setDvalue(3.14);
	wrapper.setMessage("JNI has connected");
	wrapper.print();
	wrapper.printValues();

	std::cout << "bool = " << wrapper.isBool() << std::endl;
	std::cout << "ivalue = " << wrapper.getIvalue() << std::endl;
	std::cout << "dvalue = " << wrapper.getDvalue() << std::endl;
	std::cout << "string = " << wrapper.getString() << std::endl;

	return 0;
}


