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
 * RegexUtil.cpp
 *
 *  Created on: 14-Aug-2012
 *      Author: sumeetc
 */

#include "RegexUtil.h"

map<string, regex_t> RegexUtil::patterns;
map<string, regex_t> RegexUtil::nlpatterns;
bool RegexUtil::cacheRegexes = false;

void RegexUtil::flushCache() {
	if(patterns.size()>0) {
		map<string, regex_t>::iterator it;
		for(it=patterns.begin();it!=patterns.end();++it) {
			regfree(&(it->second));
		}
		patterns.clear();
	}
	if(nlpatterns.size()>0) {
		map<string, regex_t>::iterator it;
		for(it=nlpatterns.begin();it!=nlpatterns.end();++it) {
			regfree(&(it->second));
		}
		nlpatterns.clear();
	}
}

void RegexUtil::getRegex(regex_t& regex, const string& pattern, const bool& matchNewLine) {
	if(cacheRegexes) {
		if(!matchNewLine && patterns.find(pattern)!=patterns.end()) {
			regex = patterns[pattern];
		} else if(nlpatterns.find(pattern)!=nlpatterns.end()) {
			regex = nlpatterns[pattern];
		}
	} else {
		int cflags = REG_EXTENDED;
		if(matchNewLine)
			cflags = REG_NEWLINE | REG_EXTENDED;

		int reti = regcomp(&regex, pattern.c_str(), cflags);
		if(reti!=0)
		{
			cout << ("Could not compile regex - "+pattern + " failed with error ") << reti << endl;
		}
		else if(cacheRegexes)
		{
			if(!matchNewLine) {
				patterns[pattern] = regex;
			} else {
				nlpatterns[pattern] = regex;
			}
		}
	}
}

void RegexUtil::find(const string& text, const string& pattern, int &spos, int &epos, const bool& matchNewLine/* = false*/)
{
	string ttext(text);
	regex_t regex;
	getRegex(regex, pattern, matchNewLine);
	spos = -1;
	epos = -1;
	regmatch_t pm;
	int reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	if(!cacheRegexes)regfree(&regex);
	if (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		spos = pm.rm_so;
		epos = pm.rm_eo;
	}
}

bool RegexUtil::matches(const string& text, const string& pattern, const bool& matchNewLine/* = false*/)
{
	string ttext(text);
	regex_t regex;
	getRegex(regex, pattern, matchNewLine);
	regmatch_t pm;
	int reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	if(!cacheRegexes)regfree(&regex);
	if (reti == 0) {    /* while matches found */
		return true;
	}
	return false;
}

int RegexUtil::find(const string& text, const string& pattern, const bool& matchNewLine/* = false*/)
{
	string ttext(text);
	regex_t regex;
	getRegex(regex, pattern, matchNewLine);
	regmatch_t pm;
	int reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	if(!cacheRegexes)regfree(&regex);
	if (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		return pm.rm_so;
	}
	return -1;
}

vector<string> RegexUtil::search(const string& text, const string& pattern, const bool& matchNewLine/* = false*/) {
	vector<string> vec;
	string ttext(text);
	regex_t regex;
	getRegex(regex, pattern, matchNewLine);
	regmatch_t pm;
	int reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	while (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		if(!reti) {
			string match;
			match = ttext.substr(pm.rm_so, pm.rm_eo-pm.rm_so);
			vec.push_back(match);
		} else {
			break;
		}
		ttext = ttext.substr(pm.rm_eo);
		pm.rm_eo = -1;
		pm.rm_so = -1;
		reti = regexec (&regex, ttext.c_str(), 1, &pm, 0);
	}
	if(!cacheRegexes)regfree(&regex);
	return vec;
}

string RegexUtil::replaceCopy(const string& text, const string& pattern, const string& with, const bool& matchNewLine/* = false*/) {
	string ttext(text);
	string rettxt;
	regex_t regex;
	getRegex(regex, pattern, matchNewLine);
	regmatch_t pm;
	int reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	while (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		if(!reti) {
			string match;
			match = ttext.substr(pm.rm_so, pm.rm_eo-pm.rm_so);
			rettxt += ttext.substr(0, pm.rm_so) + with;
		} else {
			rettxt += ttext;
			break;
		}
		ttext = ttext.substr(pm.rm_eo);
		pm.rm_eo = -1;
		pm.rm_so = -1;
		reti = regexec (&regex, ttext.c_str(), 1, &pm, 0);
	}
	if(!cacheRegexes)regfree(&regex);
	if(ttext!="")rettxt += ttext;

	if(text!=rettxt)
	{
		while(replace(rettxt, pattern, with, matchNewLine)) {}
	}
	return rettxt;
}

bool RegexUtil::replace(string& text, const string& pattern, const string& with, const bool& matchNewLine/* = false*/) {
	string ttext(text);
	string rettxt;
	regex_t regex;
	getRegex(regex, pattern, matchNewLine);
	regmatch_t pm;
	int reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	while (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		if(!reti) {
			string match;
			match = ttext.substr(pm.rm_so, pm.rm_eo-pm.rm_so);
			rettxt += ttext.substr(0, pm.rm_so) + with;
		} else {
			rettxt += ttext;
			break;
		}
		ttext = ttext.substr(pm.rm_eo);
		pm.rm_eo = -1;
		pm.rm_so = -1;
		reti = regexec (&regex, ttext.c_str(), 1, &pm, 0);
	}
	if(!cacheRegexes)regfree(&regex);
	if(ttext!="")rettxt += ttext;
	if(text==rettxt)
		return false;
	text = rettxt;
	while(replace(text, pattern, with, matchNewLine)) {}
	return true;
}

vector<string> RegexUtil::findWithGroups(const string& text, const string& pattern, const bool& matchNewLine) {
	vector<string> data;
	string ttext(text);
	regex_t regex;
	getRegex(regex, pattern, matchNewLine);
	regmatch_t pm[10];
	int reti = regexec(&regex, ttext.c_str(), 10, pm, 0);
	if(!cacheRegexes)regfree(&regex);
	if (reti == 0) {    /* while matches found */
		for (int i = 0; pm[i].rm_so != -1; i++)
		{
			string co = ttext.substr(pm[i].rm_so, pm[i].rm_eo-pm[i].rm_so);
			data.push_back(co);
		}
	}
	return data;
}

vector<string> RegexUtil::findWithGroups(const string& text, const string& pattern, const int& groupCount, const bool& matchNewLine /*= false*/) {
	vector<string> data;
	string ttext(text);
	regex_t regex;
	getRegex(regex, pattern, matchNewLine);
	regmatch_t pm[groupCount];
	int reti = regexec(&regex, ttext.c_str(), groupCount, pm, 0);
	if(!cacheRegexes)regfree(&regex);
	if (reti == 0) {    /* while matches found */
		for (int i = 0; pm[i].rm_so != -1; i++)
		{
			string co = ttext.substr(pm[i].rm_so, pm[i].rm_eo-pm[i].rm_so);
			data.push_back(co);
		}
	}
	return data;
}
