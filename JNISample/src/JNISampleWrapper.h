/*
 * JNISampleWrapper.h
 *
 *  Created on: 2018/09/15
 *      Author: Yuma Y
 */

#ifndef JNISAMPLEWRAPPER_H_
#define JNISAMPLEWRAPPER_H_

#include <jni.h>
#include <string>

class Object;

class JNISampleWrapper {
public:
	JNISampleWrapper();
	~JNISampleWrapper();

	void print(void);
	void printValues(void);
	int getIvalue(void);
	void setIvalue(int);
	double getDvalue(void);
	void setDvalue(double);
	bool isBool(void);
	void setBool(bool);
	std::string getString(void);
	void setMessage(std::string message);

private:
	void initJNI(void);
	void exceptionCheck(void);

	JavaVM *jvm;
	JNIEnv *env;
	jclass sample;
	jobject object;
};

#endif /* JNISAMPLEWRAPPER_H_ */
