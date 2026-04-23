#ifndef WORDFREQ_H
#define WORDFREQ_H

#include <string>
#include <vector>
#include <map>

// 각 단어의 등장 횟수를 map으로 반환
std::map<std::string, int> count_words(const std::vector<std::string>& words);

// 등장 횟수 내림차순, 동률 시 단어 알파벳 오름차순으로
// 상위 k개를 "단어 횟수\n" 형식으로 출력
void print_top(const std::map<std::string, int>& freq, int k);

#endif // WORDFREQ_H
