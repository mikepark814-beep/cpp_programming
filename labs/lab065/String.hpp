#ifndef STRING_HPP
#define STRING_HPP

#include <cstddef>

// Rule of Three: 소멸자를 직접 작성하면 복사 생성자·복사 대입 연산자도 정의해야 합니다.
// 이 실습에서는 복사 대입 연산자를 = delete로 명시적으로 제거합니다.
class String {
public:
    String();                          // 기본 생성자: 빈 문자열("") 할당
    explicit String(const char* s);    // C-문자열 생성자
    String(const String& s);          // 복사 생성자: 깊은 복사 (new → noexcept 아님)
    ~String() noexcept;               // 소멸자: delete[]는 예외를 던지지 않음

    // 복사 대입 연산자는 이 실습 범위 외 — 명시적으로 삭제
    String& operator=(const String&) = delete;

    const char* data()  const noexcept;  // 내부 C-문자열 포인터 반환
    bool        empty() const noexcept;  // 빈 문자열이면 true
    std::size_t size()  const noexcept;  // 길이 반환 ('\0' 미포함)

    String& append(const String& str);   // str을 뒤에 이어 붙임 (재할당)
    String& append(const char* str);     // C-문자열을 뒤에 이어 붙임 (재할당)

private:
    static int  count_;  // 현재 살아 있는 String 객체 수 (클래스 전체 공유)
    char*       data_;   // 힙에 할당된 문자 배열 ('\0' 포함)
    std::size_t len_;    // 문자열 길이 ('\0' 미포함)
};

#endif // STRING_HPP
