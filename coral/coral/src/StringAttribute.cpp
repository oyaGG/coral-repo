// <license>
// Copyright (C) 2011 Andrea Interguglielmi, All rights reserved.
// This file is part of the coral repository downloaded from http://code.google.com/p/coral-repo.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
// 
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// </license>

#include "StringAttribute.h"

using namespace coral;

void String::setStringValue(std::string value)
{
	_value = value;
}

const std::string& String::stringValue()
{
	return _value;
}

std::string String::asString()
{
	std::string val = stringUtils::replace(_value, "\n", "\\n");
	return val;
}

void String::setFromString(const std::string &value)
{
	_value = value;
}

StringAttribute::StringAttribute(const std::string &name, Node *parent)
	: Attribute(name, parent)
	, _longString(false)
{
	setClassName("StringAttribute");
	String *ptr = new String();
	setValuePtr(ptr);
	
	std::vector<std::string> allowedSpecialization;
	allowedSpecialization.push_back("String");
	setAllowedSpecialization(allowedSpecialization);
}

String* StringAttribute::value()
{
	return (String*)Attribute::value();
}

String* StringAttribute::outValue()
{
	return (String*)Attribute::outValue();
}

void StringAttribute::setLongString(bool value)
{
	_longString = value;
}

bool StringAttribute::longString()
{
	return _longString;
}
