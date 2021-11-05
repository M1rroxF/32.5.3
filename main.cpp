#include <iostream>
#include <cpr/cpr.h>

using namespace std;

int main()
{
    string txt;
    while (txt != "exit")
    {
        cin >> txt;
        if (txt == "get")
            cout << cpr::Get(cpr::Url("http://httpbin.org/get")).text;
        else if (txt == "post")
            cout << cpr::Post(cpr::Url("http://httpbin.org/post")).text;
        else if (txt == "put")
            cout << cpr::Put(cpr::Url("http://httpbin.org/put")).text;
        else if (txt == "delete")
            cout << cpr::Delete(cpr::Url("http://httpbin.org/delete")).text;
    }
}
