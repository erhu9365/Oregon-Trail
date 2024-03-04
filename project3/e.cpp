#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class PhoneBook
{
    public:
        PhoneBook()
        {
            int codes[400] = {0};
            string regions[400] = "";
        }
        int LoadAreaCodes(string filename)
        {
            int i = 0;
            ifstream areacodes;
            areacodes.open(filename);
            string line;
            if(areacodes.is_open())
            {
                while(getline(areacodes, line))
                {
                    string words[2];
                    int split(string s, char sep, string words[], int max_words);
                    codes[i]= stoi(words[0]);
                    regions[i] = words[1];
                    i++;
                }
            }
            else
            {
                return -1;
            }
            areacodes.close();
        }
        string GetRegion(int areaCode)
        {
            for(int j = 0; j < 400; j++)
            {
                if(codes[j] == areaCode)
                {
                    return regions[j];
                }
                else
                {
                    return "Not Found";
                }
            }
        }
        int CountAreaCodesInRegion(string region)
        {
            int count = 0;
            for(int j = 0; j < 400; j++)
            {
                if(regions[j] == region)
                {
                    count++;
                }
                else
                {
                    return 0;
                }
            }
            return count;
        }
    private:
        int codes[400];
        string regions[400];
};

int main()
{
    PhoneBook e;
    e = LoadAreaCodes("Payroll.txt");
}