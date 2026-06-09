#pragma once
#include "Skill.hpp"
#include <iostream>

// TODO: GangplankSkill 클래스를 구현하세요 (Skill을 public 상속).
// q(): "TRIAL BY FIRE" 출력
// w(): "PARRRLEY" 출력
// e(): "REMOVE SCURVY" 출력
// r(): "POWDER KEG" 출력
class GangplankSkill : public Skill {
public:
    void q() override { std::cout << "TRIAL BY FIRE\n"; }
    void w() override { std::cout << "PARRRLEY\n"; }
    void e() override { std::cout << "REMOVE SCURVY\n"; }
    void r() override { std::cout << "POWDER KEG\n"; }
};