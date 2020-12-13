# RDDRONE-BMS772
RDDRONE-BMS772를 위한 NuttX 소스 코드
## Disclaimer - CAUTION WARNING
### CAUTION - WARNING
Lithium and other batteries are dangerous and must be treated with care. 
Rechargeable Lithium Ion batteries are potentially hazardous and can present a serious FIRE HAZARD if damaged, defective or improperly used. Larger Lithium batteries and those used for industrial use involving high discharge current and frequent full discharge cycles require special precautions.

Do not connect this BMS to a lithium ion battery without expertise and  training in handling and use of batteries of this type.
Use appropriate test equipment and safety protocols during development. 

### Important Notice 
NXP provides the enclosed product(s) under the following conditions: 
This reference design is intended for use of ENGINEERING DEVELOPMENT OR EVALUATION PURPOSES ONLY. It is provided as a sample IC pre-soldered to a printed circuit board to make it easier to access inputs, outputs, and supply terminals. This reference design may be used with any development system or other source of I/O signals by simply connecting it to the host MCU or computer board via off-the-shelf cables. Final device in an application will be heavily dependent on proper printed circuit board layout and heat sinking design as well as attention to supply filtering, transient suppression, and I/O signal quality. 
The goods provided may not be complete in terms of required design, marketing, and or manufacturing related protective considerations, including product safety measures typically found in the end product incorporating the goods. 
Due to the open construction of the product, it is the user's responsibility to take any and all appropriate precautions with regard to electrostatic discharge. In order to minimize risks associated with the customers applications, adequate design and operating safeguards must be provided by the customer to minimize inherent or procedural hazards. For any safety concerns, contact NXP sales and technical support services. Should this reference design not meet the specifications indicated in the kit, it may be returned within 30 days from the date of delivery and will be replaced by a new kit. 
NXP reserves the right to make changes without further notice to any products herein. NXP makes no warranty, representation or guarantee regarding the suitability of its products for any particular purpose, nor does NXP assume any liability arising out of the application or use of any product or circuit, and specifically disclaims any and all liability, including without limitation consequential or incidental damages. 
Typical parameters can and do vary in different applications and actual performance may vary over time. All operating parameters, including Typical, must be validated for each customer application by customer’s technical experts. 
NXP does not convey any license under its patent rights nor the rights of others. NXP products are not designed, intended, or authorized for use as components in systems intended for surgical implant into the body, or other applications intended to support or sustain life, or for any other application in which the failure of the NXP product could create a situation where personal injury or death may occur. Should the Buyer purchase or use NXP products for any such unintended or unauthorized application, the Buyer shall indemnify and hold NXP and its officers, employees, subsidiaries, affiliates, and distributors harmless against all claims, costs, damages, and expenses, and reasonable attorney fees arising out of, directly or indirectly, any claim of personal injury or death associated with such unintended or unauthorized use, even if such claim alleges NXP was negligent regarding the design or manufacture of the part.

## sources
* gitbook : https://nxp.gitbook.io/rddrone-bms772/
* 디자인 파일 : https://www.nxp.com/design/designs/rddrone-bms772-smart-battery-management-for-mobile-robotics:RDDRONE-BMS772 

테스트할때 사용 가능한 NXP의 emulator :
https://www.nxp.com/design/development-boards/analog-toolbox/6-cell-battery-pack-to-supply-mc33772-evbs:BATT-6EMULATOR.

여기서는 BMS3.4 패치가 된 nuttx와 nuttx-apps repository를 가져오는 방법과 BMS 소프트웨어를 빌드하는 방법에 대해서 설명한다.
linux환경에서 작업하는 것이 최선이고 아니면 가상 머신을 이용할 수 있다.

NuttX 시작 가이드 : https://nuttx.apache.org/docs/latest/quickstart/quickstart.html.

## git 설치 확인
git이 설치하지 않았따면 아래 명령으로 설치하기
```bash
sudo apt-get update
```
```bash
sudo apt-get install git
```

## nuttx와 app의 incubator 가져오기
drones라는 폴더를 만들어서 여기서 작업
```bash
mkdir -p drones
```
```bash
cd drones
```

nuttx와 nuttx apps git repository를 clone하기
```bash
git clone https://github.com/apache/incubator-nuttx.git nuttx
```
```bash
git clone https://github.com/apache/incubator-nuttx-apps.git apps
```
## 올바른 commit Checkout
apps 디렉토리에서 올바른 commit과 branch를 checkout하기
```bash
(cd apps; git checkout 7a85bc75dcf5632154a09e75cfc431b6e25df463 -b bms772)
```
## nuttx-apps에서 BMS 가져오기
apps 내부에 nxp_bms 폴더를 만들고 해당 폴더 안에 BMS_v1 폴더 만들기
```bash
mkdir -p apps/nxp_bms
```
해당 폴더에 이 repository를 clone하기
```bash
(cd apps/nxp_bms; git clone https://github.com/NXPHoverGames/RDDRONE-BMS772.git BMS_v1)
```
data type을 checkout하기
```bash
(cd apps/nxp_bms/BMS_v1; git clone https://github.com/PX4/public_regulated_data_types)
```
## patches 적용하기
nuttx-apps에 path 적용하기
```bash
(cd apps; patch -p1 < nxp_bms/BMS_v1/Patchfiles/0001-apps-patch-BMS3.4.patch)
```
nuttx 폴더로 가서 알맞는 NuttX commit을 checkout하기
```bash
cd nuttx
```
```bash
git checkout 1115f0104bd404454b72e9e02f4583febb0fe162 -b bms772
```
nuttx patch를 추가하기
```bash
patch -p1 < ../apps/nxp_bms/BMS_v1/Patchfiles/0001-nuttx-patch-BMS3.4.patch
```
## Kconfig tools와 crosscompiler를 설치하기 (처음 사용자)
처음 NuttX 프로젝트라면 Kconfg tools와 cross compiler 설치가 필요하다. 만약 설치된 상태라면 이 단계는 건너뛰자.
### Kconfig tools 설치하기
build essentials과 필요한 것들 설치하기
```bash
sudo apt-get install build-essential
```
```bash
sudo apt-get install flex
```
```bash
sudo apt-get install bison
```
```bash
sudo apt-get install gperf
```
```bash
sudo apt-get install libncurses5-dev
```
nuttx 디렉토리로부터 돌아와서 tools 디렉토리를 만들기
```bash
cd ..
```
```bash
mkdir -p tools
```
```bash
cd tools
```
nuttx tools master를 clone하기
```bash
git clone https://bitbucket.org/nuttx/tools/src/master
```
```bash
cd master
```
patch 적용하기
```bash
patch -p1 < ../../apps/nxp_bms/BMS_v1/Patchfiles/0001-aclocal-fix.patch
```
configure 및 install 하기
```bash
cd kconfig-frontends
```
```bash
./configure --enable-mconf --disable-nconf --disable-gconf --disable-qconf
```
```bash
Make
```
```bash
sudo make install
```
```bash
sudo ldconfig
```
nuttx 디렉토리로 돌아가기
```bash
cd ../../../nuttx
```
### cross 컴파일러 설치하기
설치되어 있지 않은 경우 cross compiler를 다음 명령으로 설치하기:
```bash
sudo apt install gcc-arm-none-eabi
```

## configure 및 binary 만들기
BMS configure하기
```bash
tools/configure.sh -e rddrone-bms772:bmsdebug
```
binary 만들기:
```bash
make
```
## BMS의 CLI(command line interface) 사용하기
BMS에 전원이 연결되어 있고 BMS에 모든게 제대로 연결되어 있는지 확인하기

linux에 있는 minicom과 같이 UART 터미널을 사용하거나 윈도우에서는 PuTTY, teraTerm을 사용하여 COM port에 연결하기
설정:
*	115200 Baud
*	8 data bits
*	1 stop bit

## JLink debugger로 BMS 프로그래밍하기
debugger를 연결하는 방법은 BMS772 release note를 참고하라.

JLink debugger를 사용하여 BMS에 프로그래밍하기 위해서 JLink가 설치되어 있어야한다.
BMS에 전원이 들어왔는지 확인하자.

nuttx.bin파일이(아마도 nuttx 폴더) 위치한 곳에 terminal을 열기
JLink 열기:
```bash
JLinkExe
```
여기에 연결하기:
```bash
connect
```
올바른 장치로 진입:
```bash
S32K144
```
SWD를 사용하여 프로그램하기(굽기):
```bash
s
```
target interface 속도로 1000Khz 사용:
```bash
1000
```
장치를 reset하기:
```bash
r
```
다음 명령을 보내서 전체 flash를 리셋하기:
```bash
w1 0x40020007, 0x44     
```
```bash
w1 0x40020000, 0x80    
```
nuttx binary를 주소 0에 load하기
```bash
loadbin nuttx.bin 0
```
장치를 리셋하기
```bash
r
```
프로그램 실행하기
```bash
g
```
JLinkExe 빠져나오기
```bash
q
```
