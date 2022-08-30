#pragma once

class InputParser {
private:
    vector <string> _tokens;
public:
    // Constructor
    InputParser(int& argc, char** argv)
    {
        for (int i = 1; i < argc; i++) // The constructor puts all string-argument values in the vector of the class
            _tokens.push_back(string(argv[i]));
    }
    // Methods checks if the string input appears in the vector of the class. If it does - it returns the string input, else - it returns a blank string
    const string& getCmdOption(const string& option) const
    {
        static const string empty_string("");
        if (std::find(_tokens.begin(), _tokens.end(), option) == _tokens.end())
            return empty_string;
        return option;
    }
};