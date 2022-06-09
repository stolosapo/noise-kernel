#ifndef Argument_h__
#define Argument_h__

#include <vector>
#include <map>
#include <string>

using namespace std;

namespace NoiseKernel
{
    class Argument
    {
    private:
        string name;
        string value;

    public:
        Argument(const string& name, const string& value);
        Argument(const Argument& arg);
        virtual ~Argument();

        string getName() const;
        string getValue() const;
    };

    class ArgumentList
    {
    private:
        vector<Argument> arguments;

    public:
        ArgumentList(vector<Argument> args);
        virtual ~ArgumentList();

        const vector<Argument> getArguments() const;

        int size() const;
        bool exist(string name) const;
        string get(string name) const;
    };

    class ArgumentParser
    {
    private:
        static const char* COMMAND_PREFIX;

        bool isCommand(string arg);
        string trimCommand(string command);

    public:
        ArgumentParser();
        virtual ~ArgumentParser();

        ArgumentList parse(int argc, char* argv[]);
        void print(int argc, char* argv[]);
    };

    class ArgumentProvider
    {
    private:
        ArgumentList* arguments;

    public:
        ArgumentProvider(int argc, char* argv[]);
        virtual ~ArgumentProvider();

        bool hasArg(string name) const;
        string getStringValue(string name) const;
        int getIntValue(string name) const;
        bool getBoolValue(string name) const;
    };

    class ArgumentAdapter
    {
    private:
        ArgumentProvider* provider;

        map<string, string> registeredArgs;

        bool argExist(const string& name) const;

    public:
        ArgumentAdapter(ArgumentProvider* provider);
        virtual ~ArgumentAdapter();

        virtual string help();
        virtual void registerArguments() = 0;

    protected:
        virtual string title() = 0;
        void registerArg(string name, string description);

        bool hasArg(string name) const;
        string getStringValue(string name) const;
        int getIntValue(string name) const;
        bool getBoolValue(string name) const;
    };

}

#endif // Argument_h__
