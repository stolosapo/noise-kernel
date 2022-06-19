#ifndef Exception_h__
#define Exception_h__

#include <iostream>
#include <exception>

using namespace std;

namespace NoiseKernel
{
    class RuntimeException: public exception
    {
    private:
        const char* _cause;

    public:
        RuntimeException(const char* cause);
        virtual ~RuntimeException() throw();

        virtual const char* what() const throw();
        virtual const char* cause() const throw();
    };

    class DomainErrorCode
    {
    private:
        const char* _code;
        const char* _cause;

    public:
        DomainErrorCode(const char* code, const char* cause);
        virtual ~DomainErrorCode();

        virtual const char* code() const;
        virtual const char* cause() const;
    };

    class DomainException: public RuntimeException
    {
    private:
        const DomainErrorCode& _errorCode;
        string _arg;

    public:
        DomainException(const DomainErrorCode& errorCode);
        DomainException(const DomainErrorCode& errorCode, string arg);
        virtual ~DomainException() throw();

        virtual const char* fullError() const throw();
        virtual string message() const throw();
        virtual const char* code() const throw();
    };

    string handle(RuntimeException& e);
    string handle(DomainException& e);
}

#endif // Exception_h__
