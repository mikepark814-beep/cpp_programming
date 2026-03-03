# C/C++ 실습 환경 (VS Code + MSYS2 UCRT64 + CMake)

## 프로젝트 구조

```
C:\hello
├─ .vscode/                 ← VS Code 설정 (수정하지 마세요)
│  ├─ settings.json
│  ├─ tasks.json
│  ├─ launch.json
│  └─ c_cpp_properties.json
├─ CMakeLists.txt           ← 루트 CMake 설정
├─ hello.cpp                ← Hello World 예제
└─ labs/                    ← 실습 과제 폴더
   ├─ CMakeLists.txt        ← q* 폴더 자동 탐색
   ├─ q01/
   │  ├─ CMakeLists.txt
   │  └─ main.cpp
   └─ q02/
      ├─ CMakeLists.txt
      └─ main.cpp
```

## 1. 사전 준비

### 1-1. MSYS2 설치
- 설치 경로: **반드시 `C:\msys64`** (기본값 유지)
- 다운로드: https://www.msys2.org

### 1-2. UCRT64 도구 설치
MSYS2 터미널(UCRT64)을 열고 아래 명령 실행:

```bash
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-cmake
```

설치 확인:

```bash
g++ --version       # GCC 확인
gdb --version       # 디버거 확인
cmake --version     # CMake 확인
```

### 1-3. VS Code 확장 설치
- **C/C++** (Microsoft)
- **CMake Tools** (Microsoft)

## 2. 빌드 & 실행

### Ctrl+Shift+B (기본 빌드)
전체 프로젝트(hello + 모든 lab)를 한번에 빌드합니다.

### F5 (디버그 실행)
1. VS Code 하단 상태 표시줄에서 **CMake 빌드 타깃**을 선택 (예: `lab_q01`)
2. `F5`를 누르면 해당 타깃만 빌드 후 디버거가 실행됩니다.
3. 브레이크포인트를 설정하고 단계별 실행이 가능합니다.

### 터미널에서 직접 빌드 (참고)

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

특정 타깃만 빌드:

```bash
cmake --build build --target lab_q01
```

## 3. 과제 추가 방법

새 과제 `q03`을 추가하려면:

**1단계.** `labs/q03/` 폴더를 만들고 `main.cpp`를 작성합니다.

**2단계.** `labs/q01/CMakeLists.txt`를 `labs/q03/`에 복사합니다.

```
labs/q03/
├─ CMakeLists.txt    ← q01에서 복사 (수정 불필요)
└─ main.cpp          ← 과제 코드 작성
```

끝입니다. `labs/CMakeLists.txt`가 `q*` 폴더를 자동 탐색하므로 다른 파일은 수정할 필요가 없습니다.

빌드 타깃 이름은 자동으로 `lab_q03`이 됩니다.

## 4. 제출 전 체크리스트

1. VS Code 기본 터미널이 **MSYS2 UCRT64**인지 확인
2. `Ctrl+Shift+B` → 빌드 성공
3. `F5` → 디버그 시작 성공
4. `build/compile_commands.json` 파일 생성 확인

## 5. 문제 해결

| 증상 | 해결 |
|------|------|
| `g++`/`cmake` 명령을 못 찾음 | MSYS2 UCRT64 터미널에서 1-2 설치 명령 재실행 |
| VS Code에서 빌드 실패 | VS Code를 완전히 종료 후 재실행 |
| IntelliSense 헤더 오류 (빨간 밑줄) | `Ctrl+Shift+P` → "C/C++: Edit Configurations" → compilerPath가 `C:\msys64\ucrt64\bin\g++.exe`인지 확인 |
| 디버그 시 프로그램 못 찾음 | 하단 상태 표시줄에서 올바른 CMake 타깃을 선택했는지 확인 |
| `where g++` 결과가 여러 개 | `mingw64`와 `ucrt64` 혼용 금지 — `ucrt64\bin` 하나만 PATH에 유지 |

## 6. 환경 설정 요약 (`.vscode/` 내용 설명)

이 프로젝트의 `.vscode/` 설정은 **시스템 PATH에 의존하지 않고** 도구 경로를 직접 지정합니다. 따라서 학생 PC마다 PATH가 달라도 동일하게 동작합니다.

- **settings.json**: 기본 터미널을 MSYS2 UCRT64로 고정, CMake 경로/Generator 명시
- **tasks.json**: CMake configure + build Task 정의 (`Ctrl+Shift+B` 연결)
- **launch.json**: GDB 디버거 경로 고정, CMake 타깃 자동 연결 (`F5` 연결)
- **c_cpp_properties.json**: IntelliSense가 UCRT64 컴파일러와 `compile_commands.json`을 사용하도록 지정
