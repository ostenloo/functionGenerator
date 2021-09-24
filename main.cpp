#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

void findLinear(vector<double> domain, vector<double> codomain, int size);
void findPolynomial(vector<double> domain, vector<double> codomain, int size);
vector<vector<int>> binary(int size);
vector<int> zeros(vector<vector<int>> binary);

int main() {

    char terminate;

    do
    {
        cout << "Enter the numbers for the domain on the first line, \n" <<
             "then the numbers for the codomain on the second line \n";
        int x;
        string temp;
        vector<double> domain;
        vector<double> codomain;
        istringstream is1 , is2;
        getline(cin, temp);
        is1.str(temp);
        while(is1 >> x)
        {
            domain.push_back(x);
        }
        getline(cin, temp);
        is2.str(temp);

        while(is2 >> x)
        {
            codomain.push_back(x);
        }
        cout << "Domain: ";
        for(auto a : domain)
        {
            cout << a << " ";
        }
        cout << endl;
        cout << "Codomain: ";
        for(auto a : codomain)
        {
            cout << a << " ";
        }
        cout << endl;
        findLinear(domain, codomain, min(domain.size(), codomain.size()));
        findPolynomial(domain, codomain, min(domain.size(), codomain.size()));
        cout << "Press q to quit. Otherwise, press any other key to continue. " << endl;
        cin >> terminate;
        cin.ignore();
    } while(terminate != 'q');
    return 0;
}

void findLinear(vector<double> domain, vector<double> codomain, int size)
{
    double m, b;
    m = (codomain[1] - codomain[0]) / (domain[1] - domain[0]);
    for(int i = 1; i < size - 1; i++)
    {
        if(m != (codomain[i+1] - codomain[i]) / (domain[i+1] - domain[i]))
        {
            cout << "No linear relationship" << endl;
            return;
        }
    }
    b = codomain[0] - domain[0] * m;
    cout << "Linear Function that fits the dataset: f(x) = " << m << "x + " << b << endl;

}

void findPolynomial(vector<double> domain, vector<double> codomain, int size)
{
    vector<vector<int>> bin = binary(size - 1);
    vector<int> zer = zeros (bin);
    double temp, tempv, sum;
    vector<double> coefficients(size, 0);
    for(int i = 0; i < size; i++)
    {
        //this loop traverses each number in the codomain
        temp = codomain[i]; //4
        for(int j = 0; j < size; j++)
        {
            if(i == j)
                continue;
            temp /= (domain[i] - domain[j]); //4 / (1-2)(1-3)
        }
        coefficients[0] += temp;
        for(int j = 1; j < size; j++)
        {
            //transverse the binary vector to get the vieta formulas for each power of x
            sum = 0;
            //cout << "j " << j << endl;
            for (int k = 1; k < zer.size(); k++) {
                if(zer[k] == size - j - 1) //zer[k] == 3 - 1 = 2
                {
                    tempv = 1;
                    vector<double> copy = domain; //skips the root at the current i
                    copy.erase(copy.begin() + i);
                    //copy is correct
                    for(int l = 0; l < bin[k].size(); l++)
                    {
                        if(bin[k][l] == 1)
                        tempv *= copy[l];
                    }
                    sum += tempv;
                }
            }
            if(j % 2 == 0)
            coefficients[j] += temp*sum;
            if(j % 2 == 1)
                coefficients[j] -= temp*sum;
        }
    }
    cout << "Polynomial Function that fits the dataset: f(x) = " << coefficients[0] << "x^" << size - 1 << " + ";
    for(int i = 1; i < size; i++)
    {
        if(i == size - 1)
            cout << coefficients[i] << endl;
        else
            cout << coefficients[i] << "x^" << size - i - 1 << " + ";
    }
}

//bitmasking 
vector<vector<int>> binary(int size)
{
    vector<vector<int>> ans;
    vector<int> temp (size, 0);
    ans.push_back(temp);
    for(int i = 0; i < pow(2,size) - 1; i++)
    {
        temp[size - 1]++;
        for(int j = size - 1; j > 0; j--)
        {
            if(temp[j] == 2)
            {
                temp[j] = 0;
                temp[j - 1]++;
            }
        }
        ans.push_back(temp);
    }
    return ans;
}

vector<int> zeros(vector<vector<int>> binary)
{
    vector<int> zeros;
    int temp = 0;
    for(int i = 0; i < binary.size(); i++)
    {
        for(int j = 0; j < binary[i].size(); j++)
        {
            if(binary[i][j] == 0)
                temp++;
        }
        zeros.push_back(temp);
        temp = 0;
    }
    return zeros;
}
