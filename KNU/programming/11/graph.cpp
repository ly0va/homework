#include <iostream>
#include <algorithm>

using namespace std;

void graph(int *array, int len, int maxY=0, int scl=1) {
    if (maxY == 0) 
        maxY = *max_element(array, array+len);
    cout << "<link href=style.css rel=stylesheet><pre><table border=0>";
    for (int y = maxY; y >= 0; y--) {
        /* cout << "<tr><th>" << (y < 10 ? '0' : ' ') << y << "</th>"; */
        for (int x = 0; x < len; x++) {
            cout << "<td height=2 title='" << x << ' ' << y << "' " << (array[x] == y ? "bgcolor=black>" : ">") << "</td>";
        }
        cout << "</tr>";
    }
    cout << "<tr>";
    for (int x = 0; x < len; x++) {
        cout << "<th>" << (x < 10 && x >= 0 ? '0' : ' ') << x << "</th>";
    }
    cout << "</tr></table></pre>";

}

int main(int argc, char **argv) {

    int array[100];
    int i = 0;
    while (cin >> array[i]) {
        array[i] /= 10;
        i++;
    }
    
    graph(array, i);
    
    return 0;
}

