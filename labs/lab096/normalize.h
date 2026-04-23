#ifndef NORMALIZE_H
#define NORMALIZE_H

#include <string>

// 입력 문자열에 대해:
//   1) 앞뒤 공백 제거
//   2) 구두점 모두 제거
//   3) 영문자는 모두 소문자로 변환
// 위 세 단계를 거친 결과를 반환
std::string normalize(const std::string& input);

#endif // NORMALIZE_H
