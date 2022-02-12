#include <iostream>
#include <vector>

using namespace std;

int calculate_for_optimal(int page[], vector<int> &pageframe, int pagenumber, int index)
{

    int pos_onpageframe;
    int farpos = index;
    for (int i = 0; i < pageframe.size(); i++)
    {
        int j;
        for (j = index; j < pagenumber; j++)
        {
            if (pageframe[i] == page[j])
            {
                if (j > farpos)
                {
                    farpos = j;
                    pos_onpageframe = i;
                }
                break;
            }
        }

        if (j == pagenumber)
            return i;
    }

    return pos_onpageframe;
}

int calculate_for_LRU(int page[], vector<int> &pageframe, int pagenumber, int index)
{

    int pos_onpageframe;
    int farpos = index;
    for (int i = 0; i < pageframe.size(); i++)
    {
        int j;
        for (j = index; j >= 0; j--)
        {
            if (pageframe[i] == page[j])
            {
                if (j < farpos)
                {
                    farpos = j;
                    pos_onpageframe = i;
                }
                break;
            }
        }

        if (j == index)
            return i;
    }

    return pos_onpageframe;
}

bool have_pagefault_fi(int key, vector<int> &pageframe, int cap)
{
    if (pageframe.size() < cap)
    {  
        
        pageframe.insert(pageframe.end(), key);
        return true;
    }
    else
    {
        for (int i = 0; i < pageframe.size(); i++)
        {
            if (pageframe[i] == key)
                return false;
        }
        return true;
    }
}

bool have_pagefault(int key, vector<int> &pageframe, int cap)
{
    if (pageframe.size() < cap)
    {
        pageframe.push_back(key);
        return true;
    }
    else
    {
        for (int i = 0; i < pageframe.size(); i++)
        {
            if (pageframe[i] == key)
                return false;
        }
        return true;
    }
}

void optimalAlgo(int page[], int pagenumber, int capacity)
{
    vector<int> pageframe;
    int pagefault = 0;
    for (int i = 0; i < pagenumber; i++)
    {

        if (have_pagefault(page[i], pageframe, capacity))
        {
            pagefault++;

            int j = calculate_for_optimal(page, pageframe, pagenumber, i + 1);
            pageframe[j] = page[i];
        }
    }
    cout << "PageFaults = " << pagefault << endl;
}

void fifoAlgo(int page[], int pagenumber, int capacity)
{
    vector<int> pageframe;
    int pagefault = 0;

    for (int i = 0; i < pagenumber; i++)
    {
        if (have_pagefault_fi(page[i], pageframe, capacity))
        {
            pagefault++;
            pageframe.erase(pageframe.begin());
            pageframe.insert(pageframe.end(), page[i]);
        }
    }

    cout << "PageFaults = " << pagefault << endl;
}

void LRUAlgo(int page[], int pagenumber, int capacity)
{
    vector<int> pageframe;
    int pagefault = 0;
    for (int i = 0; i < pagenumber; i++)
    {

        if (have_pagefault(page[i], pageframe, capacity))
        {
            pagefault++;

            int j = calculate_for_LRU(page, pageframe, pagenumber, i);
            pageframe[j] = page[i];
        }
    }
    cout << "PageFaults = " << pagefault << endl;
}

int main()
{
    int reference_string_1 [] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 0
                                 };
    
    int reference_string_2 [] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 1,
                                 4, 4, 4, 5, 5, 5, 2, 2, 2, 3,
                                 1, 1, 1, 2, 2, 2, 3, 3, 3, 1,
                                 4, 4, 4, 5, 5, 5, 2, 2, 2, 3,
                                 1, 2, 3, 4, 5, 5, 4, 3, 2, 1
                                 };

    int reference_string_3 [] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1,
                                 5, 4, 3, 2, 1, 1, 2, 3, 4, 5,
                                 0, 9, 8, 7, 6, 6, 7, 8, 9, 0,
                                 6, 7, 8, 9, 0, 0, 9, 8, 7, 6,
                                 1, 2, 3, 4, 5, 5, 4, 3, 2, 1,
                                 4, 4, 4, 5, 5, 5, 2, 2, 2, 3,
                                 1, 2, 3, 4, 5, 5, 4, 3, 2, 1,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 9, 1, 8, 2, 7, 3, 6, 4, 5, 5,
                                 1, 2, 1, 2, 3, 1, 2, 1, 2, 1,
                                 
                                 };

    
    int pagenumber1 = sizeof(reference_string_1)/sizeof(reference_string_1[0]) ;
    int pagenumber2 = sizeof(reference_string_2)/sizeof(reference_string_2[0]) ;
    int pagenumber3 = sizeof(reference_string_3)/sizeof(reference_string_3[0]) ;
    int capacity = 3;

    cout << "Test reference_string_1"  << endl;

    fifoAlgo(reference_string_1, pagenumber1, capacity);
    LRUAlgo(reference_string_1, pagenumber1, capacity);
    optimalAlgo(reference_string_1, pagenumber1, capacity);

    // cout << endl<<"Test reference_string_2"  << endl;

    // fifoAlgo(reference_string_2, pagenumber2, capacity);
    // LRUAlgo(reference_string_2, pagenumber2, capacity);
    // optimalAlgo(reference_string_2, pagenumber2, capacity);
    
    // cout << endl<<"Test reference_string_3"  << endl;

    // fifoAlgo(reference_string_3, pagenumber3, capacity);
    // LRUAlgo(reference_string_3, pagenumber3, capacity);
    // optimalAlgo(reference_string_3, pagenumber3, capacity);

    return 0;
}
