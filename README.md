# <u>UVSim</u>
<div style="padding-left:2em;">
<i>
<b style="color:rgba(255,255,255,1)">UVSim</b> is a simple virtual machine used to help users execute their own machine language basicML code.
It contains a CPU, register, and main memory. An accumulator – a register into which information is put before the UVSim 
uses it in calculations or examines it in various ways.<br><br>All the information in the UVSim is handled in terms of words. 
A <b style="color:rgba(255,255,255,1)">word</b> is a signed four-digit decimal number, such as +1234, -5678. The UVSim is equipped with a 100-word memory, 
and these words are referenced by their location numbers 00, 01, ..., 99. The BasicML program must be loaded into the main 
memory starting at location 00 before executing. Each instruction written in BasicML occupies one word of the UVSim memory 
(instruction are signed four-digit decimal number). We shall assume that the sign of a BasicML instruction is always plus, 
but the sign of a data word may be either plus or minus. Each location in the UVSim memory may contain an instruction, 
a data value used by a program or an unused area of memory. The first two digits of each BasicML instruction are the 
operation code specifying the operation to be performed.
</i>
</div>

---

### <u>Installation</u>
<div style="padding-left: 2em">

 - Clone the repository.

    <i style="color:rgba(90,90,90,0.8);">**Note:** You will need the directory path of where you are placing your clone (or files) of the repository, So it may be worth jotting down the location.</i>
 - Create your UVSim's run file
</div>

#### For Windows:
<div style="padding-left: 2em">

<i style="color:rgba(90,90,90,0.8);"><b>Note:</b> The following instructions are tailored for using the [MinGW](https://www.mingw-w64.org/) g++ compiler and . But should be similar to other compiler usage. If you do not have a compiler for C++ installed please go to the Compiler section below and follow the MinGW setup instructions</i>

1. Open a Windows Command Prompt.

    <i style="color:rgba(90,90,90,0.8);">This can be done by searching for `cmd` in the Windows search bar and clicking on the Command Prompt application.</i>
2. Navigate to the directory where you cloned the repository.

    <i style="color:rgba(90,90,90,0.8);">This can be done by using the change directory `cd` command.</i>
     ```cmd
     cd path\to\repository
     ```
3. Here you will need to compile the UVSim's source code.
    ```cmd
    mingw32-make
    ```
4. Once the compilation is complete, you will have an executable file named `UVSim.exe` in the same directory as the source code. You will now proceed to the next section `Creating Your BasicML File` to create your BasicML file.

#### For MacOS:
<div style="padding-left: 2em">
<span style="color:rgba(255,0,0,0.8);">NOT CURRENTLY IMPLEMENTED</span>
</div>

#### For Linux:
<div style="padding-left: 2em">
<span style="color:rgba(255,0,0,0.8);">NOT CURRENTLY IMPLEMENTED</span>
</div>
</div>

---

### <u>Creating Your BasicML File</u>
<div style="padding-left: 2em">
As a final step before executing, you will need to create a plain text file with the extension `.txt` that contains lines of BasicML code you want to run in the UVSim.

All values should be in the following format of a signed four-digit decimal number (5 positional characters with first being a plus or minus symbol following by 4 digits with each being a integer between 0-9) and should be separated onto their own line: &nbsp;&nbsp;&nbsp;&nbsp;&plusmn; # # # #
<div style="padding-left: 3em">

<u>Example:</u>
<div style="padding-left: 3em">

```plaintext
+1007
+1008
+0000
+0000
```
</div>
</div>
</div>

For any lines that are meant to be instructions and not simply numeric values, you will still follow the same signed four-digit decimal number format but with the following structure: 

<div style="padding-left: 3em">
&plusmn; <u>[opcode]</u> <u>[memory address]</u>

Position 1: Sign<br>
Postion 2 & 3: Opcode<br>
Postion 4 & 5: Memory Address
</div>

<u>Visual Representation:</u>
<figure>
    <img src="resources/codeLineInfo.png" alt="Code Line Info" style="height:150px;border:3px solid black;">
</figure>

For a list of available opcodes and their descriptions, please refer to the Operation Codes section below.

<u>Operation Codes:</u>
<div style="padding-left: 3em">

<i>I/O operations:</i><br>
<b>10:</b> &nbsp;READ <i style="color:rgba(128,128,128,0.8);">&nbsp;– Read a word from the keyboard into a specific location in memory.</i><br>
<b>11:</b> &nbsp;WRITE <i style="color:rgba(128,128,128,0.8);">&nbsp;– Write a word from a specific location in memory to screen.</i><br>

<i>Load/store operations:</i><br>
<b>20:</b> &nbsp;LOAD <i style="color:rgba(128,128,128,0.8);">&nbsp;– Load a word from a specific location in memory into the accumulator.</i><br>
<b>21:</b> &nbsp;STORE <i style="color:rgba(128,128,128,0.8);">&nbsp;– Store a word from the accumulator into a specific location in memory.</i><br>

<i>Arithmetic operation:</i><br>
<b>30:</b> &nbsp;ADD <i style="color:rgba(128,128,128,0.8);">&nbsp;– Add a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator)</i><br>
<b>31:</b> &nbsp;SUBTRACT <i style="color:rgba(128,128,128,0.8);">&nbsp;– Subtract a word from a specific location in memory from the word in the accumulator (leave the result in the accumulator)</i><br>
<b>32:</b> &nbsp;DIVIDE <i style="color:rgba(128,128,128,0.8);">&nbsp;– Divide the word in the accumulator by a word from a specific location in memory (leave the result in the accumulator).</i><br>
<b>33:</b> &nbsp;MULTIPLY <i style="color:rgba(128,128,128,0.8);">&nbsp;– multiply a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator).</i><br>

<i>Control operation:</i><br>
<b>40:</b> &nbsp;BRANCH <i style="color:rgba(128,128,128,0.8);">&nbsp;– Branch to a specific location in memory</i><br>
<b>41:</b> &nbsp;BRANCHNEG <i style="color:rgba(128,128,128,0.8);">&nbsp;– Branch to a specific location in memory if the accumulator is negative.</i><br>
<b>42:</b> &nbsp;BRANCHZERO <i style="color:rgba(128,128,128,0.8);">&nbsp;– Branch to a specific location in memory if the accumulator is zero.</i><br>
<b>43:</b> &nbsp;HALT <i style="color:rgba(128,128,128,0.8);">&nbsp;– Stop the program</i><br>
</div>

---

### <u>Executing Your Code In The VM</u>
<div style="padding-left: 2em;">

1. If you closed your terminal or command prompt, reopen it and navigate to the directory where you cloned the repository.
2. Run the UVSim executable file.

    <i style="color:rgba(90,90,90,0.8);padding-left: 2em;">**Note:** If you are not at the directory where you cloned the repository, you will get an error message. Make sure to navigate to the correct directory.</i>
   
    <i style="color:rgba(128,128,128,0.8);padding-left: 2em;">For Windows:</i>`UVSim.exe`

    <i style="color:rgba(128,128,128,0.8);padding-left: 2em;">For MacOS:</i>`./UVSim`

    <i style="color:rgba(128,128,128,0.8);padding-left: 2em;">For Linux:</i>`./UVSim`
3. You will be prompted to enter the name of the file containing your BasicML code, this needs to be the file name with the extension `.txt`.

    <i style="color:rgba(90,90,90,0.8);padding-left: 2em;">**Note:** If you are not in the correct directory, you will get an error message. Make sure to navigate to the correct directory.</i>
4. The UVSim will execute your BasicML code and display the output in the terminal. If you have any I/O operations, you will be prompted to enter values.

    <i style="color:rgba(90,90,90,0.8);padding-left: 2em;">**Note:** If you have any I/O operations, you will need to enter values in the terminal. If you do not enter a value, the UVSim will not proceed.</i>
5. If you have no errors in your BasicML code, the UVSim will execute your code and perform the operations you have specified.

    <i style="color:rgba(90,90,90,0.8);padding-left: 2em;">**Note:** If you have any errors in your BasicML code, the UVSim will display an error message and stop the execution.</i>
6. If you need to run the UVSim again, want to try different or updated BasicML file, you can do so by repeating steps 2-5.
7. If you run into any issues where your code seems to be stuck in an infinite loop, you can stop the UVSim by pressing `Ctrl + C` or `cmd + C` in the terminal.

    <i style="color:rgba(90,90,90,0.8);padding-left: 2em;">**Note:** This will stop the UVSim and you will need to restart the UVSim to run your code again.</i>
</div>

---

### <u>Compiler</u>
<div style="padding-left: 2em">

#### For Windows:
<div style="padding-left: 2em">

   1. Install MinGW-w64:
      - Download and install [MinGW-w64-builds](https://www.mingw-w64.org/downloads).
      - During the installation process, make sure to include mingw32-make.
   2. Add MinGW-w64 to the System PATH:
      - Open the System Properties (Right-click on This PC or Computer on the desktop or in File Explorer, and then select Properties).
      - Click on Advanced system settings.
      - Click on Environment Variables.
      - In the System variables section, find the Path variable, and click Edit.
      - Add the path to your MinGW-w64 bin directory. For example:
      ```cmd
      C:\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin
      ```
      - Click OK to close all dialog boxes.
</div>
</div>

---