#include "StringSplitter.h"
#include <cctype>
#include <sstream>

// TODO: 아래 함수들을 구현하세요.
// trim(), replaceSubstring(), removePunctuation() 은 *this 를 반환하여
// 메서드 체이닝을 가능하게 합니다.

StringSplitter::StringSplitter(const std::string& str) {
    // data_ 에 입력 문자열을 저장합니다.
    // 앞에 this -> 는 있어도 되는데 이름이 겹치지 않아서 괜찮다.
    data_ = str;
}

StringSplitter& StringSplitter::trim() {
    // data_ 의 앞뒤 공백을 제거합니다.
    // 힌트: find_first_not_of(' ') 와 find_last_not_of(' ') 사용
    // 반드시 return *this; 로 끝내세요.
    auto start = data_.find_first_not_of(' ');
    auto end = data_.find_last_not_of(' ');
    auto length = end - start + 1;

    data_ = data_.substr(start , length);
    return *this;
}

StringSplitter& StringSplitter::replaceSubstring(const std::string& from,
                                                   const std::string& to) {
    // data_ 에서 from 을 찾아 to 로 교체합니다 (첫 번째 등장만).
    // 힌트: data_.find(from) 으로 위치를 찾고
    //       data_.replace(pos, from.length(), to) 로 교체
    // from 이 없으면 아무 것도 하지 않습니다.
    auto start = data_.find(from);

    data_.replace(start , from.length() , to);
    if (start != std::string::npos) {
        data_.replace(start , from.length() , to);
    }
    return *this;
}

StringSplitter& StringSplitter::removePunctuation() {
    // data_ 에서 구두점 문자를 모두 제거합니다.
    // 힌트: std::ispunct(c) 가 true 인 문자를 제거
    //       erase-remove 관용구 또는 std::erase_if(data_, ::ispunct) 사용
    std::erase_if(data_ , ::ispunct);
    return *this;
}

std::vector<std::string> StringSplitter::split(char delimiter) const {
    // data_ 를 delimiter 기준으로 나눠 벡터로 반환합니다.
    // 빈 토큰은 포함하지 않습니다.
    // 힌트: std::istringstream 으로 getline(iss, token, delimiter) 반복
    std::vector<std::string> ret;

    auto iss = std::istringstream(data_);

    std::string str;
    while(std::getline(iss , str , delimiter)) {
        if (str.empty()) continue;
        ret.push_back(str);
    }
    
    return ret;
}
