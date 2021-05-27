## PYNQ-Z2 GPIO control
### GPIO Control 
- 所有腳位在未給訊號時，皆輸出HIGH
- GPIO設置所需的資料連結與文件
    - Creating a simple Overlay for PYNQ-Z1 board from Vivado HLx
    https://yangtavares.com/2017/07/31/creating-a-simple-overlay-for-pynq-z1-board-from-vivado-hlx/
    - PYNQ-Z2 Reference Manual v1.0
        https://d2m32eurp10079.cloudfront.net/Download/pynqz2_user_manual_v1_0.pdf
    - TUL_PYNQ_Schematic_R12
    https://dpoauwgwqsy2x.cloudfront.net/Download/TUL_PYNQ_Schematic_R12.pdf
- 前置作業 : 建一個GPIO的IP    
    - 在Block Design中建一個GPIO的IP
    ![](https://i.imgur.com/CXODDpj.png)
    - 得到下圖後，點兩下IP
    ![](https://i.imgur.com/YqiVCyg.png)
    - 出現此畫面後，開始依想要的GPIO進行設定
    ![](https://i.imgur.com/llwyMSy.png)

- 使用預設GPIO
  - button (BTN0-BTN3)
      - 選取btns 4bits後，按ok即可
      ![](https://i.imgur.com/eCbTSsk.png)
      
  - LED (LD0-LD3)
    - 選取leds 4bits後，按ok即可
    ![](https://i.imgur.com/VXZnzuQ.png)
    
  - Arduino Shield Connector
      - 類比腳位 (arduino a0 - a5)
      - 數位腳位 (arduino ar0 - ar13)
      - 選取想要的腳位後，按ok即可
      ![](https://i.imgur.com/izkyJxI.png)
      
  - Raspberry Pi Header
    - 選取raspberry pi後，按ok即可
    ![](https://i.imgur.com/4RkpelS.png)
  - 在HDL Wrapper產生後，點選**Open Elaborated Design**
  ![](https://i.imgur.com/Ai7fLC6.png)
  - 跑完後，點選**Window**-->**I/O Ports**，會出現腳位的各種資訊
  ![](https://i.imgur.com/ltBr00U.png)
  - 下圖中，可以從Package Pin中看到他們的PL pins，可和[PYNQ-Z2 Reference Manual v1.0](https://d2m32eurp10079.cloudfront.net/Download/pynqz2_user_manual_v1_0.pdf)中的PL pins進行對照，會發現是一樣的
      - 紅色框框中，即是PL pins，每個腳位都有自己的PL pins
      - 藍色框框中，33代表腳位為HIGH時，輸出3.3v 
      ![](https://i.imgur.com/Y20rzJy.png)
 
:::warning
- 使用預設GPIO但想將其輸出更改腳位時，請參考下面的PWM Control with PYNQ
- 剩下還有很多預設的腳位，可自行嘗試
- 上面的預設腳位，雖然會顯示input/ouput，但實際上測試結果，除了button是input以外，剩下都是output
- 若之後有需要用自訂的Raspberry Pi Header腳位，請先使用預設腳位，並記錄PL pins的順序，這之後會使用到
![](https://i.imgur.com/IPfSXgT.png)
![](https://i.imgur.com/anQHeOb.png)
:::
- 使用自訂GPIO (自訂input/ouput/想要哪些腳位)
    - 前置設定
        - 先設定腳位為**custom**
        ![](https://i.imgur.com/dMNEdyV.png)
        
        - 設置input/output以及個數
        ![](https://i.imgur.com/Pm3Ik9g.png)
        
        - 設定好後，按**Run Connection Automation**
        - 出現下圖畫面後，要手動設定為**custom**，如下圖，所有自訂的GPIO皆要手動設定
        ![](https://i.imgur.com/fyBuTVr.png)
        - 在HDL Wrapper產生後，點選**Open Elaborated Design**-->**Window**-->**I/O Ports**
        - 出現下面畫面後，先更改腳位輸出的電壓
        ![](https://i.imgur.com/E46hWcj.png)

    - Arduino Shield Connector
    在Package Pin中輸入想要的腳位的PL Pins即可，如下圖。
     ![](https://i.imgur.com/MPlF0Y0.png)
    
    - Raspberry Pi Header
        - 當要在Package Pin輸入想要的PL Pins，不能像Arduino Shield Connector，想要甚麼即打甚麼，需要**皆按照預設腳位的Package Pin**來輸入
        
            - Example : 想要5個output和4個input，總共9個腳位
                ![](https://i.imgur.com/ebBGiKL.png)
        - 只能決定想要用的個數，沒辦法決定想要哪幾個腳位
        - 腳位順序是從[TUL_PYNQ_Schematic_R12](http://www.tul.com.tw/download/TUL_PYNQ%20Schematic_R12.pdf)裡面Raspberry Pi的電路圖得知的
        ![](https://i.imgur.com/57zQVZE.png)
        - PYNQ上腳位位置請參考[PYNQ-Z2 Reference Manual v1.0](https://d2m32eurp10079.cloudfront.net/Download/pynqz2_user_manual_v1_0.pdf)
        ![](https://i.imgur.com/b7a9RPP.png)
        - 上面兩張圖互相搭配後，可以得到下面的表。PIN NAME由上而下就是raspberry pi腳位的順序。
            - Example : 用上面5個output和4個input為例(共9個)
                1. 第一個input(9個中的第1個)的PL PIN是W18，在PYNQ上需要將線接在第3個腳位
                2. 第一個output(9個中的第5個)，的PL PIN是Y7，在PYNQ上需要將線接在第31個腳位


            ![](https://i.imgur.com/EhUlnwS.png)


### GPIO Control demo

<iframe width="560" height="315" src="https://www.youtube.com/embed/UBsCNPWudww" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

- 影片中會使用到的資料連結
    - A Verilog Johnson counter was used from here:
        http://www.myhdl.org/docs/examples/jc2.html
    - A VHDL clock divider was used from here: 
        https://allaboutfpga.com/vhdl-code-for-clock-divider/
    - [Master XDC](http://www.tul.com.tw/download/pynq-z2_v1.0.xdc.zip)
- 實作後，修改led0 pin -> T14 (arduino header, pin name AR0)
![](https://i.imgur.com/bO5gc87.gif)
