#include <iostream>
#include <fstream>
using namespace std;
// Function to display the array
void display(int **a, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}
// Function to write in file
void writeinFile(int **a, int r, int c)
{
    fstream writeFile("newMatrix.txt", ios::out | ios ::trunc);
    int write = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            writeFile << a[i][j] << ' ';
        }
        writeFile << endl;
    }
    writeFile.clear();
    writeFile.close();
}
// Function to search submatrix
void searchFunction(int **array, int **array1, int inputCol, int inpurRow, int row, int col, int counter1, int &checkFound, int arr1[], int arr2[], int &tt)
{
    // array represenet large matrix
    // array1 represents submatrix
    int i = 0, j = 0, k = 0, l = 0, x = 0, z = 0;
    int counter = 0;
    for (i = 0; i <= row - inpurRow; i++)
    {
        for (j = 0; j <= col - inputCol; j++)
        {
            // if first element of small matrix will match with large matrix then comditio will true and next loop will start
            if (array[i][j] == array1[0][0])
            {
                for (k = 0; k < inpurRow; k++)
                {
                    for (l = 0; l < inputCol; l++)
                    {
                        if (array[i + k][j + l] == array1[k][l])
                        {
                            // if all the element of submatrix is present then this counter will work
                            counter++;
                            if (counter == counter1)
                            {
                                checkFound = 1;
                                for (x = 0; x < inpurRow; x++)
                                {
                                    for (z = 0; z < inputCol; z++)
                                    {
                                        arr1[tt] = i + x;
                                        arr2[tt] = j + z;
                                        tt++;
                                    }
                                }
                            }
                        }
                    }
                }
                counter = 0;
            }
        }
    }
}
int main()
{
    int arr1[50];
    int arr2[50];
    int tt = 0;
    cout << "                        Welcome to                      \n";
    cout << "                      the Mars Camera                   " << endl;
    cout << "     In this camera you will give the submatrix and programm" << endl;
    cout << "      will check whether that submatrix exist in the file " << endl;
    cout << "         or not if it exist it will change the sign it" << endl;
    cout << "           will alse check with 90, 180, and 270" << endl;
    cout << "                     degree rotation                  " << endl;
    cout << endl;
    ifstream readFile("matrix.txt");
    // making 2d dynamic array to read file
    int **array = nullptr;
    int row, col;
    // counting number of rows and column
    int temp;
    int c = 0;
    int r = 0;
    if (readFile)
    {
        while (!readFile.eof())
        {
            // c will give us the total number of element present in file
            readFile >> temp;
            c++;
        }
    }
    else
    {
        cout << "Sorry File is not Present<<endl";
        system("pause");
    }

    // these function will bring the index to zero in file and file will read from starat now
    readFile.clear();
    readFile.seekg(0);
    // counting number of column using r
    char countArr[200];
    while (!readFile.eof())
    {
        readFile.getline(countArr, 200);
        r++;
    }
    c = c / r;
    row = r;
    col = c;
    readFile.clear();
    readFile.seekg(0);
    // Dynamically allocating row space in heap
    array = new int *[row];
    // Dynamically allocating column space in heap
    for (int i = 0; i < row; i++)
    {
        array[i] = new int[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            // from readFile we will read the characters from file
            readFile >> array[i][j];
        }
    }
    int found = 0;
    // Displaying array
    cout << "Matrix stored in the array is this" << endl
         << endl;
    display(array, row, col);
    // adding condition of less then 0 and greater than 255
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (array[i][j] < 0 || array[i][j] > 255)
            {
                found = -1;
                break;
            }
        }
        cout << endl;
    }
    if (found == -1)
    {
        cout << "The element in the file is less then 0 or greater then 255";
        cout << endl;
    }
    else
    {
        // taking submatrix from user
        int subMatrices = 0;
        cout << "How many submatrices you want to find :";
        cin >> subMatrices;
        int inpurRow = 0, inputCol = 0;
        // now this loop will run until submatics
        for (int g = 0; g < subMatrices; g++)
        {
            // counter1 is to count total number of element in submatix
            int checkFound = 0;
            int counter1 = 0;
            int **array1;
            cout << "Enter the number of rows" << endl;
            cin >> inpurRow;
            cout << "Enter the number of columns" << endl;
            cin >> inputCol;
            int **storingIndexArray = new int *[inpurRow];
            for (int i = 0; i < inpurRow; i++)
            {
                storingIndexArray[i] = new int[inputCol];
            }

            // Dynamically allocating row space in heap
            array1 = new int *[inpurRow];
            // Dynamically allocating column space in heap
            for (int i = 0; i < inpurRow; i++)
            {
                array1[i] = new int[inputCol];
            }
            // Taking input in the array
            cout << "Enter " << (inpurRow * inputCol) << " numbers \n";
            for (int i = 0; i < inpurRow; i++)
            {
                for (int j = 0; j < inputCol; j++)
                {
                    counter1++;
                    cout << "A[" << i << "][" << j << "] : ";
                    cin >> array1[i][j];
                }
            }
            // calling searchFunction
            searchFunction(array, array1, inputCol, inpurRow, row, col, counter1, checkFound, arr1, arr2, tt);
            // Rotataing submatrix to 90 degree
            int **tempArray1 = nullptr;
            // Dynamically allocating row space in heap
            tempArray1 = new int *[inpurRow];
            // Dynamically allocating column space in heap
            for (int i = 0; i < inpurRow; i++)
            {
                tempArray1[i] = new int[inputCol];
            }
            int a = 0;
            int b = 0;
            for (int i = 0; i < inpurRow; i++)
            {
                for (int j = inputCol - 1; j >= 0; j--)
                {
                    tempArray1[a][b] = array1[j][i];
                    b++;
                }
                a++;
                b = 0;
                cout << endl;
            }
            // now tempArray1 have submatrix with 90 degree rotaotion
            // Search function for 90 degree
            if (counter1 > 1)
            {
                searchFunction(array, tempArray1, inputCol, inpurRow, row, col, counter1, checkFound, arr1, arr2, tt);
            }

            // Rotataing submatrix to 180 degree
            // Dynamically allocating row space in heap
            int **tempArray2 = nullptr;
            tempArray2 = new int *[inpurRow];
            // Dynamically allocating column space in heap
            for (int i = 0; i < inpurRow; i++)
            {
                tempArray2[i] = new int[inputCol];
            }
            a = 0;
            b = 0;
            for (int i = inpurRow - 1; i >= 0; i--)
            {
                for (int j = inputCol - 1; j >= 0; j--)
                {
                    tempArray2[a][b] = array1[i][j];
                    b++;
                }
                a++;
                b = 0;
            }
            // now tempArray2 have submatrix with 180 degree rotaotion
            // Search function for 180 degree
            if (counter1 > 1)
            {
                searchFunction(array, tempArray2, inputCol, inpurRow, row, col, counter1, checkFound, arr1, arr2, tt);
            }
            // Rotataing submatrix to 270 degree
            // Dynamically allocating row space in heap
            int **tempArray3 = nullptr;
            tempArray3 = new int *[inpurRow];
            // Dynamically allocating column space in heap
            for (int i = 0; i < inpurRow; i++)
            {
                tempArray3[i] = new int[inputCol];
            }
            a = 0;
            b = 0;
            for (int i = inpurRow - 1; i >= 0; i--)
            {
                for (int j = 0; j < inputCol; j++)
                {
                    tempArray3[a][b] = array1[j][i];
                    b++;
                }
                a++;
                b = 0;
            }
            // now tempArray2 have submatrix with 270 degree rotaotion
            // Search function for 270 degree
            if (counter1 > 1)
            {
                searchFunction(array, tempArray3, inputCol, inpurRow, row, col, counter1, checkFound, arr1, arr2, tt);
            }
            counter1 = 0;
            if (checkFound == 1)
            {
                cout << "Your " << g + 1 << " submatrix have been found" << endl
                     << endl;
            }
            else
                cout << "Sorry the matrix is not present " << endl
                     << endl;
        }
    }
    // Finding OverLapping
    int a = 0;
    int b = 0;
    for (int i = 0; i < tt; i++)
    {
        a = arr1[i];
        b = arr2[i];
        // it will change the sign
        array[a][b] = array[a][b] * -1;
    }
    for (int i = 0; i < tt - 1; i++)
    {
        for (int j = i + 1; j < tt; j++)
        {
            if (arr1[i] == arr1[j] && arr2[i] == arr2[j])
            {
                cout << " Overlapping found in row index :";
                cout << arr1[i] << " and column index ";
                cout << arr2[i] << endl;
                a = arr1[i];
                b = arr2[i];
                // it will change the sign
                array[a][b] = array[a][b] * -1;
            }
        }
    }

    // calling function
    writeinFile(array, row, col);
    readFile.close();
    system("pause");
    return 0;
}
