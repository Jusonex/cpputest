/*
 * Copyright (c) 2007, Michael Feathers, James Grenning and Bas Vodde
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef D_MockActualCall_h
#define D_MockActualCall_h

#include "CppUTest/CppUTestConfig.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockNamedValue.h"
#include "CppUTestExt/MockExpectedCallsList.h"

class MockFailureReporter;
class MockFailure;

class MockActualCall
{
public:
    MockActualCall();
    virtual ~MockActualCall();

    virtual MockActualCall& withName(const SimpleString& name)=0;
    virtual MockActualCall& withCallOrder(unsigned int callOrder)=0;
    MockActualCall& withParameter(const SimpleString& name, bool value) { return withBoolParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, int value) { return withIntParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, unsigned int value) { return withUnsignedIntParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, long int value) { return withLongIntParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, unsigned long int value) { return withUnsignedLongIntParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, cpputest_longlong value) { return withLongLongIntParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, cpputest_ulonglong value) { return withUnsignedLongLongIntParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, double value) { return withDoubleParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, const char* value) { return withStringParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, void* value) { return withPointerParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, void (*value)()) { return withFunctionPointerParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, const void* value) { return withConstPointerParameter(name, value); }
    MockActualCall& withParameter(const SimpleString& name, const unsigned char* value, size_t size) { return withMemoryBufferParameter(name, value, size); }
    virtual MockActualCall& withParameterOfType(const SimpleString& typeName, const SimpleString& name, const void* value)=0;
    virtual MockActualCall& withOutputParameter(const SimpleString& name, void* output)=0;
    virtual MockActualCall& withOutputParameterOfType(const SimpleString& typeName, const SimpleString& name, void* output)=0;

    virtual MockActualCall& withBoolParameter(const SimpleString& name, bool value)=0;
    virtual MockActualCall& withIntParameter(const SimpleString& name, int value)=0;
    virtual MockActualCall& withUnsignedIntParameter(const SimpleString& name, unsigned int value)=0;
    virtual MockActualCall& withLongIntParameter(const SimpleString& name, long int value)=0;
    virtual MockActualCall& withUnsignedLongIntParameter(const SimpleString& name, unsigned long int value)=0;
    virtual MockActualCall& withLongLongIntParameter(const SimpleString& name, cpputest_longlong value)=0;
    virtual MockActualCall& withUnsignedLongLongIntParameter(const SimpleString& name, cpputest_ulonglong value)=0;
    virtual MockActualCall& withDoubleParameter(const SimpleString& name, double value)=0;
    virtual MockActualCall& withStringParameter(const SimpleString& name, const char* value)=0;
    virtual MockActualCall& withPointerParameter(const SimpleString& name, void* value)=0;
    virtual MockActualCall& withFunctionPointerParameter(const SimpleString& name, void (*value)())=0;
    virtual MockActualCall& withConstPointerParameter(const SimpleString& name, const void* value)=0;
    virtual MockActualCall& withMemoryBufferParameter(const SimpleString& name, const unsigned char* value, size_t size)=0;

#if defined(__cplusplus) && __cplusplus >= 201103L
    template<typename E, typename = typename std::enable_if<std::is_enum<E>::value>::type>
    MockActualCall& withParameter(const SimpleString& name, E enumValue)
    {
        return withParameter(name, static_cast<typename std::underlying_type<E>::type>(enumValue));
    }
#endif

    virtual bool hasReturnValue()=0;
    virtual MockNamedValue returnValue()=0;

    virtual bool returnBoolValueOrDefault(bool default_value)=0;
    virtual bool returnBoolValue()=0;

    virtual int returnIntValueOrDefault(int default_value)=0;
    virtual int returnIntValue()=0;

    virtual unsigned long int returnUnsignedLongIntValue()=0;
    virtual unsigned long int returnUnsignedLongIntValueOrDefault(unsigned long int default_value)=0;

    virtual long int returnLongIntValue()=0;
    virtual long int returnLongIntValueOrDefault(long int default_value)=0;

    virtual cpputest_ulonglong returnUnsignedLongLongIntValue()=0;
    virtual cpputest_ulonglong returnUnsignedLongLongIntValueOrDefault(cpputest_ulonglong default_value)=0;

    virtual cpputest_longlong returnLongLongIntValue()=0;
    virtual cpputest_longlong returnLongLongIntValueOrDefault(cpputest_longlong default_value)=0;

    virtual unsigned int returnUnsignedIntValue()=0;
    virtual unsigned int returnUnsignedIntValueOrDefault(unsigned int default_value)=0;

    virtual const char * returnStringValueOrDefault(const char * default_value)=0;
    virtual const char * returnStringValue()=0;

    virtual double returnDoubleValue()=0;
    virtual double returnDoubleValueOrDefault(double default_value)=0;

    virtual void * returnPointerValue()=0;
    virtual void * returnPointerValueOrDefault(void * default_value)=0;

    virtual const void * returnConstPointerValue()=0;
    virtual const void * returnConstPointerValueOrDefault(const void * default_value)=0;

    virtual void (*returnFunctionPointerValue())()=0;
    virtual void (*returnFunctionPointerValueOrDefault(void (*default_value)()))()=0;

    bool returnValueOrDefault(bool default_value) { return returnBoolValueOrDefault(default_value); }
    int returnValueOrDefault(int default_value) { return returnIntValueOrDefault(default_value); }
    unsigned long int returnValueOrDefault(unsigned long int default_value) { return returnUnsignedLongIntValueOrDefault(default_value); }
    long int returnValueOrDefault(long int default_value) { return returnLongIntValueOrDefault(default_value); }
    cpputest_ulonglong returnValueOrDefault(cpputest_ulonglong default_value) { return returnUnsignedLongLongIntValueOrDefault(default_value); }
    cpputest_longlong returnValueOrDefault(cpputest_longlong default_value) { return returnLongLongIntValueOrDefault(default_value); }
    unsigned int returnValueOrDefault(unsigned int default_value) { return returnUnsignedIntValueOrDefault(default_value); }
    const char * returnValueOrDefault(const char * default_value) { return returnStringValueOrDefault(default_value); }
    double returnValueOrDefault(double default_value) { return returnDoubleValueOrDefault(default_value); }
    void * returnValueOrDefault(void * default_value) { return returnPointerValueOrDefault(default_value); }
    const void * returnValueOrDefault(const void * default_value) { return returnConstPointerValueOrDefault(default_value); }
    void (*returnValueOrDefault(void (*default_value)()))() { return returnFunctionPointerValueOrDefault(default_value); }

#if defined(__cplusplus) && __cplusplus >= 201103L
    template<typename E, typename = typename std::enable_if<std::is_enum<E>::value>::type>
    E returnValueOrDefault(E enumValue)
    {
      return static_cast<E>(returnValueOrDefault(static_cast<typename std::underlying_type<E>::type>(enumValue)));
    }
#endif

    virtual MockActualCall& onObject(const void* objectPtr)=0;
};

#endif
