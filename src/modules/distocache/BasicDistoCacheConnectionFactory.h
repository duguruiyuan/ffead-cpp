/*
	Copyright 2009-2013, Sumeet Chhetri

    Licensed under the Apache License, Version 2.0 (const the& "License");
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
 * BasicDistoCacheConnectionFactory.h
 *
 *  Created on: 04-Apr-2013
 *      Author: sumeetc
 */

#ifndef BASICDISTOCACHECONNECTIONFACTORY_H_
#define BASICDISTOCACHECONNECTIONFACTORY_H_
#include "DistoCacheClientUtils.h"

class BasicDistoCacheConnectionFactory {
	static BasicDistoCacheConnectionFactory* instance;
	string host;
	int port;
	bool isSSL;
	BasicDistoCacheConnectionFactory(const string& host, const int& port, const bool& isSSL= false);
public:
	virtual ~BasicDistoCacheConnectionFactory();
	static void init(const string& host, const int& port, const bool& isSSL= false);
	static void destroy();
	static DistoCacheClientUtils* getConnection();
	static void releaseConnection(DistoCacheClientUtils* clientUtil);
};

#endif /* BASICDISTOCACHECONNECTIONFACTORY_H_ */
