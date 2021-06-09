\page intro Introduction

<table set border="0">
 <tr><td>Onethinx LoRaWAN module is a purpose-built module for engineers and companies that want to get into the LoRa and LoRaWAN space, design their own product or more easily design products for their clients, but do not want to spend their time developing the LoRaWAN stack, hardware, RF, matching network, LoRa antenna, deal with security and certifications, etc. Onethinx module, with its dual ARM Cortex M0+ and M4 core offers an unpresidented amount of security, ease of use and reliability. It utilizes PSoC6s' ARM Cortex M0+ core to securely store and lock our unique, and easy to use LoRa/LoRaWAN stack, while it allows you to use the full ARM Cortex M4 core for your application, without worry that it will negatively influence the operation of the LoRa/LoRaWAN stack. PSoC 6 microcontroller also integrates the (in silicon) Embedded Secure Element and Hardware Crypto Engine which expands its security capabilities without compromising ease of use (unlinke modules that utilize external secure elements or none at all). Encription of all LoRaWAN messages is encripted automatically by the stack with the use of the Embedded Secure Element. 

Furthermore, Onethinx module uses the latest and best in class Semtech SX1261 LoRa radio chip for the EU 868 MHz and SX1262 LoRa radio chip for US 915 MHz and AU 923 MHz module versions. The newest generation of Semtech SX126X radio chips improoves power efficiency while also adding several additional features like SF5, higher output power, smaller chips size, lower power consumption, etc. Onethinx module matching network and integrated high-efficiency omnidirectional antenna are specially designed and matched for the region they are used in, while keeping everything in a small thumb-sized package measuring only 24.5 mm x 20 mm (incl. antenna). This allows you, not only to integrate the Onethinx LoRaWAN module in small sized applications, but also allows you not to be an RF matching and RF design expert in order to use our all-integrated LoRaWAN module. 

Onethinx LoRaWAN module also allows you to use the onboard Bluetooth 5 (external antenna). The availability of Bluetooth on the module has prooven most useful for Firmware Over The Air updates. It allows the end user to use a smartphone with an application to upload the latest revision of your M4 application to the module. Using the end users phone to perform the Bluetooth FOTA has prooven to be most viable option for all our clients due to the wide use of smartphones.

Onethinx easy-to-use LoRaWAN API consists of several easy-to-use functions. These functions are called from the Cortex M4 core, where the users application resides, and they communicate the necessary information to the Cortex M0+ core, where the LoRa/LoRaWAN stack resides. The two cores communicate using Inter Processor Communication (IPC). This is all handeled in the background when user calls the functions, which additionaly eases the development.

<td> \image html OTX_render1.png width=400px
</table>

Onethinx LoRaWAN module is CE, FCC and LoRa Alliance certified.
 
Additional resources:
 - <a href="https://www.onethinx.com/">Onethinx Web</a>
 - <a href="https://forum.onethinx.com/">Forum</a>
 - <a href="https://github.com/onethinx">Github</a>
 - <a href="https://github.com/onethinx/Core_Datasheet">Datasheet</a>
 - <a href="https://github.com/onethinx/CAD_libraries">Cad Libraries</a>
 - <a href="https://www.facebook.com/Onethinx">Facebook</a>
 - <a href="https://www.linkedin.com/company/onethinx">LinkedIn</a>
 - <a href="https://twitter.com/onethinx">Twitter</a>

\page getstart Getting Started
    \section ide Installing the IDE
    This guide will show you how to setup Visual Studio Code with the Onethinx Core dependencies pack.
        \subsection idewindows Windows
        1. <b>Download prerequisites</b>
         - <a href="https://code.visualstudio.com/download">Download Visual Studio Code</a>
         - <a href="https://github.com/onethinx/VSCode_OnethinxPack_Windows/archive/master.zip">Download the Onethinx dependencies pack for Windows</a>
        2. <b>Install VS Code & extensions</b>
         - Install VS Code.
         - Install extensions:
             - ARM Support For Visual Studio Code (dan-c-underwood)
             - C/C++ IntelliSense, debugging (microsoft)
             - CMake language support (twxs)
             - CMake Tools (microsoft)
             - Cortex-Debug GDB support (marus25)
             - LinkerScript support for GNU (Zixuan Wang)
             - Open in Application (Fabio Spampinato)
             - Output Colorizer (IBM)
             - Tasks (actboy168)
        3. <b>Install the Onethinx Dependencies Pack</b>
         - Unzip the pack archive to your local harddisk (eg: C:\VSCode_OnethinxPack_Windows).
         - Open your command prompt (cmd).
         - Drag and drop the file setVariables.bat to your command prompt (or type C:\VSCode_OnethinxPack_Windows\setVariables.bat).
         - Press enter, you'll see the environment variables and the path being set.
         - Restart your machine.
        4. <b>Check</b>
         - If CMake, Make and the compiler is correctly installed by typing the following into your command prompt or terminal window of VS Code.
             - <tt>cmake -version</tt>
             - <tt>mingw32-make -v</tt>
             - <tt>arm-none-eabi-gcc -v</tt>
        5. <b>Remind</b>
         - After changing the device configuration (or project file structure) to use
            - Clean Reconfigure
            - Clean Rebuild in order to build the image properly
         - To delete the contents of the build folder
            - if you copied the project including build folder from another location / machine
            - when build fails.
         - This pack contains the 64bit version of CMake. Replace with the 32bit version if you run on a 32bit machine.

        Windows<hr>
        \subsection idemacos MacOS
        1. <b>Download prerequisites</b>
         - <a href="https://code.visualstudio.com/download">Download Visual Studio Code</a>
         - <a href="https://github.com/onethinx/VSCode_OnethinxPack_macOS/archive/master.zip">Download the Onethinx dependencies pack for Mac OS</a>
         - <a href="https://cmake.org/download/">Download CMake</a>
         - Install homebrew GNU by: make brew install homebrew/core/make as <a href="https://apple.stackexchange.com/questions/261918/how-to-upgrade-gnu-make-in-os-x-el-capitan">explained here</a>
        2. <b>Install VS Code & extensions</b>
         - Install CMake.
         - Install VS Code.
         - Install extensions:
             - ARM Support For Visual Studio Code (dan-c-underwood)
             - C/C++ IntelliSense, debugging (microsoft)
             - CMake language support (twxs)
             - CMake Tools (microsoft)
             - Cortex-Debug GDB support (marus25)
             - LinkerScript support for GNU (Zixuan Wang)
             - Open in Application (Fabio Spampinato)
             - Output Colorizer (IBM)
             - Tasks (actboy168)
         - Apply the CMake path to VS Settings: "cmake.cmakePath": "/Applications/CMake.app/Contents/bin/cmake",
        3. <b>Install the Onethinx Dependencies Pack</b>
         - Unzip the pack archive to your local harddisk (eg: /Applications/VSCode_OnethinxPack_macOS).
         - If the file ~.bash_profile doesn't exist, create it: Terminal >> <span style="background-color: #e6e6e6">cd ~ && touch .bash_profile</span>
         - Open ~.bash_profile: Terminal >> cd ~ && open -e .bash_profile
         - Add this to the end of the file (make sure you enter the correct path) and save:
         - # Loading environment variables for the Onethinx Pack
         - source /locationOfYour/VSCode_OnethinxPack_macOS/variables.env
         - Set the correct path in this pack's variables.env file.
         - Restart your machine (or log-out and log-in) to reload the environment variables.
        4. <b>Check</b>
         - If CMake, Make and the compiler is correctly installed by typing the following into your command prompt or terminal window of VS Code.
             - <tt>cmake -version</tt>
             - <tt>mingw32-make -v</tt>
             - <tt>arm-none-eabi-gcc -v</tt>
        5. <b>Remind</b>
         - After changing the device configuration (or project file structure) to use
            - Clean Reconfigure
            - Clean Rebuild in order to build the image properly
         - To delete the contents of the build folder
            - if you copied the project including build folder from another location / machine
            - when build fails.
         - This pack contains the 64bit version of CMake. Replace with the 32bit version if you run on a 32bit machine.

    MacOS<hr>
        \subsection idelinux Linux
        1. <b>Download prerequisites</b>
         - <a href="https://code.visualstudio.com/download">Download Visual Studio Code</a>
         - <a href="https://github.com/onethinx/VSCode_OnethinxPack_Linux/archive/master.zip">Download Onethinx Dependencies Pack</a>
         - Install CMake: <tt>sudo apt install cmake</tt>
        2. <b>Install VS Code & extensions</b>
         - Install VS Code.
         - Install extensions:
             - ARM Support For Visual Studio Code (dan-c-underwood)
             - C/C++ IntelliSense, debugging (microsoft)
             - CMake language support (twxs)
             - CMake Tools (microsoft)
             - Cortex-Debug GDB support (marus25)
             - LinkerScript support for GNU (Zixuan Wang)
             - Open in Application (Fabio Spampinato)
             - Output Colorizer (IBM)
             - Tasks (actboy168)
         - Apply the OpenOCD USB rules by running
            <tt>yourpath\VSCode_OnethinxPack_Linux/tools_2.0/linux/openocd/udev_rules/install_rules.sh</tt>
        3. Install the Onethinx Dependencies Pack
         - Unzip the pack archive to your local harddisk (eg: /Applications/VSCode_OnethinxPack_Linux).
         - Open ~.profile: Terminal >> <tt>cd ~ && sudo nano .profile</tt>
         - Add this to the end of the file (make sure you enter the correct path) and save:<br>
            <span style="background-color: #e6e6e6"># Loading environment variables for the Onethinx Pack</span><br>
            <span style="background-color: #e6e6e6">source /locationOfYour/VSCode_OnethinxPack_macOS/variables.env</span><br>
         - Set the correct path in this pack's <span style="background-color: #e6e6e6">variables.env</span> file.
         - Restart your machine (or log-out and log-in) to reload the environment variables.
        4. Check
         - If CMake, Make and the compiler is correctly installed by typing the following into your terminal or terminal window of VS Code.
             - <tt>cmake -version</tt>
             - <tt>make -v</tt>
             - <tt>arm-none-eabi-gcc -v</tt>
        5. Remind
         - After changing the device configuration (or project file structure) to use
            - Clean Reconfigure
            - Clean Rebuild in order to build the image properly
         - To delete the contents of the build folder
            - if you copied the project including build folder from another location / machine
            - when build fails.

        Linux<hr>

    \section programmer Programmer/Debugger
    In order to program a Onethinx LoRaWAN module, you need a programmer. You can also find our recomendations on our <a href="https://forum.onethinx.com/t/which-programmers-debuggers-are-compatible/216"><b>forum</b></a>.

    \emoji :white_check_mark: MiniProg 4 < recommended
        - <a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-005-miniprog4-program-and-debug-kit">CY8CKIT-005 - $99.00</a> For our dev.kit, use an extension header, eg. <a href="https://www.samtec.com/products/ssq-105-03-f-s">Samtec SSQ-105-03-F-S</a>

    \emoji :white_check_mark: KitProg 2 (<a href="https://forum.onethinx.com/t/kitprog-2-voltage-upgrade/376">fter voltage upgrade</a>!! and <a href="https://community.cypress.com/t5/ModusToolbox-General/KitProg-firmware-out-of-date-message/td-p/72805">upgrading to KitProg 3</a>)
        - <a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-147-psoc-4100ps-prototyping-kit">CY8CKIT-147 - $10.00</a> (needs <a href="https://forum.onethinx.com/t/kitprog-2-voltage-upgrade/376">upgrade</a>!!) < budgetary recommended
        - <a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-145-40xx-psoc-4000s-capsense-prototyping-kit">CY8CKIT-145 - $15.00</a> (needs <a href="https://forum.onethinx.com/t/kitprog-2-voltage-upgrade/376">upgrade</a>!!)
        - <a href="https://www.cypress.com/documentation/development-kitsboards/psoc-4-cy8ckit-146-4xxx-prototyping-kits">CY8CKIT-146 - $15.00</a> (needs <a href="https://forum.onethinx.com/t/kitprog-2-voltage-upgrade/376">upgrade</a>!!)
        - <a href="https://www.cypress.com/documentation/development-kitsboards/psoc-6-ble-prototyping-kit-cy8cproto-063-ble">CY8CPROTO-063-BLE - $20.00</a> (needs <a href="https://forum.onethinx.com/t/kitprog-2-voltage-upgrade/376">upgrade</a>!!)

    \emoji :grey_question: KitProg 3
        - <a href="https://www.cypress.com/documentation/development-kitsboards/psoc-6-wi-fi-bt-prototyping-kit-cy8cproto-062-4343w">CY8CPROTO-062-4343W - $30.00</a>

    \emoji :white_check_mark: Segger J-Link
        - <a href="https://www.segger.com/products/debug-probes/j-link/models/j-link-edu/">J-Link EDU - $60.00</a>
        - <a href="https://www.segger.com/products/debug-probes/j-link/models/j-link-pro/">J-Link PRO - $800.00</a>

    \emoji :x: KitProg 1 Doesn’t work! (<strike>should work according to <a href="https://forum.onethinx.com/t/error-on-uploading-the-code-solved/118/5">this topic</a></strike>, however not erised)
        - <strike><a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-043-psoc-4-m-series-prototyping-kit">CY8CKIT-043 - $10.00</a></strike>
        - <strike><a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-059-psoc-5lp-prototyping-kit-onboard-programmer-and">CY8CKIT-059 - $10.00</a></strike>

    \emoji :grey_question: ST Link (after <a href="https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board/">converting to J-Link?</a>)
        - <a href="https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-nucleo-boards/nucleo-f030r8.html">NUCLEO-F030R8</a>

    \emoji :x: MiniProg 3 (Not working)
        - <a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-002-psoc-miniprog3-program-and-debug-kit">CY8CKIT-002</a>
    
    <b>NOTE</b>: If you find that a programmer that is not listed here either works or does not work with our module, please let us know on the <a href="https://forum.onethinx.com/t/which-programmers-debuggers-are-compatible/216"><b>forum</b></a>.<hr>
    
    \section examples Downloading the examples
    Onethinx examples can be found on our <a href="https://github.com/onethinx/Onethinx_Creator_Examples"><b>Github</b></a> page. For detailed explanation of the examples please see the \ref ex_examples "Examples" page of this document.
    <hr>

    \section apiLibs Using the correct API libraries
    As we update our Onethinx module, newer versions of the Onethinx API and stack come out. Onethinx stack is programmed on the modules ARM Cortex M0+ core, while your application, which you will program on the ARM Cortex M4 core uses the Onethinx API to communicate with the stack. Not all stack versions support the same API version (there are versions of the stack that do support same API). Although we strive to have one single API version for all future stacks, updates are inevitable. Examples found on our Github, are usually updated to the latest API version.
    Onethinx API can be found on our <a href="https://github.com/onethinx">Github</a> page:
        - <a href="https://github.com/onethinx/OnethinxCoreAPI"><b>LoRaWAN API</b></a>
        - <a href="https://github.com/onethinx/OnethinxCoreAPI_Extended"><b>LoRa API</b></a>

    The API version you are using should always match the Stack version that is on the module according to this table:
    <table>
        <caption id="multi_row">Onethinx API Versions</caption>
        <tr><th>Stack Version         <th>LoRaWAN API Version       <th>LoRa API Version
        <tr><td>0xAD                  <td>0xAD                      <td>not available
        <tr><td>0xAE                  <td>0xAD                      <td>not available
        <tr><td>0xB0                  <td>0xB0                      <td>not available
        <tr><td>0xB1                  <td>0xB1                      <td>not available
        <tr><td>0xB2                  <td>0xB2                      <td>not available
        <tr><td>0xB3                  <td>0xB2                      <td>not available
        <tr><td>0xB4                  <td>0xB2                      <td>not available
        <tr><td>0xB5                  <td>0xB2                      <td>not available
        <tr><td>0xB6                  <td>not public                <td>not available
        <tr><td>0xB7                  <td>not public                <td>not available
        <tr><td>0xB8                  <td>0xB8                      <td>0xB8
        <tr><td>0xB9                  <td>0xB8                      <td>0xB8
        <tr><td>0xBA                  <td>0xB8                      <td>0xB8
        <tr><td>0xBB                  <td>0xBB                      <td>0xB8
        <tr><td>0xBC                  <td>0xBB                      <td>0xB8
        <tr><td>0xBD                  <td>not public                <td>not public
        <tr><td>0xBE                  <td>0xBE                      <td>0xBE
        <tr><td>0xBF                  <td>0xBE                      <td>0xBE
        <tr><td>0xC0                  <td>not public                <td>not public
        <tr><td>0xC1                  <td>0xC1                      <td>0xC1
    </table>
    If the tables in this document are not up to date, please consult the tables found in the <a href="https://github.com/onethinx/OnethinxCoreAPI">LoRaWAN API</a> and <a href="https://github.com/onethinx/OnethinxCoreAPI_Extended">LoRa API</a> pages on our Github.

    <b>Dont know which stack version your module has?</b> In order to find out which version of the stack your module has, you can copy and run a piece of code found  here: \ref ex_deveui "Stack Version Code". Similar code can also be found on the bottom of this <a href="https://github.com/onethinx/OnethinxCoreAPI">Github page</a>.

    <b>NOTE</b>: Once you find a stable version that suits you, you tested your device with it and you plan to go to mass production, we recommend to stick to that version when ordering modules.
    <hr>

    \section lwkeys LoRaWAN Keys and Connection
    In order to connect to a LoRaWAN network, you need a LoRaWAN gateway and LoRaWAN keys. Keys are 
    
    If you are using The Things Network (or some other public network), you may not need a gateway to test your LoRaWAN device because there may already be coverage in your area by a gateway somebody else has placed. Although this saves you some money not needing to put up your own gateway, we still recommend that you get your own gateway as this will save you a lot of time during development of your product as there are many things that can influence the connection. It is acceptable to use public gateways for prototyping. The public gateway may be far and the network conditions may be poor on a certain day, limiting your development. Also, the person that owns the public gateway, may decide they will unplug the gateway for a day, which will disable your connection to the Network Server. This is why, for serious development, we recommend having your own gateway.

    Onethinx LoRaWAN module supports 1.0.2 LoRaWAN specification and is LoRa Alliance Certified for this version. In order to connect to any LoRaWAN network, the LoRaWAN stack needs to know these 3 parameters (keys):
        - <b>DevEUI</b> is a unique ID in the IEEE EUI64 address space used to identify a device. There must not be 2 same DevEUIs on different devices! DevEUI is supplied by the device manufacturer, in this case, each Onethinx module has its own unique DevEUI which can be used.
        - <b>AppEUI</b> is a global application ID in the IEEE EUI64 address space identifying the join server during the over the air activation. For non-private networks it corresponds to a subdomain of joineuis.lora-alliance.org. This server name is used to find the IP address of the join server via DNS. The AppEUI can be different for each device or it can also be same for all device. It also depends on what kind of application server you are using. AppEUI identifies the join server and it can only be provided by the owner of the join server.
        - <b>AppKey</b> is an encryption key used for messages during every Over The Air Activation (OTAA). After the activation the AppSKey is used. A listener knowing the AppKey can derive the AppSKey. So you want to keep the AppKey secret. Which side of the communication channel creates it, is not important. You simply want to be sure that it is random and unique for each device.

    In Onethinx project, the LoRaWAN keys are usually saved in LoRaWAN_keys.h header file. This header file is located in the project source folder:
    Project -> source -> OnethinxCore -> LoRaWAN_keys.h

    In LoRaWAN_keys.h you will find an initalization structure, where you need to fill in the DevEUI (or use internal), AppEUI and AppKey. You can replace the zero (0x00) values in the structure with your keys.

    You can use a different DevEUI:
    \code
    LoRaWAN_keys_t TTN_OTAAkeys = {
        .KeyType 						= OTAA_10x_key,
        .PublicNetwork					= true,
        .OTAA_10x.DevEui				= {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
        .OTAA_10x.AppEui				= {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
        .OTAA_10x.AppKey				= {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}
    };
    \endcode

    Or use the internal unique DevEUI that is provided with every module:
    \code
    LoRaWAN_keys_t TTN_OTAAkeys = {
        .KeyType 						= OTAA_10x_key,
        .PublicNetwork					= true,
        .OTAA_10x.DevEui				= thisDevEUI,
        .OTAA_10x.AppEui				= {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
        .OTAA_10x.AppKey				= {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}
    };
    \endcode

    There are several ways to read out or to extract <b>Onethinx DevEUI</b> from a Onethinx module:
        1. <a href="OTX-18-Programmer"><b>OTX-18-Programmer</b></a> - This program (made by Onethinx) allows you to read our a DevEUI, but also, if needed, to program a .hex or an .elf file to the module using OpenOCD. This program is written in C# (Visual Studio) and the code is available so you can make your own program with it. For example, you can ceate a factory tester that reads out the internal DevEUI and writes the AppEUI and AppKey in with OpenOCD with the help of this programs source code.
        2. Directly from code by using this code \ref ex_deveui "DevEUI extraction"

    LoRaWAN Keys and Connection<hr>
    \section builddebug Building and Debugging
    Now that you have installed Visual Studio Code, gotten a programmer/debugger, downloaded the examples (matched the API if needed), you can get started with the examples. 
    
    If you have access to a LoRaWAN gateway, we suggest to start with the "Hello World" example. If you do not have access to a LoRaWAN gateway or a LoRaWAN network in you vicinity, you can get started with the Lora2LoRa example. In order to use LoRaWAN you need access to a LoRaWAN gateway and/or network, however in order to use LoRa, you do not need these because you can achieve LoRa communication between 2 modules (at least). To get details and differences between LoRa and LoRaWAN I suggest that you go to the \ref faq_loralorawan "LoRa vs LoRaWAN" page.

    To run the example, please open VSCode. A wellcome page will open where you can start. Start by pressing "Open Folder" (Or go to: File->Open Folder) and select the folder with the example you wish to run.

    \image html openFolderExample.png width=600px

    When opening the example for the first time (or when you move the project to a different folder), you will be asked to select the compiler. Select the latest GCC compiler you have installed. In this case, it is "GCC for arm-none-eabi 9.2.1".

    \image html vscodeCopilerSelect.png width=600px

    In order to build the code, you can press the "Build" button on the bottom, or press "Build and Launch" to Build and Launch debugging.

    \image html vscodeBuild.png width=600px

    In the Debug mode, you can use the buttons on the top to:
     - Continue/Pause
     - Step Over
     - Step Into
     - Step Out
     - Restart
     - Stop Debugging Session

    \image html debugButtons.png width=400px

    Building and Debugging<hr>

    \section gs_psoccreator PSoC Creator
    In order to extract the full power of PSoC 6 dual ARM Cortex Core microcontroller, we recommend that you use PSoC Creator for the hadware set up. Although you can use only PSoC Creator to program PSoC chips, you are not able to use PSoC Creator on its own to program/debug/make project for Onethinx module. This is because PSoC Creator needs access to the M0+ core, while the M0+ core on the Onethinx module is locked. In order to use PSoC Creator as a "HW desing setup", you need to use Onethinx VSCode Project with it. You can download <a href="https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide">PSoC Creator here</a>.

    \image html vscreator_diagram.png width=600px

    The PSoC Creator project which is used to generate the API is located in the Onethinx Visual Studio Code (VSC) project. When you make the hardware configuration (in Top Design) and assign pins (in Pins), only thing you need is to successfully build the project (with no errors), and an API usable by the VSC will be generated. After creation of the API in PSoC Creator, the only thing that is needed to be done in VSC in order for it to recognise the generated API from PSoC Creator is to do a "Clean-Reconfigure". "Clean-Reconfigure" button is located at the bottom of the screen, next to the "Build" button. No need to #include any API. You can start writing the code using the API straight away.

    Open PSoC Creator Project by double clicking on the Onethinx_Creator.cyprj:

    \image html creatorOpen.png width=1200px

    You can create your hardware configuration in TopDesign. You can place components found on the right in "Component Catalog", and after placing them, you can edit the component, its name and its settings by double clicking on it. You can connect the lines with the "Wire" tool found on the left side of the TopDesign (marked purple). (NOTE: \ref faq_err_components).

    \image html TopDesign.png width=1200px

    Map your pins in the Pins tab. You can find which pins are available by checking out our <a href="https://github.com/onethinx/Core_Datasheet/blob/master/Onethinx_Core_Specification.pdf">Onethinx Datasheet</a>.
    \image html creatorPins.png width=1200px

    Use the "Build" button located in the top tray (marked with a blue box in both images). If successful, API will be generated which can be used in the VSCode project (after "Clean-Reconfigure"). API Datasheet can be found by right clicking on the specific component, while the API documentation can be found by going to Help->Documentation->Peripheral Driver Library.

    NOTE: When building for the PSoC Creator project for the first time, if you get promted to replace some files, click Replace.

    PSoC Creator<hr>
    
\page FAQ Frequently Asked Questions
\image html OTX_modulemarketing.png width=1000px
    \section faq_loralorawan LoRa vs LoRaWAN
    TODO LoRa, LoRaWAN, 1.0.2, Regional parameters
    \section faq_lwgateways LoRaWAN Gateways
    TODO
    \section faq_vscreator VSCode + PSoC Creator
    TODO
    \section faq_nws LoRaWAN Network Servers
    TODO TTN, chirpstack, etc.
    \section faq_otaa Over-the-Air Activation (OTAA)
    TODO
    \section faq_abp Activation by Personalization (ABP)
    TODO
    \section faq_err_components VSC Errors after changing names or component in Creator
    TODO (Delete exact components API libs (component which you removed or old component name API) in Generated Source in PSoC Creator Project)

\page extraResources Extra Resources
    \section er_structs Structures
        \subsection er_structs_lorawan_config      LoRaWAN configuration
        TODO
        \subsection er_structs_lorawan_status      LoRaWAN status
        TODO
        \subsection er_structs_lora_param          LoRa configuration
        TODO
        \subsection er_structs_lora_status         LoRa status
        TODO
    \section er_otxversions Module Versions
        \subsection otxversion_EU868 EU868
        In production and available. CE and LoRa Alliance certified.
        \subsection otxversion_US915 US915
        In production and available. FCC certified.
        \subsection otxversion_AU923 AU923
        Not yet available. Close to release.
        \subsection otxversion_IN865 IN865
        Not available.
    \section er_pinout Pinout
    TODO
    \section er_footprint Footprint
    TODO
    \section er_internaldeveui Internal DevEUI
    TODO UART OpenOCD OTX18-Programmer
    \section er_openocd OpenOCD Programming
    TODO

\page ex_examples Examples
    \section ex_helloworld  LoRaWAN Hello World
    TODO
    \section ex_light       LoRaWAN Analog Sensor
    TODO
    \section ex_lora        LoRa to LoRa
    TODO
    \section ex_capsense    CapSense Example
    TODO
    \section ex_deveui      DevEUI and Stack Version
        \code
            LoRaWAN_keys_t SomeOTAAkeys = {
                .KeyType					= OTAA_10x_key,
                .PublicNetwork					= true,
                .OTAA_10x.DevEui				= {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
                .OTAA_10x.AppEui				= {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
                .OTAA_10x.AppKey				= {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}
            };

            coreConfiguration_t	coreConfigMain = {
                .Join.KeysPtr = 		&SomeOTAAkeys,
                .Join.DataRate =		DR_AUTO,
                .Join.Power =			PWR_MAX,
                .Join.MAXTries = 		100,
                .TX.Confirmed = 		false,
                .TX.DataRate = 			DR_0,
                .TX.Power = 			PWR_MAX,
                .TX.FPort = 			1,
                .System.Idle.Mode = 	M0_DeepSleep,
                .System.Idle.BleEcoON = false,
                .System.Idle.DebugON  = true,
                .RX.Boost			  = false,
            };

            coreStatus_t coreStatus;
            coreInfo_t coreInfo;

            int main(void)
            {
                CyDelay(2000);
            
                /* enable global interrupts */
                __enable_irq();
                
                coreStatus = LoRaWAN_Init(&coreConfigMain);
                coreStatus = LoRaWAN_GetInfo(&coreInfo);
                /* >>> coreInfo.devEUI[] <<< Internal DevEUI here */
                /* >>> coreStatus.system.version <<< Stack Version */
                CyDelay(2000);
            }
        \endcode 

