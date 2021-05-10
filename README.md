# Encrypted-Car-Formation-with-FPGA
1. 使用RSA進行加解密
2. 使用FPGA將加解密運算加速
    - PWM (Verilog)
    - RSA (C語言)
3. 利用Arduino和Raspberry Pi做通訊

## PYNQ-Z2 GPIO control
### GPIO Control 
- 所有腳位在未給訊號時，皆輸出HIGH
- GPIO設置所需的資料連結與文件
    - Creating a simple Overlay for PYNQ-Z1 board from Vivado HLx
    https://yangtavares.com/2017/07/31/creating-a-simple-overlay-for-pynq-z1-board-from-vivado-hlx/
    - PYNQ-Z2 Reference Manual v1.0
        https://d2m32eurp10079.cloudfront.net/Download/pynqz2_user_manual_v1_0.pdf
    - TUL_PYNQ_Schematic_R12
    http://www.tul.com.tw/download/TUL_PYNQ%20Schematic_R12.pdf
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

---
### [PWM Control with PYNQ](http://bbs.elecfans.com/jishu_1737834_1_1.html)
在這小節中，我們要在PL中建立控制邏輯，實現4個PWM輸出和8個方向控制輸出，以利進行麥克納姆輪的控制
- 建立一個新的project
    - 開啟vivado 2019.1
    - 按**Create Project**來建立新的方案
    ![](https://i.imgur.com/c1cR05l.png)

    - Add Source和Add Constraints的設定部分不用，直接按next即可。Board選擇**pynq-z2**
    ![](https://i.imgur.com/eR8BXk1.png)
    - 最後按Finish，即完成建立新的方案
- 建立新的ip
    - 點**Create and Package New IP**
    ![](https://i.imgur.com/yPtWhVL.png)

    - 選擇**Create a new AXI4 peripheral**，並為ip命名
    ![](https://i.imgur.com/QmOJMYf.png)
    - 在這個設計中，我們需要6個暫存器，所以須將Number of Registers改成6
    ![](https://i.imgur.com/ChUq6Ag.png)
    - 最後一步中，選**Edit ip**，接著按Finish，即完成基本設定
    ![](https://i.imgur.com/S0CMzc2.png)
- 在新的project中，需要新增PWM生成器和方向控制的Verilog程式
    - 新增Source
    ![](https://i.imgur.com/TrVBtdJ.png)

    - 選擇**Create File**，並為檔案命名(PWM、chassis_control)和設定存取位置
    ![](https://i.imgur.com/WhPTuii.png)
    
    - 按Finish後，會跳出下面的畫面，用來定義I/O ports名字(PWM、DIR)和I/O的方向(都是output)。
    ![](https://i.imgur.com/h4OA2B1.png)
    
    - PWM Verilog程式
    程式中，module後面即是檔案名字，注意名字需要一致
    ```c=
    module pwm
    #(
            parameter N = 32 //pwm bit width 
    )(
        input clk,
        input rst,
        input [N-1:0]period,
        input [N-1:0]duty,
        output pwm_out
    );
    reg [31:0]fre_cnt;
    always @(posedge clk)begin
        if(rst==1'b0)begin
            fre_cnt <=32'd0;
        end
        else begin
            if(fre_cnt<period) begin
                fre_cnt <= fre_cnt+1'b1;
            end
            else begin
                fre_cnt<=32'd0;
            end
        end
    end
    assign pwm_out = (duty>fre_cnt);
    endmodule
    ```
    - 方向控制 Verilog程式
    
    ```c=
    module chassis_control
    #(parameter DIRECTION_WIDTH=3) (
        input  wire clk, rst_n,
        input  wire [DIRECTION_WIDTH-1:0] direction,
        output reg [7:0] DIR_output
    );

    always @ (posedge clk)
    if(rst_n == 1'b0)begin
        DIR_output[0] <=1'b0;
        DIR_output[1] <=1'b0;
        DIR_output[2] <=1'b0;
        DIR_output[3] <=1'b0;
        DIR_output[4] <=1'b0;
        DIR_output[5] <=1'b0;
        DIR_output[6] <=1'b0;
        DIR_output[7] <=1'b0;
    end
    else
        begin
           case (direction) 
            3'd0 ://Stop
                begin
                DIR_output[0] <=1'b0;
                DIR_output[1] <=1'b0;
                DIR_output[2] <=1'b0;
                DIR_output[3] <=1'b0;
                DIR_output[4] <=1'b0;
                DIR_output[5] <=1'b0;
                DIR_output[6] <=1'b0;
                DIR_output[7] <=1'b0;
                end  

            3'd1 : //Forward
            begin
                DIR_output[0] <=1'b1;
                DIR_output[1] <=1'b0;
                DIR_output[2] <=1'b1;
                DIR_output[3] <=1'b0;
                DIR_output[4] <=1'b1;
                DIR_output[5] <=1'b0;
                DIR_output[6] <=1'b1;
                DIR_output[7] <=1'b0;
            end

            3'd2 : //Backward
            begin
                DIR_output[0] <=1'b0;
                DIR_output[1] <=1'b1;
                DIR_output[2] <=1'b0;
                DIR_output[3] <=1'b1;
                DIR_output[4] <=1'b0;
                DIR_output[5] <=1'b1;
                DIR_output[6] <=1'b0;
                DIR_output[7] <=1'b1;
            end

           3'd3 : //Left
            begin
                DIR_output[0] <=1'b0;
                DIR_output[1] <=1'b1;
                DIR_output[2] <=1'b0;
                DIR_output[3] <=1'b1;
                DIR_output[4] <=1'b1;
                DIR_output[5] <=1'b0;
                DIR_output[6] <=1'b1;
                DIR_output[7] <=1'b0;
            end

           3'd4: //Right
            begin
                DIR_output[0] <=1'b1;
                DIR_output[1] <=1'b0;
                DIR_output[2] <=1'b1;
                DIR_output[3] <=1'b0;
                DIR_output[4] <=1'b0;
                DIR_output[5] <=1'b1;
                DIR_output[6] <=1'b0;
                DIR_output[7] <=1'b1;
            end

            default: 
                begin
                    DIR_output[0] <=1'b0;
                    DIR_output[1] <=1'b0;
                    DIR_output[2] <=1'b0;
                    DIR_output[3] <=1'b0;
                    DIR_output[4] <=1'b0;
                    DIR_output[5] <=1'b0;
                    DIR_output[6] <=1'b0;
                    DIR_output[7] <=1'b0;
                end
         endcase
        end
    endmodule
    ```
   - 打開vivado自動生成的**xxx_v1_0_S00_AXI.v**檔(xxx是這個檔案的名字)，並在此檔案(通訊的module)，在特定位置增加下列程式
    ```c=
    // Users to add ports here
    output wire [3:0] PWM_output,
    output wire [7:0] DIR_output,
    // User ports ends
    ```
    - 在同一個檔案的下方，在特定位置增加下列程式，以利對pwm和方向控制的module進行例化
    ```c=
    // Add user logic here
        chassis_control #(.DIRECTION_WIDTH(3)) chassis_control_inst
        (
            .clk(S_AXI_ACLK),
            .rst_n(S_AXI_ARESETN),
            .direction(slv_reg0),
            .DIR_output(DIR_output)
        );

        pwm #(.N(32)) pwm_instance_0 (
                    .clk(S_AXI_ACLK),
                    .rst(S_AXI_ARESETN),
                    .period(slv_reg1),
                    .duty(slv_reg2),
                    .pwm_out(PWM_output[0])
                );

        pwm #(.N(32)) pwm_instance_1 (
                    .clk(S_AXI_ACLK),
                    .rst(S_AXI_ARESETN),
                    .period(slv_reg1),
                    .duty(slv_reg3),
                    .pwm_out(PWM_output[1])
                );

        pwm #(.N(32)) pwm_instance_2 (
                    .clk(S_AXI_ACLK),
                    .rst(S_AXI_ARESETN),
                    .period(slv_reg1),
                    .duty(slv_reg4),
                    .pwm_out(PWM_output[2])
                );

        pwm #(.N(32)) pwm_instance_3 (
                    .clk(S_AXI_ACLK),
                    .rst(S_AXI_ARESETN),
                    .period(slv_reg1),
                    .duty(slv_reg5),
                    .pwm_out(PWM_output[3])
                );
            // User logic ends

            endmodule
    ```
    - 打開vivado自動生成的**xxx_control_v1_0.v**，在特定位置增加下列程式
    ```c=
    // Users to add ports here
    output wire [3:0] PWM_output,
    output wire [7:0] DIR_output,
    // User ports ends
    ```
    - 在同一個檔案中，在指定位置增加下列程式(  PWM_output和DIR_output那兩行)
    ```c=
    // Instantiation of Axi Bus InteRFace S00_AXI
            chassis_control_v1_0_S00_AXI # ( 
                    .C_S_AXI_DATA_WIDTH(C_S00_AXI_DATA_WIDTH),
                    .C_S_AXI_ADDR_WIDTH(C_S00_AXI_ADDR_WIDTH)
            ) chassis_control_v1_0_S00_AXI_inst (
                .PWM_output(PWM_output),
                .DIR_output(DIR_output),
                .S_AXI_ACLK(s00_axi_aclk), 
                ...
    ```    
    - 程式修改完成後，點**Run Synthesis**->**OK**->**Overwrite**，等Synthesis Completed畫面跑出來後，點**Cancel**即可
    ![](https://i.imgur.com/2O4TG0C.png)
    ![](https://i.imgur.com/lJRAIZR.png)

    - 點**Tools** -> **Create and Package New IP**，選擇**Package your current project**，選擇要存ip的位置，並完成ip的最終封裝  
    ![](https://i.imgur.com/zxvAfzi.png)
    ![](https://i.imgur.com/XdZlscB.png)

- 重新建立一個新的project，board一樣選pynq-z2
    - **Tools** -> **Create and Package New IP**，選擇**Package a specified directory**，位置選擇你剛剛儲存ip的地方，接著選**open**
    ![](https://i.imgur.com/oUVGWks.png)

    - 選擇**Review and Package**，並點**Package IP**
    ![](https://i.imgur.com/TAOWbp0.png)

    - 選**IP Catalog**，輸入ip名稱，即可找到剛剛建立好的ip，
    ![](https://i.imgur.com/uJRF9h0.png)

    - **IP INTEGRATOR** -> **Create Block Design**，加入ip並點選**Run Block Automation**，繪製下圖
    ![](https://i.imgur.com/Ju2TedI.png)
    :::warning
    搜尋ip時，會看到兩種檔名，記得選檔名為xxx_v1_0_v1_0的。兩種檔名的ip會長得不一樣，要注意!
    ![](https://i.imgur.com/hqeZ3wU.png)
    :::
    
    - 在繪製的過程中，會發現少了兩個port，此時要先右鍵點選要增加port的地方(PWM_output、DIR_output)，選**Create Port**，接著按**OK**即可
    ![](https://i.imgur.com/wNwY4aJ.png)
    
    - 接著按**OK**，就會看到新的port了!
    ![](https://i.imgur.com/GLm8GPV.png)
    
    - Create HDL Wrapper
    ![](https://i.imgur.com/NWJf3Pz.png)

    - 加入.xdc檔
    ![](https://i.imgur.com/Ue5SZbB.png)
    
    - 打開檔案，改變其中的設定，將4個PWM輸出綁定在4顆LED上，將8個方向輸出綁定在Arduino接口的AR0~AR7
    ```c=
    ## LEDs
    set_property -dict {PACKAGE_PIN R14 IOSTANDARD LVCMOS33} [get_ports {PWM_output[0]}]
    set_property -dict {PACKAGE_PIN P14 IOSTANDARD LVCMOS33} [get_ports {PWM_output[1]}]
    set_property -dict {PACKAGE_PIN N16 IOSTANDARD LVCMOS33} [get_ports {PWM_output[2]}]
    set_property -dict {PACKAGE_PIN M14 IOSTANDARD LVCMOS33} [get_ports {PWM_output[3]}]

    ## Arduino GPIO
    set_property -dict {PACKAGE_PIN T14 IOSTANDARD LVCMOS33} [get_ports {DIR_output[0]}]
    set_property -dict {PACKAGE_PIN U12 IOSTANDARD LVCMOS33} [get_ports {DIR_output[1]}]
    set_property -dict {PACKAGE_PIN U13 IOSTANDARD LVCMOS33} [get_ports {DIR_output[2]}]
    set_property -dict {PACKAGE_PIN V13 IOSTANDARD LVCMOS33} [get_ports {DIR_output[3]}]
    set_property -dict {PACKAGE_PIN V15 IOSTANDARD LVCMOS33} [get_ports {DIR_output[4]}]
    set_property -dict {PACKAGE_PIN T15 IOSTANDARD LVCMOS33} [get_ports {DIR_output[5]}]
    set_property -dict {PACKAGE_PIN R16 IOSTANDARD LVCMOS33} [get_ports {DIR_output[6]}]
    set_property -dict {PACKAGE_PIN U17 IOSTANDARD LVCMOS33} [get_ports {DIR_output[7]}]
    ```
    - 繪製好圖後，選**Bitstream**->**OK**->**Cancel**，匯出.bit檔
    ![](https://i.imgur.com/oHC1tKm.png)

    - **File** -> **Export** -> **Export Block Design**，匯出.tcl檔(可以自己改檔名)
    ![](https://i.imgur.com/E0iEvCW.png)

- 寫程式，控制PWM的Period和Duty Cycle
    - PYNQ與電腦連線後，開機，打開Jupyter-Notebook (http://192.168.2.99 )，將剛剛存好的.bit和.tcl檔上傳
    ![](https://i.imgur.com/9sMIRFX.png)
    - 開python3，並撰寫下列程式，如下圖
    ```c=
    from pynq import Overlay
    from pynq import MMIO
    from time import sleep
    base = Overlay("/home/xilinx/jupyter_notebooks/20190807_test/chassis_control.bit")
    base.ip_dict
    base.download()
    chassis = MMIO(0x43C00000, 0x10000)
    chassis.write(0x04, 10000)
    print("PWM Period = ", chassis.read(0x04))
    while(1):
        for i in range(4):
            chassis.write(0x08, i*2500)
            chassis.write(0x0C, 10000-i*2500)
            chassis.write(0x10, i*2500)
            chassis.write(0x14, 10000-i*2500)
            sleep(0.5)
        for i in range(4):
            chassis.write(0x08, 10000-i*2500)
            chassis.write(0x0C, i*2500)
            chassis.write(0x10, 10000-i*2500)
            chassis.write(0x14, i*2500)
            sleep(0.5)
    for i in range(5):
        chassis.write(0x00, i)
        sleep(1)
    ```  
    ![](https://i.imgur.com/mKOzytW.png)
    ![](https://i.imgur.com/KVQZ2Sw.png)    
    - 0x04是PWM的Period，0x08到0x14是四顆LED的暫存器位置，後面的數字是Duty Cycle。按了RUN之後，會看到下圖的成品
    ![](https://i.imgur.com/Jdqvq16.gif)
