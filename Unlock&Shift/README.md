# Unlock&Shift

## 1. 프로젝트 개요

### 1-1. 구현 게임

![권제한_3차_프로젝트_스크린샷1](../images/Unlock&Shift/권제한_3차_프로젝트_스크린샷1.png)

**사이드뷰와 탑뷰로 시점을 전환하고 상자를 열면서 진행하는 플랫포머 퍼즐 게임 Unlock&Shift**



**게임 장르 : 플랫포머 퍼즐**

* **핵심 게임 플레이 특징**
  * 퍼즐을 풀어가며 진행하는 플랫포머 게임
  * 변환되는 시점
  * 다양한 기믹을 가진 오브젝트들
  * 최종 목표는 커다란 상자까지 도달하기



### 1-2. 기획 의도

**한 가지 시점으로만 진행하는 게임보단 여러 시점을 오가며 진행하는 게임이 만들고 싶었습니다.**

또한 게임의 장르는 이런 컨셉에 적합한 장르의 게임인 퍼즐류 게임을 기획하게 되었습니다.



### 1-3. 개발 환경

* 사용 게임 엔진 : Unreal Engine 5

* 개발 도구 : Blueprint Visual Script, Blueprint Interface(BPI)



## 2. 게임 구성 요소

### 2-1. 게임 플레이 메커니즘

* 핵심 조작 방식
  * WASD로 캐릭터 이동
  * Space키로 점프
  * F키로 상호작용
* 게임 규칙
  * 여러 오브젝트들과 시점 변환을 사용해 퍼즐을 해결
  * 배치된 플랫폼들을 건너가며 앞으로 진행
  * 열쇠 수집 및 잠긴 문 개방 메커니즘



* 승리 조건
  * 승리 : 스테이지의 목표 지점(커다란 보물 상자)에 도착



### 2-2. 구현 요소

- 플레이어 캐릭터

  - 이동, 점프, Raycast 기능 추가

  - 시점 전환에 따른 이동 방식 변경 처리

- 상호작용 가능 오브젝트

  - 상호작용 가능한 모든 오브젝트의 부모가 될 오브젝트

  - 상호작용 가능 여부만 판단하는 기능 구현

- 상자 오브젝트

  - 다른 상자 오브젝트들의 부모가 될 기본 상자 오브젝트 구현

  - 기본 상자 오브젝트의 자손으로 Destroy 이벤트가 포함된 여러 종류의 상자 오브젝트 구현

- 문/열쇠 오브젝트

  - 올바른 열쇠가 있을 때만 열리는 기능 추가

  - 특정 시점 상태여야 열리는 기능 추가

  - 열릴 때 트랜스폼 조정 및 머티리얼 조정으로 자연스러운 효과 적용

- 기타 오브젝트

  - 이동하는 발판 구현

  - 정해진 특정 위치로 이동시켜주는 포탈 구현

  - 2초 뒤 폭발해 캐릭터를 밀어내는 폭탄 구현



## 3. 개발 과정

#### **플레이어 캐릭터**

![BP_Priest1](../images/Unlock&Shift/BP_Priest1.png)

캐릭터 초기화

---

![BP_Priest2](../images/Unlock&Shift/BP_Priest2.png)

탑뷰 이동

---

![BP_Priest3](../images/Unlock&Shift/BP_Priest3.png)

사이드뷰 이동

---

![BP_Priest4](../images/Unlock&Shift/BP_Priest4.png)

점프

---

![BP_Priest5](../images/Unlock&Shift/BP_Priest5.png)

![BP_Priest8](../images/Unlock&Shift/BP_Priest8.png)

카메라 스위칭 로직 - 카메라 2개를 배치하고 바꿔가며 Active 하는 방식

---

![BP_Priest6](../images/Unlock&Shift/BP_Priest6.png)

![BP_Priest7](../images/Unlock&Shift/BP_Priest7.png)

Raycast 로직

---

#### **오브젝트**

![BPI_Interactable](../images/Unlock&Shift/BPI_Interactable.png)

공통적으로 상속받게 될 BPI_Interactable

---

![BP_MasterItem1](../images/Unlock&Shift/BP_MasterItem1.png)

![BP_MasterItem2](../images/Unlock&Shift/BP_MasterItem2.png)

![BP_MasterItem3](../images/Unlock&Shift/BP_MasterItem3.png)

![BP_MasterItem4](../images/Unlock&Shift/BP_MasterItem4.png)

모든 상호작용 가능 오브젝트들의 부모가 될 MasterItem 블루프린트

---

![BP_Key](../images/Unlock&Shift/BP_Key.png)

열쇠 블루프린트 - 열쇠를 주울 시 지정된 Door의 PickUpKey 이벤트 발생

---

![BP_Door1](../images/Unlock&Shift/BP_Door1.png)

배치된 문의 회전값 변수

---

![BP_Door2](../images/Unlock&Shift/BP_Door2.png)

![BP_Door3](../images/Unlock&Shift/BP_Door3.png)

문 상호작용 및 일정 거리만큼 떨어질 시 닫히는 로직의 블루프린트

---

![BPI_Door](../images/Unlock&Shift/BPI_Door.png)

![BP_Door5](../images/Unlock&Shift/BP_Door5.png)

![BP_Door4](../images/Unlock&Shift/BP_Door4.png)

열쇠를 주울 시 발생하는 이벤트

---

![BP_Door6](../images/Unlock&Shift/BP_Door6.png)

BP_Door의 트리거콜리전 배치

---

![BP_SideDoor1](../images/Unlock&Shift/BP_SideDoor1.png)

사이드뷰 일 시에만 열리는 SideDoor - 열었을 때 사라지는 효과로 머티리얼 조정을 위한 Dynamic Material Instance 생성

---

![BP_SideDoor2](../images/Unlock&Shift/BP_SideDoor2.png)

SideDoor상호작용 시 로직

---

![BP_SideDoor3](../images/Unlock&Shift/BP_SideDoor3.png)

오버랩 되었을 때 사이드뷰 상태일 시 상호작용 가능하게 만드는 로직

---

![BP_SideDoor4](../images/Unlock&Shift/BP_SideDoor4.png)

SideDoor 트리거콜리전 배치

---

![BP_Bomb1](../images/Unlock&Shift/BP_Bomb1.png)

생성 시 머티리얼 조정으로 점점 빛나다가 2초 후 사라지면서 플레이어를 Block하는 SphereCollision Scale을 늘렸다가 다시 줄여서 플레이어가 밀려나게 하는 폭탄 - 게임 진행에도 사용되므로 반복적으로 사용할 수 있게 폭발 후 다시 폭탄이 나오는 상자를 생성

---

![BP_Bomb2](../images/Unlock&Shift/BP_Bomb2.png)

폭탄 머티리얼

---

![BP_ViewChanger](../images/Unlock&Shift/BP_ViewChanger.png)

오버랩 시 시점을 변환시켜 주는 ViewChanger 오브젝트

---

![InteractableChest](../images/Unlock&Shift/InteractableChest.png)

다른 상자들의 부모가 될 상호작용 가능한 상자 블루프린트

---

![ChestToKey](../images/Unlock&Shift/ChestToKey.png)

열쇠를 생성하는 상자

---

![ChestToBomb](../images/Unlock&Shift/ChestToBomb.png)

폭탄을 생성하는 상자

---

![ChestToViewChanger](../images/Unlock&Shift/ChestToViewChanger.png)

시점 전환기를 생성하는 상자 - ViewPos 위치에 생성

---

![ClearChest](../images/Unlock&Shift/ClearChest.png)

게임 클리어 상자 - 커다란 보물 상자

---

![Platform](../images/Unlock&Shift/Platform.png)

움직이는 플랫폼 블루프린트

---

![Teleport1](../images/Unlock&Shift/Teleport1.png)

![Teleport2](../images/Unlock&Shift/Teleport2.png)

캐릭터를 지정 위치로 텔레포트 시켜주는 포탈 - TeleportPos를 편집 가능하고 3D 위젯이 보이게 해서 직관적으로 어디에 텔레포트 시킬 지 설정 가능

---

![Wall1](../images/Unlock&Shift/Wall1.png)

캐릭터가 오보랩 시 다시 뒤로 가지 못하게 벽이 생성되는 Wall 블루프린트

---

![Wall2](../images/Unlock&Shift/Wall2.png)

Wall의 콜리전 배치 - 콜리적에 오버랩 시 기즈모 위치에 벽이 생성된다.

---

![BP_Respawn](../images/Unlock&Shift/BP_Respawn.png)

추락 시 다시 맵 위로 이동시키는 용도로 맵의 추락 지점에 넓게 배치되는 Respawn 블루프린트

---

#### **UI**

![MainMenu](../images/Unlock&Shift/MainMenu.png)

게임 시작 시 볼 수 있는 MainMenu 위젯 블루프린트

---

![GameClear](../images/Unlock&Shift/GameClear.png)

게임 클리어 시 게임 화면에 나타나는 GameClear 위젯 블루프린트

---

![Text1](../images/Unlock&Shift/Text1.png)

![Text2](../images/Unlock&Shift/Text2.png)

튜토리얼 레벨에서 가이드용 텍스트를 출력하기 위해 TextRender 컴포넌트를 활용한 부모 Text 블루프린트

---

![Text3](../images/Unlock&Shift/Text3.png)

부모 Text 블루프린트로부터 자손 블루프린트를 생성해 필요한 텍스트들을 생성 및 배치



## 4. 시연

#### 시연 영상 유튜브 링크

**https://youtu.be/V_e4vgW0bSE**



## 5. 향후 개선 방향

### 5-1. 추가 기능

* 시점 전환 간 부드러움 개선
* 더 다양한 레벨 디자인 요소
* 더 몰입감이 느껴지는 플레이어 가이드
* AI 요소 추가
* 플레이어 컨트롤 개선
* 사운드 디자인
