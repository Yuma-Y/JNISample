/*
 * JNISampleWrapper.cpp
 *
 *  Created on: 2018/09/15
 *      Author: Yuma Y
 */

#include "JNISampleWrapper.h"
#include <iostream>

JNISampleWrapper::JNISampleWrapper()
	: jvm(NULL), env(NULL), sample(NULL), object(NULL) {
	initJNI();
}

JNISampleWrapper::~JNISampleWrapper() {
	// DestroyJavaVMしても内部的には意味がないらしいが一応
	jvm->DestroyJavaVM();
}

void JNISampleWrapper::print(void) {
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "print", "()V");
		exceptionCheck();
		if (id != NULL) {
			env->CallVoidMethod(object, id);
			exceptionCheck();
		}
	}
}

void JNISampleWrapper::printValues(void) {
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "printValues", "()V");
		exceptionCheck();
		if (id != NULL) {
			env->CallVoidMethod(object, id);
			exceptionCheck();
		}
	}
}

int JNISampleWrapper::getIvalue(void) {
	jint ret = 0;
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "getIvalue", "()I");
		exceptionCheck();
		if (id != NULL) {
			ret = env->CallIntMethod(object, id);
			exceptionCheck();
		}
	}

	return static_cast<int>(ret);
}

void JNISampleWrapper::setIvalue(int int1) {
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "setIvalue", "(I)V");
		exceptionCheck();
		if (id != NULL) {
			env->CallVoidMethod(object, id, int1);
			exceptionCheck();
		}
	}
}

double JNISampleWrapper::getDvalue(void) {
	jdouble ret = 0.0;
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "getDvalue", "()D");
		exceptionCheck();
		if (id != NULL) {
			ret = env->CallDoubleMethod(object, id);
			exceptionCheck();
		}
	}

	return static_cast<double>(ret);
}

void JNISampleWrapper::setDvalue(double double1) {
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "setDvalue", "(D)V");
		exceptionCheck();
		if (id != NULL) {
			env->CallVoidMethod(object, id, double1);
			exceptionCheck();
		}
	}
}

bool JNISampleWrapper::isBool(void) {
	jboolean ret = false;
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "isBool", "()Z");
		exceptionCheck();
		if (id != NULL) {
			ret = env->CallBooleanMethod(object, id);
			exceptionCheck();
		}
	}

	return static_cast<bool>(ret);
}

void JNISampleWrapper::setBool(bool bool1) {
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "setBool", "(Z)V");
		exceptionCheck();
		if (id != NULL) {
			env->CallVoidMethod(object, id, bool1);
			exceptionCheck();
		}
	}
}

std::string JNISampleWrapper::getString(void) {
	std::string ret = "";

	// stringだけは、Object型として取得しjstringにキャストした後
	// GetStringUTFChars()でchar*型に変換する
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "getMessage", "()Ljava/lang/String;");
		exceptionCheck();
		if (id != NULL) {
			jstring str = static_cast<jstring>(env->CallObjectMethod(object, id));
			exceptionCheck();

			const char* char_str = env->GetStringUTFChars(str, NULL);
			exceptionCheck();
			ret = char_str;
		}
	}

	return ret;
}

void JNISampleWrapper::setMessage(std::string message) {
	if (object != NULL) {
		jmethodID id = env->GetMethodID(sample, "setMessage", "(Ljava/lang/String;)V");
		exceptionCheck();
		if (id != NULL) {
			// NewStringUTF()で、char*からjstring型に変換してセットする必要あり
			jstring jstr = env->NewStringUTF(message.c_str());
			env->CallVoidMethod(object, id, jstr);
			exceptionCheck();
		}
	}
}

void JNISampleWrapper::initJNI(void) {
	// JVMの起動オプションなど
	JavaVMInitArgs vm_args;
	JavaVMOption options[3];

	options[0].optionString = "-Djava.compiler=NONE";           /* disable JIT */
	options[1].optionString = "-Djava.class.path=./JNISample.jar"; /* user classes */
	// options[2].optionString = "-verbose:class";                   /* print JNI-related messages */
	options[2].optionString = "";

	vm_args.version = JNI_VERSION_1_8;
	vm_args.options = options;
	vm_args.nOptions = 3;
	vm_args.ignoreUnrecognized = static_cast<int>(true);

	jint res = JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
	if (res != JNI_OK) {
		std::cout << "JVM create error" << std::endl;
	} else {
		// test.java.JNISampleクラスをロード
		sample = env->FindClass("test/java/JNISample");
		exceptionCheck();
		if (res != JNI_OK) {
			std::cout << "JNISample class not found!!" << std::endl;
		} else {
			// JNISampleクラスのインスタンスを生成する
			// <init>をメソッド名として指定し、GetMethodIDでコンストラクタのメソッドIDを得る。
			// それをNewObjectに渡すことでインスタンスが生成される
			jmethodID constructor = env->GetMethodID(sample, "<init>", "()V");
			exceptionCheck();
			if (constructor != NULL) {
				object = env->NewObject(sample, constructor);
				exceptionCheck();
			}
		}
	}
}

void JNISampleWrapper::exceptionCheck(void) {
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
	}
}
