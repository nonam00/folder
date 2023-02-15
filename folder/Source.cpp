//работает только на версии языка 2017 года
//делал по найденной документации к библиотеке filesystem, а также на основе
//возможных решений из интернета, ибо не знаю, как на основе только пройденного материала выполнить задание

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

int searchAndReplace(const fs::path& path, const string& searchWord, const string& replaceWord, bool replace)
{
    int count = 0;
    if (fs::is_directory(path))
    {
        for (const auto& entry : fs::recursive_directory_iterator(path))
        {
            if (fs::is_regular_file(entry))
            {
                string filename = entry.path().filename().string();
                string extension = entry.path().extension().string();
                if (extension == ".txt")
                {
                    ifstream inputFile(entry.path());
                    string fileContent((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());
                    size_t pos = 0;count++;
                        if (replace)
                            fileContent.replace(pos, searchWord.length(), replaceWord);
                        else
                            cout << "Found " << searchWord << " in file: " << entry.path() << " at position: " << pos << endl;
                        pos += replaceWord.length();
                    if (replace)
                    {
                        ofstream outputFile(entry.path());
                        outputFile << fileContent;
                    }
                }
            }
        }
    }
    return count;
}

int main()
{
    string folderPath, searchWord, replaceWord;
    cout << "Enter the path to the folder: ";
    getline(cin, folderPath);

    cout << "Enter the search word: ";
    getline(cin, searchWord);
    int count = searchAndReplace(folderPath, searchWord, "", false);

    cout << "Found " << count << " occurrences of " << searchWord << " in the folder " << folderPath << " and its subfolders." << endl;

    cout << "Do you want to replace the search word with another word? (y/n): ";
    string response;
    getline(cin, response);

    if (response == "y")
    {
        cout << "Enter the word to replace the search word: ";
        getline(cin, replaceWord);
        int replaceCount = searchAndReplace(folderPath, searchWord, replaceWord, true);
        cout << "Replaced " << replaceCount << " occurrences of " << searchWord << " with " << replaceWord << " in the folder " << folderPath << " and its subfolders." << endl;
    }

    return 0;
}