```markdown
# [Tetris Project] Day 2 학습 보고서

| 학번 | 이름 | 제출일 |
|------|------|--------|
|202255548|박세준|2026-05-04|

---

## Q1. `Board::setCell`에 경계 검사가 없으면 어떤 문제가 생기는가?
`private` 멤버와 `inBounds` 검사가 *함께* 있어야 캡슐화가 완성되는 이유를 설명하시오.

> `setCell`에 경계 검사가 없으면 `setCell(-1, 0, 'X')` 같은 OOB 좌표가 그대로 `cells_[y][x]`에 전달되어 배열 밖 메모리를 건드리게 되고, 결국 segfault나 UB가 발생한다. `cells_`를 `private`으로 숨기는 것만으로는 부족한데, 외부에서 직접 접근은 막혀 있어도 유일한 진입로인 `setCell`이 경계를 확인하지 않으면 OOB 쓰기는 여전히 가능하기 때문이다. `private`이 "외부에서 직접 손대지 못하게" 막아주고, `inBounds` 검사가 "진입로에서 잘못된 좌표를 걸러준다". 두 가지가 함께 있어야 잘못된 접근이 클래스 안에 완전히 봉인된다.

## Q2. `const GameState& state`를 받는 함수에서 `state.board.setCell(...)`을 호출하면 컴파일 에러가 나는 이유는?
Day 1에서는 같은 실수가 왜 에러 없이 통과됐는가?

> `board_to_string`은 `const GameState& state`를 받으므로 `state.board`는 `const Board`가 된다. `setCell`은 `const` 멤버 함수가 아니기 때문에 `const Board`에서는 호출 자체가 컴파일 단계에서 막힌다. Day 1에서는 `board`가 `std::vector<std::vector<char>>`로 `GameState`에 직접 노출되어 있었고, `state.board[y][x] = '#'`처럼 내부 원소를 바꾸는 것은 `board` 포인터 자체를 바꾸는 게 아니라 컴파일러가 허용했다. Day 2에서는 수정 경로가 `setCell`로만 좁혀졌고 `setCell`이 `const`가 아니어서, 실수로 원본을 건드리려 하면 빌드 자체가 안 된다.

---

## 구현 중 막혔던 부분

| 증상 | 원인 | 해결 |
|------|------|------|
| `board` 명령 출력에 깨진 문자(널 문자)가 섞여 나옴 | `Board::Board() = default`로 두면 `std::array`가 `'\0'`으로 zero-init 되어 `'.'`이 아님 | 생성자 본문에 `for (auto& row : cells_) row.fill('.');` 추가 |
| `board_to_string`에서 `rendered[board_y][board_x] = '#'` 작성 시 컴파일 에러 | `cells_`가 `private`이라 클래스 밖에서 직접 접근 불가 | `rendered.setCell({px + x, py + y}, '#')`으로 변경 |
| `Piece::Piece() = default`로 두었더니 `state` 케이스에서 `shape=0x0`으로 실패 | `default` 생성자는 `shape_`를 빈 벡터로 두기 때문 | 멤버 초기화 리스트로 `Piece::Piece() : shape_{{1, 1, 1, 1}} {}`로 수정 |
