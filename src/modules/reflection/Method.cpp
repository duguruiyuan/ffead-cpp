/*
	Copyright 2009-2012, Sumeet Chhetri 
  
    Licensed under the Apache License, Version 2.0 (the "License"); 
    you may not use this file except in compliance with the License. 
    You may obtain a copy of the License at 
  
        http://www.apache.org/licenses/LICENSE-2.0 
  
    Unless required by applicable law or agreed to in writing, software 
    distributed under the License is distributed on an "AS IS" BASIS, 
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
    See the License for the specific language governing permissions and 
    limitations under the License.  
*/
/*
 * Method.cpp
 *
 *  Created on: Oct 10, 2009
 *      Author: sumeet
 */

#include "Method.h"

Method::Method() {
	// TODO Auto-generated constructor stub

}

Method::~Method() {
	// TODO Auto-generated destructor stub
}

const string& Method::getAccessSpecifier() const
{
	return accessSpecifier;
}

void Method::setAccessSpecifier(const string& accessSpecifier)
{
	this->accessSpecifier = accessSpecifier;
}

const string& Method::getMethodName() const
{
	return methodName;
}

void Method::setMethodName(const string& methodName)
{
	this->methodName = methodName;
}

const string& Method::getReturnType() const
{
	return returnType;
}

void Method::setReturnType(const string& returnType)
{
	this->returnType = returnType;
}

args Method::getArgumentTypes() const
{
	return argumentTypes;
}

void Method::setArgumentTypes(const args& argumentTypes)
{
	this->argumentTypes = argumentTypes;
}

int Method::getArgNum() const
{
	return this->argumentTypes.size();
}

void Method::clear()
{
	accessSpecifier ="";
	methodName="";
	returnType="";
	argumentTypes.clear();
}

bool Method::isStatic()
{
	return isstat;
}

void Method::setIsStatic(const bool& isStatic)
{
	this->isstat = isStatic;
}

const string& Method::getRefName() const {
	return refName;
}

void Method::setRefName(const string& refName) {
	this->refName = refName;
}
/*string Method::getKey()
{
	string key = getMethodName();
	for (unsigned int var = 0; var < getArgumentTypes().size(); var++)
	{
		if(getArgumentTypes().at(var)!="")
			key += getArgumentTypes().at(var);
	}
	return key;
}*/
