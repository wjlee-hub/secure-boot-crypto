# 학습 노트

시큐어 부트에 쓰이는 AES-128 / SHA-256 (그리고 HMAC, CMAC)을 C로 **직접** 구현하면서 공부하는 기록.
목표: 내가 짠 코드를 한 줄씩 설명할 수 있을 것.

## 진행 방식 (Claude와 같이 할 때)

- 코드는 내가 직접 짠다. Claude는 완성 코드를 주지 않는다.
- 한 번에 개념 하나씩. "왜 이렇게 하는지"부터 설명한다.
- 막히면 힌트부터, 그래도 안 되면 그 부분만 코드로 보여준다.
- 반복문이나 배열 틀처럼 암호와 상관없는 뼈대는 틀을 받아도 된다.

## 환경

- 컴파일러: MSYS2 gcc (`C:\msys64\ucrt64\bin\gcc`)
- 다른 컴퓨터에서 받기: `git clone https://github.com/wjlee-hub/secure-boot-crypto.git`
- cryptopals 빌드/실행 예시 (PowerShell):
  ```
  gcc cryptopals/set1/challenge1.c -o challenge.exe
  .\challenge.exe
  ```
  PowerShell에서는 실행 파일 앞에 `.\`가 필요하다.

## 배운 것

### 파일 구조와 헤더
- `include/` = 헤더(약속, 인터페이스), `src/` = 구현, `test/` = 써 보는 쪽(main)
- `#include`는 그 파일 내용을 그 자리에 **복사해 붙여넣는** 전처리 명령. `gcc -E`로 결과를 볼 수 있다.
- `"..."`는 현재 폴더, 그다음 `-I`로 지정한 폴더에서 찾는다. `<...>`는 시스템 폴더.
- include guard(`#ifndef X / #define X / #endif`)는 **한 .c 파일 안에서** 중복 include를 막는다.
- 헤더에는 **선언**만 두고(`extern int x;`, 함수 원형), **정의**는 .c 파일 한 곳에만 둔다.
  - 정의가 두 .c 파일에 있으면 링커 에러: `multiple definition`
  - 한 파일 안에서 두 번 정의하면 컴파일러 에러: `redefinition`

### C 기초
- `char`도 숫자다. `'7' - '0'` = 7. 아스키 값을 외울 필요 없이 문자로 쓴다 (매직 넘버 피하기).
- 16진수 한 자리 = 2진수 4자리. 표준 C에는 2진수 표기가 없어서 마스크는 16진수로 쓴다 (`0000 0011` → `0x03`).
- 16을 곱하는 것 = `<< 4`. 비트를 붙일 때 `(a << 4) | b`.
- 빈자리를 만들려면 왼쪽으로(`<<`) 민다. `>>`는 아래 비트를 버린다.
- 함수 반환값은 받아서 써야 한다. 일반 변수는 함수에 **복사본**이 넘어간다.
- 배열을 함수에 넘기면 시작 주소가 넘어가서 **원본이 바뀐다**.
- 함수를 main 아래에 둘 거면 main 위에 선언 한 줄이 필요하다.
- 포인터(`char *p`)는 주소 하나만 담는다. 실제 글자들은 따로 연속으로 저장된다. `p[i]`로 배열처럼 쓸 수 있다.
- `const`는 "안 바꾼다"는 약속이다. 바꾸려고 하면 컴파일러가 막는다. 임베디드에서는 const 표가 플래시/ROM에 들어간다 (PC에서는 읽기 전용 메모리 영역).
- 글자는 `char`, 바이트 데이터는 `uint8_t`로 쓴다. 형변환은 비트는 그대로 두고 해석만 바꾼다. 경계(`hex_to_val`)에서 한 번만 바꾼다.
- 반복문 카운터는 `int`로 쓴다 (`uint8_t`면 256칸을 돌 때 무한 반복).

## 진행 상황

- [x] 헤더 / include / 링크 실험. `include/`, `src/`, `test/`에 실험 코드가 남아 있다 (`int hello`, XOR 연습). 아직 AES 코드는 아니다.
- [x] cryptopals Set 1 Challenge 1 (Hex → Base64): 정답 일치
  - 다듬을 것(선택): TODO 주석과 주석 처리된 줄 정리, `ByteNum` → `byte_len`, `|` 식에 괄호 추가
- [ ] cryptopals Set 1 Challenge 2 (Fixed XOR): `challenge2.c` 빈 틀만 있음
  - 1단계: challenge1 코드를 복사해서 첫 번째 입력을 바이트로 바꿔 찍기
  - 2단계: 두 번째 입력도 바이트로 바꾸기
  - 3단계: 같은 칸끼리 XOR
  - 4단계: `printf("%02x")`로 결과 출력하고 정답과 비교
- [ ] Challenge 5 (Repeating-key XOR)
- [ ] AES-128 직접 구현. 가장 쉬운 `AddRoundKey`부터.
- [ ] Challenge 7 (AES-ECB): 직접 만든 AES로 풀기
- [ ] SHA-256

## 추천 순서

cryptopals 1 → 2 → 5 → AES-128 구현 → cryptopals 7 → SHA-256
