#include <iostream>
#include <cpr/cpr.h>

using namespace std;

int main()
{
    cpr::Response r = cpr::Get(cpr::Url( "http://httpbin.org/put"), cpr::Header({{"accept", "text/html"}}));

    for (int i = 4; i < r.text.length(); i++)
    {
        if (r.text[i-1] == '>' &&
            r.text[i-2] == '1' &&
            r.text[i-3] == 'h' &&
            r.text[i-4] == '<')
        {
            while (r.text[i] != '<')
            {
                cout << r.text[i];
                i++;
            }
        }
    }
}
