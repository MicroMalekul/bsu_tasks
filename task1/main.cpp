/*    
12. Задана строка, в которой встречаются подстроки вида <лпс>, где лпс – любая последовательность символов, отличных от < и >. Например,
               <abc> xxx <defg> eee <ik> jsak
Найти все эти подстроки и вычислить конкатенацию (т.е. сцепление) лпс. Для указанной выше строки это будет 
               abcdefgik
*/


#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>

using namespace std;

int main() {
    ifstream file("task1/input.txt");

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    cout << "text = " << text << "\n";
 
    // Регулярное выражение для поиска подстрок вида <лпс>, где лпс — это любая последовательность символов,
    // не содержащая угловых скобок. (.*?) — "ленивое" выражение, соответствующее минимальной подходящей подстроке.  
     regex pattern(R"(<(.*?)>)"); 



    string result;
    auto begin = sregex_iterator(text.begin(), text.end(), pattern);
    auto end = sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        result += (*it)[1].str(); // (*it)[1] — это первая захваченная группа, т.е. содержимое между < и >
    }

    cout << "res: " << result << '\n';
    
    return 0;
}
