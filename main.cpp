#include <iostream>
#include <vector>
#include <initializer_list>
#include <cpr/cpr.h>

using namespace std;

string get(const vector<cpr::Pair>& vec)
{
    string txt = "?";
    txt += vec[0].key + "=" + vec[0].value;
    for (int i = 1; i < vec.size(); i++)
    {
        txt += "&" + vec[i].key + "=" + vec[i].value;
    }
    return txt;
}

int main()
{
    vector<cpr::Pair> var;
    string text_1;

    do {
        cin >> text_1;
        if (text_1 != "get" && text_1 != "post")
        {
            string text_2;

            cin >> text_2;

            cpr::Pair s{"", ""};
            s.key = text_1;
            s.value = text_2;
            var.push_back(s);
        }
    } while (text_1 != "get" && text_1 != "post");



    if (text_1 == "get")
    {
        cout << cpr::Get(cpr::Url( "http://httpbin.org/get" + get(var) )).text;
    }
    else
    {
        cout << cpr::Post(cpr::Url( "http://httpbin.org/post" ), cpr::Payload(var.begin(), var.end())).text;
    }
}
