//
//  main.cpp
//  StreamJSON
//
//  Created by YuanXuan on 6/11/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

string::size_type FindNextTokenIndex(const string& content, string::size_type startIndex)
{
    bool found = false;
    
    while (startIndex < content.length() && !found)
    {
        char ch = content.at(startIndex);
        
        if (ch == '"')
        {
            startIndex = content.find('"', startIndex + 1);
            if (startIndex == string::npos)
            {
                // invalid
                break;
            }
            else if (content.at(startIndex - 1) != '\\')
            {
                ++startIndex;
            }
            
        }
        else if (ch == '{' || ch == '}')
        {
            found = true;
        }
        else if (ch == '[' || ch == ']')
        {
            found = true;
        }
        else if (ch == ',')
        {
            found = true;
        }
        else
        {
            ++startIndex;
        }
        
    }
    return found ? startIndex : string::npos;
}

void PrintIndent(int tabs)
{
    for (int i = 0; i < tabs; ++i)
    {
        cout << "    ";
    }
}

void ParseAndOutputByLine(string& content)
{
    int indent = 0;
    
    string::size_type begin = content.find('{');
    string::size_type pos;
    
    // print content before JSON
    if (begin == string::npos)
    {
        cout << content << endl;
        return;
    }
    else if (begin > 0)
    {
        cout << content.substr(0, begin) << endl;
    }
    
    while ((pos = FindNextTokenIndex(content, begin)) != string::npos)
    {
        // print indent
        PrintIndent(indent);

        
        // print content before token
        string sub = content.substr(begin, pos - begin);
        cout << sub;
        
        
        // increase or decrease indent
        char token = content.at(pos);
        bool newLineToken = false;
        
        switch (token)
        {
            case '{':   ++indent; break;
            case '[':   ++indent; break;
            case '}':   --indent; newLineToken = true; break;
            case ']':   --indent; newLineToken = true; break;
            default:
                break;
        }
        
        if (indent < 0)
            indent = 0;
        
        // print token and indents before token
        if (newLineToken)
        {
            cout << endl;
            PrintIndent(indent);
        }
        cout << token << endl;
        
        // prepare next
        begin = pos + 1;
    }
    
    if (begin < content.length() - 1)
    {
        PrintIndent(indent);
        cout << content.substr(begin, content.length()) << endl;
    }
    
    
}

int main(int argc, const char * argv[]) {
    
    string content;
    
    while (getline(cin,content))
//    while (!cin.eof())
    {
//        cin >> content
        ParseAndOutputByLine(content);
    }
}
