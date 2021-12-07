# JustAudioFX - DSP Algorithms
Collection of audio FX plugins with algorithms explained, using Juce Framework. 

## Current list of digital audio FX algorithms:
* [Stereo Delay](./JustDelay)

![image](https://user-images.githubusercontent.com/6858921/142690302-c4676b8d-21e7-465e-bd95-13e96b29ef23.png)

* [Ping-Pong Delay](./JustPingPongDelay)

![image](https://user-images.githubusercontent.com/6858921/142690396-4f2484bc-35c3-406b-8652-deebe5cb1414.png)

## How to install compiled VST3 plugins?
All ready-to-use plugins are available in the [Releases](https://github.com/TheAvalanche/JustAudioFX/releases) page. 
* Download the \*.vst3 files
* Put the downloaded files into your default VST3 location (usually in `C:\Program Files\Common Files\VST3` on Windows)

## How to build and debug VST3 plugins?

> Currently build instructions only for Visual Studio 2019 and VST3. Feel free to extend it for other IDEs/plugin formats.

### Requirements
* JUCE and Projucer v6 (https://juce.com/get-juce/download) installed and ready to use
* Visual Studio 2019

### Step 1: Setup Projucer

* In Projucer choose File -> Global Paths to check, that your path to Juce and modules is correct. Example:
<img src="https://user-images.githubusercontent.com/6858921/144879649-3b75a13b-6cf8-4f2e-8f56-d086a042e9f4.png">

### Step 2: Prepare AudioPluginHost for debugging

* In Projucer choose File -> Open... and open `AudioPluginHost.jucer`, that is located in `${JUCE_PATH}/extras/AudioPluginHost`
* Select Visual Studio 2019 exporter and choose File -> Save Project and Open in IDE...
* After opening in Visual Studio, select Debug -> Start Debugging
* Check, that app is working and check either executable was built in `${JUCE_PATH}/extras/AudioPluginHost/Builds/VisualStudio2019/x64/Debug/App/AudioPluginHost.exe`

### Step 3: Clone and open the project in Visual Studio

* Clone the project
* In Projucer choose File -> Open... and select `*.jucer` file from the folder, that you want to launch
* In Projucer choose File -> Save Project and Open in IDE...

### Step 4: Setup debugging in Visual Studio

* In Visual Studio choose XXX_VST3 solution and set as Startup Project
* In Visual Studio select Debug -> XXX_VST3 Debug Properties
* In Configuration Properties -> Debugging put path to AudioPluginHost.exe
* In Visual Studio select Debug -> Start Debugging

### Step 5: Add your plugin to AudioPluginHost

* When AudioPluginHost is launched, add your plugin by pressing `Ctrl + P`. Then in Options choose 'Scan for new or updated VST3 plugins', add your project flder to the list and press 'Scan'
* Then go to Plugins -> Create Plug-in and select your new plugin
* Route inputs and outputs
* (Optional) you can save created graph to the file, not to route inputs and outputs every time
