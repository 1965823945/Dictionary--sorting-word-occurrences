#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

// Функция, которая удаляет все знаки препинания из строки 删除字符串中所有标点符号的函数
void removePunctuations(string &str)
{
    string punctuations = ".,:;?!()-";
    for (char punctuation : punctuations)
    {
        str.erase(remove(str.begin(), str.end(), punctuation), str.end());
    }
}
bool cmp(pair<string, int> a, pair<string, int> b)
{
    return a.second < b.second;
}

// bool comparePairless(const pair<string, int>& pair1, const pair<string, int>& pair2) {
//     if (pair1.second != pair2.second) {
//         return pair1.second < pair2.second;  // 按照int值从大到小排序
//     } else {
//         return pair1.first < pair2.first;  // 对于相同的int值，按照string的正常排序
//     }
// }
// bool comparePairless(const pair<string, int>& pair1, const pair<string, int>& pair2) {
//     if (pair1.second != pair2.second) {
//         return pair1.second > pair2.second;  // 按照int值从大到小排序
//     } else {
//         return pair1.first < pair2.first;  // 对于相同的int值，按照string的正常排序
//     }
// }

int main()
{
    ifstream file("text.txt"); // Заменить "text.txt" на имя вашего файла с текстом 将 "text.txt "替换为文本文件的名称
    if (!file)
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string word;
    map<string, int> frequency;

    // Чтение текста из файла 从文件中读取文本
    string line;
    while (getline(file, line))
    {
        // Удаление знаков препинания и приведение к нижнему регистру 删除标点符号并转换为小写字母
        removePunctuations(line);
        transform(line.begin(), line.end(), line.begin(), ::tolower);

        // Разбиение строки на слова 将一行分割成单词
        size_t pos = 0;
        while ((pos = line.find(' ')) != string::npos)
        {
            word = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Игнорирование слов, состоящих из цифр 忽略由数字组成的词语
            if (word.find_first_not_of("0123456789") != string::npos)
            {
                // Увеличение частоты слова в словаре 增加词语在词典中的出现频率
                frequency[word]++;
            }
        }
        if (line.find_first_not_of(" \t\n\v\f\r") != string::npos)
        {
            // Игнорирование слов, состоящих из цифр 忽略由数字组成的词语
            if (line.find_first_not_of("0123456789") != string::npos)
            {
                // Увеличение частоты слова в словаре 增加词语在词典中的出现频率
                frequency[line]++;
            }
        }
    }

    file.close();

    ofstream output("output.txt"); // Заменить "frequency.txt" на имя файла, куда сохранить частотный словарь 将 "frequency.txt "替换为保存频率字典的文件名
    if (!output)
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<pair<string, int>> vec(frequency.begin(), frequency.end());
    sort(vec.begin(), vec.end(), cmp);
    string choice;
    bool flag = false;
    do
    {
        flag = false;
        cout << "Пожалуйста, введите способ просмотра" << endl;
        cout << "1.Перечислены в алфавитном порядке" << endl;
        cout << "2.Перечислены в обратном алфавитном порядке" << endl;
        cout << "3.Перечислены в порядке возникновения" << endl;
        cout << "4.Перечислены в обратном порядке возникновения" << endl;

        cin >> choice;
        cout << endl;
        switch (choice[0])
        {

        case '1':
            // Вывод частотного словаря 频率词典输出
            for (auto it = frequency.begin(); it != frequency.end(); ++it)
            {
                output << it->first << " " << it->second << endl;

                // Вывод частотного словаря на консоль 在控制台上显示频率字典
                cout << it->first << " " << it->second << endl;
            }
            output.close();
            return 0;
        case '2':
            for (auto it = frequency.rbegin(); it != frequency.rend(); ++it)
            {
                output << it->first << " " << it->second << endl;

                // Вывод частотного словаря на консоль 在控制台上显示频率字典
                cout << it->first << " " << it->second << endl;
            }
            output.close();
            return 0;
        case '3':
            for (auto it = vec.begin(); it != vec.end(); ++it)
            {
                output << it->first << " " << it->second << endl;
                // Вывод частотного словаря на консоль 在控制台上显示频率字典
                cout << it->first << " " << it->second << endl;
            }
            output.close();
            return 0;
        case '4':
            for (auto it = vec.rbegin(); it != vec.rend(); ++it)
            {
                output << it->first << " " << it->second << endl;
                // Вывод частотного словаря на консоль 在控制台上显示频率字典
                cout << it->first << " " << it->second << endl;
            }
            output.close();
            return 0;
        default:
            cout << "Пожалуйста, повторите ввод, если вы допустили ошибку" << endl;
            cout << endl;
            flag = true;
            break;
        }
    } while (flag);
}